#include <gtest/gtest.h>
#include <vector>
#include "myans/path.h"
#include "unittest_env.h"

extern UnitTestEnv env;

TEST(Path, init) {
    ASSERT_TRUE(env.init());
}

TEST(Path, reset_NotExist) {
    Path p;
    p.reset(env.path().path + "/NotExistFile.txt");
    EXPECT_FALSE(p.valid());
    EXPECT_FALSE(p.exist());
    EXPECT_FALSE(p.is_dir());
    EXPECT_EQ(p.path(), "");
    EXPECT_EQ(p.parent(), "");
    EXPECT_EQ(p.name(), "");
    EXPECT_EQ(p.extension(), "");
    EXPECT_EQ(p.file_name(), "");
}

TEST(Path, reset_DirRoot) {
    Path p;
    p.reset("/");
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_TRUE(p.is_dir());
    EXPECT_EQ(p.path(), "/");
    EXPECT_EQ(p.parent(), "");
    EXPECT_EQ(p.name(), "");
    EXPECT_EQ(p.extension(), "");
    EXPECT_EQ(p.file_name(), "");
}

TEST(Path, reset_Dir) {
    Path p;
    p.reset(env.path().path);
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_TRUE(p.is_dir());
    EXPECT_EQ(p.path(), env.path().path);
    EXPECT_EQ(p.parent(), env.path().parent);
    EXPECT_EQ(p.name(), env.path().name);
    EXPECT_EQ(p.extension(), env.path().extension);
    EXPECT_EQ(p.file_name(), env.path().file_name);
}

TEST(Path, reset_SubDir) {
    Path p;
    p.reset(env.sub_dir().path);
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_TRUE(p.is_dir());
    EXPECT_EQ(p.path(), env.sub_dir().path);
    EXPECT_EQ(p.parent(), env.sub_dir().parent);
    EXPECT_EQ(p.name(), env.sub_dir().name);
    EXPECT_EQ(p.extension(), env.sub_dir().extension);
    EXPECT_EQ(p.file_name(), env.sub_dir().file_name);
}

TEST(Path, reset_DotDir) {
    Path p;
    p.reset(env.dot_dir().path);
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_TRUE(p.is_dir());
    EXPECT_EQ(p.path(), env.dot_dir().path);
    EXPECT_EQ(p.parent(), env.dot_dir().parent);
    EXPECT_EQ(p.name(), env.dot_dir().name);
    EXPECT_EQ(p.extension(), env.dot_dir().extension);
    EXPECT_EQ(p.file_name(), env.dot_dir().file_name);
}

TEST(Path, reset_DotFile) {
    Path p;
    p.reset(env.dot_file().path);
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_FALSE(p.is_dir());
    EXPECT_EQ(p.path(), env.dot_file().path);
    EXPECT_EQ(p.parent(), env.dot_file().parent);
    EXPECT_EQ(p.name(), env.dot_file().name);
    EXPECT_EQ(p.extension(), env.dot_file().extension);
    EXPECT_EQ(p.file_name(), env.dot_file().file_name);
}

TEST(Path, reset_DotFile2) {
    Path p;
    p.reset(env.dot_file_2().path);
    EXPECT_TRUE(p.valid());
    EXPECT_TRUE(p.exist());
    EXPECT_FALSE(p.is_dir());
    EXPECT_EQ(p.path(), env.dot_file_2().path);
    EXPECT_EQ(p.parent(), env.dot_file_2().parent);
    EXPECT_EQ(p.name(), env.dot_file_2().name);
    EXPECT_EQ(p.extension(), env.dot_file_2().extension);
    EXPECT_EQ(p.file_name(), env.dot_file_2().file_name);
}

TEST(Path, walk_NoRecursive) {
    Path p;
    p.reset(env.path().path);
    p.walk([](const Path& path) {
        if (path.extension() == "stp") {
            EXPECT_EQ(env.stp_file_table().count(path.path()), 1);
        }
        return 0;
    });
}

TEST(Path, walk_Recursive) {
    std::vector<Path> vec;
    {
        Path p;
        p.reset(env.path().path);
        vec.emplace_back(p);
        p.walk([&vec](const Path& path) {
            if (path.is_dir()) {
                vec.emplace_back(path);
            }
            return 0;
        });
    }
    size_t count = 0;
    for (const Path& p : vec) {
        p.walk([&count](const Path& path) {
            if (path.extension() == "stp") {
                count++;
                EXPECT_EQ(env.stp_file_table().count(path.path()), 1);
            }
            return 0;
        });
    }
    int stp_count_in_table = 0;
    for (const auto& stp : env.stp_file_table()) {
        Path p;
        p.reset(stp);
        if (p.extension() == "stp") {
            stp_count_in_table++;
        }
    }
    EXPECT_EQ(count, stp_count_in_table);
}
