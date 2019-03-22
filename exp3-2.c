#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_i2c.h"
#include "hw_types.h"
#include "i2c.h"
#include "pin_map.h"
#include "sysctl.h"
#include "systick.h"
#include "interrupt.h"
#include "hw_timer.h"
#include "timer.h"
#include "uart.h"

#define SYSTICK_FREQUENCY		1000			//1000hz

/*new definition and functions*/

#define GPIO_SYS SYSCTL_PERIPH_GPION
#define TIMER_BASE TIMER0_BASE
#define TIMER_SYS SYSCTL_PERIPH_TIMER0
uint32_t GPIO_BASE = GPIO_PORTN_BASE;
uint8_t PIN_N = GPIO_PIN_4;
uint32_t INT_PIN = GPIO_INT_PIN_4;
void GPIO_Init(void);
void TIMER_Init(void);
void my_handler(void);
void getAngle(void);
void UARTStringPut(const char *cMessage);

void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);

void 		S800_UART_Init(void);
//systick software counter define
volatile uint16_t systick_10ms_couter,systick_100ms_couter;
volatile uint8_t	systick_10ms_status,systick_100ms_status;

volatile uint8_t result,cnt,key_value,gpio_status;
volatile uint8_t rightshift = 0x01;
uint32_t ui32SysClock;

uint8_t uart_receive_char;

