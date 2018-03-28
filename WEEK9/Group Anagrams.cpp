class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if (strs.size() <= 1) {
        	result.push_back(strs);
        	return result;
        }

        vector<string> pattern;

        vector<string> anagrams[10000];
        for (int i = 0; i < strs.size(); i++) {
        	string p = getPattern(strs[i]);

        	bool flag = false;
        	int j;
        	for (j = 0; j < pattern.size(); j++) {
        		if (p == pattern[j]) {
        			anagrams[j].push_back(strs[i]);
        			flag = true;
        			break;
        		}
        	}
        	if (!flag) {
        		pattern.push_back(p);
        		anagrams[j].push_back(strs[i]);
        	}
        }

        for (int i = 0; anagrams[i].size() != 0; i++) {
        	result.push_back(anagrams[i]);
        }
        return result;
    }

    string getPattern(string str) {
    	for (int i = 0; i < str.length(); i++) {
    		for (int j = i; j < str.length(); j++) {
    			if (str[i] > str[j]) {
    				char temp = str[i];
    				str[i] = str[j];
    				str[j] = temp;
    			}
    		}
    	}
    	return str;
    }
};