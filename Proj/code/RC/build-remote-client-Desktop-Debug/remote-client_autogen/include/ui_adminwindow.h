/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *main;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *welcomeMsg_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *stationsComboBox;
    QSpacerItem *horizontalSpacer_8;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *poweredCheckBox;
    QLabel *currModeLabel;
    QLabel *currModeLabel_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *poweredLabel;
    QLabel *currAdLabel;
    QLabel *currAdLabel_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QPushButton *adsToActivateBtn_2;
    QPushButton *testOperationBtn_2;
    QPushButton *logoutBtn;
    QPushButton *usersBtn_2;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *statisticsBtn_2;
    QWidget *statisticsPage;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *stationName;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_5;
    QLabel *activatedLabel;
    QLabel *NrPicsGIFSLabel_2;
    QCheckBox *activatedCheckBox;
    QLabel *fragranceSlotQuantLabel;
    QLabel *NrTimesShowLabel_2;
    QSpacerItem *horizontalSpacer_15;
    QLabel *NrSharedLabel_2;
    QLabel *NrSharedLabel;
    QLabel *fragranceSlotQuantLabel_2;
    QLabel *NrPicsGIFSLabel;
    QSpacerItem *horizontalSpacer_16;
    QLabel *NrTimesShowLabel;
    QLabel *DaysRemainingLabel;
    QLabel *DaysRemainingLabel_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_13;
    QComboBox *brandComboBox;
    QSpacerItem *horizontalSpacer_14;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *goBackBtn;
    QWidget *usersPage;
    QLabel *usersLabel;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_19;
    QComboBox *usersComboBox;
    QSpacerItem *horizontalSpacer_20;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_7;
    QLabel *userTypeLabel;
    QSpacerItem *horizontalSpacer_9;
    QComboBox *userTypeComboBox;
    QLabel *emailLabel;
    QSpacerItem *horizontalSpacer_10;
    QLabel *emailLabel_2;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_8;
    QPushButton *goBackBtn_2;
    QPushButton *saveChangesBtn;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_21;
    QPushButton *deleteUserBtn;
    QPushButton *discardChangesBtn;
    QWidget *adsToActivatePage;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *adsToActivateLabel;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_23;
    QComboBox *adsToActComboBox;
    QSpacerItem *horizontalSpacer_24;
    QWidget *gridLayoutWidget_7;
    QGridLayout *gridLayout_9;
    QLabel *videoLabel;
    QLabel *stateLabel_2;
    QLabel *filterLabel_2;
    QLabel *stateLabel;
    QLabel *fragSlotLabel_2;
    QSpacerItem *horizontalSpacer_25;
    QLabel *filterLabel;
    QSpacerItem *horizontalSpacer_26;
    QLabel *fragSlotLabel;
    QPushButton *transferVideosBtn;
    QWidget *gridLayoutWidget_8;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer_28;
    QPushButton *denyAdBtn;
    QPushButton *acceptAdBtn;
    QPushButton *goBackBtn_4;
    QSpacerItem *horizontalSpacer_27;
    QWidget *testOperationPage;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *testOperationLabel;
    QPushButton *goBackBtn_3;

    void setupUi(QWidget *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName(QString::fromUtf8("AdminWindow"));
        AdminWindow->resize(800, 471);
        stackedWidget = new QStackedWidget(AdminWindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 800, 471));
        main = new QWidget();
        main->setObjectName(QString::fromUtf8("main"));
        verticalLayoutWidget = new QWidget(main);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 801, 33));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        welcomeMsg_2 = new QLabel(verticalLayoutWidget);
        welcomeMsg_2->setObjectName(QString::fromUtf8("welcomeMsg_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(welcomeMsg_2->sizePolicy().hasHeightForWidth());
        welcomeMsg_2->setSizePolicy(sizePolicy);
        welcomeMsg_2->setMinimumSize(QSize(0, 20));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        welcomeMsg_2->setFont(font);
        welcomeMsg_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(welcomeMsg_2);

        horizontalLayoutWidget = new QWidget(main);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 40, 801, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        stationsComboBox = new QComboBox(horizontalLayoutWidget);
        stationsComboBox->setObjectName(QString::fromUtf8("stationsComboBox"));
        sizePolicy.setHeightForWidth(stationsComboBox->sizePolicy().hasHeightForWidth());
        stationsComboBox->setSizePolicy(sizePolicy);
        stationsComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        stationsComboBox->setEditable(false);
        stationsComboBox->setMinimumContentsLength(0);

        horizontalLayout_2->addWidget(stationsComboBox);

        horizontalSpacer_8 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        gridLayoutWidget = new QWidget(main);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 90, 801, 116));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        poweredCheckBox = new QCheckBox(gridLayoutWidget);
        poweredCheckBox->setObjectName(QString::fromUtf8("poweredCheckBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(poweredCheckBox->sizePolicy().hasHeightForWidth());
        poweredCheckBox->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(13);
        poweredCheckBox->setFont(font1);
        poweredCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        poweredCheckBox->setLayoutDirection(Qt::RightToLeft);
        poweredCheckBox->setChecked(false);

        gridLayout_3->addWidget(poweredCheckBox, 1, 2, 1, 1, Qt::AlignLeft);

        currModeLabel = new QLabel(gridLayoutWidget);
        currModeLabel->setObjectName(QString::fromUtf8("currModeLabel"));
        sizePolicy.setHeightForWidth(currModeLabel->sizePolicy().hasHeightForWidth());
        currModeLabel->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("NewsGotTLig"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        currModeLabel->setFont(font2);

        gridLayout_3->addWidget(currModeLabel, 2, 1, 1, 1);

        currModeLabel_2 = new QLabel(gridLayoutWidget);
        currModeLabel_2->setObjectName(QString::fromUtf8("currModeLabel_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(currModeLabel_2->sizePolicy().hasHeightForWidth());
        currModeLabel_2->setSizePolicy(sizePolicy2);
        QFont font3;
        font3.setFamily(QString::fromUtf8("NewsGotTMed"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setWeight(50);
        currModeLabel_2->setFont(font3);
        currModeLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(currModeLabel_2, 2, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        poweredLabel = new QLabel(gridLayoutWidget);
        poweredLabel->setObjectName(QString::fromUtf8("poweredLabel"));
        sizePolicy.setHeightForWidth(poweredLabel->sizePolicy().hasHeightForWidth());
        poweredLabel->setSizePolicy(sizePolicy);
        poweredLabel->setFont(font2);

        gridLayout_3->addWidget(poweredLabel, 1, 1, 1, 1);

        currAdLabel = new QLabel(gridLayoutWidget);
        currAdLabel->setObjectName(QString::fromUtf8("currAdLabel"));
        sizePolicy.setHeightForWidth(currAdLabel->sizePolicy().hasHeightForWidth());
        currAdLabel->setSizePolicy(sizePolicy);
        currAdLabel->setFont(font2);

        gridLayout_3->addWidget(currAdLabel, 3, 1, 1, 1);

        currAdLabel_2 = new QLabel(gridLayoutWidget);
        currAdLabel_2->setObjectName(QString::fromUtf8("currAdLabel_2"));
        sizePolicy2.setHeightForWidth(currAdLabel_2->sizePolicy().hasHeightForWidth());
        currAdLabel_2->setSizePolicy(sizePolicy2);
        currAdLabel_2->setFont(font3);
        currAdLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(currAdLabel_2, 3, 2, 1, 1);

        gridLayoutWidget_2 = new QWidget(main);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 210, 801, 250));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(12);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        adsToActivateBtn_2 = new QPushButton(gridLayoutWidget_2);
        adsToActivateBtn_2->setObjectName(QString::fromUtf8("adsToActivateBtn_2"));
        sizePolicy1.setHeightForWidth(adsToActivateBtn_2->sizePolicy().hasHeightForWidth());
        adsToActivateBtn_2->setSizePolicy(sizePolicy1);
        adsToActivateBtn_2->setMinimumSize(QSize(80, 40));
        adsToActivateBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        adsToActivateBtn_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(adsToActivateBtn_2, 2, 1, 1, 1);

        testOperationBtn_2 = new QPushButton(gridLayoutWidget_2);
        testOperationBtn_2->setObjectName(QString::fromUtf8("testOperationBtn_2"));
        sizePolicy2.setHeightForWidth(testOperationBtn_2->sizePolicy().hasHeightForWidth());
        testOperationBtn_2->setSizePolicy(sizePolicy2);
        testOperationBtn_2->setMinimumSize(QSize(80, 40));
        testOperationBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        testOperationBtn_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(testOperationBtn_2, 3, 1, 1, 1);

        logoutBtn = new QPushButton(gridLayoutWidget_2);
        logoutBtn->setObjectName(QString::fromUtf8("logoutBtn"));
        sizePolicy2.setHeightForWidth(logoutBtn->sizePolicy().hasHeightForWidth());
        logoutBtn->setSizePolicy(sizePolicy2);
        logoutBtn->setMinimumSize(QSize(80, 40));
        logoutBtn->setCursor(QCursor(Qt::PointingHandCursor));
        logoutBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(logoutBtn, 4, 1, 1, 1);

        usersBtn_2 = new QPushButton(gridLayoutWidget_2);
        usersBtn_2->setObjectName(QString::fromUtf8("usersBtn_2"));
        sizePolicy2.setHeightForWidth(usersBtn_2->sizePolicy().hasHeightForWidth());
        usersBtn_2->setSizePolicy(sizePolicy2);
        usersBtn_2->setMinimumSize(QSize(80, 40));
        usersBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        usersBtn_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(usersBtn_2, 1, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_11, 0, 0, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_12, 0, 2, 1, 1);

        statisticsBtn_2 = new QPushButton(gridLayoutWidget_2);
        statisticsBtn_2->setObjectName(QString::fromUtf8("statisticsBtn_2"));
        sizePolicy2.setHeightForWidth(statisticsBtn_2->sizePolicy().hasHeightForWidth());
        statisticsBtn_2->setSizePolicy(sizePolicy2);
        statisticsBtn_2->setMinimumSize(QSize(80, 40));
        statisticsBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        statisticsBtn_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(statisticsBtn_2, 0, 1, 1, 1);

        stackedWidget->addWidget(main);
        statisticsPage = new QWidget();
        statisticsPage->setObjectName(QString::fromUtf8("statisticsPage"));
        verticalLayoutWidget_2 = new QWidget(statisticsPage);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 801, 33));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        stationName = new QLabel(verticalLayoutWidget_2);
        stationName->setObjectName(QString::fromUtf8("stationName"));
        sizePolicy.setHeightForWidth(stationName->sizePolicy().hasHeightForWidth());
        stationName->setSizePolicy(sizePolicy);
        stationName->setMinimumSize(QSize(0, 20));
        stationName->setFont(font);
        stationName->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(stationName);

        gridLayoutWidget_3 = new QWidget(statisticsPage);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 100, 801, 216));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        activatedLabel = new QLabel(gridLayoutWidget_3);
        activatedLabel->setObjectName(QString::fromUtf8("activatedLabel"));
        sizePolicy.setHeightForWidth(activatedLabel->sizePolicy().hasHeightForWidth());
        activatedLabel->setSizePolicy(sizePolicy);
        activatedLabel->setFont(font2);

        gridLayout_5->addWidget(activatedLabel, 7, 1, 1, 1);

        NrPicsGIFSLabel_2 = new QLabel(gridLayoutWidget_3);
        NrPicsGIFSLabel_2->setObjectName(QString::fromUtf8("NrPicsGIFSLabel_2"));
        sizePolicy2.setHeightForWidth(NrPicsGIFSLabel_2->sizePolicy().hasHeightForWidth());
        NrPicsGIFSLabel_2->setSizePolicy(sizePolicy2);
        NrPicsGIFSLabel_2->setFont(font3);
        NrPicsGIFSLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrPicsGIFSLabel_2, 4, 2, 1, 1);

        activatedCheckBox = new QCheckBox(gridLayoutWidget_3);
        activatedCheckBox->setObjectName(QString::fromUtf8("activatedCheckBox"));
        sizePolicy1.setHeightForWidth(activatedCheckBox->sizePolicy().hasHeightForWidth());
        activatedCheckBox->setSizePolicy(sizePolicy1);
        activatedCheckBox->setFont(font1);
        activatedCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        activatedCheckBox->setLayoutDirection(Qt::RightToLeft);
        activatedCheckBox->setChecked(false);

        gridLayout_5->addWidget(activatedCheckBox, 7, 2, 1, 1, Qt::AlignLeft);

        fragranceSlotQuantLabel = new QLabel(gridLayoutWidget_3);
        fragranceSlotQuantLabel->setObjectName(QString::fromUtf8("fragranceSlotQuantLabel"));
        sizePolicy.setHeightForWidth(fragranceSlotQuantLabel->sizePolicy().hasHeightForWidth());
        fragranceSlotQuantLabel->setSizePolicy(sizePolicy);
        fragranceSlotQuantLabel->setFont(font2);

        gridLayout_5->addWidget(fragranceSlotQuantLabel, 2, 1, 1, 1);

        NrTimesShowLabel_2 = new QLabel(gridLayoutWidget_3);
        NrTimesShowLabel_2->setObjectName(QString::fromUtf8("NrTimesShowLabel_2"));
        sizePolicy2.setHeightForWidth(NrTimesShowLabel_2->sizePolicy().hasHeightForWidth());
        NrTimesShowLabel_2->setSizePolicy(sizePolicy2);
        NrTimesShowLabel_2->setFont(font3);
        NrTimesShowLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrTimesShowLabel_2, 1, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_15, 7, 3, 1, 1);

        NrSharedLabel_2 = new QLabel(gridLayoutWidget_3);
        NrSharedLabel_2->setObjectName(QString::fromUtf8("NrSharedLabel_2"));
        sizePolicy2.setHeightForWidth(NrSharedLabel_2->sizePolicy().hasHeightForWidth());
        NrSharedLabel_2->setSizePolicy(sizePolicy2);
        NrSharedLabel_2->setFont(font3);
        NrSharedLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrSharedLabel_2, 5, 2, 1, 1);

        NrSharedLabel = new QLabel(gridLayoutWidget_3);
        NrSharedLabel->setObjectName(QString::fromUtf8("NrSharedLabel"));
        sizePolicy.setHeightForWidth(NrSharedLabel->sizePolicy().hasHeightForWidth());
        NrSharedLabel->setSizePolicy(sizePolicy);
        NrSharedLabel->setFont(font2);

        gridLayout_5->addWidget(NrSharedLabel, 5, 1, 1, 1);

        fragranceSlotQuantLabel_2 = new QLabel(gridLayoutWidget_3);
        fragranceSlotQuantLabel_2->setObjectName(QString::fromUtf8("fragranceSlotQuantLabel_2"));
        sizePolicy2.setHeightForWidth(fragranceSlotQuantLabel_2->sizePolicy().hasHeightForWidth());
        fragranceSlotQuantLabel_2->setSizePolicy(sizePolicy2);
        fragranceSlotQuantLabel_2->setFont(font3);
        fragranceSlotQuantLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(fragranceSlotQuantLabel_2, 2, 2, 1, 1);

        NrPicsGIFSLabel = new QLabel(gridLayoutWidget_3);
        NrPicsGIFSLabel->setObjectName(QString::fromUtf8("NrPicsGIFSLabel"));
        sizePolicy.setHeightForWidth(NrPicsGIFSLabel->sizePolicy().hasHeightForWidth());
        NrPicsGIFSLabel->setSizePolicy(sizePolicy);
        NrPicsGIFSLabel->setFont(font2);

        gridLayout_5->addWidget(NrPicsGIFSLabel, 4, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_16, 7, 0, 1, 1);

        NrTimesShowLabel = new QLabel(gridLayoutWidget_3);
        NrTimesShowLabel->setObjectName(QString::fromUtf8("NrTimesShowLabel"));
        sizePolicy.setHeightForWidth(NrTimesShowLabel->sizePolicy().hasHeightForWidth());
        NrTimesShowLabel->setSizePolicy(sizePolicy);
        NrTimesShowLabel->setFont(font2);

        gridLayout_5->addWidget(NrTimesShowLabel, 1, 1, 1, 1);

        DaysRemainingLabel = new QLabel(gridLayoutWidget_3);
        DaysRemainingLabel->setObjectName(QString::fromUtf8("DaysRemainingLabel"));
        sizePolicy.setHeightForWidth(DaysRemainingLabel->sizePolicy().hasHeightForWidth());
        DaysRemainingLabel->setSizePolicy(sizePolicy);
        DaysRemainingLabel->setFont(font2);

        gridLayout_5->addWidget(DaysRemainingLabel, 6, 1, 1, 1);

        DaysRemainingLabel_2 = new QLabel(gridLayoutWidget_3);
        DaysRemainingLabel_2->setObjectName(QString::fromUtf8("DaysRemainingLabel_2"));
        sizePolicy2.setHeightForWidth(DaysRemainingLabel_2->sizePolicy().hasHeightForWidth());
        DaysRemainingLabel_2->setSizePolicy(sizePolicy2);
        DaysRemainingLabel_2->setFont(font3);
        DaysRemainingLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(DaysRemainingLabel_2, 6, 2, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(statisticsPage);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 40, 801, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_13 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        brandComboBox = new QComboBox(horizontalLayoutWidget_2);
        brandComboBox->setObjectName(QString::fromUtf8("brandComboBox"));
        sizePolicy.setHeightForWidth(brandComboBox->sizePolicy().hasHeightForWidth());
        brandComboBox->setSizePolicy(sizePolicy);
        brandComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        brandComboBox->setEditable(false);
        brandComboBox->setMinimumContentsLength(0);

        horizontalLayout_3->addWidget(brandComboBox);

        horizontalSpacer_14 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        gridLayoutWidget_4 = new QWidget(statisticsPage);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 330, 801, 42));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setVerticalSpacing(12);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_18 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_18, 0, 2, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_17, 0, 0, 1, 1);

        goBackBtn = new QPushButton(gridLayoutWidget_4);
        goBackBtn->setObjectName(QString::fromUtf8("goBackBtn"));
        sizePolicy1.setHeightForWidth(goBackBtn->sizePolicy().hasHeightForWidth());
        goBackBtn->setSizePolicy(sizePolicy1);
        goBackBtn->setMinimumSize(QSize(124, 40));
        goBackBtn->setCursor(QCursor(Qt::PointingHandCursor));
        goBackBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_6->addWidget(goBackBtn, 0, 1, 1, 1);

        stackedWidget->addWidget(statisticsPage);
        usersPage = new QWidget();
        usersPage->setObjectName(QString::fromUtf8("usersPage"));
        usersLabel = new QLabel(usersPage);
        usersLabel->setObjectName(QString::fromUtf8("usersLabel"));
        usersLabel->setGeometry(QRect(1, 1, 799, 31));
        sizePolicy.setHeightForWidth(usersLabel->sizePolicy().hasHeightForWidth());
        usersLabel->setSizePolicy(sizePolicy);
        usersLabel->setMinimumSize(QSize(0, 20));
        usersLabel->setFont(font);
        usersLabel->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_3 = new QWidget(usersPage);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 40, 801, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_19 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_19);

        usersComboBox = new QComboBox(horizontalLayoutWidget_3);
        usersComboBox->setObjectName(QString::fromUtf8("usersComboBox"));
        sizePolicy.setHeightForWidth(usersComboBox->sizePolicy().hasHeightForWidth());
        usersComboBox->setSizePolicy(sizePolicy);
        usersComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        usersComboBox->setEditable(false);
        usersComboBox->setMinimumContentsLength(0);

        horizontalLayout_4->addWidget(usersComboBox);

        horizontalSpacer_20 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_20);

        gridLayoutWidget_5 = new QWidget(usersPage);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 100, 801, 116));
        gridLayout_7 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        userTypeLabel = new QLabel(gridLayoutWidget_5);
        userTypeLabel->setObjectName(QString::fromUtf8("userTypeLabel"));
        sizePolicy.setHeightForWidth(userTypeLabel->sizePolicy().hasHeightForWidth());
        userTypeLabel->setSizePolicy(sizePolicy);
        userTypeLabel->setFont(font2);

        gridLayout_7->addWidget(userTypeLabel, 1, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_9, 1, 3, 1, 1);

        userTypeComboBox = new QComboBox(gridLayoutWidget_5);
        userTypeComboBox->setObjectName(QString::fromUtf8("userTypeComboBox"));
        sizePolicy2.setHeightForWidth(userTypeComboBox->sizePolicy().hasHeightForWidth());
        userTypeComboBox->setSizePolicy(sizePolicy2);
        userTypeComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        userTypeComboBox->setEditable(false);
        userTypeComboBox->setMinimumContentsLength(0);

        gridLayout_7->addWidget(userTypeComboBox, 1, 2, 1, 1);

        emailLabel = new QLabel(gridLayoutWidget_5);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        sizePolicy.setHeightForWidth(emailLabel->sizePolicy().hasHeightForWidth());
        emailLabel->setSizePolicy(sizePolicy);
        emailLabel->setFont(font2);

        gridLayout_7->addWidget(emailLabel, 2, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_10, 1, 0, 1, 1);

        emailLabel_2 = new QLabel(gridLayoutWidget_5);
        emailLabel_2->setObjectName(QString::fromUtf8("emailLabel_2"));
        sizePolicy2.setHeightForWidth(emailLabel_2->sizePolicy().hasHeightForWidth());
        emailLabel_2->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setFamily(QString::fromUtf8("NewsGotTMed"));
        font4.setPointSize(12);
        font4.setBold(false);
        font4.setWeight(50);
        emailLabel_2->setFont(font4);
        emailLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(emailLabel_2, 2, 2, 1, 1);

        gridLayoutWidget_6 = new QWidget(usersPage);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 230, 801, 211));
        gridLayout_8 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setVerticalSpacing(0);
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        goBackBtn_2 = new QPushButton(gridLayoutWidget_6);
        goBackBtn_2->setObjectName(QString::fromUtf8("goBackBtn_2"));
        sizePolicy2.setHeightForWidth(goBackBtn_2->sizePolicy().hasHeightForWidth());
        goBackBtn_2->setSizePolicy(sizePolicy2);
        goBackBtn_2->setMinimumSize(QSize(80, 40));
        goBackBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
        goBackBtn_2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(goBackBtn_2, 3, 1, 1, 1);

        saveChangesBtn = new QPushButton(gridLayoutWidget_6);
        saveChangesBtn->setObjectName(QString::fromUtf8("saveChangesBtn"));
        sizePolicy2.setHeightForWidth(saveChangesBtn->sizePolicy().hasHeightForWidth());
        saveChangesBtn->setSizePolicy(sizePolicy2);
        saveChangesBtn->setMinimumSize(QSize(80, 40));
        saveChangesBtn->setCursor(QCursor(Qt::PointingHandCursor));
        saveChangesBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(saveChangesBtn, 1, 1, 1, 1);

        horizontalSpacer_22 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_22, 0, 2, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_21, 0, 0, 1, 1);

        deleteUserBtn = new QPushButton(gridLayoutWidget_6);
        deleteUserBtn->setObjectName(QString::fromUtf8("deleteUserBtn"));
        sizePolicy2.setHeightForWidth(deleteUserBtn->sizePolicy().hasHeightForWidth());
        deleteUserBtn->setSizePolicy(sizePolicy2);
        deleteUserBtn->setMinimumSize(QSize(80, 40));
        deleteUserBtn->setCursor(QCursor(Qt::PointingHandCursor));
        deleteUserBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(deleteUserBtn, 0, 1, 1, 1);

        discardChangesBtn = new QPushButton(gridLayoutWidget_6);
        discardChangesBtn->setObjectName(QString::fromUtf8("discardChangesBtn"));
        sizePolicy1.setHeightForWidth(discardChangesBtn->sizePolicy().hasHeightForWidth());
        discardChangesBtn->setSizePolicy(sizePolicy1);
        discardChangesBtn->setMinimumSize(QSize(80, 40));
        discardChangesBtn->setCursor(QCursor(Qt::PointingHandCursor));
        discardChangesBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(discardChangesBtn, 2, 1, 1, 1);

        stackedWidget->addWidget(usersPage);
        adsToActivatePage = new QWidget();
        adsToActivatePage->setObjectName(QString::fromUtf8("adsToActivatePage"));
        verticalLayoutWidget_4 = new QWidget(adsToActivatePage);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(0, 10, 801, 31));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        adsToActivateLabel = new QLabel(verticalLayoutWidget_4);
        adsToActivateLabel->setObjectName(QString::fromUtf8("adsToActivateLabel"));
        sizePolicy.setHeightForWidth(adsToActivateLabel->sizePolicy().hasHeightForWidth());
        adsToActivateLabel->setSizePolicy(sizePolicy);
        adsToActivateLabel->setMinimumSize(QSize(0, 20));
        adsToActivateLabel->setFont(font);
        adsToActivateLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(adsToActivateLabel);

        horizontalLayoutWidget_4 = new QWidget(adsToActivatePage);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 50, 799, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_23 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_23);

        adsToActComboBox = new QComboBox(horizontalLayoutWidget_4);
        adsToActComboBox->setObjectName(QString::fromUtf8("adsToActComboBox"));
        sizePolicy.setHeightForWidth(adsToActComboBox->sizePolicy().hasHeightForWidth());
        adsToActComboBox->setSizePolicy(sizePolicy);
        adsToActComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        adsToActComboBox->setEditable(false);
        adsToActComboBox->setMinimumContentsLength(0);

        horizontalLayout_5->addWidget(adsToActComboBox);

        horizontalSpacer_24 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_24);

        gridLayoutWidget_7 = new QWidget(adsToActivatePage);
        gridLayoutWidget_7->setObjectName(QString::fromUtf8("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(0, 120, 801, 171));
        gridLayout_9 = new QGridLayout(gridLayoutWidget_7);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        videoLabel = new QLabel(gridLayoutWidget_7);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        sizePolicy.setHeightForWidth(videoLabel->sizePolicy().hasHeightForWidth());
        videoLabel->setSizePolicy(sizePolicy);
        videoLabel->setFont(font2);

        gridLayout_9->addWidget(videoLabel, 3, 1, 1, 1);

        stateLabel_2 = new QLabel(gridLayoutWidget_7);
        stateLabel_2->setObjectName(QString::fromUtf8("stateLabel_2"));
        sizePolicy2.setHeightForWidth(stateLabel_2->sizePolicy().hasHeightForWidth());
        stateLabel_2->setSizePolicy(sizePolicy2);
        stateLabel_2->setFont(font4);
        stateLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(stateLabel_2, 1, 2, 1, 1);

        filterLabel_2 = new QLabel(gridLayoutWidget_7);
        filterLabel_2->setObjectName(QString::fromUtf8("filterLabel_2"));
        sizePolicy2.setHeightForWidth(filterLabel_2->sizePolicy().hasHeightForWidth());
        filterLabel_2->setSizePolicy(sizePolicy2);
        filterLabel_2->setFont(font4);
        filterLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(filterLabel_2, 4, 2, 1, 1);

        stateLabel = new QLabel(gridLayoutWidget_7);
        stateLabel->setObjectName(QString::fromUtf8("stateLabel"));
        sizePolicy.setHeightForWidth(stateLabel->sizePolicy().hasHeightForWidth());
        stateLabel->setSizePolicy(sizePolicy);
        stateLabel->setFont(font2);

        gridLayout_9->addWidget(stateLabel, 1, 1, 1, 1);

        fragSlotLabel_2 = new QLabel(gridLayoutWidget_7);
        fragSlotLabel_2->setObjectName(QString::fromUtf8("fragSlotLabel_2"));
        sizePolicy2.setHeightForWidth(fragSlotLabel_2->sizePolicy().hasHeightForWidth());
        fragSlotLabel_2->setSizePolicy(sizePolicy2);
        fragSlotLabel_2->setFont(font4);
        fragSlotLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(fragSlotLabel_2, 2, 2, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_25, 1, 3, 1, 1);

        filterLabel = new QLabel(gridLayoutWidget_7);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        sizePolicy.setHeightForWidth(filterLabel->sizePolicy().hasHeightForWidth());
        filterLabel->setSizePolicy(sizePolicy);
        filterLabel->setFont(font2);

        gridLayout_9->addWidget(filterLabel, 4, 1, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_26, 1, 0, 1, 1);

        fragSlotLabel = new QLabel(gridLayoutWidget_7);
        fragSlotLabel->setObjectName(QString::fromUtf8("fragSlotLabel"));
        sizePolicy.setHeightForWidth(fragSlotLabel->sizePolicy().hasHeightForWidth());
        fragSlotLabel->setSizePolicy(sizePolicy);
        fragSlotLabel->setFont(font2);

        gridLayout_9->addWidget(fragSlotLabel, 2, 1, 1, 1);

        transferVideosBtn = new QPushButton(gridLayoutWidget_7);
        transferVideosBtn->setObjectName(QString::fromUtf8("transferVideosBtn"));
        transferVideosBtn->setCursor(QCursor(Qt::PointingHandCursor));
        transferVideosBtn->setFlat(false);

        gridLayout_9->addWidget(transferVideosBtn, 3, 2, 1, 1);

        gridLayoutWidget_8 = new QWidget(adsToActivatePage);
        gridLayoutWidget_8->setObjectName(QString::fromUtf8("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(0, 310, 801, 151));
        gridLayout_10 = new QGridLayout(gridLayoutWidget_8);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setVerticalSpacing(0);
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_28 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_28, 0, 0, 1, 1);

        denyAdBtn = new QPushButton(gridLayoutWidget_8);
        denyAdBtn->setObjectName(QString::fromUtf8("denyAdBtn"));
        sizePolicy2.setHeightForWidth(denyAdBtn->sizePolicy().hasHeightForWidth());
        denyAdBtn->setSizePolicy(sizePolicy2);
        denyAdBtn->setMinimumSize(QSize(90, 40));
        denyAdBtn->setCursor(QCursor(Qt::PointingHandCursor));
        denyAdBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_10->addWidget(denyAdBtn, 1, 1, 1, 1);

        acceptAdBtn = new QPushButton(gridLayoutWidget_8);
        acceptAdBtn->setObjectName(QString::fromUtf8("acceptAdBtn"));
        sizePolicy2.setHeightForWidth(acceptAdBtn->sizePolicy().hasHeightForWidth());
        acceptAdBtn->setSizePolicy(sizePolicy2);
        acceptAdBtn->setMinimumSize(QSize(90, 40));
        acceptAdBtn->setCursor(QCursor(Qt::PointingHandCursor));
        acceptAdBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_10->addWidget(acceptAdBtn, 0, 1, 1, 1);

        goBackBtn_4 = new QPushButton(gridLayoutWidget_8);
        goBackBtn_4->setObjectName(QString::fromUtf8("goBackBtn_4"));
        sizePolicy1.setHeightForWidth(goBackBtn_4->sizePolicy().hasHeightForWidth());
        goBackBtn_4->setSizePolicy(sizePolicy1);
        goBackBtn_4->setMinimumSize(QSize(90, 40));
        goBackBtn_4->setCursor(QCursor(Qt::PointingHandCursor));
        goBackBtn_4->setLayoutDirection(Qt::LeftToRight);

        gridLayout_10->addWidget(goBackBtn_4, 2, 1, 1, 1);

        horizontalSpacer_27 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_27, 0, 2, 1, 1);

        stackedWidget->addWidget(adsToActivatePage);
        testOperationPage = new QWidget();
        testOperationPage->setObjectName(QString::fromUtf8("testOperationPage"));
        verticalLayoutWidget_3 = new QWidget(testOperationPage);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 801, 33));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        testOperationLabel = new QLabel(verticalLayoutWidget_3);
        testOperationLabel->setObjectName(QString::fromUtf8("testOperationLabel"));
        sizePolicy.setHeightForWidth(testOperationLabel->sizePolicy().hasHeightForWidth());
        testOperationLabel->setSizePolicy(sizePolicy);
        testOperationLabel->setMinimumSize(QSize(0, 20));
        testOperationLabel->setFont(font);
        testOperationLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(testOperationLabel);

        goBackBtn_3 = new QPushButton(testOperationPage);
        goBackBtn_3->setObjectName(QString::fromUtf8("goBackBtn_3"));
        goBackBtn_3->setGeometry(QRect(340, 370, 137, 40));
        sizePolicy2.setHeightForWidth(goBackBtn_3->sizePolicy().hasHeightForWidth());
        goBackBtn_3->setSizePolicy(sizePolicy2);
        goBackBtn_3->setMinimumSize(QSize(80, 40));
        goBackBtn_3->setCursor(QCursor(Qt::PointingHandCursor));
        goBackBtn_3->setLayoutDirection(Qt::LeftToRight);
        stackedWidget->addWidget(testOperationPage);

        retranslateUi(AdminWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QWidget *AdminWindow)
    {
        AdminWindow->setWindowTitle(QApplication::translate("AdminWindow", "Form", nullptr));
        welcomeMsg_2->setText(QApplication::translate("AdminWindow", "Welcome!!", nullptr));
        stationsComboBox->setCurrentText(QString());
        poweredCheckBox->setText(QApplication::translate("AdminWindow", "Off", nullptr));
        currModeLabel->setText(QApplication::translate("AdminWindow", "Current Mode:", nullptr));
        currModeLabel_2->setText(QApplication::translate("AdminWindow", "Normal Mode", nullptr));
        poweredLabel->setText(QApplication::translate("AdminWindow", "Powered:", nullptr));
        currAdLabel->setText(QApplication::translate("AdminWindow", "Current Brand Ad:", nullptr));
        currAdLabel_2->setText(QApplication::translate("AdminWindow", "Brand 1", nullptr));
        adsToActivateBtn_2->setText(QApplication::translate("AdminWindow", "Ads To Activate", nullptr));
        testOperationBtn_2->setText(QApplication::translate("AdminWindow", "Test Operation", nullptr));
        logoutBtn->setText(QApplication::translate("AdminWindow", "Logout", nullptr));
        usersBtn_2->setText(QApplication::translate("AdminWindow", "Users", nullptr));
        statisticsBtn_2->setText(QApplication::translate("AdminWindow", "Statistics", nullptr));
        stationName->setText(QApplication::translate("AdminWindow", "Station 1 - Universidade do Minho", nullptr));
        activatedLabel->setText(QApplication::translate("AdminWindow", "Activated", nullptr));
        NrPicsGIFSLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        activatedCheckBox->setText(QApplication::translate("AdminWindow", "Off", nullptr));
        fragranceSlotQuantLabel->setText(QApplication::translate("AdminWindow", "Fragrance Slot | Quantity", nullptr));
        NrTimesShowLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        NrSharedLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        NrSharedLabel->setText(QApplication::translate("AdminWindow", "Number of Shared Posts", nullptr));
        fragranceSlotQuantLabel_2->setText(QApplication::translate("AdminWindow", "X | X%", nullptr));
        NrPicsGIFSLabel->setText(QApplication::translate("AdminWindow", "Number of Pics/GIFs taken", nullptr));
        NrTimesShowLabel->setText(QApplication::translate("AdminWindow", "Number of times showed:", nullptr));
        DaysRemainingLabel->setText(QApplication::translate("AdminWindow", "Days remaining", nullptr));
        DaysRemainingLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        brandComboBox->setCurrentText(QString());
        goBackBtn->setText(QApplication::translate("AdminWindow", "Go back", nullptr));
        usersLabel->setText(QApplication::translate("AdminWindow", "Users", nullptr));
        usersComboBox->setCurrentText(QString());
        userTypeLabel->setText(QApplication::translate("AdminWindow", "Type of user:", nullptr));
        userTypeComboBox->setCurrentText(QString());
        emailLabel->setText(QApplication::translate("AdminWindow", "Email:", nullptr));
        emailLabel_2->setText(QApplication::translate("AdminWindow", "hugofreitas12@gmail.com", nullptr));
        goBackBtn_2->setText(QApplication::translate("AdminWindow", "Go Back", nullptr));
        saveChangesBtn->setText(QApplication::translate("AdminWindow", "Save Changes", nullptr));
        deleteUserBtn->setText(QApplication::translate("AdminWindow", "Delete User", nullptr));
        discardChangesBtn->setText(QApplication::translate("AdminWindow", "Discard Changes", nullptr));
        adsToActivateLabel->setText(QApplication::translate("AdminWindow", "Ads To Activate - Station 1", nullptr));
        adsToActComboBox->setCurrentText(QString());
        videoLabel->setText(QApplication::translate("AdminWindow", "Video", nullptr));
        stateLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        filterLabel_2->setText(QApplication::translate("AdminWindow", "X", nullptr));
        stateLabel->setText(QApplication::translate("AdminWindow", "State:", nullptr));
        fragSlotLabel_2->setText(QApplication::translate("AdminWindow", "X | X%", nullptr));
        filterLabel->setText(QApplication::translate("AdminWindow", "Filter", nullptr));
        fragSlotLabel->setText(QApplication::translate("AdminWindow", "Fragrance Slot & Quantity:", nullptr));
        transferVideosBtn->setText(QApplication::translate("AdminWindow", "somevideo.zip", nullptr));
        denyAdBtn->setText(QApplication::translate("AdminWindow", "Deny Ad", nullptr));
        acceptAdBtn->setText(QApplication::translate("AdminWindow", "Accept Ad", nullptr));
        goBackBtn_4->setText(QApplication::translate("AdminWindow", "Go Back", nullptr));
        testOperationLabel->setText(QApplication::translate("AdminWindow", "Test Operation", nullptr));
        goBackBtn_3->setText(QApplication::translate("AdminWindow", "Go Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
