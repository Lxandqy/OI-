# CSP-J 全部比赛题解验收与局部重构报告

日期：2026-10-24。执行规范：oi-contest-authoring V3.10.9。

## 处理结果

**7 套、28 题均先验收。第一套 4 题通过，保留整套全部原文件字节；其余 6 套 24 题修订后通过本轮题解文稿与正确性回归验收。原目录及四个完整 ZIP 已同步。**

本次是既有题解维护；保持原来源方式、原难度和比赛参数，不重新命题或调整评分。题面、28 份 std、全部正式数据和下发文件的 SHA-256 均与开工盘点一致，CSP-J 未生成 config。四个 ZIP 保留原来的文件名（仍含 V3.8），其中题解和教师说明已经按 V3.10.9 更新。

| 比赛 | 原稿处理 | 本轮结果 | 正式点 | 下发样例 | 题面样例 | 部分分源码／保证点运行 | PDF 页数 |
|---|---|---|---:|---:|---:|---:|---:|
| CSP-J模拟赛第一套-题解重构版 | 4 题原稿保留 | PASS（本次范围） | 80 | 8 | 8 | 12／63 | 10 |
| CSP-J金桂第一试 | 4 题未过后修订 | PASS（本次范围） | 80 | 4 | 4 | 6／37 | 8 |
| CSP-J秋日训练卷 | 4 题未过后修订 | PASS（本次范围） | 80 | 12 | 8 | 8／56 | 8 |
| 第四套_V3.8_完整重构包.zip | 4 题未过后修订 | PASS（本次范围） | 60 | 8 | 8 | 5／13 | 8 |
| 第五套_V3.8_完整重构包.zip | 4 题未过后修订 | PASS（本次范围） | 50 | 8 | 7 | 5／17 | 9 |
| 第六套_V3.8_完整重构包.zip | 4 题未过后修订 | PASS（本次范围） | 40 | 8 | 8 | 3／14 | 9 |
| 第七套_V3.8_完整重构包.zip | 4 题未过后修订 | PASS（本次范围） | 40 | 8 | 7 | 4／13 | 8 |

PASS 仅指本轮题解质量、代码对应、正确性回归与文件同步，不代替赛事完整交付和时限定标结论。

## 具体修订

- 满分主线直接从题意推导所需观察与算法；删除无必要的慢解铺垫、重复证明和总结，不删关键理由。
- 每题正文只保留与原 std 一致的满分完整代码；有公开分档的题目均在末尾表格说明条件、分值、做法、复杂度与保证覆盖。
- 保留第一套原有 12 份部分分源码；其余六套新增独立交付 31 份，共 43 份，GBK 无 BOM，按最终交付字节编译和验证。
- 删除旧稿的默认 DP 配图，必要的状态语义、转移原因、初始化和求值顺序并入正文。
- 修正实际实现成本，包括保存字符串的空间、字符串比较、竖式高精度与逐位解析、并查集的保守时间上界。
- 教师说明标记历史记录与本轮记录；保留“远行”的合法二次计数实现曾实测 100 分等原始事实，不重写成预设得分。

## 逐题结论

| 比赛 | 题目 | 原稿验收 | 最终文稿 | 证据 |
|---|---|---|---|---|
| CSP-J模拟赛第一套-题解重构版 | T1 观星（star） | PASS，保留 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s1/star.md) |
| CSP-J模拟赛第一套-题解重构版 | T2 史莱姆（slime） | PASS，保留 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s1/slime.md) |
| CSP-J模拟赛第一套-题解重构版 | T3 旋律（melody） | PASS，保留 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s1/melody.md) |
| CSP-J模拟赛第一套-题解重构版 | T4 合唱（chorus） | PASS，保留 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s1/chorus.md) |
| CSP-J金桂第一试 | T1 纪念品分组（souvenir） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s2/souvenir.md) |
| CSP-J金桂第一试 | T2 安全密码（password） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s2/password.md) |
| CSP-J金桂第一试 | T3 数组升格（growmax） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s2/growmax.md) |
| CSP-J金桂第一试 | T4 广阔图（widegraph） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s2/widegraph.md) |
| CSP-J秋日训练卷 | T1 配对（pairs） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s3/pairs.md) |
| CSP-J秋日训练卷 | T2 通行（rail） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s3/rail.md) |
| CSP-J秋日训练卷 | T3 远行（visit） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s3/visit.md) |
| CSP-J秋日训练卷 | T4 丰收（harvest） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s3/harvest.md) |
| 第四套_V3.8_完整重构包.zip | T1 接龙（chain） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s4/chain.md) |
| 第四套_V3.8_完整重构包.zip | T2 平方和（sumsq） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s4/sumsq.md) |
| 第四套_V3.8_完整重构包.zip | T3 彩彩的三彩项链（necklace） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s4/necklace.md) |
| 第四套_V3.8_完整重构包.zip | T4 表达式（eval） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s4/eval.md) |
| 第五套_V3.8_完整重构包.zip | T1 上下五千年（date） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s5/date.md) |
| 第五套_V3.8_完整重构包.zip | T2 采购（purchase） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s5/purchase.md) |
| 第五套_V3.8_完整重构包.zip | T3 整除序列（divisible） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s5/divisible.md) |
| 第五套_V3.8_完整重构包.zip | T4 绿野仙踪（green） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s5/green.md) |
| 第六套_V3.8_完整重构包.zip | T1 最多求余（maxmod） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s6/maxmod.md) |
| 第六套_V3.8_完整重构包.zip | T2 各乘一个（crossmul） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s6/crossmul.md) |
| 第六套_V3.8_完整重构包.zip | T3 三元组（triples） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s6/triples.md) |
| 第六套_V3.8_完整重构包.zip | T4 切割（splitnum） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s6/splitnum.md) |
| 第七套_V3.8_完整重构包.zip | T1 回文串（palindrome） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s7/palindrome.md) |
| 第七套_V3.8_完整重构包.zip | T2 交错四元组（quad） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s7/quad.md) |
| 第七套_V3.8_完整重构包.zip | T3 文件判定（files） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s7/files.md) |
| 第七套_V3.8_完整重构包.zip | T4 树与叶子（leafcut） | NEEDS_FIX，已修订 | PASS | [逐项量表与三次检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews/s7/leafcut.md) |

