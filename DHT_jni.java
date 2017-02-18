
public class DHT_jni {
    static {
	System.loadLibrary("DHT");
    }

    private native void init(int port);
    private native int readDHTData(DHT_data data);


    public static void main(String[] args) {
	Integer port = 0;
	if(args.length > 0) {
	    port = Integer.valueOf(args[0]);
	}
	System.out.println("port is " + port);
	DHT_jni dht = new DHT_jni();
	dht.init(port);
	DHT_data data = new DHT_data();

	if(dht.readDHTData(data) == 1) {
	    System.out.printf("%f, %f\n", data.getTemperature(), data.getHu());
	} else {
	    System.out.println("error");
	}
    }
}
