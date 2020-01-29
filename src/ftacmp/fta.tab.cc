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
    GROUP = 281,
    HAVING = 282,
    IN = 283,
    SELECT = 284,
    WHERE = 285,
    SUPERGROUP = 286,
    CLEANING_WHEN = 287,
    CLEANING_BY = 288,
    CLOSING_WHEN = 289,
    SUCH = 290,
    THAT = 291,
    CUBE = 292,
    ROLLUP = 293,
    GROUPING_SETS = 294,
    TRUE_V = 295,
    FALSE_V = 296,
    TIMEVAL_L = 297,
    HEX_L = 298,
    LHEX_L = 299,
    IP_L = 300,
    IPV6_L = 301,
    MERGE = 302,
    SLACK = 303,
    DEFINE_SEC = 304,
    PARAM_SEC = 305,
    PROTOCOL = 306,
    TABLE = 307,
    STREAM = 308,
    FTA = 309,
    UNPACK_FCNS = 310,
    OPERATOR = 311,
    OPERATOR_VIEW = 312,
    FIELDS = 313,
    SUBQUERIES = 314,
    SELECTION_PUSHDOWN = 315
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


#line 246 "fta.tab.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE FtaParserlval;

int FtaParserparse (void);

#endif /* !YY_FTAPARSER_FTA_TAB_CC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 263 "fta.tab.cc" /* yacc.c:358  */

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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   695

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  377

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,    77,    76,    19,    13,     2,
      68,    70,    17,    15,    69,    16,    71,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,     2,
       2,     2,     2,     2,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    12,     2,    75,     2,     2,     2,
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
      62,    63,    64,    65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   204,   204,   209,   216,   230,   235,   240,   245,   249,
     252,   257,   262,   266,   270,   275,   276,   280,   281,   285,
     286,   290,   291,   295,   296,   300,   304,   306,   314,   318,
     330,   331,   332,   333,   334,   335,   339,   340,   344,   345,
     349,   350,   351,   352,   353,   357,   358,   363,   364,   368,
     372,   373,   377,   378,   382,   383,   387,   388,   392,   399,
     400,   401,   402,   403,   407,   408,   409,   410,   414,   418,
     422,   423,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   458,   459,   460,
     461,   465,   466,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   487,   488,   492,   493,   497,
     498,   502,   503,   504,   505,   509,   510,   514,   515,   519,
     520,   521,   522,   533,   534,   538,   539,   540,   544,   545,
     549,   553,   554,   569,   570,   573,   575,   577,   579,   583,
     584,   588,   592,   593,   597,   600,   601,   605,   606,   610,
     611,   615,   616,   617,   618,   619,   620,   621,   622,   626,
     627,   631,   632,   636,   637,   641,   642
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
  "RIGHT_OUTER_JOIN", "GROUP", "HAVING", "IN", "SELECT", "WHERE",
  "SUPERGROUP", "CLEANING_WHEN", "CLEANING_BY", "CLOSING_WHEN", "SUCH",
  "THAT", "CUBE", "ROLLUP", "GROUPING_SETS", "TRUE_V", "FALSE_V",
  "TIMEVAL_L", "HEX_L", "LHEX_L", "IP_L", "IPV6_L", "MERGE", "SLACK",
  "DEFINE_SEC", "PARAM_SEC", "PROTOCOL", "TABLE", "STREAM", "FTA",
  "UNPACK_FCNS", "OPERATOR", "OPERATOR_VIEW", "FIELDS", "SUBQUERIES",
  "SELECTION_PUSHDOWN", "'('", "','", "')'", "'.'", "'['", "']'", "'!'",
  "'~'", "'$'", "'#'", "'@'", "':'", "$accept", "parse_result", "gsql",
  "query_list", "params_def", "variable_def", "variable_list",
  "variable_assign", "select_statement", "merge_statement", "selection",
  "table_exp", "from_clause", "table_ref_commalist", "table_ref", "table",
  "qname", "opt_where_clause", "where_clause", "opt_cleaning_when_clause",
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
     308,   309,   310,   311,   312,   313,   314,   315,    40,    44,
      41,    46,    91,    93,    33,   126,    36,    35,    64,    58
};
# endif

#define YYPACT_NINF -277

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-277)))

#define YYTABLE_NINF -138

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     413,   489,    37,    51,   105,   114,   120,   124,   128,   126,
     142,  -277,   136,    72,    24,  -277,  -277,   169,  -277,   104,
    -277,  -277,  -277,  -277,   489,   489,     0,  -277,  -277,   175,
     189,   213,   217,   224,   489,   489,   489,   170,   229,   240,
     338,   426,   182,  -277,  -277,  -277,   235,   230,   369,    35,
      36,   253,  -277,     1,   169,   319,   289,  -277,    -9,    95,
    -277,  -277,    95,  -277,  -277,  -277,   148,     8,   255,  -277,
    -277,   242,   267,  -277,  -277,  -277,  -277,  -277,   257,  -277,
    -277,  -277,  -277,  -277,    17,   309,   269,   312,   313,   321,
    -277,   316,   489,   489,   489,   489,   489,   489,   489,   489,
     347,   489,   351,    37,   489,    37,  -277,   130,  -277,    41,
    -277,  -277,    81,   372,   305,   375,   378,   360,    83,   382,
      62,  -277,   323,  -277,  -277,  -277,  -277,  -277,  -277,   676,
     101,   331,   400,   281,   342,   595,   357,  -277,   348,   349,
     410,   353,  -277,   420,   412,    17,    37,    17,    17,    17,
     411,   395,  -277,   264,   554,   248,   143,   143,  -277,  -277,
    -277,  -277,   533,  -277,   615,  -277,   408,   415,  -277,  -277,
    -277,   187,   112,   378,   425,  -277,  -277,   150,   447,   429,
     463,   319,  -277,   253,   489,  -277,   469,  -277,  -277,   165,
    -277,  -277,   414,   603,   475,   477,   409,    17,  -277,   353,
     421,   353,   353,   353,   308,   411,   411,   176,  -277,  -277,
    -277,   495,   457,   445,   488,  -277,  -277,  -277,  -277,  -277,
    -277,   513,  -277,   -37,   447,   514,  -277,   516,   107,  -277,
    -277,  -277,  -277,   455,   676,  -277,  -277,  -277,  -277,   451,
     412,   458,   482,  -277,   550,   450,  -277,    20,   376,   411,
     411,   489,   449,   162,   553,   525,  -277,   199,  -277,   113,
    -277,    11,  -277,  -277,   538,   120,   120,   120,   491,  -277,
     -32,  -277,   565,  -277,   676,   294,    38,   494,   522,   523,
     636,  -277,   524,  -277,  -277,   529,   530,   411,   555,  -277,
    -277,  -277,  -277,  -277,   253,   571,   447,   412,   412,   412,
     573,  -277,   -27,  -277,    10,   528,   528,   556,   594,   162,
     553,   553,   176,   411,   561,   305,  -277,   115,    17,   294,
    -277,   570,   172,  -277,   184,   528,   186,  -277,  -277,  -277,
    -277,   176,   411,   582,   604,   560,   353,  -277,   632,   528,
    -277,  -277,   233,   568,  -277,   176,   411,  -277,  -277,   616,
     662,  -277,  -277,   528,   176,   634,   243,   572,    99,  -277,
    -277,   653,   634,   590,   655,   245,  -277,   253,   253,   656,
    -277,   637,  -277,   659,  -277,   253,  -277
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,     2,     0,     0,     9,    14,     3,   143,   135,
     103,   104,   105,   106,     0,     0,     0,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,    28,    84,    86,    87,   135,     0,     0,     0,
       0,   159,    45,   171,     0,     0,     0,     1,     0,     0,
       7,    12,     0,     8,    13,   144,     0,     0,     0,    80,
      81,     0,     0,   109,   110,   111,   112,   113,     0,    82,
      83,    85,   114,   133,     0,     0,     0,     0,     0,     0,
      25,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,    20,     0,
      21,    18,     0,     0,   169,     0,     0,     0,     0,     0,
       0,   149,     0,    16,     6,    11,     5,    10,    92,   101,
       0,   136,     0,     0,     0,     0,     0,    88,    45,     0,
       0,    30,    36,    38,    40,     0,     0,     0,     0,     0,
       0,   115,    48,    74,    77,    79,    72,    73,    75,    76,
      78,    98,    99,   138,     0,   139,     0,     0,    19,    22,
      17,   161,     0,     0,     0,    46,   173,     0,     0,     0,
       0,     0,   148,   159,     0,    91,     0,   134,    96,     0,
      89,    90,     0,     0,     0,     0,     0,     0,    39,    31,
       0,    32,    34,    33,   135,     0,     0,    49,    63,    64,
      65,     0,     0,   117,     0,    27,    24,    23,   162,   163,
     164,     0,   160,     0,     0,     0,   172,     0,     0,   155,
       4,   151,   150,     0,   102,   137,    95,    93,    94,    45,
      41,     0,     0,    37,     0,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,    56,   100,   165,   170,     0,
     174,   159,   146,   156,     0,     0,     0,     0,     0,    66,
       0,    62,    59,    60,    68,     0,   129,     0,     0,     0,
       0,   125,   116,   121,   140,     0,   118,     0,    50,    57,
     166,   167,   168,   145,   159,     0,     0,    42,    43,    44,
       0,    67,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,    58,     0,    52,   169,   158,     0,     0,     0,
      69,   130,     0,   127,     0,     0,     0,   132,   126,   141,
     142,    51,     0,    54,     0,     0,    35,    71,     0,     0,
     123,   122,     0,     0,   124,    53,     0,    29,   157,     0,
     131,   128,   119,     0,    55,     0,     0,     0,     0,   152,
     120,     0,     0,     0,     0,     0,   153,   159,   159,     0,
     154,     0,   175,     0,   147,   159,   176
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -277,  -277,   -36,  -277,   625,   650,   614,    47,    12,    53,
    -277,  -277,   -40,  -142,   470,  -277,    -5,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -188,  -277,  -277,  -277,  -277,    -1,
    -277,  -124,  -244,  -277,  -277,  -277,   359,  -277,  -276,  -237,
    -277,     2,  -277,    15,  -277,   612,    -7,  -277,   490,  -277,
     307,  -209,  -216,  -181,  -277,   355,  -277,   499,  -277
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,   109,   110,    15,    16,
      40,    90,    91,   141,   142,   143,   144,   151,   152,   314,
     333,   347,   288,   289,   207,   208,   209,   210,   302,   211,
      42,   130,    43,   213,   255,   326,   281,   282,   322,   323,
      44,    45,    48,   285,   286,    17,    18,   120,   121,   358,
     359,   228,   229,   114,   172,   174,   117,   177,   365
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    53,   233,   199,    47,   201,   202,   203,   106,   189,
      65,   131,   263,   321,   294,   259,   283,   246,   247,   115,
     138,   139,   123,    69,    70,    60,    63,     1,   249,   250,
     324,   303,   225,    78,    79,    80,   258,   184,   107,   107,
      46,   301,   319,   263,   107,     2,   320,     3,     4,   342,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   108,   111,
       1,   272,   273,  -135,   168,   129,    61,    64,    71,   116,
     135,   124,   283,    49,   126,   337,    72,   356,     2,   113,
     295,     4,   179,   181,   107,   182,   132,   317,   132,   140,
     271,   153,   154,   155,   156,   157,   158,   159,   160,   312,
     162,   263,   351,   164,   170,   163,    66,   165,     1,   304,
     227,    65,   125,   315,    68,   127,   227,    51,   227,     1,
     362,   270,   363,    52,   215,   331,     2,    50,     3,    56,
     262,     1,   129,   166,   167,   193,   293,     2,   335,     3,
       4,     5,    57,     6,   345,     8,    54,     9,   200,     2,
      55,    19,    20,    21,    22,    23,   169,    58,   354,   169,
      97,    98,    99,    24,    25,   276,    20,    21,    22,    23,
     184,   185,    66,    81,    26,    67,   336,    24,    25,    73,
      68,   221,   222,   234,   249,   250,   371,   372,    26,   240,
     218,   219,   220,    74,   376,    27,    28,    29,    30,    31,
      32,    33,   290,   291,   292,   248,   277,   278,   279,    27,
      28,    29,    30,    31,    32,    33,    34,    75,   128,   225,
     226,    76,    35,    36,    37,    38,    39,     5,    77,     6,
      34,     8,    82,     9,   184,   236,    35,    36,    37,    38,
      39,   339,   340,    83,   129,    19,    20,    21,    22,    23,
     274,   101,   280,   339,   341,   343,   344,    24,    25,   134,
     297,   298,   299,    95,    96,    97,    98,    99,    26,    92,
      93,    94,    95,    96,    97,    98,    99,    93,    94,    95,
      96,    97,    98,    99,    19,    20,    21,    22,    23,    27,
      28,    29,    30,    31,    32,    33,    24,    25,    20,    21,
      22,    23,   339,   352,   280,   280,   102,    26,   280,   103,
      34,   122,   339,   360,   369,   370,    35,    36,    37,    38,
      39,   113,   119,   133,   280,   329,   330,   137,    27,    28,
      29,    30,    31,    32,    33,   136,   145,   146,   280,   147,
     148,    27,    28,    29,    30,    31,    32,    33,   149,    34,
     161,   188,   280,   150,   131,    35,    36,    37,    38,    39,
      19,    20,    21,    22,    23,    84,    85,    86,    87,    88,
      89,    38,    24,    25,   192,   171,    66,   173,   175,    67,
     245,   176,   178,    26,    68,   180,   183,   251,    92,    93,
      94,    95,    96,    97,    98,    99,    84,    85,    86,    87,
      88,    89,   186,   187,    27,    28,    29,    30,    31,    32,
      33,   252,   190,   196,   204,    20,    21,    22,    23,   194,
     195,   205,   197,   198,   104,    34,    24,    25,   212,   216,
     115,    35,    36,    37,    38,    39,   217,    26,    92,    93,
      94,    95,    96,    97,    98,    99,   137,   224,   105,     1,
     227,   100,   230,    19,    20,    21,    22,    23,    27,    28,
      29,    30,    31,    32,    33,    24,    25,     2,   231,     3,
       4,     5,   235,     6,     7,     8,    26,     9,   239,   206,
     241,   253,   242,   254,   237,    35,    36,    37,    38,    39,
     244,   256,    19,    20,    21,    22,    23,    27,    28,    29,
      30,    31,    32,    33,    24,    25,   251,    92,    93,    94,
      95,    96,    97,    98,    99,    26,   257,   260,    34,   261,
     264,   275,   265,   269,    35,    36,    37,    38,    39,   266,
     252,   276,    20,    21,    22,    23,    27,    28,    29,    30,
      31,    32,    33,    24,    25,    92,    93,    94,    95,    96,
      97,    98,    99,   267,    26,   268,   284,    34,   214,   287,
     296,   300,   305,    35,    36,    37,    38,    39,    94,    95,
      96,    97,    98,    99,   250,    27,    28,    29,    30,    31,
      32,    33,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
     306,   307,   316,   309,   313,  -136,    34,   327,   310,   311,
     318,   332,    35,    36,    37,    38,    39,    92,    93,    94,
      95,    96,    97,    98,    99,    92,    93,    94,    95,    96,
      97,    98,    99,   346,   325,   348,   349,    92,    93,    94,
      95,    96,    97,    98,    99,   350,   353,   357,   355,    62,
     361,   338,    84,    85,    86,    87,    88,    89,    92,    93,
      94,    95,    96,    97,    98,    99,   364,   367,   368,   373,
     374,   308,   375,    59,   112,   191,   118,   243,   328,   366,
     334,   232,   223,   238,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,     0,     0,     0,     0,     0,  -137,    92,    93,
      94,    95,    96,    97,    98,    99
};

