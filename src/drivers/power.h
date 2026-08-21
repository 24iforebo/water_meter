#ifndef POWER_H
#define POWER_H

#include "../../include/types.h"
#include <avr/sleep.h>
#include <avr/power.h>

void power_init(void);
void power_enter_sleep(void);
void power_disable_peripherals(void);
void power_enable_peripherals(void);

#endif /* POWER_H */
