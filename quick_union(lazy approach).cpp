#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;++i){
        a[i]=i;
    }
    while(1){
        cout << "\nOptions\n1.union two nodes?\n2.are two nodes connected?\t";
        int k;
        cin >> k;
        if(k==1){
            int b,c,f,t;
            cout << "two nodes\t";
            cin >> b >> c;
            while(1){
                if(a[b-1]==b-1){
                    f=a[c-1];
                    t=a[c-1]=b-1;
                    break;
                }
                else if(a[c-1]==c-1){
                    f=a[b-1];
                    t=a[b-1]=c-1;
                    break;
                }
                else{
                    b=a[b-1]+1;
                    c=a[c-1]+1;
                }
            }
            for(int i=0;i<n;++i){
                if(a[i]==t){
                    a[i]=f;
                }
            }
        }
        else if(k==2){
            int b,c;
            cout << "two nodes\t";
            cin >> b >> c;
            while(1){
                if(a[b-1]!=b-1){
                    b=a[b-1]+1;
                }
                if(a[c-1]!=c-1){
                    c=a[c-1]+1;
                }
            }
            if(a[b-1]==a[c-1]){
                cout << "Connected\n";
            }
            else{
                cout << "Not Connected\n";
            }
        }
        else{
            break;
        }
        for(int i=0;i<n;++i){
            cout << a[i] << " ";
        }
    }
    for(int i=0;i<n;++i){
        cout << a[i] << " ";
    }
    return 0;
}