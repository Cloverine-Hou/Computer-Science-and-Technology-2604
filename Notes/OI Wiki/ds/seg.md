author: Ir1d, hsfzLZH1, Tiphereth-A, ksyx, Marcythm, StudyingFather, Xeonacid, ChungZH, Early0v0, chenryang, Enter-tainer, CCXXXI, cjsoft, HeRaNO, konnyakuxzy, NachtgeistW, orzAtalod, wy-luke, amlhdsan, billchenchina, c-forrest, Chrogeek, countercurrent-time, ethan-enhe, GavinZhengOI, H-J-Granger, iamtwz, luoguojie, AKindMouse, AngelKitty, chenzheAya, CJSoft, DawnMagnet, diauweb, ezoixx130, GekkaSaori, Gesrua, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, Konano, kxccc, LovelyBuggies, lychees, Makkiy, megakite, Menci, mgt, minghu6, moon-dim, onelittlechildawa, ouuan, P-Y-Y, Peanut-Tang, PotassiumWings, SamZhangQingChuan, shadowice1984, shawlleyw, shuzhouliu, sshwy, SukkaW, Suyun514, weiyong1024, x2e6, Ycrpro, yifan0305, zeningc

## 引入

线段树是算法竞赛中常用的用来维护 **区间信息** 的数据结构．

线段树可以在 $O(\log N)$ 的时间复杂度内实现单点修改、单点查询、区间修改、区间查询等操作．

## 基本结构与操作

线段树是一棵二叉树．它的每个结点都存储一段区间的信息：

-   叶结点处存储的是单个元素 $x$ 处的信息，也可以看作是长度为 $1$ 的区间 $[x,x]$ 上的信息．
-   以非叶结点为根的子树的叶结点构成一段连续的区间 $[l,r]$．那么，该结点处就存储区间 $[l,r]$ 上的信息．

非叶结点总有两个子结点，它对应的区间就恰为这两个子结点对应区间的不交并．设某个非叶结点存储区间 $[l,r]~(l < r)$ 上的信息，那么，它的两个子结点存储的就分别是 $[l,m]$ 和 $[m+1,r]$ 上的信息，其中，$l \le m < r$．

线段树的根结点处就存储着整段区间 $[L,R]$ 上的信息．线段树的规模用该区间的长度 $N = R - L + 1$ 表示．

### 区间信息

线段树可以维护区间信息．本节介绍区间信息需要满足的常见性质以及相应的实现方法．

一般地，**区间信息** 是以区间为自变量的函数 $\varphi:\mathcal I\rightarrow M$，其中，$\mathcal I$ 表示 $[L,R]$ 的所有子区间（包括空区间），$M$ 表示区间信息可以取值的空间——本文称 **信息空间**．线段树存储的区间信息 $\varphi$ 需要满足如下性质：

1.  将一段区间划分成两段子区间，相应的信息也可以从子区间信息合并得到．也就是说，如果设 $I$ 是 $I_1$ 和 $I_2$ 的不交并，且 $I_1$ 位于 $I_2$ 左侧，那么 $\varphi(I)=\varphi(I_1)\circ\varphi(I_2)$，其中，运算 $\circ$ 表示 **信息合并** 操作．
2.  将一段区间划分为多段子区间的不交并，这些子区间信息合并的结果与划分和结合的方式都无关，都等于最开始一段区间的信息．也就是说，运算 $\circ$ 满足结合律．
3.  空区间 $\varnothing$ 也有良定义的信息 $e=\varphi(\varnothing)$．而且，因为任何区间 $I$ 都可以看作是它自身与空区间 $\varnothing$ 的不交并，所以任何区间信息与空区间信息的合并都保持不变．也就是说，$\varphi(I)\circ e = e\circ\varphi(I) = \varphi(I)$．这说明 $e$ 是运算 $\circ$ 的单位元．

这些性质保证，要查询区间 $I$ 对应的信息时，只要能够找到一系列结点，使得它们对应的区间构成 $I$ 的划分，就能从这些结点存储的信息中合并出区间 $I$ 的信息．

