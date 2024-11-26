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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "Key.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t RXDATA=0,RXDATA1=0,rx[11]={0},cq[5]={0xFF,0xAA,0x76,0x00,0x00},cntt=0,test_data,test_cnt=0,test_num[8]=" ",cq1[5]={0xFF,0xAA,0x69,0x88,0xB5},cq3[5]={0xFF,0xAA,0x00,0x00,0x00};
double yaw=0;
int Flag = 0, ffff = 0;
int16_t Speed1=0,Speed2=0,Speed3=0,Speed4=0;
int16_t Base_speed1=0,Base_speed2=0,Base_speed3=0,Base_speed4=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

uint8_t unlock_register[] = {0xFF, 0xAA, 0x69, 0x88, 0xB5};
uint8_t reset_z_axis[] = {0xFF, 0xAA, 0x76, 0x00, 0x00};
uint8_t set_output_200Hz[] = {0xFF, 0xAA, 0x03, 0x0B, 0x00};
uint8_t set_baudrate_115200[] = {0xFF, 0xAA, 0x04, 0x06, 0x00};
uint8_t save_settings[] = {0xFF, 0xAA, 0x00, 0x00, 0x00};
uint8_t restart_device[] = {0xFF, 0xAA, 0x00, 0xFF, 0x00};


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t Rx_String[100];    
uint8_t Rx_Flag=0;         
uint8_t Rx_buff,rx_buff = 0; 
int a = 0,b = 0;    
float x = 0,y = 0;  
double xielv = 0;   
__IO bool rxFrameFlag = 0;  
__IO uint8_t dj_rxCmd[128]; 
uint8_t maix_rxCmd[128];    
uint8_t k230_rxCmd[128];    
uint8_t BUFF[128];          
uint8_t xz[128];            
__IO uint8_t rxCount = 8;
int my_tmp = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
    ffff = 1;
	}
  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart1)
  { 
		if(Rx_String[Rx_Flag-1] == 0x0A) 
		{
			//HAL_UART_Transmit(&huart1, (uint8_t *)&Rx_String, Rx_Flag,0xFFFF); 
			//while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);      
      sscanf((const char * )Rx_String, "%d+%d", &a,&b);
			memset(Rx_String,0x00,sizeof(Rx_buff)); 
			Rx_Flag = 0; 
		}
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&Rx_buff, 1);   
  }
  
  if(huart->Instance==UART4)
  {
    static uint8_t i=0;
    rx[i]=RXDATA;
    if(rx[0]==0x55)
    {
      
      i+=1;
      if(i==11)
      {
        if(rx[1]==0x53)
        {
          if(rx[10]==(rx[0]+rx[1]+rx[2]+rx[3]+rx[4]+rx[5]+rx[6]+rx[7]+rx[8]+rx[9])%256)
          {
            yaw=(float)((short)((short)rx[7]*256+rx[6]))/32768*180;
            if(((int)(yaw*1000))%10>=5)
            {
              yaw=(double)((int)(yaw*100+1))/100;
            }
            else
            {
              yaw=(double)((int)(yaw*100))/100;
            }
            
          }
        }
        i=0;
      }
    }
    
    
    HAL_UART_Receive_IT(&huart4,&RXDATA,1);
  }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if(huart->Instance==USART1)
	{ 
    if(BUFF[0] != 'K')
		{
			
      memcpy(k230_rxCmd, BUFF, sizeof(BUFF));
      sscanf((const char * )k230_rxCmd, "%d+%d", &a,&b);
      memset(BUFF, 0x00, sizeof(BUFF));
      HAL_UARTEx_ReceiveToIdle_DMA(&huart1,(uint8_t*)BUFF,128);	
      //__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);
		}
	}


	if(huart->Instance==USART2)
	{
    rxFrameFlag = 1;
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2,(uint8_t*)dj_rxCmd,128);
	}
  
  
  if(huart->Instance==USART6)
	{
    rxFrameFlag = 1;
		HAL_UARTEx_ReceiveToIdle_DMA(&huart6,(uint8_t*)xz,128);
	}


  if(huart->Instance==USART3)
	{
    
    if(maix_rxCmd[0] == 'M')
		{
      sscanf((const char * )&maix_rxCmd[1], "%f+%f", &x,&y);
      // x = (int)xx;
      // y = (int)yy;
      HAL_UARTEx_ReceiveToIdle_DMA(&huart3,(uint8_t*)maix_rxCmd,128);					
		}
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void TBQD()
{
 Emm_V5_Synchronous_motion(0);
while(rxFrameFlag == false); rxFrameFlag = false;
}

void Go(int dir, int vel, int acc)
{
  HAL_TIM_Base_Stop_IT(&htim3);
  if(dir == 1)
  {
    Emm_V5_Vel_Control(1,1,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(3,1,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(2,0,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(4,0,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    TBQD();
    delay_ms(300);
  }
  if(dir == 0)
  {
    Emm_V5_Vel_Control(1,0,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(3,0,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(2,1,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    Emm_V5_Vel_Control(4,1,vel,acc,1);
    while(rxFrameFlag == false); rxFrameFlag = false;
    TBQD();
    delay_ms(300);
  }
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim3);
}

void Stop(int acc)
{
  HAL_TIM_Base_Stop_IT(&htim3);
  Emm_V5_Vel_Control(1,1,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,1,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,0,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,0,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  TBQD();
  delay_ms(700);
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim3);
}

void Stop1(int acc)
{
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Stop_IT(&htim3);
  Emm_V5_Vel_Control(1,1,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,1,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,0,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,0,0,acc,1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  TBQD();
  
}


void Set_Speed(uint8_t adr,int16_t speed)
{
  if(adr%2!=0)
  {
     if(speed>=0)
    {
      Emm_V5_Vel_Control(adr,1,speed,0,0);
      while(rxFrameFlag == false); rxFrameFlag = false;
    }
    else if(speed<0)
    {
      Emm_V5_Vel_Control(adr,0,-speed,0,0);
      while(rxFrameFlag == false); rxFrameFlag = false;
    }
  }
  else if(adr%2==0)
  {
     if(speed>=0)
    {
      Emm_V5_Vel_Control(adr,0,speed,0,0);
      while(rxFrameFlag == false); rxFrameFlag = false;
    }
    else if(speed<0)
    {
      Emm_V5_Vel_Control(adr,1,-speed,0,0);
      while(rxFrameFlag == false); rxFrameFlag = false;
    }
  }
  
  //delay_ms(10);
}



int i = 0;
int cmd[3] = {0};
int find_x(int x1, int v, int err, int xzb)
{
    int tmp ;
    tmp = x1;
    
 
    if(i > 2)
    {
        cmd[0] = cmd[1];
        cmd[1] = cmd[2];
        cmd[2] = tmp;
        tmp = (cmd[0] + cmd[1] + cmd[2])/3 ;
    }
    else
    {
        
        cmd[i] = tmp;
        tmp = (cmd[0] + cmd[1] + cmd[2]) / (i + 1);
    }
    i++;
    // OLED_ShowNum_double(0, 0,  tmp, &font12x12, OLED_COLOR_NORMAL);   
    // OLED_ShowFrame();
    tmp = tmp - 159;
    //delay_ms(5);
    if (tmp < err && tmp > -err)
    {
        /* code */
      Base_speed1=Base_speed4=0;
      Base_speed2=Base_speed3=0;
      delay_ms(200);
      i = 0;
      memset(cmd,0,sizeof(cmd));
      return 1;
    }

    else if (tmp >= err)
    {
      Base_speed1=Base_speed4=-v;
      Base_speed2=Base_speed3=-v;
    
    }
    else if (tmp <= -err)
    {
     Base_speed1=Base_speed4=v;
     Base_speed2=Base_speed3=v;
    }  

    return 0;
}

int find_y(int y1, int v, int err, int yzb)
{
    int tmp = 0;
    tmp = y1;
    

    if(i > 2)
    {
        cmd[0] = cmd[1];
        cmd[1] = cmd[2];
        cmd[2] = tmp;
        tmp = (cmd[0] + cmd[1] + cmd[2])/3 ;
    }
    else
    {
        cmd[i] = tmp;
        tmp = (cmd[0] + cmd[1] + cmd[2]) / (i + 1);
    }
    i++;
    // OLED_ShowNum_double(0, 20,  tmp, &font12x12, OLED_COLOR_NORMAL);   
    // OLED_ShowFrame();
    tmp = tmp - 106;
    //delay_ms(5);
    if (tmp < err && tmp > -err)
    {
        /* code */
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        delay_ms(200);
        i = 0;
        memset(cmd,0,sizeof(cmd));
        return 1;
    }

    else if (tmp >= err)
    {
      Base_speed1=Base_speed4=v;
      Base_speed2=Base_speed3=-v;
  
    }
    else if (tmp <= -err)
    {
      Base_speed1=Base_speed4=-v;
      Base_speed2=Base_speed3=v;
    
    }  

    return 0;
}



void color(uint8_t color, int v, int err, int xzb, int yzb)
{
    x = 0; y = 0;
    // __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
    // HAL_TIM_Base_Start_IT(&htim3);
    HAL_UART_Transmit(&huart3, &color, 1, HAL_MAX_DELAY);
    x = 0;
    delay_ms(20);
    while (1)
    {
      //delay_ms(10);
        if (x != 0)
        {//a ==1;
          if(find_x(x, v, err, xzb) == 1)
          {
            x = 0;
            break;
          }
        }
        
    }
    y = 0;
    delay_ms(20);   
    while (1)
    {
      //delay_ms(10);
      if (y != 0)
      {
        if(find_y(y, v, err, yzb) == 1)
        {
            y = 0;
            break;
        }
      }
    }
    Base_speed1=Base_speed4=0;
    Base_speed2=Base_speed3=0;
    HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
    delay_ms(100);
    
}


int P_flag = 0;
int find_pan(int x1, int zaiwu, uint8_t color)
{
  
  if (P_flag == 0)
  {
    HAL_UART_Transmit(&huart3, &color, 1, HAL_MAX_DELAY);
    P_flag = 1;
  }
  x1 = x1 - 160;
  if (x1 < 20 && x1 > -20)
  {
    HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
    zhua_pan(zaiwu);
    P_flag = 0;
    x1 = 0;
    x = 0;
    return 1;
  }
  return 0;
}
void shunxu(int num)
{
  // __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
  // delay_ms(300);
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Stop_IT(&htim3);
  delay_ms(10);
  Stop1(0);
  shengjiang(0, jiang_zhao);
  //delay_ms(700);
  x = 0;
  y = 0;
  //delay_ms(100);
  if (num == 123)
  {
    //Go(1, 70, 0);
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'r') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'g') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'b') == 1)
      {
        break;
      }
    }
    
  }
  if (num == 132)
  {
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'r') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'b') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'g') == 1)
      {
        break;
      }
    }
  }
  if (num == 213)
  {
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'g') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'r') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'b') == 1)
      {
        break;
      }
    }
  }
  if (num == 231)
  {
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'g') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'b') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'r') == 1)
      {
        break;
      }
    }
  }
  if (num == 321)
  {
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'b') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'g') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'r') == 1)
      {
        break;
      }
    }
  }
  if (num == 312)
  {
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 1, 'b') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 2, 'r') == 1)
      {
        break;
      }
    }
    while (1)
    {
      delay_ms(20);
      if (find_pan(x, 3, 'g') == 1)
      {
        break;
      }
    }
  }
  //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim3);
  
}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  
  
   if(htim->Instance==TIM3)
  {
    
    if(Flag==1)
    {
      Speed2=Speed4=Right(0,yaw,Speed1);
      Speed1=Speed3=Left(0,yaw,Speed2);
      Set_Speed(1,Speed1+Base_speed1);
      Set_Speed(2,Speed2+Base_speed2);
      Set_Speed(3,Speed3+Base_speed3);
      Set_Speed(4,Speed4+Base_speed4);
      //TBQD();
    }
    else if(Flag==2)
    {
      Speed2=Speed4=Right(90,yaw,Speed1);
      Speed1=Speed3=Left(90,yaw,Speed2);
      Set_Speed(1,Speed1+Base_speed1);
      Set_Speed(2,Speed2+Base_speed2);
      Set_Speed(3,Speed3+Base_speed3);
      Set_Speed(4,Speed4+Base_speed4);
      //TBQD();
    }
    else if(Flag==4)
    {
      Speed2=Speed4=Right(-90,yaw,Speed1);
      Speed1=Speed3=Left(-90,yaw,Speed2);
      Set_Speed(1,Speed1+Base_speed1);
      Set_Speed(2,Speed2+Base_speed2);
      Set_Speed(3,Speed3+Base_speed3);
      Set_Speed(4,Speed4+Base_speed4);
      //TBQD();
    }
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_USART6_UART_Init();
  MX_UART4_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  delay_ms(50);
  OLED_Init();
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)BUFF, 128);   //k230
 // __HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)dj_rxCmd, 128); 
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)maix_rxCmd, 128);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart6, (uint8_t *)xz, 128);   
  HAL_UART_Receive_IT(&huart4, &RXDATA, 1);             
  //HAL_TIM_Base_Start_IT(&htim2);
  
  
  
  
  
  HAL_UART_Transmit(&huart4, reset_z_axis, 5, 1000);
  delay_ms(2000);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);// pwm
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);// pwm
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);// pwm
  __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
  HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
  shengjiang(0, 0);
  xuanzhuan(1, 0);
  //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
  servo_angle(bi);
  //servo_angle(kai1);
  HAL_TIM_Base_Start_IT(&htim3);
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
tuopan_angle(zhong);
Stop(0);
// shengjiang(0, 0);
// xuanzhuan(1, zhuan_zheng);
// delay_ms(1000);
// servo_angle(bi);
// delay_ms(1000);
// shengjiang(0, jiang_di);
//zhua(1);
// xuanzhuan(1, zhuan_zheng);
// shengjiang(0, jiang_di);;



