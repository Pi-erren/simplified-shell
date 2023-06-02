#include "minunit.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../main/process_cd_command/init_location_dir.h"
#include "../main/process_cd_command/process_cd_command.h"
#include "../main/process_path_command/process_path_command.h"
#include "../main/process_path_command/init_path.h"
#include "../main/process_user_command/process_redirection.h"

/************************** WARNING **************************
 * Works for Linux
 *
 * please note that some tests required a local path using your local user name
 * please change this according to yours so that tests run correctly
 *
 */

char *username = "replace this by your local username";

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

char **command1;
char **command2;
char **command3;
char *expected_command[] = {"a", "<", "b"};

char **command21;
char **command22;
char **command23;
char *expected_command2[] = {"a", ">", "b"};

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
    int token_count0 = 3;
    int size_of_before_path = 1;
    modified_path = process_path_command(words, &token_count0, &size_of_before_path, before_path);

    int size_of_command1 = 0;
    int token_count1 = 2;
    bool input_redirection1 = false;
    bool output_redirection1 = false;
    words = malloc(2 * sizeof(char *));
    words[0] = "a<";
    words[1] = "b";
    command1 = process_redirection(words, &token_count1, &size_of_command1, &input_redirection1, &output_redirection1);

    int size_of_command2 = 0;
    int token_count2 = 2;
    bool input_redirection2 = false;
    bool output_redirection2 = false;
    words = malloc(2 * sizeof(char *));
    words[0] = "a";
    words[1] = "<b";
    command2 = process_redirection(words, &token_count2, &size_of_command2, &input_redirection2, &output_redirection2);

    int size_of_command3 = 0;
    int token_count3 = 3;
    bool input_redirection3 = false;
    bool output_redirection3 = false;
    words = malloc(3 * sizeof(char *));
    words[0] = "a";
    words[1] = "<";
    words[2] = "b";
    command3 = process_redirection(words, &token_count3, &size_of_command3, &input_redirection3, &output_redirection3);

    int size_of_command21 = 0;
    int token_count21 = 2;
    bool input_redirection21 = false;
    bool output_redirection21 = false;
    words = malloc(2 * sizeof(char *));
    words[0] = "a>";
    words[1] = "b";
    command21 = process_redirection(words, &token_count21, &size_of_command21, &input_redirection21, &output_redirection21);

    int size_of_command22 = 0;
    int token_count22 = 2;
    bool input_redirection22 = false;
    bool output_redirection22 = false;
    words = malloc(2 * sizeof(char *));
    words[0] = "a";
    words[1] = ">b";
    command22 = process_redirection(words, &token_count22, &size_of_command22, &input_redirection22, &output_redirection22);

    int size_of_command23 = 0;
    int token_count23 = 3;
    bool input_redirection23 = false;
    bool output_redirection23 = false;
    words = malloc(3 * sizeof(char *));
    words[0] = "a";
    words[1] = ">";
    words[2] = "b";
    command23 = process_redirection(words, &token_count23, &size_of_command23, &input_redirection23, &output_redirection23);
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

MU_TEST(test_process_redirection1)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command, command1, size), "String arrays are not equal");
}

MU_TEST(test_process_redirection2)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command, command2, size), "String arrays are not equal");
}

MU_TEST(test_process_redirection3)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command, command3, size), "String arrays are not equal");
}

MU_TEST(test_process_redirection21)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command2, command21, size), "String arrays are not equal");
}

MU_TEST(test_process_redirection22)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command2, command22, size), "String arrays are not equal");
}

MU_TEST(test_process_redirection23)
{

    int size = 3;
    mu_assert(compareStringArrays(expected_command2, command23, size), "String arrays are not equal");
}

MU_TEST_SUITE(test_suite)
{

    MU_RUN_TEST(test_init_location_dir);
    MU_RUN_TEST(test_cd_command);
    MU_RUN_TEST(test_init_path);
    MU_RUN_TEST(test_process_path_command);
    MU_RUN_TEST(test_process_redirection1);
    MU_RUN_TEST(test_process_redirection2);
    MU_RUN_TEST(test_process_redirection3);
    MU_RUN_TEST(test_process_redirection21);
    MU_RUN_TEST(test_process_redirection22);
    MU_RUN_TEST(test_process_redirection23);
}

/************************** Run tests **************************/

int main(int argc, char *argv[])
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}