#include <iostream>
#include <vector>
#include <string>
using namespace std;

int longest_common_substring(const string& s1, const string& s2) {
    int len1 = s1.length(), len2 = s2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    int max_len = 0;

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                max_len = max(max_len, dp[i][j]);
            }

    return max_len;
}

int main() {
    string s1 = "abcde123xyz";
    string s2 = "xyz123abcde";
    cout << "Longest Common Substring Length: " << longest_common_substring(s1, s2) << endl;
    return 0;
}
