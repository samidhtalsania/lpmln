#!/bin/bash
cd src/src
#lemon -m FOLParserGrammar.y
#mv FOLParserGrammar.c FOLParserGrammar.cpp

lemon -m ASPParserGrammar.y
mv ASPParserGrammar.c ASPParserGrammar.cpp

lemon  -m MVSMParserGrammar.y
mv MVSMParserGrammar.c MVSMParserGrammar.cpp

cd ..
cd ..
make
