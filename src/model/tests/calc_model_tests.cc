#include <cmath>
#include <limits>

#include "../smart_calc.h"
#include "../string_validation.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(Test, parser_simple_sum_test_1) {
  std::string str = "5 + 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_EQ(result, 10);
}

TEST(Test, parser_simple_sum_test_2) {
  std::string str = "5 + 5 + 5 + 5 + 5 + 5 + 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_EQ(result, 35);
}

TEST(Test, parser_simple_sum_test_3) {
  std::string str = "2 + 2 + 2 + 3 + 4 + 5 + 6 + 7 + 8";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_EQ(result, 39);
}

TEST(Test, parser_simple_sum_test_4) {
  std::string str = "1.5 + 1.55 + 1.25 + 12.31 + 16.999";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 33.609);
}

TEST(Test, parser_simple_sum_test_5) {
  std::string str = "15.99 + 19.248 + 15.963214 + 13.33 + 44.947 + 22.2 + 33";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 164.678214);
}

TEST(Test, parser_simple_sum_test_6) {
  std::string str = "999.9999 + 999.9999 + 999.9999 + 999.9999 + 999.9999";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 4999.9995);
}

TEST(Test, simple_sum_and_unar_minus_test_1) {
  std::string str = "5 + (-3)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 2);
}

TEST(Test, simple_sum_and_unar_minus_test_2) {
  std::string str = "-5 + (-3)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -8);
}

TEST(Test, simple_sum_and_unar_minus_test_3) {
  std::string str = "-5 + (-3) + 8";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Test, simple_sum_and_unar_minus_test_4) {
  std::string str = "-5 + (-3) + 8 + 5.25";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 5.25);
}

TEST(Test, simple_sum_and_unar_minus_test_5) {
  std::string str = "-5.5 + 4.35 + 44.25 + (-36)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 7.1);
}

TEST(Test, simple_sub_test_1) {
  std::string str = "10 - 10 - 15 - 20 - 25 - 35";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -95);
}

TEST(Test, simple_sub_test_2) {
  std::string str = "3.1415926 - 44 - 46 - 33.25 - 5.25";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -125.3584074);
}

TEST(Test, simple_sub_test_3) {
  std::string str =
      "1000 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - "
      "5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25 - "
      "5.25 - 5.25 - 5.25 - 5.25 - 5.25 - 5.25";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 889.75);
}

TEST(Test, simple_sub_test_4) {
  std::string str = "1000 - 555.00045 - 478.99 - 36.6 - 777";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -847.59045);
}

TEST(Test, simple_sub_test_5) {
  std::string str =
      "100 - 25.5 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1.5 - 1 - 1.15 - 1.95 - 1";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 59.9);
}

TEST(Test, simple_sub_and_sum_test_1) {
  std::string str = "100 - 100 + 100";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 100);
}

TEST(Test, simple_sub_and_sum_test_2) {
  std::string str = "100.5 - 100 + 0.55";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 1.05);
}

TEST(Test, simple_sub_and_sum_test_3) {
  std::string str = "3.1415 + 3.1415 - 1000";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -993.717);
}

TEST(Test, simple_sub_and_sum_and_unar_minus_test_1) {
  std::string str = "5 + (-5) - 5 + 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Test, simple_sub_and_sum_and_unar_minus_test_2) {
  std::string str = "5 - - 5 ";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 10);
}

TEST(Test, simple_sub_and_sum_and_unar_minus_test_3) {
  std::string str = "5.55 - - 5 - - 46 + 37.345 + 66.098";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 159.993);
}

TEST(Test, simple_expo_number_form_test_1) {
  std::string str = "1e-3 + 4E+4";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 40000.001);
}

TEST(Test, simple_expo_number_form_test_2) {
  std::string str = "0.1e-3 + 0.4E+4";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 4000.0001);
}

TEST(Test, simple_expo_number_form_test_3) {
  std::string str = "25e-3 + 25e-3 - 5e-1";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -0.45);
}

TEST(Test, simple_expo_number_form_test_4) {
  std::string str = "1e-3 + 1e-2 + 1e-3 - 1e-1 + 33 - 0.3e+3";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, -267.088);
}

TEST(Test, simple_expo_number_form_test_5) {
  std::string str = "1e+3 + 1e+2 + 1e+3 - 1e+1 + 33 - 0.3e-3";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 2122.9997);
}

