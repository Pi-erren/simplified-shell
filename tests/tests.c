#include "minunit.h"
#include <string.h>
#include <stdlib.h>

#include "../main/process_cd_command/init_location_dir.h"
#include "../main/process_cd_command/process_cd_command.h"
#include "../main/process_path_command/process_path_command.h"
#include "../main/process_path_command/init_path.h"

/************************** WARNING **************************
 * Works for Linux
 *
 * please note that some tests required a local path using your local user name
 * please change this according to yours so that tests run correctly
 *
 */
char *username = "replace this by your username";

/************************** Useful functions for tests **************************/
int compareStringArrays(char **arr1, char **arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr1[i], arr2[i]) != 0)
        {
            return 0; // Arrays are not equal
        }
    }
    return 1; // Arrays are equal
}

/************************** Instantiation of variables **************************/
char *location_dir;
char *cd_location_dir;
char **path;
char **before_path;
char **modified_path;
char **words;

/************************** Tests setups **************************/

void test_setup(void)
{
    location_dir = init_location_dir();

    words = malloc(2 * sizeof(char *));
    words[0] = "cd";
    char *specific_path = malloc(7 * sizeof(char));
    strcpy(specific_path, "/home/");
    specific_path = realloc(specific_path, (strlen(specific_path) + strlen(username) + 1) * sizeof(char));
    strcat(specific_path, username);
    words[1] = specific_path;
    cd_location_dir = process_cd_command(words);

    path = init_path();

    words = malloc(3 * sizeof(char *));
    words[0] = "path";
    words[1] = "/bin/";
    words[2] = "/dir_for_executables/";
    before_path = malloc(1 * sizeof(char *));
    before_path[0] = "/bin/";
    int token_count = 3;
    int size_of_before_path = 1;
    modified_path = process_path_command(words, &token_count, &size_of_before_path, before_path);
}
void test_teardown(void)
{
    /* Nothing */
}

/************************** Tests **************************/

MU_TEST(test_init_location_dir)
{
    mu_assert_string_eq("/home", location_dir);
}

MU_TEST(test_cd_command)
{
    char *expected_specific_path = malloc(7 * sizeof(char));
    strcpy(expected_specific_path, "/home/");
    expected_specific_path = realloc(expected_specific_path, (strlen(expected_specific_path) + strlen(username) + 1) * sizeof(char));
    strcat(expected_specific_path, username);
    mu_assert_string_eq(expected_specific_path, cd_location_dir);
}

MU_TEST(test_init_path)
{
    char *expected_path[] = {"/bin/"};
    int size = sizeof(expected_path) / sizeof(expected_path[0]);

    mu_assert(compareStringArrays(expected_path, path, size), "String arrays are not equal");
}

MU_TEST(test_process_path_command)
{
    char *expected_modified_path[] = {"/bin/", "/dir_for_executables/"};
    int size = 2;

    mu_assert(compareStringArrays(expected_modified_path, modified_path, size), "String arrays are not equal");
}

MU_TEST_SUITE(test_suite)
{

    MU_RUN_TEST(test_init_location_dir);
    MU_RUN_TEST(test_cd_command);
    MU_RUN_TEST(test_init_path);
    MU_RUN_TEST(test_process_path_command);
}

/************************** Run tests **************************/

int main(int argc, char *argv[])
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}