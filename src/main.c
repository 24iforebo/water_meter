#include "../include/system.h"
#include "drivers/timer.h"
#include "drivers/gpio.h"
#include "drivers/twi.h"
#include "drivers/uart.h"
#include "drivers/power.h"
#include "drivers/eeprom.h"
#include "devices/lcd.h"
#include "devices/valve.h"
#include "devices/button.h"
#include "devices/ds3231.h"
#include "sensors/flow_sensor.h"
#include "communication/gsm.h"
#include <stdio.h>

int main(void) {
    /* Initialize core drivers */
    system_init();
    timer_init();
    power_init();
    twi_init();
    uart_init(UART_BAUD_RATE);

    /* Initialize storage and restore previous readings */
    eeprom_driver_init();
    uint32_t saved_pulses = 0;
    float saved_liters = 0.0f;
    if (eeprom_load_meter_data(&saved_pulses, &saved_liters)) {
        flow_sensor_set_pulse_count(saved_pulses);
    }

    /* Initialize peripherals and devices */
    button_init();
    valve_init();
    valve_open();
    flow_sensor_init();
    gsm_power_init();

    /* Initialize LCD and display initial screen */
    lcd_init();
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Water Meter Init");
    ds3231_init();

    uint32_t last_display_activity = timer_millis();
    uint32_t last_eeprom_save = timer_millis();
    uint32_t last_measurement = timer_millis();
    bool display_active = true;
    char display_buf[17];

    while (1) {
        uint32_t now = timer_millis();

        /* Check for button press to wake/activate LCD */
        if (button_was_pressed()) {
            if (!display_active) {
                lcd_display_on();
                display_active = true;
            }
            last_display_activity = now;
        }

        /* Periodic measurement and display refresh if active */
        if (now - last_measurement >= 1000) {
            float flow_rate = flow_sensor_get_flow_rate(1000);
            float total_vol = flow_sensor_get_total_volume();

            if (display_active) {
                lcd_set_cursor(0, 0);
                snprintf(display_buf, sizeof(display_buf), "Flow: %d.%02d L/m",
                         (int)flow_rate, (int)((flow_rate - (int)flow_rate) * 100));
                lcd_print(display_buf);

                lcd_set_cursor(1, 0);
                snprintf(display_buf, sizeof(display_buf), "Total:%d.%02d L",
                         (int)total_vol, (int)((total_vol - (int)total_vol) * 100));
                lcd_print(display_buf);
            }

            last_measurement = now;
        }

        /* Timeout LCD display to save power */
        if (display_active && (now - last_display_activity >= LCD_ACTIVE_TIMEOUT_MS)) {
            lcd_display_off();
            display_active = false;
        }

        /* Periodic EEPROM backup to prevent data loss */
        if (now - last_eeprom_save >= EEPROM_SAVE_INTERVAL_MS) {
            eeprom_save_meter_data(flow_sensor_get_pulse_count(), flow_sensor_get_total_volume());
            last_eeprom_save = now;
        }
    }

    return 0;
}
