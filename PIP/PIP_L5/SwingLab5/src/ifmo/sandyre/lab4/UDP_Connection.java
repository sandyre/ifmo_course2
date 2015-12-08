package ifmo.sandyre.lab4;

import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * Created by aleksandr on 08.12.15.
 */
public class UDP_Connection {
    static private final UDP_Connection instance = new UDP_Connection();

    private UDP_Connection()
    {

    }

    public static UDP_Connection getInstance()
    {
        return instance;
    }

    public String Receive(int port, int buffersize) throws IOException
    {
        try(DatagramSocket socket = new DatagramSocket(port))
        {
            byte[] received_data = new byte[buffersize];
            DatagramPacket received_packet = new DatagramPacket(received_data, received_data.length);
            socket.receive(received_packet);

            return new String(received_packet.getData()).trim();
        }
    }

    public void Send(int port, String msg) throws IOException
    {
        byte[] data = msg.getBytes();

        try(DatagramSocket socket = new DatagramSocket(port+500))
        {
            InetAddress IPADDR = InetAddress.getLocalHost();

            DatagramPacket send_packet = new DatagramPacket(data, data.length, IPADDR, port);
            socket.send(send_packet);
        }
    }
}
