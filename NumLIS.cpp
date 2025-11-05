struct Node{
    int len;
    int cnt;
};

struct segtree{
    int n;
    vector<Node> st;

    explicit segtree(int _n) : n(_n){
        st.assign(4*n, {0,0});
    }

    Node merge(const Node& a, const Node& b){
        if (a.len > b.len) return a;
        if (a.len < b.len) return b;
        return {a.len, a.cnt+b.cnt};
    }

    Node query(int l, int r, int start, int end, int cur){
        if (start > r or end < l) return {0,0};
        if (start >= l and end <= r) return st[cur];

        int mid = start + (end-start)/2;
        return merge(query(l,r,start,mid,2*cur+1), query(l,r,mid+1,end,2*cur+2));
    }

    void update(int idx, Node v, int start, int end, int cur){
        if (start == end){
            if (v.len > st[cur].len) st[cur] = v;
            else if (v.len == st[cur].len) st[cur].cnt += v.cnt;
            return;
        }

        int mid = start + (end-start)/2;
        if (idx <= mid) update(idx, v, start, mid, 2*cur+1);
        else update(idx, v, mid+1, end, 2*cur+2);
        st[cur] = merge(st[2*cur+1], st[2*cur+2]);
    }

    Node query(int l, int r){
        return query(l, r, 0, n-1, 0);
    }

    void update(int idx, Node v){
        update(idx, v, 0, n-1, 0);
    }
};


class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> copy;
        for (auto x : nums) copy.push_back(x);

        sort(copy.begin(), copy.end());
        copy.erase(unique(copy.begin(), copy.end()), copy.end());
        int m = copy.size();
        for (auto &x : nums){
            x = lower_bound(copy.begin(), copy.end(), x) - copy.begin();
        }

        segtree st(m);

        int bestLen = 0, bestCnt = 0;
        
        for (int x : nums){
            Node q = st.query(0,x-1);
            int curLen = q.len+1, curCnt = (q.cnt ? q.cnt : 1);

            st.update(x, {curLen,curCnt});

            if (curLen > bestLen){
                bestLen = curLen;
                bestCnt = curCnt;
            }

            else if (curLen == bestLen) bestCnt += curCnt;
        }

        return bestCnt;
    }
};