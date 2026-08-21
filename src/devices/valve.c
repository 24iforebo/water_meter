#include "valve.h"
#include "../drivers/gpio.h"
#include "../../include/config.h"

static valve_state_t current_valve_state = VALVE_CLOSED;

void valve_init(void) {
    gpio_pin_mode(GPIO_PORT_B, VALVE_PIN_NUM, GPIO_MODE_OUTPUT);
    valve_close();
}

void valve_open(void) {
    gpio_pin_write(GPIO_PORT_B, VALVE_PIN_NUM, GPIO_PIN_HIGH);
    current_valve_state = VALVE_OPEN;
}

void valve_close(void) {
    gpio_pin_write(GPIO_PORT_B, VALVE_PIN_NUM, GPIO_PIN_LOW);
    current_valve_state = VALVE_CLOSED;
}

void valve_toggle(void) {
    if (current_valve_state == VALVE_OPEN) {
        valve_close();
    } else {
        valve_open();
    }
}

valve_state_t valve_get_state(void) {
    return current_valve_state;
}