/*new variables*/
char array[50];
double data[36];
uint32_t falling_t[36];
uint32_t rising_t[36];
uint32_t time_cnt = 0;
int end;
double angle[4];
uint32_t rising,falling;
int main(void)
{
	int tmp;
	int i;
	uint32_t status;
	//volatile uint16_t	i2c_flash_cnt,gpio_flash_cnt;
	//use internal 16M oscillator, PIOSC
   //ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ |SYSCTL_OSC_INT |SYSCTL_USE_OSC), 16000000);		
	//ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ |SYSCTL_OSC_INT |SYSCTL_USE_OSC), 8000000);		
	//use external 25M oscillator, MOSC
   //ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_OSC), 25000000);		

	//use external 25M oscillator and PLL to 120M
   ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 120000000);		
	//ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ |SYSCTL_OSC_INT |SYSCTL_USE_OSC), 16000000);		
	
	//S800_GPIO_Init();
	//S800_I2C0_Init();
	
	S800_UART_Init();
	//UARTStringPut("Start!\n");
	GPIO_Init();
	TIMER_Init();
	
	UARTStringPut("Start!\n");
	//status = GPIOIntTypeGet(GPIO_BASE,GPIO_PIN_4);
	//sprintf(array,"%d",ui32SysClock);
	//UARTStringPut(array);UARTStringPut("\n");
	while (1)
	{
		
		GPIO_BASE = GPIO_PORTN_BASE;
		PIN_N = GPIO_PIN_4;
		INT_PIN = GPIO_INT_PIN_4;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("1 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		PIN_N = GPIO_PIN_5;
		INT_PIN = GPIO_INT_PIN_5;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("2 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		GPIO_BASE = GPIO_PORTA_BASE;
		PIN_N = GPIO_PIN_5;
		INT_PIN = GPIO_INT_PIN_5;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("3 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		PIN_N = GPIO_PIN_4;
		INT_PIN = GPIO_INT_PIN_4;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("4 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		GPIO_BASE = GPIO_PORTC_BASE;
		PIN_N = GPIO_PIN_5;
		INT_PIN = GPIO_INT_PIN_5;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("5 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		PIN_N = GPIO_PIN_4;
		INT_PIN = GPIO_INT_PIN_4;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("6 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		GPIO_BASE = GPIO_PORTK_BASE;
		PIN_N = GPIO_PIN_4;
		INT_PIN = GPIO_INT_PIN_4;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("7 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		
		PIN_N = GPIO_PIN_5;
		INT_PIN = GPIO_INT_PIN_5;
		end = 0;
		GPIOIntClear(GPIO_BASE,INT_PIN);
		GPIOIntEnable(GPIO_BASE,INT_PIN);
		Delay(4000000);
		GPIOIntDisable(GPIO_BASE,INT_PIN);
		getAngle();
		//PORT OUTPUT
		UARTStringPut("8 ");
		for(i = 0;i<4;i++){
			sprintf(array,"%.10lf",angle[i]);
			UARTStringPut(array);UARTStringPut(" ");
		}
		UARTStringPut("\n");
		
		//Delay(500000);
		//printf("hello %d\n",ui32SysClock);
		//UARTStringPut("hello0006666---!\n");
		//UARTStringPut("hello----\n");
		
		//UARTStringPut("hello----\n");
	}

	

}

void getAngle(void)
{
	bool flag = true;
	int start = 0;
	double tmp;
	bool a[4];
	int i,j;
	//sprintf(array,"%d",end);
		//UARTStringPut(array);UARTStringPut("\n");
	for(i = 0;i<36;i++){
		data[i] = (rising_t[(end+i)%36]-falling_t[(end+i)%36])/120.0;
		//sprintf(array,"%.5lf",data[i]);
		//UARTStringPut(array);UARTStringPut(" ");
		//sprintf(array,"%x",falling_t[(end+i)%36]);
		//UARTStringPut(array);UARTStringPut(" ");
	}//UARTStringPut("\n");
	
	for(i = 0;i<=24;i++){
		flag = true;
		for(j = 0;j<4;j++){
			if(data[i+j*3+0]>20.0 && data[i+j*3+1]>20.0 && data[i+j*3+2]<20.0){
				//OK
			}
			else{
				flag = false;
				break;
			}
		}
		if(flag){start = i;break;}
	}
	//if(!flag)UARTStringPut("FAIL ");
	//sprintf(array,"%d",start);
	//UARTStringPut(array);UARTStringPut("\n");
	for(j = 0;j<4;j++){
		//BS1
		if(data[start+j*3]<data[start+j*3+1]){
				a[j] = false;
				angle[j] = ((falling_t[(end+start+j*3+2)%36] - falling_t[(end+start+j*3)%36])/120.0 - 4000.0)/8333.0 * 180.0;
				//sprintf(array,"%x",(falling_t[(end+start+j*3+2)%36] - falling_t[(end+start+j*3)%36]));
				//UARTStringPut(array);UARTStringPut("\n");
		}
		//BS2
		else{
			a[j] = true;
			
			angle[j] = ((falling_t[(end+start+j*3+2)%36] - falling_t[(end+start+j*3+1)%36])/120.0 - 4000.0)/8333.0 * 180.0;
			//sprintf(array,"%x",(falling_t[(end+start+j*3+2)%36] - falling_t[(end+start+j*3+1)%36]));
				//UARTStringPut(array);UARTStringPut("\n");
		}
		//sprintf(array,"%.5lf",angle[j]);
				//UARTStringPut(array);UARTStringPut("\n");
	}
	
	//0 0 1 1
	
	//1 0 0 1
	if(a[0] && a[3]){
		tmp = angle[0];
		angle[0] = angle[1];
		angle[1] = angle[2];
		angle[2] = angle[3];
		angle[3] = tmp;
	}
	//1 1 0 0
	else if(a[0] && a[1]){
		tmp = angle[0];
		angle[0] = angle[2];
		angle[2] = tmp;
		
		tmp = angle[1];
		angle[1] = angle[3];
		angle[3] = tmp;
	}
	
	//0 1 1 0
	else if(a[1]&&a[2]){
		tmp = angle[3];
		angle[3] = angle[2];
		angle[2] = angle[1];
		angle[1] = angle[0];
		angle[0] = tmp;
	}
}

void TIMER_Init(void)
{
	SysCtlPeripheralEnable(TIMER_SYS);                      // enable peripheral
	SysCtlDelay(5);
	SysCtlPeripheralReset(TIMER_SYS);
	SysCtlDelay(5);
	TimerDisable(TIMER_BASE, TIMER_A);
	//TimerDisable(TIMER_BASE, TIMER_BOTH);
	TimerConfigure(TIMER_BASE,TIMER_CFG_A_PERIODIC_UP);
	//TimerConfigure(TIMER_BASE,TIMER_CFG_PERIODIC_UP);
	TimerClockSourceSet(TIMER_BASE,TIMER_CLOCK_SYSTEM);
	//TimerPrescaleSet(TIMER_BASE,TIMER_BOTH,1);
	TimerPrescaleSet(TIMER_BASE,TIMER_A,1);
	TimerLoadSet(TIMER_BASE,TIMER_A,0xFFFFFFFF);
	//TimerLoadSet64(TIMER_BASE,0xFFFFFFFFFFFFFFFF);
	TimerEnable(TIMER_BASE,TIMER_A);
	
}
void GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_4);
	GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_5);
	
	GPIOPinTypeGPIOInput(GPIO_PORTK_BASE,GPIO_PIN_4);
	GPIOPinTypeGPIOInput(GPIO_PORTK_BASE,GPIO_PIN_5);
	GPIOPinTypeGPIOInput(GPIO_PORTK_BASE,GPIO_PIN_6);
	
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_4);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_5);
	
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_4);
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_5);
	
	GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
	GPIOPadConfigSet(GPIO_PORTK_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTK_BASE,GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTK_BASE,GPIO_PIN_6,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

	GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
	GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
	GPIOIntDisable(GPIO_PORTN_BASE,GPIO_INT_PIN_4);
	GPIOIntDisable(GPIO_PORTN_BASE,GPIO_INT_PIN_5);
	
	GPIOIntDisable(GPIO_PORTK_BASE,GPIO_INT_PIN_4);
	GPIOIntDisable(GPIO_PORTK_BASE,GPIO_INT_PIN_5);
	GPIOIntDisable(GPIO_PORTK_BASE,GPIO_INT_PIN_6);
	
	GPIOIntDisable(GPIO_PORTA_BASE,GPIO_INT_PIN_4);
	GPIOIntDisable(GPIO_PORTA_BASE,GPIO_INT_PIN_5);
	
	GPIOIntDisable(GPIO_PORTC_BASE,GPIO_INT_PIN_4);
	GPIOIntDisable(GPIO_PORTC_BASE,GPIO_INT_PIN_5);
	
	GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_5,GPIO_FALLING_EDGE);
	
	GPIOIntTypeSet(GPIO_PORTK_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTK_BASE,GPIO_PIN_5,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTK_BASE,GPIO_PIN_6,GPIO_FALLING_EDGE);
	
	GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_FALLING_EDGE);
	
	GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_FALLING_EDGE);

	GPIOIntRegister(GPIO_PORTN_BASE,my_handler);
	GPIOIntRegister(GPIO_PORTK_BASE,my_handler);
	GPIOIntRegister(GPIO_PORTA_BASE,my_handler);
	GPIOIntRegister(GPIO_PORTC_BASE,my_handler);
	
	GPIOIntClear(GPIO_PORTN_BASE,GPIO_INT_PIN_4);
	GPIOIntClear(GPIO_PORTN_BASE,GPIO_INT_PIN_5);
	
	GPIOIntClear(GPIO_PORTK_BASE,GPIO_INT_PIN_4);
	GPIOIntClear(GPIO_PORTK_BASE,GPIO_INT_PIN_5);
	GPIOIntClear(GPIO_PORTK_BASE,GPIO_INT_PIN_6);
	
	GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_4);
	GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_5);
	
	GPIOIntClear(GPIO_PORTC_BASE,GPIO_INT_PIN_4);
	GPIOIntClear(GPIO_PORTC_BASE,GPIO_INT_PIN_5);
	
	GPIOIntEnable(GPIO_PORTN_BASE,GPIO_INT_PIN_4);
	//status = GPIOIntTypeGet(GPIO_BASE,GPIO_PIN_4);
	//sprintf(array,"%x",status);
	//UARTStringPut(array);
}

