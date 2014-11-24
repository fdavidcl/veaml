%{
 
/**************************************************************************

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at http://mozilla.org/MPL/2.0/.

Copyright (c) 2014, David Charte fdavidcl@outlook.com

***************************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include "timeline.h"

enum mark_t {
  TIMELINE,
  VIDEO,
  AUDIO,
  IMAGE,
  TEXT
};

enum attr_t {
  /* Timing attributes */
  FROM,
  TO,
  START,
  END,

  /* Size and position attributes *
   * (for videos and pictures)    */
  WIDTH,
  HEIGHT,
  TOP,
  LEFT
};

int lines;
mark_t current_mark;
attr_t current_attr;
std::string current_content;
%}

%s newline
%s mark
%s expect_first_attr
%s expect_attr
%s expect_colon
%s expect_value
%s end_attr
%s expect_content

low         [a-z]
num         ([0-9]*\.?)+
blank       [\ \t]
blanks      {blank}+

mark        %{low}+

attrbegin   \{
attr        {low}+
colon       {blanks}?:{blanks}?
attrvalue   (\"{low}+\"|\'{low}+\'|{num})
comma       {blanks}?,{blanks}?
attrend     \}{blanks}?

content     [^%#\n\ \t][^#\n]*

comment     #(.*?)$

%%

  /* Comenzar líneas */
<INITIAL,newline>{blanks} {;}

  /* Detectamos una marca */
<INITIAL,newline>{mark} {
  /* Si estábamos leyendo una marca previa, la procesamos */
  if (current_content.length() > 0)
    std::cout << "Contenido de la marca: " << current_content << std::endl;
  
  /* Comenzamos lectura de nueva marca */
  std::cout << "Found mark! " << yytext << std::endl;
  
  std::string mark_text(yytext);

  if (mark_text == "%timeline") {
    current_mark = TIMELINE;
    BEGIN(mark);
  } else if (mark_text == "%video") {
    current_mark = VIDEO;
    BEGIN(mark);
  } else {
    std::cout << "Esta marca no es válida!" << std::endl;
    return -1;
  }
}

  /* La marca tiene atributos */
<mark>{attrbegin} { BEGIN(expect_first_attr); }

<expect_first_attr,expect_attr>{attr} {
  std::string cur_attr(yytext);

  std::cout << "Atributo: " << cur_attr << std::endl;
  BEGIN(expect_colon);
}

<expect_colon>{colon} { 
  BEGIN(expect_value);
}

<expect_value>{attrvalue} {
  std::cout << "Valor del atributo: " << yytext << std::endl;
  BEGIN(end_attr);
}
  /* Esperamos siguiente atributo */
<end_attr>{comma} { 
  BEGIN(expect_attr); 
}

  /* Terminando de procesar atributos */
<expect_first_attr,end_attr>{attrend} { 
  BEGIN(expect_content);
  current_content = "";
}
<mark>{blanks} { 
  BEGIN(expect_content);
  current_content = "";
}

  /* Leemos archivo o contenido */
<expect_content,newline>{content} {
  if (current_content.length() > 0) current_content += "\n";
  current_content += yytext;
}

<newline><<EOF>> {
  if (current_content.length() > 0)
    std::cout << "Contenido de la marca: " << current_content << std::endl;

  return 0;
}

{comment}         {;}

<INITIAL>\n       { lines++; }
\n                { lines++; BEGIN(newline); }

.                 { std::cerr << "Error in line " << lines << "." << std::endl; return -1; }

%%

int main(int argc, char* argv[]) {
  if (argc > 1) {
    yyin = fopen(argv[1], "rt");

    if (!yyin) {
      std::cout << "El archivo " << argv[1] << " no se puede abrir." << std::endl;
    }
  }

  lines = 1;
  current_content = "";

  int parse_state = yylex();
  
  if (parse_state != 0)
    return parse_state;

  return 0;
}