#ifndef DIALOGPROPOSINFO_H
#define DIALOGPROPOSINFO_H

#include <QDialog>

namespace Ui {
class DialogProposInfo;
}

class DialogProposInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProposInfo(QWidget *parent = 0);
    ~DialogProposInfo();

private:
    Ui::DialogProposInfo *ui;
};

#endif // DIALOGPROPOSINFO_H
