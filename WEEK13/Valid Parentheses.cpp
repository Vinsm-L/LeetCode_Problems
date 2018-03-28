class Solution {
public:
    bool isValid(string s) {
        if (s == "") return true;

        stack<char> check;

        for (int i = 0; i < s.length(); i++) {
        	if (s[i] == '(' || s[i] == '{' || s[i] == '[') 
        		check.push(s[i]);
        	else if (s[i] == ')' && check.size() > 0 && check.top() == '(')
        		check.pop();
        	else if (s[i] == ']' && check.size() > 0 && check.top() == '[')
        		check.pop();
        	else if (s[i] == '}' && check.size() > 0 && check.top() == '{')
        		check.pop();
        	else 
        		return false;
        }

        if (check.size() > 0) return false;
        return true;
    }
};