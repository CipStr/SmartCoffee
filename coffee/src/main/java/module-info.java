module gui.coffee {
    requires javafx.controls;
    requires javafx.fxml;
    requires jssc;


    opens gui.coffee to javafx.fxml;
    exports gui.coffee;
}