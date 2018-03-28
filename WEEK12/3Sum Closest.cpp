class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());

        int currentSum;
        int currentDist = 99999;
        for (int i = 0; i < nums.size(); i++) {
        	int fix = nums[i];
        	int left = i+1, right = nums.size()-1;

        	while (left < right) {
        		int tempSum = fix + nums[left] + nums[right];

        		int dist = tempSum - target;
        		if (dist < 0) dist = -dist;
        		if (dist < currentDist) {
        			currentDist = dist;
        			currentSum = tempSum;
        		}

        		if (tempSum == target) return target;
        		if (tempSum < target) left++;
        		if (tempSum > target) right--;
        	}
        }
        return currentSum;
    }
};