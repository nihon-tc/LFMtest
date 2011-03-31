/** @file
 * LFMテーブルAPI
 *
 * (C)2009 Turbo Data Laboratories, Inc.
 */

/*--------------------------------------------------------------------------
*
*	   RDI5 DLL API DEFINITION   version 2.00
*
*		(C)2001-2009 Turbo Data Laboratories, Inc.
* 
----------------------------------------------------------------------------*/

#ifndef _RD5API_H
#define _RD5API_H
#include "di5api.h"

/** 項目情報 */
typedef struct _TRFilterInfo {
	int		PVSize;			/**< 位置情報のサイズ */
	int		VLType;			/**< 値リストのデータ型を整数化したもの */
	int		VLWidth;		/**< 値リストの各値の幅 */
	int		VLSize;			/**< 値リストのサイズ（個数） */
	int		CharAreaSize;	/**< 値リストが文字列の場合、文字列格納領域のサイズ */
	char	FilterName[D5_MAX_NAME_LENGTH + 8];	/**< 項目名称 */
} TRFilterInfo;

/** メモリ情報 */
typedef struct _TRMemInfo {
	INT64  TotalPhys;	/**< トータルメモリサイズ */
	INT64  AvailPhys;	/**< 使用可能メモリサイズ */
} TRMemInfo;

#define D5_MAX_STRING_LENGTH_CHAR_CODE 32

/** サーバ環境情報 */
typedef struct _TREnvironment {
	char HostName[D5_MAX_STRING_LENGTH_OS];	/**< コンピュータ名称 */
	int  OSType;						/**< OSタイプ */
	int  OSMajorVersion;				/**< OSのメジャー・バージョン番号 */
	int  OSMinorVersion;				/**< OSのマイナー・バージョン番号 */
	int  MachineArchitecture;			/**< システムのプロセッサ･アーキテクチャ */
	int  Endian;						/**< システムのエンディアン・タイプ */
	int  ELF;							/**< LFMエンジンのビット数 */
	int  ProcessorCount;				/**< システムのプロセッサ数 */
	int  ProcessType;					/**< 未使用 */
	char OSCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< OSの漢字コード */
	char DBCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< DB文字コード */
} TREnvironment;

/** D5ファイル情報 */
typedef struct _D5FileInfo {
	unsigned char	OSType;										/**< D5Dファイルを作成したOSタイプ */
	unsigned char	Endian;										/**< D5Dファイルを作成したシステムのエンディアン・タイプ */
	unsigned char	ELF;										/**< D5Dファイルを作成した際のLFMエンジンのビット数 */
	char			DBCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< D5DファイルのDB文字コード */
	int				Version[D5_VERSION_SIZE];					/**< D5Dファイルのバージョン */
} D5FileInfo;

/** ライセンス情報 */
typedef struct _TLicenseData {
	char	LicenseMacAddr[D5_MAX_NAME_LENGTH];		/**< MACアドレス */
	INT64	MaxRow;									/**< 最大行数（単位：千行） */
	INT64	MaxMemory;								/**< 最大メモリ量（単位：MB） */
	int		CpuNum;									/**< ライセンス中CPU数 */
	int		UserNum;								/**< マルチユーザ数 */
	char	ExpirationDate[D5_LICENSE_DATE_SIZE];	/**< 有効期限（YYYYMMDD） */
} TLicenseData;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * バージョン情報や、コピーライトメッセージを取得します。
 * @param[out]	anVersion	バージョン配列
 * @param[out]	szCopyright	コピーライトメッセージ
 * @retval	0	常に0
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetVersionR1},{@link #RD5GetCopyRightR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetVersion(
		 int  anVersion[D5_VERSION_SIZE],
		 char szCopyright[D5_VERSION_STRING_SIZE]
		  );

/**
 * ワークスペースをクリアします。
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL  RD5ClearDB();

/**
 * 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。
 * @param[in]	szDBPath	D5Dファイルの存在するパス
 * @param[in]	szDBName	D5Dファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5LoadDB(
		 const char szDBPath[D5_MAX_PATH],
		 const char szDBName[D5_MAX_PATH]
	   );

/**
 * 指定されたパスに指定されたファイル名称で、ワークスペースをD5Dファイルとして書き出します。
 * @param[in]	szDBPath	D5Dファイルを書き出すパス
 * @param[in]	szDBName	D5Dファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SaveDBAs(
		 const char szDBPath[D5_MAX_PATH],
		 const char szDBName[D5_MAX_PATH]
		 );

/**
 * カンマ区切りファイルへデータをエクスポートします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	anFilterIDList	項目IDリスト
 * @param[in]	nRowFrom		出力を開始する行
 * @param[in]	nRowTo			出力の終了行
 * @param[in]	nDateSep		日付データの区切り文字を指定
 * @param[in]	szDBPath		出力ファイルへのパス
 * @param[in]	szDBName		出力ファイル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5ExportAsCSV(
		const int nTableID,
		const int nSetID,
		const int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szDBPath[D5_MAX_PATH],
		const char szDBName[D5_MAX_PATH]
		);

/**
 * TAB区切りファイルへデータをエクスポートします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID	セットID
 * @param[in]	anFilterIDList	項目IDリスト
 * @param[in]	nRowFrom	出力を開始する行
 * @param[in]	nRowTo	出力の終了行
 * @param[in]	nDateSep	日付データの区切り文字を指定
 * @param[in]	szDBPath	出力ファイルへのパス
 * @param[in]	szDBName	出力ファイル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5ExportAsTAB(
		const int nTableID,
		const int nSetID,
		const int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szDBPath[D5_MAX_PATH],
		const char szDBName[D5_MAX_PATH]
		);

/**
 * テーブルのデータをカタログ定義ファイルへエクスポートします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	anFilterIDList	出力する項目IDリスト
 * @param[in]	nFileType		出力するファイルタイプ
 * @param[in]	nRowFrom		出力する行の開始位置
 * @param[in]	nRowTo			出力する行の終了位置
 * @param[in]	nDateSep		日付データの区切り文字を指定
 * @param[in]	szCatalogPath	カタログ定義ファイルを出力するパス
 * @param[in]	szCatalogName	カタログ定義ファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5SaveAsCatalog(
		const int nTableID,
		const int nSetID,
		const int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nFileType,
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szCatalogPath[D5_MAX_PATH],
		const char szCatalogName[D5_MAX_PATH]
		);

/**
 * テーブルのデータをカタログ定義ファイルへエクスポートします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	anFilterIDList	出力する項目IDリスト
 * @param[in]	nFileType		出力するファイルタイプ
 * @param[in]	nRowFrom		出力する行の開始位置
 * @param[in]	nRowTo			出力する行の終了位置
 * @param[in]	nDateSep		日付データの区切り文字を指定
 * @param[in]	szCatalogPath	構造定義ファイルを出力するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
 * @param[in]	szSourcePath	原始データファイルの存在するパス
 * @param[in]	szSourceName	原始データファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5SaveAsCatalogEx(
		const int nTableID,
		const int nSetID,
		const int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nFileType,
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szCatalogPath[D5_MAX_PATH],
		const char szCatalogName[D5_MAX_PATH],
		const char szSourcePath[D5_MAX_PATH],
		const char szSourceName[D5_MAX_PATH]
		);

/**
 * ワークスペースを上書き保存します。
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SaveDB();

/**
 * ワークスペースのパスと名称を取得します。
 * @param[in]	szDBPath	D5Dファイルのパス
 * @param[in]	szDBName	D5Dファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetDBPathR1},{@link #RD5GetDBNameR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetPathName(
		 char szDBPath[D5_MAX_PATH],
		 char szDBName[D5_MAX_PATH]
		 );

/**
 * 存在するテーブル数を取得します。
 * @retval	0以上	テーブル数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetNTable();

/**
 * テーブルIDの一覧を取得します。
 * @param[out]	anTableIDList	テーブルIDの一覧
 * @retval	0以上	テーブル数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anTableIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetTableIDList(
			int anTableIDList[D5_MAX_TABLE_COUNT]
		  );

/**
 * 登録可能なテーブル名称を生成します。
 * @param[in]	szSeedName	生成されるテーブル名称の元となる文字列
 * @param[out]	szGenName	生成された登録可能なテーブル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GenerateTableNameR1}を使用してください。
 */
D5RESULT D5APICALL RD5GenerateTableName(
		 const char   szSeedName[D5_MAX_NAME_LENGTH],
		 char szGenName[D5_MAX_NAME_LENGTH]
		  );

/**
 * REALテーブルをロードします。
 * @param[in]	szTablePath		D5Tファイルの存在するパス
 * @param[in]	szTableName		テーブル名称
 * @retval	1以上	ロードされたテーブルのID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5LoadRealTable(
		 const char   szTablePath[D5_MAX_PATH],
		 const char   szTableName[D5_MAX_PATH]
		 );

/**
 * REALテーブルを新規作成します。
 * @param[in]	szTableName	作成するテーブル名称
 * @param[in]	nRowCount	行数
 * @retval	1以上	新規に作成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddRealTable(
		  const char szTableName[D5_MAX_NAME_LENGTH],
		  const int  nRowCount
		 );

/**
 * REALテーブルを保存します。
 * @param[in]	szTablePath	REALテーブルを保存するパス
 * @param[in]	nTableID	保存したいテーブルのID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SaveRealTable(
		 const char	szTablePath[D5_MAX_PATH],
		 const int	nTableID
		 );

/* */
D5RESULT D5APICALL RD5SaveRealTableAs(
		 const char	szTablePath[D5_MAX_PATH],
		 const char szTableName[D5_MAX_PATH],
		 const int	nTableID
		 );

/**
 * JOINテーブルを作成します。
 * @param[in]	szTableName			新規に作成するJOINテーブル名称
 * @param[in]	nIsOuter			テーブル区分
 * @param[in]	nMasterTableID		マスタテーブルID
 * @param[in]	nMasterSetID		マスタテーブルのセットID
 * @param[in]	anMasterFilterIDs	JOINキーとなるマスタテーブルの項目IDリスト
 * @param[in]	nSlaveTableID		スレーブテーブルID
 * @param[in]	nSlaveSetID			スレーブテーブルのセットID
 * @param[in]	anSlaveFilterIDs	JOINキーとなるスレーブテーブルの項目IDリスト
 * @retval	1以上	作成されたJOINテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anMasterFilterIDs,anSlaveFilterIDsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5AddJoinTable(
			const char	szTableName[D5_MAX_NAME_LENGTH],
			const int	nIsOuter,
			const int	nMasterTableID,
			const int	nMasterSetID,
			const int	anMasterFilterIDs[D5_MAX_JOIN_KEY],
			const int	nSlaveTableID,
			const int	nSlaveSetID,
			const int	anSlaveFilterIDs[D5_MAX_JOIN_KEY]
		  );

/**
 * JOIN IN/OUTセットを生成します。
 * @param[in]	nDestTableID	JOIN IN/OUTセット生成のターゲットのテーブルID
 * @param[in]	nDestSetID		JOIN IN/OUTセットを算出するターゲットのセットID
 * @param[in]	nDestFilterID	JOIN IN/OUTセットを算出するターゲットの項目ID
 * @param[in]	nSrcTableID		JOIN IN/OUTセットの算出元になるーブルID
 * @param[in]	nSrcSetID		JOIN IN/OUTセットの算出元になるのセットID
 * @param[in]	nSrcFilterID	JOIN IN/OUTセットの算出元になる項目ID
 * @param[in]	nIsJoinIn		IN/OUTを指定する
 * @retval	0以上	生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL RD5ExtractJoinInOut(
			const int	nDestTableID,
			const int	nDestSetID,
			const int	nDestFilterID,
			const int	nSrcTableID,
			const int	nSrcSetID,
			const int	nSrcFilterID,
			const int	nIsJoinIn
		);

/**
 * JOINテーブルをREALテーブルに変換します。
 * @param[in]	szTableName		新規に作成するREALテーブル名称
 * @param[in]	nJoinTableID	JOINテーブルID
 * @param[in]	nJoinSetID		JOINテーブルのセットID
 * @param[in]	nIncludeRowNoM	マスタ側行番号の項目化の設定
 * @param[in]	nIncludeRowNoS	スレーブ側行番号の項目化の設定
 * @param[in]	anFilterIDList	REALテーブルの項目に変換する項目IDリスト
 * @param[in]	nVLIsLinked		常に0を指定
 * @retval	1以上	作成されたREALテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5ConvertJoinToReal(
			const char szTableName[D5_MAX_NAME_LENGTH],
			const int  nJoinTableID,
			const int  nJoinSetID,
			const int  nIncludeRowNoM,
			const int  nIncludeRowNoS,
			const int  anFilterIDList[D5_MAX_FILTER_COUNT_REAL],
			const int  nVLIsLinked
		  );

/**
 * JOINチェーンを実体化します。
 * @param[in]	szTableName		新規テーブル名称
 * @param[in]	anJoinTableIDs	チェーンするテーブルIDリスト
 * @param[out]	anRealTableIDs	チェーンされたテーブルIDリスト
 * @param[out]	aanRealSetIDs	チェーンされたREALテーブルIDリスト
 * @retval	1以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT  D5APICALL RD5RealizeJoinChain(
			const char  szTableName[D5_MAX_NAME_LENGTH],
			const int   anJoinTableIDs[D5_MAX_JOIN_CHAIN],
			int   anRealTableIDs[D5_MAX_JOIN_CHAIN + 1],
			int   aanRealSetIDs[J_SLAVE + 1][D5_MAX_JOIN_CHAIN]
	   );

/**
 * JOINチェーンを実体化し、生成されたツリーテーブルに元テーブルの整数項目を追加します。
 * @param[in]	szTableName			新規テーブル名称
 * @param[in]	anJoinTableIDs		チェーンするテーブルIDリスト
 * @param[in]	nAssociation		出力に含める各REALテーブルの項目ID数
 * @param[in]	aanRealFilterIDs		出力する各REALテーブルの項目IDリスト
 * @param[out]	anRealTableIDs		チェーンされたテーブルIDリスト
 * @param[out]	aanRealSetIDs		チェーンされたREALテーブルIDリスト
 * @retval	1以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT  D5APICALL RD5RealizeJoinChainEx(
			const char   szTableName[D5_MAX_NAME_LENGTH],
			const int	anJoinTableIDs[D5_MAX_JOIN_CHAIN],
			const int	nAssociation,
			int   aanRealFilterIDs[D5_MAX_JOIN_CHAIN + 1][D5_MAX_CHAIN_ASSOCIATION],
			int   anRealTableIDs[D5_MAX_JOIN_CHAIN + 1],
			int   aanRealSetIDs[J_SLAVE + 1][D5_MAX_JOIN_CHAIN]
	   );

/**
 * 実体化されたJOINチェーンにソース情報を付加します。
 * @param[in]	nTableID		ツリーテーブルのID
 * @param[in]	nDepth			ターゲットとする深さ
 * @param[in]	nSrcTableID		付加する情報元のテーブルID
 * @param[in]	anSrcFilterIDs	付加する情報元の項目IDリスト
 * @param[in]	nFillAncestor	ルートの場合に値を充当するかどうかを指定
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT  D5APICALL RD5QualifyTree(
			const int	nTableID,
			const int	nDepth,
			const int	nSrcTableID,
			const int	anSrcFilterIDs[D5_MAX_TREE_QUALIFY],
			const int	nFillAncestor
			);

/**
 * JOINチェイン最大値を設定します。
 * @param[in]	nMaxJoinChain	最大階層数(16～510)
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL RD5SetMaxJoinChain (
			const int	nMaxJoinChain
							 );

/**
 * テーブルを削除します。
 * @param[in]	nTableID	削除するテーブルID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DeleteTable(
			const int nTableID
		   );

/**
 * テーブル名称を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[out]	szTableName	テーブル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetTableNameR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetTableName(
			const int nTableID,
			char szTableName[D5_MAX_NAME_LENGTH]
		   );

/**
 * テーブルの情報を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[out]	pTableInfo	テーブル情報のアドレス
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetTableProperty(
			const int nTableID,
			TTableInfo *pTableInfo
		  );

/* */
D5RESULT D5APICALL RD5GetJoinInfo(
		   const int nTableID,
		   char  szTableName[D5_MAX_NAME_LENGTH],
		   int	*pnMasterTableID,
		   int	*pnMasterSetID,
		   int	*pnMasterFilterID,
		   int	*pnSlaveTableID,
		   int	*pnSlaveSetID,
		   int	*pnSlaveFilterID
		   );

