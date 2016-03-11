package ifmo.sandyre.lab4;

import javax.management.Notification;
import javax.management.NotificationBroadcasterSupport;

/**
 * Created by aleksandr on 11.01.16.
 */
public class ShotsController extends NotificationBroadcasterSupport
        implements ShotsControllerMBean {
    public void radiusChanged(int successshots)
    {
        missed_shots_count = successshots;
    }

    public void refresh_and_add_shot(boolean shot)
    {
        if(shot)
        {
            total_shots_count++;
            missed_shots_in_row = 0;
        }
        else
        {
            missed_shots_count++;
            total_shots_count++;
            missed_shots_in_row++;
        }

        if(missed_shots_in_row == 3)
        {
            missed_shots_in_row = 0;
            sendNotification(new Notification("--- in a row", this, sequence_number++, System.currentTimeMillis(),
                    "3 missed shots were made in a row!"));
        }
    }

    public int getInShotsCount()
    {
        return missed_shots_count;
    }

    public int getTotalShotsCount()
    {
        return total_shots_count;
    }

    private int sequence_number = 1;
    private int missed_shots_in_row = 0;
    private int total_shots_count = 0;
    private int missed_shots_count = 0;
}
