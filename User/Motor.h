#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "Emm_V5.h"
void Car_go  (uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_down(uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_l   (uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_r   (uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_yl  (uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_yr  (uint16_t vel, uint8_t acc, uint32_t clk, bool raF);
void Car_go1  (uint16_t vel, uint8_t acc);
void Car_down1(uint16_t vel, uint8_t acc);
void Car_l1   (uint16_t vel, uint8_t acc);
void Car_r1   (uint16_t vel, uint8_t acc);
void Car_yl1  (uint16_t vel, uint8_t acc);
void Car_yr1  (uint16_t vel, uint8_t acc);
void Car_stop(void);


#endif
