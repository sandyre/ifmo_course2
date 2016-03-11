package ifmo.sandyre.lab4;

import javax.swing.*;
import java.awt.*;

/**
 * Created by aleksandr on 21.11.15.
 */
public class MainFrame extends JFrame {
    public MainFrame()
    {
        super("Lab4. var 1833");
        this.setResizable(false);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setSize(new Dimension(1000, 800));
        this.setMinimumSize(new Dimension(240, 240));

        MainWindow main = new MainWindow();
        this.add(main);

        this.setVisible(true);
    }
}
