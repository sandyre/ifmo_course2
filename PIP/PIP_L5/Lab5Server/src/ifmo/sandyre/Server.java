package ifmo.sandyre;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Server implements Runnable {
    int server_port = 10003;
    int client_port = 10004;

    public Server(int server_p, int client_p)
    {
        server_port = server_p;
        client_port = client_p;
    }

    @Override
    public void run()
    {
        UDP_Connection connection = UDP_Connection.getInstance();

        try
        {
            String msg = connection.Receive(server_port, 10000);
            System.out.println("Received query: [" + msg + "]");

            new Thread(new Server(server_port, client_port)).start();

            String[] parsed_msg = msg.split(" "); // SPLITTED ARGS. 0 - R, 1 - x, 2 - y

            // prepare to return answer
            Kontur kontur = new Kontur(Float.parseFloat(parsed_msg[0]));
            int result = kontur.includesPunto(new Punto(Double.parseDouble(parsed_msg[1]),
                    Double.parseDouble(parsed_msg[2])));

            String answer = result == 1 ? "true" : "false";

            System.out.println("Sent:" + answer);
            connection.Send(client_port, answer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
