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

## Build

Appropriate ways to build regularly:
`>make`
or
`>make all`

For debug:
`>make debug  # Clean automatically before build` 
