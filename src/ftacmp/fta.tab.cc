/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         FtaParserparse
#define yylex           FtaParserlex
#define yyerror         FtaParsererror
#define yydebug         FtaParserdebug
#define yynerrs         FtaParsernerrs

#define yylval          FtaParserlval
#define yychar          FtaParserchar

/* Copy the first part of user declarations.  */
#line 23 "fta.y" /* yacc.c:339  */



#include <stdio.h>

/*		Some addn'l includes, necessary but not included by the
		bison generated code.
*/

#include <stdlib.h>

/*		prototypes for the parser callbacks.
*/

#include "parse_fta.h"
#include "parse_schema.h"


extern fta_parse_t *fta_parse_result;
extern var_defs_t *fta_parse_defines;


#define YYDEBUG 1


#line 100 "fta.tab.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "fta.tab.cc.h".  */
#ifndef YY_FTAPARSER_FTA_TAB_CC_H_INCLUDED
# define YY_FTAPARSER_FTA_TAB_CC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int FtaParserdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    STRING_TOKEN = 259,
    INTNUM = 260,
    LONGINTNUM = 261,
    APPROXNUM = 262,
    OR = 263,
    AND = 264,
    NOT = 265,
    COMPARISON = 266,
    SHIFT_OP = 267,
    UMINUS = 268,
    SEMICOLON = 269,
    LEFTBRACE = 270,
    RIGHTBRACE = 271,
    BY = 272,
    AS = 273,
    AGGR = 274,
    FROM = 275,
    INNER_JOIN = 276,
    FILTER_JOIN = 277,
    OUTER_JOIN = 278,
    LEFT_OUTER_JOIN = 279,
    RIGHT_OUTER_JOIN = 280,
    WATCHLIST_JOIN = 281,
    GROUP = 282,
    HAVING = 283,
    IN = 284,
    SELECT = 285,
    WATCHLIST = 286,
    WHERE = 287,
    SUPERGROUP = 288,
    CLEANING_WHEN = 289,
    CLEANING_BY = 290,
    CLOSING_WHEN = 291,
    SUCH = 292,
    THAT = 293,
    CUBE = 294,
    ROLLUP = 295,
    GROUPING_SETS = 296,
    TRUE_V = 297,
    FALSE_V = 298,
    TIMEVAL_L = 299,
    HEX_L = 300,
    LHEX_L = 301,
    IP_L = 302,
    IPV6_L = 303,
    MERGE = 304,
    SLACK = 305,
    DEFINE_SEC = 306,
    PARAM_SEC = 307,
    PROTOCOL = 308,
    TABLE = 309,
    STREAM = 310,
    FTA = 311,
    UNPACK_FCNS = 312,
    OPERATOR = 313,
    OPERATOR_VIEW = 314,
    FIELDS = 315,
    SUBQUERIES = 316,
    SELECTION_PUSHDOWN = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "fta.y" /* yacc.c:355  */

	int intval;
	double floatval;
	char *strval;
	int subtok;

	string_t *stringval;

/*			for FTA definition.	*/
	literal_t *litval;
	scalarexp_t *scalarval;
	se_list_t *se_listval;
	select_list_t *select_listval;
	table_exp_t *tblp;
	predicate_t *predp;
	literal_list_t *lit_l;
	tablevar_t *table;
	tablevar_list_t *tbl_list;
	colref_t *colref;
	ifpref_t *ifpref;
	colref_list_t *clist;
	var_defs_t *var_defs;
	var_pair_t *var_pair;
	gb_t *gb_val;
	gb_list_t *gb_list;
	list_of_gb_list_t *list_of_gb_list;
	extended_gb_t *extended_gb;
	extended_gb_list_t *extended_gb_list;

	query_list_t *q_list;

/*		For table definition	*/
	field_entry *field_t;
	field_entry_list *field_list_t;
	table_def *table_def_t;
	table_list *table_list_schema;
	param_list *plist_t;
	name_vec  *namevec_t;
	subquery_spec *subq_spec_t;
	subqueryspec_list *subqueryspec_list_t;
	unpack_fcn	*ufcn;
	unpack_fcn_list *ufcnl;


#line 248 "fta.tab.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE FtaParserlval;

int FtaParserparse (void);

