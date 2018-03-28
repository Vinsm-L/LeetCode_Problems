class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();

        bool isEven = false;             //  the size is even or odd number
        int pos = (size1 + size2) / 2;   //  the position of the median
        if ((size1 + size2) % 2 == 0) {
        	isEven = true;
        	pos--;
        }

        int i = 0, j = 0;               //  index
        double result = 0;

        while (i + j != pos) {
        	if (i == size1) {           //  when nums1 reaches end, stop traversing it
        		j++;
        		continue;
        	}

        	if (j == size2) {           //  same as above
        		i++;
        		continue;
        	}

        	if (nums1[i] < nums2[j]) {  //  sort
        		i++;
        	} else {
        		j++;
        	}
        }

        if (isEven) {

        	//  when one side stops, identify it and pick number from the other side
        	if (i == size1) {
        		result = (double)nums2[j] + (double)nums2[j+1];
        		return result / 2;
        	}
        	if (j == size2) {
        		result = (double)nums1[i] + (double)nums1[i+1];
        		return result / 2;
        	}

        	if (nums1[i] < nums2[j]) {
        		result = (double)nums1[i];
        		i++;
        	} else {
        		result = (double)nums2[j];
        		j++;
        	}

        	//  judge again
        	if (i == size1) {
        		result += (double)nums2[j];
        		return result / 2;
        	}
        	if (j == size2) {
        		result += (double)nums1[i];
        		return result / 2;
        	}

        	if (nums1[i] < nums2[j]) {
        		result += (double)nums1[i];
        		result = result / 2;
        		i++;
        	} else {
        		result += (double)nums2[j];
        		result = result / 2;
        		j++;
        	}
        } else {
        	if (i == size1) {
        		return (double)nums2[j];
        	}
        	if (j == size2) {
        		return (double)nums1[i];
        	}

        	if (nums1[i] < nums2[j]) {
        		result = (double)nums1[i];
        	} else {
        		result = (double)nums2[j];
        	}
        }

        return result;
    }
};