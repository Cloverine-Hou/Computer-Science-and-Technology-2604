## 引入

扫描线一般运用在图形上面，它和它的字面意思十分相似，就是一条线在整个图上扫来扫去，它一般被用来解决图形面积，周长，以及二维数点等问题．

## 二维矩形面积并问题

在二维坐标系上，给出多个矩形的左下以及右上坐标，求出所有矩形构成的图形的面积．

### 过程

根据图片可知总面积可以直接暴力即可求出面积，如果数据大了怎么办？这时就需要讲到 **扫描线** 算法．

现在假设我们有一根线，从下往上开始扫描：

![](./images/scanning.svg)

如图所示，把整个矩形分成如图各个颜色不同的小矩形，小矩形的高是扫过的距离，然而矩形的水平宽一直在变化．

给每一个矩形的上下边进行标记，下面的边标记为 1，上面的边标记为 -1．每遇到一个水平边时，让这条边（在横轴投影区间）的权值加上这条边的标记．

???+ note "Note"
    这个操作类似遍历括号序列：开括号加 1，闭括号减 1，「权值」对应当前位置的深度，「权值」是否大于 0，对应当前在不在括号里，也就是这段区间是否记入小矩形的宽度．

小矩形（不一定只有一个）的宽度就是整个数轴上权值大于 0 的区间总长度．

### 实现

用线段树维护矩形的长，也就是整个数轴上覆盖次数大于 0 的点．需求列举如下：

-   一段区间权值加 1、减 1．
-   统计整个数轴上，区间权值大于 0 的「区间长度和」．

如果你尝试直接用普通线段树模板来实现的话，也许会遇到些挫折．具体地，由于在区间加时，即使修改区间和节点管理区间重合，我们还是不能常数时间知道覆盖次数如何变化．这是因为我们不能直接知道：管理范围里有多长的区间会从 1 变成 0（从 0 变成 1）．

这道题只需要朴素的分治就能实现：维护每个节点管理区间中「完全覆盖区间的次数 `v[]`」（类似不用下放的懒惰标记）和「已覆盖的长度 `w[]`」两个信息．

需要 [离散化](../misc/discrete.md)．

??? note "[洛谷 P5490【模板】扫描线 & 矩形面积并](https://www.luogu.com.cn/problem/P5490) 参考代码"
    ```cpp
    #include <algorithm>
    #include <iostream>

    using ll = long long;
    constexpr int N = 1e5 + 1;

    int n, a[N * 2], tot;   // a[] 和 tot 用于把 x 离散化
    ll v[N * 8], w[N * 8];  // 完全覆盖区间的次数、已覆盖的长度

    struct St {
      ll x1, x2, y, o;
    } b[N * 2];  // 矩形上下边缘

    int f(int y) {  // 离散化，把坐标映射到 a 中的下标
      return std::lower_bound(a, a + tot, y) - a;
    }

    void up(int u, int ul, int ur) {  // pushup
      if (v[u]) w[u] = a[ur] - a[ul];
      // 如果对叶子节点调用 w[u*2+1]，那么线段树需要开 8 倍空间
      // 乘上矩形上下两边就是 16 倍
      else if (ul + 1 == ur)
        w[u] = 0;
      else
        w[u] = w[u * 2 + 1] + w[u * 2 + 2];
    }

    void add(int lf, int rg, ll o, int u = 0, int ul = 0, int ur = tot - 1) {
      // 区间加
      if (lf == ul && rg == ur) return v[u] += o, up(u, ul, ur), void();
      int um = (ul + ur) / 2;
      if (lf < um) add(lf, std::min(rg, um), o, u * 2 + 1, ul, um);
      if (um < rg) add(std::max(lf, um), rg, o, u * 2 + 2, um, ur);
      up(u, ul, ur);
    }

    int main() {
      std::cin >> n;
      for (int i = 0, x1, x2, y1, y2; i < n; i++) {
        // y1 是局部变量不会重名
        std::cin >> x1 >> y1 >> x2 >> y2;
        b[i] = {x1, x2, y1, 1};
        b[i + n] = {x1, x2, y2, -1};
        a[i] = x1, a[i + n] = x2;
      }

      std::sort(a, a + n * 2), tot = 1;
      for (int i = 1; i < n * 2; i++)
        if (a[i] != a[tot - 1]) a[tot++] = a[i];  // 离散化

      std::sort(b, b + n * 2,
                [](St &i, St &j) -> bool { return i.y < j.y; });  // 操作排序

      ll sum = 0;
      add(f(b[0].x1), f(b[0].x2), 1);
      for (int i = 1; i < n * 2; i++) {
        int x1 = f(b[i].x1), x2 = f(b[i].x2);
        sum += (b[i].y - b[i - 1].y) * w[0];  // 对每个小矩形面积求和
        add(x1, x2, b[i].o);
      }
      std::cout << sum << '\n';
    }
    ```

