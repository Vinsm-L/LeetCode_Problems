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