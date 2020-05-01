/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 52 "fta.y" /* yacc.c:1909  */

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


#line 162 "fta.tab.cc.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE FtaParserlval;

int FtaParserparse (void);

#endif /* !YY_FTAPARSER_FTA_TAB_CC_H_INCLUDED  */
