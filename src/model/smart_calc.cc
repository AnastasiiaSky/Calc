#include "smart_calc.h"
/**
 * @brief В файле описана модель калькулятора, а именно:
 * парсинг строки и все вычисления.
 *  Все методы выполнены в пространсве имен  namespace s21
 */

namespace s21 {

/**
 * @brief Главный метод вызывающий валидацию, парсинг и вычисления для входящей
 * строки и строки со значением х, если таковое введено.
 *
 *
 * @param input_string - входная строка введенная пользователем.
 * @param x_input - входная строка со значением х введенная пользователем.
 * @return double - результат вычисления выражения.
 */
double SmartCalc::MainProcess(const std::string &input_string,
                              const std::string &x_input) {
  if (!MakeAllValidation(input_string, x_input)) {
    throw std::invalid_argument("Something went wrong! =(");
  }
  double x = get_x_from_input(x_input);
  Tockens x_tocken(x, NUMBER, 0);
  ParceInputString(input_string, x_tocken);
  WhenStringFinished();
  double result = CalculationProcess(parsed_string_, my_stack_);
  return result;
}

/**
 * @brief Главнаый метод вызывающий валидацию, парсинг и вычисления для
 * входящей строки.
 *
 * @param input_string - входная строка введенная пользователем.
 * @return double - результат вычисления выражения.
 */

double SmartCalc::MainProcess(const std::string &input_string) {
  if (!MakeAllValidation(input_string)) {
    throw std::invalid_argument("Something went wrong! =(");
  }
  ParceInputString(input_string);
  WhenStringFinished();
  double result = CalculationProcess(parsed_string_, my_stack_);
  return result;
}

/**
 * @brief Метод вызывающий валидацию входной строки и строки со значением х.
 *
 * @param input_string - входная строка введенная пользователем.
 * @param x_input - входная строка со значением х введенная пользователем.
 * @return true - валидация пройдена.
 * @return false - валидация не пройдена.
 */

bool SmartCalc::MakeAllValidation(const std::string &input_string,
                                  const std::string &x_input) {
  s21::StringValidator validator;
  if (!validator.BracketsValidation(input_string) ||
      !validator.FirstSimbolValidation(input_string) ||
      !validator.LengthValidation(input_string) ||
      !validator.NumberValidation(input_string) ||
      !validator.OperationValidation(input_string) ||
      !validator.SpaceValidation(input_string) ||
      !validator.ValidationX(x_input)) {
    return false;
  }
  return true;
}

/**
 * @brief Метод вызывающий валидацию входной строки.
 *
 * @param input_string - входная строка введенная пользователем.
 * @return true - валидация пройдена.
 * @return false - валидация не пройдена.
 */

bool SmartCalc::MakeAllValidation(const std::string &input_string) {
  s21::StringValidator validator;
  if (!validator.BracketsValidation(input_string) ||
      !validator.FirstSimbolValidation(input_string) ||
      !validator.LengthValidation(input_string) ||
      !validator.NumberValidation(input_string) ||
      !validator.OperationValidation(input_string) ||
      !validator.SpaceValidation(input_string)) {
    return false;
  }
  return true;
}

/**
 * @brief Метод получающий значение Х из введенного пользователем значения Х.
 *
 * @param x_input - входная строка со значением х введенная пользователем.
 * @return double - строка введенная пользователем преобразованная в число.
 */
double SmartCalc::get_x_from_input(const std::string &x_input) noexcept {
  double x_number = 0.0;
  for (size_t it = 0; it < x_input.length(); ++it) {
    if (IsNumber(x_input[it])) {
      x_number = ConstructNumber(&it, x_input);
    }
  }
  if (x_input[0] == '-') x_number *= -1;
  return x_number;
}

/**
 * @brief Метод парсинга входной строки.
 * Метод проверяет, является ли текущий символ числом, функцией или операцией.
 * Если текущий символ является числом, вызывается метод конструирующий число,
 * после чего данное число добавляется в выходную строку. Ессли текщий символ
 * операция, проверяется какая именно это опрация, после чего данная операция
 * добавляется в стэк или переносится выходную строку. Если текущий символ часть
 * наименования функции, прверяется какая именно это функция, после чего, данная
 * функция добавляется в стэк или переностится в выходную строку. Метод
 * испотльзует такие методы как: bool SmartCalc::IsNumber(char current_simbol)
 * noexcept; double SmartCalc::ConstructNumber(size_t *position, const
 * std::string &input_string) noexcept; bool IsOperation(char current_simbol)
 * noexcept; void WichOperation(size_t *position, const std::string
 * &input_string) noexcept; bool IsFunction(char current_simbol) noexcept; void
 * AddFunction(size_t *position, const std::string &input_string) noexcept;
 * @param input_string - входная строка введенная пользователем.
 */
void SmartCalc::ParceInputString(const std::string &input_string) {
  for (size_t it = 0; it < input_string.length(); ++it) {
    if (input_string[it] == ' ') {
      continue;
    } else if (IsNumber(input_string[it])) {
      double new_number = 0.0;
      new_number = ConstructNumber(&it, input_string);
      Tockens number_tocken(new_number, NUMBER, 0);
      parsed_string_.push_back(number_tocken);
    } else if (IsOperation(input_string[it])) {
      WichOperation(&it, input_string);
    } else if (IsFunction(input_string[it])) {
      AddFunction(&it, input_string);
    } else if (input_string[it] == 'x') {
      throw std::invalid_argument("Please fill in x value and try again =(");
    }
  }
}

/**
 * @brief Перегрузка метода парсинга входной строки, принимающая два параметра,
 * входную строку и числовое значение Х Метод проверяет, является ли текущий
 * символ числом, функцией или операцией. Если текущий символ является числом,
 * вызывается метод конструирующий число, после чего данное число добавляется в
 * выходную строку. Ессли текщий символ операция, проверяется какая именно это
 * опрация, после чего данная операция добавляется в выходную строку. Если
 * текущий символ часть наименования функции, прверяется какая именно это
 * функция, после чего, данная функция добавляется в выходную строку. Метод
 * испотльзует такие методы как: bool SmartCalc::IsNumber(char current_simbol)
 * noexcept; double SmartCalc::ConstructNumber(size_t *position, const
 * std::string &input_string) noexcept; bool IsOperation(char current_simbol)
 * noexcept; void WichOperation(size_t *position, const std::string
 * &input_string) noexcept; bool IsFunction(char current_simbol) noexcept; void
 * AddFunction(size_t *position, const std::string &input_string) noexcept;
 * @param input_string - входная строка введенная пользователем.
 * @param Tockens x_tocken - числовое значение Х, если при парсинге в строке
 * встречен "Х", то в выходную строку добавляется уже непосредственно числовое
 * значение Х.
 */
void SmartCalc::ParceInputString(const std::string &input_string,
                                 Tockens x_tocken) noexcept {
  for (size_t it = 0; it < input_string.length(); ++it) {
    if (input_string[it] == ' ') {
      continue;
    } else if (IsNumber(input_string[it])) {
      double new_number = 0.0;
      new_number = ConstructNumber(&it, input_string);
      Tockens number_tocken(new_number, NUMBER, 0);
      parsed_string_.push_back(number_tocken);
    } else if (IsOperation(input_string[it])) {
      WichOperation(&it, input_string);
    } else if (IsFunction(input_string[it])) {
      AddFunction(&it, input_string);
    } else if (input_string[it] == 'x') {
      parsed_string_.push_back(x_tocken);
    }
  }
}

/**
 * @brief Метод проверяет является ли текущий символ частью числа.
 * Метод вызывается в функциях void SmartCalc::ParceInputString(const
 * std::string &input_string, Tockens x_tocken); void
 * SmartCalc::ParceInputString(const std::string &input_string); double
 * SmartCalc::ConstructNumber(size_t *position, const std::string &input_string)
 * noexcept;
 * @param current_simbol - текущий проверяемый символ.
 * @return true - если символ число.
 * @return false  - если символ не число.
 */

bool SmartCalc::IsNumber(char current_simbol) noexcept {
  return std::isdigit(current_simbol) || current_simbol == '.' ||
         current_simbol == 'e' || current_simbol == 'E';
}

/**
 * @brief Метод преобразует символы-цифры строки в число, при помощи std::stod,
 * так же в методе проверяется является ли данное число положительным или
 * отрицательным, прсле чего для числа устанавливается знак. Метод вызывается из
 * методов: void SmartCalc::ParceInputString(const std::string &input_string,
 * Tockens x_tocken); void SmartCalc::ParceInputString(const std::string
 * &input_string); Метод возвращает число типа double. Метод использует методы:
 * std::string WorkWithExpoNumber(size_t *position, const std::string
 * &input_string);
 *
 * @param position - текущая позиция во входной строке.
 * @param input_string - входная страка введенная пользователем.
 * @return double  - результат выполнения функции, число типа double.
 */

double SmartCalc::ConstructNumber(size_t *position,
                                  const std::string &input_string) noexcept {
  std::string buffer_for_number = "\0";
  while (IsNumber(input_string[*position])) {
    if (input_string[*position] == 'E' || input_string[*position] == 'e') {
      std::string expo_part = WorkWithExpoNumber(position, input_string);
      buffer_for_number.append(expo_part);
      ++(*position);
    } else {
      buffer_for_number.push_back(input_string[*position]);
      ++(*position);
    }
  }
  buffer_for_number.push_back('\0');
  --(*position);
  double constructed_number = 0.0;
  constructed_number = std::stod(buffer_for_number);
  if (parsed_string_.back().operation_type == UNAR &&
      parsed_string_.back().operation_priority == 3) {
    constructed_number *= -1;
    parsed_string_.pop_back();
  }
  return constructed_number;
}

/**
 * @brief Метод работает с экспоненциальной формой числа и вызывается из метода
 * double SmartCalc::ConstructNumber(size_t *position, const std::string
 * &input_string) noexcept В методе используется функция проверки корректности
 * записи экспоненуиальной формы числа bool CheckExpoFormOfNumber(char
 * first_simbol, char second_simbol) noexcept;
 * @param position - текущая позиция во входной строке.
 * @param input_string - входная страка введенная пользователем.
 * @return std::string - строка, с запичсью экспоненчиальной части числа
 */

std::string SmartCalc::WorkWithExpoNumber(size_t *position,
                                          const std::string &input_string) {
  std::string expo_part_of_number;
  if ((CheckExpoFormOfNumber(input_string[*position + 1],
                             input_string[*position + 2]))) {
    expo_part_of_number = 'e';
    ++(*position);
    expo_part_of_number.push_back(input_string[*position]);
    ++(*position);
    expo_part_of_number.push_back(input_string[*position]);
    expo_part_of_number + '\0';
  }
  return std::string(expo_part_of_number);
}

/**
 * @brief Метод проверяет корректность введенной пользователем экспоненциальной
 * части числа, после "е"
 *
 * @param first_simbol - +/-.
 * @param second_simbol  - цифра.
 * @return true - корректно.
 * @return false - не корректно.
 */

bool SmartCalc::CheckExpoFormOfNumber(char first_simbol,
                                      char second_simbol) noexcept {
  return ((first_simbol == '+' || first_simbol == '-') &&
          (std::isdigit(second_simbol)));
}

/**
 * @brief Метод проверяет, является ли текущий символ одной из списка операций,
 * а имеено +-*%^()/ Вызывается методами: void SmartCalc::ParceInputString(const
 * std::string &input_string, Tockens x_tocken); void
 * SmartCalc::ParceInputString(const std::string &input_string);
 * @param current_simbol - текущий символ.
 * @return true - символ операция.
 * @return false - символ не операция.
 */

bool SmartCalc::IsOperation(char current_simbol) noexcept {
  return current_simbol == '+' || current_simbol == '-' ||
         current_simbol == '*' || current_simbol == '/' ||
         current_simbol == '%' || current_simbol == '^' ||
         current_simbol == '(' || current_simbol == ')';
}

/**
 * @brief Метод вычисляет какой операцией является секущий символ
 * input_string[position] Вызывается методами: void
 * SmartCalc::ParceInputString(const std::string &input_string, Tockens
 * x_tocken); void SmartCalc::ParceInputString(const std::string &input_string);
 * Результатом работы метода после вызова из данных функций будет добавление
 * операции в стэк. Вызываетмый метод: void SortOperations(operation_tocken);
 * Проверяет, является ли текщая операция унарной или бинарной, после чего
 * происходит добавление операции в стэе или в выходную строку.
 * @param position - итератор по строке.
 * @param input_string - входная строка.
 */
void SmartCalc::WichOperation(size_t *position,
                              const std::string &input_string) noexcept {
  Tockens operation_tocken(0.0, NUMBER, 0);
  switch (input_string[*position]) {
    case '-':
      if (CheckUnarOperation(position, input_string)) {
        operation_tocken.operation_type = UNAR;
        operation_tocken.operation_priority = 3;
        break;
      } else {
        operation_tocken.operation_type = SUB;
        operation_tocken.operation_priority = 4;
        break;
      }
    case '+':
      if (CheckUnarOperation(position, input_string)) {
        operation_tocken.operation_type = UNAR_PLUS;
        operation_tocken.operation_priority = 3;
        break;
      } else {
        operation_tocken.operation_type = SUM;
        operation_tocken.operation_priority = 4;
        break;
        case '*':
          operation_tocken.operation_type = MUL;
          operation_tocken.operation_priority = 5;
          break;
        case '/':
          operation_tocken.operation_type = DIV;
          operation_tocken.operation_priority = 5;
          break;
        case '^':
          operation_tocken.operation_type = POW;
          operation_tocken.operation_priority = 6;
          break;
        case '%':
          operation_tocken.operation_type = MOD;
          operation_tocken.operation_priority = 5;
          break;
        case '(':
          operation_tocken.operation_type = OPEN;
          operation_tocken.operation_priority = 2;
          break;
        case ')':
          operation_tocken.operation_type = CLOSE;
          operation_tocken.operation_priority = 1;
          break;
      }
  }
  SortOperations(operation_tocken);
}

/**
 * @brief Метод проверяет является ли текущий символ частью наименования
 * функции. Вызывается из метода: void SmartCalc::ParceInputString(const
 * std::string &input_string, Tockens x_tocken); void
 * SmartCalc::ParceInputString(const std::string &input_string);
 * @param current_simbol - текущий символ.
 * @return true - является.
 * @return false - не является.
 */
bool SmartCalc::IsFunction(char current_simbol) noexcept {
  return current_simbol == 's' || current_simbol == 'c' ||
         current_simbol == 't' || current_simbol == 'a' ||
         current_simbol == 'l' || current_simbol == 'S' ||
         current_simbol == 'C' || current_simbol == 'T' ||
         current_simbol == 'A' || current_simbol == 'L';
}

/**
 * @brief Метод добавляет наименовани е функции в стэк или выходную строку, в
 * зависимости от приоритета. Вызывается из метода: void
 * SmartCalc::ParceInputString(const std::string &input_string, Tockens
 * x_tocken); void SmartCalc::ParceInputString(const std::string &input_string);
 *
 * Метод вызывает методы:
 * void WichFunction(size_t *position, const std::string &input_string, size_t
 * *move, size_t *type) noexcept; который проверяет, какой функцией является
 * текущая функция и void PushOperationToStack(Tockens current_tocken) noexcept;
 * который в зависимости от приоритета текущей операции добавляется его в стек
 * или в выходную строку
 *
 * @param position - итератор по входной строке.
 * @param input_string - входная строка.
 */

void SmartCalc::AddFunction(size_t *position,
                            const std::string &input_string) noexcept {
  size_t move = 2, function_type = 0;
  WichFunction(position, input_string, &move, &function_type);
  if (function_type != 0) {
    *position += move;
    Tockens function_tocken(0.0, NUMBER, 7);
    switch (function_type) {
      case 1:
        function_tocken.operation_type = SIN;
        break;
      case 2:
        function_tocken.operation_type = COS;
        break;
      case 3:
        function_tocken.operation_type = TAN;
        break;
      case 4:
        function_tocken.operation_type = ASIN;
        break;
      case 5:
        function_tocken.operation_type = ACOS;
        break;
      case 6:
        function_tocken.operation_type = ATAN;
        break;
      case 7:
        function_tocken.operation_type = SQRT;
        break;
      case 8:
        function_tocken.operation_type = LN;
        ;
        break;
      case 9:
        function_tocken.operation_type = LOG;
        break;
    }
    PushOperationToStack(function_tocken);
  }
}

/**
 * @brief Метод проверяет, какой функцией является текущая проверяемая функция.
 * Вызывается из метода:
 * void AddFunction(size_t *position, const std::string &input_string) noexcept;
 *
 * @param position - итератор по входной строке.
 * @param input_string - входная строка.
 * @param move - значение на которое необходимо сдвинуть итератор входной строки
 * после окончания проверки символов.
 * @param type - тип операции.
 */
void SmartCalc::WichFunction(size_t *position, const std::string &input_string,
                             size_t *move, size_t *type) noexcept {
  if ((strncmp(&input_string[*position], "sin", 3) == 0) ||
      (strncmp(&input_string[*position], "SIN", 3) == 0)) {
    *type = 1;
  } else if ((strncmp(&input_string[*position], "cos", 3) == 0) ||
             (strncmp(&input_string[*position], "COS", 3) == 0)) {
    *type = 2;
  } else if ((strncmp(&input_string[*position], "tan", 3) == 0) ||
             (strncmp(&input_string[*position], "TAN", 3) == 0)) {
    *type = 3;
  } else if ((strncmp(&input_string[*position], "asin", 4) == 0) ||
             (strncmp(&input_string[*position], "ASIN", 4) == 0)) {
    *type = 4;
    *move = 3;
  } else if ((strncmp(&input_string[*position], "acos", 4) == 0) ||
             (strncmp(&input_string[*position], "ACOS", 4) == 0)) {
    *type = 5;
    *move = 3;
  } else if ((strncmp(&input_string[*position], "atan", 4) == 0) ||
             (strncmp(&input_string[*position], "ATAN", 4) == 0)) {
    *type = 6;
    *move = 3;
  } else if ((strncmp(&input_string[*position], "sqrt", 4) == 0) ||
             (strncmp(&input_string[*position], "SQRT", 4) == 0)) {
    *type = 7;
    *move = 3;
  } else if ((strncmp(&input_string[*position], "ln", 2) == 0) ||
             (strncmp(&input_string[*position], "LN", 2) == 0)) {
    *type = 8;
    *move = 1;
  } else if ((strncmp(&input_string[*position], "log", 3) == 0) ||
             (strncmp(&input_string[*position], "LOG", 3) == 0)) {
    *type = 9;
  }
}

/**
 * @brief Прорверка унарных операций.
 * @param position - итератор по входной строке.
 * @param input_string - входная строка.
 * @return true  - реультат проверки.
 * @return false - реультат проверки.
 */

bool SmartCalc::CheckUnarOperation(size_t *position,
                                   const std::string &input_string) noexcept {
  return ((input_string[*position] == '-' || input_string[*position] == '+') &&
          (input_string[*position - 1] == '(' ||
           input_string[*position - 1] == '-' ||
           input_string[*position - 1] == '+' ||
           input_string[*position - 1] == '*' ||
           input_string[*position - 1] == '/' ||
           input_string[*position - 1] == '%' ||
           input_string[*position - 1] == '^' || *position == 0 ||
           (input_string[*position - 1] == ' ' &&
            (input_string[*position - 2] == '(' ||
             input_string[*position - 2] == '-' ||
             input_string[*position - 2] == '+' ||
             input_string[*position - 2] == '*' ||
             input_string[*position - 2] == '/' ||
             input_string[*position - 2] == '%' ||
             input_string[*position - 2] == '^'))));
}

/**
 * @brief Метод проверяет является ли + и - унарным или бинарным.
 * если +/- унарный, вызывается метод
 * void ActionsWithUnarOperations(Tockens current_tocken) noexcept;
 * если бинарный вызывается метод:
 * void PushOperationToStack(Tockens current_tocken) noexcept;
 *
 * @param current_tocken - текущая проверяемая операция.
 */
void SmartCalc::SortOperations(Tockens current_tocken) noexcept {
  if (current_tocken.operation_priority == 3) {
    ActionsWithUnarOperations(current_tocken);
  } else {
    PushOperationToStack(current_tocken);
  }
}

/**
 * @brief Метод в зависимости от приоритета операции добавляет ее в стек или в
 * выходную строку. Вызывается из методов: void SortOperations(Tockens
 * current_tocken) noexcept; void AddFunction(size_t *position, const
 * std::string &input_string) noexcept;
 * @param current_tocken - текущая операция или функция.
 */
void SmartCalc::PushOperationToStack(Tockens current_tocken) noexcept {
  if (my_stack_.empty() || current_tocken.operation_type == OPEN) {
    my_stack_.push(current_tocken);
  } else {
    if (my_stack_.top().operation_priority >=
            current_tocken.operation_priority &&
        current_tocken.operation_type != OPEN &&
        current_tocken.operation_type != CLOSE &&
        current_tocken.operation_type != POW) {
      parsed_string_.push_back(my_stack_.top());
      my_stack_.pop();
      if (my_stack_.empty() || current_tocken.operation_priority >
                                   my_stack_.top().operation_priority) {
        my_stack_.push(current_tocken);
      } else if (!my_stack_.empty() && current_tocken.operation_priority <=
                                           my_stack_.top().operation_priority) {
        parsed_string_.push_back(my_stack_.top());
        my_stack_.pop();
        if (my_stack_.empty() || current_tocken.operation_priority >
                                     my_stack_.top().operation_priority) {
          my_stack_.push(current_tocken);
        } else {
          parsed_string_.push_back(my_stack_.top());
          my_stack_.pop();
          my_stack_.push(current_tocken);
        }
      }
    } else if (my_stack_.top().operation_priority >=
                   current_tocken.operation_priority &&
               current_tocken.operation_priority != 1 &&
               current_tocken.operation_type == POW) {
      if (my_stack_.top().operation_type == current_tocken.operation_type &&
          my_stack_.top().operation_type == POW) {
        my_stack_.push(current_tocken);
      } else {
        parsed_string_.push_back(my_stack_.top());
        my_stack_.pop();
        my_stack_.push(current_tocken);
      }
    } else if (my_stack_.top().operation_priority <
                   current_tocken.operation_priority &&
               current_tocken.operation_type != CLOSE) {
      my_stack_.push(current_tocken);
    } else if (current_tocken.operation_type == CLOSE) {
      while (my_stack_.top().operation_type != OPEN) {
        parsed_string_.push_back(my_stack_.top());
        my_stack_.pop();
      }
      my_stack_.pop();
    }
  }
}

/**
 * @brief Метод удаляет знак + если он является унарным
 *
 * @param current_tocken - текщая операция
 */
void SmartCalc::ActionsWithUnarOperations(Tockens current_tocken) noexcept {
  parsed_string_.push_back(current_tocken);
  if (current_tocken.operation_type == UNAR_PLUS) {
    parsed_string_.pop_back();
  }
}

/**
 * @brief Метод добавляет символы имеющиеся в стеке после окончяания парсинга в
 * выходную строку Вызывается из методов: double MainProcess(const std::string
 * &input_string,const std::string &x_input); double MainProcess(const
 * std::string &input_string);
 */

void SmartCalc::WhenStringFinished() noexcept {
  while (!my_stack_.empty()) {
    parsed_string_.push_back(my_stack_.top());
    my_stack_.pop();
  }
}

/**
 * @brief Метод вычислений после парсинга и преобразования строки в обратную
 * польскую нотацию. Метод выхывается из методов: double MainProcess(const
 * std::string &input_string, const std::string &x_input); double
 * MainProcess(const std::string &input_string);
 * @param parsed_string_ - выходная строка.
 * @param my_stack_ - стэк.
 * @return double  - число - результат вычисления.
 */

double SmartCalc::CalculationProcess(std::list<Tockens> &parsed_string_,
                                     std::stack<Tockens> &my_stack_) {
  if (my_stack_.empty()) {
    while (!parsed_string_.empty()) {
      Tockens currentTocken = parsed_string_.front();
      parsed_string_.pop_front();
      if (currentTocken.operation_priority == 0) {
        my_stack_.push(currentTocken);
      } else if (currentTocken.operation_priority == 7) {
        CalculateDifficultFunctions(currentTocken, my_stack_);
      } else {
        CalculateEasyFunctions(currentTocken, my_stack_);
      }
    }
    Tockens result(0, NUMBER, 0);
    result = my_stack_.top();
    my_stack_.pop();
    return result.number;
  } else {
    throw std::invalid_argument(
        "Something went wron in parsing, so you should try again =(");
    return 0.0;
  }
}

/**
 * @brief Метод вычисляет операции, которые для своего вычисления требуют одно
 * число. Вызывается из метода: double
 * SmartCalc::CalculationProcess(std::list<Tockens> &parsed_string_,
 * std::stack<Tockens> &my_stack_)
 *
 * @param operationType - тип опе6рации.
 * @param myStack - стэк
 */

void SmartCalc::CalculateDifficultFunctions(Tockens operationType,
                                            std::stack<Tockens> &myStack_) {
  Tockens result(0.0, NUMBER, 0), current_number = myStack_.top();
  myStack_.pop();
  if (operationType.operation_type == SIN) {
    result.number = sin(current_number.number);
  } else if (operationType.operation_type == COS) {
    result.number = cos(current_number.number);
  } else if (operationType.operation_type == TAN) {
    result.number = tan(current_number.number);
  } else if (operationType.operation_type == ASIN) {
    if (current_number.number >= -1 && current_number.number <= 1) {
      result.number = asin(current_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use arcsin(x) function, "
          "x must be in the limit from -1 TO 1");
    }
  } else if (operationType.operation_type == ACOS) {
    if (current_number.number >= -1 && current_number.number <= 1) {
      result.number = acos(current_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use arcсos(x) function, "
          "x must be in the limit from -1 TO 1");
    }
  } else if (operationType.operation_type == ATAN) {
    result.number = atan(current_number.number);
  } else if (operationType.operation_type == SQRT) {
    if (current_number.number >= 0) {
      result.number = sqrt(current_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use SQRT function, "
          "your number must be positiv");
    }
  } else if (operationType.operation_type == LN) {
    if (current_number.number >= 0) {
      result.number = log(current_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use LN function, "
          "your number must be positiv");
    }
  } else if (operationType.operation_type == LOG) {
    if (current_number.number >= 0) {
      result.number = log10(current_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use LN function, "
          "your number must be positiv");
    }
  }
  myStack_.push(result);
}

/**
 * @brief Метод вычисляет операции, которые для своего вычисления требуют два
 * числа. Вызывается из метода: double
 * SmartCalc::CalculationProcess(std::list<Tockens> &parsed_string_,
 * std::stack<Tockens> &my_stack_)
 *
 * @param operationType - тип опе6рации.
 * @param myStack - стэк
 */
void SmartCalc::CalculateEasyFunctions(Tockens operationType,
                                       std::stack<Tockens> &my_stack_) {
  Tockens result(0.0, NUMBER, 0), first_number(0.0, NUMBER, 0),
      second_number(0.0, NUMBER, 0);
  first_number = my_stack_.top();
  my_stack_.pop();
  second_number = my_stack_.top();
  my_stack_.pop();
  if (operationType.operation_type == POW) {
    if (second_number.number == 0 && first_number.number == 0) {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use POW function, "
          "base and exp can't be equal 0");
    } else {
      result.number = pow(second_number.number, first_number.number);
    }
  } else if (operationType.operation_type == DIV) {
    if (first_number.number != 0) {
      result.number = second_number.number / first_number.number;
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use MOD function, "
          "second number must be != 0");
    }
  } else if (operationType.operation_type == MUL) {
    result.number = second_number.number * first_number.number;
  } else if (operationType.operation_type == SUM) {
    result.number = second_number.number + first_number.number;
  } else if (operationType.operation_type == SUB) {
    result.number = second_number.number - first_number.number;
  } else if (operationType.operation_type == MOD) {
    if (first_number.number != 0) {
      result.number = fmod(second_number.number, first_number.number);
    } else {
      throw std::invalid_argument(
          "Your input is incorrect! =( If you want to use MOD function, "
          "second number must be != 0");
    }
  }
  my_stack_.push(result);
}

