#!/bin/bash
lemon -l src/src/FOLParserGrammar.y
mv src/src/FOLParserGrammar.c src/src/FOLParserGrammar.cpp
cp src/src/FOLParserGrammar.h src/includes/FOLParserGrammar.h
make
