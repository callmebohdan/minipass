/********************************************************************************
** Form generated from reading UI file 'minipass.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIPASS_H
#define UI_MINIPASS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniPass
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QGroupBox *groupBoxOptions;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *LabelRemoveCustomCharacters;
    QLineEdit *LineEditPasswordLength;
    QLabel *LabelMakeMnemonic;
    QCheckBox *checkBoxMakeMnemonic;
    QLabel *LabelKeepHistory;
    QCheckBox *checkBoxKeepHistory;
    QLabel *LabelRemoveSpecialCharacters;
    QCheckBox *checkBoxRemoveSpecialCharacters;
    QLabel *LabelRemoveUppercaseLetters;
    QCheckBox *checkBoxRemoveUppercaseLetters;
    QLabel *LabelRemoveLowercaseLetters;
    QCheckBox *checkBoxRemoveLowercaseLetters;
    QLabel *LabelRemoveNumbers;
    QCheckBox *checkBoxRemoveNumbers;
    QLabel *LabelDefaultOptions;
    QCheckBox *checkBoxDefaultOptions;
    QLabel *LabelPasswordLength;
    QLineEdit *LineEditRemoveCustomCharacters;
    QGroupBox *groupBoxOutput;
    QPlainTextEdit *plainTextEditRandomPassword;
    QLabel *labelRandomPassword;
    QLabel *labelLogMessage;
    QPlainTextEdit *plainTextEditLogMessage;
    QGroupBox *groupBoxActions;
    QToolButton *toolButtonGenerate;
    QToolButton *toolButtonReset;
    QToolButton *toolButtonExit;
    QToolButton *toolButtonOpenPasswordsHistory;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MiniPass)
    {
        if (MiniPass->objectName().isEmpty())
            MiniPass->setObjectName("MiniPass");
        MiniPass->setEnabled(true);
        MiniPass->resize(529, 365);
        MiniPass->setWindowTitle(QString::fromUtf8("minipass"));
        MiniPass->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        MiniPass->setAnimated(true);
        MiniPass->setDocumentMode(false);
        MiniPass->setUnifiedTitleAndToolBarOnMac(false);
        actionExit = new QAction(MiniPass);
        actionExit->setObjectName("actionExit");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MiniPass);
        centralwidget->setObjectName("centralwidget");
        groupBoxOptions = new QGroupBox(centralwidget);
        groupBoxOptions->setObjectName("groupBoxOptions");
        groupBoxOptions->setGeometry(QRect(10, 10, 281, 241));
        formLayoutWidget = new QWidget(groupBoxOptions);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 20, 261, 211));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setContentsMargins(0, 0, 0, 0);
        LabelRemoveCustomCharacters = new QLabel(formLayoutWidget);
        LabelRemoveCustomCharacters->setObjectName("LabelRemoveCustomCharacters");

        formLayout->setWidget(0, QFormLayout::LabelRole, LabelRemoveCustomCharacters);

        LineEditPasswordLength = new QLineEdit(formLayoutWidget);
        LineEditPasswordLength->setObjectName("LineEditPasswordLength");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LineEditPasswordLength->sizePolicy().hasHeightForWidth());
        LineEditPasswordLength->setSizePolicy(sizePolicy);
        LineEditPasswordLength->setMaximumSize(QSize(60, 20));
        LineEditPasswordLength->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        LineEditPasswordLength->setAutoFillBackground(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEditPasswordLength);

        LabelMakeMnemonic = new QLabel(formLayoutWidget);
        LabelMakeMnemonic->setObjectName("LabelMakeMnemonic");

        formLayout->setWidget(1, QFormLayout::LabelRole, LabelMakeMnemonic);

        checkBoxMakeMnemonic = new QCheckBox(formLayoutWidget);
        checkBoxMakeMnemonic->setObjectName("checkBoxMakeMnemonic");

        formLayout->setWidget(1, QFormLayout::FieldRole, checkBoxMakeMnemonic);

        LabelKeepHistory = new QLabel(formLayoutWidget);
        LabelKeepHistory->setObjectName("LabelKeepHistory");

        formLayout->setWidget(2, QFormLayout::LabelRole, LabelKeepHistory);

        checkBoxKeepHistory = new QCheckBox(formLayoutWidget);
        checkBoxKeepHistory->setObjectName("checkBoxKeepHistory");

        formLayout->setWidget(2, QFormLayout::FieldRole, checkBoxKeepHistory);

        LabelRemoveSpecialCharacters = new QLabel(formLayoutWidget);
        LabelRemoveSpecialCharacters->setObjectName("LabelRemoveSpecialCharacters");

        formLayout->setWidget(3, QFormLayout::LabelRole, LabelRemoveSpecialCharacters);

        checkBoxRemoveSpecialCharacters = new QCheckBox(formLayoutWidget);
        checkBoxRemoveSpecialCharacters->setObjectName("checkBoxRemoveSpecialCharacters");

        formLayout->setWidget(3, QFormLayout::FieldRole, checkBoxRemoveSpecialCharacters);

        LabelRemoveUppercaseLetters = new QLabel(formLayoutWidget);
        LabelRemoveUppercaseLetters->setObjectName("LabelRemoveUppercaseLetters");

        formLayout->setWidget(4, QFormLayout::LabelRole, LabelRemoveUppercaseLetters);

        checkBoxRemoveUppercaseLetters = new QCheckBox(formLayoutWidget);
        checkBoxRemoveUppercaseLetters->setObjectName("checkBoxRemoveUppercaseLetters");

        formLayout->setWidget(4, QFormLayout::FieldRole, checkBoxRemoveUppercaseLetters);

        LabelRemoveLowercaseLetters = new QLabel(formLayoutWidget);
        LabelRemoveLowercaseLetters->setObjectName("LabelRemoveLowercaseLetters");

        formLayout->setWidget(5, QFormLayout::LabelRole, LabelRemoveLowercaseLetters);

        checkBoxRemoveLowercaseLetters = new QCheckBox(formLayoutWidget);
        checkBoxRemoveLowercaseLetters->setObjectName("checkBoxRemoveLowercaseLetters");

        formLayout->setWidget(5, QFormLayout::FieldRole, checkBoxRemoveLowercaseLetters);

        LabelRemoveNumbers = new QLabel(formLayoutWidget);
        LabelRemoveNumbers->setObjectName("LabelRemoveNumbers");

        formLayout->setWidget(6, QFormLayout::LabelRole, LabelRemoveNumbers);

        checkBoxRemoveNumbers = new QCheckBox(formLayoutWidget);
        checkBoxRemoveNumbers->setObjectName("checkBoxRemoveNumbers");

        formLayout->setWidget(6, QFormLayout::FieldRole, checkBoxRemoveNumbers);

        LabelDefaultOptions = new QLabel(formLayoutWidget);
        LabelDefaultOptions->setObjectName("LabelDefaultOptions");

        formLayout->setWidget(7, QFormLayout::LabelRole, LabelDefaultOptions);

        checkBoxDefaultOptions = new QCheckBox(formLayoutWidget);
        checkBoxDefaultOptions->setObjectName("checkBoxDefaultOptions");

        formLayout->setWidget(7, QFormLayout::FieldRole, checkBoxDefaultOptions);

        LabelPasswordLength = new QLabel(formLayoutWidget);
        LabelPasswordLength->setObjectName("LabelPasswordLength");

        formLayout->setWidget(8, QFormLayout::LabelRole, LabelPasswordLength);

        LineEditRemoveCustomCharacters = new QLineEdit(formLayoutWidget);
        LineEditRemoveCustomCharacters->setObjectName("LineEditRemoveCustomCharacters");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LineEditRemoveCustomCharacters->sizePolicy().hasHeightForWidth());
        LineEditRemoveCustomCharacters->setSizePolicy(sizePolicy1);
        LineEditRemoveCustomCharacters->setMaximumSize(QSize(60, 20));
        LineEditRemoveCustomCharacters->setAutoFillBackground(true);

        formLayout->setWidget(8, QFormLayout::FieldRole, LineEditRemoveCustomCharacters);

        groupBoxOutput = new QGroupBox(centralwidget);
        groupBoxOutput->setObjectName("groupBoxOutput");
        groupBoxOutput->setGeometry(QRect(10, 250, 511, 91));
        plainTextEditRandomPassword = new QPlainTextEdit(groupBoxOutput);
        plainTextEditRandomPassword->setObjectName("plainTextEditRandomPassword");
        plainTextEditRandomPassword->setGeometry(QRect(150, 30, 411, 21));
        labelRandomPassword = new QLabel(groupBoxOutput);
        labelRandomPassword->setObjectName("labelRandomPassword");
        labelRandomPassword->setGeometry(QRect(10, 30, 131, 16));
        labelLogMessage = new QLabel(groupBoxOutput);
        labelLogMessage->setObjectName("labelLogMessage");
        labelLogMessage->setGeometry(QRect(10, 60, 131, 16));
        plainTextEditLogMessage = new QPlainTextEdit(groupBoxOutput);
        plainTextEditLogMessage->setObjectName("plainTextEditLogMessage");
        plainTextEditLogMessage->setGeometry(QRect(150, 60, 411, 21));
        groupBoxActions = new QGroupBox(centralwidget);
        groupBoxActions->setObjectName("groupBoxActions");
        groupBoxActions->setGeometry(QRect(300, 10, 221, 241));
        toolButtonGenerate = new QToolButton(groupBoxActions);
        toolButtonGenerate->setObjectName("toolButtonGenerate");
        toolButtonGenerate->setGeometry(QRect(10, 30, 201, 21));
        toolButtonReset = new QToolButton(groupBoxActions);
        toolButtonReset->setObjectName("toolButtonReset");
        toolButtonReset->setGeometry(QRect(10, 90, 201, 22));
        toolButtonExit = new QToolButton(groupBoxActions);
        toolButtonExit->setObjectName("toolButtonExit");
        toolButtonExit->setGeometry(QRect(10, 120, 201, 22));
        toolButtonOpenPasswordsHistory = new QToolButton(groupBoxActions);
        toolButtonOpenPasswordsHistory->setObjectName("toolButtonOpenPasswordsHistory");
        toolButtonOpenPasswordsHistory->setGeometry(QRect(10, 60, 201, 21));
        MiniPass->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MiniPass);
        toolBar->setObjectName("toolBar");
        MiniPass->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addSeparator();

        retranslateUi(MiniPass);

        QMetaObject::connectSlotsByName(MiniPass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniPass)
    {
        actionExit->setText(QCoreApplication::translate("MiniPass", "Exit", nullptr));
        groupBoxOptions->setTitle(QCoreApplication::translate("MiniPass", "Options", nullptr));
        LabelRemoveCustomCharacters->setText(QCoreApplication::translate("MiniPass", "Remove Custom Characters", nullptr));
        LabelMakeMnemonic->setText(QCoreApplication::translate("MiniPass", "Make Mnemonic", nullptr));
        checkBoxMakeMnemonic->setText(QString());
        LabelKeepHistory->setText(QCoreApplication::translate("MiniPass", "Keep History", nullptr));
        checkBoxKeepHistory->setText(QString());
        LabelRemoveSpecialCharacters->setText(QCoreApplication::translate("MiniPass", "Remove Special Characters", nullptr));
        checkBoxRemoveSpecialCharacters->setText(QString());
        LabelRemoveUppercaseLetters->setText(QCoreApplication::translate("MiniPass", "Remove Uppercase Letters", nullptr));
        checkBoxRemoveUppercaseLetters->setText(QString());
        LabelRemoveLowercaseLetters->setText(QCoreApplication::translate("MiniPass", "Remove Lowercase Letters", nullptr));
        checkBoxRemoveLowercaseLetters->setText(QString());
        LabelRemoveNumbers->setText(QCoreApplication::translate("MiniPass", "Remove Numbers", nullptr));
        checkBoxRemoveNumbers->setText(QString());
        LabelDefaultOptions->setText(QCoreApplication::translate("MiniPass", "Default Options", nullptr));
        checkBoxDefaultOptions->setText(QString());
        LabelPasswordLength->setText(QCoreApplication::translate("MiniPass", "Password Length", nullptr));
        groupBoxOutput->setTitle(QCoreApplication::translate("MiniPass", "Output", nullptr));
        labelRandomPassword->setText(QCoreApplication::translate("MiniPass", "Random Password", nullptr));
        labelLogMessage->setText(QCoreApplication::translate("MiniPass", "Log Message", nullptr));
        groupBoxActions->setTitle(QCoreApplication::translate("MiniPass", "Actions", nullptr));
        toolButtonGenerate->setText(QCoreApplication::translate("MiniPass", "Generate Password", nullptr));
        toolButtonReset->setText(QCoreApplication::translate("MiniPass", "Reset Options", nullptr));
        toolButtonExit->setText(QCoreApplication::translate("MiniPass", "Close Application", nullptr));
        toolButtonOpenPasswordsHistory->setText(QCoreApplication::translate("MiniPass", "Open PasswordsHistory.csv", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MiniPass", "toolBar", nullptr));
        (void)MiniPass;
    } // retranslateUi

};

namespace Ui {
    class MiniPass: public Ui_MiniPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPASS_H
