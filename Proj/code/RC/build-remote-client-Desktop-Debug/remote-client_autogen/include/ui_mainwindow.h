/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *Login;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *username;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *password;
    QSpacerItem *horizontalSpacer;
    QPushButton *forgotBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *signInBtn;
    QPushButton *registerBtn;
    QSpacerItem *horizontalSpacer_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *usernameLabel_2;
    QWidget *Register;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *email;
    QSpacerItem *horizontalSpacer_6;
    QLabel *emailLabel;
    QLineEdit *confPassword;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *username_2;
    QLabel *usernameLabel_3;
    QLabel *passwordLabel_2;
    QLabel *confPasswordLabel;
    QLineEdit *password_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *cancelBtn;
    QPushButton *registerBtn_2;
    QSpacerItem *horizontalSpacer_10;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleMain;
    QFrame *line;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 600));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 60, 800, 471));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(800, 471));
        Login = new QWidget();
        Login->setObjectName(QString::fromUtf8("Login"));
        gridLayoutWidget = new QWidget(Login);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 70, 816, 245));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        usernameLabel = new QLabel(gridLayoutWidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy1);
        usernameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(usernameLabel, 0, 1, 1, 1);

        passwordLabel = new QLabel(gridLayoutWidget);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        sizePolicy1.setHeightForWidth(passwordLabel->sizePolicy().hasHeightForWidth());
        passwordLabel->setSizePolicy(sizePolicy1);
        passwordLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(passwordLabel, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        username = new QLineEdit(gridLayoutWidget);
        username->setObjectName(QString::fromUtf8("username"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(username->sizePolicy().hasHeightForWidth());
        username->setSizePolicy(sizePolicy2);
        username->setMinimumSize(QSize(300, 30));
        username->setLayoutDirection(Qt::LeftToRight);
        username->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(username, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(17, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 8, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(17, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 6, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        password = new QLineEdit(gridLayoutWidget);
        password->setObjectName(QString::fromUtf8("password"));
        sizePolicy2.setHeightForWidth(password->sizePolicy().hasHeightForWidth());
        password->setSizePolicy(sizePolicy2);
        password->setMinimumSize(QSize(300, 30));
        password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        forgotBtn = new QPushButton(gridLayoutWidget);
        forgotBtn->setObjectName(QString::fromUtf8("forgotBtn"));
        forgotBtn->setEnabled(true);
        QFont font;
        font.setItalic(true);
        forgotBtn->setFont(font);
        forgotBtn->setCursor(QCursor(Qt::PointingHandCursor));
        forgotBtn->setFocusPolicy(Qt::NoFocus);
        forgotBtn->setContextMenuPolicy(Qt::NoContextMenu);
        forgotBtn->setAcceptDrops(false);
        forgotBtn->setInputMethodHints(Qt::ImhNone);
        forgotBtn->setCheckable(false);
        forgotBtn->setChecked(false);
        forgotBtn->setAutoDefault(false);
        forgotBtn->setFlat(true);

        gridLayout->addWidget(forgotBtn, 7, 1, 1, 1);

        horizontalLayoutWidget = new QWidget(Login);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 350, 801, 87));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        signInBtn = new QPushButton(horizontalLayoutWidget);
        signInBtn->setObjectName(QString::fromUtf8("signInBtn"));
        sizePolicy.setHeightForWidth(signInBtn->sizePolicy().hasHeightForWidth());
        signInBtn->setSizePolicy(sizePolicy);
        signInBtn->setMinimumSize(QSize(80, 40));
        signInBtn->setCursor(QCursor(Qt::PointingHandCursor));
        signInBtn->setLayoutDirection(Qt::LeftToRight);
        signInBtn->setFlat(false);

        horizontalLayout->addWidget(signInBtn);

        registerBtn = new QPushButton(horizontalLayoutWidget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));
        sizePolicy.setHeightForWidth(registerBtn->sizePolicy().hasHeightForWidth());
        registerBtn->setSizePolicy(sizePolicy);
        registerBtn->setMinimumSize(QSize(80, 40));
        registerBtn->setCursor(QCursor(Qt::PointingHandCursor));
        registerBtn->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(registerBtn);

        horizontalSpacer_4 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        verticalLayoutWidget_2 = new QWidget(Login);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 804, 41));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        usernameLabel_2 = new QLabel(verticalLayoutWidget_2);
        usernameLabel_2->setObjectName(QString::fromUtf8("usernameLabel_2"));
        sizePolicy1.setHeightForWidth(usernameLabel_2->sizePolicy().hasHeightForWidth());
        usernameLabel_2->setSizePolicy(sizePolicy1);
        usernameLabel_2->setMinimumSize(QSize(0, 25));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        usernameLabel_2->setFont(font1);
        usernameLabel_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(usernameLabel_2);

        stackedWidget->addWidget(Login);
        Register = new QWidget();
        Register->setObjectName(QString::fromUtf8("Register"));
        gridLayoutWidget_2 = new QWidget(Register);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 801, 401));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        email = new QLineEdit(gridLayoutWidget_2);
        email->setObjectName(QString::fromUtf8("email"));
        sizePolicy1.setHeightForWidth(email->sizePolicy().hasHeightForWidth());
        email->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(email, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        emailLabel = new QLabel(gridLayoutWidget_2);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        sizePolicy1.setHeightForWidth(emailLabel->sizePolicy().hasHeightForWidth());
        emailLabel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(emailLabel, 0, 1, 1, 1);

        confPassword = new QLineEdit(gridLayoutWidget_2);
        confPassword->setObjectName(QString::fromUtf8("confPassword"));
        confPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(confPassword, 8, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        username_2 = new QLineEdit(gridLayoutWidget_2);
        username_2->setObjectName(QString::fromUtf8("username_2"));

        gridLayout_2->addWidget(username_2, 3, 1, 1, 1);

        usernameLabel_3 = new QLabel(gridLayoutWidget_2);
        usernameLabel_3->setObjectName(QString::fromUtf8("usernameLabel_3"));
        sizePolicy1.setHeightForWidth(usernameLabel_3->sizePolicy().hasHeightForWidth());
        usernameLabel_3->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(usernameLabel_3, 2, 1, 1, 1);

        passwordLabel_2 = new QLabel(gridLayoutWidget_2);
        passwordLabel_2->setObjectName(QString::fromUtf8("passwordLabel_2"));
        sizePolicy1.setHeightForWidth(passwordLabel_2->sizePolicy().hasHeightForWidth());
        passwordLabel_2->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(passwordLabel_2, 4, 1, 1, 1);

        confPasswordLabel = new QLabel(gridLayoutWidget_2);
        confPasswordLabel->setObjectName(QString::fromUtf8("confPasswordLabel"));
        sizePolicy1.setHeightForWidth(confPasswordLabel->sizePolicy().hasHeightForWidth());
        confPasswordLabel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(confPasswordLabel, 6, 1, 1, 1);

        password_2 = new QLineEdit(gridLayoutWidget_2);
        password_2->setObjectName(QString::fromUtf8("password_2"));
        password_2->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(password_2, 5, 1, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(Register);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 400, 801, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        cancelBtn = new QPushButton(horizontalLayoutWidget_2);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        sizePolicy.setHeightForWidth(cancelBtn->sizePolicy().hasHeightForWidth());
        cancelBtn->setSizePolicy(sizePolicy);
        cancelBtn->setMinimumSize(QSize(80, 40));
        cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(cancelBtn);

        registerBtn_2 = new QPushButton(horizontalLayoutWidget_2);
        registerBtn_2->setObjectName(QString::fromUtf8("registerBtn_2"));
        sizePolicy.setHeightForWidth(registerBtn_2->sizePolicy().hasHeightForWidth());
        registerBtn_2->setSizePolicy(sizePolicy);
        registerBtn_2->setMinimumSize(QSize(80, 40));
        registerBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        registerBtn_2->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(registerBtn_2);

        horizontalSpacer_10 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        stackedWidget->addWidget(Register);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 802, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleMain = new QLabel(verticalLayoutWidget);
        titleMain->setObjectName(QString::fromUtf8("titleMain"));
        titleMain->setEnabled(true);
        sizePolicy.setHeightForWidth(titleMain->sizePolicy().hasHeightForWidth());
        titleMain->setSizePolicy(sizePolicy);
        titleMain->setMinimumSize(QSize(800, 50));
        titleMain->setSizeIncrement(QSize(10, 10));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setWeight(75);
        titleMain->setFont(font2);
        titleMain->setLayoutDirection(Qt::LeftToRight);
        titleMain->setFrameShape(QFrame::NoFrame);
        titleMain->setFrameShadow(QFrame::Raised);
        titleMain->setLineWidth(0);
        titleMain->setTextFormat(Qt::AutoText);
        titleMain->setScaledContents(false);
        titleMain->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleMain);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(500, 0));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        forgotBtn->setDefault(false);
        signInBtn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        usernameLabel->setText(QApplication::translate("MainWindow", "username", nullptr));
        passwordLabel->setText(QApplication::translate("MainWindow", "password", nullptr));
        forgotBtn->setText(QApplication::translate("MainWindow", "Forgot Password?", nullptr));
        signInBtn->setText(QApplication::translate("MainWindow", "Sign In", nullptr));
        registerBtn->setText(QApplication::translate("MainWindow", "Register", nullptr));
        usernameLabel_2->setText(QApplication::translate("MainWindow", "LOGIN", nullptr));
        emailLabel->setText(QApplication::translate("MainWindow", "Email", nullptr));
        confPassword->setText(QString());
        usernameLabel_3->setText(QApplication::translate("MainWindow", "Type your username", nullptr));
        passwordLabel_2->setText(QApplication::translate("MainWindow", "Type your password", nullptr));
        confPasswordLabel->setText(QApplication::translate("MainWindow", "Confirm Password", nullptr));
        cancelBtn->setText(QApplication::translate("MainWindow", "Cancel", nullptr));
        registerBtn_2->setText(QApplication::translate("MainWindow", "Register", nullptr));
        titleMain->setText(QApplication::translate("MainWindow", "MDO", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
