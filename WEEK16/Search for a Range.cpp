class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) {
        	return {-1, -1};
        }
        
        vector<int> result;
        int left = 0, right = nums.size()-1;
        int leftBound = -1, rightBound = -1;
        while (left < right) {
        	int mid = (left+right) / 2;
        	if (target < nums[mid]) {
        		right = mid;
        	} else if (target > nums[mid]) {
        		left = mid+1;
        	} else {
        		leftBound = mid;
        		rightBound = mid;
        		findBoundary(leftBound, rightBound, nums, target);
                break;
        	}
        }

        if (nums[left] == target) {
        	leftBound = left;
        	rightBound = left;
        	findBoundary(leftBound, rightBound, nums, target);
        }
        result.push_back(leftBound);
        result.push_back(rightBound);
        return result;
    }

    void findBoundary(int& leftBound, int& rightBound, vector<int>& nums, int target) {
        while (true) {
            bool flag = false;
            if (leftBound >= 0 && nums[leftBound] == target) {
                leftBound--;
                flag = true;
            }
            if (rightBound < nums.size() && nums[rightBound] == target) {
                rightBound++;
                flag = true;
            }
            if (!flag) break;
        }
        leftBound++;
        rightBound--;
    }
};