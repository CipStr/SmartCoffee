import javafx.application.Application;
import javafx.scene.Scene;
// import javafx.scene.control.Label;
// import javafx.scene.layout.StackPane;
import javafx.scene.*;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import javafx.stage.Stage;

public class App extends Application {
    public static void main(String[] args) throws Exception {
        launch();
    }

    @Override
    public void start(Stage stage) throws Exception {
        // String javaVersion = System.getProperty("java.version");
        // String javafxVersion = System.getProperty("javafx.version");
        // Label l = new Label("Hello, JavaFX " + javafxVersion + ", running on Java " + javaVersion + ".");
        // Scene scene = new Scene(new StackPane(l), 640, 480);
        // stage.setScene(scene);
        // stage.show();



        Group root = new Group();
        Scene s = new Scene(root, 600, 600, Color.FUCHSIA);
        

        
        Rectangle r = new Rectangle(25,25,250,250);
        r.setFill(Color.BLUE);
        
        root.getChildren().add(r);

        stage.setTitle("Smart Coffee Machine");

        stage.setScene(s);
        stage.show();
    }
}