while (ffff == 0)
{
  delay_ms(10);
  
}
HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
delay_ms(100);
HAL_UART_Transmit(&huart4, reset_z_axis, 5, 1000);
delay_ms(200);
servo_angle(kai1);





/***************************************************************************************************************************** */
//chu
  // Base_speed1=Base_speed4=20;
  // Base_speed2=Base_speed3=-20;
  // Flag = 1;
  // delay_ms(1100);
  // Base_speed1=Base_speed4=0;
  // Base_speed2=Base_speed3=0;
  // delay_ms(200);
  




  //ma
  Go(1, 200, 230);
  Base_speed1=Base_speed4=200;
  Base_speed2=Base_speed3=200;
  Flag= 1;
  delay_ms(670);
  

  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(200);



// fang dang huang xian
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 1;
  delay_ms(550);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);

  
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Stop_IT(&htim3);
  delay_ms(10);
  Stop1(0);
  xuanzhuan(1, zhuan_zheng);
  //sao ma
  while(1)
  {
    delay_ms(100);
    if (a != 0)
    {
      // OLED_Init();
      // OLED_ShowNum(0, 0, a, 4, OLED_8X16);
      // OLED_ShowNum(0, 20, b, 4, OLED_8X16);
      // OLED_Update();
      break;
    }
    
  }
  // a = 231;
  // b = 123;
  HAL_TIM_Base_Start_IT(&htim3);
  
  
  //qu zhuan pan
  Go(1, 200, 230);
  Base_speed1=Base_speed4=200;
  Base_speed2=Base_speed3=200;
  Flag= 1;
  delay_ms(570);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);



  // cou jin zhuan pan
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 1;
  delay_ms(400);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  
  // __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  // HAL_TIM_Base_Stop_IT(&htim3);
  // Stop1(0);
  

  shunxu(a);
  //delay_ms(1500);


  // yan li zhuan pan
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 1;
  delay_ms(400);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);


  
  //hou tui qu cu jia gong
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag= 1;
  delay_ms(240);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);
  
  

  


  //zuo zhuan qu cu jia gong
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 2;
  while(yaw<=90)
    {
    
    }
   delay_ms(100);


   //z zhou qing ling
  HAL_UART_Transmit(&huart4, reset_z_axis, 5, 1000);
  
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  
  
  

  //zhi xing qu cu jia gong
  Go(1, 240, 230);
  Base_speed1=Base_speed4=240;
  Base_speed2=Base_speed3=240;
  Flag = 1;
  delay_ms(1445);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
   Flag = 1;
  delay_ms(100);
  
  
  
  //zuo zhuan fang cu jia gong
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 2;
  while(yaw<=90)
    {
    
    }
   delay_ms(100);






