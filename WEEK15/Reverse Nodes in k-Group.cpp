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