#endif /* !YY_FTAPARSER_FTA_TAB_CC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 265 "fta.tab.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   738

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  390

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,     2,    79,    78,    19,    13,     2,
      70,    72,    17,    15,    71,    16,    73,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,     2,
       2,     2,     2,     2,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    75,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    12,     2,    77,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    14,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   206,   206,   211,   218,   232,   237,   242,   247,   251,
     254,   259,   264,   268,   272,   275,   280,   285,   289,   293,
     298,   299,   303,   304,   308,   309,   313,   314,   318,   319,
     323,   327,   329,   334,   342,   346,   358,   359,   360,   361,
     362,   363,   364,   368,   369,   373,   374,   378,   379,   380,
     381,   382,   386,   387,   392,   393,   397,   401,   402,   406,
     407,   411,   412,   416,   417,   421,   428,   429,   430,   431,
     432,   436,   437,   438,   439,   443,   447,   451,   452,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   487,   488,   489,   490,   494,   495,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   516,   517,   521,   522,   526,   527,   531,   532,
     533,   534,   538,   539,   543,   544,   548,   549,   550,   551,
     562,   563,   567,   568,   569,   573,   574,   578,   582,   583,
     598,   599,   602,   604,   606,   608,   612,   613,   617,   621,
     622,   626,   629,   630,   634,   635,   639,   640,   644,   645,
     646,   647,   648,   649,   650,   651,   655,   656,   660,   661,
     665,   666,   670,   671
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING_TOKEN", "INTNUM",
  "LONGINTNUM", "APPROXNUM", "OR", "AND", "NOT", "COMPARISON", "'|'",
  "'&'", "SHIFT_OP", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS",
  "SEMICOLON", "LEFTBRACE", "RIGHTBRACE", "BY", "AS", "AGGR", "FROM",
  "INNER_JOIN", "FILTER_JOIN", "OUTER_JOIN", "LEFT_OUTER_JOIN",
  "RIGHT_OUTER_JOIN", "WATCHLIST_JOIN", "GROUP", "HAVING", "IN", "SELECT",
  "WATCHLIST", "WHERE", "SUPERGROUP", "CLEANING_WHEN", "CLEANING_BY",
  "CLOSING_WHEN", "SUCH", "THAT", "CUBE", "ROLLUP", "GROUPING_SETS",
  "TRUE_V", "FALSE_V", "TIMEVAL_L", "HEX_L", "LHEX_L", "IP_L", "IPV6_L",
  "MERGE", "SLACK", "DEFINE_SEC", "PARAM_SEC", "PROTOCOL", "TABLE",
  "STREAM", "FTA", "UNPACK_FCNS", "OPERATOR", "OPERATOR_VIEW", "FIELDS",
  "SUBQUERIES", "SELECTION_PUSHDOWN", "'('", "','", "')'", "'.'", "'['",
  "']'", "'!'", "'~'", "'$'", "'#'", "'@'", "':'", "$accept",
  "parse_result", "gsql", "query_list", "params_def", "variable_def",
  "variable_list", "variable_assign", "select_statement",
  "merge_statement", "watchlist_statement", "selection", "table_exp",
  "from_clause", "table_ref_commalist", "table_ref", "table", "qname",
  "opt_where_clause", "where_clause", "opt_cleaning_when_clause",
  "opt_cleaning_by_clause", "opt_closing_when_clause", "opt_having_clause",
  "having_clause", "search_condition", "predicate", "comparison_predicate",
  "in_predicate", "literal_commalist", "scalar_exp", "select_commalist",
  "scalar_exp_commalist", "literal", "opt_group_by_clause",
  "opt_supergroup_clause", "list_of_gb_commalist", "extended_gb",
  "extended_gb_commalist", "gb_commalist", "gb", "ifparam", "column_ref",
  "column_ref_list", "gb_ref", "gb_ref_list", "table_list", "table_def",
  "unpack_func_list", "unpack_func", "subqueryspec_list", "subq_spec",
  "field_list", "field", "opt_param_commalist", "param_commalist",
  "opt_singleparam_commalist_bkt", "opt_singleparam_commalist",
  "singleparam_commalist", "namevec_commalist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   124,    38,   267,    43,    45,    42,    47,    37,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
      40,    44,    41,    46,    91,    93,    33,   126,    36,    35,
      64,    58
};
# endif

#define YYPACT_NINF -290

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-290)))

