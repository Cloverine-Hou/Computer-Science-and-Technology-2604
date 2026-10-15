二维莫队，顾名思义就是每个状态有四个方向可以扩展．

二维莫队每次移动指针要操作一行或者一列的数，具体实现方式与普通的一维莫队类似，这里不再赘述．这里重点讲块长选定部分．

## 块长选定

记询问次数为 $q$，当前矩阵的左上角坐标为 $(x_1,\ y_1)$，右下角坐标为 $(x_2,\ y_2)$，取块长为 $B$．

那么指针 $x_1$ 移动了 $\Theta(q\cdot B)$ 次，而指针 $y_2$ 移动了 $\Theta(n^4\cdot B^{-3})$ 次．

所以只需令 $q\cdot B=n^4\cdot B^{-3}$，即 $B=n\cdot q^{-\frac 14}$ 即可．

注意这样计算 $B$ 的结果 **可能为 $0$**，**注意特判**．

最终，计算部分时间复杂度是 $\Theta(n^2\cdot q^{\frac 34})$，加上对询问的排序过程，总时间复杂度为 $\Theta(n^2\cdot q^{\frac 34}+q\log q)$．

## 例题 1

???+ note "[BZOJ 2639 矩形计算](https://hydro.ac/p/bzoj-P2639)"
    输入一个 $n\times m$ 的矩阵，矩阵的每一个元素都是一个整数，然后有 $q$ 个询问，每次询问一个子矩阵的权值．矩阵的权值是这样定义的，对于一个整数 $x$，如果它在该矩阵中出现了 $p$ 次，那么它给该矩阵的权值就贡献 $p^2$．
    
    数据范围：$1\leq n,\ m\leq 200$，$0\leq q\leq 10^5$，$|$ 矩阵元素大小 $| \leq 2\times 10^9$．

