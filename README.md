# DHT library for raspberry

This library provides a c library for DHT11 temperature reading.

At the same time, a java API wrapped by jni is also avaiable.

## How to use

### 1. Build by your self.

This library required wiringPi be installed first. Refer: http://wiringpi.com/download-and-install/

Run build script as root:

`$ sudo sh build.sh`

This will install DHT library to your /usr/lib folder which could be loaded by Java through jni.

### 2. Download library directly

Just download files from lib and you can use it.