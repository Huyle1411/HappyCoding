#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    const int mxN = 2e5+5;
    int n,m;
    int64_t t[mxN];
    cin >> n >> m;
    vector<int64_t> h(n);
    for(int i=0; i<n;++i)
        cin >> h[i];
    for(int i=0; i<m; ++i) 
        cin >> t[i];
    sort(h.begin(), h.end(), greater<int64_t>());
    for(int i=0; i<m; ++i) {
        auto pos = lower_bound(h.begin(), h.end(), t[i], greater<int64_t>()) - h.begin();
        if(pos==h.size())
            cout << -1 << ' ';
        else {
            cout << h[pos] << ' ';
            h.erase(h.begin() + pos);
        }
    }
}
