以下是第3周的题目和题解。
# Longest Palindromic Substring 
## Description
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

> Input: "babad"
>
> Output: "bab"
>
> Note: "aba" is also a valid answer.

Example:

> Input: "cbbd"
>
> Output: "bb"

## Solution
这道题让我们找一个给定串的最大回文子串，回文的特点是左右对称。以前曾遇到过用栈判断一个给定串是否为回文的题目，但由于这里事先不知道子串的长度，没有想出利用栈的特性的好方法。

于是我对串中一个个字符进行判断，主要分成两种情况：
1. 假设子串的长度为偶数。先判断当前字符与下一个字符是否相同，若相同再以它们为中心向两边扩散，判断两边对应位置的字符是否相同。
2. 假设子串的长度为奇数。以当前字符为中心向两边扩散，判断两边对应位置的字符是否相同。

每次得到一个新的回文子串时，判断其长度是否为目前最长，如果是则保存子串头尾下标。另外还要注意越界的问题。时间复杂度为O（n2）。

通常在寻找子串时，若用的是遍历的方法，都是把每次遍历的第一个字符当做子串的头。但是在这里，考虑到回文对称的特点，每次遍历的第一个字符反而是作为中心。代码如下：

    class Solution {
    public:
    string longestPalindrome(string s) {
        int len = s.length();
        int min = 0;  //  store the head of target substring
        int max = 0;  //  store the tail of target substring
        int i, j;

        for (int round = 0; round < len-1; round++) {
        	//  assume the length of target is even
        	if (s[round] == s[round+1]) {
        		i = round;
        		j = i+1;
        		while (s[i] == s[j]) {
	        		if (j-i > max-min) {
	        			min = i;
	        			max = j;
        			}
        			if (i-1 < 0 || j+1 >= len) {  //  avoid run time error
	        			break;
	        		}
	        		i--;
	        		j++;
        		}
        	}

        	//  assume the length of target is odd
        	if (round-1 >= 0 && s[round-1] == s[round+1]) {
        		i = round-1;
        		j = round+1;

        		while (s[i] == s[j]) {
		        	if (j-i > max-min) {
	        			min = i;
	       				max = j;
	       			}
	       			if (i-1 < 0 || j+1 >= len) {
		        		break;
		        	}
	        		i--;
	        		j++;
        		}
        	}
        	
        }

        string result = "";
        for (int k = min; k <= max; k++) {
        	result += s[k];
        }
        return result;
    }
    };
        
# Palindrome Number
## Description
Determine whether an integer is a palindrome. Do this without extra space.
## Solution
前面做了一道回文的题目，回文的特点是左右对称。因此判断一个数是不是回文，只要看它左边一半跟右边一半的逆序是否相等即可。

有几个需要注意的地方，首先数字的长度也是事先不知道的，而因为我没有把整个数字的各个位遍历完，所以最终也不知道数字有多少位。但是如果它是回文，那么当两边长度相等时，左边必定不大于右边。另外，长度是奇数还是偶数也事先不清楚，如果是偶数的话左右两边就相等，如果是奇数的话右边除去一位后与左边相等。

当数字为负数时不是回文。还有一个特例，就是当数字最低位是0时，它不是回文，因为它的最高位不会是0。这个特例是上述循环不能正确判断的，所以要单独拿出来。

假设给定数字为n位，那么共有n/2次循环，时间复杂度为O（n）。代码如下：

    class Solution {
    public:
    bool isPalindrome(int x) {
        if (x < 0) return false;

        if (x % 10 == 0 && x != 0) return false;

        int lowerPart = 0;
        while (x > lowerPart) {
        	lowerPart = lowerPart * 10 + x % 10;
        	x /= 10;
        }

        if (lowerPart != x && lowerPart / 10 != x) return false;

        return true;
    }
    };