区间信息可以合并，合并操作满足结合律，且存在单位元．这些性质意味着信息空间 $M$ 在信息合并操作 $\circ$ 下构成一个 [幺半群](../math/algebra/basic.md#群)．[^monoid]

???+ info "约定"
    在给出线段树操作的参考实现时，本文假设信息空间 $M$ 的元素存储在 `Info` 结构体中，它的默认构造得到单位元，且它重载了加法运算符用于实现信息合并操作．

???+ example "例子"
    满足幺半群性质的区间信息有很多．区间长度、区间和、区间乘积、区间最大值都是一些简单的例子．它们对应的幺半群分别是 $(\mathbf N,+),~(\mathbf R,+),~(\mathbf R,\times),~(\mathbf R\cup\{-\infty\},\max)$，对应的单位元则分别是 $0,0,1,-\infty$．这些例子可以拓展到其他常见的符合幺半群性质的操作，例如按位取异或、矩阵乘法、函数复合等．
    
    还有一些更为复杂的例子．例如，区间最大（非空）子段和同样可以通过幺半群来维护．当然，如果只维护最大子段和这一个变量，是无法进行合并操作的．对于划分 $I = I_1 \cup I_2$，区间 $I$ 的最大子段和可能在区间 $I_1$ 的子区间处取得，可能在区间 $I_2$ 的子区间处取得，也可能在某个横跨 $I_1$ 和 $I_2$ 的子区间处取得．为了计算最后一种情况对应的最大值，需要分别记录区间和、区间最大（非空）前缀和、区间最大（非空）后缀和．
    
    === "区间和"
        ```cpp
        // Sum.
        struct Info {
          long long sum;

          Info(long long x = 0) : sum(x) {}

          Info operator+(const Info& o) const { return Info(sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        ```
    
    === "区间最大值（值域非负）"
        ```cpp
        // Range max; -1 marks the empty interval.
        struct Info {
          int ma;

          Info(int _ma = -1) : ma(_ma) {}

          Info operator+(const Info& o) const { return Info(std::max(ma, o.ma)); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        ```
    
    === "一次函数"
        ```cpp
        // Affine function: f(x) = ax + b.
        // Composition: (f1 + f2)(x) = f2(f1(x)).
        // Identity: e(x) = x.
        struct Info {
          int a, b;

          Info(int _a = 1, int _b = 0) : a(_a), b(_b) {}

          Info operator+(const Info& o) const {
            return Info((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
          }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        ```
    
    === "区间最大非空子段和"
        ```cpp
        // Maximum (non-empty) subarray sum
        struct Info {
          int sum;  // sum of the whole interval
          int lma;  // maximum sum of a non-empty prefix
          int rma;  // maximum sum of a non-empty suffix
          int ma;   // maximum sum of a non-empty subarray

          Info() : sum(0), lma(-1e9), rma(-1e9), ma(-1e9) {}

          Info(int x) : sum(x), lma(x), rma(x), ma(x) {}

          Info(int _s, int _l, int _r, int _m) : sum(_s), lma(_l), rma(_r), ma(_m) {}

          Info operator+(const Info& o) const {
            return Info(sum + o.sum, std::max(lma, sum + o.lma),
                        std::max(rma + o.sum, o.rma),
                        std::max(std::max(ma, o.ma), rma + o.lma));
          }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        ```

需要注意的是，区间信息的合并未必满足交换律．当执行合并操作时，需要严格按照子区间的顺序从左向右进行．

### 递归建树与存储方式

为了尽可能地减小树高，需要将当前结点的区间 $[l,r]$ 尽可能均匀地分成两段．为此，常选取

$$
m = \left\lfloor\dfrac{l + r}{2}\right\rfloor.
$$

这样，如果当前结点区间长度为 $n > 1$，它的两个子结点 $[l,m]$ 和 $[m+1,r]$ 就分别对应长度为 $\lceil n/2\rceil$ 和 $\lfloor n/2\rfloor$ 的区间．由此得到的线段树高度是 $\lceil\log_2N\rceil$．这就保证了线段树是平衡二叉树，单点操作的复杂度总是 $O(\log N)$ 的．

![](images/seg-1.svg)

存储长度为 $N$ 的区间上的信息，需要建立有 $N$ 个叶结点的线段树．作为完整二叉树（即每个结点都有 $0$ 或 $2$ 个子结点），线段树恰有 $2N-1$ 个存储信息的结点．也就是说，这样构造的线段树空间复杂度是 $\Theta(N)$ 的；递归建树时每个结点恰好访问一次，时间复杂度也是 $\Theta(N)$ 的．

虽然线段树的结构相对固定，但是它的存储方式却并不唯一．

![](images/seg-2.svg)

第一种常见的方式是堆式存储（如上图所示），即将线段树嵌入完美二叉树中．此时，根结点编号为 $1$；如果当前结点编号是 $i$，那么它的左右子结点编号分别是 $2i$ 和 $2i+1$．因为树高为 $\lceil\log_2N\rceil$，所以这样存储线段树需要开长度为 $2^{\lceil\log_2N\rceil + 1}$ 的数组．为计算简便，通常会直接开长度为 $4N$ 的数组[^heap-size]；或者将 $N$ 补齐为 $2$ 的幂次 $N'$ 后，开长度为 $2N'$ 的数组．这样存储的长处是无需额外存储子结点编号，短处则是存在部分无用结点，空间利用效率不高．

![](images/seg-3.svg)

第二种常见的方式是利用内存池，动态地指定结点编号．因为线段树形态固定，只要在建树的时候分配一次结点编号即可．这样做保证了没有无用结点，只需要开出长度为 $2N$ 的数组．此时，结点编号是线段树前序遍历的序号．但是，由于（右）子结点的编号无法仅由当前结点编号计算[^child-id]，通常会额外分配总长度为 $4N$ 的数组存储左右子结点编号．如果设存储单个编号需要的空间为 $1$，存储单个结点需要的空间为 $K$，那么，只要 $2NK + 4N \le 4NK$，即 $K \ge 2$ 时，动态分配的空间占用就不会劣于堆式存储．

这两种存储和建立线段树的方式实现如下：

???+ example "参考实现"
    === "堆式存储"
        ```cpp
        // Recursive structure, stored in heap.
        #define lc(x) ((x) << 1)
        #define rc(x) (((x) << 1) | 1)

        int rt, L, R;
        std::vector<Info> val;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr), ll, mm, vec);
          build(rc(cr), mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, L = l, R = r;
          val.resize((R - L + 1) << 2);
          build(rt, L, R, vec);
        }

        ```
    
    === "动态分配结点"
        ```cpp
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        ```

???+ tip "提示"
    1.  计算区间 $[l,r]$ 中点 $m = \lfloor(l+r)/2\rfloor$ 时，使用 `m = l + (r - l) / 2` 而不是 `m = (l + r) / 2` 可以避免整型溢出和负数除法向零取整等问题．
    2.  通常可以实现一个 `push_up` 函数用于将子结点信息合并到当前结点．

除了访问子结点的方法有所差异外，存储方式的选取不会影响建树后线段树操作的实现．但是，堆式存储中结点编号由它在完美二叉树中的位置决定，拓展性较差，无法支持动态开点和可持久化等拓展．

### 单点修改与查询

线段树操作中，最简单的就是单点操作．

首先考虑单点查询操作．线段树中，叶结点存储的元素是有序排列的．所以，当递归到非叶结点时，只需要比较要查询的元素和当前区间中点，就可以决定继续访问左子结点还是右子结点．当找到叶结点时，返回该叶结点处存储的信息即可．这就完成了单点查询操作．

???+ example "参考实现"
    ```cpp
    // Query info at x.
    Info query(int cr, int ll, int rr, int x) {
      if (ll == rr) return val[cr];
      int mm = ll + ((rr - ll) >> 1);
      if (x <= mm)
        return query(lc(cr), ll, mm, x);
      else
        return query(rc(cr), mm + 1, rr, x);
    }

    Info query(int x) { return query(rt, L, R, x); }

    ```

单点修改操作类似．同样是自上而下地找到要访问的叶结点．然后，对该叶结点进行修改操作．最后，还需要在回溯时，相应地更新该叶结点的所有祖先结点的信息．这就是单点修改操作．由于所有对单点的修改操作都可以看作是将它的值进行替换，所以这里仅提供了更改值的参考实现．[区间修改操作](#区间修改与懒惰标记) 一节讨论了更一般的修改操作．

???+ example "参考实现"
    ```cpp
    // Modify info at x to v.
    void modify(int cr, int ll, int rr, int x, const Info& v) {
      if (ll == rr) return (void)(val[cr] = v);
      int mm = ll + ((rr - ll) >> 1);
      if (x <= mm)
        modify(lc(cr), ll, mm, x, v);
      else
        modify(rc(cr), mm + 1, rr, x, v);
      push_up(cr);
    }

    void modify(int x, const Info& v) { modify(rt, L, R, x, v); }

    ```

由于树高是 $\Theta(\log N)$ 的，线段树的单点操作都是 $O(\log N)$ 的．

### 区间查询

接下来，考虑区间查询操作．

![](images/seg-5.svg)

前文已经说明，只要将要查询的区间拆分成若干个线段树结点对应的区间的不交并，然后将这些结点处的信息依次合并到一起即可．当然，拆分出的结点越少越好．这就要求拆分出的结点对应的是包含在查询区间内的 **极大区间**．上图中，浅色区域标出操作区间，粗边结点对应极大区间．要找到这些极大区间对应结点也很容易：从根结点开始，向下搜索所有对应区间与查询区间相交的结点；当搜索到一个完全包含于查询区间内的结点时，就找到了一个极大区间所对应的结点，因而无需继续搜索该结点的子孙结点．

???+ example "参考实现"
    ```cpp
    // Query info in [l, r].
    Info query(int cr, int ll, int rr, int tl, int tr) {
      if (tl <= ll && rr <= tr) return val[cr];
      int mm = ll + ((rr - ll) >> 1);
      Info res;
      if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
      if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
      return res;
    }

    Info query(int l, int r) { return query(rt, L, R, l, r); }

    ```

???+ tip "提示"
    1.  除了上述实现方式外，还可以在向下搜索到与查询区间不交的区间结点时终止搜索．
    2.  由于结果初始化为信息空间 $M$ 中的单位元，左子结点返回结果可以直接覆盖，无需进行信息合并．

可以说明，在区间查询过程中访问的所有结点——所有极大区间结点及其祖先结点——的总数是 $O(\log N)$ 的．因此，区间查询的复杂度也是 $O(\log N)$ 的．

??? note "证明"
    进行区间查询时，访问到的每个非根结点，其父结点对应区间必然包含查询区间左端点或右端点．如果不然，父结点对应区间要么完全包含在查询区间内，要么与查询区间不交，都不应该继续访问其子结点（即当前结点）．而且，相同深度的结点对应区间两两不交，包含左、右端点的各至多 $1$ 个，而每个结点至多有 $2$ 个子结点．所以，区间查询时访问到的相同深度结点，至多只有 $4$ 个．线段树高度是 $\Theta(\log N)$ 的，区间查询所访问到的结点数目就也是 $O(\log N)$ 的．

### 区间修改与懒惰标记

最后，考虑区间修改操作．

与区间查询操作不同的是，区间修改操作的影响并不局限于极大区间结点及其祖先结点，还会波及其子孙结点．这是因为区间修改操作会影响这些极大区间的子区间，也就是相应结点的子孙结点．如果要修改区间波及的所有结点，复杂度显然过高，并不现实．因此，实现区间修改操作时，利用了 **懒惰标记**（lazy tag）的思想．具体地，每次区间修改操作仅实际修改极大区间结点及其祖先结点，而对极大区间结点子孙结点的修改则推迟到有必要的时候再进行．为了记录后续需要进行的修改操作，还需要在极大区间结点处留下一个标记．这个标记记录了对其子孙结点（不包括自身）需要进行但是尚未进行的操作．它就是懒惰标记．

???+ info "约定"
    本文假定，带有懒惰标记的结点自身的修改已经完成．这并非强制要求，可能会因实现而异．

在支持区间修改操作的线段树中，其他操作的实现也需要相应调整．进行任何操作时，每当需要访问某结点的子结点时，都要检查当前结点是否存在尚未清空的懒惰标记．如果存在，需要先下传该懒惰标记，再继续访问子结点或进行其他操作．所谓下传懒惰标记，就是指对该结点的子结点进行相应修改操作，同时给相应的子结点打上懒惰标记，最后清空当前结点处的标记．

???+ example "示例"
    下图展示了由数组 $[4,1,3,2,5]$ 建立的线段树结构．
    
    ![](images/seg-lazy-1.svg)
    
    每个结点处，$s$ 表示当前区间的元素和，$t$ 是懒惰标记，用于实现区间加操作．初始时，所有区间元素和都是正确的，且懒惰标记均为空．现在，将区间 $[2,5]$ 中的所有元素都加 $2$，所得结果如下图所示．
    
    ![](images/seg-lazy-2.svg)
    
    图中，浅色区域标出操作区间，粗边结点对应极大区间．在这些极大区间结点处，元素和 $s$ 增加了区间长度的 $2$ 倍，正确反映了区间加操作带来的变化；同时懒惰标记增加了 $2$，表示其子孙结点尚未更新．极大区间结点的祖先结点则从其子结点处获得了更新后的元素和．此时若再查询区间 $[4,4]$ 的元素和，所得结果如下图所示．
    
    ![](images/seg-lazy-3.svg)
    
    在访问区间 $[4,4]$ 的过程中，会先访问区间 $[4,5]$，并注意到它带有懒惰标记 $t=2$．在访问其子结点之前，需要先下传懒惰标记：对其子结点各执行一次区间加 $2$，子结点的懒惰标记也增加 $2$，表示其子孙结点（尽管图中并不存在）尚未更新，最后清空 $[4,5]$ 处的标记．下传之后，再继续访问子结点区间 $[4,4]$，就能读取到正确的元素和 $4$ 了．

在执行区间修改操作或下传懒惰标记时，要标记的结点可能已经存在未清空的懒惰标记．此时，不能够直接覆盖标记，而需要将标记更新为两次操作复合的结果．由于操作的复合未必满足交换律，复合时需要注意顺序：新的操作总是复合在原有标记之后．下传标记时，总是将父结点的标记复合在子结点原有标记之后．这是因为访问子结点前必然先下传标记，子结点原有标记被打上时，父结点必定不带标记；父结点现有的标记只可能来自之后的操作．

为了正确记录区间修改操作，需要理解这类操作需要满足的性质．仍然设线段树记录的区间信息可以总结为函数 $\varphi:\mathcal I\rightarrow M$．进一步地，设修改操作是 $\pi:M\rightarrow M$，它将旧信息依某种规则变化为新信息．那么，区间修改操作 $\pi$ 需要满足如下性质：

1.  它是良定义的．也就是说，区间修改的结果只与信息 $m\in M$ 有关，而与所处区间 $I\in\mathcal I$ 无关．对于区间修改结果涉及所处区间特征的情形，可以将区间特征（例如区间长度、左右端点等）视为区间信息的一部分．
2.  修改操作必须要与区间信息的合并相兼容．也就是说，如果某区间信息可以由子区间信息合并得到，那么对该区间进行修改操作得到的结果，仍然可以由对子区间信息进行修改操作得到的结果合并得到，亦即对于 $m_1,m_2\in M$，总是有 $\pi(m_1\circ m_2) = \pi(m_1)\circ\pi(m_2)$．
3.  特别地，规定空区间信息修改后仍然是空区间信息，即 $\pi(e)=e$．[^endo]

这说明，修改操作是幺半群 $M$ 上的 [自同态映射](../math/algebra/group-theory.md#群同态)．而且，考虑这些修改操作形成的集合 $\Pi$，只要它对映射复合封闭，由于映射复合满足结合律且恒等映射是单位元，$\Pi$ 也是一个幺半群．

???+ info "约定"
    在给出线段树操作的参考实现时，本文假设修改操作存储在 `Transform` 结构体中，默认构造得到恒等操作，它重载了加法运算符用于实现操作的复合，且它重载了括号运算符用于修改区间信息．为了方便判断懒惰标记是否为空（即不修改），还重载了到布尔值的显式类型转换．

???+ example "例子"
    线段树能支持的修改操作很多，区间加、区间乘、区间赋值、区间仿射变换都是常见的例子．实现的难点往往不在操作本身，而在于如何把它作用到区间信息上，也就是如何让它满足前文的三条性质．例如，维护区间和而要支持区间加时，增量对区间和的贡献是所加的数乘以区间长度，而区间长度并不在区间信息之中．此时，按第一条性质的做法，把区间长度也记入区间信息即可．
    
    === "区间最小值信息 & 区间加操作"
        ```cpp
        // Minimum.
        struct Info {
          long long mi;

          Info(long long _mi = LLONG_MAX) : mi(_mi) {}

          Info operator+(const Info& o) const { return Info(std::min(mi, o.mi)); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // Addition.
        struct Transform {
          long long x;

          Transform(long long _x = 0) : x(_x) {}

          explicit operator bool() const { return x != 0; }

          Transform operator+(const Transform& o) const { return Transform(x + o.x); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& v) const {
            return Info(v.mi == LLONG_MAX ? LLONG_MAX : v.mi + x);
          }
        };

        ```
    
    === "区间和信息 & 区间加操作"
        ```cpp
        // Interval length and sum of elements.
        struct Info {
          long long len, sum;

          Info(long long _len = 0, long long _sum = 0) : len(_len), sum(_sum) {}

          Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // Range add.
        struct Transform {
          long long v;

          Transform(long long _v = 0) : v(_v) {}

          explicit operator bool() const { return v != 0; }

          Transform operator+(const Transform& o) const { return Transform(v + o.v); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& x) const {
            return Info(x.len, x.sum + v * x.len);
          }
        };

        ```
    
    === "区间最大值信息 & 区间赋值操作"
        ```cpp
        // Range max; -1 marks the empty interval.
        struct Info {
          int ma;

          Info(int _ma = -1) : ma(_ma) {}

          Info operator+(const Info& o) const { return Info(std::max(ma, o.ma)); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // Assignment; -1 marks no assignment.
        struct Transform {
          int x;

          Transform(int _x = -1) : x(_x) {}

          explicit operator bool() const { return x != -1; }

          Transform operator+(const Transform& o) const { return o ? o : *this; }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& v) const {
            return *this && v.ma != -1 ? Info(x) : v;
          }
        };

        ```

在实现好用于存储区间修改操作的结构后，懒惰更新和下传懒惰标记的操作就可以实现如下：

???+ example "参考实现"
    ```cpp
    // Lazy update.
    void lazy_update(int cr, const Transform& f) {
      val[cr] = f(val[cr]);
      lazy[cr] += f;
    }

    // Push down lazy tag.
    void push_down(int cr) {
      if (!lazy[cr]) return;
      lazy_update(lc(cr), lazy[cr]);
      lazy_update(rc(cr), lazy[cr]);
      lazy[cr] = Transform();
    }

    ```

???+ tip "提示"
    1.  不要将懒惰标记打到空结点上．
    2.  如果实现得仔细，也可以不将懒惰标记打到叶结点上．

单次下传操作的复杂度通常是 $O(1)$ 的．

进而，区间修改操作就可以实现如下：

???+ example "参考实现"
    ```cpp
    // Apply transformation f to the range [l, r].
    void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
      if (tl <= ll && rr <= tr) return lazy_update(cr, f);
      push_down(cr);
      int mm = ll + ((rr - ll) >> 1);
      if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
      if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
      push_up(cr);
    }

    void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

    ```

和区间查询操作一样，带懒惰标记的线段树区间修改操作同样是 $O(\log N)$ 的．带懒惰标记的线段树的其他操作和不带懒惰标记的情形实现基本相同，只需要在访问子结点之前添加下传标记操作即可．由于单次操作至多下传 $O(\log N)$ 次标记，所以这些操作时间复杂度仍然是 $O(\log N)$，只是常数变大了．如果不涉及区间修改操作，通常选择实现不带懒惰标记的线段树，降低算法常数．

### 参考实现

下面给出不带懒惰标记和带懒惰标记的线段树的完整参考实现．

??? example "参考实现"
    === "不带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Recursive. No lazy tag.
        // --8<-- [start:build]
        // Recursive structure, stored in heap.
        #define lc(x) ((x) << 1)
        #define rc(x) (((x) << 1) | 1)

        int rt, L, R;
        std::vector<Info> val;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr), ll, mm, vec);
          build(rc(cr), mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, L = l, R = r;
          val.resize((R - L + 1) << 2);
          build(rt, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int cr, int ll, int rr, int x) {
          if (ll == rr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            return query(lc(cr), ll, mm, x);
          else
            return query(rc(cr), mm + 1, rr, x);
        }

        Info query(int x) { return query(rt, L, R, x); }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Modify info at x to v.
        void modify(int cr, int ll, int rr, int x, const Info& v) {
          if (ll == rr) return (void)(val[cr] = v);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            modify(lc(cr), ll, mm, x, v);
          else
            modify(rc(cr), mm + 1, rr, x, v);
          push_up(cr);
        }

        void modify(int x, const Info& v) { modify(rt, L, R, x, v); }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        ```
    
    === "带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Recursive. With lazy tag.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr) {
          if (!lazy[cr]) return;
          lazy_update(lc(cr), lazy[cr]);
          lazy_update(rc(cr), lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int cr, int ll, int rr, int x) {
          if (ll == rr) return val[cr];
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            return query(lc(cr), ll, mm, x);
          else
            return query(rc(cr), mm + 1, rr, x);
        }

        Info query(int x) { return query(rt, L, R, x); }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Apply transformation f to the value at x.
        void modify(int cr, int ll, int rr, int x, const Transform& f) {
          if (ll == rr) return (void)(val[cr] = f(val[cr]));
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            modify(lc(cr), ll, mm, x, f);
          else
            modify(rc(cr), mm + 1, rr, x, f);
          push_up(cr);
        }

        void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (tl <= ll && rr <= tr) return lazy_update(cr, f);
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        ```

具体应用时，可能需要判断修改和查询操作是否合法．

## 常用技巧

本节介绍用线段树解决具体问题时常用的几类技巧．它们或优化了算法常数，或丰富了基本功能．

### 非递归实现

前文介绍的递归实现的线段树，都只能自上而下地递归访问，需要支付相应的递归开销．另一种方法是自下而上地维护线段树．在国内竞赛资料中，这种实现因张昆玮介绍而广为流传，所以它也常称为 **zkw 线段树**．

![](images/seg-4.svg)

上图展示了非递归实现的存储方式．它仍然将线段树嵌入完美二叉树中，但改为自下而上建树．首先，将所有叶结点存储在深度为 $\lceil\log_2N\rceil$ 的同一层，多余的叶结点存储单位元 $e$，可以看作是空区间对应的信息．然后，自下而上遍历非叶结点，将子结点的信息合并到当前结点．由于所有叶结点都排在同一层，这样建立的线段树与前两种方式结构略有差异，但同样可以维护区间信息．空间上与堆式存储相同，需要长度为 $2^{\lceil\log_2N\rceil + 1}$ 的数组．

这种存储方式的最大好处是，叶结点编号连续，容易定位，且父子结点的编号都可以直接计算．如上图所示，若设 $n=2^{\lceil\log_2N\rceil}$，即把 $N$ 向上补齐到 $2$ 的幂，则元素 $x\in[L,R]$ 处的值就存储在编号为 $n+x-L$ 的结点处；对于编号为 $i$ 的非根结点，父结点编号是 $\lfloor i/2\rfloor$，更一般地，$d$ 级祖先结点的编号是 $\lfloor i/2^d\rfloor$；对于编号为 $i$ 的非叶结点，左右子结点编号分别是 $2i$ 和 $2i+1$．

根据这些特性，建树操作和单点操作都非常容易实现．建树操作只需要将元素对应信息拷贝到对应叶结点上，然后倒序遍历结点 $[1,n-1]$ 合并子结点信息即可．单点查询可以直接返回对应叶结点存储的信息．单点修改同样可以直接修改对应叶结点，同时还需要更新其祖先结点的信息．

???+ example "参考实现"
    ```cpp
    // Nonrecursive structure, embedded in a perfect binary tree.
    int n, L, R;
    std::vector<Info> val;

    void push_up(int cr) { val[cr] = val[cr << 1] + val[(cr << 1) | 1]; }

    // Build the tree based on info stored in vec (0-indexed).
    void build(int l, int r, const std::vector<Info>& vec) {
      L = l, R = r;
      for (n = 1; n < r - l + 1; n <<= 1);
      val.resize(n << 1);
      std::copy(vec.begin(), vec.end(), val.begin() + n);
      for (int i = n - 1; i; --i) push_up(i);
    }

    // Query info at x.
    Info query(int x) { return val[n + x - L]; }

    // Modify info at x to v.
    void modify(int x, const Info& v) {
      x = x - L + n;
      val[x] = v;
      for (x >>= 1; x; x >>= 1) push_up(x);
    }

    ```

![](images/seg-6.svg)

区间查询操作稍微复杂一些，需要找到区间 $[l,r]$ 在线段树上的所有极大区间结点．不妨暂且忽略查询区间右端点，先考虑左端点 $l$ 所在的极大区间．包含它的所有区间结点就是 $l$ 对应叶结点及其祖先．于是，从 $l$ 对应叶结点出发不断上跳，直到当前结点是其父结点的右子结点为止：此时父结点还包含当前结点左侧的元素，而它们并不属于尚未统计的部分，所以当前结点对应的区间就是 $l$ 所在的极大区间．累计它的信息后，在同一层向右移动一个结点，再跳到父结点，就得到尚未统计的最左元素所在的结点，重复上述操作即可．对于右端点的处理是对称的．实际实现时需要左右同时进行，直到两侧相遇，此时查询区间恰好统计完毕．需要注意的是，累计信息时需要左右分别统计，最后再将两侧的结果合并，以保证信息合并的顺序正确．

???+ example "参考实现"
    ```cpp
    // Query info in [l, r].
    Info query(int l, int r) {
      Info la, ra;
      for (l = l - L + n, r = r - L + n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) la += val[l++];
        if (~r & 1) ra = val[r--] + ra;
      }
      return la + ra;
    }

    ```

???+ tip "提示"
    对于区间查询，不同实现存在细微差别．此处实现的是闭区间 $[l,r]$ 查询，[AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp#L52-L65) 实现的是 $[l,r)$ 查询，张昆玮原始资料实现的是 $(l,r)$ 查询．三者没有本质区别，只是边界的处理方式不同．

最后，考虑区间修改操作，关键在于懒惰标记的处理．结点的访问仍然可以自下而上进行，但标记的下传必须自上而下，否则无法清空自根到叶路径上的全部标记．因此，只要找出极大区间结点的所有祖先结点，自上而下依次下传标记即可．为此，注意到极大区间结点的父结点必然包含左右端点之一，而包含某个端点的结点都位于自根到该端点对应叶结点的路径上．不过，这条路径上并非每个结点都是极大区间结点的祖先：自包含该端点的极大区间结点起，往下直到叶结点的一段就不是，处理时应当跳过．所以，只要沿着左右端点对应叶结点的两条路径，自根向叶下传一遍标记，跳过这一段即可．修改完成后，再沿同样的两条路径自下而上地更新祖先结点的信息．

???+ example "参考实现"
    ```cpp
    // Apply transformation f to the range [l, r].
    void modify(int l, int r, const Transform& f) {
      l = l - L + n, r = r - L + n;
      for (int i = h, m = (1 << h) - 1; i; --i, m >>= 1) {
        if (l & m) push_down(l >> i);
        if (~r & m) push_down(r >> i);
      }
      for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
        if (ll & 1) lazy_update(ll++, f);
        if (~rr & 1) lazy_update(rr--, f);
      }
      for (int i = 1, m = 1; i <= h; ++i, m = (m << 1) | 1) {
        if (l & m) push_up(l >> i);
        if (~r & m) push_up(r >> i);
      }
    }

    ```

???+ tip "提示"
    1.  此处实现的仍是闭区间 $[l,r]$ 修改，半闭半开区间 $[l,r)$ 版本可以参考 [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp#L110-L138)．两个版本都应用了位操作，核心想法也一致：应当跳过的那一段结点，其对应区间的左（右）端点与修改区间的左（右）端点对齐．
    2.  这一段结点，下传时跳过与否只影响效率，回溯时却必须跳过：对刚打上懒惰标记的结点调用 `push_up`，会用尚未更新的子结点信息覆盖它．

带懒惰标记的非递归实现中，其余操作也只需类似地在访问前增加自根向叶的下传．

非递归实现线段树的完整参考实现如下，同样分为不带懒惰标记和带懒惰标记两个版本：

??? example "参考实现"
    === "不带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Nonrecursive. No lazy tag.
        // --8<-- [start:build]
        // Nonrecursive structure, embedded in a perfect binary tree.
        int n, L, R;
        std::vector<Info> val;

        void push_up(int cr) { val[cr] = val[cr << 1] + val[(cr << 1) | 1]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int l, int r, const std::vector<Info>& vec) {
          L = l, R = r;
          for (n = 1; n < r - l + 1; n <<= 1);
          val.resize(n << 1);
          std::copy(vec.begin(), vec.end(), val.begin() + n);
          for (int i = n - 1; i; --i) push_up(i);
        }

        // --8<-- [end:build]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int x) { return val[n + x - L]; }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Modify info at x to v.
        void modify(int x, const Info& v) {
          x = x - L + n;
          val[x] = v;
          for (x >>= 1; x; x >>= 1) push_up(x);
        }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int l, int r) {
          Info la, ra;
          for (l = l - L + n, r = r - L + n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) la += val[l++];
            if (~r & 1) ra = val[r--] + ra;
          }
          return la + ra;
        }

        // --8<-- [end:range-get]
        ```
    
    === "带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Nonrecursive. With lazy tag.
        // --8<-- [start:build]
        // Nonrecursive structure, embedded in a perfect binary tree.
        int n, h, L, R;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[cr << 1] + val[(cr << 1) | 1]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int l, int r, const std::vector<Info>& vec) {
          L = l, R = r, n = r - l + 1;
          for (h = 0; (1 << h) < n; ++h);
          n = 1 << h;
          val.resize(n << 1), lazy.resize(n);
          std::copy(vec.begin(), vec.end(), val.begin() + n);
          for (int i = n - 1; i; --i) push_up(i);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          if (cr < n) lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr) {
          if (!lazy[cr]) return;
          lazy_update(cr << 1, lazy[cr]);
          lazy_update((cr << 1) | 1, lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int x) {
          x = x - L + n;
          for (int i = h; i; --i) push_down(x >> i);
          return val[x];
        }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Apply transformation f to the value at x.
        void modify(int x, const Transform& f) {
          x = x - L + n;
          for (int i = h; i; --i) push_down(x >> i);
          val[x] = f(val[x]);
          for (int i = 1; i <= h; ++i) push_up(x >> i);
        }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int l, int r) {
          l = l - L + n, r = r - L + n;
          for (int i = h, m = (1 << h) - 1; i; --i, m >>= 1) {
            if (l & m) push_down(l >> i);
            if (~r & m) push_down(r >> i);
          }
          Info la, ra;
          for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) la += val[l++];
            if (~r & 1) ra = val[r--] + ra;
          }
          return la + ra;
        }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int l, int r, const Transform& f) {
          l = l - L + n, r = r - L + n;
          for (int i = h, m = (1 << h) - 1; i; --i, m >>= 1) {
            if (l & m) push_down(l >> i);
            if (~r & m) push_down(r >> i);
          }
          for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
            if (ll & 1) lazy_update(ll++, f);
            if (~rr & 1) lazy_update(rr--, f);
          }
          for (int i = 1, m = 1; i <= h; ++i, m = (m << 1) | 1) {
            if (l & m) push_up(l >> i);
            if (~r & m) push_up(r >> i);
          }
        }

        // --8<-- [end:range-set]
        ```

除了不带懒惰标记线段树的单点查询复杂度降低到 $O(1)$ 外，其余操作复杂度和递归实现版本相同，只是常数较小．

综上，非递归实现同样可以支持线段树的各种基本操作，包括区间修改和懒惰标记．但它和堆式存储一样，结点编号由位置决定，要求整棵完美二叉树的结点预先存在，因而无法动态开点，也不便可持久化．

### 动态开点

前文介绍的所有存储方式，都需要在建树时一次性地分配大小为 $\Theta(N)$ 的存储空间．这样做在区间长度 $N$ 较大（例如 $\sim 10^9$）时并不可行．为了节省空间，可以不一次性建好树，而是在最初只建立一个根结点代表整段区间．当需要访问某个子区间时，才建立代表这段区间的子结点．由于结点编号不固定，动态开点线段树只能采用内存池动态分配的方式实现，需要用数组记录子结点编号．

这样做的前提是，尚未建立的结点对应的信息是已知的．最简单的情形是，未建立的结点对应区间的信息恰为信息空间 $M$ 中的单位元 $e$（即空区间对应的信息）．此时，查询遇到空结点直接返回 $e$ 即可，合并时也无需特殊处理；只有修改操作需要写入信息时，才沿途建立经过的结点．更一般的情形是，未建立的结点的信息与其对应区间有关．对于这类问题，查询空结点、创建新结点以及合并子结点信息时，都需要根据当前区间的端点计算出相应的信息．但无论如何，动态开点线段树通常无法从任意给定的初始序列建树．此外，由于结点编号不再蕴含区间信息，划分区间时需要沿用递归实现的做法，将当前结点对应的区间作为参数逐层传递；格外需要注意的是，下传懒惰标记前，也需要先建立子结点．

![](images/seg-7.svg)

作为参考，此处给出不带懒惰标记和带懒惰标记的动态开点线段树实现．为对照上文两种情形，前者假定未建立结点的信息恰为单位元 $e$，后者则假定它与所处区间有关．

??? example "参考实现"
    === "不带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Dynamic node allocation.
        // --8<-- [start:build]
        // Dynamic node allocation.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build an empty tree.
        void build(int l, int r, int n) {
          rt = 0, id = 0, L = l, R = r;
          ch.resize(n), val.resize(n);
        }

        // --8<-- [end:build]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int cr, int ll, int rr, int x) {
          if (!cr) return {};
          if (ll == rr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            return query(lc(cr), ll, mm, x);
          else
            return query(rc(cr), mm + 1, rr, x);
        }

        Info query(int x) { return query(rt, L, R, x); }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Modify info at x to v.
        void modify(int& cr, int ll, int rr, int x, const Info& v) {
          if (!cr) cr = ++id;
          if (ll == rr) return (void)(val[cr] = v);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            modify(lc(cr), ll, mm, x, v);
          else
            modify(rc(cr), mm + 1, rr, x, v);
          push_up(cr);
        }

        void modify(int x, const Info& v) { modify(rt, L, R, x, v); }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (!cr) return {};
          if (tl <= ll && rr <= tr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        ```
    
    === "带懒惰标记"
        ```cpp
        // Segment Tree Implementation. Dynamic node allocation.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;
        Info blank(int ll, int rr);  // Info of untouched node; problem-specific.

        Info info_of(int cr, int ll, int rr) { return cr ? val[cr] : blank(ll, rr); }

        void push_up(int cr, int ll, int rr) {
          int mm = ll + ((rr - ll) >> 1);
          val[cr] = info_of(lc(cr), ll, mm) + info_of(rc(cr), mm + 1, rr);
        }

        // Build an empty tree.
        void build(int l, int r, int n) {
          rt = 0, id = 0, L = l, R = r;
          ch.resize(n), val.resize(n), lazy.resize(n);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int& cr, int ll, int rr, const Transform& f) {
          if (!cr) val[cr = ++id] = blank(ll, rr);
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr, int ll, int rr) {
          if (!lazy[cr]) return;
          int mm = ll + ((rr - ll) >> 1);
          lazy_update(lc(cr), ll, mm, lazy[cr]);
          lazy_update(rc(cr), mm + 1, rr, lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int cr, int ll, int rr, int x) {
          if (!cr) return blank(ll, rr);
          if (ll == rr) return val[cr];
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            return query(lc(cr), ll, mm, x);
          else
            return query(rc(cr), mm + 1, rr, x);
        }

        Info query(int x) { return query(rt, L, R, x); }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Apply transformation f to the value at x.
        void modify(int& cr, int ll, int rr, int x, const Transform& f) {
          if (!cr) val[cr = ++id] = blank(ll, rr);
          if (ll == rr) return (void)(val[cr] = f(val[cr]));
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            modify(lc(cr), ll, mm, x, f);
          else
            modify(rc(cr), mm + 1, rr, x, f);
          push_up(cr, ll, rr);
        }

        void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (!cr) return blank(std::max(ll, tl), std::min(rr, tr));
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int& cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (!cr) val[cr = ++id] = blank(ll, rr);
          if (tl <= ll && rr <= tr) return lazy_update(cr, ll, rr, f);
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr, ll, rr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        ```

???+ tip "提示"
    下传标记时需要先建立子结点，会增加空间常数因子，请分配好足量空间．

由于每次修改只沿着自根向叶的至多两条路径建立结点，单次操作至多新建 $O(\log N)$ 个结点．因此，$q$ 次操作后结点总数是 $O(q\log N)$ 的，这正是动态开点能处理大区间的原因．时间复杂度则与前文相同，单次操作仍是 $O(\log N)$．此处的 $O(q\log N)$ 是很宽松的上界．实际使用时，若操作区间大量重叠，新建的结点会少得多；反之，若每次操作都涉及互不相交的区间，就会接近这个上界．在初始化线段树时，应根据这一上界分配充足的空间．

动态开点只是处理这类问题的一种方法．如果已知所有操作涉及的端点，可以先将它们 [离散化](../misc/discrete.md)，再在离散化后的区间上建立普通线段树，效果相同且实现更简单；只有在操作无法预先得知（例如强制在线）时，才需要考虑使用动态开点．

此外，[可持久化线段树](./persistent-seg.md) 也建立在动态开点的基础上：每次修改只新建自根向叶一条路径上的结点，其余部分与旧版本共享，从而每次修改只需要 $O(\log N)$ 的额外空间．

### 标记永久化

前文介绍的懒惰标记都需要下传．但是，每次下传都需要读写子结点，常数不小；而且，某些情形下难以下传标记．为了避免下传懒惰标记，可以采用标记永久化的方法：标记一旦打上就永远留在原处，不再下传；查询时，再将自根到该结点沿途经过的标记复合起来，作用于该结点存储的信息．

![](images/seg-8.svg)

和前文约定一致，设结点 $x$ 处的标记只对其子孙结点生效，而 $x$ 自身存储的信息已经计入了该标记的作用．换言之，$x$ 存储的信息是不考虑其祖先结点处标记时，$x$ 对应区间的信息．以递归实现为例，线段树区间操作的实现分别是：

-   区间修改：自上而下递归．递归到极大区间结点时，在该处打上标记，并更新其信息，随即返回，不再向下．回溯时，用子结点的信息合并出当前结点的信息，再作用上当前结点的标记．
-   区间查询：自上而下递归．递归到极大区间结点时，直接返回它存储的信息．回溯时，将各子结点返回的结果合并，再作用上当前结点的标记；逐层向上，沿途结点的标记便都作用到了结果上．

两种操作时间复杂度仍然是 $O(\log N)$，但省去了全部下传，常数更小．非递归实现类似，只是将递归换成了迭代．它们的参考实现如下：

??? example "参考实现"
    === "递归实现"
        ```cpp
        // Segment Tree Implementation. Recursive. With lazy tag.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = lazy[cr](val[lc(cr)] + val[rc(cr)]); }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // --8<-- [end:tag]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int cr, int ll, int rr, int x) {
          if (ll == rr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          return lazy[cr](x <= mm ? query(lc(cr), ll, mm, x)
                                  : query(rc(cr), mm + 1, rr, x));
        }

        Info query(int x) { return query(rt, L, R, x); }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Apply transformation f to the value at x.
        void modify(int cr, int ll, int rr, int x, const Transform& f) {
          if (ll == rr) return (void)(val[cr] = f(val[cr]));
          int mm = ll + ((rr - ll) >> 1);
          if (x <= mm)
            modify(lc(cr), ll, mm, x, f);
          else
            modify(rc(cr), mm + 1, rr, x, f);
          push_up(cr);
        }

        void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return lazy[cr](res);
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (tl <= ll && rr <= tr) return lazy_update(cr, f);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        ```
    
    === "非递归实现"
        ```cpp
        // Segment Tree Implementation. Nonrecursive. With lazy tag.
        // --8<-- [start:build]
        // Nonrecursive structure, embedded in a perfect binary tree.
        int n, h, L, R;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = lazy[cr](val[cr << 1] + val[(cr << 1) | 1]); }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int l, int r, const std::vector<Info>& vec) {
          L = l, R = r, n = r - l + 1;
          for (h = 0; (1 << h) < n; ++h);
          n = 1 << h;
          val.resize(n << 1), lazy.resize(n);
          std::copy(vec.begin(), vec.end(), val.begin() + n);
          for (int i = n - 1; i; --i) push_up(i);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          if (cr < n) lazy[cr] += f;
        }

        // --8<-- [end:tag]
        // --8<-- [start:point-get]
        // Query info at x.
        Info query(int x) {
          x = x - L + n;
          auto res = val[x];
          for (int i = 1; i <= h; ++i) res = lazy[x >> i](res);
          return res;
        }

        // --8<-- [end:point-get]
        // --8<-- [start:point-set]
        // Apply transformation f to the value at x.
        void modify(int x, const Transform& f) {
          x = x - L + n;
          val[x] = f(val[x]);
          for (int i = 1; i <= h; ++i) push_up(x >> i);
        }

        // --8<-- [end:point-set]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int l, int r) {
          l = l - L + n, r = r - L + n;
          Info la, ra;
          for (int i = 0, ll = l, rr = r; i <= h; ++i) {
            if (i) la = lazy[l >> i](la), ra = lazy[r >> i](ra);
            if (ll <= rr) {
              if (ll & 1) la += val[ll++];
              if (~rr & 1) ra = val[rr--] + ra;
              ll >>= 1, rr >>= 1;
            }
          }
          return la + ra;
        }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int l, int r, const Transform& f) {
          l = l - L + n, r = r - L + n;
          for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
            if (ll & 1) lazy_update(ll++, f);
            if (~rr & 1) lazy_update(rr--, f);
          }
          for (int i = 1, m = 1; i <= h; ++i, m = (m << 1) | 1) {
            if (l & m) push_up(l >> i);
            if (~r & m) push_up(r >> i);
          }
        }

        // --8<-- [end:range-set]
        ```

但是，标记永久化并非总是可行，它对修改操作有额外要求．修改操作的复合必须满足 **交换律**．前文说明过，懒惰标记的复合未必可交换，而下传之所以能保证顺序正确，是因为每次访问子结点前都会先下传，从而根到叶的路径上，越靠近根的标记对应的操作总是越晚发生．标记永久化恰恰放弃了这一性质：标记始终停留在原处，位置由修改区间决定，与操作发生的先后无关．于是，祖先结点上的标记既可能早于、也可能晚于子孙结点上的标记．查询时按自根向叶的顺序复合标记，只有在复合可交换时才能保证结果正确．

???+ example "例子"
    区间加、区间乘等操作都是可交换的，可以标记永久化．区间仿射变换（即同时允许区间加和区间乘）、区间赋值[^assign]则不可交换，无法标记永久化．

标记永久化经常应用于 [可持久化线段树](./persistent-seg.md) 和各类树套树中．这两种情形下，下传代价高昂；标记永久化即使不是必需的，也往往是更合适的选择．还有一些问题中，标记根本无从下传（见后文「矩形面积并」例题），此时标记永久化就是唯一的办法．

### 线段树二分

有些问题需要在序列上二分．例如，给定 $l$，求最大的 $r$，使得区间 $[l,r]$ 的信息满足某个条件．直接的做法是二分 $r$，每次用线段树查询一遍区间信息，复杂度是 $O(\log^2 N)$ 的．但是，线段树本身就是一棵二分的结构，把二分的过程放到线段树上进行，就可以做到 $O(\log N)$．

仍设线段树存储的区间信息为 $\varphi:\mathcal I\rightarrow M$．设条件是关于信息空间 $M$ 的谓词 $g:M\rightarrow\{\text{True},\text{False}\}$．要让二分有意义，$g$ 必须满足（向右合并的）**单调性**：若 $g(m)$ 为假，则对任意 $m'$，$g(m\circ m')$ 也为假．也就是说，一旦区间向右延伸到条件不再成立，就不会再重新成立．此外，还需要 $g(e)$ 为真，即空区间总是满足条件．于是，问题变为：给定 $l$，求最大的 $r$，使得 $g(\varphi([l,r]))$ 为真；若 $g(\varphi([l,l]))$ 已经为假，则约定答案为 $l-1$．

![](images/seg-9.svg)

递归实现线段树中，二分的具体做法是，自上而下递归，同时维护一个累计信息 $m$，表示已经确定纳入答案区间的那一部分的信息．递归到某个结点时，若它对应的区间 $I$ 完全落在 $[l,R]$ 内，就先试着把整个结点并入：计算 $m\circ\varphi(I)$，若 $g$ 仍为真，说明该结点可以整个纳入，更新 $m$ 并返回该结点的右端点；否则，答案的分界就在该结点内部，需要继续向下递归．递归到叶结点时，若仍不满足条件，说明分界就在此处．

这样做的复杂度仍然是 $O(\log N)$ 的．这是因为，递归过程中只有两类结点会继续向下：一类是对应区间越出 $[l,R]$ 的结点，它们都在自根到 $l$ 的路径上；另一类是整个并入会使 $g$ 变假的结点，其中只有分界所在的那条路径上的结点会真正向下，每层至多一个．两类结点都只有 $O(\log N)$ 个，其余结点要么整个纳入，要么整个跳过．

![](images/seg-10.svg)

非递归实现把上述过程拆成两个阶段．先自下而上：从 $l$ 对应叶结点出发，只要当前结点是左子结点就上跳，直到它是右子结点为止，此时它对应区间的左端点恰与尚未纳入的部分对齐，于是尝试整个并入；成功则向右移动一个结点，继续上跳．一旦某个结点并入后 $g$ 变假，就转为自上而下：在该结点内部下行，每层先尝试并入左子结点，成功则转向右子结点，失败则进入左子结点，直到叶结点，即得分界．两个阶段各只走一趟，复杂度同样是 $O(\log N)$．

对称地，也可以给定 $r$，求最小的 $l$，使得 $g(\varphi([l,r]))$ 为真．此时累计信息应当从右向左合并，即计算 $\varphi(I)\circ m$，以保证合并顺序正确；无解时约定答案为 $r+1$．而且，$g$ 需要满足向左合并的单调性：若 $g(m)$ 为假，则对任意 $m'$，$g(m'\circ m)$ 也为假．

??? example "参考实现"
    === "递归实现"
        ```cpp
        // Find max r in [l, R] such that g(info([l, r])) is true.
        // Return l - 1 if no such r exists.
        template <typename G>
        int max_right(int cr, int ll, int rr, int tl, const G& g, Info& acc) {
          if (tl <= ll) {
            auto nxt = acc + val[cr];
            if (g(nxt)) return acc = nxt, rr;
            if (ll == rr) return ll - 1;
          }
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) {
            auto res = max_right(lc(cr), ll, mm, tl, g, acc);
            if (res < mm) return res;
          }
          return max_right(rc(cr), mm + 1, rr, tl, g, acc);
        }

        template <typename G>
        int max_right(int l, const G& g) {
          Info acc;
          return max_right(rt, L, R, l, g, acc);
        }

        // Find min l in [L, r] such that g(info([l, r])) is true.
        // Return r + 1 if no such l exists.
        template <typename G>
        int min_left(int cr, int ll, int rr, int tr, const G& g, Info& acc) {
          if (tr >= rr) {
            auto nxt = val[cr] + acc;
            if (g(nxt)) return acc = nxt, ll;
            if (ll == rr) return rr + 1;
          }
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tr > mm) {
            auto res = min_left(rc(cr), mm + 1, rr, tr, g, acc);
            if (res > mm + 1) return res;
          }
          return min_left(lc(cr), ll, mm, tr, g, acc);
        }

        template <typename G>
        int min_left(int r, const G& g) {
          Info acc;
          return min_left(rt, L, R, r, g, acc);
        }

        ```
    
    === "非递归实现"
        ```cpp
        // Find max r in [l, R] such that g(info([l, r])) is true.
        // Return l - 1 if no such r exists.
        template <typename G>
        int max_right(int l, const G& g) {
          l = l - L + n;
          for (int i = h; i; --i) push_down(l >> i);
          Info acc;
          for (;;) {
            while (~l & 1) l >>= 1;
            auto nxt = acc + val[l];
            if (!g(nxt)) {
              while (l < n) {
                push_down(l);
                l <<= 1;
                nxt = acc + val[l];
                if (g(nxt)) acc = nxt, ++l;
              }
              return l - n + L - 1;
            }
            acc = nxt, ++l;
            if ((l & -l) == l) break;
          }
          return R;
        }

        // Find min l in [L, r] such that g(info([l, r])) is true.
        // Return r + 1 if no such l exists.
        template <typename G>
        int min_left(int r, const G& g) {
          r = r - L + n;
          for (int i = h; i; --i) push_down(r >> i);
          Info acc;
          for (;;) {
            while ((r & 1) && (r ^ 1)) r >>= 1;
            auto nxt = val[r] + acc;
            if (!g(nxt)) {
              while (r < n) {
                push_down(r);
                r = (r << 1) | 1;
                nxt = val[r] + acc;
                if (g(nxt)) acc = nxt, --r;
              }
              return r - n + L + 1;
            }
            if ((r & -r) == r) break;
            acc = nxt, --r;
          }
          return L;
        }

        ```

???+ tip "提示"
    1.  带懒惰标记时，向下访问子结点前同样需要下传标记．非递归实现中，上跳阶段开始前需要先沿自根到 $l$ 的路径下传一遍．
    2.  若判定只与当前结点自身的信息有关（例如「区间内是否存在大于 $x$ 的元素」），则无需维护累计信息，实现更为简单．
    3.  非递归实现中，多余的叶结点存储单位元，$g$ 在其上恒为真，因此上跳阶段可能一路越过它们．此时应直接返回 $R$，而不是由结点编号换算位置．

### 权值线段树

前文的线段树都建立在序列的下标上．但是，线段树并不关心下标的含义．如果把它建立在值域上，即让元素 $v$ 对应的叶结点记录值 $v$ 在可重集中出现的次数，就得到 **权值线段树**．

![](images/seg-11.svg)

这样的线段树可以当作一个支持 [平衡树](./bst.md) 常见操作的集合来使用，而这些操作都可以由前文的操作直接得到：

-   插入元素 $v$，即在位置 $v$ 处单点加一．
-   删除元素 $v$，即在位置 $v$ 处单点减一；注意判断元素是否存在．
-   查询 $v$ 的排名，即查询值域区间 $[L,v-1]$ 上的区间和再加一．
-   查询第 $k$ 小的元素，即利用线段树二分，求最大的 $r$，使得值域区间 $[L,r]$ 上的元素个数小于 $k$；此时 $r+1$ 就是所求．由于计数可以相减，下行时只需比较左子结点的计数与 $k$，无需维护累计信息．
-   查询前驱与后继，可以由查询排名和查询第 $k$ 小元素两个操作实现．

与常见平衡树相比，权值线段树的实现要简单得多，常数也更小；代价是只能处理值域上的元素，且不支持区间翻转等依赖树形结构本身的操作．

由于值域通常远大于元素个数，直接建树往往不可行．若所有元素可以预先得知，将值域 [离散化](../misc/discrete.md) 后建立普通线段树即可；否则，就需要动态开点．后一种情形下，未出现的值对应的结点信息恰为单位元，正是前文最简单的那种情形．

??? example "参考实现"
    ```cpp
    // Segment tree on values, supporting the ordered-set operations of a BST.
    int rt, id, L, R;
    std::vector<int> lc, rc;
    std::vector<int> cnt;

    void build(int l, int r, int n) {
      rt = 0, id = 0, L = l, R = r;
      lc.resize(n), rc.resize(n), cnt.resize(n);
    }

    // Insert v.
    void insert(int& cr, int ll, int rr, int v) {
      if (!cr) cr = ++id;
      ++cnt[cr];
      if (ll == rr) return;
      int mm = ll + ((rr - ll) >> 1);
      if (v <= mm)
        insert(lc[cr], ll, mm, v);
      else
        insert(rc[cr], mm + 1, rr, v);
    }

    void insert(int v) { insert(rt, L, R, v); }

    // Remove v.
    // If there are multiple, remove once.
    // Return true if there is any, return false if there is none.
    bool remove(int cr, int ll, int rr, int v) {
      if (!cnt[cr]) return false;
      if (ll == rr) return cnt[cr]--;
      int mm = ll + ((rr - ll) >> 1);
      auto succ = false;
      if (v <= mm)
        succ = remove(lc[cr], ll, mm, v);
      else
        succ = remove(rc[cr], mm + 1, rr, v);
      return succ && cnt[cr]--;
    }

    bool remove(int v) { return remove(rt, L, R, v); }

    // Count values within range [l, r].
    int count(int cr, int ll, int rr, int tl, int tr) {
      if (!cr) return 0;
      if (tl <= ll && rr <= tr) return cnt[cr];
      int mm = ll + ((rr - ll) >> 1);
      int res = 0;
      if (tl <= mm) res = count(lc[cr], ll, mm, tl, tr);
      if (mm < tr) res += count(rc[cr], mm + 1, rr, tl, tr);
      return res;
    }

    int count(int l, int r) { return count(rt, L, R, l, r); }

    // Find the rank of v, i.e., one plus the count of numbers less than v.
    int find_rank(int v) { return v > L ? count(L, v - 1) + 1 : 1; }

    // Find the k-th element.
    int find_kth(int cr, int ll, int rr, int k) {
      if (ll == rr) return ll;
      int mm = ll + ((rr - ll) >> 1);
      if (k <= cnt[lc[cr]])
        return find_kth(lc[cr], ll, mm, k);
      else
        return find_kth(rc[cr], mm + 1, rr, k - cnt[lc[cr]]);
    }

    int find_kth(int k) {
      return k > cnt[rt] || k <= 0 ? -1 : find_kth(rt, L, R, k);
    }

    // Find the predecessor of v.
    int find_prev(int x) { return find_kth(find_rank(x) - 1); }

    // Find the successor of v.
    int find_next(int x) { return find_kth(find_rank(x + 1)); }

    ```

权值线段树也是 [可持久化线段树](./persistent-seg.md) 和线段树合并等拓展最常见的载体．前者可以查询序列某个区间内的第 $k$ 小，后者可以高效地合并两个集合．

## 拓展

线段树应用十分广泛，常见的拓展和变体如下：

-   [可持久化线段树](./persistent-seg.md)
-   各类树套树：
    -   [线段树套线段树](./seg-in-seg.md)
    -   [树状数组套线段树](./seg-in-bit.md)
    -   [线段树套平衡树](./balanced-in-seg.md)
    -   [平衡树套线段树](./seg-in-balanced.md)
-   [李超线段树](./li-chao-tree.md)
-   [猫树](./cat-tree.md)
-   [吉司机线段树](./seg-beats.md)

详细内容请参阅相关页面．

## 例题

前文介绍了线段树的基本原理，并给出了几份模板实现．但线段树的实现相当灵活．本节的参考实现将不拘泥于模板．

???+ example "[Library Checker - Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum)"
    已知一个数列．需要进行如下操作：
    
    -   将第 $p$ 个数增加 $x$．
    -   求区间 $[l,r)$ 中元素的和．

??? note "解答"
    只要实现支持单点修改、区间查询的线段树即可．
    
    === "实现 1"
        ```cpp
        #include <algorithm>
        #include <iostream>
        #include <vector>

        // --8<-- [start:info]
        // Sum.
        struct Info {
          long long sum;

          Info(long long x = 0) : sum(x) {}

          Info operator+(const Info& o) const { return Info(sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // --8<-- [end:info]
        // --8<-- [start:seg-tree]
        // Segment tree.
        class SegmentTree {
          int rt, id, L, R;
          std::vector<int> lc, rc;
          std::vector<Info> val;

          void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

          void build(int cr, int ll, int rr, const std::vector<int>& vec) {
            if (ll == rr) return (void)(val[cr] = Info(vec[ll - L]));
            int mm = ll + ((rr - ll) >> 1);
            build(lc[cr] = ++id, ll, mm, vec);
            build(rc[cr] = ++id, mm + 1, rr, vec);
            push_up(cr);
          }

          void modify(int cr, int ll, int rr, int x, int v) {
            if (ll == rr) return (void)(val[cr] += Info(v));
            int mm = ll + ((rr - ll) >> 1);
            if (x <= mm)
              modify(lc[cr], ll, mm, x, v);
            else
              modify(rc[cr], mm + 1, rr, x, v);
            push_up(cr);
          }

          Info query(int cr, int ll, int rr, int tl, int tr) {
            if (tl <= ll && rr <= tr) return val[cr];
            int mm = ll + ((rr - ll) >> 1);
            Info res;
            if (tl <= mm) res = query(lc[cr], ll, mm, tl, tr);
            if (mm < tr) res += query(rc[cr], mm + 1, rr, tl, tr);
            return res;
          }

         public:
          SegmentTree(int n, const std::vector<int>& vec)
              : rt(0), id(0), L(0), R(n - 1), lc(n << 1), rc(n << 1), val(n << 1) {
            build(rt = ++id, L, R, vec);
          }

          void modify(int x, int v) { modify(rt, L, R, x, v); }

          Info query(int l, int r) { return query(rt, L, R, l, r); }
        };

        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, q;
          std::cin >> n >> q;
          std::vector<int> vec(n);
          for (auto& x : vec) std::cin >> x;
          SegmentTree seg(n, vec);
          for (; q; --q) {
            int op;
            std::cin >> op;
            if (op == 0) {
              int p, x;
              std::cin >> p >> x;
              seg.modify(p, x);
            } else if (op == 1) {
              int l, r;
              std::cin >> l >> r;
              std::cout << seg.query(l, r - 1).sum << '\n';
            }
          }
          return 0;
        }
        ```
    
    === "实现 2"
        ```cpp
        #include <algorithm>
        #include <iostream>
        #include <vector>

        // --8<-- [start:seg-tree]
        // Segment tree.
        class SegmentTree {
          int n;
          std::vector<long long> sum;

         public:
          SegmentTree(int _n, const std::vector<int>& vec) {
            for (n = 1; n < _n; n <<= 1);
            sum.resize(n << 1);
            std::copy(vec.begin(), vec.end(), sum.begin() + n);
            for (int i = n - 1; i; --i) sum[i] = sum[i << 1] + sum[(i << 1) | 1];
          }

          void modify(int x, int v) {
            for (x += n; x; x >>= 1) sum[x] += v;
          }

          long long query(int l, int r) {
            l += n, r += n;
            long long res = 0;
            for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
              if (ll & 1) res += sum[ll++];
              if (~rr & 1) res += sum[rr--];
            }
            return res;
          }
        };

        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, q;
          std::cin >> n >> q;
          std::vector<int> vec(n);
          for (auto& x : vec) std::cin >> x;
          SegmentTree seg(n, vec);
          for (; q; --q) {
            int op;
            std::cin >> op;
            if (op == 0) {
              int p, x;
              std::cin >> p >> x;
              seg.modify(p, x);
            } else if (op == 1) {
              int l, r;
              std::cin >> l >> r;
              std::cout << seg.query(l, r - 1) << '\n';
            }
          }
          return 0;
        }
        ```

???+ example "[Luogu P3372【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)"
    已知一个数列．需要进行下面两种操作：
    
    -   将某区间每一个数加上 $k$．
    -   求出某区间每一个数的和．

??? note "解答"
    只要实现支持区间修改、区间查询的线段树即可．注意，为了实现区间加操作，需要维护当前区间长度作为区间信息的一部分，或者在区间修改时利用区间端点计算．
    
    === "实现 1"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <vector>

        // --8<-- [start:info]
        // Interval length and sum of elements.
        struct Info {
          long long len, sum;

          Info(long long _len = 0, long long _sum = 0) : len(_len), sum(_sum) {}

          Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // --8<-- [end:info]
        // --8<-- [start:transform]
        // Range add.
        struct Transform {
          long long v;

          Transform(long long _v = 0) : v(_v) {}

          explicit operator bool() const { return v != 0; }

          Transform operator+(const Transform& o) const { return Transform(v + o.v); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& x) const {
            return Info(x.len, x.sum + v * x.len);
          }
        };

        // --8<-- [end:transform]
        // --8<-- [start:seg-tree]
        // Segment Tree.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr) {
          if (!lazy[cr]) return;
          lazy_update(lc(cr), lazy[cr]);
          lazy_update(rc(cr), lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (tl <= ll && rr <= tr) return lazy_update(cr, f);
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, m;
          std::cin >> n >> m;
          std::vector<Info> vec(n);
          for (auto& v : vec) {
            long long x;
            std::cin >> x;
            v = Info(1, x);
          }
          build(1, n, vec);
          for (; m; --m) {
            int op;
            std::cin >> op;
            if (op == 1) {
              int x, y;
              long long k;
              std::cin >> x >> y >> k;
              modify(x, y, Transform(k));
            } else if (op == 2) {
              int x, y;
              std::cin >> x >> y;
              std::cout << query(x, y).sum << '\n';
            }
          }
          return 0;
        }
        ```
    
    === "实现 2"
        ```cpp
        #include <iostream>
        using LL = long long;
        LL n, a[100005], d[270000], b[270000];

        void build(LL l, LL r, LL p) {  // l:区间左端点 r:区间右端点 p:节点标号
          if (l == r) {
            d[p] = a[l];  // 将节点赋值
            return;
          }
          LL m = l + ((r - l) >> 1);
          build(l, m, p << 1), build(m + 1, r, (p << 1) | 1);  // 分别建立子树
          d[p] = d[p << 1] + d[(p << 1) | 1];
        }

        void update(LL l, LL r, LL c, LL s, LL t, LL p) {
          if (l <= s && t <= r) {
            d[p] += (t - s + 1) * c, b[p] += c;  // 如果区间被包含了，直接得出答案
            return;
          }
          LL m = s + ((t - s) >> 1);
          if (b[p])
            d[p << 1] += b[p] * (m - s + 1), d[(p << 1) | 1] += b[p] * (t - m),
                b[p << 1] += b[p], b[(p << 1) | 1] += b[p];
          b[p] = 0;
          if (l <= m)
            update(l, r, c, s, m, p << 1);  // 本行和下面的一行用来更新p*2和p*2+1的节点
          if (r > m) update(l, r, c, m + 1, t, (p << 1) | 1);
          d[p] = d[p << 1] + d[(p << 1) | 1];  // 计算该节点区间和
        }

        LL getsum(LL l, LL r, LL s, LL t, LL p) {
          if (l <= s && t <= r) return d[p];
          LL m = s + ((t - s) >> 1);
          if (b[p])
            d[p << 1] += b[p] * (m - s + 1), d[(p << 1) | 1] += b[p] * (t - m),
                b[p << 1] += b[p], b[(p << 1) | 1] += b[p];
          b[p] = 0;
          LL sum = 0;
          if (l <= m)
            sum =
                getsum(l, r, s, m, p << 1);  // 本行和下面的一行用来更新p*2和p*2+1的答案
          if (r > m) sum += getsum(l, r, m + 1, t, (p << 1) | 1);
          return sum;
        }

        int main() {
          std::ios::sync_with_stdio(false);
          LL q, i1, i2, i3, i4;
          std::cin >> n >> q;
          for (LL i = 1; i <= n; i++) std::cin >> a[i];
          build(1, n, 1);
          while (q--) {
            std::cin >> i1 >> i2 >> i3;
            if (i1 == 2)
              std::cout << getsum(i2, i3, 1, n, 1) << std::endl;  // 直接调用操作函数
            else
              std::cin >> i4, update(i2, i3, i4, 1, n, 1);
          }
          return 0;
        }
        ```

