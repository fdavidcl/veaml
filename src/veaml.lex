  /* This Source Code Form is subject to the terms of the Mozilla Public
     License, v. 2.0. If a copy of the MPL was not distributed with this
     file, You can obtain one at http://mozilla.org/MPL/2.0/.

     Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

%{
#include <iostream>
#include <string>
#include <cstdio>
#include "mark.h"
#include "clip.h"
#include "timeline.h"
#include "video.h"
#include "image.h"
#include "audio.h"

int lines;
veaml::Timeline * current_timeline;
bool adding_timeline = false;
veaml::Mark * current_mark;
veaml::attr_t current_attr;
std::string current_content;

int assign_content();
int process_timeline();
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
alpha       [A-Za-z0-9]
time        ([0-9]*\.|[0-9]+\.?){1,2}([0-9]*)?
blank       [\ \t]
blanks      {blank}+

mark        %{low}+

attrbegin   \{
attr        {low}+
colon       {blanks}?:{blanks}?
attrvalue   ({alpha}|_|\-)+|{time}
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
  int status = assign_content();
  if (status < 0) return status;
  
  /* Comenzamos lectura de nueva marca */
  std::string mark_text(yytext);

  adding_timeline = mark_text == "%timeline";

  if (adding_timeline) {
    if (current_timeline != 0) { // Ya teníamos un timeline en el archivo
      int proc = process_timeline();

      if (!proc)
        return proc;
    }

    current_mark = new veaml::Timeline();
    current_timeline = static_cast<veaml::Timeline*>(current_mark);
    BEGIN(mark);

  // Aceptamos la marca video
  } else if (mark_text == "%video") {
    current_mark = new veaml::Video;
    BEGIN(mark);

  // Aceptamos la marca audio
  } else if (mark_text == "%audio") {
    current_mark = new veaml::Audio;
    BEGIN(mark);

  // Marca no reconocida
  } else {
    std::cerr << "Error (línea " << lines << "): La marca " 
      << mark_text << " no es válida!" << std::endl;
    return -1;
  }
}

  /* La marca tiene atributos */
<mark>{attrbegin} { BEGIN(expect_first_attr); }

<expect_first_attr,expect_attr>{attr} {
  std::string cur_attr(yytext);
  bool found = false;

  int size = sizeof(veaml::attr_names) / sizeof(std::string);

  for (int i = 0; i < size && !found; ++i)
    if (cur_attr == veaml::attr_names[i]) {
      found = true;
      current_attr = static_cast<veaml::attr_t>(i);
    }

  BEGIN(expect_colon);
}

<expect_colon>{colon} { 
  BEGIN(expect_value);
}

<expect_value>{attrvalue} {
  if (current_mark != 0) {
    if (current_mark->set(current_attr, std::string(yytext)))
      std::cerr << "Añadido atributo con valor -" << yytext << "-." << std::endl;
  }

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
  int fin = assign_content();

  if (fin != 0)
    return fin;

  return process_timeline();
}

{comment}         {;}

<INITIAL>\n       { lines++; }
\n                { lines++; BEGIN(newline); }

. {
  std::cerr << "Error de sintaxis (línea " << lines << ")." << std::endl; return -1; 
}

%%

int assign_content() {
  if (current_content.length() > 0 && current_mark != 0) {
    if (!(current_mark->set(veaml::CONTENT, current_content))) {
      std::cerr << "Error (línea " << lines << 
        "): El contenido de la marca no es válido." << std::endl;
      return -2;
    }

    if (current_timeline != 0 && !adding_timeline)
      current_timeline->add(*(dynamic_cast<veaml::Clip*>(current_mark)));
  }

  return 0;
}

int process_timeline() {
  if (!current_timeline->output()) {
    std::cerr << "Error al procesar la salida." << std::endl;
    return -3;
  }

  return 0;
}

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