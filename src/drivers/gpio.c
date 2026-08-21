#include "gpio.h"

void gpio_pin_mode(gpio_port_t port, uint8_t pin, gpio_mode_t mode) {
    volatile uint8_t *ddr;
    volatile uint8_t *port_reg;

    switch (port) {
        case GPIO_PORT_B:
            ddr = &DDRB;
            port_reg = &PORTB;
            break;
        case GPIO_PORT_C:
            ddr = &DDRC;
            port_reg = &PORTC;
            break;
        case GPIO_PORT_D:
            ddr = &DDRD;
            port_reg = &PORTD;
            break;
        default:
            return;
    }

    if (mode == GPIO_MODE_OUTPUT) {
        *ddr |= (1 << pin);
    } else {
        *ddr &= ~(1 << pin);
        if (mode == GPIO_MODE_INPUT_PULLUP) {
            *port_reg |= (1 << pin);
        } else {
            *port_reg &= ~(1 << pin);
        }
    }
}

void gpio_pin_write(gpio_port_t port, uint8_t pin, gpio_state_t state) {
    volatile uint8_t *port_reg;

    switch (port) {
        case GPIO_PORT_B:
            port_reg = &PORTB;
            break;
        case GPIO_PORT_C:
            port_reg = &PORTC;
            break;
        case GPIO_PORT_D:
            port_reg = &PORTD;
            break;
        default:
            return;
    }

    if (state == GPIO_PIN_HIGH) {
        *port_reg |= (1 << pin);
    } else {
        *port_reg &= ~(1 << pin);
    }
}

gpio_state_t gpio_pin_read(gpio_port_t port, uint8_t pin) {
    volatile uint8_t *pin_reg;

    switch (port) {
        case GPIO_PORT_B:
            pin_reg = &PINB;
            break;
        case GPIO_PORT_C:
            pin_reg = &PINC;
            break;
        case GPIO_PORT_D:
            pin_reg = &PIND;
            break;
        default:
            return GPIO_PIN_LOW;
    }

    return (*pin_reg & (1 << pin)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
}

void gpio_pin_toggle(gpio_port_t port, uint8_t pin) {
    volatile uint8_t *port_reg;

    switch (port) {
        case GPIO_PORT_B:
            port_reg = &PORTB;
            break;
        case GPIO_PORT_C:
            port_reg = &PORTC;
            break;
        case GPIO_PORT_D:
            port_reg = &PORTD;
            break;
        default:
            return;
    }

    *port_reg ^= (1 << pin);
}
