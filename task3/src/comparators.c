//
// Created by nosokvkokose on 20.03.26.
//

#include "comparators.h"

#include <string.h>

int compare_plain(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    return strcmp(str1, str2);
}

int compare_lex(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    return strcasecmp(str1, str2);
}

int compare_rplain(const void *a, const void *b) {
    return compare_plain(b, a);  // Swap to get reverse order
}

int compare_rlex(const void *a, const void *b) {
    return compare_lex(b, a);  // Swap to get reverse order
}
