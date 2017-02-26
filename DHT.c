#include "DHT.h"

int DATA_PIN = 0;

int word(char low, char high) {
  int word = high;
  word <<= 8;
  word += low;
  return word;
}

void systemInit(int port) {
  DATA_PIN = port;
  wiringPiSetup();
}

int readDHTData(float* temp, float* hu) {

  char data[5] = {0,0,0,0,0};
  int start = 0;
  int end = 0;
  int bit = 0;
  int i=0;
  int j=0;
  
  int timeout = TIMEOUT_COUNT;
  int read = 0;

  //data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  //printf("Reading data:\n");

  pinMode(DATA_PIN, OUTPUT);

  //printf("Send read signal %d\n", micros());
  digitalWrite(DATA_PIN, LOW);
  delay(20); //wait for ready
  digitalWrite(DATA_PIN, HIGH);
  //printf("pull high %d\n", micros());
  delayMicroseconds(40);
  pinMode(DATA_PIN, INPUT);
  //printf("Wait coming sig %d,%d\n", millis(), micros());

  timeout = TIMEOUT_COUNT;
  // 80us
  while(digitalRead(DATA_PIN) == LOW) {
    if(timeout-- < 0) {
      return NO_RESPONSE;
    }
  }
  //printf("up\n");
  timeout = TIMEOUT_COUNT;
  // 80 us
  while(digitalRead(DATA_PIN) == HIGH) {
    if(timeout-- < 0) {
      return NO_DATA;
    }
  }
  //printf("down & ready");

  // reading 40 bits data
  for (i=0;i<40;i++) {
    timeout = TIMEOUT_COUNT;
    // 50us
    while(digitalRead(DATA_PIN) == LOW);

    start = micros();
    // 26-28us && 70us
    while(digitalRead(DATA_PIN) == HIGH) {
      if(timeout-- < 0) {
	return TIMEOUT;
      }
    }
    end = micros();
    if(end - start > 40) bit = 1;
    else bit = 0;
    data[i/8] <<= 1;
    data[i/8] += bit;
  }

  int checksum = 0;
  for (i=0;i<4;i++) {
    checksum += data[i];
  }
  //printf("readed: %d,%d,%d,%d,%d\n", data[0], data[1], data[2], data[3], data[4]);
  if((checksum&0xff) == data[4]) {
    *hu = data[0] * 1.0;
    *temp = data[2] * 1.0;
    //printf("su");
    return OK;
  } else {
    //printf("read data check error\n");
    return VALIDATION_ERROR;
  }

  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, HIGH);
}

int main(void) {
  systemInit(15);

  float temp;
  float hu;
  int resp;
  int start = 0;
  int end = 0;
  int count = TIMEOUT_COUNT;
  start = micros();
  while(1) {
    if(count-- < 0) break;
  }
  end = micros();
  printf("time out is %dus\n", end-start);

  while(1) {
    if((resp = readDHTData(&temp, &hu)) == 0) {
      printf("tempreture is %f, hu is %f\n", temp, hu);
    } else {
      printf("read error: %d\n", resp);
    }
    delay(2000);
  }
}
