#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QString>

class StudentInfo
{
    using string = QString;
public:
    string stuName;                 // ����
    string stuNumber;               // ѧ��
    string departmentName;          // ѧԺ
    string majorName;               // רҵ
    string className;               // �༶
    string gender;                  // �Ա�
    string mail;                    // ����
    string address;                 // ��ַ
    string phoneNumber;             // ��ϵ�绰
    string website;                 // ��վ
    string birth;                   // ��������
    string nationality;             // ����
    string politicalOrientation;    // ������ò
    string postcode;                // �ʱ�
    string enrollmentTime;          // ��ѧʱ��
    string experience;              // ����
    string comments;                // ��ע
    string photo;                   // ��Ƭ·��
};

#endif // STUDENTINFO_H
