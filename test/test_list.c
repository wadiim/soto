#include <soto/list.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

soto_list_char_ptr *list;

void fill_list(void)
{
	soto_list_node_char_ptr *front =
		malloc(sizeof(soto_list_node_char_ptr));
	soto_list_node_char_ptr *back =
		malloc(sizeof(soto_list_node_char_ptr));
	list->front = front;
	list->back = back;
	list->front->next = list->back;
	list->front->prev = NULL;
	list->back->next = NULL;
	list->back->prev = list->front;
}

void push_back_values(int count, ...)
{
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		soto_list_push_back_char_ptr(list, va_arg(args, char*));
	}
	va_end(args);
}

void test_list_integrity(soto_list_char_ptr *l)
{
	soto_list_node_char_ptr *curr = l->front;
	soto_list_node_char_ptr *prev = NULL;

	while (curr != NULL)
	{
		ck_assert_ptr_eq(curr->prev, prev);
		prev = curr;
		curr = curr->next;
	}
}

void setup(void)
{
	list = soto_list_create_char_ptr();
}

void teardown(void)
{
	soto_list_free_char_ptr(list);
}

START_TEST(test_list_create)
{
	ck_assert_ptr_null(list->front);
	ck_assert_ptr_null(list->back);
}
END_TEST

START_TEST(test_list_free)
{
	soto_list_free_char_ptr(list);
	ck_assert_ptr_null(list->front);
	ck_assert_ptr_null(list->back);
}
END_TEST

START_TEST(test_list_empty_with_empty_list)
{
	ck_assert(soto_list_empty_char_ptr(list) == true);
}
END_TEST

START_TEST(test_list_empty_with_non_empty_list)
{
	soto_list_node_char_ptr *node = malloc(sizeof(soto_list_node_char_ptr));
	node->next = node->prev = NULL;
	list->front = list->back = node;
	ck_assert(soto_list_empty_char_ptr(list) == false);
}
END_TEST

START_TEST(test_list_push_back_with_empty_list)
{
	soto_list_push_back_char_ptr(list, "Hello world!");
	ck_assert_str_eq(list->back->data, "Hello world!");
	ck_assert_ptr_eq(list->back, list->front);
	ck_assert_ptr_null(list->back->prev);
	ck_assert_ptr_null(list->back->next);
}
END_TEST

START_TEST(test_list_push_back_with_non_empty_list)
{
	fill_list();
	soto_list_push_back_char_ptr(list, "Hello world!");
	ck_assert_str_eq(list->back->data, "Hello world!");
	ck_assert_ptr_eq(list->back->prev->next, list->back);
	ck_assert_ptr_null(list->back->next);
}
END_TEST

START_TEST(test_list_push_front_with_empty_list)
{
	soto_list_push_back_char_ptr(list, "Hello world!");
	ck_assert_str_eq(list->front->data, "Hello world!");
	ck_assert_ptr_eq(list->back, list->front);
	ck_assert_ptr_null(list->front->prev);
	ck_assert_ptr_null(list->front->next);
}
END_TEST

START_TEST(test_list_push_front_with_non_empty_list)
{
	fill_list();
	soto_list_push_front_char_ptr(list, "Hello world!");
	ck_assert_str_eq(list->front->data, "Hello world!");
	ck_assert_ptr_eq(list->front->next->prev, list->front);
	ck_assert_ptr_null(list->front->prev);
}
END_TEST

START_TEST(test_list_size_with_empty_list)
{
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 0);
}
END_TEST

START_TEST(test_list_size_with_non_empty_list)
{
	push_back_values(3, "foo", "bar", "baz");
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 3);
}
END_TEST

START_TEST(test_list_pop_back)
{
	fill_list();
	size_t old_size = soto_list_size_char_ptr(list);
	soto_list_pop_back_char_ptr(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), old_size-1);
	ck_assert_ptr_null(list->back->next);
}
END_TEST

START_TEST(test_list_pop_back_with_single_elem_list)
{
	soto_list_push_back_char_ptr(list, "Hello world!");
	soto_list_pop_back_char_ptr(list);
	ck_assert(soto_list_empty_char_ptr(list) == true);
}
END_TEST

START_TEST(test_list_pop_front)
{
	fill_list();
	size_t old_size = soto_list_size_char_ptr(list);
	soto_list_pop_front_char_ptr(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), old_size-1);
	ck_assert_ptr_null(list->front->prev);
}
END_TEST

START_TEST(test_list_pop_front_with_single_elem_list)
{
	soto_list_push_front_char_ptr(list, "Hello world!");
	soto_list_pop_front_char_ptr(list);
	ck_assert(soto_list_empty_char_ptr(list) == true);
}
END_TEST

START_TEST(test_list_find_with_empty_list)
{
	ck_assert_int_eq(soto_list_find_char_ptr(list, "foo"), -1);
}
END_TEST

START_TEST(test_list_find_with_non_existent_value)
{
	soto_list_push_front_char_ptr(list, "Hello world!");
	ck_assert_int_eq(soto_list_find_char_ptr(list, "foo"), -1);
}
END_TEST

START_TEST(test_list_find_with_existent_value)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	ck_assert_int_eq(soto_list_find_char_ptr(list, "baz"), 2);
}
END_TEST

