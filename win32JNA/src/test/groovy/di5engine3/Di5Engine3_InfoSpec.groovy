package di5engine3;

import spock.lang.*


class Di5Engine3_InfoSpec extends Specification {

    def "バージョン情報を取得します"() {
        expect:
            Di5Engine3.RD5GetVersionR1() == 50463236
    }

    def "コピーライトメッセージを取得します"() {
        expect:
            Di5Engine3.RD5GetSerialR1() == ''
    }

    def "バージョン情報や、コピーライトメッセージを取得します"() {
        expect:
            Object[] ret =Di5Engine3.RD5GetVersion()
            ret[0] == 50463236
            ret[1] == '(C)2001-2010 Turbo Data Laboratories, Inc.'
    }

}
