set GRADLE_HOME=D:\Tooldev\gradle-1.0-milestone-3
set JAVA_HOME=c:\opt\jdk
set JAVA_OPTS=-Dgroovy.source.encoding=UTF-8 -Dfile.encoding=UTF-8
::set CMD_HOME=C:\WINDOWS\system32

set PATH=%GRADLE_HOME%/bin;%JAVA_HOME%/bin;%CMD_HOME%

::set VISUAL_STUDIO_HOME=../header/Microsoft Visual Studio 10.0
::set WINDOWS_SDK_HOME=../header/Microsoft SDKs/Windows/v7.0A


::call gradle clean jar
call gradle test %*
::call gradle jar > log 2>&1
::call gradle %*
::chcp 65001

::pause