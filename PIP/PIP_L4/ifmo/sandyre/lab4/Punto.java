package ifmo.sandyre.lab4;

/**
 * Created by aleksandr on 25.11.15.
 */
public class Punto
{
    public Punto(double _X, double _Y, int sX, int sY)
    {
        X = _X;
        Y = _Y;
        screenX = sX;
        screenY = sY;

        previous_state = false;
        current_state = false;
    }

    public double getX()
    {
        return X;
    }

    public double getY()
    {
        return Y;
    }

    public int getScreenX()
    {
        return screenX;
    }

    public int getScreenY()
    {
        return screenY;
    }

    public boolean getPreviousState()
    {
        return previous_state;
    }

    public void setPreviousState(boolean state)
    {
        previous_state = state;
    }

    public boolean getCurrentState()
    {
        return current_state;
    }

    public void setCurrentState(boolean state)
    {
        current_state = state;
    }

    private double X;
    private double Y;
    private int screenX;
    private int screenY;

    private boolean previous_state;
    private boolean current_state;
}