/********************************************************************************
** Form generated from reading UI file 'femainwindow.ui'
**
** Created: Wed 29. Aug 17:38:57 2012
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
#include <QtGui/QComboBox>
#include <QtGui/QDial>
#include <QtGui/QDockWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QToolButton>
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
    QAction *action_Export_flow_map_fast;
    QAction *actionExport_flow_map_AKIMA;
    QAction *action_Generate_grid;
    QAction *action_Flow_field;
    QAction *action_Project;
    QAction *action_Generate_gradient_grid;
    QAction *actionShow_li_cense;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuE_xport_flow_map;
    QMenu *menu_New;
    QMenu *menu_Load;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QPushButton *previewBtn;
    QPushButton *fileBtn;
    QPushButton *expAndSwitchBtn;
    QCheckBox *autoGeneratePreview;
    QSpacerItem *verticalSpacer;
    QDockWidget *tools_dockWidget;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QComboBox *tool_comboBox;
    QStackedWidget *toolSettings_widget;
    QWidget *flowPoints_page;
    QWidget *gradientPoints_page;
    QWidget *flowBrush_page;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QDial *flowBrush_dial;
    QLabel *label_9;
    QSpinBox *flowBrush_size;
    QLabel *label_7;
    QSpinBox *flowBrush_magnitude;
    QLabel *label_8;
    QSpinBox *flowBrush_strength;
    QWidget *gradientCloning_page;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *gradClone_change_comboBox;
    QLabel *label_3;
    QSpinBox *gradClone_red_spinBox;
    QLabel *label_4;
    QSpinBox *gradClone_green_spinBox;
    QLabel *label_5;
    QSpinBox *gradClone_blue_spinBox;
    QCheckBox *gradientAdjust_clone;
    QWidget *eraser_page;
    QFormLayout *formLayout_3;
    QLabel *label_10;
    QSpinBox *eraser_size;
    QWidget *gradientBrush_page;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_11;
    QSpinBox *gradientBrush_size;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_12;
    QToolButton *gradientBrush_color;
    QSpacerItem *verticalSpacer_2;
    QWidget *markPassive_page;
    QFormLayout *formLayout_4;
    QLabel *label_13;
    QSpinBox *markPassive_size;
    QLabel *label_14;
    QComboBox *markPassive_mode;
    QWidget *addBezierCurve_page;
    QWidget *addBezierPoint_page;

    void setupUi(QMainWindow *FEMainWindow)
    {
        if (FEMainWindow->objectName().isEmpty())
            FEMainWindow->setObjectName(QString::fromUtf8("FEMainWindow"));
        FEMainWindow->resize(724, 537);
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
        action_Export_flow_map_fast = new QAction(FEMainWindow);
        action_Export_flow_map_fast->setObjectName(QString::fromUtf8("action_Export_flow_map_fast"));
        actionExport_flow_map_AKIMA = new QAction(FEMainWindow);
        actionExport_flow_map_AKIMA->setObjectName(QString::fromUtf8("actionExport_flow_map_AKIMA"));
        action_Generate_grid = new QAction(FEMainWindow);
        action_Generate_grid->setObjectName(QString::fromUtf8("action_Generate_grid"));
        action_Flow_field = new QAction(FEMainWindow);
        action_Flow_field->setObjectName(QString::fromUtf8("action_Flow_field"));
        action_Project = new QAction(FEMainWindow);
        action_Project->setObjectName(QString::fromUtf8("action_Project"));
        action_Generate_gradient_grid = new QAction(FEMainWindow);
        action_Generate_gradient_grid->setObjectName(QString::fromUtf8("action_Generate_gradient_grid"));
        actionShow_li_cense = new QAction(FEMainWindow);
        actionShow_li_cense->setObjectName(QString::fromUtf8("actionShow_li_cense"));
        centralWidget = new QWidget(FEMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(graphicsView);

        horizontalLayout->setStretch(0, 1);
        FEMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FEMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 724, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuE_xport_flow_map = new QMenu(menu_File);
        menuE_xport_flow_map->setObjectName(QString::fromUtf8("menuE_xport_flow_map"));
        menu_New = new QMenu(menu_File);
        menu_New->setObjectName(QString::fromUtf8("menu_New"));
        menu_Load = new QMenu(menu_File);
        menu_Load->setObjectName(QString::fromUtf8("menu_Load"));
        FEMainWindow->setMenuBar(menuBar);
        dockWidget = new QDockWidget(FEMainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        previewBtn = new QPushButton(dockWidgetContents);
        previewBtn->setObjectName(QString::fromUtf8("previewBtn"));
        previewBtn->setCheckable(true);

        verticalLayout_3->addWidget(previewBtn);

        fileBtn = new QPushButton(dockWidgetContents);
        fileBtn->setObjectName(QString::fromUtf8("fileBtn"));

        verticalLayout_3->addWidget(fileBtn);

        expAndSwitchBtn = new QPushButton(dockWidgetContents);
        expAndSwitchBtn->setObjectName(QString::fromUtf8("expAndSwitchBtn"));

        verticalLayout_3->addWidget(expAndSwitchBtn);

        autoGeneratePreview = new QCheckBox(dockWidgetContents);
        autoGeneratePreview->setObjectName(QString::fromUtf8("autoGeneratePreview"));
        autoGeneratePreview->setChecked(true);

        verticalLayout_3->addWidget(autoGeneratePreview);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        dockWidget->setWidget(dockWidgetContents);
        FEMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        tools_dockWidget = new QDockWidget(FEMainWindow);
        tools_dockWidget->setObjectName(QString::fromUtf8("tools_dockWidget"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(dockWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        tool_comboBox = new QComboBox(dockWidgetContents_2);
        tool_comboBox->setObjectName(QString::fromUtf8("tool_comboBox"));

        verticalLayout_4->addWidget(tool_comboBox);

        toolSettings_widget = new QStackedWidget(dockWidgetContents_2);
        toolSettings_widget->setObjectName(QString::fromUtf8("toolSettings_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolSettings_widget->sizePolicy().hasHeightForWidth());
        toolSettings_widget->setSizePolicy(sizePolicy);
        flowPoints_page = new QWidget();
        flowPoints_page->setObjectName(QString::fromUtf8("flowPoints_page"));
        toolSettings_widget->addWidget(flowPoints_page);
        gradientPoints_page = new QWidget();
        gradientPoints_page->setObjectName(QString::fromUtf8("gradientPoints_page"));
        toolSettings_widget->addWidget(gradientPoints_page);
        flowBrush_page = new QWidget();
        flowBrush_page->setObjectName(QString::fromUtf8("flowBrush_page"));
        formLayout_2 = new QFormLayout(flowBrush_page);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_6 = new QLabel(flowBrush_page);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        flowBrush_dial = new QDial(flowBrush_page);
        flowBrush_dial->setObjectName(QString::fromUtf8("flowBrush_dial"));
        flowBrush_dial->setMaximum(359);
        flowBrush_dial->setValue(180);
        flowBrush_dial->setSliderPosition(180);
        flowBrush_dial->setInvertedAppearance(true);
        flowBrush_dial->setInvertedControls(false);
        flowBrush_dial->setWrapping(true);
        flowBrush_dial->setNotchTarget(3.7);
        flowBrush_dial->setNotchesVisible(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, flowBrush_dial);

        label_9 = new QLabel(flowBrush_page);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_9);

        flowBrush_size = new QSpinBox(flowBrush_page);
        flowBrush_size->setObjectName(QString::fromUtf8("flowBrush_size"));
        flowBrush_size->setMaximum(255);
        flowBrush_size->setValue(100);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, flowBrush_size);

        label_7 = new QLabel(flowBrush_page);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        flowBrush_magnitude = new QSpinBox(flowBrush_page);
        flowBrush_magnitude->setObjectName(QString::fromUtf8("flowBrush_magnitude"));
        flowBrush_magnitude->setMaximum(100);
        flowBrush_magnitude->setValue(100);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, flowBrush_magnitude);

        label_8 = new QLabel(flowBrush_page);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_8);

        flowBrush_strength = new QSpinBox(flowBrush_page);
        flowBrush_strength->setObjectName(QString::fromUtf8("flowBrush_strength"));
        flowBrush_strength->setMaximum(100);
        flowBrush_strength->setValue(10);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, flowBrush_strength);

        toolSettings_widget->addWidget(flowBrush_page);
        gradientCloning_page = new QWidget();
        gradientCloning_page->setObjectName(QString::fromUtf8("gradientCloning_page"));
        formLayout = new QFormLayout(gradientCloning_page);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_2 = new QLabel(gradientCloning_page);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        gradClone_change_comboBox = new QComboBox(gradientCloning_page);
        gradClone_change_comboBox->setObjectName(QString::fromUtf8("gradClone_change_comboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, gradClone_change_comboBox);

        label_3 = new QLabel(gradientCloning_page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        gradClone_red_spinBox = new QSpinBox(gradientCloning_page);
        gradClone_red_spinBox->setObjectName(QString::fromUtf8("gradClone_red_spinBox"));
        gradClone_red_spinBox->setMinimum(-255);
        gradClone_red_spinBox->setMaximum(255);

        formLayout->setWidget(1, QFormLayout::FieldRole, gradClone_red_spinBox);

        label_4 = new QLabel(gradientCloning_page);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        gradClone_green_spinBox = new QSpinBox(gradientCloning_page);
        gradClone_green_spinBox->setObjectName(QString::fromUtf8("gradClone_green_spinBox"));
        gradClone_green_spinBox->setMinimum(-255);
        gradClone_green_spinBox->setMaximum(255);

        formLayout->setWidget(2, QFormLayout::FieldRole, gradClone_green_spinBox);

        label_5 = new QLabel(gradientCloning_page);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        gradClone_blue_spinBox = new QSpinBox(gradientCloning_page);
        gradClone_blue_spinBox->setObjectName(QString::fromUtf8("gradClone_blue_spinBox"));
        gradClone_blue_spinBox->setMinimum(-255);
        gradClone_blue_spinBox->setMaximum(255);

        formLayout->setWidget(3, QFormLayout::FieldRole, gradClone_blue_spinBox);

        gradientAdjust_clone = new QCheckBox(gradientCloning_page);
        gradientAdjust_clone->setObjectName(QString::fromUtf8("gradientAdjust_clone"));

        formLayout->setWidget(4, QFormLayout::FieldRole, gradientAdjust_clone);

        toolSettings_widget->addWidget(gradientCloning_page);
        eraser_page = new QWidget();
        eraser_page->setObjectName(QString::fromUtf8("eraser_page"));
        formLayout_3 = new QFormLayout(eraser_page);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_10 = new QLabel(eraser_page);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_10);

        eraser_size = new QSpinBox(eraser_page);
        eraser_size->setObjectName(QString::fromUtf8("eraser_size"));
        eraser_size->setMaximum(255);
        eraser_size->setValue(100);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, eraser_size);

        toolSettings_widget->addWidget(eraser_page);
        gradientBrush_page = new QWidget();
        gradientBrush_page->setObjectName(QString::fromUtf8("gradientBrush_page"));
        verticalLayout_2 = new QVBoxLayout(gradientBrush_page);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_11 = new QLabel(gradientBrush_page);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_11);

        gradientBrush_size = new QSpinBox(gradientBrush_page);
        gradientBrush_size->setObjectName(QString::fromUtf8("gradientBrush_size"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gradientBrush_size->sizePolicy().hasHeightForWidth());
        gradientBrush_size->setSizePolicy(sizePolicy2);
        gradientBrush_size->setMaximum(255);
        gradientBrush_size->setValue(10);

        horizontalLayout_3->addWidget(gradientBrush_size);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_12 = new QLabel(gradientBrush_page);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_12);

        gradientBrush_color = new QToolButton(gradientBrush_page);
        gradientBrush_color->setObjectName(QString::fromUtf8("gradientBrush_color"));
        sizePolicy2.setHeightForWidth(gradientBrush_color->sizePolicy().hasHeightForWidth());
        gradientBrush_color->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(gradientBrush_color);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        toolSettings_widget->addWidget(gradientBrush_page);
        markPassive_page = new QWidget();
        markPassive_page->setObjectName(QString::fromUtf8("markPassive_page"));
        formLayout_4 = new QFormLayout(markPassive_page);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_13 = new QLabel(markPassive_page);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_13);

        markPassive_size = new QSpinBox(markPassive_page);
        markPassive_size->setObjectName(QString::fromUtf8("markPassive_size"));
        markPassive_size->setMaximum(255);
        markPassive_size->setValue(10);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, markPassive_size);

        label_14 = new QLabel(markPassive_page);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_14);

        markPassive_mode = new QComboBox(markPassive_page);
        markPassive_mode->setObjectName(QString::fromUtf8("markPassive_mode"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, markPassive_mode);

        toolSettings_widget->addWidget(markPassive_page);
        addBezierCurve_page = new QWidget();
        addBezierCurve_page->setObjectName(QString::fromUtf8("addBezierCurve_page"));
        toolSettings_widget->addWidget(addBezierCurve_page);
        addBezierPoint_page = new QWidget();
        addBezierPoint_page->setObjectName(QString::fromUtf8("addBezierPoint_page"));
        toolSettings_widget->addWidget(addBezierPoint_page);

        verticalLayout_4->addWidget(toolSettings_widget);

        tools_dockWidget->setWidget(dockWidgetContents_2);
        FEMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), tools_dockWidget);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(menu_New->menuAction());
        menu_File->addAction(menu_Load->menuAction());
        menu_File->addAction(action_Save_flow_field);
        menu_File->addAction(menuE_xport_flow_map->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionShow_li_cense);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menuE_xport_flow_map->addAction(action_Export_flow_map_fast);
        menuE_xport_flow_map->addAction(actionExport_flow_map_AKIMA);
        menuE_xport_flow_map->addAction(action_Export_flow_map);
        menu_New->addAction(action_Project);
        menu_New->addAction(action_Flow_field);
        menu_New->addSeparator();
        menu_New->addAction(action_Generate_grid);
        menu_New->addAction(action_Generate_gradient_grid);
        menu_Load->addAction(action_Load_image);
        menu_Load->addAction(action_Load_flow_field);

        retranslateUi(FEMainWindow);
        QObject::connect(tool_comboBox, SIGNAL(currentIndexChanged(int)), toolSettings_widget, SLOT(setCurrentIndex(int)));

        toolSettings_widget->setCurrentIndex(8);


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
        action_Export_flow_map_fast->setText(QApplication::translate("FEMainWindow", "Linear Interpolation", 0, QApplication::UnicodeUTF8));
        actionExport_flow_map_AKIMA->setText(QApplication::translate("FEMainWindow", "Cubic Interpolation", 0, QApplication::UnicodeUTF8));
        action_Generate_grid->setText(QApplication::translate("FEMainWindow", "&Generate flow grid", 0, QApplication::UnicodeUTF8));
        action_Flow_field->setText(QApplication::translate("FEMainWindow", "&Flow field", 0, QApplication::UnicodeUTF8));
        action_Project->setText(QApplication::translate("FEMainWindow", "&Project", 0, QApplication::UnicodeUTF8));
        action_Generate_gradient_grid->setText(QApplication::translate("FEMainWindow", "Generate g&radient grid", 0, QApplication::UnicodeUTF8));
        actionShow_li_cense->setText(QApplication::translate("FEMainWindow", "Show li&cense", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("FEMainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuE_xport_flow_map->setTitle(QApplication::translate("FEMainWindow", "E&xport flow map", 0, QApplication::UnicodeUTF8));
        menu_New->setTitle(QApplication::translate("FEMainWindow", "&New", 0, QApplication::UnicodeUTF8));
        menu_Load->setTitle(QApplication::translate("FEMainWindow", "&Load", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("FEMainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        previewBtn->setText(QString());
        fileBtn->setText(QApplication::translate("FEMainWindow", "&File", 0, QApplication::UnicodeUTF8));
        expAndSwitchBtn->setText(QApplication::translate("FEMainWindow", "&Repeat Last Export", 0, QApplication::UnicodeUTF8));
        autoGeneratePreview->setText(QApplication::translate("FEMainWindow", "Auto preview", 0, QApplication::UnicodeUTF8));
        tools_dockWidget->setWindowTitle(QApplication::translate("FEMainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FEMainWindow", "Tool:", 0, QApplication::UnicodeUTF8));
        tool_comboBox->clear();
        tool_comboBox->insertItems(0, QStringList()
         << QApplication::translate("FEMainWindow", "Flow points", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Gradient points", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Flow brush", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Gradient adjust", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Eraser", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Gradient brush", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Mark passive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Add Bezier curve", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Add Bezier point", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("FEMainWindow", "Direction:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FEMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FEMainWindow", "Magnitude:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FEMainWindow", "Strength:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FEMainWindow", "Change:", 0, QApplication::UnicodeUTF8));
        gradClone_change_comboBox->clear();
        gradClone_change_comboBox->insertItems(0, QStringList()
         << QApplication::translate("FEMainWindow", "Absolute", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Relative", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("FEMainWindow", "Red:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FEMainWindow", "Green:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FEMainWindow", "Blue:", 0, QApplication::UnicodeUTF8));
        gradientAdjust_clone->setText(QApplication::translate("FEMainWindow", "Clone", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FEMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FEMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("FEMainWindow", "Color:", 0, QApplication::UnicodeUTF8));
        gradientBrush_color->setText(QString());
        label_13->setText(QApplication::translate("FEMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("FEMainWindow", "Mode:", 0, QApplication::UnicodeUTF8));
        markPassive_mode->clear();
        markPassive_mode->insertItems(0, QStringList()
         << QApplication::translate("FEMainWindow", "Set passive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Set active", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FEMainWindow", "Flip", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class FEMainWindow: public Ui_FEMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEMAINWINDOW_H
