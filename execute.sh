#!/bin/bash
./pipex infile "    cat -e" "/usr/bin/cat -e" out1
exit1=$(echo $?)
< infile "cat -e" | /usr/bin/cat -e > out2
exit2=$(echo $?)

echo "exepected output: 
"
cat out2
echo "expected exit code: $exit2"
echo "---------------------------------"
echo "your output: "
cat out1
echo "your exit code: $exit1"
