#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTabWidget>


namespace Ui {
	class IntelSettingDialog;
}

class IntelSettingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit IntelSettingDialog(QWidget *parent = 0);
	~IntelSettingDialog();

private:
	Ui::IntelSettingDialog *ui;
};

#endif // DIALOG_H
