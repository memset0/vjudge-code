import java.util.Scanner;
import java.math.BigInteger;

public class Main {
    public static void main(String args[]) throws Exception {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            BigInteger a = scanner.nextBigInteger();
            BigInteger b = scanner.nextBigInteger();
            System.out.println(a + b);
        }
    }
}