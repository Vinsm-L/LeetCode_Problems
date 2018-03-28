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