TEST(Test, Test_simple_pow_test_1) {
  std::string str = "0.55e+3 * 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 2750);
}

TEST(Test, Test_simple_pow_test_2) {
  std::string str = "0.55e+3 * 5 - 3 - 2000 + 3e-1";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 747.3);
}

TEST(Test, Test_simple_pow_test_3) {
  std::string str = "1 + 1 + 1 + 1 + 1 + 2 + 3 + 4 * 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 30);
}

TEST(Test, Test_simple_pow_test_4) {
  std::string str = "1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 1e-5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 36.288);
}

TEST(Test, Test_simple_pow_test_5) {
  std::string str = "1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 3628800);
}

TEST(Test, Test_simple_pow_test_6) {
  std::string str = "1.25 * 2.33";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 2.9125);
}

TEST(Test, Test_simple_div_test_1) {
  std::string str = "0.55e+3 / 5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 110);
}

TEST(Test, Test_simple_div_test_2) {
  std::string str = "25 / 5 / 0.25";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 20);
}

TEST(Test, Test_simple_div_test_3) {
  std::string str = "100000 / 5 / 10 / 25";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 80);
}

TEST(Test, Test_simple_div_test_4) {
  std::string str = "1e+10 / 1e+8";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 100);
}

TEST(Test, Test_simple_div_test_5) {
  std::string str = "100 / 10 / 10 / 10 / 10 * 1e+2";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 1);
}

TEST(Test, Test_simple_div_test_6) {
  std::string str = "225 / 15 / 3";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  ASSERT_DOUBLE_EQ(result, 5);
}

TEST(Test, Test_simple_comboset_1) {
  std::string str = "225 / 15 * 3 - 4 + 5e-5 * 2 - 0.4E+3";
  std::string str1 = "1 + 1 + 1 + 1 + 1 + 1 * 5 / 4 - 2 - 3 + 4";
  std::string str2 = "3.5 + 500.05 / 5.25 * 2 - 33.25 - 1e+4";
  std::string str3 = "3 * 3 * 3 * 3 / 9 - 4 - 4 + 6 + 6e+4";
  std::string str4 = "5.25 + 5.25 + 5.25 * 3 / 5";
  std::string str5 = "5 * 5 * 5.25 - 4 + 6 / 2 * 3 - 1e-3 + 1e+2";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  EXPECT_NEAR(result, -358.9999, 1e-7);
  EXPECT_NEAR(result1, 5.25, 1e-7);
  EXPECT_NEAR(result2, -9839.2547619047619048, 1e-7);
  EXPECT_NEAR(result3, 60007, 1e-7);
  EXPECT_NEAR(result4, 13.65, 1e-7);
  EXPECT_NEAR(result5, 236.249, 1e-7);
}

TEST(Test, Test_simple_brackets_test_1) {
  std::string str = "(5 + 5) / 2";
  std::string str1 = "(2 - 44) * 2 + 2 * (3 + 3)";
  std::string str2 = "(2 + 2e-1 - 0.2e+3 - 44) * 2";
  std::string str3 = "(1 + 1.25) * (3 - 1) / 2 * (5 + 5.25)";
  std::string str4 = "5.25 + (5.25 + 5.25) * 3 / 5";
  std::string str5 = "5 * 5 * (5.25 - 4 + 6) / 2 * (3 - 1e-3) + 1e+2";
  std::string str6 = "2 * 2 - (4.55 - 0.55) * 3 - (44.7 - 0.77)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);
  double result6 = calc.MainProcess(str6, x);

  EXPECT_NEAR(result, 5, 1e-7);
  EXPECT_NEAR(result1, -72, 1e-7);
  EXPECT_NEAR(result2, -483.6, 1e-7);
  EXPECT_NEAR(result3, 23.0625, 1e-7);
  EXPECT_NEAR(result4, 11.55, 1e-7);
  EXPECT_NEAR(result5, 371.784375, 1e-7);
  EXPECT_NEAR(result6, -51.93, 1e-7);
}

