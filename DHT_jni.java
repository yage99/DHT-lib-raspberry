
public class DHT_jni {
    static {
	System.setProperty("java.library.path", ".");
	System.loadLibrary("DHT");
    }

    private native void init();
    private native int readDHTData(DHT_data data);


    public static void main(String[] args) {
	DHT_jni dht = new DHT_jni();
	dht.init();
	DHT_data data = new DHT_data();

	if(dht.readDHTData(data) == 1) {
	    System.out.printf("%f, %f\n", data.getTemperature(), data.getHu());
	} else {
	    System.out.println("error");
	}
    }
}
