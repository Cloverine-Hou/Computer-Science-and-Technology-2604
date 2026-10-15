author: xiezheyuan

线段树与离线询问结合的问题在 OI 领域也有出现．这种技巧又被称为线段树分治．

假如你需要维护一些信息，这些信息会在某一个时间段内出现，要求在离线的前提下回答某一个时刻的信息并，则可以考虑使用线段树分治的技巧．

实际上线段树分治常有以下用途：

1.  用原本不支持删除但是支持撤销的数据结构来模拟删除操作．如朴素的并查集无法高效支持删边操作．
2.  不同属性的数据分别计算．如需要求出除了某一种颜色外，其他颜色数据的答案．

如果大家现在不明白没有关系，这两种用途我们都会在例题中阐述．

## 过程

首先我们建立一个线段树来维护时刻，每一个节点维护一个 `vector` 来存储位于这一段时刻的信息．

插入一个信息到线段树中和普通线段树的区间修改是类似的．

然后我们考虑如何处理每一个时间段的信息并．考虑从根节点开始分治，维护当前的信息并，然后每到一个节点的时候将这个节点的所有信息进行合并．回溯时撤销这一部分的贡献．最后到达叶子节点时的信息并就是对应的答案．

如果更改信息的时间复杂度为 $O(T(n))$，可以通过设置一个栈保留更改，以 $O(T(n))$ 的时间复杂度撤销．撤销不维持均摊复杂度．

整个分治流程的总时间复杂度是 $O(n\log n(T(n) + M(n)))$ 的，其中 $O(M(n))$ 为合并信息的时间复杂度，空间复杂度为 $O(n\log n)$．

??? note "实现"
    ```cpp
    #define ls (i << 1)
    #define rs (i << 1 | 1)
    #define mid ((l + r) >> 1)
    
    vector<Object> tree[N << 2];  // 线段树
    
    void update(int ql, int qr, Object obj, int i, int l, int r) {  // 插入
      if (ql <= l && r <= qr) {
        tree[i].push_back(obj);
        return;
      }
      if (ql <= mid) update(ql, qr, obj, ls, l, mid);
      if (qr > mid) update(ql, qr, obj, rs, mid + 1, r);
    }
    
    stack<Object> sta;  // 用于撤销的栈
    Object now;         // 当前的信息并
    Object ans[N];      // 答案
    
    void solve(int i, int l, int r) {
      auto lvl = sta.size();  // 记录一下应当撤销到第几个
      for (Object x : tree[i]) sta.push(now), now = Merge(now, x);  // 合并信息
      if (l == r)
        ans[i] = now;  // 记录一下答案
      else
        solve(ls, l, mid), solve(rs, mid + 1, r);  // 分治
      while (sta.size() != lvl) {                  // 撤销信息
        now = sta.top();
        sta.pop();
      }
    }
    ```

## 例题

