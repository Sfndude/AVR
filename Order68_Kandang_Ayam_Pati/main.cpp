/*
 * Telemetry data for visual studio
 */

#include <Arduino.h>
#include "adc_ads1256.h"

static unsigned long data = 0;

void setup(){
	Serial.begin(115200);
	ads_init();
	Serial.begin("[!READ] Initializing done..");
}

void loop(){
	data = ads_read(0);
	Serial.println(String(data) + ";" + String(data*5/2-1024) + ";");
}