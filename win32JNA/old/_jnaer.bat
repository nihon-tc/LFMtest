cd /d %0\..

::'jna.library.path'
::'java.library.path'

::set GNUSTEP_HOME=D:\Tooldev\GNUstep
::set VISUAL_STUDIO_INCLUDES=%GNUSTEP_HOME%/GNUstep/System/Library/Headers

::set VISUAL_STUDIO_HOME=C:\Program Files\Microsoft Visual Studio 10.0
::set WINDOWS_SDK_HOME=C:\Program Files\Microsoft SDKs\Windows\v7.0A

set VISUAL_STUDIO_HOME=../header/Microsoft Visual Studio 10.0
set WINDOWS_SDK_HOME=../header/Microsoft SDKs/Windows/v7.0A

set JAVA_HOME=c:\opt\jdk
set INCPATH=./inc


:: ===copy==
mkdir libraries
pushd libraries
mkdir win32
mkdir win64
mkdir Linux-amd64
mkdir Linux-x86_64
popd

copy /Y master\win32\Di5Engine3.dll libraries\win32\rdi5api.dll
copy /Y master\win32\Di5Numeric.dll libraries\win32\rdi5numeric.dll
copy /Y master\win32\Di5Engine3.dll libraries\win32\rdi5apiext.dll

copy /Y master\win64\Di5Engine3.dll libraries\win64\rdi5api.dll
copy /Y master\win64\Di5Numeric.dll libraries\win64\rdi5numeric.dll
copy /Y master\win64\Di5Engine3.dll libraries\win64\rdi5apiext.dll

copy /Y master\x86_64\libDi5Engine3.so libraries\Linux-amd64\librdi5api.so
copy /Y master\x86_64\libDi5Numeric.so libraries\Linux-amd64\librdi5numeric.so
copy /Y master\x86_64\libDi5Engine3.so libraries\Linux-amd64\librdi5apiext.so

REM case 0
::set CMD_OPT=-library rdi5api rdi5api.h rdi5apiext.h -library rdi5numeric numeric.h

REM case 1
::set CMD_OPT=-library rdi5api rdi5api.h Di5Engine3.dll
::set CMD_OPT=%CMD_OPT% -library rdi5numeric numeric.h Di5Numeric.dll
::set CMD_OPT=%CMD_OPT% -library rdi5apiext rdi5apiext.h Di5Engine3.dll

REM case 2
set CMD_OPT=-library rdi5api %INCPATH%/rdi5api.h %INCPATH%/di5api.h libraries/win32/rdi5api.dll
set CMD_OPT=%CMD_OPT% -library rdi5numeric %INCPATH%/numeric.h %INCPATH%/numeric.h libraries/win32/rdi5numeric.dll
set CMD_OPT=%CMD_OPT% -library rdi5apiext %INCPATH%/rdi5apiext.h libraries/win32/rdi5apiext.dll

REM case 3
::set CMD_OPT=-library rdi5api rdi5api.h di5api.h numeric.h di5error.h tmp/rdi5api.dll 
::set CMD_OPT=%CMD_OPT% -library rdi5numeric numconv.h numeric.h tmp/rdi5numeric.dll 
::set CMD_OPT=%CMD_OPT% -library rdi5apiext rdi5apiext.h di5api.h numeric.h di5error.h tmp/rdi5apiext.dll




::set OTHER_LIB=D:\work\LFM\lfmcore\win32JNA\tmp
::set OTHER_LIB=./tmp

%JAVA_HOME%/bin/java -jar jnaerator-0.9.5.jar %CMD_OPT% -o . -I./inc -jar lib/lfm.jar -v -DD5APICALL=__stdcall
%JAVA_HOME%/bin/jar uf lib/lfm.jar libraries


:: see http://d.hatena.ne.jp/syuu1228/20100316/1268737011
:: see http://www.dreammind.net/pukiwiki/index.php?C%2B%2B
::
::#!/bin/sh
::UNAME=`uname`
::if[ $UNAME = "Darwin" ]; then
::	LIRARY=libminiupnpc.dylib
::elif [ $UNAME = "Linux" ]; then
::	LIBRARY=libminiupnpc.so
::fi
::
::java -jar jnaerator.jar -library miniupnpc miniupnpc.h declspec.h upnpcommands.h upnpreplyparse.h igd_desc_parse.h miniwget.h upnperrors.h $LIBRARY \
::-package fr.free.miniupnp -o . -jar miniupnpc_$UNAME.jar -v

