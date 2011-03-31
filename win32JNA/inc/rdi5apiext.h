/** @file
 * LFMテーブル拡張API
 *
 * (C)2009 Turbo Data Laboratories, Inc.
 */

#ifndef _RDI5APIEXT_H
#define _RDI5APIEXT_H

#include "di5api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * バージョン情報を取得します。
 * @param[out]	anVersion	バージョン配列
 * @retval	0	常に0
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anVersionは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetVersionR1(int* anVersion);

/**
 * コピーライトメッセージを取得します。
 * @retval	コピーライトメッセージ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetCopyRightR1();

/**
 * ワークスペースのパスを取得します。
 * @retval	ワークスペースのパス
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetDBPathR1();

/**
 * ワークスペースの名称を取得します。
 * @retval	ワークスペースの名称
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetDBNameR1();

/**
 * 登録可能なテーブル名称を生成します。
 * @param[in]	szSeedName	生成されるテーブル名称の元となる文字列
 * @retval	登録可能なテーブル名称
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GenerateTableNameR1(char *szSeedName);

/* */
char*	D5APICALL RD5GenTableNameR1(char *szSeedName);

/**
 * テーブル名称を取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	テーブル名称
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetTableNameR1(int nTableID);

/**
 * 指定した項目(文字列)のデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	szX			1番目の検索条件データ
 * @param[in]	szY			2番目の検索条件データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5SearchByFieldStrR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY);

/**
 * 指定した項目(整数)のデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID	セットID
 * @param[in]	nOpeNo	検索条件式
 * @param[in]	nX		1番目の検索条件データ
 * @param[in]	nY		2番目の検索条件データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5SearchByFieldIntR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, int nX, int nY);

/**
 * 指定した項目(浮動少数)のデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID	セットID
 * @param[in]	nOpeNo	検索条件式
 * @param[in]	dX		1番目の検索条件データ
 * @param[in]	dY		2番目の検索条件データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5SearchByFieldDblR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, double dX, double dY);

/**
 * 指定した項目(Numeric)のデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	pNumericX	1番目の検索条件データ
 * @param[in]	pNumericY	2番目の検索条件データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pcX,pcYは、lfmutilの{@link CNumeric}を使用してポインタを指定してください。
 */
int		D5APICALL RD5SearchByFieldNumericR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, Numeric *pNumericX, Numeric *pNumericY);

/**
 * 指定した項目の、マルチバイト文字コードを使った検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	szX			1番目の検索条件データ
 * @param[in]	szY			2番目の検索条件データ
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5SearchByFieldSJISR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY);

/**
 * 指定した項目の、マルチバイト文字コードを使った検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	szX			1番目の検索条件データ
 * @param[in]	szY			2番目の検索条件データ
 * @param[in]	nLocaleID	文字コードID
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5SearchByFieldLocaleR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY, int nLocaleID);

/* */
int		D5APICALL RD5GetDataIntR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
double	D5APICALL RD5GetDataDblR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
char*	D5APICALL RD5GetDataStrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
int		D5APICALL RD5GetDataNumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, Numeric *pNumeric);

/**
 * NUMERIC項目情報を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		フィルタID
 * @param[out]	pNumericInfo	NUMERIC項目情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pNumericInfoは、lfmutilの{@link CNumericInfo}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetNumericInfoR1(int nTableID, int nFilterID, NumericInfo *pNumericInfo);

/**
 * 単一データ(整数)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @retval	取得したデータ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5GetData1IntR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * 単一データ(浮動少数)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @retval	取得したデータ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
double	D5APICALL RD5GetData1DblR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * 単一データ(文字列)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @retval	取得したデータ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetData1StrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * 単一データ(Numeric)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pNumeric	取得したデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pNumericは、lfmutilの{@link CNumeric}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetData1NumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, Numeric *pNumeric);

/**
 * 項目IDから項目名称を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	項目名称
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetFilterNameR1(int nTableID, int nFilterID);

/* */
char*	D5APICALL RD5GetSerialR1();

/* */
char*	D5APICALL RD5CategoryReadR1(int nSumHandle, int nDimNo, int nCatNo);

