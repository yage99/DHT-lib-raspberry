#ifndef DHT_H
#define DHT_H

#include <stdio.h>
#include <wiringPi.h>

#define DATA_PIN 0

#define TIMEOUT_COUNT 10000

void systemInit();
int readDHTData(float* temp, float* hu);

#endif
