以下是题目与题解。
# Longest Substring Without Repeating Characters 
## Description
Given a string, find the length of the longest substring without repeating characters.

> Examples:
>
> Given "abcabcbb", the answer is "abc", which the length is 3.
>
> Given "bbbbb", the answer is "b", with the length of 1.
>
> Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

## Solution
要找到一个无重复字符的最长子串，最简单的方法就是遍历，而其中最暴力的就是复杂度为O（n2）的双重循环，然而这其中做了许多重复的工作。
例如，一个i~j的子串是无重复的，但第j+1位重复了，这时如果从第i+1位开始向后依次遍历，就重复检索了j-i+1位，这些工作可以被节省下来。

改进后的解法为，当遇到一个重复的位j+1时，将起始位i后移1位，即从i+1位开始，判断第j+1位的字符是否出现在前i+1~j+1位中。

这里我用C++实现，使用了STL的set容器，当遇到重复的位j+1时，将第i位的字符从set中erase，再重复判断。记录最大长度的变量需要在每次循环中更新。代码如下：

    class Solution {
    public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        int i = 0, j = 0, max = 0;
        set<char> charSet;
        while (i < len && j < len) {
        	if (charSet.find(s[j]) == charSet.end()) {
        		charSet.insert(s[j]);
        		j++;
        		max = (j - i) > max ? j - i : max;
        	} else {
        		charSet.erase(s[i]);
        		i++;
        	}
        }
        return max;
    }
    };

其实如果知道是第x个位与第j+1个位发生了重复的话，就可以直接从x+1位开始判断了，这时可以让下标与字符形成映射，通过字符找到它对应的下标。JAVA的map容器封装了这类函数。

    public class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length(), ans = 0;
        Map<Character, Integer> map = new HashMap<>();
       
        for (int j = 0, i = 0; j < n; j++) {
            if (map.containsKey(s.charAt(j))) {
                i = Math.max(map.get(s.charAt(j)), i);
            }
            ans = Math.max(ans, j - i + 1);
            map.put(s.charAt(j), j + 1);
        }
        return ans;
    }
    }

# Median of Two Sorted Arrays 
## Description
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

> Example 1:
>
> nums1 = [1, 3]
> nums2 = [2]
>
> The median is 2.0

> Example 2:
>
> nums1 = [1, 2]
> nums2 = [3, 4]
>
> The median is (2 + 3)/2 = 2.5

https://leetcode.com/problems/median-of-two-sorted-arrays/description/

## Solution
其实找两个数组合起来的中位数，并不需要排序，因为不需要知道除中位数以外的其他数之间的大小关系。但既然给定的两个数组都是有序的，我第一时间还是想到用类似
归并排序的方法。

解法的思想就是，将两个数组看作队列，不断地比较队首，比较小的就出队。当出队数量等于总数的一半时，就找到了中位数。这样，时间复杂度是线性的。

需要注意的有几个地方：
1. 中位数的计算是分奇偶的
2. 一边队列可能会先于另一边停止，这时要注意不能越界

代码如下：

    class Solution {
    public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();

        bool isEven = false;             //  the size is even or odd number
        int pos = (size1 + size2) / 2;   //  the position of the median
        if ((size1 + size2) % 2 == 0) {
        	isEven = true;
        	pos--;
        }

        int i = 0, j = 0;               //  index
        double result = 0;

        while (i + j != pos) {
        	if (i == size1) {           //  when nums1 reaches end, stop traversing it
        		j++;
        		continue;
        	}

        	if (j == size2) {           //  same as above
        		i++;
        		continue;
        	}

        	if (nums1[i] < nums2[j]) {  //  sort
        		i++;
        	} else {
        		j++;
        	}
        }

        if (isEven) {

        	//  when one side stops, identify it and pick number from the other side
        	if (i == size1) {
        		result = (double)nums2[j] + (double)nums2[j+1];
        		return result / 2;
        	}
        	if (j == size2) {
        		result = (double)nums1[i] + (double)nums1[i+1];
        		return result / 2;
        	}

        	if (nums1[i] < nums2[j]) {
        		result = (double)nums1[i];
        		i++;
        	} else {
        		result = (double)nums2[j];
        		j++;
        	}

        	//  judge again
        	if (i == size1) {
        		result += (double)nums2[j];
        		return result / 2;
        	}
        	if (j == size2) {
        		result += (double)nums1[i];
        		return result / 2;
        	}

        	if (nums1[i] < nums2[j]) {
        		result += (double)nums1[i];
        		result = result / 2;
        		i++;
        	} else {
        		result += (double)nums2[j];
        		result = result / 2;
        		j++;
        	}
        } else {
        	if (i == size1) {
        		return (double)nums2[j];
        	}
        	if (j == size2) {
        		return (double)nums1[i];
        	}

        	if (nums1[i] < nums2[j]) {
        		result = (double)nums1[i];
        	} else {
        		result = (double)nums2[j];
        	}
        }

        return result;
    }
    };
    
如前所说，既然不需要排序，那么用分治的方法应该会更出色。求中位数是求第K大数的一个特例，用分治法求第K大数，需要如下几步：
1. 从数组中随机选择一个数n
2. 将数组分成比n小、等于n、比n大的三部分，观察K落在哪个部分。如果前两部分数组的大小之和小于K，则K落在第三部分，如此类推
3. 对K落在的部分继续1、2步，直到找出所求的数

那么求中位数，就是相当于求第（m+n）/2大的数（假设为个数为奇数），关键在于数字n的选择。既然题设中两个数组nums1与nums2都是有序的，可以不断地对其中一个数组取中位数，这样很容易将这个数组分为两半，而只需与另一个数组进行比较。