/**
 * データ(整数)を上書きします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nWritePos	書き込み位置
 * @param[in]	nWriteData	書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5OverwriteRealExIntR1(int nTableID, int nSetID, int nFilterID, int nWritePos, int nWriteData);

/**
 * データ(浮動少数)を上書きします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWritePos	書き込み位置
 * @param[in]	dWriteData	書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5OverwriteRealExDblR1(int nTableID, int nSetID, int nFilterID, int nWritePos, double dWriteData);

/**
 * データ(Numeric)を上書きします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nWritePos	書き込み位置
 * @param[in]	pWriteData	書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pWriteDataは、lfmutilの{@link CNumeric}を使用してポインタを指定してください。
 */
int		D5APICALL RD5OverwriteRealExNumericR1(int nTableID, int nSetID, int nFilterID, int nWritePos, Numeric *pWriteData);

/**
 * データ(文字列)を上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWritePos		書き込み位置
 * @param[in]	szWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5OverwriteRealExStrR1(int nTableID, int nSetID, int nFilterID, int nWritePos, char *szWriteData);

/**
 * データ(整数)を上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	nWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5FillRealExIntR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, int nWriteData);

/**
 * データ(浮動少数)を上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	dWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5FillRealExDblR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, double dWriteData);

/**
 * データ(Numeric)を上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	pWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pWriteDataは、lfmutilの{@link CNumeric}を使用してポインタを指定してください。
 */
int		D5APICALL RD5FillRealExNumericR1(int nTableID, int nSetID, int  nFilterID, int nWriteStart, int nWriteCount, Numeric *pWriteData);

/**
 * データ(文字列)を上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	szWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
int		D5APICALL RD5FillRealExStrR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, char *szWriteData);

/**
 * 単一データを文字列に変換して取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @retval	取得したデータ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetData1Cnv2StrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * 浮動少数データを文字列(日付)に変換して取得します。
 * @param[in]	dData	浮動少数データ
 * @retval	変換後の文字列
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5Double2DateStrR1(double dData);

/**
 * 浮動少数データを文字列(時刻)に変換して取得します。
 * @param[in]	dData	浮動少数データ
 * @retval	変換後の文字列
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5Double2TimeStrR1(double dData);

/**
 * 浮動少数データを文字列(日付時刻)に変換して取得します。
 * @param[in]	dData	浮動少数データ
 * @retval	変換後の文字列
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5Double2DateTimeStrR1(double dData);

/**
 * Numericデータを文字列に変換します。
 * @param[in]	pNumeric		Numericデータ
 * @param[in]	pNumericInfo	Numeric項目情報
 * @param[in]	nScale			スケール（小数点以下桁数）
 * @param[in]	nPrec			精度
 * @retval	変換後の文字列
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pNumericは、lfmutilの{@link CNumeric}を使用してポインタを指定してください。
 * pNumericInfoは、lfmutilの{@link CNumericInfo}を使用してポインタを指定してください。
 */
char*	D5APICALL RD5NumericNum2StrR1(const Numeric *pNumeric, const NumericInfo *pNumericInfo, int nScale, int nPrec);