// /// Доп функции
// void SmartCalc::PrintInfoAboutStack(std::stack<Tockens> my_stack_) {
//   std::stack<Tockens> copy = my_stack_;
//   // std::cout << "STACK INFO" << std::endl;
//   // std::cout << std::endl;
//   std::cout << std::endl;
//   std::cout << "Stack_size   " << my_stack_.size() << std::endl;
//   Tockens buffer(0.0, NUMBER, 7);
//   while (!copy.empty()) {
//     buffer = copy.top();
//     switch (buffer.operation_type) {
//       case 0:
//         std::cout << buffer.number << std::endl;
//         break;
//       case 1:
//         std::cout << "sin" << std::endl;
//         break;
//       case 2:
//         std::cout << "cos" << std::endl;
//         break;
//       case 3:
//         std::cout << "tan" << std::endl;
//         break;
//       case 4:
//         std::cout << "asin" << std::endl;
//         break;
//       case 5:
//         std::cout << "acos" << std::endl;
//         break;
//       case 6:
//         std::cout << "atan" << std::endl;
//         break;
//       case 7:
//         std::cout << "sqrt" << std::endl;
//         break;
//       case 8:
//         std::cout << "ln" << std::endl;
//         break;
//       case 9:
//         std::cout << "log" << std::endl;
//         break;
//       case 10:
//         std::cout << "mod" << std::endl;
//         break;
//       case 11:
//         std::cout << '^' << std::endl;
//         break;
//       case 12:
//         std::cout << '/' << std::endl;
//         break;
//       case 13:
//         std::cout << '*' << std::endl;
//         break;
//       case 14:
//         std::cout << '+' << std::endl;
//         break;
//       case 15:
//         std::cout << '-' << std::endl;
//         break;
//       case 16:
//         std::cout << '~' << std::endl;
//         break;
//       case 17:
//         std::cout << '(' << std::endl;
//         break;
//       case 18:
//         std::cout << ')' << std::endl;
//         break;
//       case 19:
//         std::cout << "unar_+" << std::endl;
//         break;
//     }
//     copy.pop();
//   }
//   std::cout << std::endl;
// }

