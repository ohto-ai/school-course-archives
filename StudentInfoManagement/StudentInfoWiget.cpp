#include "StudentInfoWiget.h"

StudentInfoWidget::StudentInfoWidget(QWidget* parent)
    : QWidget(parent)
    , stuNameLabel("姓名：")
    , stuNumberLabel("学号：")
    , departmentNameLabel("学院：")
    , majorNameLabel("专业：")
    , genderLabel("性别：")
    , mailLabel("邮箱：")
    , addressLabel("地址：")
    , phoneNumberLabel("联系电话：")
    , websiteLabel("网站：")
    , birthLabel("出生年月：")
    , nationalityLabel("民族：")
    , politicalOrientationLabel("政治面貌：")
    , postcodeLabel("邮编：")
    , enrollmentTimeLabel("入学时间：")
    , experienceLabel("经历：")
    , commentsLabel("备注：")
    , avatarLabel("头像")
{
    genderComboBox.addItem("女");
    genderComboBox.addItem("男");

    QPixmap icon("student.png");
	avatarIconLabel.setPixmap(icon);
	avatarIconLabel.resize(icon.width(), icon.height());

    // 添加子控件
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

// 设置学生信息
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