
LFM Consortium http://www.lfm-consortium.org/
distribution library test using groovy

dll(so) Provider 
	English Page : http://www.turbo-data.co.jp/english/english.html
	Japanise Page : http://www.turbo-data.co.jp/index.html

DL version
	2010/11/10
	2011/03/12		=> 2011/04/01 download


----
need enviroments 
	jdk6u24
	gradlew.bat or sh gradlew
		or
	jdk6u24
	gradle milestorne 1 http://www.gradle.org/


win32JNA
	testing 
		dist folder copy to test enviroments
	recompile
		1)dll(so) master change?
			you gets dll/so from turbo-data
			master into copy
		2)jnaer.bat running
		3)create dist foloder

report:
	dist
		run.bat > out_win32.log 2>&1
		run.bat > out_win64.log 2>&1
		sh run.sh >& out_cent64.log
		sh run.sh >& out_ubuntu64.log
