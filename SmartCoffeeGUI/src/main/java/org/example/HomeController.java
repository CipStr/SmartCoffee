package org.example;
import java.util.Arrays;

enum MachineState {
    IDLE(1, "IDLE"),
    RUNNING(2, "MAKING"),
    PRODUCT_READY(3, "PRODUCT READY"),
    SLEEP(4, "SLEEPING"),
    ASSISTANCE(5, "ASSISTANCE");
    private int i;
    private String name;

    public int getI() {
        return this.i;
    }
    public String getName() {return this.name;}
    MachineState(int i, String name) {
        this.i = i;
        this.name = name;
    }
}

public class HomeController {

    public String message;
    private MachineState getStateByIndex(String i) {
        return Arrays.stream(MachineState.values()).filter(s -> s.getI() == Integer.parseInt(i)).findFirst().get();
    }
    private void setState(String stateIndex) {
        MachineState s = getStateByIndex(stateIndex);
    }

    /**
     * MachineUpdate precede ogni messaggio della macchina
     * Esempio Sintassi:
     * MachineUpdate&state=1&checks=5&coffee=5&tea=10&chocolate=8&
     * @param message
     */
    public void parse(String message) {
        if (message.contains("MachineUpdate")) {
            int stateIndex = message.indexOf("state")+6;
            setState(message.substring(stateIndex, message.indexOf('&',stateIndex+1)));
            int checkIndex = message.indexOf("checks")+7;
            int coffeeIndex = message.indexOf("coffee")+7;
            int teaIndex = message.indexOf("tea")+4;
            int chocolateIndex = message.indexOf("chocolate")+10;
        }
    }
    void sendMessage(String message) {
        this.message = message;
    }
}