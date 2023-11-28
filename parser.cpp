// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 46 "parser.y"

  #include "scanner.h"
  #include "driver.h"

  #include "tnode.h"

  using namespace tensorglue::top;

  static tensorglue::parser::Parser::symbol_type yylex(tensorglue::parser::Scanner& scanner, tensorglue::parser::Driver& driver) {
    return scanner.nextToken();
  }

  using namespace tensorglue::parser;

#line 56 "parser.cpp"


#include "parser.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 20 "parser.y"
namespace tensorglue { namespace parser {
#line 154 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (tensorglue::parser::Scanner& scanner_yyarg, tensorglue::parser::Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_numeric: // numeric
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_binary_expr: // binary_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< TNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_PI: // PI
      case symbol_kind::S_IF: // IF
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_call_args: // call_args
        value.YY_MOVE_OR_COPY< std::vector<TNode*>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_numeric: // numeric
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_binary_expr: // binary_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_identifier: // identifier
        value.move< TNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_PI: // PI
      case symbol_kind::S_IF: // IF
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_call_args: // call_args
        value.move< std::vector<TNode*>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_numeric: // numeric
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_binary_expr: // binary_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_identifier: // identifier
        value.copy< TNode* > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_PI: // PI
      case symbol_kind::S_IF: // IF
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_call_args: // call_args
        value.copy< std::vector<TNode*>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_numeric: // numeric
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_binary_expr: // binary_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_identifier: // identifier
        value.move< TNode* > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_PI: // PI
      case symbol_kind::S_IF: // IF
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_call_args: // call_args
        value.move< std::vector<TNode*>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_numeric: // numeric
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_binary_expr: // binary_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< TNode* > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_PI: // PI
      case symbol_kind::S_IF: // IF
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_call_args: // call_args
        yylhs.value.emplace< std::vector<TNode*>* > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: stmts
#line 99 "parser.y"
                {
  TNode* node = new TNode("tgb##output", "CompoundOutputs", OperatorType::COMPOUNDOUTPUTS);
  driver.SetRoot(node);
  for (auto &item : *yystack_[0].value.as < std::vector<TNode*>* > ()) {
    std::cout << item->node_label_ << std::endl;
    if (std::regex_match(item->node_label_, output_regex)) {
      driver.AddSubTree(driver.GetRoot(), item);
    }
  }
  delete yystack_[0].value.as < std::vector<TNode*>* > ();
  driver.ReleaseTempMapNodes();
}
#line 685 "parser.cpp"
    break;

  case 3: // stmts: stmt
#line 113 "parser.y"
             { yylhs.value.as < std::vector<TNode*>* > () = new std::vector<TNode*>{yystack_[0].value.as < TNode* > ()}; }
#line 691 "parser.cpp"
    break;

  case 4: // stmts: stmts stmt
#line 114 "parser.y"
                   { yystack_[1].value.as < std::vector<TNode*>* > ()->emplace_back(yystack_[0].value.as < TNode* > ()); yylhs.value.as < std::vector<TNode*>* > () = yystack_[1].value.as < std::vector<TNode*>* > (); }
#line 697 "parser.cpp"
    break;

  case 5: // stmt: assign SEP
#line 117 "parser.y"
                  { yylhs.value.as < TNode* > () = yystack_[1].value.as < TNode* > (); driver.StoreMap(yystack_[1].value.as < TNode* > ()); }
#line 703 "parser.cpp"
    break;

  case 6: // assign: identifier EQUAL expr
#line 120 "parser.y"
                               {
  yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > ();
  yylhs.value.as < TNode* > ()->node_label_ = yystack_[2].value.as < TNode* > ()->node_label_;
  delete yystack_[2].value.as < TNode* > ();
}
#line 713 "parser.cpp"
    break;

  case 7: // expr: identifier
#line 127 "parser.y"
                  {
  if (driver.IsStoredValue(yystack_[0].value.as < TNode* > ()->node_label_)) {
    yylhs.value.as < TNode* > () = driver.CloneTree(driver.GetStoredValue(yystack_[0].value.as < TNode* > ()->node_label_));
    delete yystack_[0].value.as < TNode* > ();
  } else {
    yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > ();
  }
}
#line 726 "parser.cpp"
    break;

  case 8: // expr: numeric
#line 135 "parser.y"
       { yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > (); }
#line 732 "parser.cpp"
    break;

  case 9: // expr: unary_expr
#line 135 "parser.y"
                 { yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > (); }
#line 738 "parser.cpp"
    break;

  case 10: // expr: binary_expr
#line 135 "parser.y"
                              { yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > (); }
#line 744 "parser.cpp"
    break;

  case 11: // expr: call_expr
#line 135 "parser.y"
                                            { yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > (); }
#line 750 "parser.cpp"
    break;

  case 12: // expr: if_expr
#line 135 "parser.y"
                                                                { yylhs.value.as < TNode* > () = yystack_[0].value.as < TNode* > (); }
#line 756 "parser.cpp"
    break;

