#!/bin/bash
cd src/src
lemon -l -m FOLParserGrammar.y
mv FOLParserGrammar.c FOLParserGrammar.cpp

lemon -l -m ASPParserGrammar.y
mv ASPParserGrammar.c ASPParserGrammar.cpp

cd ..
cd ..
make
