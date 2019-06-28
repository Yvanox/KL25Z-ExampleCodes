#include "MKL25Z4.h"
#include "LCDNokia5110.h"
#include "GPIO.h"

extern uint8_t Greeting[];
extern uint8_t thumb1[];
extern uint8_t thumb2[];
extern uint8_t thumb3[];
extern uint8_t thumb4[];

uint8_t Button2[]="btn2 Test";

void GPIO_init();
void animation();
void delay(uint32_t delay);

void PORTA_IRQHandler()
{
	/*If an interruption occurred and if the GPIOA BIT1 (PTA1) is pressed then this happens*/
	if(GPIO_readPIN(GPIOA,BIT1)==0)
	{
		animation();
	}
	if(GPIO_readPIN(GPIOA,BIT2)==0)
	{
	LCDNokia_clear();
	LCDNokia_gotoXY(12,2);
	LCDNokia_sendString(Button2);
	GPIO_clearInterrupt(PORTA);
	}
}


int main(void)
{

	LCDNokia_init();
	GPIO_init();

	LCDNokia_bitmap(Greeting);

    while(1)
    {

    }

}

void GPIO_init(void)
{
	_GPIOA_CLK_GATING();

	/*This Initializes the Button pin configurations*/
	gpio_pin_controlreg_t btn_pin_control_reg;

	/*Pin configuration options for the Buttons*/
	btn_pin_control_reg.ps = GPIO_PS;
	btn_pin_control_reg.pe = NULL;
	btn_pin_control_reg.sre = NULL;
	btn_pin_control_reg.filter = NULL;
	btn_pin_control_reg.strength = NULL;
	btn_pin_control_reg.mux = GPIO_MUX1;
	btn_pin_control_reg.irq = GPIO_IRQC6;
	btn_pin_control_reg.isf = NULL;

	/*This sets up the Button pin configurations*/
	GPIO_pinControlRegister(PORTA,BIT1,&btn_pin_control_reg);
	GPIO_pinControlRegister(PORTA,BIT2,&btn_pin_control_reg);

	/*This defines the Button pin as an input*/
	GPIO_dataDirectionPIN(GPIOA,BIT1,GPIO_INPUT);
	GPIO_dataDirectionPIN(GPIOA,BIT2,GPIO_INPUT);

	/*This function configures the interruption and the priority*/
	GPIO_configureInterrupt(PORTA_IRQn,PRIORITY_2);
}

void animation(void)
{
	LCDNokia_bitmap(thumb1);
	delay(300000);
	LCDNokia_bitmap(thumb2);
	delay(300000);
	LCDNokia_bitmap(thumb3);
	delay(300000);
	LCDNokia_bitmap(thumb4);
	delay(300000);
	LCDNokia_bitmap(thumb4);
	delay(300000);
	LCDNokia_bitmap(thumb3);
	delay(300000);
	LCDNokia_bitmap(thumb2);
	delay(300000);
	LCDNokia_bitmap(thumb1);
	delay(300000);
}

void delay(uint32_t delay){

uint32_t index;
for (index = delay; index > 0; --index)
{

}

}
