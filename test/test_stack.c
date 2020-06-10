#include <soto/stack.h>
#include <check.h>
#include <stdlib.h>

static soto_stack_int stack;
static const int VAL[5] = { 3, 1, 4, 1, 5 };
static const size_t VAL_LEN = 5;

void generate_elements(soto_stack_int *stack)
{
	for (size_t i = 0; i < VAL_LEN; ++i)
	{
		soto_stack_push_int(stack, VAL[i]);
		ck_assert_int_eq(stack->data[i], VAL[i]);
		ck_assert_int_eq(stack->size, i+1);
	}
}

void setup(void)
{
	soto_stack_init_int(&stack);
}

void teardown(void)
{
	soto_stack_free_int(&stack);
}

START_TEST(test_stack_push)
{
	generate_elements(&stack);
}
END_TEST

START_TEST(test_stack_pop)
{
	generate_elements(&stack);

	for (size_t i = VAL_LEN; i > 0; --i)
	{
		ck_assert_int_eq(soto_stack_top_int(&stack), VAL[i-1]);
		soto_stack_pop_int(&stack);
		ck_assert_int_eq(stack.size, i-1);
	}
}
END_TEST

START_TEST(test_stack_empty)
{
	// Test soto_stack_empty() with an empty stack.
	ck_assert(soto_stack_empty_int(&stack) == true);

	generate_elements(&stack);

	// Test soto_stack_empty() with a non-empty stack.
	ck_assert(soto_stack_empty_int(&stack) == false);
}
END_TEST

START_TEST(test_stack_top)
{
	generate_elements(&stack);

	ck_assert_int_eq(soto_stack_top_int(&stack), VAL[stack.size-1]);
}
END_TEST

Suite * stack_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Stack");
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, test_stack_push);
	tcase_add_test(tc_core, test_stack_pop);
	tcase_add_test(tc_core, test_stack_empty);
	tcase_add_test(tc_core, test_stack_top);

	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	Suite *s;
	SRunner *sr;

	s = stack_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_VERBOSE);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
