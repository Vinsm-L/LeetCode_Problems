class Solution {
public:
    string longestPalindrome(string s) {
    	int len = s.length();
        int min = 0;  //  store the head of target substring
        int max = 0;  //  store the tail of target substring
        int i, j;

        for (int round = 0; round < len-1; round++) {
        	//  assume the length of target is even
        	if (s[round] == s[round+1]) {
        		i = round;
        		j = i+1;
        		while (s[i] == s[j]) {
	        		if (j-i > max-min) {
	        			min = i;
	        			max = j;
        			}
        			if (i-1 < 0 || j+1 >= len) {  //  avoid run time error
	        			break;
	        		}
	        		i--;
	        		j++;
        		}
        	}

        	//  assume the length of target is odd
        	if (round-1 >= 0 && s[round-1] == s[round+1]) {
        		i = round-1;
        		j = round+1;

        		while (s[i] == s[j]) {
		        	if (j-i > max-min) {
	        			min = i;
	       				max = j;
	       			}
	       			if (i-1 < 0 || j+1 >= len) {
		        		break;
		        	}
	        		i--;
	        		j++;
        		}
        	}
        	
        }

        string result = "";
        for (int k = min; k <= max; k++) {
        	result += s[k];
        }
        return result;
    }
};