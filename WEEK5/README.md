以下是本周的题目和题解
# Remove Nth Node From End of List
## Description
Given a linked list, remove the nth node from the end of list and return its head.

For example,

> Given linked list: 1->2->3->4->5, and n = 2.
>
> After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass. 
## Solution
这道题有许多解法。如果不要求在一趟遍历中实现节点的移除，则可以首先从头到尾遍历一遍，计算出节点总数m，再从头开始，移除第m-n个节点。实际上与一趟遍历相比，两者的时间复杂度都是O（m）。代码如下：

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

    int getLength(ListNode* head) {
        int counter = 0;
        while (head) {
            counter++;
            head=head->next;
        }
        return counter;
    }
    
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) return head;
        
        int L = getLength(head);
        if (L < n) return head;
        if (L == n) return head->next;
        
        int location = 1;
        ListNode* p = head;
        ListNode* front = head;
        while (location < L-n+1) {
            front = p;
            p = p->next;
            location++;
        }
    
        front->next = p->next;
        return head;
    }
    };
    
如果需要在一趟遍历中完成所有操作的话，则有两种思路：牺牲空间换时间，寻找更优的算法。

链表的特点是不允许随机访问，单向链表只能从头结点开始访问，且节点数需要遍历结束后才能计算出来。牺牲空间，意味着赋予单向链表以数组的特性——支持“下标”访问。具体的做法，就是每访问完一个节点，新增一个指向它的指针，并将该指针与节点的顺序号关联起来。最简单的方法，就是将指针放进一个vector容器中，当一趟遍历结束后，计算出要删除的节点所在位置，直接找到指向它的指针。代码如下：

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
    	  vector<ListNode*> ptr;
        ListNode* temp = head;

        while (temp != NULL) {
        	ptr.push_back(temp);
        	temp = temp -> next;
        }

        ListNode* toRemove = ptr[ptr.size() - n];
        if (ptr.size() - n == 0) {
        	ListNode* result = toRemove -> next;
        	delete toRemove;
        	return result;
        } else {
        	ptr[ptr.size() - n - 1] -> next = toRemove -> next;
        	delete toRemove;
        	return ptr[0];
        }
    }
    };
    
寻找更优的算法，则需要考虑目标节点的空间位置与数学关系。在一个链表中，顺数第n个节点与倒数第n个节点是关于中心对称的。也就是说，如果均以头结点为起点，顺数第n个节点到起点的距离与倒数第n个节点到起点的距离之和等于链表的长度。

那么，设链表长度为m。从尾节点开始走n步，到达倒数第n个节点；从头结点开始走m-n步，到达倒数第n个节点。关键在于如何知道已经走了m-n步。设有一快一慢两个指针，快的指针先走n步，慢的才开始走，那么当快的指针走了m步时，慢的指针就走了m-n步。代码如下：
  
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
     ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *slow = head;
        ListNode *fast = head;
        
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        if (fast == NULL)
            return head->next;
            
        while (fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
    };
