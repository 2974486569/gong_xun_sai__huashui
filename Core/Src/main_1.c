/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rc522_function.h"
#include "oled.h"
#include "font.h"
#include "stdio.h"
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

/* USER CODE BEGIN PV */
unsigned char  data1[16] = {0x12,0x34,0x56,0x78,0xED,0xCB,0xA9,0x87,0x12,0x34,0x56,0x78,0x04,~0x04,0x04,~0x04};

//M1卡的某一块写为如下格式，则该块为钱包，可接收扣款和充值命令
//4字节金额（低字节在前）＋4字节金额取反＋4字节金额＋1字节块地址＋1字节块地址取反＋1字节块地址＋1字节块地址取反 
unsigned char  data2[4]  = {0,0,0,1};
unsigned char  DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 


unsigned char g_ucTempbuf[20];  
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	  unsigned char status;
	  unsigned int temp,i,temp1;
	uint8_t flag=0,flag1=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(20);
	char buff[20];
  OLED_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
			OLED_NewFrame();
			OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
			OLED_ShowFrame();
			status = PcdRequest(PICC_REQALL, g_ucTempbuf);//寻卡
		
		
		
		
		
		
			if (status != MI_OK)
			{    

					PcdReset();
					PcdAntennaOff(); 
					PcdAntennaOn(); 
					continue;
			}
			status = PcdAnticoll(g_ucTempbuf);//防冲撞
			if (status != MI_OK)
			{    
						continue;    
			}	
			status = PcdSelect(g_ucTempbuf);//选定卡片
			if (status != MI_OK)
			{    
					continue;    
			}
			status = PcdAuthState(PICC_AUTHENT1A, 4, DefaultKey, g_ucTempbuf);//验证卡片密码
			if (status != MI_OK)
			{    
					continue;    
			}
			status = PcdWrite(4, data1);//写块
			if (status != MI_OK)
			{    
					continue;    
			}

			
			
			
				while ( 1 )
				{
								  
						status = PcdRequest(PICC_REQALL, g_ucTempbuf);//寻卡 
						if (status != MI_OK)
						{   								
								PcdReset();
								PcdAntennaOff(); 
								PcdAntennaOn(); 
								continue; 
						}
						status = PcdAnticoll(g_ucTempbuf);//防冲撞 
						if (status != MI_OK)
						{    
								continue;    
						}
						for(i=0;i<4;i++)
			      {
				       temp=temp<<8;
					     temp|=g_ucTempbuf[i];
				       temp1=temp;
			      }
						//显示卡id
			      sprintf(buff,"%X",temp1);
												
						
						if(temp1==0X332A8913&&flag==0)
						{
							OLED_NewFrame();
						  OLED_PrintString(0,5,"Welcome!",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(0,20,"王玉坤",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(32,40,"借书成功",&font16x16,OLED_COLOR_NORMAL);
						  OLED_ShowFrame();
							HAL_Delay(1000);
							OLED_NewFrame();
							OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
							OLED_ShowFrame();
							flag=1;
							temp1=0;
							HAL_Delay(1000);
						}
						if(temp1==0X332A8913&&flag==1)
						{
							OLED_NewFrame();
						  OLED_PrintString(0,5,"Welcome!",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(0,20,"王玉坤",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(32,40,"还书成功",&font16x16,OLED_COLOR_NORMAL);
						  OLED_ShowFrame();
							HAL_Delay(1000);
							OLED_NewFrame();
							OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
							OLED_ShowFrame();
							flag=0;
							temp1=0;
							HAL_Delay(1000);
						}
						
						if(temp1==0X430BEBE4&&flag1==0)
						{
							OLED_NewFrame();
						  OLED_PrintString(0,5,"Welcome!",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(0,20,"李波霖",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(32,40,"借书成功",&font16x16,OLED_COLOR_NORMAL);
						  OLED_ShowFrame();
							HAL_Delay(1000);
							OLED_NewFrame();
							OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
							OLED_ShowFrame();
							flag1=1;
							temp1=0;
							HAL_Delay(1000);
						}
						
						if(temp1==0X430BEBE4&&flag1==1)
						{
							OLED_NewFrame();
						  OLED_PrintString(0,5,"Welcome!",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(0,20,"李波霖",&font16x16,OLED_COLOR_NORMAL);
						  OLED_PrintString(32,40,"还书成功",&font16x16,OLED_COLOR_NORMAL);
						  OLED_ShowFrame();
							HAL_Delay(1000);
							OLED_NewFrame();
							OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
							OLED_ShowFrame();
							flag1=0;
							temp1=0;
							HAL_Delay(1000);
						}
						
						
//						OLED_NewFrame();
//						OLED_PrintString(32,25,"借书成功",&font16x16,OLED_COLOR_NORMAL);
//						OLED_ShowFrame();
//						
//						OLED_NewFrame();
//						OLED_PrintString(15,25,"图书管理系统",&font16x16,OLED_COLOR_NORMAL);
//						OLED_ShowFrame();

					}
				
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_0)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
