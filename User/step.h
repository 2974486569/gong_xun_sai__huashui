#ifndef __STEP_H
#define __STEP_H
# include "main.h"

#define val1  140
#define acc1  30
extern __IO bool rxFrameFlag;
extern __IO uint8_t dj_rxCmd[128];
extern  uint8_t xz[128];
void stage0(void);
void stage1(void);
void stage01(void);
void stage02(void);
void stage03(void);
void wait(void);
void wait5(void);
void wait6(void);

#endif