static const yytype_int16 yycheck[] =
{
       1,     6,   183,   145,     2,   147,   148,   149,    48,   133,
      17,     3,   228,     3,     3,   224,   253,   205,   206,    18,
       3,     4,    58,    24,    25,    13,    14,    36,     8,     9,
     306,   275,    69,    34,    35,    36,    73,    69,     3,     3,
       3,    73,    69,   259,     3,    54,    73,    56,    57,   325,
      12,    13,    14,    15,    16,    17,    18,    19,    23,    23,
      36,   249,   250,    25,    23,    66,    13,    14,    68,    68,
      71,    59,   309,    22,    62,   319,    76,   353,    54,    68,
     261,    57,   118,    21,     3,    23,    78,   296,    78,    72,
      70,    92,    93,    94,    95,    96,    97,    98,    99,   287,
     101,   317,   339,   104,    23,   103,    68,   105,    36,    71,
       3,   118,    59,   294,    76,    62,     3,     3,     3,    36,
      21,   245,    23,     3,   164,   313,    54,    22,    56,     3,
      23,    36,   133,     3,     4,   136,    23,    54,    23,    56,
      57,    58,     0,    60,   332,    62,    22,    64,   146,    54,
      22,     3,     4,     5,     6,     7,   109,    21,   346,   112,
      17,    18,    19,    15,    16,     3,     4,     5,     6,     7,
      69,    70,    68,     3,    26,    71,   318,    15,    16,     4,
      76,    69,    70,   184,     8,     9,   367,   368,    26,   194,
       3,     4,     5,     4,   375,    47,    48,    49,    50,    51,
      52,    53,     3,     4,     5,   206,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    68,     4,    70,    69,
      70,     4,    74,    75,    76,    77,    78,    58,     4,    60,
      68,    62,     3,    64,    69,    70,    74,    75,    76,    77,
      78,    69,    70,     3,   245,     3,     4,     5,     6,     7,
     251,    69,   253,    69,    70,    69,    70,    15,    16,    17,
     265,   266,   267,    15,    16,    17,    18,    19,    26,    12,
      13,    14,    15,    16,    17,    18,    19,    13,    14,    15,
      16,    17,    18,    19,     3,     4,     5,     6,     7,    47,
      48,    49,    50,    51,    52,    53,    15,    16,     4,     5,
       6,     7,    69,    70,   305,   306,    71,    26,   309,    79,
      68,    22,    69,    70,    69,    70,    74,    75,    76,    77,
      78,    68,     3,    68,   325,   310,   311,    70,    47,    48,
      49,    50,    51,    52,    53,    68,    27,    68,   339,    27,
      27,    47,    48,    49,    50,    51,    52,    53,    27,    68,
       3,    70,   353,    37,     3,    74,    75,    76,    77,    78,
       3,     4,     5,     6,     7,    27,    28,    29,    30,    31,
      32,    77,    15,    16,    17,     3,    68,    72,     3,    71,
      72,     3,    22,    26,    76,     3,    63,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    27,    28,    29,    30,
      31,    32,    71,     3,    47,    48,    49,    50,    51,    52,
      53,    35,    70,     3,     3,     4,     5,     6,     7,    71,
      71,    10,    69,     3,    55,    68,    15,    16,    33,    21,
      18,    74,    75,    76,    77,    78,    21,    26,    12,    13,
      14,    15,    16,    17,    18,    19,    70,    22,    79,    36,
       3,    25,    23,     3,     4,     5,     6,     7,    47,    48,
      49,    50,    51,    52,    53,    15,    16,    54,     5,    56,
      57,    58,     3,    60,    61,    62,    26,    64,     3,    68,
       3,    24,    73,    38,    70,    74,    75,    76,    77,    78,
      69,     3,     3,     4,     5,     6,     7,    47,    48,    49,
      50,    51,    52,    53,    15,    16,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    26,     3,     3,    68,     3,
      65,    72,    71,    73,    74,    75,    76,    77,    78,    71,
      35,     3,     4,     5,     6,     7,    47,    48,    49,    50,
      51,    52,    53,    15,    16,    12,    13,    14,    15,    16,
      17,    18,    19,    71,    26,     5,     3,    68,    25,    34,
      22,    70,    68,    74,    75,    76,    77,    78,    14,    15,
      16,    17,    18,    19,     9,    47,    48,    49,    50,    51,
      52,    53,    12,    13,    14,    15,    16,    17,    18,    19,
      68,    68,    21,    69,    39,    25,    68,     3,    69,    69,
      27,    40,    74,    75,    76,    77,    78,    12,    13,    14,
      15,    16,    17,    18,    19,    12,    13,    14,    15,    16,
      17,    18,    19,    41,    68,    21,    66,    12,    13,    14,
      15,    16,    17,    18,    19,     3,    68,     3,    22,    14,
      68,    71,    27,    28,    29,    30,    31,    32,    12,    13,
      14,    15,    16,    17,    18,    19,     3,    67,     3,     3,
      23,    25,     3,    13,    50,    70,    54,   197,   309,   362,
     315,   181,   173,    70,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    12,    13,
      14,    15,    16,    17,    18,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    54,    56,    57,    58,    60,    61,    62,    64,
      81,    82,    83,    84,    85,    88,    89,   125,   126,     3,
       4,     5,     6,     7,    15,    16,    26,    47,    48,    49,
      50,    51,    52,    53,    68,    74,    75,    76,    77,    78,
      90,   109,   110,   112,   120,   121,     3,   121,   122,    22,
      22,     3,     3,    96,    22,    22,     3,     0,    21,    85,
      88,    89,    84,    88,    89,   126,    68,    71,    76,   109,
     109,    68,    76,     4,     4,     4,     4,     4,   109,   109,
     109,     3,     3,     3,    27,    28,    29,    30,    31,    32,
      91,    92,    12,    13,    14,    15,    16,    17,    18,    19,
      25,    69,    71,    79,    55,    79,    92,     3,    23,    86,
      87,    23,    86,    68,   133,    18,    68,   136,   125,     3,
     127,   128,    22,    82,    88,    89,    88,    89,    70,   109,
     111,     3,    78,    68,    17,   109,    68,    70,     3,     4,
      72,    93,    94,    95,    96,    27,    68,    27,    27,    27,
      37,    97,    98,   109,   109,   109,   109,   109,   109,   109,
     109,     3,   109,   121,   109,   121,     3,     4,    23,    87,
      23,     3,   134,    72,   135,     3,     3,   137,    22,    82,
       3,    21,    23,    63,    69,    70,    71,     3,    70,   111,
      70,    70,    17,   109,    71,    71,     3,    69,     3,    93,
     121,    93,    93,    93,     3,    10,    68,   104,   105,   106,
     107,   109,    33,   113,    25,    92,    21,    21,     3,     4,
       5,    69,    70,   137,    22,    69,    70,     3,   131,   132,
      23,     5,   128,   133,   109,     3,    70,    70,    70,     3,
      96,     3,    73,    94,    69,    72,   104,   104,   109,     8,
       9,    11,    35,    24,    38,   114,     3,     3,    73,   131,
       3,     3,    23,   132,    65,    71,    71,    71,     5,    73,
     111,    70,   104,   104,   109,    72,     3,    44,    45,    46,
     109,   116,   117,   119,     3,   123,   124,    34,   102,   103,
       3,     4,     5,    23,     3,   133,    22,    96,    96,    96,
      70,    73,   108,   112,    71,    68,    68,    68,    25,    69,
      69,    69,   104,    39,    99,   133,    21,   131,    27,    69,
      73,     3,   118,   119,   118,    68,   115,     3,   116,   123,
     123,   104,    40,   100,   135,    23,    93,   112,    71,    69,
      70,    70,   118,    69,    70,   104,    41,   101,    21,    66,
       3,   119,    70,    68,   104,    22,   118,     3,   129,   130,
      70,    68,    21,    23,     3,   138,   130,    67,     3,    69,
      70,   133,   133,     3,    23,     3,   133
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    89,    89,    90,    91,
      92,    92,    92,    92,    92,    92,    93,    93,    94,    94,
      95,    95,    95,    95,    95,    96,    96,    97,    97,    98,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   106,   107,
     108,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   110,
     110,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   116,   117,   117,   118,   118,   119,
     119,   119,   119,   120,   120,   121,   121,   121,   122,   122,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   127,
     127,   128,   129,   129,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     3,     3,     2,     2,     1,
       3,     3,     2,     2,     1,     1,     3,     4,     3,     4,
       3,     1,     2,     3,     3,     3,     3,     5,     1,     8,
       2,     3,     3,     3,     3,     8,     1,     3,     1,     2,
       1,     3,     5,     5,     5,     1,     3,     0,     1,     2,
       0,     2,     0,     2,     0,     2,     0,     1,     2,     3,
       3,     2,     3,     1,     1,     1,     3,     4,     3,     5,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     1,     2,     1,     1,     3,     4,
       4,     4,     3,     5,     5,     5,     4,     1,     3,     3,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     0,     3,     0,     2,     3,
       5,     1,     4,     4,     4,     1,     3,     1,     3,     1,
       3,     5,     3,     2,     4,     1,     3,     5,     3,     3,
       1,     3,     3,     1,     2,     7,     6,    16,     4,     1,
       3,     3,     1,     3,     4,     1,     2,     6,     4,     0,
       3,     1,     2,     2,     2,     3,     4,     4,     4,     0,
       3,     0,     3,     1,     3,     3,     5
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
#line 204 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = (yyvsp[0].q_list);
		fta_parse_result->tables = NULL;
		fta_parse_result->parse_type = QUERY_PARSE;
	}
#line 1681 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 209 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = NULL;
		fta_parse_result->fta_parse_tree = NULL;
		fta_parse_result->tables = (yyvsp[0].table_list_schema);
		fta_parse_result->parse_type = TABLE_PARSE;
	}
#line 1692 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 216 "fta.y" /* yacc.c:1646  */
    {
		fta_parse_result->parse_tree_list = NULL;
		fta_parse_result->fta_parse_tree = (yyvsp[-1].tblp);
		fta_parse_result->tables = (yyvsp[-2].table_list_schema);
		fta_parse_result->parse_type = STREAM_PARSE;
	}
#line 1703 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 230 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-2].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1713 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 235 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-2].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1723 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 240 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap(NULL);			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1733 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 245 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1742 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 249 "fta.y" /* yacc.c:1646  */
    {
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1750 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 252 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-2].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1760 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 257 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyvsp[0].tblp)->add_param_list((yyvsp[-2].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1770 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 262 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_param_list((yyvsp[-1].var_defs));		// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1779 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 266 "fta.y" /* yacc.c:1646  */
    {
				(yyvsp[0].tblp)->add_nmap((yyvsp[-1].var_defs));			// Memory leak : plug it.
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1788 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 270 "fta.y" /* yacc.c:1646  */
    {
				(yyval.tblp) = (yyvsp[0].tblp);
			}
#line 1796 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 275 "fta.y" /* yacc.c:1646  */
    {(yyval.q_list) = new query_list_t((yyvsp[0].tblp));}
#line 1802 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 276 "fta.y" /* yacc.c:1646  */
    {(yyval.q_list) = (yyvsp[-2].q_list)->append((yyvsp[0].tblp));}
#line 1808 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 280 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=(yyvsp[-1].var_defs);}
#line 1814 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 281 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=NULL;}
#line 1820 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 285 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=(yyvsp[-1].var_defs);fta_parse_defines=(yyvsp[-1].var_defs);}
#line 1826 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 286 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs)=NULL;fta_parse_defines = NULL;}
#line 1832 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 290 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs) = new var_defs_t((yyvsp[0].var_pair));}
#line 1838 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 291 "fta.y" /* yacc.c:1646  */
    {(yyval.var_defs) = (yyvsp[-1].var_defs)->add_var_pair((yyvsp[0].var_pair));}
#line 1844 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 295 "fta.y" /* yacc.c:1646  */
    {(yyval.var_pair) = new var_pair_t((yyvsp[-2].strval),(yyvsp[-1].strval));}
#line 1850 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 296 "fta.y" /* yacc.c:1646  */
    {(yyval.var_pair) = new var_pair_t((yyvsp[-2].strval),(yyvsp[-1].strval));}
#line 1856 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 300 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = (yyvsp[0].tblp)->add_selection((yyvsp[-1].select_listval));}
#line 1862 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 305 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = new table_exp_t((yyvsp[-1].clist),(yyvsp[0].tbl_list));}
#line 1868 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 307 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp) = new table_exp_t((yyvsp[-3].clist),(yyvsp[-1].scalarval),(yyvsp[0].tbl_list));}
#line 1874 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 314 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval) = (yyvsp[0].select_listval);}
#line 1880 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 326 "fta.y" /* yacc.c:1646  */
    {(yyval.tblp)=new table_exp_t((yyvsp[-7].tbl_list),(yyvsp[-6].predp),(yyvsp[-5].extended_gb_list),(yyvsp[-4].clist),(yyvsp[-3].predp),(yyvsp[-2].predp),(yyvsp[-1].predp), (yyvsp[0].predp));}
#line 1886 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 330 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(-1);}
#line 1892 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 331 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(INNER_JOIN_PROPERTY);}
#line 1898 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 332 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(OUTER_JOIN_PROPERTY);}
#line 1904 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 333 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(RIGHT_OUTER_JOIN_PROPERTY);}
#line 1910 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 334 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(LEFT_OUTER_JOIN_PROPERTY);}
#line 1916 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 335 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = (yyvsp[0].tbl_list); (yyval.tbl_list)->set_properties(FILTER_JOIN_PROPERTY); (yyval.tbl_list)->set_colref((yyvsp[-5].colref)); (yyval.tbl_list)->set_temporal_range((yyvsp[-3].strval));}
#line 1922 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 339 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list) = new tablevar_list_t((yyvsp[0].table));}
#line 1928 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 340 "fta.y" /* yacc.c:1646  */
    {(yyval.tbl_list)= (yyvsp[-2].tbl_list)->append_table((yyvsp[0].table));}
#line 1934 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 344 "fta.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table);}
#line 1940 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 345 "fta.y" /* yacc.c:1646  */
    { (yyval.table)= (yyvsp[-1].table)->set_range_var((yyvsp[0].strval));}
#line 1946 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 349 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[0].stringval)->c_str());}
#line 1952 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 350 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-2].strval),(yyvsp[0].stringval)->c_str(),0);}
#line 1958 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 351 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].stringval)->c_str());}
#line 1964 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 352 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].stringval)->c_str());}
#line 1970 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 353 "fta.y" /* yacc.c:1646  */
    {(yyval.table) = new tablevar_t((yyvsp[-3].strval),(yyvsp[0].stringval)->c_str(),1);}
#line 1976 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 357 "fta.y" /* yacc.c:1646  */
    {(yyval.stringval) = new string_t((yyvsp[0].strval));}
#line 1982 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 358 "fta.y" /* yacc.c:1646  */
    {(yyval.stringval) = (yyval.stringval)->append("/",(yyvsp[0].strval));}
#line 1988 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 363 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 1994 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 364 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp);}
#line 2000 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 368 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2006 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 372 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2012 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 373 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2018 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 377 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2024 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 378 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2030 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 382 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2036 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 383 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp); }
#line 2042 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 387 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=NULL;}
#line 2048 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 388 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=(yyvsp[0].predp);}
#line 2054 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 392 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2060 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 399 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=new predicate_t("OR",(yyvsp[-2].predp),(yyvsp[0].predp));}
#line 2066 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 400 "fta.y" /* yacc.c:1646  */
    {(yyval.predp)=new predicate_t("AND",(yyvsp[-2].predp),(yyvsp[0].predp));}
#line 2072 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 401 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t("NOT", (yyvsp[0].predp) );}
#line 2078 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 402 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[-1].predp);}
#line 2084 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 403 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = (yyvsp[0].predp);}
#line 2090 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 407 "fta.y" /* yacc.c:1646  */
    { (yyval.predp)=(yyvsp[0].predp);}
#line 2096 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 408 "fta.y" /* yacc.c:1646  */
    { (yyval.predp) = (yyvsp[0].predp);}
#line 2102 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 409 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = predicate_t::make_paramless_fcn_predicate((yyvsp[-2].strval)); }
#line 2108 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 410 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t((yyvsp[-3].strval), (yyvsp[-1].se_listval)->get_se_list()); }
#line 2114 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 414 "fta.y" /* yacc.c:1646  */
    {(yyval.predp) = new predicate_t((yyvsp[-2].scalarval),(yyvsp[-1].strval),(yyvsp[0].scalarval));}
#line 2120 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 418 "fta.y" /* yacc.c:1646  */
    { (yyval.predp) = new predicate_t((yyvsp[-4].scalarval),(yyvsp[-1].lit_l)); }
#line 2126 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 422 "fta.y" /* yacc.c:1646  */
    {(yyval.lit_l) = new literal_list_t((yyvsp[0].litval));}
#line 2132 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 423 "fta.y" /* yacc.c:1646  */
    {(yyval.lit_l) = (yyvsp[-2].lit_l)->append_literal((yyvsp[0].litval));}
#line 2138 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 429 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("+",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2144 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 430 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("-",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2150 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 431 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("|",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2156 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 432 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("*",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2162 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 433 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("/",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2168 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 434 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("&",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2174 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 435 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t("%",(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2180 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 436 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)=new scalarexp_t((yyvsp[-1].strval),(yyvsp[-2].scalarval),(yyvsp[0].scalarval));}
#line 2186 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 437 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("+",(yyvsp[0].scalarval));}
#line 2192 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 438 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("-",(yyvsp[0].scalarval));}
#line 2198 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 439 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("!",(yyvsp[0].scalarval));}
#line 2204 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 440 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t("~",(yyvsp[0].scalarval));}
#line 2210 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 441 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval)= new scalarexp_t((yyvsp[0].litval));}
#line 2216 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 442 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_param_reference((yyvsp[0].strval));}
#line 2222 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 443 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_iface_param_reference((yyvsp[0].ifpref));}
#line 2228 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 444 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = new scalarexp_t((yyvsp[0].colref));}
#line 2234 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 445 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = (yyvsp[-1].scalarval);}
#line 2240 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 446 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_star_aggr((yyvsp[-3].strval)); }
#line 2246 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 447 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_se_aggr((yyvsp[-3].strval),(yyvsp[-1].scalarval)); }
#line 2252 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 448 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = new scalarexp_t((yyvsp[-3].strval), (yyvsp[-1].se_listval)->get_se_list()); }
#line 2258 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 449 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_paramless_fcn((yyvsp[-2].strval)); }
#line 2264 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 450 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_star_aggr((yyvsp[-4].strval)); (yyval.scalarval)->set_superaggr(true); }
#line 2270 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 451 "fta.y" /* yacc.c:1646  */
    { (yyval.scalarval) = scalarexp_t::make_se_aggr((yyvsp[-4].strval),(yyvsp[-1].scalarval)); (yyval.scalarval)->set_superaggr(true); }
#line 2276 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 452 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = new scalarexp_t((yyvsp[-4].strval), (yyvsp[-1].se_listval)->get_se_list()); (yyval.scalarval)->set_superaggr(true); }
#line 2282 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 453 "fta.y" /* yacc.c:1646  */
    {(yyval.scalarval) = scalarexp_t::make_paramless_fcn((yyvsp[-3].strval)); (yyval.scalarval)->set_superaggr(true); }
#line 2288 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 458 "fta.y" /* yacc.c:1646  */
    {	(yyval.select_listval)= new select_list_t((yyvsp[0].scalarval)); }
#line 2294 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 459 "fta.y" /* yacc.c:1646  */
    {	(yyval.select_listval)= new select_list_t((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2300 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 460 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval)=(yyvsp[-2].select_listval)->append((yyvsp[0].scalarval)); }
#line 2306 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 461 "fta.y" /* yacc.c:1646  */
    { (yyval.select_listval)=(yyvsp[-4].select_listval)->append((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2312 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 465 "fta.y" /* yacc.c:1646  */
    {	(yyval.se_listval)= new se_list_t((yyvsp[0].scalarval)); }
#line 2318 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 466 "fta.y" /* yacc.c:1646  */
    { (yyval.se_listval)=(yyvsp[-2].se_listval)->append((yyvsp[0].scalarval)); }
#line 2324 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 470 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_STRING);}
#line 2330 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 471 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_INT);}
#line 2336 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 472 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_LONGINT);}
#line 2342 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 473 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_FLOAT);}
#line 2348 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 474 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t("TRUE",LITERAL_BOOL);}
#line 2354 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 475 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t("FALSE",LITERAL_BOOL);}
#line 2360 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 476 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_TIMEVAL);}
#line 2366 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 477 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_HEX);}
#line 2372 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 478 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_LONGHEX);}
#line 2378 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 479 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_IP);}
#line 2384 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 480 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = new literal_t((yyvsp[0].strval),LITERAL_IPV6);}
#line 2390 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 481 "fta.y" /* yacc.c:1646  */
    {(yyval.litval) = literal_t::make_define_literal((yyvsp[0].strval),fta_parse_defines);}
#line 2396 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 487 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb_list) = NULL;}
#line 2402 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 488 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb_list) = (yyvsp[0].extended_gb_list);}
#line 2408 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 492 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = NULL;}
#line 2414 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 493 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[0].clist);}
#line 2420 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 497 "fta.y" /* yacc.c:1646  */
    { (yyval.list_of_gb_list) = new list_of_gb_list_t((yyvsp[-1].gb_list));}
#line 2426 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 498 "fta.y" /* yacc.c:1646  */
    {(yyval.list_of_gb_list) = (yyvsp[-4].list_of_gb_list)->append((yyvsp[-1].gb_list));}
#line 2432 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 502 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::create_from_gb((yyvsp[0].gb_val));}
#line 2438 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 503 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_rollup((yyvsp[-1].gb_list));}
#line 2444 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 504 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_cube((yyvsp[-1].gb_list));}
#line 2450 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 505 "fta.y" /* yacc.c:1646  */
    {(yyval.extended_gb) = extended_gb_t::extended_create_from_gsets((yyvsp[-1].list_of_gb_list));}
#line 2456 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 509 "fta.y" /* yacc.c:1646  */
    { (yyval.extended_gb_list) = new extended_gb_list_t((yyvsp[0].extended_gb));}
#line 2462 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 510 "fta.y" /* yacc.c:1646  */
    { (yyval.extended_gb_list)=(yyvsp[-2].extended_gb_list)->append((yyvsp[0].extended_gb));}
#line 2468 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 514 "fta.y" /* yacc.c:1646  */
    { (yyval.gb_list) = new gb_list_t((yyvsp[0].gb_val));}
#line 2474 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 515 "fta.y" /* yacc.c:1646  */
    { (yyval.gb_list)=(yyvsp[-2].gb_list)->append((yyvsp[0].gb_val));}
#line 2480 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 519 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[0].strval)); }
#line 2486 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 520 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2492 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 521 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2498 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 522 "fta.y" /* yacc.c:1646  */
    {(yyval.gb_val) = new gb_t((yyvsp[-2].scalarval),(yyvsp[0].strval)); }
#line 2504 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 533 "fta.y" /* yacc.c:1646  */
    {(yyval.ifpref) = new ifpref_t((yyvsp[0].strval));}
#line 2510 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 534 "fta.y" /* yacc.c:1646  */
    {(yyval.ifpref) = new ifpref_t((yyvsp[-3].strval), (yyvsp[0].strval));}
#line 2516 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 538 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[0].strval)); }
#line 2522 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 539 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2528 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 540 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[-4].strval),(yyvsp[-2].strval),(yyvsp[0].strval)); }
#line 2534 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 544 "fta.y" /* yacc.c:1646  */
    {(yyval.clist)=new colref_list_t((yyvsp[-2].colref)); (yyval.clist)->append((yyvsp[0].colref));}
#line 2540 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 545 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[-2].clist)->append((yyvsp[0].colref));}
#line 2546 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 549 "fta.y" /* yacc.c:1646  */
    {(yyval.colref) = new colref_t((yyvsp[0].strval)); }
#line 2552 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 553 "fta.y" /* yacc.c:1646  */
    {(yyval.clist)=new colref_list_t((yyvsp[-2].colref)); (yyval.clist)->append((yyvsp[0].colref));}
#line 2558 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 554 "fta.y" /* yacc.c:1646  */
    {(yyval.clist) = (yyvsp[-2].clist)->append((yyvsp[0].colref));}
#line 2564 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 569 "fta.y" /* yacc.c:1646  */
    {(yyval.table_list_schema) = new table_list((yyvsp[0].table_def_t));}
#line 2570 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 570 "fta.y" /* yacc.c:1646  */
    {(yyval.table_list_schema) = (yyvsp[-1].table_list_schema)->append_table((yyvsp[0].table_def_t));}
#line 2576 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 573 "fta.y" /* yacc.c:1646  */
    {
					(yyval.table_def_t)=new table_def((yyvsp[-5].strval),(yyvsp[-4].plist_t),(yyvsp[-3].plist_t), (yyvsp[-1].field_list_t), PROTOCOL_SCHEMA); delete (yyvsp[-4].plist_t); delete (yyvsp[-1].field_list_t);}
#line 2583 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 575 "fta.y" /* yacc.c:1646  */
    {
					(yyval.table_def_t)=new table_def((yyvsp[-4].stringval)->c_str(),(yyvsp[-3].plist_t),NULL,(yyvsp[-1].field_list_t), STREAM_SCHEMA); delete (yyvsp[-1].field_list_t);}
#line 2590 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 577 "fta.y" /* yacc.c:1646  */
    {
				(yyval.table_def_t) = new table_def((yyvsp[-14].strval), (yyvsp[-11].plist_t), (yyvsp[-8].field_list_t), (yyvsp[-4].subqueryspec_list_t), (yyvsp[-1].plist_t)); }
#line 2597 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 579 "fta.y" /* yacc.c:1646  */
    { (yyval.table_def_t) = new table_def((yyvsp[-1].ufcnl)); }
#line 2603 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 583 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcnl) = new unpack_fcn_list((yyvsp[0].ufcn));}
#line 2609 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 584 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcnl) = (yyvsp[-2].ufcnl) -> append((yyvsp[0].ufcn));}
#line 2615 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 588 "fta.y" /* yacc.c:1646  */
    {(yyval.ufcn) = new unpack_fcn((yyvsp[-2].strval),(yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2621 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 592 "fta.y" /* yacc.c:1646  */
    {(yyval.subqueryspec_list_t) = new subqueryspec_list((yyvsp[0].subq_spec_t));}
#line 2627 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 593 "fta.y" /* yacc.c:1646  */
    {(yyval.subqueryspec_list_t) = (yyvsp[-2].subqueryspec_list_t)->append((yyvsp[0].subq_spec_t));}
#line 2633 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 597 "fta.y" /* yacc.c:1646  */
    {(yyval.subq_spec_t)=new subquery_spec((yyvsp[-3].strval), (yyvsp[-1].namevec_t)); delete (yyvsp[-1].namevec_t);}
#line 2639 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 600 "fta.y" /* yacc.c:1646  */
    {(yyval.field_list_t) = new field_entry_list((yyvsp[0].field_t));}
#line 2645 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 601 "fta.y" /* yacc.c:1646  */
    {(yyval.field_list_t) = (yyvsp[-1].field_list_t)->append_field((yyvsp[0].field_t));}
#line 2651 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 605 "fta.y" /* yacc.c:1646  */
    {(yyval.field_t) = new field_entry((yyvsp[-5].strval),(yyvsp[-4].strval),(yyvsp[-3].strval),(yyvsp[-2].plist_t),(yyvsp[-1].plist_t));}
#line 2657 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 606 "fta.y" /* yacc.c:1646  */
    {(yyval.field_t) = new field_entry((yyvsp[-3].strval),(yyvsp[-2].strval),"",(yyvsp[-1].plist_t),NULL);}
#line 2663 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 610 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2669 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 611 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2675 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 615 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[0].strval));}
#line 2681 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 616 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2687 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 617 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2693 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 618 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2699 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 619 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-2].plist_t)->append((yyvsp[0].strval));}
#line 2705 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 620 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2711 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 621 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2717 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 622 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-3].plist_t)->append((yyvsp[-1].strval),(yyvsp[0].strval));}
#line 2723 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 626 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2729 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 627 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2735 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 631 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = NULL;}
#line 2741 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 632 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-1].plist_t);}
#line 2747 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 636 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = new param_list((yyvsp[0].strval));}
#line 2753 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 637 "fta.y" /* yacc.c:1646  */
    {(yyval.plist_t) = (yyvsp[-2].plist_t)->append((yyvsp[0].strval));}
#line 2759 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 641 "fta.y" /* yacc.c:1646  */
    {(yyval.namevec_t) = new name_vec((yyvsp[-2].strval),(yyvsp[-1].strval),(yyvsp[0].plist_t));}
#line 2765 "fta.tab.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 642 "fta.y" /* yacc.c:1646  */
    {(yyval.namevec_t) = (yyvsp[-4].namevec_t)->append((yyvsp[-2].strval),(yyvsp[-1].strval), (yyvsp[0].plist_t));}
#line 2771 "fta.tab.cc" /* yacc.c:1646  */
    break;


#line 2775 "fta.tab.cc" /* yacc.c:1646  */
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
#line 645 "fta.y" /* yacc.c:1906  */