START_TEST(test_list_find_with_doubled_value)
{
	push_back_values(4, "foo", "bar", "bar", "qux");
	ck_assert_int_eq(soto_list_find_char_ptr(list, "bar"), 1);
}
END_TEST

START_TEST(test_list_find_with_numeric_value)
{
	soto_list_int *list_int = soto_list_create_int();
	soto_list_push_back_int(list_int, 1);
	soto_list_push_back_int(list_int, 1);
	soto_list_push_back_int(list_int, 2);
	soto_list_push_back_int(list_int, 3);
	ck_assert_int_eq(soto_list_find_int(list_int, 2), 2);
	soto_list_free_int(list_int);
}
END_TEST

START_TEST(test_list_node_at_with_empty_list)
{
	ck_assert_ptr_null(soto_list_node_at_char_ptr(list, 0));
}
END_TEST

START_TEST(test_list_node_at_with_the_first_position)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 0), list->front);
}
END_TEST

START_TEST(test_list_node_at_with_the_last_position)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 3), list->back);
}
END_TEST

START_TEST(test_list_node_at_with_the_inner_positon)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 1),
		list->front->next);
}
END_TEST

START_TEST(test_list_insert_at_the_beginning)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	char *val = "1337";
	soto_list_insert_char_ptr(list, 0, val);
	test_list_integrity(list);
	ck_assert_str_eq(list->front->data, val);
}
END_TEST

START_TEST(test_list_insert_at_the_end)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	char *val = "1337";
	soto_list_insert_char_ptr(list, 4, val);
	test_list_integrity(list);
	ck_assert_str_eq(list->back->data, val);
}
END_TEST

START_TEST(test_list_insert_in_the_middle)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	char *val = "1337";
	soto_list_insert_char_ptr(list, 2, val);
	test_list_integrity(list);
	ck_assert_str_eq(list->front->next->next->data, val);
}
END_TEST

START_TEST(test_list_remove_the_first_node)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	size_t old_size = soto_list_size_char_ptr(list);
	soto_list_remove_char_ptr(list, 0);
	ck_assert_int_eq(soto_list_size_char_ptr(list), old_size-1);
	test_list_integrity(list);
	ck_assert_str_eq(list->front->data, "bar");
	ck_assert_ptr_null(list->front->prev);
}
END_TEST

START_TEST(test_list_remove_the_last_node)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	size_t old_size = soto_list_size_char_ptr(list);
	soto_list_remove_char_ptr(list, 3);
	ck_assert_int_eq(soto_list_size_char_ptr(list), old_size-1);
	test_list_integrity(list);
	ck_assert_str_eq(list->back->data, "baz");
}
END_TEST

START_TEST(test_list_remove_the_inner_node)
{
	push_back_values(4, "foo", "bar", "baz", "qux");
	size_t old_size = soto_list_size_char_ptr(list);
	soto_list_remove_char_ptr(list, 2);
	ck_assert_int_eq(soto_list_size_char_ptr(list), old_size-1);
	test_list_integrity(list);
	ck_assert_str_eq(list->back->data, "qux");
	ck_assert_str_eq(list->front->next->data, "bar");

}
END_TEST

Suite * list_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("List");
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, test_list_create);
	tcase_add_test(tc_core, test_list_free);
	tcase_add_test(tc_core, test_list_empty_with_empty_list);
	tcase_add_test(tc_core, test_list_empty_with_non_empty_list);
	tcase_add_test(tc_core, test_list_push_back_with_empty_list);
	tcase_add_test(tc_core, test_list_push_back_with_non_empty_list);
	tcase_add_test(tc_core, test_list_push_front_with_empty_list);
	tcase_add_test(tc_core, test_list_push_front_with_non_empty_list);
	tcase_add_test(tc_core, test_list_size_with_empty_list);
	tcase_add_test(tc_core, test_list_size_with_non_empty_list);
	tcase_add_test(tc_core, test_list_pop_back);
	tcase_add_test(tc_core, test_list_pop_back_with_single_elem_list);
	tcase_add_test(tc_core, test_list_pop_front);
	tcase_add_test(tc_core, test_list_pop_front_with_single_elem_list);
	tcase_add_test(tc_core, test_list_find_with_empty_list);
	tcase_add_test(tc_core, test_list_find_with_non_existent_value);
	tcase_add_test(tc_core, test_list_find_with_existent_value);
	tcase_add_test(tc_core, test_list_find_with_doubled_value);
	tcase_add_test(tc_core, test_list_find_with_numeric_value);
	tcase_add_test(tc_core, test_list_node_at_with_empty_list);
	tcase_add_test(tc_core, test_list_node_at_with_the_first_position);
	tcase_add_test(tc_core, test_list_node_at_with_the_first_position);
	tcase_add_test(tc_core, test_list_node_at_with_the_inner_positon);
	tcase_add_test(tc_core, test_list_insert_at_the_beginning);
	tcase_add_test(tc_core, test_list_insert_at_the_end);
	tcase_add_test(tc_core, test_list_insert_in_the_middle);
	tcase_add_test(tc_core, test_list_remove_the_first_node);
	tcase_add_test(tc_core, test_list_remove_the_last_node);
	tcase_add_test(tc_core, test_list_remove_the_inner_node);

	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	Suite *s;
	SRunner *sr;

	s = list_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_VERBOSE);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
