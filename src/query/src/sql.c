/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
#include <assert.h>
/************ Begin %include sections from the grammar ************************/
#line 23 "../inc/sql.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "qSqlparser.h"
#include "tcmdtype.h"
#include "ttoken.h"
#include "ttokendef.h"
#include "tutil.h"
#include "tvariant.h"
#line 42 "../inc/sql.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ParseCTX_*         As ParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned short int
#define YYNOCODE 277
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE SStrToken
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  SCreateTableSql* yy56;
  int yy70;
  SCreatedTableInfo yy84;
  SRelationInfo* yy114;
  SIntervalVal yy222;
  SSqlNode* yy224;
  SCreateDbInfo yy246;
  tSqlExpr* yy260;
  TAOS_FIELD yy363;
  SSessionWindowVal yy365;
  SCreateAcctInfo yy377;
  int64_t yy387;
  SArray* yy403;
  SLimitVal yy404;
  tVariant yy488;
  SWindowStateVal yy544;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL SSqlInfo* pInfo;
#define ParseARG_PDECL ,SSqlInfo* pInfo
#define ParseARG_PARAM ,pInfo
#define ParseARG_FETCH SSqlInfo* pInfo=yypParser->pInfo;
#define ParseARG_STORE yypParser->pInfo=pInfo;
#define ParseCTX_SDECL
#define ParseCTX_PDECL
#define ParseCTX_PARAM
#define ParseCTX_FETCH
#define ParseCTX_STORE
#define YYFALLBACK 1
#define YYNSTATE             365
#define YYNRULE              291
#define YYNRULE_WITH_ACTION  291
#define YYNTOKEN             197
#define YY_MAX_SHIFT         364
#define YY_MIN_SHIFTREDUCE   572
#define YY_MAX_SHIFTREDUCE   862
#define YY_ERROR_ACTION      863
#define YY_ACCEPT_ACTION     864
#define YY_NO_ACTION         865
#define YY_MIN_REDUCE        866
#define YY_MAX_REDUCE        1156
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (758)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   208,  623,  247,  623,  623,   97,  246,  230,  362,  624,
 /*    10 */  1130,  624,  624,   56,   57,  153,   60,   61,  659, 1034,
 /*    20 */   250,   50, 1043,   59,  319,   64,   62,   65,   63,  991,
 /*    30 */   251,  989,  990,   55,   54,  233,  992,   53,   52,   51,
 /*    40 */   993, 1009,  994,  995,   53,   52,   51,  573,  574,  575,
 /*    50 */   576,  577,  578,  579,  580,  581,  582,  583,  584,  585,
 /*    60 */   586,  363,  208,  259,  231,  160,  208,   56,   57,   37,
 /*    70 */    60,   61, 1131,  175,  250,   50, 1131,   59,  319,   64,
 /*    80 */    62,   65,   63,  279,  278,   29,   79,   55,   54, 1040,
 /*    90 */   208,   53,   52,   51,   56,   57,  317,   60,   61,  236,
 /*   100 */  1131,  250,   50, 1021,   59,  319,   64,   62,   65,   63,
 /*   110 */   361,  360,  145,  232,   55,   54,   85, 1018,   53,   52,
 /*   120 */    51,   56,   58,  242,   60,   61,  744, 1021,  250,   50,
 /*   130 */    94,   59,  319,   64,   62,   65,   63,  799, 1080,  244,
 /*   140 */   291,   55,   54, 1021,  160,   53,   52,   51,   57,  350,
 /*   150 */    60,   61,    9,   44,  250,   50, 1007,   59,  319,   64,
 /*   160 */    62,   65,   63, 1004, 1005,   34, 1008,   55,   54,  864,
 /*   170 */   364,   53,   52,   51,   43,  315,  357,  356,  314,  313,
 /*   180 */   312,  355,  311,  310,  309,  354,  308,  353,  352,  983,
 /*   190 */   971,  972,  973,  974,  975,  976,  977,  978,  979,  980,
 /*   200 */   981,  982,  984,  985,   60,   61,   24, 1034,  250,   50,
 /*   210 */    37,   59,  319,   64,   62,   65,   63, 1079,   37, 1034,
 /*   220 */   259,   55,   54,  234,  211,   53,   52,   51,  249,  814,
 /*   230 */   176,  217,  803,  160,  806,  272,  809,  136,  135,  216,
 /*   240 */   317,  249,  814,  324,   85,  803,   14,  806,   37,  809,
 /*   250 */    93,  160,  731,   37,  240,  728,  747,  729, 1018,  730,
 /*   260 */   228,  229,  241,  736,  320,  737, 1018,   23,    5,   40,
 /*   270 */   179,  258,   37,  228,  229,  178,  103,  108,   99,  107,
 /*   280 */    96,   44,  623,  255,  256,  205,   64,   62,   65,   63,
 /*   290 */   624,  206,  328,  304,   55,   54, 1018,  329,   53,   52,
 /*   300 */    51, 1018,  253,  271,  293,   77,   90,   55,   54,   66,
 /*   310 */  1015,   53,   52,   51,  914,  224,  121,  114,  126,  264,
 /*   320 */  1017,  190,   66,  125,   91,  131,  134,  124,  199,  197,
 /*   330 */   195,  268,  267,  128,  707,  194,  140,  139,  138,  137,
 /*   340 */    78,  751,   37,   37,  815,  810,  260,  123,  257,  845,
 /*   350 */   335,  811,   37,  334,  333,   37,  243,  815,  810,  350,
 /*   360 */    37,   37,  340,  339,  811,  358,  952,  732,  733,   43,
 /*   370 */   212,  357,  356,  805, 1006,  808,  355,  254,  259,  252,
 /*   380 */   354,   82,  353,  352,  327,  326,  330,  331, 1019,   83,
 /*   390 */  1018, 1018,  804,  273,  807,  924,  336,    1,  177,  337,
 /*   400 */  1018,   92,  190, 1018,  338,  342,  915,   38, 1018, 1018,
 /*   410 */   151,  149,  148,  190,  763,   80,    3,  191,  275,  780,
 /*   420 */   781,  771,  772,   70,   73,  717,  275,  296,  155,  719,
 /*   430 */   321,  298,  718,   33,  801,   67,   26,  835,  816,   38,
 /*   440 */   248,   38,  622,   67,   16,   95,   67,   76,  113,   15,
 /*   450 */    18,   25,   25,  112, 1035,   17,   25,  734,   20,  735,
 /*   460 */  1127,    6,  120,   19,   74,   71,  299,  119,   22, 1126,
 /*   470 */   802,  133,  132,   21, 1125,  226,  227,  209,  210,  706,
 /*   480 */   213,  207,  214,  215,  220, 1020,  221,  222,  219,  204,
 /*   490 */  1152, 1144,  812, 1090, 1089,  238, 1086,  269, 1085,  239,
 /*   500 */   152,  341, 1042,   47, 1053, 1072, 1071, 1050, 1051, 1055,
 /*   510 */   276,  813,  154,  280,  158,  285,  172,  171, 1014, 1016,
 /*   520 */   173,  174,  929,  150,  301,  302,  762,  168,  303, 1032,
 /*   530 */   306,  161,  818,  307,   45,  202,   41,  318,  235,  294,
 /*   540 */   923,  325,   75, 1151,  162,  110,  282,  289,   72,   49,
 /*   550 */  1150,  163, 1147,  180,  292,  290,  332, 1143,  116,  164,
 /*   560 */   181, 1142, 1137,  182,  949,  288,   42,   39,  165,   46,
 /*   570 */   203,  911,  127,  909,  129,  130,  907,  906,  261,  284,
 /*   580 */   193,  904,  903,  902,  901,  900,  899,  286,  898,  196,
 /*   590 */   198,  895,  893,  281,  891,  889,  200,  886,  201,   48,
 /*   600 */   274,   81,   86,  305,  283, 1073,  351,  122,  343,  344,
 /*   610 */   345,  346,  347,  225,  245,  348,  349,  300,  359,  862,
 /*   620 */   263,  262,  223, 1140,  861,  265,  218,  266,  928,  927,
 /*   630 */   104,  105,  860,  841,  840,  275,  270,   10,  295,  739,
 /*   640 */   905,   84,  141,  142,  185,  897,  184,  950,  183,  186,
 /*   650 */   187,  189,  188,  143,    2,  896,  951,  987,  144,  888,
 /*   660 */   170,  166,  167,   30,  169,  887,    4,  277,   87,  997,
 /*   670 */   764,  156,  157,  767,   88,  237,  769,   89,  287,   31,
 /*   680 */   773,  159,   11,   32,   12,   13,   27,  297,   28,   96,
 /*   690 */    98,  101,   35,  100,  637,   36,  102,  672,  670,  669,
 /*   700 */   668,  666,  665,  664,  661,  316,  627,  106,    7,  322,
 /*   710 */   323,  817,    8,  109,  111,  819,   68,   69,  115,  117,
 /*   720 */    38,  709,  708,  118,  705,  653,  651,  643,  649,  645,
 /*   730 */   647,  641,  639,  675,  674,  673,  671,  667,  663,  662,
 /*   740 */   192,  625,  590,  588,  866,  865,  865,  865,  865,  865,
 /*   750 */   865,  865,  865,  865,  865,  865,  146,  147,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   266,    1,  206,    1,    1,  207,  206,  199,  200,    9,
 /*    10 */   276,    9,    9,   13,   14,  200,   16,   17,    5,  247,
 /*    20 */    20,   21,  200,   23,   24,   25,   26,   27,   28,  223,
 /*    30 */   206,  225,  226,   33,   34,  263,  230,   37,   38,   39,
 /*    40 */   234,  243,  236,  237,   37,   38,   39,   45,   46,   47,
 /*    50 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*    60 */    58,   59,  266,  200,   62,  200,  266,   13,   14,  200,
 /*    70 */    16,   17,  276,  210,   20,   21,  276,   23,   24,   25,
 /*    80 */    26,   27,   28,  268,  269,   82,   86,   33,   34,  267,
 /*    90 */   266,   37,   38,   39,   13,   14,   84,   16,   17,  245,
 /*   100 */   276,   20,   21,  249,   23,   24,   25,   26,   27,   28,
 /*   110 */    66,   67,   68,  244,   33,   34,   82,  248,   37,   38,
 /*   120 */    39,   13,   14,  245,   16,   17,   97,  249,   20,   21,
 /*   130 */   207,   23,   24,   25,   26,   27,   28,   83,  273,  245,
 /*   140 */   275,   33,   34,  249,  200,   37,   38,   39,   14,   90,
 /*   150 */    16,   17,  123,  119,   20,   21,    0,   23,   24,   25,
 /*   160 */    26,   27,   28,  240,  241,  242,  243,   33,   34,  197,
 /*   170 */   198,   37,   38,   39,   98,   99,  100,  101,  102,  103,
 /*   180 */   104,  105,  106,  107,  108,  109,  110,  111,  112,  223,
 /*   190 */   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,
 /*   200 */   234,  235,  236,  237,   16,   17,   44,  247,   20,   21,
 /*   210 */   200,   23,   24,   25,   26,   27,   28,  273,  200,  247,
 /*   220 */   200,   33,   34,  263,   62,   37,   38,   39,    1,    2,
 /*   230 */   210,   69,    5,  200,    7,  263,    9,   75,   76,   77,
 /*   240 */    84,    1,    2,   81,   82,    5,   82,    7,  200,    9,
 /*   250 */    86,  200,    2,  200,  244,    5,   37,    7,  248,    9,
 /*   260 */    33,   34,  244,    5,   37,    7,  248,  266,   63,   64,
 /*   270 */    65,   69,  200,   33,   34,   70,   71,   72,   73,   74,
 /*   280 */   116,  119,    1,   33,   34,  266,   25,   26,   27,   28,
 /*   290 */     9,  266,  244,   88,   33,   34,  248,  244,   37,   38,
 /*   300 */    39,  248,   69,  141,  271,  143,  273,   33,   34,   82,
 /*   310 */   200,   37,   38,   39,  205,  153,   63,   64,   65,  142,
 /*   320 */   248,  212,   82,   70,  273,   72,   73,   74,   63,   64,
 /*   330 */    65,  154,  155,   80,    5,   70,   71,   72,   73,   74,
 /*   340 */   207,  122,  200,  200,  117,  118,  144,   78,  146,  147,
 /*   350 */   148,  124,  200,  151,  152,  200,  246,  117,  118,   90,
 /*   360 */   200,  200,   33,   34,  124,  221,  222,  117,  118,   98,
 /*   370 */   266,  100,  101,    5,  241,    7,  105,  144,  200,  146,
 /*   380 */   109,   83,  111,  112,  151,  152,  244,  244,  210,   83,
 /*   390 */   248,  248,    5,   83,    7,  205,  244,  208,  209,  244,
 /*   400 */   248,  250,  212,  248,  244,  244,  205,   97,  248,  248,
 /*   410 */    63,   64,   65,  212,   83,  264,  203,  204,  120,  132,
 /*   420 */   133,   83,   83,   97,   97,   83,  120,   83,   97,   83,
 /*   430 */    15,   83,   83,   82,    1,   97,   97,   83,   83,   97,
 /*   440 */    61,   97,   83,   97,  145,   97,   97,   82,  145,  150,
 /*   450 */   145,   97,   97,  150,  247,  150,   97,    5,  145,    7,
 /*   460 */   266,   82,  145,  150,  137,  139,  115,  150,  145,  266,
 /*   470 */    37,   78,   79,  150,  266,  266,  266,  266,  266,  114,
 /*   480 */   266,  266,  266,  266,  266,  249,  266,  266,  266,  266,
 /*   490 */   249,  249,  124,  239,  239,  239,  239,  200,  239,  239,
 /*   500 */   200,  239,  200,  265,  200,  274,  274,  200,  200,  200,
 /*   510 */   247,  124,  200,  270,  200,  200,  200,  251,  200,  247,
 /*   520 */   200,  200,  200,   61,  200,  200,  124,  254,  200,  262,
 /*   530 */   200,  261,  117,  200,  200,  200,  200,  200,  270,  130,
 /*   540 */   200,  200,  136,  200,  260,  200,  270,  270,  138,  135,
 /*   550 */   200,  259,  200,  200,  134,  129,  200,  200,  200,  258,
 /*   560 */   200,  200,  200,  200,  200,  128,  200,  200,  257,  200,
 /*   570 */   200,  200,  200,  200,  200,  200,  200,  200,  200,  126,
 /*   580 */   200,  200,  200,  200,  200,  200,  200,  127,  200,  200,
 /*   590 */   200,  200,  200,  125,  200,  200,  200,  200,  200,  140,
 /*   600 */   201,  201,  201,   89,  201,  201,  113,   96,   95,   51,
 /*   610 */    92,   94,   55,  201,  201,   93,   91,  201,   84,    5,
 /*   620 */     5,  156,  201,  201,    5,  156,  201,    5,  211,  211,
 /*   630 */   207,  207,    5,  100,   99,  120,  142,   82,  115,   83,
 /*   640 */   201,  121,  202,  202,  214,  201,  218,  220,  219,  217,
 /*   650 */   215,  213,  216,  202,  208,  201,  222,  238,  202,  201,
 /*   660 */   252,  256,  255,   82,  253,  201,  203,   97,   97,  238,
 /*   670 */    83,   82,   97,   83,   82,    1,   83,   82,   82,   97,
 /*   680 */    83,   82,  131,   97,  131,   82,   82,  115,   82,  116,
 /*   690 */    78,   71,   87,   86,    5,   87,   86,    9,    5,    5,
 /*   700 */     5,    5,    5,    5,    5,   15,   85,   78,   82,   24,
 /*   710 */    59,   83,   82,  150,  150,  117,   16,   16,  150,  150,
 /*   720 */    97,    5,    5,  149,   83,    5,    5,    5,    5,    5,
 /*   730 */     5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
 /*   740 */    97,   85,   61,   60,    0,  277,  277,  277,  277,  277,
 /*   750 */   277,  277,  277,  277,  277,  277,   21,   21,  277,  277,
 /*   760 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   770 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   780 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   790 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   800 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   810 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   820 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   830 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   840 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   850 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   860 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   870 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   880 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   890 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   900 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   910 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   920 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   930 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   940 */   277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
 /*   950 */   277,  277,  277,  277,  277,
};
#define YY_SHIFT_COUNT    (364)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (744)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   162,   76,   76,  271,  271,   12,  227,  240,  240,    3,
 /*    10 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*    20 */   281,  281,  281,    0,    2,  240,  250,  250,  250,   34,
 /*    30 */    34,  281,  281,  281,  156,  281,  281,  281,  281,  269,
 /*    40 */    12,   59,   59,   13,  758,  758,  758,  240,  240,  240,
 /*    50 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    60 */   240,  240,  240,  240,  240,  240,  240,  250,  250,  250,
 /*    70 */   329,  329,  329,  329,  329,  329,  329,  281,  281,  281,
 /*    80 */   219,  281,  281,  281,   34,   34,  281,  281,  281,  281,
 /*    90 */   287,  287,   29,   34,  281,  281,  281,  281,  281,  281,
 /*   100 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*   110 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*   120 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*   130 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*   140 */   281,  281,  281,  281,  281,  281,  281,  281,  281,  281,
 /*   150 */   281,  281,  462,  462,  462,  402,  402,  402,  462,  402,
 /*   160 */   462,  406,  410,  409,  414,  420,  426,  437,  460,  453,
 /*   170 */   468,  459,  462,  462,  462,  514,  514,  493,   12,   12,
 /*   180 */   462,  462,  462,  511,  513,  558,  518,  517,  557,  522,
 /*   190 */   525,  493,   13,  462,  534,  534,  462,  534,  462,  534,
 /*   200 */   462,  462,  758,  758,   54,   81,   81,  108,   81,  134,
 /*   210 */   188,  205,  261,  261,  261,  261,  253,  265,  202,  274,
 /*   220 */   274,  274,  274,  233,  177,  164,    7,    7,  368,  387,
 /*   230 */    44,  347,  310,  298,  306,  331,  338,  339,  326,  327,
 /*   240 */   342,  344,  346,  348,  349,  351,  354,  355,  433,  379,
 /*   250 */   415,  359,  299,  303,  305,  258,  452,  313,  317,  365,
 /*   260 */   323,  393,  614,  465,  615,  619,  469,  622,  627,  533,
 /*   270 */   535,  494,  515,  523,  555,  520,  556,  581,  570,  571,
 /*   280 */   587,  589,  590,  575,  592,  593,  595,  674,  596,  597,
 /*   290 */   599,  582,  551,  586,  553,  603,  523,  604,  572,  606,
 /*   300 */   573,  612,  605,  607,  620,  689,  608,  610,  688,  693,
 /*   310 */   694,  695,  696,  697,  698,  699,  621,  690,  629,  626,
 /*   320 */   628,  598,  630,  685,  651,  700,  563,  564,  623,  623,
 /*   330 */   623,  623,  701,  568,  569,  574,  623,  623,  623,  716,
 /*   340 */   717,  641,  623,  720,  721,  722,  723,  724,  725,  726,
 /*   350 */   727,  728,  729,  730,  731,  732,  733,  734,  643,  656,
 /*   360 */   735,  736,  681,  683,  744,
};
#define YY_REDUCE_COUNT (203)
#define YY_REDUCE_MIN   (-266)
#define YY_REDUCE_MAX   (464)
static const short yy_reduce_ofst[] = {
 /*     0 */   -28,  -34,  -34, -194, -194,  -77, -204, -200, -176, -185,
 /*    10 */  -131, -135,   33,   10,   18,   48,   53,  142,  143,  152,
 /*    20 */   155,  160,  161, -178, -192, -266, -146, -122, -106, -228,
 /*    30 */   -40,  -56,   51,  110, -202, -137,   20,  178,   72,  109,
 /*    40 */   133,  190,  201,  144,  151,  189,  213,    1,   19,   25,
 /*    50 */   104,  194,  203,  208,  209,  210,  211,  212,  214,  215,
 /*    60 */   216,  217,  218,  220,  221,  222,  223,  236,  241,  242,
 /*    70 */   254,  255,  256,  257,  259,  260,  262,  297,  300,  302,
 /*    80 */   238,  304,  307,  308,  207,  263,  309,  312,  314,  315,
 /*    90 */   231,  232,  266,  272,  316,  318,  320,  321,  322,  324,
 /*   100 */   325,  328,  330,  333,  334,  335,  336,  337,  340,  341,
 /*   110 */   343,  345,  350,  352,  353,  356,  357,  358,  360,  361,
 /*   120 */   362,  363,  364,  366,  367,  369,  370,  371,  372,  373,
 /*   130 */   374,  375,  376,  377,  378,  380,  381,  382,  383,  384,
 /*   140 */   385,  386,  388,  389,  390,  391,  392,  394,  395,  396,
 /*   150 */   397,  398,  399,  400,  401,  243,  268,  276,  403,  277,
 /*   160 */   404,  267,  270,  284,  292,  301,  311,  405,  407,  273,
 /*   170 */   411,  408,  412,  413,  416,  417,  418,  419,  423,  424,
 /*   180 */   421,  422,  425,  427,  429,  428,  430,  432,  435,  436,
 /*   190 */   438,  431,  434,  439,  440,  441,  444,  451,  454,  456,
 /*   200 */   458,  464,  446,  463,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   863,  986,  925,  996,  912,  922, 1133, 1133, 1133,  863,
 /*    10 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*    20 */   863,  863,  863, 1044,  883, 1133,  863,  863,  863,  863,
 /*    30 */   863,  863,  863,  863,  922,  863,  863,  863,  863,  932,
 /*    40 */   922,  932,  932,  863, 1039,  970,  988,  863,  863,  863,
 /*    50 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*    60 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*    70 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*    80 */  1046, 1052, 1049,  863,  863,  863, 1054,  863,  863,  863,
 /*    90 */  1076, 1076, 1037,  863,  863,  863,  863,  863,  863,  863,
 /*   100 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   110 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   120 */   863,  863,  863,  863,  863,  863,  863,  910,  863,  908,
 /*   130 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   140 */   863,  863,  863,  863,  863,  894,  863,  863,  863,  863,
 /*   150 */   863,  863,  885,  885,  885,  863,  863,  863,  885,  863,
 /*   160 */   885, 1083, 1087, 1069, 1081, 1077, 1068, 1064, 1062, 1060,
 /*   170 */  1059, 1091,  885,  885,  885,  930,  930,  926,  922,  922,
 /*   180 */   885,  885,  885,  948,  946,  944,  936,  942,  938,  940,
 /*   190 */   934,  913,  863,  885,  920,  920,  885,  920,  885,  920,
 /*   200 */   885,  885,  970,  988,  863, 1092, 1082,  863, 1132, 1122,
 /*   210 */  1121,  863, 1128, 1120, 1119, 1118,  863,  863,  863, 1114,
 /*   220 */  1117, 1116, 1115,  863,  863,  863, 1124, 1123,  863,  863,
 /*   230 */   863,  863,  863,  863,  863,  863,  863,  863, 1088, 1084,
 /*   240 */   863,  863,  863,  863,  863,  863,  863,  863,  863, 1094,
 /*   250 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  998,
 /*   260 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   270 */   863,  863, 1036,  863,  863,  863,  863,  863, 1048, 1047,
 /*   280 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   290 */   863, 1078,  863, 1070,  863,  863, 1010,  863,  863,  863,
 /*   300 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   310 */   863,  863,  863,  863,  863,  863,  863,  863,  863,  863,
 /*   320 */   863,  863,  863,  863,  863,  863,  863,  863, 1153, 1148,
 /*   330 */  1149, 1146,  863,  863,  863,  863, 1145, 1138, 1141,  863,
 /*   340 */   863,  863, 1136,  863,  863,  863,  863,  863,  863,  863,
 /*   350 */   863,  863,  863,  863,  863,  863,  863,  863,  954,  863,
 /*   360 */   892,  890,  863,  881,  863,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         ID => nothing */
    1,  /*       BOOL => ID */
    1,  /*    TINYINT => ID */
    1,  /*   SMALLINT => ID */
    1,  /*    INTEGER => ID */
    1,  /*     BIGINT => ID */
    1,  /*      FLOAT => ID */
    1,  /*     DOUBLE => ID */
    1,  /*     STRING => ID */
    1,  /*  TIMESTAMP => ID */
    1,  /*     BINARY => ID */
    1,  /*      NCHAR => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*        NOT => nothing */
    0,  /*         EQ => nothing */
    0,  /*         NE => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         IS => nothing */
    1,  /*       LIKE => ID */
    1,  /*       GLOB => ID */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*         GT => nothing */
    0,  /*         GE => nothing */
    0,  /*         LT => nothing */
    0,  /*         LE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     DIVIDE => nothing */
    0,  /*      TIMES => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     CONCAT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*     TOPICS => nothing */
    0,  /*  FUNCTIONS => nothing */
    0,  /*     MNODES => nothing */
    0,  /*     DNODES => nothing */
    0,  /*   ACCOUNTS => nothing */
    0,  /*      USERS => nothing */
    0,  /*    MODULES => nothing */
    0,  /*    QUERIES => nothing */
    0,  /* CONNECTIONS => nothing */
    0,  /*    STREAMS => nothing */
    0,  /*  VARIABLES => nothing */
    0,  /*     SCORES => nothing */
    0,  /*     GRANTS => nothing */
    0,  /*     VNODES => nothing */
    1,  /*    IPTOKEN => ID */
    0,  /*        DOT => nothing */
    0,  /*     CREATE => nothing */
    0,  /*      TABLE => nothing */
    1,  /*     STABLE => ID */
    1,  /*   DATABASE => ID */
    0,  /*     TABLES => nothing */
    0,  /*    STABLES => nothing */
    0,  /*    VGROUPS => nothing */
    0,  /*       DROP => nothing */
    0,  /*      TOPIC => nothing */
    0,  /*   FUNCTION => nothing */
    0,  /*      DNODE => nothing */
    0,  /*       USER => nothing */
    0,  /*    ACCOUNT => nothing */
    0,  /*        USE => nothing */
    0,  /*   DESCRIBE => nothing */
    0,  /*      ALTER => nothing */
    0,  /*       PASS => nothing */
    0,  /*  PRIVILEGE => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*    COMPACT => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*         IF => nothing */
    0,  /*     EXISTS => nothing */
    0,  /*         AS => nothing */
    0,  /* OUTPUTTYPE => nothing */
    0,  /*  AGGREGATE => nothing */
    0,  /*    BUFSIZE => nothing */
    0,  /*        PPS => nothing */
    0,  /*    TSERIES => nothing */
    0,  /*        DBS => nothing */
    0,  /*    STORAGE => nothing */
    0,  /*      QTIME => nothing */
    0,  /*      CONNS => nothing */
    0,  /*      STATE => nothing */
    0,  /*      COMMA => nothing */
    0,  /*       KEEP => nothing */
    0,  /*      CACHE => nothing */
    0,  /*    REPLICA => nothing */
    0,  /*     QUORUM => nothing */
    0,  /*       DAYS => nothing */
    0,  /*    MINROWS => nothing */
    0,  /*    MAXROWS => nothing */
    0,  /*     BLOCKS => nothing */
    0,  /*      CTIME => nothing */
    0,  /*        WAL => nothing */
    0,  /*      FSYNC => nothing */
    0,  /*       COMP => nothing */
    0,  /*  PRECISION => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*  CACHELAST => nothing */
    0,  /* PARTITIONS => nothing */
    0,  /*   UNSIGNED => nothing */
    0,  /*       TAGS => nothing */
    0,  /*      USING => nothing */
    1,  /*       NULL => ID */
    1,  /*        NOW => ID */
    0,  /*     SELECT => nothing */
    0,  /*      UNION => nothing */
    1,  /*        ALL => ID */
    0,  /*   DISTINCT => nothing */
    0,  /*       FROM => nothing */
    0,  /*   VARIABLE => nothing */
    0,  /*   INTERVAL => nothing */
    0,  /*    SESSION => nothing */
    0,  /* STATE_WINDOW => nothing */
    0,  /*       FILL => nothing */
    0,  /*    SLIDING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    1,  /*        ASC => ID */
    1,  /*       DESC => ID */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    1,  /*     OFFSET => ID */
    0,  /*     SLIMIT => nothing */
    0,  /*    SOFFSET => nothing */
    0,  /*      WHERE => nothing */
    0,  /*      RESET => nothing */
    0,  /*      QUERY => nothing */
    0,  /*     SYNCDB => nothing */
    0,  /*        ADD => nothing */
    0,  /*     COLUMN => nothing */
    0,  /*     MODIFY => nothing */
    0,  /*     DEATCH => nothing */
    1,  /*     ATTACH => ID */
    0,  /*         TO => nothing */
    0,  /*        TAG => nothing */
    0,  /*     CHANGE => nothing */
    0,  /*        SET => nothing */
    0,  /*       KILL => nothing */
    0,  /* CONNECTION => nothing */
    0,  /*     STREAM => nothing */
    0,  /*      COLON => nothing */
    1,  /*      ABORT => ID */
    1,  /*      AFTER => ID */
    1,  /*     BEFORE => ID */
    1,  /*      BEGIN => ID */
    1,  /*    CASCADE => ID */
    1,  /*    CLUSTER => ID */
    1,  /*   CONFLICT => ID */
    1,  /*       COPY => ID */
    1,  /*   DEFERRED => ID */
    1,  /* DELIMITERS => ID */
    1,  /*     DETACH => ID */
    1,  /*       EACH => ID */
    1,  /*        END => ID */
    1,  /*    EXPLAIN => ID */
    1,  /*       FAIL => ID */
    1,  /*        FOR => ID */
    1,  /*     IGNORE => ID */
    1,  /*  IMMEDIATE => ID */
    1,  /*  INITIALLY => ID */
    1,  /*    INSTEAD => ID */
    1,  /*      MATCH => ID */
    1,  /*        KEY => ID */
    1,  /*         OF => ID */
    1,  /*      RAISE => ID */
    1,  /*    REPLACE => ID */
    1,  /*   RESTRICT => ID */
    1,  /*        ROW => ID */
    1,  /*  STATEMENT => ID */
    1,  /*    TRIGGER => ID */
    1,  /*       VIEW => ID */
    1,  /*       SEMI => ID */
    1,  /*       NONE => ID */
    1,  /*       PREV => ID */
    1,  /*     LINEAR => ID */
    1,  /*     IMPORT => ID */
    1,  /*     TBNAME => ID */
    1,  /*       JOIN => ID */
    1,  /*     INSERT => ID */
    1,  /*       INTO => ID */
    1,  /*     VALUES => ID */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
  ParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "ID",
  /*    2 */ "BOOL",
  /*    3 */ "TINYINT",
  /*    4 */ "SMALLINT",
  /*    5 */ "INTEGER",
  /*    6 */ "BIGINT",
  /*    7 */ "FLOAT",
  /*    8 */ "DOUBLE",
  /*    9 */ "STRING",
  /*   10 */ "TIMESTAMP",
  /*   11 */ "BINARY",
  /*   12 */ "NCHAR",
  /*   13 */ "OR",
  /*   14 */ "AND",
  /*   15 */ "NOT",
  /*   16 */ "EQ",
  /*   17 */ "NE",
  /*   18 */ "ISNULL",
  /*   19 */ "NOTNULL",
  /*   20 */ "IS",
  /*   21 */ "LIKE",
  /*   22 */ "GLOB",
  /*   23 */ "BETWEEN",
  /*   24 */ "IN",
  /*   25 */ "GT",
  /*   26 */ "GE",
  /*   27 */ "LT",
  /*   28 */ "LE",
  /*   29 */ "BITAND",
  /*   30 */ "BITOR",
  /*   31 */ "LSHIFT",
  /*   32 */ "RSHIFT",
  /*   33 */ "PLUS",
  /*   34 */ "MINUS",
  /*   35 */ "DIVIDE",
  /*   36 */ "TIMES",
  /*   37 */ "STAR",
  /*   38 */ "SLASH",
  /*   39 */ "REM",
  /*   40 */ "CONCAT",
  /*   41 */ "UMINUS",
  /*   42 */ "UPLUS",
  /*   43 */ "BITNOT",
  /*   44 */ "SHOW",
  /*   45 */ "DATABASES",
  /*   46 */ "TOPICS",
  /*   47 */ "FUNCTIONS",
  /*   48 */ "MNODES",
  /*   49 */ "DNODES",
  /*   50 */ "ACCOUNTS",
  /*   51 */ "USERS",
  /*   52 */ "MODULES",
  /*   53 */ "QUERIES",
  /*   54 */ "CONNECTIONS",
  /*   55 */ "STREAMS",
  /*   56 */ "VARIABLES",
  /*   57 */ "SCORES",
  /*   58 */ "GRANTS",
  /*   59 */ "VNODES",
  /*   60 */ "IPTOKEN",
  /*   61 */ "DOT",
  /*   62 */ "CREATE",
  /*   63 */ "TABLE",
  /*   64 */ "STABLE",
  /*   65 */ "DATABASE",
  /*   66 */ "TABLES",
  /*   67 */ "STABLES",
  /*   68 */ "VGROUPS",
  /*   69 */ "DROP",
  /*   70 */ "TOPIC",
  /*   71 */ "FUNCTION",
  /*   72 */ "DNODE",
  /*   73 */ "USER",
  /*   74 */ "ACCOUNT",
  /*   75 */ "USE",
  /*   76 */ "DESCRIBE",
  /*   77 */ "ALTER",
  /*   78 */ "PASS",
  /*   79 */ "PRIVILEGE",
  /*   80 */ "LOCAL",
  /*   81 */ "COMPACT",
  /*   82 */ "LP",
  /*   83 */ "RP",
  /*   84 */ "IF",
  /*   85 */ "EXISTS",
  /*   86 */ "AS",
  /*   87 */ "OUTPUTTYPE",
  /*   88 */ "AGGREGATE",
  /*   89 */ "BUFSIZE",
  /*   90 */ "PPS",
  /*   91 */ "TSERIES",
  /*   92 */ "DBS",
  /*   93 */ "STORAGE",
  /*   94 */ "QTIME",
  /*   95 */ "CONNS",
  /*   96 */ "STATE",
  /*   97 */ "COMMA",
  /*   98 */ "KEEP",
  /*   99 */ "CACHE",
  /*  100 */ "REPLICA",
  /*  101 */ "QUORUM",
  /*  102 */ "DAYS",
  /*  103 */ "MINROWS",
  /*  104 */ "MAXROWS",
  /*  105 */ "BLOCKS",
  /*  106 */ "CTIME",
  /*  107 */ "WAL",
  /*  108 */ "FSYNC",
  /*  109 */ "COMP",
  /*  110 */ "PRECISION",
  /*  111 */ "UPDATE",
  /*  112 */ "CACHELAST",
  /*  113 */ "PARTITIONS",
  /*  114 */ "UNSIGNED",
  /*  115 */ "TAGS",
  /*  116 */ "USING",
  /*  117 */ "NULL",
  /*  118 */ "NOW",
  /*  119 */ "SELECT",
  /*  120 */ "UNION",
  /*  121 */ "ALL",
  /*  122 */ "DISTINCT",
  /*  123 */ "FROM",
  /*  124 */ "VARIABLE",
  /*  125 */ "INTERVAL",
  /*  126 */ "SESSION",
  /*  127 */ "STATE_WINDOW",
  /*  128 */ "FILL",
  /*  129 */ "SLIDING",
  /*  130 */ "ORDER",
  /*  131 */ "BY",
  /*  132 */ "ASC",
  /*  133 */ "DESC",
  /*  134 */ "GROUP",
  /*  135 */ "HAVING",
  /*  136 */ "LIMIT",
  /*  137 */ "OFFSET",
  /*  138 */ "SLIMIT",
  /*  139 */ "SOFFSET",
  /*  140 */ "WHERE",
  /*  141 */ "RESET",
  /*  142 */ "QUERY",
  /*  143 */ "SYNCDB",
  /*  144 */ "ADD",
  /*  145 */ "COLUMN",
  /*  146 */ "MODIFY",
  /*  147 */ "DEATCH",
  /*  148 */ "ATTACH",
  /*  149 */ "TO",
  /*  150 */ "TAG",
  /*  151 */ "CHANGE",
  /*  152 */ "SET",
  /*  153 */ "KILL",
  /*  154 */ "CONNECTION",
  /*  155 */ "STREAM",
  /*  156 */ "COLON",
  /*  157 */ "ABORT",
  /*  158 */ "AFTER",
  /*  159 */ "BEFORE",
  /*  160 */ "BEGIN",
  /*  161 */ "CASCADE",
  /*  162 */ "CLUSTER",
  /*  163 */ "CONFLICT",
  /*  164 */ "COPY",
  /*  165 */ "DEFERRED",
  /*  166 */ "DELIMITERS",
  /*  167 */ "DETACH",
  /*  168 */ "EACH",
  /*  169 */ "END",
  /*  170 */ "EXPLAIN",
  /*  171 */ "FAIL",
  /*  172 */ "FOR",
  /*  173 */ "IGNORE",
  /*  174 */ "IMMEDIATE",
  /*  175 */ "INITIALLY",
  /*  176 */ "INSTEAD",
  /*  177 */ "MATCH",
  /*  178 */ "KEY",
  /*  179 */ "OF",
  /*  180 */ "RAISE",
  /*  181 */ "REPLACE",
  /*  182 */ "RESTRICT",
  /*  183 */ "ROW",
  /*  184 */ "STATEMENT",
  /*  185 */ "TRIGGER",
  /*  186 */ "VIEW",
  /*  187 */ "SEMI",
  /*  188 */ "NONE",
  /*  189 */ "PREV",
  /*  190 */ "LINEAR",
  /*  191 */ "IMPORT",
  /*  192 */ "TBNAME",
  /*  193 */ "JOIN",
  /*  194 */ "INSERT",
  /*  195 */ "INTO",
  /*  196 */ "VALUES",
  /*  197 */ "program",
  /*  198 */ "cmd",
  /*  199 */ "dbPrefix",
  /*  200 */ "ids",
  /*  201 */ "cpxName",
  /*  202 */ "ifexists",
  /*  203 */ "alter_db_optr",
  /*  204 */ "alter_topic_optr",
  /*  205 */ "acct_optr",
  /*  206 */ "exprlist",
  /*  207 */ "ifnotexists",
  /*  208 */ "db_optr",
  /*  209 */ "topic_optr",
  /*  210 */ "typename",
  /*  211 */ "bufsize",
  /*  212 */ "pps",
  /*  213 */ "tseries",
  /*  214 */ "dbs",
  /*  215 */ "streams",
  /*  216 */ "storage",
  /*  217 */ "qtime",
  /*  218 */ "users",
  /*  219 */ "conns",
  /*  220 */ "state",
  /*  221 */ "intitemlist",
  /*  222 */ "intitem",
  /*  223 */ "keep",
  /*  224 */ "cache",
  /*  225 */ "replica",
  /*  226 */ "quorum",
  /*  227 */ "days",
  /*  228 */ "minrows",
  /*  229 */ "maxrows",
  /*  230 */ "blocks",
  /*  231 */ "ctime",
  /*  232 */ "wal",
  /*  233 */ "fsync",
  /*  234 */ "comp",
  /*  235 */ "prec",
  /*  236 */ "update",
  /*  237 */ "cachelast",
  /*  238 */ "partitions",
  /*  239 */ "signed",
  /*  240 */ "create_table_args",
  /*  241 */ "create_stable_args",
  /*  242 */ "create_table_list",
  /*  243 */ "create_from_stable",
  /*  244 */ "columnlist",
  /*  245 */ "tagitemlist",
  /*  246 */ "tagNamelist",
  /*  247 */ "select",
  /*  248 */ "column",
  /*  249 */ "tagitem",
  /*  250 */ "selcollist",
  /*  251 */ "from",
  /*  252 */ "where_opt",
  /*  253 */ "interval_opt",
  /*  254 */ "session_option",
  /*  255 */ "windowstate_option",
  /*  256 */ "fill_opt",
  /*  257 */ "sliding_opt",
  /*  258 */ "groupby_opt",
  /*  259 */ "having_opt",
  /*  260 */ "orderby_opt",
  /*  261 */ "slimit_opt",
  /*  262 */ "limit_opt",
  /*  263 */ "union",
  /*  264 */ "sclp",
  /*  265 */ "distinct",
  /*  266 */ "expr",
  /*  267 */ "as",
  /*  268 */ "tablelist",
  /*  269 */ "sub",
  /*  270 */ "tmvar",
  /*  271 */ "sortlist",
  /*  272 */ "sortitem",
  /*  273 */ "item",
  /*  274 */ "sortorder",
  /*  275 */ "grouplist",
  /*  276 */ "expritem",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= cmd",
 /*   1 */ "cmd ::= SHOW DATABASES",
 /*   2 */ "cmd ::= SHOW TOPICS",
 /*   3 */ "cmd ::= SHOW FUNCTIONS",
 /*   4 */ "cmd ::= SHOW MNODES",
 /*   5 */ "cmd ::= SHOW DNODES",
 /*   6 */ "cmd ::= SHOW ACCOUNTS",
 /*   7 */ "cmd ::= SHOW USERS",
 /*   8 */ "cmd ::= SHOW MODULES",
 /*   9 */ "cmd ::= SHOW QUERIES",
 /*  10 */ "cmd ::= SHOW CONNECTIONS",
 /*  11 */ "cmd ::= SHOW STREAMS",
 /*  12 */ "cmd ::= SHOW VARIABLES",
 /*  13 */ "cmd ::= SHOW SCORES",
 /*  14 */ "cmd ::= SHOW GRANTS",
 /*  15 */ "cmd ::= SHOW VNODES",
 /*  16 */ "cmd ::= SHOW VNODES IPTOKEN",
 /*  17 */ "dbPrefix ::=",
 /*  18 */ "dbPrefix ::= ids DOT",
 /*  19 */ "cpxName ::=",
 /*  20 */ "cpxName ::= DOT ids",
 /*  21 */ "cmd ::= SHOW CREATE TABLE ids cpxName",
 /*  22 */ "cmd ::= SHOW CREATE STABLE ids cpxName",
 /*  23 */ "cmd ::= SHOW CREATE DATABASE ids",
 /*  24 */ "cmd ::= SHOW dbPrefix TABLES",
 /*  25 */ "cmd ::= SHOW dbPrefix TABLES LIKE ids",
 /*  26 */ "cmd ::= SHOW dbPrefix STABLES",
 /*  27 */ "cmd ::= SHOW dbPrefix STABLES LIKE ids",
 /*  28 */ "cmd ::= SHOW dbPrefix VGROUPS",
 /*  29 */ "cmd ::= SHOW dbPrefix VGROUPS ids",
 /*  30 */ "cmd ::= DROP TABLE ifexists ids cpxName",
 /*  31 */ "cmd ::= DROP STABLE ifexists ids cpxName",
 /*  32 */ "cmd ::= DROP DATABASE ifexists ids",
 /*  33 */ "cmd ::= DROP TOPIC ifexists ids",
 /*  34 */ "cmd ::= DROP FUNCTION ids",
 /*  35 */ "cmd ::= DROP DNODE ids",
 /*  36 */ "cmd ::= DROP USER ids",
 /*  37 */ "cmd ::= DROP ACCOUNT ids",
 /*  38 */ "cmd ::= USE ids",
 /*  39 */ "cmd ::= DESCRIBE ids cpxName",
 /*  40 */ "cmd ::= ALTER USER ids PASS ids",
 /*  41 */ "cmd ::= ALTER USER ids PRIVILEGE ids",
 /*  42 */ "cmd ::= ALTER DNODE ids ids",
 /*  43 */ "cmd ::= ALTER DNODE ids ids ids",
 /*  44 */ "cmd ::= ALTER LOCAL ids",
 /*  45 */ "cmd ::= ALTER LOCAL ids ids",
 /*  46 */ "cmd ::= ALTER DATABASE ids alter_db_optr",
 /*  47 */ "cmd ::= ALTER TOPIC ids alter_topic_optr",
 /*  48 */ "cmd ::= ALTER ACCOUNT ids acct_optr",
 /*  49 */ "cmd ::= ALTER ACCOUNT ids PASS ids acct_optr",
 /*  50 */ "cmd ::= COMPACT VNODES IN LP exprlist RP",
 /*  51 */ "ids ::= ID",
 /*  52 */ "ids ::= STRING",
 /*  53 */ "ifexists ::= IF EXISTS",
 /*  54 */ "ifexists ::=",
 /*  55 */ "ifnotexists ::= IF NOT EXISTS",
 /*  56 */ "ifnotexists ::=",
 /*  57 */ "cmd ::= CREATE DNODE ids",
 /*  58 */ "cmd ::= CREATE ACCOUNT ids PASS ids acct_optr",
 /*  59 */ "cmd ::= CREATE DATABASE ifnotexists ids db_optr",
 /*  60 */ "cmd ::= CREATE TOPIC ifnotexists ids topic_optr",
 /*  61 */ "cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize",
 /*  62 */ "cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize",
 /*  63 */ "cmd ::= CREATE USER ids PASS ids",
 /*  64 */ "bufsize ::=",
 /*  65 */ "bufsize ::= BUFSIZE INTEGER",
 /*  66 */ "pps ::=",
 /*  67 */ "pps ::= PPS INTEGER",
 /*  68 */ "tseries ::=",
 /*  69 */ "tseries ::= TSERIES INTEGER",
 /*  70 */ "dbs ::=",
 /*  71 */ "dbs ::= DBS INTEGER",
 /*  72 */ "streams ::=",
 /*  73 */ "streams ::= STREAMS INTEGER",
 /*  74 */ "storage ::=",
 /*  75 */ "storage ::= STORAGE INTEGER",
 /*  76 */ "qtime ::=",
 /*  77 */ "qtime ::= QTIME INTEGER",
 /*  78 */ "users ::=",
 /*  79 */ "users ::= USERS INTEGER",
 /*  80 */ "conns ::=",
 /*  81 */ "conns ::= CONNS INTEGER",
 /*  82 */ "state ::=",
 /*  83 */ "state ::= STATE ids",
 /*  84 */ "acct_optr ::= pps tseries storage streams qtime dbs users conns state",
 /*  85 */ "intitemlist ::= intitemlist COMMA intitem",
 /*  86 */ "intitemlist ::= intitem",
 /*  87 */ "intitem ::= INTEGER",
 /*  88 */ "keep ::= KEEP intitemlist",
 /*  89 */ "cache ::= CACHE INTEGER",
 /*  90 */ "replica ::= REPLICA INTEGER",
 /*  91 */ "quorum ::= QUORUM INTEGER",
 /*  92 */ "days ::= DAYS INTEGER",
 /*  93 */ "minrows ::= MINROWS INTEGER",
 /*  94 */ "maxrows ::= MAXROWS INTEGER",
 /*  95 */ "blocks ::= BLOCKS INTEGER",
 /*  96 */ "ctime ::= CTIME INTEGER",
 /*  97 */ "wal ::= WAL INTEGER",
 /*  98 */ "fsync ::= FSYNC INTEGER",
 /*  99 */ "comp ::= COMP INTEGER",
 /* 100 */ "prec ::= PRECISION STRING",
 /* 101 */ "update ::= UPDATE INTEGER",
 /* 102 */ "cachelast ::= CACHELAST INTEGER",
 /* 103 */ "partitions ::= PARTITIONS INTEGER",
 /* 104 */ "db_optr ::=",
 /* 105 */ "db_optr ::= db_optr cache",
 /* 106 */ "db_optr ::= db_optr replica",
 /* 107 */ "db_optr ::= db_optr quorum",
 /* 108 */ "db_optr ::= db_optr days",
 /* 109 */ "db_optr ::= db_optr minrows",
 /* 110 */ "db_optr ::= db_optr maxrows",
 /* 111 */ "db_optr ::= db_optr blocks",
 /* 112 */ "db_optr ::= db_optr ctime",
 /* 113 */ "db_optr ::= db_optr wal",
 /* 114 */ "db_optr ::= db_optr fsync",
 /* 115 */ "db_optr ::= db_optr comp",
 /* 116 */ "db_optr ::= db_optr prec",
 /* 117 */ "db_optr ::= db_optr keep",
 /* 118 */ "db_optr ::= db_optr update",
 /* 119 */ "db_optr ::= db_optr cachelast",
 /* 120 */ "topic_optr ::= db_optr",
 /* 121 */ "topic_optr ::= topic_optr partitions",
 /* 122 */ "alter_db_optr ::=",
 /* 123 */ "alter_db_optr ::= alter_db_optr replica",
 /* 124 */ "alter_db_optr ::= alter_db_optr quorum",
 /* 125 */ "alter_db_optr ::= alter_db_optr keep",
 /* 126 */ "alter_db_optr ::= alter_db_optr blocks",
 /* 127 */ "alter_db_optr ::= alter_db_optr comp",
 /* 128 */ "alter_db_optr ::= alter_db_optr update",
 /* 129 */ "alter_db_optr ::= alter_db_optr cachelast",
 /* 130 */ "alter_topic_optr ::= alter_db_optr",
 /* 131 */ "alter_topic_optr ::= alter_topic_optr partitions",
 /* 132 */ "typename ::= ids",
 /* 133 */ "typename ::= ids LP signed RP",
 /* 134 */ "typename ::= ids UNSIGNED",
 /* 135 */ "signed ::= INTEGER",
 /* 136 */ "signed ::= PLUS INTEGER",
 /* 137 */ "signed ::= MINUS INTEGER",
 /* 138 */ "cmd ::= CREATE TABLE create_table_args",
 /* 139 */ "cmd ::= CREATE TABLE create_stable_args",
 /* 140 */ "cmd ::= CREATE STABLE create_stable_args",
 /* 141 */ "cmd ::= CREATE TABLE create_table_list",
 /* 142 */ "create_table_list ::= create_from_stable",
 /* 143 */ "create_table_list ::= create_table_list create_from_stable",
 /* 144 */ "create_table_args ::= ifnotexists ids cpxName LP columnlist RP",
 /* 145 */ "create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP",
 /* 146 */ "create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP",
 /* 147 */ "create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP",
 /* 148 */ "tagNamelist ::= tagNamelist COMMA ids",
 /* 149 */ "tagNamelist ::= ids",
 /* 150 */ "create_table_args ::= ifnotexists ids cpxName AS select",
 /* 151 */ "columnlist ::= columnlist COMMA column",
 /* 152 */ "columnlist ::= column",
 /* 153 */ "column ::= ids typename",
 /* 154 */ "tagitemlist ::= tagitemlist COMMA tagitem",
 /* 155 */ "tagitemlist ::= tagitem",
 /* 156 */ "tagitem ::= INTEGER",
 /* 157 */ "tagitem ::= FLOAT",
 /* 158 */ "tagitem ::= STRING",
 /* 159 */ "tagitem ::= BOOL",
 /* 160 */ "tagitem ::= NULL",
 /* 161 */ "tagitem ::= NOW",
 /* 162 */ "tagitem ::= MINUS INTEGER",
 /* 163 */ "tagitem ::= MINUS FLOAT",
 /* 164 */ "tagitem ::= PLUS INTEGER",
 /* 165 */ "tagitem ::= PLUS FLOAT",
 /* 166 */ "select ::= SELECT selcollist from where_opt interval_opt session_option windowstate_option fill_opt sliding_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt",
 /* 167 */ "select ::= LP select RP",
 /* 168 */ "union ::= select",
 /* 169 */ "union ::= union UNION ALL select",
 /* 170 */ "cmd ::= union",
 /* 171 */ "select ::= SELECT selcollist",
 /* 172 */ "sclp ::= selcollist COMMA",
 /* 173 */ "sclp ::=",
 /* 174 */ "selcollist ::= sclp distinct expr as",
 /* 175 */ "selcollist ::= sclp STAR",
 /* 176 */ "as ::= AS ids",
 /* 177 */ "as ::= ids",
 /* 178 */ "as ::=",
 /* 179 */ "distinct ::= DISTINCT",
 /* 180 */ "distinct ::=",
 /* 181 */ "from ::= FROM tablelist",
 /* 182 */ "from ::= FROM sub",
 /* 183 */ "sub ::= LP union RP",
 /* 184 */ "sub ::= LP union RP ids",
 /* 185 */ "sub ::= sub COMMA LP union RP ids",
 /* 186 */ "tablelist ::= ids cpxName",
 /* 187 */ "tablelist ::= ids cpxName ids",
 /* 188 */ "tablelist ::= tablelist COMMA ids cpxName",
 /* 189 */ "tablelist ::= tablelist COMMA ids cpxName ids",
 /* 190 */ "tmvar ::= VARIABLE",
 /* 191 */ "interval_opt ::= INTERVAL LP tmvar RP",
 /* 192 */ "interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP",
 /* 193 */ "interval_opt ::=",
 /* 194 */ "session_option ::=",
 /* 195 */ "session_option ::= SESSION LP ids cpxName COMMA tmvar RP",
 /* 196 */ "windowstate_option ::=",
 /* 197 */ "windowstate_option ::= STATE_WINDOW LP ids RP",
 /* 198 */ "fill_opt ::=",
 /* 199 */ "fill_opt ::= FILL LP ID COMMA tagitemlist RP",
 /* 200 */ "fill_opt ::= FILL LP ID RP",
 /* 201 */ "sliding_opt ::= SLIDING LP tmvar RP",
 /* 202 */ "sliding_opt ::=",
 /* 203 */ "orderby_opt ::=",
 /* 204 */ "orderby_opt ::= ORDER BY sortlist",
 /* 205 */ "sortlist ::= sortlist COMMA item sortorder",
 /* 206 */ "sortlist ::= item sortorder",
 /* 207 */ "item ::= ids cpxName",
 /* 208 */ "sortorder ::= ASC",
 /* 209 */ "sortorder ::= DESC",
 /* 210 */ "sortorder ::=",
 /* 211 */ "groupby_opt ::=",
 /* 212 */ "groupby_opt ::= GROUP BY grouplist",
 /* 213 */ "grouplist ::= grouplist COMMA item",
 /* 214 */ "grouplist ::= item",
 /* 215 */ "having_opt ::=",
 /* 216 */ "having_opt ::= HAVING expr",
 /* 217 */ "limit_opt ::=",
 /* 218 */ "limit_opt ::= LIMIT signed",
 /* 219 */ "limit_opt ::= LIMIT signed OFFSET signed",
 /* 220 */ "limit_opt ::= LIMIT signed COMMA signed",
 /* 221 */ "slimit_opt ::=",
 /* 222 */ "slimit_opt ::= SLIMIT signed",
 /* 223 */ "slimit_opt ::= SLIMIT signed SOFFSET signed",
 /* 224 */ "slimit_opt ::= SLIMIT signed COMMA signed",
 /* 225 */ "where_opt ::=",
 /* 226 */ "where_opt ::= WHERE expr",
 /* 227 */ "expr ::= LP expr RP",
 /* 228 */ "expr ::= ID",
 /* 229 */ "expr ::= ID DOT ID",
 /* 230 */ "expr ::= ID DOT STAR",
 /* 231 */ "expr ::= INTEGER",
 /* 232 */ "expr ::= MINUS INTEGER",
 /* 233 */ "expr ::= PLUS INTEGER",
 /* 234 */ "expr ::= FLOAT",
 /* 235 */ "expr ::= MINUS FLOAT",
 /* 236 */ "expr ::= PLUS FLOAT",
 /* 237 */ "expr ::= STRING",
 /* 238 */ "expr ::= NOW",
 /* 239 */ "expr ::= VARIABLE",
 /* 240 */ "expr ::= PLUS VARIABLE",
 /* 241 */ "expr ::= MINUS VARIABLE",
 /* 242 */ "expr ::= BOOL",
 /* 243 */ "expr ::= NULL",
 /* 244 */ "expr ::= ID LP exprlist RP",
 /* 245 */ "expr ::= ID LP STAR RP",
 /* 246 */ "expr ::= expr IS NULL",
 /* 247 */ "expr ::= expr IS NOT NULL",
 /* 248 */ "expr ::= expr LT expr",
 /* 249 */ "expr ::= expr GT expr",
 /* 250 */ "expr ::= expr LE expr",
 /* 251 */ "expr ::= expr GE expr",
 /* 252 */ "expr ::= expr NE expr",
 /* 253 */ "expr ::= expr EQ expr",
 /* 254 */ "expr ::= expr BETWEEN expr AND expr",
 /* 255 */ "expr ::= expr AND expr",
 /* 256 */ "expr ::= expr OR expr",
 /* 257 */ "expr ::= expr PLUS expr",
 /* 258 */ "expr ::= expr MINUS expr",
 /* 259 */ "expr ::= expr STAR expr",
 /* 260 */ "expr ::= expr SLASH expr",
 /* 261 */ "expr ::= expr REM expr",
 /* 262 */ "expr ::= expr LIKE expr",
 /* 263 */ "expr ::= expr IN LP exprlist RP",
 /* 264 */ "exprlist ::= exprlist COMMA expritem",
 /* 265 */ "exprlist ::= expritem",
 /* 266 */ "expritem ::= expr",
 /* 267 */ "expritem ::=",
 /* 268 */ "cmd ::= RESET QUERY CACHE",
 /* 269 */ "cmd ::= SYNCDB ids REPLICA",
 /* 270 */ "cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist",
 /* 271 */ "cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids",
 /* 272 */ "cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist",
 /* 273 */ "cmd ::= ALTER TABLE ids cpxName DEATCH",
 /* 274 */ "cmd ::= ALTER TABLE ids cpxName ATTACH TO ids cpxName",
 /* 275 */ "cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist",
 /* 276 */ "cmd ::= ALTER TABLE ids cpxName DROP TAG ids",
 /* 277 */ "cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids",
 /* 278 */ "cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem",
 /* 279 */ "cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist",
 /* 280 */ "cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist",
 /* 281 */ "cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids",
 /* 282 */ "cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist",
 /* 283 */ "cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist",
 /* 284 */ "cmd ::= ALTER STABLE ids cpxName DROP TAG ids",
 /* 285 */ "cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids",
 /* 286 */ "cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem",
 /* 287 */ "cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist",
 /* 288 */ "cmd ::= KILL CONNECTION INTEGER",
 /* 289 */ "cmd ::= KILL STREAM INTEGER COLON INTEGER",
 /* 290 */ "cmd ::= KILL QUERY INTEGER COLON INTEGER",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypRawParser ParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ParseCTX_STORE
    ParseInit(yypParser ParseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH
  ParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 206: /* exprlist */
    case 250: /* selcollist */
    case 264: /* sclp */
{
#line 750 "../inc/sql.y"
tSqlExprListDestroy((yypminor->yy403));
#line 1513 "../inc/sql.c"
}
      break;
    case 221: /* intitemlist */
    case 223: /* keep */
    case 244: /* columnlist */
    case 245: /* tagitemlist */
    case 246: /* tagNamelist */
    case 256: /* fill_opt */
    case 258: /* groupby_opt */
    case 260: /* orderby_opt */
    case 271: /* sortlist */
    case 275: /* grouplist */
{
#line 253 "../inc/sql.y"
taosArrayDestroy((yypminor->yy403));
#line 1529 "../inc/sql.c"
}
      break;
    case 242: /* create_table_list */
{
#line 361 "../inc/sql.y"
destroyCreateTableSql((yypminor->yy56));
#line 1536 "../inc/sql.c"
}
      break;
    case 247: /* select */
{
#line 481 "../inc/sql.y"
destroySqlNode((yypminor->yy224));
#line 1543 "../inc/sql.c"
}
      break;
    case 251: /* from */
    case 268: /* tablelist */
    case 269: /* sub */
{
#line 536 "../inc/sql.y"
destroyRelationInfo((yypminor->yy114));
#line 1552 "../inc/sql.c"
}
      break;
    case 252: /* where_opt */
    case 259: /* having_opt */
    case 266: /* expr */
    case 276: /* expritem */
{
#line 683 "../inc/sql.y"
tSqlExprDestroy((yypminor->yy260));
#line 1562 "../inc/sql.c"
}
      break;
    case 263: /* union */
{
#line 489 "../inc/sql.y"
destroyAllSqlNode((yypminor->yy403));
#line 1569 "../inc/sql.c"
}
      break;
    case 272: /* sortitem */
{
#line 616 "../inc/sql.y"
tVariantDestroy(&(yypminor->yy488));
#line 1576 "../inc/sql.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    assert( i<=YY_ACTTAB_COUNT );
    assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    assert( i<(int)YY_NLOOKAHEAD );
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      assert( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0]) );
      iFallback = yyFallback[iLookAhead];
      if( iFallback!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        assert( j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) );
        if( yy_lookahead[j]==YYWILDCARD && iLookAhead>0 ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      assert( i>=0 && i<sizeof(yy_action)/sizeof(yy_action[0]) );
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH
   ParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
   197,  /* (0) program ::= cmd */
   198,  /* (1) cmd ::= SHOW DATABASES */
   198,  /* (2) cmd ::= SHOW TOPICS */
   198,  /* (3) cmd ::= SHOW FUNCTIONS */
   198,  /* (4) cmd ::= SHOW MNODES */
   198,  /* (5) cmd ::= SHOW DNODES */
   198,  /* (6) cmd ::= SHOW ACCOUNTS */
   198,  /* (7) cmd ::= SHOW USERS */
   198,  /* (8) cmd ::= SHOW MODULES */
   198,  /* (9) cmd ::= SHOW QUERIES */
   198,  /* (10) cmd ::= SHOW CONNECTIONS */
   198,  /* (11) cmd ::= SHOW STREAMS */
   198,  /* (12) cmd ::= SHOW VARIABLES */
   198,  /* (13) cmd ::= SHOW SCORES */
   198,  /* (14) cmd ::= SHOW GRANTS */
   198,  /* (15) cmd ::= SHOW VNODES */
   198,  /* (16) cmd ::= SHOW VNODES IPTOKEN */
   199,  /* (17) dbPrefix ::= */
   199,  /* (18) dbPrefix ::= ids DOT */
   201,  /* (19) cpxName ::= */
   201,  /* (20) cpxName ::= DOT ids */
   198,  /* (21) cmd ::= SHOW CREATE TABLE ids cpxName */
   198,  /* (22) cmd ::= SHOW CREATE STABLE ids cpxName */
   198,  /* (23) cmd ::= SHOW CREATE DATABASE ids */
   198,  /* (24) cmd ::= SHOW dbPrefix TABLES */
   198,  /* (25) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   198,  /* (26) cmd ::= SHOW dbPrefix STABLES */
   198,  /* (27) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   198,  /* (28) cmd ::= SHOW dbPrefix VGROUPS */
   198,  /* (29) cmd ::= SHOW dbPrefix VGROUPS ids */
   198,  /* (30) cmd ::= DROP TABLE ifexists ids cpxName */
   198,  /* (31) cmd ::= DROP STABLE ifexists ids cpxName */
   198,  /* (32) cmd ::= DROP DATABASE ifexists ids */
   198,  /* (33) cmd ::= DROP TOPIC ifexists ids */
   198,  /* (34) cmd ::= DROP FUNCTION ids */
   198,  /* (35) cmd ::= DROP DNODE ids */
   198,  /* (36) cmd ::= DROP USER ids */
   198,  /* (37) cmd ::= DROP ACCOUNT ids */
   198,  /* (38) cmd ::= USE ids */
   198,  /* (39) cmd ::= DESCRIBE ids cpxName */
   198,  /* (40) cmd ::= ALTER USER ids PASS ids */
   198,  /* (41) cmd ::= ALTER USER ids PRIVILEGE ids */
   198,  /* (42) cmd ::= ALTER DNODE ids ids */
   198,  /* (43) cmd ::= ALTER DNODE ids ids ids */
   198,  /* (44) cmd ::= ALTER LOCAL ids */
   198,  /* (45) cmd ::= ALTER LOCAL ids ids */
   198,  /* (46) cmd ::= ALTER DATABASE ids alter_db_optr */
   198,  /* (47) cmd ::= ALTER TOPIC ids alter_topic_optr */
   198,  /* (48) cmd ::= ALTER ACCOUNT ids acct_optr */
   198,  /* (49) cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
   198,  /* (50) cmd ::= COMPACT VNODES IN LP exprlist RP */
   200,  /* (51) ids ::= ID */
   200,  /* (52) ids ::= STRING */
   202,  /* (53) ifexists ::= IF EXISTS */
   202,  /* (54) ifexists ::= */
   207,  /* (55) ifnotexists ::= IF NOT EXISTS */
   207,  /* (56) ifnotexists ::= */
   198,  /* (57) cmd ::= CREATE DNODE ids */
   198,  /* (58) cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
   198,  /* (59) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   198,  /* (60) cmd ::= CREATE TOPIC ifnotexists ids topic_optr */
   198,  /* (61) cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
   198,  /* (62) cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
   198,  /* (63) cmd ::= CREATE USER ids PASS ids */
   211,  /* (64) bufsize ::= */
   211,  /* (65) bufsize ::= BUFSIZE INTEGER */
   212,  /* (66) pps ::= */
   212,  /* (67) pps ::= PPS INTEGER */
   213,  /* (68) tseries ::= */
   213,  /* (69) tseries ::= TSERIES INTEGER */
   214,  /* (70) dbs ::= */
   214,  /* (71) dbs ::= DBS INTEGER */
   215,  /* (72) streams ::= */
   215,  /* (73) streams ::= STREAMS INTEGER */
   216,  /* (74) storage ::= */
   216,  /* (75) storage ::= STORAGE INTEGER */
   217,  /* (76) qtime ::= */
   217,  /* (77) qtime ::= QTIME INTEGER */
   218,  /* (78) users ::= */
   218,  /* (79) users ::= USERS INTEGER */
   219,  /* (80) conns ::= */
   219,  /* (81) conns ::= CONNS INTEGER */
   220,  /* (82) state ::= */
   220,  /* (83) state ::= STATE ids */
   205,  /* (84) acct_optr ::= pps tseries storage streams qtime dbs users conns state */
   221,  /* (85) intitemlist ::= intitemlist COMMA intitem */
   221,  /* (86) intitemlist ::= intitem */
   222,  /* (87) intitem ::= INTEGER */
   223,  /* (88) keep ::= KEEP intitemlist */
   224,  /* (89) cache ::= CACHE INTEGER */
   225,  /* (90) replica ::= REPLICA INTEGER */
   226,  /* (91) quorum ::= QUORUM INTEGER */
   227,  /* (92) days ::= DAYS INTEGER */
   228,  /* (93) minrows ::= MINROWS INTEGER */
   229,  /* (94) maxrows ::= MAXROWS INTEGER */
   230,  /* (95) blocks ::= BLOCKS INTEGER */
   231,  /* (96) ctime ::= CTIME INTEGER */
   232,  /* (97) wal ::= WAL INTEGER */
   233,  /* (98) fsync ::= FSYNC INTEGER */
   234,  /* (99) comp ::= COMP INTEGER */
   235,  /* (100) prec ::= PRECISION STRING */
   236,  /* (101) update ::= UPDATE INTEGER */
   237,  /* (102) cachelast ::= CACHELAST INTEGER */
   238,  /* (103) partitions ::= PARTITIONS INTEGER */
   208,  /* (104) db_optr ::= */
   208,  /* (105) db_optr ::= db_optr cache */
   208,  /* (106) db_optr ::= db_optr replica */
   208,  /* (107) db_optr ::= db_optr quorum */
   208,  /* (108) db_optr ::= db_optr days */
   208,  /* (109) db_optr ::= db_optr minrows */
   208,  /* (110) db_optr ::= db_optr maxrows */
   208,  /* (111) db_optr ::= db_optr blocks */
   208,  /* (112) db_optr ::= db_optr ctime */
   208,  /* (113) db_optr ::= db_optr wal */
   208,  /* (114) db_optr ::= db_optr fsync */
   208,  /* (115) db_optr ::= db_optr comp */
   208,  /* (116) db_optr ::= db_optr prec */
   208,  /* (117) db_optr ::= db_optr keep */
   208,  /* (118) db_optr ::= db_optr update */
   208,  /* (119) db_optr ::= db_optr cachelast */
   209,  /* (120) topic_optr ::= db_optr */
   209,  /* (121) topic_optr ::= topic_optr partitions */
   203,  /* (122) alter_db_optr ::= */
   203,  /* (123) alter_db_optr ::= alter_db_optr replica */
   203,  /* (124) alter_db_optr ::= alter_db_optr quorum */
   203,  /* (125) alter_db_optr ::= alter_db_optr keep */
   203,  /* (126) alter_db_optr ::= alter_db_optr blocks */
   203,  /* (127) alter_db_optr ::= alter_db_optr comp */
   203,  /* (128) alter_db_optr ::= alter_db_optr update */
   203,  /* (129) alter_db_optr ::= alter_db_optr cachelast */
   204,  /* (130) alter_topic_optr ::= alter_db_optr */
   204,  /* (131) alter_topic_optr ::= alter_topic_optr partitions */
   210,  /* (132) typename ::= ids */
   210,  /* (133) typename ::= ids LP signed RP */
   210,  /* (134) typename ::= ids UNSIGNED */
   239,  /* (135) signed ::= INTEGER */
   239,  /* (136) signed ::= PLUS INTEGER */
   239,  /* (137) signed ::= MINUS INTEGER */
   198,  /* (138) cmd ::= CREATE TABLE create_table_args */
   198,  /* (139) cmd ::= CREATE TABLE create_stable_args */
   198,  /* (140) cmd ::= CREATE STABLE create_stable_args */
   198,  /* (141) cmd ::= CREATE TABLE create_table_list */
   242,  /* (142) create_table_list ::= create_from_stable */
   242,  /* (143) create_table_list ::= create_table_list create_from_stable */
   240,  /* (144) create_table_args ::= ifnotexists ids cpxName LP columnlist RP */
   241,  /* (145) create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP */
   243,  /* (146) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP */
   243,  /* (147) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP */
   246,  /* (148) tagNamelist ::= tagNamelist COMMA ids */
   246,  /* (149) tagNamelist ::= ids */
   240,  /* (150) create_table_args ::= ifnotexists ids cpxName AS select */
   244,  /* (151) columnlist ::= columnlist COMMA column */
   244,  /* (152) columnlist ::= column */
   248,  /* (153) column ::= ids typename */
   245,  /* (154) tagitemlist ::= tagitemlist COMMA tagitem */
   245,  /* (155) tagitemlist ::= tagitem */
   249,  /* (156) tagitem ::= INTEGER */
   249,  /* (157) tagitem ::= FLOAT */
   249,  /* (158) tagitem ::= STRING */
   249,  /* (159) tagitem ::= BOOL */
   249,  /* (160) tagitem ::= NULL */
   249,  /* (161) tagitem ::= NOW */
   249,  /* (162) tagitem ::= MINUS INTEGER */
   249,  /* (163) tagitem ::= MINUS FLOAT */
   249,  /* (164) tagitem ::= PLUS INTEGER */
   249,  /* (165) tagitem ::= PLUS FLOAT */
   247,  /* (166) select ::= SELECT selcollist from where_opt interval_opt session_option windowstate_option fill_opt sliding_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt */
   247,  /* (167) select ::= LP select RP */
   263,  /* (168) union ::= select */
   263,  /* (169) union ::= union UNION ALL select */
   198,  /* (170) cmd ::= union */
   247,  /* (171) select ::= SELECT selcollist */
   264,  /* (172) sclp ::= selcollist COMMA */
   264,  /* (173) sclp ::= */
   250,  /* (174) selcollist ::= sclp distinct expr as */
   250,  /* (175) selcollist ::= sclp STAR */
   267,  /* (176) as ::= AS ids */
   267,  /* (177) as ::= ids */
   267,  /* (178) as ::= */
   265,  /* (179) distinct ::= DISTINCT */
   265,  /* (180) distinct ::= */
   251,  /* (181) from ::= FROM tablelist */
   251,  /* (182) from ::= FROM sub */
   269,  /* (183) sub ::= LP union RP */
   269,  /* (184) sub ::= LP union RP ids */
   269,  /* (185) sub ::= sub COMMA LP union RP ids */
   268,  /* (186) tablelist ::= ids cpxName */
   268,  /* (187) tablelist ::= ids cpxName ids */
   268,  /* (188) tablelist ::= tablelist COMMA ids cpxName */
   268,  /* (189) tablelist ::= tablelist COMMA ids cpxName ids */
   270,  /* (190) tmvar ::= VARIABLE */
   253,  /* (191) interval_opt ::= INTERVAL LP tmvar RP */
   253,  /* (192) interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
   253,  /* (193) interval_opt ::= */
   254,  /* (194) session_option ::= */
   254,  /* (195) session_option ::= SESSION LP ids cpxName COMMA tmvar RP */
   255,  /* (196) windowstate_option ::= */
   255,  /* (197) windowstate_option ::= STATE_WINDOW LP ids RP */
   256,  /* (198) fill_opt ::= */
   256,  /* (199) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   256,  /* (200) fill_opt ::= FILL LP ID RP */
   257,  /* (201) sliding_opt ::= SLIDING LP tmvar RP */
   257,  /* (202) sliding_opt ::= */
   260,  /* (203) orderby_opt ::= */
   260,  /* (204) orderby_opt ::= ORDER BY sortlist */
   271,  /* (205) sortlist ::= sortlist COMMA item sortorder */
   271,  /* (206) sortlist ::= item sortorder */
   273,  /* (207) item ::= ids cpxName */
   274,  /* (208) sortorder ::= ASC */
   274,  /* (209) sortorder ::= DESC */
   274,  /* (210) sortorder ::= */
   258,  /* (211) groupby_opt ::= */
   258,  /* (212) groupby_opt ::= GROUP BY grouplist */
   275,  /* (213) grouplist ::= grouplist COMMA item */
   275,  /* (214) grouplist ::= item */
   259,  /* (215) having_opt ::= */
   259,  /* (216) having_opt ::= HAVING expr */
   262,  /* (217) limit_opt ::= */
   262,  /* (218) limit_opt ::= LIMIT signed */
   262,  /* (219) limit_opt ::= LIMIT signed OFFSET signed */
   262,  /* (220) limit_opt ::= LIMIT signed COMMA signed */
   261,  /* (221) slimit_opt ::= */
   261,  /* (222) slimit_opt ::= SLIMIT signed */
   261,  /* (223) slimit_opt ::= SLIMIT signed SOFFSET signed */
   261,  /* (224) slimit_opt ::= SLIMIT signed COMMA signed */
   252,  /* (225) where_opt ::= */
   252,  /* (226) where_opt ::= WHERE expr */
   266,  /* (227) expr ::= LP expr RP */
   266,  /* (228) expr ::= ID */
   266,  /* (229) expr ::= ID DOT ID */
   266,  /* (230) expr ::= ID DOT STAR */
   266,  /* (231) expr ::= INTEGER */
   266,  /* (232) expr ::= MINUS INTEGER */
   266,  /* (233) expr ::= PLUS INTEGER */
   266,  /* (234) expr ::= FLOAT */
   266,  /* (235) expr ::= MINUS FLOAT */
   266,  /* (236) expr ::= PLUS FLOAT */
   266,  /* (237) expr ::= STRING */
   266,  /* (238) expr ::= NOW */
   266,  /* (239) expr ::= VARIABLE */
   266,  /* (240) expr ::= PLUS VARIABLE */
   266,  /* (241) expr ::= MINUS VARIABLE */
   266,  /* (242) expr ::= BOOL */
   266,  /* (243) expr ::= NULL */
   266,  /* (244) expr ::= ID LP exprlist RP */
   266,  /* (245) expr ::= ID LP STAR RP */
   266,  /* (246) expr ::= expr IS NULL */
   266,  /* (247) expr ::= expr IS NOT NULL */
   266,  /* (248) expr ::= expr LT expr */
   266,  /* (249) expr ::= expr GT expr */
   266,  /* (250) expr ::= expr LE expr */
   266,  /* (251) expr ::= expr GE expr */
   266,  /* (252) expr ::= expr NE expr */
   266,  /* (253) expr ::= expr EQ expr */
   266,  /* (254) expr ::= expr BETWEEN expr AND expr */
   266,  /* (255) expr ::= expr AND expr */
   266,  /* (256) expr ::= expr OR expr */
   266,  /* (257) expr ::= expr PLUS expr */
   266,  /* (258) expr ::= expr MINUS expr */
   266,  /* (259) expr ::= expr STAR expr */
   266,  /* (260) expr ::= expr SLASH expr */
   266,  /* (261) expr ::= expr REM expr */
   266,  /* (262) expr ::= expr LIKE expr */
   266,  /* (263) expr ::= expr IN LP exprlist RP */
   206,  /* (264) exprlist ::= exprlist COMMA expritem */
   206,  /* (265) exprlist ::= expritem */
   276,  /* (266) expritem ::= expr */
   276,  /* (267) expritem ::= */
   198,  /* (268) cmd ::= RESET QUERY CACHE */
   198,  /* (269) cmd ::= SYNCDB ids REPLICA */
   198,  /* (270) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   198,  /* (271) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   198,  /* (272) cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist */
   198,  /* (273) cmd ::= ALTER TABLE ids cpxName DEATCH */
   198,  /* (274) cmd ::= ALTER TABLE ids cpxName ATTACH TO ids cpxName */
   198,  /* (275) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   198,  /* (276) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   198,  /* (277) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   198,  /* (278) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   198,  /* (279) cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist */
   198,  /* (280) cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist */
   198,  /* (281) cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids */
   198,  /* (282) cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist */
   198,  /* (283) cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist */
   198,  /* (284) cmd ::= ALTER STABLE ids cpxName DROP TAG ids */
   198,  /* (285) cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids */
   198,  /* (286) cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem */
   198,  /* (287) cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist */
   198,  /* (288) cmd ::= KILL CONNECTION INTEGER */
   198,  /* (289) cmd ::= KILL STREAM INTEGER COLON INTEGER */
   198,  /* (290) cmd ::= KILL QUERY INTEGER COLON INTEGER */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -1,  /* (0) program ::= cmd */
   -2,  /* (1) cmd ::= SHOW DATABASES */
   -2,  /* (2) cmd ::= SHOW TOPICS */
   -2,  /* (3) cmd ::= SHOW FUNCTIONS */
   -2,  /* (4) cmd ::= SHOW MNODES */
   -2,  /* (5) cmd ::= SHOW DNODES */
   -2,  /* (6) cmd ::= SHOW ACCOUNTS */
   -2,  /* (7) cmd ::= SHOW USERS */
   -2,  /* (8) cmd ::= SHOW MODULES */
   -2,  /* (9) cmd ::= SHOW QUERIES */
   -2,  /* (10) cmd ::= SHOW CONNECTIONS */
   -2,  /* (11) cmd ::= SHOW STREAMS */
   -2,  /* (12) cmd ::= SHOW VARIABLES */
   -2,  /* (13) cmd ::= SHOW SCORES */
   -2,  /* (14) cmd ::= SHOW GRANTS */
   -2,  /* (15) cmd ::= SHOW VNODES */
   -3,  /* (16) cmd ::= SHOW VNODES IPTOKEN */
    0,  /* (17) dbPrefix ::= */
   -2,  /* (18) dbPrefix ::= ids DOT */
    0,  /* (19) cpxName ::= */
   -2,  /* (20) cpxName ::= DOT ids */
   -5,  /* (21) cmd ::= SHOW CREATE TABLE ids cpxName */
   -5,  /* (22) cmd ::= SHOW CREATE STABLE ids cpxName */
   -4,  /* (23) cmd ::= SHOW CREATE DATABASE ids */
   -3,  /* (24) cmd ::= SHOW dbPrefix TABLES */
   -5,  /* (25) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   -3,  /* (26) cmd ::= SHOW dbPrefix STABLES */
   -5,  /* (27) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   -3,  /* (28) cmd ::= SHOW dbPrefix VGROUPS */
   -4,  /* (29) cmd ::= SHOW dbPrefix VGROUPS ids */
   -5,  /* (30) cmd ::= DROP TABLE ifexists ids cpxName */
   -5,  /* (31) cmd ::= DROP STABLE ifexists ids cpxName */
   -4,  /* (32) cmd ::= DROP DATABASE ifexists ids */
   -4,  /* (33) cmd ::= DROP TOPIC ifexists ids */
   -3,  /* (34) cmd ::= DROP FUNCTION ids */
   -3,  /* (35) cmd ::= DROP DNODE ids */
   -3,  /* (36) cmd ::= DROP USER ids */
   -3,  /* (37) cmd ::= DROP ACCOUNT ids */
   -2,  /* (38) cmd ::= USE ids */
   -3,  /* (39) cmd ::= DESCRIBE ids cpxName */
   -5,  /* (40) cmd ::= ALTER USER ids PASS ids */
   -5,  /* (41) cmd ::= ALTER USER ids PRIVILEGE ids */
   -4,  /* (42) cmd ::= ALTER DNODE ids ids */
   -5,  /* (43) cmd ::= ALTER DNODE ids ids ids */
   -3,  /* (44) cmd ::= ALTER LOCAL ids */
   -4,  /* (45) cmd ::= ALTER LOCAL ids ids */
   -4,  /* (46) cmd ::= ALTER DATABASE ids alter_db_optr */
   -4,  /* (47) cmd ::= ALTER TOPIC ids alter_topic_optr */
   -4,  /* (48) cmd ::= ALTER ACCOUNT ids acct_optr */
   -6,  /* (49) cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
   -6,  /* (50) cmd ::= COMPACT VNODES IN LP exprlist RP */
   -1,  /* (51) ids ::= ID */
   -1,  /* (52) ids ::= STRING */
   -2,  /* (53) ifexists ::= IF EXISTS */
    0,  /* (54) ifexists ::= */
   -3,  /* (55) ifnotexists ::= IF NOT EXISTS */
    0,  /* (56) ifnotexists ::= */
   -3,  /* (57) cmd ::= CREATE DNODE ids */
   -6,  /* (58) cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
   -5,  /* (59) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   -5,  /* (60) cmd ::= CREATE TOPIC ifnotexists ids topic_optr */
   -8,  /* (61) cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
   -9,  /* (62) cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
   -5,  /* (63) cmd ::= CREATE USER ids PASS ids */
    0,  /* (64) bufsize ::= */
   -2,  /* (65) bufsize ::= BUFSIZE INTEGER */
    0,  /* (66) pps ::= */
   -2,  /* (67) pps ::= PPS INTEGER */
    0,  /* (68) tseries ::= */
   -2,  /* (69) tseries ::= TSERIES INTEGER */
    0,  /* (70) dbs ::= */
   -2,  /* (71) dbs ::= DBS INTEGER */
    0,  /* (72) streams ::= */
   -2,  /* (73) streams ::= STREAMS INTEGER */
    0,  /* (74) storage ::= */
   -2,  /* (75) storage ::= STORAGE INTEGER */
    0,  /* (76) qtime ::= */
   -2,  /* (77) qtime ::= QTIME INTEGER */
    0,  /* (78) users ::= */
   -2,  /* (79) users ::= USERS INTEGER */
    0,  /* (80) conns ::= */
   -2,  /* (81) conns ::= CONNS INTEGER */
    0,  /* (82) state ::= */
   -2,  /* (83) state ::= STATE ids */
   -9,  /* (84) acct_optr ::= pps tseries storage streams qtime dbs users conns state */
   -3,  /* (85) intitemlist ::= intitemlist COMMA intitem */
   -1,  /* (86) intitemlist ::= intitem */
   -1,  /* (87) intitem ::= INTEGER */
   -2,  /* (88) keep ::= KEEP intitemlist */
   -2,  /* (89) cache ::= CACHE INTEGER */
   -2,  /* (90) replica ::= REPLICA INTEGER */
   -2,  /* (91) quorum ::= QUORUM INTEGER */
   -2,  /* (92) days ::= DAYS INTEGER */
   -2,  /* (93) minrows ::= MINROWS INTEGER */
   -2,  /* (94) maxrows ::= MAXROWS INTEGER */
   -2,  /* (95) blocks ::= BLOCKS INTEGER */
   -2,  /* (96) ctime ::= CTIME INTEGER */
   -2,  /* (97) wal ::= WAL INTEGER */
   -2,  /* (98) fsync ::= FSYNC INTEGER */
   -2,  /* (99) comp ::= COMP INTEGER */
   -2,  /* (100) prec ::= PRECISION STRING */
   -2,  /* (101) update ::= UPDATE INTEGER */
   -2,  /* (102) cachelast ::= CACHELAST INTEGER */
   -2,  /* (103) partitions ::= PARTITIONS INTEGER */
    0,  /* (104) db_optr ::= */
   -2,  /* (105) db_optr ::= db_optr cache */
   -2,  /* (106) db_optr ::= db_optr replica */
   -2,  /* (107) db_optr ::= db_optr quorum */
   -2,  /* (108) db_optr ::= db_optr days */
   -2,  /* (109) db_optr ::= db_optr minrows */
   -2,  /* (110) db_optr ::= db_optr maxrows */
   -2,  /* (111) db_optr ::= db_optr blocks */
   -2,  /* (112) db_optr ::= db_optr ctime */
   -2,  /* (113) db_optr ::= db_optr wal */
   -2,  /* (114) db_optr ::= db_optr fsync */
   -2,  /* (115) db_optr ::= db_optr comp */
   -2,  /* (116) db_optr ::= db_optr prec */
   -2,  /* (117) db_optr ::= db_optr keep */
   -2,  /* (118) db_optr ::= db_optr update */
   -2,  /* (119) db_optr ::= db_optr cachelast */
   -1,  /* (120) topic_optr ::= db_optr */
   -2,  /* (121) topic_optr ::= topic_optr partitions */
    0,  /* (122) alter_db_optr ::= */
   -2,  /* (123) alter_db_optr ::= alter_db_optr replica */
   -2,  /* (124) alter_db_optr ::= alter_db_optr quorum */
   -2,  /* (125) alter_db_optr ::= alter_db_optr keep */
   -2,  /* (126) alter_db_optr ::= alter_db_optr blocks */
   -2,  /* (127) alter_db_optr ::= alter_db_optr comp */
   -2,  /* (128) alter_db_optr ::= alter_db_optr update */
   -2,  /* (129) alter_db_optr ::= alter_db_optr cachelast */
   -1,  /* (130) alter_topic_optr ::= alter_db_optr */
   -2,  /* (131) alter_topic_optr ::= alter_topic_optr partitions */
   -1,  /* (132) typename ::= ids */
   -4,  /* (133) typename ::= ids LP signed RP */
   -2,  /* (134) typename ::= ids UNSIGNED */
   -1,  /* (135) signed ::= INTEGER */
   -2,  /* (136) signed ::= PLUS INTEGER */
   -2,  /* (137) signed ::= MINUS INTEGER */
   -3,  /* (138) cmd ::= CREATE TABLE create_table_args */
   -3,  /* (139) cmd ::= CREATE TABLE create_stable_args */
   -3,  /* (140) cmd ::= CREATE STABLE create_stable_args */
   -3,  /* (141) cmd ::= CREATE TABLE create_table_list */
   -1,  /* (142) create_table_list ::= create_from_stable */
   -2,  /* (143) create_table_list ::= create_table_list create_from_stable */
   -6,  /* (144) create_table_args ::= ifnotexists ids cpxName LP columnlist RP */
  -10,  /* (145) create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP */
  -10,  /* (146) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP */
  -13,  /* (147) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP */
   -3,  /* (148) tagNamelist ::= tagNamelist COMMA ids */
   -1,  /* (149) tagNamelist ::= ids */
   -5,  /* (150) create_table_args ::= ifnotexists ids cpxName AS select */
   -3,  /* (151) columnlist ::= columnlist COMMA column */
   -1,  /* (152) columnlist ::= column */
   -2,  /* (153) column ::= ids typename */
   -3,  /* (154) tagitemlist ::= tagitemlist COMMA tagitem */
   -1,  /* (155) tagitemlist ::= tagitem */
   -1,  /* (156) tagitem ::= INTEGER */
   -1,  /* (157) tagitem ::= FLOAT */
   -1,  /* (158) tagitem ::= STRING */
   -1,  /* (159) tagitem ::= BOOL */
   -1,  /* (160) tagitem ::= NULL */
   -1,  /* (161) tagitem ::= NOW */
   -2,  /* (162) tagitem ::= MINUS INTEGER */
   -2,  /* (163) tagitem ::= MINUS FLOAT */
   -2,  /* (164) tagitem ::= PLUS INTEGER */
   -2,  /* (165) tagitem ::= PLUS FLOAT */
  -14,  /* (166) select ::= SELECT selcollist from where_opt interval_opt session_option windowstate_option fill_opt sliding_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt */
   -3,  /* (167) select ::= LP select RP */
   -1,  /* (168) union ::= select */
   -4,  /* (169) union ::= union UNION ALL select */
   -1,  /* (170) cmd ::= union */
   -2,  /* (171) select ::= SELECT selcollist */
   -2,  /* (172) sclp ::= selcollist COMMA */
    0,  /* (173) sclp ::= */
   -4,  /* (174) selcollist ::= sclp distinct expr as */
   -2,  /* (175) selcollist ::= sclp STAR */
   -2,  /* (176) as ::= AS ids */
   -1,  /* (177) as ::= ids */
    0,  /* (178) as ::= */
   -1,  /* (179) distinct ::= DISTINCT */
    0,  /* (180) distinct ::= */
   -2,  /* (181) from ::= FROM tablelist */
   -2,  /* (182) from ::= FROM sub */
   -3,  /* (183) sub ::= LP union RP */
   -4,  /* (184) sub ::= LP union RP ids */
   -6,  /* (185) sub ::= sub COMMA LP union RP ids */
   -2,  /* (186) tablelist ::= ids cpxName */
   -3,  /* (187) tablelist ::= ids cpxName ids */
   -4,  /* (188) tablelist ::= tablelist COMMA ids cpxName */
   -5,  /* (189) tablelist ::= tablelist COMMA ids cpxName ids */
   -1,  /* (190) tmvar ::= VARIABLE */
   -4,  /* (191) interval_opt ::= INTERVAL LP tmvar RP */
   -6,  /* (192) interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
    0,  /* (193) interval_opt ::= */
    0,  /* (194) session_option ::= */
   -7,  /* (195) session_option ::= SESSION LP ids cpxName COMMA tmvar RP */
    0,  /* (196) windowstate_option ::= */
   -4,  /* (197) windowstate_option ::= STATE_WINDOW LP ids RP */
    0,  /* (198) fill_opt ::= */
   -6,  /* (199) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   -4,  /* (200) fill_opt ::= FILL LP ID RP */
   -4,  /* (201) sliding_opt ::= SLIDING LP tmvar RP */
    0,  /* (202) sliding_opt ::= */
    0,  /* (203) orderby_opt ::= */
   -3,  /* (204) orderby_opt ::= ORDER BY sortlist */
   -4,  /* (205) sortlist ::= sortlist COMMA item sortorder */
   -2,  /* (206) sortlist ::= item sortorder */
   -2,  /* (207) item ::= ids cpxName */
   -1,  /* (208) sortorder ::= ASC */
   -1,  /* (209) sortorder ::= DESC */
    0,  /* (210) sortorder ::= */
    0,  /* (211) groupby_opt ::= */
   -3,  /* (212) groupby_opt ::= GROUP BY grouplist */
   -3,  /* (213) grouplist ::= grouplist COMMA item */
   -1,  /* (214) grouplist ::= item */
    0,  /* (215) having_opt ::= */
   -2,  /* (216) having_opt ::= HAVING expr */
    0,  /* (217) limit_opt ::= */
   -2,  /* (218) limit_opt ::= LIMIT signed */
   -4,  /* (219) limit_opt ::= LIMIT signed OFFSET signed */
   -4,  /* (220) limit_opt ::= LIMIT signed COMMA signed */
    0,  /* (221) slimit_opt ::= */
   -2,  /* (222) slimit_opt ::= SLIMIT signed */
   -4,  /* (223) slimit_opt ::= SLIMIT signed SOFFSET signed */
   -4,  /* (224) slimit_opt ::= SLIMIT signed COMMA signed */
    0,  /* (225) where_opt ::= */
   -2,  /* (226) where_opt ::= WHERE expr */
   -3,  /* (227) expr ::= LP expr RP */
   -1,  /* (228) expr ::= ID */
   -3,  /* (229) expr ::= ID DOT ID */
   -3,  /* (230) expr ::= ID DOT STAR */
   -1,  /* (231) expr ::= INTEGER */
   -2,  /* (232) expr ::= MINUS INTEGER */
   -2,  /* (233) expr ::= PLUS INTEGER */
   -1,  /* (234) expr ::= FLOAT */
   -2,  /* (235) expr ::= MINUS FLOAT */
   -2,  /* (236) expr ::= PLUS FLOAT */
   -1,  /* (237) expr ::= STRING */
   -1,  /* (238) expr ::= NOW */
   -1,  /* (239) expr ::= VARIABLE */
   -2,  /* (240) expr ::= PLUS VARIABLE */
   -2,  /* (241) expr ::= MINUS VARIABLE */
   -1,  /* (242) expr ::= BOOL */
   -1,  /* (243) expr ::= NULL */
   -4,  /* (244) expr ::= ID LP exprlist RP */
   -4,  /* (245) expr ::= ID LP STAR RP */
   -3,  /* (246) expr ::= expr IS NULL */
   -4,  /* (247) expr ::= expr IS NOT NULL */
   -3,  /* (248) expr ::= expr LT expr */
   -3,  /* (249) expr ::= expr GT expr */
   -3,  /* (250) expr ::= expr LE expr */
   -3,  /* (251) expr ::= expr GE expr */
   -3,  /* (252) expr ::= expr NE expr */
   -3,  /* (253) expr ::= expr EQ expr */
   -5,  /* (254) expr ::= expr BETWEEN expr AND expr */
   -3,  /* (255) expr ::= expr AND expr */
   -3,  /* (256) expr ::= expr OR expr */
   -3,  /* (257) expr ::= expr PLUS expr */
   -3,  /* (258) expr ::= expr MINUS expr */
   -3,  /* (259) expr ::= expr STAR expr */
   -3,  /* (260) expr ::= expr SLASH expr */
   -3,  /* (261) expr ::= expr REM expr */
   -3,  /* (262) expr ::= expr LIKE expr */
   -5,  /* (263) expr ::= expr IN LP exprlist RP */
   -3,  /* (264) exprlist ::= exprlist COMMA expritem */
   -1,  /* (265) exprlist ::= expritem */
   -1,  /* (266) expritem ::= expr */
    0,  /* (267) expritem ::= */
   -3,  /* (268) cmd ::= RESET QUERY CACHE */
   -3,  /* (269) cmd ::= SYNCDB ids REPLICA */
   -7,  /* (270) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   -7,  /* (271) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   -7,  /* (272) cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist */
   -5,  /* (273) cmd ::= ALTER TABLE ids cpxName DEATCH */
   -8,  /* (274) cmd ::= ALTER TABLE ids cpxName ATTACH TO ids cpxName */
   -7,  /* (275) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   -7,  /* (276) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   -8,  /* (277) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   -9,  /* (278) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   -7,  /* (279) cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist */
   -7,  /* (280) cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist */
   -7,  /* (281) cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids */
   -7,  /* (282) cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist */
   -7,  /* (283) cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist */
   -7,  /* (284) cmd ::= ALTER STABLE ids cpxName DROP TAG ids */
   -8,  /* (285) cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids */
   -9,  /* (286) cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem */
   -7,  /* (287) cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist */
   -3,  /* (288) cmd ::= KILL CONNECTION INTEGER */
   -5,  /* (289) cmd ::= KILL STREAM INTEGER COLON INTEGER */
   -5,  /* (290) cmd ::= KILL QUERY INTEGER COLON INTEGER */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s, pop back to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action",
        yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s.\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action");
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= cmd */
      case 138: /* cmd ::= CREATE TABLE create_table_args */ yytestcase(yyruleno==138);
      case 139: /* cmd ::= CREATE TABLE create_stable_args */ yytestcase(yyruleno==139);
      case 140: /* cmd ::= CREATE STABLE create_stable_args */ yytestcase(yyruleno==140);
#line 63 "../inc/sql.y"
{}
#line 2547 "../inc/sql.c"
        break;
      case 1: /* cmd ::= SHOW DATABASES */
#line 66 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DB, 0, 0);}
#line 2552 "../inc/sql.c"
        break;
      case 2: /* cmd ::= SHOW TOPICS */
#line 67 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_TP, 0, 0);}
#line 2557 "../inc/sql.c"
        break;
      case 3: /* cmd ::= SHOW FUNCTIONS */
#line 68 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_FUNCTION, 0, 0);}
#line 2562 "../inc/sql.c"
        break;
      case 4: /* cmd ::= SHOW MNODES */
#line 69 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MNODE, 0, 0);}
#line 2567 "../inc/sql.c"
        break;
      case 5: /* cmd ::= SHOW DNODES */
#line 70 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DNODE, 0, 0);}
#line 2572 "../inc/sql.c"
        break;
      case 6: /* cmd ::= SHOW ACCOUNTS */
#line 71 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_ACCT, 0, 0);}
#line 2577 "../inc/sql.c"
        break;
      case 7: /* cmd ::= SHOW USERS */
#line 72 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_USER, 0, 0);}
#line 2582 "../inc/sql.c"
        break;
      case 8: /* cmd ::= SHOW MODULES */
#line 74 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MODULE, 0, 0);  }
#line 2587 "../inc/sql.c"
        break;
      case 9: /* cmd ::= SHOW QUERIES */
#line 75 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_QUERIES, 0, 0);  }
#line 2592 "../inc/sql.c"
        break;
      case 10: /* cmd ::= SHOW CONNECTIONS */
#line 76 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_CONNS, 0, 0);}
#line 2597 "../inc/sql.c"
        break;
      case 11: /* cmd ::= SHOW STREAMS */
#line 77 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_STREAMS, 0, 0);  }
#line 2602 "../inc/sql.c"
        break;
      case 12: /* cmd ::= SHOW VARIABLES */
#line 78 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VARIABLES, 0, 0);  }
#line 2607 "../inc/sql.c"
        break;
      case 13: /* cmd ::= SHOW SCORES */
#line 79 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_SCORES, 0, 0);   }
#line 2612 "../inc/sql.c"
        break;
      case 14: /* cmd ::= SHOW GRANTS */
#line 80 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_GRANTS, 0, 0);   }
#line 2617 "../inc/sql.c"
        break;
      case 15: /* cmd ::= SHOW VNODES */
#line 82 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, 0, 0); }
#line 2622 "../inc/sql.c"
        break;
      case 16: /* cmd ::= SHOW VNODES IPTOKEN */
#line 83 "../inc/sql.y"
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, &yymsp[0].minor.yy0, 0); }
#line 2627 "../inc/sql.c"
        break;
      case 17: /* dbPrefix ::= */
