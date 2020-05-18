#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QString>

class StudentInfo
{
    using string = QString;
public:
    string stuName;                 // 姓名
    string stuNumber;               // 学号
    string departmentName;          // 学院
    string majorName;               // 专业
    string className;               // 班级
    string gender;                  // 性别
    string mail;                    // 邮箱
    string address;                 // 地址
    string phoneNumber;             // 联系电话
    string website;                 // 网站
    string birth;                   // 出生日期
    string nationality;             // 民族
    string politicalOrientation;    // 政治面貌
    string postcode;                // 邮编
    string enrollmentTime;          // 入学时间
    string experience;              // 经历
    string comments;                // 备注
    string photo;                   // 照片路径
};

#endif // STUDENTINFO_H
