#ifndef VALVE_H
#define VALVE_H

#include "../../include/types.h"

typedef enum {
    VALVE_CLOSED = 0,
    VALVE_OPEN = 1
} valve_state_t;

void valve_init(void);
void valve_open(void);
void valve_close(void);
void valve_toggle(void);
valve_state_t valve_get_state(void);

#endif /* VALVE_H */