#line 87 "../inc/sql.y"
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.type = 0;}
#line 2632 "../inc/sql.c"
        break;
      case 18: /* dbPrefix ::= ids DOT */
#line 88 "../inc/sql.y"
{yylhsminor.yy0 = yymsp[-1].minor.yy0;  }
#line 2637 "../inc/sql.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* cpxName ::= */
#line 91 "../inc/sql.y"
{yymsp[1].minor.yy0.n = 0;  }
#line 2643 "../inc/sql.c"
        break;
      case 20: /* cpxName ::= DOT ids */
#line 92 "../inc/sql.y"
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; yymsp[-1].minor.yy0.n += 1;    }
#line 2648 "../inc/sql.c"
        break;
      case 21: /* cmd ::= SHOW CREATE TABLE ids cpxName */
#line 94 "../inc/sql.y"
{
   yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
   setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_TABLE, 1, &yymsp[-1].minor.yy0);
}
#line 2656 "../inc/sql.c"
        break;
      case 22: /* cmd ::= SHOW CREATE STABLE ids cpxName */
#line 98 "../inc/sql.y"
{
   yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
   setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_STABLE, 1, &yymsp[-1].minor.yy0);
}
#line 2664 "../inc/sql.c"
        break;
      case 23: /* cmd ::= SHOW CREATE DATABASE ids */
