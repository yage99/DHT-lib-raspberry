rm *.class
rm lib/DHT.jar
javac DHT_jni.java
javac DHT_data.java
jar cvfm lib/DHT.jar manifest.txt DHT_jni.class DHT_data.class
rm *.class
