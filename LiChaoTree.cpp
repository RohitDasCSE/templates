struct Line{
    int m, c;
 
    explicit Line(int _m=0, int _c=9e18) : m(_m), c(_c) {};
 
    int y(int x){
        return m*x + c;
    }
};
 
struct LiChaoCompressed{
    int n;
    vector<int> xs;
    vector<Line> v;
 
    explicit LiChaoCompressed(const vector<int>& _xs){
        n = _xs.size();
        xs = _xs;
        v.assign(4*n, Line());
    }
 
    void insert(int l, int r, int cur, Line& nw){
        int m = l + (r-l)/2;
        int xl = xs[l], xr = xs[r], xm = xs[m];
        if (nw.y(xm) < v[cur].y(xm)) swap(nw, v[cur]);
        if (l == r) return;
        if (nw.y(xl) < v[cur].y(xl)) insert(l, m, 2*cur+1, nw);
        else if (nw.y(xr) < v[cur].y(xr)) insert(m+1, r, 2*cur+2, nw);
    }
 
    int query(int l, int r, int cur, int pos, int q){
        int res = v[cur].y(q);
        if (l == r) return res;
        int m = l + (r-l)/2;
        if (pos <= m) return min(res, query(l, m, 2*cur+1, pos, q));
        else return min(res, query(m+1, r, 2*cur+2, pos, q));
    }
 
 
    void insert(Line nw){
        insert(0,n-1,0,nw);
    }
 
    int query(int q){
        int pos = lower_bound(xs.begin(), xs.end(), q) - xs.begin();
        if (pos == n or xs[pos] != q) return 9e18;
        return query(0,n-1,0,pos,q);
    }
};

