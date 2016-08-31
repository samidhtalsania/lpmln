#!/bin/bash
cd src/src
#lemon -l -m FOLParserGrammar.y
#mv FOLParserGrammar.c FOLParserGrammar.cpp

#lemon  -m ASPParserGrammar.y
#mv ASPParserGrammar.c ASPParserGrammar.cpp

lemon -l -m MVSMParserGrammar.y
mv MVSMParserGrammar.c MVSMParserGrammar.cpp

cd ..
cd ..
make
