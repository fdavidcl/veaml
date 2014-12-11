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

# ¿Cómo escribir Veaml?

Componer un archivo Veaml es muy sencillo. Para ello, basta con utilizar nuestro
editor de texto favorito y utilizar las marcas que forman el lenguaje. A
continuación un ejemplo:

~~~haml
/ Timeline es un contenedor que generará un único vídeo como salida

%timeline{width: 1920, height: 1080, videocodec: libx264, audiocodec: libfaac, fps: 24} srfc.mp4
  / Cada marca se puede delimitar
  %video{from:  .1.70, to:     .4, volume: 0} surface.mp4
  %video{from:  .7.50, to:     .8, volume: 0} surface.mp4
  %video{from:    .23, to:    .24, volume: 0} surface.mp4
  %video{from:    .27, to: .27.50, volume: 0} surface.mp4
  %video{from: .28.70, to:    .29, volume: 0} surface.mp4
  %video{from:    .42, to: .42.90, volume: 0} surface.mp4
  %video{from:    .46, to: .47.10, volume: 0} surface.mp4

  %audio{from:    .15, to: .21.50, start:  0} srfc.aac
~~~

## Timeline

La primera marca de un archivo Veaml será siempre `%timeline`, que servirá para
especificar los detalles de la salida que queremos: ancho y alto, nombre del 
archivo y datos sobre los códecs. Los atributos que acepta `%timeline` son: 

 - `width`: Especifica el ancho
 - `height`: Especifica el alto
 - `audiocodec`: El codificador para la salida de audio (por ejemplo, `libfaac`, `flac` o `libmp3lame`)
 - `videocodec`: El codificador para la salida de vídeo (por ejemplo, `libx264`, `libtheora` o `libvpx`)
 - `fps`: El número de frames por segundo (por defecto 25)
 - `samplerate`: El *sample rate* para el audio (por defecto 44100)

Tras indicar un `%timeline` se pueden añadir las marcas `%audio`, `%video` e 
`%image` deseadas, que conformarán el vídeo resultante. En un mismo archivo
Veaml puede haber varios timelines.

## Vídeo

La marca `%video` acepta los atributos:

 - `width`: Especifica el ancho
 - `height`: Especifica el alto
 - `top`: Especifica la posición desde el borde superior
 - `left`: Especifica la posición desde el borde izquierdo
 - `from`: Especifica el punto temporal del vídeo desde el que se incluirá
 - `to`: El punto temporal del vídeo hasta el que se incluirá
 - `start`: La posición temporal del timeline en la que comenzará el vídeo
 - `end`: La posición temporal del timeline en la que terminará el vídeo
 - `codec`: El decodificador para la entrada de vídeo
 - `volume`: El volumen, de 0 a 100 (por defecto 100)

Por defecto los clips añadidos se incluirán de forma secuencial, es
decir, se comenzará a reproducir cada clip cuando termine el anterior.
Para modificar este comportamiento recurrimos a los atributos `start`, `end`.

## Audio

La marca `%audio` acepta los atributos:

 - `from`: Especifica el punto temporal del audio desde el que se incluirá
 - `to`: El punto temporal del audio hasta el que se incluirá
 - `start`: La posición temporal del timeline en la que comenzará el audio
 - `end`: La posición temporal del timeline en la que terminará el audio
 - `codec`: El decodificador para la entrada de audio
 - `volume`: El volumen, de 0 a 100 (por defecto 100)


## Imagen

La marca `%image` acepta los atributos:

 - `width`: Especifica el ancho
 - `height`: Especifica el alto
 - `top`: Especifica la posición desde el borde superior
 - `left`: Especifica la posición desde el borde izquierdo
 - `to`: Duración de la imagen en pantalla
 - `start`: La posición temporal del timeline en la que comenzará a verse
 - `end`: La posición temporal del timeline en la que terminará de verse