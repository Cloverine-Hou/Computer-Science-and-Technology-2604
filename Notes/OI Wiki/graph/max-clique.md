author: Persdre

前置知识：[团](./concept.md)

## 引入

在计算机科学中，团问题指的是在给定的图中找到团（顶点的子集，都彼此相邻，也称为完全子图）的计算问题．

团的问题在现实生活中也有体现．例如我们考虑一个社交网络，其中图的点代表用户，图的边代表其所连接的两个用户互相认识．那么我们找到了一个团，也就找到了一群互相认识的人．

我们如果想要找到这个社交网络中最大的一群互相认识的人，那么就需要用到最大团搜索算法．

我们已经介绍了 [极大团](./concept.md) 的概念，最大团指的是点数量最多的极大团．

## 解释

想法是利用递归和回溯，用一个列表存储点，每次加入点进来都检查这些点是否仍在一个团中．如果加入进来这个点后就无法还是一个团了，就回溯到满足条件的位置，重新加入别的点．

采用回溯策略的原因是，我们并不知道某个顶点 $v$  **最终** 是否是最大团中的成员．如果递归算法选择 $v$ 作为最大团的成员时，并没有找到最大团，那么应该回溯，并查找最大团中没有 $v$ 的解．

## 过程

**Bron–Kerbosch** 算法对于这种想法进行了优化实现．它的基础形式是通过给定三个集合：$R$、$P$、$X$ 来递归地进行搜索．步骤如下：

1.  初始化集合 $R,X$ 分别为空，集合 $P$ 是图中所有点的集合．
2.  每次从集合 $P$ 中取顶点 $v$，当集合中没有顶点时，有两种情况：
    1.  集合 $R$ 是最大团，此时集合 $X$ 为空
    2.  无最大团，此时回溯
3.  对于每一个从集合 $P$ 中取得的顶点 $v$，有如下处理：
    1.  将顶点 $v$ 加到集合 $R$ 中，之后递归集合 $R,P,X$
    2.  从集合 $P$ 中删除顶点 $v$，并将顶点 $v$ 添加到集合 $X$ 中
    3.  若集合 $P,X$ 都为空，则集合 $R$ 即为最大团

此方法也可继续优化．为了节省时间让算法更快的回溯，可以通过设定关键点（pivot vertex）来进行搜索．另一种优化思路是在开始时把所有点排序，枚举时按照下标顺序，防止重复．

## 实现

### 伪代码

```text
R := {}
P := node set of G 
X := {}

BronKerbosch1(R, P, X):
    if P and X are both empty:
        report R as a maximal clique
    for each vertex v in P:
        BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
```

### C++ 实现

??? note "实现代码"
    ```cpp
    #include <cstring>
    #include <iostream>
    using namespace std;
    constexpr int MAXN = 105;

    struct MaxClique {
      bool g[MAXN][MAXN];
      int n, dp[MAXN], st[MAXN][MAXN], ans;

      // dp[i]表示第i个点之后能组成的最大团的大小，
      // st[i][j]表示算法中第i层dfs所需要的点的集合，保存有可能是最大团其中之一的点

      void init(int n) {
        this->n = n;
        memset(g, false, sizeof(g));
      }

      void addedge(int u, int v, int w) { g[u][v] = w; }

      bool dfs(int sz, int num) {
        if (sz == 0) {
          if (num > ans) {
            ans = num;
            return true;
          }
          return false;
        }
        for (int i = 0; i < sz; i++) {  // 在第num层的集合中枚举一个点i
          if (sz - i + num <= ans) return false;  // 剪枝1
          int u = st[num][i];
          if (dp[u] + num <= ans) return false;  // 剪枝2
          int cnt = 0;
          for (
              int j = i + 1; j < sz;
              j++) {  // 在第num层遍历在i之后的且与i所相连的点，并且加入第num+1层集合
            if (g[u][st[num][j]]) st[num + 1][cnt++] = st[num][j];
          }
          if (dfs(cnt, num + 1)) return true;
        }
        return false;
      }

      int solver() {
        ans = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = n; i >= 1; i--) {
          int cnt = 0;
          for (int j = i + 1; j <= n; j++) {  // 初始化第1层集合
            if (g[i][j]) st[1][cnt++] = j;
          }
          dfs(cnt, 1);
          dp[i] = ans;
        }
        return ans;
      }

    } maxclique;

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      int n;
      while (cin >> n, n) {
        maxclique.init(n);
        for (int i = 1; i <= n; i++) {
          for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            maxclique.addedge(i, j, x);
          }
        }
        cout << maxclique.solver() << '\n';
      }
      return 0;
    }
    ```

