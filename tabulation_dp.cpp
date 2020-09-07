#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
long long int a[1000000]={0};
long long int calculated=2;
int cal=0;
long long int fib(long long int x){
    if(a[x]==0){
        if(x==0){
            a[x]=0;
        }
        else if(x==1){
            a[x]=1;
        }
        else{
            for(long long int i=calculated;i<=x;i++){
                cal++;
                a[i]=fib(i-1)+fib(i-2);
                //a[i]=a[i-1]+a[i-2];
            }
        }
    }
    calculated=x;
    return a[x];
}
int main(){
    //a[0]=0;
    //a[1]=1;
    cout<<fib(10)<<endl;
    cout<<cal;
}
