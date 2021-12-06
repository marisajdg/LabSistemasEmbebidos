/*int main(void)
{
   	SystemInit();
   	spiInit();
 
   	volatile uint8_t rData;
   	volatile uint8_t sData = 85;
   	while (1) {
			REG_PORT_OUTCLR0 = PORT_PA18; //initiate transaction by SS_low
          	rData = spiSend( sData );
			REG_PORT_OUTSET0 = PORT_PA18; //finish transaction by SS_high
   	}


}*/

#define RXBUFSIZE 0x400
#define LENGTH_R1 0x03
#define LENGTH_R7 0x07

void initCycles(void);

#define SIZE_SD_CMD 0x06
#define kCMD00 0x40
#define kCMD08 0x48
#define kCMD55 0x77
#define kCMD41 0x69

const uint8_t CMD00[SIZE_SD_CMD]  ={0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
const uint8_t CMD08[SIZE_SD_CMD]  ={0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
uint8_t CMD17[SIZE_SD_CMD]  ={0x51, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t CMD172[SIZE_SD_CMD]  ={0x51, 0x00, 0x00, 0x08, 0x00, 0x01};
const uint8_t CMD18[SIZE_SD_CMD]  ={0x52, 0x00, 0x00, 0x00, 0x00, 0x01};
const uint8_t CMD55[SIZE_SD_CMD]  ={0x77, 0x00, 0x00, 0x00, 0x00, 0x65};
const uint8_t CMD41[SIZE_SD_CMD] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x77};

uint8_t RxBuffer[RXBUFSIZE];

int main(void)
{
  uint32_t temp = 0xFF;
  /* Initialize the SAM system */
  SystemInit();

  initUART();
  spiInit();

  initCycles();
  //myprintf("\n");
	
  spiXchg( CMD00, SIZE_SD_CMD, RxBuffer );  /* reset instruction */
  myprintf("\n");

  //Write your code here

  myprintf("\nDone");
}

void initCycles(void){
	uint32_t i;
	REG_PORT_OUTSET0 = PORT_PA18;
	for(i=0;i<76;i++)
	spiSend(0xFF);
}

//ADD spiXchg FUNCTION TO THE “spi.c” FILE

uint32_t spiXchg(const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff ) {
	uint8_t temp = 0xFF;
	uint32_t i;
	uint8_t temp_cmd = send_buff[0];
	
	REG_PORT_OUTCLR0 = PORT_PA18;
	for(i=0; i< bc; i++) {
		temp = spiSend(*(send_buff++));
		myprintf(" %x", temp);
	}
	switch(temp_cmd) {
		case kCMD00 :
			for(i=0; i<LENGTH_R1; i++) {
				temp = spiSend(0xFF);
				myprintf(" %x", temp);
			}
			break;
		case kCMD08 :
			for(i=0; i<LENGTH_R7; i++) {
				temp = spiSend(0xFF);
				myprintf(" %x", temp);
			}
			break;
		case kCMD41 :
			for(i=0; i<LENGTH_R1-1; i++) {
				temp = spiSend(0xFF);
				myprintf(" %x", temp);
			}
			spiSend(0xFF);
			break;
		case kCMD55 :
			for(i=0; i<LENGTH_R1; i++) {
				temp = spiSend(0xFF);
				//myprintf(" %x", temp);
			}
			break;
		default :
			myprintf("\n Error in CMD");
	}
	REG_PORT_OUTSET0 = PORT_PA18;
	return(temp);
}