#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n,m;
    const int mxN = 2e5+5;
    int64_t k, a[mxN], b[mxN];
    cin >> n >> m >> k;
    for(int i=0; i<n; ++i)
        cin >> a[i];
    for(int i=0; i<m; ++i)
        cin >> b[i];
    sort(a, a+n);
    sort(b, b+m);
    bool vis[mxN] = {0};
    int ans=0, i=0, j=0;
    while(i<n) {
        while(b[j] < a[i]-k)
            ++j;
        if(b[j] > a[i]+k) {
            if(j)
                --j;
            ++i;
            continue;
        }
        if(b[j] >= a[i]-k && b[j] <= a[i]+k) {
            if(!vis[j]) {
                ++ans;
                vis[j++]=1;
            } else {
                ++j;
                continue;
            }
        }
        ++i;
    }
    cout << ans;
}

