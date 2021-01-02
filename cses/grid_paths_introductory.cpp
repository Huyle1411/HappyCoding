#include<iostream>
using namespace std;

int ans;
string s;
bool vis[7][7];

/*
 * The idea: prunch the search
 * stop the search if cannot go to 1 direction 
 * but can go to the 2 others side
 */
bool isValid(const int x, const int y) {
    return (x>=0 && x<7 && y>=0 && y<7 && (!vis[x][y]));
}

void dfs(const int i, const int ro, const int co) {
    /*
     * if reach the destination stop the search immediately
     * even the index is reach the of string or not
     * if reach the end of string at that moment
     * increase the result
     */
    if(ro==6 && co==0) {
        if(i==48)
            ++ans;
        return;
    }

    if ((s[i] == '?' || s[i] == 'U') && isValid(ro - 1, co)) {
        bool locked = !isValid(ro - 2, co) && isValid(ro - 1, co - 1) && isValid(ro - 1, co + 1);

        if (!locked) {
            vis[ro - 1][co] = true;
            dfs(i + 1, ro - 1, co);
            vis[ro - 1][co] = false;
        }
    }

    if ((s[i] == '?' || s[i] == 'D') && isValid(ro + 1, co)) {
        bool locked = !isValid(ro + 2, co) && isValid(ro + 1, co - 1) && isValid(ro + 1, co + 1);

        if (!locked) {
            vis[ro + 1][co] = true;
            dfs(i + 1, ro + 1, co);
            vis[ro + 1][co] = false;
        }
    }

    if ((s[i] == '?' || s[i] == 'L') && isValid(ro, co - 1)) {
        bool locked = !isValid(ro, co - 2) && isValid(ro - 1, co - 1) && isValid(ro + 1, co - 1);

        if (!locked) {
            vis[ro][co - 1] = true;
            dfs(i + 1, ro, co - 1);
            vis[ro][co - 1] = false;
        }
    }

    if ((s[i] == '?' || s[i] == 'R') && isValid(ro, co + 1)) { // R
        bool locked = !isValid(ro, co + 2) && isValid(ro - 1, co + 1) && isValid(ro + 1, co + 1);

        if (!locked) {
            vis[ro][co + 1] = true;
            dfs(i + 1, ro, co + 1);
            vis[ro][co + 1] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    vis[0][0] = true;
    dfs(0, 0, 0);
    cout << ans;
    return 0;
}
