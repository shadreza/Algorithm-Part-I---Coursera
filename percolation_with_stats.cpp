#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;
class uf{
public:
    int nodes;
    int * a;
    int * s;
    int maxsize=0;
    uf(int e,int f){
        nodes = e*f;
        a = new int [nodes];
        s = new int [nodes];
        for(int i=0;i<nodes;++i){
            a[i]=i;
            s[i]=1;
        }
    }
    ~uf(){
        for(int i=0;i<nodes;++i){
            a[i]=s[i]=0;
        }
        delete a;
        delete s;
        nodes = 0;
    }
    int root(int i){
        while(a[i]!=i){
            i=a[i];
        }
        return i;
    }
    void connect(int x,int y){
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
        for(int i=0;i<nodes;++i){
            if(a[i]==from){
                a[i]=r;
            }
        }
    }
    void show(){
        for(int i=0;i<nodes;++i){
            printf("node(%d)_%d_size(%d)\n",i+1,a[i],s[i]);
        }
    }
};
class percolation{
public:
    int r,c,n_of_open_sites=0;
    int ** a;
    uf * set;
    vector < pair<int,int> > a_open_sites;
    percolation(int y,int x){
        r=y;
        c=x;
        set = new uf(r,c);
//        cout << "Preparing the grid " << r << "x" << c << "\n";
        a = new int*[r];
        for(int i=0;i<r;++i){
            a[i] = new int[c];
        }
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                a[i][j]=0;
            }
        }
    }
    void open_site(int x, int y){
        if(a[x-1][y-1]==1){
            return ;
        }
        a[x-1][y-1]=1;
        if(((x-1-1>=0)&&(x-1-1<r)) && ((y-1>=0)&&(y-1<c)) && a[x-1-1][y-1]==1){
            set->connect((x-1)*c + (y-1) +1, (x-1-1)*c + (y-1) +1);
        }
        if(((x-1+1>=0)&&(x-1+1<r)) && ((y-1>=0)&&(y-1<c)) && a[x-1+1][y-1]==1){
            set->connect((x-1)*c + (y-1) +1, (x-1+1)*c + (y-1) +1);
        }
        if(((x-1>=0)&&(x-1<r)) && ((y-1-1>=0)&&(y-1-1<c)) && a[x-1][y-1-1]==1){
            set->connect((x-1)*c + (y-1) +1, (x-1)*c + (y-1-1) +1);
        }
        if(((x-1>=0)&&(x-1<r)) && ((y-1-1>=0)&&(y-1-1<c)) && a[x-1][y-1+1]==1){
            set->connect((x-1)*c + (y-1) +1, (x-1)*c + (y-1+1) +1);
        }
//        cout << "The site is open\n";
        n_of_open_sites++;
        a_open_sites.push_back(make_pair(x, y));
        sort(a_open_sites.begin(),a_open_sites.end());
    }
    bool is_open(int x,int y){
        if(a[x-1][y-1]==1){
//            cout << "Yes it is open\n";
            return true;
        }
//        cout << "No it is not open\n";
        return false;
    }
    int number_of_open_sites(){
        cout << "The grid has " << n_of_open_sites << " open sites\n";
        return n_of_open_sites;
    }
    void sort_a_open_sites(){
        sort(a_open_sites.begin(),a_open_sites.end());
    }
    bool may_percolate(){
        if(a_open_sites[0].first == 1 && a_open_sites[a_open_sites.size()-1].first == r){
            return true;
        }
        return false;
    }
    bool is_system_percolated(){
        if(a_open_sites.size()<r){
//            cout << "The Grid is not Percolated\n";
            return false;
        }
        if(may_percolate()){
            int a1r[c];
            for(int i=0;i<c;++i){
                a1r[i]=set->root(i);
            }
            int a2r[c];
            for(int i=(r*(c-1));i<(r*c);++i){
                a2r[i%c]=set->root(i);
            }
            for(int i=0;i<c;++i){
                for(int j=0;j<c;++j){
                    if(a1r[i]==a2r[j]){
//                        cout << "Percolated\n";
                        return true;
                    }
                }
            }
//            cout << "Not Percolated Yet\n";
            return false;
        }
        else{
//            cout << "The Grid is not Percolated\n";
            return false;
        }
    }
    ~percolation(){
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                a[i][j]=0;
            }
        }
        delete a;
//        cout << "The grid is Nullified and deleted\n";
    }
};
class percolationstats{
public:
    double * probability;
    int attempts;
    percolationstats(int trials,int r,int c){
        attempts=trials;
        probability = new double[trials];
        for(int i=0;i<trials;++i){
            percolation p(r,c);
            int steps_needed_to_percolate=0;
            while(!p.is_system_percolated()){
                int rx,cy;
                re_gen_rand:
                std::random_device xx;
                std::mt19937 gen(xx());
                std::uniform_int_distribution<> distr(1,r);
                rx=distr(gen);
                cy=distr(gen);
                if(p.is_open(rx,cy)){
                    continue;
                }
                p.open_site(rx,cy);
                ++steps_needed_to_percolate;
            }
            probability[i]=(1.0*steps_needed_to_percolate)/(r*c);
        }
    }
    double mean(){
        double sum_x=0.0;
        for(int i=0;i<attempts;++i){
            sum_x+=probability[i];
        }
        double mean=sum_x/attempts;
//        cout << "The mean probability is " << mean << "\n";
        return mean;
    }
    double standar_deviation(){
        double median = mean();
        double s=0.0;
        for(int i=0;i<attempts;++i){
            s+=(probability[i]-median)*(probability[i]-median);
        }
        s/=(attempts-1);
        s=sqrt(s);
//        cout << "The standard deviation is " << s << "\n";
        return s;
    }
    double confidenceLo(){
        double cnf_low = mean()-((1.96*standar_deviation())/sqrt(attempts));
        //cout << "The Low endpoint of confidence is " << cnf_low << "\n";
        return cnf_low;
    }
    double confidenceHi(){
        double cnf_hi = mean()+((1.96*standar_deviation())/sqrt(attempts));
        //cout << "The Low endpoint of confidence is " << cnf_hi << "\n";
        return cnf_hi;
    }
    void show_cnf(){
        cout << "[" << confidenceLo() << " , " << confidenceHi() << "]";
    }
};
int main() {
    int t,r;
    cout << "How many trials?\t";
    cin >> t;
    cout << "Number of Rows and collumns cause its a square grid\t";
    cin >> r;
    percolationstats app(t,r,r);
    cout << "\nMean\t" << app.mean() << "\n";
    cout << "Standard Deviation " << app.standar_deviation() << "\n";
    cout << "95% confidence interval\t";
    app.show_cnf();
    cout << "\n\nEnd of the program\n\n";
    return 0;
}
