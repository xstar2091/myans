#include <gtest/gtest.h>
#include <limits>
#include "myans/solution.h"

TEST(Solution, removeSublists) {
    std::string expected, actual;
    ListNode* head = nullptr;
    Solution sln;

    head = ListNode::create({-2, 5, -1, -10, 1, -1, 10, 2, 2, 2, 5, 5});
    head = sln.removeSublists(head);
    expected = "[2]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({10});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({10, 10, 10});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 2, 5, 5});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 2, 5, 3});
    head = sln.removeSublists(head);
    expected = "[2,3]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 10, 3});
    head = sln.removeSublists(head);
    expected = "[2,3]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 1, 10, 3});
    head = sln.removeSublists(head);
    expected = "[2,3]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 2, 5});
    head = sln.removeSublists(head);
    expected = "[2]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2});
    head = sln.removeSublists(head);
    expected = "[2]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = nullptr;
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5, 1, 1, 1});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5, 1, 1, 1, -1, 1, 1, -1, 1});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5, 1, 1, 1, -1, 1, 1, -1, 1, 3});
    head = sln.removeSublists(head);
    expected = "[3]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 5, 1, 1, 1, -1, 1, 1});
    head = sln.removeSublists(head);
    expected = "[-1,1,1]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 5, 1, 1, 1, -1, -1, 1});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5, 1, 1, 1, -1, 1, -1});
    head = sln.removeSublists(head);
    EXPECT_EQ(head, nullptr);

    head = ListNode::create({2, 5, 1, 1, 1, -1, -1, -1});
    head = sln.removeSublists(head);
    expected = "[-1]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({2, 5, 1, 1, 0, 1, -1, 1, 1});
    head = sln.removeSublists(head);
    expected = "[0,1,-1,1,1]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({1, 2, 3, 2, 5, -1, 1, 1, -1, 1, 3});
    head = sln.removeSublists(head);
    expected = "[1,2,3,3]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({1, 2, 3, 2});
    head = sln.removeSublists(head);
    expected = "[1,2,3,2]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({3, 2, 5, 4, 2, 5, 5});
    head = sln.removeSublists(head);
    expected = "[3,4,5]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);

    head = ListNode::create({std::numeric_limits<int>::max(), 10, 10, 10});
    head = sln.removeSublists(head);
    expected = "[" + std::to_string(head->val) + "]";
    actual = head->toString();
    EXPECT_EQ(actual, expected);
    ListNode::destroy(head);
}