#define YYTABLE_NINF -145

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      87,   519,   -34,    49,    60,    70,    66,   108,   104,   112,
     137,   161,  -290,   157,    16,    98,  -290,  -290,  -290,   277,
    -290,    45,  -290,  -290,  -290,  -290,   519,   519,   -12,  -290,
    -290,   184,   198,   220,   256,   295,   519,   519,   519,   196,
     226,   308,   500,   315,   265,  -290,  -290,  -290,   320,   280,
     285,   141,    20,    28,   306,  -290,     6,   277,   374,   358,
    -290,   -10,    92,  -290,  -290,  -290,    92,  -290,  -290,  -290,
    -290,   228,    13,   311,  -290,  -290,   309,   312,  -290,  -290,
    -290,  -290,  -290,   356,  -290,  -290,  -290,  -290,  -290,    17,
     351,   313,   357,   370,   371,   372,  -290,   361,   519,   519,
     519,   519,   519,   519,   519,   519,   398,   519,   404,   405,
      49,   519,    49,  -290,   152,  -290,    44,  -290,  -290,   119,
     406,   336,   409,   419,   401,   121,   421,   116,  -290,   362,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,   719,   170,
     353,   426,   341,   359,   446,   399,  -290,   360,   366,   427,
     369,  -290,   429,   424,    17,    49,    17,    17,    17,    17,
     431,   410,  -290,   618,   481,   176,   209,   209,  -290,  -290,
    -290,  -290,   674,   440,   181,  -290,  -290,   652,  -290,   434,
     435,  -290,  -290,  -290,   252,   192,   419,   423,  -290,  -290,
     213,   404,   443,   462,   374,  -290,   306,   519,  -290,   465,
    -290,  -290,   215,  -290,  -290,   400,   644,   467,   468,   412,
      17,  -290,   369,   402,   369,   369,   369,   369,   188,   431,
     431,   260,  -290,  -290,  -290,   234,   450,   448,   486,    26,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,   501,  -290,
     -41,   404,   502,  -290,   197,  -290,  -290,  -290,   439,   719,
    -290,  -290,  -290,  -290,   441,   424,   442,   444,  -290,   507,
     487,  -290,    36,   602,   431,   431,   519,   445,   160,   513,
     485,  -290,   306,   522,   268,  -290,   200,  -290,  -290,   499,
     108,   108,   108,   472,  -290,   -16,  -290,   545,  -290,   719,
      35,   534,   488,   490,   491,   688,  -290,   484,  -290,  -290,
     504,   505,   431,   515,  -290,   336,  -290,  -290,  -290,  -290,
    -290,   404,   424,   424,   424,   550,  -290,   146,  -290,    15,
     575,   575,   514,   580,   160,   513,   513,   260,   431,   543,
     565,   202,    17,    35,  -290,   276,   225,  -290,   231,   575,
     238,  -290,  -290,  -290,  -290,   260,   431,   544,  -290,   520,
     369,  -290,   589,   575,  -290,  -290,   246,   523,  -290,   260,
     431,  -290,   572,   705,  -290,  -290,   575,   260,   597,   250,
     532,   195,  -290,  -290,   600,   597,   536,   603,   279,  -290,
     306,   306,   605,  -290,   586,  -290,   607,  -290,   306,  -290
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     2,     0,     0,     9,    14,    19,     3,
     150,   142,   110,   111,   112,   113,     0,     0,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,    34,    91,    93,    94,     0,   142,
       0,     0,     0,     0,   166,    52,   178,     0,     0,     0,
       1,     0,     0,     7,    12,    17,     0,     8,    13,    18,
     151,     0,     0,     0,    87,    88,     0,     0,   116,   117,
     118,   119,   120,     0,    89,    90,    92,   121,   140,     0,
       0,     0,     0,     0,     0,     0,    30,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    25,     0,    26,    23,     0,
       0,   176,     0,     0,     0,     0,     0,     0,   156,     0,
      21,     6,    11,    16,     5,    10,    15,    99,   108,     0,
     143,     0,     0,     0,     0,     0,    95,    52,     0,     0,
      36,    43,    45,    47,     0,     0,     0,     0,     0,     0,
       0,   122,    55,    81,    84,    86,    79,    80,    82,    83,
      85,   105,   106,     0,     0,   162,   145,     0,   146,     0,
       0,    24,    27,    22,   168,     0,     0,     0,    53,   180,
       0,     0,     0,     0,     0,   155,   166,     0,    98,     0,
     141,   103,     0,    96,    97,     0,     0,     0,     0,     0,
       0,    46,    37,     0,    38,    40,    39,    41,   142,     0,
       0,    56,    70,    71,    72,     0,     0,   124,     0,   166,
      33,   163,    32,    29,    28,   169,   170,   171,     0,   167,
       0,     0,     0,   179,     0,     4,   158,   157,     0,   109,
     144,   102,   100,   101,    52,    48,     0,     0,    44,     0,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
      63,   107,   166,     0,   172,   177,     0,   181,   153,     0,
       0,     0,     0,     0,    73,     0,    69,    66,    67,    75,
       0,   136,     0,     0,     0,     0,   132,   123,   128,   147,
       0,   125,     0,    57,    64,   176,   165,   173,   174,   175,
     152,     0,    49,    50,    51,     0,    74,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,    59,
       0,     0,     0,     0,    76,   137,     0,   134,     0,     0,
       0,   139,   133,   148,   149,    58,     0,    61,   164,     0,
      42,    78,     0,     0,   130,   129,     0,     0,   131,    60,
       0,    35,     0,   138,   135,   126,     0,    62,     0,     0,
       0,     0,   159,   127,     0,     0,     0,     0,     0,   160,
     166,   166,     0,   161,     0,   182,     0,   154,   166,   183
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -290,  -290,   -42,  -290,   596,   608,   570,   -48,    47,    50,
      65,  -290,  -290,   -49,  -150,   430,  -290,    -6,  -290,  -290,
    -290,  -290,  -290,  -290,  -290,  -208,  -290,  -290,  -290,  -290,
      -1,  -290,  -128,  -273,  -290,  -290,  -290,   317,  -290,  -289,
    -246,  -290,     7,  -290,    29,  -290,   582,    -4,  -290,   449,
    -290,   267,  -178,  -171,  -191,  -290,   339,  -290,   460,  -290
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    15,   116,   117,    16,    17,
      18,    42,    96,    97,   150,   151,   152,   153,   161,   162,
     329,   347,   361,   303,   304,   221,   222,   223,   224,   317,
     225,    44,   139,    45,   227,   270,   340,   296,   297,   336,
     337,    46,    47,    51,   300,   301,    19,    20,   127,   128,
     371,   372,   174,   175,   121,   185,   187,   124,   190,   378
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    56,   113,   231,   212,   248,   214,   215,   216,   217,
      50,   261,   262,   244,   202,    70,   140,   318,   335,   130,
     147,   148,   298,   114,   122,    74,    75,     1,     2,   272,
     242,   114,   338,    48,   275,    83,    84,    85,   273,    22,
      23,    24,    25,   115,   264,   265,     3,   114,     4,     5,
     356,   118,    49,     1,     2,   197,   287,   288,    76,   316,
     351,    63,    67,   276,    64,    68,    77,   181,   182,    54,
     138,   182,     3,   231,     4,   144,   123,   369,   298,    65,
      69,   305,    52,   192,    29,    30,    31,    32,    33,    34,
      35,   149,    53,   141,   327,   141,   120,   163,   164,   165,
     166,   167,   168,   169,   170,   231,   172,   364,   286,   131,
     177,    55,   132,   134,    40,    71,   135,   176,    72,   178,
     345,    70,   114,    73,     1,     2,    57,   133,   232,     1,
       2,   136,   285,   331,    58,     1,     2,   194,   359,   195,
      59,   138,   183,     3,   206,     4,     5,     6,     3,     7,
       8,     9,   367,    10,     3,   179,   180,     5,     1,     2,
     231,    60,   213,   291,    22,    23,    24,    25,    89,    90,
      91,    92,    93,    94,    95,    26,    27,     3,    61,     4,
       5,     6,   350,     7,   173,     9,    28,    10,    78,   384,
     385,   101,   102,   103,   104,   105,   249,   389,   111,    86,
     173,   255,    79,   173,   230,   173,   292,   293,   294,    29,
      30,    31,    32,    33,    34,    35,   375,   333,   376,   263,
     278,   334,   112,   310,    80,   349,   103,   104,   105,    87,
      36,    21,    22,    23,    24,    25,    37,    38,    39,    40,
      41,   197,   198,    26,    27,   266,    98,    99,   100,   101,
     102,   103,   104,   105,    28,   235,   236,   237,    71,   138,
      81,    72,   260,   238,   239,   289,    73,   295,   264,   265,
     267,   307,   308,   309,   312,   313,   314,    29,    30,    31,
      32,    33,    34,    35,   242,   243,   197,   251,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,   353,   354,    36,    82,
     137,  -143,   353,   355,    37,    38,    39,    40,    41,   357,
     358,    88,    21,    22,    23,    24,    25,   353,   365,   295,
     295,   353,   373,   295,    26,    27,   143,    98,    99,   100,
     101,   102,   103,   104,   105,    28,   107,     6,   295,     7,
     106,     9,   108,    10,    21,    22,    23,    24,    25,   352,
     382,   383,   295,   109,   343,   344,    26,    27,    29,    30,
      31,    32,    33,    34,    35,   295,   110,    28,    98,    99,
     100,   101,   102,   103,   104,   105,   120,   126,   154,    36,
     129,   142,   145,   155,   156,    37,    38,    39,    40,    41,
      29,    30,    31,    32,    33,    34,    35,   157,   158,   159,
     160,   171,    21,    22,    23,    24,    25,   173,   140,   184,
     186,    36,   188,   201,    26,    27,   205,    37,    38,    39,
      40,    41,   189,   191,   193,    28,   199,   196,   146,   200,
     209,   203,   211,   207,   218,    22,    23,    24,    25,   208,
     210,   219,   122,   229,   226,   241,    26,    27,    29,    30,
      31,    32,    33,    34,    35,   233,   234,    28,    98,    99,
     100,   101,   102,   103,   104,   105,   245,   246,   250,    36,
     254,   256,   252,   259,   268,    37,    38,    39,    40,    41,
      29,    30,    31,    32,    33,    34,    35,   257,   269,   271,
      21,    22,    23,    24,    25,   100,   101,   102,   103,   104,
     105,   220,    26,    27,   274,   277,   279,    37,    38,    39,
      40,    41,   283,    28,   280,   281,   299,   282,   204,   290,
     302,   311,    21,    22,    23,    24,    25,    89,    90,    91,
      92,    93,    94,    95,    26,    27,    29,    30,    31,    32,
      33,    34,    35,   306,   315,    28,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,   265,   324,   328,    36,   320,  -142,
     321,   322,   284,    37,    38,    39,    40,    41,    29,    30,
      31,    32,    33,    34,    35,   325,   326,   332,   291,    22,
      23,    24,    25,   341,   339,   346,   348,   360,   362,    36,
      26,    27,   363,   366,   368,    37,    38,    39,    40,    41,
     370,    28,   374,   377,    71,   380,   381,   319,   386,   387,
     388,    66,    73,   266,    98,    99,   100,   101,   102,   103,
     104,   105,    62,   119,    29,    30,    31,    32,    33,    34,
      35,    99,   100,   101,   102,   103,   104,   105,   267,   125,
     258,   342,   379,   247,   330,    36,   240,     0,     0,     0,
       0,    37,    38,    39,    40,    41,    98,    99,   100,   101,
     102,   103,   104,   105,    98,    99,   100,   101,   102,   103,
     104,   105,     0,     0,   146,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,    95,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,   228,
      98,    99,   100,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,   323,     0,     0,   253,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,     0,     0,     0,     0,     0,
    -144,    98,    99,   100,   101,   102,   103,   104,   105
};

static const yytype_int16 yycheck[] =
{
       1,     7,    51,   174,   154,   196,   156,   157,   158,   159,
       3,   219,   220,   191,   142,    19,     3,   290,     3,    61,
       3,     4,   268,     3,    18,    26,    27,    37,    38,     3,
      71,     3,   321,    67,    75,    36,    37,    38,   229,     4,
       5,     6,     7,    23,     8,     9,    56,     3,    58,    59,
     339,    23,     3,    37,    38,    71,   264,   265,    70,    75,
     333,    14,    15,   241,    14,    15,    78,    23,   116,     3,
      71,   119,    56,   244,    58,    76,    70,   366,   324,    14,
      15,   272,    22,   125,    49,    50,    51,    52,    53,    54,
      55,    74,    22,    80,   302,    80,    70,    98,    99,   100,
     101,   102,   103,   104,   105,   276,   107,   353,    72,    62,
     111,     3,    62,    66,    79,    70,    66,   110,    73,   112,
     328,   125,     3,    78,    37,    38,    22,    62,   177,    37,
      38,    66,   260,   311,    22,    37,    38,    21,   346,    23,
       3,   142,    23,    56,   145,    58,    59,    60,    56,    62,
      63,    64,   360,    66,    56,     3,     4,    59,    37,    38,
     331,     0,   155,     3,     4,     5,     6,     7,    27,    28,
      29,    30,    31,    32,    33,    15,    16,    56,    21,    58,
      59,    60,   332,    62,     3,    64,    26,    66,     4,   380,
     381,    15,    16,    17,    18,    19,   197,   388,    57,     3,
       3,   207,     4,     3,    23,     3,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    21,    71,    23,   220,
      23,    75,    81,    23,     4,    23,    17,    18,    19,     3,
      70,     3,     4,     5,     6,     7,    76,    77,    78,    79,
      80,    71,    72,    15,    16,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    26,     3,     4,     5,    70,   260,
       4,    73,    74,    71,    72,   266,    78,   268,     8,     9,
      36,     3,     4,     5,   280,   281,   282,    49,    50,    51,
      52,    53,    54,    55,    71,    72,    71,    72,    12,    13,
      14,    15,    16,    17,    18,    19,    71,    72,    70,     4,
      72,    25,    71,    72,    76,    77,    78,    79,    80,    71,
      72,     3,     3,     4,     5,     6,     7,    71,    72,   320,
     321,    71,    72,   324,    15,    16,    17,    12,    13,    14,
      15,    16,    17,    18,    19,    26,    71,    60,   339,    62,
      25,    64,    22,    66,     3,     4,     5,     6,     7,    73,
      71,    72,   353,    73,   325,   326,    15,    16,    49,    50,
      51,    52,    53,    54,    55,   366,    81,    26,    12,    13,
      14,    15,    16,    17,    18,    19,    70,     3,    27,    70,
      22,    70,    70,    70,    27,    76,    77,    78,    79,    80,
      49,    50,    51,    52,    53,    54,    55,    27,    27,    27,
      39,     3,     3,     4,     5,     6,     7,     3,     3,     3,
      74,    70,     3,    72,    15,    16,    17,    76,    77,    78,
      79,    80,     3,    22,     3,    26,    73,    65,    72,     3,
       3,    72,     3,    73,     3,     4,     5,     6,     7,    73,
      71,    10,    18,     3,    34,    22,    15,    16,    49,    50,
      51,    52,    53,    54,    55,    21,    21,    26,    12,    13,
      14,    15,    16,    17,    18,    19,    23,     5,     3,    70,
       3,     3,    72,    71,    24,    76,    77,    78,    79,    80,
      49,    50,    51,    52,    53,    54,    55,    75,    40,     3,
       3,     4,     5,     6,     7,    14,    15,    16,    17,    18,
      19,    70,    15,    16,     3,     3,    67,    76,    77,    78,
      79,    80,     5,    26,    73,    73,     3,    73,    72,    74,
      35,    22,     3,     4,     5,     6,     7,    27,    28,    29,
      30,    31,    32,    33,    15,    16,    49,    50,    51,    52,
      53,    54,    55,    21,    72,    26,    12,    13,    14,    15,
      16,    17,    18,    19,     9,    71,    41,    70,    70,    25,
      70,    70,    75,    76,    77,    78,    79,    80,    49,    50,
      51,    52,    53,    54,    55,    71,    71,    27,     3,     4,
       5,     6,     7,     3,    70,    42,    21,    43,    68,    70,
      15,    16,     3,    70,    22,    76,    77,    78,    79,    80,
       3,    26,    70,     3,    70,    69,     3,    73,     3,    23,
       3,    15,    78,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    14,    53,    49,    50,    51,    52,    53,    54,
      55,    13,    14,    15,    16,    17,    18,    19,    36,    57,
     210,   324,   375,   194,   305,    70,   186,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    12,    13,    14,    15,
      16,    17,    18,    19,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    72,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    72,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    12,    13,    14,    15,    16,    17,    18,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    56,    58,    59,    60,    62,    63,    64,
      66,    83,    84,    85,    86,    87,    90,    91,    92,   128,
     129,     3,     4,     5,     6,     7,    15,    16,    26,    49,
      50,    51,    52,    53,    54,    55,    70,    76,    77,    78,
      79,    80,    93,   112,   113,   115,   123,   124,    67,     3,
     124,   125,    22,    22,     3,     3,    99,    22,    22,     3,
       0,    21,    87,    90,    91,    92,    86,    90,    91,    92,
     129,    70,    73,    78,   112,   112,    70,    78,     4,     4,
       4,     4,     4,   112,   112,   112,     3,     3,     3,    27,
      28,    29,    30,    31,    32,    33,    94,    95,    12,    13,
      14,    15,    16,    17,    18,    19,    25,    71,    22,    73,
      81,    57,    81,    95,     3,    23,    88,    89,    23,    88,
      70,   136,    18,    70,   139,   128,     3,   130,   131,    22,
      84,    90,    91,    92,    90,    91,    92,    72,   112,   114,
       3,    80,    70,    17,   112,    70,    72,     3,     4,    74,
      96,    97,    98,    99,    27,    70,    27,    27,    27,    27,
      39,   100,   101,   112,   112,   112,   112,   112,   112,   112,
     112,     3,   112,     3,   134,   135,   124,   112,   124,     3,
       4,    23,    89,    23,     3,   137,    74,   138,     3,     3,
     140,    22,    84,     3,    21,    23,    65,    71,    72,    73,
       3,    72,   114,    72,    72,    17,   112,    73,    73,     3,
      71,     3,    96,   124,    96,    96,    96,    96,     3,    10,
      70,   107,   108,   109,   110,   112,    34,   116,    25,     3,
      23,   135,    95,    21,    21,     3,     4,     5,    71,    72,
     140,    22,    71,    72,   134,    23,     5,   131,   136,   112,
       3,    72,    72,    72,     3,    99,     3,    75,    97,    71,
      74,   107,   107,   112,     8,     9,    11,    36,    24,    40,
     117,     3,     3,   136,     3,    75,   134,     3,    23,    67,
      73,    73,    73,     5,    75,   114,    72,   107,   107,   112,
      74,     3,    46,    47,    48,   112,   119,   120,   122,     3,
     126,   127,    35,   105,   106,   136,    21,     3,     4,     5,
      23,    22,    99,    99,    99,    72,    75,   111,   115,    73,
      70,    70,    70,    25,    71,    71,    71,   107,    41,   102,
     138,   134,    27,    71,    75,     3,   121,   122,   121,    70,
     118,     3,   119,   126,   126,   107,    42,   103,    21,    23,
      96,   115,    73,    71,    72,    72,   121,    71,    72,   107,
      43,   104,    68,     3,   122,    72,    70,   107,    22,   121,
       3,   132,   133,    72,    70,    21,    23,     3,   141,   133,
      69,     3,    71,    72,   136,   136,     3,    23,     3,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    91,    91,    92,    93,    94,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      98,    98,    99,    99,   100,   100,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   107,   107,   107,   107,
     107,   108,   108,   108,   108,   109,   110,   111,   111,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   122,   122,   122,
     123,   123,   124,   124,   124,   125,   125,   126,   127,   127,
     128,   128,   129,   129,   129,   129,   130,   130,   131,   132,
     132,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     3,     3,     2,     2,     1,
       3,     3,     2,     2,     1,     3,     3,     2,     2,     1,
       1,     3,     4,     3,     4,     3,     1,     2,     3,     3,
       3,     3,     5,     5,     1,     8,     2,     3,     3,     3,
       3,     3,     8,     1,     3,     1,     2,     1,     3,     5,
       5,     5,     1,     3,     0,     1,     2,     0,     2,     0,
       2,     0,     2,     0,     1,     2,     3,     3,     2,     3,
       1,     1,     1,     3,     4,     3,     5,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     1,     2,     1,     1,     3,     4,     4,     4,     3,
       5,     5,     5,     4,     1,     3,     3,     5,     1,     3,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     0,     3,     0,     2,     3,     5,     1,     4,
       4,     4,     1,     3,     1,     3,     1,     3,     5,     3,
       2,     4,     1,     3,     5,     3,     3,     1,     3,     3,
       1,     2,     7,     6,    16,     4,     1,     3,     3,     1,
       3,     4,     1,     2,     6,     4,     0,     3,     1,     2,
       2,     2,     3,     4,     4,     4,     0,     3,     0,     3,
       1,     3,     3,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 206 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = (yyvsp[0].q_list);
		fta_parse_result->tables = NULL;
		fta_parse_result->parse_type = QUERY_PARSE;
	}
