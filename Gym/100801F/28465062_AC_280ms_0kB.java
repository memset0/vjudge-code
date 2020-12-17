/******************************************************************/
/* ACM ICPC 2015-2016, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 24, 2015                                */
/******************************************************************/
/* Problem F. Fygon                                               */
/*                                                                */
/* Original idea         Pavel Mavrin                             */
/* Problem statement     Pavel Mavrin                             */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/
 
import java.io.*;
import java.util.*;
 
public class fygon_gk {
    static Scanner in;
    static PrintWriter out;
 
    class For {
        List<For> ops = new ArrayList<For>();
        boolean varBound;
        int bound;
        int var;
        int lags;
 
        For(int var, boolean varBound, int bound) {
            this.var = var;
            this.varBound = varBound;
            this.bound = bound;
        }
 
        public int ops(int[] vars) {
            int b = varBound ? vars[bound] : bound;
            int result = 0;
            for (vars[var] = 0; vars[var] < b; vars[var]++) {
                result += lags;
                for (For op : ops) {
                    result += op.ops(vars);
                }
            }
            return result;
        }
    }
 
    For parse(String line) {
        int var = line.replaceAll(" *for *([a-z]).*", "$1").charAt(0) - 'a';
        char bound = line.replaceAll(".*range\\(([a-z0-9])\\).*", "$1").charAt(0);
        if ('a' <= bound && bound <= 'z') {
            return new For(var, true, bound - 'a');
        } else {
            return new For(var, false, bound - '0');
        }
    }
 
    void run() {
        int n = 'n' - 'a';
 
        Deque<For> loops = new ArrayDeque<>();
        loops.add(new For(n, true, 0));
        int fors = 1;
        while (in.hasNext()) {
            String line = in.nextLine();
            int indent = (line.indexOf("for") + line.indexOf("lag") + 1) / 4;
            while (loops.size() > indent + 1) {
                loops.removeLast();
            }
            if (line.contains("lag")) {
                loops.getLast().lags++;
            } else {
                For op = parse(line);
                loops.getLast().ops.add(op);
                loops.addLast(op);
            }
            fors = Math.max(fors, loops.size());
        }
 
        int[] data = new int[fors];
        int[] vars = new int[26];
        for (vars[n] = 0; vars[n] < fors; vars[n]++) {
            data[vars[n]] = loops.getFirst().lags;
            for (For op : loops.getFirst().ops) {
                data[vars[n]] += op.ops(vars);
            }
        }
 
        long div = 1;
        for (int i = 1; i < fors; i++) {
            div *= i;
        }
        long[] coeffs = new long[fors];
        for (int i = 0; i < fors; i++) {
            long q = 1;
            for (int j = 0; j < fors; j++) {
                if (i != j) {
                    q *= (i - j);
                }
            }
            assert div % q == 0;
            q = data[i] * div / q;
            for (int m = 0; m < (1 << fors); m++) {
                if (((m >> i) & 1) == 0) {
                    long p = q;
                    int bits = -1;
                    for (int j = 0; j < fors; j++) {
                        if (((m >> j) & 1) == 1) {
                            p *= -j;
                        } else {
                            bits++;
                        }
                    }
                    coeffs[bits] += p;
                }
            }
        }
        for (int i = 0; i < fors; i++) {
            out.print(coeffs[i] + "/" + div + "+n*(");
        }
        out.print(0);
        for (int i = 0; i < fors; i++) {
            out.print(")");
        }
    }
 
    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("fygon.in"));
        out = new PrintWriter("fygon.out");
 
        new fygon_gk().run();
 
        in.close();
        out.close();
    }
}
 