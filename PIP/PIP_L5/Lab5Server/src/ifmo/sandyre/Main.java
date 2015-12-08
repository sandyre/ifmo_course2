package ifmo.sandyre;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by aleksandr on 08.12.15.
 */
public class Main {
    public static void main(String[] args) {
        int server_port = 10000;
        int client_port = 20000;

        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        Date date = new Date();
        System.out.println("Server started " + dateFormat.format(date));
        System.out.println("Listening port: " + server_port);
        Server server = new Server(server_port, client_port);
        server.run();
    }
}
