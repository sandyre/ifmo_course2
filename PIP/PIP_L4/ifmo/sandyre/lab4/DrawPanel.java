package ifmo.sandyre.lab4;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.HashSet;
import java.util.Iterator;

/**
 * Created by aleksandr on 25.11.15.
 */
public class DrawPanel extends JPanel {
    // COLORS definitions
    Color bieg = new Color(253, 245, 230);
    Color brown = new Color(160,82,45);
    Color konturcolor = new Color(160, 82, 45);
    Color lightgreen = new Color(123, 255, 162);
    // end of COLORS

    private Float R = 3.0f;
    private int x;
    private int y;
    private boolean initialized = false;
    public  double lastpointx = 0.0f, lastpointy = 0.0f;
    private int centerx;
    private int centery;
    private int heigth;
    private int width;
    private int step;

    private Kontur kontur;
    private HashSet<Punto> points = new HashSet<Punto>();
    private JTextField coordsField;

    public DrawPanel(final JTextField coordsField_)
    {
        setBackground(bieg); // beige color
        setLayout(null);
        coordsField = coordsField_;

        kontur = new Kontur(R);
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                AddNewPoint(e.getX(), e.getY());
            }
        });
    }

    @Override
    public void paintComponent(Graphics g)
    {
        x = this.getX();
        y = this.getY();
        heigth = this.getHeight();
        width = this.getWidth();
        if(!initialized)
        {
            if(width + x < heigth + y) step = (x + width)/20;
            else step = (y + heigth)/20;
            initialized = true;
        }

        centerx = (x + width)/2;
        centery = (y + heigth)/2;

        super.paintComponent(g);
        DrawKontur(g);
        DrawCoords(g);
        DrawPoints(g);
    }

    private void DrawCoords(Graphics g)
    {
        g.setColor(Color.black);
        g.drawLine(centerx, y, centerx, heigth); // Y axis
        g.drawLine(x, centery, width, centery); // X axis

        for(int i = centerx; i <= width; i += step)
            g.drawLine(i, centery - 2, i, centery + 2);
        for(int i = centerx; i >= x; i -= step)
            g.drawLine(i, centery - 2, i, centery + 2);
        for(int i = centery; i <= heigth; i += step)
            g.drawLine(centerx - 2, i, centerx + 2, i);
        for(int i = centery; i >= y; i -= step)
            g.drawLine(centerx - 2, i, centerx + 2, i);
    }

    public void AddNewPoint(int x, int y)
    {
        Punto punto = new Punto((x - centerx)/(float)step * 1.0f, (centery - y)/(float)step * 1.0f, x, y);
        if(kontur.includesPunto(punto) == 1)
        {
            punto.setCurrentState(true);
        }
        else
        {
            punto.setCurrentState(false);
        }

        // to set jtextedit values
        lastpointx = (x - centerx)/(float)step * 1.0f;
        lastpointy = (centery - y)/(float)step * 1.0f;

        coordsField.setText(new String("{" + new BigDecimal(punto.getX()).setScale(3, RoundingMode.UP).doubleValue() + ";" +
                new BigDecimal(punto.getY()).setScale(3, RoundingMode.UP).doubleValue() + "}"));

        points.add(punto);
        repaint();
    }

    public void AddNewPointWithButton(int x, int y)
    {
        Punto punto = new Punto((x) * 1.0f, (y) * 1.0f, x * step + centerx, centery - y * step);
        if(kontur.includesPunto(punto) == 1)
        {
            punto.setCurrentState(true);
        }
        else
        {
            punto.setCurrentState(false);
        }

        coordsField.setText(new String("{" + punto.getX() + ";" + punto.getY() + "}"));

        points.add(punto);
        repaint();
    }

    public void SetRadius(int Radius)
    {
        R = new Float(Radius);

        if(R > (x + width)/step/2) step /= 2;
        kontur = new Kontur(R);

        boolean needanimation = false;
        for(Iterator<Punto> i = points.iterator(); i.hasNext(); )
        {
            Punto p = i.next();
            if((p.getCurrentState() == true) && (kontur.includesPunto(p) == 0))
            {
                needanimation = true;
            }
            if((kontur.includesPunto(p) == 1))
                p.setCurrentState(true);
            else p.setCurrentState(false);
        }

        if(needanimation) {
            new Animation().start();
        }

        repaint();
    }

    private void DrawPoints(Graphics g)
    {
        for (Punto p : points)
        {
            if(p.getCurrentState() == true) g.setColor(Color.green);
            else g.setColor(Color.red);

            g.drawOval(p.getScreenX(), p.getScreenY(), 3, 3);
        }
    }

    private void DrawKontur(Graphics g)
    {
        g.setColor(konturcolor); // brown

        Polygon polygon = new Polygon();
        polygon.addPoint(centerx, centery);
        polygon.addPoint(centerx, centery + R.intValue() * step);
        polygon.addPoint(centerx - R.intValue() * step, centery + R.intValue() * step);
        polygon.addPoint(centerx - R.intValue() * step, centery);

        g.fillPolygon(polygon);

        polygon = new Polygon();
        polygon.addPoint(centerx, centery);
        polygon.addPoint(centerx, centery + R.intValue() * step);
        polygon.addPoint(centerx + R.intValue() * step, centery);

        g.fillPolygon(polygon);

        g.fillArc(centerx - (R.intValue() * step)/2, centery - (R.intValue() * step)/2,
                R.intValue() * step, R.intValue() * step, 0, 90);
    }

    class Animation implements Runnable
    {
        Thread runner;

        public void start()
        {
            if(runner == null)
            {
                runner = new Thread(this);
                runner.start();
                run();
            }
        }

        public void stop()
        {
            if(runner != null)
            {
                runner = null;
            }
        }

        @Override
        public void run()
        {
            // brown 160, 82, 45
            // light green 123, 255, 162
            int red = 160;
            int green = 82;
            int blue = 45;
            int stagespassed = 0;
            konturcolor = brown;
            Thread thisThread = Thread.currentThread();
            while(runner == thisThread && stagespassed != 2) {
                while (true) {
                    konturcolor = new Color(red, green, blue);
                    if(green < lightgreen.getGreen()) green += 1;
                    if(blue < lightgreen.getBlue()) blue += 1;

                    try {
                        repaint();
                        Thread.sleep(5);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                    if(green == lightgreen.getGreen() && blue == lightgreen.getBlue())
                    {
                        stagespassed++;
                        break;
                    }
                }

                konturcolor = lightgreen;
                while (true) {
                    konturcolor = new Color(red, green, blue);
                    if(green > brown.getGreen()) green -= 1;
                    if(blue > brown.getBlue()) blue -= 1;
                    try {
                        repaint();
                        Thread.sleep(5);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                    if(green == brown.getGreen() && blue == brown.getBlue())
                    {
                        stagespassed++;
                        break;
                    }
                }
            }
        }
    }
 }
