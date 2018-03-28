以下是本周的题目和题解
# 3Sum Closest
## Description
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

>    For example, given array S = {-1 2 1 -4}, and target = 1.
>
>    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
## Solution
本题与3 Sum有相似之处，但3 Sum要求给出精确解，而本题要求给出最近似target的解。基本思路也是相似的，利用排序后的数组进行扫描，
设置头尾指针以节省某些不必要的组合。具体步骤如下：

1. 对数组进行排序
2. 从数组中选定一个数fix，fix = a[i]，i:0~n-1。对每一个fix，设置两个指针left、right，初始化left = i+1, right = n-1
3. 计算fix与left、right指向的数之和，若它与target的距离比之前保持的最小距离currentDist要小，则更新currentDist以及当前和currentSum
4. 若fix与left、right指向的数之和比target小，则left++，若比较大则right--，若相等则直接结束。重复过程3、4直至left == right

算法的时间复杂度大约是O（n2），代码如下：

    class Solution {
    public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());

        int currentSum;
        int currentDist = 99999;
        for (int i = 0; i < nums.size(); i++) {
        	int fix = nums[i];
        	int left = i+1, right = nums.size()-1;

        	while (left < right) {
        		int tempSum = fix + nums[left] + nums[right];

        		int dist = tempSum - target;
        		if (dist < 0) dist = -dist;
        		if (dist < currentDist) {
        			currentDist = dist;
        			currentSum = tempSum;
        		}

        		if (tempSum == target) return target;
        		if (tempSum < target) left++;
        		if (tempSum > target) right--;
        	}
        }
        return currentSum;
    }
    };
    
# Reverse Integer
## Description
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output:  321

Example 2:

Input: -123
Output: -321

Example 3:

Input: 120
Output: 21

Note:
Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows. 
## Solution
对一个整数进行逆序输出，需要注意的地方有3点：符号、消除数字前面的0、溢出。分别进行以下处理：
1. 保存原始数字x的符号，然后把原始数字x转换为正数。
2. 为了消除逆序数字前面的0，需要将原始数字从低到高位第一个非0位之前的所有0全部忽略掉。如果x是0，则直接返回0，否则不能进入循环。
3. 对于溢出，需要提前判断，即当当前逆序数字大于INT_MAX / 10，或者乘以10再加完下一个位以后大于INT_MAX的话（当然不能直接这样比较，因为大于INT_MAX就已经溢出了，可以在不等式两边调整），返回0。

整个过程需要1次遍历，时间复杂度为O（n）。虽然还有一种方法，即用声明结果类型为long，就可以不用担心计算时溢出，只需要在最后判断有没有大于INT_MAX即可，但还是上述方法比较利用原理。代码如下：

    class Solution {
    public:
    int reverse(int x) {
    	if (x == 0) return 0;

        bool notZero = false;
        int sign = 1;
        if (x < 0) {
        	sign = -1;
        	x = -x;
        }
        int result = 0;

        while (x != 0) {
        	int bit = x % 10;
        	x = x / 10;

        	if (bit == 0 && !notZero) continue;
        	notZero = true;

        	if (result > INT_MAX / 10 || result * 10 > INT_MAX - bit) {
        		return 0;
        	} else {
        		result = result * 10 + bit;
        	}
        }
        return sign * result;
    }
    };
