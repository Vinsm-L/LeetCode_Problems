以下是本周的题目和题解
# Reverse Nodes in k-Group
## Description
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
> Given this linked list: 1->2->3->4->5
>
> For k = 2, you should return: 2->1->4->3->5
>
> For k = 3, you should return: 3->2->1->4->5 
## Solution
给定一个链表和一个数字k，以链表中连续的k个结点为一组，使这k个结点顺序逆转，然后处理下一组结点，直到某一组结点中结点数不足k为止。

![image](https://github.com/Vinsm-L/-WEEK15-LeetCode_Problems/blob/master/linked%20list&ptrs.PNG?raw=true)

如上图所示，对一组连续的k个结点进行逆序处理，所使用的算法需要分别指向一头一尾的两个指针begin、end，记录begin、end所在链表位置的变量beginIndex、endIndex，以及指向begin的前一个结点的指针beginBefore和指向end的后一个结点的指针endNext。getNextPtr函数根据传入的index和head指针返回指向链表对应位置的指针。

逆序的实现使用了栈这种数据结构，将结点从begin到end压入栈中，再一个个弹出，重新形成一个子链表。这个过程是可以优化的，可以不必删除结点，而是把原结点直接压入栈中。另外，使用栈也不够高效。可以将头尾两个结点的位置互换，然后头尾指针向中间移动，这样节省了更多时间。

实现了逆序处理后，令beginBefore指向结点的next指针指向子链表的头部，endNext指向结点的next指针指向子链表的尾部。最后是对所使用的指针进行更新，begin、end指向下一组的头尾，同时beginIndex、endIndex、beginBefore、endNext也要同步更新，然后进入下一个循环。

算法总体上使用了常量空间，时间复杂度为O（n2）。

需要注意的细节：
1. k <= 1或者链表为空时直接返回头指针
2. 判断一个指针ptr不为NULL时不能用!ptr
3. 当需要用容器存储结构体时，尽量用容器存储指向实例的指针，否则可能会出现内存错误
4. 注意链表的边界情况，避免内存错误

代码如下：

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1 || head == NULL) return head;

        int beginIndex = 0, endIndex = k-1;
        ListNode* begin = head;
        ListNode* end = getNextPtr(head, endIndex);
        ListNode* beginBefore = NULL;
        ListNode* endNext;

        while (end != NULL) {
        	endNext = end->next;
        	stack<ListNode*> reverseStack;

        	for (ListNode* i = begin; i != endNext; ) {
        		ListNode* temp = new ListNode(i -> val);
        		reverseStack.push(temp);
        		ListNode* a = i;
        		i = i -> next;
        		delete a;
        	}

        	ListNode* newHead = reverseStack.top();
        	ListNode* tmpPtr = newHead;
        	reverseStack.pop();
        	while (!reverseStack.empty()) {
        		tmpPtr->next = reverseStack.top();
        		tmpPtr = tmpPtr->next;
        		reverseStack.pop();
        	}
        	if (beginIndex == 0) head = newHead;

        	if (beginBefore != NULL) beginBefore->next = newHead;
        	tmpPtr->next = endNext;
        	beginBefore = tmpPtr;
        	beginIndex += k;
        	endIndex += k;
        	begin = getNextPtr(head, beginIndex);
        	end = getNextPtr(head, endIndex);
        }

        return head;
    }

    ListNode* getNextPtr(ListNode* head, int dist) {
    	ListNode* ptr = head;
    	for (int i = 0; i < dist; i++) {
    		ptr = ptr -> next;
    		if (ptr == NULL) return NULL;
    	}
    	return ptr;
    }
    };

# Search in Rotated Sorted Array
## Description
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
## Solution
题目的意思是，现在给定一个数组，它最初是按照升序排序且没有重复元素的，但现在它从某个位置被分成了两半，这两半位置互换，构成了现在的数组。要求从这个数组中找到一个目标元素并返回它的下标，如果没找到就返回-1。

若把它当做无序数组看待，也只需要一趟遍历就可以完成查找，时间复杂度为O（n），这是最坏的情况，所以所有的优化都应该比O（n）要小。对于一个有序数组的查找，通常使用二分法，所以我们首先要“还原”出一个有序的数组，即找到最小的元素的位置，然后将左右两半交换位置。

首先用二分搜索最小元素。数组最右边的元素是右边一半的最大元素，记为nums[right]；数组最左边的元素是左边一半的最小元素，记为nums[left]；左右两半分别有序，左边一半的所有元素都比右边一半的大。那么也就是说，我们需要找到右边一半的最小元素的位置。如果数组中间的元素比nums[right]要小，则它属于右边一半；如果比nums[right]要大，则它属于左边一半。根据中间元素与nums[right]的大小关系，重新确定左右边界，直到左右边界相等为止。过程如下：
1. 初始化left = 0, right = nums.size()-1
2. 计算mid = （left+right）/2，如它比nums[right]要小或相等，则right = mid，否则left = mid+1
3. 重复2，直到left等于right

找到最小元素的位置startIndex后，就可以直接用二分法搜索目标元素了，只不过中间元素位置的计算需要加上偏移量，即mid = ((left + right)/2 + startIndex) % size，因为有序数组的真正开始位置其实是startIndex。有时可能刚找到目标元素时，left就等于right了，也就不再进入循环，所以要在循环外再判断一次是否等于目标元素。

算法的时间复杂度为O（log n），代码如下：

    class Solution {
    public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        if (size < 1) return -1;

        int left = 0, right = size-1;
        while (left < right) {
        	int mid = (left + right) / 2;
        	if (nums[mid] <= nums[right]) {
        		right = mid;
        	} else {
        		left = mid + 1;
        	}
        	if (nums[mid] == target) return mid;
        }

        int startIndex = left;
        left = 0;
        right = size-1;
        while (left < right) {
        	int mid = ( (left + right)/2 + startIndex) % size;
        	if (nums[mid] < target) left = (left + right)/2 + 1;
        	if (nums[mid] > target) right = (left + right)/2;
        	if (nums[mid] == target) return mid;
        }
        if (nums[left] == target) return left;

        return -1;
    }
    };
