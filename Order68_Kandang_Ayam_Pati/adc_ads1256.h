/*
 * Created by Muh. Shofuwan Anwar
 * 26 August 2016
 * Please report the error to muhshofuwananwar@gmail.com
 */

#include <SPI.h>

#define SPI_FREQ 1250000
#define RESET 8
#define READY 9
#define CS 10

/*
 * builtin delay function will increased the loss counting
 * make subfunction for decreasing the error time counting
 */
void _delay(unsigned int time){
	for(int x=0;x<time;x++)
		delay(1);
}

void _delayM(unsigned int time){
	for(int x=0;x<time;x++)
		delayMicroseconds(1);
}

void ads_init(void){
	pinMode(CS, OUTPUT);
	pinMode(READY, INPUT);
	pinMode(RESET, OUTPUT);
	SPI.begin();

	/*
	 * Start SPI protocol
	 */
	digitalWrite(RESET, 0);
	_delay(1);
	digitalWrite(RESET, 1);
	_delay(150);

	digitalWrite(CS, 0); // Select SPI chip
	_delayM(50);
	while(digitalRead(READY)); // Read the sign for ads is ready
	SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE1));
	_delayM(10);

	SPI.transfer(0xFE);
	_delayM(100);

	unsigned char status_reg = 0 ;
	unsigned char status_data = 0x01;
	SPI.transfer(0x50 | status_reg);
	SPI.transfer(0x00);
	SPI.transfer(status_data);
	_delayM(10);

	unsigned char adcon_reg = 2;
	unsigned char adcon_data = 0x20;
	SPI.transfer(0x50 | adcon_reg);
	SPI.transfer(0x00);
	SPI.transfer(adcon_data);
	_delayM(10);

	//Set sampling rate
	unsigned char drate_reg = 3;
	unsigned char drate_data = 0b11000000;
	SPI.transfer(0x50 | drate_reg);
	SPI.transfer(0x00);
	SPI.transfer(drate_data);
	_delayM(10);

	digitalWrite(CS, 1); //unselect ADS
	_delayM(50);
}

unsigned long ads_read(unsigned char ch){
	unsigned long adc_val = 0;

	digitalWrite(CS, 0);
	_delayM(50);
	SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE1)); // start SPI
	_delayM(10);
	while(digitalRead(READY));

	unsigned char data = (channel << 4) | (1 << 3);
	SPI.transfer(0x50 | 1);
	SPI.transfer(0x00);
	SPI.transfer(data);
	_delayM(10);

	SPI.transfer(0xFC);
	_delayM(10);
	SPI.transfer(0x00);
	_delayM(10);
	SPI.transfer(0x01);
	_delayM(10);

	adc_val = SPI.transfer(0);
	adc_val <<= 8;
	adc_val |= SPI.transfer(0);
	adc_val <<= 8;
	adc_val |= SPI.transfer(0);

	if (adc_val > 0x7fffff) {
		adc_val = 16777216ul - adc_val;

	_delayM(10);

	digitalWrite(CS, 1);
	_delayM(50);
	SPI.endTransaction();

	return adc_val;
}

unsigned long ads_read_diff(unsigned char pos, unsigned char neg){
	long adc_val = 0;

	digitalWrite(CS, 0);
	_delayM(50);
	SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE1));
	_delayM(10);
	while(digitalRead(READY));

	unsigned char data = (pos << 4) | neg;
	SPI.transfer(0x50 | 1);
	SPI.transfer(0x00);
	SPI.transfer(data);
	_delayM(10);

	SPI.transfer(0xFC);
	_delayM(10);
	SPI.transfer(0x00);
	_delayM(10);
	SPI.transfer(0x01);
	_delayM(10);

	adc_val = SPI.transfer(0);
	adc_val <<= 8;
	adc_val |= SPI.transfer(0);
	adc_val <<= 8;
	adc_val |= SPI.transfer(0);

	_delayM(10);

	digitalWrite(CS, 1);
	_delayM(50);

	if (adc_val > 0x7fffff)
		adc_val = adc_val - 16777216;

	return adc_val;
}
	
/*
 *CLK  - pin 13
 *DIN  - pin 11 (MOSI)
 *DOUT - pin 12 (MISO)
 *CS   - pin 10
 *DRDY - pin 9
 *RESET- pin 8 (or tie HIGH?)
 *DVDD - 3V3
 *DGND - GND
 */
