#ifndef S21_STRING_VALODATION_H_
#define S21_STRING_VALODATION_H_

#include <cctype>
#include <iostream>
#include <string>

#include "smart_calc.h"

namespace s21 {
class StringValidator {
  friend class SmartCalc;

 public:
  bool ValidationX(const std::string &expression) const;
  bool LengthValidation(const std::string &expression) const;
  bool NumberValidation(const std::string &expression) const;
  bool SpaceValidation(const std::string &expression) const;
  bool OperationValidation(const std::string &expression) const;
  bool BracketsValidation(const std::string &expression) const;
  bool FirstSimbolValidation(const std::string &expression) const;
};
}  // namespace s21

#endif  // S21_STRING_VALODATION_H_
