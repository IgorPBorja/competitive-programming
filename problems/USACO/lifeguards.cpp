#include <bits/stdc++.h>
using namespace std;

/*

OBS: ALL ENDPOINTS ARE DISTINCT

find out how many lifeguards cover i ( unit [i,i + 1) ):
    we need all j such that left[j] <= i && i < right[j]
    let this quantity be q[i] for 0 <= i < 1e9 

then we find j such that N(j) = |{left[j] <= i < right[j] && q[i] > 1}| is minimum 
(lifeguard with the smallest non overlap area)

the answer will be TOTAL - N(j)


Let left[] be the positions of left endpoints and right[] the positions of right endpoints
binary search l = max(j | left[j] <= i)
binary search r = max(j | right[j] <= i)
It's clear that r >= l, since that can't be more closing parenthesis (ends of ranges) before i
than open ones.
Thus there are l ranges that might cover unit i, but r of those are closed before. 
Answer: l - r in O(log n) 

Let's try to expand these type of queries to ranges:
    given a range [left[i], right[i]) we want how many 
    left[i] <= k < right[i] for which exists 0 <= j (!= i) < n such that k is in range j

    let PREF_left[i] be how many intervals are still open at unit left[i] (cover it)
    (i.e it is i - |{j| right[j] <= left[i]}| = i - (1 + max(j | right[j] <= left[i]) 
        which can be determined in O(log n))
    let p = max(right[j] | right[j] <= r) the when 

    let  
*/

int main()
{

}