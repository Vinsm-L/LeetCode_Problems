以下为本周的题目和题解
# Swap Nodes in Pairs
## Description
Given a linked list, swap every two adjacent nodes and return its head.

> For example,
>
> Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. 
## Solution
要求以每两个结点为一组，交换这两个结点在链表中的位置。如果把一个链表打散成许多个这样的结点对，要交换它们的位置，只要维护一对指针，一个指针slow指向前一个结点，另一个指针fast指向后一个结点。令slow指向结点的下一个节点为fast指向的下一个结点，fast指向的下一个结点为slow指向的结点。

但是当这些结点对重新连接成一个链表时，就会出现这样的问题：对于每个结点对中的后一个结点，它的下一个结点的位置出错了。

以1->2->3->4为例子，处理完第一个结点对以后，链表变成2->1->3->4。处理完第二个结点对以后，结果理应是2->1->4->3，但实际并不是这样，因为此时1的后一个结点仍然是3，所以链表最后变成了2->1->3和4->3，4和1同时指向3。

为了解决这个问题，加入bridge指针，它指向前一个结点对中的后一个结点，用于桥接两个结点对。当一个结点对处理完成后，bridge把它指向的下一个结点设置为当前结点对的前一个结点。还是以1->2->3->4为例子，处理完第一个结点对后bridge指向1，现在的链表为2->1->3->4。当处理完第二个结点对时，bridge把1的后一个结点设置为4，因此链表就正确地变成了2->1->4->3。

只需要一趟遍历和常量的空间，时间复杂度和空间复杂度分别为O（n）和O（1）。代码如下：

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
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* slow = head;
        ListNode* fast = head->next;
        ListNode* bridge = NULL;
        head = fast;

        while (slow != NULL && fast != NULL) {
        	slow->next = fast->next;
        	fast->next = slow;
        	if (bridge != NULL) {
        		bridge->next = fast;
        	}
        	bridge = slow;

        	slow = slow->next;  
        	if (slow != NULL) fast = slow->next;
        }
        return head;
    }
    };

# Group Anagrams
## Description
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

> [
>  ["ate", "eat","tea"],
>  ["nat","tan"],
>  ["bat"]
> ]

Note: All inputs will be in lower-case.
## Solution
Anagrams是指字母及其个数都相同，但字母的顺序不同的字符串。题目要求把属于同一Anagram的字符串找出来并放在一起。

从Anagrams的标准入手，既然属于同一Anagrams的字符串拥有相同的字母和个数，那么可以为每个Anagrams设置一个模板，只要与模板匹配了，就属于模板对应的Anagrams。最容易想到的应该就是对字符串进行升/降序排序了，属于同一Anagrams的字符串，排序后的字符串必定相同。

先对数组中的每个字符串进行升序排序，再到模板数组中寻找它们对应的模板。若是找到了，就把字符串放到模板对应的vector中；若是找不到，就把字符串对应的模板加入模板数组中，再新开一个vector用于存放该字符串。

设字符串数量为n，字符串的平均长度为m，那么时间复杂度为O（n * m2）。代码如下：

    class Solution {
    public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if (strs.size() <= 1) {
        	result.push_back(strs);
        	return result;
        }

        vector<string> pattern;

        vector<string> anagrams[10000];
        for (int i = 0; i < strs.size(); i++) {
        	string p = getPattern(strs[i]);

        	bool flag = false;
        	int j;
        	for (j = 0; j < pattern.size(); j++) {
        		if (p == pattern[j]) {
        			anagrams[j].push_back(strs[i]);
        			flag = true;
        			break;
        		}
        	}
        	if (!flag) {
        		pattern.push_back(p);
        		anagrams[j].push_back(strs[i]);
        	}
        }

        for (int i = 0; anagrams[i].size() != 0; i++) {
        	result.push_back(anagrams[i]);
        }
        return result;
    }

    string getPattern(string str) {
    	for (int i = 0; i < str.length(); i++) {
    		for (int j = i; j < str.length(); j++) {
    			if (str[i] > str[j]) {
    				char temp = str[i];
    				str[i] = str[j];
    				str[j] = temp;
    			}
    		}
    	}
    	return str;
    }
    };
    
另外，我还想到用哈希的方法，若是能够对每个由相同的字母和个数组成的字符串都得出相同的哈希值，那么时间复杂度应该不会超过O（n * m）。但是我尝试了几个哈希函数，都没能完全消除冲突。参考答案中有一个与哈希有一点类似的方法，即统计字符串中出现字母的个数，所有出现字母个数都相同的字符串都属于同一个Anagrams。用一个二维数组map[i][j]存放字母个数，j从0到25，代表26个字母；map[i]代表一个模板的26个字母出现的数量。当一个字符串的26个字母出现数量与模板i匹配，则它属于模板i对应的Anagrams。这种方法的时间复杂度会达到O（n2 * m）。