## 例题

???+ note "[POJ 2989: All Friends](http://poj.org/problem?id=2989)"
    题目大意：给出 $n$ 个人，其中有 $m$ 对朋友，求最大团数量．

思路：模版题，要用 Bron–Kerbosch 算法

伪代码：

```text
 BronKerbosch(All, Some, None):  
     if Some and None are both empty:  
         report All as a maximal clique // 所有点已选完，且没有不能选的点，累加答案  
     for each vertex v in Some: // 枚举 Some 中的每一个元素  
         BronKerbosch1(All ⋃ {v}, Some ⋂ N(v), None ⋂ N(v))   
         // 将 v 加入 All，显然只有与 v 为朋友的人才能作为备选，None 中也只有与 v 为朋友的才会对接下来造成影响  
         Some := Some - {v} // 已经搜过，从 Some 中删除，加入 None  
         None := None ⋃ {v} 
```

为了节省时间和让算法更快的回溯，我们可以通过设定关键点（pivot vertex）$v$ 进行优化．

我们知道在上述的算法中必然有许多重复计算之前计算过的极大团，然后回溯的过程．

以前文提到的 $R$、$P$、$X$ 三个集合为例：

我们考虑如下问题，取集合 $P\cup X$ 中的一个点 $u$，要与 $R$ 集合构成极大团，那么取的点必然是 $P\cap N(u)$ 中一个点（$N(u)$ 代表与 $u$ 相邻的点）．

如果取完 $u$ 之后我们再取与 $u$ 相邻的点 $v$ 也能加入到极大团，那么我们只取 $u$ 就好了．这样做可以减少之后对 $v$ 的重复计算．我们之后只需要取与 $u$ 不相邻的点．

加入优化后的 C++ 代码实现：

??? note "实现代码"
    ```cpp
    #include <cstring>
    #include <iostream>
    using namespace std;
    constexpr int MAXN = 130;
    bool mp[MAXN][MAXN];
    int some[MAXN][MAXN], none[MAXN][MAXN], all[MAXN][MAXN];
    int n, m, ans;

    void dfs(int d, int an, int sn, int nn) {
      if (!sn && !nn) ++ans;
      int u = some[d][0];
      for (int i = 0; i < sn; ++i) {
        int v = some[d][i];
        if (mp[u][v]) continue;
        for (int j = 0; j < an; ++j) all[d + 1][j] = all[d][j];
        all[d + 1][an] = v;
        int tsn = 0, tnn = 0;
        for (int j = 0; j < sn; ++j)
          if (mp[v][some[d][j]]) some[d + 1][tsn++] = some[d][j];
        for (int j = 0; j < nn; ++j)
          if (mp[v][none[d][j]]) none[d + 1][tnn++] = none[d][j];
        dfs(d + 1, an + 1, tsn, tnn);
        some[d][i] = 0, none[d][nn++] = v;
        if (ans > 1000) return;
      }
    }

    int work() {
      ans = 0;
      for (int i = 0; i < n; ++i) some[1][i] = i + 1;
      dfs(1, 0, n, 0);
      return ans;
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      while (cin >> n >> m) {
        memset(mp, 0, sizeof mp);
        for (int i = 1; i <= m; ++i) {
          int u, v;
          cin >> u >> v;
          mp[u][v] = mp[v][u] = true;
        }
        int tmp = work();
        if (tmp > 1000)
          cout << "Too many maximal sets of friends.\n";
        else
          cout << tmp << '\n';
      }
      return 0;
    }
    ```

## 习题

-   [ZOJ 1492 Maximum Clique](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=4&problemSetProblemId=91827364991)
-   [POJ 1419 无向图最大团](http://poj.org/problem?id=1419)
-   [POJ 1129 广播电台](http://poj.org/problem?id=1129)

## 参考资料

-   [团问题 - 维基百科](https://en.wikipedia.org/wiki/Clique_problem)
-   [无向图的极大团、最大团（Bron–Kerbosch 算法）](https://blog.csdn.net/yo_bc/article/details/77453478)
-   [最大团问题——Bron–Kerbosch 算法](https://hallelujahjeff.github.io/2018/04/12/34/)
-   [最大团问题](https://www.cnblogs.com/zhj5chengfeng/archive/2013/07/29/3224092.html)
