#pragma once
#include "translator.h"
#include <gtest.h>


TEST(Translator, can_count_expressions)
{
	Arithmetic_Expression expr("1+2-20/4*5");
	map<string, double> values;

	double res = expr.Calculate(values);

	ASSERT_EQ(res, -22);
}

TEST(Translator, can_count_expressions_with_brackets)
{
	Arithmetic_Expression expr("1+2-20/(4*5)");
	map<string, double> values;

	double res = expr.Calculate(values);

	ASSERT_EQ(res, 2);
}

TEST(Translator, can_count_expressions_with_floating_point_operands)
{
	Arithmetic_Expression expr("1/2+2.2-20/(4*5)");
	map<string, double> values;
	double check = 0.5 + 2.2 - 1;
	
	double res = expr.Calculate(values);

	ASSERT_EQ(res, check);
}

TEST(Translator, can_count_expressions_with_variables)
{
	Arithmetic_Expression expr("a+b-c+1+a");
	map<string, double> values;
	values["a"] = 1;
	values["b"] = 2;
	values["c"] = 3;

	double res = expr.Calculate(values);

	ASSERT_EQ(res, 2);
}

TEST(Translator, can_count_expressions_with_unary_minus)
{
	Arithmetic_Expression expr("-1+2+(-20)/4*5");
	map<string, double> values;

	double res = expr.Calculate(values);

	ASSERT_EQ(res, -24);
}

TEST(Translator, throw_when_expression_contain_unknown_symbols)
{
	ASSERT_ANY_THROW(Arithmetic_Expression expr("1^2"));
}

TEST(Translator, throw_when_expression_contain_incorrect_brackets)
{
	ASSERT_ANY_THROW(Arithmetic_Expression expr("((1+2)"));
}

TEST(Translator, throw_when_expression_contain_variable_that_starts_from_a_number)
{
	ASSERT_ANY_THROW(Arithmetic_Expression expr("12b+12"));
}

TEST(Translator, throw_when_expression_contain_incorrect_floating_points){
	ASSERT_ANY_THROW(Arithmetic_Expression expr("12..2+12"));
}

TEST(Translator, throw_when_expression_contain_incorrect_operators) {
	ASSERT_ANY_THROW(Arithmetic_Expression expr("12++12"));
}

TEST(Translator, throw_when_expression_contain_division_by_zero) {
	Arithmetic_Expression expr("12/(2-2)");
	map<string, double> values;

	ASSERT_ANY_THROW(expr.Calculate(values););
}