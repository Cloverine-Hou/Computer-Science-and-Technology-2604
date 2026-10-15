author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc

线段树的合并与分裂是线段树的常用技巧，常见于权值线段树维护可重集的场景．

例如，树上某些结点处有若干操作，如果需要自下而上地将子节点信息传递给亲节点，而单个结点处的信息又方便用线段树维护时，就可以应用线段树合并的技巧控制整体的复杂度．

## 线段树合并

### 过程

顾名思义，线段树合并是指建立一棵新的线段树，这棵线段树的每个节点都是两棵原线段树对应节点合并后的结果．它常常被用于维护树上或是图上的信息．

显然，我们不可能真的每次建满一棵新的线段树，因此我们需要使用上文的动态开点线段树．

线段树合并的过程本质上相当暴力：

假设两棵线段树为 A 和 B，我们从 1 号节点开始递归合并．

递归到某个节点时，如果 A 树或者 B 树上的对应节点为空，直接返回另一个树上对应节点，这里运用了动态开点线段树的特性．

如果递归到叶子节点，我们合并两棵树上的对应节点．

最后，根据子节点更新当前节点并且返回．

???+ note "线段树合并的复杂度"
    显然，对于两棵满的线段树，单次合并操作的复杂度是 $O(n)$ 的．但实际情况下使用的常常是权值线段树，所有需要合并的线段树的总点数和 $n$ 的规模相差并不大．并且合并时一般不会重复地合并某个线段树，所以我们最终增加的点数大致是 $n\log n$ 级别的．这样，合并所有线段树总的复杂度就是 $O(n\log n)$ 级别的．当然，在一些情况下，可并堆可能是更好的选择．

### 实现

```cpp
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    // do something...
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}
```

### 例题

???+ note "[luogu P4556 \[Vani 有约会\] 雨天的尾巴/【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)"
    ??? note "解题思路"
        线段树合并模板题，用差分把树上修改转化为单点修改，然后向上 dfs 线段树合并统计答案即可．
    
    ??? note "参考代码"
        ```cpp
        #include <iostream>
        #include <vector>
        using namespace std;
        int n, fa[100005][22], dep[100005], rt[100005];
        int sum[5000005], cnt = 0, res[5000005], ls[5000005], rs[5000005];
        int m, ans[100005];
        vector<int> v[100005];

        void update(int x) {
          if (sum[ls[x]] < sum[rs[x]]) {
            res[x] = res[rs[x]];
            sum[x] = sum[rs[x]];
          } else {
            res[x] = res[ls[x]];
            sum[x] = sum[ls[x]];
          }
        }

        int merge(int a, int b, int x, int y) {
          if (!a) return b;
          if (!b) return a;
          if (x == y) {
            sum[a] += sum[b];
            return a;
          }
          int mid = (x + y) >> 1;
          ls[a] = merge(ls[a], ls[b], x, mid);
          rs[a] = merge(rs[a], rs[b], mid + 1, y);
          update(a);
          return a;
        }

        int add(int id, int x, int y, int co, int val) {
          if (!id) id = ++cnt;
          if (x == y) {
            sum[id] += val;
            res[id] = co;
            return id;
          }
          int mid = (x + y) >> 1;
          if (co <= mid)
            ls[id] = add(ls[id], x, mid, co, val);
          else
            rs[id] = add(rs[id], mid + 1, y, co, val);
          update(id);
          return id;
        }

        void initlca(int x) {
          for (int i = 0; i <= 20; i++) fa[x][i + 1] = fa[fa[x][i]][i];
          for (int i : v[x]) {
            if (i == fa[x][0]) continue;
            dep[i] = dep[x] + 1;
            fa[i][0] = x;
            initlca(i);
          }
        }

        int lca(int x, int y) {
          if (dep[x] < dep[y]) swap(x, y);
          for (int d = dep[x] - dep[y], i = 0; d; d >>= 1, i++)
            if (d & 1) x = fa[x][i];
          if (x == y) return x;
          for (int i = 20; i >= 0; i--)
            if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
          return fa[x][0];
        }

        void cacl(int x) {
          for (int i : v[x]) {
            if (i == fa[x][0]) continue;
            cacl(i);
            rt[x] = merge(rt[x], rt[i], 1, 100000);
          }
          ans[x] = res[rt[x]];
          if (sum[rt[x]] == 0) ans[x] = 0;
        }

        int main() {
          ios::sync_with_stdio(false);
          cin >> n >> m;
          for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
          }
          initlca(1);
          for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            rt[a] = add(rt[a], 1, 100000, c, 1);
            rt[b] = add(rt[b], 1, 100000, c, 1);
            int t = lca(a, b);
            rt[t] = add(rt[t], 1, 100000, c, -1);
            rt[fa[t][0]] = add(rt[fa[t][0]], 1, 100000, c, -1);
          }
          cacl(1);
          for (int i = 1; i <= n; i++) cout << ans[i] << endl;
          return 0;
        }
        ```

## 线段树分裂

### 过程

线段树分裂实质上是线段树合并的逆过程．线段树分裂只适用于有序的序列，无序的序列是没有意义的，常用在动态开点的权值线段树．

注意当分裂和合并都存在时，我们在合并的时候必须回收节点，以避免分裂时会可能出现节点重复占用的问题．

从一棵区间为 $[1,N]$ 的线段树中分裂出 $[l,r]$，建一棵新的树：

