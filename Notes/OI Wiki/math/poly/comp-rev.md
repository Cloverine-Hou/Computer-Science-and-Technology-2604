形式幂级数的复合和复合逆也是常见的形式幂级数操作，对于没有特殊性质的 $f$ 之前我们一直使用的多是 $O\left(n^2\right)$ 的算法（该算法仍需使用 FFT）来计算 $f(g) \bmod{x^n}$ 其中 $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，但是因为效率较低应用较少．我们介绍 Kinoshita–Li 的 $O\left(\mathsf{M}\left(n\right)\log n\right)$ 的算法，其中 $O\left(\mathsf{M}\left(n\right)\right)$ 为两个次数为 $O\left( n\right)$ 的多项式相乘的时间．

## 形式幂级数/多项式的复合

若要计算 $f\left(g\left(x\right)\right)\bmod{x^n}$ 那么需要 $f\left(g\left(x\right)\right)$ 的每一项系数都是有限项之和，所以之前要求 $f(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g(x)\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，而如果 $f(x),g(x)\in\mathbb{C}\left\lbrack x\right\rbrack$ 也可以满足这个条件．因为我们需要将 $f\left(g\left(x\right)\right)$ 的系数截断，不妨直接考虑 $f(x),g(x)$ 都是多项式的情况．对于 $f(x)=\sum_{j=0}^{n-1}f_jx^j$，有

$$
f\left(g\left(x\right)\right)=\sum_{j=0}^{n-1}f_jg\left(x\right)^j
$$

我们考虑环 $\mathbb{C}\left\lbrack x\right\rbrack\left(\left( y\right)\right)$ 上的有理函数

$$
\begin{aligned}
\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}&=\sum_{j\geq 0}\left(\cdots +f_jy^{-j}+\cdots\right)g(x)^jy^j \\
f\left(g\left(x\right)\right)&=\left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}
\end{aligned}
$$

根据 [常系数齐次线性递推](./linear-recurrence.md) 中提到的 Bostan–Mori 算法，Kinoshita 和 Li 指出可以将其修改为二元形式：

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V(x^2,y)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

这样递归的计算在 $n=1$ 时我们只需计算

$$
\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)
$$

