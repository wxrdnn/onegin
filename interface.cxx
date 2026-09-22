#include "h/interface.h"
#include "h/types.h"
#include <cassert>
#include <cstdio>
#include <cstring>

int ParseLaunchOptions(const int argc, char *const *const argv, LaunchOptions *const launchOptions)
{
    launchOptions->inputFileName = "onegin";
    launchOptions->outputFileName = "onegin_sorted";
    launchOptions->sortingMode = smAscending;

    if (argc == 1 || argc > 4)
    {
        // fprintf(stderr, "case 1 / default");
        return -1;
    }

    if (argc >= 2)
    {
        assert(argv[1]);

        if (strcmp(argv[1], "-h") == 0)
        {
            return -1;
        }
        // fprintf(stderr, "case 2");
        launchOptions->inputFileName = argv[1];
    }
    if (argc >= 3)
    {
        // fprintf(stderr, "case 3");
        assert(argv[2]);
        launchOptions->outputFileName = argv[2];
    }
    if (argc >= 4)
    {
        // fprintf(stderr, "case 4");
        assert(argv[3]);
        if (strcmp(argv[3], "-a") == 0)
        {
            // fprintf(stderr, "DEBUG: selected ascending sorting mode.\n");
            launchOptions->sortingMode = smAscending;
        }
        else if (strcmp(argv[3], "-d") == 0)
        {
            // fprintf(stderr, "DEBUG: selected descending sorting mode.\n");
            launchOptions->sortingMode = smDescending;
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

void PrintHelp(const char *const programName)
{
    printf("Usage: %s [INPUT_FILE] [OUTPUT_FILE] [SORTING_MODE]\n\n"
           "Sorting modes:\n"
           "\t-a - Sort by ascending.\n"
           "\t-d - Sort by descending.\n",
           programName);
}
