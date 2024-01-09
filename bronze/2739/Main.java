import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

  public static void main(String[] args) {
    String inp;

    try {
      BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
      inp = bf.readLine();
      int a = Integer.parseInt(inp);
      for (int i = 1; i <= 9; i++) {
        System.out.println(String.format("%s * %s = %s", a, i, a * i));
      }
    } catch (IOException e) {
      System.out.println(e);
    } catch (NumberFormatException e) {
      System.out.println(e);
    }
  }
}
