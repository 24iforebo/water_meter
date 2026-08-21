#ifndef GSM_H
#define GSM_H

#include "../../include/types.h"

void gsm_power_init(void);
void gsm_power_on(void);
void gsm_power_off(void);

status_t gsm_init(void);
status_t gsm_send_command(const char *cmd);
status_t gsm_wait_response(const char *expected, uint16_t timeout_ms);
status_t gsm_send_sms(const char *phone_number, const char *message);

#endif /* GSM_H */
