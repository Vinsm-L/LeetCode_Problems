以下是本周的题目和题解
# String to Integer (atoi)
## Description
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front. 
## Solution
题目没有给出详细的输入格式，也没有给出处理的要求，所以需要从出错反馈中不断去理解和总结。我总结了以下4点要求：
1. 以第一个非空格字符为起点，前面的字符都过滤掉。
2. 若第一个非空格字符不是+或-或数字，直接返回0。+、-指示整数的符号，都没有的时候为正数。
3. 从起点往后遍历，遇到不属于数字的字符时直接结束遍历。
4. 字符串的遍历是从左到右的，转换成整数是从高位到低位的。转换的过程需要判断溢出。

需要注意的地方是溢出和转换过程中高位到低位的顺序。整个过程只需要一趟遍历，时间复杂度为O（n）。代码如下：

    class Solution {
    public:
    int myAtoi(string str) {
        int sign = 1;
        int sum = 0;
        bool start = false;
        for (int i = 0; i < str.length(); i++) {
        	if (str[i] != ' ' && !start) {
        		start = true;
        		if (str[i] == '-') sign = -1;
        		if (str[i] == '-' || str[i] == '+') continue;
        	}
        	
        	if (str[i] >= '0' && str[i] <= '9') {
        		if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && str[i] - '0' > 7)) {
        			if (sign == 1) {
        				return INT_MAX;
        			}
        			return INT_MIN;
        		}
        		sum = sum * 10 + str[i] - '0';
        	} else if (start) {
        		break;
        	}
        }
        return sum * sign;
    }
    };
    
    
# 3 Sum
## Description
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

> For example, given array S = [-1, 0, 1, 2, -1, -4],
>
> A solution set is:
> [
>  [-1, 0, 1],
>  [-1, -1, 2]
> ]

## Solution
求给定数组中3个数字之和为0的所有组合，要求去除重复，即结果是数字的组合而不是排列。

首先想到，把问题切分为更小的子问题。求3个数字之和，可以先求出两个数字之和。如果事先求出给定数组中每两个数字之和，存到一个新的二维数组里，然后对给定数组中的每一个元素，判断每一个不包含它自身的数对是否符合要求。

这种方法时间复杂度大致为O（n3），但实际没有那么高。但是超时了，而且也没有很好地解决去除重复结果的问题。

为了同时去除重复以及降低时间复杂度，采取另一种算法。先对给定数组按照升序排序，然后从头到尾进行遍历：
1. 取出当前元素作为target，设置front、back两个指针，分别指向target的后一个元素和数组最后一个元素。
2. 计算front、back指向的元素与target之和，若比0小则front++；若比0大则back--；若等于0则得到一个结果，把它记录下来，此时还要使front和back往中间移动，直至它们指向的元素出现变化为止。也就是说，借由跳过重复的数字，来去除重复的结果。
3. 重复2，直到front、back相遇为止。此时target向后移动，并重复1、2。

这种方法时间复杂度为O（n2），代码如下：

    class Solution {
    public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > res;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            
            int target = -nums[i];
            int front = i + 1;
            int back = nums.size() - 1;

            while (front < back) {

                int sum = nums[front] + nums[back];
                
                // Finding answer which start from number nums[i]
                if (sum < target)
                    front++;

                else if (sum > target)
                    back--;

                else {
                    vector<int> triplet(3, 0);
                    triplet[0] = nums[i];
                    triplet[1] = nums[front];
                    triplet[2] = nums[back];
                    res.push_back(triplet);
                    
                    // Processing duplicates of Number 2
                    // Rolling the front pointer to the next different number forwards
                    while (front < back && nums[front] == triplet[1]) front++;

                    // Processing duplicates of Number 3
                    // Rolling the back pointer to the next different number backwards
                    while (front < back && nums[back] == triplet[2]) back--;
                }
                
            }

            // Processing duplicates of Number 1
            while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
                i++;

        }
        
        return res;
    }
    };
