以下是本周的题目和题解
# 4Sum
## Description
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets. 

> For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
>
> A solution set is:
> [
>  [-1,  0, 0, 1],
>  [-2, -1, 1, 2],
>  [-2,  0, 0, 2]
> ]

## Solution
前面已经打过3 Sum，3 Sum Closest这样的题目，因此要求求出四个数字之和等于给定目标的无重复结果，思路跟3 Sum是差不多的。

也就是说，对数组中的每个元素，把它固定下来，然后对它后面的元素计算3 Sum。其中还要考虑一些消除重复的问题。计算3 Sum的时间复杂度是O（n2），那么计算4 Sum
则是O（n3）。

如果要求计算5 Sum、6 Sum……等等呢？经过3 Sum、4 Sum的递进和思考，应该可以抽象出一个能够重用的函数来，用于计算任意x Sum（x > 3）。

算法的思想是递推，不断把问题的规模缩小，当缩小到求3 Sum时可以求出解。示意图如下：

![image](https://github.com/Vinsm-L/LeetCode_Problems/blob/master/WEEK13/%E7%A4%BA%E6%84%8F%E5%9B%BE.PNG)

箭头旁边是传递给下层的参数。在到达层次3（计算3 Sum）之前的每一个层次中，从起始元素开始，固定每一个元素（将它放入fix中），并将它的下标加一，index+1，
作为下一个层次的起始元素下标。最后，在更新完要达到的目标值，即currentTarget以后，函数落到下一个层次。

当函数到达层次3时，计算3 Sum。为了消除重复结果，每个层次在选择元素进行固定时，需要跳过已固定的相邻的重复元素。另外，为了保证fix数组中的值被更新，从下层返回到上层时需要把上层的值pop出去。

如此一来，就完成了一个可重用的x Sum函数。代码及注释如下：

    /*
    ** a solution to four-sum problem
    ** the xSum function can be reused to calculate the sum of any number, which is greater than 3, of array elements.
    */
    class Solution {
    public:
        vector<vector<int>> result;

        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            if (nums.size() < 4) return result;

            std::sort(nums.begin(), nums.end());  // the array has to be sorted

            vector<int> fix;
            xSum(nums, target, fix, 0, 4);

            return result;
        }

        /*
        ** nums: the sorted array
        ** currentTarget: the current target for the sum to achieve
        ** fix: store the elements chosen before the function reaches 3Sum level
        ** startIndex: indicate which index the current level should start at
        ** x: indicate which level the function arrives at currently
        */
        void xSum(vector<int>& nums, int currentTarget, vector<int>& fix, int startIndex, int x) {
    	    // for every element starting from startIndex
    	    // choose the element and fix it, then refresh the target, come to a lower level, and start from next index
    	    if (x > 3) {
    		      for (int i = startIndex; i < nums.size(); i++) {
    			        fix.push_back(nums[i]);
    			        xSum(nums, currentTarget-nums[i], fix, i+1, x-1);
    			        fix.pop_back();

    			        // skip the repeated neighboring elements, to avoid duplicate x sum results
    			        while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
                	            i++;
                }
            } else {
    		        // when it arrives at level 3, calculate 3 sum
    		        if (nums.size() - startIndex < 3) return;

	    	        for (int i = startIndex; i < nums.size(); i++) {
	    		        int n = nums[i];
	    		        int left = i+1;  // left pointer
	    		        int right = nums.size()-1;  // right pointer

	    		        while (left < right) {
	    			        int sum = n + nums[left] + nums[right];

	    			        // adjust the pointer according to the sum and target
	    			        if (sum < currentTarget) {
	    				        left++;
	    			        } else if (sum > currentTarget) {
	    				        right--;
	    			        } else {
	    				        vector<int> temp = fix;
	    				        temp.push_back(n);
	    				        temp.push_back(nums[left]);
	    				        temp.push_back(nums[right]);
	    				        result.push_back(temp);
	    				        int numLeft = nums[left];
	    				        int numRight = nums[right];

	    				        // to avoid duplicate 3 sum results
	    				        while (left < right && nums[left] == numLeft) left++;

	    				        while (left < right && nums[right] == numRight) right--;
	    			        }
	    		        }

	    		        // skip the repeated neighboring elements, to avoid duplicate 3 sum results
	    		        while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
	                            i++;
	    	        }
    	            }
                }
            };
        
这样的思路跟分治比较接近，划分子问题，缩小问题规模，递归调用函数解决问题。

# Valid Parentheses
## Description
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
## Solution
这是利用栈这种数据结构后进先出特性的经典题目。左括号压入栈，右括号与栈顶的左括号匹配。
因为各种括号的匹配规则是就近原则，所以如果一个右括号找不到一个最近的左括号与之匹配，则不合法。另外，
如果匹配结束后，栈中还有未弹出的左括号，则不合法。算法可以在线性时间内解答，代码如下：

    class Solution {
    public:
    bool isValid(string s) {
        if (s == "") return true;

        stack<char> check;

        for (int i = 0; i < s.length(); i++) {
        	if (s[i] == '(' || s[i] == '{' || s[i] == '[') 
        		check.push(s[i]);
        	else if (s[i] == ')' && check.size() > 0 && check.top() == '(')
        		check.pop();
        	else if (s[i] == ']' && check.size() > 0 && check.top() == '[')
        		check.pop();
        	else if (s[i] == '}' && check.size() > 0 && check.top() == '{')
        		check.pop();
        	else 
        		return false;
        }

        if (check.size() > 0) return false;
        return true;
    }
    };
    
