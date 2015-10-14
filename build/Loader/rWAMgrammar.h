/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     P_VARIABLE = 258,
     P_VALUE = 259,
     P_UNS_VALUE = 260,
     P_STRUCTURE = 261,
     P_LIST = 262,
     P_CONSTANT = 263,
     S_VARIABLE = 264,
     S_VALUE = 265,
     S_LCL_VALUE = 266,
     S_CONSTANT = 267,
     S_VOID = 268,
     G_VARIABLE = 269,
     G_VALUE = 270,
     G_STRUCTURE = 271,
     G_LIST = 272,
     G_CONSTANT = 273,
     U_VARIABLE = 274,
     U_VALUE = 275,
     U_LCL_CONSTANT = 276,
     U_CONSTANT = 277,
     U_VOID = 278,
     ALLOCATE = 279,
     DEALLOCATE = 280,
     CALL = 281,
     EXECUTE = 282,
     PROCEED = 283,
     SW_TERM = 284,
     SW_CONSTANT = 285,
     SW_STRUCTURE = 286,
     TRY_ME_ELSE = 287,
     RETRY_ME_ELSE = 288,
     TRUST_ME = 289,
     TRY = 290,
     RETRY = 291,
     TRUST = 292,
     NECK_CUT = 293,
     GET_LEVEL = 294,
     CUT = 295,
     INT = 296,
     FUNCTOR = 297,
     STRING = 298,
     PRINT_HEAP = 299,
     PRINT_ARG_REGISTERS = 300,
     PRINT_RESULT_ARG = 301,
     WRITE_OUT = 302,
     QUOTE = 303
   };
#endif
/* Tokens.  */
#define P_VARIABLE 258
#define P_VALUE 259
#define P_UNS_VALUE 260
#define P_STRUCTURE 261
#define P_LIST 262
#define P_CONSTANT 263
#define S_VARIABLE 264
#define S_VALUE 265
#define S_LCL_VALUE 266
#define S_CONSTANT 267
#define S_VOID 268
#define G_VARIABLE 269
#define G_VALUE 270
#define G_STRUCTURE 271
#define G_LIST 272
#define G_CONSTANT 273
#define U_VARIABLE 274
#define U_VALUE 275
#define U_LCL_CONSTANT 276
#define U_CONSTANT 277
#define U_VOID 278
#define ALLOCATE 279
#define DEALLOCATE 280
#define CALL 281
#define EXECUTE 282
#define PROCEED 283
#define SW_TERM 284
#define SW_CONSTANT 285
#define SW_STRUCTURE 286
#define TRY_ME_ELSE 287
#define RETRY_ME_ELSE 288
#define TRUST_ME 289
#define TRY 290
#define RETRY 291
#define TRUST 292
#define NECK_CUT 293
#define GET_LEVEL 294
#define CUT 295
#define INT 296
#define FUNCTOR 297
#define STRING 298
#define PRINT_HEAP 299
#define PRINT_ARG_REGISTERS 300
#define PRINT_RESULT_ARG 301
#define WRITE_OUT 302
#define QUOTE 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "src/Loader/rWAMgrammar.y"
{
    int i;
    char* s;
}
/* Line 1529 of yacc.c.  */
#line 150 "build/Loader/rWAMgrammar.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



