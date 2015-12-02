import java.io.*;
import org.junit.*;

public class KonturTest extends junit.framework.TestCase {
    Kontur k;
    Punto m1, m2, m3, m4, m5;
    float R;

    @Test
    public void testKonturURP() {
        R = 3.0f;
        k = new Kontur(R);

        m1 = new Punto(R/2,R/2);
        m2 = new Punto(R/2,0);
        m3 = new Punto(0,R/2);

        m4 = new Punto(R/4,R/4);
        m5 = new Punto(R/3,R/3);

        assertEquals(true,(k.includesPunto(m1) == 0) && (k.includesPunto(m2) == 0)
                && (k.includesPunto(m3) == 0) && (k.includesPunto(m4) == 1) && (k.includesPunto(m5) == 1));
    }


    @Test
    public void testKonturULP() {
        R = 10.0f;
        k = new Kontur(R);

        m1 = new Punto(-R,R);
        m2 = new Punto(-2*R,2*R);
        m3 = new Punto(-4*R,4*R);

        assertEquals(true,(k.includesPunto(m1) == 0) && (k.includesPunto(m2) == 0)
                && (k.includesPunto(m3) == 0));
    }

    @Test
    public void testKonturDLP() {
        R = 5.0f;
        k = new Kontur(R);

        m1 = new Punto(-R,0);
        m2 = new Punto(-R,-R);
        m3 = new Punto(0,-R);

        m4 = new Punto(-R/4,-R/4);
        m5 = new Punto(-R/3,-R/3);

        assertEquals(true,(k.includesPunto(m1) == 0) && (k.includesPunto(m2) == 0)
                && (k.includesPunto(m3) == 0) && (k.includesPunto(m4) == 1) && (k.includesPunto(m5) == 1));
    }

    @Test
    public void testKonturDRP() {
        R = 7.0f;
        k = new Kontur(R);

        m1 = new Punto(R,0);
        m2 = new Punto(0,-R);
        m3 = new Punto(R/2,-R/2);

        m4 = new Punto(R/4,-R/4);
        m5 = new Punto(R/3,-R/3);

        assertEquals(true,(k.includesPunto(m1) == 0) && (k.includesPunto(m2) == 0)
                && (k.includesPunto(m3) == 0) && (k.includesPunto(m4) == 1) && (k.includesPunto(m5) == 1));
    }
}