/**
 * JOINテーブルの情報を取得します。
 * @param[in]	nTableID			情報を取得するJOINテーブルID
 * @param[out]	szTableName			テーブル名称
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
 * 本APIは使用せず、{@link #RD5GetJoinInfoExR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetJoinInfoEx(
		 const int nTableID,
		 char	szTableName[D5_MAX_NAME_LENGTH],
		 int	*pnIsOuter,
		 int	*pnJoinKeyCount,
		 int	*pnMasterTableID,
		 int	*pnMasterSetID,
		 int	anMasterFilterIDs[D5_MAX_JOIN_KEY],
		 int	*pnSlaveTableID,
		 int	*pnSlaveSetID,
		 int	anSlaveFilterIDs[D5_MAX_JOIN_KEY]
			);

/**
 * JOIN情報を取得します。
 * @param[in]	nTableID		指定のテーブルのテーブルID
 * @param[out]	anJoinFilterIDs		指定のテーブルのフィルタIDリスト
 * @param[out]	anSrcTableIDs	指定のテーブルの元テーブルIDリスト
 * @param[out]	anSrcFilterIDs	指定のテーブルの元フィルタIDリスト
 * @retval	0以上	項目数の合計
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anJoinFilterIDs,anSrcTableIDs,anSrcFilterIDsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetJoinSrcTblIDs(
		 const int nTableID,
		 int anJoinFilterIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int anSrcTableIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int anSrcFilterIDs[D5_MAX_FILTER_COUNT_JOIN]
			);

/**
 * JOINテーブルの情報を取得します。
 * @param[in]	nTableID		指定のテーブルのテーブルID
 * @param[out]	pnNMasterFilter	マスタ側フィルタに由来するフィルタの数
 * @param[out]	pnNSlaveFilter	スレイブ側テーブルに由来するフィルタの数
 * @param[out]	anJoinFilterIDs	指定のテーブルのフィルタID[1..N]
 * @param[out]	anSrcTableIDs	指定のテーブルのマスターテーブルID[Nm, Nm, ... Nm, Ns, Ns, ... Ns]
 * @param[out]	anSrcFilterIDs	指定のテーブルのマスター集合ID[FIDm1, FIDm2, ..., FIDs1, FIDs2, ...]
 * @retval	0以上	取得したフィルタの数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnNMasterFilter,pnNSlaveFilter,anJoinFilterIDs,anSrcTableIDs,anSrcFilterIDsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetJoinSrcTblInfo(
		 const int	nTableID,
		 int		*pnNMasterFilter,
		 int		*pnNSlaveFilter,
		 int	 anJoinFilterIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int	 anSrcTableIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int	 anSrcFilterIDs[D5_MAX_FILTER_COUNT_JOIN]
		 );

/**
 * REALテーブルを複製します。
 * @param[in]	szTableName		新規に設定するテーブル名称
 * @param[in]	nTableID		複製元のテーブルID
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL RD5DuplicateRealTable(
		const char szTableName[D5_MAX_NAME_LENGTH],
		const int  nTableID
		);

/**
 * REALテーブルを抽出します。
 * @param[in]	szTableName				新規に設定するテーブル名称
 * @param[in]	nTableID				抽出元のテーブルID
 * @param[in]	nSetID					抽出するセットID
 * @param[in]	anExtractFilterIDList	抽出する項目IDリスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anExtractFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5ExtractRealTable(
		 const char  szTableName[D5_MAX_NAME_LENGTH],
		 const int   nTableID,
		 const int   nSetID,
		 const int   anExtractFilterIDList[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * REALテーブルを抽出します。
 * @param[in]	szTableName				新規に設定するテーブル名称
 * @param[in]	nTableID				抽出元のテーブルID
 * @param[in]	nSetID					抽出するセットID
 * @param[in]	nIncludeTableID			抽出元テーブルIDの項目化設定値
 * @param[in]	nIncludeRecNo			抽出元レコード番号の項目化設定値
 * @param[in]	anExtractFilterIDList	抽出する項目IDリスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anExtractFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5ExtractRealTableEx(
			const char  szTableName[D5_MAX_NAME_LENGTH],
			const int   nTableID,
			const int   nSetID,
			const int	nIncludeTableID,
			const int   nIncludeRecNo,
			const int   anExtractFilterIDList[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * REALテーブルを縦結合します。
 * @param[in]	szTableName		新規に設定するテーブル名称
 * @param[in]	nTableID1		結合する1番目のテーブルID
 * @param[in]	nSetID1			結合する1番目のセットID
 * @param[in]	anFilterIDs1	結合する1番目の項目リスト
 * @param[in]	nTableID2		結合する2番目のテーブルID
 * @param[in]	nSetID2			結合する2番目のセットID
 * @param[in]	anFilterIDs2	結合する2番目の項目リスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDs1,anFilterIDs2は、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5CombineRealTable(
			const char	szTableName[D5_MAX_NAME_LENGTH],
			const int	nTableID1,
			const int	nSetID1,
			const int	anFilterIDs1[D5_MAX_FILTER_COUNT_REAL],
			const int	nTableID2,
			const int	nSetID2,
			const int	anFilterIDs2[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * REALテーブルを縦結合します。
 * @param[in]	szTableName		新規に設定するテーブル名称
 * @param[in]	nIncludeTableID	抽出元のテーブルIDの項目化設定値
 * @param[in]	nIncludeRecNo	抽出元のレコード番号の項目化設定値
 * @param[in]	nTableID1		結合する1番目のテーブルID
 * @param[in]	nSetID1			結合する1番目のセットID
 * @param[in]	anFilterIDs1	結合する1番目の項目リスト
 * @param[in]	nTableID2		結合する2番目のテーブルID
 * @param[in]	nSetID2			結合する2番目のセットID
 * @param[in]	anFilterIDs2	結合する2番目の項目リスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDs1,anFilterIDs2は、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5CombineRealTableEx(
		 const char	szTableName[D5_MAX_NAME_LENGTH],
		 const int	nIncludeTableID,
		 const int	nIncludeRecNo,
		 const int	nTableID1,
		 const int	nSetID1,
		 const int	anFilterIDs1[D5_MAX_FILTER_COUNT_REAL],
		 const int	nTableID2,
		 const int	nSetID2,
		 const int	anFilterIDs2[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * REALテーブルを縦結合します。
 * @param[in]	szTableName		新規に設定するテーブル名称
 * @param[in]	nIncludeTableID	抽出元のテーブルIDの項目化設定値
 * @param[in]	nIncludeRecNo	抽出元のレコード番号の項目化設定値
 * @param[in]	nTableID1		結合する1番目のテーブルID
 * @param[in]	nSetID1			結合する1番目のセットID
 * @param[in]	anFilterIDs1	結合する1番目の項目のリスト
 * @param[in]	nTableID2		結合する2番目のテーブルID
 * @param[in]	nSetID2			結合する2番目のセットID
 * @param[in]	anFilterIDs2	結合する2番目の項目のリスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDs1,anFilterIDs2は、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5CombineRealTableEx2(
		 const char	szTableName[D5_MAX_NAME_LENGTH],
		 const int	nIncludeTableID,
		 const int	nIncludeRecNo,
		 const int	nTableID1,
		 const int	nSetID1,
		 const int	anFilterIDs1[D5_MAX_FILTER_COUNT_REAL],
		 const int	nTableID2,
		 const int	nSetID2,
		 const int	anFilterIDs2[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * 複数のREALテーブルの整数項目を結合します。
 * @param[in]	szTableName			新規に設定するテーブル名称
 * @param[in]	anTableIDList		結合するテーブルIDリスト
 * @param[in]	anSetIDList			結合するセットIDリスト
 * @param[in]	anIntFilterList0	新テーブルの1番目の項目に設定する項目IDリスト
 * @param[in]	anIntFilterList1	新テーブルの2番目の項目に設定する項目IDリスト
 * @param[in]	anIntFilterList2	新テーブルの3番目の項目に設定する項目IDリスト
 * @param[in]	anIntFilterList3	新テーブルの4番目の項目に設定する項目IDリスト
 * @retval	0以上	生成されたテーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anTableIDList,anSetIDList,anIntFilterList0,anIntFilterList1,anIntFilterList2,anIntFilterList3は、
 * lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT  D5APICALL RD5CombineTableList(
		 const char	szTableName[D5_MAX_NAME_LENGTH],
		 const int	anTableIDList[D5_MAX_COMBINE],
		 const int	anSetIDList[D5_MAX_COMBINE],
		 const int	anIntFilterList0[D5_MAX_COMBINE],
		 const int	anIntFilterList1[D5_MAX_COMBINE],
		 const int	anIntFilterList2[D5_MAX_COMBINE],
		 const int	anIntFilterList3[D5_MAX_COMBINE]
		 );

/**
 * REALテーブルを圧縮します。
 * @param[in]	nTableID	圧縮するテーブルID
 * @retval	0	正常
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL RD5CondenseRealTable(
			 const int  nTableID
			);

/* */
D5RESULT  D5APICALL RD5GenTableName(
		 const char   szSeedName[D5_MAX_NAME_LENGTH],
		 char szGenName[D5_MAX_NAME_LENGTH]
			);

