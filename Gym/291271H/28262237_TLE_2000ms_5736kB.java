import java.util.Arrays;
import java.util.Scanner;
import java.math.BigInteger;

public class Main {
  public static void main(String args[]) throws Exception {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    BigInteger[] arr = new BigInteger[n];
    for (int i = 0; i < n; i++) {
      arr[i] = scanner.nextBigInteger();
    }
    Arrays.sort(arr);
    for (int i = 0; i < n; i++) {
      System.out.print(arr[i]);
      System.out.print(' ');
    }
  }
}