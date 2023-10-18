#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVector>

#include "../controller/controller.h"
#include "library/qcustomplot.h"

namespace Ui {
class graphwindow;
}

class graphwindow : public QDialog {
  Q_OBJECT

 public:
  explicit graphwindow(QWidget *parent = nullptr);
  ~graphwindow();

  bool CheckDataForGraph();
  void FillInVectorsForPlot();
  bool CheckFunctionData();
  bool CheckArcsinArccos();

 private slots:
  void on_pushButton_create_graph_clicked();

  void on_pushButton_clear_graph_clicked();

  void on_pushButton_back_to_calc_clicked();

 private:
  Ui::graphwindow *ui;
  QVector<double> X, Y;
};

#endif  // GRAPHWINDOW_H