/**
 * 指定したテーブルに属するセット数を取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	1以上	セットの数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetNSet(
			const int nTableID
		  );

/**
 * ルートセットの件数を取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	0以上	ルートセットのサイズ
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetTotalRows(
			const int nTableID
		  );

/**
 * ルートセット以外のセットを削除します。
 * @param[in]	nTableID	テーブルID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5PurgeSubsets(
			const int nTableID
		  );

/**
 * セットIDを指定し、セットサイズを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @retval	0以上	セットのサイズ
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetSetSize(
			const int nTableID,
			const int nSetID
		  );

/**
 * 指定したIDのセットを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[out]	pnSetSize	セットの行数
 * @param[in]	nGetCount	セット配列（pnSetArray）のサイズ
 * @param[out]	pnSetArray	セット配列
 * @retval	0以上	セットのサイズ
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5GetSet(
            const int	nTableID,
            const int	nSetID,
            int			*pnSetSize,
            const int	nGetCount,
            int			*pnSetArray
          );

/**
 * 指定したIDのスレーブセットを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[out]	pnSetSize	セットの行数
 * @param[in]	nGetCount	セット配列（pnSetArray）のサイズ
 * @param[out]	pnSetArray	セット配列
 * @retval	0以上	セットのサイズ
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5GetJoinSlaveSet(
            const int	nTableID,
            const int	nSetID,
            int			*pnSetSize,
            const int	nGetCount,
            int			*pnSetArray
          );

/**
 * 指定したセットのJOINの方向を取得します。
 * @param[in] nTableID	テーブルID
 * @param[in] nSetID	セットID
 * @retval	0	左→右
 * @retval	1	右→左
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetJoinDir(
			const int nTableID,
			const int nSetID
		  );

/**
 * 指定されたJOINテーブルの累計数配列を取得します。
 * @param[in]		nTableID			テーブルID
 * @param[in]		nSetID				セットID
 * @param[out]		pnMasterSize		マスタ側累計数配列のサイズ
 * @param[in]		nMasterGetCount		マスタ側取得サイズ
 * @param[in,out]	pnMasterSetArray	取得されるマスタ側累計数配列
 * @param[out]		pnSlaveSize			スレーブ側累計数配列のサイズ
 * @param[in]		nSlaveGetCount		スレーブ側取得サイズ
 * @param[in,out]	pnSlaveSetArray		取得されるスレーブ側累計数配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnMasterSize,pnMasterSetArray,pnSlaveSize,pnSlaveSetArrayは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetJoinProjectionSets(
			const int	nTableID,
			const int	nSetID,
			int			*pnMasterSize,
			const int	nMasterGetCount,
			int			*pnMasterSetArray,
			int			*pnSlaveSize,
			const int	nSlaveGetCount,
			int			*pnSlaveSetArray
		  );

/**
 * セットIDの一覧を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[out]	anSetIDList		セットIDリスト
 * @retval	0以上	セットIDの個数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anSetIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetSetList(
				const int nTableID,
				int anSetIDList[D5_MAX_SET_COUNT]
		  );

/**
 * 指定されたテーブルのセットのうち指定された個数のセットを取得します。（セット番号の昇順に取り出します。）
 * @param[in]	nTableID	セットを取得したいテーブルのテーブルID
 * @param[in]	nSize		受け取るセットの個数
 * @param[out]	anSetIDList	セットを受け取る配列へのポインタ
 * @retval	0以上	セットの個数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anSetIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetSetIDList(
				const int nTableID,
				int nSize,
				int *anSetIDList
		  );

/**
 * セットを追加します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetSize	追加するセットの個数
 * @param[in]	pnSetArray	追加するセットリスト
 * @retval	1以上	追加したセットのセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5AddSetReal(
            const int	nTableID,
            const int	nSetSize,
            const int	*pnSetArray
          );

/**
 * セットを削除します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DeleteSet(
			const int nTableID,
			const int nSetID
		  );

/**
 * カレントのセットIDを取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	0以上	カレントセットのID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetCurrentSetID(
			const int nTableID
		  );

/**
 * カレントセットを設定します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		カレントセットに設定するセットID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5ChangeCurrentSetID(
			const int nTableID,
			const int nSetID
		  );

/**
 * 指定したサブセット以外のレコードからなるサブセットを作成します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		補集合を作成したいセットID
 * @retval	0以上	作成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL  RD5SetNotReal(
			const int nTableID,
			const int nSetID
		  );

/**
 * セットの共通集合／和集合／差集合を作成します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nOpeNo		作成したいセットの種類
 * @param[in]	nSetAID		1番目に指定するセットID（A）
 * @param[in]	nSetBID		2番目に設定するセットID（B）
 * @retval	0以上	作成された集合のID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetOpeReal(
			const int nTableID,
			const int nOpeNo,
			const int nSetAID,
			const int nSetBID
		  );

/**
 * ユニーク行を抽出します。
 * @param[in]	nJBAHandle				常に0
 * @param[in]	nTableID				テーブルID
 * @param[in]	nSetID					セットID
 * @param[in]	anFilterIDs				項目IDリスト
 * @param[in]	nConserveOriginalOrder	True または False
 * @retval	1以上	生成されたセットのID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL  RD5ExtractUniqueReal(
			const int		nJBAHandle,
			const int		nTableID,
			const int		nSetID,
			const int		anFilterIDs[D5_MAX_FILTER_COUNT_REAL],
			const int		nConserveOriginalOrder
			);

/**
 * JOINにマッチした行、マッチしなかった行をセットとして生成します。
 * @param[in]	nJoinTableID		JOINテーブルID
 * @param[in]	nPutSlave			セットを生成するテーブルを指定
 * @param[in]	nPutJoinOut			生成するセットの種類を指定
 * @param[out]	pnTargetTableID		セットが追加されたテーブルID
 * @param[out]	pnTargetSetID		生成されたセットID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnTargetTableID,pnTargetSetIDは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL  RD5PutJoinSetToParent(
		 const int	nJoinTableID,
		 const int	nPutSlave,
		 const int	nPutJoinOut,
		 int	*pnTargetTableID,
		 int	*pnTargetSetID
	   );

/**
 * JOINにマッチしたスレーブ側の行のセットを生成します。
 * @param[in]	nJoinTableID		JOINテーブルIDJOIN元スレーブテーブルID
 * @param[in]	pnTargetTableID		JOIN元スレーブテーブルID
 * @retval	1以上	生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnTargetTableIDは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5ReturnSet2SlaveTable(
		 const int	nJoinTableID,
		 int	*pnTargetTableID
	   );

/**
 * 項目の個数を取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	0以上	項目の個数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetNFilter(
			const int nTableID
		  );

/**
 * 項目IDの一覧を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[out]	anFilterIDList	項目IDリスト
 * @retval	4byte	項目のデータ型が整数
 * @retval	8byte	項目のデータ型が浮動小数点or日付or時刻or日付時刻
 * @retval	最大長の文字列から\0を除いたbyte数	項目のデータ型が文字列
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anFilterIDListは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetFilterIDList(
			const int nTableID,
			int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN]
		  );

/**
 * 項目の幅を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	0以上	項目の幅
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetFilterWidth(
			const int nTableID,
			const int nFilterID
		  );

/**
 * 項目のデータ型を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	2～7	5-1. 定数定義を参照
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetFilterType(
			const int nTableID,
			const int nFilterID
		  );

/**
 * 項目の情報を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[out]	pFilterInfo	項目情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetFilterInfo(
		const int nTableID,
		const int nFilterID,
		TRFilterInfo *pFilterInfo
	);

/* */
D5RESULT D5APICALL RD5GetJoinKeyInfo(
		const int nJoinTableID,
		TRFilterInfo	*pMasterFilterInfo,
		TRFilterInfo	*pSlaveFilterInfo
	);

/**
 * 項目のアトリビュート領域を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[out]	acAttrs		アトリビュート配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、lfmutilの{@link CFilterAttr}を使用してください。
 */
