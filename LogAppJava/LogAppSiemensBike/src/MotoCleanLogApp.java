import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.ArrayList;
import javax.sound.sampled.*; // New import for audio

public class MotoCleanLogApp extends JFrame {
    private boolean isDisplayActive = false;
    private CardLayout cardLayout = new CardLayout();
    private JPanel mainPanel = new JPanel(cardLayout);

    private JLabel lblRPM, lblViteza, lblTemp, lblEmisii, lblConsum, lblEcoMode, lblHonkIndicator;
    private LiveChart liveChart;

    private SourceDataLine engineLine;
    private byte[] rawEngineBytes; // The original idle sound
    private float currentPitch = 1.0f;
    private final int BUFFER_SIZE = 4096;

    private final int PORT = 5005;
    private final String FILE_NAME = "telemetrie.csv";
    private boolean isConnected = false;
    private boolean wasHonking = false;

    private Clip honkClip; // Audio clip object

    private final Color COLOR_BG = new Color(10, 11, 15);
    private final Color COLOR_ACCENT = new Color(0, 255, 200);

    public MotoCleanLogApp() {
        resetFile();
        loadEngineSound();
        initUI();
        loadHonkSound(); // Load the audio file into memory
        startUDPListener();
    }

    // New method to load your .wav file
    private void loadHonkSound() {
        try {
            // Ensure honk.wav is in your project root folder
            File soundFile = new File("C:\\Users\\Omen\\Desktop\\TemeFac\\AN2\\SiemensHackaton\\code-the-future-2026-briliant-minds\\LogAppJava\\LogAppSiemensBike\\src\\Goofy ahh car honk sound effect.wav");
            AudioInputStream audioStream = AudioSystem.getAudioInputStream(soundFile);
            honkClip = AudioSystem.getClip();
            honkClip.open(audioStream);
        } catch (Exception e) {
            System.err.println("Audio Error: " + e.getMessage());
        }
    }

    private void playHonk() {
        if (honkClip != null) {
            honkClip.setFramePosition(0); // Rewind to start
            honkClip.start();
        }
    }

