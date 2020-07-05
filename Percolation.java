import java.util.Scanner;

public class Percolation {
    private int n;
    private int number_of_open_sites = 0;
    private int[][] a;
    private int[] ar;
    private int[] sr;
    private int maxsize=0;

    public Percolation(int node) {
        n = node;
        ar = new int[n*n];
        sr = new int[n*n];
        final int[][] arr = new int[n][n];
        a = arr;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                arr[i][j] = 0;
                ar[(n * i) + j] = (n * i) + j;
                sr[(n * i) + j] = 1;
            }
        }
    }

    public boolean isOpen(final int row, final int col) {
        return a[row - 1][col - 1] == 1;
    }
    
    public boolean isFull(final int row, final int col) {
        return a[row - 1][col - 1] != 1;
    }

    public int numberOfOpenSites() {
        int nn = number_of_open_sites;
        return nn;
    }

    private int root(int pos) {
        while (ar[pos] != pos) {
            pos = ar[pos];
        }
        return pos;
    }

    private void connect(int x, int y) {
        if (root(x - 1) == root(y - 1)) {
            return;
        }
        if (sr[root(y - 1)] < sr[root(x - 1)]) {
            x += y;
            y = x - y;
            x -= y;
        }
        sr[root(y - 1)] += sr[root(x - 1)];
        if (maxsize < sr[root(y - 1)]) {
            maxsize = sr[root(y - 1)];
        }
        final int r = root(y - 1);
        final int from = ar[x - 1];
        ar[x - 1] = r;
        for (int i = 0; i < n; ++i) {
            if (ar[i] == from) {
                ar[i] = r;
            }
        }
    }

    public void open(final int x, final int y) {
        if (isOpen(x, y)) {
            return;
        }
        a[x - 1][y - 1] = 1;
        if (((x - 1 - 1 >= 0) && (x - 1 - 1 < n)) && ((y - 1 >= 0) && (y - 1 < n)) && a[x - 1 - 1][y - 1] == 1) {
            connect((x - 1) * n + (y - 1) + 1, (x - 1 - 1) * n + (y - 1) + 1);
        }
        if (((x - 1 + 1 >= 0) && (x - 1 + 1 < n)) && ((y - 1 >= 0) && (y - 1 < n)) && a[x - 1 + 1][y - 1] == 1) {
            connect((x - 1) * n + (y - 1) + 1, (x - 1 + 1) * n + (y - 1) + 1);
        }
        if (((x - 1 >= 0) && (x - 1 < n)) && ((y - 1 - 1 >= 0) && (y - 1 - 1 < n)) && a[x - 1][y - 1 - 1] == 1) {
            connect((x - 1) * n + (y - 1) + 1, (x - 1) * n + (y - 1 - 1) + 1);
        }
        if (((x - 1 >= 0) && (x - 1 < n)) && ((y - 1 - 1 >= 0) && (y - 1 + 1 < n)) && a[x - 1][y - 1 + 1] == 1) {
            connect((x - 1) * n + (y - 1) + 1, (x - 1) * n + (y - 1 + 1) + 1);
        }
        number_of_open_sites++;
    }

    private boolean may_Percolate() {
        int l = 0;
        for (int i = 0; i < n; ++i) {
            if (a[0][i] != 0) {
                l = 1;
                break;
            }
        }
        if (l == 0) {
            return false;
        }
        for (int i = 0; i < n; ++i) {
            if (a[n - 1][i] != 0) {
                l = 0;
                break;
            }
        }
        return l != 1;
    }

    public boolean percolates() {
        if (number_of_open_sites < n) {
            return false;
        }
        if (!may_Percolate()) {
            return false;
        }
        final int[] a1 = new int[n];
        final int[] a2 = new int[n];
        for (int i = 0; i < n; i++) {
            a1[i] = root(i);
        }
        for (int i = 0; i < n; i++) {
            a2[i] = root(i + (n * (n - 1)));
        }
        int l = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a1[i] == a2[j]) {
                    l = 1;
                    break;
                }
            }
            if (l == 1) {
                break;
            }
        }
        if (l == 1) {
            return true;
        }
        return false;
    }

    public static void main(final String[] args) {
        Scanner inp = new Scanner(System.in);
        System.out.println("Grid number");
        int n;
        n = inp.nextInt();
        Percolation p = new Percolation(n);
        while(!p.percolates()){
            int x,y;
            x=inp.nextInt();
            y=inp.nextInt();
            p.open(x,y);
            if(p.percolates()){
                System.out.println("Yes");
            }
            else{
                System.out.println("No");
            }
        }
    }
}
