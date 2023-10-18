#include "controller.h"
/**
 * @brief Методы данного файла передают и информацию из view в model 
 * 
 */

namespace s21 {
/**
 * @brief Производит передачу данных из части вью в модель и вычисляет выражения, как для самого калькулятора так и для построения графиков
 */
double Controller::Calculate(const std::string &expression,
                             const std::string &x) {
  double result;
  s21::SmartCalc calc;
  result = calc.MainProcess(expression, x);
  return result;
}

double Controller::Calculate(const std::string &expression) {
  double result;
  s21::SmartCalc calc;
  result = calc.MainProcess(expression);
  return result;
}
/**
 * @brief Производит вычисления кредита приниямая данные из view, передавая в модель
 * 
 * @param input_values 
 * @return ResultCreditData 
 */
ResultCreditData
Controller::credit_calculate(const struct InputCreditData &input_values) {
  s21::CreditCalc credit;
  credit.CheckCreditCalcFunction(input_values);
  ResultCreditData result = credit.calculating();
  return result;
}
} // namespace s21