#line 103 "../inc/sql.y"
{
  setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_DATABASE, 1, &yymsp[0].minor.yy0);
}
#line 2671 "../inc/sql.c"
        break;
      case 24: /* cmd ::= SHOW dbPrefix TABLES */
#line 107 "../inc/sql.y"
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-1].minor.yy0, 0);
}
#line 2678 "../inc/sql.c"
        break;
      case 25: /* cmd ::= SHOW dbPrefix TABLES LIKE ids */
#line 111 "../inc/sql.y"
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2685 "../inc/sql.c"
        break;
      case 26: /* cmd ::= SHOW dbPrefix STABLES */
#line 115 "../inc/sql.y"
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &yymsp[-1].minor.yy0, 0);
}
#line 2692 "../inc/sql.c"
        break;
      case 27: /* cmd ::= SHOW dbPrefix STABLES LIKE ids */
#line 119 "../inc/sql.y"
{
    SStrToken token;
    tSetDbName(&token, &yymsp[-3].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &token, &yymsp[0].minor.yy0);
}
#line 2701 "../inc/sql.c"
        break;
      case 28: /* cmd ::= SHOW dbPrefix VGROUPS */
#line 125 "../inc/sql.y"
{
    SStrToken token;
    tSetDbName(&token, &yymsp[-1].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_VGROUP, &token, 0);
}
#line 2710 "../inc/sql.c"
        break;
      case 29: /* cmd ::= SHOW dbPrefix VGROUPS ids */
