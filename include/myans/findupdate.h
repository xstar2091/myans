#ifndef MYANS_FINDUPDATE_H
#define MYANS_FINDUPDATE_H

#include <string>

class Findupdate {
public:
    // 不对原文件名进行排序，即原文件名为
    // a.stp, b.stp, c.stp, d.stp, e.stp
    // 重命名后一种可能的结果为
    // a-03.stp, b-05.stp, c-02.stp, d-04.stp, e-01.stp
    // 同一层级的stp文件，编号从-01开始，即给定目录存在编号为-01的文件，其每一个子目录中同样存在编号为-01的文件
    // 如果文件数量超过100，若想要a-001.stp, b-010.stp这种，可通过增加参数或环境变量实现
    bool checkFile(const std::string& filename);
    // 对原文件名进行字典排序然后再重命名，即原文件名为
    // a.stp, b.stp, c.stp, d.stp, e.stp
    // 重命名后结果为
    // a-01.stp, b-02.stp, c-03.stp, d-04.stp, e-05.stp
    // 同一层级的stp文件，编号从-01开始，即给定目录存在编号为-01的文件，其每一个子目录中同样存在编号为-01的文件
    // 如果文件数量超过100，若想要a-001.stp, b-010.stp这种，可通过增加参数或环境变量实现
    bool checkFile2(const std::string& filename);
    // 对原文件名进行字典排序然后再重命名，即原文件名为
    // a.stp, b.stp, c.stp, d.stp, e.stp
    // 重命名后结果为
    // a-01.stp, b-02.stp, c-03.stp, d-04.stp, e-05.stp
    // 所有stp文件，编号递增，即给定目录和所有子目录中只有一个编号为-01的文件
    bool checkFile3(const std::string& filename);
};


#endif //MYANS_FINDUPDATE_H
