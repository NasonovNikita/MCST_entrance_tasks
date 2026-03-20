//
// Created by nosokvkokose on 20.03.26.
//

#pragma once

#ifndef COMPARATORS_H
#define COMPARATORS_H

typedef int (*comparator)(const void *, const void *);

int compare_plain(const void *a, const void *b);
int compare_lex(const void *a, const void *b);
int compare_rplain(const void *a, const void *b);
int compare_rlex(const void *a, const void *b);

#endif //COMPARATORS_H