#line 1699 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 211 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = NULL;
		fta_parse_result->fta_parse_tree = NULL;
		fta_parse_result->tables = (yyvsp[0].table_list_schema);
		fta_parse_result->parse_type = TABLE_PARSE;
	}
#line 1710 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 218 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = NULL;
		fta_parse_result->fta_parse_tree = (yyvsp[-1].tblp);
		fta_parse_result->tables = (yyvsp[-2].table_list_schema);
		fta_parse_result->parse_type = STREAM_PARSE;
	}
#line 1721 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 232 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-2].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1731 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 237 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-2].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1741 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 242 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap(NULL);			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1751 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 247 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1760 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 251 "fta.y" /* yacc.c:1646  */
    {
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1768 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 254 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-2].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1778 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 259 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-2].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1788 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 264 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1797 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 268 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1806 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 272 "fta.y" /* yacc.c:1646  */
    {
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1814 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 275 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-2].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1824 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 280 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-2].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1834 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 285 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1843 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 289 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1852 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 293 "fta.y" /* yacc.c:1646  */
    {
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1860 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 298 "fta.y" /* yacc.c:1646  */
    {(yyval.q_list) = new query_list_t((yyvsp[0].tblp));}
#line 1866 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 299 "fta.y" /* yacc.c:1646  */
    {(yyval.q_list) = (yyvsp[-2].q_list)->append((yyvsp[0].tblp));}
#line 1872 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 303 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=(yyvsp[-1].var_defs);}
#line 1878 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 304 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=NULL;}
#line 1884 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 308 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=(yyvsp[-1].var_defs);fta_parse_defines=(yyvsp[-1].var_defs);}
#line 1890 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 309 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=NULL;fta_parse_defines = NULL;}
#line 1896 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 313 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs) = new var_defs_t((yyvsp[0].var_pair));}
#line 1902 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 314 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs) = (yyvsp[-1].var_defs)->add_var_pair((yyvsp[0].var_pair));}
#line 1908 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 318 "fta.y" /* yacc.c:1646  */
    {(yyval.var_pair) = new var_pair_t((yyvsp[-2].strval),(yyvsp[-1].strval));}
#line 1914 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 319 "fta.y" /* yacc.c:1646  */
    {(yyval.var_pair) = new var_pair_t((yyvsp[-2].strval),(yyvsp[-1].strval));}
#line 1920 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 323 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = (yyvsp[0].tblp)->add_selection((yyvsp[-1].select_listval));}
#line 1926 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 328 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = new table_exp_t((yyvsp[-1].clist),(yyvsp[0].tbl_list));}
#line 1932 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 330 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = new table_exp_t((yyvsp[-3].clist),(yyvsp[-1].scalarval),(yyvsp[0].tbl_list));}
#line 1938 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 335 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = table_exp_t::make_watchlist_tbl((yyvsp[-1].field_list_t)); }
#line 1944 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 342 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval) = (yyvsp[0].select_listval);}
#line 1950 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 354 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp)=new table_exp_t((yyvsp[-7].tbl_list),(yyvsp[-6].predp),(yyvsp[-5].extended_gb_list),(yyvsp[-4].clist),(yyvsp[-3].predp),(yyvsp[-2].predp),(yyvsp[-1].predp), (yyvsp[0].predp));}
#line 1956 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 358 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(-1);}
#line 1962 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 359 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(INNER_JOIN_PROPERTY);}
#line 1968 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 360 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(OUTER_JOIN_PROPERTY);}
#line 1974 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 361 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(RIGHT_OUTER_JOIN_PROPERTY);}
#line 1980 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 362 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(LEFT_OUTER_JOIN_PROPERTY);}
#line 1986 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 363 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(WATCHLIST_JOIN_PROPERTY);}
#line 1992 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 364 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(FILTER_JOIN_PROPERTY); (yyval.tbl_list)->set_colref((yyvsp[-5].colref)); (yyval.tbl_list)->set_temporal_range((yyvsp[-3].strval));}
#line 1998 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 368 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = new tablevar_list_t((yyvsp[0].table));}
#line 2004 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 369 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list)= (yyvsp[-2].tbl_list)->append_table((yyvsp[0].table));}
#line 2010 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 373 "fta.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table);}
#line 2016 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 374 "fta.y" /* yacc.c:1646  */
    { (yyval.table)= (yyvsp[-1].table)->set_range_var((yyvsp[0].strval));}
#line 2022 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 378 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[0].stringval)->c_str());}
#line 2028 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 379 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-2].strval),(yyvsp[0].stringval)->c_str(),0);}
#line 2034 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 380 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].stringval)->c_str());}
#line 2040 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 381 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].stringval)->c_str());}
#line 2046 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 382 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-3].strval),(yyvsp[0].stringval)->c_str(),1);}
#line 2052 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 386 "fta.y" /* yacc.c:1646  */
    {(yyval.stringval) = new string_t((yyvsp[0].strval));}
#line 2058 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 387 "fta.y" /* yacc.c:1646  */
    {(yyval.stringval) = (yyval.stringval)->append("/",(yyvsp[0].strval));}
#line 2064 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 392 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2070 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 393 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp);}
#line 2076 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 397 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2082 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 401 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2088 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 402 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2094 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 406 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2100 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 407 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2106 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 411 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2112 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 412 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2118 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 416 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2124 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 417 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp);}
#line 2130 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 421 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2136 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 428 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=new predicate_t("OR",(yyvsp[-2].predp),(yyvsp[0].predp));}
#line 2142 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 429 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=new predicate_t("AND",(yyvsp[-2].predp),(yyvsp[0].predp));}
#line 2148 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 430 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t("NOT", (yyvsp[0].predp) );}
#line 2154 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 431 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[-1].predp);}
#line 2160 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 432 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2166 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 436 "fta.y" /* yacc.c:1646  */
    { (yyval.predp)=(yyvsp[0].predp);}
#line 2172 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 437 "fta.y" /* yacc.c:1646  */
    { (yyval.predp) = (yyvsp[0].predp);}
#line 2178 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 438 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = predicate_t::make_paramless_fcn_predicate((yyvsp[-2].strval)); }
#line 2184 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 439 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t((yyvsp[-3].strval), (yyvsp[-1].se_listval)->get_se_list()); }
#line 2190 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 443 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t((yyvsp[-2].scalarval),(yyvsp[-1].strval),(yyvsp[0].scalarval));}
#line 2196 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 447 "fta.y" /* yacc.c:1646  */
    { (yyval.predp) = new predicate_t((yyvsp[-4].scalarval),(yyvsp[-1].lit_l)); }
#line 2202 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 451 "fta.y" /* yacc.c:1646  */
    {(yyval.lit_l) = new literal_list_t((yyvsp[0].litval));}
#line 2208 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 452 "fta.y" /* yacc.c:1646  */
    {(yyval.lit_l) = (yyvsp[-2].lit_l)->append_literal((yyvsp[0].litval));}
#line 2214 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 458 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("+",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2220 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 459 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("-",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2226 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 460 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("|",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2232 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 461 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("*",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2238 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 462 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("/",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2244 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 463 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("&",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2250 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 464 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("%",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2256 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 465 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t((yyvsp[-1].strval),(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2262 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 466 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("+",(yyvsp[0].scalarval));}
#line 2268 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 467 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("-",(yyvsp[0].scalarval));}
#line 2274 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 468 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("!",(yyvsp[0].scalarval));}
#line 2280 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 469 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("~",(yyvsp[0].scalarval));}
#line 2286 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 470 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)= new scalarexp_t((yyvsp[0].litval));}
#line 2292 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 471 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_param_reference((yyvsp[0].strval));}
#line 2298 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 472 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_iface_param_reference((yyvsp[0].ifpref));}
#line 2304 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 473 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t((yyvsp[0].colref));}
#line 2310 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 474 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = (yyvsp[-1].scalarval);}
#line 2316 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 475 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_star_aggr((yyvsp[-3].strval)); }
#line 2322 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 476 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_se_aggr((yyvsp[-3].strval),(yyvsp[-1].scalarval)); }
#line 2328 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 477 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = new scalarexp_t((yyvsp[-3].strval), (yyvsp[-1].se_listval)->get_se_list()); }
#line 2334 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 478 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_paramless_fcn((yyvsp[-2].strval)); }
#line 2340 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 479 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_star_aggr((yyvsp[-4].strval)); (yyval.scalarval)->set_superaggr(true); }
#line 2346 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 480 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_se_aggr((yyvsp[-4].strval),(yyvsp[-1].scalarval)); (yyval.scalarval)->set_superaggr(true); }
#line 2352 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 481 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = new scalarexp_t((yyvsp[-4].strval), (yyvsp[-1].se_listval)->get_se_list()); (yyval.scalarval)->set_superaggr(true); }
#line 2358 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 482 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_paramless_fcn((yyvsp[-3].strval)); (yyval.scalarval)->set_superaggr(true); }
#line 2364 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 487 "fta.y" /* yacc.c:1646  */
    {	(yyval.select_listval)= new select_list_t((yyvsp[0].scalarval)); }
#line 2370 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 488 "fta.y" /* yacc.c:1646  */
    {	(yyval.select_listval)= new select_list_t((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2376 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 489 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval)=(yyvsp[-2].select_listval)->append((yyvsp[0].scalarval)); }
#line 2382 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 490 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval)=(yyvsp[-4].select_listval)->append((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2388 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 494 "fta.y" /* yacc.c:1646  */
    {	(yyval.se_listval)= new se_list_t((yyvsp[0].scalarval)); }
#line 2394 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 495 "fta.y" /* yacc.c:1646  */
    { (yyval.se_listval)=(yyvsp[-2].se_listval)->append((yyvsp[0].scalarval)); }
#line 2400 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 499 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_STRING);}
#line 2406 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 500 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_INT);}
#line 2412 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 501 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_LONGINT);}
#line 2418 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 502 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_FLOAT);}
#line 2424 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 503 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t("TRUE",LITERAL_BOOL);}
#line 2430 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 504 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t("FALSE",LITERAL_BOOL);}
#line 2436 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 505 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_TIMEVAL);}
#line 2442 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 506 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_HEX);}
#line 2448 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 507 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_LONGHEX);}
#line 2454 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 508 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_IP);}
#line 2460 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 509 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_IPV6);}
#line 2466 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 510 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = literal_t::make_define_literal((yyvsp[0].strval),fta_parse_defines);}
#line 2472 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 516 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb_list) = NULL;}
#line 2478 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 517 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb_list) = (yyvsp[0].extended_gb_list);}
#line 2484 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 521 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = NULL;}
#line 2490 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 522 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[0].clist);}
#line 2496 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 526 "fta.y" /* yacc.c:1646  */
    { (yyval.list_of_gb_list) = new list_of_gb_list_t((yyvsp[-1].gb_list));}
#line 2502 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 527 "fta.y" /* yacc.c:1646  */
    {(yyval.list_of_gb_list) = (yyvsp[-4].list_of_gb_list)->append((yyvsp[-1].gb_list));}
#line 2508 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 531 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::create_from_gb((yyvsp[0].gb_val));}
#line 2514 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 532 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_rollup((yyvsp[-1].gb_list));}
#line 2520 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 533 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_cube((yyvsp[-1].gb_list));}
#line 2526 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 534 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_gsets((yyvsp[-1].list_of_gb_list));}
#line 2532 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 538 "fta.y" /* yacc.c:1646  */
    { (yyval.extended_gb_list) = new extended_gb_list_t((yyvsp[0].extended_gb));}
#line 2538 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 539 "fta.y" /* yacc.c:1646  */
    { (yyval.extended_gb_list)=(yyvsp[-2].extended_gb_list)->append((yyvsp[0].extended_gb));}
#line 2544 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 543 "fta.y" /* yacc.c:1646  */
    { (yyval.gb_list) = new gb_list_t((yyvsp[0].gb_val));}
#line 2550 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 544 "fta.y" /* yacc.c:1646  */
    { (yyval.gb_list)=(yyvsp[-2].gb_list)->append((yyvsp[0].gb_val));}
#line 2556 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 548 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[0].strval)); }
#line 2562 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 549 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2568 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 550 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2574 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 551 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2580 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 562 "fta.y" /* yacc.c:1646  */
    {(yyval.ifpref) = new ifpref_t((yyvsp[0].strval));}
#line 2586 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 563 "fta.y" /* yacc.c:1646  */
    {(yyval.ifpref) = new ifpref_t((yyvsp[-3].strval), (yyvsp[0].strval));}
#line 2592 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 567 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[0].strval)); }
#line 2598 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 568 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2604 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 569 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2610 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 573 "fta.y" /* yacc.c:1646  */
    {(yyval.clist)=new colref_list_t((yyvsp[-2].colref)); (yyval.clist)->append((yyvsp[0].colref));}
#line 2616 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 574 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[-2].clist)->append((yyvsp[0].colref));}
#line 2622 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 578 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[0].strval)); }
#line 2628 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 582 "fta.y" /* yacc.c:1646  */
    {(yyval.clist)=new colref_list_t((yyvsp[-2].colref)); (yyval.clist)->append((yyvsp[0].colref));}
#line 2634 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 583 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[-2].clist)->append((yyvsp[0].colref));}
#line 2640 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 598 "fta.y" /* yacc.c:1646  */
    {(yyval.table_list_schema) = new table_list((yyvsp[0].table_def_t));}
#line 2646 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 599 "fta.y" /* yacc.c:1646  */
    {(yyval.table_list_schema) = (yyvsp[-1].table_list_schema)->append_table((yyvsp[0].table_def_t));}
#line 2652 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 602 "fta.y" /* yacc.c:1646  */
    {
					(yyval.table_def_t)=new table_def((yyvsp[-5].strval),(yyvsp[-4].plist_t),(yyvsp[-3].plist_t), (yyvsp[-1].field_list_t), PROTOCOL_SCHEMA); delete (yyvsp[-4].plist_t); delete (yyvsp[-1].field_list_t);}
#line 2659 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 604 "fta.y" /* yacc.c:1646  */
    {
					(yyval.table_def_t)=new table_def((yyvsp[-4].stringval)->c_str(),(yyvsp[-3].plist_t),NULL,(yyvsp[-1].field_list_t), STREAM_SCHEMA); delete (yyvsp[-1].field_list_t);}
#line 2666 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 606 "fta.y" /* yacc.c:1646  */
    {
				(yyval.table_def_t) = new table_def((yyvsp[-14].strval), (yyvsp[-11].plist_t), (yyvsp[-8].field_list_t), (yyvsp[-4].subqueryspec_list_t), (yyvsp[-1].plist_t)); }
#line 2673 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 608 "fta.y" /* yacc.c:1646  */
    { (yyval.table_def_t) = new table_def((yyvsp[-1].ufcnl)); }
#line 2679 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 612 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcnl) = new unpack_fcn_list((yyvsp[0].ufcn));}
#line 2685 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 613 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcnl) = (yyvsp[-2].ufcnl) -> append((yyvsp[0].ufcn));}
#line 2691 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 617 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcn) = new unpack_fcn((yyvsp[-2].strval),(yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2697 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 621 "fta.y" /* yacc.c:1646  */
    {(yyval.subqueryspec_list_t) = new subqueryspec_list((yyvsp[0].subq_spec_t));}
#line 2703 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 622 "fta.y" /* yacc.c:1646  */
    {(yyval.subqueryspec_list_t) = (yyvsp[-2].subqueryspec_list_t)->append((yyvsp[0].subq_spec_t));}
#line 2709 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 626 "fta.y" /* yacc.c:1646  */
    {(yyval.subq_spec_t)=new subquery_spec((yyvsp[-3].strval), (yyvsp[-1].namevec_t)); delete (yyvsp[-1].namevec_t);}
#line 2715 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 629 "fta.y" /* yacc.c:1646  */
    {(yyval.field_list_t) = new field_entry_list((yyvsp[0].field_t));}
#line 2721 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 630 "fta.y" /* yacc.c:1646  */
    {(yyval.field_list_t) = (yyvsp[-1].field_list_t)->append_field((yyvsp[0].field_t));}
#line 2727 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 634 "fta.y" /* yacc.c:1646  */
    {(yyval.field_t) = new field_entry((yyvsp[-5].strval),(yyvsp[-4].strval),(yyvsp[-3].strval),(yyvsp[-2].plist_t),(yyvsp[-1].plist_t));}
#line 2733 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 635 "fta.y" /* yacc.c:1646  */
    {(yyval.field_t) = new field_entry((yyvsp[-3].strval),(yyvsp[-2].strval),"",(yyvsp[-1].plist_t),NULL);}
#line 2739 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 639 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2745 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 640 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2751 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 644 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[0].strval));}
#line 2757 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 645 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2763 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 646 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2769 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 647 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2775 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 648 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-2].plist_t)->append((yyvsp[0].strval));}
#line 2781 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 649 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2787 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 650 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2793 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 651 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2799 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 655 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2805 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 656 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2811 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 660 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2817 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 661 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2823 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 665 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[0].strval));}
#line 2829 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 666 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-2].plist_t)->append((yyvsp[0].strval));}
#line 2835 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 670 "fta.y" /* yacc.c:1646  */
    {(yyval.namevec_t) = new name_vec((yyvsp[-2].strval),(yyvsp[-1].strval),(yyvsp[0].plist_t));}
#line 2841 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 671 "fta.y" /* yacc.c:1646  */
    {(yyval.namevec_t) = (yyvsp[-4].namevec_t)->append((yyvsp[-2].strval),(yyvsp[-1].strval), (yyvsp[0].plist_t));}
#line 2847 "fta.tab.cc" /* yacc.c:1646  */
    break;


#line 2851 "fta.tab.cc" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 674 "fta.y" /* yacc.c:1906  */


