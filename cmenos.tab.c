
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "cmenos.y"

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static char * savedName2; /* Variáveis */
static char * savedName3; /* Funções */
static int savedNum;  /* Salva o número de um token NUM */
static int savedLineNo;  /* ditto */
static int savedLineNo2;  /* Salvas as linhas só para declaração de função */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
int yyerror(char * message);
PPilha pilhinha = NULL;



/* Line 189 of yacc.c  */
#line 94 "cmenos.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     INT = 260,
     RETURN = 261,
     VOID = 262,
     WHILE = 263,
     ID = 264,
     NUM = 265,
     SUB = 266,
     SOMA = 267,
     DIV = 268,
     MULT = 269,
     DIFERENTE = 270,
     IGUAL = 271,
     MAIORIG = 272,
     MAIOR = 273,
     MENORIG = 274,
     MENOR = 275,
     RECEBE = 276,
     PONTOVIR = 277,
     VIRGULA = 278,
     ABREPAR = 279,
     FECHAPAR = 280,
     ABRECOL = 281,
     FECHACOL = 282,
     ABRECHAVE = 283,
     FECHACHAVE = 284,
     ERROR = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 166 "cmenos.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   105

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    15,    20,
      21,    22,    31,    33,    35,    36,    44,    46,    48,    52,
      54,    57,    58,    64,    69,    72,    73,    76,    77,    79,
      81,    83,    85,    87,    90,    92,    98,   106,   112,   115,
     119,   123,   125,   127,   128,   134,   138,   140,   142,   144,
     146,   148,   150,   152,   156,   158,   160,   162,   166,   168,
     170,   172,   176,   178,   180,   182,   183,   189,   191,   192,
     196
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    33,    34,    -1,    34,    -1,
      35,    -1,    40,    -1,    -1,    39,     9,    36,    22,    -1,
      -1,    -1,    39,     9,    37,    26,    10,    38,    27,    22,
      -1,     5,    -1,     7,    -1,    -1,    39,     9,    41,    24,
      42,    25,    46,    -1,    43,    -1,     7,    -1,    43,    23,
      44,    -1,    44,    -1,    39,     9,    -1,    -1,    39,     9,
      45,    26,    27,    -1,    28,    47,    48,    29,    -1,    47,
      35,    -1,    -1,    48,    49,    -1,    -1,    50,    -1,    46,
      -1,    51,    -1,    52,    -1,    53,    -1,    54,    22,    -1,
      22,    -1,     3,    24,    54,    25,    49,    -1,     3,    24,
      54,    25,    49,     4,    49,    -1,     8,    24,    54,    25,
      49,    -1,     6,    22,    -1,     6,    54,    22,    -1,    55,
      21,    54,    -1,    57,    -1,     9,    -1,    -1,     9,    56,
      26,    54,    27,    -1,    59,    58,    59,    -1,    59,    -1,
      19,    -1,    20,    -1,    18,    -1,    17,    -1,    16,    -1,
      15,    -1,    59,    60,    61,    -1,    61,    -1,    12,    -1,
      11,    -1,    61,    62,    63,    -1,    63,    -1,    14,    -1,
      13,    -1,    24,    54,    25,    -1,    55,    -1,    64,    -1,
      10,    -1,    -1,     9,    65,    24,    66,    25,    -1,    67,
      -1,    -1,    67,    23,    54,    -1,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    34,    34,    39,    49,    54,    57,    62,    62,    73,
      74,    73,    89,    92,    97,    97,   111,   114,   119,   128,
     133,   143,   143,   157,   175,   184,   189,   198,   203,   206,
     209,   212,   215,   220,   223,   228,   233,   241,   248,   252,
     259,   264,   269,   275,   275,   286,   291,   296,   300,   304,
     308,   312,   316,   322,   327,   332,   336,   342,   347,   352,
     356,   362,   365,   368,   371,   377,   377,   388,   391,   396,
     405
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "INT", "RETURN", "VOID",
  "WHILE", "ID", "NUM", "SUB", "SOMA", "DIV", "MULT", "DIFERENTE", "IGUAL",
  "MAIORIG", "MAIOR", "MENORIG", "MENOR", "RECEBE", "PONTOVIR", "VIRGULA",
  "ABREPAR", "FECHAPAR", "ABRECOL", "FECHACOL", "ABRECHAVE", "FECHACHAVE",
  "ERROR", "$accept", "programa", "declaracao_lista", "declaracao",
  "var_declaracao", "$@1", "$@2", "$@3", "tipo_especificador",
  "fun_declaracao", "$@4", "params", "param_lista", "param", "$@5",
  "composto_decl", "local_declaracoes", "statement_lista", "statement",
  "expressao_decl", "selecao_decl", "iteracao_decl", "retorno_decl",
  "expressao", "var", "$@6", "simples_expressao", "relacional",
  "soma_expressao", "soma", "termo", "mult", "fator", "ativacao", "$@7",
  "args", "arg_lista", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    36,    35,    37,
      38,    35,    39,    39,    41,    40,    42,    42,    43,    43,
      44,    45,    44,    46,    47,    47,    48,    48,    49,    49,
      49,    49,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    55,    56,    55,    57,    57,    58,    58,    58,
      58,    58,    58,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    63,    65,    64,    66,    66,    67,
      67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     4,     0,
       0,     8,     1,     1,     0,     7,     1,     1,     3,     1,
       2,     0,     5,     4,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     5,     2,     3,
       3,     1,     1,     0,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     0,     5,     1,     0,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     4,     5,     0,     6,     1,
       3,     7,     0,     0,     0,     8,     0,     0,    10,    13,
       0,     0,    16,    19,     0,    20,     0,     0,     0,     0,
      25,    15,    18,    11,     0,    27,    22,    24,     0,     0,
       7,     0,     0,     0,    42,    64,    34,     0,    23,    29,
      26,    28,    30,    31,    32,     0,    62,    41,    46,    54,
      58,    63,     0,    38,     0,     0,     0,     0,     0,    33,
       0,    56,    55,    52,    51,    50,    49,    47,    48,     0,
       0,    60,    59,     0,     0,    39,     0,     0,    68,    61,
      40,    62,    45,    53,    57,     0,     0,     0,    70,     0,
      67,    35,    37,    44,    66,     0,     0,    69,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    13,    24,     7,     8,
      14,    21,    22,    23,    29,    49,    35,    39,    50,    51,
      52,    53,    54,    55,    56,    66,    57,    79,    58,    80,
      59,    83,    60,    61,    67,    99,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int8 yypact[] =
{
      14,   -89,   -89,     1,    14,   -89,   -89,     7,   -89,   -89,
     -89,     0,   -12,     8,     5,   -89,    37,    43,   -89,    34,
      47,    45,    39,   -89,    46,    48,    50,    14,    53,    51,
     -89,   -89,   -89,   -89,    52,    14,   -89,   -89,    62,     3,
      54,    57,    -7,    58,    28,   -89,   -89,    29,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,    61,    55,   -89,    49,    44,
     -89,   -89,    29,   -89,    63,    29,    60,    64,    59,   -89,
      29,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,    29,
      29,   -89,   -89,    29,    65,   -89,    66,    29,    29,   -89,
     -89,   -89,    31,    44,   -89,    27,    27,    67,   -89,    68,
      69,    83,   -89,   -89,   -89,    29,    27,   -89,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -89,   -89,   -89,    85,    70,   -89,   -89,   -89,   -13,   -89,
     -89,   -89,   -89,    71,   -89,    73,   -89,   -89,   -88,   -89,
     -89,   -89,   -89,   -42,   -39,   -89,   -89,   -89,    16,   -89,
      -8,   -89,    13,   -89,   -89,   -89,   -89
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int8 yytable[] =
{
      64,     9,    44,    45,    20,    68,    41,   101,   102,    42,
      15,    43,    44,    45,    20,    63,    11,    47,   108,     1,
      84,     2,    38,    86,   -14,    46,    -9,    47,    90,    17,
      41,    30,    48,    42,    16,    43,    44,    45,    44,    45,
      91,    91,    71,    72,    91,    97,    98,    18,     1,    46,
      19,    47,   -65,    47,   -43,    30,    25,    81,    82,   -17,
      71,    72,    27,   107,    73,    74,    75,    76,    77,    78,
      26,    40,    93,    28,   -21,    33,    70,    34,    30,    36,
      -9,    62,    65,    69,    89,    85,    87,   106,    88,    10,
      95,    96,   105,   104,   103,    92,    94,     0,    32,    31,
       0,     0,     0,     0,     0,    37
};

static const yytype_int8 yycheck[] =
{
      42,     0,     9,    10,    17,    47,     3,    95,    96,     6,
      22,     8,     9,    10,    27,    22,     9,    24,   106,     5,
      62,     7,    35,    65,    24,    22,    26,    24,    70,    24,
       3,    28,    29,     6,    26,     8,     9,    10,     9,    10,
      79,    80,    11,    12,    83,    87,    88,    10,     5,    22,
       7,    24,    24,    24,    26,    28,     9,    13,    14,    25,
      11,    12,    23,   105,    15,    16,    17,    18,    19,    20,
      25,     9,    80,    27,    26,    22,    21,    26,    28,    27,
      26,    24,    24,    22,    25,    22,    26,     4,    24,     4,
      25,    25,    23,    25,    27,    79,    83,    -1,    27,    26,
      -1,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     7,    32,    33,    34,    35,    39,    40,     0,
      34,     9,    36,    37,    41,    22,    26,    24,    10,     7,
      39,    42,    43,    44,    38,     9,    25,    23,    27,    45,
      28,    46,    44,    22,    26,    47,    27,    35,    39,    48,
       9,     3,     6,     8,     9,    10,    22,    24,    29,    46,
      49,    50,    51,    52,    53,    54,    55,    57,    59,    61,
      63,    64,    24,    22,    54,    24,    56,    65,    54,    22,
      21,    11,    12,    15,    16,    17,    18,    19,    20,    58,
      60,    13,    14,    62,    54,    22,    54,    26,    24,    25,
      54,    55,    59,    61,    63,    25,    25,    54,    54,    66,
      67,    49,    49,    27,    25,    23,     4,    54,    49
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 34 "cmenos.y"
    {
                        savedTree = (yyvsp[(1) - (1)]);
                      ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 39 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(1) - (2)]);
                        //t = t->child[0];
                        if (t != NULL)
                        { while (t->child[0]->sibling != NULL)
                              t = t->child[0]->sibling;
                          t->child[0]->sibling = (yyvsp[(2) - (2)]);
                          (yyval) = (yyvsp[(1) - (2)]); }
                        else (yyval) = (yyvsp[(2) - (2)]);
                      ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 49 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 54 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 57 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 62 "cmenos.y"
    {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 64 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (4)]); 
                        YYSTYPE t = newExpNode(IdK);
                        (yyval)->child[0] = t;
                        t->attr.name = savedName2;
                        t->lineno = savedLineNo;
                        t->tipoID = "var";
                        t->declaracao = 1;
                      ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 73 "cmenos.y"
    {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 74 "cmenos.y"
    {savedNum = atoi(tokenString);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 74 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (8)]);
                        YYSTYPE t = newExpNode(IdK);
                        t->attr.name = savedName2;
                        t->lineno = savedLineNo;
                        t->tipoID = "var";
                        t->declaracao = 1;
                        (yyval)->child[0] = t;
                        YYSTYPE t2 = newExpNode(ConstK);
                        t2->attr.val = savedNum;
                        t->child[0] = t2;
                        t->vetor = 1;
                    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 89 "cmenos.y"
    {
                        (yyval) = newEspNode(IntK);
                      ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 92 "cmenos.y"
    {
                      (yyval) = newEspNode(VoidK);
                    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 97 "cmenos.y"
    {savedName3 = copyString(ID_tokenString);
                          savedLineNo2 = lineno;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 98 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (7)]); 
                        YYSTYPE t = newExpNode(FuncK);
                        (yyval)->child[0] = t;
                        t->child[0] = (yyvsp[(5) - (7)]);
                        t->child[1] = (yyvsp[(7) - (7)]);
                        t->attr.name = savedName3;
                        t->lineno = savedLineNo2;
                        t->tipoID = "fun";
                        t->declaracao = 1;
                      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 111 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                      ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 114 "cmenos.y"
    {
                      (yyval) = NULL;
                    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 119 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(1) - (3)]);
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = (yyvsp[(3) - (3)]);
                          (yyval) = (yyvsp[(1) - (3)]); }
                          else (yyval) = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 128 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 133 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (2)]);
                        YYSTYPE t = newExpNode(IdK);
                        t->attr.name = copyString(ID_tokenString);
                        t->lineno = lineno;
                        t->tipoID = "var";
                        t->declaracao = 1;
                        t->isArg = 1;
                        (yyval)->child[0] = t;
                      ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 143 "cmenos.y"
    {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 144 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (5)]);
                      YYSTYPE t = newExpNode(IdK);
                      t->attr.name = savedName2;
                      t->lineno = savedLineNo;
                      t->tipoID = "var";
                      t->declaracao = 1;
                      t->isArg = 1;
                      (yyval)->child[0] = t;
                      t->vetor = 1;
                    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 157 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(2) - (4)]);
                        if (t != NULL) {
                          (yyval) = (yyvsp[(2) - (4)]);
                          if((yyval)->sibling == NULL) (yyval)->sibling = (yyvsp[(3) - (4)]);
                          else{ 
                            YYSTYPE aux = t;
                            while (aux->sibling != NULL)
                              aux = aux->sibling;
                            aux->sibling = (yyvsp[(3) - (4)]);
                          }
                        }
                        else{
                          (yyval)=(yyvsp[(3) - (4)]);
                        }
                      ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 175 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(1) - (2)]);
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = (yyvsp[(2) - (2)]);
                          (yyval) = (yyvsp[(1) - (2)]); }
                          else (yyval) = (yyvsp[(2) - (2)]);
                      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 184 "cmenos.y"
    {
                      (yyval) = NULL;
                    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 189 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(1) - (2)]);
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = (yyvsp[(2) - (2)]);
                          (yyval) = (yyvsp[(1) - (2)]); }
                          else (yyval) = (yyvsp[(2) - (2)]);
                      ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 198 "cmenos.y"
    {
                      (yyval) = NULL;
                    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 203 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 206 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 209 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 212 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 215 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 220 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (2)]);
                      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 223 "cmenos.y"
    {
                      (yyval) = NULL;
                    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 228 "cmenos.y"
    {
                        (yyval) = newStmtNode(IfK);
                        (yyval)->child[0] = (yyvsp[(3) - (5)]);
                        (yyval)->child[1] = (yyvsp[(5) - (5)]);
                      ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 233 "cmenos.y"
    {
                      (yyval) = newStmtNode(IfK);
                      (yyval)->child[0] = (yyvsp[(3) - (7)]);
                      (yyval)->child[1] = (yyvsp[(5) - (7)]);
                      (yyval)->child[2] = (yyvsp[(7) - (7)]);
                    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 241 "cmenos.y"
    {
                        (yyval) = newStmtNode(WhileK);
                        (yyval)->child[0] = (yyvsp[(3) - (5)]);
                        (yyval)->child[1] = (yyvsp[(5) - (5)]);
                      ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 248 "cmenos.y"
    {
                        (yyval) = newStmtNode(RetornoK);
                        (yyval)->attr.op = RETURN;
                      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 252 "cmenos.y"
    {
                        (yyval) = newStmtNode(RetornoK);
                        (yyval)->attr.op = RETURN;
                        (yyval)->child[0] = (yyvsp[(2) - (3)]);
                    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 259 "cmenos.y"
    {
                        (yyval) = newStmtNode(RecebeK);
                        (yyval)->child[0] = (yyvsp[(1) - (3)]);
                        (yyval)->child[1] = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 264 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 269 "cmenos.y"
    {
                            (yyval) = newExpNode(IdK);
                            (yyval)->attr.name = copyString(ID_tokenString);
                            (yyval)->lineno = lineno;
                            (yyval)->tipoID = "var";
                          ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 275 "cmenos.y"
    {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 277 "cmenos.y"
    {
                        (yyval) = newExpNode(IdK);
                        (yyval)->child[0] = (yyvsp[(4) - (5)]);
                        (yyval)->attr.name = savedName2;
                        (yyval)->lineno = savedLineNo;
                        (yyval)->tipoID = "var";
                      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 286 "cmenos.y"
    {
                        (yyval) = (yyvsp[(2) - (3)]);
                        (yyval)->child[0] = (yyvsp[(1) - (3)]);
                        (yyval)->child[1] = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 291 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 296 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = MENORIG;
                      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 300 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = MENOR;
                      ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 304 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = MAIOR;
                      ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 308 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = MAIORIG;
                      ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 312 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = IGUAL;
                      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 316 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = DIFERENTE;
                      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 322 "cmenos.y"
    {
                        (yyval) = (yyvsp[(2) - (3)]);
                        (yyval)->child[0] = (yyvsp[(1) - (3)]);
                        (yyval)->child[1] = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 327 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 332 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = SOMA;
                      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 336 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = SUB;
                      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 342 "cmenos.y"
    {
                        (yyval) = (yyvsp[(2) - (3)]);
                        (yyval)->child[0] = (yyvsp[(1) - (3)]);
                        (yyval)->child[1] = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 347 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 352 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = MULT;
                      ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 356 "cmenos.y"
    {
                        (yyval) = newExpNode(OpK);
                        (yyval)->attr.op = DIV;
                      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 362 "cmenos.y"
    {
                        (yyval) = (yyvsp[(2) - (3)]);
                      ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 365 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 368 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 371 "cmenos.y"
    {
                      (yyval) = newExpNode(ConstK);
                      (yyval)->attr.val = atoi(tokenString);
                    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 377 "cmenos.y"
    {if(pilhinha == NULL) pilhinha = criaPilha(); addPilha(pilhinha,copyString(ID_tokenString));
                          savedLineNo = lineno;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 378 "cmenos.y"
    {
                        (yyval) = newExpNode(IdK);
                        (yyval)->attr.name = popPilha(pilhinha);
                        (yyval)->lineno = savedLineNo;
                        (yyval)->tipoID = "fun";
                        (yyval)->child[0] = (yyvsp[(4) - (5)]);
                        if(strcmp((yyval)->attr.name,"input") == 0 || strcmp((yyval)->attr.name,"output") == 0) (yyval)->declaracao = 1;
                      ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 388 "cmenos.y"
    {
                        (yyval) = (yyvsp[(1) - (1)]);
                      ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 391 "cmenos.y"
    {
                      (yyval) = NULL;
                    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 396 "cmenos.y"
    {
                        YYSTYPE t = (yyvsp[(1) - (3)]);
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = (yyvsp[(3) - (3)]);
                          (yyval) = (yyvsp[(1) - (3)]); }
                          else (yyval) = (yyvsp[(3) - (3)]);
                      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 405 "cmenos.y"
    {
                      (yyval) = (yyvsp[(1) - (1)]);
                    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2199 "cmenos.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 410 "cmenos.y"


int yyerror(char * message)
{ if(Error) return 0;
  fprintf(listing,"ERRO SINTATICO: ");
  printToken(yychar,"\0");
  fprintf(listing," LINHA: %d\n",lineno);
  Error = TRUE;
  return 0;
}

static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}
