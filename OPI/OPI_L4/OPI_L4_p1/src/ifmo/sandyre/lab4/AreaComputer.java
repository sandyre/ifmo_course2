package ifmo.sandyre.lab4;

/**
 * Created by aleksandr on 11.01.16.
 */
public class AreaComputer implements AreaComputerMBean {
    public AreaComputer(double rad)
    {
        radius = rad;
        refreshArea();
    }

    public double getCurrentArea()
    {
        return current_area;
    }

    public void refreshArea()
    {
        current_area = (radius * radius) + (radius * radius)/2.0 +
                (Math.PI * 0.25 * radius * radius);
    }

    public void setRadius(double rad)
    {
        radius = rad;
    }

    private double radius;
    private double current_area;
}
