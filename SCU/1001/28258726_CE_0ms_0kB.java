import java.util.Scanner;

public class Main {
    public static void main(String args[]) throws Exception {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            BigInteger a = scanner.nextInt();
            BigInteger b = scanner.nextInt();
            System.out.println(a + b);
        }
    }
}