???+ example "[Luogu P3373【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)"
    已知一个数列．需要进行下面三种操作：
    
    -   将某区间每一个数乘上 $x$．
    -   将某区间每一个数加上 $x$．
    -   求出某区间每一个数的和．

??? note "解答"
    只要实现支持区间修改、区间查询的线段树即可．可以直接实现区间仿射变换来同时支持区间加、区间乘操作．如果要使用两个懒惰标记分别记录区间加和区间乘，需要注意两标记下传的顺序．
    
    === "实现 1"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <vector>

        int M;

        // --8<-- [start:info]
        // Interval length and sum of elements.
        struct Info {
          int len, sum;

          Info(int _len = 0, int _sum = 0) : len(_len), sum(_sum) {}

          Info operator+(const Info& o) const {
            return Info(len + o.len, (sum + o.sum) % M);
          }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // --8<-- [end:info]
        // --8<-- [start:transform]
        // Affine transformation.
        struct Transform {
          int a, b;

          Transform(int _a = 1, int _b = 0) : a(_a), b(_b) {}

          explicit operator bool() const { return a != 1 || b != 0; }

          Transform operator+(const Transform& o) const {
            return Transform((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
          }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& x) const {
            return Info(x.len, ((long long)a * x.sum + (long long)b * x.len) % M);
          }
        };

        // --8<-- [end:transform]
        // --8<-- [start:seg-tree]
        // Segment Tree.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr) {
          if (!lazy[cr]) return;
          lazy_update(lc(cr), lazy[cr]);
          lazy_update(rc(cr), lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (tl <= ll && rr <= tr) return lazy_update(cr, f);
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, q;
          std::cin >> n >> q >> M;
          std::vector<Info> vec(n);
          for (auto& v : vec) {
            long long x;
            std::cin >> x;
            v = Info(1, x);
          }
          build(1, n, vec);
          for (; q; --q) {
            int op;
            std::cin >> op;
            if (op == 1) {
              int x, y, k;
              std::cin >> x >> y >> k;
              modify(x, y, Transform(k, 0));
            } else if (op == 2) {
              int x, y, k;
              std::cin >> x >> y >> k;
              modify(x, y, Transform(1, k));
            } else if (op == 3) {
              int x, y;
              std::cin >> x >> y;
              std::cout << query(x, y).sum << '\n';
            }
          }
          return 0;
        }
        ```
    
    === "实现 2"
        ```cpp
        #include <iostream>
        using ll = long long;

        int n, m;
        ll mod;
        ll a[100005], sum[400005], mul[400005], laz[400005];

        void up(int i) { sum[i] = (sum[(i << 1)] + sum[(i << 1) | 1]) % mod; }

        void pd(int i, int s, int t) {
          int l = (i << 1), r = (i << 1) | 1, mid = (s + t) >> 1;
          if (mul[i] != 1) {  // 懒标记传递，两个懒标记
            mul[l] *= mul[i];
            mul[l] %= mod;
            mul[r] *= mul[i];
            mul[r] %= mod;
            laz[l] *= mul[i];
            laz[l] %= mod;
            laz[r] *= mul[i];
            laz[r] %= mod;
            sum[l] *= mul[i];
            sum[l] %= mod;
            sum[r] *= mul[i];
            sum[r] %= mod;
            mul[i] = 1;
          }
          if (laz[i]) {  // 懒标记传递
            sum[l] += laz[i] * (mid - s + 1);
            sum[l] %= mod;
            sum[r] += laz[i] * (t - mid);
            sum[r] %= mod;
            laz[l] += laz[i];
            laz[l] %= mod;
            laz[r] += laz[i];
            laz[r] %= mod;
            laz[i] = 0;
          }
          return;
        }

        void build(int s, int t, int i) {
          mul[i] = 1;
          if (s == t) {
            sum[i] = a[s];
            return;
          }
          int mid = s + ((t - s) >> 1);
          build(s, mid, i << 1);
          build(mid + 1, t, (i << 1) | 1);
          up(i);
        }

        void chen(int l, int r, int s, int t, int i, ll z) {
          int mid = s + ((t - s) >> 1);
          if (l <= s && t <= r) {
            mul[i] *= z;
            mul[i] %= mod;
            laz[i] *= z;
            laz[i] %= mod;
            sum[i] *= z;
            sum[i] %= mod;
            return;
          }
          pd(i, s, t);
          if (mid >= l) chen(l, r, s, mid, (i << 1), z);
          if (mid + 1 <= r) chen(l, r, mid + 1, t, (i << 1) | 1, z);
          up(i);
        }

        void add(int l, int r, int s, int t, int i, ll z) {
          int mid = s + ((t - s) >> 1);
          if (l <= s && t <= r) {
            sum[i] += z * (t - s + 1);
            sum[i] %= mod;
            laz[i] += z;
            laz[i] %= mod;
            return;
          }
          pd(i, s, t);
          if (mid >= l) add(l, r, s, mid, (i << 1), z);
          if (mid + 1 <= r) add(l, r, mid + 1, t, (i << 1) | 1, z);
          up(i);
        }

        ll getans(int l, int r, int s, int t,
                  int i) {  // 得到答案，可以看下上面懒标记助于理解
          int mid = s + ((t - s) >> 1);
          ll tot = 0;
          if (l <= s && t <= r) return sum[i];
          pd(i, s, t);
          if (mid >= l) tot += getans(l, r, s, mid, (i << 1));
          tot %= mod;
          if (mid + 1 <= r) tot += getans(l, r, mid + 1, t, (i << 1) | 1);
          return tot % mod;
        }

        using std::cin;
        using std::cout;

        int main() {  // 读入
          cin.tie(nullptr)->sync_with_stdio(false);
          int i, j, x, y, bh;
          ll z;
          cin >> n >> m >> mod;
          for (i = 1; i <= n; i++) cin >> a[i];
          build(1, n, 1);  // 建树
          for (i = 1; i <= m; i++) {
            cin >> bh;
            if (bh == 1) {
              cin >> x >> y >> z;
              chen(x, y, 1, n, 1, z);
            } else if (bh == 2) {
              cin >> x >> y >> z;
              add(x, y, 1, n, 1, z);
            } else if (bh == 3) {
              cin >> x >> y;
              cout << getans(x, y, 1, n, 1) << '\n';
            }
          }
          return 0;
        }
        ```

???+ example "[SPOJ GSS3 - Can you answer these queries III](https://www.spoj.com/problems/GSS3/)"
    已知一个数列．需要进行如下操作：
    
    -   将第 $x$ 个数设置为 $y$．
    -   求区间 $[x,y]$ 的最大非空子段和．

??? note "解答"
    只要实现支持单点修改、区间查询的线段树即可．[前文](#区间信息) 已经分析过维护最大非空子段和的方法．这道题目中，信息合并不再满足交换律，需要注意实现时的合并顺序．
    
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>

    // --8<-- [start:info]
    // Maximum (non-empty) subarray sum
    struct Info {
      int sum;  // sum of the whole interval
      int lma;  // maximum sum of a non-empty prefix
      int rma;  // maximum sum of a non-empty suffix
      int ma;   // maximum sum of a non-empty subarray

      Info() : sum(0), lma(-1e9), rma(-1e9), ma(-1e9) {}

      Info(int x) : sum(x), lma(x), rma(x), ma(x) {}

      Info(int _s, int _l, int _r, int _m) : sum(_s), lma(_l), rma(_r), ma(_m) {}

      Info operator+(const Info& o) const {
        return Info(sum + o.sum, std::max(lma, sum + o.lma),
                    std::max(rma + o.sum, o.rma),
                    std::max(std::max(ma, o.ma), rma + o.lma));
      }

      Info& operator+=(const Info& o) { return *this = *this + o; }
    };

    // --8<-- [end:info]
    // --8<-- [start:seg-tree]
    // Segment tree.
    class SegmentTree {
      int rt, id, L, R;
      std::vector<int> lc, rc;
      std::vector<Info> val;

      void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

      void build(int cr, int ll, int rr, const std::vector<int>& vec) {
        if (ll == rr) return (void)(val[cr] = Info(vec[ll - L]));
        int mm = ll + ((rr - ll) >> 1);
        build(lc[cr] = ++id, ll, mm, vec);
        build(rc[cr] = ++id, mm + 1, rr, vec);
        push_up(cr);
      }

      void modify(int cr, int ll, int rr, int x, int v) {
        if (ll == rr) return (void)(val[cr] = Info(v));
        int mm = ll + ((rr - ll) >> 1);
        if (x <= mm)
          modify(lc[cr], ll, mm, x, v);
        else
          modify(rc[cr], mm + 1, rr, x, v);
        push_up(cr);
      }

      Info query(int cr, int ll, int rr, int tl, int tr) {
        if (tl <= ll && rr <= tr) return val[cr];
        int mm = ll + ((rr - ll) >> 1);
        Info res;
        if (tl <= mm) res = query(lc[cr], ll, mm, tl, tr);
        if (mm < tr) res += query(rc[cr], mm + 1, rr, tl, tr);
        return res;
      }

     public:
      SegmentTree(int n, const std::vector<int>& vec)
          : rt(0), id(0), L(1), R(n), lc(n << 1), rc(n << 1), val(n << 1) {
        build(rt = ++id, L, R, vec);
      }

      void modify(int x, int v) { modify(rt, L, R, x, v); }

      Info query(int l, int r) { return query(rt, L, R, l, r); }
    };

    // --8<-- [end:seg-tree]
    int main() {
      std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
      int n;
      std::cin >> n;
      std::vector<int> vec(n);
      for (auto& x : vec) std::cin >> x;
      SegmentTree seg(n, vec);
      int m;
      std::cin >> m;
      for (; m; --m) {
        int op;
        std::cin >> op;
        if (op == 0) {
          int x, y;
          std::cin >> x >> y;
          seg.modify(x, y);
        } else if (op == 1) {
          int l, r;
          std::cin >> l >> r;
          std::cout << seg.query(l, r).ma << '\n';
        }
      }
      return 0;
    }
    ```

???+ example "[Luogu P13825【模板】线段树 1.5](https://www.luogu.com.cn/problem/P13825)"
    设长度为 $n\le 10^9$ 的序列 $\{a_i\}$ 初始为 $a_i = i$．需要进行如下操作：
    
    -   将某区间每一个数加上 $k$．
    -   求出某区间每一个数的和．

??? note "解答"
    由于 $n$ 过大，不能直接建树，需要动态开点．又因为尚未修改过的区间信息并非单位元，空结点的信息需要由其区间端点算出，创建新结点时也要据此初始化．这也意味着下传标记、合并子结点信息时，都需要传入当前区间的端点．
    
    就本题而言，其实还可以把初始值的贡献单独算出，线段树只维护各元素的增量．此时空结点的增量之和为 $0$，恰是单位元，创建结点和合并信息都无需再考虑区间端点；但施加区间加时仍需知道区间长度，因此它只能由递归参数提供，不能并入区间信息．
    
    由于本题没有强制在线，也可以先把所有操作存下来，将端点离散化，再用普通线段树处理．离散化后，每个叶结点对应原序列的一段连续区间，其信息需要按该段的长度和元素之和初始化．
    
    === "实现 1"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <vector>

        using u64 = unsigned long long;

        // --8<-- [start:info]
        // Interval length and sum of elements.
        struct Info {
          u64 len, sum;

          Info(u64 _len = 0, u64 _sum = 0) : len(_len), sum(_sum) {}

          Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // --8<-- [end:info]
        // --8<-- [start:transform]
        // Range add.
        struct Transform {
          u64 a;

          Transform(u64 _a = 0) : a(_a) {}

          explicit operator bool() const { return a != 0; }

          Transform operator+(const Transform& o) const { return Transform(a + o.a); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& v) const {
            return Info(v.len, v.sum + a * v.len);
          }
        };

        // --8<-- [end:transform]
        // --8<-- [start:seg-tree]
        // Segment Tree Implementation. Dynamic node allocation.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        Info blank(int ll, int rr) {
          return Info(rr - ll + 1, rr * (rr + 1ULL) / 2 - ll * (ll - 1ULL) / 2);
        }

        Info info_of(int cr, int ll, int rr) { return cr ? val[cr] : blank(ll, rr); }

        void push_up(int cr, int ll, int rr) {
          int mm = ll + ((rr - ll) >> 1);
          val[cr] = info_of(lc(cr), ll, mm) + info_of(rc(cr), mm + 1, rr);
        }

        // Build an empty tree.
        void build(int l, int r, int n) {
          rt = 0, id = 0, L = l, R = r;
          ch.resize(n), val.resize(n), lazy.resize(n);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int& cr, int ll, int rr, const Transform& f) {
          if (!cr) val[cr = ++id] = blank(ll, rr);
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr, int ll, int rr) {
          if (!lazy[cr]) return;
          int mm = ll + ((rr - ll) >> 1);
          lazy_update(lc(cr), ll, mm, lazy[cr]);
          lazy_update(rc(cr), mm + 1, rr, lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (!cr) return blank(std::max(ll, tl), std::min(rr, tr));
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int& cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (!cr) val[cr = ++id] = blank(ll, rr);
          if (tl <= ll && rr <= tr) return lazy_update(cr, ll, rr, f);
          push_down(cr, ll, rr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr, ll, rr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, m;
          std::cin >> n >> m;
          build(1, n, 1.5e7);
          for (; m; --m) {
            int op;
            std::cin >> op;
            if (op == 1) {
              int l, r, k;
              std::cin >> l >> r >> k;
              modify(l, r, Transform(k));
            } else if (op == 2) {
              int l, r;
              std::cin >> l >> r;
              std::cout << query(l, r).sum << '\n';
            }
          }
          return 0;
        }
        ```
    
    === "实现 2"
        ```cpp
        #include <algorithm>
        #include <iostream>
        #include <vector>

        class SegmentTree {
          static constexpr int N = 2e7;
          int rt, id, L, R;
          std::vector<int> lc, rc;
          std::vector<unsigned long long> sum;
          std::vector<unsigned long long> lz;

          void lazy_update(int& cr, int ll, int rr, unsigned long long v) {
            if (!cr) cr = ++id;
            sum[cr] += v * (rr - ll + 1);
            lz[cr] += v;
          }

          void push_down(int cr, int ll, int rr) {
            if (!lz[cr]) return;
            int mm = (ll + rr) >> 1;
            lazy_update(lc[cr], ll, mm, lz[cr]);
            lazy_update(rc[cr], mm + 1, rr, lz[cr]);
            lz[cr] = 0;
          }

          void add(int& cr, int ll, int rr, int tl, int tr, int k) {
            if (!cr) cr = ++id;
            if (tl <= ll && rr <= tr) return lazy_update(cr, ll, rr, k);
            push_down(cr, ll, rr);
            int mm = (ll + rr) / 2;
            if (tl <= mm) add(lc[cr], ll, mm, tl, tr, k);
            if (mm < tr) add(rc[cr], mm + 1, rr, tl, tr, k);
            sum[cr] = sum[lc[cr]] + sum[rc[cr]];
          }

          unsigned long long query(int cr, int ll, int rr, int tl, int tr) {
            if (!cr) return 0;
            if (tl <= ll && rr <= tr) return sum[cr];
            push_down(cr, ll, rr);
            int mm = (ll + rr) / 2;
            unsigned long long res = 0;
            if (tl <= mm) res = query(lc[cr], ll, mm, tl, tr);
            if (mm < tr) res += query(rc[cr], mm + 1, rr, tl, tr);
            return res;
          }

         public:
          SegmentTree(int n) : rt(0), id(0), L(1), R(n), lc(N), rc(N), sum(N), lz(N) {}

          void add(int l, int r, int k) { add(rt, L, R, l, r, k); }

          unsigned long long query(int l, int r) { return query(rt, L, R, l, r); }
        };

        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, m;
          std::cin >> n >> m;
          SegmentTree seg(n);
          for (; m; --m) {
            int op;
            std::cin >> op;
            if (op == 1) {
              int l, r, k;
              std::cin >> l >> r >> k;
              seg.add(l, r, k);
            } else if (op == 2) {
              int l, r;
              std::cin >> l >> r;
              auto res = (r + 1ULL) * r / 2 - (l - 1ULL) * l / 2;
              std::cout << (res + seg.query(l, r)) << '\n';
            }
          }
          return 0;
        }
        ```
    
    === "实现 3"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <unordered_map>
        #include <vector>

        using u64 = unsigned long long;

        // --8<-- [start:info]
        // Interval length and sum of elements.
        struct Info {
          u64 len, sum;

          Info(u64 _len = 0, u64 _sum = 0) : len(_len), sum(_sum) {}

          Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        // --8<-- [end:info]
        // --8<-- [start:transform]
        // Range add.
        struct Transform {
          u64 a;

          Transform(u64 _a = 0) : a(_a) {}

          explicit operator bool() const { return a != 0; }

          Transform operator+(const Transform& o) const { return Transform(a + o.a); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& v) const {
            return Info(v.len, v.sum + a * v.len);
          }
        };

        // --8<-- [end:transform]
        // --8<-- [start:seg-tree]
        // Segment Tree.
        // --8<-- [start:build]
        // Recursive structure, stored in a full binary tree.
        #define lc(x) ch[(x)][0]
        #define rc(x) ch[(x)][1]

        int rt, id, L, R;
        std::vector<std::array<int, 2>> ch;
        std::vector<Info> val;
        std::vector<Transform> lazy;

        void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

        // Build the tree based on info stored in vec (0-indexed).
        void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
          if (ll == rr) return (void)(val[cr] = vec[ll - L]);
          int mm = ll + ((rr - ll) >> 1);
          build(lc(cr) = ++id, ll, mm, vec);
          build(rc(cr) = ++id, mm + 1, rr, vec);
          push_up(cr);
        }

        void build(int l, int r, const std::vector<Info>& vec) {
          rt = 1, id = 0, L = l, R = r;
          int n = R - L + 1;
          ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
          build(rt = ++id, L, R, vec);
        }

        // --8<-- [end:build]
        // --8<-- [start:tag]
        // Lazy update.
        void lazy_update(int cr, const Transform& f) {
          val[cr] = f(val[cr]);
          lazy[cr] += f;
        }

        // Push down lazy tag.
        void push_down(int cr) {
          if (!lazy[cr]) return;
          lazy_update(lc(cr), lazy[cr]);
          lazy_update(rc(cr), lazy[cr]);
          lazy[cr] = Transform();
        }

        // --8<-- [end:tag]
        // --8<-- [start:range-get]
        // Query info in [l, r].
        Info query(int cr, int ll, int rr, int tl, int tr) {
          if (tl <= ll && rr <= tr) return val[cr];
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          Info res;
          if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
          if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
          return res;
        }

        Info query(int l, int r) { return query(rt, L, R, l, r); }

        // --8<-- [end:range-get]
        // --8<-- [start:range-set]
        // Apply transformation f to the range [l, r].
        void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
          if (tl <= ll && rr <= tr) return lazy_update(cr, f);
          push_down(cr);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
          if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
          push_up(cr);
        }

        void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

        // --8<-- [end:range-set]
        // --8<-- [end:seg-tree]
        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n, m;
          std::cin >> n >> m;
          // Offline queries and discretization.
          std::vector<std::array<int, 4>> queries(m);
          std::vector<int> loc;
          loc.reserve((m << 1) | 1);
          loc.push_back(0);
          for (auto& q : queries) {
            std::cin >> q[0] >> q[1] >> q[2];
            if (q[0] == 1) std::cin >> q[3];
            loc.push_back(q[1] - 1);
            loc.push_back(q[2]);
          }
          std::sort(loc.begin(), loc.end());
          loc.erase(std::unique(loc.begin(), loc.end()), loc.end());
          int sz = loc.size();
          std::unordered_map<int, int> ids;
          for (int i = 0; i < sz; ++i) ids[loc[i]] = i;
          std::vector<Info> vec(sz);
          for (int i = 1; i < sz; ++i) {
            vec[i].len = loc[i] - loc[i - 1];
            vec[i].sum = vec[i].len * (loc[i] + loc[i - 1] + 1ULL) / 2;
          }
          // Ordinary seg tree operations.
          build(0, sz - 1, vec);
          for (auto q : queries) {
            if (q[0] == 1) {
              modify(ids[q[1] - 1] + 1, ids[q[2]], Transform(q[3]));
            } else if (q[0] == 2) {
              std::cout << query(ids[q[1] - 1] + 1, ids[q[2]]).sum << '\n';
            }
          }
          return 0;
        }
        ```

???+ example "[Luogu P5490【模板】扫描线 & 矩形面积并](https://www.luogu.com.cn/problem/P5490)"
    求 $n$ 个四边平行于坐标轴的矩形的面积并．

??? note "解答"
    这是一道 [扫描线](../geometry/scanning.md#二维矩形面积并问题) 模板题．利用扫描线转化问题的细节请参考所引页面，此处只讨论转化后的数据结构．转化后需要维护的是一个支持区间加减覆盖层数的结构：每次操作给某段区间的覆盖层数加一或减一，每次查询覆盖层数至少为一的位置的总长度．
    
    考虑利用线段树实现这些区间操作．一种自然的想法是，每个结点处维护该区间的覆盖层数和覆盖层数至少为一的总长度．但是，区间一旦整体覆盖，子区间各自的覆盖情况就从总长度中丢失了，之后撤去这层覆盖便无从恢复．解决办法是把两类操作分开记录：覆盖层数只计入恰好整体覆盖该区间的操作，总长度只统计记录在子孙结点上的覆盖长度．于是，该区间实际覆盖到的长度就是：覆盖层数大于零时为区间长度，否则为记录的总长度．合并时，把两个子结点各自算出的实际长度相加，即为本结点的总长度．这样一来，覆盖层数就不能下传了，因为每次覆盖的加入与移除落在同一组结点处，只有让层数留在原处才能相互抵消．这正是标记永久化．
    
    当然，本题也可以用前文的线段树模板实现．只需将区间信息设为该区间内的最小覆盖层数，以及取得该最小值的部分的总长度．容易验证，这样的信息空间是幺半群，而加减覆盖层数是其上的自同态，于是区间修改和区间查询都可以照搬模板．要得到覆盖到的总长度，用整段区间的长度减去覆盖层数为零的部分的长度即可；而后者就是最小覆盖层数为零时所记录的长度，否则为零．
    
    === "实现 1"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <unordered_map>
        #include <vector>

        struct Info {
          int len;  // Length of this interval.
          int cnt;  // Number of operations that cover this interval exactly.
          int tot;  // Length covered by operations recorded in the descendants.
        };

        // Segment tree.
        int rt, id, L, R;
        std::vector<int> lc, rc;
        std::vector<Info> val;

        // Build the tree.
        void build(int cr, int ll, int rr, const std::vector<int>& vec) {
          if (ll == rr) return (void)(val[cr].len = (ll ? vec[ll] - vec[ll - 1] : 0));
          int mm = ll + ((rr - ll) >> 1);
          build(lc[cr] = ++id, ll, mm, vec);
          build(rc[cr] = ++id, mm + 1, rr, vec);
          val[cr].len = val[lc[cr]].len + val[rc[cr]].len;
        }

        void build(int n, const std::vector<int>& vec) {
          rt = 0, id = 0, L = 0, R = n - 1;
          lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1);
          build(rt = ++id, 0, n - 1, vec);
        }

        // Query.
        int query(int cr) { return val[cr].cnt ? val[cr].len : val[cr].tot; }

        int query() { return query(rt); }

        // Cover.
        void cover(int cr, int ll, int rr, int tl, int tr, int v) {
          if (tl <= ll && rr <= tr) return (void)(val[cr].cnt += v);
          int mm = ll + ((rr - ll) >> 1);
          if (tl <= mm) cover(lc[cr], ll, mm, tl, tr, v);
          if (mm < tr) cover(rc[cr], mm + 1, rr, tl, tr, v);
          val[cr].tot = query(lc[cr]) + query(rc[cr]);
        }

        void cover(int l, int r, int v) { cover(rt, L, R, l, r, v); }

        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n;
          std::cin >> n;
          // Scanning and discretizing.
          std::vector<std::array<int, 4>> ops;
          ops.reserve(n << 1);
          std::vector<int> locs;
          locs.reserve(n << 1);
          for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            ops.push_back({x1, y1, y2, 1});
            ops.push_back({x2, y1, y2, -1});
            locs.push_back(y1);
            locs.push_back(y2);
          }
          std::sort(ops.begin(), ops.end());
          std::sort(locs.begin(), locs.end());
          locs.erase(std::unique(locs.begin(), locs.end()), locs.end());
          int m = locs.size();
          std::unordered_map<int, int> ids;
          for (int i = 0; i < m; ++i) ids[locs[i]] = i;
          // Segment tree operations.
          build(m, locs);
          long long res = 0;
          for (int l = 0, r; l < (n << 1); l = r) {
            for (r = l; r < (n << 1) && ops[r][0] == ops[l][0]; ++r) {
              cover(ids[ops[r][1]] + 1, ids[ops[r][2]], ops[r][3]);
            }
            if (r < (n << 1)) res += (long long)(ops[r][0] - ops[l][0]) * query();
          }
          std::cout << res << std::endl;
          return 0;
        }
        ```
    
    === "实现 2"
        ```cpp
        #include <algorithm>
        #include <array>
        #include <climits>
        #include <iostream>
        #include <unordered_map>
        #include <vector>

        struct Info {
          int cnt;  // Minimum cover count over this interval.
          int len;  // Total length of the parts attaining that minimum.

          Info(int _cnt = INT_MAX, int _len = 0) : cnt(_cnt), len(_len) {}

          Info operator+(const Info& o) const {
            return cnt < o.cnt ? *this : (cnt > o.cnt ? o : Info(cnt, len + o.len));
          }

          Info& operator+=(const Info& o) { return *this = *this + o; }
        };

        struct Transform {
          int v;

          Transform(int _v = 0) : v(_v) {}

          explicit operator bool() const { return v != 0; }

          Transform operator+(const Transform& o) const { return Transform(v + o.v); }

          Transform& operator+=(const Transform& o) { return *this = *this + o; }

          Info operator()(const Info& x) const {
            return Info(x.cnt == INT_MAX ? INT_MAX : x.cnt + v, x.len);
          }
        };

        class SegmentTree {
          int rt, id, L, R;
          std::vector<int> lc, rc;
          std::vector<Info> val;
          std::vector<Transform> lz;

          void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

          void lazy_update(int cr, const Transform& f) {
            val[cr] = f(val[cr]);
            lz[cr] += f;
          }

          void push_down(int cr) {
            if (!lz[cr]) return;
            lazy_update(lc[cr], lz[cr]);
            lazy_update(rc[cr], lz[cr]);
            lz[cr] = Transform();
          }

          void build(int cr, int ll, int rr, const std::vector<int>& locs) {
            if (ll == rr)
              return (void)(val[cr] = Info(0, ll ? locs[ll] - locs[ll - 1] : 0));
            int mm = ll + ((rr - ll) >> 1);
            build(lc[cr] = ++id, ll, mm, locs);
            build(rc[cr] = ++id, mm + 1, rr, locs);
            push_up(cr);
          }

          void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
            if (tl <= ll && rr <= tr) return lazy_update(cr, f);
            push_down(cr);
            int mm = ll + ((rr - ll) >> 1);
            if (tl <= mm) modify(lc[cr], ll, mm, tl, tr, f);
            if (mm < tr) modify(rc[cr], mm + 1, rr, tl, tr, f);
            push_up(cr);
          }

         public:
          SegmentTree(int n, const std::vector<int>& locs) {
            rt = 0, id = 0, L = 0, R = n - 1;
            lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1), lz.resize(n << 1);
            build(rt = ++id, L, R, locs);
          }

          void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

          Info query() const { return val[rt]; }
        };

        int main() {
          std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
          int n;
          std::cin >> n;
          // Scanning and discretizing.
          std::vector<std::array<int, 4>> ops;
          ops.reserve(n << 1);
          std::vector<int> locs;
          locs.reserve(n << 1);
          for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            ops.push_back({x1, y1, y2, 1});
            ops.push_back({x2, y1, y2, -1});
            locs.push_back(y1);
            locs.push_back(y2);
          }
          std::sort(ops.begin(), ops.end());
          std::sort(locs.begin(), locs.end());
          locs.erase(std::unique(locs.begin(), locs.end()), locs.end());
          int m = locs.size();
          std::unordered_map<int, int> ids;
          for (int i = 0; i < m; ++i) ids[locs[i]] = i;
          // Segment tree operations.
          long long all = locs.back() - locs[0];
          SegmentTree seg(m, locs);
          long long res = 0;
          for (int l = 0, r; l < (n << 1); l = r) {
            for (r = l; r < (n << 1) && ops[r][0] == ops[l][0]; ++r) {
              seg.modify(ids[ops[r][1]] + 1, ids[ops[r][2]], Transform(ops[r][3]));
            }
            if (r < (n << 1)) res += (ops[r][0] - ops[l][0]) * (all - seg.query().len);
          }
          std::cout << res << std::endl;
          return 0;
        }
        ```

???+ example "[Luogu P2894【USACO08FEB】Hotel G](https://www.luogu.com.cn/problem/P2894)"
    有 $n$ 个房间，初始都是空房．需要进行如下操作：
    
    -   找到长度为 $x$ 的连续空房．如果存在，让它们住上人．
    -   房间 $[x,x+y-1]$ 退房．
    
    每次进行第一个操作时，输出连续 $x$ 个空房中最小的房间号；若不存在，返回 $0$．

??? note "解答"
    考虑构造线段树，维护每个区间中连续空房的最大长度．为了合并这一信息，还需维护最长空房前缀、最长空房后缀和区间长度：跨越中点的连续空房，恰是左子区间的最长后缀接上右子区间的最长前缀．懒惰标记只需实现区间赋值，即整段置为空或置为已住；不修改的情形记录为特殊值（例如 $-1$）．要找最小的可用房号，只需查询最小的 $r$，使得 $[1,r]$ 中连续空房的最大长度不小于 $x$，房号即 $r-x+1$．为此，利用线段树二分实现即可．
    
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>

    // Interval info.
    // lt - longest prefix run.
    // rt - longest suffix run.
    // ma - longest run.
    // len - interval length.
    struct Info {
      int lt, rt, ma, len;

      Info(int _lt = 0, int _rt = 0, int _ma = 0, int _len = 0)
          : lt(_lt), rt(_rt), ma(_ma), len(_len) {}

      Info operator+(const Info& o) const {
        auto _lt = lt == len ? len + o.lt : lt;
        auto _rt = o.rt == o.len ? rt + o.len : o.rt;
        return Info(_lt, _rt, std::max({_lt, _rt, rt + o.lt, ma, o.ma}),
                    len + o.len);
      }

      Info& operator+=(const Info& o) { return *this = *this + o; }
    };

    // Assignment.
    struct Transform {
      int v;

      Transform(int _v = -1) : v(_v) {}

      explicit operator bool() const { return v != -1; }

      Transform operator+(const Transform& o) const { return o ? o : *this; }

      Transform& operator+=(const Transform& o) { return *this = *this + o; }

      Info operator()(const Info& x) const {
        return v == 1 ? Info(0, 0, 0, x.len)
                      : (v == 0 ? Info(x.len, x.len, x.len, x.len) : x);
      }
    };

    // Segment tree.
    class SegmentTree {
      int rt, id, L, R;
      std::vector<int> lc, rc;
      std::vector<Info> val;
      std::vector<Transform> lz;

      void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

      void lazy_update(int cr, const Transform& f) {
        val[cr] = f(val[cr]);
        lz[cr] += f;
      }

      void push_down(int cr) {
        if (!lz[cr]) return;
        lazy_update(lc[cr], lz[cr]);
        lazy_update(rc[cr], lz[cr]);
        lz[cr] = Transform();
      }

      void build(int cr, int ll, int rr) {
        if (ll == rr) return (void)(val[cr] = Info(1, 1, 1, 1));
        int mm = ll + ((rr - ll) >> 1);
        build(lc[cr] = ++id, ll, mm);
        build(rc[cr] = ++id, mm + 1, rr);
        push_up(cr);
      }

      void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
        if (tl <= ll && rr <= tr) return lazy_update(cr, f);
        push_down(cr);
        int mm = ll + ((rr - ll) >> 1);
        if (tl <= mm) modify(lc[cr], ll, mm, tl, tr, f);
        if (mm < tr) modify(rc[cr], mm + 1, rr, tl, tr, f);
        push_up(cr);
      }

      template <typename G>
      int lower_bound(int cr, int ll, int rr, const G& g, const Info& acc) {
        if (ll == rr) return ll;
        push_down(cr);
        int mm = ll + ((rr - ll) >> 1);
        return g(acc + val[lc[cr]])
                   ? lower_bound(lc[cr], ll, mm, g, acc)
                   : lower_bound(rc[cr], mm + 1, rr, g, acc + val[lc[cr]]);
      }

     public:
      SegmentTree(int n) : rt(0), id(0), L(1), R(n) {
        lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1), lz.resize(n << 1);
        build(rt = ++id, L, R);
      }

      // Apply f to [l,r].
      void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

      // Find the lowest r such that g(info([1,r])) is true.
      template <typename G>
      int lower_bound(const G& g) {
        return g(val[rt]) ? lower_bound(rt, L, R, g, Info()) : R + 1;
      }
    };

    int main() {
      int n, m;
      std::cin >> n >> m;
      SegmentTree seg(n);
      for (; m; --m) {
        int op;
        std::cin >> op;
        if (op == 1) {
          int x;
          std::cin >> x;
          auto y =
              seg.lower_bound([&](const Info& v) -> bool { return v.ma >= x; });
          if (y <= n) {
            std::cout << (y - x + 1) << '\n';
            seg.modify(y - x + 1, y, Transform(1));
          } else {
            std::cout << 0 << '\n';
          }
        } else if (op == 2) {
          int x, y;
          std::cin >> x >> y;
          seg.modify(x, x + y - 1, Transform(0));
        }
      }
      return 0;
    }
    ```

