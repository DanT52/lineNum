#include <stdio.h>
#include <stdlib.h>


int lineNum(const char *file, const char *word, int num);

// int main(int argc, char const *argv[])
// {
//     // Check if the correct number of arguments are provided
//     if (argc != 4)
//     {
//         fprintf(stderr, "Usage: %s word file num\n",argv[0]);
//         return 1;
//     }

//     const char *word = argv[1];
//     const char *file = argv[2];
//     int num = atoi(argv[3]);  // Convert the string to an integer

//     int result = lineNum(file, word, num);
//     printf("line num: %d \n", result);

//     return 0;
// }


int main(int argc, char const *argv[]){

    // Define test cases
    char* words[] = {"a b c", "adul", "readable", "readable"};
    char* dicts[] = {"tiny_9", "webster_16", "webster_no_read", "asdfsdfsad"};
    int nums[] = {9, 16, 16, 16};  // Assuming a width of 16 for the last dictionary, adjust as necessary
    int num_tests = sizeof(words) / sizeof(words[0]);

    for(int i = 0; i < num_tests; i++) {
        printf("Testing word '%s' with dictionary '%s'...\n", words[i], dicts[i]);
        int result = lineNum(dicts[i], words[i], nums[i]);
        printf("Result: line num = %d\n\n", result);
    }

    return 0;
}
