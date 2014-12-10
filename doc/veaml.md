---
title: "Veaml: Un lenguaje de marcado para edición de vídeo"
author: David Charte
---

# Introducción

Los métodos actuales de edición de vídeo no profesional se basan en 
la utilización de programas muy complejos y tediosos, lo cual dificulta la
creación de contenido audiovisual en Internet por parte de personas
con pocos conocimientos o falta de tiempo para el manejo de los mismos.

Veaml es una propuesta de lenguaje de marcado que permite realizar las
operaciones clásicas de edición de vídeos, entre otras, recortar, unir,
mezclar y superponer vídeos. Para conformar un lenguaje con una notación
simple y legible se basa en Haml, el lenguaje de marcado de abstracción
de HTML.

# ¿Por qué un lenguaje de marcado?

## Rápido de aprender

Los programas más utilizados para edición de vídeo proporcionan una
funcionalidad muy amplia, lo que los hace muy complejos de usar.
Aprender los procedimientos básicos de edición (recortar, pegar, etc.)
puede suponer una inversión de tiempo importante, e incluso requerir de
manuales acerca de la herramienta.

Un lenguaje de marcado es muy simple de aprender ya que los únicos
elementos de los que consta son marcas, que a su vez tienen atributos.
La forma de escribir y organizar estas marcas es intuitiva, luego 
serán necesarios apenas unos minutos para familiarizarse con el lenguaje.

## Reutilizable

Las personas que editan vídeo actualmente pueden querer obtener varios
vídeos con el mismo formato (por ejemplo, intro-contenido-outro), lo que
hace tediosa la edición de varios proyectos de edición, uno para cada
vídeo.

Un archivo de Veaml, sin embargo, es reutilizable, en el sentido
de que se puede ejecutar para distintos vídeos (simplemente sustituyendo
los ficheros referenciados por otros) sin necesidad de reescribir lo mismo
una y otra vez.

## Fácil de compartir

Si varias personas se ponen de acuerdo para componer un vídeo, y cada
una se encarga de una tarea (música, animación, guion, etc.), entonces
es muy útil poder compartir una representación del vídeo final para
proporcionar la información sobre el tiempo de cada escena, etc.

## Separa edición y procesamiento

Los programas actuales de edición cumplen la tarea de representar el vídeo
editado y procesarlo en sí, de forma que si ocurre un fallo durante el
procesamiento del vídeo, se pueden perder datos sobre la edición.

Al utilizar un archivo de texto Veaml para la edición y un *parser* para
el procesamiento, nunca perderemos nuestro proyecto, aunque el procesamiento
provoque errores.


