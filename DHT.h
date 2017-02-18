#ifndef DHT_H
#define DHT_H

#include <stdio.h>
#include <wiringPi.h>

#define TIMEOUT_COUNT 10000

void systemInit(int port);
int readDHTData(float* temp, float* hu);

#endif
