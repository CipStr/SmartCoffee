package org.example;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    public static void main(String[] args) throws Exception {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("resources/Home.fxml"));
        Parent root = loader.load();
        CommunicationThread comm = new CommunicationThread((HomeController)loader.getController());
        comm.startCommunication();
        primaryStage.setTitle("SmartCoffee");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
}

