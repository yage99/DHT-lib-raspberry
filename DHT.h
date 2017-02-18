#ifndef DHT_H
#define DHT_H

#include <stdio.h>
#include <wiringPi.h>

#define TIMEOUT_COUNT 20000

#define OK 0
#define TIMEOUT 1
#define VALIDATION_ERROR 2
#define NO_DATA 3
#define NO_RESPONSE 4

void systemInit(int port);
int readDHTData(float* temp, float* hu);

#endif