从 1 号结点开始递归分裂，当节点不存在或者代表的区间 $[s,t]$ 与 $[l,r]$ 没有交集时直接回溯．

当 $[s,t]$ 与 $[l,r]$ 有交集时需要开一个新结点．

当 $[s,t]$ 包含于 $[l,r]$ 时，需要将当前结点直接接到新的树下面，并把旧边断开．

???+ note "线段树分裂的复杂度"
    可以发现被断开的边最多只会有 $\log n$ 条，所以最终每次分裂的时间复杂度就是 $O(\log⁡ n)$，相当于区间查询的复杂度．

### 实现

```cpp
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
}
```

### 例题

???+ note "[P5494【模板】线段树分裂](https://www.luogu.com.cn/problem/P5494)"
    ??? note "解题思路"
        线段树分裂模板题，将 $[x,y]$ 分裂出来．
        
        -   将 $t$ 树合并入 $p$ 树：单次合并即可．
        
        -   $p$ 树中插入 $x$ 个 $q$：单点修改．
        
        -   查询 $[x,y]$ 中数的个数：区间求和．
        
        -   查询第 $k$ 小．
    
    ??? note "参考代码"
        ```cpp
        #include <iostream>
        using namespace std;
        constexpr int N = 2e5 + 10;
        int n, m;
        int idx = 1;
        long long sum[N << 5];
        int ls[N << 5], rs[N << 5], root[N << 2], rub[N << 5], cnt, tot;

        // 内存分配与回收
        int New() { return cnt ? rub[cnt--] : ++tot; }

        void Del(int &p) {
          ls[p] = rs[p] = sum[p] = 0;
          rub[++cnt] = p;
          p = 0;
        }

        void push_up(int p) { sum[p] = sum[ls[p]] + sum[rs[p]]; }

        void build(int s, int t, int &p) {
          if (!p) p = New();
          if (s == t) {
            cin >> sum[p];
            return;
          }
          int m = (s + t) >> 1;
          build(s, m, ls[p]);
          build(m + 1, t, rs[p]);
          push_up(p);
        }

        // 单点修改
        void update(int x, int c, int s, int t, int &p) {
          if (!p) p = New();
          if (s == t) {
            sum[p] += c;
            return;
          }
          int m = (s + t) >> 1;
          if (x <= m)
            update(x, c, s, m, ls[p]);
          else
            update(x, c, m + 1, t, rs[p]);
          push_up(p);
        }

        // 合并
        int merge(int p, int q, int s, int t) {
          if (!p || !q) return p + q;
          if (s == t) {
            sum[p] += sum[q];
            Del(q);
            return p;
          }
          int m = (s + t) >> 1;
          ls[p] = merge(ls[p], ls[q], s, m);
          rs[p] = merge(rs[p], rs[q], m + 1, t);
          push_up(p);
          Del(q);
          return p;
        }

        // 分裂
        void split(int &p, int &q, int s, int t, int l, int r) {
          if (t < l || r < s) return;
          if (!p) return;
          if (l <= s && t <= r) {
            q = p;
            p = 0;
            return;
          }
          if (!q) q = New();
          int m = (s + t) >> 1;
          if (l <= m) split(ls[p], ls[q], s, m, l, r);
          if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
          push_up(p);
          push_up(q);
        }

        long long query(int l, int r, int s, int t, int p) {
          if (!p) return 0;
          if (l <= s && t <= r) return sum[p];
          int m = (s + t) >> 1;
          long long ans = 0;
          if (l <= m) ans += query(l, r, s, m, ls[p]);
          if (m < r) ans += query(l, r, m + 1, t, rs[p]);
          return ans;
        }

        int kth(int s, int t, int k, int p) {
          if (s == t) return s;
          int m = (s + t) >> 1;
          long long left = sum[ls[p]];
          if (k <= left)
            return kth(s, m, k, ls[p]);
          else
            return kth(m + 1, t, k - left, rs[p]);
        }

        int main() {
          cin >> n >> m;
          build(1, n, root[1]);
          while (m--) {
            int op;
            cin >> op;
            if (!op) {
              int p, x, y;
              cin >> p >> x >> y;
              split(root[p], root[++idx], 1, n, x, y);
            } else if (op == 1) {
              int p, t;
              cin >> p >> t;
              root[p] = merge(root[p], root[t], 1, n);
            } else if (op == 2) {
              int p, x, q;
              cin >> p >> x >> q;
              update(q, x, 1, n, root[p]);
            } else if (op == 3) {
              int p, x, y;
              cin >> p >> x >> y;
              cout << query(x, y, 1, n, root[p]) << endl;
            } else {
              int p, k;
              cin >> p >> k;
              if (sum[root[p]] < k)
                cout << -1 << endl;
              else
                cout << kth(1, n, k, root[p]) << endl;
            }
          }
        }
        ```

## 习题

-   [Luogu P4556 \[Vani 有约会\] 雨天的尾巴/【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)
-   [Luogu P5494【模板】线段树分裂](https://www.luogu.com.cn/problem/P5494)
-   [Luogu P1600 天天爱跑步](https://www.luogu.com.cn/problem/P1600)
-   [Luogu P4577 \[FJOI2018\] 领导集团问题](https://www.luogu.com.cn/problem/P4577)
-   [Luogu P2824 \[HEOI2016/TJOI2016\] 排序](https://www.luogu.com.cn/problem/P2824)
