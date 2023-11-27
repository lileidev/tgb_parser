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

%token <std::string> IDENTIFIER INTEGER DOUBLE PI IF

%token CEQ CNE CLT CLE CGT CGE EQUAL
%token LPAREN RPAREN COMMA DOT SEP
%token PLUS MINUS MUL DIV MATMUL POWER
%token NOT PLUS1 MINUS1

%token EOL
%token END 0

%type <std::vector<TNode*>> stmts call_args
%type <TNode*> stmt assign expr numeric identifier unary_expr binary_expr call_expr if_expr
%type <std::string> compare_op math_op binary_op ceq cne clt cle cgt cge plus minus mul div matmul power

/* operator precedence for methematical operations */
%nonassoc SEP
%right EQUAL
%left CEQ CNE
%left CLT CLE CGT CGE
%left PLUS MINUS
%left MUL DIV MATMUL
%right PLUS1 MINUS1 
%right NOT

%start program

%%

program : stmts {
  TNode* node = new TNode("tgb##output", "CompoundOutputs", OperatorType::COMPOUNDOUTPUTS);
  driver.SetRoot(node);
  for (auto &item : $1) {
    if (std::regex_match(item->node_label_, output_regex)) {
      driver.AddSubTree(driver.GetRoot(), item);
    }
  }
  driver.ReleaseTempMapNodes();
}
        ;
      
stmts : stmt { $$ = std::vector<TNode*>{$1}; }
      | stmts stmt { $$.emplace_back($2); }
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

binary_expr : expr binary_op expr { $$ = new TNode(driver.GetNodeTempName(), $2, OperatorType::FUNDAMENTAL, std::vector<TNode*>{$1, $3}); }
            ;

binary_op : compare_op | math_op { $$ = $1; }
          ;

compare_op : ceq | cne | clt | cle | cgt | cge { $$ = $1; }
           ;

ceq : CEQ { $$ = "Equal"; }
    ;
  
cne : CNE { $$ = "NotEqual"; }
    ;

clt : CLT { $$ = "Less"; }
    ;

cle : CLE { $$ = "LessOrEqual"; }
    ;

cgt : CGT { $$ = "Greater"; }
    ;

cge : CGE { $$ = "GreaterOrEqual"; }
    ;

math_op : plus | minus | mul | div | matmul | power { $$ = $1; }
        ;

plus : PLUS { $$ = "Add"; }
     ;

minus : MINUS { $$ = "Subtract"; }
      ;

mul : MUL { $$ = "Multiply"; }
    ;

div : DIV { $$ = "Divide"; }
    ;

matmul : MATMUL { $$ = "MatMul"; }
       ;

power : POWER { $$ = "Power"; }
      ;

call_expr : identifier LPAREN call_args RPAREN {
  $$ = new TNode(driver.GetNodeTempName(), $1->operator_str_, driver.GetOpFuncType($1->operator_str_), $3);
  delete $1;
}
          ;

if_expr : IF LPAREN call_args RPAREN { $$ = new TNode(driver.GetNodeTempName(), "if", OperatorType::IF, $3); }
        ;

call_args : expr { $$ = std::vector<TNode*>{$1}; }
          | call_args COMMA expr { $$.emplace_back($3); }
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
