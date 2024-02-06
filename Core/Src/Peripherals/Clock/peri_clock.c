/**
 ******************************************************************************
 *  @attention
 *
 *  All Rights Reserved
 *  Copyright (C) 2023  Henry Odoemelem <hodoemelem@gmail.com>
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *******************************************************************************
 */
#include "io.h"
#include "peri_clock.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h" // Device header
void peri_clock_init()
{
	RCC_AHB2ENR_wr(GPIOAEN, SETBIT, WRITE); // enable GPIOA clk, port A
	RCC_AHB2ENR_wr(GPIOBEN, SETBIT, WRITE); // enable gpiob clock rm pg251
	RCC_AHB2ENR_wr(GPIOCEN, SETBIT, WRITE);

	RCC_APB2ENR_wr(USART_1EN, SETBIT, WRITE);
	RCC_APB1ENR1_wr(USART2EN, SETBIT, WRITE);
	RCC_APB1ENR1_wr(USART3EN, SETBIT, WRITE);

	RCC_APB1ENR1_wr(I2C1EN, SETBIT, WRITE);

	RCC_AHB1ENR_wr(DMA_1EN, SETBIT, WRITE);

	RCC_APB1ENR1_wr(TIM2EN, SETBIT, WRITE);
	RCC_APB2ENR_wr(TIM_1EN, SETBIT, WRITE);
	RCC_APB1ENR1_wr(TIM3EN, SETBIT, WRITE);
}
void systick_delay_ms(int n)
{
	// Based  on 72MHz clk
	SysTick->LOAD = 72000 - 1; // 1m sec event @72MHz clk
	SysTick->VAL = 0;		   // Clear current value reg.
	SysTick->CTRL = 0x5;	   // Enable Systick

	for (int i = 0; i < n; i++)
	{
		while ((SysTick->CTRL & 0x10000) == 0)
			;
	}
	SysTick->CTRL = 0; // Disable SysTick
}

void systick_delay_us(int n)
{
	// Based  on 72MHz clk
	SysTick->LOAD = 72 - 1; // 1u sec event @72MHz clk
	SysTick->VAL = 0;		// Clear current value reg.
	SysTick->CTRL = 0x5;	// Enable Systick and use processor clock

	for (int i = 0; i < n; i++)
	{
		while ((SysTick->CTRL & 0x10000) == 0)
			;
	}
	SysTick->CTRL = 0; // Disable SysTick
}

// /**
//  * @brief  This function is executed in case of error occurrence.
//  * @retval None
//  */
// void Error_Handler(void)
// {
// 	/* USER CODE BEGIN Error_Handler_Debug */
// 	/* User can add his own implementation to report the HAL error return state */

// 	/* USER CODE END Error_Handler_Debug */
// }

// /**
//  * @brief System Clock Configuration using timer not system clock
//  * @retval None
//  */
// void SystemClock_Config(void)
// {
// 	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
// 	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

// 	/** Initializes the RCC Oscillators according to the specified parameters
// 	 * in the RCC_OscInitTypeDef structure.
// 	 */
// 	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
// 	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
// 	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
// 	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
// 	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
// 	RCC_OscInitStruct.PLL.PLLM = 1;
// 	RCC_OscInitStruct.PLL.PLLN = 9; // 72MHz
// 	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
// 	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
// 	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
// 	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
// 	{
// 		Error_Handler();
// 	}
// 	/** Initializes the CPU, AHB and APB buses clocks
// 	 */
// 	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
// 	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
// 	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
// 	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; // then x2 for timer
// 	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

// 	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
// 	{
// 		Error_Handler();
// 	}
// 	/** Configure the main internal regulator output voltage
// 	 */
// 	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
// 	{
// 		Error_Handler();
// 	}
// }

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM7 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM7)
	{
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */