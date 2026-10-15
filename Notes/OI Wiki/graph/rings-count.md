## 普通环计数

???+ note "[例题 1：Codeforces Beta Round 11 D. A Simple Task](https://codeforces.com/problemset/problem/11/D)"
    给定一个简单图，求图中简单环的数目．简单环是指没有重复顶点或边的环．
    
    结点数目 $1\leq n\leq 19$．

??? note "解题思路"
    考虑状态压缩动态规划．记 $f(s,i)$ 表示满足当前经过结点集合为 $s$，且现在在结点 $i$ 上，且第一个结点为结点集合 $s$ 中 **编号最小的那个** 的路径条数．
    
    对于状态 $f(s,i)$，枚举下一个结点 $u$．若 $u$ 在集合 $s$ 中且是编号最小的那个（即起点），就将答案 $A$ 加上 $f(s,i)$．若 $u$ 不在 $s$ 中，就将 $f(s,i)$ 加到 $f(s\cup\{u\},u)$ 上．
    
    这样会把二元环（即重边）也算上，并且每个非二元环会被计算两次（因为固定起点可以向两个方向走），所以答案为 $\dfrac{A-m}2$，其中 $m$ 表示边数．时间复杂度 $O(2^nm)$．

??? note "示例代码"
    ```cpp
    #include <iostream>
    using namespace std;

    int n, m;

    struct Edge {
      int to, nxt;
    } edge[500];

    int cntEdge, head[20];

    void addEdge(int u, int v) {
      edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
    }

    long long answer, dp[1 << 19][20];

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
      }
      for (int i = 1; i <= n; i++) dp[1 << (i - 1)][i] = 1;
      for (int s = 1; s < (1 << n); s++)
        for (int i = 1; i <= n; i++) {
          if (!dp[s][i]) continue;
          for (int j = head[i]; j; j = edge[j].nxt) {
            int u = i, v = edge[j].to;
            if ((s & -s) > (1 << (v - 1))) continue;
            if (s & (1 << (v - 1))) {
              if ((s & -s) == (1 << (v - 1))) answer += dp[s][u];
            } else
              dp[s | (1 << (v - 1))][v] += dp[s][u];
          }
        }
      cout << (answer - m) / 2 << '\n';
      return 0;
    }
    ```

## 三元环计数

**三元环** 指的是一个简单图 $G$ 中的一个无序三元组 $(u,\ v,\ w)$ 满足存在三条边分别连接 $(u,\ v)$，$(v,\ w)$ 和 $(w,\ u)$．而 **三元环计数问题** 要求计算出图中所有三元环的数量．

首先给所有边定向．我们规定从度数小的点指向度数大的点，度数相同就从编号小的点指向编号大的点．那么此时此图是一张有向无环图（DAG）．

