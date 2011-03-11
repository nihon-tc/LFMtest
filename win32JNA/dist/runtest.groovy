//runtest.groovy
import di5engine3.*
import di5numeric.*

import com.sun.jna.ptr.*
import com.sun.jna.*

IntByReference version = new IntByReference()
Di5Engine3Library.INSTANCE.RD5GetVersionR1(version)
println "version=${version.getValue()}"

Pointer serial = Di5Engine3Library.INSTANCE.RD5GetSerialR1()
println "serial=${serial.dump()}"


IntByReference version2 = new IntByReference()
Pointer serial2 = new Pointer()

Di5Engine3Library.INSTANCE.RD5GetVersion(version2,serial2)
println "version2=${version2.getValue()}"
println "serial2=${serial2.dump()}"
