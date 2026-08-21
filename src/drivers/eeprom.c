#include "eeprom.h"
#include <avr/eeprom.h>

static eeprom_meter_data_t EEMEM eeprom_storage;

void eeprom_driver_init(void) {
    /* No special hardware initialization required for internal EEPROM */
}

void eeprom_save_meter_data(uint32_t pulses, float liters) {
    eeprom_meter_data_t data;
    data.magic = EEPROM_MAGIC_KEY;
    data.total_pulses = pulses;
    data.total_volume_liters = liters;

    eeprom_update_block(&data, &eeprom_storage, sizeof(eeprom_meter_data_t));
}

bool eeprom_load_meter_data(uint32_t *pulses, float *liters) {
    eeprom_meter_data_t data;
    eeprom_read_block(&data, &eeprom_storage, sizeof(eeprom_meter_data_t));

    if (data.magic != EEPROM_MAGIC_KEY) {
        return false;
    }

    if (pulses) *pulses = data.total_pulses;
    if (liters) *liters = data.total_volume_liters;
    return true;
}