    private void loadEngineSound() {
        try {
            File engineFile = new File("C:\\Users\\Omen\\Desktop\\TemeFac\\AN2\\SiemensHackaton\\code-the-future-2026-briliant-minds\\LogAppJava\\LogAppSiemensBike\\src\\Bike Idle Engine Sound Loop.wav");
            AudioInputStream stream = AudioSystem.getAudioInputStream(engineFile);
            AudioFormat format = stream.getFormat();

            rawEngineBytes = stream.readAllBytes();

            DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);
            engineLine = (SourceDataLine) AudioSystem.getLine(info);
            engineLine.open(format);
            engineLine.start();

            // New Thread: Software Resampler
            new Thread(() -> {
                float playbackIndex = 0;
                byte[] outputBuffer = new byte[BUFFER_SIZE];
                int frameSize = format.getFrameSize(); // usually 2 for mono, 4 for stereo

                while (true) {
                    for (int i = 0; i < BUFFER_SIZE; i += frameSize) {
                        int intIndex = (int) playbackIndex;
                        // Loop logic
                        if (intIndex * frameSize >= rawEngineBytes.length - frameSize) {
                            playbackIndex = 0;
                            intIndex = 0;
                        }

                        // Copy the "frame" (Left/Right samples)
                        for (int j = 0; j < frameSize; j++) {
                            outputBuffer[i + j] = rawEngineBytes[intIndex * frameSize + j];
                        }

                        // The secret: Move the index by the pitch factor instead of by 1
                        playbackIndex += currentPitch;
                    }
                    engineLine.write(outputBuffer, 0, BUFFER_SIZE);
                }
            }).start();

        } catch (Exception e) { e.printStackTrace(); }
    }

    private void initUI() {
        setTitle("TELEMETRY SYSTEM V4.0");
        setSize(1100, 750);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel startPage = new JPanel(new GridBagLayout());
        startPage.setBackground(COLOR_BG);
        JPanel logoContainer = new JPanel(new BorderLayout(15, 15));
        logoContainer.setOpaque(false);

        JLabel lblLogo = new JLabel("<html><center><font color='#888888' size='4'>CORE UNIT</font><br>" + "<b style='letter-spacing: 5px;'>SYSTEM INITIALIZED</b></center></html>", SwingConstants.CENTER);
        lblLogo.setFont(new Font("Segoe UI", Font.BOLD, 42));
        lblLogo.setForeground(COLOR_ACCENT);

        JLabel lblSubText = new JLabel("AWAITING UDP TELEMETRY STREAM [PORT " + PORT + "]", SwingConstants.CENTER);
        lblSubText.setFont(new Font("Monospaced", Font.PLAIN, 13));
        lblSubText.setForeground(Color.GRAY);

        JProgressBar bootBar = new JProgressBar();
        bootBar.setIndeterminate(true);
        bootBar.setPreferredSize(new Dimension(300, 3));
        bootBar.setBackground(new Color(20, 20, 25));
        bootBar.setForeground(COLOR_ACCENT);
        bootBar.setBorder(null);

        logoContainer.add(lblLogo, BorderLayout.NORTH);
        logoContainer.add(lblSubText, BorderLayout.CENTER);
        logoContainer.add(bootBar, BorderLayout.SOUTH);
        startPage.add(logoContainer);

        JPanel dashboardPage = createProfessionalDashboard();

        mainPanel.add(startPage, "START");
        mainPanel.add(dashboardPage, "DASHBOARD");
        add(mainPanel);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private JPanel createProfessionalDashboard() {
        JPanel panel = new JPanel(new BorderLayout(20, 20));
        panel.setBackground(COLOR_BG);
        panel.setBorder(BorderFactory.createEmptyBorder(25, 25, 25, 25));

        JPanel topGrid = new JPanel(new FlowLayout(FlowLayout.CENTER, 60, 10));
        topGrid.setOpaque(false);

        lblRPM = createCircularDisplay("0", "RPM", new Color(46, 204, 113));
        lblViteza = createCircularDisplay("0", "KM/H", new Color(52, 152, 219));

        topGrid.add(lblRPM);
        topGrid.add(lblViteza);

        JPanel midPanel = new JPanel(new GridLayout(1, 5, 15, 0));
        midPanel.setOpaque(false);
        midPanel.setPreferredSize(new Dimension(0, 100));

        lblTemp = createSmallDisplay("0.0°C", "TEMP", Color.ORANGE);
        lblEmisii = createSmallDisplay("0", "CO2 ppm", Color.WHITE);
        lblConsum = createSmallDisplay("0.0 L", "FUEL", new Color(231, 76, 60));

        // This will now show the Gear
        lblEcoMode = new JLabel("<html><center>GEAR<br><font color='gray'>N</font></center></html>", SwingConstants.CENTER);
        lblEcoMode.setOpaque(true);
        lblEcoMode.setBackground(new Color(25, 25, 30));
        lblEcoMode.setForeground(Color.WHITE);
        lblEcoMode.setBorder(BorderFactory.createLineBorder(new Color(40, 40, 50)));

        lblHonkIndicator = new JLabel("HORN", SwingConstants.CENTER);
        lblHonkIndicator.setOpaque(true);
        lblHonkIndicator.setBackground(new Color(25, 25, 30));
        lblHonkIndicator.setForeground(Color.DARK_GRAY);
        lblHonkIndicator.setBorder(BorderFactory.createLineBorder(new Color(40, 40, 50)));

        midPanel.add(lblTemp);
        midPanel.add(lblEmisii);
        midPanel.add(lblConsum);
        midPanel.add(lblEcoMode);
        midPanel.add(lblHonkIndicator);

        JPanel upperDashboard = new JPanel(new BorderLayout(20, 20));
        upperDashboard.setOpaque(false);
        upperDashboard.add(topGrid, BorderLayout.NORTH);
        upperDashboard.add(midPanel, BorderLayout.CENTER);

        liveChart = new LiveChart();
        liveChart.setPreferredSize(new Dimension(0, 180));
        JPanel footer = new JPanel(new BorderLayout(10, 10));
        footer.setOpaque(false);

        JButton btnHistory = new JButton("VIEW DATA LOGS");
        styleButton(btnHistory);
        btnHistory.addActionListener(e -> openHistoryWindow());

        JPanel buttonWrapper = new JPanel(new FlowLayout(FlowLayout.CENTER));
        buttonWrapper.setOpaque(false);
        JButton btnStartDisplay = new JButton("START MONITORING");
        btnStartDisplay.setFont(new Font("Segoe UI", Font.BOLD, 12));
        btnStartDisplay.setPreferredSize(new Dimension(200, 30));
        btnStartDisplay.setBackground(new Color(46, 204, 113));
        btnStartDisplay.setForeground(Color.WHITE);

        btnStartDisplay.addActionListener(e -> {
            isDisplayActive = !isDisplayActive;
            btnStartDisplay.setText(isDisplayActive ? "STOP MONITORING" : "START MONITORING");
            btnStartDisplay.setBackground(isDisplayActive ? new Color(231, 76, 60) : new Color(46, 204, 113));
        });

        buttonWrapper.add(btnStartDisplay);
        footer.add(buttonWrapper, BorderLayout.CENTER);
        footer.add(btnHistory, BorderLayout.SOUTH);

        panel.add(upperDashboard, BorderLayout.NORTH);
        panel.add(liveChart, BorderLayout.CENTER);
        panel.add(footer, BorderLayout.SOUTH);
        return panel;
    }

    private JLabel createCircularDisplay(String val, String unit, Color accentColor) {
        JLabel lbl = new JLabel("<html><center><font size='4' color='gray'>" + unit + "</font><br><font size='7' color='white' face='Monospaced'><b>" + val + "</b></font></center></html>", SwingConstants.CENTER) {
            @Override
            protected void paintComponent(Graphics g) {
                Graphics2D g2 = (Graphics2D) g.create();
                g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                int size = Math.min(getWidth(), getHeight()) - 10;
                int x = (getWidth() - size) / 2;
                int y = (getHeight() - size) / 2;
                g2.setColor(new Color(20, 20, 28));
                g2.fillOval(x, y, size, size);
                g2.setStroke(new BasicStroke(5f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
                g2.setColor(new Color(40, 40, 50));
                g2.drawOval(x + 5, y + 5, size - 10, size - 10);
                g2.setColor(accentColor);
                g2.drawArc(x + 5, y + 5, size - 10, size - 10, -30, 240);
                super.paintComponent(g);
                g2.dispose();
            }
        };
        lbl.setPreferredSize(new Dimension(250, 250));
        return lbl;
    }

    private void processData(String data) {
        try {
            String[] p = data.split(",");
            // Changed to length >= 7 to accommodate Gear
            if (p.length >= 7) {
                double rpm = Double.parseDouble(p[0]);
                double speed = Double.parseDouble(p[1]);
                double temp = Double.parseDouble(p[2]);
                double co2 = Double.parseDouble(p[3]);
                double l100 = Double.parseDouble(p[4]);
                int honk = Integer.parseInt(p[5]);
                int gear = Integer.parseInt(p[6]); // New gear variable

                float pitch = (float)(rpm / 1200.0f); // 1.0 pitch at 1200 RPM
                currentPitch = Math.max(0.4f, Math.min(pitch, 5.0f));

                // Log to console so you can see the values changing
                System.out.println("DEBUG -> RPM: " + (int)rpm + " | Target Pitch: " + currentPitch);

                saveToFile(data);

                if (isDisplayActive) {
                    SwingUtilities.invokeLater(() -> {
                        lblRPM.setText(formatLarge((int)rpm + "", "RPM"));
                        lblViteza.setText(formatLarge((int)speed + "", "KM/H"));
                        lblTemp.setText(formatSmall(temp + "°C", "TEMP"));
                        lblEmisii.setText(formatSmall((int)co2 + "", "CO2"));
                        lblConsum.setText(formatSmall(String.format("%.1f L", l100), "ECONOMY"));

                        // Update Gear Display
                        String gearText = (gear == 0) ? "N" : "G" + gear;
                        lblEcoMode.setText("<html><center>GEAR<br><font color='#00FFC8' size='6'>" + gearText + "</font></center></html>");

                        if (honk == 1) {
                            lblHonkIndicator.setBackground(new Color(46, 204, 113));
                            lblHonkIndicator.setForeground(Color.BLACK);
                            if (!wasHonking) {
                                playHonk(); // Use custom sound
                                wasHonking = true;
                            }
                        } else {
                            lblHonkIndicator.setBackground(new Color(25, 25, 30));
                            lblHonkIndicator.setForeground(Color.DARK_GRAY);
                            wasHonking = false;
                        }

                        liveChart.addValue(speed);
                    });
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private JLabel createSmallDisplay(String v, String t, Color c) {
        JLabel l = new JLabel(formatSmall(v, t), SwingConstants.CENTER);
        l.setOpaque(true);
        l.setBackground(new Color(25, 25, 30));
        l.setBorder(BorderFactory.createMatteBorder(0, 0, 3, 0, c));
        return l;
    }

    private String formatLarge(String v, String u) { return "<html><center><font size='65' face='Monospaced'>" + v + "</font><br><font size='4'>" + u + "</font></center></html>"; }
    private String formatSmall(String v, String t) { return "<html><center><font color='#888888' face='Arial' size='3'>" + t + "</font><br><font size='22' face='Monospaced' color='white'>" + v + "</font></center></html>"; }
    private void styleButton(JButton b) { b.setBackground(new Color(25,25,30)); b.setForeground(Color.WHITE); b.setBorder(new LineBorder(COLOR_ACCENT)); b.setCursor(new Cursor(Cursor.HAND_CURSOR)); }

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

    private void saveToFile(String l) { try (FileWriter fw = new FileWriter(FILE_NAME, true); PrintWriter pw = new PrintWriter(fw)) { pw.println(System.currentTimeMillis() + "," + l); } catch (Exception e) {} }
    private void resetFile() { try (PrintWriter pw = new PrintWriter(new FileWriter(FILE_NAME, false))) { pw.println("Time,RPM,Speed,Temp,CO2,Consum,Honk,Gear"); } catch (Exception e) {} }

    private void openHistoryWindow() {
        JFrame f = new JFrame("History Log");
        DefaultTableModel m = new DefaultTableModel(new String[]{"Time", "RPM", "Speed", "Temp", "CO2", "L/100", "Honk", "Gear"}, 0);
        try (BufferedReader br = new BufferedReader(new FileReader(FILE_NAME))) {
            br.readLine(); String line;
            while ((line = br.readLine()) != null) m.addRow(line.split(","));
        } catch (Exception e) {}
        f.add(new JScrollPane(new JTable(m))); f.setSize(750, 400); f.setLocationRelativeTo(this); f.setVisible(true);
    }

    public static void main(String[] args) { new MotoCleanLogApp(); }

    class LiveChart extends JPanel {
        private ArrayList<Double> values = new ArrayList<>();
        private final int MAX_POINTS = 50;
        private final int MARGIN_LEFT = 50, MARGIN_BOTTOM = 40, MARGIN_TOP = 20;

        public void addValue(double val) { values.add(val); if (values.size() > MAX_POINTS) values.remove(0); repaint(); }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            this.setBackground(COLOR_BG);
            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            int w = getWidth() - MARGIN_LEFT - 20, h = getHeight() - MARGIN_BOTTOM - MARGIN_TOP;
            g2.setColor(new Color(60, 60, 70));
            g2.drawLine(MARGIN_LEFT, MARGIN_TOP, MARGIN_LEFT, h + MARGIN_TOP);
            g2.drawLine(MARGIN_LEFT, h + MARGIN_TOP, w + MARGIN_LEFT, h + MARGIN_TOP);
            g2.setFont(new Font("Monospaced", Font.PLAIN, 11));
            for (int i = 0; i <= 4; i++) {
                int sl = i * 100;
                int y = h + MARGIN_TOP - (int) (sl * (h / 400.0));
                g2.setColor(new Color(40, 40, 50)); g2.drawLine(MARGIN_LEFT, y, w + MARGIN_LEFT, y);
                g2.setColor(Color.GRAY); g2.drawString(String.format("%3d", sl), 10, y + 5);
            }
            if (values.size() < 2) return;
            double step = (double) w / (MAX_POINTS - 1);
            int[] xP = new int[values.size()], yP = new int[values.size()];
            for (int i = 0; i < values.size(); i++) {
                xP[i] = MARGIN_LEFT + (int) (i * step);
                yP[i] = h + MARGIN_TOP - (int) (Math.min(400, values.get(i)) * (h / 400.0));
            }
            g2.setStroke(new BasicStroke(2.5f)); g2.setColor(COLOR_ACCENT); g2.drawPolyline(xP, yP, values.size());
            g2.setPaint(new GradientPaint(0, MARGIN_TOP, new Color(0, 255, 200, 60), 0, h + MARGIN_TOP, new Color(0,0,0,0)));
            Polygon poly = new Polygon(); poly.addPoint(MARGIN_LEFT, h + MARGIN_TOP);
            for (int i = 0; i < values.size(); i++) poly.addPoint(xP[i], yP[i]);
            poly.addPoint(xP[values.size() - 1], h + MARGIN_TOP); g2.fill(poly);
            g2.setColor(Color.GRAY); g2.drawString("TIMP SIMULARE (SEC)", w / 2, h + MARGIN_TOP + 30);
        }
    }
}