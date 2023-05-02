#!/bin/bash

YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

parent_folder=$(find /tmp -type d -name 'test*' -print -quit)

for test in "$parent_folder"/*/;
do
  test_id=$(basename "$test")
  printf "\n"
  echo -e "${YELLOW}Valgrind output for Test ID: $test_id${NC}\n"

  valgrind_log_file="$test/valgrind.log"

  if [ -f "$valgrind_log_file" ]; then
    valgrind_output=$(cat "$valgrind_log_file")
    echo "$valgrind_output"

    # Check for memory leaks or errors
    if grep -q "ERROR SUMMARY: 0 errors" "$valgrind_log_file" && grep -q "All heap blocks were freed -- no leaks are possible" "$valgrind_log_file"; then
      echo -e "${GREEN}No Valgrind issues found.${NC}"
    else
      echo -e "${RED}Valgrind issues detected.${NC}"
      echo "::error file=Test $test_id,title=Valgrind issues::$test_id has Valgrind issues. Check the logs for more information."
    fi
  else
    echo -e "${RED}Valgrind log not found${NC}"
    echo "::error file=Test $test_id,title=Valgrind log not found::$test_id Valgrind log not found"
  fi
  echo "------------------------"
done
