class Solution {
public:
    bool isMatch(string s, string p) {
        return compare(0, 0, s, p);
    }

    bool compare(int i, int j, string s, string p) {
    	if (j == p.length()) {
    		return i == s.length();
    	}
    	bool match = false;
    	if (i < s.length() && (s[i] == p[j] || p[j] == '.')) {
    		match = true;
    	}

    	if (j+1 < p.length() && p[j+1] == '*') {
    		return ((match && compare(i+1, j, s, p)) || compare(i, j+2, s, p));
    	} else {
    		return match && compare(i+1, j+1, s, p);
    	}
    	
    }
};