???+ note "[luogu P5787 二分图/【模板】线段树分治](https://www.luogu.com.cn/problem/P5787)"
    你需要维护一个 $n$ 个点 $m$ 条边的无向图．第 $i$ 条边为 $(x_i,y_i)$，出现的时刻为 $[l_i,r_i)$，其余时刻消失．
    
    对于每一个时刻，若此时该图为二分图，输出 `Yes`，否则输出 `No`．
    
    ??? note "解题思路"
        使用种类并查集来维护一个图是否是二分图，然后就可以套用线段树分治了．
        
        注意可撤销的并查集不能路径压缩，只能按秩合并．
    
    ??? note "参考代码"
        ```cpp
        #include <iostream>
        #include <stack>
        #include <vector>
        #define ls (i << 1)
        #define rs (i << 1 | 1)
        #define mid ((l + r) >> 1)
        using namespace std;

        int n, m, k;
        constexpr int N = 2e5 + 5;
        int fa[N << 1], siz[N << 1];

        struct UndoObject {
          int pos, val;

          UndoObject(int p, int v) { pos = p, val = v; }
        };

        stack<UndoObject> undo_sz, undo_fa;

        int find(int x) {
          if (fa[x] == x)
            return x;
          else
            return find(fa[x]);
        }

        void merge(int u, int v) {
          int x = find(u), y = find(v);
          if (x == y) return;
          if (siz[x] < siz[y]) {
            swap(x, y);
          }
          undo_sz.push(UndoObject(x, siz[x]));
          siz[x] += siz[y];
          undo_fa.push(UndoObject(y, fa[y]));
          fa[y] = x;
        }

        void undo() {
          fa[undo_fa.top().pos] = undo_fa.top().val;
          undo_fa.pop();
          siz[undo_sz.top().pos] = undo_sz.top().val;
          undo_sz.pop();
        }

        vector<int> tree[N << 2];

        void update(int ql, int qr, int v, int i, int l, int r) {
          if (ql <= l && r <= qr) {
            tree[i].push_back(v);
            return;
          }
          if (ql <= mid) update(ql, qr, v, ls, l, mid);
          if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
        }

        struct edge {
          int u, v;
        } g[N];

        vector<bool> ret;

        void solve(int i, int l, int r) {
          auto level = undo_fa.size();
          bool ans = true;
          for (int u : tree[i]) {
            int a = find(g[u].u);
            int b = find(g[u].v);
            if (a == b) {
              for (int k = l; k <= r; k++) {
                ret.push_back(false);
              }
              ans = false;
              break;
            }
            merge(g[u].u, g[u].v + n);
            merge(g[u].v, g[u].u + n);
          }
          if (ans) {
            if (l == r) {
              ret.push_back(true);
            } else {
              solve(ls, l, mid);
              solve(rs, mid + 1, r);
            }
          }
          while (undo_fa.size() > level) {
            undo();
          }
        }

        signed main() {
          cin >> n >> m >> k;
          for (int i = 1; i <= (n << 1); i++) {
            fa[i] = i;
            siz[i] = 1;
          }
          for (int i = 1, l, r; i <= m; i++) {
            cin >> g[i].u >> g[i].v >> l >> r;
            update(l + 1, r, i, 1, 1, k);
          }
          solve(1, 1, k);
          for (bool i : ret) {
            cout << (i ? "Yes" : "No") << '\n';
          }
          return 0;
        }
        ```

???+ note "颜色限制 restriction"
    一个 $n$ 点 $m$ 边的无向图，有 $k$ 种颜色编号为 $0\sim k-1$，每条边有一种颜色．
    
    对于每种颜色，请判断假如删去所有这种颜色的边，得到的图是否连通？是否是一棵树？
    
    输出满足删去后图连通的颜色数和删去后图是树的颜色数．
    
    ??? note "解题思路"
        对于每一种颜色，建立一个时间，在这个时间内没有这个颜色的边，其他边都有．用一个并查集维护一下即可．
    
    ??? note "参考代码"
        ```cpp
        #include <bitset>
        #include <iostream>
        #include <stack>
        #include <vector>
        #define ls (i << 1)
        #define rs (i << 1 | 1)
        #define mid ((l + r) >> 1)
        using namespace std;

        int n, m, k;
        constexpr int N = 1e5 + 5;

        struct edge {
          int u, v, c;
        } g[N];

        vector<int> t[N << 2];
        int fa[N], siz[N], cnt[N];

        void update(int ql, int qr, int v, int i, int l, int r) {
          if (ql > qr) return;
          if (ql <= l && r <= qr) {
            t[i].push_back(v);
            return;
          }
          if (ql <= mid) update(ql, qr, v, ls, l, mid);
          if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
        }

        stack<pair<int, int>> fas, sizs;

        int find(int x) { return fa[x] == x ? x : find(fa[x]); }

        void merge(int u, int v) {
          int fu = find(u), fv = find(v);
          if (fu == fv) return;
          if (siz[fu] < siz[fv]) swap(fu, fv);
          fas.push(make_pair(fv, fa[fv]));
          fa[fv] = fu;
          sizs.push(make_pair(fu, siz[fu]));
          siz[fu] += siz[fv];
        }

        bitset<N> ans;

        void solve(int i, int l, int r) {
          unsigned lvl = fas.size();
          for (int eg : t[i]) merge(g[eg].u, g[eg].v);
          if (l == r)
            ans[l] = (siz[find(1)] == n);
          else
            solve(ls, l, mid), solve(rs, mid + 1, r);
          while (fas.size() != lvl) {
            auto p1 = fas.top(), p2 = sizs.top();
            fas.pop(), sizs.pop();
            fa[p1.first] = p1.second;
            siz[p2.first] = p2.second;
          }
        }

        signed main() {
          ios::sync_with_stdio(false);
          cin.tie(nullptr);
          cin >> n >> m >> k;
          for (int i = 1; i <= m; i++) {
            cin >> g[i].u >> g[i].v >> g[i].c;
            g[i].c++;
            update(1, g[i].c - 1, i, 1, 1, k);
            update(g[i].c + 1, k, i, 1, 1, k);
            cnt[g[i].c]++;
          }
          for (int i = 1; i <= n; i++) {
            fa[i] = i;
            siz[i] = 1;
          }
          solve(1, 1, k);
          int ans1 = 0, ans2 = 0;
          for (int i = 1; i <= k; i++) {
            ans1 += ans[i];
            ans2 += (ans[i] && (m - cnt[i]) == (n - 1));
          }
          cout << ans1 << ' ' << ans2;
          return 0;
        }
        ```

