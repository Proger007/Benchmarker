//
// Created by root on 5/10/25.
//

#include "board.h"

#include "bsp.h"

#include "stm32u5xx_hal_icache.h"
#include "stm32u5xx_hal_flash.h"

extern "C"
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    return HAL_OK;
}

namespace {
  [[noreturn]] void Error_Handler()
  {
    while (true);
  }

  /**
    * @brief System Clock Configuration
    * @retval None
    */
  void SystemClock_Config()
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE2) != HAL_OK)
    {
      Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                                       |RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
    RCC_OscInitStruct.PLL.PLLM = 3;
    RCC_OscInitStruct.PLL.PLLN = 12;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
    RCC_OscInitStruct.PLL.PLLFRACN = 4096;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                                  |RCC_CLOCKTYPE_PCLK3;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
      Error_Handler();
    }
  }

  /**
    * @brief Power Configuration
    * @retval None
    */
  void SystemPower_Config()
  {
    HAL_PWREx_EnableVddIO2();

    /*
     * Switch to SMPS regulator instead of LDO
     */
    if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
    {
      Error_Handler();
    }
    /* USER CODE BEGIN PWR */
    /* USER CODE END PWR */
  }
  /**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
  void MX_ICACHE_Init()
  {

    /* USER CODE BEGIN ICACHE_Init 0 */

    /* USER CODE END ICACHE_Init 0 */

    /* USER CODE BEGIN ICACHE_Init 1 */

    /* USER CODE END ICACHE_Init 1 */

    /** Enable instruction cache in 1-way (direct mapped cache)
    */
    if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_ICACHE_Enable() != HAL_OK)
    {
      Error_Handler();
    }
    /* USER CODE BEGIN ICACHE_Init 2 */

    /* USER CODE END ICACHE_Init 2 */

  }
}

void board::init()
{
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Configure the System Power */
    SystemPower_Config();

    MX_ICACHE_Init();

    __HAL_FLASH_PREFETCH_BUFFER_DISABLE();

    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_3);

    DWT->CYCCNT = 0;
}

void board::disableCache()
{
  HAL_ICACHE_Disable();
}

void board::enableCache()
{
  HAL_ICACHE_Enable();
}

