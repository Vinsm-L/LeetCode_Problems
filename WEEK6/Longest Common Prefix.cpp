class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
    	if (strs.size() == 0) return "";

        vector<string> match = strs;  //  store the strings to match for each turn
        int pos = 100000;  //  initial the prefix position to be near the max

        while (match.size() > 1) {  //  when there is one string left, stop
        	vector<string> temp;

        	//  each time match 2 strings, and find the new shortest common prefix
        	for (int i = 0; i < match.size(); i += 2) {
        		if (i+1 == match.size()) {
        			if (match[i].length() < pos) pos = match[i].length();

        			temp.push_back(match[i]);
        			break;
        		}

        		int j;
        		for (j = 0; j < pos && j < match[i].length() && j < match[i+1].length(); j++) {
        			if (match[i][j] != match[i+1][j]) break;
        		}
        		if (j < pos) pos = j;
        		temp.push_back(match[i]);
        	}

        	match = temp;
        }

        string result = "";
        for (int i = 0; i < pos; i++) {
        	result += strs[0][i];
        }
        return result;
    }
};