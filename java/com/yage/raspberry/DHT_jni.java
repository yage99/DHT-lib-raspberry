package com.yage.raspberry;

import java.io.*;

public class DHT_jni {
    static {
	try {
	    loadLibraryFromJar("/libDHT.so");
	} catch (IOException e) {
	}
    }

    public native void init(int port);
    public native int readDHTData(DHT_data data);

    public DHT_jni(int port) {
	init(port);
    }

    public static void loadLibraryFromJar(String path) throws IOException {

	if (!path.startsWith("/")) {
	    throw new IllegalArgumentException("The path has to be absolute (start with '/').");
	}

	// Obtain filename from path
	String[] parts = path.split("/");
	String filename = (parts.length > 1) ? parts[parts.length - 1] : null;

	// Split filename to prexif and suffix (extension)
	String prefix = "";
	String suffix = null;
	if (filename != null) {
	    parts = filename.split("\\.", 2);
	    prefix = parts[0];
	    suffix = (parts.length > 1) ? "."+parts[parts.length - 1] : null; // Thanks, davs! :-)
	}

	// Check if the filename is okay
	if (filename == null || prefix.length() < 3) {
	    throw new IllegalArgumentException("The filename has to be at least 3 characters long.");
	}

	// Prepare temporary file
	File temp = File.createTempFile(prefix, suffix);
	temp.deleteOnExit();

	if (!temp.exists()) {
	    throw new FileNotFoundException("File " + temp.getAbsolutePath() + " does not exist.");
	}

	// Prepare buffer for data copying
	byte[] buffer = new byte[1024];
	int readBytes;

	// Open and check input stream
	InputStream is = DHT_jni.class.getResourceAsStream(path);
	if (is == null) {
	    throw new FileNotFoundException("File " + path + " was not found inside JAR.");
	}

	// Open output stream and copy data between source file in JAR and the temporary file
	OutputStream os = new FileOutputStream(temp);
	try {
	    while ((readBytes = is.read(buffer)) != -1) {
		os.write(buffer, 0, readBytes);
	    }
	} finally {
	    // If read/write fails, close streams safely before throwing an exception
	    os.close();
	    is.close();
	}

	// Finally, load the library
	System.load(temp.getAbsolutePath());
    }

    public static void main(String[] args) {
	Integer port = 0;
	if(args.length > 0) {
	    port = Integer.valueOf(args[0]);
	}
	System.out.println("port is " + port);
	DHT_jni dht = new DHT_jni(port);
	DHT_data data = new DHT_data();

	int response = 0;
	if((response = dht.readDHTData(data)) == 0) {
	    System.out.printf("%f, %f\n", data.getTemperature(), data.getHu());
	} else {
	    System.out.println("error: " + response);
	}
    }
}