???+ example "[Luogu P1168 中位数](https://www.luogu.com.cn/problem/P1168)"
    给定长度为 $n$ 的数列．对于每一个奇数 $i\le n$，输出前 $i$ 个数的中位数．

??? note "解答"
    中位数只与元素的大小关系有关，与它们在数列中的位置无关，因此可以用权值线段树维护．依次插入各个元素，每插入奇数个后查询第 $(i+1)/2$ 小的元素即可．只需要实现插入和查询第 $k$ 小两种操作．
    
    ```cpp
    #include <iostream>
    #include <vector>

    class SegmentTree {
      int rt, id, L, R;
      std::vector<int> lc, rc;
      std::vector<int> cnt;

      void insert(int& cr, int ll, int rr, int v) {
        if (!cr) cr = ++id;
        ++cnt[cr];
        if (ll == rr) return;
        int mm = ll + ((rr - ll) >> 1);
        if (v <= mm)
          insert(lc[cr], ll, mm, v);
        else
          insert(rc[cr], mm + 1, rr, v);
      }

      int find_kth(int cr, int ll, int rr, int k) {
        if (ll == rr) return ll;
        int mm = ll + ((rr - ll) >> 1);
        if (k <= cnt[lc[cr]])
          return find_kth(lc[cr], ll, mm, k);
        else
          return find_kth(rc[cr], mm + 1, rr, k - cnt[lc[cr]]);
      }

     public:
      SegmentTree(int l, int r, int n)
          : rt(0), id(0), L(l), R(r), lc(n), rc(n), cnt(n) {}

      void insert(int v) { insert(rt, L, R, v); }

      int find_kth(int k) { return find_kth(rt, L, R, k); }
    };

    int main() {
      int n;
      std::cin >> n;
      SegmentTree seg(0, 1e9, 5e6);
      for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        seg.insert(v);
        if (~i & 1) std::cout << seg.find_kth((i >> 1) + 1) << '\n';
      }
      return 0;
    }
    ```