  case 13: // expr: LPAREN expr RPAREN
#line 136 "parser.y"
                          { yylhs.value.as < TNode* > () = yystack_[1].value.as < TNode* > (); }
#line 762 "parser.cpp"
    break;

  case 14: // numeric: INTEGER
#line 139 "parser.y"
                  { yylhs.value.as < TNode* > () = new TNode(yystack_[0].value.as < std::string > (), yystack_[0].value.as < std::string > (), OperatorType::INT); }
#line 768 "parser.cpp"
    break;

  case 15: // numeric: DOUBLE
#line 140 "parser.y"
                 { yylhs.value.as < TNode* > () = new TNode(yystack_[0].value.as < std::string > (), yystack_[0].value.as < std::string > (), OperatorType::DOUBLE); }
#line 774 "parser.cpp"
    break;

  case 16: // numeric: PI
#line 141 "parser.y"
             { yylhs.value.as < TNode* > () = new TNode("3.141592653589793", "3.141592653589793", OperatorType::DOUBLE); }
#line 780 "parser.cpp"
    break;

  case 17: // unary_expr: NOT expr
#line 144 "parser.y"
                      { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Not", OperatorType::FUNDAMENTAL, yystack_[0].value.as < TNode* > ()); }
#line 786 "parser.cpp"
    break;

  case 18: // unary_expr: identifier PLUS1
#line 145 "parser.y"
                              { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[1].value.as < TNode* > (), new TNode("1", "1", OperatorType::INT)}); }
#line 792 "parser.cpp"
    break;

  case 19: // unary_expr: identifier MINUS1
#line 146 "parser.y"
                               { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Subtract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[1].value.as < TNode* > (), new TNode("1", "1", OperatorType::INT)}); }
#line 798 "parser.cpp"
    break;

  case 20: // unary_expr: PLUS1 identifier
#line 147 "parser.y"
                              { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[0].value.as < TNode* > (), new TNode("1", "1", OperatorType::INT)}); }
#line 804 "parser.cpp"
    break;

  case 21: // unary_expr: MINUS1 identifier
#line 148 "parser.y"
                               { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Subtract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[0].value.as < TNode* > (), new TNode("1", "1", OperatorType::INT)}); }
#line 810 "parser.cpp"
    break;

  case 22: // binary_expr: expr CEQ expr
#line 151 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Equal", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 816 "parser.cpp"
    break;

  case 23: // binary_expr: expr CNE expr
#line 152 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "NotEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 822 "parser.cpp"
    break;

  case 24: // binary_expr: expr CLT expr
#line 153 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Less", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 828 "parser.cpp"
    break;

  case 25: // binary_expr: expr CLE expr
#line 154 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "LessOrEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 834 "parser.cpp"
    break;

  case 26: // binary_expr: expr CGT expr
#line 155 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Greater", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 840 "parser.cpp"
    break;

  case 27: // binary_expr: expr CGE expr
#line 156 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "GreaterOrEqual", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 846 "parser.cpp"
    break;

  case 28: // binary_expr: expr PLUS expr
