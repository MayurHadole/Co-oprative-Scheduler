#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"






TIM_HandleTypeDef tim1;

void cmdPWMtimerinit(int mode)
{
if(mode != CMD_INTERACTIVE) 
	{
    	return;
	}
	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Pin = (GPIO_PIN_8 | GPIO_PIN_9);
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = 6;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* Initialize PWM */
__TIM1_CLK_ENABLE();
tim1.Instance = TIM1;
tim1.Init.Prescaler =
 HAL_RCC_GetPCLK2Freq()*2/1000000;
tim1.Init.CounterMode   = TIM_COUNTERMODE_UP;
tim1.Init.Period        = 1000;
tim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
tim1.Init.RepetitionCounter = 0;
HAL_TIM_Base_Init(&tim1);

TIM_OC_InitTypeDef sConfig;
sConfig.OCMode       = TIM_OCMODE_PWM1;
sConfig.Pulse        = 500;
sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
sConfig.OCNPolarity  = TIM_OCNPOLARITY_LOW;
sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
sConfig.OCNIdleState =TIM_OCNIDLESTATE_RESET;
HAL_TIM_PWM_ConfigChannel(&tim1,&sConfig,TIM_CHANNEL_1);
HAL_TIM_PWM_ConfigChannel(&tim1,&sConfig,TIM_CHANNEL_2);  
HAL_TIM_PWM_ConfigChannel(&tim1,&sConfig,TIM_CHANNEL_3);  
printf("GPIO and Timer initialized");

}

void cmdPWM(int mode)
{
	int rc;
	uint32_t channel,value;
	rc = fetch_uint32_arg(&channel);
	if(rc) {
		printf("Missing channel");
	}
	rc = fetch_uint32_arg(&value);
	if(rc) {
		printf("Missing value");
	}

	if(channel==1)
	{
		HAL_TIM_PWM_Start(&tim1,TIM_CHANNEL_1);
		TIM1->CCR1 = value;
	}
	else if(channel==2)
	{
		HAL_TIM_PWM_Start(&tim1,TIM_CHANNEL_2);
		TIM1->CCR2 = value;
	}
	else if(channel==3)
	{
		HAL_TIM_PWM_Start(&tim1,TIM_CHANNEL_3);
		TIM1->CCR3 = value;
	}
	else if(channel==0)
	{
		HAL_TIM_PWM_Stop(&tim1,TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&tim1,TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&tim1,TIM_CHANNEL_3);
	}
}

void cmddcinit(int mode)
{
if(mode != CMD_INTERACTIVE) 
	{
    	return;
	}
	__GPIOF_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Pin = (GPIO_PIN_6| GPIO_PIN_9);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void cmddc(int mode)
{
  uint32_t dcDirection;
  	fetch_uint32_arg(&dcDirection);
  if(dcDirection== 1)
	{
 	 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,1);
 	 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,0);
	}
 else if(dcDirection == 2)
	{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,0);
 	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
	}
else if(dcDirection == 0)
	{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,0);
 	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,0);
	}
}


ADD_CMD("PWMtimerinit",cmdPWMtimerinit,"	PWM Timer Initialization");
ADD_CMD("PWM",cmdPWM," 		<channel> <value> Start PWM");
ADD_CMD("dcinit",cmddcinit," 		dc motor initialization");
ADD_CMD("dc",cmddc,"    <direction>     spin motor");


