#include "com_yage_raspberry_DHT_jni.h"
#include "DHT.h"

JNIEXPORT void JNICALL Java_com_yage_raspberry_DHT_1jni_init(JNIEnv *env, jobject obj, jint port) {
  int data_pin = port;
  systemInit(data_pin);
}

JNIEXPORT jint JNICALL Java_com_yage_raspberry_DHT_1jni_readDHTData(JNIEnv *env, jobject obj, jobject dhtData) {
  float temp;
  float hu;

  int resp = 0;
  if((resp = readDHTData(&temp, &hu)) != 0) return resp;

  jclass clazz = (*env)->GetObjectClass(env, dhtData);

  jfieldID param1Field = (*env)->GetFieldID(env, clazz, "temperature", "F");
  jfieldID param2Field = (*env)->GetFieldID(env, clazz, "hu", "F");

  (*env)->SetFloatField(env, dhtData, param1Field, temp);
  (*env)->SetFloatField(env, dhtData, param2Field, hu);

  return 0;
}
