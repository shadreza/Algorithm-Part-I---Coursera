#include<iostream>
using namespace std;
typedef long long ll;
class uf{
private:
    int nodes;
    int * a;
    int * s;
    int maxsize=0;
public:
    uf(){
        cout << "How many nodes?\t";
        cin >> nodes;
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
    void is_connected(){
        int x,y;
        printf("Whics two nodes to check connections?\t");
        cin >> x >> y;
        if(root(x-1)==root(y-1)){
            printf("YES\tNode %d and Node %d are connected\n",x,y);
        }
        else{
            printf("NO\tNode %d and Node %d are not connected\n",x,y);
        }
    }
    void connect(){
        int x,y;
        printf("Whics two nodes to bridge?\t");
        cin >> x >> y;
        if(root(x-1)==root(y-1)){
            cout << "Already Connected\n";
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
        printf("ALHAMDULILLAH bridge between Node %d and Node %d is successful\n",x,y);
    }
    void show(){
        for(int i=0;i<nodes;++i){
            printf("node(%d)_%d_size(%d)\n",i+1,a[i],s[i]);
        }
    }
    bool all_connected(){
        if(maxsize==nodes){
            return true;
        }
        return false;
    }
    int find(){
        cout << "Connected with which node?\t";
        int d,maxx=0;
        cin >> d;
        d=a[d-1];
        for(int i=0;i<nodes;++i){
            if(a[i]==d){
                maxx=max(i+1,maxx);
            }
        }
        return maxx;
    }
    void remove(){
        int x;
        cout << "WHAT IS X\t";
        cin >> x;
        int r = root(x);
        s[r-1]--;
        a[x-1]=x-1;
        for(int i=0;i<nodes;++i){
            if(a[i]==r){
                cout << i+1 << endl;
                return ;
            }
        }
    }
    bool options(){
        cout << "\nThe optins are\n\t1.Check Connections\n\t2.Make Connections\n\t3.Show Data\n\t4.Exit\n";
        int k;
        cin >> k;
        if(k==1){
            is_connected();
            return true;
        }
        else if(k==2){
            connect();
            return true;
        }
        else if(k==3){
            show();
            return true;
        }
        else{
            return false;
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    uf a;
    string s,t;
    t="no";
    int inp;
    cout << "How manu trials to connect\t";
    cin >> inp;
    while (inp--) {
        a.connect();
        cout << "The time\t";
        getchar();
        getline(cin,s);
        if(a.all_connected() && t=="no"){
            t=s;
        }
    }
    cout << a.find() << endl;
    cout << t << endl;
    return 0;
}
