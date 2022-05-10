package org.example;


import java.awt.*;

import javax.swing.*;

class SmartCoffee {
    private JFrame frame;
    private JPanel pane;
    private JLabel label;
    private JButton button1;
    private JButton button2;

    public static void main(String[] args) throws Exception {
        CommunicationThread comm = new CommunicationThread(new HomeController());
        comm.startCommunication();
        SwingUtilities.invokeLater(new SmartCoffee()::createAndShowGui);

    }

    public void createAndShowGui() {
        frame = new JFrame(getClass().getSimpleName());
        frame.setMinimumSize(new Dimension(400,400));
        pane = new JPanel();
        pane.setLayout(new BoxLayout(pane, BoxLayout.LINE_AXIS));

        button1 = new JButton("Refill");
        button2 = new JButton("Recover");
        label = new JLabel("Modality:");
        pane.add(label,BorderLayout.CENTER);
        pane.add(button1,BorderLayout.PAGE_END);
        pane.add(button2,BorderLayout.PAGE_END);

        frame.add(pane);

        frame.pack();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}