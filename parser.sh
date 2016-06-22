#!/bin/bash
lemon -l src/src/parser.y
mv src/src/parser.c src/src/parser.cpp
make
