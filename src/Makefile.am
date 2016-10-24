INCLUDE = $(PROJECT_ROOT)/src/includes
AM_CPPFLAGS = -I $(INCLUDE)
AM_CFLAGS = -I $(INCLUDE)
AM_CXXFLAGS = -I $(INCLUDE)
bin_PROGRAMS = ../lpmlncompiler  lpmln lpmln2wc

___lpmlncompiler_SOURCES = \
			main.cpp \
			src/Completion.cpp \
			src/Domain.cpp \
			src/FactCompletion.cpp \
			src/Predicate.cpp \
			src/Token.cpp \
			src/Tree.cpp \
			src/Variable.cpp \
			src/RuleCompletion.cpp \
			src/Body.cpp \
			src/BodyDef.cpp \
			src/Head.cpp \
			src/exceptions/undefined_predicate.cpp \
			src/exceptions/syntax_exception.cpp \
			src/exceptions/undefined_key.cpp \
			src/exceptions/invalid_arguments.cpp \
			src/Config.cpp \
			src/ParserWrapper.cpp \
			src/ParserFactory.cpp \
			src/FOLParserGrammar.cpp \
			src/ASPParserGrammar.cpp \
			src/MVSMParserGrammar.cpp \
			src/FOLLexer.cpp \
			src/ASPLexer.cpp \
			src/MVSMLexer.cpp \
			src/LexerFactory.cpp \
			src/LanguageConstants.cpp

lpmln_LDADD = -luuid

lpmln_SOURCES = \
		lpexec_src/lpexec.cpp \
		lpexec_src/FileConfig.cpp \
		lpexec_src/NoLanguageSelectedException.cpp

lpmln2wc_LDADD = -lboost_regex
lpmln2wc_SOURCES = \
		lpmln2wc_src/lpmln2wc.cpp