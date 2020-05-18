#ifndef STUDENTINFOWIGET_H
#define STUDENTINFOWIGET_H

#include "StudentInfo.h"
#include "GridLayoutTemplate.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>

#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")   //解决 VS编译器下中文乱码
#endif

class StudentInfoWidget : public QWidget
{
    Q_OBJECT
protected:
    /// Label
    QLabel stuNameLabel;         // 姓名
    QLabel stuNumberLabel;       // 学号
    QLabel departmentNameLabel;  // 学院
    QLabel majorNameLabel;       // 专业
    QLabel classNameLabel;       // 班级
    QLabel genderLabel;          // 性别
    QLabel mailLabel;            // 邮箱
    QLabel addressLabel;         // 地址
    QLabel phoneNumberLabel;     // 联系电话
    QLabel websiteLabel;         // 网站
    QLabel birthLabel;           // 出生日期
    QLabel nationalityLabel;     // 民族
    QLabel politicalOrientationLabel;    // 政治面貌
    QLabel postcodeLabel;        // 邮编
    QLabel enrollmentTimeLabel;  // 入学时间
    QLabel experienceLabel;      // 经历
    QLabel commentsLabel;        // 备注
    QLabel avatarLabel;          // 头像
    QLabel avatarIconLabel;

    /// Edit
    QLineEdit stuNameEdit;         // 姓名
    QLineEdit stuNumberEdit;       // 学号
    QLineEdit departmentNameTextEdit;  // 学院
    QLineEdit majorNameTextEdit;       // 专业
    QLineEdit classNameTextEdit;       // 班级
    QComboBox genderComboBox;          // 性别
    QLineEdit mailTextEdit;            // 邮箱
    QLineEdit addressTextEdit;         // 地址
    QLineEdit phoneNumberTextEdit;     // 联系电话
    QLineEdit websiteTextEdit;         // 网站
    QLineEdit birthTextEdit;           // 出生日期
    QLineEdit nationalityTextEdit;     // 民族
    QLineEdit politicalOrientationTextEdit;    // 政治面貌
    QLineEdit postcodeTextEdit;        // 邮编
    QLineEdit enrollmentTimeTextEdit;  // 入学时间
    QTextEdit experienceTextEdit;      // 经历
    QTextEdit commentsTextEdit;        // 备注


    // Layout
    GridLayoutTemplate leftLayout;
    QVBoxLayout rightLayout;
    QHBoxLayout topRightLayout; 
public:
    explicit StudentInfoWidget(QWidget* parent = nullptr);
    void stickStudent(const StudentInfo&);
signals:

};

#endif // STUDENTINFOWIGET_H
