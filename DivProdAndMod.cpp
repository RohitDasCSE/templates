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
 
int modAdd(int a, int b, int m){
    return ((a%m) + (b%m))%m;
}
 
int modMul(int a, int b, int m){
    return ((a%m) * (b%m))%m;
}
 
int modSub(int a, int b, int m){
    return ((a%m) - (b%m) + m)%m;
}
 
int modDiv(int a, int b, int m){
    return modMul(a, modInv(b,m), m);
}
 
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    int n;
    cin >> n;
    vector<int> X(n), K(n);
    for (int i=0; i<n; ++i) cin >> X[i] >> K[i];
 
    int sum = 1;
    for (int i=0; i<n; ++i){
        int num = modSub(modExp(X[i], K[i]+1, M), 1, M);
        int deno = modSub(X[i], 1, M);
        sum = (sum * modDiv(num, deno, M))%M;
    }
 
    int pro = 1, cntM = 1, cntM_1 = 1;
    for (int i=0; i<n; ++i){
        int a = modExp(pro, K[i]+1, M);
 
        int exp = cntM_1;
        if (K[i]&1){
            exp = modMul(exp, K[i], M-1);
            exp = modMul(exp, (K[i]+1)/2, M-1);
        }
        else{
            exp = modMul(exp, K[i]/2, M-1);
            exp = modMul(exp, K[i]+1, M-1);
        }
        int b = modExp(X[i], exp, M);
 
        pro = modMul(a, b, M);
        cntM = modMul(cntM, K[i]+1, M);
        cntM_1 = modMul(cntM_1, K[i]+1, M-1);
    }
 
    cout << cntM << " " << sum << " " << pro;
