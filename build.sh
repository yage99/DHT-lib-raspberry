rm libDHT.so
rm /usr/lib/libDHT.so
gcc -o libDHT.so -shared DHT_jni.c -lwiringPi -I/usr/lib/jvm/java-7-openjdk-armhf/include DHT.c
ln libDHT.so /usr/lib
ldconfig
