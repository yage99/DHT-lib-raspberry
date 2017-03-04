rm lib/libDHT.so
rm /usr/lib/libDHT.so
gcc -o lib/libDHT.so -shared com_yage_raspberry_DHT_jni.c -lwiringPi -I/usr/lib/jvm/java-8-openjdk-armhf/include -I/usr/lib/jvm/java-8-openjdk-armhf/include/linux DHT.c
ln lib/libDHT.so /usr/lib
ldconfig
