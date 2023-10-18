#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(OnPushButtonPointClicked()));

  connect(ui->pushButton_e_negativ, SIGNAL(clicked()), this,
          SLOT(ExpoNumberPositiv()));
  connect(ui->pushButton_e_positiv, SIGNAL(clicked()), this,
          SLOT(ExpoNumber()));

  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(Operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(Functions()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(OnPushButtonXClicked()));

  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(DeliteOneSimbol()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(CleanString()));

  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(OnPushButtonResultClicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  input_string = (ui->result_show->text() + button->text());
  if (button->text() == '0') {
    ZeroChecking();
  }
  ui->result_show->setText(input_string);
}

void MainWindow::OnPushButtonPointClicked() {
  QPushButton *button = (QPushButton *)sender();
  input_string = (ui->result_show->text() + button->text());
  CheckStringForDot();
  ui->result_show->setText(input_string);
}

void MainWindow::ExpoNumber() {
  input_string = (ui->result_show->text() + 'e' + '+');
  ExpoNumberChecking();
  ui->result_show->setText(input_string);
}

void MainWindow::ExpoNumberPositiv() {
  input_string = (ui->result_show->text() + 'e' + '-');
  ExpoNumberChecking();
  ui->result_show->setText(input_string);
}

void MainWindow::Operations() {
  QPushButton *button = (QPushButton *)sender();
  input_string = (ui->result_show->text() + button->text());
  OperationChecking();
  ui->result_show->setText(input_string);
}

void MainWindow::Functions() {
  QPushButton *button = (QPushButton *)sender();
  input_string = (ui->result_show->text() + button->text() + '(');
  FunctionChecking();
  ui->result_show->setText(input_string);
}

void MainWindow::DeliteOneSimbol() {
  input_string.resize(input_string.size() - 1);
  ui->result_show->setText(input_string);
}

void MainWindow::CleanString() {
  input_string.clear();
  ui->result_show->setText(input_string);
}

void MainWindow::OnPushButtonXClicked() {
  input_string = (ui->result_show->text() + 'x');
  ui->result_show->setText(input_string);
}

void MainWindow::OnPushButtonResultClicked() {
  input_string = ui->result_show->text();
  result_string = input_string.toStdString();
  if (CheckingResultStringFirstSimbol() && TrigonometryChecking() &&
      ZeroChecking() && CheckStringForDot() && OperationChecking()) {
    std::string result;
    double result_number;
    s21::Controller controller;
    if (result_string.find('x') != std::string::npos) {
      result_number = controller.Calculate(input_string.toStdString(),
                                           ui->x_value->text().toStdString());
    } else {
      result_number = controller.Calculate(input_string.toStdString());
    }
    output_string = QString::number(result_number);
    ui->result_show->setText(output_string);
  }
}

bool MainWindow::ExpoNumberChecking() {
  std::string checking_string = input_string.toStdString();
  for (size_t it = 0; it < checking_string.length(); ++it) {
    if (checking_string[it] == 'e' &&
        (checking_string[it + 1] == '-' || checking_string[it + 1] == '+')) {
      if (!std::isdigit(checking_string[it - 1])) {
        QMessageBox::warning(
            this, "Warning",
            "e-n и e+n это представление действительных чисел в виде мантиссы "
            "и порядка. Поэтому перед e-n и e+n должно быть число, которое вы "
            "бы хотели представить в такой форме! Попробуй еще раз)");
        return false;
      }
    }
  }
  return true;
}

bool MainWindow::OperationChecking() {
  std::string checking_string = input_string.toStdString();
  for (size_t it = 0; it < checking_string.length(); ++it) {
    if ((checking_string[it] == '*' || checking_string[it] == '/' ||
         checking_string[it] == '^' || checking_string[it] == '%') &&
        (checking_string[it + 1] == '*' || checking_string[it + 1] == '/' ||
         checking_string[it + 1] == '^' || checking_string[it + 1] == '%')) {
      QMessageBox::warning(this, "Warning",
                           "Кажется, ты что-то делаешь не так!");
      return false;
    } else if (checking_string[it] == '(') {
      switch (checking_string[it + 1]) {
        case ')':
          QMessageBox::warning(
              this, "Warning",
              "Нельзя добавить пустые скобки, попробуй еще раз");
          return false;
          break;
        case '/':
          QMessageBox::warning(this, "Warning", "На что будем делить скобку?");
          return false;
          break;
        case '*':
          QMessageBox::warning(this, "Warning",
                               "На что будем умножать скобку?");
          return false;
          break;
        case '^':
          QMessageBox::warning(this, "Warning",
                               "В какую степень будем возводить скобку?");
          return false;
          break;
      }

    } else if ((checking_string[it] == '-' && checking_string[it + 1] == '-' &&
                (checking_string[it + 2] == '-' ||
                 checking_string[it + 2] == '+' ||
                 checking_string[it + 2] == '*' ||
                 checking_string[it + 2] == '/' ||
                 checking_string[it + 2] == '^')) ||
               (checking_string[it] == '+' && checking_string[it + 1] == '+' &&
                (checking_string[it + 2] == '-' ||
                 checking_string[it + 2] == '+' ||
                 checking_string[it + 2] == '*' ||
                 checking_string[it + 2] == '/' ||
                 checking_string[it + 2] == '^'))) {
      QMessageBox::warning(this, "Warning", "Не многовато ли знаков?");
      return false;
    } else if ((checking_string[it] == '-' || checking_string[it] == '+' ||
                checking_string[it] == '(' || checking_string[it] == ')' ||
                checking_string[it] == '*' || checking_string[it] == '/' ||
                checking_string[it] == '^') &&
               ((checking_string[it - 1] == '-' ||
                 checking_string[it - 1] == '+') &&
                checking_string[it - 2] == 'e')) {
      QMessageBox::warning(
          this, "Warning",
          "e-n и e+n это представление действительных чисел в виде мантиссы "
          "и порядка. Поэтому n должно быть числом. Попробуй еще раз)");
      return false;
    }
  }
  return true;
}

bool MainWindow::CheckStringForDot() {
  std::string checking_string = input_string.toStdString();
  for (size_t it = 0; it < checking_string.length(); ++it) {
    int point = 0;
    while ((std::isdigit(checking_string[it])) || checking_string[it] == '.' ||
           checking_string[it] == 'e' || checking_string[it] == '-' ||
           checking_string[it] == '+') {
      if (checking_string[it] == '.') {
        if (point > 0) {
          QMessageBox::warning(
              this, "Warning",
              "Оу, в числе не может быть больше одной точки! Давай еще раз!");
          return false;
        }
        ++point;
      }
      ++it;
    }
  }
  return true;
}

bool MainWindow::ZeroChecking() {
  std::string checking_string = input_string.toStdString();
  for (size_t it = 0; it < checking_string.length(); ++it) {
    if (checking_string[it] == '0') {
      if (checking_string[it - 1] == '/') {
        QMessageBox::warning(this, "Warning",
                             "Ой! Ну ты чего? На ноль делить нельзя!");
        return false;
      } else if (checking_string[it - 1] == '%') {
        QMessageBox::warning(
            this, "Warning",
            "Ой! Ну ты чего? Как это остаток от деления на ноль?!");
        return false;
      }
    }
  }
  return true;
}

bool MainWindow::FunctionChecking() {
  std::string checking_string = input_string.toStdString();
  for (size_t it = 0; it < checking_string.length(); ++it) {
    if (checking_string[it] == 'e' &&
        (checking_string[it + 1] == '-' || checking_string[it + 1] == '+') &&
        (checking_string[it + 2] == 'L' || checking_string[it + 2] == 'S' ||
         checking_string[it + 2] == 'A' || checking_string[it + 2] == 'C' ||
         checking_string[it + 2] == 'T' || checking_string[it + 2] == 'M')) {
      QMessageBox::warning(this, "Warning",
                           "Нельзя добавить функцию в экспоненциальную форму "
                           "записи числа. Попробуй еще раз");
      return false;
    }
  }

  return true;
}

bool MainWindow::CheckingResultStringFirstSimbol() {
  TrigonometryChecking();
  if (result_string[0] == '*' || result_string[0] == '/' ||
      result_string[0] == '^' || result_string[0] == ')' ||
      result_string[0] == 'e' || result_string[0] == '.' ||
      result_string[0] == '%') {
    QMessageBox::warning(this, "Warning",
                         "Некорректно введена строка! Давай еще раз!");
    return false;
  }
  return true;
}

bool MainWindow::TrigonometryChecking() {
  size_t counter = 0;
  for (size_t it = 0; it < result_string.length(); ++it) {
    if (result_string[it] == '-') {
      if (result_string[it - 2] == 'N' && result_string[it - 3] == 'L') {
        QMessageBox::warning(this, "Warning",
                             "Функции LN/LOG не принимают отрицательные "
                             "значения, давай еще раз и без '-'");
        return false;
      } else if (result_string[it - 2] == 'G' && result_string[it - 3] == 'O' &&
                 result_string[it - 4] == 'L') {
        QMessageBox::warning(this, "Warning",
                             "Функции LN/LOG не принимают отрицательные "
                             "значения, давай еще раз и без '-'");
        return false;
      } else if (result_string[it - 2] == 'T' && result_string[it - 3] == 'R' &&
                 result_string[it - 4] == 'Q' && result_string[it - 5] == 'S') {
        QMessageBox::warning(this, "Warning",
                             "Не-не-не, нельзя вычислить корень из "
                             "отрицательного числа. Так не бывает.");
        return false;
      }
    }
    if (result_string[it] == '(') {
      ++counter;
    }
    if (result_string[it] == ')') {
      --counter;
    }
  }
  if (counter != 0) {
    QMessageBox::warning(this, "Warning", "Упс! Проверь скобки в выражении!");
    return false;
  }
  return true;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    OnPushButtonResultClicked();

  } else if (e->key() == Qt::Key_Escape) {
    this->close();
  }
}

void MainWindow::on_pushButton_createGraf_clicked() {
  grafic.setModal(true);
  grafic.exec();
}

void MainWindow::on_pushButton_creditCalc_clicked() {
  credit.setModal(true);
  credit.exec();
}
