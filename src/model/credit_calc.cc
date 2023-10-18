#include "credit_calc.h"

/**
 * @brief В файле выполняюся вычисления по кредиту
 * входные параметры сумма кредита, процент, срок кредита, тип кредита,
 * аттуитентный или диффиринцированный
 *
 */

namespace s21 {
/**
 * @brief Функция валидации входных значений
 *
 * @param input_values - структура с входными значениями
 */
void CreditCalc::CheckCreditCalcFunction(const InputCreditData &input_values) {
  start_sum_ = input_values.start_sum;
  credit_term_ = input_values.credit_term;
  interest_rate_ = input_values.interest_rate;
  credit_type_ = input_values.credit_type;

  if (credit_term_ >= 0 && start_sum_ >= 0 && interest_rate_ >= 0 &&
      (credit_type_ == 1 || credit_type_ == 2)) {
    credit_status_ = true;
  } else {
    throw std::invalid_argument("Incorrect values");
  }
}

/**
 * @brief функция вычисления средита
 *
 * @return struct ResultCreditData - структура с выходными даннвми, переплата,
 * финальная сумма кредита, ежемесячный платеж
 */
struct ResultCreditData CreditCalc::calculating() {
  if (credit_type_ == 1) {
    AnuityCreditType();
  } else {
    DifferentiatedCreditType();
  }

  ResultCreditData result(final_sum_, overpay_, first_pay_, last_pay_);
  return result;
}

/**
 * @brief Функция вычисления кредита аннуетентного типа
 *
 */
void CreditCalc::AnuityCreditType() {
  double monthly_pay = 0.0, monthly_rate = 0.0, period = 0.0;
  period = credit_term_ * (-1);
  monthly_rate = interest_rate_ / (100 * 12);

  monthly_pay =
      start_sum_ * (monthly_rate / (1 - pow((1 + monthly_rate), period)));

  first_pay_ = monthly_pay;
  last_pay_ = monthly_pay;
  final_sum_ = monthly_pay * credit_term_;
  overpay_ = final_sum_ - start_sum_;
}

/**
 * @brief Функция вычисления кредита дифференциированного типа
 *
 */
void CreditCalc::DifferentiatedCreditType() {
  double month_rate = 0.0, month_pay_middle = 0.0, month_overpay = 0.0,
         first_pay = 0.0, last_pay, overpay = 0.0;

  month_pay_middle = start_sum_ / credit_term_;
  month_rate = interest_rate_ / (100 * 12);

  double balance = start_sum_;
  double cur_period = credit_term_;

  while (cur_period) {
    month_overpay = balance * month_rate;
    if (cur_period == credit_term_) {
      first_pay = month_pay_middle + month_overpay;
    } else if (cur_period == 1) {
      last_pay = month_pay_middle + month_overpay;
    }
    overpay += month_overpay;
    balance -= month_pay_middle;
    cur_period--;
  }

  first_pay_ = first_pay;
  last_pay_ = last_pay;
  overpay_ = overpay;
  final_sum_ = start_sum_ + overpay;
}
};  // namespace s21