???+ note "[luogu P4219 \[BJOI2014\] 大融合](https://www.luogu.com.cn/problem/P4219)"
    需要维护一个 $n$ 个点的森林，初始时是散点．
    
    有 $q$ 个操作，支持：
    
    -   `A x y` 连边 $(x,y)$．
    -   `Q x y` 输出经过边 $(x,y)$ 的路径数．
    
    允许离线．
    
    ??? note "解题思路"
        考虑允许离线，因此可以想到线段树分治．
        
        然后考虑如何支持 Q 操作．如果不存在 $(x,y)$ 这条边，答案就是 $x$ 所在连通块大小乘上 $y$ 所在连通块大小．可以用并查集维护．
        
        因此你可以将 Q 拆成三个时间 $k-1,k,k+1$．其中 $k-1$ 是这条边的终止时刻，$k+1$ 是这条边的起始时刻．这样 $k$ 就没有这条边，正好回答询问．
    
    ??? note "参考代码"
        ```cpp
        #include <iostream>
        #include <map>
        #include <stack>
        #include <vector>
        #define ls (i << 1)
        #define rs (i << 1 | 1)
        #define mid ((l + r) >> 1)
        using namespace std;

        int n, m;
        constexpr int N = 1e5 + 5;
        int fa[N], siz[N], tim;

        struct UndoObject {
          int pos, val;

          UndoObject(int p, int v) { pos = p, val = v; }
        };

        stack<UndoObject> undo_sz, undo_fa;

        int find(int x) {
          if (fa[x] == x)
            return x;
          else
            return find(fa[x]);
        }

        void merge(int u, int v) {
          int x = find(u), y = find(v);
          if (x == y) return;
          if (siz[x] < siz[y]) {
            swap(x, y);
          }
          undo_sz.push(UndoObject(x, siz[x]));
          siz[x] += siz[y];
          undo_fa.push(UndoObject(y, fa[y]));
          fa[y] = x;
        }

        void undo() {
          fa[undo_fa.top().pos] = undo_fa.top().val;
          undo_fa.pop();
          siz[undo_sz.top().pos] = undo_sz.top().val;
          undo_sz.pop();
        }

        vector<pair<int, int>> tree[N << 4];

        void update(int ql, int qr, pair<int, int> v, int i, int l, int r) {
          if (ql <= l && r <= qr) {
            tree[i].push_back(v);
            return;
          }
          if (ql <= mid) update(ql, qr, v, ls, l, mid);
          if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
        }

        map<pair<int, int>, int> tims;

        struct ops {
          int l, r;
          pair<int, int> v;
        } opp[N << 3];

        int opcnt;
        map<int, int> queries;
        map<int, pair<int, int>> querylr;
        int ans[N << 3];

        void solve(int i, int l, int r) {
          auto level = undo_fa.size();
          for (auto u : tree[i]) {
            merge(u.first, u.second);
          }
          if (l == r) {
            if (queries[l]) {
              int x = querylr[l].first;
              int y = querylr[l].second;
              // cout<<siz[find(x)]<<' '<<siz[find(y)]<<'\n';
              ans[l] = siz[find(x)] * siz[find(y)];
            }
          } else {
            solve(ls, l, mid);
            solve(rs, mid + 1, r);
          }
          while (undo_fa.size() > level) {
            undo();
          }
        }

        signed main() {
          ios::sync_with_stdio(false);
          cin.tie(nullptr);
          cin >> n >> m;
          for (int i = 1; i <= n; i++) {
            fa[i] = i;
            siz[i] = 1;
          }
          while (m--) {
            char op;
            int x, y;
            cin >> op >> x >> y;
            if (op == 'A') {
              tims[make_pair(x, y)] = ++tim;
            } else {
              pair<int, int> xy = make_pair(x, y);
              opp[++opcnt] = {tims[xy], (++tim), xy};
              queries[++tim] = 1;
              // cout<<tim<<'\n';
              querylr[tim] = xy;
              tims[xy] = ++tim;
            }
          }
          int tm = ++tim;
          for (auto i : tims) {
            opp[++opcnt] = {tims[i.first], tm, i.first};
          }
          for (int i = 1; i <= opcnt; i++) {
            // cout<<opp[i].l<<' '<<opp[i].r<<' '<<opp[i].v.first<<'
            // '<<opp[i].v.second<<'\n';
            update(opp[i].l, opp[i].r, opp[i].v, 1, 1, tim);
          }
          // cout<<tim<<'\n';
          solve(1, 1, tim);
          for (int i = 1; i <= tim; i++) {
            if (queries[i]) {
              cout << ans[i] << "\n";
            }
          }
          return 0;
        }
        ```

