#include <gtest/gtest.h>
#include "PolishRecord.h"

TEST(PolishRecord, can_convert_to_polish_a_simple_string_with_numbers) {
  Polish Expression;
  char* expression = "10+5";
  char* current = Expression.ConvertToPolish(expression);
  char* res = "10 5 +";
  for (int i = 0; i < strlen(res); ++i)
    EXPECT_EQ(res[i], current[i]);
}

TEST(PolishRecord, can_convert_to_polish_a_simple_string_with_variables) {
  Polish Expression;
  char* expression = "(a-10)*5";
  char* current = Expression.ConvertToPolish(expression);
  char* res = "a 10 - 5 *";
  for (int i = 0; i < strlen(res); ++i)
    EXPECT_EQ(res[i], current[i]);
}

TEST(PolishRecord, can_convert_to_polish_a_simple_string_with_unary_minus) {
  Polish Expression;
  char* expression = "-10+5*b^(-3)";
  char* current = Expression.ConvertToPolish(expression);
  char* res = "10 _ 5 b 3 _ ^ * +";
  for (int i = 0; i < strlen(res); ++i)
    EXPECT_EQ(res[i], current[i]);
}

TEST(PolishRecord, can_convert_to_polish_string_with_numbers_and_module) {
  Polish Expression;
  char* expression = "3 + 5 - | 8 - 10 * 2 + 6 / 3 |";
  char* current = Expression.ConvertToPolish(expression);
  char* res = "3 5 + 8 10 2 * - 6 3 / + | -";
  for (int i = 0; i < strlen(res); ++i)
    EXPECT_EQ(res[i], current[i]);
}

TEST(PolishRecord, can_convert_to_polish_string_with_modules) {
  Polish Expression;
  char* expression = "|-|-|a|+|b|+|c|||";
  char* current = Expression.ConvertToPolish(expression);
  char* res = "a | _ b | + c | + | _ |";
  for (int i = 0; i < strlen(res); ++i)
    EXPECT_EQ(res[i], current[i]);
}

TEST(Calculator, example_1_with_modules_and_unary_minus) {
  Polish Expression;
  char* expression = "|-15^2+|-5|^2+|-5^2||-10";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(165, res);
}

TEST(Calculator, example_2_with_numbers) {
  Polish Expression;
  char* expression = "100 - | 20 - 15 * 3 + 15 / 3 |";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(80, res);
}

TEST(Calculator, example_3_with_numbers) {
  Polish Expression;
  char* expression = "15-5-8/(3*2+2)-3^2";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(0, res);
}

TEST(Calculator, example_4_with_numbers) {
  Polish Expression;
  char* expression = "(11-1) - 3*5^1 -5 -21/(8-1)*2/3*2";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-14, res);
}

TEST(Calculator, example_5_with_module) {
  Polish Expression;
  char* expression = "|1 - 15| / 2";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(7, res);
}

TEST(Calculator, example_6_with_module_and_variable) {
  Polish Expression;
  char* expression = "|1 - a| / 2";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 15);
  double res = Expression.Calculator(a);

  EXPECT_EQ(7, res);
}

TEST(Calculator, example_6_with_variables) {
  Polish Expression;
  char* expression = "(a-1) - 3*b^1 -5 -21/(c-1)*2/3*2";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 11);
  Expression.AddVar('b', 5);
  Expression.AddVar('c', 8);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-14, res);
}

TEST(Calculator, example_7_with_variables_and_unary_minus) {
  Polish Expression;
  char* expression = "(a-1) + (- 3*b^1) -5 -21/(c-1)*2/3*2";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 11);
  Expression.AddVar('b', 5);
  Expression.AddVar('c', 8);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-14, res);
}

TEST(Calculator, example_8_with_variables) {
  Polish Expression;
  char* expression = "-(a-1) + (- 3*b^1) -5 -21/(c-1)*2/3*2";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 11);
  Expression.AddVar('b', 5);
  Expression.AddVar('c', 8);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-34, res);
}

TEST(Calculator, example_9_with_halfpart) {
  Polish Expression;
  char* expression = "(-(a+5)) - b*5 +5.5 -c/(5-1)";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', -25);
  Expression.AddVar('b', 5);
  Expression.AddVar('c', 4);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-0.5, res);
}

TEST(Calculator, example_10_with_halfpart) {
  Polish Expression;
  char* expression = "-10.5+a^(2*b)/4";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 2);
  Expression.AddVar('b', 2);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-6.5, res);
}

TEST(Calculator, example_11_with_modules) {
  Polish Expression;
  char* expression = "-||-a|+|b||";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 5);
  Expression.AddVar('b', -5);
  double res = Expression.Calculator(a);

  EXPECT_EQ(-10, res);
}

TEST(Calculator, example_12_with_modules) {
  Polish Expression;
  char* expression = "|-a|-b";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 5);
  Expression.AddVar('b', 5);
  double res = Expression.Calculator(a);

  EXPECT_EQ(0, res);
}

TEST(Calculator, example_13_with_powers) {
  Polish Expression;
  char* expression = "2^3^2";
  char* a = Expression.ConvertToPolish(expression);
  double res = Expression.Calculator(a);

  EXPECT_EQ(512, res);
}

TEST(PolishRecord, throw_when_costant_and_variable_together) {
  Polish Expression;
  char* expression = "(-5a) - 55^5 + 555 -5/(5-5/1)";
  char* a = Expression.ConvertToPolish(expression);

  ASSERT_ANY_THROW(Expression.Calculator(a));
}

TEST(PolishRecord, throw_when_empty_string) {
  Polish Expression;
  char* expression = "";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(PolishRecord, throw_when_two_operators_together) {
  Polish Expression;
  char* expression = "+-10.5+a^(2*b)/4";

  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(Calculator, throw_when_variable_is_not_declared) {
  Polish Expression;
  char* expression = "-10.5+a^(2*b)/4";
  char* a = Expression.ConvertToPolish(expression);
  Expression.AddVar('a', 2);

  ASSERT_ANY_THROW(Expression.Calculator(a));
}

TEST(PolishRecord, throw_1_with_wrong_brackets) {
  Polish Expression;
  char* expression = "|1+2-(2+1|-2)*5)";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(PolishRecord, throw_2_with_wrong_brackets) {
  Polish Expression;
  char* expression = "|1+1*(2+2)*3|-4)";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(PolishRecord, throw_3_with_empty_brackets) {
  Polish Expression;
  char* expression = "()";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(PolishRecord, throw_4_with_empty_brackets) {
  Polish Expression;
  char* expression = "||";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

TEST(PolishRecord, throw_5_with_double_operators) {
  Polish Expression;
  char* expression = "--8";
  ASSERT_ANY_THROW(Expression.ConvertToPolish(expression));
}

int main(int ac, char* av[]) {
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
