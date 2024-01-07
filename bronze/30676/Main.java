import java.util.Scanner;

public class Main {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String s = new String();
    int spectrum = sc.nextInt();

    if (spectrum > 780 || spectrum < 380) {
      sc.close();
      return;
    }

    if (spectrum >= 620) s = "Red"; else if (spectrum >= 590) s =
      "Orange"; else if (spectrum >= 570) s = "Yellow"; else if (
      spectrum >= 495
    ) s = "Green"; else if (spectrum >= 450) s = "Blue"; else if (
      spectrum >= 425
    ) s = "Indigo"; else if (spectrum >= 380) s = "Violet";

    System.out.println(s);
    sc.close();
    return;
  }
}
