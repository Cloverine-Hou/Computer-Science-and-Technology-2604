author: Lyccrius, AtomAlpaca

## 综述

有时我们会遇见一些题目，这些题目看起来很适合使用莫队算法处理，但是他们的单次转移并非是 $O(1)$ 的，这时直接使用莫队即使调整块长，也会导致复杂度不正确．

此时，如果每次转移对答案的贡献可以进行差分，我们就可以将这些转移拆开离线下来，使用其它算法批量处理．

我们用 $f(x, l, r)$ 表示 $x$ 关于 $[l, r]$ 产生的贡献．

如我们在将当前区间 $[l, r]$ 扩展到 $[l, r + 1]$ 时，我们要求的是 $f(a_{r + 1}, l, r)$．如果可以差分，我们可以将其写成 $f(a_{r + 1}, 1, r) - f(a_{r + 1}, 1, l - 1)$，其中第一项我们可以对于每个 $r$ 都预处理出来，后一项我们可以把每个这样的项都离线存到对应的 $l - 1$ 上，然后从小到大枚举并扫描线处理．其它几个转移的方向也都可以类似地处理．

这一在莫队这个离线算法上，将转移再次离线处理的算法叫做莫队二次离线．

我们结合实际题目来理解．

## 例题

???+ note "[Luogu P5047 \[Ynoi2019 模拟赛\] Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047)"
    给你一个长为 $n$ 的序列 $a$，$m$ 次询问，每次查询一个区间的逆序对数．
    
    数据范围：$1 \leq n,m \leq 10^5$，$0 \leq a_i \leq 10^9$．

直接莫队每次转移至少是 $O(\log n)$ 的，观察可以发现我们每次转移要求的信息是「一个数在某个区间内的排名」，而这一信息关于区间可以差分，因此考虑二次离线．

我们将 $[l, r]$ 拓展到 $[l, r + 1]$，要求的是 在 $[l, r]$ 区间内有多少比 $a_{r + 1}$ 大的数．
我们用 $f(x, r)$ 表示 $[1, r]$ 区间内比 $a_x$ 大的数，$g(x, r)$ 表示 $[1, r]$ 区间内比 $a_x$ 小的数．则答案的变化量可以写作 $f(r + 1, r) - f(r + 1, l - 1)$．

同理 $[l, r]$ 缩小至 $[l, r - 1]$ 的变化量可以写作 $-f(r, r - 1) + f(r, l - 1)$；$[l, r]$ 拓展到 $[l - 1, r]$ 可以写作 $g(l - 1, r) - g(l - 1, l - 2)$,$[l, r]$ 缩小至 $[l + 1, r]$ 可以写作 $- g(l, r) + g(l, l - 1)$．

对于这些式子中的 $f(x, x - 1)$ 和 $g(x, x - 1)$，我们可以使用树状数组提前 $O(n \log n)$ 预处理出来；对于其余的 $f(x, p)$ 和 $g(x, p)$ 项，我们将 $x$ 离线存在 $l$ 进行批量处理．

这里有一个优化空间的技巧：我们发现处理每个询问时，离线到 $p$ 上的 $x$ 都是连续的一段，因此我们不需要把每次移动都存下，只需要存下调整的一段即可．这样我们的空间可以从总次数 $O(n\sqrt{m})$ 下降到询问数 $O(m)$．

现在我们来处理我们二次离线下来的问题：向一个集合中加入数，查询一个数在集合中的排名．莫队总共移动端点的次数是 $O(n\sqrt{m})$ 的，而数组总共只有 $O(n)$ 的长度，因此我们考虑使用 $O(\sqrt{n})$ 插入、$O(1)$ 查询的值域分块解决这个问题．

至此，我们在 $O(n \sqrt{m} + n \sqrt{n})$ 的时间复杂度和 $O(n + m)$ 的空间复杂度下解决了此题．

