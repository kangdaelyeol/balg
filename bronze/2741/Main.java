import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

  public static void main(String[] args) {
    String s = new String();
    int n;

    try {
      BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
      s = bf.readLine();
      n = Integer.parseInt(s);
      for (int i = 1; i <= n; i++) {
        System.out.println(i);
      }
    } catch (IOException e) {
      System.err.println(e);
    }
  }
}
