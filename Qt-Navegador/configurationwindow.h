#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class ConfigurationWindow : public QDialog
{
  Q_OBJECT
public:
  explicit ConfigurationWindow(const QString& homepage, QWidget *parent = 0);

private:
  QPushButton* ok_;
  QPushButton* cancel_;
  QLineEdit* homepage_;

signals:
  void homepageSaved(QString url);

public slots:
  void onSaveHomepage();

};

#endif // CONFIGURATIONWINDOW_H
