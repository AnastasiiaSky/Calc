#include <cmath>
#include <list>

#include "../credit_calc.h"
#include "gtest/gtest.h"

TEST(Test, Test_credit_calc_test_1) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1000000, 24, 7.5, 1);
  credit.CheckCreditCalcFunction(input);
  struct s21::ResultCreditData output = credit.calculating();

  EXPECT_NEAR(output.final_sum, 1079990.16, 1e-1);
  EXPECT_NEAR(output.overpay, 79990.16, 1e-1);
  EXPECT_NEAR(output.first_pay, 44999.59, 1e-1);
  EXPECT_NEAR(output.last_pay, 44999.59, 1e-1);
}

// TEST(Test, Test_credit_calc_test_2) {

//   s21::CreditCalc credit;
//   struct s21::InputCreditData input(0, 24, 7.5, 2);
//   credit.CheckCreditCalcFunction(input);
//   struct s21::ResultCreditData output = credit.calculating();

//   EXPECT_NEAR(output.final_sum, 1078125.00, 1e-1);
//   EXPECT_NEAR(output.overpay, 78125.00, 1e-1);
//   EXPECT_NEAR(output.first_pay, 47916.67, 1e-1);
//   EXPECT_NEAR(output.last_pay, 41927.08, 1e-0);

// }

TEST(Test, Test_credit_calc_test_3) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1500000, 12, 11.2, 1);
  credit.CheckCreditCalcFunction(input);
  struct s21::ResultCreditData output = credit.calculating();

  EXPECT_NEAR(output.final_sum, 1592549.52, 1e-1);
  EXPECT_NEAR(output.overpay, 92549.52, 1e-1);
  EXPECT_NEAR(output.first_pay, 132712.46, 1e-1);
  EXPECT_NEAR(output.last_pay, 132712.46, 1e-1);
}

TEST(Test, Test_credit_calc_test_4) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1500000, 12, 11.2, 2);
  credit.CheckCreditCalcFunction(input);
  struct s21::ResultCreditData output = credit.calculating();

  EXPECT_NEAR(output.final_sum, 1591000.00, 1e-1);
  EXPECT_NEAR(output.overpay, 91000.00, 1e-1);
  EXPECT_NEAR(output.first_pay, 139000.00, 1e-1);
  EXPECT_NEAR(output.last_pay, 126166.67, 1e-1);
}

TEST(Test, Test_credit_calc_test_5) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(560000, 6, 15.2, 1);
  credit.CheckCreditCalcFunction(input);
  struct s21::ResultCreditData output = credit.calculating();

  EXPECT_NEAR(output.final_sum, 585087.06, 1e-1);
  EXPECT_NEAR(output.overpay, 25087.06, 1e-1);
  EXPECT_NEAR(output.first_pay, 97514.51, 1e-1);
  EXPECT_NEAR(output.last_pay, 97514.51, 1e-1);
}

TEST(Test, Test_credit_calc_test_7) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(-1500000, 12, 11.2, 2);
  ASSERT_ANY_THROW(credit.CheckCreditCalcFunction(input));
}

TEST(Test, Test_credit_calc_test_8) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1500000, -12, 11.2, 2);
  ASSERT_ANY_THROW(credit.CheckCreditCalcFunction(input));
}

TEST(Test, Test_credit_calc_test_9) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1500000, 12, -11.2, 2);
  ASSERT_ANY_THROW(credit.CheckCreditCalcFunction(input));
}

TEST(Test, Test_credit_calc_test_10) {
  s21::CreditCalc credit;
  struct s21::InputCreditData input(1500000, 12, 11.2, 5);
  ASSERT_ANY_THROW(credit.CheckCreditCalcFunction(input));
}

GTEST_API_ int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