???+ note "[luogu P2056 \[ZJOI2007\] 捉迷藏](https://www.luogu.com.cn/problem/P2056)"
    出一个 $n$ 个点的树，每个点有黑白两种颜色．初始时每个点都是黑色的．$q$ 次操作，支持：
    
    -   `C x` 将第 $x$ 个点的颜色反转．
    -   `G` 询问树上两个黑色点的最远距离．特别地，若不存在黑色点，输出 $-1$．
    
    允许离线．
    
    ??? note "解题思路"
        首先考虑如何维护树上点集的直径，有下面的推论：
        
        > 对于一个集合 $S$ 和只有一个点的集合 $\{P\}$．若集合 $S$ 的直径为 $(U,V)$．则点集 $S\cap\{P\}$ 的直径只可能为 $(U,V),(U,P)$ 或 $(V,P)$．
        
        然后考虑解决原问题．我们可以考虑维护黑色点集，维护每一个点在黑色点集中的若干个时间段（具体你开一个桶记录一下上一次进入黑色点集的时刻即可）．
        
        然后就自然地想到离线，将所有时间刻插入到线段树中．然后在线段树上分治，每次线段树上的点会记录当前时间段点集新增的点，新增点可以使用上面的推论，找到新点集直径的两个端点．
        
        撤销是平凡的，开一个栈记录一下直径端点的变化即可．
    
    ??? note "参考代码"
        ```cpp
        #include <algorithm>
        #include <bitset>
        #include <iostream>
        #include <stack>
        #include <vector>
        #define ls (i << 1)
        #define rs (i << 1 | 1)
        #define mid ((l + r) >> 1)
        using namespace std;

        constexpr int N = 5e5 + 5, M = 5e5 + 5;

        int siz[N], dep[N], father[N], top[N], son[N];
        int n, q;

        struct edge {
          int nxt, to;
        } g[N << 1];

        int head[N], ec;

        void add(int u, int v) {
          g[++ec].nxt = head[u];
          g[ec].to = v;
          head[u] = ec;
        }

        void dfs1(int u, int fa) {
          dep[u] = dep[fa] + 1;
          siz[u] = 1;
          father[u] = fa;
          for (int i = head[u]; i; i = g[i].nxt) {
            int v = g[i].to;
            if (v == fa) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[son[u]] < siz[v]) son[u] = v;
          }
        }

        void dfs2(int u, int fa) {
          if (son[u]) {
            top[son[u]] = top[u];
            dfs2(son[u], u);
          }
          for (int i = head[u]; i; i = g[i].nxt) {
            int v = g[i].to;
            if (v == fa || v == son[u]) continue;
            top[v] = v;
            dfs2(v, u);
          }
        }

        int lca(int x, int y) {
          while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = father[top[x]];
          }
          return dep[x] < dep[y] ? x : y;
        }

        int dis(int x, int y) { return dep[x] + dep[y] - (dep[lca(x, y)] << 1); }

        vector<int> t[N << 2];

        void update(int ql, int qr, int v, int i, int l, int r) {
          if (ql <= l && r <= qr) {
            t[i].push_back(v);
            return;
          }
          if (ql <= mid) update(ql, qr, v, ls, l, mid);
          if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
        }

        stack<pair<int, int>> stk;
        int u, v;
        int ans[M];

        void solve(int i, int l, int r) {
          auto lvl = stk.size();
          for (int x : t[i]) {
            stk.push(make_pair(u, v));
            if (!u && !v)
              u = x, v = x;
            else {
              vector<int> vct = {dis(u, v), dis(u, x), dis(v, x)};
              sort(vct.begin(), vct.end(), greater<int>());
              if (vct[0] == dis(u, x))
                v = x;
              else if (vct[0] == dis(x, v))
                u = x;
            }
          }
          if (l == r)
            ans[l] = (!u || !v) ? -1 : dis(u, v);
          else
            solve(ls, l, mid), solve(rs, mid + 1, r);
          while (stk.size() != lvl) {
            auto top = stk.top();
            u = top.first, v = top.second;
            stk.pop();
          }
        }

        int lst[N];
        bitset<N> col;
        bitset<M> haveq;

        signed main() {
          ios::sync_with_stdio(false);
          cin.tie(nullptr);
          cin >> n;
          for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v);
            add(v, u);
          }
          top[1] = 1;
          dfs1(1, 0);
          dfs2(1, 0);
          for (int i = 1; i <= n; i++) lst[i] = 1;
          cin >> q;
          for (int i = 2; i <= (q + 1); i++) {
            char c;
            int x;
            cin >> c;
            if (c == 'C') {
              cin >> x;
              if (!col[x]) {
                col[x] = 1;
                update(lst[x], i, x, 1, 1, q + 2);
              } else
                col[x] = 0, lst[x] = i;
            } else
              haveq[i] = 1;
          }
          for (int i = 1; i <= n; i++) {
            if (!col[i]) update(lst[i], q + 2, i, 1, 1, q + 2);
          }
          solve(1, 1, q + 2);
          for (int i = 1; i <= (q + 2); i++) {
            if (haveq[i]) cout << ans[i] << '\n';
          }
          return 0;
        }
        ```

## 习题

-   [CF601E A Museum Robbery](https://codeforces.com/problemset/problem/601/E) 线段树分治 + 背包 dp．
-   [CF19E Fairy](https://codeforces.com/problemset/problem/19/E) 线段树分治 + 种类并查集．
-   [luogu P5227 \[AHOI2013\] 连通图](https://www.luogu.com.cn/problem/P5227) 线段树分治 + 并查集．
-   [luogu P4319 变化的道路](https://www.luogu.com.cn/problem/P4319) 线段树分治 + Link Cut Tree 维护最小生成树．
-   [luogu P3733 \[HAOI2017\] 八纵八横](https://www.luogu.com.cn/problem/P3733) 线段树分治 + 线性基．

**本页面部分内容参考自博文 [Deleting from a data structure](https://cp-algorithms.com/data_structures/deleting_in_log_n.html)，版权协议为 CC-BY-SA 4.0．**
