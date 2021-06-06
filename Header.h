#include <TM4C123.h>
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Math.h"
#define magicKey 0x4C4F434B

#define PI 3.14159265358979323846
void PortA_Init();
void PortD_Init();
void PortF_Init(void);
void PortB_Init();
void lcd_control(char command ,char RS);
void delay_1msec(int n);
void LCD_init();
void delayMs(unsigned long t);
void LCD_data (unsigned char data);
void LCD_command (unsigned char command);
void delayUs(unsigned long t);