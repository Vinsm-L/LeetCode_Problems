class Solution {
public:
    void nextPermutation(vector<int>& nums) {
    	int size = nums.size();
        if (size <= 1) return;

        bool flag = false;
        for (int m = size - 2; m >= 0; m--) {
        	int index = m;
        	for (int i = m + 1; i < size; i++) {
        		if (nums[i] > nums[m]) {
        			if (index == m || nums[i] < nums[index]) {
        				index = i;
        			}
        		}
        	}

        	if (index != m) {
        		int temp = nums[m];
        		nums[m] = nums[index];
        		nums[index] = temp;
        		for (int i = m + 1; i < size; i++) {
        			for (int j = i + 1; j < size; j++) {
        				if (nums[j] < nums[i]) {
        					int temp = nums[i];
        					nums[i] = nums[j];
        					nums[j] = temp;
        				}
        			}
        		}
        		flag = true;
        		break;
        	}
        }

        if (flag) return;

        for (int i = 0; i < size; i++) {
        	for (int j = i + 1; j < size; j++) {
        		if (nums[j] < nums[i]) {
       				int temp = nums[i];
    				nums[i] = nums[j];
        			nums[j] = temp;
        		}
        	}
        }
    }
};