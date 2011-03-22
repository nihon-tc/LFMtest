package di5engine3;
import com.ochafik.lang.jnaerator.runtime.Structure;
/**
 * <i>native declaration : inc\rdi5api.h</i><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.free.fr/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public class TREnvironment extends Structure<TREnvironment, TREnvironment.ByValue, TREnvironment.ByReference > {
	/**
	 * < �R���s���[�^����<br>
	 * C type : char[D5_MAX_STRING_LENGTH_OS]
	 */
	public byte[] HostName = new byte[(di5engine3.Di5Engine3Library.D5_MAX_STRING_LENGTH_OS)];
	/// < OS�^�C�v
	public int OSType;
	/// < OS�̃��W���[�E�o�[�W�����ԍ�
	public int OSMajorVersion;
	/// < OS�̃}�C�i�[�E�o�[�W�����ԍ�
	public int OSMinorVersion;
	/// < �V�X�e���̃v���Z�b�T��A�[�L�e�N�`��
	public int MachineArchitecture;
	/// < �V�X�e���̃G���f�B�A���E�^�C�v
	public int Endian;
	/// < LFM�G���W���̃r�b�g��
	public int ELF;
	/// < �V�X�e���̃v���Z�b�T��
	public int ProcessorCount;
	/// < ���g�p
	public int ProcessType;
	/**
	 * < OS�̊����R�[�h<br>
	 * C type : char[32]
	 */
	public byte[] OSCharCode = new byte[(32)];
	/**
	 * < DB�����R�[�h<br>
	 * C type : char[32]
	 */
	public byte[] DBCharCode = new byte[(32)];
	public TREnvironment() {
		super();
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected TREnvironment newInstance() { return new TREnvironment(); }
	public static TREnvironment[] newArray(int arrayLength) {
		return Structure.newArray(TREnvironment.class, arrayLength);
	}
	public static class ByReference extends TREnvironment implements Structure.ByReference {
		
	};
	public static class ByValue extends TREnvironment implements Structure.ByValue {
		
	};
}