#include "myans/list_node.h"

ListNode::ListNode()
    : val(0)
    , next(nullptr) {

}

ListNode::ListNode(int x)
    : val(x)
    , next(nullptr) {

}

ListNode::ListNode(int x, ListNode *next)
    : val(x)
    , next(next){

}

ListNode *ListNode::create(const std::initializer_list<int> &initList) {
    ListNode virtualHead;
    ListNode* cur = &virtualHead;
    for (int val : initList) {
        cur->next = new ListNode(val);
        cur = cur->next;
    }
    return virtualHead.next;
}

void ListNode::destroy(ListNode *head) {
    ListNode* nt = nullptr;
    while (head) {
        nt = head->next;
        delete head;
        head = nt;
    }
}

std::string ListNode::toString() const {
    std::string str("[");
    char buf[32] = {0};
    const ListNode *cur = this;
    const ListNode* nt = nullptr;
    while (cur) {
        nt = cur->next;
        snprintf(buf, sizeof(buf), "%d,", cur->val);
        str.append(buf);
        cur = nt;
    }
    if (str.size() > 1) {
        str.pop_back();
    }
    str.append("]");
    return str;
}
