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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> temp = lists;
        ListNode* head = NULL;
        if (lists.size() == 0) return head;

        ListNode* current;
        int min, minIndex;
        bool flag = true;

        while (flag) {
        	min = 999999;
        	flag = false;

        	for (int i = 0; i < temp.size(); i++) {
        		if (temp[i] != NULL) {
        			flag = true;
        			if (temp[i]->val < min) {
        				min = temp[i]->val;
        				minIndex = i;
        			}
        		}
        	}

        	if (!flag) break;

        	if (head == NULL) {
        		head = new ListNode(min);
        		head->next = NULL;
        		current = head;
        	} else {
        		current->next = new ListNode(min);
        		(current->next)->next = NULL;
        		current = current->next;
        	}
        	temp[minIndex] = temp[minIndex]->next;
        }

        return head;
    }
};