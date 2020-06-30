#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int a[n];
    int ar[n];
    for(int i=0;i<n;++i){
        a[i]=i;
        ar[i]=1;
    }
    for(int i=0;i<n;++i){
        cout << a[i] << " " << ar[i]  << endl;
    }
    while(1){
        cout << "\nOptions\n1.union two nodes?\n2.are two nodes connected?\t";
        int k;
        cin >> k;
        if(k==1){
            int c,b;
            cout << "the two nodes?\n";
            cin >> b >> c;
            if(a[c-1]==a[b-1]){
                cout << "Already Connected\n";
            }
            else{
                int big,small;
                if(ar[b-1]<ar[c-1]){
                    small=a[b-1];
                    big=a[c-1];
                }
                else{
                    small=a[c-1];
                    big=a[b-1];
                }
                for(int i=0;i<n;++i){
                    if(a[i]==small){
                        a[i]=big;
                        ar[small]--;
                        ar[big]++;
                    }
                }
            }
            cout << "now result\n";
            for(int i=0;i<n;++i){
                cout << a[i] << " " << ar[i]  << endl;
            }
        }
        else if(k==2){
            int c,b;
            cout << "the two nodes?\n";
            cin >> c >> b;
            if(a[c-1]==a[b-1]){
                cout << "Connected\n";
            }
            else{
                cout << "Not Connected\n";
            }
            cout << "now result\n";
            for(int i=0;i<n;++i){
                cout << a[i] << " " << ar[i]  << endl;
            }
        }
        else{
            break;
        }
    }
    cout << "end result\n";
    for(int i=0;i<n;++i){
        cout << a[i] << " " << ar[i]  << endl;
    }
    return 0;
}