#line 131 "../inc/sql.y"
{
    SStrToken token;
    tSetDbName(&token, &yymsp[-2].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_VGROUP, &token, &yymsp[0].minor.yy0);
}
#line 2719 "../inc/sql.c"
        break;
      case 30: /* cmd ::= DROP TABLE ifexists ids cpxName */
#line 138 "../inc/sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDropDbTableInfo(pInfo, TSDB_SQL_DROP_TABLE, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0, -1, -1);
}
#line 2727 "../inc/sql.c"
        break;
      case 31: /* cmd ::= DROP STABLE ifexists ids cpxName */
#line 144 "../inc/sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDropDbTableInfo(pInfo, TSDB_SQL_DROP_TABLE, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0, -1, TSDB_SUPER_TABLE);
}
#line 2735 "../inc/sql.c"
        break;
      case 32: /* cmd ::= DROP DATABASE ifexists ids */
#line 149 "../inc/sql.y"
{ setDropDbTableInfo(pInfo, TSDB_SQL_DROP_DB, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0, TSDB_DB_TYPE_DEFAULT, -1); }
#line 2740 "../inc/sql.c"
        break;
      case 33: /* cmd ::= DROP TOPIC ifexists ids */
#line 150 "../inc/sql.y"
{ setDropDbTableInfo(pInfo, TSDB_SQL_DROP_DB, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0, TSDB_DB_TYPE_TOPIC, -1); }
#line 2745 "../inc/sql.c"
        break;
      case 34: /* cmd ::= DROP FUNCTION ids */
