package ifmo.sandyre.lab4;

import javax.management.NotificationEmitter;

/**
 * Created by aleksandr on 11.01.16.
 */
public interface ShotsControllerMBean extends NotificationEmitter {
    int getTotalShotsCount();
    int getInShotsCount();
}
