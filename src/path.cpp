#include "myans/path.h"
#include <dirent.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>

#define DEFAULT_FULL_PATH_MAX 4096
#define FULL_PATH_MAX_ENV_KEY "FULL_PATH_MAX"

class PathLimits {
public:
    PathLimits();

public:
    static int full_path_max;
};
int PathLimits::full_path_max = DEFAULT_FULL_PATH_MAX;
PathLimits::PathLimits() {
    char* val = getenv(FULL_PATH_MAX_ENV_KEY);
    if (val != nullptr) {
        full_path_max = atoi(val);
    }
    if (full_path_max <= 0) {
        full_path_max = DEFAULT_FULL_PATH_MAX;
    }
}
static PathLimits path_limits;

void Path::reset() {
    valid_ = false;
    exist_ = false;
    is_dir_ = false;
    path_ = "";
    parent_ = "";
    name_ = "";
    extension_ = "";
    file_name_ = "";
}

void Path::reset(const std::string &path_str) {
    reset();
    if (!getAbsPath(path_str)) return;
    valid_ = true;
    const char* head = path_.c_str();
    const char* tail = strrchr(head, '/');
    if (head == tail) {
        exist_ = true;
        is_dir_ = true;
        return;
    }
    parent_.assign(head, tail);
    head = tail + 1;
    file_name_.assign(head);
    tail = strrchr(head, '.');
    if (tail == nullptr || head == tail) {
        name_.assign(head);
    } else {
        name_.assign(head, tail);
        extension_.assign(tail + 1);
    }
    struct stat buf{};
    if (lstat(path_.c_str(), &buf) == 0) {
        exist_ = true;
        is_dir_ = S_ISDIR(buf.st_mode);
    }
    if (is_dir_) {
        name_ = file_name_;
        extension_ = "";
    }
}

bool Path::getAbsPath(const std::string &path_str) {
    bool result = false;
    char* abs = new char[PathLimits::full_path_max + 1];
    if (realpath(path_str.c_str(), abs) != nullptr) {
        path_.assign(abs);
        result = true;
    }
    delete[] abs;
    return result;
}

void Path::setName(const std::string &name) {
    if (name_ == name) return;
    name_ = name;
    file_name_ = name_ + "." + extension_;
    path_ = parent_ + "/" + file_name_;
}

int  Path::walk(const std::function<int(const Path &)> &callback) const {
    if (!is_dir_) {
        return 0;
    }
    DIR* dir = opendir(path_.c_str());
    if (dir == nullptr) {
        return errno;
    }
    int ret = 0;
    dirent *entry = nullptr;
    while (ret == 0 && (entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        Path p;
        p.reset(path_ + "/" + entry->d_name);
        ret = callback(p);
    }
    closedir(dir);
    return ret;
}