/**
 * 文字列(日付)を浮動少数に変換して取得します。
 * @param[in]	szData	文字列データ
 * @retval	変換後の浮動少数データ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
double	D5APICALL RD5Str2DateR1(char *szData);

/**
 * 文字列(時刻)を浮動少数に変換して取得します。
 * @param[in]	szData	文字列データ
 * @retval	変換後の浮動少数データ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
double	D5APICALL RD5Str2TimeR1(char *szData);

/**
 * 文字列(日付時刻)を浮動少数に変換して取得します。
 * @param[in]	szData	文字列データ
 * @retval	変換後の浮動少数データ
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
double	D5APICALL RD5Str2DateTimeR1(char *szData);

/**
 * 複数データ(整数)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pnGotCount	取得したデータ数
 * @param[out]	pnBuf		取得したデータ格納領域へのポインタ
 * @retval	0以上	取得した行のうち、単一で最大のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnGotCount,pnBufは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetData1MIntR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, int *pnBuf);

/**
 * 複数データ(浮動少数)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pnGotCount	取得したデータ数
 * @param[out]	pdBuf		取得したデータ格納領域へのポインタ
 * @retval	0以上	取得した行のうち、単一で最大のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnGotCountは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 * pdBufは、lfmutilの{@link CTypeDblAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetData1MDblR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, double *pdBuf);

/**
 * 複数データ(Numeric)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pnGotCount	取得したデータ数
 * @param[out]	pNumericBuf	取得したデータ格納領域へのポインタ
 * @retval	0以上	取得した行のうち、単一で最大のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnGotCountは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 * pNumericBufは、lfmutilの{@link CTypeNumAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetData1MNumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, Numeric *pNumericBuf);

/**
 * 複数データ(文字列)を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pnGotCount	取得したデータ数
 * @param[out]	pnOffset	buf内での単一データの開始位置(4バイト)の配列
 * @param[out]	pvBuf		取得したデータ格納領域へのポインタ
 * @retval	0以上	NULL終端を含まない最終行のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnGotCountは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 * pnOffsetは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 * pvBufは、lfmutilの{@link CTypeCharAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetData1MStrR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int*pnGotCount, int *pnOffset, void *pvBuf);

/**
 * セット名称を取得します。
 * @param[in]	nTableID	セットの属するテーブルID
 * @param[in]	nSetID		セットID
 * @retval	セット名称
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
char*	D5APICALL RD5GetSetNameR1(int nTableID, int nSetID);

/* */
int		D5APICALL RD5GetJoinInfoR1(int nTableID,
					   int	*pnMasterTableID,	//  OUT:指定のテーブルのマスターテーブルID
					   int	*pnMasterSetID,		//  OUT:指定のテーブルのマスター集合ID
					   int	*pnMasterFilterID,	//  OUT:最初のJOINKEYのID
					   int	*pnSlaveTableID,	//  OUT:指定のテーブルのスレーブテーブルID
					   int	*pnSlaveSetID,		//  OUT:指定のテーブルのスレーブ集合ID
					   int	*pnSlaveFilterID	//  OUT:最初のJOINKEYのID
						);

/**
 * JOINテーブルの情報を取得します。
 * @param[in]	nTableID			情報を取得するJOINテーブルID
 * @param[out]	pnIsOuter			JOINテーブルの種類
 * @param[out]	pnJoinKeyCount		JOINキーの数
 * @param[out]	pnMasterTableID		マスタテーブルID
 * @param[out]	pnMasterSetID		マスタテーブルセットID
 * @param[out]	anMasterFilterIDs	マスタテーブルのJOINキーの一覧
 * @param[out]	pnSlaveTableID		スレーブテーブルID
 * @param[out]	pnSlaveSetID		スレーブテーブルセットID
 * @param[out]	anSlaveFilterIDs	スレーブテーブルのJOINキーの一覧
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnIsOuter,pnJoinKeyCount,pnMasterTableID,pnMasterSetID,anMasterFilterIDs,pnSlaveTableID,pnSlaveSetID,anSlaveFilterIDsは、
*  lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
int		D5APICALL RD5GetJoinInfoExR1(
         int nTableID,				//    IN:指定のテーブルのテーブルID
         int	*pnIsOuter,			//    OUT:OuterJoin=1, InnerJoin=0
         int	*pnJoinKeyCount,	//   OUT:JoinKey's count
         int	*pnMasterTableID,	//    OUT:指定のテーブルのマスターテーブルID
         int	*pnMasterSetID,		//    OUT:指定のテーブルのマスター集合ID
         int    anMasterFilterIDs[D5_MAX_JOIN_KEY],	//  OUT:JOINKEYのFilter-ID配列（領域は呼び出し側で）
         int	*pnSlaveTableID,	//    OUT:指定のテーブルのスレーブテーブルID
         int	*pnSlaveSetID,		//    OUT:指定のテーブルのスレーブ集合ID
         int    anSlaveFilterIDs[D5_MAX_JOIN_KEY]	//   OUT:JOINKEYのFilter-ID配列（領域は呼び出し側で）
        );							//  0:Success, －の時、エラーコード


/* */
int		D5APICALL RD5Connect2LFMServer(int nOpt, char *szIdentity);

/* */
int		D5APICALL RD5DisconnectFromLFMServer();

/* */
char*	D5APICALL RD5GetNamingServiceIdentity();

#ifdef __cplusplus
}
#endif

#endif
