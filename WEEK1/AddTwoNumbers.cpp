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