在计算 $\dfrac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\in\mathbb{C}\left\lbrack z\right\rbrack\left(\left( y\right)\right)$ 时我们不需要保留所有 $y$ 的系数，因为最后我们只需要提取 $y^0$ 的系数，所以 $y^{>0}$ 的系数是不需要的，而因为求出前者之后需要将其乘以若干个形如 $Q(-x,y)\in\mathbb{C}\left\lbrack x,y\right\rbrack$ 的「**多项式**」，所以只需要保留对于 $y^0$ 有贡献的系数即可．我们准备好给出伪代码：

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{Comp}}\left(P(y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j< n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P(y)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\left(\left\lbrack y^{-m+1}\right\rbrack\frac{P(y)}{Q(0,y)},\dots ,\left\lbrack y^0\right\rbrack\frac{P(y)}{Q(0,y)}\right) \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n} \\
3&d\gets\deg_y Q\left(-x,y\right)\\
4&\left(t_{-(m+d)+1},\dots ,t_0\right)\gets \operatorname{\mathsf{Comp}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m+d\right) \\
5&T(x,y)\gets \sum_{j=-(m+d)+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-(m+d)+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
7&\textbf{return }\left(u_{-m+1},\dots ,u_0\right)
\end{array}
$$

那么我们有

$$
f\left(g\left(x\right)\right)\bmod{x^n}=\operatorname{\mathsf{Comp}}\left(f\left(y^{-1}\right),1-y\cdot g(x),\max\left\lbrace 1+\deg f,n\right\rbrace ,1\right)\bmod{x^n}
$$

注意第三个参数是因为 $g(0)$ 可能不为零，如果 $\deg f\geq n$ 此时不能截断 $f(x)$ 来计算 $f\left(g(x)\right)$，我们也可以选择计算 $f(g)=f\circ \left(x+g(0)\right)\circ \left(g-g(0)\right)$，此时可以取 $F:=f\left(x+g(0)\right)\bmod{x^n}$ 和 $G:=g-g(0)$ 转而计算 $\operatorname{\mathsf{Comp}}\left(F\left(y^{-1}\right),1-y\cdot G(x),n,1\right)$．

另外因为调用的限制最后递归终止时的 $Q(0,y)^{-1}$ 是可以直接导出的，不需要使用形式幂级数的乘法逆元算法来计算，我们只需计算一次乘法然后提取需要的系数．

## 常见的特殊形式复合

我们常用的 [多项式初等函数](./elementary-func.md) 都可以通过复合计算：

$$
\begin{aligned}
g(0)=1&,\space g^{-1}=1+(1-g)+(1-g)^2+\cdots \\
g(0)=1&,\space \log g=-\dfrac{1-g}{1}-\dfrac{(1-g)^2}{2}-\dfrac{(1-g)^3}{3}-\cdots \\
g(0)=0&,\space \exp g=1+\dfrac{g}{1!}+\dfrac{g^2}{2!}+\dfrac{g^3}{3!}+\cdots \\
g(0)=1&,\space g^e=1+\dfrac{e}{1!}(g-1)+\dfrac{e(e-1)}{2!}(g-1)^2+\cdots
\end{aligned}
$$

在复合逆的计算中我们也会用到求幂函数．

### Kronecker 代换

在分析时间复杂度之前我们先考虑如何作二元多项式乘法，一种想法是将系数「打包」，这一方法由 Kronecker 在 1882 年通过 $y\mapsto x^N$ 将 $R\left\lbrack x,y\right\rbrack$ 上的乘法缩减为 $R\left\lbrack x\right\rbrack$ 上的乘法，但是要求 $N$ 足够大．

不妨设 $\deg_x \left(AB\right)<N$，那么我们计算 $A\left(x,x^N\right)B\left(x,x^N\right)$ 之后仍然可以还原出 $A(x,y)B(x,y)$ 且「打包」和「拆包」的时间为线性．

我们使用 Kronecker 代换再计算一元多项式乘法即可，不难发现在 $n$ 为二的幂时上述算法可以在 $O\left(\mathsf{M}\left(n\right)\log n\right)$ 时间完成，因为每一次递归中 $y$ 的次数翻倍，但是 $x$ 的次数减半．

??? note "模板（[P5373【模板】多项式复合函数](https://www.luogu.com.cn/problem/P5373)）"
    代码相对于原算法作了一些简化及修改，使得代码更短．
    
    ```cpp
    #include <cassert>
    #include <cstdio>
    #include <tuple>
    #include <utility>
    #include <vector>

    using uint = unsigned;
    using ull = unsigned long long;
    constexpr uint MOD = 998244353;

    constexpr uint PowMod(uint a, ull e) {
      for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
      }
    }

    constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

    constexpr uint QUAD_NONRESIDUE = 3;
    constexpr int LOG2_ORD = 23;  // __builtin_ctz(MOD - 1)
    constexpr uint ZETA = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
    constexpr uint INV_ZETA = InvMod(ZETA);

    // 返回做 n 长 FFT 所需的单位根数组，长度为一半
    std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
      assert((n & (n - 1)) == 0);
      if (n / 2 == 0) return {};
      std::vector<uint> root(n / 2), inv_root(n / 2);
      root[0] = inv_root[0] = 1;
      for (int i = 0; (1 << i) < n / 2; ++i)
        root[1 << i] = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
      for (int i = 1; i < n / 2; ++i)
        root[i] = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
        inv_root[i] =
            (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
      return {root, inv_root};
    }

    void Butterfly(int n, uint a[], const uint root[]) {
      assert((n & (n - 1)) == 0);
      for (int i = n; i >= 2; i /= 2)
        for (int j = 0; j < n; j += i)
          for (int k = j; k < j + i / 2; ++k) {
            const uint u = a[k];
            a[k + i / 2] = (ull)a[k + i / 2] * root[j / i] % MOD;
            if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
            if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;
          }
    }

    void InvButterfly(int n, uint a[], const uint root[]) {
      assert((n & (n - 1)) == 0);
      for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
          for (int k = j; k < j + i / 2; ++k) {
            const uint u = a[k];
            if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
            a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
          }
    }

    void FFT(int n, uint a[], const uint root[]) { Butterfly(n, a, root); }

    void InvFFT(int n, uint a[], const uint root[]) {
      InvButterfly(n, a, root);
      const uint inv_n = InvMod(n);
      for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * inv_n % MOD;
    }

    // 形式幂级数复合，求出 f(g) mod x^n 要求 g(0) = 0
    std::vector<uint> FPSComposition(std::vector<uint> f, std::vector<uint> g,
                                     int n) {
      assert(g.empty() || g[0] == 0);
      int len = 1;
      while (len < n) len *= 2;
      std::vector<uint> root, inv_root;
      std::tie(root, inv_root) = GetFFTRoot(len * 4);
      // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
      const auto KinoshitaLi = [&](auto &&KinoshitaLi, const std::vector<uint> &P,
                                   const std::vector<uint> &Q, int d, int n) {
        assert((int)P.size() == d * n);
        assert((int)Q.size() == d * n);
        if (n == 1) return P;
        std::vector<uint> dftQ(d * n * 4);
        for (int i = 0; i < d; ++i)
          for (int j = 0; j < n; ++j) dftQ[i * n * 2 + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        FFT(d * n * 4, dftQ.data(), root.data());
        std::vector<uint> V(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2)
          V[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
        InvFFT(d * n * 2, V.data(), inv_root.data());
        assert(V[0] == 1);
        V[0] = 0;
        for (int i = 1; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i * n + j];
        V.resize(d * n);
        const std::vector<uint> T = KinoshitaLi(KinoshitaLi, P, V, d * 2, n / 2);
        std::vector<uint> dftT(d * n * 2);
        for (int i = 0; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) dftT[i * n + j] = T[i * (n / 2) + j];
        FFT(d * n * 2, dftT.data(), root.data());
        for (int i = 0; i < d * n * 4; i += 2) {
          const uint u = dftQ[i];
          dftQ[i] = (ull)dftT[i / 2] * dftQ[i + 1] % MOD;
          dftQ[i + 1] = (ull)dftT[i / 2] * u % MOD;
        }
        InvFFT(d * n * 4, dftQ.data(), inv_root.data());
        for (int i = 0; i < d; ++i)
          for (int j = 0; j < n; ++j) dftQ[i * n + j] = dftQ[(i + d) * (n * 2) + j];
        dftQ.resize(d * n);
        return dftQ;
      };
      f.resize(len);
      g.resize(len);
      for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
      std::vector<uint> res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
      res.resize(n);
      return res;
    }

    std::pair<std::vector<uint>, std::vector<uint>> GetFactorial(int n) {
      if (n == 0) return {};
      std::vector<uint> factorial(n), inv_factorial(n);
      factorial[0] = inv_factorial[0] = 1;
      if (n == 1) return {factorial, inv_factorial};
      std::vector<uint> inv(n);
      inv[1] = 1;
      for (int i = 2; i < n; ++i)
        inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
      for (int i = 1; i < n; ++i)
        factorial[i] = (ull)factorial[i - 1] * i % MOD,
        inv_factorial[i] = (ull)inv_factorial[i - 1] * inv[i] % MOD;
      return {factorial, inv_factorial};
    }

    // f(x) |-> f(x + c)
    std::vector<uint> TaylorShift(std::vector<uint> f, uint c) {
      if (f.empty() || c == 0) return f;
      const int n = f.size();
      std::vector<uint> factorial, inv_factorial;
      std::tie(factorial, inv_factorial) = GetFactorial(n);
      for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * factorial[i] % MOD;
      std::vector<uint> g(n);
      uint cp = 1;
      for (int i = 0; i < n; ++i)
        g[i] = (ull)cp * inv_factorial[i] % MOD, cp = (ull)cp * c % MOD;
      int len = 1;
      while (len < n * 2 - 1) len *= 2;
      std::vector<uint> root, inv_root;
      std::tie(root, inv_root) = GetFFTRoot(len);
      f.resize(len);
      g.resize(len);
      FFT(len, f.data(), inv_root.data());
      FFT(len, g.data(), root.data());
      for (int i = 0; i < len; ++i) f[i] = (ull)f[i] * g[i] % MOD;
      InvFFT(len, f.data(), root.data());
      f.resize(n);
      for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * inv_factorial[i] % MOD;
      return f;
    }

    // 多项式复合，求出 f(g) mod x^n
    std::vector<uint> PolyComposition(const std::vector<uint> &f,
                                      const std::vector<uint> &g, int n) {
      if (g.empty() || g[0] == 0) return FPSComposition(f, g, n);
      std::vector<uint> gg = g;
      gg[0] = 0;
      return FPSComposition(TaylorShift(f, g[0]), gg, n);
    }

    int main() {
      int n, m;
      std::scanf("%d%d", &n, &m);
      std::vector<uint> f(n + 1), g(m + 1);
      for (int i = 0; i <= n; ++i) std::scanf("%u", &f[i]);
      for (int i = 0; i <= m; ++i) std::scanf("%u", &g[i]);
      const std::vector<uint> res = PolyComposition(f, g, n + 1);
      for (int i = 0; i <= n; ++i) std::printf("%u%c", res[i], " \n"[i == n]);
      return 0;
    }
    ```

## 形式幂级数的复合逆

现给出 $f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ 且 $f'(0)\neq 0$，求出 $g(x)\bmod{x^n}$ 满足 $f(g)\equiv g(f)\equiv x\pmod{x^n}$．

根据 [Lagrange 反演](./lagrange-inversion.md)，对于 $n>1,k\geq 0$ 我们有

$$
\left\lbrack x^{n-1}\right\rbrack f(x)^k=\frac{k}{n-1}\left\lbrack x^{n-1-k}\right\rbrack \left(\frac{g(x)}{x}\right)^{-(n-1)}
$$

也就是我们如果能对 $k=0,1,\dots ,n-1$ 求出 $\left\lbrack x^{n-1}\right\rbrack f(x)^k$，那么就可以求出其复合逆．

Kinoshita 和 Li 指出我们可以考虑二元有理函数

$$
\frac{1}{1-y\cdot f(x)}=\sum_{j\geq 0}f(x)^jy^j
$$

且这个问题有一个更一般的形式即 Power Projection 问题：我们考虑计算

$$
u:=\left\lbrack x^{n-1}\right\rbrack\frac{P(x,y)}{Q(x,y)}\bmod{y^m}
$$

当 $n-1=0$ 时显然有 $u=\dfrac{P(0,y)}{Q(0,y)}\bmod{y^m}$，否则我们有

$$
\frac{P(x,y)}{Q(x,y)}=\frac{P(x,y)Q(-x,y)}{Q(x,y)Q(-x,y)}=\frac{U_e\left(x^2,y\right)+xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}
$$

那么

$$
\begin{aligned}
u&=\begin{cases}
\left\lbrack x^{n-1}\right\rbrack\dfrac{U_e\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{n-1}\right\rbrack\dfrac{xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases} \\
&=\begin{cases}
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_e\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_o\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases}
\end{aligned}
$$

我们给出其伪代码：

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{PowProj}}\left(P(x,y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P,Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{n-1}\right\rbrack\dfrac{P(x,y)}{Q(x,y)}\bmod{y^m}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{while }n>1\textbf{ do} \\
2&\qquad U(x,y)\gets P(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
3&\qquad \textbf{if }n-1\text{ is even }\textbf{then} \\
4&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack U(x,y)\right)x^j \\
5&\qquad \textbf{else} \\
6&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j+1}\right\rbrack U(x,y)\right)x^j \\
7&\qquad \textbf{end if} \\
8&\qquad V(x,y)\gets Q(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
9&\qquad Q(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack V(x,y)\right)x^j \\
10&\qquad n\gets \left\lceil n/2\right\rceil \\
11&\textbf{end while} \\
12&\textbf{return }\left(\frac{P(0,y)}{Q(0,y)}\bmod{y^m}\right)
\end{array}
$$

同样的我们也可以直接导出 $Q(0,y)^{-1}$ 而不需要计算形式幂级数的乘法逆元，那么复合逆的算法就是

$$
\begin{array}{ll} &\textbf{Algorithm }\operatorname{\mathsf{Rev}}(f(x),n)\text{:} \\
&\textbf{Input}\text{: }f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack, f'(0)\neq 0,n\in\mathbb{N}_{\geq 2}\text{.} \\
&\textbf{Output}\text{: }g(x)\bmod{x^n} \text{ such that }f(g)\equiv g(f)\equiv x\pmod{x^n}\text{.} \\
1&t\gets f'(0) \\
2&F(x)\gets f\left(t^{-1}x\right) \\
3&\sum_{k=0}^{n-1}a_ky^k\gets \operatorname{\mathsf{PowProj}}\left(1,1-y\cdot F(x),n,n\right) \\
4&G(x)\gets \sum_{k=1}^{n-1}\frac{n-1}{k}a_{k}x^{n-1-k} \\
5&H(x)\gets \left(G(x)^{1/(n-1)}\right)^{-1}\bmod{x^{n-1}} \\
6&\textbf{return }\left((t^{-1}x) \circ \left(x\cdot H\right)\right)
\end{array}
$$

??? note "模板（[P5809【模板】多项式复合逆](https://www.luogu.com.cn/problem/P5809)）"
    代码相对于原算法作了一些简化及修改，使得代码更短．
    
    ```cpp
    #include <algorithm>
    #include <cassert>
    #include <cstdio>
    #include <tuple>
    #include <utility>
    #include <vector>

    using uint = unsigned;
    using ull = unsigned long long;
    constexpr uint MOD = 998244353;

    constexpr uint PowMod(uint a, ull e) {
      for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
      }
    }

    constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

    constexpr uint QUAD_NONRESIDUE = 3;
    constexpr int LOG2_ORD = 23;  // __builtin_ctz(MOD - 1)
    constexpr uint ZETA = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
    constexpr uint INV_ZETA = InvMod(ZETA);

    // 返回做 n 长 FFT 所需的单位根数组，长度为一半
    std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
      assert((n & (n - 1)) == 0);
      if (n / 2 == 0) return {};
      std::vector<uint> root(n / 2), inv_root(n / 2);
      root[0] = inv_root[0] = 1;
      for (int i = 0; (1 << i) < n / 2; ++i)
        root[1 << i] = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
      for (int i = 1; i < n / 2; ++i)
        root[i] = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
        inv_root[i] =
            (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
      return {root, inv_root};
    }

    void Butterfly(int n, uint a[], const uint root[]) {
      assert((n & (n - 1)) == 0);
      for (int i = n; i >= 2; i /= 2)
        for (int j = 0; j < n; j += i)
          for (int k = j; k < j + i / 2; ++k) {
            const uint u = a[k];
            a[k + i / 2] = (ull)a[k + i / 2] * root[j / i] % MOD;
            if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
            if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;
          }
    }

    void InvButterfly(int n, uint a[], const uint root[]) {
      assert((n & (n - 1)) == 0);
      for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
          for (int k = j; k < j + i / 2; ++k) {
            const uint u = a[k];
            if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
            a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
          }
    }

    void FFT(int n, uint a[], const uint root[]) { Butterfly(n, a, root); }

    void InvFFT(int n, uint a[], const uint root[]) {
      InvButterfly(n, a, root);
      const uint inv_n = InvMod(n);
      for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * inv_n % MOD;
    }

    // 形式幂级数复合，求出 f(g) mod x^n 要求 g(0) = 0
    std::vector<uint> FPSComposition(std::vector<uint> f, std::vector<uint> g,
                                     int n) {
      assert(g.empty() || g[0] == 0);
      int len = 1;
      while (len < n) len *= 2;
      std::vector<uint> root, inv_root;
      std::tie(root, inv_root) = GetFFTRoot(len * 4);
      // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
      const auto KinoshitaLi = [&](auto &&KinoshitaLi, const std::vector<uint> &P,
                                   const std::vector<uint> &Q, int d, int n) {
        assert((int)P.size() == d * n);
        assert((int)Q.size() == d * n);
        if (n == 1) return P;
        std::vector<uint> dftQ(d * n * 4);
        for (int i = 0; i < d; ++i)
          for (int j = 0; j < n; ++j) dftQ[i * n * 2 + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        FFT(d * n * 4, dftQ.data(), root.data());
        std::vector<uint> V(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2)
          V[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
        InvFFT(d * n * 2, V.data(), inv_root.data());
        assert(V[0] == 1);
        V[0] = 0;
        for (int i = 1; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i * n + j];
        V.resize(d * n);
        const std::vector<uint> T = KinoshitaLi(KinoshitaLi, P, V, d * 2, n / 2);
        std::vector<uint> dftT(d * n * 2);
        for (int i = 0; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) dftT[i * n + j] = T[i * (n / 2) + j];
        FFT(d * n * 2, dftT.data(), root.data());
        for (int i = 0; i < d * n * 4; i += 2) {
          const uint u = dftQ[i];
          dftQ[i] = (ull)dftT[i / 2] * dftQ[i + 1] % MOD;
          dftQ[i + 1] = (ull)dftT[i / 2] * u % MOD;
        }
        InvFFT(d * n * 4, dftQ.data(), inv_root.data());
        for (int i = 0; i < d; ++i)
          for (int j = 0; j < n; ++j) dftQ[i * n + j] = dftQ[(i + d) * (n * 2) + j];
        dftQ.resize(d * n);
        return dftQ;
      };
      f.resize(len);
      g.resize(len);
      for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
      std::vector<uint> res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
      res.resize(n);
      return res;
    }

    // Power Projection: [x^(n-1)] (fg^i) for i=0,..,n-1 要求 g(0) = 0
    std::vector<uint> PowerProjection(std::vector<uint> f, std::vector<uint> g,
                                      int n) {
      assert(g.empty() || g[0] == 0);
      int len = 1;
      while (len < n) len *= 2;
      std::vector<uint> root, inv_root;
      std::tie(root, inv_root) = GetFFTRoot(len * 4);
      // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))
      const auto KinoshitaLi = [&](auto &&KinoshitaLi, std::vector<uint> P,
                                   std::vector<uint> Q, int d,
                                   int n) -> std::vector<uint> {
        assert((int)P.size() == d * n);
        assert((int)Q.size() == d * n);
        if (n == 1) return P;
        std::vector<uint> dftQ(d * n * 4), dftP(d * n * 4);
        for (int i = 0; i < d; ++i)
          for (int j = 0; j < n; ++j)
            dftP[(2 * (i + d) + 1) * n + j] = P[i * n + j],
                                         dftQ[i * n * 2 + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        FFT(d * n * 4, dftP.data(), inv_root.data());
        FFT(d * n * 4, dftQ.data(), root.data());
        P.resize(d * n * 2);
        Q.resize(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2) {
          P[i / 2] =
              ((ull)dftP[i] * dftQ[i + 1] + (ull)dftP[i + 1] * dftQ[i]) % MOD;
          if (P[i / 2] & 1) P[i / 2] += MOD;
          P[i / 2] /= 2;
          Q[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
        }
        InvFFT(d * n * 2, P.data(), root.data());
        InvFFT(d * n * 2, Q.data(), inv_root.data());
        for (int i = 0; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) P[i * (n / 2) + j] = P[i * n + n / 2 + j];
        assert(Q[0] == 1);
        Q[0] = 0;
        for (int i = 1; i < d * 2; ++i)
          for (int j = 0; j < n / 2; ++j) Q[i * (n / 2) + j] = Q[i * n + j];
        P.resize(d * n);
        Q.resize(d * n);
        return KinoshitaLi(KinoshitaLi, P, Q, d * 2, n / 2);
      };
      f.insert(f.begin(), len - n, 0);
      f.resize(len);
      g.resize(len);
      std::reverse(f.begin(), f.end());
      for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
      auto res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
      res.resize(n);
      return res;
    }

    // 形式幂级数幂函数，计算 g^e mod x^n 要求 g(0) = 1
    std::vector<uint> FPSPow1(std::vector<uint> g, uint e, int n) {
      assert(!g.empty() && g[0] == 1);
      if (n == 1) return std::vector<uint>{1u};
      std::vector<uint> inv(n), f(n);
      inv[1] = f[0] = 1;
      for (int i = 2; i < n; ++i)
        inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
      for (int i = 1; i < n; ++i)
        f[i] = (ull)f[i - 1] * (e + MOD + 1 - i) % MOD * inv[i] % MOD;
      g[0] = 0;
      return FPSComposition(f, g, n);
    }

    // 形式幂级数复合逆
    // 计算 g mod x^n 满足 g(f) = f(g) = x 要求 g(0) = 0 且 g'(0) ≠ 0
    std::vector<uint> FPSReversion(std::vector<uint> f, int n) {
      assert(f.size() >= 2 && f[0] == 0 && f[1] != 0);
      if (n == 1) return std::vector<uint>{0u};
      f.resize(n);
      const uint invf1 = InvMod(f[1]);
      uint invf1p = 1;
      for (int i = 0; i < n; ++i)
        f[i] = (ull)f[i] * invf1p % MOD, invf1p = (ull)invf1p * invf1 % MOD;
      std::vector<uint> inv(n);
      inv[1] = 1;
      for (int i = 2; i < n; ++i)
        inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
      std::vector<uint> proj = PowerProjection(std::vector<uint>{1u}, f, n);
      for (int i = 1; i < n; ++i)
        proj[i] = (ull)proj[i] * (n - 1) % MOD * inv[i] % MOD;
      std::reverse(proj.begin(), proj.end());
      std::vector<uint> res = FPSPow1(proj, InvMod(MOD + 1 - n), n - 1);
      for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i] * invf1 % MOD;
      res.insert(res.begin(), 0);
      return res;
    }

    int main() {
      int n;
      std::scanf("%d", &n);
      std::vector<uint> f(n);
      for (int i = 0; i < n; ++i) std::scanf("%u", &f[i]);
      const std::vector<uint> res = FPSReversion(f, n);
      for (int i = 0; i < n; ++i) std::printf("%u%c", res[i], " \n"[i + 1 == n]);
      return 0;
    }
    ```

### 由转置原理导出

Power Projection 问题是 Modular Composition 的转置，Kinoshita 和 Li 指出我们前文的复合算法可以由 Power Projection 算法直接转置得到．同样的，如果优化可以应用于 Power Projection 算法，其也可以应用于 Modular Composition 算法．我们省略细节．

## 参考文献

1.  Yasunori Kinoshita, Baitian Li.[Power Series Composition in Near-Linear Time](https://arxiv.org/abs/2404.05177). FOCS 2024.
2.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822). SOSA 2021: 118-132
3.  R. P. Brent and H. T. Kung. 1978.[Fast Algorithms for Manipulating Formal Power Series](https://doi.org/10.1145/322092.322099). J. ACM 25, 4 (Oct. 1978), 581–595.
4.  Daniel J. Bernstein. "[Fast multiplication and its applications](https://cr.yp.to/papers.html#multapps)." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545.
