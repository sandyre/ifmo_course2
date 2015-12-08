package ifmo.sandyre;

/**
 * Created by aleksandr on 25.11.15.
 */
public class Punto
{
    public Punto(double _X, double _Y)
    {
        X = _X;
        Y = _Y;

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

    private boolean previous_state;
    private boolean current_state;
}