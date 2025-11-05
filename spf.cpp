#include <iostream>
#include <vector>
using namespace std;
#define int long long
 
 
const int n = 1e6;
vector<int> spf(n+1);
 
 
void solve() {
    int m;
    cin >> m;
 
    int ans = 1;
    while (m > 1) {
        int p = spf[m], cnt = 0;
        while (m%p == 0) {
            m /= p;
            cnt += 1;
        }
        ans *= (cnt + 1);
    }
 
    cout << ans << "\n";
}
 
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    for (int i=2; i<=n; ++i) spf[i] = i;
 
    for (int i=2; i*i<=n; ++i) {
        if (spf[i] == i) {
            for (int j=i*i; j<=n; j+=i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
