与离散傅里叶变换类似，Chirp Z 变换是给出多项式 $f(x) = \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ 和 $q \in \mathbb{C} \setminus \{0\}$ 求出 $f(1), f(q), \dots, f(q^{n - 1})$ 的一种算法，不要求 $q$ 为单位根．也可用于数论变换．后文将介绍 Chirp Z 变换与其逆变换．

## Chirp Z 变换

根据定义，Chirp Z 变换可以写作

$$
\operatorname{\mathsf{CZT}}_n : \left(f(x), q\right) \mapsto
\begin{bmatrix}
f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
\end{bmatrix}
$$

其中 $f(x) := \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ 且 $q \in \mathbb{C} \setminus \{0\}$．

### Bluestein 算法

考虑

$$
ij = \binom{i}{2} + \binom{-j}{2} - \binom{i - j}{2}
$$

其中 $i, j \in \mathbb{Z}$，我们可以构造

$$
\begin{aligned}
G(x) & := \sum_{i = -(m - 1)}^{n - 1} q^{-\binom{i}{2}}x^i, \\
F(x) & := \sum_{i = 0}^{m - 1} f_i q^{\binom{-i}{2}}x^i.
\end{aligned}
$$

其中 $G(x) \in \mathbb{C}\left\lbrack x, x^{-1}\right\rbrack$，且对于 $i = 0, \dots, n - 1$ 我们有

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack\left(G(x)F(x)\right) &=
\sum_{j = 0}^{m - 1}\left(\left(\left\lbrack x^{i - j}\right\rbrack G(x)\right)\left(\left\lbrack x^j\right\rbrack F(x)\right)\right) \\
&= \sum_{j = 0}^{m - 1} f_j q^{\binom{-j}{2} - \binom{i - j}{2}} \\
&= q^{-\binom{i}{2}} f\left(q^i\right)
\end{aligned}
$$

且 $q^{\binom{i + 1}{2}} = q^{\binom{i}{2}}\cdot q^i$，$\binom{-i}{2} = \binom{i + 1}{2}$．可以由一次多项式乘法完成求算，该算法被称为 Bluestein 算法．

??? note "模板（[P6800【模板】Chirp Z-Transform](https://www.luogu.com.cn/problem/P6800)）"
    ```cpp
    std::vector<uint> CZT(const std::vector<uint>& f, uint q, int n) {
      if (f.empty() || n == 0) return std::vector<uint>(n);
      const int m = f.size();
      if (q == 0) {
        std::vector<uint> res(n, f[0]);
        for (int i = 1; i < m; ++i)
          if ((res[0] += f[i]) >= MOD) res[0] -= MOD;
        return res;
      }
      // H[i] = q^(binom(i + 1, 2))
      std::vector<uint> H(std::max(m, n - 1));
      H[0] = 1;     // H[0] = q^0
      uint qi = 1;  // qi = q^i
      for (int i = 1; i < (int)H.size(); ++i) {
        qi = (ull)qi * q % MOD;
        // H[i] = q^(binom(i, 2)) * q^i
        H[i] = (ull)H[i - 1] * qi % MOD;
      }
      // F[i] = f[i] * q^(binom(i + 1, 2))
      std::vector<uint> F(m);
      for (int i = 0; i < m; ++i) F[i] = (ull)f[i] * H[i] % MOD;
      std::vector<uint> G_p(m + n - 1);
      // G[i] = q^(-binom(i, 2)), -(m - 1) ≤ i < n
      uint* const G = G_p.data() + (m - 1);
      const uint iq = InvMod(q);
      // G[-(m - 1)] = q^(-binom(-(m - 1), 2)),
      // binom(-(m - 1), 2) = (-(m - 1)) * (-(m - 1) - 1) / 2
      //                    = (m - 1) * m / 2
      G[-(m - 1)] = PowMod(iq, (ull)(m - 1) * m / 2);
      uint qmi = PowMod(q, m - 1);  // q^(-i), -(m - 1) ≤ i < n
      for (int i = -(m - 1) + 1; i < n; ++i) {
        // q^(-binom(i, 2)) = q^(-binom(i - 1, 2)) * q^(-(i - 1))
        G[i] = (ull)G[i - 1] * qmi % MOD;
        // q^(-i) = q^(-(i - 1)) * q^(-1)
        qmi = (ull)qmi * iq % MOD;
      }
      // res[i] = q^(-binom(i, 2)) * f(q^i), 0 ≤ i < n
      std::vector<uint> res = MiddleProduct(G_p, F);
      for (int i = 1; i < n; ++i) res[i] = (ull)res[i] * H[i - 1] % MOD;
      return res;
    }

    ```

## 逆 Chirp Z 变换

逆 Chirp Z 变换可以写作

$$
\operatorname{\mathsf{ICZT}}_n :
\left(
    \begin{bmatrix} f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
    \end{bmatrix},q
\right)
\mapsto f(x)
$$

其中 $f(x) \in \mathbb{C}\left\lbrack x\right\rbrack_{< n}$ 且 $q \in \mathbb{C} \setminus \{0\}$，并且 $q^i \neq q^j$ 对于所有 $i \neq j$ 成立，这是多项式插值的条件．

### Bostan–Schost 算法

