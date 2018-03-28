以下为本周的题目和题解
# Jump Game
## Description
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
> A = [2,3,1,1,4], return true.
>
> A = [3,2,1,0,4], return false. 
## Solution
题目中给出的数组的每个下标对应的数字表示从该位置开始，最多能走的步数。如果从位置0（下标0）开始能走到最后一个位置，那么返回true，否则返回false。

对于这种有一个根结点，由多个结点（情况、位置）组成、每个结点有多个分支（变化、选择）的题目，可以把它当成一棵树来看待。判断从根结点能否到达某个结点，
只需要对树进行遍历即可，一般来说3种顺序都可以。

但是在这里，一棵树的分支因子太大了，导致递归的效率极其低下。那么我们应该想办法优化递归（如用某种方法剪枝），或者不用递归。

考虑剪枝。对于一个结点，若从它能到达终点，那么它是好的结点（good），否则是坏的结点（bad）。如果不清楚从该结点能不能到达终点，则对它的评价为未知（unknown）。
可以用一个数组memo来记录某个对结点的评价。若一个结点的评价是bad，那么就不再去访问该结点了。这样我们就减少了很多递归时重复遍历的结点。

考虑不用递归。这时可以考虑动态规划，仍然用memo数组来记录对某个结点的评价。子问题是这样推导出来的：要知道起点是不是good，需要知道它能到达的点是不是good。
可以反向推导：知道了终点是good，那么终点的前一个结点是否为good，只要看它能否到达终点。那么更前面的结点是否为good，只要看它能到达的结点中有没有good结点。

所以从终点出发，向前判断每个结点是否为good，最终到达起点。这种动态规划的算法，时间复杂度为O（n2），比最初的递归遍历所有结点要优秀很多。代码如下：

    enum Index {
        GOOD, BAD, UNKNOWN
    }

    public class Solution {
        public boolean canJump(int[] nums) {
            Index[] memo = new Index[nums.length];
            for (int i = 0; i < memo.length; i++) {
                memo[i] = Index.UNKNOWN;
            }
            memo[memo.length - 1] = Index.GOOD;

            for (int i = nums.length - 2; i >= 0; i--) {
                int furthestJump = Math.min(i + nums[i], nums.length - 1);
                for (int j = i + 1; j <= furthestJump; j++) {
                    if (memo[j] == Index.GOOD) {
                        memo[i] = Index.GOOD;
                        break;
                    }
                }
            }

            return memo[0] == Index.GOOD;
        }
    }
