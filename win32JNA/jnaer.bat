set GRADLE_HOME=D:\Tooldev\gradle-1.0-milestone-2
set JAVA_HOME=c:\opt\jdk

set PATH=%GRADLE_HOME%/bin;%JAVA_HOME%/bin

::set VISUAL_STUDIO_HOME=../header/Microsoft Visual Studio 10.0
::set WINDOWS_SDK_HOME=../header/Microsoft SDKs/Windows/v7.0A

::call gradle clean jar
::call gradle jar
gradle %*
