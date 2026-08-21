#ifndef DS3231_H
#define DS3231_H

#include "../../include/types.h"

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} ds3231_time_t;

status_t ds3231_init(void);
status_t ds3231_set_time(const ds3231_time_t *time);
status_t ds3231_get_time(ds3231_time_t *time);

#endif /* DS3231_H */
