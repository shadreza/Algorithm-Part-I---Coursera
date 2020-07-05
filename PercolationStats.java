import java.util.Scanner;
import java.util.Random;
class uf{
    private int n;
    private int[] a;
    private int[] s;
    private int maxsize=0;
    public uf(int node){
        n=node*node;
        int[] arr = new int[n];
        int[] srr = new int[n];
        a=arr;
        s=srr;
        for(int i=0;i<n;++i){
            arr[i]=i;
            srr[i]=1;
        }
    }
    public int root(int pos) {
        while (a[pos] != pos) {
            pos = a[pos];
        }
        return pos;
    }
    public void connect(int x,int y){
        if(root(x-1)==root(y-1)){
            return ;
        }
        if(s[root(y-1)]<s[root(x-1)]){
            x+=y;
            y=x-y;
            x-=y;
        }
        s[root(y-1)]+=s[root(x-1)];
        if(maxsize<s[root(y-1)]){
            maxsize=s[root(y-1)];
        }
        int r = root(y-1);
        int from = a[x-1];
        a[x-1]=r;
        for(int i=0;i<n;++i){
            if(a[i]==from){
                a[i]=r;
            }
        }
    }
}
class Percolation {
    uf u;
    public int n;
    int number_of_open_sites=0;
    public int[][] a;
    public Percolation(int node){
        n=node;
        u = new uf(n);
        int[][] arr = new int[n][n];
        a=arr;
        for(int i=0;i<n;++i) {
            for (int j=0;j<n;++j) {
                arr[i][j] = 0;
            }
        }
    }
    public boolean isOpen(int row, int col){
        return a[row - 1][col - 1] == 1;
    }
    public boolean isFull(int row, int col){
        return a[row - 1][col - 1] != 1;
    }
    public int numberOfOpenSites(){
        return  number_of_open_sites;
    }
    public void open(int x, int y){
        if(isOpen(x,y)){
            return;
        }
        a[x-1][y-1]=1;
        if(((x-1-1>=0)&&(x-1-1<n)) && ((y-1>=0)&&(y-1<n)) && a[x-1-1][y-1]==1){
            u.connect((x-1)*n + (y-1) +1, (x-1-1)*n + (y-1) +1);
        }
        if(((x-1+1>=0)&&(x-1+1<n)) && ((y-1>=0)&&(y-1<n)) && a[x-1+1][y-1]==1){
            u.connect((x-1)*n + (y-1) +1, (x-1+1)*n + (y-1) +1);
        }
        if(((x-1>=0)&&(x-1<n)) && ((y-1-1>=0)&&(y-1-1<n)) && a[x-1][y-1-1]==1){
            u.connect((x-1)*n + (y-1) +1, (x-1)*n + (y-1-1) +1);
        }
        if(((x-1>=0)&&(x-1<n)) && ((y-1-1>=0)&&(y-1+1<n)) && a[x-1][y-1+1]==1){
            u.connect((x-1)*n + (y-1) +1, (x-1)*n + (y-1+1) +1);
        }
        number_of_open_sites++;
    }
    private boolean may_Percolate(){
        int l=0;
        for(int i=0;i<n;++i){
            if(a[0][i]!=0){
                l=1;
                break;
            }
        }
        if(l==0){
            return false;
        }
        for(int i=0;i<n;++i){
            if(a[n-1][i]!=0){
                l=0;
                break;
            }
        }
        return l != 1;
    }
    public boolean percolates(){
        if(numberOfOpenSites()<n){
            return false;
        }
        if(!may_Percolate()){
            return false;
        }
        int[] a1 = new int[n];
        int[] a2 = new int[n];
        for(int i=0;i<n;i++){
            a1[i]=u.root(i);
        }
        for(int i=0;i<n;i++){
            a2[i]=u.root(i+(n*(n-1)));
        }
        int l=0;
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(a1[i]==a2[j]){
                    l=1;
                    break;
                }
            }
            if(l==1){
                break;
            }
        }
        if(l==1){
            return  true;
        }
        return false;
    }

    public static void main(String[] args) {

    }
}
public class PercolationStats {
    private double[]  probability;
    private int attempts;
    private int n;
    public PercolationStats(int node, int trials){
        n=node;
        attempts=trials;
        probability = new double[trials];
        for(int i=0;i<trials;++i){
            Percolation p = new Percolation(n);
            int steps_needed_to_percolate=0;
            while(!p.percolates()){
                int rx,cy;
                Random ran = new Random();
                rx=ran.nextInt(n)+1;
                cy=ran.nextInt(n)+1;
                if(p.isOpen(rx,cy)){
                    continue;
                }
                p.open(rx,cy);
                ++steps_needed_to_percolate;
            }
            probability[i]=(1.0*steps_needed_to_percolate)/(n*n);
        }
    }
    public double mean(){
        double sum_x=0.0;
        for(int i=0;i<attempts;++i){
            sum_x+=probability[i];
        }
        double mean=sum_x/attempts;
        return mean;
    }
    public double stddev(){
        double median = mean();
        double s=0.0;
        for(int i=0;i<attempts;++i){
            s+=(probability[i]-median)*(probability[i]-median);
        }
        s/=(attempts-1);
        s=Math.sqrt(s);
        return s;
    }
    public double confidenceLo(){
        double cnf_low = mean()-((1.96*stddev())/Math.sqrt(attempts));
        return cnf_low;
    }
    public double confidenceHi(){
        double cnf_hi = mean()+((1.96*stddev())/Math.sqrt(attempts));
        return cnf_hi;
    }
    public static void main(String[] args){
        Scanner inp = new Scanner(System.in);
        int n = inp.nextInt();
        int tr = inp.nextInt();
        PercolationStats p = new PercolationStats(n,tr);
        System.out.println("mean\t\t\t\t\t= "+p.mean());
        System.out.println("stddev\t\t\t\t\t= "+p.stddev());
        System.out.println("95% confidence interval\t= ["+p.confidenceLo()+", "+p.confidenceHi()+"]");
    }
}