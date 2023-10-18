#include "creditwindow.h"

#include "ui_creditwindow.h"

creditwindow::creditwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::creditwindow) {
  ui->setupUi(this);
}

creditwindow::~creditwindow() { delete ui; }

void creditwindow::on_result_clicked() {
  CheckData();
  credit_sum = ui->credit_sum->text().toDouble();
  rate = ui->rate->text().toDouble();
  if (ui->credit_type->currentIndex() == 0) {
    credit_type = 1;
  } else {
    credit_type = 2;
  }

  if (ui->month_or_years->currentIndex() == 1) {
    time = ui->time->text().toInt() * 12;
  } else {
    time = ui->time->text().toInt();
  }

  s21::InputCreditData input_data = {credit_sum, time, rate, credit_type};
  s21::Controller controller;
  s21::ResultCreditData credit_result = {0.0, 0.0, 0.0, 0.0};
  credit_result = controller.credit_calculate(input_data);

  QString final_sum, overpay, first_pay, last_pay;

  final_sum = QString::number(credit_result.final_sum, 'g', 10);
  overpay = QString::number(credit_result.overpay, 'g', 10);
  first_pay = QString::number(credit_result.first_pay, 'g', 10);
  first_pay += "...";
  last_pay = QString::number(credit_result.last_pay, 'g', 10);
  last_pay = "..." + last_pay;

  ui->final_sum->setText(final_sum);
  ui->final_rate_amout->setText(overpay);
  ui->first_pay->setText(first_pay);
  ui->last_pay->setText(last_pay);
}

void creditwindow::CheckData() {
  if (ui->credit_sum->text().isEmpty()) {
    QMessageBox::warning(this, "Warning", "Не введена сумма кредита");
  }

  if (ui->time->text().isEmpty()) {
    QMessageBox::warning(this, "Warning", "Не введен срок кредита");
  }

  if (ui->rate->text().isEmpty()) {
    QMessageBox::warning(this, "Warning",
                         "Не введена процентная ставка кредита");
  }
}

void creditwindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    on_result_clicked();

  } else if (e->key() == Qt::Key_Escape) {
    this->close();
  }
}

void creditwindow::on_clear_data_clicked() {
  ui->credit_sum->clear();
  ui->credit_type->clear();
  ui->final_rate_amout->clear();
  ui->final_sum->clear();
  ui->first_pay->clear();
  ui->last_pay->clear();
  ui->rate->clear();
  ui->time->clear();
}

void creditwindow::on_back_tocalc_clicked() { this->close(); }
