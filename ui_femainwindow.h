/********************************************************************************
** Form generated from reading UI file 'femainwindow.ui'
**
** Created: Thu 7. Jun 17:31:38 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEMAINWINDOW_H
#define UI_FEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FEMainWindow
{
public:
    QAction *action_Load_image;
    QAction *action_Load_flow_field;
    QAction *action_Save_flow_field;
    QAction *action_Export_flow_map;
    QAction *action_Quit;
    QAction *action_New;
    QAction *action_Export_flow_map_fast;
    QAction *actionExport_flow_map_AKIMA;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *previewBtn;
    QPushButton *fileBtn;
    QPushButton *expAndSwitchBtn;
    QPushButton *makeGridBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPushButton *indivBtn;
    QPushButton *brushBtn;
    QPushButton *eraserBtn;
    QLabel *label_2;
    QSlider *brushSizeSlider;
    QCheckBox *brushOnceChkbx;
    QSpacerItem *verticalSpacer;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuE_xport_flow_map;

    void setupUi(QMainWindow *FEMainWindow)
    {
        if (FEMainWindow->objectName().isEmpty())
            FEMainWindow->setObjectName(QString::fromUtf8("FEMainWindow"));
        FEMainWindow->resize(614, 415);
        action_Load_image = new QAction(FEMainWindow);
        action_Load_image->setObjectName(QString::fromUtf8("action_Load_image"));
        action_Load_flow_field = new QAction(FEMainWindow);
        action_Load_flow_field->setObjectName(QString::fromUtf8("action_Load_flow_field"));
        action_Save_flow_field = new QAction(FEMainWindow);
        action_Save_flow_field->setObjectName(QString::fromUtf8("action_Save_flow_field"));
        action_Export_flow_map = new QAction(FEMainWindow);
        action_Export_flow_map->setObjectName(QString::fromUtf8("action_Export_flow_map"));
        action_Quit = new QAction(FEMainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_New = new QAction(FEMainWindow);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        action_Export_flow_map_fast = new QAction(FEMainWindow);
        action_Export_flow_map_fast->setObjectName(QString::fromUtf8("action_Export_flow_map_fast"));
        actionExport_flow_map_AKIMA = new QAction(FEMainWindow);
        actionExport_flow_map_AKIMA->setObjectName(QString::fromUtf8("actionExport_flow_map_AKIMA"));
        centralWidget = new QWidget(FEMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        previewBtn = new QPushButton(centralWidget);
        previewBtn->setObjectName(QString::fromUtf8("previewBtn"));
        previewBtn->setCheckable(true);

        verticalLayout->addWidget(previewBtn);

        fileBtn = new QPushButton(centralWidget);
        fileBtn->setObjectName(QString::fromUtf8("fileBtn"));

        verticalLayout->addWidget(fileBtn);

        expAndSwitchBtn = new QPushButton(centralWidget);
        expAndSwitchBtn->setObjectName(QString::fromUtf8("expAndSwitchBtn"));

        verticalLayout->addWidget(expAndSwitchBtn);

        makeGridBtn = new QPushButton(centralWidget);
        makeGridBtn->setObjectName(QString::fromUtf8("makeGridBtn"));

        verticalLayout->addWidget(makeGridBtn);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        indivBtn = new QPushButton(widget);
        indivBtn->setObjectName(QString::fromUtf8("indivBtn"));
        indivBtn->setCheckable(true);
        indivBtn->setChecked(true);
        indivBtn->setAutoExclusive(true);

        verticalLayout_2->addWidget(indivBtn);

        brushBtn = new QPushButton(widget);
        brushBtn->setObjectName(QString::fromUtf8("brushBtn"));
        brushBtn->setCheckable(true);
        brushBtn->setAutoExclusive(true);

        verticalLayout_2->addWidget(brushBtn);

        eraserBtn = new QPushButton(widget);
        eraserBtn->setObjectName(QString::fromUtf8("eraserBtn"));
        eraserBtn->setCheckable(true);
        eraserBtn->setAutoExclusive(true);

        verticalLayout_2->addWidget(eraserBtn);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        brushSizeSlider = new QSlider(widget);
        brushSizeSlider->setObjectName(QString::fromUtf8("brushSizeSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(brushSizeSlider->sizePolicy().hasHeightForWidth());
        brushSizeSlider->setSizePolicy(sizePolicy);
        brushSizeSlider->setMinimum(1);
        brushSizeSlider->setMaximum(100);
        brushSizeSlider->setOrientation(Qt::Horizontal);
        brushSizeSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_2->addWidget(brushSizeSlider);

        brushOnceChkbx = new QCheckBox(widget);
        brushOnceChkbx->setObjectName(QString::fromUtf8("brushOnceChkbx"));

        verticalLayout_2->addWidget(brushOnceChkbx);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(graphicsView);

        FEMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FEMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 614, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuE_xport_flow_map = new QMenu(menu_File);
        menuE_xport_flow_map->setObjectName(QString::fromUtf8("menuE_xport_flow_map"));
        FEMainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Load_image);
        menu_File->addAction(action_Load_flow_field);
        menu_File->addAction(action_Save_flow_field);
        menu_File->addAction(menuE_xport_flow_map->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menuE_xport_flow_map->addAction(action_Export_flow_map_fast);
        menuE_xport_flow_map->addAction(actionExport_flow_map_AKIMA);
        menuE_xport_flow_map->addAction(action_Export_flow_map);

        retranslateUi(FEMainWindow);

        QMetaObject::connectSlotsByName(FEMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FEMainWindow)
    {
        FEMainWindow->setWindowTitle(QApplication::translate("FEMainWindow", "Flow Editor (C) Stanislaw Adaszewski, 2012, http://algoholic.eu", 0, QApplication::UnicodeUTF8));
        action_Load_image->setText(QApplication::translate("FEMainWindow", "&Load image", 0, QApplication::UnicodeUTF8));
        action_Load_flow_field->setText(QApplication::translate("FEMainWindow", "Load &flow field", 0, QApplication::UnicodeUTF8));
        action_Save_flow_field->setText(QApplication::translate("FEMainWindow", "&Save flow field", 0, QApplication::UnicodeUTF8));
        action_Export_flow_map->setText(QApplication::translate("FEMainWindow", "Natural Neighbor Interpolation", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("FEMainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("FEMainWindow", "&New", 0, QApplication::UnicodeUTF8));
        action_Export_flow_map_fast->setText(QApplication::translate("FEMainWindow", "Linear Interpolation", 0, QApplication::UnicodeUTF8));
        actionExport_flow_map_AKIMA->setText(QApplication::translate("FEMainWindow", "Cubic Interpolation", 0, QApplication::UnicodeUTF8));
        previewBtn->setText(QString());
        fileBtn->setText(QApplication::translate("FEMainWindow", "&File", 0, QApplication::UnicodeUTF8));
        expAndSwitchBtn->setText(QApplication::translate("FEMainWindow", "&Repeat Last Export", 0, QApplication::UnicodeUTF8));
        makeGridBtn->setText(QApplication::translate("FEMainWindow", "Make &Grid", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FEMainWindow", "Tool:", 0, QApplication::UnicodeUTF8));
        indivBtn->setText(QApplication::translate("FEMainWindow", "&Individual", 0, QApplication::UnicodeUTF8));
        brushBtn->setText(QApplication::translate("FEMainWindow", "&Brush", 0, QApplication::UnicodeUTF8));
        eraserBtn->setText(QApplication::translate("FEMainWindow", "&Eraser", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FEMainWindow", "Brush size:", 0, QApplication::UnicodeUTF8));
        brushOnceChkbx->setText(QApplication::translate("FEMainWindow", "Brush once", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("FEMainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuE_xport_flow_map->setTitle(QApplication::translate("FEMainWindow", "E&xport flow map", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FEMainWindow: public Ui_FEMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEMAINWINDOW_H
