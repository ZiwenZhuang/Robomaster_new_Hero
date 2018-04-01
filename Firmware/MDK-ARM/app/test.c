#include "test.h"
#include "sys_config.h"
#include "RemoteTask.h"
#include "imu_task.h"
#include "gimbal_task.h"
#include "chassis_task.h"
#include "shoot_task.h"
#include "PC_communication_task.h"
UBaseType_t test_task_stack_surplus;
uint32_t test_wake_time;
extern float can2_buf[3];
void test_task( const void* argu){
	
	
	  test_wake_time= osKernelSysTick();
  while(1)
  {
		//used in calibrate
		#ifndef CALI_DONE
		update_gimbal_sensor();
		printf("pit_relative ecd %f imu %f , yaw_relative ecd %f imu %f \r\n",
		gim.sensor.pit_relative_angle_ecd,
		gim.sensor.pit_relative_angle_imu,
		gim.sensor.yaw_relative_angle_ecd,
		gim.sensor.yaw_relative_angle_imu);
		printf("imu offset pit %f yaw %f \r\n",gim.sensor.pit_offset_angle_imu,gim.sensor.yaw_offset_angle_imu);
		
		printf("encoder: yaw %d pitch %d  \r\n",gim.yaw_motor.ecd,gim.pit_motor.ecd);
		printf("atti is pitch: %f yaw: %f roll: %f\r\n",atti.pitch,atti.yaw,atti.roll);
		//printf("mpu  gx %d gy %d gz:%d \r\n",mpu_data.gx,mpu_data.gy,mpu_data.gz);		
		#endif
		
		//LED_G_TOGGLE;
		
		
		
     //printf("can2_buf is %f %f %f \r\n",can2_buf[0],can2_buf[1],can2_buf[2]);
		//printf("test\r\n");
		//test_shoot_task();
		//send_all_pack_to_pc();
		
		// Ӣ�۳�˿�˵�����ƴ���
		if (KEY_Q)
		{
			puts("Q");
			send_gimbal_cur(0,1000,0);	//Ͷ����
		}
		else if (KEY_E)
		{
			puts("E");
			send_gimbal_cur(0,-1000,0);	//Ͷ����
		}
		else
		{
			send_gimbal_cur(0,0,0);
		}
		if (KEY_F)	//���״̬�ı�
		{
			puts("F");
			//TIM2->CCR3=5200;	//���1��ק
			//TIM2->CCR4=1600;	//���2��ק
			TIM2->CCR3=6800-TIM2->CCR3;
			TIM2->CCR4=6800-TIM2->CCR4;
			osDelay(200);
		}
		/*
		if (KEY_G)
		{
			TIM2->CCR3=1600;  //���1��λ
			TIM2->CCR4=5200;	//���2��λ
			
		}*/
		if (KEY_Z)
		{
			puts("Z");
			//TIM2->CCR2=40000;	//��������ת���ٰ�ֹͣ
			TIM2->CCR2=40000-TIM2->CCR2;
			TIM2->CCR1=0;
			osDelay(200);
		}
		if (KEY_X)
		{
			TIM2->CCR1=40000-TIM2->CCR1;;	//�����ַ�����ת���ٰ�ֹͣ
			TIM2->CCR2=0;
			osDelay(200);
		}
		if (KEY_CTRL)
		{
			TIM8->CCR1=1000;	//˿��1��ת��40sȫ�̣�����Ƶ�ʸļ���
		}
		else
		{
			TIM8->CCR1=0;		//˿��1��ֹ
		}
		if (KEY_C)
		{
			TIM8->CCR4=1000;	//˿��2��ת
		}
		else
		{
			TIM8->CCR4=0;		//˿��2��ֹ
		}
		if (KEY_V)
		{
			TIM8->CCR2=4000;	//˿��������ת
		}
		if (KEY_B)
		{
			TIM8->CCR2=0;			//˿��������ת
		}
		if (KEY_R)
		{
			TIM8->CCR3=4000-TIM8->CCR3;		//���ȿ���
			osDelay(200);
		}
		// ˿�˵���������
		
    test_task_stack_surplus = uxTaskGetStackHighWaterMark(NULL);
    
    osDelayUntil(&test_wake_time, TEST_TASK_PERIOD);  
  }
}
