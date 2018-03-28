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