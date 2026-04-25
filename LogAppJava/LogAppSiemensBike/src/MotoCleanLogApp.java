import javax.swing.*;//bib. fereastra (JButton, Jlabel, Jframe)
import javax.swing.table.DefaultTableModel;//face structura tebelului csv
import javax.swing.border.LineBorder;//borduri
import java.awt.*;//pentru grafica(Color, Font)
import java.io.*;//pentru a scrie in csv
import java.net.DatagramPacket;//pentru a primii pachetul UDP
import java.net.DatagramSocket;//canaul UDP
import java.util.ArrayList;//pt linia din chart


public class MotoCleanLogApp extends JFrame {
    private boolean isDisplayActive = false;//pentru a putea face functional butnul start/stop monitoring, cand este fals ignora datele trimise prin port dac este true incepe afisarea
    private CardLayout cardLayout = new CardLayout();//permite schimbarea ecranelor de la asteptat la dash
    private JPanel mainPanel = new JPanel(cardLayout);

    private JLabel lblRPM, lblViteza, lblTemp, lblEmisii, lblConsum, lblEcoMode, lblHonkIndicator;//container text pastreaza ref zona dash
    private LiveChart liveChart;//obiectul chart

    private final int PORT = 5005;//canal UDP pt receptie date mathlab
    private final String FILE_NAME = "telemetrie.csv";//csv salvare date
    private boolean isConnected = false;//mem. daca a sosit primul pachet date UDP
    private boolean wasHonking = false; //previne repetarea sunetului la fiecare pachet si presupun ca la inceput de app e 0
    //tema color
    private final Color COLOR_BG = new Color(10, 11, 15);
    private final Color COLOR_ACCENT = new Color(0, 255, 200);
    //cand run
    public MotoCleanLogApp() {
        resetFile();//sa stearga date precedente csv
        initUI();//construieste fereastra
        startUDPListener();//incepe sa pazaesca portul UDP
    }
    //interfata grafica
    private void initUI() {
        setTitle("TELEMETRY SYSTEM V4.0");//nume platforma
        setSize(1100, 750);//dim. fereastra
        setDefaultCloseOperation(EXIT_ON_CLOSE);//exit on close

        //pagina asteptare conectare
        //creare panel
        JPanel startPage = new JPanel(new GridBagLayout());
        startPage.setBackground(COLOR_BG);//folosim peste tot aceeasi culoare de fundal
        JPanel logoContainer = new JPanel(new BorderLayout(15, 15));//container
        logoContainer.setOpaque(false);//
        //text pagina
        JLabel lblLogo = new JLabel("<html><center><font color='#888888' size='4'>CORE UNIT</font><br>" + "<b style='letter-spacing: 5px;'>SYSTEM INITIALIZED</b></center></html>", SwingConstants.CENTER);//
        lblLogo.setFont(new Font("Segoe UI", Font.BOLD, 42));
        lblLogo.setForeground(COLOR_ACCENT);//folosim culorile din tema
        //text asteapta conectare + port
        JLabel lblSubText = new JLabel("AWAITING UDP TELEMETRY STREAM [PORT " + PORT + "]", SwingConstants.CENTER);
        lblSubText.setFont(new Font("Monospaced", Font.PLAIN, 13));
        lblSubText.setForeground(Color.GRAY);
        //bara de progress care cerste gradual foarte incet
        JProgressBar bootBar = new JProgressBar();
        bootBar.setIndeterminate(true);
        bootBar.setPreferredSize(new Dimension(300, 3));//dimens
        bootBar.setBackground(new Color(20, 20, 25));
        bootBar.setForeground(COLOR_ACCENT);
        bootBar.setBorder(null);
        //adauga el. in Container
        logoContainer.add(lblLogo, BorderLayout.NORTH);
        logoContainer.add(lblSubText, BorderLayout.CENTER);
        logoContainer.add(bootBar, BorderLayout.SOUTH);
        startPage.add(logoContainer);
        //creare panel dash
        JPanel dashboardPage = createProfessionalDashboard();
        //add in container main pannel la pagina asteptare si dash
        mainPanel.add(startPage, "START");
        mainPanel.add(dashboardPage, "DASHBOARD");
        add(mainPanel);
        setLocationRelativeTo(null);
        setVisible(true);
    }
    //dash profesional
    private JPanel createProfessionalDashboard() {
        //creez pannel
        JPanel panel = new JPanel(new BorderLayout(20, 20));
        panel.setBackground(COLOR_BG);
        panel.setBorder(BorderFactory.createEmptyBorder(25, 25, 25, 25));
        //partea de sus a paginii dash(partea principala RPM si viteza)
        JPanel topGrid = new JPanel(new FlowLayout(FlowLayout.CENTER, 60, 10));
        topGrid.setOpaque(false);
        //sunt circ display amandoua
        lblRPM = createCircularDisplay("0", "RPM", new Color(46, 204, 113));
        lblViteza = createCircularDisplay("0", "KM/H", new Color(52, 152, 219));
        //le dau add in topgrid
        topGrid.add(lblRPM);
        topGrid.add(lblViteza);
        // partea de mijloc date mai neimportante(temp, co2, si economy si honk)
        JPanel midPanel = new JPanel(new GridLayout(1, 5, 15, 0));
        midPanel.setOpaque(false);
        midPanel.setPreferredSize(new Dimension(0, 100));
        //de tip small dysplay
        lblTemp = createSmallDisplay("0.0°C", "TEMP", Color.ORANGE);
        lblEmisii = createSmallDisplay("0", "CO2 ppm", Color.WHITE);
        lblConsum = createSmallDisplay("0.0 L", "FUEL", new Color(231, 76, 60));
        lblEcoMode = new JLabel("<html><center>MODE<br><font color='gray'>DRIVE</font></center></html>", SwingConstants.CENTER);
        lblEcoMode.setOpaque(true);
        lblEcoMode.setBackground(new Color(25, 25, 30));
        lblEcoMode.setForeground(Color.WHITE);
        lblEcoMode.setBorder(BorderFactory.createLineBorder(new Color(40, 40, 50)));
        //honk l-am adaugat mai tarziu:( si este buton care doar isi schimba culoarea si scoate sunet de notif
        lblHonkIndicator = new JLabel("HORN", SwingConstants.CENTER);
        lblHonkIndicator.setOpaque(true);
        lblHonkIndicator.setBackground(new Color(25, 25, 30));
        lblHonkIndicator.setForeground(Color.DARK_GRAY);
        lblHonkIndicator.setBorder(BorderFactory.createLineBorder(new Color(40, 40, 50)));
        //add catre zona midpannel
        midPanel.add(lblTemp);
        midPanel.add(lblEmisii);
        midPanel.add(lblConsum);
        midPanel.add(lblEcoMode);
        midPanel.add(lblHonkIndicator);
        //adaugare zone precedente
        JPanel upperDashboard = new JPanel(new BorderLayout(20, 20));
        upperDashboard.setOpaque(false);
        upperDashboard.add(topGrid, BorderLayout.NORTH);
        upperDashboard.add(midPanel, BorderLayout.CENTER);
        // footer
        //am facut chartul
        liveChart = new LiveChart();
        liveChart.setPreferredSize(new Dimension(0, 180));
        JPanel footer = new JPanel(new BorderLayout(10, 10));
        footer.setOpaque(false);
        //butonul de csv
        JButton btnHistory = new JButton("VIEW DATA LOGS");
        styleButton(btnHistory);
        btnHistory.addActionListener(e -> openHistoryWindow());
        //butonul de start stop monitoring care da toggle la daca sa asculte canalul UDP sau nu
        JPanel buttonWrapper = new JPanel(new FlowLayout(FlowLayout.CENTER));
        buttonWrapper.setOpaque(false);
        JButton btnStartDisplay = new JButton("START MONITORING");
        btnStartDisplay.setFont(new Font("Segoe UI", Font.BOLD, 12));
        btnStartDisplay.setPreferredSize(new Dimension(200, 30));
        btnStartDisplay.setBackground(new Color(46, 204, 113));
        btnStartDisplay.setForeground(Color.WHITE);
        //action listener
        btnStartDisplay.addActionListener(e -> {
            isDisplayActive = !isDisplayActive;
            //se schimba textul in fct de daca este apasat sau nu(stare)+culaorea
            btnStartDisplay.setText(isDisplayActive ? "STOP MONITORING" : "START MONITORING");
            btnStartDisplay.setBackground(isDisplayActive ? new Color(231, 76, 60) : new Color(46, 204, 113));
        });

        buttonWrapper.add(btnStartDisplay);
        footer.add(buttonWrapper, BorderLayout.CENTER);
        footer.add(btnHistory, BorderLayout.SOUTH);
        //ordinea de cum le adaug in pannel in zona de footer
        panel.add(upperDashboard, BorderLayout.NORTH);
        panel.add(liveChart, BorderLayout.CENTER);
        //le-am bagat in zona de footer
        panel.add(footer, BorderLayout.SOUTH);
        return panel;
    }
    //metoda sa fac RPM si viteza cercuri
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
    //cum procesez datele venite de pe UDPport
    private void processData(String data) {
        try {
            //vin sub forma de string ca in csv si le dau split
            String[] p = data.split(",");
            if (p.length >= 6) {
                //stiu ordinea lor ca sunt grupate ca in csv si stiu si ce tip de val astept
                double rpm = Double.parseDouble(p[0]);
                double speed = Double.parseDouble(p[1]);
                double temp = Double.parseDouble(p[2]);
                double co2 = Double.parseDouble(p[3]);
                double l100 = Double.parseDouble(p[4]);
                int honk = Integer.parseInt(p[5]);
                //le salvez in csv
                saveToFile(data);
                //doar daca s-a apsat start monitoring
                if (isDisplayActive) {
                    SwingUtilities.invokeLater(() -> {
                        //se schimba textul din labels de la 0 la ce val vin din port
                        lblRPM.setText(formatLarge((int)rpm + "", "RPM"));
                        lblViteza.setText(formatLarge((int)speed + "", "KM/H"));
                        lblTemp.setText(formatSmall(temp + "°C", "TEMP"));
                        lblEmisii.setText(formatSmall((int)co2 + "", "CO2"));
                        lblConsum.setText(formatSmall(String.format("%.1f L", l100), "ECONOMY"));
                        //aici verific daca se conzidera in mod eco sau nu
                        if (l100 > 0 && l100 < 5.0) {
                            lblEcoMode.setText("● ECO ACTIVE");
                            lblEcoMode.setForeground(new Color(46, 204, 113));
                        } else {
                            lblEcoMode.setText("○ ECO INACTIVE");
                            lblEcoMode.setForeground(Color.DARK_GRAY);
                        }
                        //am claxon sau nu am claxon
                        if (honk == 1) {
                            lblHonkIndicator.setBackground(new Color(46, 204, 113));
                            lblHonkIndicator.setForeground(Color.BLACK);
                            //ca sa nu coxoneze incontinuu verific daca data precedent a fost 0
                            if (!wasHonking) {
                                //daca var este false adica nu s-a claxonat deja pot sa claxonez
                                Toolkit.getDefaultToolkit().beep(); // sunet notificare
                                wasHonking = true;// schimb var ca sa nu claxonez incontinuu chiar daca datele mele vin 1 la honk
                            }
                        } else {
                            lblHonkIndicator.setBackground(new Color(25, 25, 30));
                            lblHonkIndicator.setForeground(Color.DARK_GRAY);
                            wasHonking = false; //il resetam daca nu a fost honk
                        }

                        liveChart.addValue(speed);//pun valoarea in chart
                    });
                }
            }
        } catch (Exception e) {}
    }
    //pentru formatare micile patrate de TEMP CO@ si eco
    private JLabel createSmallDisplay(String v, String t, Color c) {
        JLabel l = new JLabel(formatSmall(v, t), SwingConstants.CENTER);
        l.setOpaque(true);
        l.setBackground(new Color(25, 25, 30));
        l.setBorder(BorderFactory.createMatteBorder(0, 0, 3, 0, c));
        return l;
    }
    //generatoare de cod html si se respecta pt formatare
    private String formatLarge(String v, String u) { return "<html><center><font size='65' face='Monospaced'>" + v + "</font><br><font size='4'>" + u + "</font></center></html>"; }
    private String formatSmall(String v, String t) { return "<html><center><font color='#888888' face='Arial' size='3'>" + t + "</font><br><font size='22' face='Monospaced' color='white'>" + v + "</font></center></html>"; }
    private void styleButton(JButton b) { b.setBackground(new Color(25,25,30)); b.setForeground(Color.WHITE); b.setBorder(new LineBorder(COLOR_ACCENT)); b.setCursor(new Cursor(Cursor.HAND_CURSOR)); }
    //incepe asculatarea pe port
    private void startUDPListener() {
        new Thread(() -> {
            //pe thread separat pentru a fi eficient
            try (DatagramSocket s = new DatagramSocket(PORT)) {
                //fac un canal nou
                byte[] buf = new byte[1024];//creez buffer
                while (true) {//permanent
                    DatagramPacket p = new DatagramPacket(buf, buf.length);//creez pachet de date
                    s.receive(p);//porneste receive care parseaza datele
                    if (!isConnected) { isConnected = true; SwingUtilities.invokeLater(() -> cardLayout.show(mainPanel, "DASHBOARD")); }// daca vin datele se inchide pannel de asteptat si se deschide pannel de dash
                    processData(new String(p.getData(), 0, p.getLength()).trim());//process data proceseaza inf si le baga sub forma d esting ca sa le pot parsa
                }
            } catch (Exception e) {}
        }).start();
    }
    //salveaza in csv sub forma usuala
    private void saveToFile(String l) { try (FileWriter fw = new FileWriter(FILE_NAME, true); PrintWriter pw = new PrintWriter(fw)) { pw.println(System.currentTimeMillis() + "," + l); } catch (Exception e) {} }
    //metoda care sterge datele precedente din csv la restart page
    private void resetFile() { try (PrintWriter pw = new PrintWriter(new FileWriter(FILE_NAME, false))) { pw.println("Time,RPM,Speed,Temp,CO2,Consum,Honk"); } catch (Exception e) {} }
    //metoda care ma lasa sa accesez pannelul de istprie date
    private void openHistoryWindow() {
        //pannel nou
        JFrame f = new JFrame("History Log");
        //de tip table ca sa semene cu csv
        DefaultTableModel m = new DefaultTableModel(new String[]{"Time", "RPM", "Speed", "Temp", "CO2", "L/100", "Honk"}, 0);
        //baga el in table
        try (BufferedReader br = new BufferedReader(new FileReader(FILE_NAME))) {
            br.readLine(); String line;
            while ((line = br.readLine()) != null) m.addRow(line.split(","));
        } catch (Exception e) {}
        f.add(new JScrollPane(new JTable(m))); f.setSize(700, 400); f.setLocationRelativeTo(this); f.setVisible(true);
    }
    //the main
    public static void main(String[] args) { new MotoCleanLogApp(); }
    //clasa chart
    class LiveChart extends JPanel {
        //baga in lista de double
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
