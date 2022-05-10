package org.example;

import javafx.application.Platform;

public class CommunicationThread {
    private CommChannel commChannel;
    private HomeController controller;
    public CommunicationThread(final HomeController controller) throws Exception {
        commChannel = new SerialCommChannel("COM6",9600);
        this.controller = controller;
    }
    public void startCommunication() {
        Thread thread = new Thread(){
            public void run(){
                while(true) {
                    try {
                        Thread.sleep(500);
                        if (commChannel.isMsgAvailable()) {
                            String msg = commChannel.receiveMsg();
                            System.out.println("Received: " + msg);
                            Platform.runLater(() -> controller.parse(msg));
                        }
                        Platform.runLater(() -> {
                            if(controller.message != null && controller.message.length() > 0) {
                                commChannel.sendMsg(controller.message);
                                controller.message = "";
                            }
                        });

                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        thread.start();
    }
}