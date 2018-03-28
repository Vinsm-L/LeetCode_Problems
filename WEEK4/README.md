以下是第四周的题目和题解。
# Regular Expression Matching 
## Description
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:

bool isMatch(const char *s, const char *p)

Some examples:
> isMatch("aa","a") → false
> 
> isMatch("aa","aa") → true
> 
> isMatch("aaa","aa") → false
> 
> isMatch("aa", "a*") → true
> 
> isMatch("aa", ".*") → true
> 
> isMatch("ab", ".*") → true
> 
> isMatch("aab", "c*a*b") → true
## Solution
正则表达式的匹配，分解为小问题，就是表达式中一个个字符的匹配。这可以分为2种情况：
1. 模板字符为普通字符或'.'。此时可以简单地判断给定串中对应的字符是否与之匹配。
2. 模板字符带有'*'。这时需要考虑的问题有几个。

因此，比较的思路就可以分成两步，第一步判断给定串与模板的对应字符是否匹配，第二步看模板字符后是否带有'*'。

也就是说s[i]与p[j]的比较过程可以分解成一棵二叉树：是否带'*'？是否匹配？对应列出了4种处理方法：
1. 匹配且带'*'，比较s[i+1]与p[j]
2. 匹配且不带'*'，比较s[i+1]与p[j+1]
3. 不匹配且带'*'，比较s[i]与p[j+2]
4. 不匹配且不带'*'，退出

但实际上以上处理方法是有疏漏的，问题出在第1点。匹配且带'*'的时候，未必要继续用s[i+1]与p[j]比较，也就是说p[j]需要重复出现多少次是因情况而异的。这时就需要比较s[i]与p[j+2]，看看p[j]在当前的重复次数下是否满足后续字符串的匹配。

改正后实现起来，第1、3点合并在一个分支语句，第2、4点合并在另一个分支语句。

此外，还要考虑问题的边界，不然递归就没完没了了。在定义好的处理方法中，给定串先结束，仍可以继续比较，后续比较的过程均视为不匹配。给定串后结束则表达式匹配失败。同时结束则视为最后一组字符是匹配的。

代码如下：

    class Solution {
    public:
    bool isMatch(string s, string p) {
        return compare(0, 0, s, p);
    }

    bool compare(int i, int j, string s, string p) {
    	if (j == p.length()) {
    		return i == s.length();
    	}
    	bool match = false;
    	if (i < s.length() && (s[i] == p[j] || p[j] == '.')) {
    		match = true;
    	}

    	if (j+1 < p.length() && p[j+1] == '*') {
    		return ((match && compare(i+1, j, s, p)) || compare(i, j+2, s, p));
    	} else {
    		return match && compare(i+1, j+1, s, p);
    	}
    	
    }
    };
    
题目解析中出现了一种动态规划的方法，做法与上述递归类似。其实我认为上述解法也属于动态规划，它符合子问题重叠与存在边界的特点，而且只要每一次递归都是正确的（子问题最优），最后的结果就是正确的。

# Container With Most Water 
## Description
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2. 
## Solution
一个容器能装多少水取决于它的短板，在这道题中最大容积则与短板和底面积都有关。把计算公式列出来：

area = min(ai, aj) * (j - i)。其实就是计算较矮边与底边之积。

在参考答案的算法之前，我思考了很多方法，如固定j-i比较min(ai, aj)、尝试利用前面的比较结果等等，似乎都得不到明显的时间复杂度降低，也就是说我的方法都不能显著减少比较[ai, aj]数对的数量。而答案的算法则将时间复杂度降到了O（n）：

首先从数组的头尾开始，用left、right指针指向一头一尾，然后将指向矮边的指针往中间移动，每移动一次，比较新围成的面积与目前最大面积，直到两指针相遇。

因为决定面积的因素有底边和矮边，所以算法就从最大底边开始，不断寻找更大的矮边，同时进行面积的比较。下面是对其正确性的分析：

如果height[left]比height[right]小，即left指向矮边，则left+1，此时我们就忽略了height[left]与height[right-1], height[right-2]...的所有组合。因为height[left]是矮边，所以：
1. 若height[right-m]中有比height[left]大的，height[left]仍然是矮边，此时底边变小了，不可能得到更大的面积；
2. 若height[right-m]中有比height[left]小的，则height[right-m]是矮边，不仅底边变小了，矮边也比原来更小了，所以不可能得到更大的面积。

如果height[left]比height[right]大，同理。因此，算法的每一步操作不会漏掉比当前最大面积更大的[ai, aj]数对，是正确的。

代码如下：

    class Solution {
    public:
    int maxArea(vector<int>& height) {
        int i = 0;  //  left pointer
        int j = height.size() - 1;    //  right pointer
        int max = 0;   //   store the max area
        while (i < j) {
        	if (height[i] < height[j]) {
        		max = height[i] * (j-i) > max ? height[i] * (j-i) : max;
        		i++;    //  move the left pointer towards middle
        	} else {
        		max = height[j] * (j-i) > max ? height[j] * (j-i) : max;
        		j--;    //  move the right pointer towards middle
        	}
        }
        return max;
    }
    };
