#include "ds3231.h"
#include "../drivers/twi.h"
#include "../../include/config.h"

static uint8_t dec_to_bcd(uint8_t val) {
    return (uint8_t)(((val / 10) << 4) | (val % 10));
}

static uint8_t bcd_to_dec(uint8_t val) {
    return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));
}

status_t ds3231_init(void) {
    twi_init();
    return STATUS_OK;
}

status_t ds3231_set_time(const ds3231_time_t *time) {
    if (!time) return STATUS_ERROR;

    if (twi_start() != STATUS_OK) return STATUS_ERROR;
    if (twi_write((DS3231_I2C_ADDR << 1) | TWI_WRITE) != STATUS_OK) {
        twi_stop();
        return STATUS_ERROR;
    }

    twi_write(0x00); /* Start from register 0x00 */
    twi_write(dec_to_bcd(time->seconds));
    twi_write(dec_to_bcd(time->minutes));
    twi_write(dec_to_bcd(time->hours & 0x3F));
    twi_write(dec_to_bcd(time->day_of_week));
    twi_write(dec_to_bcd(time->date));
    twi_write(dec_to_bcd(time->month));
    twi_write(dec_to_bcd(time->year));
    twi_stop();

    return STATUS_OK;
}

status_t ds3231_get_time(ds3231_time_t *time) {
    if (!time) return STATUS_ERROR;

    uint8_t raw[7];
    if (twi_read_bytes(DS3231_I2C_ADDR, 0x00, raw, 7) != STATUS_OK) {
        return STATUS_ERROR;
    }

    time->seconds     = bcd_to_dec(raw[0] & 0x7F);
    time->minutes     = bcd_to_dec(raw[1] & 0x7F);
    time->hours       = bcd_to_dec(raw[2] & 0x3F);
    time->day_of_week = bcd_to_dec(raw[3] & 0x07);
    time->date        = bcd_to_dec(raw[4] & 0x3F);
    time->month       = bcd_to_dec(raw[5] & 0x1F);
    time->year        = bcd_to_dec(raw[6]);

    return STATUS_OK;
}
