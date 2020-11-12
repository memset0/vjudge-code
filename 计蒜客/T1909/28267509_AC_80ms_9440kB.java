import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
  public static void main(String args[]) throws Exception {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    BigInteger ans = BigInteger.valueOf(0);
    for (int i = 1; i <= n; i++) {
      BigInteger cur = BigInteger.valueOf(1);
      for (int j = 1; j <= i; j++) {
        cur = cur.multiply(BigInteger.valueOf(j));
      }
      ans = ans.add(cur);
    }
    System.out.println(ans);
  }
}