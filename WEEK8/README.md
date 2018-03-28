以下为本周的题目和题解。
# Next Permutation
## Description
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
> 1,2,3 → 1,3,2
>
> 3,2,1 → 1,2,3
>
> 1,1,5 → 1,5,1
## Solution
为了寻找比当前排列的字典序要大的下一排列，我们首先仔细观察排列的特征。使用分治的思想，设排列有n个数，固定前m个数（0 <= m <= n-2），调度后面n-m个数。以1、2、3的全排列为例，观察相邻两个排列之间的关系：
> 1 2 3
> 
> 1 3 2
>
> 2 1 3
>
> 2 3 1
>
> 3 1 2
> 
> 3 2 1

对于排列1 2 3，固定前面1个数，调度后2个数。发现2比3小，于是交换2、3。

对于排列2 3 1，固定前面1个数，调度后2个数，3的后面已没有比3大的数，所以m需要减1。固定前面0个数，调度后3个数，发现2比3小，于是选择2后面比2大的最小的那个数，即3，交换它们的位置，再对后面n-m个数从小到大排列。

由此，我们可以发现一些规律。固定前面m个数，调度后面n-m个数，当这轮调度得不到结果时，一定是因为调度开始的那一位数比它后面的数都要大。在这种情况下还有一个规律，即这轮调度后面n-m个数一定是从大到小降序排列。

根据这两个规律，我们可以在一趟遍历中检查出可以通过调度得到想要结果的那个m，即当第m个数并不是比它后面的数都大，就可以进行调度了。检查过程如下：
1. 从最后两位数开始。若第m个数比第m+1个数大，则m--。
2. 重复1一直到找到第m个数比第m+1个数小。此时第m个数后面的所有数都是按降序排列，因此只要从结尾开始找，找到第一个大于第m个数的数t，t就是大于第m个数的最小数。

至此检查结束。调度就是要将第m个数后面大于它的最小数与它交换位置，再对第m个数后面的数做升序排列。调度过程如下：
1. 将检查过程中找到的t与第m个数交换位置。
2. 因为t是第m个数后面大于第m个数的最小数，因此互换位置之后，后面的数仍然是降序排列。此时要将后面的数变成升序排列的话，只要设置两个指向头尾的指针，不断交换两个指针指向的值，直到指针相遇。

用该算法最多需要两趟遍历，因此时间复杂度为O（n），空间复杂度为O（1）。代码如下：

    class Solution {
    public:
    void nextPermutation(vector<int>& nums) {  
        int i = nums.size()-2, j = nums.size()-1;
        while (i >= 0 && nums[i] >= nums[i+1]) i--;
        if (i != -1) {
            while (nums[j] <= nums[i]) j--;
            nums[i] = nums[i] ^ nums[j];  //  exchange position
            nums[j] = nums[i] ^ nums[j];
            nums[i] = nums[i] ^ nums[j];
        }
        i++;
        for (j = nums.size() - 1; i < j; i++, j--) {
            nums[i] = nums[i] ^ nums[j];  //  exchange position
            nums[j] = nums[i] ^ nums[j];
            nums[i] = nums[i] ^ nums[j];
        }
    }
    };
    
我一开始的实现并不是用这种算法，而是一种时间复杂度为O（n2）的算法，因为我忽略了一个规律：当一个调度得不到结果时，这轮调度后面n-m个数一定是从大到小降序排列，导致每次检查都从第m个数开始向后遍历，这里花费了O（n2）。此外，忽略这个规律还导致我调度时使用了冒泡排序而不是首尾互换位置，这里又花费了O（n2）。代码如下：

    class Solution {
    public:
    void nextPermutation(vector<int>& nums) {
    	int size = nums.size();
        if (size <= 1) return;

        bool flag = false;
        for (int m = size - 2; m >= 0; m--) {
        	int index = m;
        	for (int i = m + 1; i < size; i++) {
        		if (nums[i] > nums[m]) {
        			if (index == m || nums[i] < nums[index]) {
        				index = i;
        			}
        		}
        	}

        	if (index != m) {
        		int temp = nums[m];
        		nums[m] = nums[index];
        		nums[index] = temp;
        		for (int i = m + 1; i < size; i++) {
        			for (int j = i + 1; j < size; j++) {
        				if (nums[j] < nums[i]) {
        					int temp = nums[i];
        					nums[i] = nums[j];
        					nums[j] = temp;
        				}
        			}
        		}
        		flag = true;
        		break;
        	}
        }

        if (flag) return;

        for (int i = 0; i < size; i++) {
        	for (int j = i + 1; j < size; j++) {
        		if (nums[j] < nums[i]) {
       				int temp = nums[i];
    				nums[i] = nums[j];
        			nums[j] = temp;
        		}
        	}
        }
    }
    };
    
# Longest Valid Parentheses
## Description
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
## Solution
以前也接触过括号匹配的题目，使用的是栈的数据结构，于是现在也很自然地想到用栈。但是这道题要求最长的合法序列的长度，故简单地往栈中压入字符再弹出进行匹配是行不通的。

判断合法序列很简单，当一个新的字符与栈顶字符组成一对（），则匹配成功，否则将新的字符压入栈。然而判断何时出现合法序列的分割，则需要斟酌。

观察一些匹配中断的例子，如（）（（（）），如果没有第3个字符(，那么最长的合法序列长度就是6，而现在最长合法序列长度为4。这是因为，该字符(阻挡在了两个合法序列的中间，导致左边最长为2，右边最长为4，于是全局最长为4。

我们还可以观察到，最长合法序列的最后一个元素的下标，减去该分割字符的下标，等于最长合法序列的长度。那么向栈中压入字符的下标，就可以利用这一规律了。有如下算法：
1. 初始化时向栈压入-1，作为第一个分割字符的下标。
2. 得到一个新的元素，如果它是），栈顶元素指向的字符是（，则匹配，弹出栈顶元素，用新元素的下标减去现在的栈顶元素，得到当前最长合法序列的长度。否则将新元素压入栈，作为当前的分割字符下标。

该算法利用了分割字符的存在，在一趟遍历中得出了最长合法序列的长度，时间复杂度为O（n）。代码如下：

    class Solution {
    public:
    int longestValidParentheses(string s) {
        int count = 0;
        int maxLen = 0;
        stack<int> myStack;
        myStack.push(-1);

        for (int i = 0; i < s.length(); i++) {
        	if (myStack.empty()) {
        		myStack.push(i);
        		continue;
        	}

        	int top = myStack.top();
        	if (top == -1) {
        		myStack.push(i);
        		continue;
        	}

        	if (s[i] == ')' && s[top] == '(') {
        		myStack.pop();
        		count = i - myStack.top();
        	} else {
        		myStack.push(i);
        	}

        	if (count > maxLen) maxLen = count;
        }

        return maxLen;
    }
    };


除此以外，还有一种无需借助栈的，空间复杂度为O（1）的算法，有如下步骤：
1. 初始化left、right两个计数变量为0
2. 从左到右开始遍历字符串，若遇到（，left加1；若遇到），right加1。当left等于right时，计算当前合法序列长度len = left + right，若len大于全局最长合法序列长度则进行更新
3. 当right大于left时，把left和right重置为0

该算法时间复杂度为O（n），空间复杂度为O（1），因此更为优秀。
