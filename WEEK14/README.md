以下是本周的题目和题解。
# Generate Parentheses
## Description
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

> For example, given n = 3, a solution set is:
>
> [
>  "((()))",
>  "(()())",
>  "(())()",
>  "()(())",
>  "()()()"
> ]
## Solution
给定n对括号，求出它们合法的所有可能组合。所谓合法，即左右括号数量相等，且符合括号嵌套规则。

若采用递推的思想，则从1对括号开始，进行推导：
* （）
* （）（），（（））
* （）（）（），（）（（）），（（））（），（（）（）），（（（）））

……
可以归纳出一个公式，如下：

generate(n) = （generate（i））generate（n-i-1），i = 0~n-1

即第n次生成n对括号的所有组合，在generate（i）返回的串外面添加括号，再与generate（n-i-1）返回的串连接，最后将生成的所有串作为generate（n）的结果。它依赖于前面n-1次生成的结果，因此这个公式是递推的。

算法实现如下：

    class Solution {
    public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string> > result;
        vector<string> v0;
        v0.push_back("");
        if (n == 0) return v0;
        result.push_back(v0);

        for (int i = 1; i <= n; i++) {
        	NthGeneration(i, result);
        }
        return result[n];
    }

    void NthGeneration(int n, vector<vector<string> >& result) {
		    vector<string> temp;
		    for (int i = 0; i < n; i++) {
			    for (int j = 0; j < result[i].size(); j++) {
				    for (int k = 0; k < result[n-i-1].size(); k++) {
					    string str = "(" + result[i][j] + ")" + result[n-i-1][k];
					    temp.push_back(str);
				    }
			    }
		    }
		    result.push_back(temp);
    }
    };
    
另一种思路则用两个变量记录剩下要被添加的左括号和右括号的数量，记为n， m。当n > 0，添加左括号；当m > 0，添加右括号。当n = m = 0时，结束算法。实现如下：

    class Solution {
    public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        addingpar(res, "", n, 0);
        return res;
    }
    void addingpar(vector<string> &v, string str, int n, int m){
        if(n==0 && m==0) {
            v.push_back(str);
            return;
        }
        if(m > 0){ addingpar(v, str+")", n, m-1); }
        if(n > 0){ addingpar(v, str+"(", n-1, m+1); }
    }
    };
    
    
