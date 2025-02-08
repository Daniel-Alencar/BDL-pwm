#include <stdio.h>
// Inclui a biblioteca padrão para funcionalidades básicas
#include "pico/stdlib.h"
// Inclui a biblioteca para gerenciamento de temporizadores de hardware.
#include "hardware/timer.h"

//biblioteca para controlar o hardware de PWM
#include "hardware/pwm.h" 
#include "pwm/pwm.h"

#define USE_BITDOGLAB true

#if USE_BITDOGLAB
  #define PWM_PIN 12
#else
  #define PWM_PIN 22
#endif

#define FREQUENCY 50
#define F_CLOCK 125000000
#define WRAP 65465
#define D_I 38
#define D_F 3

#define DUTY_CYCLE_1 0.12   // 180º
#define DUTY_CYCLE_2 0.0735 // 90º
#define DUTY_CYCLE_3 0.025  // 0º

#define DUTY_CYCLE_STEP 0.001

uint scene = 0;
double duty_cycle_servo = DUTY_CYCLE_3;
bool duty_cycle_servo_increase = true;
static volatile uint pwm_signal_state = 0;

// Função de callback do alarme
int64_t switch_pwm_signal(alarm_id_t id, void *user_data);
void move_servo_slowly();

int main() {

  stdio_init_all();

  //habilitar o pino GPIO como PWM
  gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
  //obter o canal PWM da GPIO
  uint slice = pwm_gpio_to_slice_num(PWM_PIN); 
  //definir o valor de wrap
  pwm_set_wrap(slice, WRAP);

  // uint *parameters;
  // compute_pwm_parameters(FREQUENCY, F_CLOCK, &parameters);
  // compute_pwm_frequency(F_CLOCK, WRAP, D_I, D_F);

  //define o divisor de clock do PWM
  pwm_set_clkdiv(slice, D_I + (D_F) / 10.0);

  printf("Duty Cycle 1\n");
  //definir o ciclo de trabalho (duty cycle) do pwm
  pwm_set_gpio_level(PWM_PIN, WRAP * DUTY_CYCLE_1);
  //habilita o pwm no slice correspondente
  pwm_set_enabled(slice, true);

  add_alarm_in_ms(5000, switch_pwm_signal, NULL, false);
  pwm_signal_state++;

  while (true) {
    printf("No loop\n");
    if(scene) {
      move_servo_slowly();
    }
    sleep_ms(500);
  }
}

void move_servo_slowly() {
  while (true) {
    if(duty_cycle_servo_increase) {
      if(duty_cycle_servo + DUTY_CYCLE_STEP <= DUTY_CYCLE_1) {
        duty_cycle_servo += DUTY_CYCLE_STEP;
      } else if (duty_cycle_servo - DUTY_CYCLE_STEP >= DUTY_CYCLE_3) {
        duty_cycle_servo_increase = false;
        duty_cycle_servo -= DUTY_CYCLE_STEP;
      }
    } else {
      if(duty_cycle_servo - DUTY_CYCLE_STEP >= DUTY_CYCLE_3) {
        duty_cycle_servo -= DUTY_CYCLE_STEP;
      } else if(duty_cycle_servo + DUTY_CYCLE_STEP <= DUTY_CYCLE_1) {
        duty_cycle_servo_increase = true;
        duty_cycle_servo += DUTY_CYCLE_STEP;
      } 
    }
    printf("changing PWM duty cycle\n");
    //definir o ciclo de trabalho (duty cycle) do pwm
    pwm_set_gpio_level(PWM_PIN, WRAP * duty_cycle_servo);
    sleep_ms(10);
  }
}

int64_t switch_pwm_signal(alarm_id_t id, void *user_data) {
  if(pwm_signal_state == 0) {
    printf("Duty Cycle 1\n");
    pwm_set_gpio_level(PWM_PIN, WRAP * DUTY_CYCLE_1);
    add_alarm_in_ms(5000, switch_pwm_signal, NULL, false);
    pwm_signal_state++;
  } else if (pwm_signal_state == 1) {
    printf("Duty Cycle 2\n");
    pwm_set_gpio_level(PWM_PIN, WRAP * DUTY_CYCLE_2);
    add_alarm_in_ms(5000, switch_pwm_signal, NULL, false);
    pwm_signal_state++;
  } else if (pwm_signal_state == 2) {
    printf("Duty Cycle 3\n");
    pwm_set_gpio_level(PWM_PIN, WRAP * DUTY_CYCLE_3);
    add_alarm_in_ms(5000, switch_pwm_signal, NULL, false);
    pwm_signal_state++;
  } else if (pwm_signal_state == 3) {
    scene++;
  }
}