// //you yi dong cou jin
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 2;
  delay_ms(370);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  xingshi(a, 0, 1, 2);

  //delay_ms(200);


  //yi kai yuan li
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 2;
  delay_ms(600);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);

  
  //li kai cu jia gong dao guai jiao      hongse
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 2;
  delay_ms(520);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 2;
  delay_ms(100);

 
   



  

//   //zhuan xiang qu zan cun qu
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(800);




//  //zhi xing qu zan cun qu
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 1;
  delay_ms(675);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);
  

// //cou jin yi dian
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 1;
  delay_ms(650);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  

  xingshi(a, 0, 0, 1);

  
// // yuan li
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 1;
  delay_ms(600);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(200);



// //dao zhuan pan guai jiao
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 1;
  delay_ms(620);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);








 //guai jiao zhuan xiang
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 4;
  delay_ms(1500);
  

//  guai jiao zhi xing zhuan pan
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 4;
  delay_ms(210);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 4;
  delay_ms(100);


  // cou jin zhuan pan
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 4;
  delay_ms(450);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);

  // __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  // HAL_TIM_Base_Stop_IT(&htim3);
  // Stop1(0);
  shunxu(b);
  //delay_ms(1500);


  // yan li zhuan pan
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 4;
  delay_ms(450);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  

  

