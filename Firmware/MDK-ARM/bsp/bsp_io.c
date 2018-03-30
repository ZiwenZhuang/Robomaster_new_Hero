
#include "bsp_io.h"
#include "sys_config.h"
#include "tim.h"


void turn_on_laser(void)
{
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
}

void turn_off_laser(void)
{
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
}

void turn_on_friction_wheel(uint16_t spd)
{
  LEFT_FRICTION  = spd;
  RIGHT_FIRCTION = spd;
	LEFT_42_FRACTION = spd;
	RIGHT_42_FRACTION = spd;
}

void turn_off_friction_wheel(void)
{
  LEFT_FRICTION  = 1000;
  RIGHT_FIRCTION = 1000;
	LEFT_42_FRACTION = 1000;
	RIGHT_42_FRACTION = 1000;
}

void mpu_heat_ctrl(uint16_t pwm_pulse)
{
  IMU_PWM_PULSE = pwm_pulse;
}


void pwm_device_init(void)
{
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // ctrl imu temperature
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // beep
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2); // friction wheel //TODO
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // 42mm fraction
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);	// 42mm fraction
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	TIM8->CCR1=0;	//丝杆电机1运转
	TIM8->CCR4=0;	//丝杆电机2运转
	TIM8->CCR2=0;	//丝杆电机方向
	TIM8->CCR3=4000;	//风扇转速
	TIM2->CCR1=0;	//辅助轮不转
	TIM2->CCR2=0;	//辅助轮不转
	TIM2->CCR3=1600;	//舵机1
	TIM2->CCR4=5200;	//舵机2
}

uint8_t sd_insert(void)
{
  return !HAL_GPIO_ReadPin(SD_EXTI_GPIO_Port, SD_EXTI_Pin);
}
