package ifmo.sandyre.lab4;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.*;
import java.util.Locale;
import java.util.ResourceBundle;

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
    private JRadioButton y0RadioButton;
    private JRadioButton y1RadioButton1;
    private JRadioButton y2RadioButton1;
    private JRadioButton y3RadioButton1;
    private JRadioButton y4RadioButton1;
    private JRadioButton y5RadioButton1;
    private JTextField textField1;
    private JSpinner spinner1;
    private JPanel DrawingPanel;
    private JButton addPointButton;
    private JLabel setxlabel;
    private JLabel setylabel;
    private JLabel setrlabel;
    private JLabel addedpntlabel;
    private JButton RUButton;

    private int selectedx = 1, selectedy = 1;
    private double Radius = 3.0f;

    String current_locale = "ru";
    ResourceBundle lang_resources = ResourceBundle.getBundle("translations", new Locale("ru","RU")); // default lang is RU

    public void ChangeInterfaceLanguage()
    {
        setxlabel.setText(lang_resources.getString("setx"));
        setylabel.setText(lang_resources.getString("sety"));
        setrlabel.setText(lang_resources.getString("setr"));
        setxlabel.setText(lang_resources.getString("setx"));
        addPointButton.setText(lang_resources.getString("addpnt"));
        addedpntlabel.setText(lang_resources.getString("addedpnt"));
    }

    public MainWindow()
    {
        this.setLayout(new BorderLayout(2,2));

        ButtonGroup ybuttongroup = new ButtonGroup();
        ybuttongroup.add(y1RadioButton1);
        ybuttongroup.add(y2RadioButton1);
        ybuttongroup.add(y3RadioButton1);
        ybuttongroup.add(y4RadioButton1);
        ybuttongroup.add(y5RadioButton1);
        ybuttongroup.add(y0RadioButton);
        ybuttongroup.add(y1RadioButton);
        ybuttongroup.add(y2RadioButton);
        ybuttongroup.add(y3RadioButton);
        ybuttongroup.add(y4RadioButton);
        ybuttongroup.add(y5RadioButton);

        list1.setSelectedIndex((int)selectedx + 5);
        spinner1.setValue(Radius);
        this.add(mwd);
        mwd.add(DrawingPanel);

        DrawPanel draw = new DrawPanel(textField1);
        DrawingPanel.add(draw);


        ChangeInterfaceLanguage();

        list1.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) { // x changed
                selectedx = list1.getSelectedIndex() - 5;
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
        y0RadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = 0;
            }
        });
        y1RadioButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = -1;
            }
        });
        y2RadioButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = -2;
            }
        });
        y3RadioButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = -3;
            }
        });
        y4RadioButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = -4;
            }
        });
        y5RadioButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedy = -5;
            }
        });
        y5RadioButton1.addActionListener(new ActionListener() {
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
            public void stateChanged(ChangeEvent e)
            {
                draw.AddNewPointWithButton(selectedx,selectedy);
                textField1.setText(new String("{" + selectedx + ";" + selectedy + "}"));
            }
        });

        RUButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(current_locale == "ru")
                {
                    lang_resources = ResourceBundle.getBundle("translations", new Locale("sr","SR"));
                    current_locale = "sr";
                    ChangeInterfaceLanguage();
                }
                else
                {
                    lang_resources = ResourceBundle.getBundle("translations", new Locale("ru","RU"));
                    current_locale = "ru";
                    ChangeInterfaceLanguage();
                }
            }
        });
    }
}