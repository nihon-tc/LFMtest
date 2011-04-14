package di5engine3;

import com.sun.jna.*;
import com.sun.jna.ptr.*;
import di5engine3.Di5Engine3Library;

public class Di5Engine3{

	/**
	 * バージョン情報を取得します。
	 * @param[out]	anVersion	バージョン番号
	*/
	public static int RD5GetVersionR1(){
		IntByReference version = new IntByReference();
		int retID = Di5Engine3Library.INSTANCE.RD5GetVersionR1(version);
		return version.getValue();
	}

	/**
	 * コピーライトメッセージを取得します。
	 * @param[out]	szCopyright	コピーライトメッセージ
	*/
	public static String RD5GetSerialR1(){
		Pointer serial = Di5Engine3Library.INSTANCE.RD5GetSerialR1();
		return serial.getString(0);
	}

	/**
	 * バージョン情報や、コピーライトメッセージを取得します。
	 * @param[out]	anVersion	バージョン配列
	 * @param[out]	szCopyright	コピーライトメッセージ
	*/
	public static Object[] RD5GetVersion(){
		IntByReference version_ = new IntByReference();
		Pointer serial_ = new Memory(Di5Engine3Library.D5_VERSION_STRING_SIZE);

		Di5Engine3Library.INSTANCE.RD5GetVersion(version_,serial_);

		//System.out.println("[version_="+ version_.getValue() +"]");
		//System.out.println("[serial_="+ serial_.getString(0) + "]");

		return new Object[]{version_.getValue(),serial_.getString(0)};
	}
}
