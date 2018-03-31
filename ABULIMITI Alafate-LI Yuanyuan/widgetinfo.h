#ifndef WIDGETINFO_H
#define WIDGETINFO_H

#include <QWidget>

namespace Ui {
class WidgetInfo;
}

class WidgetInfo : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetInfo(QWidget *parent = 0);
    ~WidgetInfo();

private:
    Ui::WidgetInfo *ui;
};

#endif // WIDGETINFO_H
