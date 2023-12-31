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

%{
  #include "parser.h"
  #include "scanner.h"
  #include "location.hh"

  static tensorglue::parser::location loc;
  #define YY_USER_ACTION  loc.columns (yyleng);

  #undef yywrap
  #define yywrap() 1

  using namespace tensorglue::parser;
  #define yyterminate() Parser::make_END(loc);
%}

%option noyywrap
%option yylineno
%option c++
%option yyclass="Scanner"
%option prefix="Parser_"
%option outfile="lexer.cpp"
%%

%{
  loc.step();  
%}

[ \t\n]                 ;
[Pp][Ii]                { return Parser::make_PI(yytext, loc); }
if                      { return Parser::make_IF(yytext, loc); }
[a-zA-Z_][a-zA-Z0-9_]*  { return Parser::make_IDENTIFIER(yytext, loc); }
-?[0-9]+\.[0-9]*        { return Parser::make_DOUBLE(yytext, loc); }
-?[0-9]+                { return Parser::make_INTEGER(yytext, loc); }
"="                     { return Parser::make_EQUAL(loc); }
"=="                    { return Parser::make_CEQ(loc); }
"!="                    { return Parser::make_CNE(loc); }
"<"                     { return Parser::make_CLT(loc); }
"<="                    { return Parser::make_CLE(loc); }
">"                     { return Parser::make_CGT(loc); }
">="                    { return Parser::make_CGE(loc); }
"("                     { return Parser::make_LPAREN(loc); }
")"                     { return Parser::make_RPAREN(loc); }
"."                     { return Parser::make_DOT(loc); }
","                     { return Parser::make_COMMA(loc); }
";"                     { return Parser::make_SEP(loc); }
"+"                     { return Parser::make_PLUS(loc); }
"-"                     { return Parser::make_MINUS(loc); }
"*"                     { return Parser::make_MUL(loc); }
"/"                     { return Parser::make_DIV(loc); }
"@"                     { return Parser::make_MATMUL(loc); }
"**"                    { return Parser::make_POWER(loc); }
"!"                     { return Parser::make_NOT(loc); }
"++"                    { return Parser::make_PLUS1(loc); }
"--"                    { return Parser::make_MINUS1(loc); }
<<EOF>>                 return yyterminate();
.                       { printf("Unkown token %s!", yytext); loc.step(); }

%%