TEST(Test, Test_simple_brackets_test_2) {
  std::string str = "(5 + (3 * 2)) / 2";
  std::string str1 = "(2 - (33 + 2) + 44) * (2 + 2 * (3 - (1 + 1))) - (3 + 3)";
  std::string str2 = "2 * (2 + (3 + 3 * (4 * 2 / 0.5)))";
  std::string str3 =
      "-1 + (-3 - 3) * (3 + 3) + (2 + (2 + (2.3 - (6 - 6 * (4 + "
      "4 - (8.8 - 9.9 + (10.1 - 2.2)))))))";
  std::string str4 = "(((((((((22.2 - 33.3)))))))) * 2)";
  std::string str5 =
      "(2e-6 + 0.2e+8) * (3 + 2 - 2 + 3 + 4 *(1 * 1 * 1 * 2 * (0.3 + 0.2)))";
  std::string str6 =
      "2 * (2 * (2 * (2 * (2 * (2 * (2 * (2 * (2 * (2 * (2 * 1)))))))))) / 10";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);
  double result6 = calc.MainProcess(str6, x);

  EXPECT_NEAR(result, 5.5, 1e-7);
  EXPECT_NEAR(result1, 38, 1e-7);
  EXPECT_NEAR(result2, 106, 1e-7);
  EXPECT_NEAR(result3, -29.5, 1e-7);
  EXPECT_NEAR(result4, -22.2, 1e-7);
  EXPECT_NEAR(result5, 200000000.00002, 1e-7);
  EXPECT_NEAR(result6, 204.8, 1e-7);
}

TEST(Test, Test_simple_sin_test_1) {
  std::string str = "sin(1)";
  std::string str1 = "sin(0.5)";
  std::string str2 = "sin(-1)";
  std::string str3 = "sin(-0.5)";
  std::string str4 = "sin(1.5)";
  std::string str5 = "sin(-1.5)";
  std::string str6 = "sin(5)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);
  double result6 = calc.MainProcess(str6, x);

  ASSERT_DOUBLE_EQ(result, 0.8414709848078965);
  ASSERT_DOUBLE_EQ(result1, 0.47942553860420301);
  ASSERT_DOUBLE_EQ(result2, -0.8414709848078965);
  ASSERT_DOUBLE_EQ(result3, -0.47942553860420301);
  ASSERT_DOUBLE_EQ(result4, 0.99749498660405445);
  ASSERT_DOUBLE_EQ(result5, -0.99749498660405445);
  ASSERT_DOUBLE_EQ(result6, -0.95892427466313845);
}

TEST(Test, Test_simple_sin_test_2) {
  std::string str = "sin(3.1415926)";
  std::string str1 = "sin(3.1415926 / 2)";
  std::string str2 = "sin(3.1415926 / 3)";
  std::string str3 = "sin(3.1415926 / 4)";
  std::string str4 = "sin(2 * 3.1415926)";
  std::string str5 = "sin(3 * 3.1415926)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  ASSERT_DOUBLE_EQ(result, 5.3589793170057245e-08);
  ASSERT_DOUBLE_EQ(result1, 0.99999999999999967);
  ASSERT_DOUBLE_EQ(result2, 0.86602539485280627);
  ASSERT_DOUBLE_EQ(result3, 0.70710677171312097);
  ASSERT_DOUBLE_EQ(result4, -1.0717958634011433e-07);
  ASSERT_DOUBLE_EQ(result5, 1.607693786219927e-07);
}

TEST(Test, Test_simple_cos_test_1) {
  std::string str = "cos(3.1415926)";
  std::string str1 = "cos(3.1415926 / 2)";
  std::string str2 = "cos(3.1415926 / 3)";
  std::string str3 = "cos(3.1415926 / 4)";
  std::string str4 = "cos(2 * 3.1415926)";
  std::string str5 = "cos(3 * 3.1415926)";
  std::string x = "\0";

  SmartCalc calc;
  double result = cos(3.1415926) - calc.MainProcess(str, x);
  double result1 = cos(3.1415926 / 2) - calc.MainProcess(str1, x);
  double result2 = cos(3.1415926 / 3) - calc.MainProcess(str2, x);

  double result3 = cos(3.1415926 / 4) - calc.MainProcess(str3, x);
  double result4 = cos(2 * 3.1415926) - calc.MainProcess(str4, x);
  double result5 = cos(3 * 3.1415926) - calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 0, 1e-7);
  EXPECT_NEAR(result1, 0, 1e-7);
  EXPECT_NEAR(result2, 0, 1e-7);
  EXPECT_NEAR(result3, 0, 1e-7);
  EXPECT_NEAR(result4, 0, 1e-7);
  EXPECT_NEAR(result5, 0, 1e-7);
}

