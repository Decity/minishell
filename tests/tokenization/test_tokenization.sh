#!/bin/bash
# filepath: /home/elie/Codam/minishell/tests/tokenization/run_test.sh

echo "=== Compiling Tokenization Test ==="

gcc -Wall -Wextra -Werror -g \
    -I../../inc \
    -I../../lib/libft/inc \
    test_tokenization.c \
    ../../src/tokenization.c \
    ../../src/debug.c \
    ../../lib/libft/libft.a \
    -o test_tokenization

if [ $? -eq 0 ]; then
    echo "=== Running Tests ==="
    ./test_tokenization
    rm -f test_tokenization
else
    echo "Compilation failed!"
    exit 1
fi