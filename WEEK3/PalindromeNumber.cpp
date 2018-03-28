class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;

        if (x % 10 == 0 && x != 0) return false;

        int lowerPart = 0;
        while (x > lowerPart) {
        	lowerPart = lowerPart * 10 + x % 10;
        	x /= 10;
        }

        if (lowerPart != x && lowerPart / 10 != x) {
        	return false;
        }
        return true;
    }
};