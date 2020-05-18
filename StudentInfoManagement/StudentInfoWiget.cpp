#include "StudentInfoWiget.h"

StudentInfoWidget::StudentInfoWidget(QWidget* parent)
    : QWidget(parent)
    , stuNameLabel("������")
    , stuNumberLabel("ѧ�ţ�")
    , departmentNameLabel("ѧԺ��")
    , majorNameLabel("רҵ��")
    , genderLabel("�Ա�")
    , mailLabel("���䣺")
    , addressLabel("��ַ��")
    , phoneNumberLabel("��ϵ�绰��")
    , websiteLabel("��վ��")
    , birthLabel("�������£�")
    , nationalityLabel("���壺")
    , politicalOrientationLabel("������ò��")
    , postcodeLabel("�ʱࣺ")
    , enrollmentTimeLabel("��ѧʱ�䣺")
    , experienceLabel("������")
    , commentsLabel("��ע��")
    , avatarLabel("ͷ��")
{
    genderComboBox.addItem("Ů");
    genderComboBox.addItem("��");

    QPixmap icon("student.png");
	avatarIconLabel.setPixmap(icon);
	avatarIconLabel.resize(icon.width(), icon.height());

    // ����ӿؼ�
	leftLayout.pushWidgets({ &stuNameLabel,&stuNameEdit });
	leftLayout.pushWidgets({ &stuNumberLabel,&stuNumberEdit });
	leftLayout.pushWidgets({ &genderLabel,&genderComboBox });
	leftLayout.pushWidgets({ &departmentNameLabel,&departmentNameTextEdit });
	leftLayout.pushWidgets({ &majorNameLabel,&majorNameTextEdit });
    leftLayout.pushWidgets({ &mailLabel,&mailTextEdit });
    leftLayout.pushWidgets({ &addressLabel,&addressTextEdit });
    leftLayout.pushWidgets({ &websiteLabel,&websiteTextEdit });
    leftLayout.pushWidgets({ &birthLabel,&birthTextEdit });
    leftLayout.pushWidgets({ &nationalityLabel,&nationalityTextEdit });
    leftLayout.pushWidgets({ &politicalOrientationLabel,&politicalOrientationTextEdit });
    leftLayout.pushWidgets({ &postcodeLabel,&postcodeTextEdit });
    leftLayout.pushWidgets({ &enrollmentTimeLabel,&enrollmentTimeTextEdit });

    leftLayout.setColumnStretch(0, 1);
    leftLayout.setColumnStretch(1, 3);

	topRightLayout.setSpacing(20);
	topRightLayout.addWidget(&avatarLabel);
	topRightLayout.addWidget(&avatarIconLabel);

    rightLayout.setMargin(10);
    rightLayout.addLayout(&topRightLayout);
    rightLayout.addWidget(&experienceLabel);
    rightLayout.addWidget(&experienceTextEdit);
    rightLayout.addWidget(&commentsLabel);
    rightLayout.addWidget(&commentsTextEdit);

    auto mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(&leftLayout, 0, 0);
    mainLayout->addLayout(&rightLayout,0,1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

// ����ѧ����Ϣ
void StudentInfoWidget::stickStudent(const StudentInfo& stu)
{
    stuNameEdit.setText(stu.stuName);
    stuNumberEdit.setText(stu.stuNumber);
    departmentNameTextEdit.setText(stu.departmentName);
    majorNameTextEdit.setText(stu.majorName);
    classNameTextEdit.setText(stu.className);
    genderComboBox.setEditText(stu.gender);
    mailTextEdit.setText(stu.mail);
    addressTextEdit.setText(stu.address);
    phoneNumberTextEdit.setText(stu.phoneNumber);
    websiteTextEdit.setText(stu.website);
    birthTextEdit.setText(stu.birth);
    nationalityTextEdit.setText(stu.nationality);
    politicalOrientationTextEdit.setText(stu.politicalOrientation);
    postcodeTextEdit.setText(stu.postcode);
    enrollmentTimeTextEdit.setText(stu.enrollmentTime);
    experienceTextEdit.setText(stu.experience);
    commentsTextEdit.setText(stu.comments);

    QPixmap icon(stu.photo.isEmpty() ? "student.png" : stu.photo);
    avatarIconLabel.setPixmap(icon);
    avatarIconLabel.resize(icon.width(), icon.height());
}