#!/bin/bash
# filepath: /home/elie/Codam/minishell/tests/tokenization/test_tokenization.sh

# Get the script's directory and navigate to project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

cd "$PROJECT_ROOT" || exit 1

echo "=== Compiling Tokenization Test ==="

gcc -Wall -Wextra -Werror -g \
    tests/tokenization/test_tokenization.c \
    src/tokenization/*.c \
    src/parsing.c \
    src/cleanup.c \
    -I inc \
    -L lib/libft \
    -lft \
    -o test_tokenization

if [ $? -eq 0 ]; then
    echo "=== Compilation Successful ==="
    echo "=== Running Tests ==="
    echo ""
    ./test_tokenization
    TEST_EXIT_CODE=$?
    echo ""
    echo "=== Cleaning up ==="
    rm -f test_tokenization

    if [ $TEST_EXIT_CODE -eq 0 ]; then
        echo "✓ All tests completed successfully"
    else
        echo "✗ Tests completed with errors (exit code: $TEST_EXIT_CODE)"
    fi

    exit $TEST_EXIT_CODE
else
    echo "✗ Compilation failed!"
    exit 1
fi