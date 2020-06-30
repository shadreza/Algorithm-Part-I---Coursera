#include <iostream>
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
    percolation(){
        cout << "The Row?\t";
        cin >> r;
        cout << "The Column?\t";
        cin >> c;
        set = new uf(r,c);
        cout << "Preparing the grid " << r << "x" << c << "\n";
        a = new int*[r];
        for(int i=0;i<r;++i){
            a[i] = new int[c];
        }
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                a[i][j]=0;
            }
        }
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
    void open_site(){
        cout << "The grid is " << r << "x" << c << "\nWhich Slot to open?\t";
        int x,y;
        cout << "Of which Row?\t";
        cin >> x;
        cout << "Of which Column?\t";
        cin >> y;
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
        cout << "The site is open\n";
        n_of_open_sites++;
        a_open_sites.push_back(make_pair(x, y));
        sort(a_open_sites.begin(),a_open_sites.end());
    }
    bool is_open(){
        cout << "The grid is " << r << "x" << c << "\nWhich Slot to open?\t";
        int x,y;
        cout << "Of which Row?\t";
        cin >> x;
        cout << "Of which Column?\t";
        cin >> y;
        if(a[x-1][y-1]==1){
            cout << "Yes it is open\n";
            return true;
        }
        cout << "No it is not open\n";
        return false;
    }
    bool is_full(){
        cout << "The grid is " << r << "x" << c << "\nWhich Slot to open?\t";
        int x,y;
        cout << "Of which Row?\t";
        cin >> x;
        cout << "Of which Column?\t";
        cin >> y;
        if(a[x-1][y-1]==0){
            cout << "Yes it is Blocked\n";
            return true;
        }
        cout << "No it is not Blocked\n";
        return false;
    }
    int number_of_open_sites(){
        cout << "The grid has " << n_of_open_sites << " open sites\n";
        return n_of_open_sites;
    }
    void show_open_sites(){
        cout << "The Open Sites are\n";
        for(int i=0;i<a_open_sites.size();++i){
            cout << a_open_sites[i].first << "," << a_open_sites[i].second << "\n";
        }
        set->show();
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
    void is_system_percolated(){
        if(a_open_sites.size()<r){
            cout << "The Grid is not Percolated\n";
            return ;
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
                        cout << "Percolated\n";
                        return ;
                    }
                }
            }
            cout << "Not Percolated Yet\n";
            return ;
        }
        else{
            cout << "The Grid is not Percolated\n";
            return ;
        }
    }
    bool options(){
        cout << "The options are\n\t1.Open a Site\n\t2.Check if site is open\n\t3.Check is site is closed\n\t4.Show number of open sites\n\t5.Show the open sites\n\t6.Does it Percolate?\n\t7.Exit\t";
        int k;
        cin >> k;
        if(k==1){
            open_site();
        }
        else if(k==2){
            is_open();
        }
        else if(k==3){
            is_full();
        }
        else if(k==4){
            number_of_open_sites();
        }
        else if(k==5){
            show_open_sites();
        }
        else if(k==6){
            is_system_percolated();
        }
        else{
            return false;
        }
        return true;
    }
    ~percolation(){
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                a[i][j]=0;
            }
        }
        delete a;
        cout << "The grid is Nullified and deleted\n";
    }
};
int main() {
    percolation a;
    while (a.options()){
        a.is_system_percolated();
    }
    return 0;
}
