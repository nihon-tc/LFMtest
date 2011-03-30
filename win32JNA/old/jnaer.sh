#cd /d %0\..

#'jna.library.path'
#'java.library.path'

#set GNUSTEP_HOME=D:\Tooldev\GNUstep
#set VISUAL_STUDIO_INCLUDES=%GNUSTEP_HOME%/GNUstep/System/Library/Headers

#set VISUAL_STUDIO_HOME=C:\Program Files\Microsoft Visual Studio 10.0
#set WINDOWS_SDK_HOME=C:\Program Files\Microsoft SDKs\Windows\v7.0A

JAVA_HOME=/usr/bin/java
INCPATH=./inc

mkdir tmp
cp -f libDi5Engine3.so ./tmp/rdi5api.so
cp -f libDi5Numeric.so ./tmp/rdi5numeric.so
cp -f libDi5Engine3.so ./tmp/rdi5apiext.so


#REM case 0
#set CMD_OPT=-library rdi5api rdi5api.h rdi5apiext.h -library rdi5numeric numeric.h

#REM case 1
#set CMD_OPT=-library rdi5api rdi5api.h Di5Engine3.so
#set CMD_OPT=%CMD_OPT% -library rdi5numeric numeric.h Di5Numeric.so
#set CMD_OPT=%CMD_OPT% -library rdi5apiext rdi5apiext.h Di5Engine3.so

#REM case 2
#CMD_OPT=-library rdi5api $INCPATH/rdi5api.h $INCPATH/di5api.h ./tmp/rdi5api.so
#CMD_OPT=$CMD_OPT -library rdi5numeric $INCPATH/numeric.h $INCPATH/numeric.h ./tmp/rdi5numeric.so
#CMD_OPT=$CMD_OPT -library rdi5apiext $INCPATH/rdi5apiext.h ./tmp/rdi5apiext.so

CMD_OPT=-library ./tmp/rdi5api.so $INCPATH/rdi5api.h $INCPATH/di5api.h 
CMD_OPT=$CMD_OPT ./tmp/rdi5numeric.so $INCPATH/numeric.h $INCPATH/numeric.h 
CMD_OPT=$CMD_OPT ./tmp/rdi5apiext.so $INCPATH/rdi5apiext.h 

#REM case 3
#set CMD_OPT=-library rdi5api rdi5api.h di5api.h numeric.h di5error.h tmp/rdi5api.so 
#set CMD_OPT=%CMD_OPT% -library rdi5numeric numconv.h numeric.h tmp/rdi5numeric.so 
#set CMD_OPT=%CMD_OPT% -library rdi5apiext rdi5apiext.h di5api.h numeric.h di5error.h tmp/rdi5apiext.so



#set OTHER_LIB=D:\work\LFM\lfmcore\win32JNA\tmp
#set OTHER_LIB=./tmp
#$JAVA_HOME -jar jnaerator-0.9.5.jar $CMD_OPT -o . -I./inc -jar ./lib/lfm.jar -v -DD5APICALL=__stdcall

$JAVA_HOME -jar jnaerator-0.9.5.jar $CMD_OPT -o . -I./inc -jar ./lib/lfm.jar


# see http://d.hatena.ne.jp/syuu1228/20100316/1268737011
# see http://www.dreammind.net/pukiwiki/index.php?C%2B%2B
#
##!/bin/sh
#UNAME=`uname`
#if[ $UNAME = "Darwin" ]; then
#	LIRARY=libminiupnpc.dylib
#elif [ $UNAME = "Linux" ]; then
#	LIBRARY=libminiupnpc.so
#fi
#
#java -jar jnaerator.jar -library miniupnpc miniupnpc.h declspec.h upnpcommands.h upnpreplyparse.h igd_desc_parse.h miniwget.h upnperrors.h $LIBRARY \
#-package fr.free.miniupnp -o . -jar miniupnpc_$UNAME.jar -v

