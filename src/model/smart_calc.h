#ifndef S21_SMART_CALC_H_
#define S21_SMART_CALC_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "string_validation.h"

class StringValidator;
namespace s21 {
class SmartCalc {
 public:
  enum OperationType {
    NUMBER,
    SIN,
    COS,
    TAN,
    ASIN,
    ACOS,
    ATAN,
    SQRT,
    LN,
    LOG,
    MOD,
    POW,
    DIV,
    MUL,
    SUM,
    SUB,
    UNAR,
    OPEN,
    CLOSE,
    UNAR_PLUS
  };

  struct Tockens {
    double number;
    OperationType operation_type;
    int operation_priority;
    Tockens(double number, OperationType operation_type, int operation_priority)
        : number(number),
          operation_type(operation_type),
          operation_priority(operation_priority) {}
  };

  double MainProcess(const std::string &input_string,
                     const std::string &x_input);
  double MainProcess(const std::string &input_string);
  bool MakeAllValidation(const std::string &input_string,
                         const std::string &x_input);
  bool MakeAllValidation(const std::string &input_string);
  double get_x_from_input(const std::string &x_input) noexcept;
  void ParceInputString(const std::string &input_string);
  void ParceInputString(const std::string &input_string,
                        Tockens x_tocken) noexcept;
  bool IsNumber(char current_simbol) noexcept;
  double ConstructNumber(size_t *position,
                         const std::string &input_string) noexcept;
  std::string WorkWithExpoNumber(size_t *position,
                                 const std::string &input_string);
  bool CheckExpoFormOfNumber(char first_simbol, char second_simbol) noexcept;
  bool IsOperation(char current_simbol) noexcept;
  void WichOperation(size_t *position,
                     const std::string &input_string) noexcept;
  bool IsFunction(char current_simbol) noexcept;
  void AddFunction(size_t *position, const std::string &input_string) noexcept;
  void WichFunction(size_t *position, const std::string &input_string,
                    size_t *move, size_t *type) noexcept;
  bool CheckUnarOperation(size_t *position,
                          const std::string &input_string) noexcept;
  void SortOperations(Tockens current_tocken) noexcept;
  void PushOperationToStack(Tockens current_tocken) noexcept;
  void ActionsWithUnarOperations(Tockens current_tocken) noexcept;
  void WhenStringFinished() noexcept;
  double CalculationProcess(std::list<Tockens> &parsed_string_,
                            std::stack<Tockens> &my_stack_);
  void CalculateDifficultFunctions(Tockens operationType,
                                   std::stack<Tockens> &my_stack_);
  void CalculateEasyFunctions(Tockens operationType,
                              std::stack<Tockens> &my_stack_);

  // void PrintInfoAboutStack(std::stack<Tockens> my_stack_);
  // void PrintInfoAboutString(std::list<Tockens> parsed_string_);

 private:
  std::list<Tockens> parsed_string_;
  std::stack<Tockens> my_stack_;
};
}  // namespace s21

#endif  // S21_SMART_CALC_H_