#line 151 "../inc/sql.y"
{ setDropFuncInfo(pInfo, TSDB_SQL_DROP_FUNCTION, &yymsp[0].minor.yy0); }
#line 2750 "../inc/sql.c"
        break;
      case 35: /* cmd ::= DROP DNODE ids */
#line 153 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_DNODE, 1, &yymsp[0].minor.yy0);    }
#line 2755 "../inc/sql.c"
        break;
      case 36: /* cmd ::= DROP USER ids */
#line 154 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_USER, 1, &yymsp[0].minor.yy0);     }
#line 2760 "../inc/sql.c"
        break;
      case 37: /* cmd ::= DROP ACCOUNT ids */
#line 155 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_ACCT, 1, &yymsp[0].minor.yy0);  }
#line 2765 "../inc/sql.c"
        break;
      case 38: /* cmd ::= USE ids */
#line 158 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_USE_DB, 1, &yymsp[0].minor.yy0);}
#line 2770 "../inc/sql.c"
        break;
      case 39: /* cmd ::= DESCRIBE ids cpxName */
#line 161 "../inc/sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDCLSqlElems(pInfo, TSDB_SQL_DESCRIBE_TABLE, 1, &yymsp[-1].minor.yy0);
}
#line 2778 "../inc/sql.c"
        break;
      case 40: /* cmd ::= ALTER USER ids PASS ids */
