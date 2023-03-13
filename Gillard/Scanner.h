/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: @) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Run-time error token */
	SEOF_T		/* 11: Source end-of-file token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	gillard_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	gillard_intg intValue;						/* integer literal attribute (value) */
	gillard_intg keywordIndex;					/* keyword index in the keyword table */
	gillard_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	gillard_real floatValue;					/* floating-point literal attribute (value) */
	gillard_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	gillard_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	gillard_byte flags;			/* Flags information */
	union {
		gillard_intg intValue;				/* Integer value */
		gillard_real floatValue;			/* Float value */
		gillard_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	gillard_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */

#define CHRCOL2 '@'
#define CHRCOL3 '"'
#define CHRCOL4 '-'
#define CHRCOL5 '.'
#define CHRCOL6 '_'

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	6		/* Error state with no retract */
#define ESWR	7		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 8

/* TO_DO: Transition table - type of states defined in separate table */
static gillard_intg transitionTable[][TABLE_COLUMNS] = {
	/*[A-z], [0-9],  [@],  ["],  [-],  [.],  [_],  other 
	   L(0),  D(1), M(2), Q(3), N(4), P(5),  U(6),  O(7) */
	{    5,    1,   FS,   3,   1,   FS,   FS,   FS}, // S0: NOAS
	{    FS,    1,   FS,   FS,   FS,   2,   FS,   FS}, // S1: ASNR[Int]
	{    FS,    2,   FS,   FS,   FS,   FS,   FS}, // S2: ASWR[Float]
	{    3,    3,   3,   4,   3,   3,   3}, // S3: NOAS
	{    FSNR,    FSNR,   FSNR,   FSNR,   FSNR,   FSNR,   FSNR}, // S4: ASNR[String]
	{    5,    6,   FS,   FS,   FS,   6,   FS}, // S5: ASNR[Key]
	{    6,    6,   7,   FS,   FS,   6,   FS}, // S6: NOAS[6]
	{    FSNR,    FSNR,   FSNR,   FSNR,   FSNR,   FSNR,   FSNR}  // S7: ASWR[MID]
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static gillard_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	FSNR, /* 06 (Err1 - no retract) */
	FSWR  /* 07 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
gillard_intg startScanner(ReaderPointer psc_buf);
Token tokenizer(gillard_void);
static gillard_intg nextClass(gillard_char c);				/* character class function */
static gillard_intg nextState(gillard_intg, gillard_char);		/* state machine function */
gillard_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(gillard_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(gillard_char lexeme[]);
Token funcID	(gillard_char lexeme[]);
Token funcKEY	(gillard_char lexeme[]);
Token funcErr	(gillard_char lexeme[]);
Token funcIL	(gillard_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] - Methods */
	funcKEY,	/* KEY  [03] - Keywords */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	funcErr,	/* ERR1 [06] - No retract */
	funcErr		/* ERR2 [07] - Retract */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 26

/* TO_DO: Define the list of keywords */
static gillard_char* keywordTable[KWT_SIZE] = {
	"break",
	"const",
	"continue",
	"do",
	"else",
	"elseif",
	"end",
	"export",
	"false",
	"for",
	"function",
	"if",
	"import",
	"let",
	"macro",
	"module",
	"quote",
	"return",
	"scan",
	"struct",
	"true",
	"try",
	"using",
	"while",
	"int",
	"float",
	"string"
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	gillard_char indentationCharType;
	gillard_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
gillard_intg numScannerErrors;

#endif
