#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "myans/findupdate.h"
#include "myans/path.h"
#include "unittest_env.h"

extern UnitTestEnv env;

TEST(Findupdate, init) {
    ASSERT_TRUE(env.init());
}

// 测试不存在的路径
TEST(Findupdate, checkFile_NotExist) {
    Path p;
    p.reset(env.path().path);
    p.setName("not.exist.dir");
    Findupdate fu;
    EXPECT_FALSE(fu.checkFile(p.path()));
}

// 测试文件
TEST(Findupdate, checkFile_ExistButIsFile) {
    Path p;
    p.reset(env.dot_file().path);
    Findupdate fu;
    EXPECT_FALSE(fu.checkFile(p.path()));
}

bool splitSortNumFromName(const char* name, int& num) {
    const char* head = strrchr(name, '-');
    if (head == nullptr) {
        return false;
    }
    head++;
    char* end_ptr = nullptr;
    num = static_cast<int>(strtol(head, &end_ptr, 10));
    return strlen(end_ptr) == 0;
}

void walkPathAndTest(const Path& p, std::vector<int>& numList) {
    size_t count = 0;
    p.walk([&count, &numList](const Path& path) -> int {
        if (path.extension() == "stp") {
            count++;
            int num = 0;
            splitSortNumFromName(path.name().c_str(), num);
            numList.push_back(num);
        } else if (path.is_dir()) {
            std::vector<int> newNumList = {0};
            walkPathAndTest(path, newNumList);
        }
        return 0;
    });
    std::sort(numList.begin(), numList.end(), std::less<>());
    if (numList.size() > 1) {
        numList[0] = numList[1] - 1;
    }
    EXPECT_EQ(numList.size(), count + 1);
    for (size_t i = 1; i < numList.size(); i++) {
        EXPECT_EQ(numList[i] - 1, numList[i - 1]);
    }
}

TEST(Findupdate, checkFile_Dir) {
    ASSERT_TRUE(env.init("unittest_temp_dir_check_file"));
    Path p;
    p.reset(env.path().path);
    Findupdate fu;
    EXPECT_TRUE(fu.checkFile(p.path()));
    std::vector<int> numList = {0};
    walkPathAndTest(p, numList);
}

void walkPathAndTest(const Path& p, std::vector<std::string>& pathList) {
    p.walk([&pathList](const Path& path) -> int {
        if (path.extension() == "stp") {
            pathList.emplace_back(path.path());
        } else if (path.is_dir()) {
            std::vector<std::string> newPathList;
            walkPathAndTest(path, newPathList);
        }
        return 0;
    });
    for (const auto& path_str : pathList) {
        EXPECT_EQ(env.stp_new_file_table().count(path_str), 1);
    }
}

TEST(Findupdate, checkFile2_Dir) {
    ASSERT_TRUE(env.init("unittest_temp_dir_check_file_2"));
    Path p;
    p.reset(env.path().path);
    Findupdate fu;
    EXPECT_TRUE(fu.checkFile2(p.path()));
    std::vector<std::string> pathList;
    walkPathAndTest(p, pathList);
}

TEST(Findupdate, checkFile3_Dir) {
    ASSERT_TRUE(env.init("unittest_temp_dir_check_file_3"));
    Path p;
    p.reset(env.path().path);
    Findupdate fu;
    EXPECT_TRUE(fu.checkFile3(p.path()));
    std::vector<int> numList = {0};
    walkPathAndTest(p, numList);
}
