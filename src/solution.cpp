#include "myans/solution.h"

ListNode *Solution::removeSublists(ListNode *head) {
    ListNode virtualHead(0, head);
    ListNode* prev = &virtualHead;
    ListNode* cur = prev->next;
    ListNode* tail = cur;

    // 删除[cur, tail)范围内的节点
    auto deleteRange = [](ListNode*& cur, ListNode*& tail) {
        while (cur != tail) {
            ListNode* gc = cur;
            cur = cur->next;
            delete gc;
        }
    };

    int result = 1;
    while (tail) {
        result = 1;
        while (tail && result != 10) {
            result *= tail->val;
            tail = tail->next;
        }
        if (result == 10) {
            // 删除[cur, tail)
            deleteRange(cur, tail);
            // 10后面跟着的1和-1
            while (tail) {
                if (tail->val == 1) {
                    while (tail && tail->val == 1) {
                        tail = tail->next;
                    }
                    deleteRange(cur, tail);
                } else if (tail->val == -1) {
                    // 找到另一个-1,则删除
                    // 若找不到，tail需要复位到当前-1
                    tail = tail->next;
                    while (tail) {
                        if (tail->val == 1) {
                            tail = tail->next;
                            continue;
                        } else if (tail->val == -1) {
                            tail = tail->next;
                            deleteRange(cur, tail);
                            break;
                        } else {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }
            prev->next = cur;
            prev = &virtualHead;
        } else {
            prev = cur;
        }
        if (prev) {
            cur = prev->next;
            tail = cur;
        }
    }
    return virtualHead.next;
}
