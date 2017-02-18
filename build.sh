jar cvfm DHT.jar manifest.txt DHT_jni.class DHT_data.class
rm libDHT.so
gcc -o libDHT.so -shared DHT_jni.c -lwiringPi -I/usr/lib/jvm/java-7-openjdk-armhf/include DHT.c
rm /usr/lib/libDHT.so
ln libDHT.so /usr/lib
ldconfig
