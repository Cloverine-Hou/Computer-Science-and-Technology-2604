## 简介

状压 DP 是动态规划的一种，通过将状态集合转化为整数记录在 DP 状态中来实现状态转移的目的．

为了达到更低的时间复杂度，通常需要寻找更低状态数的状态．大部分题目中会利用二元状态，用 $n$ 位二进制数表示 $n$ 个独立二元状态的情况．

使用状态压缩通常涉及位操作，关于基础位操作详见 [位操作](../math/bit.md) 页面．

## 例题 1

???+ note "[「SCOI2005」互不侵犯](https://loj.ac/problem/2153)"
    在 $N\times N$ 的棋盘里面放 $K$ 个国王（$1 \leq N \leq 9, 1 \leq K \leq N \times N$），使他们互不攻击，共有多少种摆放方案．
    
    国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共 $8$ 个格子．

### 解释

设 $f(i,j,l)$ 表示前 $i$ 行，第 $i$ 行的状态为 $j$，且棋盘上已经放置 $l$ 个国王时的合法方案数．

对于编号为 $j$ 的状态，我们用二进制整数 $sit(j)$ 表示国王的放置情况，$sit(j)$ 的某个二进制位为 $0$ 表示对应位置不放国王，为 $1$ 表示在对应位置上放置国王；用 $sta(j)$ 表示该状态的国王个数，即二进制数 $sit(j)$ 中 $1$ 的个数．例如，如下图所示的状态可用二进制数 $100101$ 来表示（棋盘左边对应二进制低位），则有 $sit(j)=100101_{(2)}=37, sta(j)=3$．

![](./images/SCOI2005-互不侵犯.png)

设当前行的状态为 $j$，上一行的状态为 $x$，可以得到下面的状态转移方程：$f(i,j,l) = \sum f(i-1,x,l-sta(j))$．

设上一行的状态编号为 $x$，在保证当前行和上一行不冲突的前提下，枚举所有可能的 $x$ 进行转移，转移方程：

$$
f(i,j,l) = \sum f(i-1,x,l-sta(j))
$$

### 实现

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    using namespace std;
    long long sta[2005], sit[2005], f[15][2005][105];
    int n, k, cnt;

    void dfs(int x, int num, int cur) {
      if (cur >= n) {  // 有新的合法状态
        sit[++cnt] = x;
        sta[cnt] = num;
        return;
      }
      dfs(x, num, cur + 1);  // cur位置不放国王
      dfs(x + (1 << cur), num + 1,
          cur + 2);  // cur位置放国王，与它相邻的位置不能再放国王
    }

    bool compatible(int j, int x) {
      if (sit[j] & sit[x]) return false;
      if ((sit[j] << 1) & sit[x]) return false;
      if (sit[j] & (sit[x] << 1)) return false;
      return true;
    }

    int main() {
      cin >> n >> k;
      dfs(0, 0, 0);  // 先预处理一行的所有合法状态
      for (int j = 1; j <= cnt; j++) f[1][j][sta[j]] = 1;
      for (int i = 2; i <= n; i++)
        for (int j = 1; j <= cnt; j++)
          for (int x = 1; x <= cnt; x++) {
            if (!compatible(j, x)) continue;  // 排除不合法转移
            for (int l = sta[j]; l <= k; l++) f[i][j][l] += f[i - 1][x][l - sta[j]];
          }
      long long ans = 0;
      for (int i = 1; i <= cnt; i++) ans += f[n][i][k];  // 累加答案
      cout << ans << endl;
      return 0;
    }
    ```

## 例题 2

???+ note "[\[POI2004\] PRZ](https://www.luogu.com.cn/problem/P5911)"
    有 $n$ 个人需要过桥，第 $i$ 的人的重量为 $w_i$，过桥用时为 $t_i$. 这些人过桥时会分成若干组，只有在某一组的所有人全部过桥后，其余的组才能过桥．桥最大承重为 $W$，问这些人全部过桥的最短时间．
    
    $100\le W \le 400$，$1\le n\le 16$，$1\le t_i\le 50$，$10\le w_i\le 100$.

### 解释

我们用 $S$ 表示所有人构成集合的一个子集，设 $t(S)$ 表示 $S$ 中人的最长过桥时间，$w(S)$ 表示 $S$ 中所有人的总重量，$f(S)$ 表示 $S$ 中所有人全部过桥的最短时间，则：

$$
\begin{cases}
    f(\varnothing)=0,\\
    f(S)=\min\limits_{T\subseteq S;~w(T)\leq W}\left\{t(T)+f(S\setminus T)\right\}.
\end{cases}
$$

需要注意的是这里不能直接枚举集合再判断是否为子集，而应使用 [子集枚举](../math/binary-set.md#遍历所有掩码的子掩码)，从而使时间复杂度为 $O(3^n)$.

### 实现

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <limits>
    #include <vector>
    using namespace std;

    int main() {
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      int W, n;
      cin >> W >> n;
      const int S = (1 << n) - 1;
      vector<int> ts(S + 1), ws(S + 1);
      for (int j = 0, t, w; j < n; ++j) {
        cin >> t >> w;
        for (int i = 0; i <= S; ++i)
          if (i & (1 << j)) {
            ts[i] = max(ts[i], t);
            ws[i] += w;
          }
      }
      vector<int> dp(S + 1, numeric_limits<int>::max() / 2);
      for (int i = 0; i <= S; ++i) {
        if (ws[i] <= W) dp[i] = ts[i];
        for (int j = i; j; j = i & (j - 1))
          if (ws[i ^ j] <= W) dp[i] = min(dp[i], dp[j] + ts[i ^ j]);
      }
      cout << dp[S] << '\n';
      return 0;
    }
    ```

## 习题

-   [「NOI2001」炮兵阵地](https://loj.ac/problem/10173)
-   [「USACO06NOV」玉米田 Corn Fields](https://www.luogu.com.cn/problem/P1879)
-   [「九省联考 2018」一双木棋](https://loj.ac/problem/2471)
