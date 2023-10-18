#ifndef S21_CREDIT_CALC_H_
#define S21_CREDIT_CALC_H_

#include <cmath>
#include <iostream>
#include <list>
#include <string>

namespace s21 {
struct ResultCreditData {
  double final_sum;
  double overpay;
  double first_pay;
  double last_pay;

  ResultCreditData(double final_sum, double overpay, double first_pay,
                   double last_pay)
      : final_sum(final_sum),
        overpay(overpay),
        first_pay(first_pay),
        last_pay(last_pay) {}
};

struct InputCreditData {
  double start_sum;
  int credit_term;
  double interest_rate;
  int credit_type;

  InputCreditData(double start_sum, int credit_term, double interest_rate,
                  int credit_type)
      : start_sum(start_sum),
        credit_term(credit_term),
        interest_rate(interest_rate),
        credit_type(credit_type) {}
};
};  // namespace s21

namespace s21 {
class CreditCalc {
 public:
  // CreditCalc() noexcept;
  void CheckCreditCalcFunction(const struct InputCreditData &input_values);
  struct ResultCreditData calculating();

  void AnuityCreditType();
  void DifferentiatedCreditType();

 private:
  double start_sum_;
  int credit_term_;
  double interest_rate_;
  int credit_type_;

  double final_sum_;
  double overpay_;
  double first_pay_;
  double last_pay_;
  bool credit_status_;

  //   ResultCreditData result{};
};
}  // namespace s21

#endif  // S21_CREDIT_CALC_H_
