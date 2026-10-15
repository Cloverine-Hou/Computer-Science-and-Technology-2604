# OI Wiki 离线镜像索引

本目录是 [OI Wiki](https://oi-wiki.org/) 官方内容的本地 **原始 Markdown** 镜像（共 **465** 个页面 / `.md` 文件，快照于 2026-10-15）。本 README 按官方 `mkdocs.yml` 的 `nav` 层级给出完整分类索引，并为每个页面同时给出**本地相对路径**与**在线地址**。

- 源站：<https://oi-wiki.org/>
- 仓库：<https://github.com/OI-wiki/OI-wiki>

## 抓取说明

- **内容来源**：OI Wiki 官方仓库 [`OI-wiki/OI-wiki`](https://github.com/OI-wiki/OI-wiki) 的 `master` 分支**原始 Markdown**（而不是抓渲染后的 HTML）。原始 Markdown 更完整：保留 `author:` 等元信息行、`??? note` 折叠块、LaTeX 公式、代码围栏与注释。
- **页面清单**：以 oi-wiki.org 的 `sitemap.xml` 为准，抓取日期 **2026-10-15**，共 **465** 个站点 URL（原始清单见 [`_manifest/sitemap-urls.txt`](_manifest/sitemap-urls.txt)）。
- **本地路径与在线 URL 的对应**：`path/to/page.md` → `https://oi-wiki.org/path/to/page/`；名为 `index.md` 的取其所在目录，根级 `index.md` 即 `https://oi-wiki.org/`。
- **最终生成方式**：465 个页面全部由脚本（见 [`_tools/`](_tools/)）从 `master` 分支原始 Markdown 重新抓取、并按 pymdownx 语义**确定性展开** snippets 后生成；抓取优先直连 `raw.githubusercontent.com`，失败时回退 `ghproxy.net` / jsDelivr 等同分支镜像（共约 1250 次 HTTP 请求，0 个引用目标抓取失败）。
- **可复现性**：生成结果与抓取过程中的逐页产物做过字节级对账——292 个页面完全一致，其余差异为空白字符或上游近期的文本更新，最终统一以重算结果为准；重算后的镜像与生成树 **465/465 逐字节一致**。

## 重要保真说明

1. **pymdownx snippets 外置代码已按官方语义展开**：
   - 不带小节选择器的引用会插入**整份文件**；
   - 带 `:小节名` 选择器的引用只插入该小节 `start` 与 `end` 标记行**之间**的正文，**标记行本身不保留**；
   - 插入的内容按**原引用指令行的缩进**整体缩进，以保持插入位置的缩进层级。
   因此正文中已看不到外置引用语法，代码内容直接内联在页面里。
2. **图片未下载**：镜像只包含 Markdown 文本，正文中的图片引用保持原样（相对路径形式），所以离线打开时图片会缺失；如需图片请访问 oi-wiki.org 上对应页面。
3. **行尾空白与空行结构**：最终生成基于原始字节流而非渲染后的文本投影，并做了端到端逆向校验——对不含 snippets 的页面要求与上游**逐字节一致**，对含 snippets 的页面要求上游的每一条非指令行都在成品中按原顺序出现。结论见 [`_manifest/verify-final.md`](_manifest/verify-final.md)。
4. **差异只可能出现在 snippets 展开处**：展开完全确定，可随时用 [`_tools/fetch_and_expand.py`](_tools/fetch_and_expand.py) 重新生成并与本目录逐字节比对。

## 版权与许可

OI Wiki 的内容采用 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh) 与 [SATA](https://github.com/zTrix/sata-license) 许可发布，**转载请遵守相应许可条款**（署名 + 相同方式共享）。

- 源站：<https://oi-wiki.org/>
- 仓库：<https://github.com/OI-wiki/OI-wiki>

## 统计

- 本地 `.md` 文件总数：**465**（= 官方 `nav` 叶子 463 + nav 之外的 `edit-landing.md`、`intro/docker-deploy.md`）
- 官方 `nav` 叶子页面数：**463**
- sitemap 站点 URL 数：**465**
- 本地缺失页面数：**0**
- 镜像总字节数：**7,056,271**（UTF-8，LF 行尾）

### 顶层目录文件数

| 顶层目录 | 文件数 |
| --- | ---: |
| `basic/` | 26 |
| `contest/` | 12 |
| `dp/` | 22 |
| `ds/` | 59 |
| `geometry/` | 14 |
| `graph/` | 61 |
| `intro/` | 9 |
| `lang/` | 41 |
| `math/` | 113 |
| `misc/` | 32 |
| `search/` | 12 |
| `string/` | 22 |
| `tools/` | 36 |
| `topic/` | 4 |
| （根级，`index.md` + `edit-landing.md`） | 2 |
| **合计** | **465** |

> 表中数字为 2026-10-15 快照当日的最终磁盘状态，与 `sitemap.xml` 的 465 条 URL 逐条对应（详细对账见 [`_manifest/integrity-report.md`](_manifest/integrity-report.md) 与 [`_manifest/verify-final.md`](_manifest/verify-final.md)）。

## 分类索引

图例：`- [标题](本地相对路径) · [在线](在线地址)`。

- 无本地链接、只标为分组名的条目，是官方 `nav` 中的**分组标题**（本身没有页面）。
- 官方 `nav` 与 sitemap 中的**全部 465 个页面均已落盘**，因此本文档不再有「本地缺失」标注。

### 简介

- [Getting Started](index.md) · [在线](https://oi-wiki.org/)
- [关于本项目](intro/about.md) · [在线](https://oi-wiki.org/intro/about/)
- [如何参与](intro/htc.md) · [在线](https://oi-wiki.org/intro/htc/)
- [OI Wiki 不是什么](intro/what-oi-wiki-is-not.md) · [在线](https://oi-wiki.org/intro/what-oi-wiki-is-not/)
- [格式手册](intro/format.md) · [在线](https://oi-wiki.org/intro/format/)
- [数学符号表](intro/symbol.md) · [在线](https://oi-wiki.org/intro/symbol/)
- [F.A.Q.](intro/faq.md) · [在线](https://oi-wiki.org/intro/faq/)
- [镜像站列表](intro/mirrors.md) · [在线](https://oi-wiki.org/intro/mirrors/)
- [致谢](intro/thanks.md) · [在线](https://oi-wiki.org/intro/thanks/)

### 比赛相关

- [比赛相关简介](contest/index.md) · [在线](https://oi-wiki.org/contest/)
- **赛事**
  - [OI 赛事与赛制](contest/oi.md) · [在线](https://oi-wiki.org/contest/oi/)
  - [ICPC/CCPC 赛事与赛制](contest/icpc.md) · [在线](https://oi-wiki.org/contest/icpc/)
- **题型**
  - [题型概述](contest/problems.md) · [在线](https://oi-wiki.org/contest/problems/)
  - [交互题](contest/interaction.md) · [在线](https://oi-wiki.org/contest/interaction/)
- [学习路线](contest/roadmap.md) · [在线](https://oi-wiki.org/contest/roadmap/)
- [学习资源](contest/resources.md) · [在线](https://oi-wiki.org/contest/resources/)
- **技巧**
  - [读入、输出优化](contest/io.md) · [在线](https://oi-wiki.org/contest/io/)
  - [分段打表](contest/dictionary.md) · [在线](https://oi-wiki.org/contest/dictionary/)
  - [常见错误](contest/common-mistakes.md) · [在线](https://oi-wiki.org/contest/common-mistakes/)
  - [常见技巧](contest/common-tricks.md) · [在线](https://oi-wiki.org/contest/common-tricks/)
- [出题](contest/problemsetting.md) · [在线](https://oi-wiki.org/contest/problemsetting/)

### 工具软件

- [工具软件简介](tools/index.md) · [在线](https://oi-wiki.org/tools/)
- **代码编辑工具**
  - [Vim](tools/editor/vim.md) · [在线](https://oi-wiki.org/tools/editor/vim/)
  - [Emacs](tools/editor/emacs.md) · [在线](https://oi-wiki.org/tools/editor/emacs/)
  - [VS Code](tools/editor/vscode.md) · [在线](https://oi-wiki.org/tools/editor/vscode/)
  - [Atom](tools/editor/atom.md) · [在线](https://oi-wiki.org/tools/editor/atom/)
  - [Eclipse](tools/editor/eclipse.md) · [在线](https://oi-wiki.org/tools/editor/eclipse/)
  - [Notepad++](tools/editor/npp.md) · [在线](https://oi-wiki.org/tools/editor/npp/)
  - [Kate](tools/editor/kate.md) · [在线](https://oi-wiki.org/tools/editor/kate/)
  - [Dev-C++](tools/editor/devcpp.md) · [在线](https://oi-wiki.org/tools/editor/devcpp/)
  - [CLion](tools/editor/clion.md) · [在线](https://oi-wiki.org/tools/editor/clion/)
  - [Geany](tools/editor/geany.md) · [在线](https://oi-wiki.org/tools/editor/geany/)
  - [Xcode](tools/editor/xcode.md) · [在线](https://oi-wiki.org/tools/editor/xcode/)
  - [GUIDE](tools/editor/guide.md) · [在线](https://oi-wiki.org/tools/editor/guide/)
  - [Sublime Text](tools/editor/sublime.md) · [在线](https://oi-wiki.org/tools/editor/sublime/)
  - [CP Editor](tools/editor/cpeditor.md) · [在线](https://oi-wiki.org/tools/editor/cpeditor/)
  - [Code::Blocks](tools/editor/codeblocks.md) · [在线](https://oi-wiki.org/tools/editor/codeblocks/)
- **评测工具**
  - [评测工具简介](tools/judger/index.md) · [在线](https://oi-wiki.org/tools/judger/)
  - [Arbiter](tools/judger/arbiter.md) · [在线](https://oi-wiki.org/tools/judger/arbiter/)
  - [Cena](tools/judger/cena.md) · [在线](https://oi-wiki.org/tools/judger/cena/)
  - [CCR Plus](tools/judger/ccr-plus.md) · [在线](https://oi-wiki.org/tools/judger/ccr-plus/)
  - [Lemon](tools/judger/lemon.md) · [在线](https://oi-wiki.org/tools/judger/lemon/)
- [命令行](tools/cmd.md) · [在线](https://oi-wiki.org/tools/cmd/)
- [命令行编译与调试](tools/compile-debug.md) · [在线](https://oi-wiki.org/tools/compile-debug/)
- [编译器](tools/compiler.md) · [在线](https://oi-wiki.org/tools/compiler/)
- [WSL (Windows 10)](tools/wsl.md) · [在线](https://oi-wiki.org/tools/wsl/)
- [Special Judge](tools/special-judge.md) · [在线](https://oi-wiki.org/tools/special-judge/)
- **Testlib**
  - [Testlib 简介](tools/testlib/index.md) · [在线](https://oi-wiki.org/tools/testlib/)
  - [通用](tools/testlib/general.md) · [在线](https://oi-wiki.org/tools/testlib/general/)
  - [Generator](tools/testlib/generator.md) · [在线](https://oi-wiki.org/tools/testlib/generator/)
  - [Validator](tools/testlib/validator.md) · [在线](https://oi-wiki.org/tools/testlib/validator/)
  - [Interactor](tools/testlib/interactor.md) · [在线](https://oi-wiki.org/tools/testlib/interactor/)
  - [Checker](tools/testlib/checker.md) · [在线](https://oi-wiki.org/tools/testlib/checker/)
- [Polygon](tools/polygon.md) · [在线](https://oi-wiki.org/tools/polygon/)
- [OJ 工具](tools/oj-tool.md) · [在线](https://oi-wiki.org/tools/oj-tool/)
- [LaTeX 入门](tools/latex.md) · [在线](https://oi-wiki.org/tools/latex/)
- [Git](tools/git.md) · [在线](https://oi-wiki.org/tools/git/)

### 语言基础

- [语言基础简介](lang/index.md) · [在线](https://oi-wiki.org/lang/)
- **C++ 基础**
  - [Hello, World!](lang/helloworld.md) · [在线](https://oi-wiki.org/lang/helloworld/)
  - [C++ 语法基础](lang/basic.md) · [在线](https://oi-wiki.org/lang/basic/)
  - [变量](lang/var.md) · [在线](https://oi-wiki.org/lang/var/)
  - [运算](lang/op.md) · [在线](https://oi-wiki.org/lang/op/)
  - **流程控制语句**
    - [分支](lang/branch.md) · [在线](https://oi-wiki.org/lang/branch/)
    - [循环](lang/loop.md) · [在线](https://oi-wiki.org/lang/loop/)
  - **高级数据类型**
    - [数组](lang/array.md) · [在线](https://oi-wiki.org/lang/array/)
    - [结构体](lang/struct.md) · [在线](https://oi-wiki.org/lang/struct/)
    - [联合体](lang/union.md) · [在线](https://oi-wiki.org/lang/union/)
    - [指针](lang/pointer.md) · [在线](https://oi-wiki.org/lang/pointer/)
  - [函数](lang/func.md) · [在线](https://oi-wiki.org/lang/func/)
  - [文件操作](lang/file-op.md) · [在线](https://oi-wiki.org/lang/file-op/)
- **C++ 标准库**
  - [C++ 标准库简介](lang/csl/index.md) · [在线](https://oi-wiki.org/lang/csl/)
  - **STL 容器**
    - [STL 容器简介](lang/csl/container.md) · [在线](https://oi-wiki.org/lang/csl/container/)
    - [迭代器](lang/csl/iterator.md) · [在线](https://oi-wiki.org/lang/csl/iterator/)
    - [序列式容器](lang/csl/sequence-container.md) · [在线](https://oi-wiki.org/lang/csl/sequence-container/)
    - [关联式容器](lang/csl/associative-container.md) · [在线](https://oi-wiki.org/lang/csl/associative-container/)
    - [无序关联式容器](lang/csl/unordered-container.md) · [在线](https://oi-wiki.org/lang/csl/unordered-container/)
    - [容器适配器](lang/csl/container-adapter.md) · [在线](https://oi-wiki.org/lang/csl/container-adapter/)
  - [STL 算法](lang/csl/algorithm.md) · [在线](https://oi-wiki.org/lang/csl/algorithm/)
  - [bitset](lang/csl/bitset.md) · [在线](https://oi-wiki.org/lang/csl/bitset/)
  - [string](lang/csl/string.md) · [在线](https://oi-wiki.org/lang/csl/string/)
  - [pair](lang/csl/pair.md) · [在线](https://oi-wiki.org/lang/csl/pair/)
- **C++ 进阶**
  - [类](lang/class.md) · [在线](https://oi-wiki.org/lang/class/)
  - [命名空间](lang/namespace.md) · [在线](https://oi-wiki.org/lang/namespace/)
  - [值类别](lang/value-category.md) · [在线](https://oi-wiki.org/lang/value-category/)
  - [重载运算符](lang/op-overload.md) · [在线](https://oi-wiki.org/lang/op-overload/)
  - [引用](lang/reference.md) · [在线](https://oi-wiki.org/lang/reference/)
  - [常量](lang/const.md) · [在线](https://oi-wiki.org/lang/const/)
  - [新版 C++ 特性](lang/new.md) · [在线](https://oi-wiki.org/lang/new/)
  - [Lambda 表达式](lang/lambda.md) · [在线](https://oi-wiki.org/lang/lambda/)
  - **pb_ds**
    - [pb_ds 简介](lang/pb-ds/index.md) · [在线](https://oi-wiki.org/lang/pb-ds/)
    - [堆](lang/pb-ds/pq.md) · [在线](https://oi-wiki.org/lang/pb-ds/pq/)
    - [平衡树](lang/pb-ds/tree.md) · [在线](https://oi-wiki.org/lang/pb-ds/tree/)
  - [编译优化](lang/optimizations.md) · [在线](https://oi-wiki.org/lang/optimizations/)
- [C++ 与其他常用语言的区别](lang/cpp-other-langs.md) · [在线](https://oi-wiki.org/lang/cpp-other-langs/)
- [Pascal 转 C++ 急救](lang/pas-cpp.md) · [在线](https://oi-wiki.org/lang/pas-cpp/)
- [Python 速成](lang/python.md) · [在线](https://oi-wiki.org/lang/python/)
- [Java 速成](lang/java.md) · [在线](https://oi-wiki.org/lang/java/)
- [Java 进阶](lang/java-pro.md) · [在线](https://oi-wiki.org/lang/java-pro/)

### 算法基础

- [算法基础简介](basic/index.md) · [在线](https://oi-wiki.org/basic/)
- **复杂度**
  - [复杂度简介](basic/complexity.md) · [在线](https://oi-wiki.org/basic/complexity/)
  - [均摊复杂度](basic/amortized-analysis.md) · [在线](https://oi-wiki.org/basic/amortized-analysis/)
- [枚举](basic/enumerate.md) · [在线](https://oi-wiki.org/basic/enumerate/)
- [模拟](basic/simulate.md) · [在线](https://oi-wiki.org/basic/simulate/)
- [递归 & 分治](basic/divide-and-conquer.md) · [在线](https://oi-wiki.org/basic/divide-and-conquer/)
- [贪心](basic/greedy.md) · [在线](https://oi-wiki.org/basic/greedy/)
- **排序**
  - [排序简介](basic/sort-intro.md) · [在线](https://oi-wiki.org/basic/sort-intro/)
  - [选择排序](basic/selection-sort.md) · [在线](https://oi-wiki.org/basic/selection-sort/)
  - [冒泡排序](basic/bubble-sort.md) · [在线](https://oi-wiki.org/basic/bubble-sort/)
  - [插入排序](basic/insertion-sort.md) · [在线](https://oi-wiki.org/basic/insertion-sort/)
  - [计数排序](basic/counting-sort.md) · [在线](https://oi-wiki.org/basic/counting-sort/)
  - [基数排序](basic/radix-sort.md) · [在线](https://oi-wiki.org/basic/radix-sort/)
  - [快速排序](basic/quick-sort.md) · [在线](https://oi-wiki.org/basic/quick-sort/)
  - [归并排序](basic/merge-sort.md) · [在线](https://oi-wiki.org/basic/merge-sort/)
  - [堆排序](basic/heap-sort.md) · [在线](https://oi-wiki.org/basic/heap-sort/)
  - [桶排序](basic/bucket-sort.md) · [在线](https://oi-wiki.org/basic/bucket-sort/)
  - [希尔排序](basic/shell-sort.md) · [在线](https://oi-wiki.org/basic/shell-sort/)
  - [锦标赛排序](basic/tournament-sort.md) · [在线](https://oi-wiki.org/basic/tournament-sort/)
  - [Tim 排序](basic/tim-sort.md) · [在线](https://oi-wiki.org/basic/tim-sort/)
  - [排序相关 STL](basic/stl-sort.md) · [在线](https://oi-wiki.org/basic/stl-sort/)
  - [排序应用](basic/use-of-sort.md) · [在线](https://oi-wiki.org/basic/use-of-sort/)
- [前缀和 & 差分](basic/prefix-sum.md) · [在线](https://oi-wiki.org/basic/prefix-sum/)
- [二分](basic/binary.md) · [在线](https://oi-wiki.org/basic/binary/)
- [倍增](basic/binary-lifting.md) · [在线](https://oi-wiki.org/basic/binary-lifting/)
- [构造](basic/construction.md) · [在线](https://oi-wiki.org/basic/construction/)

### 搜索

- [搜索部分简介](search/index.md) · [在线](https://oi-wiki.org/search/)
- [DFS（搜索）](search/dfs.md) · [在线](https://oi-wiki.org/search/dfs/)
- [BFS（搜索）](search/bfs.md) · [在线](https://oi-wiki.org/search/bfs/)
- [双向搜索](search/bidirectional.md) · [在线](https://oi-wiki.org/search/bidirectional/)
- [启发式搜索](search/heuristic.md) · [在线](https://oi-wiki.org/search/heuristic/)
- [A*](search/astar.md) · [在线](https://oi-wiki.org/search/astar/)
- [迭代加深搜索](search/iterative.md) · [在线](https://oi-wiki.org/search/iterative/)
- [IDA*](search/idastar.md) · [在线](https://oi-wiki.org/search/idastar/)
- [回溯法](search/backtracking.md) · [在线](https://oi-wiki.org/search/backtracking/)
- [Dancing Links](search/dlx.md) · [在线](https://oi-wiki.org/search/dlx/)
- [Alpha–Beta 剪枝](search/alpha-beta.md) · [在线](https://oi-wiki.org/search/alpha-beta/)
- [优化](search/opt.md) · [在线](https://oi-wiki.org/search/opt/)

### 动态规划

- [动态规划部分简介](dp/index.md) · [在线](https://oi-wiki.org/dp/)
- [动态规划基础](dp/basic.md) · [在线](https://oi-wiki.org/dp/basic/)
- [记忆化搜索](dp/memo.md) · [在线](https://oi-wiki.org/dp/memo/)
- **背包 DP**
  - [背包 DP 基础](dp/knapsack/basic.md) · [在线](https://oi-wiki.org/dp/knapsack/basic/)
  - [背包 DP 进阶](dp/knapsack/advanced.md) · [在线](https://oi-wiki.org/dp/knapsack/advanced/)
- [区间 DP](dp/interval.md) · [在线](https://oi-wiki.org/dp/interval/)
- [DAG 上的 DP](dp/dag.md) · [在线](https://oi-wiki.org/dp/dag/)
- [树形 DP](dp/tree.md) · [在线](https://oi-wiki.org/dp/tree/)
- [状压 DP](dp/state.md) · [在线](https://oi-wiki.org/dp/state/)
- [数位 DP](dp/number.md) · [在线](https://oi-wiki.org/dp/number/)
- [插头 DP](dp/plug.md) · [在线](https://oi-wiki.org/dp/plug/)
- [计数 DP](dp/count.md) · [在线](https://oi-wiki.org/dp/count/)
- [动态 DP](dp/dynamic.md) · [在线](https://oi-wiki.org/dp/dynamic/)
- [概率 DP](dp/probability.md) · [在线](https://oi-wiki.org/dp/probability/)
- [DP 套 DP](dp/dp-of-dp.md) · [在线](https://oi-wiki.org/dp/dp-of-dp/)
- **DP 优化**
  - [DP 优化简介](dp/opt/dp-opt.md) · [在线](https://oi-wiki.org/dp/opt/dp-opt/)
  - [单调队列/单调栈优化](dp/opt/monotonic-queue-stack.md) · [在线](https://oi-wiki.org/dp/opt/monotonic-queue-stack/)
  - [斜率优化](dp/opt/slope.md) · [在线](https://oi-wiki.org/dp/opt/slope/)
  - [四边形不等式优化](dp/opt/quadrangle.md) · [在线](https://oi-wiki.org/dp/opt/quadrangle/)
  - [Slope Trick 优化](dp/opt/slope-trick.md) · [在线](https://oi-wiki.org/dp/opt/slope-trick/)
  - [WQS 二分](dp/opt/wqs-binary-search.md) · [在线](https://oi-wiki.org/dp/opt/wqs-binary-search/)
  - [状态设计优化](dp/opt/state.md) · [在线](https://oi-wiki.org/dp/opt/state/)

### 字符串

- [字符串部分简介](string/index.md) · [在线](https://oi-wiki.org/string/)
- [字符串基础](string/basic.md) · [在线](https://oi-wiki.org/string/basic/)
- [标准库](string/lib-func.md) · [在线](https://oi-wiki.org/string/lib-func/)
- [字符串匹配](string/match.md) · [在线](https://oi-wiki.org/string/match/)
- [字符串哈希](string/hash.md) · [在线](https://oi-wiki.org/string/hash/)
- [字典树 (Trie)](string/trie.md) · [在线](https://oi-wiki.org/string/trie/)
- [前缀函数与 KMP 算法](string/kmp.md) · [在线](https://oi-wiki.org/string/kmp/)
- [Boyer–Moore 算法](string/bm.md) · [在线](https://oi-wiki.org/string/bm/)
- [Z 函数（扩展 KMP）](string/z-func.md) · [在线](https://oi-wiki.org/string/z-func/)
- [AC 自动机](string/ac-automaton.md) · [在线](https://oi-wiki.org/string/ac-automaton/)
- **后缀数组 (SA)**
  - [后缀数组简介](string/sa.md) · [在线](https://oi-wiki.org/string/sa/)
  - [最优原地后缀排序算法](string/sa-optimal-inplace.md) · [在线](https://oi-wiki.org/string/sa-optimal-inplace/)
- [后缀自动机 (SAM)](string/sam.md) · [在线](https://oi-wiki.org/string/sam/)
- [后缀平衡树](string/suffix-bst.md) · [在线](https://oi-wiki.org/string/suffix-bst/)
- [广义后缀自动机](string/general-sam.md) · [在线](https://oi-wiki.org/string/general-sam/)
- [后缀树](string/suffix-tree.md) · [在线](https://oi-wiki.org/string/suffix-tree/)
- [Manacher](string/manacher.md) · [在线](https://oi-wiki.org/string/manacher/)
- [回文树](string/pam.md) · [在线](https://oi-wiki.org/string/pam/)
- [序列自动机](string/seq-automaton.md) · [在线](https://oi-wiki.org/string/seq-automaton/)
- [最小表示法](string/minimal-string.md) · [在线](https://oi-wiki.org/string/minimal-string/)
- [Lyndon 分解](string/lyndon.md) · [在线](https://oi-wiki.org/string/lyndon/)
- [Main–Lorentz 算法](string/main-lorentz.md) · [在线](https://oi-wiki.org/string/main-lorentz/)

### 数学

- [数学部分简介](math/index.md) · [在线](https://oi-wiki.org/math/)
- [布尔代数](math/boolean-algebra.md) · [在线](https://oi-wiki.org/math/boolean-algebra/)
- **数字系统**
  - [数字系统简介](math/numeral-sys/intro.md) · [在线](https://oi-wiki.org/math/numeral-sys/intro/)
  - [进位制](math/numeral-sys/base.md) · [在线](https://oi-wiki.org/math/numeral-sys/base/)
  - [平衡三进制](math/numeral-sys/balanced-ternary.md) · [在线](https://oi-wiki.org/math/numeral-sys/balanced-ternary/)
  - [格雷码](math/numeral-sys/gray-code.md) · [在线](https://oi-wiki.org/math/numeral-sys/gray-code/)
- [位操作](math/bit.md) · [在线](https://oi-wiki.org/math/bit/)
- [二进制集合操作](math/binary-set.md) · [在线](https://oi-wiki.org/math/binary-set/)
- [高精度计算](math/bignum.md) · [在线](https://oi-wiki.org/math/bignum/)
- [快速幂](math/binary-exponentiation.md) · [在线](https://oi-wiki.org/math/binary-exponentiation/)
- [置换和排列](math/permutation.md) · [在线](https://oi-wiki.org/math/permutation/)
- [弧度制与坐标系](math/coordinate.md) · [在线](https://oi-wiki.org/math/coordinate/)
- [复数](math/complex.md) · [在线](https://oi-wiki.org/math/complex/)
- **数论**
  - [数论基础](math/number-theory/basic.md) · [在线](https://oi-wiki.org/math/number-theory/basic/)
  - [模算术简介](math/number-theory/mod-arithmetic.md) · [在线](https://oi-wiki.org/math/number-theory/mod-arithmetic/)
  - [素数](math/number-theory/prime.md) · [在线](https://oi-wiki.org/math/number-theory/prime/)
  - [最大公约数](math/number-theory/gcd.md) · [在线](https://oi-wiki.org/math/number-theory/gcd/)
  - [欧拉函数](math/number-theory/euler-totient.md) · [在线](https://oi-wiki.org/math/number-theory/euler-totient/)
  - [筛法](math/number-theory/sieve.md) · [在线](https://oi-wiki.org/math/number-theory/sieve/)
  - [分解质因数](math/number-theory/pollard-rho.md) · [在线](https://oi-wiki.org/math/number-theory/pollard-rho/)
  - [裴蜀定理 & 一次不定方程](math/number-theory/bezouts.md) · [在线](https://oi-wiki.org/math/number-theory/bezouts/)
  - [费马小定理 & 欧拉定理](math/number-theory/fermat.md) · [在线](https://oi-wiki.org/math/number-theory/fermat/)
  - [模逆元](math/number-theory/inverse.md) · [在线](https://oi-wiki.org/math/number-theory/inverse/)
  - [线性同余方程](math/number-theory/linear-equation.md) · [在线](https://oi-wiki.org/math/number-theory/linear-equation/)
  - [中国剩余定理](math/number-theory/crt.md) · [在线](https://oi-wiki.org/math/number-theory/crt/)
  - [升幂引理](math/number-theory/lift-the-exponent.md) · [在线](https://oi-wiki.org/math/number-theory/lift-the-exponent/)
  - [阶乘取模](math/number-theory/factorial.md) · [在线](https://oi-wiki.org/math/number-theory/factorial/)
  - [卢卡斯定理](math/number-theory/lucas.md) · [在线](https://oi-wiki.org/math/number-theory/lucas/)
  - [同余方程](math/number-theory/congruence-equation.md) · [在线](https://oi-wiki.org/math/number-theory/congruence-equation/)
  - [二次剩余](math/number-theory/quad-residue.md) · [在线](https://oi-wiki.org/math/number-theory/quad-residue/)
  - [阶 & 原根](math/number-theory/primitive-root.md) · [在线](https://oi-wiki.org/math/number-theory/primitive-root/)
  - [离散对数](math/number-theory/discrete-logarithm.md) · [在线](https://oi-wiki.org/math/number-theory/discrete-logarithm/)
  - [高次剩余 & 单位根](math/number-theory/residue.md) · [在线](https://oi-wiki.org/math/number-theory/residue/)
  - [数论分块](math/number-theory/sqrt-decomposition.md) · [在线](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)
  - [狄利克雷卷积](math/number-theory/dirichlet.md) · [在线](https://oi-wiki.org/math/number-theory/dirichlet/)
  - [莫比乌斯反演](math/number-theory/mobius.md) · [在线](https://oi-wiki.org/math/number-theory/mobius/)
  - [狄利克雷双曲线法 & 杜教筛](math/number-theory/hyperbola.md) · [在线](https://oi-wiki.org/math/number-theory/hyperbola/)
  - [素数计数](math/number-theory/prime-counting.md) · [在线](https://oi-wiki.org/math/number-theory/prime-counting/)
  - [Powerful Number 筛](math/number-theory/powerful-number.md) · [在线](https://oi-wiki.org/math/number-theory/powerful-number/)
  - [Min_25 筛](math/number-theory/min-25.md) · [在线](https://oi-wiki.org/math/number-theory/min-25/)
  - [洲阁筛](math/number-theory/zhou.md) · [在线](https://oi-wiki.org/math/number-theory/zhou/)
  - [类欧几里得算法](math/number-theory/euclidean.md) · [在线](https://oi-wiki.org/math/number-theory/euclidean/)
  - [连分数](math/number-theory/continued-fraction.md) · [在线](https://oi-wiki.org/math/number-theory/continued-fraction/)
  - [Stern–Brocot 树与 Farey 序列](math/number-theory/stern-brocot.md) · [在线](https://oi-wiki.org/math/number-theory/stern-brocot/)
  - [二次域](math/number-theory/quadratic.md) · [在线](https://oi-wiki.org/math/number-theory/quadratic/)
  - [Pell 方程](math/number-theory/pell-equation.md) · [在线](https://oi-wiki.org/math/number-theory/pell-equation/)
- **多项式与生成函数**
  - [多项式与生成函数简介](math/poly/intro.md) · [在线](https://oi-wiki.org/math/poly/intro/)
  - [代数基本定理](math/poly/fundamental.md) · [在线](https://oi-wiki.org/math/poly/fundamental/)
  - [快速傅里叶变换](math/poly/fft.md) · [在线](https://oi-wiki.org/math/poly/fft/)
  - [快速数论变换](math/poly/ntt.md) · [在线](https://oi-wiki.org/math/poly/ntt/)
  - [快速沃尔什变换](math/poly/fwt.md) · [在线](https://oi-wiki.org/math/poly/fwt/)
  - [Chirp Z 变换](math/poly/czt.md) · [在线](https://oi-wiki.org/math/poly/czt/)
  - [多项式牛顿迭代](math/poly/newton.md) · [在线](https://oi-wiki.org/math/poly/newton/)
  - [多项式多点求值|快速插值](math/poly/multipoint-eval-interpolation.md) · [在线](https://oi-wiki.org/math/poly/multipoint-eval-interpolation/)
  - [多项式初等函数](math/poly/elementary-func.md) · [在线](https://oi-wiki.org/math/poly/elementary-func/)
  - [常系数齐次线性递推](math/poly/linear-recurrence.md) · [在线](https://oi-wiki.org/math/poly/linear-recurrence/)
  - [多项式平移|连续点值平移](math/poly/shift.md) · [在线](https://oi-wiki.org/math/poly/shift/)
  - [符号化方法](math/poly/symbolic-method.md) · [在线](https://oi-wiki.org/math/poly/symbolic-method/)
  - [Lagrange 反演](math/poly/lagrange-inversion.md) · [在线](https://oi-wiki.org/math/poly/lagrange-inversion/)
  - [形式幂级数复合|复合逆](math/poly/comp-rev.md) · [在线](https://oi-wiki.org/math/poly/comp-rev/)
  - [普通生成函数](math/poly/ogf.md) · [在线](https://oi-wiki.org/math/poly/ogf/)
  - [指数生成函数](math/poly/egf.md) · [在线](https://oi-wiki.org/math/poly/egf/)
- **组合数学**
  - [排列组合](math/combinatorics/combination.md) · [在线](https://oi-wiki.org/math/combinatorics/combination/)
  - [抽屉原理](math/combinatorics/drawer-principle.md) · [在线](https://oi-wiki.org/math/combinatorics/drawer-principle/)
  - [容斥原理](math/combinatorics/inclusion-exclusion-principle.md) · [在线](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/)
  - [斐波那契数列](math/combinatorics/fibonacci.md) · [在线](https://oi-wiki.org/math/combinatorics/fibonacci/)
  - [错位排列](math/combinatorics/derangement.md) · [在线](https://oi-wiki.org/math/combinatorics/derangement/)
  - [卡特兰数](math/combinatorics/catalan.md) · [在线](https://oi-wiki.org/math/combinatorics/catalan/)
  - [斯特林数](math/combinatorics/stirling.md) · [在线](https://oi-wiki.org/math/combinatorics/stirling/)
  - [贝尔数](math/combinatorics/bell.md) · [在线](https://oi-wiki.org/math/combinatorics/bell/)
  - [伯努利数](math/combinatorics/bernoulli.md) · [在线](https://oi-wiki.org/math/combinatorics/bernoulli/)
  - [Entringer Number](math/combinatorics/entringer.md) · [在线](https://oi-wiki.org/math/combinatorics/entringer/)
  - [Eulerian Number](math/combinatorics/eulerian.md) · [在线](https://oi-wiki.org/math/combinatorics/eulerian/)
  - [分拆数](math/combinatorics/partition.md) · [在线](https://oi-wiki.org/math/combinatorics/partition/)
  - [范德蒙德卷积](math/combinatorics/vandermonde-convolution.md) · [在线](https://oi-wiki.org/math/combinatorics/vandermonde-convolution/)
  - [Pólya 计数](math/combinatorics/polya.md) · [在线](https://oi-wiki.org/math/combinatorics/polya/)
  - [图论计数](math/combinatorics/graph-enumeration.md) · [在线](https://oi-wiki.org/math/combinatorics/graph-enumeration/)
- **线性代数**
  - [线性代数简介](math/linear-algebra/index.md) · [在线](https://oi-wiki.org/math/linear-algebra/)
  - [向量](math/linear-algebra/vector.md) · [在线](https://oi-wiki.org/math/linear-algebra/vector/)
  - [内积和外积](math/linear-algebra/product.md) · [在线](https://oi-wiki.org/math/linear-algebra/product/)
  - [矩阵](math/linear-algebra/matrix.md) · [在线](https://oi-wiki.org/math/linear-algebra/matrix/)
  - [初等变换](math/linear-algebra/elementary-operations.md) · [在线](https://oi-wiki.org/math/linear-algebra/elementary-operations/)
  - [行列式](math/linear-algebra/determinant.md) · [在线](https://oi-wiki.org/math/linear-algebra/determinant/)
  - [线性空间](math/linear-algebra/vector-space.md) · [在线](https://oi-wiki.org/math/linear-algebra/vector-space/)
  - [线性基](math/linear-algebra/basis.md) · [在线](https://oi-wiki.org/math/linear-algebra/basis/)
  - [线性映射](math/linear-algebra/linear-mapping.md) · [在线](https://oi-wiki.org/math/linear-algebra/linear-mapping/)
  - [特征多项式](math/linear-algebra/char-poly.md) · [在线](https://oi-wiki.org/math/linear-algebra/char-poly/)
  - [对角化](math/linear-algebra/diagonalization.md) · [在线](https://oi-wiki.org/math/linear-algebra/diagonalization/)
  - [Jordan标准型](math/linear-algebra/jordan.md) · [在线](https://oi-wiki.org/math/linear-algebra/jordan/)
- **线性规划**
  - [线性规划基础](math/linear-programming.md) · [在线](https://oi-wiki.org/math/linear-programming/)
  - [单纯形法](math/simplex.md) · [在线](https://oi-wiki.org/math/simplex/)
- **抽象代数**
  - [基本概念](math/algebra/basic.md) · [在线](https://oi-wiki.org/math/algebra/basic/)
  - [群论](math/algebra/group-theory.md) · [在线](https://oi-wiki.org/math/algebra/group-theory/)
  - [环论](math/algebra/ring-theory.md) · [在线](https://oi-wiki.org/math/algebra/ring-theory/)
  - [域论](math/algebra/field-theory.md) · [在线](https://oi-wiki.org/math/algebra/field-theory/)
  - [Schreier–Sims 算法](math/algebra/schreier-sims.md) · [在线](https://oi-wiki.org/math/algebra/schreier-sims/)
- **概率论**
  - [基本概念](math/probability/basic-conception.md) · [在线](https://oi-wiki.org/math/probability/basic-conception/)
  - [条件概率与独立性](math/probability/conditional-probability.md) · [在线](https://oi-wiki.org/math/probability/conditional-probability/)
  - [随机变量](math/probability/random-variable.md) · [在线](https://oi-wiki.org/math/probability/random-variable/)
  - [随机变量的数字特征](math/probability/exp-var.md) · [在线](https://oi-wiki.org/math/probability/exp-var/)
  - [概率不等式](math/probability/concentration-inequality.md) · [在线](https://oi-wiki.org/math/probability/concentration-inequality/)
- **博弈论**
  - [博弈论简介](math/game-theory/intro.md) · [在线](https://oi-wiki.org/math/game-theory/intro/)
  - [公平组合游戏](math/game-theory/impartial-game.md) · [在线](https://oi-wiki.org/math/game-theory/impartial-game/)
  - [零和游戏](math/game-theory/zero-sum-game.md) · [在线](https://oi-wiki.org/math/game-theory/zero-sum-game/)
  - [非公平组合游戏](math/game-theory/partizan-game.md) · [在线](https://oi-wiki.org/math/game-theory/partizan-game/)
- **数值算法**
  - [插值](math/numerical/interp.md) · [在线](https://oi-wiki.org/math/numerical/interp/)
  - [数值积分](math/numerical/integral.md) · [在线](https://oi-wiki.org/math/numerical/integral/)
  - [高斯消元](math/numerical/gauss.md) · [在线](https://oi-wiki.org/math/numerical/gauss/)
  - [牛顿迭代法](math/numerical/newton.md) · [在线](https://oi-wiki.org/math/numerical/newton/)
- [序理论](math/order-theory.md) · [在线](https://oi-wiki.org/math/order-theory/)
- [杨氏矩阵](math/young-tableau.md) · [在线](https://oi-wiki.org/math/young-tableau/)
- [拟阵](math/matroid.md) · [在线](https://oi-wiki.org/math/matroid/)
- [Berlekamp–Massey 算法](math/berlekamp-massey.md) · [在线](https://oi-wiki.org/math/berlekamp-massey/)

### 数据结构

- [数据结构部分简介](ds/index.md) · [在线](https://oi-wiki.org/ds/)
- [栈](ds/stack.md) · [在线](https://oi-wiki.org/ds/stack/)
- [队列](ds/queue.md) · [在线](https://oi-wiki.org/ds/queue/)
- [链表](ds/linked-list.md) · [在线](https://oi-wiki.org/ds/linked-list/)
- [哈希表](ds/hash.md) · [在线](https://oi-wiki.org/ds/hash/)
- **并查集**
  - [并查集](ds/dsu.md) · [在线](https://oi-wiki.org/ds/dsu/)
  - [并查集复杂度](ds/dsu-complexity.md) · [在线](https://oi-wiki.org/ds/dsu-complexity/)
- **堆**
  - [堆简介](ds/heap.md) · [在线](https://oi-wiki.org/ds/heap/)
  - [二叉堆](ds/binary-heap.md) · [在线](https://oi-wiki.org/ds/binary-heap/)
  - [配对堆](ds/pairing-heap.md) · [在线](https://oi-wiki.org/ds/pairing-heap/)
  - [左偏树](ds/leftist-tree.md) · [在线](https://oi-wiki.org/ds/leftist-tree/)
- **块状数据结构**
  - [分块思想](ds/decompose.md) · [在线](https://oi-wiki.org/ds/decompose/)
  - [块状数组](ds/block-array.md) · [在线](https://oi-wiki.org/ds/block-array/)
  - [块状链表](ds/block-list.md) · [在线](https://oi-wiki.org/ds/block-list/)
  - [树分块](ds/tree-decompose.md) · [在线](https://oi-wiki.org/ds/tree-decompose/)
  - [Sqrt Tree](ds/sqrt-tree.md) · [在线](https://oi-wiki.org/ds/sqrt-tree/)
- [单调栈](ds/monotonic-stack.md) · [在线](https://oi-wiki.org/ds/monotonic-stack/)
- [单调队列](ds/monotonic-queue.md) · [在线](https://oi-wiki.org/ds/monotonic-queue/)
- [ST 表](ds/sparse-table.md) · [在线](https://oi-wiki.org/ds/sparse-table/)
- [树状数组](ds/fenwick.md) · [在线](https://oi-wiki.org/ds/fenwick/)
- **线段树**
  - [线段树基础](ds/seg.md) · [在线](https://oi-wiki.org/ds/seg/)
  - [线段树合并 & 分裂](ds/seg-merge-split.md) · [在线](https://oi-wiki.org/ds/seg-merge-split/)
  - [李超线段树](ds/li-chao-tree.md) · [在线](https://oi-wiki.org/ds/li-chao-tree/)
  - [猫树](ds/cat-tree.md) · [在线](https://oi-wiki.org/ds/cat-tree/)
  - [区间最值操作 & 区间历史最值](ds/seg-beats.md) · [在线](https://oi-wiki.org/ds/seg-beats/)
  - [Kinetic Tournament Tree](ds/kinetic-tournament-tree.md) · [在线](https://oi-wiki.org/ds/kinetic-tournament-tree/)
- [划分树](ds/dividing.md) · [在线](https://oi-wiki.org/ds/dividing/)
- **二叉搜索树 & 平衡树**
  - [二叉搜索树 & 平衡树](ds/bst.md) · [在线](https://oi-wiki.org/ds/bst/)
  - [Treap](ds/treap.md) · [在线](https://oi-wiki.org/ds/treap/)
  - [Splay 树](ds/splay.md) · [在线](https://oi-wiki.org/ds/splay/)
  - [WBLT](ds/wblt.md) · [在线](https://oi-wiki.org/ds/wblt/)
  - [替罪羊树](ds/sgt.md) · [在线](https://oi-wiki.org/ds/sgt/)
  - [笛卡尔树](ds/cartesian-tree.md) · [在线](https://oi-wiki.org/ds/cartesian-tree/)
  - [Size Balanced Tree](ds/sbt.md) · [在线](https://oi-wiki.org/ds/sbt/)
  - [AVL 树](ds/avl.md) · [在线](https://oi-wiki.org/ds/avl/)
  - [红黑树](ds/rbtree.md) · [在线](https://oi-wiki.org/ds/rbtree/)
  - [左偏红黑树](ds/llrbt.md) · [在线](https://oi-wiki.org/ds/llrbt/)
  - [AA 树](ds/aa-tree.md) · [在线](https://oi-wiki.org/ds/aa-tree/)
- [跳表](ds/skiplist.md) · [在线](https://oi-wiki.org/ds/skiplist/)
- **可持久化数据结构**
  - [可持久化数据结构简介](ds/persistent.md) · [在线](https://oi-wiki.org/ds/persistent/)
  - [可持久化线段树](ds/persistent-seg.md) · [在线](https://oi-wiki.org/ds/persistent-seg/)
  - [可持久化块状数组](ds/persistent-block-array.md) · [在线](https://oi-wiki.org/ds/persistent-block-array/)
  - [可持久化平衡树](ds/persistent-balanced.md) · [在线](https://oi-wiki.org/ds/persistent-balanced/)
  - [可持久化字典树](ds/persistent-trie.md) · [在线](https://oi-wiki.org/ds/persistent-trie/)
  - [可持久化可并堆](ds/persistent-heap.md) · [在线](https://oi-wiki.org/ds/persistent-heap/)
- **树套树**
  - [线段树套线段树](ds/seg-in-seg.md) · [在线](https://oi-wiki.org/ds/seg-in-seg/)
  - [平衡树套线段树](ds/seg-in-balanced.md) · [在线](https://oi-wiki.org/ds/seg-in-balanced/)
  - [线段树套平衡树](ds/balanced-in-seg.md) · [在线](https://oi-wiki.org/ds/balanced-in-seg/)
  - [树状数组套权值线段树](ds/seg-in-bit.md) · [在线](https://oi-wiki.org/ds/seg-in-bit/)
  - [分块套树状数组](ds/bit-in-block-array.md) · [在线](https://oi-wiki.org/ds/bit-in-block-array/)
- [K-D Tree](ds/kdt.md) · [在线](https://oi-wiki.org/ds/kdt/)
- **动态树**
  - [Link Cut Tree](ds/lct.md) · [在线](https://oi-wiki.org/ds/lct/)
  - [全局平衡二叉树](ds/global-bst.md) · [在线](https://oi-wiki.org/ds/global-bst/)
  - [Euler Tour Tree](ds/ett.md) · [在线](https://oi-wiki.org/ds/ett/)
  - [Top Tree](ds/top-tree.md) · [在线](https://oi-wiki.org/ds/top-tree/)
- [析合树](ds/divide-combine.md) · [在线](https://oi-wiki.org/ds/divide-combine/)
- [PQ 树](ds/pq-tree.md) · [在线](https://oi-wiki.org/ds/pq-tree/)
- [手指树](ds/finger-tree.md) · [在线](https://oi-wiki.org/ds/finger-tree/)
- [霍夫曼树](ds/huffman-tree.md) · [在线](https://oi-wiki.org/ds/huffman-tree/)

### 图论

- [图论部分简介](graph/index.md) · [在线](https://oi-wiki.org/graph/)
- [图论相关概念](graph/concept.md) · [在线](https://oi-wiki.org/graph/concept/)
- [图的存储](graph/save.md) · [在线](https://oi-wiki.org/graph/save/)
- [DFS（图论）](graph/dfs.md) · [在线](https://oi-wiki.org/graph/dfs/)
- [BFS（图论）](graph/bfs.md) · [在线](https://oi-wiki.org/graph/bfs/)
- **树上问题**
  - [树基础](graph/tree-basic.md) · [在线](https://oi-wiki.org/graph/tree-basic/)
  - [树的直径](graph/tree-diameter.md) · [在线](https://oi-wiki.org/graph/tree-diameter/)
  - [树的中心](graph/tree-center.md) · [在线](https://oi-wiki.org/graph/tree-center/)
  - [树的重心](graph/tree-centroid.md) · [在线](https://oi-wiki.org/graph/tree-centroid/)
  - [最近公共祖先](graph/lca.md) · [在线](https://oi-wiki.org/graph/lca/)
  - [树链剖分](graph/hld.md) · [在线](https://oi-wiki.org/graph/hld/)
  - [树上启发式合并](graph/dsu-on-tree.md) · [在线](https://oi-wiki.org/graph/dsu-on-tree/)
  - [虚树](graph/virtual-tree.md) · [在线](https://oi-wiki.org/graph/virtual-tree/)
  - [树分治](graph/tree-divide.md) · [在线](https://oi-wiki.org/graph/tree-divide/)
  - [动态树分治](graph/dynamic-tree-divide.md) · [在线](https://oi-wiki.org/graph/dynamic-tree-divide/)
  - [AHU 算法](graph/tree-ahu.md) · [在线](https://oi-wiki.org/graph/tree-ahu/)
  - [树哈希](graph/tree-hash.md) · [在线](https://oi-wiki.org/graph/tree-hash/)
  - [树上随机游走](graph/tree-random-walk.md) · [在线](https://oi-wiki.org/graph/tree-random-walk/)
- [有向无环图](graph/dag.md) · [在线](https://oi-wiki.org/graph/dag/)
- [拓扑排序](graph/topo.md) · [在线](https://oi-wiki.org/graph/topo/)
- **最短路问题**
  - [最短路](graph/shortest-path.md) · [在线](https://oi-wiki.org/graph/shortest-path/)
  - [差分约束](graph/diff-constraints.md) · [在线](https://oi-wiki.org/graph/diff-constraints/)
  - [k 短路](graph/kth-path.md) · [在线](https://oi-wiki.org/graph/kth-path/)
  - [同余最短路](graph/mod-shortest-path.md) · [在线](https://oi-wiki.org/graph/mod-shortest-path/)
- **生成树问题**
  - [最小生成树](graph/mst.md) · [在线](https://oi-wiki.org/graph/mst/)
  - [最小树形图](graph/dmst.md) · [在线](https://oi-wiki.org/graph/dmst/)
  - [最小直径生成树](graph/mdst.md) · [在线](https://oi-wiki.org/graph/mdst/)
- [斯坦纳树](graph/steiner-tree.md) · [在线](https://oi-wiki.org/graph/steiner-tree/)
- [拆点](graph/node.md) · [在线](https://oi-wiki.org/graph/node/)
- **连通性相关**
  - [强连通分量](graph/scc.md) · [在线](https://oi-wiki.org/graph/scc/)
  - [双连通分量](graph/bcc.md) · [在线](https://oi-wiki.org/graph/bcc/)
  - [割点和桥](graph/cut.md) · [在线](https://oi-wiki.org/graph/cut/)
  - [圆方树](graph/block-forest.md) · [在线](https://oi-wiki.org/graph/block-forest/)
  - [点/边连通度](graph/connectivity.md) · [在线](https://oi-wiki.org/graph/connectivity/)
- [环计数问题](graph/rings-count.md) · [在线](https://oi-wiki.org/graph/rings-count/)
- [最小环](graph/min-cycle.md) · [在线](https://oi-wiki.org/graph/min-cycle/)
- [2-SAT](graph/2-sat.md) · [在线](https://oi-wiki.org/graph/2-sat/)
- [欧拉图](graph/euler.md) · [在线](https://oi-wiki.org/graph/euler/)
- [哈密顿图](graph/hamilton.md) · [在线](https://oi-wiki.org/graph/hamilton/)
- [二分图](graph/bi-graph.md) · [在线](https://oi-wiki.org/graph/bi-graph/)
- [平面图](graph/planar.md) · [在线](https://oi-wiki.org/graph/planar/)
- [弦图](graph/chord.md) · [在线](https://oi-wiki.org/graph/chord/)
- [图的着色](graph/color.md) · [在线](https://oi-wiki.org/graph/color/)
- **网络流**
  - [网络流简介](graph/flow.md) · [在线](https://oi-wiki.org/graph/flow/)
  - [最大流](graph/flow/max-flow.md) · [在线](https://oi-wiki.org/graph/flow/max-flow/)
  - [最小割](graph/flow/min-cut.md) · [在线](https://oi-wiki.org/graph/flow/min-cut/)
  - [费用流](graph/flow/min-cost.md) · [在线](https://oi-wiki.org/graph/flow/min-cost/)
  - [上下界网络流](graph/flow/bound.md) · [在线](https://oi-wiki.org/graph/flow/bound/)
  - [Stoer–Wagner 算法](graph/stoer-wagner.md) · [在线](https://oi-wiki.org/graph/stoer-wagner/)
- **图的匹配**
  - [图匹配](graph/graph-matching/graph-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/graph-match/)
  - [二分图最大匹配](graph/graph-matching/bigraph-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/bigraph-match/)
  - [二分图最大权匹配](graph/graph-matching/bigraph-weight-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/)
  - [一般图最大匹配](graph/graph-matching/general-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/general-match/)
  - [一般图最大权匹配](graph/graph-matching/general-weight-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/general-weight-match/)
  - [稳定匹配](graph/graph-matching/stable-match.md) · [在线](https://oi-wiki.org/graph/graph-matching/stable-match/)
- [Prüfer 序列](graph/prufer.md) · [在线](https://oi-wiki.org/graph/prufer/)
- [矩阵树定理](graph/matrix-tree.md) · [在线](https://oi-wiki.org/graph/matrix-tree/)
- [LGV 引理](graph/lgv.md) · [在线](https://oi-wiki.org/graph/lgv/)
- [最大团搜索算法](graph/max-clique.md) · [在线](https://oi-wiki.org/graph/max-clique/)
- [支配树](graph/dominator-tree.md) · [在线](https://oi-wiki.org/graph/dominator-tree/)
- [图上随机游走](graph/graph-random-walk.md) · [在线](https://oi-wiki.org/graph/graph-random-walk/)

### 计算几何

- [计算几何部分简介](geometry/index.md) · [在线](https://oi-wiki.org/geometry/)
- [二维计算几何基础](geometry/2d.md) · [在线](https://oi-wiki.org/geometry/2d/)
- [三维计算几何基础](geometry/3d.md) · [在线](https://oi-wiki.org/geometry/3d/)
- [距离](geometry/distance.md) · [在线](https://oi-wiki.org/geometry/distance/)
- [Pick 定理](geometry/pick.md) · [在线](https://oi-wiki.org/geometry/pick/)
- [三角剖分](geometry/triangulation.md) · [在线](https://oi-wiki.org/geometry/triangulation/)
- [凸包](geometry/convex-hull.md) · [在线](https://oi-wiki.org/geometry/convex-hull/)
- [扫描线](geometry/scanning.md) · [在线](https://oi-wiki.org/geometry/scanning/)
- [旋转卡壳](geometry/rotating-calipers.md) · [在线](https://oi-wiki.org/geometry/rotating-calipers/)
- [半平面交](geometry/half-plane.md) · [在线](https://oi-wiki.org/geometry/half-plane/)
- [平面最近点对](geometry/nearest-points.md) · [在线](https://oi-wiki.org/geometry/nearest-points/)
- [随机增量法](geometry/random-incremental.md) · [在线](https://oi-wiki.org/geometry/random-incremental/)
- [最小圆覆盖](geometry/smallest-enclosing-circle.md) · [在线](https://oi-wiki.org/geometry/smallest-enclosing-circle/)
- [反演变换](geometry/inverse.md) · [在线](https://oi-wiki.org/geometry/inverse/)

### 杂项

- [杂项简介](misc/index.md) · [在线](https://oi-wiki.org/misc/)
- [离散化](misc/discrete.md) · [在线](https://oi-wiki.org/misc/discrete/)
- [双指针](misc/two-pointer.md) · [在线](https://oi-wiki.org/misc/two-pointer/)
- **离线算法**
  - [离线算法简介](misc/offline.md) · [在线](https://oi-wiki.org/misc/offline/)
  - [CDQ 分治](misc/cdq-divide.md) · [在线](https://oi-wiki.org/misc/cdq-divide/)
  - [整体二分](misc/parallel-binsearch.md) · [在线](https://oi-wiki.org/misc/parallel-binsearch/)
  - **莫队算法**
    - [莫队算法简介](misc/mo-algo-intro.md) · [在线](https://oi-wiki.org/misc/mo-algo-intro/)
    - [普通莫队算法](misc/mo-algo.md) · [在线](https://oi-wiki.org/misc/mo-algo/)
    - [带修改莫队](misc/modifiable-mo-algo.md) · [在线](https://oi-wiki.org/misc/modifiable-mo-algo/)
    - [树上莫队](misc/mo-algo-on-tree.md) · [在线](https://oi-wiki.org/misc/mo-algo-on-tree/)
    - [回滚莫队](misc/rollback-mo-algo.md) · [在线](https://oi-wiki.org/misc/rollback-mo-algo/)
    - [二维莫队](misc/mo-algo-2dimen.md) · [在线](https://oi-wiki.org/misc/mo-algo-2dimen/)
    - [莫队二次离线](misc/mo-algo-secondary-offline.md) · [在线](https://oi-wiki.org/misc/mo-algo-secondary-offline/)
    - [莫队配合 bitset](misc/mo-algo-with-bitset.md) · [在线](https://oi-wiki.org/misc/mo-algo-with-bitset/)
- [分数规划](misc/frac-programming.md) · [在线](https://oi-wiki.org/misc/frac-programming/)
- **随机化**
  - [随机函数](misc/random.md) · [在线](https://oi-wiki.org/misc/random/)
  - [随机化技巧](misc/rand-technique.md) · [在线](https://oi-wiki.org/misc/rand-technique/)
  - [爬山算法](misc/hill-climbing.md) · [在线](https://oi-wiki.org/misc/hill-climbing/)
  - [模拟退火](misc/simulated-annealing.md) · [在线](https://oi-wiki.org/misc/simulated-annealing/)
- [悬线法](misc/hoverline.md) · [在线](https://oi-wiki.org/misc/hoverline/)
- [有限状态自动机](misc/fsm.md) · [在线](https://oi-wiki.org/misc/fsm/)
- [计算理论基础](misc/cc-basic.md) · [在线](https://oi-wiki.org/misc/cc-basic/)
- [字节顺序](misc/endianness.md) · [在线](https://oi-wiki.org/misc/endianness/)
- [约瑟夫问题](misc/josephus.md) · [在线](https://oi-wiki.org/misc/josephus/)
- [表达式求值](misc/expression.md) · [在线](https://oi-wiki.org/misc/expression/)
- [在一台机器上规划任务](misc/job-order.md) · [在线](https://oi-wiki.org/misc/job-order/)
- [主元素问题](misc/main-element.md) · [在线](https://oi-wiki.org/misc/main-element/)
- [Garsia–Wachs 算法](misc/garsia-wachs.md) · [在线](https://oi-wiki.org/misc/garsia-wachs/)
- [15-puzzle](misc/15-puzzle.md) · [在线](https://oi-wiki.org/misc/15-puzzle/)
- [Kahan 求和](misc/kahan-summation.md) · [在线](https://oi-wiki.org/misc/kahan-summation/)
- [珂朵莉树/颜色段均摊](misc/odt.md) · [在线](https://oi-wiki.org/misc/odt/)
- [空间优化简介](misc/space-optimization.md) · [在线](https://oi-wiki.org/misc/space-optimization/)

### 专题

- [RMQ](topic/rmq.md) · [在线](https://oi-wiki.org/topic/rmq/)
- [并查集应用](topic/dsu-app.md) · [在线](https://oi-wiki.org/topic/dsu-app/)
- [括号序列](topic/bracket.md) · [在线](https://oi-wiki.org/topic/bracket/)
- [线段树与离线询问](topic/segment-tree-offline.md) · [在线](https://oi-wiki.org/topic/segment-tree-offline/)

## nav 之外的页面

以下页面存在于 oi-wiki.org 的 sitemap，但**不在** `mkdocs.yml` 的 `nav` 中（多为站点功能页/部署文档）：

- [edit-landing](edit-landing.md) · [在线](https://oi-wiki.org/edit-landing/)（站点「编辑本页」跳转页）
- [intro/docker-deploy](intro/docker-deploy.md) · [在线](https://oi-wiki.org/intro/docker-deploy/)（用 Docker 部署 OI Wiki 的说明）

除这两页外，本地其余 463 个 `.md` 文件均能在 `nav` 或 sitemap 中找到对应条目，没有多余文件。

## 缺失清单

**无缺失。** 465 条 sitemap URL 已逐条对账，全部命中本地文件；上一轮快照中缺的 `graph/lca.md`、`graph/planar.md`、`math/numeral-sys/gray-code.md`、`math/berlekamp-massey.md` 以及 `graph/graph-matching/graph-match.md` 均已补齐。对账明细见 [`_manifest/integrity-report.md`](_manifest/integrity-report.md)。

> 说明：本 README 中的索引条目以官方 `mkdocs.yml`（`master` 分支）为准；若上游 `nav` 后续调整，索引结构需同步更新。
