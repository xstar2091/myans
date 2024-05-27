#ifndef MYANS_UNITTEST_ENV_H
#define MYANS_UNITTEST_ENV_H

#include <string>
#include <set>

struct UnitTestEnvPath {
    std::string path;
    std::string parent;
    std::string name;
    std::string extension;
    std::string file_name;
};

class UnitTestEnv {
public:
    bool init(const std::string& unittest_dir_name = "unittest_temp_dir");

    const UnitTestEnvPath& path() const { return path_; }
    const UnitTestEnvPath& sub_dir() const { return sub_dir_; }
    const UnitTestEnvPath& dot_dir() const { return dot_dir_; }
    const UnitTestEnvPath& dot_file() const { return dot_file_; }
    const UnitTestEnvPath& dot_file_2() const { return dot_file_2_; }
    const std::set<std::string>& stp_file_table() const { return stp_file_table_; };
    const std::set<std::string>& stp_new_file_table() const { return stp_new_file_table_; };

private:
    // 单元测试根目录，路径为${PWD}/unittest_temp_dir
    UnitTestEnvPath path_;
    // 子目录
    UnitTestEnvPath sub_dir_;
    // 隐藏目录，目录名为.dot_dir
    UnitTestEnvPath dot_dir_;
    // 隐藏文件，文件名为.dot_file.txt
    UnitTestEnvPath dot_file_;
    // 隐藏文件，文件名为.dot_file_2
    UnitTestEnvPath dot_file_2_;
    // stp文件
    std::set<std::string> stp_file_table_;
    std::set<std::string> stp_new_file_table_;
};


#endif //MYANS_UNITTEST_ENV_H
