/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    freertos_tickless.c
  * @author  GPM Application Team
  * @brief   Management of timers and ticks
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
#include <stdio.h>
#include "freertos_tickless.h"
#include "bsp_conf.h"
#include "main.h"
#include "app_config.h"
#include "utilities_conf.h"
#if (LOW_POWER_MODE != LOW_POWER_DISABLE)
#include "stm32_lpm.h"
#endif /* LOW_POWER_MODE */

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Global variables ----------------------------------------------------------*/
#if (LOW_POWER_MODE != LOW_POWER_DISABLE)
#ifndef LPTIM_HANDLE
#error "LPTIM instance not selected. Please use platform settings panel in STM32CubeMX GUI."
#endif /* LPTIM_HANDLE */

/** LPTIM handle */
extern LPTIM_HandleTypeDef LPTIM_HANDLE;
#endif /* LOW_POWER_MODE */

/* USER CODE BEGIN GV */

/* USER CODE END GV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void DisableSuppressTicksAndSleep(uint32_t bitmask)
{
  /* USER CODE BEGIN DisableSuppressTicksAndSleep_1 */
  #warning("LowPower implementation provided only for STM32U5 devices. Up to the users to implement for other device families.");

  /* USER CODE END DisableSuppressTicksAndSleep_1 */
}

void EnableSuppressTicksAndSleep(uint32_t bitmask)
{
  /* USER CODE BEGIN EnableSuppressTicksAndSleep_1 */
  #warning("LowPower implementation provided only for STM32U5 devices. Up to the users to implement for other device families.");

  /* USER CODE END EnableSuppressTicksAndSleep_1 */
}

#if (LOW_POWER_MODE != LOW_POWER_DISABLE)
void vPortSetupTimerInterrupt(void);
void vPortSetupTimerInterrupt(void)
{
  /* USER CODE BEGIN vPortSetupTimerInterrupt_1 */
  #warning("LowPower implementation provided only for STM32U5 devices. Up to the users to implement for other device families.");

  /* USER CODE END vPortSetupTimerInterrupt_1 */
  /* USER CODE BEGIN vPortSetupTimerInterrupt_End */

  /* USER CODE END vPortSetupTimerInterrupt_End */
}
#endif /* LOW_POWER_MODE */

void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime)
{
#if (LOW_POWER_MODE != LOW_POWER_DISABLE)
  /* USER CODE BEGIN vPortSuppressTicksAndSleep_1 */
  #warning("LowPower implementation provided only for STM32U5 devices. Up to the users to implement for other device families.");

  /* USER CODE END vPortSuppressTicksAndSleep_1 */
#endif /* LOW_POWER_MODE */
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/* Private Functions Definition ----------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */
