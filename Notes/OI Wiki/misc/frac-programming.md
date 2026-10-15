author: greyqz, Ir1d, hsfzLZH1, huaruoji, banglee13

分数规划用来求一个分式的极值．其形式化表述是，给出 $a_i$ 和 $b_i$，求一组 $w_i\in\{0,1\}$，最小化或最大化

$$
\displaystyle\frac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}
$$

通俗来讲，这类问题类似于：每种物品有两个权值 $a$ 和 $b$，选出若干个物品使得 $\displaystyle\frac{\sum a}{\sum b}$ 最小或最大．

一般分数规划问题还会有一些特殊的限制，比如「分母至少为 $W$」．

## 求解

### 二分法

分数规划问题的通用方法是二分答案法．假设当前二分到的答案为 $\textit{mid}$，则一组满足条件的 $\{w_i\}$ 会让权值大于等于 $\textit{mid}$．根据这一条件列不等式并变形

$$
\displaystyle
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}\ge mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i\ge 0\\
\Longrightarrow&\sum w_i\times(a_i-mid\times b_i)\ge 0
\end{aligned}
$$

那么只要求出不等号左边的式子的最大值就行了．如果最大值比 $0$ 要大，说明 $mid$ 是可行的，否则不可行．分数规划的主要难点就在于如何求 $\displaystyle \sum w_i\times(a_i-mid\times b_i)$ 的最大值或最小值．

### Dinkelbach 算法

Dinkelbach 算法[^note1]的大概思想是每次用上一轮的答案当做新的 $L$ 来输入，不断地迭代，直至答案收敛．

## 例题

???+ example "[LOJ 149 01 分数规划](https://loj.ac/p/149)"
    有 $n$ 个物品，每个物品有两个权值 $a$ 和 $b$．求一组 $w_i\in\{0,1\}$，满足 $w_i$ 中恰好有 $k$ 个 $1$，最大化 $\displaystyle\frac{\sum a_i\times w_i}{\sum b_i\times w_i}$ 的值．

??? note "解法"
    把 $a_i-mid\times b_i$ 作为第 $i$ 个物品的权值，贪心地选权值前 $k$ 大的物品．若权值和大于 $0$ 则可行，否则不可行．

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <functional>
    using namespace std;

    constexpr int N = 100000 + 10;
    constexpr double eps = 1e-6;

    int n, k;
    int a[N], b[N];
    double c[N];

    bool check(double mid) {
      double s = 0;
      for (int i = 1; i <= n; i++) c[i] = a[i] - b[i] * mid;
      // 将权值从大到小排序
      sort(c + 1, c + n + 1, greater<double>());
      for (int i = 1; i <= k; ++i)  // 选择前 k 个物品
        s += c[i];
      return s >= 0;
    }

    int main() {
      scanf("%d %d", &n, &k);
      for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
      for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
      double L = 0, R = 1;
      while (R - L > eps) {
        double mid = (L + R) / 2;
        if (check(mid))  // mid 可行，答案比 mid 大
          L = mid;
        else  // mid 不可行，答案比 mid 小
          R = mid;
      }
      printf("%.6lf\n", L);
      return 0;
    }
    ```

???+ example "[洛谷 4377 Talent Show G](https://www.luogu.com.cn/problem/P4377)"
    有 $n$ 个物品，每个物品有两个权值 $a$ 和 $b$．
    
    你需要确定一组 $w_i\in\{0,1\}$，使得 $\displaystyle\frac{\sum w_i\times a_i}{\sum w_i\times b_i}$ 最大．
    
    要求 $\displaystyle\sum w_i\times b_i \geq W$．

??? note "解法"
    本题多了分母至少为 $W$ 的限制，因此无法再使用上一题的贪心算法．
    
    可以考虑 01 背包．把 $b_i$ 作为第 $i$ 个物品的重量，$a_i-mid\times b_i$ 作为第 $i$ 个物品的价值，然后问题就转化为背包了．那么 $dp[n][W]$ 就是最大值．
    
    在 DP 过程中，物品重量和可能超过 $W$，此时直接视为 $W$ 即可．

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    using namespace std;

    constexpr int MAXN = 250 + 10;
    constexpr int MAXW = 1000 + 10;
    constexpr double eps = 1e-6;

    int n, W;
    int w[MAXN], t[MAXN];
    double f[MAXW];

    bool check(double mid) {
      double s = 0;
      for (int i = 1; i <= W; i++) f[i] = -1e9;
      for (int i = 1; i <= n; i++)
        for (int j = W; j >= 0; j--) {
          int k = min(W, j + w[i]);
          f[k] = max(f[k], f[j] + t[i] - mid * w[i]);
        }
      return f[W] >= 0;
    }

    int main() {
      scanf("%d %d", &n, &W);
      double L = 0, R = 0;
      for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &w[i], &t[i]);
        R += t[i];
      }
      while (R - L > eps) {
        double mid = (L + R) / 2;
        if (check(mid))
          L = mid;
        else
          R = mid;
      }
      printf("%d\n", (int)(L * 1000));
      return 0;
    }
    ```

