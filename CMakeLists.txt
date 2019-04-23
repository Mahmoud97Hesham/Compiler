# cmake_minimum_required(VERSION <specify CMake version here>)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexicalAnalyzer main.cpp DFAState.cpp DFAState.h NfaAlgorithm.cpp NfaAlgorithm.h LexicalRulesParser.cpp LexicalRulesParser.h NFAState.cpp NFAState.h ConversionToDFA.cpp ConversionToDFA.h MinimizeDFA.cpp MinimizeDFA.h LexicalAnalyzerGenerator.cpp LexicalAnaLyzerGenerator.h Phase2Main.cpp ProductionRule.cpp ProductionRule.h Symbol.cpp Symbol.h SymbolsSet.cpp SymbolsSet.h ParserGenerator.cpp ParserGenerator.h SyntaxRulesParser.cpp SyntaxRulesParser.h)
