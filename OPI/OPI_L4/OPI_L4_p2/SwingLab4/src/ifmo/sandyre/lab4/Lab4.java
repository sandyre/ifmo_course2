package ifmo.sandyre.lab4;

import javax.management.MBeanServer;
import javax.management.ObjectName;
import java.lang.management.ManagementFactory;

public class Lab4 {
    public static void main(String[] args) {
        MBeanServer mbs = ManagementFactory.getPlatformMBeanServer();

        mbs.registerMBean(controller.getModel(), new ObjectName("Lab4:type=Model"));
        mbs.registerMBean(controller.getAreaCalculator(), new ObjectName("Lab4:type=AreaCalculator"))
    }
}
