#include "jixiebi.h"

int servo_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    return 0;
}


/**
 * @brief 设置伺服电机的角度
 * 
 * 本函数将给定的角度转换为伺服电机控制所需的脉宽调制(PWM)信号占空比，并设置到相应的定时器通道。
 * 这个转换基于特定的数学关系，即新的PWM占空比（用于控制伺服电机的角度）通过给定的角度值计算得出。
 * 
 * @param angle 期望的伺服电机角度，使用角度值
 * @return int 返回0，表示函数执行正常（无错误代码返回表示成功）
 */
int servo_angle(int angle)
{
    angle = (angle * 10 / 9) + 50;
    angle = angle * 2 / 3;
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, angle);
    return 0;
}
int tuopan_angle(int angle)
{
    angle = (angle * 10 / 9) + 50;
    angle = angle * 2 / 3;
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, angle+10);
    return 0;
}



/**
 * @brief 转动函数
 * @param dir 方向
 * @param angle 期望的电机角度，使用角度值，脉冲值
 * @return int 返回0，表示函数执行正常（无错误代码返回表示成功）
 */


void xuanzhuan(int dir, int angle)
{

    /* code */
  //ZDT_X42_V2_Traj_Position_Control5(5, dir, 300, 300, 1200, angle, 1, 0);
  Emm_V5_Pos_Control(5, dir, 70, 100, angle, 1, 0);
  while(rxFrameFlag == false); rxFrameFlag = false;
  wait5(); 
}

void shengjiang(int dir, int angle)
{

    /* code */
  ZDT_X42_V2_Traj_Position_Control(6, dir, 600, 250, angle, 1, 0);
  while(rxFrameFlag == false); rxFrameFlag = false;
  wait6(); 
}



//yi 120 wei qi dian
//123 rgb
void zhua(int x)
{
    
    if (x == 1)
    {
        tuopan_angle(zhong);
        //shengjiang(0, 0);
        shengjiang(0, jiang_maix);
        xuanzhuan(1, zhuan_zheng);
        servo_angle(kai1);
        shengjiang(0, jiang_di);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        servo_angle(kai1);
        shengjiang(0, jiang_maix);
    }
    else if (x == 2)
    {
        tuopan_angle(chu);
        //shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        servo_angle(kai1);
        shengjiang(0, jiang_di);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        servo_angle(kai1);
        shengjiang(0, jiang_maix);
    }
    else if (x == 3)
    {
        tuopan_angle(mo);
        //shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        servo_angle(kai1);
        shengjiang(0, jiang_di);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        tuopan_angle(zhong);
        servo_angle(kai1);
        shengjiang(0, jiang_maix);
    }
}

// 123: 132 16 250  di
//11 12 13: 132 16 250 duo
void fang(int x)
{
    if (x == 1)
    {
        tuopan_angle(zhong);
        servo_angle(kai2);
        shengjiang(0, 0);
        delay_ms(300);
        
        xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_di);
        servo_angle(kai1);
        delay_ms(700);
        shengjiang(0, jiang_maix);
    }
    else if (x == 2)
    {
        tuopan_angle(chu);
        servo_angle(kai2);
        shengjiang(0, 0);
        delay_ms(500);
        //xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_di);
        servo_angle(kai1);
        delay_ms(700);
        //shengjiang(0, 0);
        shengjiang(0, jiang_maix);
    }
    else if (x == 3)
    {
        tuopan_angle(mo);
        servo_angle(kai2);
        shengjiang(0, 0);
        delay_ms(700);
        //xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_di);
        servo_angle(kai1);
        delay_ms(700);
        tuopan_angle(zhong);
        shengjiang(0, jiang_maix);
        
    }


    
    else if (x == 11)
    {
        tuopan_angle(zhong);
        servo_angle(kai2);
        delay_ms(300);
        
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_duo);
        servo_angle(kai1);
        delay_ms(700);
        shengjiang(0, 0);
    }
    else if (x == 12)
    {
        tuopan_angle(chu);
        servo_angle(kai2);
        delay_ms(500);
        
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(1000);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_duo);
        servo_angle(kai1);
        delay_ms(1000);
        shengjiang(0, 0);
    }
    else if (x == 13)
    {
        tuopan_angle(mo);
        servo_angle(kai2);
        delay_ms(700);
        
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(bi);
        delay_ms(500);
        shengjiang(0, 0);
        xuanzhuan(1, zhuan_zheng);
        shengjiang(0, jiang_duo);
        servo_angle(kai1);
        delay_ms(700);
        tuopan_angle(zhong);
        shengjiang(0, 0);
        
    }
    
    
}


