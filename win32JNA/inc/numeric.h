#ifndef _NUMERIC_H
#define _NUMERIC_H


#ifdef __cplusplus
extern "C" {
#endif

/* ROUNDING MODES */

/**
 * Rounding mode to round away from zero. Always increments the digit prior to a nonzero discarded fraction. Note that this rounding mode never decreases the magnitude of the calculated value.
 */
#define NUMERIC_ROUND_UP (0)

/**
 * Rounding mode to round towards zero. Never increments the digit prior to a discarded fraction (i.e., truncates). Note that this rounding mode never increases the magnitude of the calculated value. 
 */
#define NUMERIC_ROUND_DOWN (1)

/**
 * Rounding mode to round towards positive infinity. If the Numeric is positive, behaves as for NUMERIC_ROUND_UP; if negative, behaves as for NUMERIC_ROUND_DOWN. Note that this rounding mode never decreases the calculated value.
 */
#define NUMERIC_ROUND_CEILING (2)

/**
 * Rounding mode to round towards negative infinity. If the Numeric is positive, behave as for NUMERIC_ROUND_DOWN; if negative, behave as for NUMERIC_ROUND_UP. Note that this rounding mode never increases the calculated value. 
 */
#define NUMERIC_ROUND_FLOOR (3)

/**
 * Rounding mode to round towards "nearest neighbor" unless both neighbors are equidistant, in which case round up. Behaves as for NUMERIC_ROUND_UP if the discarded fraction is >= 0.5; otherwise, behaves as for NUMERIC_ROUND_DOWN. Note that this is the rounding mode that most of us were taught in grade school. 
 */
#define NUMERIC_ROUND_HALF_UP (4)

/**
 * Rounding mode to round towards "nearest neighbor" unless both neighbors are equidistant, in which case round down. Behaves as for NUMERIC_ROUND_UP if the discarded fraction is > 0.5; otherwise, behaves as for NUMERIC_ROUND_DOWN. 
 */
#define NUMERIC_ROUND_HALF_DOWN (5)

/**
 * Rounding mode to round towards the "nearest neighbor" unless both neighbors are equidistant, in which case, round towards the even neighbor. Behaves as for NUMERIC_ROUND_HALF_UP if the digit to the left of the discarded fraction is odd; behaves as for NUMERIC_ROUND_HALF_DOWN if it's even. Note that this is the rounding mode that minimizes cumulative error when applied repeatedly over a sequence of calculations. 
 */
#define NUMERIC_ROUND_HALF_EVEN (6) /* Chiefly used in the U.S., a.k.a. Banker's rounding.  See java.math.RoundingMode for further info. */

/* INFO CODES */

/**
 * Return code indicating the result is NaN.
 */
#define NUMERIC_INFO_NAN (1)

/**
 * Return code indicating the result has been truncated.
 */
#define NUMERIC_INFO_TRUNCATED (2)

/**
 * Return code indicating overflow has occurred.
 */
#define NUMERIC_INFO_OVERFLOW (3)

/**
 * Return code indicating underflow has occurred.
 */
#define NUMERIC_INFO_UNDERFLOW (4)

#define D5_MAX_ROUND_NAME_LENGTH (16)

/* ENDIAN */
#ifdef NUMERIC_LITTLE_ENDIAN
#ifdef NUMERIC_BIG_ENDIAN
#error "Both NUMERIC_LITTLE_ENDIAN and NUMERIC_BIG_ENDIAN are defined."
#endif
#else
#ifndef NUMERIC_BIG_ENDIAN
#error "Neither NUMERIC_LITTLE_ENDIAN nor NUMERIC_BIG_ENDIAN is defined."
#endif
#endif

#ifndef EXPORT
#ifdef _WINDOWS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#endif

typedef int NUMERIC_INT32;
typedef unsigned int NUMERIC_UINT32;

#ifdef _WINDOWS
typedef __int64 NUMERIC_INT64;
#else
typedef long long NUMERIC_INT64;
#endif

#ifdef _WINDOWS
typedef unsigned __int64 NUMERIC_UINT64;
#else
typedef unsigned long long NUMERIC_UINT64;
#endif

/* TODO: USE NAMED STRUCT INSTEAD */
typedef struct {
  union {
    struct {
#ifdef NUMERIC_LITTLE_ENDIAN
      NUMERIC_UINT64 r0;
      NUMERIC_UINT64 r1;
#else
      NUMERIC_UINT64 r1;
      NUMERIC_UINT64 r0;
#endif
    };
    struct {
#ifdef NUMERIC_LITTLE_ENDIAN
      NUMERIC_UINT32 e0;
      NUMERIC_UINT32 e1;
      NUMERIC_UINT32 e2;
      NUMERIC_UINT32 e3;
#else
      NUMERIC_UINT32 e3;
      NUMERIC_UINT32 e2;
      NUMERIC_UINT32 e1;
      NUMERIC_UINT32 e0;
#endif
    };
  };
} Numeric;

typedef struct {
  NUMERIC_INT32 scale;
  NUMERIC_INT32 rounding_mode;
} NumericInfo;

/*
 * SCALE-INDEPENDENT FUNCTIONS (FAST)
 *
 * ALL THE Numeric OPERANDS OF EACH OF THE FOLLOWING FUNCTIONS ARE
 * SUPPOSED TO HAVE THE SAME SCALE.
 */

/**
 * Performs addition. All parameters are supposed to have the same scale.
 * @param[in] a unscaled addend
 * @param[in] b unscaled augend
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericAdd(const Numeric* a,const Numeric* b,Numeric* c);

/**
 * Performs subtraction. All parameters are supposed to have the same scale.
 * @param[in] a unscaled minuend
 * @param[in] b unscaled subtrahend
 * @param[out] c buffer to hold the unscaled value of the result (The caller must prepare the buffer beforehand.)
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericSub(const Numeric* a,const Numeric* b,Numeric* c);

/**
 * Performs comparison. All parameters are supposed to have the same scale. NaN is assumed to be smaller than any Numeric that is not NaN. Two NaNs are assumed to be equal.
 * @param[in] a unscaled value to be compared with b
 * @param[in] b unscaled value to be compared with a
 * @retval 1 if b is bigger than a.
 * @retval 0 if b is equal to a.
 * @retval -1 if b is smaller than a.
 */
EXPORT NUMERIC_INT32 RD5NumericCmp(const Numeric* a,const Numeric* b);

/**
 * Performs multiplication.
 * @param[in,out] a unscaled multiplier
 * @param[in] b 32-bit signed integer multiplicand
 * @retval 0 Success. The result is stored in a. The input and output have the same scale.  
 * @retval NUMERIC_INFO_NAN a is a NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. a is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. a is set NaN.
 * @see NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericMul(Numeric* a,NUMERIC_INT32 b);

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
 * @see NUMERIC_INFO_TRUNCATED,NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericDiv(Numeric* a,NumericInfo* info_a,NUMERIC_INT32 b);

/**
 * Sets a Numeric zero.
 * @param[out] c buffer to be set zero (The caller must prepare the buffer beforehand.)
 */
EXPORT void RD5NumericSetZero(Numeric* c);

/**
 * Tests whether a Numeric is zero.
 * @param[in] c unscaled value to be tested
 * @retval zero if c is not zero.
 * @retval non-zero if c is zero.
 */
EXPORT NUMERIC_INT32 RD5NumericIsZero(const Numeric* c);

/**
 * Sets a Numeric NaN.
 * @param[out] c buffer to be set NaN (The caller must prepare the buffer beforehand.)
 */
EXPORT void RD5NumericSetNan(Numeric* c);

/**
 * Tests whether a Numeric is NaN.
 * @param[in] c unscaled value to be tested
 * @retval zero if c is not NaN.
 * @retval non-zero if c is NaN.
 */
EXPORT NUMERIC_INT32 RD5NumericIsNan(const Numeric* c);

/*
 * FOR DEBUGGING PURPOSE
 */
void dump(const Numeric* c);

/*
 * SCALE DEPENDENT FUNCTIONS
 *
 * DECIMAL RESCALING IS TIME-CONSUMING.
 */

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
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericRescalingAdd(const NumericInfo* info_a,const NumericInfo* info_b,const NumericInfo* info_c,const Numeric* a,const Numeric* b,Numeric* c);

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
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericRescalingSub(const NumericInfo* info_a,const NumericInfo* info_b,const NumericInfo* info_c,const Numeric* a,const Numeric* b,Numeric* c);

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
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericRescalingMul(const NumericInfo* info_a,const NumericInfo* info_b,const NumericInfo* info_c,const Numeric* a,const Numeric* b,Numeric* c);

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
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericRescalingDiv(const NumericInfo* info_a,const NumericInfo* info_b,const NumericInfo* info_c,const Numeric* a,const Numeric* b,Numeric* c);

/**
 * Performs comparison. NaN is assumed to be smaller than any Numeric that is not a NaN. Two NaNs are assumed to be equal.
 * @param[in] info_a->scale scale of a
 * @param[in] info_b->scale scale of b
 * @param[in] a unscaled value to be compared with b
 * @param[in] b unscaled value to be compared with a
 * @retval 1 if b is bigger than a.
 * @retval 0 if b is equal to a.
 * @retval -1 if b is smaller than a.
 */
EXPORT NUMERIC_INT32 RD5NumericRescalingCmp(const NumericInfo* info_a,const NumericInfo* info_b,const Numeric* a,const Numeric* b);

/**
 * Performs rounding towards positive infinity. Equlvalent to numeric_round with info_c->rounding_mode=NUMERIC_ROUND_CEILING.
 * @param[in] info_c->scale scale of c
 * @param[in] prec precision (number of fractional digits) of the result 
 * @param[in,out] c unscaled value to be rounded towards positive infinity
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
 * @retval NUMERIC_INFO_OVERFLOW if overflow has occurred. c is set NaN.
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericCeil(const NumericInfo* info_c,const NUMERIC_INT32 prec,Numeric* c);

/**
 * Performs rounding towards negative infinity. Equlvalent to numeric_round with info_c->rounding_mode=NUMERIC_ROUND_FLOOR.
 * @param[in] info_c->scale scale of c
 * @param[in] prec precision (number of fractional digits) of the result
 * @param[in,out] c unscaled value to be rounded towards negative infinity
 * @retval 0 Success. The result is stored in c.
 * @retval NUMERIC_INFO_TRUNCATED Success with non-zero truncation. The result is stored in c.
 * @retval NUMERIC_INFO_NAN Either a or b is NaN. c is set NaN.
 * @retval NUMERIC_INFO_UNDERFLOW if underflow has occurred. c is set NaN.
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericFloor(const NumericInfo* info_c,const NUMERIC_INT32 prec,Numeric* c);

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
 * @see NUMERIC_INFO_TRUNCATED, NUMERIC_INFO_NAN, NUMERIC_INFO_OVERFLOW, NUMERIC_INFO_UNDERFLOW
 */
EXPORT NUMERIC_INT32 RD5NumericRound(const NumericInfo* info_c,const NUMERIC_INT32 prec,Numeric* c);

EXPORT NUMERIC_INT32 RD5NumericRescale(const NumericInfo* info_a,const NumericInfo* info_c,const Numeric* a,Numeric* c);

#ifdef __cplusplus
};
#endif

#endif
