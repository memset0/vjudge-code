import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;
 
public class cactus_gk {
    static Scanner in;
    static PrintWriter out;
 
    static class Solution {
        List<List<Integer>> edges;
        List<List<Integer>> directs;
        List<String> ops = new ArrayList<>();
        int[] color;
        int[] parents;
 
        void run() {
            int n = in.nextInt();
            int m = in.nextInt();
            edges = Stream.<List<Integer>>generate(ArrayList::new).limit(n + 1).collect(Collectors.toList());
            directs = Stream.<List<Integer>>generate(ArrayList::new).limit(n + 1).collect(Collectors.toList());
            color = new int[n + 1];
            parents = IntStream.rangeClosed(0, n).toArray();
            for (int i = 0; i < m; i++) {
                int k = in.nextInt();
                int v = in.nextInt();
                for (int j = 0; j < k - 1; j++) {
                    int u = in.nextInt();
                    edges.get(u).add(v);
                    edges.get(v).add(u);
                    v = u;
                }
            }
            dfs(1, 0);
            out.println(ops.size());
            ops.forEach(out::println);
        }
 
        private boolean dfs(int v, int p) {
            color[v] = 1;
            boolean immediate = false;
            List<Integer> joins = new ArrayList<>();
            List<Integer> djoins = new ArrayList<>();
            for (int u : edges.get(v)) {
                if (u == p) {
                    // Do not go back
                } else if (color[u] == 0) {
                    if (dfs(u, v)) {
                        djoins.add(u);
                    } else {
                        joins.add(u);
                    }
                } else if (color[u] == 1) {
                    immediate = true;
                    directs.get(u).add(v);
                }
            }
 
            for (Integer u : directs.get(v)) {
                join(u, v);
                connect(v, "1 4");
                recolor(v, "4 3");
            }
 
            djoins.forEach(u -> join(v, u));
            connect(v, "1 4");
 
            joins.forEach(u -> join(v, u));
            connect(v, "1 2");
            recolor(v, "2 3");
 
            if (immediate) {
                recolor(v, "1 4");
            } else {
                recolor(v, "1 2");
            }
 
            color[v] = 2;
            return immediate;
        }
 
        private void connect(final int v, final String s) {
            out("c " + v + " " + s);
        }
 
        private void out(final String x) {
            ops.add(x);
        }
 
        private void recolor(final int v, final String s) {
            out("r " + v + " " + s);
        }
 
        private void join(final int v, final int u) {
            if (get(v) != get(u)) {
                parents[get(v)] = get(u);
                out("j " + v + " " + u);
            }
        }
 
        private int get(final int v) {
            if (parents[v] == v) {
                return v;
            } else {
                return parents[v] = get(parents[v]);
            }
        }
    }
 
    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("cactus.in"));
        out = new PrintWriter("cactus.out");
 
        new Solution().run();
 
        in.close();
        out.close();
    }
}