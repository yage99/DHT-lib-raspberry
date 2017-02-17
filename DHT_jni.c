#include "DHT.h"
#include "DHT_jni.h"

JNIEXPORT void JNICALL Java_DHT_1jni_init (JNIEnv *env, jobject obj) {
  systemInit();
}

JNIEXPORT jint JNICALL Java_DHT_1jni_readDHTData (JNIEnv *env, jobject obj, jobject dhtData) {
  float temp;
  float hu;

  if(readDHTData(&temp, &hu) != 1) return 0;

  jclass clazz = (*env)->GetObjectClass(env, dhtData);

  jfieldID param1Field = (*env)->GetFieldID(env, clazz, "temperature", "F");
  jfieldID param2Field = (*env)->GetFieldID(env, clazz, "hu", "F");

  (*env)->SetFloatField(env, dhtData, param1Field, temp);
  (*env)->SetFloatField(env, dhtData, param2Field, hu);

  return 1;
}
