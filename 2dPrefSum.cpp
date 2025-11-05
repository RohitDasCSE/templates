int query(const vector<vector<int>>& p){
    return p[X2][Y2] - p[X1-1][Y2] - p[X2][Y1-1] + p[X1-1][Y1-1];
}
 
// add diff 

 
void solve(){
    int n, q;
    cin >> n >> q;
 
    vector a(n+1, vector<int>(n+1)), b(n+1, vector<int>(n+1)), c(n+1, vector<int>(n+1));
    for (int i=1; i<=n; ++i){
        for (int j=1; j<=n; ++j){
            cin >> a[i][j];
            b[i][j] = b[i][j-1] + b[i-1][j] - b[i-1][j-1] + (i*a[i][j]);
            c[i][j] = c[i][j-1] + c[i-1][j] - c[i-1][j-1] + (j*a[i][j]);
            a[i][j] = a[i][j-1] + a[i-1][j] - a[i-1][j-1] + a[i][j];
        }
    }
 
    while (q--){
        cin >> X1 >> Y1 >> X2 >> Y2;
        cout << (Y2 - Y1 + 1)*query(b) + query(c) + (1 - Y1 - X1*(Y2 - Y1 + 1))*query(a) << " ";
    }
    cout << "\n";
}