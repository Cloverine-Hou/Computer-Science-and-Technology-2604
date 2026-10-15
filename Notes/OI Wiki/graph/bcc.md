## 简介

在阅读下列内容之前，请务必了解 [图论相关概念](./concept.md) 部分．

相关阅读：[割点和桥](./cut.md)

## 定义

割点和桥更严谨的定义参见 [图论相关概念](./concept.md)．

在一张连通的无向图中，对于两个点 $u$ 和 $v$，如果无论删去哪条边（只能删去一条）都不能使它们不连通，我们就说 $u$ 和 $v$  **边双连通**．

在一张连通的无向图中，对于两个点 $u$ 和 $v$，如果无论删去哪个点（只能删去一个，且不能删 $u$ 和 $v$ 自己）都不能使它们不连通，我们就说 $u$ 和 $v$  **点双连通**．

边双连通具有传递性，即，若 $x,y$ 边双连通，$y,z$ 边双连通，则 $x,z$ 边双连通．

点双连通 **不** 具有传递性，反例如下图，$A,B$ 点双连通，$B,C$ 点双连通，而 $A,C$  **不** 点双连通．

![bcc-counterexample.png](./images/bcc-0.svg)

对于一个无向图中的 **极大** 边双连通的子图，我们称这个子图为一个 **边双连通分量**．

对于一个无向图中的 **极大** 点双连通的子图，我们称这个子图为一个 **点双连通分量**．

## DFS 生成树

对于一张连通的无向图，我们可以从任意一点开始 DFS，得到原图的一棵 DFS 生成树（以开始 DFS 的那个点为根），这棵生成树上的边称作 **树边**，不在生成树上的边称作 **非树边**．

由于 DFS 的性质，我们可以保证所有非树边连接的两个点在生成树上都满足其中一个是另一个的祖先．

DFS 的代码如下：

???+ note "实现"
    === "C++"
        ```cpp
        void DFS(int p) {
          visited[p] = true;
          for (int to : edge[p])
            if (!visited[to]) DFS(to);
        }
        ```
    
    === "Python"
        ```python
        def DFS(p):
            visited[p] = True
            for to in edge[p]:
                if visited[to] == False:
                    DFS(to)
        ```

## 边双连通分量

???+ note "[例题：洛谷 P8436【模版】边双连通分量](https://www.luogu.com.cn/problem/P8436)"
    对于一个 $n$ 个节点 $m$ 条无向边的图，请输出其边双连通分量的个数，并且输出每个边双连通分量．

### Tarjan 算法 1

用 Tarjan 求双连通分量过程与求强连通分量类似，可以先阅读 [强连通分量](./scc.md) 的 Tarjan 算法．

我们考虑先求出所有的桥，再 DFS 求出边双连通分量．

求桥可参见 [割点和桥](./cut.md) 的桥部分．

