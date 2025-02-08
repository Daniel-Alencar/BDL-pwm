#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

//biblioteca para controlar o hardware de PWM
#include "hardware/pwm.h" 
#include "pwm/pwm.h"

#define PWM_PIN 22

#define FREQUENCY 50
#define F_CLOCK 125000000
#define WRAP 65465
#define D_I 38
#define D_F 3

int main() {

  stdio_init_all();

  //habilitar o pino GPIO como PWM
  gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
  //obter o canal PWM da GPIO
  uint slice = pwm_gpio_to_slice_num(PWM_PIN); 
  //definir o valor de wrap
  pwm_set_wrap(slice, WRAP);

  uint *parameters;
  compute_pwm_parameters(FREQUENCY, F_CLOCK, &parameters);
  compute_pwm_frequency(F_CLOCK, WRAP, D_I, D_F);

  //define o divisor de clock do PWM
  pwm_set_clkdiv(slice, D_I + (D_F) / 10.0); 
  //definir o ciclo de trabalho (duty cycle) do pwm
  pwm_set_gpio_level(PWM_PIN, WRAP / 2);
  
  //habilita o pwm no slice correspondente
  pwm_set_enabled(slice, true); 

  while (true) {
    printf("No loop\n");
    sleep_ms(500);
  }
}