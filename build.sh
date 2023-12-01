#!/bin/bash

cmake --build `pwd`/build --config Debug --target all --

`pwd`/build/bin/aoc2023 `date +%d`
