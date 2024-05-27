#ifndef MYANS_LIST_NODE_H
#define MYANS_LIST_NODE_H

#include <string>

struct ListNode {
    int val;
    ListNode* next;
    ListNode();
    ListNode(int x);
    ListNode(int x, ListNode* next);

    static ListNode* create(const std::initializer_list<int>& initList);
    static void destroy(ListNode* head);
    std::string toString() const;
};


#endif //MYANS_LIST_NODE_H
