#include "Header.h"
#define LCD_DATA 	 GPIOB
#define LCD_CTRL   GPIOA
#define RS				 0x20
#define RW				 0x40
#define EN				 0x80

	
int main(){

	LCD_init();

	while(1){
		
	
	
		LCD_command(0x01);
		LCD_command(0x80);
		delayMs(100);
		
				
		LCD_data('t');
		delayMs(100);
		LCD_data('e');
		delayMs(100);
		LCD_data('a');
		delayMs(100);
		LCD_data('m');
		delayMs(100);
		LCD_data('3');
		delayMs(100);
		LCD_data('3');
		delayMs(100);
		delayMs(1000000);
		return 0;
		}
	
}

// Initialization of Port B pins
void PortB_Init(){
  // Initializing Clock and wait until get stablized
  SYSCTL_RCGCGPIO_R |= 0x02;
  while((SYSCTL_PRGPIO_R & 0x02) == 0){};
  
  // Initializing Port B pins
    GPIO_PORTB_LOCK_R = magicKey;
  GPIO_PORTB_CR_R |= 0xFF;
  GPIO_PORTB_AMSEL_R = 0;
  GPIO_PORTB_PCTL_R =0;
  GPIO_PORTB_DIR_R |= 0xFF;
  GPIO_PORTB_AFSEL_R =0;
  GPIO_PORTB_DEN_R |= 0xFF;
}

// Initializing Port A pins
void PortA_Init(){
	// Initializing Clock and wait until get stablized
  SYSCTL_RCGCGPIO_R |= 0x01;
  while((SYSCTL_PRGPIO_R & 0x00) == 0){};
  
  // Initializing Port A pins
   GPIO_PORTA_LOCK_R = magicKey;
  GPIO_PORTA_CR_R |= 0xe0;
  GPIO_PORTA_AMSEL_R &= ~0xE0;
  GPIO_PORTA_PCTL_R &= ~0xFFF00000;
  GPIO_PORTA_DIR_R |= 0xE0;
  GPIO_PORTA_AFSEL_R &= ~0xE0;
  GPIO_PORTA_DEN_R |= 0xE0;
}


void delay_1msec(int n){
	int i, j;
	for(i = 0; i < n; i++)
	for(j = 0; j < 3180; j++){}
}


void delayMs(unsigned long t)
{
	long i , j;
	   i = 0;
	   j = 0;
	  while(i<t){
       while(j<3180){
				 j++;
			 //Do Nothing
			 }
			 i++;
	  }
}

void LCD_command (unsigned char command)
{
	LCD_CTRL->DATA = 0; // SET RS=0 , RW=0
	LCD_DATA->DATA = command; //SET RS as command and RW as write
	LCD_CTRL->DATA = EN; //pulse E
	delayUs(0);
	
	LCD_CTRL->DATA = 0;
	if (command < 4)
		delayMs(2);
	else 
		delayUs(40);
}

///////////////////////////////////////////////

void LCD_data (unsigned char data)
{
	LCD_CTRL->DATA = RS; // Enable RS as data
	LCD_DATA->DATA = data;
	LCD_CTRL->DATA = EN | RS; //enable Pulse
	delayUs(0);
	LCD_CTRL->DATA = 0;
	delayUs(40);
}	

void delayUs(unsigned long t){
	long i , j;
	   i = 0;
	   j = 0;
	  while(i<t){
       while(j<3){
				 j++;
			 //Do Nothing
			 }
			 i++;
	  }
}


void LCD_init(void)
{
	SYSCTL->RCGCGPIO |= 0X01; // enable clock Port A
		SYSCTL->RCGCGPIO |= 0X02; // enable clock port B
		LCD_CTRL->DIR |=0xE0 ;
		LCD_CTRL->DEN |=0xE0 ;
		LCD_DATA->DIR = 0xFF ;
		LCD_DATA->DEN = 0xFF ;
	
		delayMs(20); // Waking up the LCD
		LCD_command(0x30);
		delayMs(20);
		
		LCD_command(0x38); // 8-bit data
		LCD_command(0x06); // shift cursor right
		LCD_command(0x01); // clear display screen
		LCD_command(0x80);
		LCD_command(0x0F); // display on
		
}




