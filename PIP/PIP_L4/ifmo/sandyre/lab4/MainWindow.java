package ifmo.sandyre.lab4;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by aleksandr on 21.11.15.
 */
public class MainWindow extends JPanel {
    private JPanel mwd;
    private JList list1;
    private JRadioButton y1RadioButton;
    private JRadioButton y2RadioButton;
    private JRadioButton y3RadioButton;
    private JRadioButton y4RadioButton;
    private JRadioButton y5RadioButton;
    private JTextField textField1;
    private JSpinner spinner1;
    private JPanel DrawingPanel;
    private JButton addPointButton;

    private int selectedx = 1, selectedy = 1;
    private double Radius = 3.0f;

    public MainWindow()
    {
        this.setLayout(new BorderLayout(2,2));

        ButtonGroup ybuttongroup = new ButtonGroup();
        ybuttongroup.add(y1RadioButton);
        ybuttongroup.add(y2RadioButton);
        ybuttongroup.add(y3RadioButton);
        ybuttongroup.add(y4RadioButton);
        ybuttongroup.add(y5RadioButton);

        list1.setSelectedIndex((int)selectedx - 1);
        spinner1.setValue(Radius);
        this.add(mwd);
        mwd.add(DrawingPanel);

        DrawPanel draw = new DrawPanel();
        DrawingPanel.add(draw);

        list1.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) { // x changed
                selectedx = list1.getSelectedIndex() + 1;
            }
        });


        y1RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 1;
            }
        });
        y2RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 2;
            }
        });
        y3RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 3;
            }
        });
        y4RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 4;
            }
        });
        y5RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 5;
            }
        });
        spinner1.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if((int)spinner1.getValue() >= 0)
                    Radius = Double.valueOf(spinner1.getValue().toString());
                else spinner1.setValue(0);
                draw.SetRadius(Integer.valueOf(spinner1.getValue().toString()));
            }
        });
        addPointButton.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                draw.AddNewPointWithButton(selectedx,selectedy);
            }
        });
    }
}