TEST(Test, Test_simple_cos_test_2) {
  std::string str = "cos(1)";
  std::string str1 = "cos(2 / 2)";
  std::string str2 = "cos(-2)";
  std::string str3 = "cos(0.5)";
  std::string str4 = "cos(1.5)";
  std::string str5 = "cos(-1.75)";
  std::string x = "\0";

  SmartCalc calc;
  double result = cos(1) - calc.MainProcess(str, x);
  double result1 = cos(2 / 2) - calc.MainProcess(str1, x);
  double result2 = cos(-2) - calc.MainProcess(str2, x);
  double result3 = cos(0.5) - calc.MainProcess(str3, x);
  double result4 = cos(1.5) - calc.MainProcess(str4, x);
  double result5 = cos(-1.75) - calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 0, 1e-7);
  EXPECT_NEAR(result1, 0, 1e-7);
  EXPECT_NEAR(result2, 0, 1e-7);
  EXPECT_NEAR(result3, 0, 1e-7);
  EXPECT_NEAR(result4, 0, 1e-7);
  EXPECT_NEAR(result5, 0, 1e-7);
}

TEST(Test, Test_simple_tan_test_1) {
  std::string str = "tan(1)";
  std::string str1 = "tan(2 / 2)";
  std::string str2 = "tan(-2)";
  std::string str3 = "tan(0.5)";
  std::string str4 = "tan(1.5)";
  std::string str5 = "tan(-1.75)";
  std::string x = "\0";

  SmartCalc calc;
  double result = tan(1) - calc.MainProcess(str, x);
  double result1 = tan(2 / 2) - calc.MainProcess(str1, x);
  double result2 = tan(-2) - calc.MainProcess(str2, x);
  double result3 = tan(0.5) - calc.MainProcess(str3, x);
  double result4 = tan(1.5) - calc.MainProcess(str4, x);
  double result5 = tan(-1.75) - calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 0, 1e-7);
  EXPECT_NEAR(result1, 0, 1e-7);
  EXPECT_NEAR(result2, 0, 1e-7);
  EXPECT_NEAR(result3, 0, 1e-7);
  EXPECT_NEAR(result4, 0, 1e-7);
  EXPECT_NEAR(result5, 0, 1e-7);
}

TEST(Test, Test_simple_asin_test_1) {
  std::string str = "asin(1)";
  std::string str1 = "asin(2 / 2)";
  std::string str2 = "asin(0.5)";
  std::string str3 = "asin(0.75)";
  std::string str4 = "asin(-0.25)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);

  EXPECT_NEAR(result, 1.57079633, 1e-7);
  EXPECT_NEAR(result1, 1.57079633, 1e-7);
  EXPECT_NEAR(result2, 0.523598776, 1e-7);
  EXPECT_NEAR(result3, 0.848062079, 1e-7);
  EXPECT_NEAR(result4, -0.252680255, 1e-7);
}

TEST(Test, Test_simple_asin_test_throw) {
  std::string str = "asin(10)";
  std::string str1 = "asin(-44)";

  std::string x = "\0";

  SmartCalc calc;
  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1, x));
}

TEST(Test, Test_simple_acos_test_1) {
  std::string str = "acos(1)";
  std::string str1 = "acos(2 / 2)";
  std::string str2 = "acos(0.5)";
  std::string str3 = "acos(0.75)";
  std::string str4 = "acos(-0.25)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);

  EXPECT_NEAR(result, 0, 1e-7);
  EXPECT_NEAR(result1, 0, 1e-7);
  EXPECT_NEAR(result2, 1.04719755, 1e-7);
  EXPECT_NEAR(result3, 0.722734248, 1e-7);
  EXPECT_NEAR(result4, 1.82347658, 1e-7);
}

TEST(Test, Test_simple_acos_test_throw) {
  std::string str = "acos(10)";
  std::string str1 = "acos(-44)";
  std::string x = "\0";

  SmartCalc calc;
  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1, x));
}

