import java.util.Scanner;

public class Main {
    public static void main(String args[]) throws Exception {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.println(a + b);
        }
    }
}