# MCST_entrance_tasks
Solutions for entrance tasks for summer (2026) internship in MCST

## Task 1
sort given int array using N threads

example:

```
echo 3 7 12 95 2 51 12 412 124 | ./task1 6  # 6 threads (at maximum< less can be used)
>2 3 7 12 12 51 95 124 412
```

## Task 2

Known issue: doesn't work

## Task 3

Sort input file and save result in output file. 

```
# cat in.txt
>3
>
>2
>a
# ./task3 in.txt out.txt plain
# cat out.txt
>2
>3
>a
```

## Task 4

Parse console arguments and print short, long options and other arguments.

> [!IMPORTANT]
> Conventionally short options don't have arguments and long options do

Current list of parsed arguments can be found in main.c

#### Examples:
```
# task4 -tm -s --elbrus=16c file0 --elbrus=2c3 file1
>Short options: 't' 'm' 's'
>Long options: 'elbrus=16c' 'elbrus=2c3'
>Non options: 'file0' 'file1'
# task4 -tm -x --elbrus=8c
>Incorrect option: 'x'
```

## Task 5

Intentionally causes error and prints the error

```
build/bin/task5
Can't open file: No such file or directory
Errno = ENOENT
```

> [!WARNING]
> Uses _GNU_SOURCE, requires gcc/CLang at glibc > 2.32

## Build

Appropriate ways to build regularly:
`>make`
or
`>make all`

For debug:
`>make debug  # Clean automatically before build` 
