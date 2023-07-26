#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"

static unsigned int period = 4000;
static signed int rate = 200;

void buzzer_init() {
  timerAUpmode();
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_advance_frequency() {
  period += rate;
  if (period > MAX_PERIOD || period < MIN_PERIOD) {
    rate = -rate;
    period += rate * 2;
  }
  buzzer_set_period(period);
}

void buzzer_set_period(short cycles) {
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}
