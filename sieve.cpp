const int N = 1e6;
vector<int> primes = {2};


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<bool> v((N-1)/2, true);
    for (int i=3; i*i<=N; i+=2){
        if (v[(i-3)/2]){
            for (int j=i*i; j<=N; j+=2*i){
                v[(j-3)/2] = false;
            }
        }
    }

    for (int i=0; i<v.size(); ++i){
        if (v[i]) primes.push_back(2*i + 3);
    }
}