
LFM Consortium http://www.lfm-consortium.org/
distribution library test using groovy

dll(so) Provider 
	English Page : http://www.turbo-data.co.jp/english/english.html
	Japanise Page : http://www.turbo-data.co.jp/index.html


----
need enviroments 
	jdk6u24
	gradlew.bat or sh gradlew
		or
	jdk6u24
	gradle milestorne 1 http://www.gradle.org/


win32JNA
	1)jnaer.bat running
	2)dist folder copy to test enviroments


report:
	dist
		run.bat > out_win32.log 2>&1
		run.bat > out_win64.log 2>&1
		sh run.sh >& out_cent64.log
		sh run.sh >& out_cent64.log
