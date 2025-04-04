#!/bin/env bash

cmake -B build/ -DCMAKE_BUILD_TYPE=Release . && cmake --build build/

retree() {
    ./build/retree "$@"
}

test_retree_assert_with_diff() {
    local test_file="$1"
    local expected_file="$2"
    local output_dir="./runs"
    local preserve_files=true

    # Check for --no-preserve-files flag
    for arg in "$@"; do
        if [[ "$arg" == "--no-preserve-files" ]]; then
            preserve_files=false
            break
        fi
    done

    rm -rf "$output_dir"
    mkdir -p "$output_dir"

    # Construct retree command
    if $preserve_files; then
        retree -f "$test_file" -v -d "$output_dir" -p
    else
        retree -f "$test_file" -v -d "$output_dir"
    fi

    # Determine expected output
    if [[ -z "$expected_file" ]]; then
        expected=$(tree -a --noreport "$output_dir")
    else
        expected=$(cat "$expected_file")
    fi

    # Compare actual output with expected
    if diff <(tree -a --noreport "$output_dir") <(echo "$expected"); then
        echo "✅ Test passed for $test_file"
    else
        echo "❌ Test failed for $test_file"
        exit 1
    fi
}

# Run tests
test_retree_assert_with_diff "tests/simple-tree.txt"
test_retree_assert_with_diff "tests/tree-with-comments.txt" "tests/simple-tree.txt"
test_retree_assert_with_diff "tests/no-preserve-files-tree.txt" "tests/no-preserve-files.txt" "--no-preserve-files"
test_retree_assert_with_diff "tests/giant-example.txt"
