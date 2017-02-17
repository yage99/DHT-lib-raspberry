#include "DHT.h"

int word(char low, char high) {
  int word = high;
  word <<= 8;
  word += low;
  return word;
}

void systemInit() {
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

  
  while(digitalRead(DATA_PIN) == LOW);
  //printf("up\n");
  while(digitalRead(DATA_PIN) == HIGH);
  //printf("down & ready");

  // reading 40 bits data
  for (i=0;i<40;i++) {
    timeout = TIMEOUT_COUNT;
    while(digitalRead(DATA_PIN) == LOW);

    start = micros();
    while(digitalRead(DATA_PIN) == HIGH) {
      if(timeout-- < 0) {
	return 0;
      }
    }
    end = micros();
    if(end - start > 40) bit = 1;
    else bit = 0;
    data[i/8] <<= 1;
    data[i/8] |= bit;
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
    return 1;
  } else {
    //printf("read data check error\n");
    return 0;
  }

  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, HIGH);
}

int main(void) {
  systemInit();

  float temp;
  float hu;
  
  int s = micros();
  printf("printf use time %d ", micros());
  int e = micros();
  printf("%d us\n", e-s);
  while(1) {
    if(readDHTData(&temp, &hu)) {
      printf("tempreture is %f, hu is %f\n", temp, hu);
    } else {
      printf("read error\n");
    }
    delay(2000);
  }
}
