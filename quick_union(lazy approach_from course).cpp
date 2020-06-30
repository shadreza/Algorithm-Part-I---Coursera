#include <bits/stdc++.h>
using namespace std;
class quick_union{
public:
    quick_union(int n){
        int * a = new int (n);
        for(int i=0;i<n;++i){
            a[i]=i;
        }
    }
    int root(int i){
        while(i!=a[i]){
            i=a[i];
        }
        return i;
    }
    bool is_connected(int x,int y){
        if(root(x-1)==root(y-1)){
            return true;
        }
        else{
            return false;
        }
    }
    void union(int x,int y){
        if(root(x-1)!=root(y-1)){
            a[x-1]=root(y-1);
        }
    }
};
int main(){
    int n;
    cout << "Number of nodes\t";
    cin >> n;
    quick_union a;

    return 0;
}