#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "../controller/controller.h"

namespace Ui {
class creditwindow;
}

class creditwindow : public QDialog {
  Q_OBJECT

 public:
  explicit creditwindow(QWidget *parent = nullptr);
  ~creditwindow();

  void CheckData();

 private slots:
  void keyPressEvent(QKeyEvent *e);
  void on_result_clicked();

  void on_clear_data_clicked();

  void on_back_tocalc_clicked();

 private:
  Ui::creditwindow *ui;
  double credit_sum, rate;
  int credit_type, time, time_type;
};

#endif  // CREDITWINDOW_H
