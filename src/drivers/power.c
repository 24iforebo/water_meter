#include "power.h"
#include <avr/interrupt.h>

void power_init(void) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void power_enter_sleep(void) {
    sleep_enable();
    sei();

#if defined(sleep_bod_disable)
    sleep_bod_disable();
#endif

    sleep_cpu();
    sleep_disable();
}

void power_disable_peripherals(void) {
    power_adc_disable();
    power_spi_disable();
}

void power_enable_peripherals(void) {
    power_adc_enable();
    power_spi_enable();
}
