class Solution {
public:
    int myAtoi(string str) {
        int sign = 1;
        int sum = 0;
        bool start = false;
        for (int i = 0; i < str.length(); i++) {
        	if (str[i] != ' ' && !start) {
        		start = true;
        		if (str[i] == '-') sign = -1;
        		if (str[i] == '-' || str[i] == '+') continue;
        	}
        	
        	if (str[i] >= '0' && str[i] <= '9') {
        		if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && str[i] - '0' > 7)) {
        			if (sign == 1) {
        				return INT_MAX;
        			}
        			return INT_MIN;
        		}
        		sum = sum * 10 + str[i] - '0';
        	} else if (start) {
        		break;
        	}
        }
        return sum * sign;
    }
};