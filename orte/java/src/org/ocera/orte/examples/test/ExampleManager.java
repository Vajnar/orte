import org.ocera.orte.*;

public class ExampleManager {

  public static void main(String[] args) {
    Manager manager = new Manager();

    while(true) {
      try {
        Thread.sleep(1000);
      } catch(Exception e) {
        e.printStackTrace();
      }
    }
  }
}

