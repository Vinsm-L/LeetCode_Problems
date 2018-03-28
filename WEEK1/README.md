本周共完成2道题，以下为第一周的题目和题解。
# Two Sum
## Description
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

> Given nums = [2, 7, 11, 15], target = 9,
>
> Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].

https://leetcode.com/problems/two-sum/description/

## Solution
看完题目，脑海中浮现出来的第一种方法便是双重循环。利用双重循环，对于外层循环中的每一个数，在内层循环中向后遍历，找到和为目标数的数对并返回。

这种解法时间复杂度为O(n2)，当数据量很大时，消耗的时间就会明显增加。以下是代码：

    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            for (int i = 0; i < nums.size(); i++) {
            	for (int j = i + 1; j < nums.size(); j++) {
            		if (nums[i] + nums[j] == target) {
            			vector<int> temp;
        	    		temp.push_back(i);
            			temp.push_back(j);
            			return temp;
            		}
            	}
            }
        }
    };

那么，可以怎么优化呢？这里可以利用STL中的map容器。印象中有老师介绍过，map使用的数据结构是一种高效的平衡二叉树，红黑树。而vector使用的数据结构是数组。
这就决定了在查找时，vector的遍历要比map慢。

在这道题中，利用元素下标及元素本身形成映射，时间复杂度得以降低。代码如下(因为Java的map容器封装了直接对value查找key的函数，所以用Java写）：

    class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
           map.put(nums[i], i);
        }
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement) && map.get(complement) != i) {
                return new int[] { i, map.get(complement) };
            }
        }    
        throw new IllegalArgumentException("No two sum solution");
        }
    }

# Add Two Numbers 
## Description
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
## Solution
做这道题，主要用的就是最普通的整数加法：从低位到高位，每个位相加，大于9的产生进位。因为链表就是从低位到高位排序的，所以第一时间想到这个解法。

但是仍然有许多细节需要注意：
1. 两个整数的位数可能不相等。这种情况下，需要把后结束的整数的所有位遍历完。
2. 结束遍历后，可能还有一个进位，这时需要在循环外把这个进位加上。
3. 进位要随每次加法进行判断并设置。
4. 写链表时用指针的一些小细节。

以下为代码：

    /**
     * Definition for singly-linked list.
     * struct ListNode {
     *     int val;
     *     ListNode *next;
     *     ListNode(int x) : val(x), next(NULL) {}
     * };
     */
    class Solution {
    public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        ListNode* newList = NULL;
        ListNode* ptr3 = NULL;

        bool carry = false;

        while (ptr1 != NULL || ptr2 != NULL) {
        	int sum;
        	if (ptr1 == NULL) {
        		sum = ptr2->val;
        		ptr2 = ptr2->next;
        	} else if (ptr2 == NULL) {
        		sum = ptr1->val;
        		ptr1 = ptr1->next;
        	} else {
        		sum = ptr1->val + ptr2->val;
        		ptr1 = ptr1->next;
        		ptr2 = ptr2->next;
        	}

        	if (carry == true) {
        		sum++;
        	}

        	if (sum > 9) {
        		carry = true;
        		sum -= 10;
        	} else {
        		carry = false;
        	}

        	if (newList == NULL) {
        		newList = new ListNode(sum);
        		ptr3 = newList;
        	} else {
        		ptr3->next = new ListNode(sum);
        		ptr3 = ptr3->next;
        	}
        }

        if (carry == true) {
        	if (newList == NULL) {
        		newList = new ListNode(1);
        	} else {
        		ptr3->next = new ListNode(1);
        		ptr3 = ptr3->next;
        	}
        }
        return newList;
    }
    };
