#include<iostream>
#include<cmath>
using namespace std;

/*
 * Becareful about big number in test case, should use uint64_t
 */

uint64_t total[20];
void preCalcu() {
    for(int i=1; i<19; ++i) {
        total[i] = (uint64_t)pow(10ULL,i-1)*i*9;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    preCalcu();
    while(T--) {
        uint64_t k;
        cin >> k;
        int pos=1;
        while(k>total[pos]) 
            k -= total[pos++];
        if(pos==1) {
            cout << k << '\n';
            continue;
        }
        int tmp = k%pos, ans;
        k /= pos;
        if(tmp)
            ans = k/((uint64_t)pow(10ULL, pos-tmp))%10+(tmp==1 ? 1 : 0);
        else 
            ans = (k-1)%10;
        cout << ans << '\n';
    }
}
