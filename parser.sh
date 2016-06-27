#!/bin/bash
lemon -l src/src/parser.y
mv src/src/parser.c src/src/parser.cpp
cp src/src/parser.h src/includes/parser.h
make
