#include "gsm.h"
#include "../drivers/uart.h"
#include "../drivers/timer.h"
#include "../drivers/gpio.h"
#include "../../include/system.h"
#include "../../include/config.h"
#include <string.h>
#include <stdio.h>

void gsm_power_init(void) {
    gpio_pin_mode(GPIO_PORT_B, GSM_PWR_PIN_NUM, GPIO_MODE_OUTPUT);
    gsm_power_off();
}

void gsm_power_on(void) {
    gpio_pin_write(GPIO_PORT_B, GSM_PWR_PIN_NUM, GPIO_PIN_HIGH);
}

void gsm_power_off(void) {
    gpio_pin_write(GPIO_PORT_B, GSM_PWR_PIN_NUM, GPIO_PIN_LOW);
}

status_t gsm_init(void) {
    gsm_power_on();
    uart_init(UART_BAUD_RATE);
    delay_ms(1000);

    gsm_send_command("AT\r\n");
    if (gsm_wait_response("OK", 2000) != STATUS_OK) {
        return STATUS_ERROR;
    }

    /* Set SMS to text mode */
    gsm_send_command("AT+CMGF=1\r\n");
    if (gsm_wait_response("OK", 2000) != STATUS_OK) {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

status_t gsm_send_command(const char *cmd) {
    if (!cmd) return STATUS_ERROR;
    uart_print(cmd);
    return STATUS_OK;
}

status_t gsm_wait_response(const char *expected, uint16_t timeout_ms) {
    if (!expected) return STATUS_ERROR;

    char buffer[64];
    uint8_t idx = 0;
    uint32_t start_time = timer_millis();

    while ((timer_millis() - start_time) < timeout_ms) {
        if (uart_available()) {
            char c = uart_receive();
            if (idx < sizeof(buffer) - 1) {
                buffer[idx++] = c;
                buffer[idx] = '\0';
                if (strstr(buffer, expected) != NULL) {
                    return STATUS_OK;
                }
            }
        }
    }
    return STATUS_TIMEOUT;
}

status_t gsm_send_sms(const char *phone_number, const char *message) {
    if (!phone_number || !message) return STATUS_ERROR;

    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+CMGS=\"%s\"\r\n", phone_number);
    gsm_send_command(cmd);

    if (gsm_wait_response(">", 3000) != STATUS_OK) {
        return STATUS_ERROR;
    }

    uart_print(message);
    uart_transmit(0x1A); /* Ctrl+Z to send */

    return gsm_wait_response("OK", 10000);
}
