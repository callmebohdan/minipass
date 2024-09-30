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
    QLabel *removeCustomCharactersLabel;
    QLineEdit *removeCustomCharacters;
    QLabel *makeMnemonicLabel;
    QCheckBox *makeMnemonic;
    QLabel *keepHistoryLabel;
    QCheckBox *keepHistory;
    QLabel *removeSpecialCharactersLabel;
    QCheckBox *removeSpecialCharacters;
    QLabel *removeUppercaseLettersLabel;
    QCheckBox *removeUppercaseLetters;
    QLabel *removeLowercaseLettersLabel;
    QCheckBox *removeLowercaseLetters;
    QLabel *removeNumbersLabel;
    QCheckBox *removeNumbers;
    QLabel *defaultOptionsLabel;
    QCheckBox *defaultOptions;
    QLabel *passwordLengthLabel;
    QLineEdit *passwordLength;
    QGroupBox *groupBoxOutput;
    QPlainTextEdit *randomPassword;
    QLabel *randomPasswordLabel;
    QLabel *logMessageLabel;
    QPlainTextEdit *logMessage;
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
        removeCustomCharactersLabel = new QLabel(formLayoutWidget);
        removeCustomCharactersLabel->setObjectName("removeCustomCharactersLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, removeCustomCharactersLabel);

        removeCustomCharacters = new QLineEdit(formLayoutWidget);
        removeCustomCharacters->setObjectName("removeCustomCharacters");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(removeCustomCharacters->sizePolicy().hasHeightForWidth());
        removeCustomCharacters->setSizePolicy(sizePolicy);
        removeCustomCharacters->setMaximumSize(QSize(60, 20));
        removeCustomCharacters->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        removeCustomCharacters->setAutoFillBackground(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, removeCustomCharacters);

        makeMnemonicLabel = new QLabel(formLayoutWidget);
        makeMnemonicLabel->setObjectName("makeMnemonicLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, makeMnemonicLabel);

        makeMnemonic = new QCheckBox(formLayoutWidget);
        makeMnemonic->setObjectName("makeMnemonic");

        formLayout->setWidget(1, QFormLayout::FieldRole, makeMnemonic);

        keepHistoryLabel = new QLabel(formLayoutWidget);
        keepHistoryLabel->setObjectName("keepHistoryLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, keepHistoryLabel);

        keepHistory = new QCheckBox(formLayoutWidget);
        keepHistory->setObjectName("keepHistory");

        formLayout->setWidget(2, QFormLayout::FieldRole, keepHistory);

        removeSpecialCharactersLabel = new QLabel(formLayoutWidget);
        removeSpecialCharactersLabel->setObjectName("removeSpecialCharactersLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, removeSpecialCharactersLabel);

        removeSpecialCharacters = new QCheckBox(formLayoutWidget);
        removeSpecialCharacters->setObjectName("removeSpecialCharacters");

        formLayout->setWidget(3, QFormLayout::FieldRole, removeSpecialCharacters);

        removeUppercaseLettersLabel = new QLabel(formLayoutWidget);
        removeUppercaseLettersLabel->setObjectName("removeUppercaseLettersLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, removeUppercaseLettersLabel);

        removeUppercaseLetters = new QCheckBox(formLayoutWidget);
        removeUppercaseLetters->setObjectName("removeUppercaseLetters");

        formLayout->setWidget(4, QFormLayout::FieldRole, removeUppercaseLetters);

        removeLowercaseLettersLabel = new QLabel(formLayoutWidget);
        removeLowercaseLettersLabel->setObjectName("removeLowercaseLettersLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, removeLowercaseLettersLabel);

        removeLowercaseLetters = new QCheckBox(formLayoutWidget);
        removeLowercaseLetters->setObjectName("removeLowercaseLetters");

        formLayout->setWidget(5, QFormLayout::FieldRole, removeLowercaseLetters);

        removeNumbersLabel = new QLabel(formLayoutWidget);
        removeNumbersLabel->setObjectName("removeNumbersLabel");

        formLayout->setWidget(6, QFormLayout::LabelRole, removeNumbersLabel);

        removeNumbers = new QCheckBox(formLayoutWidget);
        removeNumbers->setObjectName("removeNumbers");

        formLayout->setWidget(6, QFormLayout::FieldRole, removeNumbers);

        defaultOptionsLabel = new QLabel(formLayoutWidget);
        defaultOptionsLabel->setObjectName("defaultOptionsLabel");

        formLayout->setWidget(7, QFormLayout::LabelRole, defaultOptionsLabel);

        defaultOptions = new QCheckBox(formLayoutWidget);
        defaultOptions->setObjectName("defaultOptions");

        formLayout->setWidget(7, QFormLayout::FieldRole, defaultOptions);

        passwordLengthLabel = new QLabel(formLayoutWidget);
        passwordLengthLabel->setObjectName("passwordLengthLabel");

        formLayout->setWidget(8, QFormLayout::LabelRole, passwordLengthLabel);

        passwordLength = new QLineEdit(formLayoutWidget);
        passwordLength->setObjectName("passwordLength");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(passwordLength->sizePolicy().hasHeightForWidth());
        passwordLength->setSizePolicy(sizePolicy1);
        passwordLength->setMaximumSize(QSize(60, 20));
        passwordLength->setAutoFillBackground(true);

        formLayout->setWidget(8, QFormLayout::FieldRole, passwordLength);

        groupBoxOutput = new QGroupBox(centralwidget);
        groupBoxOutput->setObjectName("groupBoxOutput");
        groupBoxOutput->setGeometry(QRect(10, 250, 511, 91));
        randomPassword = new QPlainTextEdit(groupBoxOutput);
        randomPassword->setObjectName("randomPassword");
        randomPassword->setGeometry(QRect(120, 30, 381, 21));
        randomPasswordLabel = new QLabel(groupBoxOutput);
        randomPasswordLabel->setObjectName("randomPasswordLabel");
        randomPasswordLabel->setGeometry(QRect(10, 30, 131, 16));
        logMessageLabel = new QLabel(groupBoxOutput);
        logMessageLabel->setObjectName("logMessageLabel");
        logMessageLabel->setGeometry(QRect(10, 60, 131, 16));
        logMessage = new QPlainTextEdit(groupBoxOutput);
        logMessage->setObjectName("logMessage");
        logMessage->setGeometry(QRect(120, 60, 381, 21));
        groupBoxActions = new QGroupBox(centralwidget);
        groupBoxActions->setObjectName("groupBoxActions");
        groupBoxActions->setGeometry(QRect(300, 10, 221, 241));
        generatePassword = new QToolButton(groupBoxActions);
        generatePassword->setObjectName("generatePassword");
        generatePassword->setGeometry(QRect(10, 30, 201, 21));
        resetOptions = new QToolButton(groupBoxActions);
        resetOptions->setObjectName("resetOptions");
        resetOptions->setGeometry(QRect(10, 90, 201, 22));
        exitMinipass = new QToolButton(groupBoxActions);
        exitMinipass->setObjectName("exitMinipass");
        exitMinipass->setGeometry(QRect(10, 120, 201, 22));
        openPasswordsHistory = new QToolButton(groupBoxActions);
        openPasswordsHistory->setObjectName("openPasswordsHistory");
        openPasswordsHistory->setGeometry(QRect(10, 60, 201, 21));
        MiniPass->setCentralWidget(centralwidget);

        retranslateUi(MiniPass);

        QMetaObject::connectSlotsByName(MiniPass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniPass)
    {
        actionExit->setText(QCoreApplication::translate("MiniPass", "Exit", nullptr));
        groupBoxOptions->setTitle(QCoreApplication::translate("MiniPass", "Options", nullptr));
        removeCustomCharactersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Custom Characters", nullptr));
        makeMnemonicLabel->setText(QCoreApplication::translate("MiniPass", "Make Mnemonic", nullptr));
        makeMnemonic->setText(QString());
        keepHistoryLabel->setText(QCoreApplication::translate("MiniPass", "Keep History", nullptr));
        keepHistory->setText(QString());
        removeSpecialCharactersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Special Characters", nullptr));
        removeSpecialCharacters->setText(QString());
        removeUppercaseLettersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Uppercase Letters", nullptr));
        removeUppercaseLetters->setText(QString());
        removeLowercaseLettersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Lowercase Letters", nullptr));
        removeLowercaseLetters->setText(QString());
        removeNumbersLabel->setText(QCoreApplication::translate("MiniPass", "Remove Numbers", nullptr));
        removeNumbers->setText(QString());
        defaultOptionsLabel->setText(QCoreApplication::translate("MiniPass", "Default Options", nullptr));
        defaultOptions->setText(QString());
        passwordLengthLabel->setText(QCoreApplication::translate("MiniPass", "Password Length", nullptr));
        groupBoxOutput->setTitle(QCoreApplication::translate("MiniPass", "Output", nullptr));
        randomPasswordLabel->setText(QCoreApplication::translate("MiniPass", "Random Password", nullptr));
        logMessageLabel->setText(QCoreApplication::translate("MiniPass", "Log Message", nullptr));
        groupBoxActions->setTitle(QCoreApplication::translate("MiniPass", "Actions", nullptr));
        generatePassword->setText(QCoreApplication::translate("MiniPass", "Generate Password", nullptr));
        resetOptions->setText(QCoreApplication::translate("MiniPass", "Reset Options", nullptr));
        exitMinipass->setText(QCoreApplication::translate("MiniPass", "Close Application", nullptr));
        openPasswordsHistory->setText(QCoreApplication::translate("MiniPass", "Open PasswordsHistory.csv", nullptr));
        (void)MiniPass;
    } // retranslateUi

};

namespace Ui {
    class MiniPass: public Ui_MiniPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPASS_H
