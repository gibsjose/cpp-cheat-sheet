#include <bits/stdc++.h>

using namespace std;



int minTrials(int n, int k)
{
    int dp[n+1][k+1], res;
    int i,j,x;

    for (i = 1; i <= n; i++)
    {
        dp[i][1] = 1;
        dp[i][0] = 0;
    }

    for (j = 1; j <= k; j++)
        dp[1][j] = j;


    for (i = 2; i <= n; i++)
    {
        for (j = 2; j <= k; j++)
        {
            dp[i][j] = INT_MAX;
            for (x = 1; x <= j; x++)
            {
                res = 1 + max(dp[i-1][x-1], dp[i][j-x]);
                if (res < dp[i][j])
                    dp[i][j] = res;
            }
        }
    }

    return dp[n][k];

}
int main()
{

    int t,n,k;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        cout<<minTrials(n,k)<<endl;
    }
}
