#include "myans/findupdate.h"
#include <cerrno>
#include <cstdio>
#include <algorithm>
#include <vector>
#include "myans/path.h"

namespace {

int renamePath(const Path& old, int num) {
    char buf[16] = {0};
    snprintf(buf, sizeof(buf), "-%02d", num);
    Path newPath = old;
    newPath.setName(old.name() + buf);
    int ret = 0;
    if (rename(old.path().c_str(), newPath.path().c_str()) != 0) {
        ret = errno;
    }
    return ret;
}

const std::string  ext("stp");
int walkPath(bool recursive, int start, const Path& p) {
    return p.walk([recursive, &start](const Path& path) -> int {
        int ret = 0;
        if (path.extension() == ext) {
            ret = renamePath(path, start++);
        } else if (path.is_dir()) {
            ret = walkPath(recursive, 1, path);
        }
        return ret;
    });
}

int walkPath(bool recursive, const Path& p, std::vector<Path> pathList) {
    int ret = p.walk([recursive, &pathList](const Path& path) -> int {
        int ret = 0;
        if (path.extension() == ext) {
            pathList.emplace_back(path);
        } else if (path.is_dir()) {
            std::vector<Path> newPathList;
            ret = walkPath(recursive, path, newPathList);
        }
        return ret;
    });
    if (ret == 0) {
        std::sort(pathList.begin(), pathList.end(), [](const Path& left, const Path& right) {
            return left.name() < right.name();
        });
        int start = 1;
        for (auto& path : pathList) {
            ret = renamePath(path, start++);
            if (ret != 0) {
                break;
            }
        }
    }
    return ret;
}

}

bool Findupdate::checkFile(const std::string &filename) {
    Path p;
    p.reset(filename);
    if (!p.is_dir()) {
        return false;
    }
    return walkPath(true, 1, p) == 0;
}

bool Findupdate::checkFile2(const std::string &filename) {
    Path p;
    p.reset(filename);
    if (!p.is_dir()) {
        return false;
    }
    std::vector<Path> pathList;
    return walkPath(true, p, pathList) == 0;
}

bool Findupdate::checkFile3(const std::string &filename) {
    Path p;
    p.reset(filename);
    if (!p.is_dir()) {
        return false;
    }
    std::vector<Path> dirList = {p};
    p.walk([&dirList](const Path& p) -> int {
        if (p.is_dir()) {
            dirList.emplace_back(p);
        }
        return 0;
    });
    std::sort(dirList.begin(), dirList.end(), [](const Path& left, const Path& right) -> bool {
        return left.path() < right.path();
    });
    int start = 1;
    int ret = 0;
    std::vector<Path> stpList;
    for (const auto& path : dirList) {
        stpList.clear();
        ret = path.walk([&start, &stpList](const Path& p) -> int {
            if (p.extension() == ext) {
                stpList.emplace_back(p);
            }
            return 0;
        });
        if (ret != 0) {
            break;
        }
        std::sort(stpList.begin(), stpList.end(), [](const Path& left, const Path& right) {
            return left.path() < right.path();
        });
        for (const auto& old : stpList) {
            ret = renamePath(old, start++);
            if (ret != 0) {
                break;
            }
        }
        if (ret != 0) {
            break;
        }
    }
    return ret == 0;
}
