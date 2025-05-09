#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_common_substring(const char* s1, const char* s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int** dp = malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; ++i)
        dp[i] = calloc(len2 + 1, sizeof(int));

    int max_len = 0;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len)
                    max_len = dp[i][j];
            }
        }
    }

    for (int i = 0; i <= len1; ++i)
        free(dp[i]);
    free(dp);

    return max_len;
}

int main() {
    const char* s1 = "abcde123xyz";
    const char* s2 = "xyz123abcde";
    printf("Longest Common Substring Length: %d\n", longest_common_substring(s1, s2));
    return 0;
}
