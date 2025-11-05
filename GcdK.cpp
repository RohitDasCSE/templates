const int N = 1e6;
 
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    int n;
    cin >> n;
 
    vector<int> cnt(N + 1);
    for (int i=0; i<n; ++i){
        int x;
        cin >> x;
        cnt[x] += 1;
    }
 
    for (int i=1; i<=N; ++i){
        for (int j=2*i; j<=N; j+=i) cnt[i] += cnt[j];
    }
 
    for (int i=1; i<=N; ++i) cnt[i] = cnt[i]*(cnt[i]-1)/2;
 
    for (int i=N; i>=1; --i){
        for (int j=2*i; j<=N; j+=i) cnt[i] -= cnt[j];
    }
 
  