??? note "解题思路"
    先离散化，二维莫队时用一个数组记录每个数当前出现的次数即可．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <iostream>
    using namespace std;

    int n, m, q, a[201][201];
    long long ans[100001];
    int disc[250001], cntdisc;  // 离散化用

    int blocklen, counts[40001];
    long long now;

    struct Question {
      int x1, y1, x2, y2, qid;

      bool operator<(Question tmp) const {
        if (x1 / blocklen != tmp.x1 / blocklen) return x1 < tmp.x1;
        if (y1 / blocklen != tmp.y1 / blocklen) return y1 < tmp.y1;
        if (x2 / blocklen != tmp.x2 / blocklen) return x2 < tmp.x2;
        return y2 < tmp.y2;
      }
    } Q[100001];

    int Qcnt;

    void mo_algo_row(int id, int val, int Y1, int Y2) {
      for (int i = Y1; i <= Y2; i++)
        now -= (long long)counts[a[id][i]] * counts[a[id][i]],
            counts[a[id][i]] += val,
            now += (long long)counts[a[id][i]] * counts[a[id][i]];
    }

    void mo_algo_column(int id, int val, int X1, int X2) {
      for (int i = X1; i <= X2; i++)
        now -= (long long)counts[a[i][id]] * counts[a[i][id]],
            counts[a[i][id]] += val,
            now += (long long)counts[a[i][id]] * counts[a[i][id]];
    }

    void mo_algo() {
      blocklen = pow(n * m, 0.5) / pow(q, 0.25);
      if (blocklen < 1) blocklen = 1;
      sort(Q + 1, Q + 1 + Qcnt);

      int X1 = 1, Y1 = 1, X2 = 0, Y2 = 0;
      for (int i = 1; i <= Qcnt; i++) {
        while (X1 > Q[i].x1) mo_algo_row(--X1, 1, Y1, Y2);
        while (X2 < Q[i].x2) mo_algo_row(++X2, 1, Y1, Y2);
        while (Y1 > Q[i].y1) mo_algo_column(--Y1, 1, X1, X2);
        while (Y2 < Q[i].y2) mo_algo_column(++Y2, 1, X1, X2);
        while (X1 < Q[i].x1) mo_algo_row(X1++, -1, Y1, Y2);
        while (X2 > Q[i].x2) mo_algo_row(X2--, -1, Y1, Y2);
        while (Y1 < Q[i].y1) mo_algo_column(Y1++, -1, X1, X2);
        while (Y2 > Q[i].y2) mo_algo_column(Y2--, -1, X1, X2);
        ans[Q[i].qid] = now;
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> m;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j], disc[++cntdisc] = a[i][j];
      sort(disc + 1, disc + 1 + cntdisc);
      cntdisc = unique(disc + 1, disc + cntdisc + 1) - disc - 1;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
          a[i][j] = lower_bound(disc + 1, disc + 1 + cntdisc, a[i][j]) - disc;
      cin >> q;
      for (int i = 1; i <= q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        Q[++Qcnt] = {x1, y1, x2, y2, i};
      }

      mo_algo();
      for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
      return 0;
    }
    ```

## 例题 2

???+ note "[洛谷 P1527 \[国家集训队\] 矩阵乘法](https://www.luogu.com.cn/problem/P1527)"
    给你一个 $n\times n$ 的矩阵，$q$ 次询问，每次询问一个子矩形的第 $k$ 小数．
    
    数据范围：$1\leq n\leq 500$，$1\leq q\leq 6\times 10^4$，$0\leq a_{i,j}\leq 10^9$．

首先和上一题一样，需要离散化整个矩阵．但是需要注意，本题除了需要对数值进行分块，还需要对数值的值域进行分块，才能求出答案．

这里还需要用到奇偶化排序进行优化，具体内容请见 [普通莫队算法](../misc/mo-algo.md#普通莫队的优化)．

对于本题而言，时间限制不那么宽，注意代码常数的处理．取的块长计算值普遍较小，$n,\ q$ 都取最大值时块长大约在 $11$ 左右，可以直接设定为常数来节约代码耗时．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>
    using namespace std;

    int n, q, a[501][501], ans[60001];
    int disc[250001], cntdisc;  // 离散化用
    int nn;

    int blockId[501], blocklen;               // 分块
    int rangeblockId[250001], rangeblocklen;  // 值域分块
    int counts[250001], countsum[501];        // 该值次数及值域块总和

    struct Position {
      int x, y;
    };

    vector<Position> pos[250001];

    struct Question {
      int x1, y1, x2, y2, k, qid;

      bool operator<(Question tmp) const {
        if (blockId[x1] != blockId[tmp.x1]) return blockId[x1] < blockId[tmp.x1];
        if (blockId[y1] != blockId[tmp.y1])
          return blockId[x1] & 1 ? y1 < tmp.y1 : y1 > tmp.y1;
        if (blockId[y2] != blockId[tmp.y2])
          return blockId[y1] & 1 ? y2 < tmp.y2 : y2 > tmp.y2;
        else
          return blockId[y2] & 1 ? x2 < tmp.x2 : x2 > tmp.x2;
      }
    } Q[60001];

    int Qcnt;

    void mo_algo() {
      blocklen = 11;
      for (int i = 1; i <= n; ++i) blockId[i] = (i - 1) / blocklen + 1;
      rangeblocklen = n + 1;
      for (int i = 1; i <= nn; ++i) rangeblockId[i] = (i - 1) / rangeblocklen + 1;
      counts[a[1][1]] = countsum[rangeblockId[a[1][1]]] = 1;
      sort(Q + 1, Q + 1 + Qcnt);

      int L = 1, R = 1, D = 1, U = 1;
      for (int i = 1; i <= q; ++i) {
        while (R < Q[i].y2) {
          ++R;
          for (int i = U; i <= D; ++i)
            ++counts[a[i][R]], ++countsum[rangeblockId[a[i][R]]];
        }
        while (L > Q[i].y1) {
          --L;
          for (int i = U; i <= D; ++i)
            ++counts[a[i][L]], ++countsum[rangeblockId[a[i][L]]];
        }
        while (D < Q[i].x2) {
          ++D;
          for (int i = L; i <= R; ++i)
            ++counts[a[D][i]], ++countsum[rangeblockId[a[D][i]]];
        }
        while (U > Q[i].x1) {
          --U;
          for (int i = L; i <= R; ++i)
            ++counts[a[U][i]], ++countsum[rangeblockId[a[U][i]]];
        }
        while (R > Q[i].y2) {
          for (int i = U; i <= D; ++i)
            --counts[a[i][R]], --countsum[rangeblockId[a[i][R]]];
          --R;
        }
        while (L < Q[i].y1) {
          for (int i = U; i <= D; ++i)
            --counts[a[i][L]], --countsum[rangeblockId[a[i][L]]];
          ++L;
        }
        while (D > Q[i].x2) {
          for (int i = L; i <= R; ++i)
            --counts[a[D][i]], --countsum[rangeblockId[a[D][i]]];
          --D;
        }
        while (U < Q[i].x1) {
          for (int i = L; i <= R; ++i)
            --counts[a[U][i]], --countsum[rangeblockId[a[U][i]]];
          ++U;
        }
        int res = 1, cnt = 0;
        while (cnt + countsum[res] < Q[i].k && res <= rangeblockId[nn])
          cnt += countsum[res], ++res;
        res = (res - 1) * rangeblocklen + 1;
        while (cnt + counts[res] < Q[i].k && res <= nn) cnt += counts[res], ++res;
        ans[Q[i].qid] = disc[res];
      }
    }

    int main() {
      cin.tie(nullptr)->sync_with_stdio(false);
      cin >> n >> q;
      nn = n * n;
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
          int x;
          cin >> x;
          a[i][j] = disc[++cntdisc] = x;
        }
      sort(disc + 1, disc + 1 + cntdisc);
      cntdisc = unique(disc + 1, disc + cntdisc + 1) - disc - 1;
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          a[i][j] = lower_bound(disc + 1, disc + 1 + cntdisc, a[i][j]) - disc;
      for (int i = 1; i <= q; ++i) {
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        Q[++Qcnt] = {x1, y1, x2, y2, k, i};
      }

      mo_algo();
      for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
      return 0;
    }
    ```
