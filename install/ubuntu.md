# Veaml installation in Ubuntu

1. Descargar dependencias básicas
    
    `sudo apt-get install build-essentials cmake yasm`

1. Descargar dependencias de FFmpeg
    
    Los codecs que vayamos a usar deberán estar descargados junto
    a sus paquetes de desarrollo (acabados en `-dev`). Por ejemplo,
    para poder leer y codificar vídeo MP4 deberemos instalar
    `libx264-dev` y `libfdk-aac-dev`.

    Más información sobre los codecs disponibles en la 
    [guía de compilación](https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu)
    de FFmpeg

1. Descargar y compilar FFmpeg
    
    Utilizaremos los siguientes comandos para compilar e instalar FFmpeg:

    ~~~
    mkdir ~/ffmpeg_sources
    cd ~/ffmpeg_sources
    wget http://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2
    tar xjvf ffmpeg-snapshot.tar.bz2
    cd ffmpeg
    PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig"
    ./configure \
      --prefix="$HOME/ffmpeg_build" \
      --extra-cflags="-I$HOME/ffmpeg_build/include" \
      --extra-ldflags="-L$HOME/ffmpeg_build/lib" \
      --bindir="$HOME/bin" \
      --enable-gpl \
      --enable-libfdk-aac \
      --enable-libfreetype \
      --enable-libmp3lame \
      --enable-libtheora \
      --enable-libvorbis \
      --enable-libvpx \
      --enable-libx264 \
      --enable-nonfree \
      --enable-x11grab \
      --enable-libfaac \
      --enable-pic \
      --extra-ldexeflags=-pie
    PATH="$HOME/bin:$PATH" make
    make install
    make distclean
    hash -r
    ~~~

1. Descargar y compilar libopenshot

    ...

    `cmake ..`

    En el archivo CMakeCache.txt, modificaremos los caminos a
    las librerías de FFmpeg:

    ~~~
    //Path to a file.
    AVCODEC_INCLUDE_DIR:PATH=/home/user/ffmpeg_build/include
    
    //Path to a library.
    AVCODEC_LIBRARY:FILEPATH=/home/user/ffmpeg_build/lib/libavcodec.a
    
    //Path to a file.
    AVDEVICE_INCLUDE_DIR:PATH=/home/user/ffmpeg_build/include
    
    //Path to a library.
    AVDEVICE_LIBRARY:FILEPATH=/home/user/ffmpeg_build/lib/libavdevice.a
    
    //Path to a file.
    AVFORMAT_INCLUDE_DIR:PATH=/home/user/ffmpeg_build/include
    
    //Path to a library.
    AVFORMAT_LIBRARY:FILEPATH=/home/user/ffmpeg_build/lib/libavformat.a
    
    //Path to a file.
    AVUTIL_INCLUDE_DIR:PATH=/home/user/ffmpeg_build/include
    
    //Path to a library.
    AVUTIL_LIBRARY:FILEPATH=/home/user/ffmpeg_build/lib/libavutil.a
    
    (...)
    //Flags used by the linker.
    CMAKE_EXE_LINKER_FLAGS:STRING= -shared -lunittest++
    ~~~

    Y ejecutamos `make` y `make install`.

1. Compilar veaml
    
    `cd build/ && qmake && make && cd ..`
