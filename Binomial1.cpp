const int N = 1e6;
const int M = 1e9 + 7;
 
 
int modExp(int a, int b, int m){
    int ans = 1;
    while (b){
        if (b&1) ans = (ans * a)%m;
        a = (a * a)%m;
        b >>= 1;
    }
    return ans;
}
 
 
int modInv(int a, int m){
    return modExp(a, m-2, m);
}
 
int modMul(int a, int b, int m){
    return ((a%m) * (b%m))%m;
}
 
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    vector<int> f(N+1), inv(N+1);
    f[0] = inv[0] = 1;
 
    for (int i=1; i<=N; ++i){
        f[i] = (f[i-1] * i)%M;
        inv[i] = (inv[i-1] * modInv(i,M))%M;
    }
 
    int t;
    cin >> t;
    while (t--){
        int n, r;
        cin >> n >> r;
        cout << modMul(f[n], modMul(inv[r], inv[n-r], M) ,M) << "\n";
    }
