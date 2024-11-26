#include "find.h"
// PID初始化函数
// void PID_Init(PID *pid, float Kp, float Ki, float Kd, float setpoint) {
//     pid->Kp = Kp;
//     pid->Ki = Ki;
//     pid->Kd = Kd;
//     pid->setpoint = setpoint;
//     pid->integral = 0;
//     pid->last_error = 0;
// }


// // PID计算函数
// float PID_Calculate(PID *pid, float current_value) 
// {
//     float error = pid->setpoint - current_value; // 计算误差
//     pid->integral += error; // 更新积分值
//     float derivative = error - pid->last_error; // 计算微分值
//     pid->last_error = error; // 更新上一次的误差

//     // 限制输出值在-100到100之间
//     float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
//     if (output > 100) {
//         output = 100;
//     } else if (output < -100) {
//         output = -100;
//     }
//     return output;
// }




//centrol find
// int find_x(int x)
// {
//     int tmp;
//     tmp = x;
//     static int i = 0;
//     static int cmd[3] = {0};
//     i++;
//     cmd[i] = x;
    
 
//     if(i > 2)
//     {
//         cmd[0] = cmd[1];
//         cmd[1] = cmd[2];
//         cmd[2] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2])/3 ;
//     }
//     else
//     {
//         cmd[i] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2]) / i;
//     }
//     // OLED_ShowNum_double(0, 0,  tmp, &font12x12, OLED_COLOR_NORMAL);   
//     // OLED_ShowFrame();
//     tmp = tmp - 120;
//     if (tmp < 5 && tmp > -5)
//     {
//         /* code */
//         Car_stop();
//         //    wait();
//         return 1;
//     }

//     if (tmp > 10)
//     {
//         /* code 
//         后退
//         */
//     //    Car_down(2, 0, 5, 0);
//     //    wait();
//      Car_down1(3, 1);
//     //    wait();
    
//     }
//     else if (tmp < -10)
//     {
//         /* code 
//         前进
//         */
//     //    Car_go(2, 0, 5, 0);
//     //    wait();
//      Car_go1(3, 1);
//     //    wait();
    
//     }  

//     return 0;
// }

// int find_y(int y)
// {
//     int tmp;
//     tmp = y;
//     static int i = 0;
//     static int cmd[3] = {0};
//     i++;
//     cmd[i] = y;
//     if(i > 2)
//     {
//         cmd[0] = cmd[1];
//         cmd[1] = cmd[2];
//         cmd[2] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2])/3 ;
//     }
//     else
//     {
//         cmd[i] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2]) / i;
//     }
//     // OLED_ShowNum_double(0, 20,  tmp, &font12x12, OLED_COLOR_NORMAL);   
//     // OLED_ShowFrame();
//     tmp = tmp - 40;
//     if (tmp < 5 && tmp > -5)
//     {
//         /* code */
//         Car_stop();
//         return 1;
//     }

//     if (tmp > 5)
//     {
//         /* code 
//         后退
//         */
//     Car_r1(2, 1);
    
//     }
//     if (tmp < -5)
//     {
//         /* code 
//         前进
//         */
//     Car_l1(2, 1);
    
//     }  

//     return 0;
// }

// int wai(double slope)
// {
//     double tmp;
//     tmp = slope;
//     static int i = 0;
//     static double cmd[3] = {0};
//     i++;
//     cmd[i] = slope;
//     if(i > 2)
//       {
//         cmd[0] = cmd[1];
//         cmd[1] = cmd[2];
//         cmd[2] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2])/3 ;
//       }
//       else
//       {
//         cmd[i] = tmp;
//         tmp = (cmd[0] + cmd[1] + cmd[2]) / i;
//       }
    
//     if (tmp < 0.020 && tmp > -0.020)
//     {
//         /* code */
//         Car_stop();
//         return 1;
//     }

//     if (tmp > 0.02)
//     {
//         /* code 
        
//         */
//        Car_yr1(2, 1);
       
//     }
//     if (tmp < -0.02)
//     {
//         /* code 
        
//         */
//        Car_yl1(2, 1);
       
//     }  
//     return 0;
// }


// void color(uint8_t color)
// {
//     HAL_UART_Transmit(&huart3, &color, 1, HAL_MAX_DELAY);
//     x = 0;
//     while (1)
//     {
//         HAL_Delay(80);
//         if (x != 0)
//         {
//         //HAL_Delay(10);
        
//         /* code */
//             if(find_x(x) == 1)
//             {
            
//             break;
//             }
//         }
        
//     }
//     y = 0;
//     while (1)
//     {
//     HAL_Delay(80);
//         if (y != 0)
//         {
        
//         /* code */
//         if(find_y(y) == 1)
//         {
            
//             break;
//         }
//         }
//     }
//     HAL_UART_Transmit(&huart3, "a", 1, HAL_MAX_DELAY);
//     xielv = 0;
//     // while (1)
//     // {
//     // HAL_Delay(80);
//     //     if (xielv != 0)
//     //     {
        
//     //     /* code */
//     //     if(wai(xielv) == 1)
//     //     {
            
//     //         break;
//     //     }
//     //     }
//     // }
// }

