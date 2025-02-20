#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(stack<int> s);
}


TEST(Stack, can_create_copied_stack)
{
	stack<int> s1;

	ASSERT_NO_THROW(stack<int> s2(s1));
}

TEST(Stack, equal_stacks_are_equal)
{
    stack<int> s1;
    stack<int> s2;
    s1.push(1); s2.push(1);
    s1.push(1); s2.push(1);

    ASSERT_EQ(s1==s2,1);
}

TEST(Stack, not_equal_stacks_are_not_equal)
{
    stack<int> s1;
    stack<int> s2;
    s1.push(1); s2.push(2);
    s1.push(1); s2.push(2);

    ASSERT_EQ(s1!=s2, 1);
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
    stack<int> s1;

    stack<int> s2(s1);

    EXPECT_EQ(s1==s2, 1);
}

TEST(Stack, can_get_size)
{
    stack<int> s;
    s.push(1);
    s.push(1);
    s.push(1);
    s.push(1);

    EXPECT_EQ(4, s.size());
}

TEST(Stack, can_check_if_stack_is_empty)
{
    stack<int> s;

    EXPECT_EQ(1, s.empty());
}

TEST(Stack, can_push_element_in_stack)
{
    stack<int> s;

    ASSERT_NO_THROW(s.push(1));
}

TEST(Stack, can_pop_element_from_non_empty_stack)
{
    stack<int> s;
    s.push(1);

    ASSERT_NO_THROW(s.pop());
}

TEST(Stack, cant_pop_element_from_empty_stack)
{
    stack<int> s;

    ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, can_get_top_element_from_non_empty_stack)
{
    stack<int> s;
    s.push(1);
    s.push(2);

    ASSERT_NO_THROW(s.top(),2);
}

TEST(Stack, can_get_top_element_from_stack)
{
    stack<int> s;

    ASSERT_ANY_THROW(s.top());
}

TEST(Stack, some_push_and_pop_operations_in_random_order)
{
    stack<int> s;
    stack<int> s1;
    s1.push(5);
    
    s.push(1);
    s.pop();
    s.push(2);
    s.push(3);
    s.pop();
    s.push(4);
    s.pop();
    s.pop();
    s.push(5);
    s.push(6);
    s.pop();

    EXPECT_EQ(s1==s, 1);
}