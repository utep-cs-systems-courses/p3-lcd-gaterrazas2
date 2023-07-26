#ifndef BUZZER_H
#define BUZZER_H

#define MIN_PERIOD 8000
#define MAX_PERIOD 100

void buzzer_init();
void buzzer_advance_frequency();
void buzzer_set_period(short cycles);

#endif /* BUZZER_H */