// void SmartCalc::PrintInfoAboutString(std::list<Tockens> parsed_string_) {
//   // std::cout << std::endl;
//   // std::cout << "STRING INFO" << std::endl;
//   std::cout << std::endl;
//   std::cout << "String_size  " << parsed_string_.size() << std::endl;
//   Tockens buffer(0.0, NUMBER, 7);
//   std::list<Tockens> copy = parsed_string_;
//   while (copy.size() > 0) {
//     buffer = copy.front();
//     switch (buffer.operation_type) {
//       case 0:
//         std::cout << buffer.number << ' ';
//         break;
//       case 1:
//         std::cout << "sin" << ' ';
//         break;
//       case 2:
//         std::cout << "cos" << ' ';
//         break;
//       case 3:
//         std::cout << "tan" << ' ';
//         break;
//       case 4:
//         std::cout << "asin" << ' ';
//         break;
//       case 5:
//         std::cout << "acos" << ' ';
//         break;
//       case 6:
//         std::cout << "atan" << ' ';
//         break;
//       case 7:
//         std::cout << "sqrt" << ' ';
//         break;
//       case 8:
//         std::cout << "ln" << ' ';
//         break;
//       case 9:
//         std::cout << "log" << ' ';
//         break;
//       case 10:
//         std::cout << "mod" << ' ';
//         break;
//       case 11:
//         std::cout << '^' << ' ';
//         break;
//       case 12:
//         std::cout << '/' << ' ';
//         break;
//       case 13:
//         std::cout << '*' << ' ';
//         break;
//       case 14:
//         std::cout << '+' << ' ';
//         break;
//       case 15:
//         std::cout << '-' << ' ';
//         break;
//       case 16:
//         std::cout << '~' << ' ';
//         break;
//       case 17:
//         std::cout << '(' << ' ';
//         break;
//       case 18:
//         std::cout << ')' << ' ';
//         break;
//       case 19:
//         std::cout << "unar_+" << ' ';
//         break;
//     }
//     copy.pop_front();
//   }
//   std::cout << std::endl;
// }

};  // namespace s21