#line 157 "parser.y"
                             { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Add", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 852 "parser.cpp"
    break;

  case 29: // binary_expr: expr MINUS expr
#line 158 "parser.y"
                              { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Substract", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 858 "parser.cpp"
    break;

  case 30: // binary_expr: expr MUL expr
#line 159 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Multiply", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 864 "parser.cpp"
    break;

  case 31: // binary_expr: expr DIV expr
#line 160 "parser.y"
                            { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Divide", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 870 "parser.cpp"
    break;

  case 32: // binary_expr: expr MATMUL expr
#line 161 "parser.y"
                               { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "MatMul", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 876 "parser.cpp"
    break;

  case 33: // binary_expr: expr POWER expr
#line 162 "parser.y"
                             { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "Power", OperatorType::FUNDAMENTAL, std::vector<TNode*>{yystack_[2].value.as < TNode* > (), yystack_[0].value.as < TNode* > ()}); }
#line 882 "parser.cpp"
    break;

  case 34: // call_expr: identifier LPAREN call_args RPAREN
#line 165 "parser.y"
                                               {
  yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), yystack_[3].value.as < TNode* > ()->operator_str_, driver.GetOpFuncType(yystack_[3].value.as < TNode* > ()->operator_str_), *yystack_[1].value.as < std::vector<TNode*>* > ());
  delete yystack_[3].value.as < TNode* > ();
  delete yystack_[1].value.as < std::vector<TNode*>* > ();
}
#line 892 "parser.cpp"
    break;

  case 35: // if_expr: IF LPAREN call_args RPAREN
#line 172 "parser.y"
                                     { yylhs.value.as < TNode* > () = new TNode(driver.GetNodeTempName(), "if", OperatorType::IF, *yystack_[1].value.as < std::vector<TNode*>* > ()); delete yystack_[1].value.as < std::vector<TNode*>* > (); }
#line 898 "parser.cpp"
    break;

  case 36: // call_args: expr
#line 175 "parser.y"
                 { yylhs.value.as < std::vector<TNode*>* > () = new std::vector<TNode*>{yystack_[0].value.as < TNode* > ()}; }
#line 904 "parser.cpp"
    break;

  case 37: // call_args: call_args COMMA expr
#line 176 "parser.y"
                                 { yystack_[2].value.as < std::vector<TNode*>* > ()->emplace_back(yystack_[0].value.as < TNode* > ()); yylhs.value.as < std::vector<TNode*>* > () = yystack_[2].value.as < std::vector<TNode*>* > (); }
#line 910 "parser.cpp"
    break;

  case 38: // identifier: IDENTIFIER
#line 179 "parser.y"
                        {
  // if this is a call_expr identifier, the operator_type_ will be reset to correct value in call_expr pattern.
  if (driver.IsInput(yystack_[0].value.as < std::string > ())) {
    yylhs.value.as < TNode* > () = new TNode(driver.GetConvertedInputName(yystack_[0].value.as < std::string > ()), yystack_[0].value.as < std::string > (), OperatorType::IN);
  } else if (driver.IsOutput(yystack_[0].value.as < std::string > ())) {
    yylhs.value.as < TNode* > () = new TNode(driver.GetConvertedOutputName(yystack_[0].value.as < std::string > ()), yystack_[0].value.as < std::string > (), OperatorType::OUT);
  } else {
    yylhs.value.as < TNode* > () = new TNode(yystack_[0].value.as < std::string > (), yystack_[0].value.as < std::string > ());
  }
}
#line 925 "parser.cpp"
    break;


#line 929 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -14;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      25,   -14,    20,    25,   -14,    61,    65,   -14,   -14,   -14,
      47,    25,    25,    47,    47,   -14,   -14,   -14,    29,    46,
     -14,   -14,   -14,   -14,   -14,   -13,   -14,   -14,   -14,    26,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,   -14,   -14,    47,   -14,    46,    -5,    68,
      68,    -3,    -3,    -3,    -3,    30,    30,   -14,   -14,   -14,
     -14,    -4,    47,   -14,   -14,    46
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,    38,     0,     2,     3,     0,     0,     1,     4,     5,
       0,     0,     0,     0,     0,    14,    15,    16,     0,     6,
       8,     9,    10,    11,    12,     7,    20,    21,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    19,     0,    13,    36,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    35,    34,    37
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -14,   -14,   -14,    84,   -14,   -10,   -14,   -14,   -14,   -14,
     -14,    43,     5
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,     5,    47,    20,    21,    22,    23,
      24,    48,    25
  };

  const signed char
  Parser::yytable_[] =
  {
      19,    62,    62,    28,    29,     6,    43,    44,     6,    45,
      37,    38,    39,    40,    41,    42,    26,    27,    63,    64,
       7,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    39,    40,    41,    42,    46,
       1,    30,    65,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     9,    11,    12,    13,    14,
      10,     0,     1,    15,    16,    17,    18,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     8,    61
  };

  const signed char
  Parser::yycheck_[] =
  {
      10,     6,     6,    13,    14,     0,    19,    20,     3,    22,
      13,    14,    15,    16,    17,    18,    11,    12,    23,    23,
       0,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    15,    16,    17,    18,    23,
      25,    22,    62,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     4,    19,    20,    21,    22,
       5,    -1,    25,    26,    27,    28,    29,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     3,    45
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    25,    31,    32,    33,    34,    42,     0,    33,     4,
       5,    19,    20,    21,    22,    26,    27,    28,    29,    35,
      36,    37,    38,    39,    40,    42,    42,    42,    35,    35,
      22,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    22,    23,    35,    41,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    41,     6,    23,    23,    35
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    30,    31,    32,    32,    33,    34,    35,    35,    35,
      35,    35,    35,    35,    36,    36,    36,    37,    37,    37,
      37,    37,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    39,    40,    41,    41,    42
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     1,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "EOL", "SEP", "EQUAL", "COMMA",
  "CEQ", "CNE", "CLT", "CLE", "CGT", "CGE", "PLUS", "MINUS", "MUL", "DIV",
  "MATMUL", "POWER", "PLUS1", "MINUS1", "NOT", "LPAREN", "RPAREN", "DOT",
  "IDENTIFIER", "INTEGER", "DOUBLE", "PI", "IF", "$accept", "program",
  "stmts", "stmt", "assign", "expr", "numeric", "unary_expr",
  "binary_expr", "call_expr", "if_expr", "call_args", "identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    99,    99,   113,   114,   117,   120,   127,   135,   135,
     135,   135,   135,   136,   139,   140,   141,   144,   145,   146,
     147,   148,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   165,   172,   175,   176,   179
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 20 "parser.y"
} } // tensorglue::parser
#line 1438 "parser.cpp"

#line 191 "parser.y"


void tensorglue::parser::Parser::error(const tensorglue::parser::location& location, const std::string& message) {
  throw std::runtime_error(message);
}
