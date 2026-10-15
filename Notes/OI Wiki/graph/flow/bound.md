在阅读这篇文章之前请先阅读 [最大流](./max-flow.md) 并确保自己熟练掌握最大流算法．

## 概述

上下界网络流本质是给流量网络的每一条边设置了流量上界 $c(u,v)$ 和流量下界 $b(u,v)$．也就是说，一种可行的流必须满足 $b(u,v) \leq f(u,v) \leq c(u,v)$．同时必须满足除了源点和汇点之外的其余点流量平衡．

根据题目要求，我们可以使用上下界网络流解决不同问题．

## 无源汇上下界可行流

给定无源汇流量网络 $G$．询问是否存在一种标定每条边流量的方式，使得每条边流量满足上下界同时每一个点流量平衡．

不妨假设每条边已经流了 $b(u,v)$ 的流量，设其为初始流．同时我们在新图中加入 $u$ 连向 $v$ 的流量为 $c(u,v) - b(u,v)$ 的边．考虑在新图上进行调整．

由于最大流需要满足初始流量平衡条件（最大流可以看成是下界为 $0$ 的上下界最大流），但是构造出来的初始流很有可能不满足初始流量平衡．假设一个点初始流入流量减初始流出流量为 $M$．

若 $M=0$，此时流量平衡，不需要附加边．

若 $M>0$，此时入流量过大，需要新建附加源点 $S'$，$S'$ 向其连流量为 $M$ 的附加边．

若 $M<0$，此时出流量过大，需要新建附加汇点 $T'$，其向 $T'$ 连流量为 $-M$ 的附加边．

如果附加边满流，说明这一个点的流量平衡条件可以满足，否则这个点的流量平衡条件不满足．（因为原图加上附加流之后才会满足原图中的流量平衡．）

在建图完毕之后跑 $S'$ 到 $T'$ 的最大流，若 $S'$ 连出去的边全部满流，则存在可行流，否则不存在．

### 例题

???+ note "[luogu P14578【模板】无源汇上下界可行流](https://www.luogu.com.cn/problem/P14578)"
    一个 $n$ 个点、$m$ 条有向边的有向图 $G$，每条边有流量下界 $l_i$ 和流量上界 $r_i$．
    
    构造一种方案使得每条边的流量 $w_i$ 满足流量限制 $l_i\leq w_i\leq r_i$，且每个点流量平衡，即每个点流入流量等于流出流量．或报告无解．

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <queue>
    using namespace std;
    constexpr int MAXN = 3e4 + 10;
    constexpr int INF = 1e9 + 10;
    int n, m, s = 0, t;
    int ecnt = 1, head[MAXN], dep[MAXN], now[MAXN], l[MAXN], d[MAXN], id[MAXN];

    struct edge {
      int to, nxt, w;
    } e[MAXN];

    void add_edge(int u, int v, int w) {
      e[++ecnt] = {v, head[u], w};
      head[u] = ecnt;
    }

    void init() {
      for (int i = 0; i <= n + 1; i++) dep[i] = 0;
      for (int i = 0; i <= n + 1; i++) now[i] = head[i];
    }

    int bfs() {
      init();
      queue<int> q;
      q.push(s);
      dep[s] = 1;
      while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = e[i].nxt) {
          int v = e[i].to;
          if (dep[v] || !e[i].w) continue;
          dep[v] = dep[x] + 1;
          q.push(v);
        }
      }
      return dep[t];
    }

    int dfs(int x, int flow) {
      if (x == t) return flow;
      int ret = 0;
      for (int i = now[x]; i; i = e[i].nxt) {
        now[x] = i;
        int v = e[i].to;
        if (dep[v] != dep[x] + 1 || !e[i].w) continue;
        int w = dfs(v, min(flow - ret, e[i].w));
        e[i].w -= w;
        e[i ^ 1].w += w;
        ret += w;
        if (ret == flow) return ret;
      }
      return ret;
    }

    int main() {
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      cin >> n >> m;
      s = 0, t = n + 1;
      for (int i = 1; i <= m; i++) {
        int u, v, r;
        cin >> u >> v >> l[i] >> r;
        add_edge(u, v, r - l[i]);
        add_edge(v, u, 0);
        id[i] = ecnt;
        d[v] += l[i];
        d[u] -= l[i];
      }
      long long sum = 0;
      for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
          add_edge(s, i, d[i]);
          add_edge(i, s, 0);
          sum += d[i];
        } else if (d[i] < 0) {
          add_edge(i, t, -d[i]);
          add_edge(t, i, 0);
        }
      }
      long long ans = 0;
      while (bfs()) ans += dfs(s, INF);
      if (ans < sum) {
        cout << "No\n";
        return 0;
      }
      cout << "Yes\n";
      for (int i = 1; i <= m; i++) cout << e[id[i]].w + l[i] << "\n";
      return 0;
    }
    ```

## 有源汇上下界可行流

给定有源汇流量网络 $G$．询问是否存在一种标定每条边流量的方式，使得每条边流量满足上下界同时除了源点和汇点每一个点流量平衡．

假设源点为 $S$，汇点为 $T$．

则我们可以加入一条 $T$ 到 $S$ 的上界为 $\infty$，下界为 $0$ 的边转化为无源汇上下界可行流问题．

若有解，则 $S$ 到 $T$ 的可行流流量等于 $T$ 到 $S$ 的附加边的流量．

## 有源汇上下界最大流

给定有源汇流量网络 $G$．询问是否存在一种标定每条边流量的方式，使得每条边流量满足上下界同时除了源点和汇点每一个点流量平衡．如果存在，询问满足标定的最大流量．

我们找到网络上的任意一个可行流．如果找不到解就可以直接结束．

否则我们考虑删去所有附加边之后的残量网络并且在网络上进行调整．

我们在残量网络上再跑一次 $S$ 到 $T$ 的最大流，将可行流流量和最大流流量相加即为答案．

??? warning "一个非常易错的问题"
    $S$ 到 $T$ 的最大流直接在跑完有源汇上下界可行的残量网络上跑．
    
    千万不可以在原来的流量网络上跑．

## 有源汇上下界最小流

给定有源汇流量网络 $G$．询问是否存在一种标定每条边流量的方式，使得每条边流量满足上下界同时除了源点和汇点每一个点流量平衡．如果存在，询问满足标定的最小流量．

类似的，我们考虑将残量网络中不需要的流退掉．

我们找到网络上的任意一个可行流．如果找不到解就可以直接结束．

否则我们考虑删去所有附加边之后的残量网络．

我们在残量网络上再跑一次 $T$ 到 $S$ 的最大流，将可行流流量减去最大流流量即为答案．

??? note "[AHOI 2014 支线剧情](https://loj.ac/problem/2226)"
    对于每条 $x$ 到 $y$ 花费 $v$ 的剧情边设上界为 $\infty$, 下界为 $1$．
    
    对于每个点，向 $T$ 连边权 $c$, 上界 $\infty$, 下界为 $1$．
    
    $S$ 点为 $1$ 号节点．
    
    跑一次 上下界带源汇最小费用可行流 即可．
    
    因为最小费用可行流解法与最小可行流类似，这里不再展开．
