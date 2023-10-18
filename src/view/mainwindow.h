#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <string>

#include "../controller/controller.h"
#include "creditwindow.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  bool CheckStringForDot();
  bool OperationChecking();
  bool ExpoNumberChecking();
  bool FunctionChecking();
  bool ZeroChecking();
  bool CheckingResultStringFirstSimbol();
  bool TrigonometryChecking();

 private:
  Ui::MainWindow *ui;
  graphwindow grafic;
  creditwindow credit;

  QString input_string;
  QString x_input_string;
  QString output_string;
  std::string result_string;
  std::string x_result_string;
  std::string calculation_result;

 private slots:
  void keyPressEvent(QKeyEvent *e);
  void DigitsNumbers();
  void OnPushButtonPointClicked();
  void Operations();
  void ExpoNumber();
  void ExpoNumberPositiv();
  void Functions();
  void DeliteOneSimbol();
  void CleanString();
  void OnPushButtonXClicked();
  void OnPushButtonResultClicked();

  void on_pushButton_createGraf_clicked();
  void on_pushButton_creditCalc_clicked();
};
#endif  // MAINWINDOW_H
