#!/bin/sh
set -eu
for file in ./*.c; do
    name="${file#./}"
    output="${name%.c}"
    if [ "$name" = "11_polynomial_evaluation.c" ]; then
        gcc -std=c11 -Wall -Wextra -pedantic "$file" -lm -o "$output"
    else
        gcc -std=c11 -Wall -Wextra -pedantic "$file" -o "$output"
    fi
done
printf '%s\n' "All C files compiled."