???+ example "[POJ2728 Desert King](http://poj.org/problem?id=2728)"
    每条边有两个权值 $a_i$ 和 $b_i$，求一棵生成树 $T$ 使得 $\displaystyle\frac{\sum_{e\in T}a_e}{\sum_{e\in T}b_e}$ 最小．

??? note "解法"
    把 $a_i-mid\times b_i$ 作为每条边的权值，那么最小生成树就是最小值．本题中需要求解一个完全图中的最小生成树，应利用 Prim 算法求解．

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    using namespace std;

    const int N = 1000 + 10;
    const double eps = 1e-5;

    int n;
    double d[N][N], c[N][N], dis[N];
    int x[N], y[N], z[N];
    bool vis[N];

    bool ok(double m) {
      double ans = 0;
      for (int i = 1; i <= n; i++) vis[i] = false;
      dis[1] = 0;
      for (int i = 2; i <= n; i++) dis[i] = 1e18;
      for (int i = 1; i <= n; i++) {
        double mn = 1e18;
        int pt = -1;
        for (int j = 1; j <= n; j++)
          if (!vis[j] && mn > dis[j]) {
            pt = j;
            mn = dis[j];
          }
        if (!~pt) break;
        vis[pt] = true;
        ans += mn;
        for (int j = 1; j <= n; j++)
          if (j != pt) dis[j] = min(dis[j], c[pt][j] - m * d[pt][j]);
      }
      return ans >= 0;
    }

    int main() {
      while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        for (int i = 1; i <= n; i++) scanf("%d %d %d", &x[i], &y[i], &z[i]);
        for (int i = 1; i <= n; i++)
          for (int j = i + 1; j <= n; j++) {
            d[i][j] = d[j][i] =
                sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            c[i][j] = c[j][i] = abs(z[i] - z[j]);
          }
        double l = 0, r = 10000000;
        while (r - l > eps) {
          double m = (l + r) / 2;
          if (ok(m))
            l = m;
          else
            r = m;
        }
        printf("%.3f\n", l);
      }
      return 0;
    }
    ```

???+ example "[\[HNOI2009\] 最小圈](https://www.luogu.com.cn/problem/P3199)"
    每条边的边权为 $w$，求一个环 $C$ 使得 $\displaystyle\frac{\sum_{e\in C}w}{|C|}$ 最小．

??? note "解法"
    把 $a_i-mid$ 作为边权，那么权值最小的环就是最小值．
    
    因为我们只需要判最小值是否小于 $0$，所以只需要判断图中是否存在负环即可．
    
    另外本题存在一种复杂度 $O(nm)$ 的算法，如果有兴趣可以阅读 [这篇文章](https://www.cnblogs.com/y-clever/p/7043553.html)．

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <tuple>
    #include <vector>
    using namespace std;

    constexpr int N = 3000 + 10;
    constexpr double eps = 1e-9;

    int n, m;
    double dis[N];
    vector<pair<int, double>> g[N];

    bool check(double mid) {  // 如果有负环返回 true
      bool flag = false;
      dis[0] = 0;
      for (int i = 1; i <= n; ++i) dis[i] = 1e9;
      for (int t = 1; t <= n; ++t) {
        flag = false;
        for (int u = 0; u <= n; ++u)
          for (auto vw : g[u]) {
            int v;
            double w;
            tie(v, w) = vw;
            if (dis[v] > dis[u] + w - mid) {
              dis[v] = dis[u] + w - mid;
              flag = true;
            }
          }
        if (!flag) break;
      }
      return flag;
    }

    int main() {
      scanf("%d %d", &n, &m);
      for (int i = 1; i <= m; ++i) {
        int u, v;
        double w;
        scanf("%d %d %lf", &u, &v, &w);
        g[u].push_back({v, w});
      }
      for (int i = 1; i <= n; i++) g[0].push_back({i, 0});
      double L = -1e7, R = 1e7;
      while (R - L > eps) {
        double mid = (L + R) / 2;
        if (check(mid))
          R = mid;
        else
          L = mid;
      }
      printf("%.8lf\n", L);
      return 0;
    }
    ```

## 习题

-   [JSOI2016 最佳团体](https://loj.ac/problem/2071)
-   [SDOI2017 新生舞会](https://loj.ac/problem/2003)
-   [UVa1389 Hard Life](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4135)
-   [洛谷 P2868 \[USACO07DEC\] Sightseeing Cows G](https://www.luogu.com.cn/problem/P2868)
-   [AtCoder Beginner Contest 324 F - Beautiful Path](https://atcoder.jp/contests/abc324/tasks/abc324_f)

## 参考资料与注释

[^note1]: [Dinkelbach, Werner. "On nonlinear fractional programming." Management science 13.7 (1967): 492-498.](https://doi.org/10.1287/mnsc.13.7.492)
