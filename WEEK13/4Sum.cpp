/*
** a solution to four-sum problem
** the xSum function can be reused to calculate the sum of any number, which is greater than 3, of array elements.
*/
class Solution {
public:
	vector<vector<int>> result;

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) return result;

        std::sort(nums.begin(), nums.end());  // the array has to be sorted

        vector<int> fix;
        xSum(nums, target, fix, 0, 4);

        return result;
    }

    /*
    ** nums: the sorted array
    ** currentTarget: the current target for the sum to achieve
    ** fix: store the elements chosen before the function reaches 3Sum level
    ** startIndex: indicate which index the current level should start at
    ** x: indicate which level the function arrives at currently
    */
    void xSum(vector<int>& nums, int currentTarget, vector<int>& fix, int startIndex, int x) {
    	// for every element starting from startIndex
    	// choose the element and fix it, then refresh the target, come to a lower level, and start from next index
    	if (x > 3) {
    		for (int i = startIndex; i < nums.size(); i++) {
    			fix.push_back(nums[i]);
    			xSum(nums, currentTarget-nums[i], fix, i+1, x-1);
    			fix.pop_back();

    			// skip the repeated neighboring elements, to avoid duplicate x sum results
    			while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
                	i++;
    		}
    	} else {
    		// when it arrives at level 3, calculate 3 sum
    		if (nums.size() - startIndex < 3) return;

	    	for (int i = startIndex; i < nums.size(); i++) {
	    		int n = nums[i];
	    		int left = i+1;  // left pointer
	    		int right = nums.size()-1;  // right pointer

	    		while (left < right) {
	    			int sum = n + nums[left] + nums[right];

	    			// adjust the pointer according to the sum and target
	    			if (sum < currentTarget) {
	    				left++;
	    			} else if (sum > currentTarget) {
	    				right--;
	    			} else {
	    				vector<int> temp = fix;
	    				temp.push_back(n);
	    				temp.push_back(nums[left]);
	    				temp.push_back(nums[right]);
	    				result.push_back(temp);
	    				int numLeft = nums[left];
	    				int numRight = nums[right];

	    				// to avoid duplicate 3 sum results
	    				while (left < right && nums[left] == numLeft) left++;

	    				while (left < right && nums[right] == numRight) right--;
	    			}
	    		}

	    		// skip the repeated neighboring elements, to avoid duplicate 3 sum results
	    		while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
	                i++;
	    	}
    	}
    }
};