#line 167 "../inc/sql.y"
{ setAlterUserSql(pInfo, TSDB_ALTER_USER_PASSWD, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, NULL);    }
#line 2783 "../inc/sql.c"
        break;
      case 41: /* cmd ::= ALTER USER ids PRIVILEGE ids */
#line 168 "../inc/sql.y"
{ setAlterUserSql(pInfo, TSDB_ALTER_USER_PRIVILEGES, &yymsp[-2].minor.yy0, NULL, &yymsp[0].minor.yy0);}
#line 2788 "../inc/sql.c"
        break;
      case 42: /* cmd ::= ALTER DNODE ids ids */
#line 169 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_DNODE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
#line 2793 "../inc/sql.c"
        break;
      case 43: /* cmd ::= ALTER DNODE ids ids ids */
#line 170 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_DNODE, 3, &yymsp[-2].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);      }
#line 2798 "../inc/sql.c"
        break;
      case 44: /* cmd ::= ALTER LOCAL ids */
#line 171 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_LOCAL, 1, &yymsp[0].minor.yy0);              }
#line 2803 "../inc/sql.c"
        break;
      case 45: /* cmd ::= ALTER LOCAL ids ids */
#line 172 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_LOCAL, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
#line 2808 "../inc/sql.c"
        break;
      case 46: /* cmd ::= ALTER DATABASE ids alter_db_optr */
      case 47: /* cmd ::= ALTER TOPIC ids alter_topic_optr */ yytestcase(yyruleno==47);
#line 173 "../inc/sql.y"
{ SStrToken t = {0};  setCreateDbInfo(pInfo, TSDB_SQL_ALTER_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy246, &t);}
#line 2814 "../inc/sql.c"
        break;
      case 48: /* cmd ::= ALTER ACCOUNT ids acct_optr */
#line 176 "../inc/sql.y"
{ setCreateAcctSql(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-1].minor.yy0, NULL, &yymsp[0].minor.yy377);}
#line 2819 "../inc/sql.c"
        break;
      case 49: /* cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
#line 177 "../inc/sql.y"
{ setCreateAcctSql(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy377);}
#line 2824 "../inc/sql.c"
        break;
      case 50: /* cmd ::= COMPACT VNODES IN LP exprlist RP */
#line 181 "../inc/sql.y"
{ setCompactVnodeSql(pInfo, TSDB_SQL_COMPACT_VNODE, yymsp[-1].minor.yy403);}
#line 2829 "../inc/sql.c"
        break;
      case 51: /* ids ::= ID */
      case 52: /* ids ::= STRING */ yytestcase(yyruleno==52);
#line 187 "../inc/sql.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0; }
#line 2835 "../inc/sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 53: /* ifexists ::= IF EXISTS */
#line 191 "../inc/sql.y"
{ yymsp[-1].minor.yy0.n = 1;}
#line 2841 "../inc/sql.c"
        break;
      case 54: /* ifexists ::= */
      case 56: /* ifnotexists ::= */ yytestcase(yyruleno==56);
      case 180: /* distinct ::= */ yytestcase(yyruleno==180);
#line 192 "../inc/sql.y"
{ yymsp[1].minor.yy0.n = 0;}
#line 2848 "../inc/sql.c"
        break;
      case 55: /* ifnotexists ::= IF NOT EXISTS */
#line 195 "../inc/sql.y"
{ yymsp[-2].minor.yy0.n = 1;}
#line 2853 "../inc/sql.c"
        break;
      case 57: /* cmd ::= CREATE DNODE ids */
#line 200 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_CREATE_DNODE, 1, &yymsp[0].minor.yy0);}
#line 2858 "../inc/sql.c"
        break;
      case 58: /* cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
#line 202 "../inc/sql.y"
{ setCreateAcctSql(pInfo, TSDB_SQL_CREATE_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy377);}
#line 2863 "../inc/sql.c"
        break;
      case 59: /* cmd ::= CREATE DATABASE ifnotexists ids db_optr */
      case 60: /* cmd ::= CREATE TOPIC ifnotexists ids topic_optr */ yytestcase(yyruleno==60);
#line 203 "../inc/sql.y"
{ setCreateDbInfo(pInfo, TSDB_SQL_CREATE_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy246, &yymsp[-2].minor.yy0);}
#line 2869 "../inc/sql.c"
        break;
      case 61: /* cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
#line 205 "../inc/sql.y"
{ setCreateFuncInfo(pInfo, TSDB_SQL_CREATE_FUNCTION, &yymsp[-5].minor.yy0, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy363, &yymsp[0].minor.yy0, 1);}
#line 2874 "../inc/sql.c"
        break;
      case 62: /* cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
#line 206 "../inc/sql.y"
{ setCreateFuncInfo(pInfo, TSDB_SQL_CREATE_FUNCTION, &yymsp[-5].minor.yy0, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy363, &yymsp[0].minor.yy0, 2);}
#line 2879 "../inc/sql.c"
        break;
      case 63: /* cmd ::= CREATE USER ids PASS ids */
#line 207 "../inc/sql.y"
{ setCreateUserSql(pInfo, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);}
#line 2884 "../inc/sql.c"
        break;
      case 64: /* bufsize ::= */
      case 66: /* pps ::= */ yytestcase(yyruleno==66);
      case 68: /* tseries ::= */ yytestcase(yyruleno==68);
      case 70: /* dbs ::= */ yytestcase(yyruleno==70);
      case 72: /* streams ::= */ yytestcase(yyruleno==72);
      case 74: /* storage ::= */ yytestcase(yyruleno==74);
      case 76: /* qtime ::= */ yytestcase(yyruleno==76);
      case 78: /* users ::= */ yytestcase(yyruleno==78);
      case 80: /* conns ::= */ yytestcase(yyruleno==80);
      case 82: /* state ::= */ yytestcase(yyruleno==82);
#line 209 "../inc/sql.y"
{ yymsp[1].minor.yy0.n = 0;   }
#line 2898 "../inc/sql.c"
        break;
      case 65: /* bufsize ::= BUFSIZE INTEGER */
      case 67: /* pps ::= PPS INTEGER */ yytestcase(yyruleno==67);
      case 69: /* tseries ::= TSERIES INTEGER */ yytestcase(yyruleno==69);
      case 71: /* dbs ::= DBS INTEGER */ yytestcase(yyruleno==71);
      case 73: /* streams ::= STREAMS INTEGER */ yytestcase(yyruleno==73);
      case 75: /* storage ::= STORAGE INTEGER */ yytestcase(yyruleno==75);
      case 77: /* qtime ::= QTIME INTEGER */ yytestcase(yyruleno==77);
      case 79: /* users ::= USERS INTEGER */ yytestcase(yyruleno==79);
      case 81: /* conns ::= CONNS INTEGER */ yytestcase(yyruleno==81);
      case 83: /* state ::= STATE ids */ yytestcase(yyruleno==83);
#line 210 "../inc/sql.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;     }
#line 2912 "../inc/sql.c"
        break;
      case 84: /* acct_optr ::= pps tseries storage streams qtime dbs users conns state */
