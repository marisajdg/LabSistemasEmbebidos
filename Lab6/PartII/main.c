#include "stdio.h"
#include "myprintf.h"
#include "sam.h"
#include "stdbool.h"
#include "RTCControl.h"

#define slaveAddress 0x68
#define bufferSize 7

uint8_t tx[bufferSize] = {0x00, 0x00, 0x01, 0x04, 0x08, 0x11, 0x10, 0x21};
uint8_t rx[bufferSize];


void UARTInit(void);

int main(void)
{
	UARTInit();
	I2CInit();
	
	sendI2CDataArray(slaveAddress, SECONDS_ADDR,tx, bufferSize);
	receiveI2CDataArray(slaveAddress, SECONDS_ADDR,rx, bufferSize);
	
	time_type time;
	
	while(true){
		time.seconds.reg = rx[SECONDS_ADDR];
		time.minutes.reg = rx[MINUTES_ADDR];
		time.hours.reg	= rx[HOURS_ADDR];
		time.day.reg = rx[DAY_ADDR];
		time.date.reg = rx[DATE_ADDR];
		time.month.reg = rx[MONTH_ADDR];
		time.year.reg = rx[YEAR_ADDR];
		
		myprintf("%d%d/", time.date.field.dec_date, time.date.field.un_date);
		myprintf("%d%d/", time.month.field.dec_mont, time.month.field.un_month);
		myprintf("%d%d ", time.year.field.dec_year, time.year.field.un_year);
		myprintf("%d%d:", time.hours.field.dec_hours, time.hours.field.un_hours);
		myprintf("%d%d ", time.seconds.field.dec_seconds, time.seconds.field.un_seconds);
		myprintf("%d%d:", time.minutes.field.dec_minutes, time.minutes.field.un_minutes);
		myprintf("\n");
		
		receiveI2CDataArray(slaveAddress, SECONDS_ADDR,rx, bufferSize);
	}
	
	
	return 0;
}

void UARTInit(void) {
	/* Initialize the SAM system */
	SystemInit();
	/* Switch to 8MHz clock (disable prescaler) */
	SYSCTRL->OSC8M.bit.PRESC = 0;
	
	/* port mux configuration*/
	PORT->Group[0].DIR.reg |= (1 << 10);                  /* Pin 10 configured as output */
	PORT->Group[0].PINCFG[PIN_PA11].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	PORT->Group[0].PINCFG[PIN_PA10].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	
	/*PMUX: even = n/2, odd: (n-1)/2 */
	PORT->Group[0].PMUX[5].reg |= 0x02;                   /* Selecting peripheral function C */
	PORT->Group[0].PMUX[5].reg |= 0x20;                   /* Selecting peripheral function C */
	
	/* APBCMASK */
	//PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;			  /* SERCOM 0 enable*/
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;

	/*GCLK configuration for sercom0 module: using generic clock generator 0, ID for sercom0, enable GCLK*/

	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE) |
	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);

	
	/* configure SERCOM0 module for UART as Standard Frame, 8 Bit size, No parity, BAUDRATE:9600*/

	SERCOM0->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_MODE_USART_INT_CLK |
	SERCOM_USART_CTRLA_RXPO(3/*PAD3*/) | SERCOM_USART_CTRLA_TXPO(1/*PAD2*/);
	
	uint64_t br = (uint64_t)65536 * (8000000 - 16 * 9600) / 8000000;
	
	SERCOM0->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0/*8 bits*/);

	SERCOM0->USART.BAUD.reg = (uint16_t)br;

	SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}