最后值得注意的是，我们求得的是每次的答案变化量而非答案本身，需要对其进行前缀和才能得到最终的答案．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <iostream>
    #include <vector>

    constexpr int MAX = 1e5 + 5;
    constexpr int MAXX = 4e2 + 5;
    constexpr int MX = 1e5;
    typedef long long ll;

    int n, m, sz, _sz;
    int a[MAX], b[MAX], bl[MAX], st[MAXX], ed[MAXX], b1[MAXX], b2[MAX], p1[MAX],
        p2[MAX];
    ll ans[MAX];

    struct N {
      int l, r, id, x, y;
    };

    std::vector<N> v[MAX];

    struct Q {
      int l, r, id;
      ll ans = 0;
    } q[MAX];

    bool cmp(Q a, Q b) {
      if (a.l / _sz != b.l / _sz) {
        return a.l < b.l;
      }
      return ((a.l / _sz) & 1) ? a.r < b.r : a.r > b.r;
    }

    void init() {
      sz = sqrt(MX);
      for (int i = 1; i <= sz; ++i) {
        st[i] = (MX / sz) * (i - 1) + 1;
        ed[i] = (MX / sz) * i;
      }
      ed[sz] = MX;
      for (int i = 1; i <= sz; ++i) {
        for (int j = st[i]; j <= ed[i]; ++j) {
          bl[j] = i;
        }
      }
    }

    void clear() {
      memset(b1, 0, sizeof(b1));
      memset(b2, 0, sizeof(b2));
    }

    void mdf(int x) {
      for (int i = bl[x]; i <= sz; ++i) {
        ++b1[i];
      }
      for (int i = x; i <= ed[bl[x]]; ++i) {
        ++b2[i];
      }
    }

    int qry(int x) {
      if (!x) {
        return 0;
      }
      return b1[bl[x] - 1] + b2[x];
    }

    int main() {
      scanf("%d%d", &n, &m);
      init();
      _sz = sqrt(m);
      for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
      }
      std::sort(b + 1, b + n + 1);
      int len = std::unique(b + 1, b + n + 1) - b - 1;
      for (int i = 1; i <= n; ++i) {
        a[i] = std::lower_bound(b + 1, b + len + 1, a[i]) - b;
      }
      for (int i = 1; i <= n; ++i) {
        p1[i] = qry(a[i] - 1);
        p2[i] = qry(n) - qry(a[i]);
        mdf(a[i]);
      }
      for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
      }
      std::sort(q + 1, q + m + 1, cmp);
      clear();
      for (int i = 1, L = 1, R = 0; i <= m; ++i) {
        int l = q[i].l, r = q[i].r;
        if (L > l) {
          v[R].push_back({l, L - 1, i, 1, 0});
        }
        while (L > l) {
          --L;
          q[i].ans -= p1[L];
        }
        if (R < r) {
          v[L - 1].push_back({R + 1, r, i, -1, 1});
        }
        while (R < r) {
          ++R;
          q[i].ans += p2[R];
        }
        if (L < l) {
          v[R].push_back({L, l - 1, i, -1, 0});
        }
        while (L < l) {
          q[i].ans += p1[L];
          ++L;
        }
        if (R > r) {
          v[L - 1].push_back({r + 1, R, i, 1, 1});
        }
        while (R > r) {
          q[i].ans -= p2[R];
          --R;
        }
      }
      for (int i = 1; i <= n; ++i) {
        mdf(a[i]);
        for (N j : v[i]) {
          for (int k = j.l; k <= j.r; ++k) {
            if (j.y == 0) {
              q[j.id].ans += j.x * qry(a[k] - 1);
            } else {
              q[j.id].ans += j.x * (i - qry(a[k]));
            }
          }
        }
      }
      for (int i = 2; i <= m; ++i) {
        q[i].ans += q[i - 1].ans;
      }
      for (int i = 1; i <= m; ++i) {
        ans[q[i].id] = q[i].ans;
      }
      for (int i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
      }
    }
    ```

???+ note "[Luogu P5501 \[LnOI2019\] 来者不拒，去者不追](https://www.luogu.com.cn/problem/P5501)"
    多次询问区间中 $[l, r]$ 中所有数的「Abbi 值」之和．
    
    Abbi 值定义为：若 $a_i$ 在询问区间 $[l,r]$ 中是第 $k$ 小，那么它的「Abbi 值」等于 $ka_i$．

我们不妨令 $f(x,r)$ 是 $[1,r]$ 中比 $a_x$ 大的数之和，$g(x,r)$ 是 $[1,r]$ 中比 $a_x$ 大的数的数量，那么我们向右移动右端点时，产生的贡献为 $f(r,r-1)-f(r,l-1) + a_r(r-l+ 1-(g(r,r-1)-g(r,l-1)))$，其它几个方向可同理写出，在此不加赘述．

上式中的 $f(r, r - 1)$ 和 $g(r, r - 1)$ 依旧可以进行预处理，其余的离线到另一端点上，进行扫描线处理．不难发现我们要处理的依然是 $O(n)$ 次插入、$O(n\sqrt{m})$ 次询问排名的问题，因此同样使用值域分块解决．

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <iostream>
    #include <vector>

    constexpr int MAX = 1e5 + 5;
    constexpr int MAXX = 4e2 + 5;
    constexpr int MX = 1e5;

    typedef long long ll;

    ll n, m, sz, _sz, sm;
    ll st[MAXX], ed[MAXX], bl[MAX], a[MAX], ans[MAX], sm1[MAXX], sm3[MAXX],
        sm2[MAX], sm4[MAX], s[MAX], pre[MAX];

    void init() {
      sz = sqrt(MX);
      for (int i = 1; i <= sz; ++i) {
        st[i] = (MX / sz) * (i - 1) + 1;
        ed[i] = (MX / sz) * i;
      }
      ed[sz] = MX;
      for (int i = 1; i <= sz; ++i) {
        for (int j = st[i]; j <= ed[i]; ++j) {
          bl[j] = i;
        }
      }
    }

    void mdf(ll x) {
      sm += x;
      for (int i = bl[x]; i <= sz; ++i) {
        ++sm1[i];
        sm3[i] += x;
      }
      for (int i = x; i <= ed[bl[x]]; ++i) {
        ++sm2[i];
        sm4[i] += x;
      }
    }

    ll qry(ll x) {
      if (!x) {
        return 0;
      }
      return sm1[bl[x] - 1] + sm2[x];
    }

    ll _qry(ll x) {
      if (!x) {
        return 0;
      }
      return sm3[bl[x] - 1] + sm4[x];
    }

    void clear() {
      sm = 0;
      memset(sm1, 0, sizeof(sm1));
      memset(sm2, 0, sizeof(sm2));
      memset(sm3, 0, sizeof(sm3));
      memset(sm4, 0, sizeof(sm4));
    }

    struct Q {
      ll l, r, id, ans;
    } q[MAX];

    struct N {
      ll l, r, id, x;
    };

    std::vector<N> v[MAX];

    bool cmp(Q a, Q b) {
      if (a.l / _sz != b.l / _sz) {
        return a.l < b.l;
      } else {
        return ((a.l / _sz) & 1) ? a.r < b.r : a.r > b.r;
      }
    }

    int main() {
      scanf("%lld%lld", &n, &m);
      _sz = n / sqrt(m);
      init();
      for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
      }
      for (int i = 1; i <= n; ++i) {
        pre[i] = qry(a[i] - 1) * a[i] + sm - _qry(a[i]);
        mdf(a[i]);
      }
      clear();
      for (int i = 1; i <= m; ++i) {
        scanf("%lld%lld", &q[i].l, &q[i].r);
        q[i].id = i;
      }
      std::sort(q + 1, q + m + 1, cmp);
      for (int i = 1, L = 1, R = 0; i <= m; ++i) {
        int l = q[i].l, r = q[i].r;
        if (L > l) {
          v[R].push_back({l, L - 1, i, 1});
        }
        while (L > l) {
          --L;
          q[i].ans -= pre[L];
        }
        if (R < r) {
          v[L - 1].push_back({R + 1, r, i, -1});
        }
        while (R < r) {
          ++R;
          q[i].ans += pre[R];
        }
        if (L < l) {
          v[R].push_back({L, l - 1, i, -1});
        }
        while (L < l) {
          q[i].ans += pre[L];
          ++L;
        }
        if (R > r) {
          v[L - 1].push_back({r + 1, R, i, 1});
        }
        while (R > r) {
          q[i].ans -= pre[R];
          --R;
        }
      }
      for (int i = 1; i <= n; ++i) {
        mdf(a[i]);
        for (N j : v[i]) {
          for (int k = j.l; k <= j.r; ++k) {
            q[j.id].ans += 1ll * j.x * (qry(a[k] - 1) * a[k] + sm - _qry(a[k]));
          }
        }
      }
      for (int i = 2; i <= m; ++i) {
        q[i].ans += q[i - 1].ans;
      }
      for (int i = 1; i <= m; ++i) {
        ans[q[i].id] = q[i].ans + s[q[i].r] - s[q[i].l - 1];
      }
      for (int i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
      }
      return 0;
    }
    ```
