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

%skeleton "lalr1.cc" // -*- C++ -*-
%require  "3.8.2"
%language "c++"

%define api.namespace {tensorglue::parser}
%define api.parser.class {Parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%defines

%header "parser.h"
%output "parser.cpp"

%code requires {
  #include <memory>
  #include <string>
  #include <iostream>
  #include <unordered_map>

  #include "tnode.h"
  using namespace tensorglue::top;

  namespace tensorglue::parser {
    class Scanner;
    class Driver;
  }
}

%{
  #include "scanner.h"
  #include "driver.h"

  #include "tnode.h"

  using namespace tensorglue::top;

  static tensorglue::parser::Parser::symbol_type yylex(tensorglue::parser::Scanner& scanner, tensorglue::parser::Driver& driver) {
    return scanner.nextToken();
  }

  using namespace tensorglue::parser;
%}

// define parameters parser pass to scanner
%lex-param { tensorglue::parser::Scanner& scanner }
%lex-param { tensorglue::parser::Driver& driver }

// define parameters driver pass to parser
%parse-param { tensorglue::parser::Scanner& scanner }
%parse-param { tensorglue::parser::Driver& driver }

%locations

%define parse.error verbose
%define api.token.prefix {TOKEN_}

%token EOL
%token END 0

%type <std::vector<TNode*>*> stmts call_args
%type <TNode*> stmt assign expr numeric identifier unary_expr binary_expr call_expr if_expr

/* operator precedence for methematical operations */
%left SEP
%nonassoc EQUAL
%left COMMA
%left CEQ CNE
%left CLT CLE CGT CGE
%left PLUS MINUS
%left MUL DIV MATMUL POWER
%right PLUS1 MINUS1
%nonassoc NOT
%left LPAREN RPAREN
%left DOT

%token <std::string> IDENTIFIER INTEGER DOUBLE PI IF

%start program

%%

program : stmts {
  TNode* node = new TNode("tgb##output", "CompoundOutputs", OperatorType::COMPOUNDOUTPUTS);
  driver.SetRoot(node);
  for (auto &item : *$1) {
    if (std::regex_match(item->node_label_, output_regex)) {
      driver.AddSubTree(driver.GetRoot(), item);
    }
  }
  delete $1;
  driver.ReleaseTempMapNodes();
}
        ;
      
stmts : stmt { $$ = new std::vector<TNode*>{$1}; }
      | stmts stmt { $1->emplace_back($2); $$ = $1; }
      ;

stmt : assign SEP { $$ = $1; driver.StoreMap($1); }
     ;
     
assign : identifier EQUAL expr {
  $$ = $3;
  $$->node_label_ = $1->node_label_;
  delete $1;
}
       ;

expr : identifier {
  if (driver.IsStoredValue($1->node_label_)) {
    $$ = driver.CloneTree(driver.GetStoredValue($1->node_label_));
    delete $1;
  } else {
    $$ = $1;
  }
}
     | numeric | unary_expr | binary_expr | call_expr | if_expr { $$ = $1; }
     | LPAREN expr RPAREN { $$ = $2; }
     ;

numeric : INTEGER { $$ = new TNode($1, $1, OperatorType::INT); }
        | DOUBLE { $$ = new TNode($1, $1, OperatorType::DOUBLE); }
        | PI { $$ = new TNode("3.141592653589793", "3.141592653589793", OperatorType::DOUBLE); }
        ;

unary_expr : NOT expr { $$ = new TNode(driver.GetNodeTempName(), "Not", OperatorType::FUNDAMENTAL, $2); }
           | identifier PLUS1 { $$ = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, new TNode("1", "1", OperatorType::INT)}); }
           | identifier MINUS1 { $$ = new TNode(driver.GetNodeTempName(), "Subtract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, new TNode("1", "1", OperatorType::INT)}); }
           | PLUS1 identifier { $$ = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$2, new TNode("1", "1", OperatorType::INT)}); }
           | MINUS1 identifier { $$ = new TNode(driver.GetNodeTempName(), "Subtract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$2, new TNode("1", "1", OperatorType::INT)}); }
           ;

binary_expr : expr CEQ expr { $$ = new TNode(driver.GetNodeTempName(), "Equal", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr CNE expr { $$ = new TNode(driver.GetNodeTempName(), "NotEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr CLT expr { $$ = new TNode(driver.GetNodeTempName(), "Less", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr CLE expr { $$ = new TNode(driver.GetNodeTempName(), "LessOrEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr CGT expr { $$ = new TNode(driver.GetNodeTempName(), "Greater", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr CGE expr { $$ = new TNode(driver.GetNodeTempName(), "GreaterOrEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr PLUS expr { $$ = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr MINUS expr { $$ = new TNode(driver.GetNodeTempName(), "Substract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr MUL expr { $$ = new TNode(driver.GetNodeTempName(), "Multiply", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr DIV expr { $$ = new TNode(driver.GetNodeTempName(), "Divide", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr MATMUL expr { $$ = new TNode(driver.GetNodeTempName(), "MatMul", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            | expr POWER expr{ $$ = new TNode(driver.GetNodeTempName(), "Power", OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            ;

call_expr : identifier LPAREN call_args RPAREN {
  $$ = new TNode(driver.GetNodeTempName(), $1->operator_str_, driver.GetOpFuncType($1->operator_str_), *$3);
  delete $1;
  delete $3;
}
          ;

if_expr : IF LPAREN call_args RPAREN { $$ = new TNode(driver.GetNodeTempName(), "if", OperatorType::IF, *$3); delete $3; }
        ;

call_args : expr { $$ = new std::vector<TNode*>{$1}; }
          | call_args COMMA expr { $1->emplace_back($3); $$ = $1; }
          ;

identifier : IDENTIFIER {
  // if this is a call_expr identifier, the operator_type_ will be reset to correct value in call_expr pattern.
  if (driver.IsInput($1)) {
    $$ = new TNode(driver.GetConvertedInputName($1), $1, OperatorType::IN);
  } else if (driver.IsOutput($1)) {
    $$ = new TNode(driver.GetConvertedOutputName($1), $1, OperatorType::OUT);
  } else {
    $$ = new TNode($1, $1);
  }
}
           ;

%%

void tensorglue::parser::Parser::error(const tensorglue::parser::location& location, const std::string& message) {
  throw std::runtime_error(message);
}
