#ifndef __JIXIEBI_H__
#define __JIXIEBI_H__
#include "main.h"
extern int Flag ;
extern int16_t Speed1,Speed2,Speed3,Speed4;
extern int16_t Base_speed1,Base_speed2,Base_speed3,Base_speed4;
int servo_init(void);
int servo_angle(int angle);
int tuopan_angle(int angle);
void xuanzhuan(int dir, int angle);
void shengjiang(int dir, int angle);
void zhua(int x);
void fang(int x);

void zhua_pan(int x);//wu


void xingshi(int x, int z, int y, int dir);
#endif

