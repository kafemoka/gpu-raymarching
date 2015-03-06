#!/bin/bash

for file in ./build/bin/*
    do
    if [ ${file: -9} == "_test.out" ]
        then
        echo "Running ${file}"
        $file
    fi
done
