# include "step.h"
void wait()
{
    int ok = 0, fal = 0;
    while(1)
  {
    Emm_V5_Read_Sys_Params(0,S_FLAG);
    while(rxFrameFlag == false); 
    rxFrameFlag = false;
    ok = dj_rxCmd[2]&0x02;
    fal ++;
    HAL_Delay(2);
    if (ok == 2)
    {
        /* code */
        break;
    }
    else if (fal > 10000)
    {
      /* code */
      break;
    }
  }
}

void wait5()
{
    int ok = 0, fal = 0;
    
    while(1)
  {
    Emm_V5_Read_Sys_Params(5, S_FLAG);
    while(rxFrameFlag == false); 
    rxFrameFlag = false;
    // OLED_Printf(0, 0, OLED_8X16, "%X", dj_rxCmd[0]);
    // OLED_Printf(0, 14, OLED_8X16, "%X", dj_rxCmd[1]);
    // OLED_Printf(0, 28, OLED_8X16, "%X", dj_rxCmd[2]);
    // OLED_Printf(0, 42, OLED_8X16, "%X", dj_rxCmd[3]);
    // OLED_Update();
    fal ++;
    delay_ms(2);
    
    ok = dj_rxCmd[2]&0x02;
    
    if (ok != 0)
    {
        /* code */
        break;
    }
    else if (fal > 10000)
    {
      /* code */
      break;
    }
  }
}

void wait6()
{
    int ok = 0, fal = 0;
    //rxFrameFlag = false;
    
    while(1)
  {
    
    
    ZDT_X42_V2_Read_Sys_Params(6, S_FLAG2);
    while(rxFrameFlag == false); 
    rxFrameFlag = false;
    fal ++;
    delay_ms(2); 
    // OLED_Printf(0, 0, OLED_8X16, "%X", xz[0]);
    // OLED_Printf(0, 14, OLED_8X16, "%X", xz[1]);
    // OLED_Printf(0, 28, OLED_8X16, "%X", xz[2]);
    // OLED_Printf(0, 42, OLED_8X16, "%X", xz[3]);
    // OLED_Update();
    
    
    ok = xz[2]&0x02;
    
    if (ok != 0)
    {
        /* code */
        break;
    }
    else if (fal > 10000)
    {
      /* code */
      break;
    }
  }
}

void stage0()
{

        Car_l(val1, acc1, 1914, 0);
        wait();
        Car_go(val1, acc1, 10507, 0);
        wait();
        
       
    
}
void stage1()
{
    

        Car_go(val1, acc1, 19715, 0);
        wait();
        Car_l(val1, acc1, 14700, 0);
        wait();
        Car_down(val1, acc1, 13433, 0);
        wait();
}
void stage01()
{
        Car_r(val1, acc1, 14331, 0);
        wait();
        Car_down(val1, acc1, 16851, 0);
        wait();
        Car_r(val1, acc1, 1635, 0);
        wait();
}
  
void stage02()
{
        Car_down(val1, acc1, 13424, 0);
        wait();
        Car_r(val1, acc1, 14166, 0);
        wait();
        Car_down(val1, acc1, 3350, 0);
        wait();
        Car_r(val1, acc1, 1665, 0);
        wait();
        
    
}

void stage03()
{
        Car_l(val1, acc1, 14016, 0);
        wait();
        Car_down(val1, acc1, 13483, 0);
        wait();
        Car_r(val1, acc1, 27500, 0);
        wait();
        Car_down(val1, acc1, 3700, 0);
        wait();
        Car_r(val1, acc1, 1375, 0);
        wait();
    
}



  
