#include "button.h"
#include "../drivers/gpio.h"
#include "../../include/config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile bool button_pressed_flag = false;

ISR(INT1_vect) {
    button_pressed_flag = true;
}

void button_init(void) {
    /* Set PD3 as input with internal pull-up */
    gpio_pin_mode(GPIO_PORT_D, BUTTON_PIN_NUM, GPIO_MODE_INPUT_PULLUP);

    /* Configure INT1 for falling edge */
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);
    EIMSK |= (1 << INT1);
}

bool button_was_pressed(void) {
    bool flag;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        flag = button_pressed_flag;
        button_pressed_flag = false;
    }
    return flag;
}

bool button_is_down(void) {
    return (gpio_pin_read(GPIO_PORT_D, BUTTON_PIN_NUM) == GPIO_PIN_LOW);
}
