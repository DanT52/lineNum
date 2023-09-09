#include <stdio.h>
#include <stdlib.h>


int lineNum(const char *file, const char *word, int num);

int main(int argc, char const *argv[])
{
    // Check if the correct number of arguments are provided
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s word file num\n",argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *file = argv[2];
    int num = atoi(argv[3]);  // Convert the string to an integer

    int result = lineNum(file, word, num);
    printf("line num: %d \n", result);

    return 0;
}
