#include "Motor.h"
extern __IO bool rxFrameFlag;
/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_go(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  0,  vel,  acc,  clk,  raF,  1);
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  0,  vel,  acc,  clk,  raF,  1);
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  1,  vel,  acc,  clk,  raF,  1);
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  1,  vel,  acc,  clk,  raF,  1);
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); 
  rxFrameFlag = false;
 }


/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_down(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}


/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_l(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  0,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  1,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_r(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  0,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  1,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_yl(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  1,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  1,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  1,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_yr(uint16_t vel, uint8_t acc, uint32_t clk, bool raF)
{
  Emm_V5_Pos_Control(1,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(2,  0,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(3,  0,  vel,  acc,  clk,  raF,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Pos_Control(4,  0,  vel,  acc,  clk,  raF,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
  
}













;
/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_go1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  0,  vel,  acc,  1);
  while(rxFrameFlag == false);
  rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  0,  vel,  acc,  1);
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  1,  vel,  acc,  1); //右侧    后即是前
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  1,  vel,  acc,  1); //右侧    后即是前
  while(rxFrameFlag == false); 
  rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); 
  rxFrameFlag = false;
 }


/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_down1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  0,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  0,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}


/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_r1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  0,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  0,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  1,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_l1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  0,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  1,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  0,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_yl1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  1,  vel,  acc,  1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  1,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  1,  vel,  acc,  1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

/**
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  */

void Car_yr1(uint16_t vel, uint8_t acc)
{
  Emm_V5_Vel_Control(1,  0,  vel,  acc, 1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  0,  vel,  acc, 1);  //前
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  0,  vel,  acc, 1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  0,  vel,  acc, 1);  //后
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

void Car_stop(void)
{
  Emm_V5_Vel_Control(1,  0,  0,  20,  1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(2,  0,  0,  20,  1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(3,  0,  0,  20,  1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Vel_Control(4,  0,  0,  20,  1);
  while(rxFrameFlag == false); rxFrameFlag = false;
  Emm_V5_Synchronous_motion(0);
 	while(rxFrameFlag == false); rxFrameFlag = false;
}

