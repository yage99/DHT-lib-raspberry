rm com/yage/raspberry/*.class
rm ../lib/DHT.jar
javac com/yage/raspberry/DHT_jni.java
javac com/yage/raspberry/DHT_data.java
jar cvfm ../lib/DHT.jar manifest.txt com/yage/raspberry/DHT_jni.class com/yage/raspberry/DHT_data.class
rm com/yage/raspberry/*.class