## 习题

基础实现与区间信息设计：

-   [Luogu P2574 XOR 的艺术](https://www.luogu.com.cn/problem/P2574)
-   [Luogu P4588【TJOI2018】数学计算](https://www.luogu.com.cn/problem/P4588)
-   [Luogu P1253 扶苏的问题](https://www.luogu.com.cn/problem/P1253)
-   [Luogu P1471 方差](https://www.luogu.com.cn/problem/P1471)
-   [Luogu P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)
-   [Luogu P2572【SCOI2010】序列操作](https://www.luogu.com.cn/problem/P2572)

动态开点：

-   [Codeforces 915 E. Physical Education Lessons](https://codeforces.com/problemset/problem/915/E)
-   [Library Checker - Range Affine Range Sum (Large Array)](https://judge.yosupo.jp/problem/range_affine_range_sum_large_array)
-   [Codeforces 817 F. MEX Queries](https://codeforces.com/problemset/problem/817/F)

标记永久化：

-   [Luogu P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502)
-   [2018 Multi-University Training Contest 5 G. Glad You Came](https://acm.hdu.edu.cn/showproblem.php?pid=6356)

线段树二分：

-   [AtCoder Library Practice Contest J - Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_j)
-   [AtCoder Beginner Contest 292 Ex - Rating Estimator](https://atcoder.jp/contests/abc292/tasks/abc292_h)
-   [Luogu P4137 Rmq Problem/mex](https://www.luogu.com.cn/problem/P4137)
-   [Codeforces 773 E. Blog Post Rating](https://codeforces.com/problemset/problem/773/E)
-   [Codeforces 407 E. k-d-sequence](https://codeforces.com/problemset/problem/407/E)
-   [Codeforces 671 E. Organizing a Race](https://codeforces.com/problemset/problem/671/E)

权值线段树：

-   [Luogu P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
-   [Luogu P1801 黑匣子](https://www.luogu.com.cn/problem/P1801)
-   [Luogu P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)
-   [Luogu P2286【HNOI2004】宠物收养场](https://www.luogu.com.cn/problem/P2286)

## 应用：线段树优化建图

在建图连边的过程中，我们有时会碰到这种题目，一个点向一段连续的区间中的点连边或者一个连续的区间向一个点连边，如果我们真的一条一条连过去，那一旦点的数量多了复杂度就爆炸了，这里就需要用线段树的区间性质来优化我们的建图了．

下面是一个线段树．

![](./images/segt5.svg)

每个结点都代表了一段区间，假设我们要向区间 $[2, 4]$ 连边．

![](./images/segt6.svg)

在一些题目中，还会出现一段区间连向一个点的情况，则我们将上面第一张图的有向边全部反过来即可，上面的树叫做入树，下面这个叫做出树．

![](./images/segt7.svg)

???+ note "[Legacy](https://codeforces.com/problemset/problem/786/B)"
    题目大意：有 $n$ 个点、$q$ 次操作．每一种操作为以下三种类型中的一种：
    
    -   操作一：连一条 $u \rightarrow v$ 的有向边，权值为 $w$．
    -   操作二：对于所有 $i \in [l,r]$ 连一条 $u \rightarrow i$ 的有向边，权值为 $w$．
    -   操作三：对于所有 $i \in [l,r]$ 连一条 $i \rightarrow u$ 的有向边，权值为 $w$．
    
    求从点 $s$ 到其他点的最短路．
    
    $1 \le n,q \le 10^5, 1 \le w \le 10^9$．
    
    ??? note "参考代码"
        ```cpp
        #include <bitset>
        #include <iostream>
        #include <queue>
        #include <vector>
        using namespace std;
        using ll = long long;

        constexpr int N = 1e5 + 5;

        using pil = pair<int, ll>;
        using pli = pair<ll, int>;

        int n, q, s, tot, rt1, rt2;
        int pos[N];
        ll dis[N << 3];
        vector<pil> e[N << 3];
        bitset<(N << 3)> vis;

        struct seg {
          int l, r, lson, rson;
        } t[N << 3];

        int ls(int u) {  // 左儿子
          return t[u].lson;
        }

        int rs(int u) {  // 右儿子
          return t[u].rson;
        }

        void build(int &u, int l, int r) {  // 动态开点建造入树
          u = ++tot;
          t[u] = seg{l, r};
          if (l == r) {
            pos[l] = u;
            return;
          }
          int mid = (l + r) >> 1;
          build(t[u].lson, l, mid);
          build(t[u].rson, mid + 1, r);
          e[u].emplace_back(ls(u), 0);
          e[u].emplace_back(rs(u), 0);
        }

        void build2(int &u, int l, int r) {  // 动态开点建造出树
          if (l == r) {
            u = pos[l];
            return;
          }
          u = ++tot;
          t[u] = seg{l, r};
          int mid = (l + r) >> 1;
          build2(t[u].lson, l, mid);
          build2(t[u].rson, mid + 1, r);
          e[ls(u)].emplace_back(u, 0);
          e[rs(u)].emplace_back(u, 0);
        }

        void add1(int u, int lr, int rr, int v, ll w) {  // 点向区间连边
          if (lr <= t[u].l && t[u].r <= rr) {
            e[v].emplace_back(u, w);
            return;
          }
          int mid = (t[u].l + t[u].r) >> 1;
          if (lr <= mid) {
            add1(ls(u), lr, rr, v, w);
          }
          if (rr > mid) {
            add1(rs(u), lr, rr, v, w);
          }
        }

        void add2(int u, int lr, int rr, int v, ll w) {  // 区间向点连边
          if (lr <= t[u].l && t[u].r <= rr) {
            e[u].emplace_back(v, w);
            return;
          }
          int mid = (t[u].l + t[u].r) >> 1;
          if (lr <= mid) {
            add2(ls(u), lr, rr, v, w);
          }
          if (rr > mid) {
            add2(rs(u), lr, rr, v, w);
          }
        }

        void dij(int S) {
          priority_queue<pli, vector<pli>, greater<pli>> q;
          int tot = (n << 2);
          for (int i = 1; i <= tot; ++i) {
            dis[i] = 1e18;
          }
          dis[S] = 0;
          q.emplace(dis[S], S);
          while (!q.empty()) {
            pli fr = q.top();
            q.pop();
            int u = fr.second;
            if (vis[u]) continue;
            for (pil it : e[u]) {
              int v = it.first;
              ll w = it.second;
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.emplace(dis[v], v);
              }
            }
          }
        }

        int main() {
          cin.tie(nullptr)->sync_with_stdio(false);
          cin >> n >> q >> s;
          build(rt1, 1, n);
          build2(rt2, 1, n);
          for (int i = 1, op, u; i <= q; ++i) {
            cin >> op >> u;
            if (op == 1) {
              int v;
              ll w;
              cin >> v >> w;
              e[pos[u]].emplace_back(pos[v], w);
            } else if (op == 2) {
              int l, r;
              ll w;
              cin >> l >> r >> w;
              add1(rt1, l, r, pos[u], w);
            } else {
              int l, r;
              ll w;
              cin >> l >> r >> w;
              add2(rt2, l, r, pos[u], w);
            }
          }
          dij(pos[s]);
          for (int i = 1; i <= n; ++i) {
            if (dis[pos[i]] == 1e18) {
              cout << "-1 ";
            } else {
              cout << dis[pos[i]] << ' ';
            }
          }
          return 0;
        }
        ```

## 参考资料与注释

-   [统计的力量 - 张昆玮](https://github.com/hzwer/shareOI/blob/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E7%BB%9F%E8%AE%A1%E7%9A%84%E5%8A%9B%E9%87%8F%E2%80%94%E2%80%94%E7%BA%BF%E6%AE%B5%E6%A0%91%E5%85%A8%E6%8E%A5%E8%A7%A6_%E5%BC%A0%E6%98%86%E7%8E%AE.pptx)
-   [Generalizing Segment Trees by Eklavya](https://sharmaeklavya2.github.io/blog/generalizing-segment-trees.html)
-   [线段树进阶 Part 1 by Alex\_Wei - 洛谷](https://www.luogu.com.cn/article/r1mp3hga)

[^monoid]: 严格地说，线段树维护的信息只需构成半群，不必要求单位元存在．递归实现中用到单位元，通常是因为区间查询以它作为累计信息的初值；改为按相交情况分类讨论即可避开．不过，非递归实现中的多余叶结点和动态开点中的空结点都绕不开单位元．退一步说，即使确实需要，也总可以向半群 $S$ 中添加一个元素 $e$，规定它与任意元素运算的结果都是该元素本身，从而得到幺半群 $S\cup\{e\}$．本文为表述方便，总是假定维护的是幺半群信息．

[^endo]: 类似区间信息处的讨论，很多实现中单位元并不会作为修改操作的输入，此时就不必要求这条性质，只需要修改操作是半群上的自同态即可．但是，在后文标记永久化的非递归实现中，累计信息的初值就是单位元，且会逐层施加沿途的标记，这条性质不可忽略．本文为表述方便，总是假定修改操作是幺半群上的自同态．

[^child-id]: 实际上，当如图所示按照前序遍历编号时，右子结点编号可以由当前结点编号和左子树大小计算得到，而左子树大小可以通过区间长度计算．由于递归访问线段树结点时，通常都会维护区间左右端点，所以右子结点编号也是可以直接计算的．

[^heap-size]: 考察二叉树占用的空间 $2^{\lceil\log_2N\rceil+1}$ 与线段树规模 $N$ 的比值．前者只与二叉树的高度有关．当线段树高度为 $k$ 时，线段树的最小规模为 $N = 2^{k-1}+1$．相应地，二者比值为 $(4N-4)/N = 4 - 4/N$，上确界为 $4$．这就是为什么存储规模为 $N$ 的线段树时，需要为相应的完美二叉树开辟大小为 $4N$ 的数组．

[^assign]: 区间赋值操作本身不可交换．如果同时记录赋值操作的时间戳 $t$，并规定标记 $(v_1,t_1)$ 与 $(v_2,t_2)$ 的复合取其中时间戳较大者，就得到了可交换的标记．利用这一方法，可以实现支持区间赋值和单点查询的标记永久化线段树：查询时沿途取时间戳最大的标记，作用于叶结点即可．但是，它无法支持区间查询，因为 $(v,t)$ 并非信息空间上的自同态：一段区间中，哪些位置已有更晚的赋值覆盖，无法从这段区间的信息中得知．
