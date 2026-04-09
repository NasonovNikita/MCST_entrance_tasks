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
> Uses _GNU_SOURCE, requires gcc/CLang at glibc > 2.32.
> 
> Otherwise use `CFLAGS+=-DDONT_USE_GNU_ERROR_HANDLING`

## Task 6

Prints stats of a given file/directory.

```
File: /***/******/******/README.md
Mode: -rw-r--r--
Size: 1319 bytes
UID: 1000
Blocks: 8
Block size: 4096
Last change: Fri Mar dd hh:mm:ss 2026
Last access: Fri Mar dd hh:mm:ss 2026
```

## Task 7

Copies given file to "parent_copy" and "child_copy" created in fork. Also prints the result of copying.

```
# cat test_file
qwerty_mega resg43qt 3qt4 4f2q34 f
# ./task6 test_file
Parent: 
qwerty_mega resg43qt 3qt4 4f2q34 f
Child: 
qwerty_mega resg43qt 3qt4 4f2q34 f
# ls
child_copy  parent_copy  task6  test_file
```

## Task 8

Multiplies matrices 100x100 with additional 0.5 sec delay between iterations. On first SIGINT (ctrl+C) writes current position, on second terminates program.

```
# task8 --signal  (or -- sigaction)
^C
3 83
83 1
3 1
^C
>        # Program ended
```

> [!IMPORTANT]
> Indexes output contains new line as first symbol, as many systems don't go to new line after special inputs.
> It is made for inputs not to be like this:
> ```
> ^C3 83  # blending
> 83 1
> 3 1
> ^C
> ```

## Task 9

Finds longest rising sequence in given array (ending with new line or EOF).

```
# ./task9
<1 2 3 0 4 5 6 0
>0 4 5 6

# ./task9
<1 2 3 4 0 4 5 6 8
>0 4 5 6 8
```

## Build

Appropriate ways to build regularly:
`>make`
or
`>make all`

For debug:
`>make debug  # Clean automatically before build` 
