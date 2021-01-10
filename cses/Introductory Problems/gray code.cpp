#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s(n,'0');
    vector<string> ans;
    ans.push_back(s);
    s[s.size()-1]='1';
    ans.push_back(s);
    int i=1;
    for(;i<n; ++i) {
        int sz = ans.size();
        vector<string> nxt(sz);
        for(int j=0; j<sz; ++j) {
            string tmp = ans[j];
            tmp[tmp.size()-1-i] = '1';
            nxt[sz-1-j]=tmp;
        }
        ans.insert(ans.end(), nxt.begin(), nxt.end());
    }
    for(auto it:ans)
        cout << it << '\n';
    return 0;
}
