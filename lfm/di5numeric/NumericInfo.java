package di5numeric;
import com.ochafik.lang.jnaerator.runtime.Structure;
/**
 * <i>native declaration : inc\numeric.h</i><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.free.fr/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public class NumericInfo extends Structure<NumericInfo, NumericInfo.ByValue, NumericInfo.ByReference > {
	/// C type : NUMERIC_INT32
	public int scale;
	/// C type : NUMERIC_INT32
	public int rounding_mode;
	public NumericInfo() {
		super();
	}
	/**
	 * @param scale C type : NUMERIC_INT32<br>
	 * @param rounding_mode C type : NUMERIC_INT32
	 */
	public NumericInfo(int scale, int rounding_mode) {
		super();
		this.scale = scale;
		this.rounding_mode = rounding_mode;
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected NumericInfo newInstance() { return new NumericInfo(); }
	public static NumericInfo[] newArray(int arrayLength) {
		return Structure.newArray(NumericInfo.class, arrayLength);
	}
	public static class ByReference extends NumericInfo implements Structure.ByReference {
		
	};
	public static class ByValue extends NumericInfo implements Structure.ByValue {
		
	};
}
