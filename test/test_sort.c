#include <soto/sort.h>
#include <soto/utils.h>
#include <check.h>
#include <stdlib.h>

#define ARRSIZE 7

static int sorted[ARRSIZE] = { 1, 1, 2, 3, 4, 5, 9 };
static char *strings_sorted[ARRSIZE] = {
	"bar",
	"baz",
	"corge",
	"foo",
	"quux",
	"quuz",
	"qux"
};
int *arr;
char **strings;

void setup(void)
{
	arr = malloc(ARRSIZE*sizeof(int));
	memcpy(arr, (int []){ 3, 1, 4, 1, 5, 9, 2 }, ARRSIZE*sizeof(int));

	strings = malloc(ARRSIZE*sizeof(char *));
	memcpy(strings, (char * []){
		"foo",
		"bar",
		"baz",
		"qux",
		"quux",
		"quuz",
		"corge"
	}, ARRSIZE*sizeof(char *));
}

void teardown(void)
{
	free(arr);
	free(strings);
}

START_TEST(test_bubble_sort)
{
	soto_bubble_sort_int(arr, ARRSIZE, &soto_greater_int);
	ck_assert(arr[_i] == sorted[_i]);

	soto_bubble_sort_char_ptr(strings, ARRSIZE, &soto_greater_char_ptr);
	ck_assert_str_eq(strings[_i], strings_sorted[_i]);
}
END_TEST

START_TEST(test_selection_sort)
{
	soto_selection_sort_int(arr, ARRSIZE, &soto_greater_int);
	ck_assert(arr[_i] == sorted[_i]);

	soto_selection_sort_char_ptr(strings, ARRSIZE, &soto_greater_char_ptr);
	ck_assert_str_eq(strings[_i], strings_sorted[_i]);
}
END_TEST

START_TEST(test_insertion_sort)
{
	soto_insertion_sort_int(arr, ARRSIZE, &soto_greater_int);
	ck_assert(arr[_i] == sorted[_i]);

	soto_insertion_sort_char_ptr(strings, ARRSIZE, &soto_greater_char_ptr);
	ck_assert_str_eq(strings[_i], strings_sorted[_i]);
}
END_TEST

START_TEST(test_quick_sort)
{
	soto_quick_sort_int(arr, ARRSIZE, &soto_greater_int);
	ck_assert(arr[_i] == sorted[_i]);

	soto_quick_sort_char_ptr(strings, ARRSIZE, &soto_greater_char_ptr);
	ck_assert_str_eq(strings[_i], strings_sorted[_i]);
}
END_TEST

Suite * sort_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Sort");
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_loop_test(tc_core, test_bubble_sort, 0, ARRSIZE);
	tcase_add_loop_test(tc_core, test_selection_sort, 0, ARRSIZE);
	tcase_add_loop_test(tc_core, test_insertion_sort, 0, ARRSIZE);
	tcase_add_loop_test(tc_core, test_quick_sort, 0, ARRSIZE);

	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	Suite *s;
	SRunner *sr;

	s = sort_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_VERBOSE);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
