package ifmo.sandyre.lab4;

/**
 * Created by aleksandr on 25.11.15.
 */
public class Kontur
{
    public Kontur(float _R)
    {
        R = _R;
    }

    public int includesPunto(Punto punto)
    {
        double x = punto.getX();
        double y = punto.getY();

        return  (((x > -R) && (x <= 0) && (y > -R) && (y < 0)) ||
                ((x > 0) && (x < R) && (y > -R) && (y < 0) && (y > x-R)) ||
                ((x > 0) && (y >= 0) && ((x*x + y*y) < (R*R/4)))) ? 1 : 0;

    }

    private float R;
}
