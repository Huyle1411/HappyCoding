#include<iostream>
#include<vector>

using namespace std;

vector<pair<int,int>> ans;
void solve(int n, int source=1, int dest=3) {
    if(n==1) {
        ans.push_back({source, dest});
        return;
    }
    int middle = source^dest;
    solve(n-1, source, middle);
    ans.push_back({source, dest});
    solve(n-1, middle, dest);
}

int main() {
    int n;
    cin >> n;
    solve(n);
    cout << ans.size() << '\n';
    for(auto it:ans)
        cout << it.first << ' ' << it.second << '\n';

    return 0;
}
