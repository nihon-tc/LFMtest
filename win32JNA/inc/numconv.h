#ifndef _NUMPARSE_H
#define _NUMPARSE_H

#include "numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef double NUMERIC_IEEE754_DOUBLE; 

/* ERROR CODES */

/**
 * Return code indicating any number of leading characters are not a valid string representation of a Numeric.
 */
#define NUMERIC_ERROR_INVALID_FORMAT    (-1)

/**
 * Return code indicating the prepared buffer is too small to hold the result.
 */
#define NUMERIC_ERROR_BUFFER_TOO_SHORT  (-2)

/**
 * Translates the string representation of a Numeric into a Numeric.
 * @param[in] numstr the string representation
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 * @param[out] endptr buffer to hold the pointer to the character following the valid string representation if endptr is not null.
 *
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 * @retval NUMERIC_ERROR_INVALID_FORMAT if the string representation is not valid.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_OVERFLOW,NUMERIC_INFO_UNDERFLOW,NUMERIC_ERROR_INVALID_FORMAT
 *
 * @note
 *
 * Valid string representation is described by the following grammar.
 *
 * <table><tr><td>
 * \e NumericString : \e SIGN \e UnsignedNumericString
 *                  | \e UnsignedNumericString
 *                  ;
 *
 * \e UnsignedNumericString : \e Significand \e Exponent
 *                          | \e Significand
 *                          ;
 *
 * \e Significand : \e IntegerPart \e POINT \e FractionPart
 *                | \e IntegerPart \e POINT
 *                | \e POINT \e FractionPart
 *                | \e IntegerPart
 *                ;
 *
 * \e IntegerPart : \e Digits
 *                ;
 *
 * \e FractionPart : \e Digits
 *                 ;
 *
 * \e Exponent : \e EXPONENT_INDICATOR \e SignedInteger
 *             ;
 *
 * \e SignedInteger : \e SIGN \e Digits
 *                  | \e Digits
 *                  ;
 *
 * \e Digits : \e DIGIT
 *           | \e Digits \e DIGIT;
 *
 * \e SIGN: + | -;
 *
 * \e POINT: .;
 *
 * \e EXPONENT_INDICATOR: e | E;
 *
 * \e DIGIT: [0-9]{1};
 * </td></tr></table>
 */
EXPORT NUMERIC_INT32 RD5NumericStr2Num(const char* numstr,const NumericInfo* info_c,Numeric* c,const char** endptr);

/**
 * Translates the string representation of a Numeric into a Numeric.
 * @param[in] numstr the string representation
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 * @param[out] endptr buffer to hold the pointer to the character following the valid string representation if endptr is not null.
 *
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 * @retval NUMERIC_ERROR_INVALID_FORMAT if the string representation is not valid.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_OVERFLOW,NUMERIC_INFO_UNDERFLOW,NUMERIC_ERROR_INVALID_FORMAT
 *
 * @note
 *
 * Valid string representation is described by the following grammar.
 *
 * <table><tr><td>
 * \e NumericString : \e SIGN \e UnsignedNumericString
 *                  | \e UnsignedNumericString
 *                  ;
 *
 * \e UnsignedNumericString : \e Significand \e Exponent
 *                          | \e Significand
 *                          ;
 *
 * \e Significand : \e IntegerPart \e POINT \e FractionPart
 *                | \e IntegerPart \e POINT
 *                | \e POINT \e FractionPart
 *                | \e IntegerPart
 *                ;
 *
 * \e IntegerPart : \e Digits
 *                ;
 *
 * \e FractionPart : \e DigitsWithoutComma
 *                 ;
 *
 * \e Exponent : \e EXPONENT_INDICATOR \e SignedInteger
 *             ;
 *
 * \e SignedInteger : \e SIGN \e Digits
 *                  | \e Digits
 *                  ;
 *
 * \e Digits : \e DigitsWithoutComma
 *           | \e DigitsWithComma
 *           ;
 *
 * \e DigitsWithoutComma : \e LESS_THAN_FOUR_DIGITS
 *                       | \e MORE_THAN_THREE_DIGITS
 *                       ;
 *
 * \e DigitsWithComma : \e LESS_THAN_FOUR_DIGITS \e DigitsWithLeadingComma
 *                    ;
 *
 * \e DigitsWithLeadingComma : \e THREE_DIGITS_WITH_LEADING_COMMA
 *                           | \e DigitsWithLeadingComma \e THREE_DIGITS_WITH_LEADING_COMMA
 *                           ;
 *
 *
 * \e SIGN: + | -;
 *
 * \e POINT: .;
 *
 * \e EXPONENT_INDICATOR: e | E;
 *
 * \e LESS_THAN_FOUR_DIGITS: [0-9]{1,3};
 *
 * \e MORE_THAN_THREE_DIGITS: [0-9]{4,};
 *
 * \e THREE_DIGITS_WITH_LEADING_COMMA: \\,[0-9]{3};
 * </td></tr></table>
 */
