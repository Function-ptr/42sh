#!/bin/bash

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Specify the parent folder containing the subfolders
parent_folder=$(find /tmp -type d -name 'test*' -print -quit)

# Loop through each test ID in the parent folder
for test in "$parent_folder"/*/; do
  test_id=$(basename "$test")
  printf "\n"
  # Print the name of the subfolder
  echo -e "${YELLOW}Test ID: $test_id${NC}\n"

  # Check if tcsh.out exists in the subfolder
  if [ -f "$test/tcsh.out" ]; then
    echo -e "${GREEN}Expected output:${NC}"
    tcsh_output=$(cat "$test/tcsh.out")
    echo "$tcsh_output"
  else
    echo -e "${RED}Expected output: tcsh.out not found${NC}"
    echo "::error file=Test $test_id,title=Failed Test $test_id::$test_id is failed. Expected output: Not found, Actual output: Not found"
    continue
  fi
  printf "\n"

  # Check if mysh.out exists in the subfolder
  if [ -f "$test/mysh.out" ]; then
    echo -e "${GREEN}Actual output:${NC}"
    mysh_output=$(cat "$test/mysh.out")
    echo "$mysh_output"
  else
    echo -e "${RED}Actual output: mysh.out not found${NC}"
    echo "::error file=Test $test_id,title=Failed Test $test_id::$test_id is failed. Expected output: $tcsh_output, Actual output: Not found"
    continue
  fi
  echo "------------------------"

  # Compare expected and actual output
  if [ "$tcsh_output" != "$mysh_output" ]; then
    echo "::error file=Test $test_id,title=Failed Test $test_id::$test_id is failed. Expected output: $tcsh_output, Actual output: $mysh_output"
  fi
done