时间复杂度 $O(n+m)$．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>

    using namespace std;
    constexpr int N = 5e5 + 5, M = 2e6 + 5;
    int n, m, ans;
    int tot = 1, hd[N];

    struct edge {
      int to, nt;
    } e[M << 1];

    void add(int u, int v) { e[++tot].to = v, e[tot].nt = hd[u], hd[u] = tot; }

    void uadd(int u, int v) { add(u, v), add(v, u); }

    bool bz[M << 1];
    int bcc_cnt, dfn[N], low[N], vis_bcc[N];
    vector<vector<int>> bcc;

    void tarjan(int x, int in) {
      dfn[x] = low[x] = ++bcc_cnt;
      for (int i = hd[x]; i; i = e[i].nt) {
        int v = e[i].to;
        if (dfn[v] == 0) {
          tarjan(v, i);
          if (dfn[x] < low[v]) bz[i] = bz[i ^ 1] = true;
          low[x] = min(low[x], low[v]);
        } else if (i != (in ^ 1))
          low[x] = min(low[x], dfn[v]);
      }
    }

    void dfs(int x, int id) {
      vis_bcc[x] = id, bcc[id - 1].push_back(x);
      for (int i = hd[x]; i; i = e[i].nt) {
        int v = e[i].to;
        if (vis_bcc[v] || bz[i]) continue;
        dfs(v, id);
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      int u, v;
      for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        if (u == v) continue;
        uadd(u, v);
      }
      for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i, 0);
      for (int i = 1; i <= n; i++)
        if (vis_bcc[i] == 0) {
          bcc.push_back(vector<int>());
          dfs(i, ++ans);
        }
      cout << ans << '\n';
      for (int i = 0; i < ans; i++) {
        cout << bcc[i].size();
        for (int j = 0; j < bcc[i].size(); j++) cout << ' ' << bcc[i][j];
        cout << '\n';
      }
      return 0;
    }
    ```

### Tarjan 算法 2

我们先总结出一个重要的性质，在无向图中，DFS 生成树上的边不是树边就只有非树边．

我们联系一下求强连通分量的方法，在无向图中只要一个分量没有桥，那么在 DFS 生成树上，它的所有点都在同一个强连通分量中．

反过来，在 DFS 生成树上的一个强连通分量，在原无向图中是边双连通分量．

可以发现，求边双连通分量的过程实际上就是求强连通分量的过程．

时间复杂度 $O(n+m)$．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <stack>
    #include <vector>

    using namespace std;
    constexpr int N = 5e5 + 5, M = 2e6 + 5;
    int n, m;

    struct edge {
      int to, nt;
    } e[M << 2];

    int hd[N << 1], tot = 1;

    void add(int u, int v) { e[++tot] = edge{v, hd[u]}, hd[u] = tot; }

    void uadd(int u, int v) { add(u, v), add(v, u); }

    int bcc_cnt, sum;
    int dfn[N], low[N];
    bool vis[N];
    vector<vector<int>> ans;
    stack<int> st;

    void tarjan(int u, int in) {
      low[u] = dfn[u] = ++bcc_cnt;
      st.push(u), vis[u] = true;
      for (int i = hd[u]; i; i = e[i].nt) {
        int v = e[i].to;
        if (i == (in ^ 1)) continue;
        if (!dfn[v])
          tarjan(v, i), low[u] = min(low[u], low[v]);
        else if (vis[v])
          low[u] = min(low[u], dfn[v]);
      }
      if (dfn[u] == low[u]) {
        vector<int> t;
        t.push_back(u);
        while (st.top() != u)
          t.push_back(st.top()), vis[st.top()] = false, st.pop();
        st.pop(), ans.push_back(t);
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      int u, v;
      for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        if (u != v) uadd(u, v);
      }
      for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
      cout << ans.size() << '\n';
      for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].size() << ' ';
        for (int j = 0; j < ans[i].size(); j++) cout << ans[i][j] << ' ';
        cout << '\n';
      }
      return 0;
    }
    ```

### 差分算法

和 Tarjan 算法 1 类似，我们先求出所有的桥，再差分求出边双连通分量．

首先，对原图进行 DFS．

![bcc-1.png](./images/bcc-1.svg)

如上图所示，黑色与绿色边为树边，红色边为非树边．每一条非树边的两个端点都唯一对应了树上的一条由树边构成的简单路径，我们说这条非树边 **覆盖** 了这条简单路径上所有的边．

在图中，绿色的树边 **至少** 被一条非树边覆盖，黑色的树边不被 **任何** 非树边覆盖．

显然，**非树边** 和 **绿色的树边** 一定不是桥，**黑色的树边** 一定是桥．

首先考虑一个暴力的做法，对于每一条非树边，都逐个地将它覆盖的每一条树边置成绿色，时间复杂度为 $O(nm)$．

考虑用差分优化．对于每一条非树边，在其树上深度较小的端点处打上 `-1` 标记，在其树上深度较大的端点处打上 `+1` 标记，然后 $O(n)$ 求出每个点的子树内部的标记和．

