#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile uint32_t system_millis = 0;

ISR(TIMER0_COMPA_vect) {
    system_millis++;
}

void timer_init(void) {
    /* Configure Timer0 in CTC mode, 1ms interrupt at 16MHz */
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00); /* Prescaler 64 */
    OCR0A = 249;
    TIMSK0 |= (1 << OCIE0A);
}

uint32_t timer_millis(void) {
    uint32_t ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms = system_millis;
    }
    return ms;
}