TEST(Test, Test_simple_atan_test_1) {
  std::string str = "atan(1)";
  std::string str1 = "atan(2 / 2)";
  std::string str2 = "atan(-4)";
  std::string str3 = "atan(0.5)";
  std::string str4 = "atan(1.5)";
  std::string str5 = "atan(-1.75)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 0.785398163, 1e-7);
  EXPECT_NEAR(result1, 0.785398163, 1e-7);
  EXPECT_NEAR(result2, -1.32581766, 1e-7);
  EXPECT_NEAR(result3, 0.463647609, 1e-7);
  EXPECT_NEAR(result4, 0.982793723, 1e-7);
  EXPECT_NEAR(result5, -1.05165021, 1e-7);
}

TEST(Test, Test_simple_sqrt_test_1) {
  std::string str = "sqrt(25)";
  std::string str1 = "sqrt(49)";
  std::string str2 = "sqrt(0)";
  std::string str3 = "sqrt(225)";
  std::string str4 = "sqrt(24025)";
  std::string str5 = "sqrt(1102.24)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 5, 1e-7);
  EXPECT_NEAR(result1, 7, 1e-7);
  EXPECT_NEAR(result2, 0, 1e-7);
  EXPECT_NEAR(result3, 15, 1e-7);
  EXPECT_NEAR(result4, 155, 1e-7);
  EXPECT_NEAR(result5, 33.2, 1e-7);
}

TEST(Test, Test_simple_sqrt_test_errorr) {
  std::string str = "sqrt(-33)";
  std::string str1 = "sqrt(-25)";
  std::string x = "\0";

  SmartCalc calc;

  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1, x));
}

TEST(Test, Test_simple_ln_test_1) {
  std::string str = "ln(25)";
  std::string str1 = "ln(49)";
  std::string str2 = "ln(0)";
  std::string str3 = "ln(1)";
  std::string str4 = "ln(24025)";
  std::string str5 = "ln(1102.24)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 3.21887582487, 1e-7);
  EXPECT_NEAR(result1, 3.89182029811, 1e-7);
  ASSERT_DOUBLE_EQ(result2, -INFINITY);
  EXPECT_NEAR(result3, 0, 1e-7);
  EXPECT_NEAR(result4, 10.0868502338, 1e-7);
  EXPECT_NEAR(result5, 7.00509975184, 1e-7);
}

TEST(Test, Test_simple_log_test_1) {
  std::string str = "log(25)";
  std::string str1 = "log(49)";
  std::string str2 = "log(0)";
  std::string str3 = "log(1)";
  std::string str4 = "log(24025)";
  std::string str5 = "log(1102.24)";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);
  double result5 = calc.MainProcess(str5, x);

  EXPECT_NEAR(result, 1.3979400086720377, 1e-7);
  EXPECT_NEAR(result1, 1.6901960800285136, 1e-7);
  ASSERT_DOUBLE_EQ(result2, -INFINITY);
  EXPECT_NEAR(result3, 0, 1e-7);
  EXPECT_NEAR(result4, 4.380663396340583, 1e-7);
  EXPECT_NEAR(result5, 3.0422761674080725, 1e-7);
}

TEST(Test, Test_simple_log_ln_test_errorr) {
  std::string str = "ln(-33)";
  std::string str1 = "ln(-1000000000000)";
  std::string str2 = "log(-33)";
  std::string str3 = "log(-1000000000000)";
  std::string x = "\0";

  SmartCalc calc;

  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1, x));
  ASSERT_ANY_THROW(calc.MainProcess(str2, x));
  ASSERT_ANY_THROW(calc.MainProcess(str3, x));
}

TEST(Test, Test_simple_mod_test_1) {
  std::string str = "24%5";
  std::string str1 = "98752364465165%9";
  std::string str2 = "951428965485%2.5";
  std::string str3 = "234567890%-5";
  std::string str4 = "-76%3";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);

  ASSERT_DOUBLE_EQ(result, 4);
  ASSERT_DOUBLE_EQ(result1, 8);
  ASSERT_DOUBLE_EQ(result2, 0);
  ASSERT_DOUBLE_EQ(result3, 0);
  ASSERT_DOUBLE_EQ(result4, -1);
}

