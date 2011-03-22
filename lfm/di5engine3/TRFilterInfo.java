package di5engine3;
import com.ochafik.lang.jnaerator.runtime.Structure;
/**
 * <i>native declaration : inc\rdi5api.h</i><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.free.fr/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public class TRFilterInfo extends Structure<TRFilterInfo, TRFilterInfo.ByValue, TRFilterInfo.ByReference > {
	/// < �ʒu���̃T�C�Y
	public int PVSize;
	/// < �l���X�g�̃f�[�^�^�𐮐�����������
	public int VLType;
	/// < �l���X�g�̊e�l�̕�
	public int VLWidth;
	/// < �l���X�g�̃T�C�Y�i���j
	public int VLSize;
	/// < �l���X�g��������̏ꍇ�A������i�[�̈�̃T�C�Y
	public int CharAreaSize;
	/**
	 * < ���ږ���<br>
	 * C type : char[D5_MAX_NAME_LENGTH + 8]
	 */
	public byte[] FilterName = new byte[(di5engine3.Di5Engine3Library.D5_MAX_NAME_LENGTH + 8)];
	public TRFilterInfo() {
		super();
	}
	/**
	 * @param PVSize < �ʒu���̃T�C�Y<br>
	 * @param VLType < �l���X�g�̃f�[�^�^�𐮐�����������<br>
	 * @param VLWidth < �l���X�g�̊e�l�̕�<br>
	 * @param VLSize < �l���X�g�̃T�C�Y�i���j<br>
	 * @param CharAreaSize < �l���X�g��������̏ꍇ�A������i�[�̈�̃T�C�Y<br>
	 * @param FilterName < ���ږ���<br>
	 * C type : char[D5_MAX_NAME_LENGTH + 8]
	 */
	public TRFilterInfo(int PVSize, int VLType, int VLWidth, int VLSize, int CharAreaSize, byte FilterName[]) {
		super();
		this.PVSize = PVSize;
		this.VLType = VLType;
		this.VLWidth = VLWidth;
		this.VLSize = VLSize;
		this.CharAreaSize = CharAreaSize;
		if (FilterName.length != this.FilterName.length) 
			throw new java.lang.IllegalArgumentException("Wrong array size !");
		this.FilterName = FilterName;
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected TRFilterInfo newInstance() { return new TRFilterInfo(); }
	public static TRFilterInfo[] newArray(int arrayLength) {
		return Structure.newArray(TRFilterInfo.class, arrayLength);
	}
	public static class ByReference extends TRFilterInfo implements Structure.ByReference {
		
	};
	public static class ByValue extends TRFilterInfo implements Structure.ByValue {
		
	};
}