D5RESULT	D5APICALL RD5GetFilterAttr(
		 const int	nTableID,
		 const int	nFilterID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * セットのアトリビュート領域を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[out]	acAttrs		アトリビュート配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、lfmutilの{@link CSubsetAttr}を使用してください。
 */
D5RESULT	D5APICALL RD5GetSubsetAttr(
		 const int	nTableID,
		 const int	nSetID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * 項目のアトリビュート領域にデータを格納します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	acAttrs		アトリビュート配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、lfmutilの{@link CFilterAttr}を使用してください。
 */
D5RESULT	D5APICALL RD5SetFilterAttr(
		 const int	nTableID,
		 const int	nFilterID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * セットのアトリビュート領域を設定します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	acAttrs		アトリビュート配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、lfmutilの{@link CSubsetAttr}を使用してください。
 */
D5RESULT	D5APICALL RD5SetSubsetAttr(
		 const int	nTableID,
		 const int	nSetID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * 指定項目を削除します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DeleteRealFilter(
			const int nTableID,
			const int nFilterID
		  );

/**
 * 項目の位置を変更します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFromIndex	移動対象の位置
 * @param[in]	nToIndex	挿入先の位置
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5MoveRealFilter(
			const int nTableID,
			const int nFromIndex,
			const int nToIndex
		  );

/**
 * 項目を複製します。
 * @param[in]	nTableID	テーブルID	
 * @param[in]	nFilterID	複製元の項目ID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DupRealFilter(
			const int nTableID,
			const int nFilterID
		  );

/**
 * 任意のデータ型に変換して項目を複製します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	複製元の項目ID
 * @param[in]	nDataType	作成するデータ型
 * @retval	1以上	生成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DupRealFilterEx(
			const int nTableID,
			const int nFilterID,
			const int nDataType
		  );

/**
 * カタログ定義ファイルからテーブルへデータを追加します。
 * @param[in]	nTableID		追加するテーブルID
 * @param[in]	nAppendPos		追加開始位置
 * @param[in]	nDataArraySize	追加する行数
 * @param[in]	szCatalogPath	カタログ定義ファイルの存在するパス
 * @param[in]	szCatalogName	カタログ定義ファイルの名称
 * @retval	0以上	追加された行数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AppendCatalogFile(
			const int	 nTableID,
			const int	 nAppendPos,
			const int	 nDataArraySize,
			const char   szCatalogPath[D5_MAX_PATH],
			const char   szCatalogName[D5_MAX_PATH]
			);

/**
 * カタログ定義ファイルからテーブルへデータを追加します。
 * @param[in]	nTableID		追加するテーブルID
 * @param[in]	nAppendPos		追加開始位置
 * @param[in]	nDataArraySize	追加する行数
 * @param[in]	szCatalogPath	構造定義ファイルの存在するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
 * @param[in]	szSourcePath	原始データファイルの存在するパス
 * @param[in]	szSourceName	原始データファイルの名称
 * @retval	0以上	追加された行数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AppendCatalogFileEx2(
			const int	 nTableID,
			const int	 nAppendPos,
			const int	 nDataArraySize,
			const char	 szCatalogPath[D5_MAX_PATH],
			const char	 szCatalogName[D5_MAX_PATH],
			const char	 szSourcePath[D5_MAX_PATH],
			const char	 szSourceName[D5_MAX_PATH]
			);

/**
 * カタログ定義ファイルからテーブルを生成します。
 * @param[in]	szCatalogPath	構造定義ファイルの存在するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
 * @param[in]	szSourcePath	原始データファイルの存在するパス
 * @param[in]	szSourceName	原始データファイルの名称
 * @param[in]	szTableName		新規に生成するテーブル名称
 * @retval	0以上	生成されたテーブルのID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddCatalogFileEx2(
			const char   szCatalogPath[D5_MAX_PATH],
			const char   szCatalogName[D5_MAX_PATH],
			const char   szSourcePath[D5_MAX_PATH],
			const char   szSourceName[D5_MAX_PATH],
			const char   szTableName[D5_MAX_PATH]
			);

/**
 * カタログ定義ファイルからテーブルを生成します。
 * 説明：　エラーの発生箇所、エラーとなったデータ、差し替え値がログファイルにタブ区切りのデータとして出力されます。
 *            ログファイルは、読み込んでテーブルにすることができますので、エラーの原因を特定し、修正することが容易になります。
 *            なお、本機能は、シングルスレッドで動作するため処理速度が低速です。
 * @param[in]	szCatalogPath	構造定義ファイルの存在するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
								"structinfo.txt"を使うことが多い
 * @param[in]	szSourcePath	原始データファイルの存在するパス
 * @param[in]	szSourceName	原始データファイルの名称
								"Sample.csv", "Sample.txt" など
 * @param[in]	szTableName		新規に生成するテーブル名称
								エンジンの命名規則と、ワークスペース上の
								既存テーブル名称によりエンジンにより変更されることがある
 * @retval	0以上	生成されたテーブルのID
 * @retval	負		エラーコード
 			 主にファイル関係のエラー（オープンできないなど）が返されるが、
			 メモリ不足、フォーマット異常などのエラーも返されることがある
 */
D5RESULT D5APICALL RD5AddCatalogFileChecker(
			const char   szCatalogPath[D5_MAX_PATH],         
			const char   szCatalogName[D5_MAX_PATH],         
            const char   szSourcePath[D5_MAX_PATH],          
            const char   szSourceName[D5_MAX_PATH],          
            const char   szTableName[D5_MAX_PATH]            
			);

/* */
D5RESULT D5APICALL RD5AppendRealFilter2(
			const int	 nTableID,
			const int	 nFilterID,
			const int	 nDataType,
			const int	 nAppendPos,
			const int	 nDataArraySize,
			const char	 szFilePath[D5_MAX_PATH],
			const char	 szFileName[D5_MAX_PATH]
			);

/**
 * 項目を追加します。
 * @param[in]	nTableID		追加するテーブルID
 * @param[in]	nLoc			項目挿入位置
 * @param[in]	szFilterName	新規に追加する項目名称
 * @param[in]	nDataType		追加項目のデータ型
 * @param[in]	nDataArraySize	追加するレコード配列のサイズ
 * @param[in]	nDataUnitSize	1レコードのサイズ(byte)
 * @param[in]	szFilePath		追加するデータのファイルパス
 * @param[in]	szFileName		追加するデータのファイル名称
 * @retval	0以上	生成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddRealFilter2(
			const int	nTableID,
			const int	nLoc,
			const char	szFilterName[D5_MAX_NAME_LENGTH],
			const int	nDataType,
			const int	nDataArraySize,
			const int	nDataUnitSize,
			const char	szFilePath[D5_MAX_PATH],
			const char	szFileName[D5_MAX_PATH]
		   );

/**
 * カタログ定義ファイルからテーブルを生成します。
 * @param[in]	szCatalogPath	カタログ定義ファイルの存在するパス
 * @param[in]	szCatalogName	カタログ定義ファイルの名称
 * @retval	0以上	生成されたテーブルのID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddCatalogFile(
		 const char   szCatalogPath[D5_MAX_PATH],
		 const char   szCatalogName[D5_MAX_PATH]
		 );

/**
 * スレーブ側テーブルの項目一覧を取得します。
 * @param[in]	nJoinTableID		JOINテーブルID
 * @param[out]	pnMasterTableID		マスタテーブルID
 * @param[out]	pnMasterSetID		JOIN作成時に使用したマスタテーブルのセットID
 * @param[out]	pnSlaveTableID		スレーブテーブルID
 * @param[out]	pnSlaveSetID		JOIN作成時に使用したスレーブテーブルのセットID
 * @param[out]	pnSlaveFilterCount	スレーブテーブルの項目数
 * @param[out]	anSlaveFilterIDs	スレーブテーブルの項目ID一覧
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnMasterTableID,pnMasterSetID,pnSlaveTableID,pnSlaveSetID,pnSlaveFilterCount,anSlaveFilterIDsは、
 * lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetSlaveInfo(
		 const int	nJoinTableID,
		 int	*pnMasterTableID,
		 int	*pnMasterSetID,
		 int	*pnSlaveTableID,
		 int	*pnSlaveSetID,
		 int	*pnSlaveFilterCount,
		 int	anSlaveFilterIDs[D5_MAX_FILTER_COUNT_REAL]
		  );

/**
 * スレーブテーブルの項目をマスタテーブルに転送します。
 * @param[in]	nJoinTableID	JOINテーブルID
 * @param[in]	nSlaveFilterID	転送元のスレーブテーブルの項目ID
 * @retval	0以上	追加作成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5MoveSlaveFlt2Master(
		 const	int	nJoinTableID,
		 const	int	nSlaveFilterID
		 );

/**
 * 行番号からセット内順序番号を検索します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nTargetRecNo	検索対象の行番号
 * @retval	0		条件に一致する行が見つからなかった
 * @retval	1以上	条件に一致するセット内順序番号
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5FindRecNoReal(
		 const	int	   nTableID,
		 const	int	   nSetID,
		 const	int	   nTargetRecNo
		 );

/**
 * 文字列型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		検索するテーブルID
 * @param[in]	nFilterID		検索対象となる文字列型の項目ID
 * @param[in]	nStrSrchKind	検索条件式を指定する値
 * @param[in]	szSrchStr1		1番目の検索条件文字列
 * @param[in]	szSrchStr2		2番目の検索条件文字列
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenStrFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nStrSrchKind,
		 const	char   szSrchStr1[D5_MAX_STRING_SIZE],
		 const	char   szSrchStr2[D5_MAX_STRING_SIZE]
		 );

/**
 * SJISコードの文字列型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		検索対象となる文字列型の項目ID
 * @param[in]	nStrSrchKind	検索条件式を指定する値
 * @param[in]	szSrchStr1		1番目の検索条件文字列
 * @param[in]	szSrchStr2		2番目の検索条件文字列
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenStrFindRealSJIS(
			const	int		nTableID,
			const	int		nFilterID,
			const	int		nStrSrchKind,
			const	char	szSrchStr1[D5_MAX_STRING_SIZE],
			const	char	szSrchStr2[D5_MAX_STRING_SIZE]
		);

/**
 * 文字列型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		検索対象となる文字列型の項目ID
 * @param[in]	nStrSrchKind	検索条件式を指定する値
 * @param[in]	szSrchStr1		1番目の検索条件文字列
 * @param[in]	szSrchStr2		2番目の検索条件文字列
 * @param[in]	nLocaleID		文字コードID
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenStrFindRealLocale(
			const	int		nTableID,
			const	int		nFilterID,
			const	int		nStrSrchKind,
			const	char	szSrchStr1[D5_MAX_STRING_SIZE],
			const	char	szSrchStr2[D5_MAX_STRING_SIZE],
			const	int		nLocaleID
		);

/**
 * 整数型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		検索するテーブルID
 * @param[in]	nFilterID		検索対象となる整数型の項目ID
 * @param[in]	nValSrchKind	検索条件式を指定する値
 * @param[in]	nSrchVal1		1番目の検索条件値
 * @param[in]	nSrchVal2		2番目の検索条件値
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenIntFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nValSrchKind,
		 const	int	   nSrchVal1,
		 const	int	   nSrchVal2
		 );

/**
 * 浮動小数点型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		検索するテーブルID
 * @param[in]	nFilterID		検索対象となる浮動小数点型の項目ID
 * @param[in]	nValSrchKind	検索条件式を指定する値
 * @param[in]	dSrchVal1		1番目の検索条件値
 * @param[in]	dSrchVal2		2番目の検索条件値
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenFloatFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nValSrchKind,
		 const	double dSrchVal1,
		 const	double dSrchVal2
		 );

/**
 * 検索ステータスを取得します。
 * @param[in]	nTableID	検索するテーブルID
 * @param[out]	pnHitCount	ルートセットで、検索条件に一致した件数
 * @param[out]	pnFilterID	検索対象の項目ID
 * @retval	0		検索条件が登録されていない
 * @retval	1以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnHitCount,pnFilterIDは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetFindStatus(
		 const int	nTableID,
		 int		*pnHitCount,
		 int		*pnFilterID
		 );

/**
 * 値ジャンプで条件に一致する行を見つけます。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSrchID		検索ID
 * @param[in]	nSetID		検索対象のセットID
 * @param[in]	nCurPos		現在の位置
 * @param[in]	nDir		検索方向
 * @param[out]	pnFilterID	検索対象の項目ID
 * @param[out]	pnNextPos	検索条件に一致するセット内順序番号
 * @retval	0	条件に一致する行が見つからなかった
 * @retval	1	条件に一致する行が見つかった
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnFilterID,pnNextPosは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetNextHitReal(
		 const	int		nTableID,
		 const	int		nSrchID,
		 const	int		nSetID,
		 const	int		nCurPos,
		 const	int		nDir,
		 int			*pnFilterID,
		 int			*pnNextPos
		 );

/**
 * 値ジャンプをクローズします。
 * @param[in]	nTableID	テーブルID
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5CloseFindReal(
		 const	int	   nTableID
		 );

/**
 * カテゴリ定義に基づき分類を行います。
 * @param[in]	nTableID			テーブルID
 * @param[in]	nFilterID			項目ID
 * @param[in]	nCategoryTableID	カテゴリ定義テーブルID
 * @retval	0以上	分類し、新規に作成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddCategoryReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nCategoryTableID
		 );

/**
 * 計算処理を行います。
 * @param[in]	nTableID	計算を行うテーブルID
 * @param[in]	nSetID		計算を行うセットID
 * @param[in]	nFilterID	計算を行う項目ID
 * @param[in]	nCalStart	計算開始位置
 * @param[in]	nCalCount	計算するレコード数
 * @param[in]	szFormula	計算式
 * @param[out]	szErrorRep	エラー説明
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * ErrorRepは無効なので空文字列を指定してください。
 */
D5RESULT D5APICALL RD5CalcReal(
		 const	int	   nTableID,
		 const	int	   nSetID,
		 const	int	   nFilterID,
		 const	int	   nCalStart,
		 const	int	   nCalCount,
		 const	char   szFormula[D5_MAX_STRING_SIZE],
		 char szErrorRep[D5_MAX_STRING_SIZE]
		 );

/**
 * テーブルが編集可能であるかを調べます。
 * @param[in]	nTableID	調べる対象のテーブルID
 * @param[out]	anReferIDs	このテーブルを参照しているテーブルIDの一覧
 * @retval	0		anReferIDsの有効サイズ（編集可能）
 * @retval	1以上	anReferIDsの有効サイズ（編集不可）
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * anReferIDsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5TableCanEdit(
			const int  nTableID,
			int  anReferIDs[D5_MAX_TABLE_COUNT]
		   );

/**
 * 行を削除します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nDelStart	削除開始行
 * @param[in]	nDelCount	削除する行数
 * @retval	0以上	実際に削除された数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DeleteRealRows(
			const int nTableID,
			const int nDelStart,
			const int nDelCount
		   );

/**
 * 行を削除します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nDelStart	削除開始行
 * @param[in]	nDelCount	削除する行数
 * @retval	0以上	実際に削除された数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DeleteRealRowsEx(
			const int nTableID,
			const int nSetID,
			const int nDelStart,
			const int nDelCount
		   );

/**
 * 行を挿入します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nInsPos		挿入位置
 * @param[in]	nInsCount	挿入する行数
 * @retval	0以上	実際に削除された数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5InsertRealRows(
			const int nTableID,
			const int nInsPos,
			const int nInsCount
		   );

/**
 * データを上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	pvWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pvWriteDataは、データ型に合わせたlfmutilのクラスを使用して配列へのポインタを指定してください。
 * 1データのみの場合は、{@link #RD5OverwriteRealExIntR1},{@link #RD5OverwriteRealExDblR1}
 * ,{@link #RD5OverwriteRealExNumericR1},{@link #RD5OverwriteRealExStrR1}を使用してください。
 */
D5RESULT D5APICALL RD5OverwriteRealEx(
			const int   nTableID,
			const int   nSetID,
			const int   nFilterID,
			const int   nWriteStart,
			const int   nWriteCount,
			const void	*pvWriteData
		  );

/**
 * データを上書きします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nWriteStart		書き込み開始位置
 * @param[in]	nWriteCount		書き込み数
 * @param[in]	pvWriteData		書き込みデータ
 * @retval	0以上	書き込みに成功したデータ数
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pvWriteDataは、データ型に合わせたlfmutilのクラスを使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5FillRealEx(
			const int   nTableID,
			const int   nSetID,
			const int   nFilterID,
			const int   nWriteStart,
			const int   nWriteCount,
			const void  *pvWriteData
		  );

/**
 * 単一データを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		セット内順序番号
 * @param[out]	pnDataType	取得したデータ型
 * @param[out]	acBuf		取得したデータ
 * @retval	0以上	acBuf上で使用された領域長
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetData1IntR1},{@link #RD5GetData1DblR1},{@link #RD5GetData1StrR1},{@link #RD5GetData1NumericR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetData1(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const int nRowNo,
			int	*pnDataType,
			char acBuf[D5_MAX_STRING_SIZE+1]
		  );

/**
 * 複数データを取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		項目ID
 * @param[in]	nSetID			セットID
 * @param[in]	nRowNo			セット内順序番号
 * @param[out]	pnDataType		取得したデータ型
 * @param[out]	pnGotCount		取得したデータ数
 * @param[out]	acBuf			取得した文字列型以外のデータ または 文字列型データのacCharBuf内データ開始位置
 * @param[out]	acCharBuf		取得した文字列データ
 * @retval	0以上	整数・浮動小数点型：取得した行のうち、単一で最大のデータサイズ(byte) 文字列型：NULL終端を含まない最終行のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetData1MIntR1},{@link #RD5GetData1MDblR1},{@link #RD5GetData1MNumericR1},{@link #RD5GetData1MStrR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetData1M(
			const int	nTableID,
			const int	nFilterID,
			const int	nSetID,
			const int	nRowNo,
			int		*pnDataType,
			int		*pnGotCount,
			char	acBuf[sizeof(double) * D5_MAX_CACHE],
			char	acCharBuf[D5_MAX_STRING_SIZE]
		  );

/* */
D5RESULT D5APICALL RD5GetRowNo(
			const int  nTableID,
			const int  nSetID,
			const int  nRowNo,
			int		   *pnRow1,
			int		   *pnRow2
		   );

/**
 * ルートセットにおける行位置を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		取得したいセット内順序番号(1から始まる)
 * @param[out]	pnRow1		REALテーブル：取得する行番号 JOINテーブル：マスタ側の行番号
 * @param[out]	pnRow2		REALテーブル：使用しない JOINテーブル：スレーブ側行番号
 * @retval	4	REALテーブルの場合の成功
 * @retval	8	JOINテーブルの場合の成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnRow1,pnRow2は、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetRowNo1(
			const int nTableID,
			const int nSetID,
			const int nRowNo,
			int		*pnRow1,
			int		*pnRow2
		   );

/**
 * ルートセットにおける複数の行位置を取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nRowNo		取得したいセット内順序番号(1から始まる)
 * @param[out]	pnGotCount	取得した行数
 * @param[out]	anRow1		REALテーブル：取得する行番号 JOINテーブル：マスタ側の行番号
 * @param[out]	anRow2		REALテーブル：使用しない JOINテーブル：スレーブ側行番号
 * @retval	4	REALテーブルの場合の成功
 * @retval	8	JOINテーブルの場合の成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnGotCount,anRow1,anRow2は、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL RD5GetRowNo1M(
			const int	nTableID,
			const int	nSetID,
			const int	nRowNo,
			int			*pnGotCount,
			int			anRow1[D5_MAX_CACHE],
			int			anRow2[D5_MAX_CACHE]
		   );

/**
 * セット内順序番号による検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	nX			1番目の検索条件(セット内順序番号)
 * @param[in]	nY			2番目の検索条件(セット内順序番号)
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByDispRowNoReal(
			 const int nTableID,
			 const int nSetID,
			 const int nOpeNo,
			 const int nX,
			 const int nY
		 );

/**
 * ルートセットの行番号による検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nTableNo	マスタテーブルか、スレーブテーブルかの設定
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	nX			1番目の検索条件(行番号)
 * @param[in]	nY			2番目の検索条件(行番号)
 * @retval	0以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByRowNo(
			const int nTableID,
			const int nTableNo,
			const int nSetID,
			const int nOpeNo,
			const int nX,
			const int nY
		   );

/**
 * 指定した項目のデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	pvX			1番目の検索条件データ
 * @param[in]	pvY			2番目の検索条件データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5SearchByFieldIntR1},{@link #RD5SearchByFieldDblR1},{@link #RD5SearchByFieldNumericR1},{@link #RD5SearchByFieldStrR1}を使用してください。
 */
D5RESULT D5APICALL RD5SearchByField(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const int nOpeNo,
			const void *pvX,
			const void *pvY
		  );

/**
 * 指定した項目の、マルチバイト文字コードを使った検索を行います。
 * 文字列項目以外の検索には{@link #RD5SearchByField}を使用してください。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	pvX			1番目の検索条件データ
 * @param[in]	pvY			2番目の検索条件データ
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5SearchByFieldSJISR1}を使用してください。
 */
D5RESULT D5APICALL RD5SearchByFieldSJIS(
            const int nTableID,
            const int nFilterID,
            const int nSetID,
            const int nOpeNo,
            const void *pvX,
            const void *pvY
          );

/**
 * 指定した項目の、マルチバイト文字コードを使った検索を行います。
 * 文字列項目以外の検索には{@link #RD5SearchByField}を使用してください。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nOpeNo		検索条件式
 * @param[in]	pvX			1番目の検索条件データ
 * @param[in]	pvY			2番目の検索条件データ
 * @param[in]	nLocaleID	文字コードID
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5SearchByFieldLocaleR1}を使用してください。
 */
D5RESULT D5APICALL RD5SearchByFieldLocale(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const int nOpeNo,
			const void *pvX,
			const void *pvY,
			const int nLocaleID
		  );

/**
 * 指定した項目の、ワイルドカードを含むデータによる検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	szText		検索条件式
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByFieldWildCard(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const char *szText
		);

/**
 * 文字列で書かれた検索式で検索を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	szText		検索文字列
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByText(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE]
				);

/**
 * 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	szText		検索文字列
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByTextSJIS(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE]
				);

/**
 * 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	szText		検索文字列
 * @param[in]	nLocaleID	文字コードID
 * @retval	1以上	検索結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SearchByTextLocale(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE],
				const int nLocaleID
				);

/**
 * 指定された項目でソート処理を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nSetID		セットID
 * @param[in]	nSortDir	ソートする方向
 * @retval	1以上	ソート結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SortByField(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const int nSortDir
		  );

/**
 * 行番号によるソート処理を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nTableNo	マスタまたはスレーブテーブルを指定
 * @param[in]	nSetID		セットID
 * @param[in]	nSortDir	ソートする方向
 * @retval	1以上	ソート結果で新規に生成されたセットID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SortByRowNo(
			const int nTableID,
			const int nTableNo,
			const int nSetID,
			const int nSortDir
		  );

/**
 * 項目詳細情報取得機能をオープンします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	nFilterID		項目ID
 * @param[out]	pnDataType		データ型
 * @param[out]	pnRangeSize		登録されている値の総数
 * @param[out]	pnNonZeroCount	ゼロでない値を持つレコード数
 * @retval	1以上	成功（詳細表示ハンドル）
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnDataType,pnRangeSize,pnNonZeroCountは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT	D5APICALL RD5OpenDetailInfo(
		  const int nTableID,
		  const int nSetID,
		  const int nFilterID,
		  int		*pnDataType,
		  int		*pnRangeSize,
		  int		*pnNonZeroCount
		  );

/**
 * オープンした項目詳細情報の項目値を指定した順序に並べ、指定した順序番号の項目値を取得します。
 * （先頭の項目値の番号を1とし、並びの順番に番号がつけられます）
 * @param[in]	nHandle			オープン時に取得したハンドル
 * @param[in]	nOrderByN		存在数順に並べるかどうかを指定
 * @param[in]	nReverse		逆順にするかどうかを指定
 * @param[in]	nZeroSuppress	存在数が0のデータを含めるかどうかを指定
 * @param[in]	nRow			項目値の順序番号
 * @param[out]	pnDataType		データ型
 * @param[out]	pvData			取得データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnDataTypeは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 * pvDataは、データ型に合わせたlfmutilのクラスを使用してポインタを指定してください。
 */
D5RESULT	D5APICALL RD5GetDetailValue(
		  const int   nHandle,
		  const int   nOrderByN,
		  const int   nReverse,
		  const int   nZeroSuppress,
		  const int   nRow,
		  int		  *pnDataType,
		  void		  *pvData
		  );

/**
 * オープンした項目詳細情報の存在数を取得します。
 * @param[in]	nHandle			オープン時に取得したハンドル
 * @param[in]	nOrderByN		存在数順に並べるかどうかを指定
 * @param[in]	nReverse		逆順にするかどうかを指定
 * @param[in]	nZeroSuppress	存在数が0のデータを含めるかどうかを指定
 * @param[in]	nRow			項目値の順序番号
 * @param[out]	pnCount			取得データ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnCountは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT	D5APICALL RD5GetDetailCount(
		  const int   nHandle,
		  const int   nOrderByN,
		  const int   nReverse,
		  const int   nZeroSuppress,
		  const int   nRow,
		  int		  *pnCount
		  );

/**
 * オープンした項目詳細情報をクローズします。
 * @param[in]	nHandle	オープン時に取得したハンドル
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT	D5APICALL RD5CloseDetailInfo(
		  const int	 nHandle
		  );

/**
 * 集計を行い、集計テーブルを作成します。
 * @param[in]	nTableID			テーブルID
 * @param[in]	nSetID				セットID
 * @param[in]	nDimCount			集計次元数
 * @param[in]	pnDimFilterIDs		集計次元となる項目ID配列
 * @param[in]	nMeasureCount		集計測度の数
 * @param[in]	pnMeasureFilterIDs	集計測度となる項目ID配列
 * @param[in]	pnSummaryTypes		pnMeasureFilterIDsの各項目に集計種別を指定する配列
 * @param[in]	pnFloatFormats		pnMeasureFilterIDsの各項目に固定小数点を使用するかしないかを指定する配列
 * @retval	1以上	生成された集計結果の新規テーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pnDimFilterIDs,pnMeasureFilterIDs,pnSummaryTypes,pnFloatFormatsは、lfmutilの{@link CTypeIntAr}を使用してポインタを指定してください。
 */
D5RESULT D5APICALL  RD5NonCubeSum(
			const int nTableID,
			const int nSetID,
			const int nDimCount,
			const int *pnDimFilterIDs,
			const int nMeasureCount,
			const int *pnMeasureFilterIDs,
			const int *pnSummaryTypes,
			const int *pnFloatFormats
			);

/**
 * テーブル名称からテーブルIDを取得します。
 * @param[in]	szTableName	テーブル名称
 * @retval	0以上	テーブルID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL  RD5GetTableIDFromName(
			const  char szTableName[D5_MAX_NAME_LENGTH]
		 );

/**
 * 項目名称から項目IDを取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	szFilterName	項目名称
 * @retval	1以上	項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL  RD5GetFilterIDFromName(
			const int nTableID,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * REALテーブル又はJOINテーブルの項目名称から項目IDを取得します。
 * @param[in]	nTableID		テーブルID（JOINテーブル又はREALテーブル）
 * @param[in]	nIsSlave		JOINテーブルの場合、マスタ側かスレーブ側かを指定
 * @param[in]	szFilterName	項目名称
 * @retval	1以上	項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL  RD5GetFilterIDFromName2(
			const int nTableID,
			const int nIsSlave,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * テーブル名称を変更します。
 * @param[in]	nTableID		変更するテーブルID
 * @param[in]	szTableName		新規に設定するテーブル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetTableName(
			const int  nTableID,
			const char szTableName[D5_MAX_NAME_LENGTH]
			);

/**
 * 項目の名称を変更します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		項目ID
 * @param[in]	szFilterName	項目の新規名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetFilterName(
			const int  nTableID,
			const int  nFilterID,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * セット名称を設定します。
 * @param[in]	nTableID	セットの属するテーブル名称
 * @param[in]	nSetID		セットID
 * @param[in]	szSetName	設定するセット名称を格納した文字配列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetSetName(
			const int  nTableID,
			const int  nSetID,
			const char szSetName[D5_MAX_NAME_LENGTH]
			);

/**
 * 項目IDから項目名称を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		項目ID
 * @param[out]	szFilterName	項目名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetFilterNameR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetFilterName(
			const int  nTableID,
			const int  nFilterID,
			char szFilterName[D5_MAX_NAME_LENGTH]
		   );

/**
 * セット名称を取得します。
 * @param[in]	nTableID	セットの属するテーブルID
 * @param[in]	nSetID		セットID
 * @param[out]	szSetName	セット名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetSetNameR1}を使用してください。
 */
D5RESULT D5APICALL RD5GetSetName(
			const int nTableID,
			const int  nSetID,
			char szSetName[D5_MAX_NAME_LENGTH]
		   );

/**
 * 文字列の末尾のスペースを削除するかどうかについてフラグを設定します。
 * @param[in]	nFlag	文字列末尾のスペース削除チェックフラグ
 * @retval	0	常に0
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetTailSpaceFlag(
		 const	int	nFlag
		 );

/**
 * サーバのIPアドレスを取得します。
 * @param[out]	szIPAddress	IPアドレス
 * @retval	0	ローカルサーバ
 * @retval	1	リモートサーバ
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5GetServerIPAddress(char szIPAddress[D5_MAX_NAME_LENGTH]);

/**
 * サーバの環境情報を取得します。
 * @param[out]	pEnvironment	環境情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetEnvironment( TREnvironment *pEnvironment);

/**
 * エンジンのDB文字コードを設定します。
 * @param[in]	szDBCode	DB文字コード
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetDBCharCode( const char *szDBCode );

/**
 * 指定されたD5DファイルのヘッダからDBコード、バージョンを読み出します。
 * @param[in]	szDBPath		D5Dファイルの存在するパス
 * @param[in]	szDBName		D5Dファイルの名称
 * @param[out]	pD5FileInfo		D5Dファイル情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pD5FileInfo->Versionの各要素取得には、lfmutilの{@link #int_at}を使用してください。
 */
D5RESULT D5APICALL RD5GetD5DFileInfo( const char szDBPath[D5_MAX_PATH],
										const char szDBName[D5_MAX_PATH],
										D5FileInfo	*pD5FileInfo
										);

/**
 * 指定されたD5TファイルのヘッダからDBコード、バージョンを読み出します。
 * @param[in]	szTablePath		D5Tファイルの存在するパス
 * @param[in]	szTableName		D5Tファイルの名称
 * @param[out]	pD5FileInfo		D5Tファイル情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * pD5FileInfo->Versionの各要素取得には、lfmutilの{@link #int_at}を使用してください。
 */
D5RESULT D5APICALL RD5GetD5TFileInfo( const char szTablePath[D5_MAX_PATH],
										const char szTableName[D5_MAX_PATH],
										D5FileInfo	*pD5FileInfo
										);

/**
 * サーバ側のカレントディレクトリを取得します。
 * @param[out]	szDirectory	カレントディレクトリ名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetCurrentDirectory(
			char	szDirectory[D5_MAX_PATH]
			);

/**
 * サーバ側のカレントディレクトリを変更します。
 * @param[in]	szDirectory	変更先ディレクトリ名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserSetCurrentDirectory(
			const char	szDirectory[D5_MAX_PATH]
			);

/**
 * サーバのファイルサイズを取得します。
 * @param[in]	szFileName	ファイル名称
 * @retval	0以上	ファイルサイズ（8btye整数型） Windows：int64, Linux：long long
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULTL D5APICALL	RD5BrowserGetFileSize(
			const char	szFileName[D5_MAX_NAME_LENGTH]
		);

/**
 * サーバのファイル一覧を取得します。
 * @param[in]	szFindCondition	ファイル検索条件
 * @param[in]	nStart			取得開始位置
 * @param[out]	pnExist			検索条件に合致した数
 * @param[out]	pnGotCount		取得した数
 * @param[out]	acAttrList		ファイルアトリビュートの配列
 * @param[out]	szListBuf		ファイル名称一覧
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetFileList(
			const char	szFindCondition[D5_MAX_NAME_LENGTH],
			const int	nStart,
			int			*pnExist,
			int			*pnGotCount,
			char		acAttrList[D5_MAX_STRING_SIZE / 2],
			char		szListBuf[D5_MAX_STRING_SIZE]
		);

/**
 * サーバからファイルを読み込みます。
 * @param[in]	szFileName	ファイル名称
 * @param[in]	nStart		読出し開始位置
 * @param[out]	pnFileSize	ファイルサイズ
 * @param[out]	pnGetLen	読み出したサイズ(byte)
 * @param[out]	acFileBody	ファイルデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetFileEx(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const int	nStart,
			int			*pnFileSize,
			int			*pnGetLen,
			char		acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * サーバからファイルを読み込みます。
 * @param[in]	szFileName		ファイル名称
 * @param[in]	n64Start		読出し開始位置
 * @param[out]	pn64FileSize	ファイルサイズ
 * @param[out]	pnGetLen		読み出したサイズ(byte)
 * @param[out]	acFileBody		ファイルデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetFileEx64(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const INT64	n64Start,
			INT64		*pn64FileSize,
			int			*pnGetLen,
			char		acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * サーバからファイルを読み込みます。
 * @param[in]	szFileName	ファイル名称
 * @param[out]	pnFileSize	ファイルサイズ
 * @param[out]	pnGetLen	読み出したサイズ(byte)
 * @param[out]	acFileBody	ファイルデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetFile(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			int		*pnFileSize,
			int		*pnGetLen,
			char	acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * サーバからファイルを読み込みます。
 * @param[in]	szFileName		ファイル名称
 * @param[out]	pn64FileSize	ファイルサイズ
 * @param[out]	pnGetLen		読み出したサイズ(byte)
 * @param[out]	acFileBody		ファイルデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserGetFile64(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			INT64	*pn64FileSize,
			int		*pnGetLen,
			char	acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * サーバにファイルを作成します。
 * @param[in]	szFileName	ファイル名称
 * @param[in]	nPutLen		書き出すデータサイズ(byte)
 * @param[in]	acFileBody	書き出すデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserPutFile(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const int	nPutLen,
			const char	acFileBody[D5_MAX_TEXT_SIZE]
			);

/**
 * サーバのファイルを削除します。
 * @param[in]	szFileName	削除するファイル名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserDelFile(
			const char	szFileName[D5_MAX_PATH]
		);

/**
 * サーバにディレクトリを作成します。
 * @param[in]	szDirectory	作成ディレクトリ名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL	RD5BrowserMakeDirectory(
			const char	szDirectory[D5_MAX_PATH]
		);

/**
 * サーバにディレクトリを作成します。
 * @param[in]	szDirectory	削除するディレクトリ名称
 * @param[in]	nIsAll		削除内容詳細
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5BrowserDelDirectory(
			const char szDirectory[D5_MAX_PATH],
			const int  nIsAll
			);

/**
 * サーバのファイル又はディレクトリ名称を変更します。また、指定のディレクトリに移動します。
 * @param[in]	szOldName	ファイル名称
 * @param[in]	szNewName	作成位置
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5BrowserMove(
			const char szOldName[D5_MAX_PATH],
			const char szNewName[D5_MAX_PATH]
			);

// サーバーに小規模なファイルを作成します
/**
 * サーバにファイルを作成します。
 * @param[in]	szFileName	ファイル名称
 * @param[in]	nStart		作成位置
 * @param[in]	nPutLen		書き出すデータサイズ(byte)
 * @param[in]	acFileBody	書き出すデータ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5BrowserPutFileEx(
			const char szFileName[D5_MAX_NAME_LENGTH],
			const int  nStart,
			const int  nPutLen,
			const char acFileBody[D5_MAX_TEXT_SIZE]
			); 

/**
 * カンマ区切りファイルへデータをエクスポートします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	anIDList	項目IDリスト
 * @param[in]	nRowFrom	出力を開始する行
 * @param[in]	nRowTo		出力の終了行
 * @param[in]	nDateSep	日付データの区切り文字を指定
 * @param[in]	szDBPath	出力ファイルへのパス
 * @param[in]	szDBName	出力ファイル名称
 * @param[in]	szDefFile	浮動小数点型データの定義ファイル
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5ExportAsCSVwithF(
		const int nTableID,
		const int nSetID,
		const int anIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szDBPath[D5_MAX_PATH],
		const char szDBName[D5_MAX_PATH],
		const char szDefFile[D5_MAX_PATH]
		);	

/**
 * TAB区切りファイルへデータをエクスポートします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	anIDList	項目IDリスト
 * @param[in]	nRowFrom	出力を開始する行
 * @param[in]	nRowTo		出力の終了行
 * @param[in]	nDateSep	日付データの区切り文字を指定
 * @param[in]	szDBPath	出力ファイルへのパス
 * @param[in]	szDBName	出力ファイル名称
 * @param[in]	szDefFile	浮動小数点型データの定義ファイル
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5ExportAsTABwithF(
		const int nTableID,
		const int nSetID,
		const int anIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szDBPath[D5_MAX_PATH],
		const char szDBName[D5_MAX_PATH],
		const char szDefFile[D5_MAX_PATH]
		);

/**
 * テーブルのデータを、浮動小数点の桁数を指定して、カタログ定義ファイルへエクスポートします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	anIDList		出力する項目IDリスト
 * @param[in]	nType			出力するファイルタイプ
 * @param[in]	nRowFrom		出力する行の開始位置
 * @param[in]	nRowTo			出力する行の終了位置
 * @param[in]	nDateSep		日付データの区切り文字を指定
 * @param[in]	szCatalogPath	構造定義ファイルを出力するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
 * @param[in]	szDefFile		浮動小数点型データの定義ファイル
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5SaveAsCatalogwithF(
		const int nTableID,
		const int nSetID,
		const int anIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nType,
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szCatalogPath[D5_MAX_PATH],
		const char szCatalogName[D5_MAX_PATH],
		const char szDefFile[D5_MAX_PATH]
		);

/**
 * テーブルのデータを、浮動小数点の桁数を指定して、カタログ定義ファイルへエクスポートします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nSetID			セットID
 * @param[in]	anIDList		出力する項目IDリスト
 * @param[in]	nType			出力するファイルタイプ
 * @param[in]	nRowFrom		出力する行の開始位置
 * @param[in]	nRowTo			出力する行の終了位置
 * @param[in]	nDateSep		日付データの区切り文字を指定
 * @param[in]	szCatalogPath	構造定義ファイルを出力するパス
 * @param[in]	szCatalogName	構造定義ファイルの名称
 * @param[in]	szDefFile		浮動小数点型データの定義ファイル
 * @param[in]	szSourcePath	原始データファイルの存在するパス
 * @param[in]	szSourceName	原始データファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5SaveAsCatalogwithFEx(
		const int nTableID,
		const int nSetID,
		const int anIDList[D5_MAX_FILTER_COUNT_JOIN],
		const int nType,
		const int nRowFrom,
		const int nRowTo,
		const int nDateSep,
		const char szCatalogPath[D5_MAX_PATH],
		const char szCatalogName[D5_MAX_PATH],
		const char szDefFile[D5_MAX_PATH],
        const char szSourcePath[D5_MAX_PATH],
        const char szSourceName[D5_MAX_PATH]
		);

/**
 * D5Dデータを共有メモリ領域から読み込みます。
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5LoadDBFromSharedMemory();

/* */
D5RESULT D5APICALL RD5UnLoadSharedMemoryDB();

/* */
D5RESULT D5APICALL RD5UnMapSharedMemory();

/**
 * D5Dデータを共有メモリ領域へ生成します。
 * @param[in]	szDBPath	D5Dファイルの存在するパス
 * @param[in]	szDBName	D5Dファイルの名称
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5CreateSharedMemoryDB(
			const char szDBPath[D5_MAX_PATH],
			const char szDBName[D5_MAX_PATH]
			 );

/**
 * D5Dデータを共有メモリ領域から解放します。
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5ReleaseSharedMemoryArea();

/**
 * サーバのシステムメモリサイズを取得します。
 * @param[out]	pMemInfo	メモリサイズ情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5GetSystemMemInfo(TRMemInfo *pMemInfo);

/**
 * テーブルが共有メモリ上にあるか判別します。
 * @param[in]	nTableID	テーブルID
 * @retval	1	共有メモリから参照されている。
 * @retval	0	共有メモリから参照されていない。
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5IsSharedMemoryTable(int nTableID);

/**
 * 項目情報を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nGet			情報を取得する項目数
 * @param[out]	pnFltCnt		情報を取得した項目数
 * @param[out]	aFilterInfo		項目情報
 * @param[out]	aacAttrs		小数点以下表示桁数の設定情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * スクリプト言語ではサポートしません。
 */
D5RESULT D5APICALL RD5GetAllFilterInfo(
				const int nTableID,
				const int nGet,
				int *pnFltCnt,
				TRFilterInfo aFilterInfo[D5_MAX_FILTER_COUNT_JOIN],
				char aacAttrs[D5_MAX_FILTER_COUNT_JOIN][D5_FILTER_ATTR_SIZE]
				);

/**
 * 使用メモリサイズを取得します。
 * @retval	0以上	メモリバイト数
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetTotalMemorySize();

/**
 * 共用メモリを含めた使用メモリサイズを取得します。
 * @retval	0以上	メモリサイズ(8byte整数型) Windows：int64, Linux：long long
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetTotalMemorySizeWithShared();

/**
 * テーブルの使用メモリサイズを取得します。
 * @param[in]	nTableID	テーブルID
 * @retval	0以上	メモリバイト数(8byte整数型) Windows：int64, Linux：long long
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetTableMemorySize(const  int nTableID);

/**
 * 項目の使用メモリサイズを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	0以上	メモリバイト数（8byte整数） Windows：int64, Linux：long long
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetFilterMemorySize(const int nTableID, const int nFilterID);

/**
 * セットの仕様メモリサイズを取得します。
 * @param[in]	nTableID	テーブルID
 * @param[out]	nSetID		セットID
 * @retval	0以上	指定したセットの使用メモリサイズ(8byte整数型) Windows：int64, Linux：long long
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetSetMemorySize(const int nTableID, const int nSetID);

/**
 * エンジンで使用したメモリを開放します。
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT  D5APICALL RD5Shutdown();

/**
 * 高速検索の実行宣言を行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nMark		高速検索指定フラグ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5HighSpeedSearchSetMark(
				const int nTableID,
				const int nSetID,
				const int nFilterID,
				const int nMark
				);

/**
 * 高速検索の対象かどうかをチェックします。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nSetID		セットID
 * @param[in]	nFilterID	項目ID
 * @retval	1	高速検索の対象である
 * @retval	0	高速検索の対象でない
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5HighSpeedSearchHasMark(
				const int nTableID,
				const int nSetID,
				const int nFilterID
				);

/**
 * 通常検索／高速検索状態の切り替えを行います。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @param[in]	nEnable		検索状態の切り替えフラグ
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5HighSpeedSearchEnable(
				const int nTableID,
				const int nFilterID,
				const int nEnable
				);

/**
 * 通常検索／高速検索の状態を問い合わせます。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	項目ID
 * @retval	1	高速検索状態
 * @retval	0	通常検索状態
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5HighSpeedSearchIsEnabled(
				const int nTableID,
				const int nFilterID
				);

/**
 * ライセンスキーのパスワード認証を行います。
 * @param[in]	szLicenseKey	ライセンスキー
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5SetPassword(
			const char szLicenseKey[D5_PASSWORD_LENGTH + 1]
);

/* */
D5RESULT D5APICALL RD5GetSerial(
			const char szSerial[D5_SERIALNUM_SIZE + 1]
			);

/**
 * 行数制限値を取得します。
 * @retval	0		無制限
 * @retval	1以上	行数制限値
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetLimitRowSize();

/**
 * メモリ使用量制限値を取得します。
 * @retval	0以上	メモリ使用量制限値(byte)
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULTL D5APICALL RD5GetLimitMemSize();

/* */
D5RESULT  D5APICALL RD5GetLimitCPUSize();

/* */
D5RESULT D5APICALL	RD5GetLicenseInfo(
	TLicenseData *pLicenseInfo
);

/**
 * NUMERIC項目情報を取得します。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		フィルタID
 * @param[out]	pNumericInfo	NUMERIC項目情報
 * @param[out]	szRoundMode		丸めモード文字列
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 本APIは使用せず、{@link #RD5GetNumericInfoR1}を使用してください。
 */
D5RESULT D5APICALL	RD5GetNumericInfo(
	const int nTableID,
	const int nFilterID,
	NumericInfo *pNumericInfo,
	char *szRoundMode
);

/**
 * NUMERIC項目情報をセットします。
 * @param[in]	nTableID		テーブルID
 * @param[in]	nFilterID		フィルタID
 * @param[in]	pNumericInfo	NUMERIC項目情報
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL	RD5SetNumericInfo(
	const int nTableID,
	const int nFilterID,
	NumericInfo *pNumericInfo
);

/**
 * 浮動小数点型の項目を条件として、値ジャンプ機能をオープンします。
 * @param[in]	nTableID		検索するテーブルID
 * @param[in]	nFilterID		検索対象となる浮動小数点型の項目ID
 * @param[in]	nValSrchKind	検索条件式を指定する値
 * @param[in]	SrchVal1		1番目の検索条件値
 * @param[in]	SrchVal2		2番目の検索条件値
 * @retval	0以上	検索ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5OpenNumericFindReal(
			const	int		nTableID,
			const	int		nFilterID,
			const	int		nValSrchKind,
			const	Numeric	SrchVal1,
			const	Numeric	SrchVal2
);

/**
 * NUMERIC型の項目を追加します。NUMERIC型の項目に必要なNumericInfo構造体を同時に設定します。
 * @param[in]	nTableID		追加するテーブルID
 * @param[in]	nLoc			項目挿入位置
 * @param[in]	szFilterName	新規に追加する項目名称
 * @param[in]	nDataArraySize	追加するレコード配列のサイズ
 * @param[in]	nScale			NumericInfo構造体に設定するScale値
 * @param[in]	nRoundMode		NumericInfo構造体に設定するRoundMode値
 * @param[in]	szFilePath		追加するデータのファイルパス
 * @param[in]	szFileName		追加するデータのファイル名称
 * @retval	0以上	生成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5AddRealFilter2Numeric(
			const int	nTableID,
			const int	nLoc,
			const char	szFilterName[D5_MAX_NAME_LENGTH],
			const int	nDataArraySize,
			const int	nScale,
			const int	nRoundMode,
			const char	szFilePath[D5_MAX_PATH],
			const char	szFileName[D5_MAX_PATH]
);

/**
 * NUMERIC型のデータ型に変換して項目を複製します。
 * @param[in]	nTableID	テーブルID
 * @param[in]	nFilterID	複製元の項目ID
 * @param[in]	nScale		項目に設定するScale値
 * @param[in]	nRoundMode	項目に設定するRoundMode値
 * @retval	1以上	生成された項目ID
 * @retval	負		エラーコード
 * 
 * @par	スクリプト言語から使用する際の注意事項:
 * 特になし
 */
D5RESULT D5APICALL RD5DupRealFilterExNumeric(
			const int	nTableID,
			const int	nFilterID,
			const int	nScale,
			const int	nRoundMode
);

/* */
D5RESULT D5APICALL RD5IntegratedSortByField(
			const int nTableID,
			const int nSetID,
			const int anFilterIDList[D5_MAX_FILTER_COUNT_REAL],
			const int anSortDirList[D5_MAX_FILTER_COUNT_REAL]
		);

/* */
D5RESULT D5APICALL RD5SaveDBAsOldVer(
		 const char szDBPath[D5_MAX_PATH],
		 const char szDBName[D5_MAX_PATH],
		 const int	nFileVersion
		 );

/* */
D5RESULT D5APICALL RD5SaveRealTableOldVer(
		 const char	szTablePath[D5_MAX_PATH],
		 const int	nTableID,
		 const int	nFileVersion
		 );

/* */
D5RESULT D5APICALL RD5SaveRealTableAsOldVer(
		 const char	szTablePath[D5_MAX_PATH],
		 const char szTableName[D5_MAX_PATH],
		 const int	nTableID,
		 const int	nFileVersion
		);



/*
 * WAIT FLAG DEFINITIONS
 */

#define D5_LOCK_WAIT      (0)
#define D5_LOCK_NOWAIT    (1)

#define D5_SHMLOCK_WAIT   (D5_LOCK_WAIT)   /* MODE VALUE */
#define D5_SHMLOCK_NOWAIT (D5_LOCK_NOWAIT) /* MODE_VALUE */

			
/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        SETUP THE D5TSHM FUNCTION (FOR ADMIN PROCESS)   */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmSetup(int nTableMax);            */
/*                                                        */
/* ARGUMENTS:                                             */
/*        nTableMax: MAXIMUM NUMBER OF LOADED TABLES      */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          nTableMax IS NON POSITIVE.                    */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_OUT_OF_MEMORY:                         */
/*          NO AVAILABLE MEMORY                           */
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_D5TSHM_SMCS_READY:                     */
/*          SETUP IS ALREADY DONE.                        */
/*          NUMBER OF TABLES IS ZERO.                     */
/*        D5_ERROR_D5TSHM_SMCS_ACTIVE:                    */
/*          SETUP IS ALREADY DONE.                        */
/*          NUMBER OF TABLES IS POSITIVE.                 */
/*        D5_ERROR_FILE_IO: FILE I/O ERROR                */
/*        D5_INVALID_OS: THE OS IS NOT 64-BIT.            */
/*        D5_ERROR_D5TSHM_TOO_MANY_D5TSHM_TABLES:         */
/*          nTables EXCEEDS THE UPPER LIMIT.              */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_UNKNOWN: UNKNOWN ERROR                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000018 : D5_ERROR_OUT_OF_MEMORY                 */ 
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE000025C : D5_ERROR_D5TSHM_SMCS_READY             */
/*    0xE000025D : D5_ERROR_D5TSHM_SMCS_ACTIVE            */
/*    0xE000008D : D5_ERROR_FILE_IO                       */
/*    0xE0000110 : D5_INVALID_OS                          */
/*    0xE000025E : D5_ERROR_D5TSHM_TOO_MANY_D5TSHM_TABLES */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* USED LOCKS:                                            */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.24 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmSetup(int nTableMax);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        SHUTDOWN THE D5TSHM FUNCTION                    */
/*        (FOR ADMIN PROCESS)                             */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmShutdown();                      */
/*                                                        */
/* ARGUMENTS:                                             */
/*        <NONE>                                          */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_D5TSHM_SMCS_INIT:                      */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_D5TSHM_SMCS_ACTIVE:                    */
/*          NUMBER OF LOADED TABLES IS POSITIVE.          */
/*        D5_ERROR_UNKNOWN:                               */
/*           UNKNOWN ERROR                                */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE000025B : D5_ERROR_D5TSHM_SMCS_INIT              */
/*    0xE000025D : D5_ERROR_D5TSHM_SMCS_ACTIVE            */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmShutdown();

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        LOAD A D5TSHM TABLE (FOR ADMIN PROCESS)         */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmLoad                             */
/*        (const char* pchPath,const char* pchTableName); */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchPath: THE PATH TO THE DIRECTORY THAT         */
/*                 CONTAINS THE D5T FILE TO BE LOADED     */
/*        pchTableName: THE TABLE NAME TO BE LOADED       */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          EITHER pchPath OR pchTableName IS NULL.       */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_OUT_OF_MEMORY:                         */
/*           NO AVAILABLE MEMORY                          */
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SHMTBL_INIT:                    */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_D5TSHM_SHMTBL_STANDBY:                 */
/*          A D5TSHM TABLE WITH THE SAME NAME HAS BEEN    */
/*          ALREADY LOADED.                               */
/*          NUMBER OF ATTACHING PROCESSES IS ZERO.        */
/*        D5_ERROR_D5TSHM_SHMTBL_REFERENCED:              */
/*          A D5TSHM TABLE WITH THE SAME NAME HAS BEEN    */
/*          ALREADY LOADED.                               */
/*          NUMBER OF ATTACHING PROCESSES IS POSITIVE.    */
/*        D5_ERROR_FILE_IO: FILE I/O ERROR                */
/*        D5_ERROR_D5TSHM_TOO_MANY_D5TSHM_TABLES:         */
/*          nTables EXCEEDS THE UPPER LIMIT SPECIFIED     */
/*          BY RD5ShmSetup.                               */
/*        D5_ERROR_ILLEGAL_TABLE_NAME:                    */
/*          THE SPECIFIED TABLE NAME IS TOO LONG.         */
/*        D5_ERROR_FILE_PATH:                             */
/*          THE SPECIFIED PATH IS TOO LONG.               */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000018 : D5_ERROR_OUT_OF_MEMORY                 */ 
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE000025F : D5_ERROR_D5TSHM_SHMTBL_INIT            */
/*    0xE0000261 : D5_ERROR_D5TSHM_SHMTBL_STANDBY         */
/*    0xE0000262 : D5_ERROR_D5TSHM_SHMTBL_REFERENCED      */
/*    0xE000008D : D5_ERROR_FILE_IO                       */
/*    0xE000025E : D5_ERROR_D5TSHM_TOO_MANY_D5TSHM_TABLES */
/*    0xE0000035 : D5_ERROR_ILLEGAL_TABLE_NAME            */
/*    0xE000008E : D5_ERROR_FILE_PATH                     */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmLoad(const char* pchPath,
		    const char* pchTableName);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        LOAD ALL AVAILABLE D5TSHM TABLES IN A DIRECTORY */
/*        (FOR ADMIN PROCESS)                             */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmLoadAll                          */
/*        (const char* pchPath,                           */
/*         const char* pchSearchTableName);               */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchPath: THE PATH TO THE DIRECTORY THAT         */
/*                 CONTAINS THE D5T FILES TO BE LOADED    */
/*        pchSearchTableName: A WILDCARD PATTERN THAT     */
/*                            MATCHES THE TABLE NAMES TO  */
/*                            BE LOADED                   */
/* RETURN VALUE:                                          */
/*        <NON NEGATIVE>:                                 */
/*          THE NUMBER OF SUCCESSFULLY LOADED TABLES      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          EITHER pchPath OR pchSearchTableName IS NULL. */
/*        D5_ERROR_ILLEGAL_TABLE_NAME:                    */
/*          THE SPECIFIED TABLE NAME IS TOO LONG.         */
/*        D5_ERROR_D5TSHM_SEMAPHORE_REMOVED:              */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SHMTBL_INIT:                    */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_FILE_PATH:                             */
/*          THE SPECIFIED PATH IS TOO LONG.               */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000035 : D5_ERROR_ILLEGAL_TABLE_NAME            */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE000025F : D5_ERROR_D5TSHM_SHMTBL_INIT            */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE000008E : D5_ERROR_FILE_PATH                     */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmLoadAll(const char* pchPath,
		       const char* pchSearchTableName);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        RELEASE A D5TSHM TABLE. (FOR ADMIN PROCESS)     */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmRelease                          */
/*        (const char* pchTableName);                     */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchTableName: THE TABLE NAME TO BE RELEASED     */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          pchTableName IS NULL.                         */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_SEMAPHORE_REMOVED: SEMAPHORE IS        */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS   */
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_SHMTBL_INIT:                    */
/*          SETUP HASN'T BEEN DONE.                       */
/*        D5_ERROR_D5TSHM_SHMTBL_READY:                   */
/*          THE SPECIFIED TABLE HASN'T BEEN LOADED.       */
/*        D5_ERROR_FILE_IO:                               */
/*          FILE I/O ERROR                                */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE000025F : D5_ERROR_D5TSHM_SHMTBL_INIT            */
/*    0xE0000260 : D5_ERROR_D5TSHM_SHMTBL_READY           */
/*    0xE000008D : D5_ERROR_FILE_IO                       */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmRelease(const char* pchTableName);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        RELEASE ALL TABLES. (FOR ADMIN PROCESS)         */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmReleaseAll();                    */
/*                                                        */
/* ARGUMENTS:                                             */
/*        <NONE>                                          */
/*                                                        */
/* RETURN VALUE:                                          */
/*        <NON NEGATIVE>:                                 */
/*          THE NUMBER OF SUCCESSFULLY RELEASED TABLES    */
/*        D5_ERROR_D5TSHM_SEMAPHORE_REMOVED:              */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SHMTBL_INIT:                    */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE000025F : D5_ERROR_D5TSHM_SHMTBL_INIT            */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmReleaseAll();

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        GET THE LIST OF LOADED D5TSHM TABLES.           */
/*        (FOR ADMIN PROCESS)                             */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5GetSharedMemoryTableList            */
/*        (char* pchTableNameList,int* piTableCount);     */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchTableNameList: BUFFER TO STORE THE LIST OF   */
/*                          LOADED TABLES                 */
/*        piTableCount: INT BUFFER TO STORE THE NUMBER OF */
/*                      LOADED TABLES                     */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          EITHER pTableNameList OR pTableCount IS NULL. */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_D5TSHM_SMCS_INIT:                      */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE000025B : D5_ERROR_D5TSHM_SMCS_INIT              */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*    2005.11.30 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5GetSharedMemoryTableList(char* pchTableNameList,
				     int* piTableCount);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        GET THE LIST OF LOADED D5TSHM TABLES.           */
/*        (FOR ADMIN PROCESS)                             */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5GetSharedMemoryTableListEx          */
/*        (char* pchTableNameList,int* piTableCount);     */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchTableNameList: BUFFER TO STORE THE LIST OF   */
/*                          LOADED TABLES                 */
/*        piTableCount: INT BUFFER TO STORE THE NUMBER OF */
/*                      LOADED TABLES                     */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          EITHER pTableNameList OR pTableCount IS NULL. */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_D5TSHM_SMCS_INIT:                      */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE000025B : D5_ERROR_D5TSHM_SMCS_INIT              */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.30 CREATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5GetSharedMemoryTableListEx(char* pchTableNameList,
				       int* piTableCount);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*         ATTACH A D5TSHM TABLE. (FOR CLIENT PROCESS)    */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmAttach                           */
/*        (const char* pchTableName,int nWaitFlag);       */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchTableName: THE TABLE NAME TO BE ATTACHED     */
/*        nWaitFlag: THE WAIT POLICY                      */
/*                   (D5_SHMLOCK_WAIT OR                  */
/*                    D5_SHMLOCK_NOWAIT)                  */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_OUT_OF_MEMORY:                         */
/*          NO AVAILABLE MEMORY                           */
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SHMTBL_INIT:                    */
/*          SETUP HAS NOT BEEN DONE.                      */
/*        D5_ERROR_D5TSHM_SHMTBL_READY:                   */
/*          THE SPECIFIED TABLE HAS NOT BEEN LOADED.      */
/*        D5_ERROR_OVERFLOW_TABLE:                        */
/*          THE NUMBER OF TABLES EXCEEDS THE LIMIT NUMBER */
/*          OF TABLES THAT A PROCESS CAN HOLD.            */
/*        D5_ERROR_D5TSHM_DUPLICATE_TABLE:                */
/*          A TABLE OF THE SAME NAME ALREADY EXISTS IN    */ 
/*          THE WORKSPACE.                                */
/*        D5_ERROR_D5TSHM_RESOURCE_BUSY:                  */
/*          SOME ONE HAS BEEN ATTACHING THE TABLE, AND    */
/*          D5_SHMLOCK_NOWAIT IS SPECIFIED TO nWaitFlag.  */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          NEITHER D5_SHMLOCK_WAIT NOR D5_SHMLOCK_NOWAIT */
/*          IS SPECIFIED TO nWaitFlag, OR                 */
/*          pchTableName IS NULL.                         */
/*        D5_ERROR_D5TSHM_TOO_LARGE_D5T_FILE:             */
/*          THE TOTAL AMOUNT OF ATTACHED D5T FILES        */
/*          EXCEEDS THE CAPACITY OF AVAILABLE             */
/*          VIRTUAL MEMORY SPACE.                         */
/*        D5_ERROR_FILE_IO:                               */
/*          FILE I/O ERROR                                */
/*        D5_ERROR_INVALID_TABLE_TYPE:                    */
/*          D5T FILE TYPE MISMATCH                        */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*        D5_ERROR_ILLEGAL_TABLE_NAME:                    */
/*          THE SPECIFIED TABLE NAME IS TOO LONG.         */
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE0000018 : D5_ERROR_OUT_OF_MEMORY                 */ 
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE000025F : D5_ERROR_D5TSHM_SHMTBL_INIT            */
/*    0xE0000260 : D5_ERROR_D5TSHM_SHMTBL_READY           */
/*    0xE0000063 : D5_ERROR_OVERFLOW_TABLE                */
/*    0xE0000263 : D5_ERROR_D5TSHM_DUPLICATE_TABLE        */
/*    0xE000025A : D5_ERROR_D5TSHM_RESOURCE_BUSY          */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE0000266 : D5_ERROR_D5TSHM_TOO_LARGE_D5T_FILE     */
/*    0xE000008D : D5_ERROR_FILE_IO                       */
/*    0xE0000076 : D5_ERROR_INVALID_TABLE_TYPE            */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*    0xE0000035 : D5_ERROR_ILLEGAL_TABLE_NAME            */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmAttach(const char* pchTableName,int nWaitFlag);

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        DELETE ALL D5TSHM TABLES USED BY THIS PROCESS   */
/*        (FOR CLIENT PROCESS)                            */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5DetachAll();                        */
/*                                                        */
/* ARGUMENTS:                                             */
/*        <NONE>                                          */
/*                                                        */
/* RETURN VALUE:                                          */
/*        <NON NEGATIVE>:                                 */
/*          THE NUMBER OF SUCCESSFULLY DETACHED TABLES    */
/*        D5_ERROR_SEMAPHORE_REMOVED:                     */
/*          SEMAPHORE IS REMOVED WHILE CONTROLLING SMCS.  */
/*        D5_ERROR_D5TSHM_SIGNAL_CAUGHT:                  */
/*          SIGNAL WAS CAUGHT WHILE BEING WAITED BY semop.*/
/*        D5_ERROR_D5TSHM_INVALID_OS_PARAM:               */
/*          NEED TO MODIFY OS PARAMETER                   */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000258 : D5_ERROR_D5TSHM_SEMAPHORE_REMOVED      */
/*    0xE0000259 : D5_ERROR_D5TSHM_SIGNAL_CAUGHT          */
/*    0xE0000264 : D5_ERROR_D5TSHM_INVALID_OS_PARAM       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5DetachAll();

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        INITIALIZE THE D5TSHM ENVIRONMENT               */
/*        (FOR SPECIAL ADMIN PROCESS)                     */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ClearSharedMemory();                */
/*                                                        */
/* ARGUMENTS:                                             */
/*        <NONE>                                          */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_ACCESS_DENIED:                         */
/*          INSUFFICIENT ACCESS PERMISSION                */ 
/*        D5_ERROR_UNKNOWN:                               */
/*          UNKNOWN ERROR                                 */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000098 : D5_ERROR_ACCESS_DENIED                 */
/*    0xE00001F4 : D5_ERROR_UNKNOWN                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ClearSharedMemory();

/**********************************************************/
/*                                                        */
/* MODULE NAME:                                           */
/*        d5tshm.c                                        */
/*                                                        */
/* FUNCTION DESCRIPTION:                                  */
/*        DUMP THE CONTENTS OF CURRENT SMCS               */
/*                            (FOR SPECIAL ADMIN PROCESS) */
/*                                                        */
/* FUNCTION NAME:                                         */
/*        D5RESULT RD5ShmDumpSMCS                         */
/*	  (const char* pchPathDumpFile);                  */
/*                                                        */
/* ARGUMENTS:                                             */
/*        pchPathDumpFile: THE PATH TO THE DUMP FILE      */
/*                                                        */
/* RETURN VALUE:                                          */
/*        0: SUCCESS                                      */
/*        D5_ERROR_INVALID_PARAM:                         */
/*          pchPathDumpFile IS NULL.                      */
/*        D5_ERROR_FILE_IO: FILE I/O ERROR                */
/*                                                        */
/* ERROR CODE:                                            */
/*    0xE0000082 : D5_ERROR_INVALID_PARAM                 */
/*    0xE000008D : D5_ERROR_FILE_IO                       */
/*                                                        */
/* REFERENCED EXTERNAL VARIABLE:                          */
/*        TheLSMCS: THE SINGLETON INSTANCE OF LSMCS       */
/*                                                        */
/* LOCKS:                                                 */
/*        LOCK_SMCS (FOR EXCLUSIVE CONTROL OF SMCS)       */
/*                                                        */
/* UPDATE HISTORY:                                        */
/*    2005.11.16 CREATE K. SAITOH                         */
/*    2005.11.25 UPDATE K. SAITOH                         */
/*                                                        */
/**********************************************************/
D5RESULT D5APICALL RD5ShmDumpSMCS(const char* pchPathDumpFile);



/** Call this function inside the child process ***/
/** for creating child process using fork operation **/
D5RESULT D5APICALL RD5ReInitializeMS();

/**
 * 複数データを取得します。
 * @param[in]	TableID			テーブルID
 * @param[in]	FltID			項目ID
 * @param[in]	SetID			セットID
 * @param[in]	RowNo			セット内順序番号
 * @param[in]	RCount			取得レコード数
 * @param[in]	BufSize			文字列データエリアのサイズ
 * @param[out]	iDataType		取得したデータ型
 * @param[out]	nGot			取得したデータ数
 * @param[out]	pOutBuf			取得した文字列型以外のデータ または 文字列型データのacCharBuf内データ開始位置
 * @param[out]	charbuf			取得した文字列データ
 * @retval	0以上	整数・浮動小数点型：取得した行のうち、単一で最大のデータサイズ(byte) 文字列型：NULL終端を含まない最終行のデータサイズ(byte)
 * @retval	負		エラーコード
 * 
 */
D5RESULT D5APICALL RD5GetData1MEx(
            const int	TableID,						//  IN:テーブルＩＤ
            const int	FltID,							//  IN:FilterID
            const int	SetID,							//  IN:-1 ならカレントセット
            const int	RowNo,							//  IN:行番号（１から始まる）
			const int	RCount,							//  IN:取得レコード数
			const int	BufSize,						//	INT:文字列データエリアのサイズ
            int*		iDataType,						//  OUT:データのタイプ番号
			int*		nGot,							//	OUT:取得できたデータ数
			void*		pOutBuf,						//	OUT:データ(呼び出し側で領域確保) 文字列の時は、charbuf内での開始位置
			char*		charbuf							//  OUT:文字列データ(呼び出し側で領域確保)
          );		 //  OUT:負の時、エラー

/**
 * 計算処理を行います。
 * @param[in]	nTableID	計算を行うテーブルID
 * @param[in]	nSetID		計算を行うセットID
 * @param[in]	nCalStart	計算開始位置
 * @param[in]	nCalCount	計算するレコード数
 * @param[in]	szFormula	計算式
 * @param[in]	iResultDataType	 計算結果データのタイプ
 * @param[out]	pvOutput		計算結果を出力する配列領域
 * @param[in]	iStrAreaSize	pcStrArea領域のサイズ（バイト単位）
 * @param[out]	pcStrArea	計算結果文字列を格納する領域
 * @param[out]	szErrorRep	エラー説明
 * @retval	0	成功
 * @retval	負	エラーコード
 * 
 *　計算結果を配列もらいます
 * ErrorRepは無効なので空文字列を指定してください。
 */
D5RESULT D5APICALL RD5CalcPtr (
        const int   TablelID,
        const int   SetID,
        const int   CalStart,
        const int   CalCount,
        const char  PCFormula[D5_MAX_STRING_SIZE],
        const int	iResultDataType,		//計算結果データのタイプ	int=3,・・・
        void*   pvOutput,					//計算結果を出力する配列領域
        size_t   iStrAreaSize,				//pcStrArea領域のサイズ（バイト単位）
        char *   pcStrArea,					//計算結果文字列を格納する領域
        char       ErrorRep[D5_MAX_STRING_SIZE]
        );

/**
* REALテーブルをメモリに格納します。
* @param[in]	nTableID	格納したいテーブルのID
* @param[in]	pMemPtr	　　格納するメモリのポインタ
* @param[in]	szMemSize　 使用可能メモリサイズ
* @param[out]	pEndMemPtr	終了位置へのポインタ。 
* @retval	0	成功
* @retval	負	エラーコード
* 
*/
D5RESULT D5APICALL RD5SaveRealTable2Mem(
										const int    nTableID, 
										const void*  pMemPtr, 
										const size_t szMemSize,
										 void** pEndMemPtr
										);
/**
* ワークスペースをメモリに格納します。
* @param[in]	pMemPtr	　　格納するメモリのポインタ
* @param[in]	szMemSize　 使用可能メモリサイズ
* @param[out]	pEndMemPtr	終了位置へのポインタ。 
* @retval	0	成功
* @retval	負	エラーコード
* 
*/
D5RESULT D5APICALL RD5SaveDB2Mem(
								 const  void*	pMemPtr, 
								 const size_t	szMemSize,
								 void**	pEndMemPtr
								 );


/**
* REALテーブルを指定されたメモリからロードします。
* @param[in]	pMemPtr	　　テーブルが格納しているメモリのポインタ
* @param[out]	pEndMemPtr	終了位置へのポインタ。 
* @retval	ロードされたテーブルＩＤ
* @retval	負	エラーコード
* 
*/
D5RESULT D5APICALL RD5LoadRealTableFromMem(
											const void* pMemPtr,
											void** pEndMemPtr
											);

/**
* ワークスペースを指定されたメモリからロードします。
* @param[in]	pMemPtr	　　ワークスペースが格納しているメモリのポインタ
* @param[out]	pEndMemPtr	終了位置へのポインタ。 
* @retval	0	成功
* @retval	負	エラーコード
* 
*/
D5RESULT D5APICALL RD5LoadDBFromMem(
									const void* pMemPtr,
									void** pEndMemPtr
									);



/**
* テーブルのSetID作成を設定するsetＩＤから始める。
* @param[in]	　nTableID	格納したいテーブルのID
* @param[in]	　nNewSetID	始めるＳｅｔＩＤ番号
* @retval	0 　成功
* @retval	負	エラーコード
* 
*/
D5RESULT D5APICALL RD5ResetSetID(const int nTableID,
								 const int nNewSetID
								 );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_RD5API_H
