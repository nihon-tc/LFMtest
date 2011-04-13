//runtest.groovy
import di5engine3.*
import di5numeric.*

import com.sun.jna.ptr.*
import com.sun.jna.*

IntByReference version = new IntByReference()
Di5Engine3Library.INSTANCE.RD5GetVersionR1(version)
println "[version=${version.getValue()}]"

Pointer serial = Di5Engine3Library.INSTANCE.RD5GetSerialR1()
println "[serial=${serial.dump()}/${serial.getString(0)}]"


IntByReference version2 = new IntByReference()
Pointer serial2 = new Memory(1024)

Di5Engine3Library.INSTANCE.RD5GetVersion(version2,serial2)
println "[version2=${version2.getValue()}]"
println "[serial2=${serial2.dump()}/${serial2.getString(0)}]"


println "------------------------------"
println "[version=${Di5Engine3.RD5GetVersionR1()}]"
println "[serial=${Di5Engine3.RD5GetSerialR1()}]"

/*
Integer version_f
String serial_f

Di5Engine3.RD5GetVersion(version_f,serial_f)

println "[version_f=${version_f}]"
println "[serial_f=${serial_f}]"
*/