// 123: 132 16 250
void zhua_pan(int x)
{
    static int i = 0;
    
    if (x == 1)
    {
        shengjiang(0, jiang_zhao);
        tuopan_angle(zhong);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(700);
        shengjiang(0, 0);
        servo_angle(kai1);
        xuanzhuan(1, zhuan_zheng);
        if (i != 2)
        {
            shengjiang(0, jiang_zhao);
        }
    }
    else if (x == 2)
    {
        tuopan_angle(chu);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(700);
        shengjiang(0, 0);
        servo_angle(kai1);
        xuanzhuan(1, zhuan_zheng);
        if (i != 2)
        {
            shengjiang(0, jiang_zhao);
        }
    }
    else if (x == 3)
    {
        tuopan_angle(mo);
        servo_angle(bi);
        delay_ms(700);
        shengjiang(0, jiang_liu);
        xuanzhuan(1, zhuan_hui);
        shengjiang(0, jiang_pan);
        servo_angle(kai);
        delay_ms(700);
        shengjiang(0, 0);
        servo_angle(kai1);
        xuanzhuan(1, zhuan_zheng);
        tuopan_angle(zhong);
        if (i != 2)
        {
            shengjiang(0, jiang_zhao);
        }
    }

    i++;
    i %= 3;
    
}





//X:fang de shun xu   
//Z:fang de cheng du  0:di  1:duo
//Y:1 zhua hui lai   0 zhi jie zou 
//dir:2 jia gong    1 zan cun
void xingshi(int x, int z, int y, int dir)
{
    int a=0,b=0,c=0;
    if (z == 0)
    {
        a = 1;
        b = 2;
        c = 3;
    }
    else
    {
        a = 11;
        b = 12;
        c = 13;
    }
    delay_ms(10);
    
    if (x == 123)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        delay_ms(200);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);


        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(300);
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //g
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
   
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);


        
        if(y == 1){
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
 
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
 
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //g
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        
       
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}

        delay_ms(10);

        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
  
        
        
        //HAL_TIM_Base_Start_IT(&htim3);

        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        
        
    }
    
    if (x == 132)
    {
     //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        
        //HAL_TIM_Base_Stop_IT(&htim3);
        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(200);
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //g
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);  


       if(y == 1){
     //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
    
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //g
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        
        
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        
        
    }
    if (x == 213)
    {
        //g
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(200);
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);
        

        if(y == 1){
        //g
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        //Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}


        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        //delay_ms(500);
       
    }
    if (x == 231)
    {
        //g
       
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(200);
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);

        

        if(y == 1){
        //g
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        //__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}

      
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
    }
    if (x == 312)
    {
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        
        
        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(200);
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //g
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);




        if(y == 1){
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
       
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //g
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
   
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
       
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        //delay_ms(200);
        
    }
    if (x == 321)
    {
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        
    
        shengjiang(0, jiang_maix);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 1000);
        delay_ms(200);
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);
  
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(a);
        HAL_TIM_Base_Start_IT(&htim3);

        //g
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
    
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(b);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
     
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        fang(c);
        HAL_TIM_Base_Start_IT(&htim3);



        if(y == 1){
        //b
        Base_speed1=Base_speed4=speed_1;
        Base_speed2=Base_speed3=speed_1;
        Flag = dir;
        delay_ms(wait_1*2);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('b', v1, e1, x_zb, y_zb);
        //color('b', v2, e2, x_zb, y_zb);
        delay_ms(200);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(1);
        HAL_TIM_Base_Start_IT(&htim3);

        //g
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('g', v1, e1, x_zb, y_zb);
        //color('g', v2, e2, x_zb, y_zb);
        delay_ms(200);
 
        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(2);
        HAL_TIM_Base_Start_IT(&htim3);
        
        //r
        Base_speed1=Base_speed4=-speed_1;
        Base_speed2=Base_speed3=-speed_1;
        Flag = dir;
        delay_ms(wait_1);//  wu kuai jian ju
        Base_speed1=Base_speed4=0;
        Base_speed2=Base_speed3=0;
        Flag = dir;
        
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);

        __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
        HAL_TIM_Base_Stop_IT(&htim3);
        delay_ms(10);
        Stop1(0);
        zhua(3);
        HAL_TIM_Base_Start_IT(&htim3);}
        
       
        color('r', v1, e1, x_zb, y_zb);
        //color('r', v2, e2, x_zb, y_zb);
        delay_ms(200);
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 0);
        
        
        

    }
}

