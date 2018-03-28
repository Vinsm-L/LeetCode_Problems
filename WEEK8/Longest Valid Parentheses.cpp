class Solution {
public:
    int longestValidParentheses(string s) {
        int count = 0;
        int maxLen = 0;
        stack<int> myStack;
        myStack.push(-1);

        for (int i = 0; i < s.length(); i++) {
        	if (myStack.empty()) {
        		myStack.push(i);
        		continue;
        	}

        	int top = myStack.top();
        	if (top == -1) {
        		myStack.push(i);
        		continue;
        	}

        	if (s[i] == ')' && s[top] == '(') {
        		myStack.pop();
        		count = i - myStack.top();
        	} else {
        		myStack.push(i);
        	}

        	if (count > maxLen) maxLen = count;
        }

        return maxLen;
    }
};