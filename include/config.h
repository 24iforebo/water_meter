#ifndef CONFIG_H
#define CONFIG_H

#ifndef F_CPU
#define F_CPU                   16000000UL
#endif

/* Communication Settings */
#define UART_BAUD_RATE          9600UL
#define TWI_BITRATE             100000UL

/* I2C Device Addresses (7-bit) */
#define DS3231_I2C_ADDR         0x68
#define LCD_I2C_ADDR            0x27

/* Pin Configurations */
#define VALVE_PORT              PORTB
#define VALVE_DDR               DDRB
#define VALVE_PIN               PINB
#define VALVE_PIN_NUM           0

#define GSM_PWR_PORT            PORTB
#define GSM_PWR_DDR             DDRB
#define GSM_PWR_PIN             PINB
#define GSM_PWR_PIN_NUM         1

#define FLOW_SENSOR_PORT        PORTD
#define FLOW_SENSOR_DDR         DDRD
#define FLOW_SENSOR_PIN         PIND
#define FLOW_SENSOR_PIN_NUM     2

#define BUTTON_PORT             PORTD
#define BUTTON_DDR              DDRD
#define BUTTON_PIN              PIND
#define BUTTON_PIN_NUM          3

/* Flow Sensor Calibration */
#define FLOW_PULSES_PER_LITER   450.0f

/* Power & Display Timing */
#define LCD_ACTIVE_TIMEOUT_MS   5000UL
#define EEPROM_SAVE_INTERVAL_MS 60000UL

#endif /* CONFIG_H */
