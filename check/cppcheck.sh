#!/bin/bash

function Check()
{
    cppcheck -j 8 --enable=all  --project=./compile_commands.json ./include/*.h ./src/*.cpp --suppress=*:external/* > ./check/cppcheck.log 2>&1
}