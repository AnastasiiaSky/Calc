#include "graphwindow.h"

#include "ui_graphwindow.h"

graphwindow::graphwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::graphwindow) {
  ui->setupUi(this);

  ui->graphic->setInteraction(QCP::iRangeZoom, true);
  ui->graphic->setInteraction(QCP::iRangeDrag, true);
}

void graphwindow::on_pushButton_create_graph_clicked() {
  if (CheckDataForGraph()) {
    FillInVectorsForPlot();
    ui->graphic->clearGraphs();
    ui->graphic->xAxis->setRange(ui->x_min->text().toDouble(),
                                 ui->x_max->text().toDouble());
    ui->graphic->yAxis->setRange(ui->y_min->text().toDouble(),
                                 ui->y_max->text().toDouble());
    ui->graphic->addGraph();
    ui->graphic->graph(0)->setData(X, Y);
    ui->graphic->replot();
    X.clear();
    Y.clear();
  }
}

bool graphwindow::CheckFunctionData() {
  std::string checking_string = ui->function->text().toStdString();
  for (int it = 0; it < checking_string.length(); ++it) {
    if (checking_string[it] == 'l' || checking_string[it] == 'L' &&
                                          (checking_string[it + 1] == 'o' ||
                                           checking_string[it + 1] == 'O') &&
                                          (checking_string[it + 2] == 'g' ||
                                           checking_string[it + 2] == 'G')) {
      return true;
    }
    if (checking_string[it] == 'l' ||
        checking_string[it] == 'L' && (checking_string[it + 1] == 'n' ||
                                       checking_string[it + 1] == 'N')) {
      return true;
    }
    if (checking_string[it] == 'S' || checking_string[it] == 's' &&
                                          (checking_string[it + 1] == 'q' ||
                                           checking_string[it + 1] == 'Q') &&
                                          (checking_string[it + 2] == 'r' ||
                                           checking_string[it + 2] == 'R')) {
      return true;
    }
  }
  return false;
}

bool graphwindow::CheckArcsinArccos() {
  std::string checking_string = ui->function->text().toStdString();
  for (int it = 0; it < checking_string.length(); ++it) {
    if ((checking_string[it] == 'a' || checking_string[it] == 'A') &&
        (checking_string[it + 1] == 's' || checking_string[it + 1] == 'S') &&
        (checking_string[it + 2] == 'i' || checking_string[it + 2] == 'i') &&
        (checking_string[it + 3] == 'n' || checking_string[it + 3] == 'N')) {
      return true;
    }
    if ((checking_string[it] == 'a' || checking_string[it] == 'A') &&
        (checking_string[it + 1] == 'c' || checking_string[it + 1] == 'C') &&
        (checking_string[it + 2] == 'o' || checking_string[it + 2] == 'O') &&
        (checking_string[it + 3] == 's' || checking_string[it + 3] == 'S')) {
      return true;
    }
  }
  return false;
}

bool graphwindow::CheckDataForGraph() {
  if (ui->y_max->text().toStdString() == ui->y_min->text().toStdString() &&
      ui->y_min->text().toStdString() == "0.0") {
    QMessageBox::warning(this, "Warning",
                         "Не введено значение для Y-max и Y-min");
    return false;
  }
  if (ui->x_max->text().toStdString() == ui->x_min->text().toStdString() &&
      ui->x_min->text().toStdString() == "0.0") {
    QMessageBox::warning(this, "Warning",
                         "Не введено значение для X-max и X-min");
    return false;
  }
  if (ui->function->text().toStdString().empty()) {
    QMessageBox::warning(
        this, "Warning",
        "Не введена функция для которой необходимо построить график");
    return false;
  }
  return true;
}

void graphwindow::FillInVectorsForPlot() {
  X.clear();
  Y.clear();
  double x = 0, xmax = 0, xmin;
  if (CheckFunctionData()) {
    xmin = 0;
    x = 0;
    xmax = ui->x_max->text().toDouble();
  } else if (CheckArcsinArccos()) {
    xmin = -1;
    x = -1;
    xmax = 1;
  } else {
    xmin = ui->x_min->text().toDouble();
    x = ui->x_min->text().toDouble();
    xmax = ui->x_max->text().toDouble();
  }
  double step = ui->step->text().toDouble();
  s21::Controller controller;
  for (x = xmin; x <= xmax; x += step) {
    X.push_back(x);
    double y;
    std::string x_value;
    x_value = std::to_string(x);
    y = controller.Calculate(ui->function->text().toStdString(), x_value);
    Y.push_back(y);
  }
}

graphwindow::~graphwindow() { delete ui; }

void graphwindow::on_pushButton_clear_graph_clicked() {
  ui->graphic->clearGraphs();
  ui->function->clear();
  ui->x_max->clear();
  ui->x_min->clear();
  ui->y_max->clear();
  ui->y_min->clear();
}

void graphwindow::on_pushButton_back_to_calc_clicked() { this->close(); }
