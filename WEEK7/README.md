以下为本周的题目和题解。
# Merge k Sorted Lists
## Description
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 
## Solution
归并k个有序的链表，从整体归并和利用局部有序这两个角度，分别可以引申出两种算法：同时对k个链表进行归并，两两归并。

若同时对k个链表进行归并，则初始化指向这k个链表的首部的指针，比较它们指向的数值，选出最小的那个添加到新的链表中，然后令指向数值最小的指针向后移动一位，继续比较。需要注意两个情况：
1. 某指针到达链表尾部
2. 当所有指针都到达尾部，则排序结束

这种做法相当于对所有链表都遍历了一遍，设最终链表有n个节点，原链表数目为k，则时间复杂度为O（n*k），这里n与k都不是常量，因此时间复杂度可看作O（n2）级别的。代码如下：

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
    
若进行两两归并，则是利用了归并排序的思想。取出两个链表，对它们进行排序形成一个新的链表并将其放到一个容器中。完成一趟两两归并后，继续从容器中取出链表进行新一趟的两两归并。需要注意的地方有：
1. 当容器中只剩一个链表时结束排序
2. 两两归并时剩一个链表无法匹配的，直接把它放进容器中
3. 归并时注意某链表为空的情况

设最终链表有n个节点，原链表数目为k，每个链表的平均节点数为N。第一遍需要归并k/2次，每次归并包含N个节点；第二遍需要归并k/4次，每次归并包含2N个节点……总共归并了log k遍，则总的循环次数为（kN/2）* log k，这里kN = n，则时间复杂度为O（n*log k）。代码如下：

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

# Remove Element
## Description
Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

> Example:
> Given input array nums = [3,2,2,3], val = 3
> 
> Your function should return length = 2, with the first two elements of nums being 2.
## Solution
移除数组中所有与给定值相等的元素，条件是对剩余元素的顺序没有要求，且不检查剩余元素之外的其他元素。那么思路有两种：操作目标元素和操作剩余元素。

若操作目标元素，则初始化一个指向数组尾部的指针end和一个指向首部的指针i。当i发现目标元素时，就把目标元素与end指向的元素交换位置，并令end指针向前移动。否则令i向后移动。当i与end相遇时结束，并返回剩余元素的个数。此时时间复杂度为O（n）。代码如下：

    class Solution {
    public:
    int removeElement(vector<int>& nums, int val) {
        int count = nums.size();
        if (count == 0) return 0;

        int end = count - 1;

        for (int i = 0; i <= end; ) {
        	if (nums[i] != val) {
        		i++;
        	} else {
        		int temp = nums[end];
        		nums[end] = nums[i];
        		nums[i] = temp;

        		end--;
        		count--;
        	}
        }

        return count;
    }
    };

若操作剩余元素，则初始化指向数组首部的指针i，head。当i发现剩余元素时便把它们复制到head指向的位置，并令head、i向后移动。否则令i向后移动。当i遍历数组中所有元素时结束。此时时间复杂度也为O（n）。代码如下：
    
    class Solution {
    public:
    int removeElement(vector<int>& nums, int val) {
        int head = 0;
	    for (int i = 0; i < nums.size(); i++) {
	        if (nums[i] != val) {
	            nums[head] = nums[i];
	            head++;
	        }
	    }
	    return head;
    }
    };

