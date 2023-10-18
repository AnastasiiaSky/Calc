#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/credit_calc.h"
#include "../model/smart_calc.h"

namespace s21 {

class Controller {
public:
  double Calculate(const std::string &expression, const std::string &x);
  double Calculate(const std::string &expression);
  static ResultCreditData
  credit_calculate(const struct InputCreditData &input_values);
};
} // namespace s21

#endif // CONTROLLER_H_