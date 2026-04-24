import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Random;

public class MotoTester {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket();
        InetAddress address = InetAddress.getByName("localhost");
        Random random = new Random();

        System.out.println("Pornire Simulare (6 Parametri: RPM, Vit, Temp, CO2, Consum, Honk)...");

        for (int i = 0; i < 1000; i++) {
            int rpm, viteza, honk;
            double l100;

            if (i % 60 < 30) {
                // MOD ECO: RPM mic, Viteza mare
                rpm = 2200 + random.nextInt(300);
                viteza = 95 + random.nextInt(10);
                l100 = 3.8 + random.nextDouble();
            } else {
                // ACCELERARE
                rpm = 5500 + random.nextInt(1000);
                viteza = 40 + random.nextInt(30);
                l100 = 9.5 + random.nextDouble();
            }

            // Honk activ intermitent la fiecare 25 de pachete
            honk = (i % 25 < 4) ? 1 : 0;

            String data = rpm + "," + viteza + "," +
                    String.format("%.1f", 92.0 + random.nextDouble()*3).replace(",", ".") + "," +
                    (250 + random.nextInt(100)) + "," +
                    String.format("%.2f", l100).replace(",", ".") + "," +
                    honk;

            byte[] buffer = data.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, 5005);
            socket.send(packet);

            System.out.println("Trimis: " + data + (honk == 1 ? " [HONK!]" : ""));
            Thread.sleep(200);
        }
        socket.close();
    }
}
