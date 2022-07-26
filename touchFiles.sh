#!/bin/bash

# Files with .h and .c extensions
files=("PriorityQueue" "List" "Graph")

for file in "${files[@]}"; do
    touch $file.c
    touch $file.h
done
