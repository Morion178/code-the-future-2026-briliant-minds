import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Random;

public class MotoTester {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket();
        InetAddress address = InetAddress.getByName("localhost");
        Random random = new Random();

        System.out.println("Pornire Simulare Dinamică (Accelerare -> Croazieră -> Frânare)...");


        for (int i = 0; i < 100; i++) {
            int rpm, viteza;
            double temp = 90.0 + random.nextDouble() * 5;
            int emisii = 200 + random.nextInt(200);

            if (i < 30) {
                rpm = 1500 + (i * 200);
                viteza = 10 + (i * 3);
                emisii += 400;
            } else if (i < 70) {
                rpm = 3000 + random.nextInt(200);
                viteza = 100 + random.nextInt(5);
                emisii -= 100;
            } else {
                rpm = 1000 + (100 - i) * 10;
                viteza = Math.max(0, 110 - (i - 70) * 5);
            }

            String testData = rpm + "," + viteza + "," + String.format("%.1f", temp) + "," + emisii;
            byte[] buffer = testData.getBytes();

            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, 5005);
            socket.send(packet);

            System.out.println("Trimis: " + testData + (i >= 30 && i < 70 ? " [MOD ECO AȘTEPTAT]" : ""));

            Thread.sleep(200);
        }

        System.out.println("Simulare finalizată.");
        socket.close();
    }
}
