package di5engine3;

public class Di5Engine3{

	/**
	 * バージョン情報を取得します。
	 * @param[out]	anVersion	バージョン番号
	*/
	int RD5GetVersionR1(){
		IntByReference version = new IntByReference()
		int retID = Di5Engine3Library.INSTANCE.RD5GetVersionR1(version)
		return version.getValue()
	}

	/**
	 * コピーライトメッセージを取得します。
	 * @param[out]	szCopyright	コピーライトメッセージ
	*/
	String RD5GetSerialR1(){
		Pointer serial = Di5Engine3Library.INSTANCE.RD5GetSerialR1()
		return serial.getString(0)
	}

	/**
	 * バージョン情報や、コピーライトメッセージを取得します。
	 * @param[out]	anVersion	バージョン配列
	 * @param[out]	szCopyright	コピーライトメッセージ
	*/
	void RD5GetVersion(Integer version,String serial){
		IntByReference version_ = new IntByReference()
		Pointer serial_ = new Memory(Di5Engine3Library.D5_VERSION_STRING_SIZE)

		Di5Engine3Library.INSTANCE.RD5GetVersion(version_,serial_)
		version = version_.getValue()
		serial = serial2.getString(0)
	}
}
