/* Copyright 2023 The TensorGlue Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

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
 public:
  Scanner(tensorglue::parser::Driver &driver) : driver_(driver) {}

  virtual tensorglue::parser::Parser::symbol_type nextToken();

  virtual ~Scanner() {}

 private:
  Driver& driver_;  
};

}  // namespace parser
}  // namespace parser
