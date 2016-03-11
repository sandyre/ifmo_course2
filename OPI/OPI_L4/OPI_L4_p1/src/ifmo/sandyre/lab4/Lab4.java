package ifmo.sandyre.lab4;

import javax.swing.*;

public class Lab4 extends Thread {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Lab4());
    }

    @Override
    public void run()
    {
        new MainFrame();
    }
}
