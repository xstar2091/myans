#ifndef MYANS_PATH_H
#define MYANS_PATH_H

#include <functional>
#include <string>

class Path {
public:
    void reset();
    void reset(const std::string& path_str);
    void setName(const std::string& name);
    int  walk(const std::function<int(const Path&)>& callback) const;

public:
    bool valid() const { return valid_; }
    bool is_dir() const { return is_dir_; }
    bool exist() const { return exist_; }
    const std::string& path() const { return path_; }
    const std::string& parent() const { return parent_; }
    const std::string& name() const { return name_; }
    const std::string& extension() const { return extension_; }
    const std::string& file_name() const { return file_name_; }

private:
    bool getAbsPath(const std::string& path_str);

private:
    bool valid_;
    bool exist_;
    bool is_dir_;
    std::string path_;
    std::string parent_;
    std::string name_;
    std::string extension_;
    std::string file_name_;
};


#endif //MYANS_PATH_H
