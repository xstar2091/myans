#include <unistd.h>
#include <cstdio>
#include "myans/path.h"

#include "unittest_env.h"

bool UnitTestEnv::init(const std::string& unittest_dir_name) {
    char buf[4096] = {0};
    char* cwd = getcwd(buf, sizeof(buf));
    if (cwd == nullptr) {
        perror("get current working directory failed");
        return false;
    }
    path_ = UnitTestEnvPath{
        std::string(cwd) + "/" + unittest_dir_name,
        cwd,
        unittest_dir_name,
        "",
        unittest_dir_name,
    };

    std::string cmd;

    cmd = "rm -rf " + path_.path;
    if (system(cmd.c_str()) != 0) {
        perror("clean unittest temp directory failed");
        return false;
    }
    cmd = "mkdir " + path_.path;
    if (system(cmd.c_str()) != 0) {
        perror("create unittest temp directory failed");
        return false;
    }

    sub_dir_ = UnitTestEnvPath{
        path_.path + "/sub.dir",
        path_.path,
        "sub.dir",
        "",
        "sub.dir",
    };
    cmd = "mkdir " + sub_dir_.path;
    if (system(cmd.c_str()) != 0) {
        perror("create unittest sub directory failed");
        return false;
    }
    dot_dir_ = UnitTestEnvPath{
        path_.path + "/.dot_dir",
        path_.path,
        ".dot_dir",
        "",
        ".dot_dir",
    };
    cmd = "mkdir " + dot_dir_.path;
    if (system(cmd.c_str()) != 0) {
        perror("create unittest dot directory failed");
        return false;
    }
    dot_file_ = UnitTestEnvPath{
            path_.path + "/.dot_file.txt",
            path_.path,
            ".dot_file",
            "txt",
            ".dot_file.txt",
    };
    cmd = "echo 123 > " + dot_file_.path;
    if (system(cmd.c_str()) != 0) {
        perror("create unittest dot file failed");
        return false;
    }
    dot_file_2_ = UnitTestEnvPath{
            path_.path + "/.dot_file_2",
            path_.path,
            ".dot_file_2",
            "",
            ".dot_file_2",
    };
    cmd = "echo 456 > " + dot_file_2_.path;
    if (system(cmd.c_str()) != 0) {
        perror("create unittest dot file failed");
        return false;
    }

    stp_file_table_.clear();
    stp_new_file_table_.clear();
    stp_file_table_.insert(path_.path + "/a.txt");
    stp_file_table_.insert(path_.path + "/a.log");
    stp_file_table_.insert(path_.path + "/a.stp");
    stp_file_table_.insert(path_.path + "/b.stp");
    stp_file_table_.insert(path_.path + "/c.stp");
    stp_file_table_.insert(path_.path + "/d.stp");
    stp_file_table_.insert(path_.path + "/e.stp");
    stp_file_table_.insert(sub_dir_.path + "/aa.txt");
    stp_file_table_.insert(sub_dir_.path + "/aa.log");
    stp_file_table_.insert(sub_dir_.path + "/aa.stp");
    stp_file_table_.insert(sub_dir_.path + "/ab.stp");
    stp_file_table_.insert(sub_dir_.path + "/ac.stp");
    stp_file_table_.insert(sub_dir_.path + "/ad.stp");
    stp_file_table_.insert(sub_dir_.path + "/ae.stp");
    stp_new_file_table_.insert(path_.path + "/a-01.stp");
    stp_new_file_table_.insert(path_.path + "/b-02.stp");
    stp_new_file_table_.insert(path_.path + "/c-03.stp");
    stp_new_file_table_.insert(path_.path + "/d-04.stp");
    stp_new_file_table_.insert(path_.path + "/e-05.stp");
    stp_new_file_table_.insert(sub_dir_.path + "/aa-01.stp");
    stp_new_file_table_.insert(sub_dir_.path + "/ab-02.stp");
    stp_new_file_table_.insert(sub_dir_.path + "/ac-03.stp");
    stp_new_file_table_.insert(sub_dir_.path + "/ad-04.stp");
    stp_new_file_table_.insert(sub_dir_.path + "/ae-05.stp");
    for (const std::string& file : stp_file_table_) {
        cmd = "echo 111 > " + file;
        if (system(cmd.c_str()) != 0) {
            perror("create unittest stp file failed");
            return false;
        }
    }
    return true;
}

UnitTestEnv env;