void my_handler(void)
{
	//uint32_t status=0;
	
	//time_cnt = TimerValueGet(TIMER_BASE,TIMER_A);
	time_cnt = TimerValueGet(TIMER_BASE,TIMER_A);
	//status = GPIOIntStatus(GPIO_BASE,true);
	//GPIOIntClear(GPIO_BASE,GPIO_INT_PIN_4);
	//status = GPIOIntStatus(GPIO_BASE,true);
	GPIOIntClear(GPIO_BASE,INT_PIN);
		//Then there was a pin4 interrupt
		//UARTStringPut("Here4!\n");
		//sprintf(array,"%#018"PRIx32"\n",time_cnt);
		//UARTStringPut(array);
		//status = GPIOIntTypeGet(GPIO_BASE,GPIO_PIN_4);
		//sprintf(array,"%d",status);
		//UARTStringPut(array);UARTStringPut("\n");
		if(GPIOIntTypeGet(GPIO_BASE,PIN_N) == GPIO_FALLING_EDGE){
			falling = time_cnt;
			falling_t[end%36] = time_cnt;
			//UARTStringPut("Falling!\n");
			//GPIOIntDisable(GPIO_BASE,GPIO_INT_PIN_4);
			GPIOIntTypeSet(GPIO_BASE,PIN_N,GPIO_RISING_EDGE);
			//status = GPIOIntTypeGet(GPIO_BASE,GPIO_PIN_4);
			//sprintf(array,"%x",status);
			//UARTStringPut(array);
			//GPIOIntClear(GPIO_BASE,GPIO_INT_PIN_4);
			//GPIOIntEnable(GPIO_BASE,GPIO_INT_PIN_4);
			
		}
		else{
			rising_t[end%36] = time_cnt;
			end++;
			rising = time_cnt;
			//UARTStringPut("Rising!\n");
			//data[(end++)%36] = (rising-falling)/120.0;
			
			//sprintf(array,"%.5lf",(rising-falling)/120.0);
			//sprintf(array,"%.5lf",(rising_t[(end-1)%36]-falling_t[(end-1)%36])/120.0);
			GPIOIntTypeSet(GPIO_BASE,PIN_N,GPIO_FALLING_EDGE);
			//UARTStringPut(array);UARTStringPut("\n");
		}
	if(GPIO_BASE == GPIO_PORTC_BASE){
		//sprintf(array,"%d",status);
		//UARTStringPut(array);
		//UARTStringPut("getINT\n");
	}
	/*
	if( (status & GPIO_INT_PIN_5) == GPIO_INT_PIN_5){
		//Then there was a pin5 interrupt
		UARTStringPut("Here5!\n");
	}
	*/
	//sprintf(array,"%d",status);
	//UARTStringPut(array);
	//UARTStringPut("getINT\n");
	
}

