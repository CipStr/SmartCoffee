package gui.coffee;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

import java.util.Arrays;

public class HomeController {
    @FXML
    public Label label;
    public String message;

    public void parse(String message) {
        label.setText(message);
        //if (message.contains("MachineUpdate")) {
          //  label.setText(message);
        //}
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