??? note "该图没有环的证明"
    反证法，假设存在环，那么环中的点度数一个比一个大，要形成环，所有点的度数必须相等，但是编号必定不同，矛盾．
    
    所以定向后图肯定不存在环．
    
    事实上，可以根据上述定向规则构造一个 [偏序](../math/order-theory.md#二元关系)，所以按此规则构造的图（也即该偏序的 [Hasse 图](../math/order-theory.md#偏序集的可视化表示hasse-图)）一定是一个 DAG．

枚举 $u$ 和 $u$ 指向的点 $v$，再在 $v$ 指向的点中枚举 $w$，检验 $u$ 是否与 $w$ 相连即可．

这个算法的时间复杂度为 $O(m\sqrt m)$．

???+ note "时间复杂度证明"
    对于定向部分，遍历了所有的边，时间复杂度 $O(n+m)$．
    
    对于每一对 $(v,\ w)$，$u$ 的数量都不超过 $v$ 的入度 $d^-(v)$．
    
    若 $d^-(v)\leq\sqrt m$，由于 $w$ 的个数至多为 $n$，所以这部分时间复杂度为 $O(n\sqrt m)$．
    
    若 $d^-(v) > \sqrt m$，由于 $v$ 指向 $w$，所以 $d(v) \leq d(w)$，得出 $d(w) > \sqrt m$，但是总边数只有 $m$，所以这样的 $w$ 的个数至多为 $\sqrt m$，故时间复杂度为 $O(m\sqrt m)$．
    
    总时间复杂度为 $O(n+m+n\sqrt m+m\sqrt m)=O(m\sqrt m)$．
    
    事实上，如果定向时从度数大的点指向度数小的点，复杂度也正确，只需要交换 $u,\ w$ 两个点，上述证明也成立．

???+ note "示例代码（[洛谷 P1989 无向图三元环计数](https://www.luogu.com.cn/problem/P1989)）"
    ```cpp
    #include <iostream>
    using namespace std;

    int n, m, total;
    int deg[200001], u[200001], v[200001];
    bool vis[200001];

    struct Edge {
      int to, nxt;
    } edge[200001];

    int cntEdge, head[100001];

    void addEdge(int u, int v) {
      edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      for (int i = 1; i <= m; i++) cin >> u[i] >> v[i], deg[u[i]]++, deg[v[i]]++;
      for (int i = 1; i <= m; i++) {
        if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] < deg[v[i]])
          swap(u[i], v[i]);
        addEdge(u[i], v[i]);
      }
      for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = edge[i].nxt) vis[edge[i].to] = true;
        for (int i = head[u]; i; i = edge[i].nxt) {
          int v = edge[i].to;
          for (int j = head[v]; j; j = edge[j].nxt) {
            int w = edge[j].to;
            if (vis[w]) total++;
          }
        }
        for (int i = head[u]; i; i = edge[i].nxt) vis[edge[i].to] = false;
      }
      cout << total << '\n';
      return 0;
    }
    ```

### 例题 2

???+ note "[HDU 6184 Counting Stars](https://acm.hdu.edu.cn/showproblem.php?pid=6184)"
    给定一张有 $n$ 个点和 $m$ 条边的无向图，求下面图形的出现次数．
    
    ![](./images/rings-count1.svg)
    
    $2\leq n\leq 10^5$，$1\leq m\leq\min\left\{2\times 10^5,\ \dfrac{n(n-1)}2\right\}$．

??? note "解题思路"
    这个图形是两个三元环共用了一条边形成的．所以我们先跑一遍三元环计数，统计出一条边上三元环的数量，然后枚举共用的那条边，设有 $x$ 个三元环中有此边，那么对答案的贡献就是 $\dbinom x2$．
    
    时间复杂度 $O(m\sqrt m)$．

??? note "示例代码"
    ```cpp
    #include <cstring>
    #include <iostream>
    using namespace std;

    int n, m, total;
    int deg[200001], u[200001], v[200001];
    int edgeId[200001], cnt[200001];

    struct Edge {
      int to, nxt;
    } edge[200001];

    int cntEdge, head[100001];

    void addEdge(int u, int v) {
      edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
    }

    int main() {
      while (cin >> n >> m) {
        cntEdge = total = 0;
        memset(deg, 0, sizeof deg);
        memset(head, 0, sizeof head);
        for (int i = 1; i <= m; i++) cin >> u[i] >> v[i], deg[u[i]]++, deg[v[i]]++;
        for (int i = 1; i <= m; i++) {
          if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] < deg[v[i]])
            swap(u[i], v[i]);
          addEdge(u[i], v[i]);
        }

        for (int u = 1; u <= n; u++) {
          for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = i;
          for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;
            for (int j = head[v]; j; j = edge[j].nxt) {
              int w = edge[j].to;
              if (edgeId[w]) cnt[i]++, cnt[j]++, cnt[edgeId[w]]++;
            }
          }
          for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = 0;
        }
        for (int i = 1; i <= m; i++) total += cnt[i] * (cnt[i] - 1) / 2, cnt[i] = 0;
        cout << total << '\n';
      }
      return 0;
    }
    ```

## 四元环计数

类似地，**四元环** 就是指四个点 $a,\ b,\ c,\ d$ 满足 $(a,\ b)$，$(b,\ c)$，$(c,\ d)$ 和 $(d,\ a)$ 均有边连接．

考虑先对点进行排序．度数小的排在前面，度数大的排在后面．

考虑枚举排在最后面的点 $a$，此时只需要对于每个比 $a$ 排名更前的点 $c$，都求出有多少个排名比 $a$ 前的点 $b$ 满足 $(a,\ b)$，$(b,\ c)$ 有边．然后只需要从这些 $b$ 中任取两个都能成为一个四元环．求 $b$ 的数量只需要遍历一遍 $b$ 和 $c$ 即可．

注意到我们枚举的复杂度本质上与枚举三元环等价，所以时间复杂度也是 $O(m\sqrt m)$（假设 $n,\ m$ 同阶）．

值得注意的是，$(a,\ b,\ c,\ d)$ 和 $(a,\ c,\ b,\ d)$ 可以是两个不同的四元环．

另外，度数相同的结点的排名将不相同，并且需要注意判断 $a\neq c$．

???+ note "示例代码（[LibreOJ P191 无向图四元环计数](https://loj.ac/p/191)）"
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;

    int n, m, deg[100001], cnt[100001];
    vector<int> E[100001], E1[100001];

    long long total;

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
        deg[u]++, deg[v]++;
      }
      for (int u = 1; u <= n; u++)
        for (int v : E[u])
          if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v)) E1[u].push_back(v);
      for (int a = 1; a <= n; a++) {
        for (int b : E1[a])
          for (int c : E[b]) {
            if (deg[a] < deg[c] || (deg[a] == deg[c] && a <= c)) continue;
            total += cnt[c]++;
          }
        for (int b : E1[a])
          for (int c : E[b]) cnt[c] = 0;
      }
      cout << total << '\n';
      return 0;
    }
    ```

### 例题 3

???+ note "[Gym 102028L Connected Subgraphs](https://codeforces.com/gym/102028/problem/L)"
    给定一张有 $n$ 个点和 $m$ 条边的无向图，求四条边的导出子图连通的情况数．
    
    $4\leq n\leq 10^5$，$4\leq m\leq 2\times 10^5$．

??? note "解题思路"
    容易把情况分为五种：菊花图、四元环、三元环上一个点连出一条边、四个点构成的链中间一个点连出一条边以及五个点构成的链．
    
    菊花图直接枚举点的度数，用组合数解决即可．四元环可以直接按照上述算法求得．三元环部分只需枚举三元环 $(u,\ v,\ w)$，那么对答案的贡献就是 $[d(u)-2]+[d(v)-2]+[d(w)-2]$．
    
    下面考虑第四种情况．考虑枚举度数为 $2$ 的点 $x$，再枚举与它相邻的一个结点 $y$ 作为度数为 $3$ 的那个点．此时对答案的贡献为 $[d(x)-1]\cdot\dbinom{d(y)-1}2$．但是注意到 $y$ 的相邻节点可能会和 $x$ 的相邻结点重合，此时的图形等价于第三种情况．但是每种多算的第三种情况都会被多算两次（因为有两个度数为 $3$ 的点），所以应该减去第三种情况数目的两倍．
    
    对于最后一种情况，先枚举中间的点 $x$，那么容易发现对答案的贡献是
    
    $$
    \sum_{y\in son_x}\sum_{z\in son_x}[d(y)-1]\cdot[d(z)-1].
    $$
    
    同样地，这其中有多算的部分．设 $y$ 的相邻结点为 $s$，$z$ 的相邻结点为 $t$，那么思考后发现多算的有如下几种情况：
    
    1.  $y$ 与 $t$ 重合，但是 $s$ 与 $z$ 不重合时，等价于第三种情况；
    2.  $s$ 与 $z$ 重合，但是 $y$ 与 $t$ 不重合时，同样等价于第三种情况；
    3.  $y$ 与 $t$，$s$ 与 $z$ 都重合时，等价于一个三元环；
    4.  $s$ 与 $t$ 重合时，等价于一个四元环（第二种情况）．
    
    考虑到第三种情况中两个度数 $2$ 的点作为 $x$ 时正好分别对应上述多算情况的 1 和 2，所以要额外减去第三种情况数目的两倍．对于一个三元环，三个结点都可以作为 $x$，多算了 $3$ 次．同样的，四元环的情况被多算了 $4$ 次．
    
    于是我们就得出了所有情况的算法，时间复杂度为 $O(n+m\sqrt m)$．

??? note "示例代码"
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;
    constexpr int mod = 1000000007;

    constexpr long long power(long long a, long long n = mod - 2) {
      long long res = 1;
      while (n) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
      }
      return res;
    }

    constexpr long long power24 = power(24), power2 = power(2);

    int n, m;
    vector<int> E[100001], E1[100001], E2[100001];
    bool vis[100001];
    int cnt1[100001], cnt2[100001];

    long long solve1();
    long long solve2();
    long long solve3();
    long long solve4();
    long long solve5();
    long long ans[6];

    long long solve1() {
      if (ans[1] != -1) return ans[1];
      ans[1] = 0;
      for (int i = 1; i <= n; i++) {
        int x = E[i].size();
        ans[1] +=
            1ll * x * (x - 1) % mod * (x - 2) % mod * (x - 3) % mod * power24 % mod;
      }
      return ans[1] %= mod;
    }

    long long solve2() {
      if (ans[2] != -1) return ans[2];
      ans[2] = 0;
      for (int i = 1; i <= n; i++) {
        for (int j : E1[i])
          for (int k : E1[j]) cnt1[k]++;
        for (int j : E2[i])
          for (int k : E1[j])
            if (k != i) cnt2[k]++;
        for (int j : E1[i])
          for (int k : E1[j])
            ans[2] +=
                (1ll * cnt1[k] * (cnt1[k] - 1) / 2 + 1ll * cnt1[k] * cnt2[k]) % mod,
                cnt1[k] = 0;
        for (int j : E2[i])
          for (int k : E1[j])
            if (k != i)
              ans[2] += 1ll * cnt2[k] * (cnt2[k] - 1) / 2 % mod * power2 % mod,
                  cnt2[k] = 0;
      }
      return ans[2];
    }

    long long solve3() {
      if (ans[3] != -1) return ans[3];
      ans[0] = ans[3] = 0;
      for (int i = 1; i <= n; i++) {
        for (int j : E1[i]) vis[j] = true;
        for (int j : E1[i])
          for (int k : E1[j])
            if (vis[k])
              ans[3] =
                  (1ll * ans[3] + E[i].size() + E[j].size() + E[k].size() - 6) %
                  mod,
              ans[0]++;
        for (int j : E1[i]) vis[j] = false;
      }
      return ans[3];
    }

    long long solve4() {
      if (ans[4] != -1) return ans[4];
      ans[4] = 0;
      for (int i = 1; i <= n; i++)
        for (int j : E[i])
          (ans[4] += 1ll * (E[j].size() - 1) * (E[j].size() - 2) / 2 *
                     (E[i].size() - 1) % mod) %= mod;
      return ans[4] = (ans[4] - 2 * solve3()) % mod;
    }

    long long solve5() {
      if (ans[5] != -1) return ans[5];
      ans[5] = 0;
      for (int i = 1; i <= n; i++) {
        long long sum = 0;
        for (int j : E[i]) {
          ans[5] += sum * (E[j].size() - 1) % mod;
          sum += E[j].size() - 1;
        }
      }
      solve3();
      return ans[5] =
                 (ans[5] % mod - 2 * solve3() - 4 * solve2() - 3 * ans[0]) % mod;
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      int T;
      cin >> T;
      while (T--) {
        ans[5] = ans[1] = ans[2] = ans[4] = ans[3] = -1;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) E[i].clear(), E1[i].clear(), E2[i].clear();
        while (m--) {
          int x, y;
          cin >> x >> y;
          E[x].push_back(y), E[y].push_back(x);
        }
        for (int i = 1; i <= n; i++)
          for (int j : E[i]) {
            if (make_pair(E[i].size(), i) < make_pair(E[j].size(), j))
              E1[i].push_back(j);
            else
              E2[i].push_back(j);
          }
        cout << ((solve5() + solve1() + solve2() + solve4() + solve3()) % mod +
                 mod) %
                    mod
             << '\n';
      }
      return 0;
    }
    ```

## 习题

[洛谷 P3547 \[POI2013\] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

[CodeForces 985G Team Players](https://codeforces.com/contest/985/problem/G)（容斥原理）
