#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H

#include "../../include/types.h"

#define EEPROM_MAGIC_KEY    0x574D5452 /* "WMTR" */

typedef struct {
    uint32_t magic;
    uint32_t total_pulses;
    float total_volume_liters;
} eeprom_meter_data_t;

void eeprom_driver_init(void);
void eeprom_save_meter_data(uint32_t pulses, float liters);
bool eeprom_load_meter_data(uint32_t *pulses, float *liters);

#endif /* EEPROM_DRIVER_H */
