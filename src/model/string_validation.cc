#include "string_validation.h"

/**
 * @brief Данный файл содержит функции валидации входящей строки.
 * А имеено: валидация входящей х_стрки и входящей строки значений.
 * Все методы валидации выполнены в пространсве имен  namespace s21
 * Валидация строки вызывается в классе SmartCalc
 */

namespace s21 {

/**
 * @brief Функция проверки входящей строки со значением х.
 * В результате выполнения функции программа получает ответ,
 * валидно ли значение х или нет.
 *
 * @param expression - это std::string x_value - строка со значением х
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool StringValidator::ValidationX(const std::string &expression) const {
  if (expression[0] == '-' || expression[0] == '+' || isdigit(expression[0])) {
    return true;
  }
  for (size_t it = 0; it < expression.length(); ++it) {
    if (expression[it] == '-' || expression[it] == '+' ||
        expression[it] == 'e' || expression[it] == 'E' ||
        expression[it] == '.' || isdigit(expression[it])) {
      return true;
    } else {
      return false;
      break;
    }
  }
  return true;
}

/**
 * @brief Функция проверяет длинну стрки, а именно, если строка пустая или
 * больше 255 символов, возвращается результат false
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool s21::StringValidator::LengthValidation(const std::string &input) const {
  if (input.empty()) {
    throw std::invalid_argument("Your input is empty! =(");
    return false;
  }

  if (input.length() > 255) {
    throw std::invalid_argument("Your input is too long! =(");
    return false;
  }
  return true;
}

/**
 * @brief Валидация первого символа входной строки.
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool StringValidator::FirstSimbolValidation(
    const std::string &expression) const {
  if (expression[0] == ')' || expression[0] == '*' || expression[0] == '/' ||
      expression[0] == '^' || expression[0] == '%' || expression[0] == 'E' ||
      expression[0] == 'e') {
    throw std::invalid_argument(
        "Really!? Your first simbol of the string is "
        "incorrect! Check it and try again! =(");
    return false;
  }
  return true;
}

/**
 * @brief Валидация числовых значений строки.
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool s21::StringValidator::NumberValidation(
    const std::string &expression) const {
  bool point = false;
  for (size_t it = 0; it < expression.length(); ++it) {
    while (std::isdigit(expression[it]) || expression[it] == '.' ||
           expression[it] == 'e' || expression[it] == 'E' ||
           expression[it] == '-' || expression[it] == '+') {
      it++;
      if (expression[it] == '.') {
        if (point == true) {
          throw std::invalid_argument("Really!? Your number has two '.'! =(");
          return false;
        } else {
          point = true;
        }
      }
      if (expression[it] == ' ') {
        point = false;
      }
      if (expression[it] == 'E' || expression[it] == 'e') {
        if (expression[it + 1] == '+' || expression[it + 1] == '-') {
          if (!(std::isdigit(expression[it + 2]))) {
            throw std::invalid_argument(
                "You are using exponential form a number, so after +/- you "
                "should write a degree of a number! =(");
            return false;
          }
        } else {
          throw std::invalid_argument(
              "You are using exponential form a number, so after E/e you "
              "should write a sign and degree of a number! =(");
          return false;
        }
      }
    }
  }
  return true;
}

/**
 * @brief Валидация колличества пробелов в входной строке.
 * В входной строке не может быть более двух пробелов подряд.
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool StringValidator::SpaceValidation(const std::string &expression) const {
  for (size_t it = 0; it < expression.length(); ++it) {
    if (expression[it] == ' ' && expression[it + 1] == ' ') {
      throw std::invalid_argument(
          "Sorry! Check amout of spaces in your expression =(");
      return false;
    }
  }
  return true;
}

/**
 * @brief Валидация операций в входной строке.
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool s21::StringValidator::OperationValidation(
    const std::string &expression) const {
  for (size_t it = 0; it < expression.length(); ++it) {
    if ((expression[it] == '*' || expression[it] == '/' ||
         expression[it] == '%' || expression[it] == '^' ||
         expression[it] == '+' || expression[it] == '-') &&
        (expression[it + 1] == '*' || expression[it + 1] == '/' ||
         expression[it + 1] == '%' || expression[it + 1] == '^')) {
      throw std::invalid_argument(
          "Really!? Your have ivalid arguments! Check your string =(");
      return false;
    } else if (expression[it] == '-' && expression[it + 1] == '-' &&
               expression[it + 2] == '-') {
      throw std::invalid_argument(
          "OMG!!! What happand? You really want to add three minus signs? =(");
      return false;
    } else if ((expression[it] == '*' || expression[it] == '/' ||
                expression[it] == '%' || expression[it] == '^' ||
                expression[it] == '+' || expression[it] == '-') &&
               (expression[it + 1] == '*' || expression[it + 1] == '/' ||
                expression[it + 1] == '%' || expression[it + 1] == '^') &&
               (expression[it + 2] == '*' || expression[it + 2] == '/' ||
                expression[it + 2] == '%' || expression[it + 2] == '^' ||
                expression[it + 2] == '+' || expression[it + 2] == '-')) {
      throw std::invalid_argument("OMG!!! Are you okey? =(");
      return false;
    }
  }
  return true;
}

/**
 * @brief Валидация скобок в входной строке.
 *
 * @param input - входная строка из пользовательсткого интерфейса
 * @return true - строка валидна
 * @return false - строка не валидна
 */

bool StringValidator::BracketsValidation(const std::string &expression) const {
  for (size_t it = 0; it < expression.length(); ++it) {
    if ((expression[it] == '(' &&
         (expression[it + 1] == ')' || expression[it + 1] == '*' ||
          expression[it + 1] == '/' || expression[it + 1] == '^' ||
          expression[it + 1] == '%')) ||
        ((expression[it] == ')' &&
          (expression[it + 1] == '(' || std::isdigit(expression[it + 1]))))) {
      throw std::invalid_argument(
          "Really!? Your have ivalid arguments after "
          "'('! Check your string =(");
      return false;
    }
  }
  return true;
}

};  // namespace s21
