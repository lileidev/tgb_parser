#pragma once

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Parser_FlexLexer

#include "FlexLexer.h"

#endif

#undef YY_DECL
#define YY_DECL tensorglue::parser::Parser::symbol_type tensorglue::parser::Scanner::nextToken()

#include "parser.h"

namespace tensorglue {
namespace parser {

class Driver;

class Scanner : public yyFlexLexer {
  private:
  Driver& driver_;

  public:
  Scanner(tensorglue::parser::Driver &driver) : driver_(driver) {}

  virtual tensorglue::parser::Parser::symbol_type nextToken();

  virtual ~Scanner() {}
};

}
}
