#include "widgetinfo.h"
#include "ui_widgetinfo.h"

WidgetInfo::WidgetInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetInfo)
{
    ui->setupUi(this);
}

WidgetInfo::~WidgetInfo()
{
    delete ui;
}