void Delay(uint32_t value)
{
	uint32_t ui32Loop;
	for(ui32Loop = 0; ui32Loop < value; ui32Loop++){};
}


void UARTStringPut(const char *cMessage)
{
	while(*cMessage!='\0')
		UARTCharPut(UART2_BASE,*(cMessage++));
}

void S800_UART_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);						//Enable PortA
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));			//Wait for the GPIO moduleA ready

	GPIOPinConfigure(GPIO_PD4_U2RX);												// Set GPIO A0 and A1 as UART pins.
  GPIOPinConfigure(GPIO_PD5_U2TX);    			

  GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	// Configure the UART for 115,200, 8-N-1 operation.
  UARTConfigSetExpClk(UART2_BASE, ui32SysClock,1500000,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTStringPut((uint8_t *)"\r\nHello, world!\r\n");
}
void S800_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);						//Enable PortF
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));			//Wait for the GPIO moduleF ready
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);						//Enable PortJ	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));			//Wait for the GPIO moduleJ ready	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);						//Enable PortN	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));			//Wait for the GPIO moduleN ready		
	
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);			//Set PF0 as Output pin
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);			//Set PN0 as Output pin

	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1);//Set the PJ0,PJ1 as input pin
	GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}


/*
	Corresponding to the startup_TM4C129.s vector table systick interrupt program name
*/
void SysTick_Handler(void)
{
	if (systick_100ms_couter	!= 0)
		systick_100ms_couter--;
	else
	{
		systick_100ms_couter	= SYSTICK_FREQUENCY/10;
		systick_100ms_status 	= 1;
	}
	
	if (systick_10ms_couter	!= 0)
		systick_10ms_couter--;
	else
	{
		systick_10ms_couter		= SYSTICK_FREQUENCY/100;
		systick_10ms_status 	= 1;
	}
	if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0) == 0)
	{
		systick_100ms_status	= systick_10ms_status = 0;
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,GPIO_PIN_0);		
	}
	else
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,0);		
}
