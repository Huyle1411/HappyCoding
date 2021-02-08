#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    const int mxN = 2e5+5;
    int n;
    int64_t x, p[mxN];
    cin >> n >> x;
    for(int i=0; i<n; ++i)
        cin >> p[i];
    sort(p, p+n);
    int ans=0;
    int i=0, j=n-1;
    for(; i<j; --j) {
        if(p[j] > x)
            continue;
        if(p[i]+p[j]<=x)
            ++i;
        ++ans;
    }
    cout << ans+(i==j);
}
