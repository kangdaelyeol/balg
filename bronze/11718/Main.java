import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

  public static void main(String[] args) {
    String line;
    try {
      BufferedReader reader = new BufferedReader(
        new InputStreamReader(System.in)
      );
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
    } catch (IOException e) {
      System.out.println(e);
    }
  }
}