每题均有 A—G 逐项证据、硬门槛结果及三次短检查（遮结果复述、核心实现对照、直接性与删除测试）。当前作者复审记录均为适用项 14/14、H 无图 N/A；没有独立人员试读或学生试讲，分数不代表学生理解率。

## 本轮实测与文件核验

- 28 份 std 独立编译通过；正式测试点 **430/430 AC**。
- 题面内联样例 **50/50**、下发样例 **56/56** 均由原 std 复现。
- 43 份部分分源码独立编译通过，声明保证点的 **213/213 次运行**全部 AC；这里是程序—测试点运行次数，不能误写成 213 个互不相同的测试点。
- 官方题面、题解与独立源码机械检查 7/7 套通过；28/28 题的公开—隐藏输入隔离检查通过。
- 7 份题解 PDF 共 **60 页**完成逐页版式复核；六份修订 PDF 已同步，第一套 PDF 原字节保留。
- 最终目录和 ZIP 内的每个成员均与已验收工作副本逐个计算 hash 比对。四个 ZIP 通过 CRC、实际完整解压、成员唯一性与安全路径检查；没有删除原成员。
- 替换前再次核对原目录与 ZIP 的初始 hash，未发现并发改动。允许变动只限六套的题解 Markdown/PDF、教师说明和新增部分分源码。

运行口径：Windows 本机，g++ C++14 `-O2 -Wl,--stack=536870912`；部分分另加 `-finput-charset=GBK`。正确性运行单次超时 15 秒；本轮 std 单次最长观测约 0.263 秒，该数字含进程启动且只用于记录本次运行，不据此重新决定原题时限。编译器、源码、可执行文件及输入答案 hash 保存在 compilation.json 与 execution.json。

## 交付与备份

- 比赛目录：[CSP-J](C:/Users/Administrator/Desktop/OI-/比赛题目/CSP-J)。
- 完整原始备份：[before](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/before)，保留开工前的三个目录和四个 ZIP。
- 核验记录与脚本：[cspj-editorials-v3109](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109)。
- 六份修订题解的便于阅读副本：[pdf](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/output/pdf)，字节与正式题包对应 PDF 相同。

| 已更新 ZIP | SHA-256 |
|---|---|
| 第四套_V3.8_完整重构包.zip | `4d7c2fde23f4340df113e91891de5e77292b8c35e8f57c8127febd4d12874175` |
| 第五套_V3.8_完整重构包.zip | `b5f72fff68fc0a6f76116c1e7ce19edf8c9ca48a221f0f68bbac8d3fe637f159` |
| 第六套_V3.8_完整重构包.zip | `81791b23844bcf75fc0c384fd661ab2d38ac7ed38fecd0beec24c35d0a3112b2` |
| 第七套_V3.8_完整重构包.zip | `351eb0a77b54c6ea9809e27eed1ada90753a208c972e68682868989d084ceb3e` |

内部主要证据：

- [原稿逐题初审](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/audit-before.json)。
- [28 题量表总表（每题详情见 reviews）](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/reviews.json)。
- [官方机械检查](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/official-checks.json)。
- [本轮运行统计](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/run-summary.json)。
- [编译与源码/可执行文件 hash](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/compilation.json)。
- [逐程序、逐点运行和输入答案 hash](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/execution.json)。
- [公开隐藏隔离](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/isolation-checks.json)。
- [PDF 页数、版本及逐页审核记录](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/pdf-review.json)。
- [最终同步位置与完整成员 hash](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/published.json)。
- [原稿至最终稿的允许变更列表](C:/Users/Administrator/Desktop/OI-/2026-10-24/cspj-editorials-v3109/stage-final-manifests.json)。

## 沿用的风险与未完成项

- 第四至第七套原包来源仍待确认；本轮没有重新查重或查询评级。第一套教师材料中 T4 与 VNOJ kkdd 核心相近的原风险保留。
- 未在目标评测环境重跑逐点按原时限、内存和反退化的完整压力矩阵。历史测分作为历史记录保留，本轮正确性回归不冒充该矩阵。
- 难度待校准：没有学生样本试做或试讲，本轮只验收文稿及程序对应。
