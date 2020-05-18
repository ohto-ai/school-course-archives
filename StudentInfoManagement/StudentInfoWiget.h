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
#pragma execution_character_set("utf-8")   //��� VS����������������
#endif

class StudentInfoWidget : public QWidget
{
    Q_OBJECT
protected:
    /// Label
    QLabel stuNameLabel;         // ����
    QLabel stuNumberLabel;       // ѧ��
    QLabel departmentNameLabel;  // ѧԺ
    QLabel majorNameLabel;       // רҵ
    QLabel classNameLabel;       // �༶
    QLabel genderLabel;          // �Ա�
    QLabel mailLabel;            // ����
    QLabel addressLabel;         // ��ַ
    QLabel phoneNumberLabel;     // ��ϵ�绰
    QLabel websiteLabel;         // ��վ
    QLabel birthLabel;           // ��������
    QLabel nationalityLabel;     // ����
    QLabel politicalOrientationLabel;    // ������ò
    QLabel postcodeLabel;        // �ʱ�
    QLabel enrollmentTimeLabel;  // ��ѧʱ��
    QLabel experienceLabel;      // ����
    QLabel commentsLabel;        // ��ע
    QLabel avatarLabel;          // ͷ��
    QLabel avatarIconLabel;

    /// Edit
    QLineEdit stuNameEdit;         // ����
    QLineEdit stuNumberEdit;       // ѧ��
    QLineEdit departmentNameTextEdit;  // ѧԺ
    QLineEdit majorNameTextEdit;       // רҵ
    QLineEdit classNameTextEdit;       // �༶
    QComboBox genderComboBox;          // �Ա�
    QLineEdit mailTextEdit;            // ����
    QLineEdit addressTextEdit;         // ��ַ
    QLineEdit phoneNumberTextEdit;     // ��ϵ�绰
    QLineEdit websiteTextEdit;         // ��վ
    QLineEdit birthTextEdit;           // ��������
    QLineEdit nationalityTextEdit;     // ����
    QLineEdit politicalOrientationTextEdit;    // ������ò
    QLineEdit postcodeTextEdit;        // �ʱ�
    QLineEdit enrollmentTimeTextEdit;  // ��ѧʱ��
    QTextEdit experienceTextEdit;      // ����
    QTextEdit commentsTextEdit;        // ��ע


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
