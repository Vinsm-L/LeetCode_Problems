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