EXPORT NUMERIC_INT32 RD5NumericDgstr2Num(const char* numstr,const NumericInfo* info_c,Numeric* c,const char** endptr);

/**
 * Translates a Numeric into a string representation.
 * @param[in] c unscaled value to be translated
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[in] scale the exponent of the result string representation. The result string representation ends with 'E<-scale>' if scale is not zero.
 * @param[in] prec precision (number of fractional digits without exponent) of the result
 * @param[out] numstr buffer to hold the result.
 * @param[in] len the length of the buffer (=numstr)
 *
 * @retval 0 Success. The result is stored in numstr.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in numstr.
 * @retval NUMERIC_INFO_NAN if c is a NaN. 'NaN' is stored in numstr.
 * @retval NUMERIC_ERROR_BUFFER_TOO_SHORT indicating the length of buffer (=len) is too small for the buffer (=numstr) to hold the result. The contents of numstr is undefined.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN,NUMERIC_ERROR_BUFFER_TOO_SHORT
 */
EXPORT NUMERIC_INT32 RD5NumericNum2Str(const Numeric* c,const NumericInfo* info_c,NUMERIC_INT32 scale,NUMERIC_INT32 prec,char* numstr,size_t len);

/**
 * Translates a Numeric into a digit-grouped (by commas) string representation.
 * @param[in] c unscaled value to be translated
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[in] scale the exponent of the result string representation. The result string representation ends with 'E<-scale>' if scale is not zero.
 * @param[in] prec precision (number of fractional digits without exponent) of the result
 * @param[out] numstr buffer to hold the result.
 * @param[in] len the length of the buffer (=numstr)
 *
 * @retval 0 Success. The result is stored in numstr.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in numstr.
 * @retval NUMERIC_INFO_NAN if c is a NaN. 'NaN' is stored in numstr.
 * @retval NUMERIC_ERROR_BUFFER_TOO_SHORT indicating the length of buffer (=len) is too small for the buffer (=numstr) to hold the result. The contents of numstr is undefined.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN,NUMERIC_ERROR_BUFFER_TOO_SHORT
 */
EXPORT NUMERIC_INT32 RD5NumericNum2Dgstr(const Numeric* c,const NumericInfo* info_c,NUMERIC_INT32 scale,NUMERIC_INT32 prec,char* numstr,size_t len);

/**
 * Converts an IEEE754 double number into a Numeric.
 * @param[in] val IEEE754 double number to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_NAN if val is a NaN. c is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 */
EXPORT NUMERIC_INT32 RD5NumericDbl2Num(const NUMERIC_IEEE754_DOUBLE val,const NumericInfo* info_c,Numeric* c);

/**
 * Converts a Numeric into an IEEE754 double number.
 * @param[in] c unscaled value to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] val buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in val.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in val.
 * @retval NUMERIC_INFO_NAN if c is NaN. val is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. val is set +inf.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. val is set -inf.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN,NUMERIC_INFO_OVERFLOW,NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericNum2Dbl(const Numeric* c,const NumericInfo* info_c,NUMERIC_IEEE754_DOUBLE* val);

/**
 * Converts a 32-bit signed integer into a Numeric.
 * @param[in] val 32-bit signed integer to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 */
EXPORT NUMERIC_INT32 RD5NumericInt2Num(const NUMERIC_INT32 val,const NumericInfo* info_c,Numeric* c);

/**
 * Converts a Numeric into a 32-bit signed integer number.
 * @param[in] c unscaled value to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] val buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in val.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in val.
 * @retval NUMERIC_INFO_NAN if c is NaN. val is undefined.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. val is undefined.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. val is undefined.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN,NUMERIC_INFO_OVERFLOW,NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericNum2Int(const Numeric* c,const NumericInfo* info_c,NUMERIC_INT32* val);

/**
 * Converts a 64-bit signed integer into a Numeric.
 * @param[in] val 64-bit signed integer to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 */
EXPORT NUMERIC_INT32 RD5NumericLong2Num(const NUMERIC_INT64 val,const NumericInfo* info_c,Numeric* c);

/**
 * Converts a Numeric into a 64-bit signed integer number.
 * @param[in] c unscaled value to be converted
 * @param[in] info_c->scale scale of c
 * @param[in] info_c->rounding_mode the rounding mode to be applied
 * @param[out] val buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 *
 * @retval 0 Success. The result is stored in val.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in val.
 * @retval NUMERIC_INFO_NAN if c is NaN. val is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. val is undefined.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. val is undefined.
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN,NUMERIC_INFO_OVERFLOW,NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericNum2Long(const Numeric* c,const NumericInfo* info_c,NUMERIC_INT64* val);

#ifdef __cplusplus
};
#endif

#endif


