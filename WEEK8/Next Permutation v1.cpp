class Solution {
public:
    void nextPermutation(vector<int>& nums) {  
        int i = nums.size()-2, j = nums.size()-1;
        while (i >= 0 && nums[i] >= nums[i+1]) i--;
        if (i != -1) {
            while (nums[j] <= nums[i]) j--;
            nums[i] = nums[i] ^ nums[j];
            nums[j] = nums[i] ^ nums[j];
            nums[i] = nums[i] ^ nums[j];
        }
        i++;
        for (j = nums.size() - 1; i < j; i++, j--) {
            nums[i] = nums[i] ^ nums[j];
            nums[j] = nums[i] ^ nums[j];
            nums[i] = nums[i] ^ nums[j];
        }
    }
};