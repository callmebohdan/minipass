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
#include <QtWidgets/QFrame>
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
    QWidget *CentralWidget;
    QFrame *FrameMinipass;
    QPlainTextEdit *TextEditPassword;
    QToolButton *ButtonResetOptions;
    QCheckBox *CheckBoxMnemonic;
    QCheckBox *CheckBoxNumbers;
    QCheckBox *CheckBoxLowercase;
    QLineEdit *LineEditCustom;
    QCheckBox *CheckBoxUppercase;
    QToolButton *ButtonGeneratePassword;
    QLineEdit *LineEditLength;
    QToolButton *ButtonOpenHistory;
    QPushButton *ButtonCopyPassword;
    QCheckBox *CheckBoxHistory;
    QCheckBox *CheckBoxSpecial;

    void setupUi(QMainWindow *MiniPass)
    {
        if (MiniPass->objectName().isEmpty())
            MiniPass->setObjectName("MiniPass");
        MiniPass->setEnabled(true);
        MiniPass->resize(221, 191);
        MiniPass->setWindowTitle(QString::fromUtf8("minipass"));
        MiniPass->setAutoFillBackground(false);
        MiniPass->setStyleSheet(QString::fromUtf8(""));
        MiniPass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MiniPass->setAnimated(true);
        MiniPass->setDocumentMode(false);
        MiniPass->setUnifiedTitleAndToolBarOnMac(false);
        CentralWidget = new QWidget(MiniPass);
        CentralWidget->setObjectName("CentralWidget");
        CentralWidget->setStyleSheet(QString::fromUtf8(""));
        FrameMinipass = new QFrame(CentralWidget);
        FrameMinipass->setObjectName("FrameMinipass");
        FrameMinipass->setGeometry(QRect(0, 0, 221, 191));
        FrameMinipass->setFrameShape(QFrame::StyledPanel);
        FrameMinipass->setFrameShadow(QFrame::Raised);
        TextEditPassword = new QPlainTextEdit(FrameMinipass);
        TextEditPassword->setObjectName("TextEditPassword");
        TextEditPassword->setGeometry(QRect(10, 130, 200, 30));
        TextEditPassword->setFocusPolicy(Qt::TabFocus);
        ButtonResetOptions = new QToolButton(FrameMinipass);
        ButtonResetOptions->setObjectName("ButtonResetOptions");
        ButtonResetOptions->setGeometry(QRect(10, 90, 200, 20));
        ButtonResetOptions->setCursor(QCursor(Qt::ArrowCursor));
        CheckBoxMnemonic = new QCheckBox(FrameMinipass);
        CheckBoxMnemonic->setObjectName("CheckBoxMnemonic");
        CheckBoxMnemonic->setEnabled(true);
        CheckBoxMnemonic->setGeometry(QRect(10, 10, 100, 21));
        CheckBoxMnemonic->setCursor(QCursor(Qt::ArrowCursor));
        CheckBoxMnemonic->setLayoutDirection(Qt::LeftToRight);
        CheckBoxMnemonic->setAutoFillBackground(false);
        CheckBoxNumbers = new QCheckBox(FrameMinipass);
        CheckBoxNumbers->setObjectName("CheckBoxNumbers");
        CheckBoxNumbers->setGeometry(QRect(110, 50, 100, 20));
        CheckBoxNumbers->setCursor(QCursor(Qt::PointingHandCursor));
        CheckBoxNumbers->setLayoutDirection(Qt::LeftToRight);
        CheckBoxLowercase = new QCheckBox(FrameMinipass);
        CheckBoxLowercase->setObjectName("CheckBoxLowercase");
        CheckBoxLowercase->setGeometry(QRect(110, 30, 100, 20));
        CheckBoxLowercase->setCursor(QCursor(Qt::PointingHandCursor));
        CheckBoxLowercase->setLayoutDirection(Qt::LeftToRight);
        LineEditCustom = new QLineEdit(FrameMinipass);
        LineEditCustom->setObjectName("LineEditCustom");
        LineEditCustom->setGeometry(QRect(110, 70, 100, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LineEditCustom->sizePolicy().hasHeightForWidth());
        LineEditCustom->setSizePolicy(sizePolicy);
        LineEditCustom->setMinimumSize(QSize(20, 0));
        LineEditCustom->setMaximumSize(QSize(200, 20));
        LineEditCustom->setContextMenuPolicy(Qt::NoContextMenu);
        LineEditCustom->setAutoFillBackground(false);
        CheckBoxUppercase = new QCheckBox(FrameMinipass);
        CheckBoxUppercase->setObjectName("CheckBoxUppercase");
        CheckBoxUppercase->setGeometry(QRect(110, 10, 100, 20));
        CheckBoxUppercase->setCursor(QCursor(Qt::PointingHandCursor));
        CheckBoxUppercase->setLayoutDirection(Qt::LeftToRight);
        ButtonGeneratePassword = new QToolButton(FrameMinipass);
        ButtonGeneratePassword->setObjectName("ButtonGeneratePassword");
        ButtonGeneratePassword->setGeometry(QRect(10, 110, 200, 20));
        ButtonGeneratePassword->setCursor(QCursor(Qt::ArrowCursor));
        LineEditLength = new QLineEdit(FrameMinipass);
        LineEditLength->setObjectName("LineEditLength");
        LineEditLength->setGeometry(QRect(10, 70, 100, 20));
        sizePolicy.setHeightForWidth(LineEditLength->sizePolicy().hasHeightForWidth());
        LineEditLength->setSizePolicy(sizePolicy);
        LineEditLength->setMaximumSize(QSize(100, 20));
        LineEditLength->setAutoFillBackground(false);
        ButtonOpenHistory = new QToolButton(FrameMinipass);
        ButtonOpenHistory->setObjectName("ButtonOpenHistory");
        ButtonOpenHistory->setGeometry(QRect(110, 160, 100, 20));
        ButtonOpenHistory->setCursor(QCursor(Qt::ArrowCursor));
        ButtonCopyPassword = new QPushButton(FrameMinipass);
        ButtonCopyPassword->setObjectName("ButtonCopyPassword");
        ButtonCopyPassword->setGeometry(QRect(10, 160, 100, 20));
        ButtonCopyPassword->setCursor(QCursor(Qt::ArrowCursor));
        ButtonCopyPassword->setFocusPolicy(Qt::TabFocus);
        CheckBoxHistory = new QCheckBox(FrameMinipass);
        CheckBoxHistory->setObjectName("CheckBoxHistory");
        CheckBoxHistory->setGeometry(QRect(10, 30, 100, 20));
        CheckBoxHistory->setCursor(QCursor(Qt::PointingHandCursor));
        CheckBoxHistory->setLayoutDirection(Qt::LeftToRight);
        CheckBoxSpecial = new QCheckBox(FrameMinipass);
        CheckBoxSpecial->setObjectName("CheckBoxSpecial");
        CheckBoxSpecial->setGeometry(QRect(10, 50, 100, 20));
        CheckBoxSpecial->setCursor(QCursor(Qt::PointingHandCursor));
        CheckBoxSpecial->setLayoutDirection(Qt::LeftToRight);
        MiniPass->setCentralWidget(CentralWidget);

        retranslateUi(MiniPass);

        QMetaObject::connectSlotsByName(MiniPass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniPass)
    {
        TextEditPassword->setPlaceholderText(QCoreApplication::translate("MiniPass", "Generated Password", nullptr));
        ButtonResetOptions->setText(QCoreApplication::translate("MiniPass", "Reset Options", nullptr));
#if QT_CONFIG(tooltip)
        CheckBoxMnemonic->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        CheckBoxMnemonic->setText(QCoreApplication::translate("MiniPass", "Mnemonic", nullptr));
        CheckBoxNumbers->setText(QCoreApplication::translate("MiniPass", "Numbers", nullptr));
        CheckBoxLowercase->setText(QCoreApplication::translate("MiniPass", "Lowercase", nullptr));
        LineEditCustom->setText(QString());
        LineEditCustom->setPlaceholderText(QCoreApplication::translate("MiniPass", "Custom", nullptr));
        CheckBoxUppercase->setText(QCoreApplication::translate("MiniPass", "Uppercase", nullptr));
        ButtonGeneratePassword->setText(QCoreApplication::translate("MiniPass", "Generate", nullptr));
        LineEditLength->setInputMask(QString());
        LineEditLength->setText(QString());
        LineEditLength->setPlaceholderText(QCoreApplication::translate("MiniPass", "Length: 16", nullptr));
        ButtonOpenHistory->setText(QCoreApplication::translate("MiniPass", "History", nullptr));
        ButtonCopyPassword->setText(QCoreApplication::translate("MiniPass", "Copy", nullptr));
        CheckBoxHistory->setText(QCoreApplication::translate("MiniPass", "History", nullptr));
        CheckBoxSpecial->setText(QCoreApplication::translate("MiniPass", "Special", nullptr));
        (void)MiniPass;
    } // retranslateUi

};

namespace Ui {
    class MiniPass: public Ui_MiniPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPASS_H