// //zhuan pan dao zhong jian
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 4;
  delay_ms(265);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 4;




  





// di er ci fang zhi  /################################################################################################################################/
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(1500);



  //zhi xing qu cu jia gong
  Go(1, 240, 230);
  Base_speed1=Base_speed4=240;
  Base_speed2=Base_speed3=240;
  Flag = 1;
  delay_ms(1445);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
   Flag = 1;
  delay_ms(200);
  
  
  
  //zuo zhuan fang cu jia gong
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 2;
  while(yaw<=90)
    {
    
    }
   delay_ms(500);






// //you yi dong cou jin
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 2;
  delay_ms(260);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  xingshi(b, 0, 1, 2);




  //yi kai yuan li
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 2;
  delay_ms(600);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);


  
  //li kai cu jia gong dao guai jiao      hongse
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 2;
  delay_ms(520);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 2;
  delay_ms(100);
 
   



//   //zhuan xiang qu zan cun qu
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(800);




//  //zhi xing qu zan cun qu
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 1;
  delay_ms(675);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);
  

// //cou jin yi dian
  Base_speed1=Base_speed4=-40;
  Base_speed2=Base_speed3=40;
  Flag = 1;
  delay_ms(775);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);
  

  

  xingshi(b, 1, 0, 1);
// // yuan li
  Base_speed1=Base_speed4=40;
  Base_speed2=Base_speed3=-40;
  Flag = 1;
  delay_ms(450);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);



