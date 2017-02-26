rm com/yage/raspberry/*.class
rm ../lib/DHT.jar
javac com/yage/raspberry/DHT_jni.java
javac com/yage/raspberry/DHT_data.java
rm libDHT.so
cp ../lib/libDHT.so .
jar cvfm ../lib/DHT.jar manifest.txt com/yage/raspberry/DHT_jni.class com/yage/raspberry/DHT_data.class libDHT.so
rm com/yage/raspberry/*.class