??? note "[「POJ 1151」Atlantis](http://poj.org/problem?id=1151) 参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    constexpr int MAXN = 300;
    using namespace std;

    int lazy[MAXN << 3];  // 标记了这条线段出现的次数
    double s[MAXN << 3];

    struct node1 {
      double l, r;
      double sum;
    } cl[MAXN << 3];  // 线段树

    struct node2 {
      double x, y1, y2;
      int flag;
    } p[MAXN << 3];  // 坐标

    // 定义sort比较
    bool cmp(node2 a, node2 b) { return a.x < b.x; }

    // 上传
    void pushup(int rt) {
      if (lazy[rt] > 0)
        cl[rt].sum = cl[rt].r - cl[rt].l;
      else
        cl[rt].sum = cl[rt * 2].sum + cl[rt * 2 + 1].sum;
    }

    // 建树
    void build(int rt, int l, int r) {
      if (r - l > 1) {
        cl[rt].l = s[l];
        cl[rt].r = s[r];
        build(rt * 2, l, (l + r) / 2);
        build(rt * 2 + 1, (l + r) / 2, r);
        pushup(rt);
      } else {
        cl[rt].l = s[l];
        cl[rt].r = s[r];
        cl[rt].sum = 0;
      }
      return;
    }

    // 更新
    void update(int rt, double y1, double y2, int flag) {
      if (cl[rt].l == y1 && cl[rt].r == y2) {
        lazy[rt] += flag;
        pushup(rt);
        return;
      } else {
        if (cl[rt * 2].r > y1) update(rt * 2, y1, min(cl[rt * 2].r, y2), flag);
        if (cl[rt * 2 + 1].l < y2)
          update(rt * 2 + 1, max(cl[rt * 2 + 1].l, y1), y2, flag);
        pushup(rt);
      }
    }

    int main() {
      int temp = 1, n;
      double x1, y1, x2, y2, ans;
      while (scanf("%d", &n) && n) {
        ans = 0;
        for (int i = 0; i < n; i++) {
          scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
          p[i].x = x1;
          p[i].y1 = y1;
          p[i].y2 = y2;
          p[i].flag = 1;
          p[i + n].x = x2;
          p[i + n].y1 = y1;
          p[i + n].y2 = y2;
          p[i + n].flag = -1;
          s[i + 1] = y1;
          s[i + n + 1] = y2;
        }
        sort(s + 1, s + (2 * n + 1));  // 离散化
        sort(p, p + 2 * n, cmp);  // 把矩形的边的横坐标从小到大排序
        build(1, 1, 2 * n);       // 建树
        memset(lazy, 0, sizeof(lazy));
        update(1, p[0].y1, p[0].y2, p[0].flag);
        for (int i = 1; i < 2 * n; i++) {
          ans += (p[i].x - p[i - 1].x) * cl[1].sum;
          update(1, p[i].y1, p[i].y2, p[i].flag);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", temp++, ans);
      }
      return 0;
    }
    ```

### 练习

-   [「POJ1177」Picture](http://poj.org/problem?id=1177)
-   [「POJ3832」Posters](http://poj.org/problem?id=3832)
-   [洛谷 P1856 \[IOI1998\] \[USACO5.5\] 矩形周长 Picture](https://www.luogu.com.cn/problem/P1856)
    -   横边贡献就是覆盖长度变化量．
    -   两个方向分别算一次可以避免竖直边的讨论．
    -   操作排序时注意考虑两个矩形边重合的情况．
    -   数据范围允许不用线段树，直接平方时间模拟．

## B 维正交范围

B 维正交范围指在一个 B 维直角坐标系下，第 $i$ 维坐标在一个整数范围 $[l_i,r_i]$ 间，内部的点集．

一般来说，一维正交范围简称区间，二维正交范围简称矩形，三维正交范围简称立方体（我们常说的二维数点就是二维正交范围）．

对于一个静态的二维问题，我们可以使用扫描线扫一维，数据结构维护另一维．
在扫描线从左到右扫的过程中，会在数据结构维护的那一维上产生一些修改与查询．
如果查询的信息可差分的话直接使用差分，否则需要使用分治．差分一般用树状数组和线段树维护，但因为树状数组好写而且常数小，所以大部分人会选择用树状数组来维护．分治一般是 CDQ 分治（但是这里不涉及分治）．

另一种比较容易理解的看待问题的角度是站在序列角度，而不站在二维平面角度．如果我们这样看待问题，则扫描线实际上是枚举了右端点 $r=1\cdots n$，维护一个数据结构，支持查询对于当前的 $r$，给定一个值 $l$，$l$ 到 $r$ 的答案是什么．即扫描线扫询问右端点，数据结构维护所有左端点的答案，或者说遍历一维，数据结果维护另一维．

复杂度一般为 $O((n+m)\log n)$．

## 二维数点

给一个长为 $n$ 的序列，有 $m$ 次查询，每次查区间 $[l,r]$ 中值在 $[x,y]$ 内的元素个数．

这个问题就叫做二维数点．我们可以发现等价于我们要查询一个二维平面上矩形内的点的数量和．这里讲一下这个问题最简单的处理方法，扫描线 + 树状数组．

很显然，这个问题是一个静态的二维问题，我们通过扫描线可以将静态的二维问题转换为动态的一维问题．维护动态的一维问题就使用数据结构维护序列，这里可以使用树状数组．

先将所有的询问离散化，用树状数组维护权值，对于每次询问的 $l$ 和 $r$，我们在枚举到 $l-1$ 时统计当前位于区间 $[x,y]$ 内的数的数量 $a$，继续向后枚举，枚举到 $r$ 时统计当前位于区间 $[x,y]$ 内的数的数量 $b$，$b-a$ 即为该次询问的答案．

### 例题

???+ note "[洛谷 P2163 \[SHOI2007\] 园丁的烦恼](https://www.luogu.com.cn/problem/P2163)"
    首先离散化．设一个左下角为 $(0, 0)$，右上角为 $(x, y)$ 的矩形内包含 $ans_{x, y}$ 个点．则询问的答案可以被差分为 $ans_{c, d} - ans_{a - 1, d} - ans_{c, b - 1} + ans_{a - 1, b - 1}$．
    
    ??? note "代码"
        ```cpp
        #include <algorithm>
        #include <iostream>

        int n, m;
        int x[500010], y[500010], ans[500010];
        int ax[1500010], ay[1500010], tx, ty;  // 离散化

        struct query {
          int a, b, c, d;
        } q[500010];  // 保存查询操作方便离散化

        struct ope {
          int type, x, y, id;

          ope(int type = 0, int x = 0, int y = 0, int id = 0) {
            this->type = type, this->x = x, this->y = y, this->id = id;
          }

          bool operator<(const ope& rhs) const {
            if (x == rhs.x) return type < rhs.type;
            return x < rhs.x;
          }
        };

        ope op[2500010];
        int tot;  // 操作总数

        int sum[1500010];  // 树状数组

        int lowbit(int x) { return x & (-x); }

        void add(int x, int k) {
          while (x <= 1500000) {
            sum[x] = sum[x] + k;
            x = x + lowbit(x);
          }
        }

        int getsum(int x) {
          int ret = 0;
          while (x > 0) {
            ret = ret + sum[x];
            x = x - lowbit(x);
          }
          return ret;
        }

        using std::cin;
        using std::cout;

        int main() {
          cin.tie(nullptr)->sync_with_stdio(false);
          cin >> n >> m, tx = n, ty = n;
          for (int i = 1; i <= n; i++) cin >> x[i] >> y[i], ax[i] = x[i], ay[i] = y[i];
          for (int i = 1, l, r; i <= m; i++) {
            cin >> q[i].a >> q[i].b >> q[i].c >> q[i].d;
            ax[++tx] = q[i].a, ay[++ty] = q[i].b, ax[++tx] = q[i].c, ay[++ty] = q[i].d;
          }
          std::sort(ax + 1, ax + tx + 1), std::sort(ay + 1, ay + ty + 1);
          tx = std::unique(ax + 1, ax + tx + 1) - ax - 1;
          ty = std::unique(ay + 1, ay + ty + 1) - ay - 1;
          for (int i = 1; i <= n; i++) {
            x[i] = std::lower_bound(ax + 1, ax + tx + 1, x[i]) - ax;
            y[i] = std::lower_bound(ay + 1, ay + ty + 1, y[i]) - ay;
            op[++tot] = ope(0, x[i], y[i], i);  // 加点操作
          }
          for (int i = 1; i <= m; i++) {
            q[i].a = std::lower_bound(ax + 1, ax + tx + 1, q[i].a) - ax;
            q[i].b = std::lower_bound(ay + 1, ay + ty + 1, q[i].b) - ay;
            q[i].c = std::lower_bound(ax + 1, ax + tx + 1, q[i].c) - ax;
            q[i].d = std::lower_bound(ay + 1, ay + ty + 1, q[i].d) - ay;
            op[++tot] = ope(1, q[i].c, q[i].d, i);  // 将查询差分
            op[++tot] = ope(1, q[i].a - 1, q[i].b - 1, i);
            op[++tot] = ope(2, q[i].a - 1, q[i].d, i);
            op[++tot] = ope(2, q[i].c, q[i].b - 1, i);
          }
          std::sort(op + 1, op + tot + 1);  // 将操作按横坐标排序，且优先执行加点操作
          for (int i = 1; i <= tot; i++) {
            if (op[i].type == 0)
              add(op[i].y, 1);
            else if (op[i].type == 1)
              ans[op[i].id] += getsum(op[i].y);
            else
              ans[op[i].id] -= getsum(op[i].y);
          }
          for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
          return 0;
        }
        ```

???+ note "[洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)"
    没错，逆序对也可以用扫描线的思维来做．考虑将求逆序对的个数转化为从后向前枚举每个位置 $i$，求在区间 $[i+1,n]$ 中，大小在区间 $[0,a_i]$ 中的点的个数．题目中数据范围为 $10^9$，很显然要先进行离散化，我们可以考虑从后向前遍历数组，每次遍历到一个数时更新树状数组（线段树），之后统计当前一共有多少个数小于当前枚举的数，因为我们是从后向前遍历的，所以比当前值小的数的个数就是他的逆序对的个数，可以用树状数组或线段树进行单点修改和区间查询．
    
    ??? note "代码"
        ```cpp
        #include <algorithm>
        #include <iostream>
        using ll = long long;
        using namespace std;

        struct node {
          ll data;
          ll num;
        } f[500010];

        ll n, ans, a[500010];

        bool cmp(node a, node b) {
          if (a.data == b.data) {
            return a.num < b.num;
          }
          return a.data < b.data;
        }

        ll sum[500010];

        int lowbit(int x) { return x & (-x); }

        void add(int x, int k) {
          while (x <= n) {
            sum[x] = sum[x] + k;
            x = x + lowbit(x);
          }
        }

        int getsum(int x) {
          int ret = 0;
          while (x > 0) {
            ret = ret + sum[x];
            x = x - lowbit(x);
          }
          return ret;
        }

        int main() {
          cin >> n;
          for (ll i = 1; i <= n; i++) {
            cin >> f[i].data;
            f[i].num = i;
          }
          sort(f + 1, f + 1 + n, cmp);
          for (int i = 1; i <= n; i++) {
            a[f[i].num] = i;
          }
          for (ll i = n; i > 0; i--) {
            ans += getsum(a[i]);
            add(a[i], 1);
          }
          cout << ans;
          return 0;
        }
        ```

???+ note "[洛谷 P1972 \[SDOI2009\] HH 的项链](https://www.luogu.com.cn/problem/P1972)"
    简要题意：给定一个序列，多次询问区间 $[l,r]$ 中有多少种不同的数．
    
    这类问题我们可以考虑推导性质，之后使用扫描线枚举所有右端点，数据结构维护每个左端点的答案的方法来实现，我们也可以将问题转换到二维平面上，变为一个矩形查询信息的问题．
    
    在本题中，我们设序列中 $a_i$ 上一次出现的位置为 $pre_i$，如果 $a_i$ 没有出现过，则 $pre_i = 0$．根据题意，如果一种数在区间中出现多次，只会产生一次贡献．不妨认为每种数产生贡献的位置是区间中第一次出现的位置，这时可以发现，产生的总贡献即为 $pre_x \le l - 1$ 的个数，反证法易证．
    
    现在问题即为：给定一个序列 $pre$，多次查询区间 $[l,r]$ 中有多少个 $pre_i \le l - 1$．
    
    我们可以把 $pre_i$ 看成二维平面的点：$i$ 是横坐标，$pre_i$ 是纵坐标，问题就转化为了二维数点问题：每次询问左下角为 $(l,0)$，右上角为 $(r,l - 1)$ 的矩形中有几个点．
    
    注意到这个询问是可差分的，我们可以将询问差分为左下角为 $(0,0)$，右上角为 $(r,l - 1)$ 的矩形减去左下角为 $(0,0)$，右上角为 $(l - 1,l - 1)$ 的矩形有几个点，这样方便我们使用扫描线思想．
    
    单次操作复杂度 $O(\log n)$，共有 $n$ 次加点操作和 $2m$ 次查询操作，总时间复杂度 $O((n + m) \log n)$．
    
    ??? note "代码"
        ```cpp
        #include <algorithm>
        #include <iostream>

        int n, m, a[1000010], ans[1000010];
        int pre[1000010], lst[1000010];  // 处理 pre

        struct ope {
          int type, x, y, id;

          ope(int type = 0, int x = 0, int y = 0, int id = 0) {
            this->type = type, this->x = x, this->y = y, this->id = id;
          }

          bool operator<(const ope& rhs) const {
            if (x == rhs.x) return type < rhs.type;
            return x < rhs.x;
          }
        };

        ope op[2500010];
        int tot;  // 操作总数

        int sum[1000010];  // 树状数组

        int lowbit(int x) { return x & (-x); }

        void add(int x, int k) {
          x++;  // 位置 0 也要进行修改，所以树状数组下标均加 1
          while (x <= n) {
            sum[x] = sum[x] + k;
            x = x + lowbit(x);
          }
        }

        int getsum(int x) {
          x++;
          int ret = 0;
          while (x > 0) {
            ret = ret + sum[x];
            x = x - lowbit(x);
          }
          return ret;
        }

        using std::cin;
        using std::cout;

        int main() {
          cin.tie(nullptr)->sync_with_stdio(false);
          cin >> n;
          for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = lst[a[i]], lst[a[i]] = i;  // 处理 pre
            op[++tot] = ope{0, i, pre[i], i};   // 加点操作
          }
          cin >> m;
          for (int i = 1, l, r; i <= m; i++) {
            cin >> l >> r;
            op[++tot] = ope{1, r, l - 1, i};  // 将查询差分
            op[++tot] = ope{2, l - 1, l - 1, i};
          }
          std::sort(op + 1, op + tot + 1);  // 将操作按横坐标排序，且优先执行加点操作
          for (int i = 1; i <= tot; i++) {
            if (op[i].type == 0)
              add(op[i].y, 1);
            else if (op[i].type == 1)
              ans[op[i].id] += getsum(op[i].y);
            else
              ans[op[i].id] -= getsum(op[i].y);
          }
          for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
          return 0;
        }
        ```

### 练习

-   [洛谷 P8593「KDOI-02」一个弹的投](https://www.luogu.com.cn/problem/P8593) 逆序对的应用．
-   [AcWing 4709. 三元组](https://www.acwing.com/problem/content/4712/) 上题的弱化版，同样为逆序对的应用．
-   [洛谷 P8773 \[蓝桥杯 2022 省 A\] 选数异或](https://www.luogu.com.cn/problem/P8773) HH 的项链魔改版．
-   [洛谷 P8844 \[传智杯 #4 初赛\] 小卡与落叶](https://www.luogu.com.cn/problem/P8844) 树上问题转序列问题然后进行二维数点．

总而言之，二维数点的主要思路就是数据结构维护一维，然后枚举另一维．

## 参考资料

-   [cnblogs/Yang1208：扫描线讲解，动态开点版线段树](https://www.cnblogs.com/yangsongyi/p/8378629.html)
-   [csdn/riba2534：POJ1151 Atlantis 题解](https://blog.csdn.net/riba2534/article/details/76851233)
-   [csdn/刀刀狗 0102：POJ1151 Atlantis 题解](https://blog.csdn.net/winddreams/article/details/38495093)
-   [浅谈扫描线](https://www.luogu.com.cn/article/f8q5bmnz)
