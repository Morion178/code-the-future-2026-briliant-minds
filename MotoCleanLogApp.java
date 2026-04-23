import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.ArrayList;

public class MotoCleanLogApp extends JFrame {
    private CardLayout cardLayout = new CardLayout();
    private JLabel lblEcoMode;
    private JPanel mainPanel = new JPanel(cardLayout);
    private JLabel lblRPM, lblViteza, lblTemp, lblEmisii, lblConsum;
    private JProgressBar barGaz;
    private LiveChart liveChart;

    private final int PORT = 5005;// port UDP
    private final String FILE_NAME = "telemetrie.csv";//
    private boolean isConnected = false;

    private final Color COLOR_BG = new Color(10, 11, 15);
    private final Color COLOR_ACCENT = new Color(0, 255, 200);

    public MotoCleanLogApp() {
        resetFile();
        initUI();
        startUDPListener();
    }

    private void initUI() {
        setTitle("TELEMETRY SYSTEM V4.0");
        setSize(1100, 750);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        //pagina waiting pana cand se conecteaza la port
        JPanel startPage = new JPanel(new GridBagLayout());
        startPage.setBackground(COLOR_BG);
        JLabel lblLogo = new JLabel("SYSTEM INITIALIZED");
        lblLogo.setFont(new Font("Arial", Font.BOLD, 30));
        lblLogo.setForeground(COLOR_ACCENT);
        startPage.add(lblLogo);

        JPanel dashboardPage = createProfessionalDashboard();
        mainPanel.add(startPage, "START");
        mainPanel.add(dashboardPage, "DASHBOARD");
        add(mainPanel);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private JPanel createProfessionalDashboard() {
        JPanel panel = new JPanel(new BorderLayout(15, 15));
        panel.setBackground(COLOR_BG);
        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        // zona de main features
        JPanel topGrid = new JPanel(new GridLayout(1, 2, 20, 0));
        topGrid.setOpaque(false);
        lblRPM = createDisplay("0", "RPM", new Color(46, 204, 113));// zona de vizualizare RPM
        lblViteza = createDisplay("0", "KM/H", new Color(52, 152, 219));// zona vizualizare viteza
        topGrid.add(lblRPM);
        topGrid.add(lblViteza);

        // chart
        liveChart = new LiveChart();

        // zona secundara
        JPanel sidePanel = new JPanel(new GridLayout(3, 1, 15, 15));
        sidePanel.setOpaque(false);
        sidePanel.setPreferredSize(new Dimension(240, 0));

        lblTemp = createSmallDisplay("0.0°C", "TEMP", Color.ORANGE);//temperatura
        lblEmisii = createSmallDisplay("0", "CO2 ppm", Color.WHITE);//noxe
        lblConsum = createSmallDisplay("0.0 L", "ECONOMY", new Color(231, 76, 60));//daca e in economy mode
        //afisare economy
        lblEcoMode = new JLabel("ECO INACTIVE", SwingConstants.CENTER);
        lblEcoMode.setFont(new Font("Arial", Font.BOLD, 12));
        lblEcoMode.setForeground(Color.DARK_GRAY);
        lblEcoMode.setBorder(BorderFactory.createLineBorder(new Color(40, 40, 50)));

        sidePanel.add(lblTemp);
        sidePanel.add(lblEmisii);

        sidePanel.add(lblTemp);
        sidePanel.add(lblEmisii);
        sidePanel.add(lblConsum);
        JPanel fuelPanel = new JPanel(new GridLayout(2, 1));
        fuelPanel.setOpaque(false);
        fuelPanel.add(lblConsum);
        fuelPanel.add(lblEcoMode);
        sidePanel.add(fuelPanel);

        //pentru a vizualiza csv
        JPanel footer = new JPanel(new BorderLayout(10, 10));
        footer.setOpaque(false);
        barGaz = new JProgressBar(0, 100);
        barGaz.setForeground(COLOR_ACCENT);
        JButton btnHistory = new JButton("VIEW DATA LOGS");
        styleButton(btnHistory);
        btnHistory.addActionListener(e -> openHistoryWindow());
        footer.add(btnHistory, BorderLayout.SOUTH);

        panel.add(topGrid, BorderLayout.NORTH);
        panel.add(liveChart, BorderLayout.CENTER);
        panel.add(sidePanel, BorderLayout.EAST);
        panel.add(footer, BorderLayout.SOUTH);

        return panel;
    }

    private void processData(String data) {
        try {
            //data vine sub forma de string tip csv cu , intre elemente
            String[] p = data.split(",");
            if (p.length >= 4) {
                double gazRPM = Double.parseDouble(p[0]);
                double speedVal = Double.parseDouble(p[1]);
                double tempVal = Double.parseDouble(p[2]);
                double emisiiVal = Double.parseDouble(p[3]);

                // calc. consum
                double consumLitriOra = (gazRPM * 0.0008) * (1 + (gazRPM / 8000.0));
                double l100 = (speedVal > 5) ? (consumLitriOra / speedVal) * 100 : 0;

                saveToFile(data + "," + String.format("%.2f", l100));

                SwingUtilities.invokeLater(() -> {
                    lblRPM.setText(formatLarge((int)gazRPM + "", "RPM"));
                    lblViteza.setText(formatLarge((int)speedVal + "", "KM/H"));
                    lblTemp.setText(formatSmall(tempVal + "°C", "TEMP"));
                    lblEmisii.setText(formatSmall((int)emisiiVal + "", "CO2"));
                    lblConsum.setText(formatSmall(String.format("%.1f L", l100), "ECONOMY"));

                    // daca sunt in zona de eco merge doar la 100 km
                    if (l100 > 0 && l100 < 5.0) {
                        lblEcoMode.setText("● ECO ACTIVE");
                        lblEcoMode.setForeground(new Color(46, 204, 113)); // activ
                    } else {
                        lblEcoMode.setText("○ ECO INACTIVE");
                        lblEcoMode.setForeground(Color.DARK_GRAY);
                    }

                    barGaz.setValue((int)((gazRPM/8000.0)*100));
                    liveChart.addValue(speedVal);
                });
            }
        } catch (Exception e) {}
    }

 //formatare window
    private JLabel createDisplay(String v, String u, Color c) {
        JLabel l = new JLabel(formatLarge(v, u), SwingConstants.CENTER);
        l.setForeground(c);
        l.setBorder(BorderFactory.createLineBorder(new Color(40,40,50)));
        return l;
    }

    private JLabel createSmallDisplay(String v, String t, Color c) {
        JLabel l = new JLabel(formatSmall(v, t), SwingConstants.CENTER);
        l.setBorder(BorderFactory.createLineBorder(new Color(40,40,50)));
        return l;
    }

    private String formatLarge(String v, String u) {
        return "<html><center><font size='65' face='Monospaced'>" + v + "</font><br><font size='4'>" + u + "</font></center></html>";
    }

    private String formatSmall(String v, String t) {
        return "<html><center><font color='#888888' face='Arial' size='3'>" + t + "</font><br><font size='22' face='Monospaced' color='white'>" + v + "</font></center></html>";
    }

    private void styleButton(JButton b) {
        b.setBackground(new Color(25,25,30));
        b.setForeground(Color.WHITE);
        b.setBorder(new LineBorder(COLOR_ACCENT));
        b.setCursor(new Cursor(Cursor.HAND_CURSOR));
    }

   //prelucrare packet date din UDP
    private void startUDPListener() {
        new Thread(() -> {
            try (DatagramSocket s = new DatagramSocket(PORT)) {
                byte[] buf = new byte[1024];
                while (true) {
                    DatagramPacket p = new DatagramPacket(buf, buf.length);
                    s.receive(p);
                    if (!isConnected) {
                        isConnected = true;
                        SwingUtilities.invokeLater(() -> cardLayout.show(mainPanel, "DASHBOARD"));
                    }
                    processData(new String(p.getData(), 0, p.getLength()).trim());
                }
            } catch (Exception e) {}
        }).start();
    }
    //salvare date in csv
    private void saveToFile(String l) {
        try (FileWriter fw = new FileWriter(FILE_NAME, true); PrintWriter pw = new PrintWriter(fw)) {
            pw.println(System.currentTimeMillis() + "," + l);
        } catch (Exception e) {}
    }
    //cand dau run din nou se reseteaza datele din csv
    private void resetFile() {
        try (PrintWriter pw = new PrintWriter(new FileWriter(FILE_NAME, false))) {
            pw.println("Time,RPM,Speed,Temp,CO2,Consum");
        } catch (Exception e) {}
    }
    //deschide in alt panel csv-ul cu toate datele trimise
    private void openHistoryWindow() {
        JFrame f = new JFrame("History Log");
        DefaultTableModel m = new DefaultTableModel(new String[]{"Time", "RPM", "Speed", "Temp", "CO2", "L/100"}, 0);
        try (BufferedReader br = new BufferedReader(new FileReader(FILE_NAME))) {
            br.readLine(); String line;
            while ((line = br.readLine()) != null) m.addRow(line.split(","));
        } catch (Exception e) {}
        f.add(new JScrollPane(new JTable(m)));
        f.setSize(700, 400);
        f.setLocationRelativeTo(this);
        f.setVisible(true);
    }

    public static void main(String[] args) { new MotoCleanLogApp(); }

    // chart
    class LiveChart extends JPanel {
        private ArrayList<Double> values = new ArrayList<>();
        private final int MAX_POINTS = 50;
        private final int MARGIN_LEFT = 50;   // OY spatiu
        private final int MARGIN_BOTTOM = 40; // OX spatiu
        private final int MARGIN_TOP = 20;

        public void addValue(double val) {
            values.add(val);
            if (values.size() > MAX_POINTS) values.remove(0);
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int w = getWidth() - MARGIN_LEFT - 20;
            int h = getHeight() - MARGIN_BOTTOM - MARGIN_TOP;

            // deseneaza axele
            g2.setColor(new Color(60, 60, 70));
            g2.setStroke(new BasicStroke(1.5f));
            // OY
            g2.drawLine(MARGIN_LEFT, MARGIN_TOP, MARGIN_LEFT, h + MARGIN_TOP);
            // OX
            g2.drawLine(MARGIN_LEFT, h + MARGIN_TOP, w + MARGIN_LEFT, h + MARGIN_TOP);

            // numerotare pe axe la viteza
            g2.setFont(new Font("Monospaced", Font.PLAIN, 11));
            for (int i = 0; i <= 4; i++) {
                int speedLabel = i * 50; //din 50 in 50
                int yPos = h + MARGIN_TOP - (int) (speedLabel * (h / 200.0));

                // linii delimitare
                g2.setColor(new Color(40, 40, 50));
                g2.drawLine(MARGIN_LEFT, yPos, w + MARGIN_LEFT, yPos);
                g2.setColor(Color.GRAY);
                g2.drawString(String.format("%3d", speedLabel), 10, yPos + 5);
                g2.drawLine(MARGIN_LEFT - 5, yPos, MARGIN_LEFT, yPos);
            }

            // desenare linie de grafic
            if (values.size() < 2) return;

            double step = (double) w / (MAX_POINTS - 1);
            int[] xPoints = new int[values.size()];
            int[] yPoints = new int[values.size()];

            for (int i = 0; i < values.size(); i++) {
                xPoints[i] = MARGIN_LEFT + (int) (i * step);
                // limita superioara
                double val = Math.min(200, values.get(i));
                yPoints[i] = h + MARGIN_TOP - (int) (val * (h / 200.0));
            }

            // linie cu umbra
            g2.setStroke(new BasicStroke(3f));
            g2.setColor(COLOR_ACCENT);
            g2.drawPolyline(xPoints, yPoints, values.size());

            // gradient sub
            g2.setPaint(new GradientPaint(0, MARGIN_TOP, new Color(0, 255, 200, 60), 0, h + MARGIN_TOP, new Color(0,0,0,0)));
            Polygon poly = new Polygon();
            poly.addPoint(MARGIN_LEFT, h + MARGIN_TOP);
            for (int i = 0; i < values.size(); i++) poly.addPoint(xPoints[i], yPoints[i]);
            poly.addPoint(xPoints[values.size() - 1], h + MARGIN_TOP);
            g2.fill(poly);

            // eticheta OX
            g2.setColor(Color.GRAY);
            g2.setFont(new Font("Arial", Font.ITALIC, 10));
            g2.drawString("TIMP SIMULARE (SEC)", w / 2, h + MARGIN_TOP + 30);
        }

    }
}
