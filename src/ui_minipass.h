/********************************************************************************
** Form generated from reading UI file 'minipass.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIPASS_H
#define UI_MINIPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniPass
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBoxOptions;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *useCustomLabel;
    QLineEdit *useCustom;
    QLabel *makeMnemonicLabel;
    QCheckBox *makeMnemonic;
    QLabel *keepHistoryLabel;
    QCheckBox *keepHistory;
    QLabel *useSpecialLabel;
    QCheckBox *useSpecial;
    QCheckBox *useUppercase;
    QLabel *useLowercaseLabel;
    QCheckBox *useLowercase;
    QLabel *useNumbersLabel;
    QCheckBox *useNumbers;
    QLabel *defaultOptionsLabel;
    QCheckBox *defaultOptions;
    QLabel *passwordLengthLabel;
    QLineEdit *passwordLength;
    QLabel *useUppercaseLabel;
    QGroupBox *groupBoxOutput;
    QPlainTextEdit *randomPassword;
    QPushButton *copyPassword;
    QPushButton *clearPassword;
    QGroupBox *groupBoxActions;
    QToolButton *generatePassword;
    QToolButton *resetOptions;
    QToolButton *exitMinipass;
    QToolButton *openPasswordsHistory;

    void setupUi(QMainWindow *MiniPass)
    {
        if (MiniPass->objectName().isEmpty())
            MiniPass->setObjectName("MiniPass");
        MiniPass->setEnabled(true);
        MiniPass->resize(431, 251);
        MiniPass->setWindowTitle(QString::fromUtf8("minipass"));
        MiniPass->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        MiniPass->setAnimated(true);
        MiniPass->setDocumentMode(false);
        MiniPass->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MiniPass);
        centralwidget->setObjectName("centralwidget");
        groupBoxOptions = new QGroupBox(centralwidget);
        groupBoxOptions->setObjectName("groupBoxOptions");
        groupBoxOptions->setGeometry(QRect(10, 0, 241, 241));
        formLayoutWidget = new QWidget(groupBoxOptions);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 30, 221, 201));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setContentsMargins(0, 0, 0, 0);
        useCustomLabel = new QLabel(formLayoutWidget);
        useCustomLabel->setObjectName("useCustomLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, useCustomLabel);

        useCustom = new QLineEdit(formLayoutWidget);
        useCustom->setObjectName("useCustom");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(useCustom->sizePolicy().hasHeightForWidth());
        useCustom->setSizePolicy(sizePolicy);
        useCustom->setMaximumSize(QSize(60, 20));
        useCustom->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        useCustom->setAutoFillBackground(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, useCustom);

        makeMnemonicLabel = new QLabel(formLayoutWidget);
        makeMnemonicLabel->setObjectName("makeMnemonicLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, makeMnemonicLabel);

        makeMnemonic = new QCheckBox(formLayoutWidget);
        makeMnemonic->setObjectName("makeMnemonic");
        makeMnemonic->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(1, QFormLayout::FieldRole, makeMnemonic);

        keepHistoryLabel = new QLabel(formLayoutWidget);
        keepHistoryLabel->setObjectName("keepHistoryLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, keepHistoryLabel);

        keepHistory = new QCheckBox(formLayoutWidget);
        keepHistory->setObjectName("keepHistory");
        keepHistory->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(2, QFormLayout::FieldRole, keepHistory);

        useSpecialLabel = new QLabel(formLayoutWidget);
        useSpecialLabel->setObjectName("useSpecialLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, useSpecialLabel);

        useSpecial = new QCheckBox(formLayoutWidget);
        useSpecial->setObjectName("useSpecial");
        useSpecial->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(3, QFormLayout::FieldRole, useSpecial);

        useUppercase = new QCheckBox(formLayoutWidget);
        useUppercase->setObjectName("useUppercase");
        useUppercase->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(4, QFormLayout::FieldRole, useUppercase);

        useLowercaseLabel = new QLabel(formLayoutWidget);
        useLowercaseLabel->setObjectName("useLowercaseLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, useLowercaseLabel);

        useLowercase = new QCheckBox(formLayoutWidget);
        useLowercase->setObjectName("useLowercase");
        useLowercase->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(5, QFormLayout::FieldRole, useLowercase);

        useNumbersLabel = new QLabel(formLayoutWidget);
        useNumbersLabel->setObjectName("useNumbersLabel");

        formLayout->setWidget(6, QFormLayout::LabelRole, useNumbersLabel);

        useNumbers = new QCheckBox(formLayoutWidget);
        useNumbers->setObjectName("useNumbers");
        useNumbers->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(6, QFormLayout::FieldRole, useNumbers);

        defaultOptionsLabel = new QLabel(formLayoutWidget);
        defaultOptionsLabel->setObjectName("defaultOptionsLabel");

        formLayout->setWidget(7, QFormLayout::LabelRole, defaultOptionsLabel);

        defaultOptions = new QCheckBox(formLayoutWidget);
        defaultOptions->setObjectName("defaultOptions");
        defaultOptions->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        formLayout->setWidget(7, QFormLayout::FieldRole, defaultOptions);

        passwordLengthLabel = new QLabel(formLayoutWidget);
        passwordLengthLabel->setObjectName("passwordLengthLabel");

        formLayout->setWidget(8, QFormLayout::LabelRole, passwordLengthLabel);

        passwordLength = new QLineEdit(formLayoutWidget);
        passwordLength->setObjectName("passwordLength");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(passwordLength->sizePolicy().hasHeightForWidth());
        passwordLength->setSizePolicy(sizePolicy1);
        passwordLength->setMaximumSize(QSize(60, 20));
        passwordLength->setAutoFillBackground(true);

        formLayout->setWidget(8, QFormLayout::FieldRole, passwordLength);

        useUppercaseLabel = new QLabel(formLayoutWidget);
        useUppercaseLabel->setObjectName("useUppercaseLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, useUppercaseLabel);

        groupBoxOutput = new QGroupBox(centralwidget);
        groupBoxOutput->setObjectName("groupBoxOutput");
        groupBoxOutput->setGeometry(QRect(260, 150, 161, 91));
        randomPassword = new QPlainTextEdit(groupBoxOutput);
        randomPassword->setObjectName("randomPassword");
        randomPassword->setGeometry(QRect(10, 50, 141, 31));
        copyPassword = new QPushButton(groupBoxOutput);
        copyPassword->setObjectName("copyPassword");
        copyPassword->setGeometry(QRect(90, 20, 41, 21));
        clearPassword = new QPushButton(groupBoxOutput);
        clearPassword->setObjectName("clearPassword");
        clearPassword->setGeometry(QRect(30, 20, 41, 21));
        groupBoxActions = new QGroupBox(centralwidget);
        groupBoxActions->setObjectName("groupBoxActions");
        groupBoxActions->setGeometry(QRect(260, 0, 161, 151));
        generatePassword = new QToolButton(groupBoxActions);
        generatePassword->setObjectName("generatePassword");
        generatePassword->setGeometry(QRect(10, 20, 141, 21));
        resetOptions = new QToolButton(groupBoxActions);
        resetOptions->setObjectName("resetOptions");
        resetOptions->setGeometry(QRect(10, 80, 141, 22));
        exitMinipass = new QToolButton(groupBoxActions);
        exitMinipass->setObjectName("exitMinipass");
        exitMinipass->setGeometry(QRect(10, 110, 141, 22));
        openPasswordsHistory = new QToolButton(groupBoxActions);
        openPasswordsHistory->setObjectName("openPasswordsHistory");
        openPasswordsHistory->setGeometry(QRect(10, 50, 141, 21));
        MiniPass->setCentralWidget(centralwidget);

        retranslateUi(MiniPass);

        QMetaObject::connectSlotsByName(MiniPass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniPass)
    {
        groupBoxOptions->setTitle(QCoreApplication::translate("MiniPass", "Options", nullptr));
        useCustomLabel->setText(QCoreApplication::translate("MiniPass", "Remove Custom Characters", nullptr));
        makeMnemonicLabel->setText(QCoreApplication::translate("MiniPass", "Make Mnemonic", nullptr));
        makeMnemonic->setText(QString());
        keepHistoryLabel->setText(QCoreApplication::translate("MiniPass", "Keep History", nullptr));
        keepHistory->setText(QString());
        useSpecialLabel->setText(QCoreApplication::translate("MiniPass", "Remove Special Characters", nullptr));
        useSpecial->setText(QString());
        useUppercase->setText(QString());
        useLowercaseLabel->setText(QCoreApplication::translate("MiniPass", "Remove Lowercase Letters", nullptr));
        useLowercase->setText(QString());
        useNumbersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Numbers", nullptr));
        useNumbers->setText(QString());
        defaultOptionsLabel->setText(QCoreApplication::translate("MiniPass", "Default Options", nullptr));
        defaultOptions->setText(QString());
        passwordLengthLabel->setText(QCoreApplication::translate("MiniPass", "Password Length", nullptr));
        useUppercaseLabel->setText(QCoreApplication::translate("MiniPass", "Remove Uppercase Letters", nullptr));
        groupBoxOutput->setTitle(QCoreApplication::translate("MiniPass", "Output", nullptr));
        copyPassword->setText(QCoreApplication::translate("MiniPass", "Copy", nullptr));
        clearPassword->setText(QCoreApplication::translate("MiniPass", "Clear", nullptr));
        groupBoxActions->setTitle(QCoreApplication::translate("MiniPass", "Actions", nullptr));
        generatePassword->setText(QCoreApplication::translate("MiniPass", "Generate Password", nullptr));
        resetOptions->setText(QCoreApplication::translate("MiniPass", "Reset Options", nullptr));
        exitMinipass->setText(QCoreApplication::translate("MiniPass", "Close Application", nullptr));
        openPasswordsHistory->setText(QCoreApplication::translate("MiniPass", "Open Passwords History", nullptr));
        (void)MiniPass;
    } // retranslateUi

};

namespace Ui {
    class MiniPass: public Ui_MiniPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPASS_H
