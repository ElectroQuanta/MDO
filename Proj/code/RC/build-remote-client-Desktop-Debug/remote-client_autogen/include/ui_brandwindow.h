/********************************************************************************
** Form generated from reading UI file 'brandwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRANDWINDOW_H
#define UI_BRANDWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
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

class Ui_BrandWindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *welcomePage;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QPushButton *logoutBtn;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *rentedBtn;
    QPushButton *toRentBtn;
    QSpacerItem *horizontalSpacer_11;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *welcomeMsg;
    QPushButton *notificationsBtn;
    QWidget *rentedPage;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_5;
    QLabel *NrTimesShowLabel_2;
    QLabel *NrTimesShowLabel;
    QLabel *fragranceSlotQuantLabel_2;
    QLabel *NrSharedLabel_2;
    QLabel *fragranceSlotQuantLabel;
    QLabel *NrPicsGIFSLabel;
    QLabel *NrSharedLabel;
    QLabel *NrPicsGIFSLabel_2;
    QLabel *DaysRemainingLabel;
    QLabel *DaysRemainingLabel_2;
    QLabel *DaysRemainingLabel_3;
    QLabel *activatedLabel;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_15;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_13;
    QComboBox *stationsComboBox;
    QSpacerItem *horizontalSpacer_14;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *goBackBtn;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *stationName;
    QWidget *toRentPage;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_19;
    QComboBox *stationsComboBox_2;
    QSpacerItem *horizontalSpacer_20;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_23;
    QLabel *activatedLabel_3;
    QComboBox *targetHoursComboBox;
    QSpacerItem *horizontalSpacer_24;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_25;
    QCalendarWidget *calendarWidget;
    QSpacerItem *horizontalSpacer_26;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *rentBtn;
    QLabel *franganceLabel;
    QPushButton *uploadBtn;
    QLabel *addVideoLabel;
    QSpacerItem *horizontalSpacer_29;
    QPushButton *goBackBtn_2;
    QSpacerItem *horizontalSpacer_27;
    QSpacerItem *horizontalSpacer_28;
    QLabel *filterLabel;
    QComboBox *filterComboBox;
    QComboBox *fragranceComboBox;
    QSpacerItem *horizontalSpacer_30;
    QLabel *filenameLabel;

    void setupUi(QWidget *BrandWindow)
    {
        if (BrandWindow->objectName().isEmpty())
            BrandWindow->setObjectName(QString::fromUtf8("BrandWindow"));
        BrandWindow->resize(800, 471);
        stackedWidget = new QStackedWidget(BrandWindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 800, 471));
        welcomePage = new QWidget();
        welcomePage->setObjectName(QString::fromUtf8("welcomePage"));
        gridLayoutWidget_2 = new QWidget(welcomePage);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 120, 801, 250));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(12);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        logoutBtn = new QPushButton(gridLayoutWidget_2);
        logoutBtn->setObjectName(QString::fromUtf8("logoutBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logoutBtn->sizePolicy().hasHeightForWidth());
        logoutBtn->setSizePolicy(sizePolicy);
        logoutBtn->setMinimumSize(QSize(80, 40));
        logoutBtn->setCursor(QCursor(Qt::PointingHandCursor));
        logoutBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(logoutBtn, 2, 1, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_12, 0, 2, 1, 1);

        rentedBtn = new QPushButton(gridLayoutWidget_2);
        rentedBtn->setObjectName(QString::fromUtf8("rentedBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rentedBtn->sizePolicy().hasHeightForWidth());
        rentedBtn->setSizePolicy(sizePolicy1);
        rentedBtn->setMinimumSize(QSize(100, 40));
        rentedBtn->setCursor(QCursor(Qt::PointingHandCursor));
        rentedBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(rentedBtn, 0, 1, 1, 1);

        toRentBtn = new QPushButton(gridLayoutWidget_2);
        toRentBtn->setObjectName(QString::fromUtf8("toRentBtn"));
        sizePolicy.setHeightForWidth(toRentBtn->sizePolicy().hasHeightForWidth());
        toRentBtn->setSizePolicy(sizePolicy);
        toRentBtn->setMinimumSize(QSize(80, 40));
        toRentBtn->setCursor(QCursor(Qt::PointingHandCursor));
        toRentBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(toRentBtn, 1, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_11, 0, 0, 1, 1);

        verticalLayoutWidget = new QWidget(welcomePage);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 40, 801, 33));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        welcomeMsg = new QLabel(verticalLayoutWidget);
        welcomeMsg->setObjectName(QString::fromUtf8("welcomeMsg"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(welcomeMsg->sizePolicy().hasHeightForWidth());
        welcomeMsg->setSizePolicy(sizePolicy2);
        welcomeMsg->setMinimumSize(QSize(0, 20));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        welcomeMsg->setFont(font);
        welcomeMsg->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(welcomeMsg);

        notificationsBtn = new QPushButton(welcomePage);
        notificationsBtn->setObjectName(QString::fromUtf8("notificationsBtn"));
        notificationsBtn->setGeometry(QRect(0, 0, 111, 34));
        stackedWidget->addWidget(welcomePage);
        rentedPage = new QWidget();
        rentedPage->setObjectName(QString::fromUtf8("rentedPage"));
        gridLayoutWidget_3 = new QWidget(rentedPage);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 90, 801, 273));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        NrTimesShowLabel_2 = new QLabel(gridLayoutWidget_3);
        NrTimesShowLabel_2->setObjectName(QString::fromUtf8("NrTimesShowLabel_2"));
        sizePolicy.setHeightForWidth(NrTimesShowLabel_2->sizePolicy().hasHeightForWidth());
        NrTimesShowLabel_2->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("NewsGotTMed"));
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        NrTimesShowLabel_2->setFont(font1);
        NrTimesShowLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrTimesShowLabel_2, 1, 2, 1, 1);

        NrTimesShowLabel = new QLabel(gridLayoutWidget_3);
        NrTimesShowLabel->setObjectName(QString::fromUtf8("NrTimesShowLabel"));
        sizePolicy2.setHeightForWidth(NrTimesShowLabel->sizePolicy().hasHeightForWidth());
        NrTimesShowLabel->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("NewsGotTLig"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        NrTimesShowLabel->setFont(font2);

        gridLayout_5->addWidget(NrTimesShowLabel, 1, 1, 1, 1);

        fragranceSlotQuantLabel_2 = new QLabel(gridLayoutWidget_3);
        fragranceSlotQuantLabel_2->setObjectName(QString::fromUtf8("fragranceSlotQuantLabel_2"));
        sizePolicy.setHeightForWidth(fragranceSlotQuantLabel_2->sizePolicy().hasHeightForWidth());
        fragranceSlotQuantLabel_2->setSizePolicy(sizePolicy);
        fragranceSlotQuantLabel_2->setFont(font1);
        fragranceSlotQuantLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(fragranceSlotQuantLabel_2, 2, 2, 1, 1);

        NrSharedLabel_2 = new QLabel(gridLayoutWidget_3);
        NrSharedLabel_2->setObjectName(QString::fromUtf8("NrSharedLabel_2"));
        sizePolicy.setHeightForWidth(NrSharedLabel_2->sizePolicy().hasHeightForWidth());
        NrSharedLabel_2->setSizePolicy(sizePolicy);
        NrSharedLabel_2->setFont(font1);
        NrSharedLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrSharedLabel_2, 5, 2, 1, 1);

        fragranceSlotQuantLabel = new QLabel(gridLayoutWidget_3);
        fragranceSlotQuantLabel->setObjectName(QString::fromUtf8("fragranceSlotQuantLabel"));
        sizePolicy2.setHeightForWidth(fragranceSlotQuantLabel->sizePolicy().hasHeightForWidth());
        fragranceSlotQuantLabel->setSizePolicy(sizePolicy2);
        fragranceSlotQuantLabel->setFont(font2);

        gridLayout_5->addWidget(fragranceSlotQuantLabel, 2, 1, 1, 1);

        NrPicsGIFSLabel = new QLabel(gridLayoutWidget_3);
        NrPicsGIFSLabel->setObjectName(QString::fromUtf8("NrPicsGIFSLabel"));
        sizePolicy2.setHeightForWidth(NrPicsGIFSLabel->sizePolicy().hasHeightForWidth());
        NrPicsGIFSLabel->setSizePolicy(sizePolicy2);
        NrPicsGIFSLabel->setFont(font2);

        gridLayout_5->addWidget(NrPicsGIFSLabel, 4, 1, 1, 1);

        NrSharedLabel = new QLabel(gridLayoutWidget_3);
        NrSharedLabel->setObjectName(QString::fromUtf8("NrSharedLabel"));
        sizePolicy2.setHeightForWidth(NrSharedLabel->sizePolicy().hasHeightForWidth());
        NrSharedLabel->setSizePolicy(sizePolicy2);
        NrSharedLabel->setFont(font2);

        gridLayout_5->addWidget(NrSharedLabel, 5, 1, 1, 1);

        NrPicsGIFSLabel_2 = new QLabel(gridLayoutWidget_3);
        NrPicsGIFSLabel_2->setObjectName(QString::fromUtf8("NrPicsGIFSLabel_2"));
        sizePolicy.setHeightForWidth(NrPicsGIFSLabel_2->sizePolicy().hasHeightForWidth());
        NrPicsGIFSLabel_2->setSizePolicy(sizePolicy);
        NrPicsGIFSLabel_2->setFont(font1);
        NrPicsGIFSLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(NrPicsGIFSLabel_2, 4, 2, 1, 1);

        DaysRemainingLabel = new QLabel(gridLayoutWidget_3);
        DaysRemainingLabel->setObjectName(QString::fromUtf8("DaysRemainingLabel"));
        sizePolicy2.setHeightForWidth(DaysRemainingLabel->sizePolicy().hasHeightForWidth());
        DaysRemainingLabel->setSizePolicy(sizePolicy2);
        DaysRemainingLabel->setFont(font2);

        gridLayout_5->addWidget(DaysRemainingLabel, 6, 1, 1, 1);

        DaysRemainingLabel_2 = new QLabel(gridLayoutWidget_3);
        DaysRemainingLabel_2->setObjectName(QString::fromUtf8("DaysRemainingLabel_2"));
        sizePolicy.setHeightForWidth(DaysRemainingLabel_2->sizePolicy().hasHeightForWidth());
        DaysRemainingLabel_2->setSizePolicy(sizePolicy);
        DaysRemainingLabel_2->setFont(font1);
        DaysRemainingLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(DaysRemainingLabel_2, 6, 2, 1, 1);

        DaysRemainingLabel_3 = new QLabel(gridLayoutWidget_3);
        DaysRemainingLabel_3->setObjectName(QString::fromUtf8("DaysRemainingLabel_3"));
        sizePolicy.setHeightForWidth(DaysRemainingLabel_3->sizePolicy().hasHeightForWidth());
        DaysRemainingLabel_3->setSizePolicy(sizePolicy);
        DaysRemainingLabel_3->setFont(font1);
        DaysRemainingLabel_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(DaysRemainingLabel_3, 0, 2, 1, 1);

        activatedLabel = new QLabel(gridLayoutWidget_3);
        activatedLabel->setObjectName(QString::fromUtf8("activatedLabel"));
        sizePolicy2.setHeightForWidth(activatedLabel->sizePolicy().hasHeightForWidth());
        activatedLabel->setSizePolicy(sizePolicy2);
        activatedLabel->setFont(font2);

        gridLayout_5->addWidget(activatedLabel, 0, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_16, 1, 0, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_15, 1, 3, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(rentedPage);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 40, 801, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_13 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        stationsComboBox = new QComboBox(horizontalLayoutWidget_2);
        stationsComboBox->setObjectName(QString::fromUtf8("stationsComboBox"));
        sizePolicy2.setHeightForWidth(stationsComboBox->sizePolicy().hasHeightForWidth());
        stationsComboBox->setSizePolicy(sizePolicy2);
        stationsComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        stationsComboBox->setEditable(false);
        stationsComboBox->setMinimumContentsLength(0);

        horizontalLayout_3->addWidget(stationsComboBox);

        horizontalSpacer_14 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        gridLayoutWidget_4 = new QWidget(rentedPage);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 380, 801, 42));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setVerticalSpacing(12);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_17 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_17, 0, 0, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_18, 0, 2, 1, 1);

        goBackBtn = new QPushButton(gridLayoutWidget_4);
        goBackBtn->setObjectName(QString::fromUtf8("goBackBtn"));
        sizePolicy1.setHeightForWidth(goBackBtn->sizePolicy().hasHeightForWidth());
        goBackBtn->setSizePolicy(sizePolicy1);
        goBackBtn->setMinimumSize(QSize(124, 40));
        goBackBtn->setCursor(QCursor(Qt::PointingHandCursor));
        goBackBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_6->addWidget(goBackBtn, 0, 1, 1, 1);

        verticalLayoutWidget_2 = new QWidget(rentedPage);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 801, 33));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        stationName = new QLabel(verticalLayoutWidget_2);
        stationName->setObjectName(QString::fromUtf8("stationName"));
        sizePolicy2.setHeightForWidth(stationName->sizePolicy().hasHeightForWidth());
        stationName->setSizePolicy(sizePolicy2);
        stationName->setMinimumSize(QSize(0, 20));
        stationName->setFont(font);
        stationName->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(stationName);

        stackedWidget->addWidget(rentedPage);
        toRentPage = new QWidget();
        toRentPage->setObjectName(QString::fromUtf8("toRentPage"));
        horizontalLayoutWidget_3 = new QWidget(toRentPage);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 801, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_19 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_19);

        stationsComboBox_2 = new QComboBox(horizontalLayoutWidget_3);
        stationsComboBox_2->setObjectName(QString::fromUtf8("stationsComboBox_2"));
        sizePolicy2.setHeightForWidth(stationsComboBox_2->sizePolicy().hasHeightForWidth());
        stationsComboBox_2->setSizePolicy(sizePolicy2);
        stationsComboBox_2->setCursor(QCursor(Qt::PointingHandCursor));
        stationsComboBox_2->setEditable(false);
        stationsComboBox_2->setMinimumContentsLength(0);

        horizontalLayout_4->addWidget(stationsComboBox_2);

        horizontalSpacer_20 = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_20);

        horizontalLayoutWidget = new QWidget(toRentPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 40, 801, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_23 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_23);

        activatedLabel_3 = new QLabel(horizontalLayoutWidget);
        activatedLabel_3->setObjectName(QString::fromUtf8("activatedLabel_3"));
        sizePolicy2.setHeightForWidth(activatedLabel_3->sizePolicy().hasHeightForWidth());
        activatedLabel_3->setSizePolicy(sizePolicy2);
        activatedLabel_3->setFont(font2);

        horizontalLayout->addWidget(activatedLabel_3);

        targetHoursComboBox = new QComboBox(horizontalLayoutWidget);
        targetHoursComboBox->setObjectName(QString::fromUtf8("targetHoursComboBox"));
        sizePolicy1.setHeightForWidth(targetHoursComboBox->sizePolicy().hasHeightForWidth());
        targetHoursComboBox->setSizePolicy(sizePolicy1);
        targetHoursComboBox->setMinimumSize(QSize(150, 35));
        targetHoursComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        targetHoursComboBox->setEditable(false);
        targetHoursComboBox->setMinimumContentsLength(0);

        horizontalLayout->addWidget(targetHoursComboBox);

        horizontalSpacer_24 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_24);

        horizontalLayoutWidget_4 = new QWidget(toRentPage);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 80, 820, 251));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_25 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_25);

        calendarWidget = new QCalendarWidget(horizontalLayoutWidget_4);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        sizePolicy.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy);
        calendarWidget->setLocale(QLocale(QLocale::English, QLocale::Europe));
        calendarWidget->setSelectedDate(QDate(2022, 1, 25));
        calendarWidget->setFirstDayOfWeek(Qt::Monday);
        calendarWidget->setGridVisible(false);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::ISOWeekNumbers);
        calendarWidget->setNavigationBarVisible(true);
        calendarWidget->setDateEditEnabled(true);

        horizontalLayout_2->addWidget(calendarWidget);

        horizontalSpacer_26 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_26);

        gridLayoutWidget = new QWidget(toRentPage);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 330, 804, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        rentBtn = new QPushButton(gridLayoutWidget);
        rentBtn->setObjectName(QString::fromUtf8("rentBtn"));
        sizePolicy1.setHeightForWidth(rentBtn->sizePolicy().hasHeightForWidth());
        rentBtn->setSizePolicy(sizePolicy1);
        rentBtn->setMinimumSize(QSize(90, 35));
        rentBtn->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(rentBtn, 1, 5, 1, 1, Qt::AlignRight);

        franganceLabel = new QLabel(gridLayoutWidget);
        franganceLabel->setObjectName(QString::fromUtf8("franganceLabel"));
        sizePolicy.setHeightForWidth(franganceLabel->sizePolicy().hasHeightForWidth());
        franganceLabel->setSizePolicy(sizePolicy);
        franganceLabel->setFont(font2);

        gridLayout->addWidget(franganceLabel, 1, 1, 1, 1);

        uploadBtn = new QPushButton(gridLayoutWidget);
        uploadBtn->setObjectName(QString::fromUtf8("uploadBtn"));
        sizePolicy1.setHeightForWidth(uploadBtn->sizePolicy().hasHeightForWidth());
        uploadBtn->setSizePolicy(sizePolicy1);
        uploadBtn->setMinimumSize(QSize(120, 0));
        uploadBtn->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(uploadBtn, 0, 3, 1, 1);

        addVideoLabel = new QLabel(gridLayoutWidget);
        addVideoLabel->setObjectName(QString::fromUtf8("addVideoLabel"));
        sizePolicy2.setHeightForWidth(addVideoLabel->sizePolicy().hasHeightForWidth());
        addVideoLabel->setSizePolicy(sizePolicy2);
        addVideoLabel->setFont(font2);

        gridLayout->addWidget(addVideoLabel, 0, 1, 1, 1);

        horizontalSpacer_29 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_29, 0, 4, 1, 1);

        goBackBtn_2 = new QPushButton(gridLayoutWidget);
        goBackBtn_2->setObjectName(QString::fromUtf8("goBackBtn_2"));
        sizePolicy1.setHeightForWidth(goBackBtn_2->sizePolicy().hasHeightForWidth());
        goBackBtn_2->setSizePolicy(sizePolicy1);
        goBackBtn_2->setMinimumSize(QSize(90, 35));
        goBackBtn_2->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(goBackBtn_2, 2, 5, 1, 1, Qt::AlignRight);

        horizontalSpacer_27 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_27, 0, 6, 1, 1);

        horizontalSpacer_28 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_28, 0, 0, 1, 1);

        filterLabel = new QLabel(gridLayoutWidget);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        sizePolicy.setHeightForWidth(filterLabel->sizePolicy().hasHeightForWidth());
        filterLabel->setSizePolicy(sizePolicy);
        filterLabel->setFont(font2);

        gridLayout->addWidget(filterLabel, 2, 1, 1, 1);

        filterComboBox = new QComboBox(gridLayoutWidget);
        filterComboBox->setObjectName(QString::fromUtf8("filterComboBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(filterComboBox->sizePolicy().hasHeightForWidth());
        filterComboBox->setSizePolicy(sizePolicy3);
        filterComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        filterComboBox->setEditable(false);
        filterComboBox->setMinimumContentsLength(0);

        gridLayout->addWidget(filterComboBox, 2, 3, 1, 1);

        fragranceComboBox = new QComboBox(gridLayoutWidget);
        fragranceComboBox->setObjectName(QString::fromUtf8("fragranceComboBox"));
        sizePolicy3.setHeightForWidth(fragranceComboBox->sizePolicy().hasHeightForWidth());
        fragranceComboBox->setSizePolicy(sizePolicy3);
        fragranceComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        fragranceComboBox->setEditable(false);
        fragranceComboBox->setMinimumContentsLength(0);

        gridLayout->addWidget(fragranceComboBox, 1, 3, 1, 1);

        horizontalSpacer_30 = new QSpacerItem(100, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_30, 0, 2, 1, 1);

        filenameLabel = new QLabel(gridLayoutWidget);
        filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));
        sizePolicy.setHeightForWidth(filenameLabel->sizePolicy().hasHeightForWidth());
        filenameLabel->setSizePolicy(sizePolicy);
        filenameLabel->setMinimumSize(QSize(0, 0));
        filenameLabel->setFont(font2);

        gridLayout->addWidget(filenameLabel, 0, 5, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        stackedWidget->addWidget(toRentPage);

        retranslateUi(BrandWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(BrandWindow);
    } // setupUi

    void retranslateUi(QWidget *BrandWindow)
    {
        BrandWindow->setWindowTitle(QApplication::translate("BrandWindow", "Form", nullptr));
        logoutBtn->setText(QApplication::translate("BrandWindow", "Logout", nullptr));
        rentedBtn->setText(QApplication::translate("BrandWindow", "Rented", nullptr));
        toRentBtn->setText(QApplication::translate("BrandWindow", "To Rent", nullptr));
        welcomeMsg->setText(QApplication::translate("BrandWindow", "Welcome!!", nullptr));
        notificationsBtn->setText(QApplication::translate("BrandWindow", "Notifications", nullptr));
        NrTimesShowLabel_2->setText(QApplication::translate("BrandWindow", "X", nullptr));
        NrTimesShowLabel->setText(QApplication::translate("BrandWindow", "Number of times showed:", nullptr));
        fragranceSlotQuantLabel_2->setText(QApplication::translate("BrandWindow", "X | X%", nullptr));
        NrSharedLabel_2->setText(QApplication::translate("BrandWindow", "X", nullptr));
        fragranceSlotQuantLabel->setText(QApplication::translate("BrandWindow", "Fragrance Slot | Quantity", nullptr));
        NrPicsGIFSLabel->setText(QApplication::translate("BrandWindow", "Number of Pics/GIFs taken", nullptr));
        NrSharedLabel->setText(QApplication::translate("BrandWindow", "Number of Shared Posts", nullptr));
        NrPicsGIFSLabel_2->setText(QApplication::translate("BrandWindow", "X", nullptr));
        DaysRemainingLabel->setText(QApplication::translate("BrandWindow", "Days remaining", nullptr));
        DaysRemainingLabel_2->setText(QApplication::translate("BrandWindow", "X", nullptr));
        DaysRemainingLabel_3->setText(QApplication::translate("BrandWindow", "Activated", nullptr));
        activatedLabel->setText(QApplication::translate("BrandWindow", "Status:", nullptr));
        stationsComboBox->setCurrentText(QString());
        goBackBtn->setText(QApplication::translate("BrandWindow", "Go back", nullptr));
        stationName->setText(QApplication::translate("BrandWindow", "Statistics", nullptr));
        stationsComboBox_2->setCurrentText(QString());
        activatedLabel_3->setText(QApplication::translate("BrandWindow", "Target hours:", nullptr));
        targetHoursComboBox->setCurrentText(QString());
        rentBtn->setText(QApplication::translate("BrandWindow", "Rent", nullptr));
        franganceLabel->setText(QApplication::translate("BrandWindow", "Fragrance: ", nullptr));
        uploadBtn->setText(QApplication::translate("BrandWindow", "Upload", nullptr));
        addVideoLabel->setText(QApplication::translate("BrandWindow", "Add .zip file:", nullptr));
        goBackBtn_2->setText(QApplication::translate("BrandWindow", "Go back", nullptr));
        filterLabel->setText(QApplication::translate("BrandWindow", "Filter:", nullptr));
        filterComboBox->setCurrentText(QString());
        fragranceComboBox->setCurrentText(QString());
        filenameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BrandWindow: public Ui_BrandWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRANDWINDOW_H
