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
        if (lists.size() == 0) return NULL;

        vector<ListNode*> merging = lists;
        while (merging.size() > 1) {
        	vector<ListNode*> temp;

        	for (int i = 0; i < merging.size(); i++) {
        		if (i+1 < merging.size()) {
        			temp.push_back(merge2Lists(merging[i], merging[i+1]));
        			i++;
        		} else {
        			temp.push_back(merging[i]);
        		}
        	}
        	merging = temp;
        }
        return merging[0];
    }

    ListNode* merge2Lists(ListNode* list1, ListNode* list2) {
    	if (list1 == NULL) {
    		return list2;
    	} else if (list2 == NULL) {
    		return list1;
    	}

    	ListNode* head = NULL;
    	ListNode* current;

    	while (list1 != NULL || list2 != NULL) {
    		int toInsert;
    		if (list1 != NULL && list2 == NULL) {
    			toInsert = list1->val;
    			list1 = list1->next;
    		} else if (list1 == NULL && list2 != NULL) {
    			toInsert = list2->val;
    			list2 = list2->next;
    		} else {
    			if (list1->val < list2->val) {
    				toInsert = list1->val;
    				list1 = list1->next;
    			} else {
    				toInsert = list2->val;
    				list2 = list2->next;
    			}
    		}

    		if (head == NULL) {
    			head = new ListNode(toInsert);
    			head->next = NULL;
    			current = head;
    		} else {
    			current->next = new ListNode(toInsert);
        		(current->next)->next = NULL;
        		current = current->next;
    		}
    	}

    	return head;
    }
};