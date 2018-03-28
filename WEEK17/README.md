# Exercise 8.8
## Description
In the Exact 4SAT problem, the input is a set of clauses, each of which is a disjunction of exactly 4 literals, and such that each varibles occurs at most once in each clause. 

The goal is to find a satisfying assignment, if one exists. Prove that Exact 4SAT is NP-complete.
## Proof
给定一个4SAT问题，即问题包含多个子句，每个子句包含4个文字的析取，要求找到一个使所有子句同时满足的赋值。证明该问题是NP完全的问题。

如果一个NP完全问题能规约到该问题，那么该问题也是一个NP完全的问题。首先进行构造，完成从SAT到4SAT的实例的映射。

给定SAT的一个实例I，对于I中的一个子句(a1 V a2 V ... V ak)，其中ai为文字，k > 4，采用如下子句进行替代：

(a1 V a2 V a3 V y1)(-y1 V a4 V a5 V y2)...(y(k/2 -1) V a(k-2) V a(k-1) V ak)，其中yi是一些新增的变量。

把这样的4SAT实例记为I'，从I到I'的构造是多项式时间内可以完成的。

现在证明该规约是有效的，即I与I'在可满足性上是等价的。假设I'的实例中所有子句都满足，则a1, ..., ak中至少有一个为真，否则y1必须为真，并进而使得y2必须为真，如此类推，最终导致最后一个子句不满足。因此I子句也是满足的。

反之，若I的子句为真，则必存在一个ai为真，此时可令y1, ... ,y(i-2)为真，其余为假，使得I'的子句也满足。

因此，该规约是有效的，即I与I'在可满足性上是等价的。所以4SAT是一个NP完全的问题。
