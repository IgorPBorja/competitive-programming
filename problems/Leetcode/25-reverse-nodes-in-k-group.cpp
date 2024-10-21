#include <vector>
#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
 
class Solution {
public:
    static void printList(ListNode* head){
        while (head != nullptr){
            cout << head->val << "->";
            head = head->next;
        }
        cout << endl;
    }
    
    static ListNode* build(vector<int>& a){
        ListNode *head = new ListNode(), *cur = head;
        const int n = a.size();
        for (int i = 0; i < n; i++){
            cur->val = a[i];
            if (i + 1 < n){
                cur->next = new ListNode();
                cur = cur->next;
            }
        }
        return head;
    }

    static bool hasBlock(ListNode* node, int k){
        int cnt = 0;
        while (node != nullptr && cnt < k){
            ++cnt;
            node = node->next;
        }
        return cnt == k;
    }

    static ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *beforeStart = nullptr, *start = head, *prev = head, *cur = head->next;
        bool setFinalStart = false;
        ListNode *finalStart = head;
        while (start != nullptr){
            if (!hasBlock(start, k)) break;
            for (int i = 0; i < k - 1 && cur != nullptr; i++){
                // cout << "at node " << cur->val << endl;
                ListNode* next = cur->next;
                // prev -> cur -> next
                cur->next = prev;
                prev = cur;
                cur = next;
            }
            // prev is new start now
            // beforeStart -> prev -> ... -> start -> cur
            if (beforeStart != nullptr){
                beforeStart->next = prev;
            }
            if (!setFinalStart) {
                finalStart = prev;
                setFinalStart = true;
                // cout << "set new head! to " << prev->val << endl;
            }
            start->next = cur;
            beforeStart = start;
            start = cur;
            prev = cur;
            if (cur != nullptr){
                cur = cur->next;
            }
        } 
        return finalStart;
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    ListNode* head = Solution::build(a);
    head = Solution::reverseKGroup(head, k);
    Solution::printList(head);
}