#line 240 "../inc/sql.y"
{
    yylhsminor.yy377.maxUsers   = (yymsp[-2].minor.yy0.n>0)?atoi(yymsp[-2].minor.yy0.z):-1;
    yylhsminor.yy377.maxDbs     = (yymsp[-3].minor.yy0.n>0)?atoi(yymsp[-3].minor.yy0.z):-1;
    yylhsminor.yy377.maxTimeSeries = (yymsp[-7].minor.yy0.n>0)?atoi(yymsp[-7].minor.yy0.z):-1;
    yylhsminor.yy377.maxStreams = (yymsp[-5].minor.yy0.n>0)?atoi(yymsp[-5].minor.yy0.z):-1;
    yylhsminor.yy377.maxPointsPerSecond     = (yymsp[-8].minor.yy0.n>0)?atoi(yymsp[-8].minor.yy0.z):-1;
    yylhsminor.yy377.maxStorage = (yymsp[-6].minor.yy0.n>0)?strtoll(yymsp[-6].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy377.maxQueryTime   = (yymsp[-4].minor.yy0.n>0)?strtoll(yymsp[-4].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy377.maxConnections   = (yymsp[-1].minor.yy0.n>0)?atoi(yymsp[-1].minor.yy0.z):-1;
    yylhsminor.yy377.stat    = yymsp[0].minor.yy0;
}
#line 2927 "../inc/sql.c"
  yymsp[-8].minor.yy377 = yylhsminor.yy377;
        break;
      case 85: /* intitemlist ::= intitemlist COMMA intitem */
      case 154: /* tagitemlist ::= tagitemlist COMMA tagitem */ yytestcase(yyruleno==154);
#line 256 "../inc/sql.y"
{ yylhsminor.yy403 = tVariantListAppend(yymsp[-2].minor.yy403, &yymsp[0].minor.yy488, -1);    }
#line 2934 "../inc/sql.c"
  yymsp[-2].minor.yy403 = yylhsminor.yy403;
        break;
      case 86: /* intitemlist ::= intitem */
      case 155: /* tagitemlist ::= tagitem */ yytestcase(yyruleno==155);
#line 257 "../inc/sql.y"
{ yylhsminor.yy403 = tVariantListAppend(NULL, &yymsp[0].minor.yy488, -1); }
#line 2941 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 87: /* intitem ::= INTEGER */
      case 156: /* tagitem ::= INTEGER */ yytestcase(yyruleno==156);
      case 157: /* tagitem ::= FLOAT */ yytestcase(yyruleno==157);
      case 158: /* tagitem ::= STRING */ yytestcase(yyruleno==158);
      case 159: /* tagitem ::= BOOL */ yytestcase(yyruleno==159);
#line 259 "../inc/sql.y"
{ toTSDBType(yymsp[0].minor.yy0.type); tVariantCreate(&yylhsminor.yy488, &yymsp[0].minor.yy0); }
#line 2951 "../inc/sql.c"
  yymsp[0].minor.yy488 = yylhsminor.yy488;
        break;
      case 88: /* keep ::= KEEP intitemlist */
#line 263 "../inc/sql.y"
{ yymsp[-1].minor.yy403 = yymsp[0].minor.yy403; }
#line 2957 "../inc/sql.c"
        break;
      case 89: /* cache ::= CACHE INTEGER */
      case 90: /* replica ::= REPLICA INTEGER */ yytestcase(yyruleno==90);
      case 91: /* quorum ::= QUORUM INTEGER */ yytestcase(yyruleno==91);
      case 92: /* days ::= DAYS INTEGER */ yytestcase(yyruleno==92);
      case 93: /* minrows ::= MINROWS INTEGER */ yytestcase(yyruleno==93);
      case 94: /* maxrows ::= MAXROWS INTEGER */ yytestcase(yyruleno==94);
      case 95: /* blocks ::= BLOCKS INTEGER */ yytestcase(yyruleno==95);
      case 96: /* ctime ::= CTIME INTEGER */ yytestcase(yyruleno==96);
      case 97: /* wal ::= WAL INTEGER */ yytestcase(yyruleno==97);
      case 98: /* fsync ::= FSYNC INTEGER */ yytestcase(yyruleno==98);
      case 99: /* comp ::= COMP INTEGER */ yytestcase(yyruleno==99);
      case 100: /* prec ::= PRECISION STRING */ yytestcase(yyruleno==100);
      case 101: /* update ::= UPDATE INTEGER */ yytestcase(yyruleno==101);
      case 102: /* cachelast ::= CACHELAST INTEGER */ yytestcase(yyruleno==102);
      case 103: /* partitions ::= PARTITIONS INTEGER */ yytestcase(yyruleno==103);
#line 265 "../inc/sql.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; }
#line 2976 "../inc/sql.c"
        break;
      case 104: /* db_optr ::= */
#line 282 "../inc/sql.y"
{setDefaultCreateDbOption(&yymsp[1].minor.yy246); yymsp[1].minor.yy246.dbType = TSDB_DB_TYPE_DEFAULT;}
#line 2981 "../inc/sql.c"
        break;
      case 105: /* db_optr ::= db_optr cache */
#line 284 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.cacheBlockSize = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2986 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 106: /* db_optr ::= db_optr replica */
      case 123: /* alter_db_optr ::= alter_db_optr replica */ yytestcase(yyruleno==123);
#line 285 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.replica = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2993 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 107: /* db_optr ::= db_optr quorum */
      case 124: /* alter_db_optr ::= alter_db_optr quorum */ yytestcase(yyruleno==124);
#line 286 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.quorum = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3000 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 108: /* db_optr ::= db_optr days */
#line 287 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.daysPerFile = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3006 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 109: /* db_optr ::= db_optr minrows */
#line 288 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.minRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
#line 3012 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 110: /* db_optr ::= db_optr maxrows */
#line 289 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.maxRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
#line 3018 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 111: /* db_optr ::= db_optr blocks */
      case 126: /* alter_db_optr ::= alter_db_optr blocks */ yytestcase(yyruleno==126);
#line 290 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.numOfBlocks = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3025 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 112: /* db_optr ::= db_optr ctime */
#line 291 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.commitTime = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3031 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 113: /* db_optr ::= db_optr wal */
#line 292 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.walLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3037 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 114: /* db_optr ::= db_optr fsync */
#line 293 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.fsyncPeriod = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3043 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 115: /* db_optr ::= db_optr comp */
      case 127: /* alter_db_optr ::= alter_db_optr comp */ yytestcase(yyruleno==127);
#line 294 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.compressionLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3050 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 116: /* db_optr ::= db_optr prec */
#line 295 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.precision = yymsp[0].minor.yy0; }
#line 3056 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 117: /* db_optr ::= db_optr keep */
      case 125: /* alter_db_optr ::= alter_db_optr keep */ yytestcase(yyruleno==125);
#line 296 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.keep = yymsp[0].minor.yy403; }
#line 3063 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 118: /* db_optr ::= db_optr update */
      case 128: /* alter_db_optr ::= alter_db_optr update */ yytestcase(yyruleno==128);
#line 297 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.update = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3070 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 119: /* db_optr ::= db_optr cachelast */
      case 129: /* alter_db_optr ::= alter_db_optr cachelast */ yytestcase(yyruleno==129);
#line 298 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.cachelast = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3077 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 120: /* topic_optr ::= db_optr */
      case 130: /* alter_topic_optr ::= alter_db_optr */ yytestcase(yyruleno==130);
#line 302 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[0].minor.yy246; yylhsminor.yy246.dbType = TSDB_DB_TYPE_TOPIC; }
#line 3084 "../inc/sql.c"
  yymsp[0].minor.yy246 = yylhsminor.yy246;
        break;
      case 121: /* topic_optr ::= topic_optr partitions */
      case 131: /* alter_topic_optr ::= alter_topic_optr partitions */ yytestcase(yyruleno==131);
#line 303 "../inc/sql.y"
{ yylhsminor.yy246 = yymsp[-1].minor.yy246; yylhsminor.yy246.partitions = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3091 "../inc/sql.c"
  yymsp[-1].minor.yy246 = yylhsminor.yy246;
        break;
      case 122: /* alter_db_optr ::= */
#line 306 "../inc/sql.y"
{ setDefaultCreateDbOption(&yymsp[1].minor.yy246); yymsp[1].minor.yy246.dbType = TSDB_DB_TYPE_DEFAULT;}
#line 3097 "../inc/sql.c"
        break;
      case 132: /* typename ::= ids */
#line 326 "../inc/sql.y"
{ 
  yymsp[0].minor.yy0.type = 0;
  tSetColumnType (&yylhsminor.yy363, &yymsp[0].minor.yy0);
}
#line 3105 "../inc/sql.c"
  yymsp[0].minor.yy363 = yylhsminor.yy363;
        break;
      case 133: /* typename ::= ids LP signed RP */
#line 332 "../inc/sql.y"
{
  if (yymsp[-1].minor.yy387 <= 0) {
    yymsp[-3].minor.yy0.type = 0;
    tSetColumnType(&yylhsminor.yy363, &yymsp[-3].minor.yy0);
  } else {
    yymsp[-3].minor.yy0.type = -yymsp[-1].minor.yy387;  // negative value of name length
    tSetColumnType(&yylhsminor.yy363, &yymsp[-3].minor.yy0);
  }
}
#line 3119 "../inc/sql.c"
  yymsp[-3].minor.yy363 = yylhsminor.yy363;
        break;
      case 134: /* typename ::= ids UNSIGNED */
#line 343 "../inc/sql.y"
{
  yymsp[-1].minor.yy0.type = 0;
  yymsp[-1].minor.yy0.n = ((yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z);
  tSetColumnType (&yylhsminor.yy363, &yymsp[-1].minor.yy0);
}
#line 3129 "../inc/sql.c"
  yymsp[-1].minor.yy363 = yylhsminor.yy363;
        break;
      case 135: /* signed ::= INTEGER */
#line 350 "../inc/sql.y"
{ yylhsminor.yy387 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3135 "../inc/sql.c"
  yymsp[0].minor.yy387 = yylhsminor.yy387;
        break;
      case 136: /* signed ::= PLUS INTEGER */
#line 351 "../inc/sql.y"
{ yymsp[-1].minor.yy387 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 3141 "../inc/sql.c"
        break;
      case 137: /* signed ::= MINUS INTEGER */
#line 352 "../inc/sql.y"
{ yymsp[-1].minor.yy387 = -strtol(yymsp[0].minor.yy0.z, NULL, 10);}
#line 3146 "../inc/sql.c"
        break;
      case 141: /* cmd ::= CREATE TABLE create_table_list */
#line 358 "../inc/sql.y"
{ pInfo->type = TSDB_SQL_CREATE_TABLE; pInfo->pCreateTableInfo = yymsp[0].minor.yy56;}
#line 3151 "../inc/sql.c"
        break;
      case 142: /* create_table_list ::= create_from_stable */
#line 362 "../inc/sql.y"
{
  SCreateTableSql* pCreateTable = calloc(1, sizeof(SCreateTableSql));
  pCreateTable->childTableInfo = taosArrayInit(4, sizeof(SCreatedTableInfo));

  taosArrayPush(pCreateTable->childTableInfo, &yymsp[0].minor.yy84);
  pCreateTable->type = TSQL_CREATE_TABLE_FROM_STABLE;
  yylhsminor.yy56 = pCreateTable;
}
#line 3163 "../inc/sql.c"
  yymsp[0].minor.yy56 = yylhsminor.yy56;
        break;
      case 143: /* create_table_list ::= create_table_list create_from_stable */
#line 371 "../inc/sql.y"
{
  taosArrayPush(yymsp[-1].minor.yy56->childTableInfo, &yymsp[0].minor.yy84);
  yylhsminor.yy56 = yymsp[-1].minor.yy56;
}
#line 3172 "../inc/sql.c"
  yymsp[-1].minor.yy56 = yylhsminor.yy56;
        break;
      case 144: /* create_table_args ::= ifnotexists ids cpxName LP columnlist RP */
#line 377 "../inc/sql.y"
{
  yylhsminor.yy56 = tSetCreateTableInfo(yymsp[-1].minor.yy403, NULL, NULL, TSQL_CREATE_TABLE);
  setSqlInfo(pInfo, yylhsminor.yy56, NULL, TSDB_SQL_CREATE_TABLE);

  yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-4].minor.yy0, &yymsp[-5].minor.yy0);
}
#line 3184 "../inc/sql.c"
  yymsp[-5].minor.yy56 = yylhsminor.yy56;
        break;
      case 145: /* create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP */
#line 387 "../inc/sql.y"
{
  yylhsminor.yy56 = tSetCreateTableInfo(yymsp[-5].minor.yy403, yymsp[-1].minor.yy403, NULL, TSQL_CREATE_STABLE);
  setSqlInfo(pInfo, yylhsminor.yy56, NULL, TSDB_SQL_CREATE_TABLE);

  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-8].minor.yy0, &yymsp[-9].minor.yy0);
}
#line 3196 "../inc/sql.c"
  yymsp[-9].minor.yy56 = yylhsminor.yy56;
        break;
      case 146: /* create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP */
#line 398 "../inc/sql.y"
{
  yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  yylhsminor.yy84 = createNewChildTableInfo(&yymsp[-5].minor.yy0, NULL, yymsp[-1].minor.yy403, &yymsp[-8].minor.yy0, &yymsp[-9].minor.yy0);
}
#line 3206 "../inc/sql.c"
  yymsp[-9].minor.yy84 = yylhsminor.yy84;
        break;
      case 147: /* create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP */
#line 404 "../inc/sql.y"
{
  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  yymsp[-11].minor.yy0.n += yymsp[-10].minor.yy0.n;
  yylhsminor.yy84 = createNewChildTableInfo(&yymsp[-8].minor.yy0, yymsp[-5].minor.yy403, yymsp[-1].minor.yy403, &yymsp[-11].minor.yy0, &yymsp[-12].minor.yy0);
}
#line 3216 "../inc/sql.c"
  yymsp[-12].minor.yy84 = yylhsminor.yy84;
        break;
      case 148: /* tagNamelist ::= tagNamelist COMMA ids */
#line 412 "../inc/sql.y"
{taosArrayPush(yymsp[-2].minor.yy403, &yymsp[0].minor.yy0); yylhsminor.yy403 = yymsp[-2].minor.yy403;  }
#line 3222 "../inc/sql.c"
  yymsp[-2].minor.yy403 = yylhsminor.yy403;
        break;
      case 149: /* tagNamelist ::= ids */
#line 413 "../inc/sql.y"
{yylhsminor.yy403 = taosArrayInit(4, sizeof(SStrToken)); taosArrayPush(yylhsminor.yy403, &yymsp[0].minor.yy0);}
#line 3228 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 150: /* create_table_args ::= ifnotexists ids cpxName AS select */
#line 417 "../inc/sql.y"
{
  yylhsminor.yy56 = tSetCreateTableInfo(NULL, NULL, yymsp[0].minor.yy224, TSQL_CREATE_STREAM);
  setSqlInfo(pInfo, yylhsminor.yy56, NULL, TSDB_SQL_CREATE_TABLE);

  yymsp[-3].minor.yy0.n += yymsp[-2].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-3].minor.yy0, &yymsp[-4].minor.yy0);
}
#line 3240 "../inc/sql.c"
  yymsp[-4].minor.yy56 = yylhsminor.yy56;
        break;
      case 151: /* columnlist ::= columnlist COMMA column */
#line 428 "../inc/sql.y"
{taosArrayPush(yymsp[-2].minor.yy403, &yymsp[0].minor.yy363); yylhsminor.yy403 = yymsp[-2].minor.yy403;  }
#line 3246 "../inc/sql.c"
  yymsp[-2].minor.yy403 = yylhsminor.yy403;
        break;
      case 152: /* columnlist ::= column */
#line 429 "../inc/sql.y"
{yylhsminor.yy403 = taosArrayInit(4, sizeof(TAOS_FIELD)); taosArrayPush(yylhsminor.yy403, &yymsp[0].minor.yy363);}
#line 3252 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 153: /* column ::= ids typename */
#line 433 "../inc/sql.y"
{
  tSetColumnInfo(&yylhsminor.yy363, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy363);
}
#line 3260 "../inc/sql.c"
  yymsp[-1].minor.yy363 = yylhsminor.yy363;
        break;
      case 160: /* tagitem ::= NULL */
#line 448 "../inc/sql.y"
{ yymsp[0].minor.yy0.type = 0; tVariantCreate(&yylhsminor.yy488, &yymsp[0].minor.yy0); }
#line 3266 "../inc/sql.c"
  yymsp[0].minor.yy488 = yylhsminor.yy488;
        break;
      case 161: /* tagitem ::= NOW */
#line 449 "../inc/sql.y"
{ yymsp[0].minor.yy0.type = TSDB_DATA_TYPE_TIMESTAMP; tVariantCreate(&yylhsminor.yy488, &yymsp[0].minor.yy0);}
#line 3272 "../inc/sql.c"
  yymsp[0].minor.yy488 = yylhsminor.yy488;
        break;
      case 162: /* tagitem ::= MINUS INTEGER */
      case 163: /* tagitem ::= MINUS FLOAT */ yytestcase(yyruleno==163);
      case 164: /* tagitem ::= PLUS INTEGER */ yytestcase(yyruleno==164);
      case 165: /* tagitem ::= PLUS FLOAT */ yytestcase(yyruleno==165);
#line 451 "../inc/sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    yymsp[-1].minor.yy0.type = yymsp[0].minor.yy0.type;
    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantCreate(&yylhsminor.yy488, &yymsp[-1].minor.yy0);
}
#line 3286 "../inc/sql.c"
  yymsp[-1].minor.yy488 = yylhsminor.yy488;
        break;
      case 166: /* select ::= SELECT selcollist from where_opt interval_opt session_option windowstate_option fill_opt sliding_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt */
#line 482 "../inc/sql.y"
{
  yylhsminor.yy224 = tSetQuerySqlNode(&yymsp[-13].minor.yy0, yymsp[-12].minor.yy403, yymsp[-11].minor.yy114, yymsp[-10].minor.yy260, yymsp[-4].minor.yy403, yymsp[-2].minor.yy403, &yymsp[-9].minor.yy222, &yymsp[-8].minor.yy365, &yymsp[-7].minor.yy544, &yymsp[-5].minor.yy0, yymsp[-6].minor.yy403, &yymsp[0].minor.yy404, &yymsp[-1].minor.yy404, yymsp[-3].minor.yy260);
}
#line 3294 "../inc/sql.c"
  yymsp[-13].minor.yy224 = yylhsminor.yy224;
        break;
      case 167: /* select ::= LP select RP */
#line 486 "../inc/sql.y"
{yymsp[-2].minor.yy224 = yymsp[-1].minor.yy224;}
#line 3300 "../inc/sql.c"
        break;
      case 168: /* union ::= select */
#line 490 "../inc/sql.y"
{ yylhsminor.yy403 = setSubclause(NULL, yymsp[0].minor.yy224); }
#line 3305 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 169: /* union ::= union UNION ALL select */
#line 491 "../inc/sql.y"
{ yylhsminor.yy403 = appendSelectClause(yymsp[-3].minor.yy403, yymsp[0].minor.yy224); }
#line 3311 "../inc/sql.c"
  yymsp[-3].minor.yy403 = yylhsminor.yy403;
        break;
      case 170: /* cmd ::= union */
#line 493 "../inc/sql.y"
{ setSqlInfo(pInfo, yymsp[0].minor.yy403, NULL, TSDB_SQL_SELECT); }
#line 3317 "../inc/sql.c"
        break;
      case 171: /* select ::= SELECT selcollist */
#line 500 "../inc/sql.y"
{
  yylhsminor.yy224 = tSetQuerySqlNode(&yymsp[-1].minor.yy0, yymsp[0].minor.yy403, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}
#line 3324 "../inc/sql.c"
  yymsp[-1].minor.yy224 = yylhsminor.yy224;
        break;
      case 172: /* sclp ::= selcollist COMMA */
#line 512 "../inc/sql.y"
{yylhsminor.yy403 = yymsp[-1].minor.yy403;}
#line 3330 "../inc/sql.c"
  yymsp[-1].minor.yy403 = yylhsminor.yy403;
        break;
      case 173: /* sclp ::= */
      case 203: /* orderby_opt ::= */ yytestcase(yyruleno==203);
#line 513 "../inc/sql.y"
{yymsp[1].minor.yy403 = 0;}
#line 3337 "../inc/sql.c"
        break;
      case 174: /* selcollist ::= sclp distinct expr as */
#line 514 "../inc/sql.y"
{
   yylhsminor.yy403 = tSqlExprListAppend(yymsp[-3].minor.yy403, yymsp[-1].minor.yy260,  yymsp[-2].minor.yy0.n? &yymsp[-2].minor.yy0:0, yymsp[0].minor.yy0.n?&yymsp[0].minor.yy0:0);
}
#line 3344 "../inc/sql.c"
  yymsp[-3].minor.yy403 = yylhsminor.yy403;
        break;
      case 175: /* selcollist ::= sclp STAR */
#line 518 "../inc/sql.y"
{
   tSqlExpr *pNode = tSqlExprCreateIdValue(NULL, TK_ALL);
   yylhsminor.yy403 = tSqlExprListAppend(yymsp[-1].minor.yy403, pNode, 0, 0);
}
#line 3353 "../inc/sql.c"
  yymsp[-1].minor.yy403 = yylhsminor.yy403;
        break;
      case 176: /* as ::= AS ids */
#line 526 "../inc/sql.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;    }
#line 3359 "../inc/sql.c"
        break;
      case 177: /* as ::= ids */
#line 527 "../inc/sql.y"
{ yylhsminor.yy0 = yymsp[0].minor.yy0;    }
#line 3364 "../inc/sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 178: /* as ::= */
#line 528 "../inc/sql.y"
{ yymsp[1].minor.yy0.n = 0;  }
#line 3370 "../inc/sql.c"
        break;
      case 179: /* distinct ::= DISTINCT */
#line 531 "../inc/sql.y"
{ yylhsminor.yy0 = yymsp[0].minor.yy0;  }
#line 3375 "../inc/sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 181: /* from ::= FROM tablelist */
      case 182: /* from ::= FROM sub */ yytestcase(yyruleno==182);
#line 537 "../inc/sql.y"
{yymsp[-1].minor.yy114 = yymsp[0].minor.yy114;}
#line 3382 "../inc/sql.c"
        break;
      case 183: /* sub ::= LP union RP */
#line 542 "../inc/sql.y"
{yymsp[-2].minor.yy114 = addSubqueryElem(NULL, yymsp[-1].minor.yy403, NULL);}
#line 3387 "../inc/sql.c"
        break;
      case 184: /* sub ::= LP union RP ids */
#line 543 "../inc/sql.y"
{yymsp[-3].minor.yy114 = addSubqueryElem(NULL, yymsp[-2].minor.yy403, &yymsp[0].minor.yy0);}
#line 3392 "../inc/sql.c"
        break;
      case 185: /* sub ::= sub COMMA LP union RP ids */
#line 544 "../inc/sql.y"
{yylhsminor.yy114 = addSubqueryElem(yymsp[-5].minor.yy114, yymsp[-2].minor.yy403, &yymsp[0].minor.yy0);}
#line 3397 "../inc/sql.c"
  yymsp[-5].minor.yy114 = yylhsminor.yy114;
        break;
      case 186: /* tablelist ::= ids cpxName */
#line 548 "../inc/sql.y"
{
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy114 = setTableNameList(NULL, &yymsp[-1].minor.yy0, NULL);
}
#line 3406 "../inc/sql.c"
  yymsp[-1].minor.yy114 = yylhsminor.yy114;
        break;
      case 187: /* tablelist ::= ids cpxName ids */
#line 553 "../inc/sql.y"
{
  yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
  yylhsminor.yy114 = setTableNameList(NULL, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);
}
#line 3415 "../inc/sql.c"
  yymsp[-2].minor.yy114 = yylhsminor.yy114;
        break;
      case 188: /* tablelist ::= tablelist COMMA ids cpxName */
#line 558 "../inc/sql.y"
{
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy114 = setTableNameList(yymsp[-3].minor.yy114, &yymsp[-1].minor.yy0, NULL);
}
#line 3424 "../inc/sql.c"
  yymsp[-3].minor.yy114 = yylhsminor.yy114;
        break;
      case 189: /* tablelist ::= tablelist COMMA ids cpxName ids */
#line 563 "../inc/sql.y"
{
  yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
  yylhsminor.yy114 = setTableNameList(yymsp[-4].minor.yy114, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);
}
#line 3433 "../inc/sql.c"
  yymsp[-4].minor.yy114 = yylhsminor.yy114;
        break;
      case 190: /* tmvar ::= VARIABLE */
#line 570 "../inc/sql.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
#line 3439 "../inc/sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 191: /* interval_opt ::= INTERVAL LP tmvar RP */
#line 573 "../inc/sql.y"
{yymsp[-3].minor.yy222.interval = yymsp[-1].minor.yy0; yymsp[-3].minor.yy222.offset.n = 0;}
#line 3445 "../inc/sql.c"
        break;
      case 192: /* interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
#line 574 "../inc/sql.y"
{yymsp[-5].minor.yy222.interval = yymsp[-3].minor.yy0; yymsp[-5].minor.yy222.offset = yymsp[-1].minor.yy0;}
#line 3450 "../inc/sql.c"
        break;
      case 193: /* interval_opt ::= */
#line 575 "../inc/sql.y"
{memset(&yymsp[1].minor.yy222, 0, sizeof(yymsp[1].minor.yy222));}
#line 3455 "../inc/sql.c"
        break;
      case 194: /* session_option ::= */
#line 578 "../inc/sql.y"
{yymsp[1].minor.yy365.col.n = 0; yymsp[1].minor.yy365.gap.n = 0;}
#line 3460 "../inc/sql.c"
        break;
      case 195: /* session_option ::= SESSION LP ids cpxName COMMA tmvar RP */
#line 579 "../inc/sql.y"
{
   yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
   yymsp[-6].minor.yy365.col = yymsp[-4].minor.yy0;
   yymsp[-6].minor.yy365.gap = yymsp[-1].minor.yy0;
}
#line 3469 "../inc/sql.c"
        break;
      case 196: /* windowstate_option ::= */
#line 585 "../inc/sql.y"
{ yymsp[1].minor.yy544.col.n = 0; yymsp[1].minor.yy544.col.z = NULL;}
#line 3474 "../inc/sql.c"
        break;
      case 197: /* windowstate_option ::= STATE_WINDOW LP ids RP */
#line 586 "../inc/sql.y"
{ yymsp[-3].minor.yy544.col = yymsp[-1].minor.yy0; }
#line 3479 "../inc/sql.c"
        break;
      case 198: /* fill_opt ::= */
#line 590 "../inc/sql.y"
{ yymsp[1].minor.yy403 = 0;     }
#line 3484 "../inc/sql.c"
        break;
      case 199: /* fill_opt ::= FILL LP ID COMMA tagitemlist RP */
#line 591 "../inc/sql.y"
{
    tVariant A = {0};
    toTSDBType(yymsp[-3].minor.yy0.type);
    tVariantCreate(&A, &yymsp[-3].minor.yy0);

    tVariantListInsert(yymsp[-1].minor.yy403, &A, -1, 0);
    yymsp[-5].minor.yy403 = yymsp[-1].minor.yy403;
}
#line 3496 "../inc/sql.c"
        break;
      case 200: /* fill_opt ::= FILL LP ID RP */
#line 600 "../inc/sql.y"
{
    toTSDBType(yymsp[-1].minor.yy0.type);
    yymsp[-3].minor.yy403 = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);
}
#line 3504 "../inc/sql.c"
        break;
      case 201: /* sliding_opt ::= SLIDING LP tmvar RP */