TEST(Test, Test_simple_power_test_1) {
  std::string str = "5^2";
  std::string str1 = "5^5";
  std::string str2 = "-5^5";
  std::string str3 = "5^-5";
  std::string str4 = "-5^-5";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);
  double result2 = calc.MainProcess(str2, x);
  double result3 = calc.MainProcess(str3, x);
  double result4 = calc.MainProcess(str4, x);

  ASSERT_DOUBLE_EQ(result, 25);
  ASSERT_DOUBLE_EQ(result1, 3125);
  ASSERT_DOUBLE_EQ(result2, -3125);
  EXPECT_NEAR(result3, 0.00032, 1e-7);
  EXPECT_NEAR(result4, -0.00032, 1e-7);
}

TEST(Test, Test_combinethions_of_differnt_functions_1) {
  std::string str = "2 + 2e-2 * sin(5e-1) + 3 + 142.5 / (1.5 * cos(3e-1))";
  std::string str1 = "sin(1.5)^5 + cos(1)^-2 * sqrt(49)";
  std::string str2 = "";
  std::string x = "\0";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);
  double result1 = calc.MainProcess(str1, x);

  EXPECT_NEAR(result, 104.450990657, 1e-7);
  EXPECT_NEAR(result1, 24.9661692726, 1e-7);
}

TEST(Test, Test_calc_model_validation_tests_1) {
  std::string str = "5^x";
  std::string x = "*2";
  std::string str1 = "****5^x";
  SmartCalc calc;

  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1));
}

TEST(Test, Test_calc_model_validation_tests_2) {
  std::string str = "2 + 2e-2 * sin(5e-1) + 3 + 142.5 / (1.5 * cos(3e-1))";
  std::string str1 = "sin(1.5)^5 + cos(1)^-2 * sqrt(49)";

  SmartCalc calc;
  double result = calc.MainProcess(str);
  double result1 = calc.MainProcess(str1);

  EXPECT_NEAR(result, 104.450990657, 1e-7);
  EXPECT_NEAR(result1, 24.9661692726, 1e-7);
}

TEST(Test, Test_calc_model_validation_tests_3) {
  std::string str = "5 + x";
  std::string x = "-2";

  SmartCalc calc;
  double result = calc.MainProcess(str, x);

  EXPECT_NEAR(result, 3, 1e-7);
}

TEST(Test, Test_calc_model_validation_tests_4) {
  std::string str = "";
  std::string str1 =
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111+11111111111111111+"
      "11111111111111111+11111111111111111+11111111111111111";
  std::string str2 = "^25 + x";
  std::string str3 = "^25";
  std::string str4 = "5.25.55 + 4";
  std::string str5 = "5.25.55 + x";
  std::string str6 = "5e5";
  std::string str7 = "5e*3";
  std::string str8 = "5e";
  std::string str9 = "5e-^";
  std::string str10 = "5       + 4";
  std::string str11 = "5*/-4";
  std::string str12 = "5---4";
  std::string str13 = "5%%%4";
  std::string str14 = "()*()+";
  std::string str15 = "5*/*3";

  std::string x = "2";

  SmartCalc calc;

  ASSERT_ANY_THROW(calc.MainProcess(str, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1, x));
  ASSERT_ANY_THROW(calc.MainProcess(str1));
  ASSERT_ANY_THROW(calc.MainProcess(str3));
  ASSERT_ANY_THROW(calc.MainProcess(str2, x));
  ASSERT_ANY_THROW(calc.MainProcess(str4));
  ASSERT_ANY_THROW(calc.MainProcess(str5));
  ASSERT_ANY_THROW(calc.MainProcess(str6));
  ASSERT_ANY_THROW(calc.MainProcess(str7));
  ASSERT_ANY_THROW(calc.MainProcess(str8));
  ASSERT_ANY_THROW(calc.MainProcess(str9));
  ASSERT_ANY_THROW(calc.MainProcess(str10));
  ASSERT_ANY_THROW(calc.MainProcess(str11));
  ASSERT_ANY_THROW(calc.MainProcess(str12));
  ASSERT_ANY_THROW(calc.MainProcess(str13));
  ASSERT_ANY_THROW(calc.MainProcess(str14));
  ASSERT_ANY_THROW(calc.MainProcess(str15));
}


TEST(Test, Test_calc_model_validation_tests_10) {
  std::string str = "***************************************ln(10)";
  std::string str1 = "                                            ***************************************ln(10)";
  SmartCalc calc;
  ASSERT_ANY_THROW(calc.MainProcess(str));
  ASSERT_ANY_THROW(calc.MainProcess(str1));

}

GTEST_API_ int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}