对于一个点 $u$，其子树内部的标记之和等于覆盖了 $u$ 和 $fa_u$ 之间的树边的非树边数量．若这个值等于 $0$，则 $u$ 和 $fa_u$ 之间的树边是 **桥**．

再用 DFS 求出边双连通分量．

时间复杂度 $O(n+m)$．

??? note "示例代码"
    ```cpp
    #include <cstring>
    #include <iostream>
    #include <vector>
    using namespace std;
    #define min(x, y) (x < y ? x : y)
    #define max(x, y) (x > y ? x : y)
    constexpr int N = 5e5 + 5, M = 2e6 + 5;
    int n, m;

    struct edge {
      int to, nt;
    } e[M << 1];

    int hd[N], tot;

    void add(int u, int v) { e[++tot] = {v, hd[u]}, hd[u] = tot; }

    void uadd(int u, int v) { add(u, v), add(v, u); }  // 链式前向星

    using ll = long long;
    #define P(x, y) ((ll)min(x, y) * N + (ll)max(x, y))
    constexpr int hmod = 1e5 + 7;

    struct hash {
      vector<ll> v1[hmod];
      vector<short> v2[hmod];

      short &operator[](ll x) {
        int y = x % hmod;
        for (int i = 0; i < v1[y].size(); i++)
          if (v1[y][i] == x) return v2[y][i];
        v1[y].push_back(x), v2[y].push_back(0);
        return v2[y].back();
      }
    } re, be;  // 用 vector 实现 hash 表，因为本题时空限制均比较紧

    // re 判断是否有重边，be 记录边是不是桥

    // #define P(x, y) {min(x, y), max(x, y)}
    // using pii = pair<int, int>;
    // map<pii, int> re, be; // 不紧时可以用 map 实现 hash 表

    int dep[N], bz[N], sum[N];  // 记录深度、差分值、子树查分和
    int vis[N], fa[N];          // 记录是否访问过，分组编号

    void dfs(int x, int pre) {  // 计算每个点的深度和单点查分
      if (dep[x] < dep[pre]) bz[x]++, bz[pre]--;  // 回到祖先，更改差分值
      if (dep[x]) return;
      dep[x] = dep[pre] + 1;
      for (int i = hd[x]; i; i = e[i].nt) dfs(e[i].to, x);
    }

    int dfs2(int x, int pre) {  // 处理子树查分
      if (vis[x] == 1) return sum[x];
      vis[x] = 1, sum[x] = bz[x];
      for (int i = hd[x]; i; i = e[i].nt) {
        int v = e[i].to;
        if (dep[v] > dep[x] && !vis[v]) sum[x] += dfs2(v, x);
      }
      if (sum[x] == 0 && re[P(x, pre)] == 1) be[P(x, pre)] = 1;  // 记录桥
      return sum[x];
    }

    int cnt;
    vector<int> ans[N];

    void dfs3(int x) {  // 计算双连通分量
      if (fa[x]) return;
      ans[cnt].push_back(x), fa[x] = cnt;
      for (int i = hd[x]; i; i = e[i].nt) {
        int v = e[i].to;
        if (be[P(x, v)] != 1) dfs3(v);  // 不是桥，递归处理子树
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      int u, v;
      for (int i = 1; i <= m; i++) cin >> u >> v, uadd(u, v), re[P(u, v)]++;
      for (int i = 1; i <= n; i++)
        if (!dep[i]) dfs(i, 0);
      for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs2(i, 0);
      for (int i = 1; i <= n; i++)
        if (!fa[i]) cnt++, dfs3(i);
      cout << cnt << '\n';
      for (int i = 1; i <= cnt; i++) {
        cout << ans[i].size() << ' ';
        for (int j = 0; j < ans[i].size(); j++) cout << ans[i][j] << ' ';
        cout << '\n';
      }
      return 0;
    }
    ```

???+ note "[#2788.「CEOI2015 Day1」管道](https://loj.ac/p/2788)"
    给出一个 $N$ 点 $M$ 边的无向图，不保证连通．将每个连通块视为子图，请求出每一个子图中的桥．**你只有 16 MB 的内存空间．**

