/**
 * 题目：双核处理
 * 简化为背包问题
 */
#include <iostream>  
using namespace std;  
int dp[210000];  
int n,arr[51];  
int main()  
{  
    int n;  
    scanf("%d",&n);  
    int sum = 0;  
    for(int i = 0 ; i < n ; i ++){  
        scanf("%d",&arr[i]);  
        arr[i] /= 1024;  
        sum += arr[i];  
    }
    memset(dp, 0, sizeof(dp));  
    //对于第i个物体，容量为j，第i个物体加入或者不加入
    //使得装的容量更加接近j
    for(int i = 0 ; i < n ; i ++)  
        for(int j = sum/2 ; j >= arr[i] ; --j)  
            dp[j] = max(dp[j],dp[j-arr[i]]+arr[i]);
    printf("%d\n",(sum-dp[sum/2])*1024);  
    return 0;  
}