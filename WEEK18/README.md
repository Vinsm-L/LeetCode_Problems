以下为本周的题目和题解
# Pow(x, n)
## Description
Implement pow(x, n).

> Example 1:
>
> Input: 2.00000, 10
> Output: 1024.00000

> Example 2:
>
> Input: 2.10000, 3
> Output: 9.26100
## Solution
计算一个数x的n次方，利用分治的思想，可以不用将x连乘n次，而是首先将x的n次方分成两个x的n/2次方相乘，然后x的n/2次方又分成两个x的n/4相乘……一直到分成x的0次方为止。如果n是负数，那么将x转换成1/x即可。

这样就可以将时间复杂度降低到O(log n)。代码如下：

    class Solution {
    public:
    double fastPow(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double half = fastPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        return fastPow(x, N);
    }
    };
