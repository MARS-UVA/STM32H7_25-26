/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "serial.h"
#include "fdcan.h"
#include "usart.h"
#include "debug.h"
#include "pdp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern int enableSync;
extern uint8_t rx_buff[16];
extern SerialPacket motorValues;
extern int count;
extern FDCAN_HandleTypeDef hfdcan1;
extern UART_HandleTypeDef huart6;
PDP pdp;
/* USER CODE END Variables */
/* Definitions for ControlTask */
osThreadId_t ControlTaskHandle;
const osThreadAttr_t ControlTask_attributes = {
  .name = "ControlTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for FeedbackTask */
osThreadId_t FeedbackTaskHandle;
const osThreadAttr_t FeedbackTask_attributes = {
  .name = "FeedbackTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ADCTask */
osThreadId_t ADCTaskHandle;
const osThreadAttr_t ADCTask_attributes = {
  .name = "ADCTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void can_irq(FDCAN_HandleTypeDef *pcan);
/* USER CODE END FunctionPrototypes */

void ControlTaskFunction(void *argument);
void FeedbackTaskFunction(void *argument);
void ADCTaskFunction(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ControlTask */
  ControlTaskHandle = osThreadNew(ControlTaskFunction, NULL, &ControlTask_attributes);

  /* creation of FeedbackTask */
  FeedbackTaskHandle = osThreadNew(FeedbackTaskFunction, NULL, &FeedbackTask_attributes);

  /* creation of ADCTask */
  ADCTaskHandle = osThreadNew(ADCTaskFunction, NULL, &ADCTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_ControlTaskFunction */
/**
  * @brief  Function implementing the ControlTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ControlTaskFunction */
void ControlTaskFunction(void *argument)
{
  /* USER CODE BEGIN ControlTaskFunction */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
	  //sendGlobalEnableFrame(&hfdcan1);
	  //sendCANMessage(&hfdcan1, 0x204b540 | 36, (uint8_t *)"\x00\x01\x00\x00\x00\x00\xfe\x0c", 8);
	  /**if (HAL_UART_Receive_IT(&huart6, rx_buff, 16) != HAL_OK){
		  HAL_StatusTypeDef state1 = HAL_UART_Receive_IT(&huart6, rx_buff, 16);
		  writeDebugFormat("HAL_UART_Receive_IT returned %d\n", (int)state1);
		  writeDebugString("wrong");
	  }**/
	directControl(motorValues, enableSync); // send CAN packets to motors to set motor speeds
    osDelay(10);
  }
  /* USER CODE END ControlTaskFunction */
}

/* USER CODE BEGIN Header_FeedbackTaskFunction */
/**
* @brief Function implementing the FeedbackTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FeedbackTaskFunction */
void FeedbackTaskFunction(void *argument)
{
  /* USER CODE BEGIN FeedbackTaskFunction */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END FeedbackTaskFunction */
}

/* USER CODE BEGIN Header_ADCTaskFunction */
/**
* @brief Function implementing the ADCTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ADCTaskFunction */
void ADCTaskFunction(void *argument)
{
  /* USER CODE BEGIN ADCTaskFunction */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END ADCTaskFunction */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
// This function is called upon receiving a motor command packet over UART
#define START_BYTE 255

// Check if start byte exists in motor command packets
int findStartByte(uint8_t *rx_buff, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (rx_buff[i] == START_BYTE)
		{
			return i;
		}
	}

	return -1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (HAL_UART_Receive_IT(huart, rx_buff, 16) != HAL_OK)
	{
		writeDebugString("ERROR OCCURED DURING UART RX INTERRUPT\r\n");
	}
	else{
		writeDebugString("ts working");
		int startByte = findStartByte(rx_buff, 8);
			if (startByte == -1)
				return;

			if (startByte == 0 && rx_buff[8] == START_BYTE)
				startByte += 8;

			count = 0;
			motorValues = (SerialPacket) {
				.invalid = 0,
				.header = rx_buff[startByte + 1],
				.top_left_wheel = rx_buff[startByte + 2],
				.back_left_wheel = rx_buff[startByte + 3],
				.top_right_wheel  = rx_buff[startByte + 4],
				.back_right_wheel = rx_buff[startByte + 5],
				.drum  = rx_buff[startByte + 6],
				.actuator  = rx_buff[startByte + 7],
			};

	}
}

void can_irq(FDCAN_HandleTypeDef *pfdcan)
{
  FDCAN_RxHeaderTypeDef msg;
  uint64_t data;
  HAL_FDCAN_GetRxMessage(pfdcan, FDCAN_RX_FIFO0, &msg, (uint8_t *) &data);
  if (pdp.receiveCAN)
	  pdp.receiveCAN(&pdp, &msg, &data);
}


/* USER CODE END Application */

