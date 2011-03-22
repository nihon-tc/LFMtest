package di5numeric;
import com.ochafik.lang.jnaerator.runtime.LibraryExtractor;
import com.ochafik.lang.jnaerator.runtime.MangledFunctionMapper;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.NativeLibrary;
/**
 * JNA Wrapper for library <b>Di5Numeric</b><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.free.fr/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public interface Di5NumericLibrary extends Library {
	public static final java.lang.String JNA_LIBRARY_NAME = LibraryExtractor.getLibraryPath("Di5Numeric", true, di5numeric.Di5NumericLibrary.class);
	public static final NativeLibrary JNA_NATIVE_LIB = NativeLibrary.getInstance(di5numeric.Di5NumericLibrary.JNA_LIBRARY_NAME, com.ochafik.lang.jnaerator.runtime.MangledFunctionMapper.DEFAULT_OPTIONS);
	public static final Di5NumericLibrary INSTANCE = (Di5NumericLibrary)Native.loadLibrary(di5numeric.Di5NumericLibrary.JNA_LIBRARY_NAME, di5numeric.Di5NumericLibrary.class, com.ochafik.lang.jnaerator.runtime.MangledFunctionMapper.DEFAULT_OPTIONS);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int D5_MAX_ROUND_NAME_LENGTH = (16);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_HALF_DOWN = (5);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_UP = (0);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_HALF_EVEN = (6);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_INFO_TRUNCATED = (2);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_INFO_NAN = (1);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_DOWN = (1);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_HALF_UP = (4);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_CEILING = (2);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_INFO_OVERFLOW = (3);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_INFO_UNDERFLOW = (4);
	/// <i>native declaration : inc\numeric.h</i>
	public static final int NUMERIC_ROUND_FLOOR = (3);
	/**
	 * Performs addition. All parameters are supposed to have the same scale.
	 * @param[in] a unscaled addend
	 * @param[in] b unscaled augend
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericAdd(const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:154</i>
	 */
	int RD5NumericAdd(di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs subtraction. All parameters are supposed to have the same scale.
	 * @param[in] a unscaled minuend
	 * @param[in] b unscaled subtrahend
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericSub(const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:167</i>
	 */
	int RD5NumericSub(di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs comparison. All parameters are supposed to have the same scale. NaN is assumed to be smaller than any Numeric that is not NaN. Two NaNs are assumed to be equal.
	 * @param[in] a unscaled value to be compared with b
	 * @param[in] b unscaled value to be compared with a
	 * @retval 1 if b is bigger than a.
	 * @retval 0 if b is equal to a.
	 * @retval -1 if b is smaller than a.<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericCmp(const Numeric*, const Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:177</i>
	 */
	int RD5NumericCmp(di5numeric.Numeric a, di5numeric.Numeric b);
	/**
	 * Performs multiplication.
	 * @param[in,out] a unscaled multiplier
	 * @param[in] b 32-bit signed integer multiplicand
	 * @retval 0 Success. The result is stored in a. The input and output have the same scale.  
	 * @retval NUMERIC_INFO_NAN a is a NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. a is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. a is set NaN.
	 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericMul(Numeric*, NUMERIC_INT32)</code><br>
	 * <i>native declaration : inc\numeric.h:189</i>
	 */
	int RD5NumericMul(di5numeric.Numeric a, int b);
	/**
	 * Performs division.
	 * @param[in,out] a unscaled dividend
	 * @param[in] info_a->rounding_mode the rounding mode to be applied
	 * @param[in] b 32-bit signed integer divisor
	 * @retval 0 Success. The result is stored in a. The input and output have the same scale.  
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in a. The input and output have the same scale.
	 * @retval NUMERIC_INFO_NAN a is a NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. a is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. a is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericDiv(Numeric*, NumericInfo*, NUMERIC_INT32)</code><br>
	 * <i>native declaration : inc\numeric.h:203</i>
	 */
	int RD5NumericDiv(di5numeric.Numeric a, di5numeric.NumericInfo info_a, int b);
	/**
	 * Sets a Numeric zero.
	 * @param[out] c buffer to be set zero (The caller must prepare the buffer beforehand.)<br>
	 * Original signature : <code>void RD5NumericSetZero(Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:209</i>
	 */
	void RD5NumericSetZero(di5numeric.Numeric c);
	/**
	 * Tests whether a Numeric is zero.
	 * @param[in] c unscaled value to be tested
	 * @retval zero if c is not zero.
	 * @retval non-zero if c is zero.<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericIsZero(const Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:217</i>
	 */
	int RD5NumericIsZero(di5numeric.Numeric c);
	/**
	 * Sets a Numeric NaN.
	 * @param[out] c buffer to be set NaN (The caller must prepare the buffer beforehand.)<br>
	 * Original signature : <code>void RD5NumericSetNan(Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:223</i>
	 */
	void RD5NumericSetNan(di5numeric.Numeric c);
	/**
	 * Tests whether a Numeric is NaN.
	 * @param[in] c unscaled value to be tested
	 * @retval zero if c is not NaN.
	 * @retval non-zero if c is NaN.<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericIsNan(const Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:231</i>
	 */
	int RD5NumericIsNan(di5numeric.Numeric c);
	/**
	 * FOR DEBUGGING PURPOSE<br>
	 * Original signature : <code>void dump(const Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:236</i>
	 */
	void dump(di5numeric.Numeric c);
	/**
	 * Performs addition.
	 * @param[in] info_a->scale scale of a
	 * @param[in] info_b->scale scale of b
	 * @param[in] info_c->scale scale of c
	 * @param[in] info_c->rounding_mode the rounding mode to be applied
	 * @param[in] a unscaled addend
	 * @param[in] b unscaled augend
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescalingAdd(const NumericInfo*, const NumericInfo*, const NumericInfo*, const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:260</i>
	 */
	int RD5NumericRescalingAdd(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_b, di5numeric.NumericInfo info_c, di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs subtraction.
	 * @param[in] info_a->scale scale of a
	 * @param[in] info_b->scale scale of b
	 * @param[in] info_c->scale scale of c
	 * @param[in] info_c->rounding_mode the rounding mode to be applied
	 * @param[in] a unscaled minuend
	 * @param[in] b unscaled subtrahend
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescalingSub(const NumericInfo*, const NumericInfo*, const NumericInfo*, const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:278</i>
	 */
	int RD5NumericRescalingSub(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_b, di5numeric.NumericInfo info_c, di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs subtraction.
	 * @param[in] info_a->scale scale of a
	 * @param[in] info_b->scale scale of b
	 * @param[in] info_c->scale scale of c
	 * @param[in] info_c->rounding_mode the rounding mode to be applied
	 * @param[in] a unscaled multiplier
	 * @param[in] b unscaled multiplicand
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescalingMul(const NumericInfo*, const NumericInfo*, const NumericInfo*, const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:296</i>
	 */
	int RD5NumericRescalingMul(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_b, di5numeric.NumericInfo info_c, di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs division.
	 * @param[in] info_a->scale scale of a
	 * @param[in] info_b->scale scale of b
	 * @param[in] info_c->scale scale of c
	 * @param[in] info_c->rounding_mode the rounding mode to be applied
	 * @param[in] a unscaled dividend
	 * @param[in] b unscaled divisor
	 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescalingDiv(const NumericInfo*, const NumericInfo*, const NumericInfo*, const Numeric*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:314</i>
	 */
	int RD5NumericRescalingDiv(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_b, di5numeric.NumericInfo info_c, di5numeric.Numeric a, di5numeric.Numeric b, di5numeric.Numeric c);
	/**
	 * Performs comparison. NaN is assumed to be smaller than any Numeric that is not a NaN. Two NaNs are assumed to be equal.
	 * @param[in] info_a->scale scale of a
	 * @param[in] info_b->scale scale of b
	 * @param[in] a unscaled value to be compared with b
	 * @param[in] b unscaled value to be compared with a
	 * @retval 1 if b is bigger than a.
	 * @retval 0 if b is equal to a.
	 * @retval -1 if b is smaller than a.<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescalingCmp(const NumericInfo*, const NumericInfo*, const Numeric*, const Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:326</i>
	 */
	int RD5NumericRescalingCmp(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_b, di5numeric.Numeric a, di5numeric.Numeric b);
	/**
	 * Performs rounding towards positive infinity. Equlvalent to numeric_round with info_c->rounding_mode=NUMERIC_ROUND_CEILING.
	 * @param[in] info_c->scale scale of c
	 * @param[in] prec precision (number of fractional digits) of the result 
	 * @param[in,out] c unscaled value to be rounded towards positive infinity
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericCeil(const NumericInfo*, const NUMERIC_INT32, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:339</i>
	 */
	int RD5NumericCeil(di5numeric.NumericInfo info_c, int prec, di5numeric.Numeric c);
	/**
	 * Performs rounding towards negative infinity. Equlvalent to numeric_round with info_c->rounding_mode=NUMERIC_ROUND_FLOOR.
	 * @param[in] info_c->scale scale of c
	 * @param[in] prec precision (number of fractional digits) of the result
	 * @param[in,out] c unscaled value to be rounded towards negative infinity
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericFloor(const NumericInfo*, const NUMERIC_INT32, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:352</i>
	 */
	int RD5NumericFloor(di5numeric.NumericInfo info_c, int prec, di5numeric.Numeric c);
	/**
	 * Performs rounding.
	 * @param[in] info_c->scale scale of c
	 * @param[in] info_c->rounding_mode rounding mode to be applied
	 * @param[in] prec precision (number of fractional digits) of the result
	 * @param[in,out] c unscaled value to be rounded
	 * @retval 0 Success. The result is stored in c.
	 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
	 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
	 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
	 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
	 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW<br>
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRound(const NumericInfo*, const NUMERIC_INT32, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:367</i>
	 */
	int RD5NumericRound(di5numeric.NumericInfo info_c, int prec, di5numeric.Numeric c);
	/**
	 * Original signature : <code>NUMERIC_INT32 RD5NumericRescale(const NumericInfo*, const NumericInfo*, const Numeric*, Numeric*)</code><br>
	 * <i>native declaration : inc\numeric.h:369</i>
	 */
	int RD5NumericRescale(di5numeric.NumericInfo info_a, di5numeric.NumericInfo info_c, di5numeric.Numeric a, di5numeric.Numeric c);
}