回顾 [Lagrange 插值公式](../numerical/interp.md#lagrange-插值法) 为

$$
f(x) = \sum_{i = 0}^{n - 1}\left(f\left(x_i\right)\prod_{0 \leq j < n \atop j \neq i} \frac{x - x_j}{x_i - x_j}\right)
$$

且 $x_i \neq x_j$ 对于所有 $i \neq j$ 成立．与 [多项式的快速插值](./multipoint-eval-interpolation.md#多项式的快速插值) 中相同，我们令 $M(x) := \prod_{i = 0}^{n - 1}\left(x - x_i\right)$，根据洛必达法则，有

$$
M'(x_i) = \lim_{x \to x_i} \frac{M(x)}{x - x_i} = \prod_{0 \leq j < n \atop j \neq i}\left(x_i - x_j\right)
$$

**修正 Lagrange 插值公式** 就是

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(x_i\right)/M'(x_i)}{x - x_i}\right)
$$

那么现在我们有

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(q^i\right)/M'\left(q^i\right)}{x - q^i}\right)
$$

其中 $M(x)=\prod_{j = 0}^{n - 1}\left(x - q^j\right)$．若我们设 $n$ 为偶数，令 $n = 2k$ 和 $H(x) := \prod_{j = 0}^{k - 1}\left(x - q^j\right)$，那么

$$
M(x) = H(x) \cdot q^{k^2} \cdot H\left(\frac{x}{q^k}\right)
$$

这使得我们可以快速计算 $M(x)$．然后用 Bluestein 算法来计算 $M'(1), \dots, M'(q^{n - 1})$．令 $c_i := f\left(q^i\right)/M'\left(q^i\right)$，我们有

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\right)
$$

因为 $\deg f(x) < n$，我们只需计算 $\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\bmod{x^n}$，其中 $\frac{c_i}{x - q^i} \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，也就是

$$
\begin{aligned}
\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i} \bmod x^n &=
-\sum_{i = 0}^{n - 1}\left(\sum_{j = 0}^{n - 1} c_i q^{-i(j+1)}x^j\right) \\
&= -\sum_{j = 0}^{n - 1} C\left(q^{-j - 1}\right) x^j
\end{aligned}
$$

其中 $C(x) = \sum_{i = 0}^{n - 1} c_i x^i$．我们可以用 Bluestein 算法来计算 $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$．

简单来说，我们分别进行下面的计算：

1.  用减治法（decrease and conquer）计算 $M(x)$；
2.  用 Bluestein 算法计算 $M'(1), \dots, M'(q^{n - 1})$；
3.  用 Bluestein 算法计算 $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$；
4.  用一次多项式乘法计算 $f(x)$．

其中每一步的时间复杂度都等于两个次数小于等于 $n$ 的多项式相乘的时间复杂度．

??? note "模板实现"
    ```cpp
    std::vector<uint> InvCZT(const std::vector<uint>& f, uint q) {
      if (f.empty()) return {};
      const int n = f.size();
      if (q == 0) {
        // f[0] = f(1), f[1] = f(0)
        assert(n <= 2);
        if (n == 1) return {f[0]};                 // deg(f) < 1
        return {f[1], (f[0] + MOD - f[1]) % MOD};  // deg(f) < 2
      }
      // prod[0 ≤ i < n] (x - q^i)
      const auto DaC = [q](auto&& DaC, int n) -> std::vector<uint> {
        if (n == 1) return {MOD - 1, 1u};
        // H = prod[0 ≤ i < ⌊n/2⌋] (x - q^i)
        const std::vector<uint> H = DaC(DaC, n / 2);
        // HH = H(x / q^(⌊n/2⌋)) * q^(⌊n/2⌋^2)
        std::vector<uint> HH = H;
        const uint iqn = InvMod(PowMod(q, n / 2));
        uint qq = PowMod(q, (ull)(n / 2) * (n / 2));
        for (int i = 0; i <= n / 2; ++i)
          HH[i] = (ull)HH[i] * qq % MOD, qq = (ull)qq * iqn % MOD;
        std::vector<uint> res = Product(H, HH);
        if (n & 1) {
          res.resize(n + 1);
          const uint qnm1 = MOD - PowMod(q, n - 1);
          for (int i = n; i > 0; --i) {
            if ((res[i] += res[i - 1]) >= MOD) res[i] -= MOD;
            res[i - 1] = (ull)res[i - 1] * qnm1 % MOD;
          }
        }
        return res;
      };
      const std::vector<uint> M = DaC(DaC, n);
      // C[i] = (M'(q^i))^(-1)
      std::vector<uint> C = InvModBatch(CZT(Deriv(M), q, n));
      // C[i] = f(q^i) / M'(q^i)
      for (int i = 0; i < n; ++i) C[i] = (ull)f[i] * C[i] % MOD;
      // C(x) ← C(q^(-1)x)
      const uint iq = InvMod(q);
      uint qmi = 1;
      for (int i = 0; i < n; ++i)
        C[i] = (ull)C[i] * qmi % MOD, qmi = (ull)qmi * iq % MOD;
      C = CZT(C, iq, n);
      for (int i = 0; i < n; ++i)
        if (C[i] != 0) C[i] = MOD - C[i];
      std::vector<uint> res = Product(M, C);
      res.resize(n);
      return res;
    }

    ```

## 参考文献

1.  [Bostan, A. (2010). Fast algorithms for polynomials and matrices. JNCF 2010. Algorithms Project, INRIA.](https://specfun.inria.fr/bostan/publications/exposeJNCF.pdf)
