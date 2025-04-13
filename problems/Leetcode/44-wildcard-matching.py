class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        """
            dp[i][j] = (p[...i-1] matches s[...j-1]) ?

            dp[0][0] = true,
            dp[i][0] = true if p[...i-1] = **...* else false, for i > 0
            dp[i][j] =
                if p[i - 1] == * or and dp[i][j - 1]:
                    true (greedily reuse wildcard)
                elif p[i - 1] == '?' and dp[i - 1][j - 1]:
                    true (match single char with '?')
                elif p[i - 1] == s[j] and dp[i - 1][j - 1]:
                    true (match single char with corresponding)
                else
                    false
            
            Complexity: O(n^2)
        """
        partialMatches = [[False for i in range(len(p) + 1)] for i in range(len(s) + 1)]
        ## empty pattern matches empty string
        partialMatches[0][0] = True
        for i in range(1, len(p) + 1):
            ## non-empty pattern matches empty-string iff it is only composed by *
            partialMatches[i][0] = (p[i] == '*') and partialMatches[i - 1][0]
        for j in range(1, len(s) + 1):
            ## empty pattern does not match non-empty string
            partialMatches[0][j] = False 

        for i in range(1, len(p) + 1):
            for j in range(1, len(s) + 1):
                if (p[i - 1] == '*' and dp[i][j - 1]):
                    ## greedily reuse star
                    dp[i][j] = True
                elif (p[i - 1] == '?' and dp[i - 1][j - 1]):
                    ## match character using single use wildcard '?'
                    dp[i][j] = True
                elif (p[i - 1] == s[j - 1] and dp[i - 1][j - 1]):
                    dp[i][j] = True
        
        return dp[len(p)][len(s)]
        
