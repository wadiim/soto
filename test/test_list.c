#include <soto/list.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define VAL1 "foo"
#define VAL2 "bar"
#define VAL3 "baz"
#define VAL4 "qux"

soto_list_char_ptr *list;

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

void generate_nodes(soto_list_char_ptr* l)
{
	soto_list_push_back_char_ptr(l, VAL1);
	test_list_integrity(l);
	soto_list_push_back_char_ptr(l, VAL2);
	test_list_integrity(l);
	soto_list_push_back_char_ptr(l, VAL3);
	test_list_integrity(l);
	soto_list_push_back_char_ptr(l, VAL4);
	test_list_integrity(l);
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

START_TEST(test_list_empty)
{
	// Test soto_list_empty with an empty list.
	ck_assert(soto_list_empty_char_ptr(list) == true);

	generate_nodes(list);

	// Test soto_list_empty with a non-empty list.
	ck_assert(soto_list_empty_char_ptr(list) == false);
}
END_TEST

START_TEST(test_list_push_back)
{
	generate_nodes(list);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL3);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 3), VAL4);

	// Test case where the back pointer is NULL but the list is not empty.
	soto_list_node_char_ptr *back = list->back;
	list->back = NULL;
	ck_assert_int_eq(
		soto_list_push_back_char_ptr(list, "Hello world!"), -1);
	list->back = back;
}
END_TEST

START_TEST(test_list_push_front)
{
	// Push front the first value.
	soto_list_push_front_char_ptr(list, VAL1);
	test_list_integrity(list);

	// Push front the second value.
	soto_list_push_front_char_ptr(list, VAL2);
	test_list_integrity(list);

	// Push front the third value.
	soto_list_push_front_char_ptr(list, VAL3);
	test_list_integrity(list);

	// Push front the fourth value.
	soto_list_push_front_char_ptr(list, VAL4);
	test_list_integrity(list);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL4);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL3);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 3), VAL1);
}
END_TEST

START_TEST(test_list_size)
{
	// Test soto_list_size with an empty list.
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 0);

	generate_nodes(list);

	// Test soto_list_size with a non-empty list.
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 4);
}
END_TEST

START_TEST(test_list_pop_back)
{
	generate_nodes(list);

	// Pop the last node.
	soto_list_pop_back_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 3);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL3);

	// Pop the last node.
	soto_list_pop_back_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 2);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL2);

	// Pop the last node.
	soto_list_pop_back_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 1);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);

	// Pop the last node left.
	soto_list_pop_back_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 0);
}
END_TEST

START_TEST(test_list_pop_front)
{
	generate_nodes(list);

	// Pop the first node.
	soto_list_pop_front_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 3);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL3);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL4);

	// Pop the first node.
	soto_list_pop_front_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 2);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL3);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL4);

	// Pop the first node.
	soto_list_pop_front_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 1);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL4);

	// Pop the last node left.
	soto_list_pop_front_char_ptr(list);
	test_list_integrity(list);
	ck_assert_uint_eq(soto_list_size_char_ptr(list), 0);
}
END_TEST

START_TEST(test_list_find)
{
	// Test soto_list_find with an empty list.
	ck_assert_int_eq(soto_list_find_char_ptr(list, "foo"), -1);

	generate_nodes(list);

	// Test soto_list_find with non-existent value.
	ck_assert_int_eq(soto_list_find_char_ptr(list, "???"), -1);

	// Test soto_list_find with existent value.
	ck_assert_int_eq(soto_list_find_char_ptr(list, VAL2), 1);

	// Test soto_list_find with doubled value.
	soto_list_push_front_char_ptr(list, VAL2);
	ck_assert_int_eq(soto_list_find_char_ptr(list, VAL2), 0);

	// Create a list that stores integers.
	soto_list_int *list_int = soto_list_create_int();

	// Push some values to the newly created list.
	soto_list_push_back_int(list_int, 1);
	soto_list_push_back_int(list_int, 1);
	soto_list_push_back_int(list_int, 2);
	soto_list_push_back_int(list_int, 3);

	// Test soto_list_find with a numeric value.
	ck_assert_int_eq(soto_list_find_int(list_int, 2), 2);

	soto_list_free_int(list_int);
}
END_TEST

START_TEST(test_list_node_at)
{
	// Test soto_list_node_at with an empty list.
	ck_assert_ptr_null(soto_list_node_at_char_ptr(list, 0));

	generate_nodes(list);

	// Test soto_list_node_at with the first position.
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 0), list->front);

	// Test soto_list_node_at with the last position.
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 3), list->back);

	// Test soto_list_node_at with the inner position.
	ck_assert_ptr_eq(soto_list_node_at_char_ptr(list, 2), list->back->prev);
}
END_TEST

START_TEST(test_list_at)
{
	generate_nodes(list);

	// Test soto_list_at with the first position.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);

	// Test soto_list_at with the last position.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 3), VAL4);

	// Test soto_list_at with the inner position.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL3);
}
END_TEST

START_TEST(test_list_insert)
{
	// Test soto_list_insert with an empty list.
	soto_list_insert_char_ptr(list, 0, VAL1);
	test_list_integrity(list);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	soto_list_pop_back_char_ptr(list);

	generate_nodes(list);

	// Test soto_list_insert at the beginnig.
	char *val1 = "1337";
	soto_list_insert_char_ptr(list, 0, val1);
	test_list_integrity(list);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), val1);

	// Test soto_list_insert at the end.
	char *val2 = "2020";
	soto_list_insert_char_ptr(list, soto_list_size_char_ptr(list), val2);
	test_list_integrity(list);
	ck_assert_str_eq(soto_list_at_char_ptr(
		list, soto_list_size_char_ptr(list)-1), val2);

	// Test soto_list_insert at the inner position.
	char *val3 = "0000";
	soto_list_insert_char_ptr(list, 2, val3);
	test_list_integrity(list);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), val3);
}
END_TEST

START_TEST(test_list_remove)
{
	generate_nodes(list);

	// Test removing the first node.
	soto_list_remove_char_ptr(list, 0);
	test_list_integrity(list);
	ck_assert_int_eq(soto_list_size_char_ptr(list), 3);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL3);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL4);

	soto_list_push_front_char_ptr(list, VAL1);

	// Test removing the last node.
	soto_list_remove_char_ptr(list, 3);
	test_list_integrity(list);
	ck_assert_int_eq(soto_list_size_char_ptr(list), 3);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL3);

	soto_list_push_back_char_ptr(list, VAL4);

	// Test removing the inner node.
	soto_list_remove_char_ptr(list, 2);
	test_list_integrity(list);
	ck_assert_int_eq(soto_list_size_char_ptr(list), 3);

	// Test all values in the list.
	ck_assert_str_eq(soto_list_at_char_ptr(list, 0), VAL1);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 1), VAL2);
	ck_assert_str_eq(soto_list_at_char_ptr(list, 2), VAL4);
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
	tcase_add_test(tc_core, test_list_empty);
	tcase_add_test(tc_core, test_list_push_back);
	tcase_add_test(tc_core, test_list_push_front);
	tcase_add_test(tc_core, test_list_size);
	tcase_add_test(tc_core, test_list_pop_back);
	tcase_add_test(tc_core, test_list_pop_front);
	tcase_add_test(tc_core, test_list_find);
	tcase_add_test(tc_core, test_list_node_at);
	tcase_add_test(tc_core, test_list_at);
	tcase_add_test(tc_core, test_list_insert);
	tcase_add_test(tc_core, test_list_remove);

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
