#ifndef GPIO_H
#define GPIO_H

#include "../../include/types.h"
#include <avr/io.h>

typedef enum {
    GPIO_PORT_B = 0,
    GPIO_PORT_C,
    GPIO_PORT_D
} gpio_port_t;

typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_INPUT_PULLUP
} gpio_mode_t;

typedef enum {
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH = 1
} gpio_state_t;

void gpio_pin_mode(gpio_port_t port, uint8_t pin, gpio_mode_t mode);
void gpio_pin_write(gpio_port_t port, uint8_t pin, gpio_state_t state);
gpio_state_t gpio_pin_read(gpio_port_t port, uint8_t pin);
void gpio_pin_toggle(gpio_port_t port, uint8_t pin);

#endif /* GPIO_H */
