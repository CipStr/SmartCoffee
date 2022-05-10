package fxml;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.paint.Color;

import java.util.Arrays;

enum MachineState {
    IDLE(1, "IDLE", Color.BLACK),
    RUNNING(2, "MAKING", Color.GREEN),
    PRODUCT_READY(3, "PRODUCT READY", Color.BLUE),
    SLEEP(4, "SLEEPING", Color.PINK),
    ASSISTANCE(5, "ASSISTANCE", Color.ORANGE);
    private int i;
    private String name;
    private Color color;

    public int getI() {
        return this.i;
    }
    public String getName() {return this.name;}
    public Color getColor() {return this.color;}
    MachineState(int i, String name, Color color) {
        this.i = i;
        this.name = name;
        this.color = color;
    }
}

public class HomeController {

    public String message;
    @FXML
    public Label state;
    @FXML
    Label checkAmount;
    @FXML
    Label coffee_qty;
    @FXML
    Label tea_qty;
    @FXML
    Label chocolate_qty;

    private MachineState getStateByIndex(String i) {
        return Arrays.stream(MachineState.values()).filter(s -> s.getI() == Integer.parseInt(i)).findFirst().get();
    }
    private void setState(String stateIndex) {
        MachineState s = getStateByIndex(stateIndex);
        state.setText(s.getName());
        state.setTextFill(s.getColor());
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
            checkAmount.setText(message.substring(checkIndex, message.indexOf('&', checkIndex)));
            int coffeeIndex = message.indexOf("coffee")+7;
            coffee_qty.setText(message.substring(coffeeIndex, message.indexOf('&',coffeeIndex)));
            int teaIndex = message.indexOf("tea")+4;
            tea_qty.setText(message.substring(teaIndex, message.indexOf('&',teaIndex)));
            int chocolateIndex = message.indexOf("chocolate")+10;
            chocolate_qty.setText(message.substring(chocolateIndex, message.indexOf('&',chocolateIndex)));
        }
    }

    @FXML
    void recover() {
        sendMessage("recover");
    }
    @FXML
    void refill() {
        sendMessage("refill");
    }

    void sendMessage(String message) {
        this.message = message;
    }
}