??? note "题解"
    此题最大的特征在于，你存不下所有的边．
    
    考虑优化存边，若一条非树边被另一条非树边完全覆盖，则这条边无用．
    
    用并查集维护即可．

## 点双连通分量

???+ note "[例题：洛谷 P8435【模板】点双连通分量](https://www.luogu.com.cn/problem/P8435)"
    对于一个 $n$ 个节点 $m$ 条无向边的图，请输出其点双连通分量的个数，并且输出每个点双连通分量．

### Tarjan 算法

需要先学习割点，可以先参见 [割点和桥](./cut.md) 的割点部分．

先给出两个性质：

1.  两个点双最多只有一个公共点，且一定是割点．
2.  对于一个点双，它在 DFS 搜索树中 dfn 值最小的点一定是割点或者树根．

我们根据第二个性质，分类讨论：

1.  当这个点为割点时，它一定是点双连通分量的根，因为一旦包含它的父节点，他仍然是割点．
2.  当这个点为树根时：
    1.  有两个及以上子树，它是一个割点．
    2.  只有一个子树，它是一个点双连通分量的根．
    3.  它没有子树，视作一个点双．

??? note "示例代码"
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;
    constexpr int N = 5e5 + 5, M = 2e6 + 5;
    int n, m;

    struct edge {
      int to, nt;
    } e[M << 1];

    int hd[N], tot = 1;

    void add(int u, int v) { e[++tot] = edge{v, hd[u]}, hd[u] = tot; }

    void uadd(int u, int v) { add(u, v), add(v, u); }

    int ans;
    int dfn[N], low[N], bcc_cnt;
    int sta[N], top, cnt;
    bool cut[N];
    vector<int> dcc[N];
    int root;

    void tarjan(int u) {
      dfn[u] = low[u] = ++bcc_cnt, sta[++top] = u;
      if (u == root && hd[u] == 0) {
        dcc[++cnt].push_back(u);
        return;
      }
      int f = 0;
      for (int i = hd[u]; i; i = e[i].nt) {
        int v = e[i].to;
        if (!dfn[v]) {
          tarjan(v);
          low[u] = min(low[u], low[v]);
          if (low[v] >= dfn[u]) {
            if (++f > 1 || u != root) cut[u] = true;
            cnt++;
            do dcc[cnt].push_back(sta[top--]);
            while (sta[top + 1] != v);
            dcc[cnt].push_back(u);
          }
        } else
          low[u] = min(low[u], dfn[v]);
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      int u, v;
      for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        if (u != v) uadd(u, v);
      }
      for (int i = 1; i <= n; i++)
        if (!dfn[i]) root = i, tarjan(i);
      cout << cnt << '\n';
      for (int i = 1; i <= cnt; i++) {
        cout << dcc[i].size() << ' ';
        for (int j = 0; j < dcc[i].size(); j++) cout << dcc[i][j] << ' ';
        cout << '\n';
      }
      return 0;
    }
    ```

### 差分算法

![bcc-2.png](./images/bcc-2.svg)

如上图所示，黑色边为树边，红色边为非树边，每一条非树边的两个端点都唯一对应了树上由树边构成的一条简单路径．

考虑一张新图，新图中的每一个点对应原图中的每一条树边（在图中用蓝色点表示）．对于原图中的每一条非树边，将这条非树边对应的树上简单路径中的所有边在新图中对应的蓝点连成一个连通块（在图中用蓝色的边体现出来）．

这样，一个点若 **不是** 割点，当且仅当与其相连的所有边在新图中对应的蓝点都 **属于** 同一个连通块．

两个点 **是** 点双连通，当且仅当它们在原图的树上路径中的所有边在新图中对应的蓝点都 **属于** 同一个连通块，即图中的每个蓝点构成的连通块都是一个点双连通分量．

蓝点间的连通关系可以用与求边双连通时用到的差分类似的方法维护，时间复杂度 $O(n+m)$．