#line 606 "../inc/sql.y"
{yymsp[-3].minor.yy0 = yymsp[-1].minor.yy0;     }
#line 3509 "../inc/sql.c"
        break;
      case 202: /* sliding_opt ::= */
#line 607 "../inc/sql.y"
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.z = NULL; yymsp[1].minor.yy0.type = 0;   }
#line 3514 "../inc/sql.c"
        break;
      case 204: /* orderby_opt ::= ORDER BY sortlist */
#line 619 "../inc/sql.y"
{yymsp[-2].minor.yy403 = yymsp[0].minor.yy403;}
#line 3519 "../inc/sql.c"
        break;
      case 205: /* sortlist ::= sortlist COMMA item sortorder */
#line 621 "../inc/sql.y"
{
    yylhsminor.yy403 = tVariantListAppend(yymsp[-3].minor.yy403, &yymsp[-1].minor.yy488, yymsp[0].minor.yy70);
}
#line 3526 "../inc/sql.c"
  yymsp[-3].minor.yy403 = yylhsminor.yy403;
        break;
      case 206: /* sortlist ::= item sortorder */
#line 625 "../inc/sql.y"
{
  yylhsminor.yy403 = tVariantListAppend(NULL, &yymsp[-1].minor.yy488, yymsp[0].minor.yy70);
}
#line 3534 "../inc/sql.c"
  yymsp[-1].minor.yy403 = yylhsminor.yy403;
        break;
      case 207: /* item ::= ids cpxName */
#line 630 "../inc/sql.y"
{
  toTSDBType(yymsp[-1].minor.yy0.type);
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;

  tVariantCreate(&yylhsminor.yy488, &yymsp[-1].minor.yy0);
}
#line 3545 "../inc/sql.c"
  yymsp[-1].minor.yy488 = yylhsminor.yy488;
        break;
      case 208: /* sortorder ::= ASC */
#line 638 "../inc/sql.y"
{ yymsp[0].minor.yy70 = TSDB_ORDER_ASC; }
#line 3551 "../inc/sql.c"
        break;
      case 209: /* sortorder ::= DESC */
#line 639 "../inc/sql.y"
{ yymsp[0].minor.yy70 = TSDB_ORDER_DESC;}
#line 3556 "../inc/sql.c"
        break;
      case 210: /* sortorder ::= */
#line 640 "../inc/sql.y"
{ yymsp[1].minor.yy70 = TSDB_ORDER_ASC; }
#line 3561 "../inc/sql.c"
        break;
      case 211: /* groupby_opt ::= */
#line 648 "../inc/sql.y"
{ yymsp[1].minor.yy403 = 0;}
#line 3566 "../inc/sql.c"
        break;
      case 212: /* groupby_opt ::= GROUP BY grouplist */
#line 649 "../inc/sql.y"
{ yymsp[-2].minor.yy403 = yymsp[0].minor.yy403;}
#line 3571 "../inc/sql.c"
        break;
      case 213: /* grouplist ::= grouplist COMMA item */
#line 651 "../inc/sql.y"
{
  yylhsminor.yy403 = tVariantListAppend(yymsp[-2].minor.yy403, &yymsp[0].minor.yy488, -1);
}
#line 3578 "../inc/sql.c"
  yymsp[-2].minor.yy403 = yylhsminor.yy403;
        break;
      case 214: /* grouplist ::= item */
#line 655 "../inc/sql.y"
{
  yylhsminor.yy403 = tVariantListAppend(NULL, &yymsp[0].minor.yy488, -1);
}
#line 3586 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 215: /* having_opt ::= */
      case 225: /* where_opt ::= */ yytestcase(yyruleno==225);
      case 267: /* expritem ::= */ yytestcase(yyruleno==267);
#line 662 "../inc/sql.y"
{yymsp[1].minor.yy260 = 0;}
#line 3594 "../inc/sql.c"
        break;
      case 216: /* having_opt ::= HAVING expr */
      case 226: /* where_opt ::= WHERE expr */ yytestcase(yyruleno==226);
#line 663 "../inc/sql.y"
{yymsp[-1].minor.yy260 = yymsp[0].minor.yy260;}
#line 3600 "../inc/sql.c"
        break;
      case 217: /* limit_opt ::= */
      case 221: /* slimit_opt ::= */ yytestcase(yyruleno==221);
#line 667 "../inc/sql.y"
{yymsp[1].minor.yy404.limit = -1; yymsp[1].minor.yy404.offset = 0;}
#line 3606 "../inc/sql.c"
        break;
      case 218: /* limit_opt ::= LIMIT signed */
      case 222: /* slimit_opt ::= SLIMIT signed */ yytestcase(yyruleno==222);
#line 668 "../inc/sql.y"
{yymsp[-1].minor.yy404.limit = yymsp[0].minor.yy387;  yymsp[-1].minor.yy404.offset = 0;}
#line 3612 "../inc/sql.c"
        break;
      case 219: /* limit_opt ::= LIMIT signed OFFSET signed */
#line 670 "../inc/sql.y"
{ yymsp[-3].minor.yy404.limit = yymsp[-2].minor.yy387;  yymsp[-3].minor.yy404.offset = yymsp[0].minor.yy387;}
#line 3617 "../inc/sql.c"
        break;
      case 220: /* limit_opt ::= LIMIT signed COMMA signed */
#line 672 "../inc/sql.y"
{ yymsp[-3].minor.yy404.limit = yymsp[0].minor.yy387;  yymsp[-3].minor.yy404.offset = yymsp[-2].minor.yy387;}
#line 3622 "../inc/sql.c"
        break;
      case 223: /* slimit_opt ::= SLIMIT signed SOFFSET signed */
#line 678 "../inc/sql.y"
{yymsp[-3].minor.yy404.limit = yymsp[-2].minor.yy387;  yymsp[-3].minor.yy404.offset = yymsp[0].minor.yy387;}
#line 3627 "../inc/sql.c"
        break;
      case 224: /* slimit_opt ::= SLIMIT signed COMMA signed */
#line 680 "../inc/sql.y"
{yymsp[-3].minor.yy404.limit = yymsp[0].minor.yy387;  yymsp[-3].minor.yy404.offset = yymsp[-2].minor.yy387;}
#line 3632 "../inc/sql.c"
        break;
      case 227: /* expr ::= LP expr RP */
#line 693 "../inc/sql.y"
{yylhsminor.yy260 = yymsp[-1].minor.yy260; yylhsminor.yy260->exprToken.z = yymsp[-2].minor.yy0.z; yylhsminor.yy260->exprToken.n = (yymsp[0].minor.yy0.z - yymsp[-2].minor.yy0.z + 1);}
#line 3637 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 228: /* expr ::= ID */
#line 695 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_ID);}
#line 3643 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 229: /* expr ::= ID DOT ID */
#line 696 "../inc/sql.y"
{ yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[-2].minor.yy0, TK_ID);}
#line 3649 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 230: /* expr ::= ID DOT STAR */
#line 697 "../inc/sql.y"
{ yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[-2].minor.yy0, TK_ALL);}
#line 3655 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 231: /* expr ::= INTEGER */
#line 699 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_INTEGER);}
#line 3661 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 232: /* expr ::= MINUS INTEGER */
      case 233: /* expr ::= PLUS INTEGER */ yytestcase(yyruleno==233);
#line 700 "../inc/sql.y"
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_INTEGER; yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[-1].minor.yy0, TK_INTEGER);}
#line 3668 "../inc/sql.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 234: /* expr ::= FLOAT */
#line 702 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_FLOAT);}
#line 3674 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 235: /* expr ::= MINUS FLOAT */
      case 236: /* expr ::= PLUS FLOAT */ yytestcase(yyruleno==236);
#line 703 "../inc/sql.y"
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_FLOAT; yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[-1].minor.yy0, TK_FLOAT);}
#line 3681 "../inc/sql.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 237: /* expr ::= STRING */
#line 705 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_STRING);}
#line 3687 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 238: /* expr ::= NOW */
#line 706 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_NOW); }
#line 3693 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 239: /* expr ::= VARIABLE */
#line 707 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_VARIABLE);}
#line 3699 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 240: /* expr ::= PLUS VARIABLE */
      case 241: /* expr ::= MINUS VARIABLE */ yytestcase(yyruleno==241);
#line 708 "../inc/sql.y"
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_VARIABLE; yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[-1].minor.yy0, TK_VARIABLE);}
#line 3706 "../inc/sql.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 242: /* expr ::= BOOL */
#line 710 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_BOOL);}
#line 3712 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 243: /* expr ::= NULL */
#line 711 "../inc/sql.y"
{ yylhsminor.yy260 = tSqlExprCreateIdValue(&yymsp[0].minor.yy0, TK_NULL);}
#line 3718 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 244: /* expr ::= ID LP exprlist RP */
#line 714 "../inc/sql.y"
{ tStrTokenAppend(pInfo->funcs, &yymsp[-3].minor.yy0); yylhsminor.yy260 = tSqlExprCreateFunction(yymsp[-1].minor.yy403, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type); }
#line 3724 "../inc/sql.c"
  yymsp[-3].minor.yy260 = yylhsminor.yy260;
        break;
      case 245: /* expr ::= ID LP STAR RP */
#line 717 "../inc/sql.y"
{ tStrTokenAppend(pInfo->funcs, &yymsp[-3].minor.yy0); yylhsminor.yy260 = tSqlExprCreateFunction(NULL, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type); }
#line 3730 "../inc/sql.c"
  yymsp[-3].minor.yy260 = yylhsminor.yy260;
        break;
      case 246: /* expr ::= expr IS NULL */
#line 720 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, NULL, TK_ISNULL);}
#line 3736 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 247: /* expr ::= expr IS NOT NULL */
#line 721 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-3].minor.yy260, NULL, TK_NOTNULL);}
#line 3742 "../inc/sql.c"
  yymsp[-3].minor.yy260 = yylhsminor.yy260;
        break;
      case 248: /* expr ::= expr LT expr */
#line 724 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_LT);}
#line 3748 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 249: /* expr ::= expr GT expr */
#line 725 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_GT);}
#line 3754 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 250: /* expr ::= expr LE expr */
#line 726 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_LE);}
#line 3760 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 251: /* expr ::= expr GE expr */
#line 727 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_GE);}
#line 3766 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 252: /* expr ::= expr NE expr */
#line 728 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_NE);}
#line 3772 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 253: /* expr ::= expr EQ expr */
#line 729 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_EQ);}
#line 3778 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 254: /* expr ::= expr BETWEEN expr AND expr */
#line 731 "../inc/sql.y"
{ tSqlExpr* X2 = tSqlExprClone(yymsp[-4].minor.yy260); yylhsminor.yy260 = tSqlExprCreate(tSqlExprCreate(yymsp[-4].minor.yy260, yymsp[-2].minor.yy260, TK_GE), tSqlExprCreate(X2, yymsp[0].minor.yy260, TK_LE), TK_AND);}
#line 3784 "../inc/sql.c"
  yymsp[-4].minor.yy260 = yylhsminor.yy260;
        break;
      case 255: /* expr ::= expr AND expr */
#line 733 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_AND);}
#line 3790 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 256: /* expr ::= expr OR expr */
#line 734 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_OR); }
#line 3796 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 257: /* expr ::= expr PLUS expr */
#line 737 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_PLUS);  }
#line 3802 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 258: /* expr ::= expr MINUS expr */
#line 738 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_MINUS); }
#line 3808 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 259: /* expr ::= expr STAR expr */
#line 739 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_STAR);  }
#line 3814 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 260: /* expr ::= expr SLASH expr */
#line 740 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_DIVIDE);}
#line 3820 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 261: /* expr ::= expr REM expr */
#line 741 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_REM);   }
#line 3826 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 262: /* expr ::= expr LIKE expr */
#line 744 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-2].minor.yy260, yymsp[0].minor.yy260, TK_LIKE);  }
#line 3832 "../inc/sql.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 263: /* expr ::= expr IN LP exprlist RP */
#line 747 "../inc/sql.y"
{yylhsminor.yy260 = tSqlExprCreate(yymsp[-4].minor.yy260, (tSqlExpr*)yymsp[-1].minor.yy403, TK_IN); }
#line 3838 "../inc/sql.c"
  yymsp[-4].minor.yy260 = yylhsminor.yy260;
        break;
      case 264: /* exprlist ::= exprlist COMMA expritem */
#line 755 "../inc/sql.y"
{yylhsminor.yy403 = tSqlExprListAppend(yymsp[-2].minor.yy403,yymsp[0].minor.yy260,0, 0);}
#line 3844 "../inc/sql.c"
  yymsp[-2].minor.yy403 = yylhsminor.yy403;
        break;
      case 265: /* exprlist ::= expritem */
#line 756 "../inc/sql.y"
{yylhsminor.yy403 = tSqlExprListAppend(0,yymsp[0].minor.yy260,0, 0);}
#line 3850 "../inc/sql.c"
  yymsp[0].minor.yy403 = yylhsminor.yy403;
        break;
      case 266: /* expritem ::= expr */
#line 757 "../inc/sql.y"
{yylhsminor.yy260 = yymsp[0].minor.yy260;}
#line 3856 "../inc/sql.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 268: /* cmd ::= RESET QUERY CACHE */
#line 761 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_RESET_CACHE, 0);}
#line 3862 "../inc/sql.c"
        break;
      case 269: /* cmd ::= SYNCDB ids REPLICA */
#line 764 "../inc/sql.y"
{ setDCLSqlElems(pInfo, TSDB_SQL_SYNC_DB_REPLICA, 1, &yymsp[-1].minor.yy0);}
#line 3867 "../inc/sql.c"
        break;
      case 270: /* cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
#line 767 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_ADD_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3876 "../inc/sql.c"
        break;
      case 271: /* cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
#line 773 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, NULL, K, TSDB_ALTER_TABLE_DROP_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3889 "../inc/sql.c"
        break;
      case 272: /* cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist */
#line 783 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_CHANGE_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3898 "../inc/sql.c"
        break;
      case 273: /* cmd ::= ALTER TABLE ids cpxName DEATCH */
#line 789 "../inc/sql.y"
{
    yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-2].minor.yy0, NULL, NULL, NULL, TSDB_ALTER_TABLE_DETACH_FROM_STABLE, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3907 "../inc/sql.c"
        break;
      case 274: /* cmd ::= ALTER TABLE ids cpxName ATTACH TO ids cpxName */
#line 795 "../inc/sql.y"
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-5].minor.yy0, &yymsp[-1].minor.yy0, NULL, NULL, TSDB_ALTER_TABLE_ATTACH_TO_STABLE, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3917 "../inc/sql.c"
        break;
      case 275: /* cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
#line 803 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_ADD_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3926 "../inc/sql.c"
        break;
      case 276: /* cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
#line 808 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_DROP_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3939 "../inc/sql.c"
        break;
      case 277: /* cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
#line 818 "../inc/sql.y"
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-5].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_CHANGE_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3955 "../inc/sql.c"
        break;
      case 278: /* cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
#line 831 "../inc/sql.y"
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1);
    A = tVariantListAppend(A, &yymsp[0].minor.yy488, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-6].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_UPDATE_TAG_VAL, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3969 "../inc/sql.c"
        break;
      case 279: /* cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist */
#line 842 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_MODIFY_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3978 "../inc/sql.c"
        break;
      case 280: /* cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist */
#line 849 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_ADD_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 3987 "../inc/sql.c"
        break;
      case 281: /* cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids */
#line 855 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, NULL, K, TSDB_ALTER_TABLE_DROP_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4000 "../inc/sql.c"
        break;
      case 282: /* cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist */
#line 865 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_CHANGE_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4009 "../inc/sql.c"
        break;
      case 283: /* cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist */
#line 872 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_ADD_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4018 "../inc/sql.c"
        break;
      case 284: /* cmd ::= ALTER STABLE ids cpxName DROP TAG ids */
#line 877 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_DROP_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4031 "../inc/sql.c"
        break;
      case 285: /* cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids */
#line 887 "../inc/sql.y"
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-5].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_CHANGE_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4047 "../inc/sql.c"
        break;
      case 286: /* cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem */
#line 900 "../inc/sql.y"
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1);
    A = tVariantListAppend(A, &yymsp[0].minor.yy488, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-6].minor.yy0, NULL, NULL, A, TSDB_ALTER_TABLE_UPDATE_TAG_VAL, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4061 "../inc/sql.c"
        break;
      case 287: /* cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist */
#line 911 "../inc/sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, yymsp[0].minor.yy403, NULL, TSDB_ALTER_TABLE_MODIFY_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
#line 4070 "../inc/sql.c"
        break;
      case 288: /* cmd ::= KILL CONNECTION INTEGER */
#line 918 "../inc/sql.y"
{setKillSql(pInfo, TSDB_SQL_KILL_CONNECTION, &yymsp[0].minor.yy0);}
#line 4075 "../inc/sql.c"
        break;
      case 289: /* cmd ::= KILL STREAM INTEGER COLON INTEGER */
#line 919 "../inc/sql.y"
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSql(pInfo, TSDB_SQL_KILL_STREAM, &yymsp[-2].minor.yy0);}
#line 4080 "../inc/sql.c"
        break;
      case 290: /* cmd ::= KILL QUERY INTEGER COLON INTEGER */
#line 920 "../inc/sql.y"
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSql(pInfo, TSDB_SQL_KILL_QUERY, &yymsp[-2].minor.yy0);}
#line 4085 "../inc/sql.c"
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 37 "../inc/sql.y"

  pInfo->valid = false;
  int32_t outputBufLen = tListLen(pInfo->msg);
  int32_t len = 0;

  if(TOKEN.z) {
    char msg[] = "syntax error near \"%s\"";
    int32_t sqlLen = strlen(&TOKEN.z[0]);

    if (sqlLen + sizeof(msg)/sizeof(msg[0]) + 1 > outputBufLen) {
        char tmpstr[128] = {0};
        memcpy(tmpstr, &TOKEN.z[0], sizeof(tmpstr)/sizeof(tmpstr[0]) - 1);
        len = sprintf(pInfo->msg, msg, tmpstr);
    } else {
        len = sprintf(pInfo->msg, msg, &TOKEN.z[0]);
    }

  } else {
    len = sprintf(pInfo->msg, "Incomplete SQL statement");
  }

  assert(len <= outputBufLen);
#line 4170 "../inc/sql.c"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 61 "../inc/sql.y"
#line 4197 "../inc/sql.c"
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ParseCTX_FETCH
  ParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ParseFallback(int iToken){
#ifdef YYFALLBACK
  assert( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) );
  return yyFallback[iToken];
#else
  (void)iToken;
  return 0;
#endif
}