// //dao zhuan pan guai jiao
  Go(0, 200, 230);
  Base_speed1=Base_speed4=-200;
  Base_speed2=Base_speed3=-200;
  Flag = 1;
  delay_ms(620);
  Stop(230);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 1;
  delay_ms(100);
 






 //guai jiao zhuan xiang
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 4;
  delay_ms(800);
  
//hui ku
  Go(0, 150, 230);
  Base_speed1=Base_speed4=-150;
  Base_speed2=Base_speed3=-150;
  Flag = 4;
  delay_ms(2000);
  Stop(100);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  Flag = 4;
  delay_ms(100);
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Stop_IT(&htim3);
  delay_ms(10);
  Stop1(0);
  xuanzhuan(1, 840);
  HAL_TIM_Base_Start_IT(&htim3);
  

    //Flag = 4;
    delay_ms(100);
    x = 0;
    HAL_UART_Transmit(&huart3, "y", 1, HAL_MAX_DELAY);
    Base_speed1=Base_speed4=-10;
    Base_speed2=Base_speed3=10;
    Flag = 4;
    delay_ms(20);
    x = 0;
    while (1)
    {
      delay_ms(20);
      if (x != 0)
      {
        while (1)
        {
          delay_ms(20);
          Base_speed1=Base_speed4=-10;
          Base_speed2=Base_speed3=10;
          Flag = 4;
          if (x < 270)
          {
            break;
          }
          
        }
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        delay_ms(200);
        break;
      }
    }
    HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
    delay_ms(200);
    HAL_TIM_Base_Stop_IT(&htim3);
    xuanzhuan(1, 0);
    HAL_TIM_Base_Start_IT(&htim3);
    delay_ms(200);
    Base_speed1=Base_speed4=-80;
    Base_speed2=Base_speed3=-80;
    x = 0;
    HAL_UART_Transmit(&huart3, "y", 1, HAL_MAX_DELAY);
    
    delay_ms(20);
    while (1)
    {
      delay_ms(20);
      if (x != 0)
      {
        while (1)
        {
          delay_ms(20);
          Base_speed1=Base_speed4=-10;
          Base_speed2=Base_speed3=-10;
          Flag = 4;
          if (x > 130)
          {
            break;
          }
          
        }
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
        delay_ms(200);
        break;
      }
    }


    Base_speed1=Base_speed4=0;
    Base_speed2=Base_speed3=0;
    HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
    delay_ms(20);




  Base_speed1=Base_speed4=-20;
  Base_speed2=Base_speed3=20;
  Flag = 4;
  delay_ms(200);
  Base_speed1=Base_speed4=0;
  Base_speed2=Base_speed3=0;
  delay_ms(100);

  
  
  
  while (1)
  {



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
