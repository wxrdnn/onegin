#ifndef INTERFACE_H

#define INTERFACE_H

#include "types.h"

int ParseLaunchOptions(const int argc, char *const *const argv, LaunchOptions *const launchOptions);

void PrintHelp(const char *const programName);

#endif
