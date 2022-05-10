import Task.CommunicationThread;
import fxml.HomeController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import serial.CommChannel;
import serial.SerialCommChannel;


public class Main extends Application  {
    public static void main(String args[]) throws Exception {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("fxml/Home.fxml"));
        Parent root = loader.load();
        CommunicationThread comm = new CommunicationThread((HomeController)loader.getController());
        comm.startCommunication();
        primaryStage.setTitle("Coffee Machine");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
}
