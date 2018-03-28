以下为本周的题目与题解。
# Longest Common Prefix 
## Description
Write a function to find the longest common prefix string amongst an array of strings. 
## Solution
给出一组字符串，找出它们的最长共同前缀。最直观的做法就是将这些字符串的头对齐，然后逐位向后比较。这样做，时间复杂度为O（mn），m为共同前缀平均长度，n为字符串个数。

其实既然前缀是共同的，那么不用同时对所有字符串进行匹配也可以。如果将它们两两匹配，根据分治法，最后的时间复杂度可以降到O（mlogn）。步骤如下：

1. 两个一组进行匹配，找出两者的最长共同前缀所在位置pos
2. 比较得出当前最短的“最长共同前缀”
3. 将两个一组中的其中一个字符串放进新的容器
4. 重复123，只匹配到字符串结束或者到pos为止。当容器中只剩一个字符串时结束。

之所以要找出全局最短的“最长共同前缀”，是因为如果“最长共同前缀”再增加任何一个字符，它就与某些字符串不再匹配。也就是说，不断求解局部“最长共同前缀”，得到的全局最短的“最长共同前缀”就是全局的“最长共同前缀”。

在这个过程中，pos不断缩小，需要比较的字符串长度也随之降低；字符串个数不断除以2，最后只剩一个字符串和最短的“最长共同前缀”。代码如下：

    class Solution {
    public:
    string longestCommonPrefix(vector<string>& strs) {
    	if (strs.size() == 0) return "";

        vector<string> match = strs;  //  store the strings to match for each turn
        int pos = 100000;  //  initial the prefix position to be near the max

        while (match.size() > 1) {  //  when there is one string left, stop
        	vector<string> temp;

        	//  each time match 2 strings, and find the new shortest common prefix
        	for (int i = 0; i < match.size(); i += 2) {
        		if (i+1 == match.size()) {
        			if (match[i].length() < pos) pos = match[i].length();

        			temp.push_back(match[i]);
        			break;
        		}

        		int j;
        		for (j = 0; j < pos && j < match[i].length() && j < match[i+1].length(); j++) {
        			if (match[i][j] != match[i+1][j]) break;
        		}
        		if (j < pos) pos = j;
        		temp.push_back(match[i]);
        	}

        	match = temp;
        }

        string result = "";
        for (int i = 0; i < pos; i++) {
        	result += strs[0][i];
        }
        return result;
    }
    };
    
除此以外，还有对同时匹配所有字符串算法的优化。设想如果从开头开始匹配字符串的话，大部分情况结束点都落在中间。如果找出最短串后从后往前开始匹配的话，也面临着同样的问题。那么何不从中间开始？从中间字符开始，与其他串对应的位置匹配，若成功则在右边的区间继续二分，若不成功则再左边的区间继续二分。这样，时间复杂度可以降到O（nlogm）。步骤如下：
1. 找出最短串
2. 从最短串的中间位置开始与其他串对应位置进行匹配，若两者前缀匹配则向右继续二分，若不匹配则向左继续二分，直到区间不能再分为止。
# Remove Duplicates from Sorted Array 
## Description
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length. 
## Solution
给定的数组中的元素是有序的，那么一趟遍历就可以去掉重复元素。我的思路是两两比较相邻元素，发现重复时，删除前面的那个元素。代码如下：

    class Solution {
    public:
    int removeDuplicates(vector<int>& nums) {
    	if (nums.size() == 0) return 0;
    	for (vector<int>::iterator it = nums.begin(); it != nums.end(); ) {
    		if (it+1 != nums.end() && *it == *(it+1)) {
    			it = nums.erase(it);
    		} else {
    			it++;
    		}
    	}

    	return nums.size();
    }
    };
    
看了参考答案的方法后，我才发现题目的意思原来是指，返回无重复的那些元素的数目，在原数组中保持它们从头开始排列且有序，但数组中超过返回值范围的那些元素则不作检查。那么就可以保存两个指针i、j，当i、j指向的元素相等时，j继续增大，直到它们指向的元素不相等。此时i加1，将j指向的元素复制到i指向的位置，重复比较的过程，直到j到达数组尾端。这样一来，无重复的所有元素都从数组首部开始排列，且保持有序。代码如下：

    class Solution {
    public:
    int removeDuplicates(vector<int>& nums) {
    	if (nums.size() == 0) return 0;
        
    	int i = 0;
        for (int j = 1; j < nums.length(); j++) {
            if (nums[j] != nums[i]) {
                i++;
                nums[i] = nums[j];
            }
        }
    	return i + 1;
    }
    };
