#include "flow_sensor.h"
#include "../drivers/gpio.h"
#include "../../include/config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile uint32_t total_pulse_count = 0;
static volatile uint32_t interval_pulse_count = 0;

ISR(INT0_vect) {
    total_pulse_count++;
    interval_pulse_count++;
}

void flow_sensor_init(void) {
    /* PD2 (INT0) configured as input with pullup */
    gpio_pin_mode(GPIO_PORT_D, FLOW_SENSOR_PIN_NUM, GPIO_MODE_INPUT_PULLUP);

    /* Trigger INT0 on falling edge */
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);
}

uint32_t flow_sensor_get_pulse_count(void) {
    uint32_t count;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        count = total_pulse_count;
    }
    return count;
}

void flow_sensor_set_pulse_count(uint32_t count) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        total_pulse_count = count;
    }
}

float flow_sensor_get_total_volume(void) {
    uint32_t count = flow_sensor_get_pulse_count();
    return (float)count / FLOW_PULSES_PER_LITER;
}

float flow_sensor_get_flow_rate(uint32_t sample_period_ms) {
    if (sample_period_ms == 0) return 0.0f;

    uint32_t pulses;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        pulses = interval_pulse_count;
        interval_pulse_count = 0;
    }

    /* Flow rate in L/min */
    float liters = (float)pulses / FLOW_PULSES_PER_LITER;
    return (liters / ((float)sample_period_ms / 60000.0f));
}

void flow_sensor_reset(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        total_pulse_count = 0;
        interval_pulse_count = 0;
    }
}
