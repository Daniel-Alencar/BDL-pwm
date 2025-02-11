#include "pwd.h"

#define FREQUENCY 50
#define F_CLOCK 125000000

int main() {
    compute_pwm_parameters(FREQUENCY, F_CLOCK);
}