以下为本周的题目和题解。
# Search for a Range
## Description
Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

> For example,
> Given [5, 7, 7, 8, 8, 10] and target value 8,
> return [3, 4]. 
## Solution
给定一个有序数组，要求从中找到目标元素的下标范围（元素可能重复），使用算法的时间复杂度不能超过O(log n)。结合这些条件，首先想到用二分搜索。

通过二分搜索，找到目标元素所在位置。此时找到的目标元素可能只是其中一个，因此需要从该位置开始，向左向右搜索边界，停止搜索的条件：
1. 数组越界
2. 当前元素不等于目标元素

需要注意的细节是，二分搜索结束时，left、right指针可能正好落在目标元素上，所以要在循环外面再进行一次判断。二分搜索时间复杂度为O(log n)，代码如下：

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
    
