/** @file
 * LFM�e�[�u��API
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

/** ���ڏ�� */
typedef struct _TRFilterInfo {
	int		PVSize;			/**< �ʒu���̃T�C�Y */
	int		VLType;			/**< �l���X�g�̃f�[�^�^�𐮐����������� */
	int		VLWidth;		/**< �l���X�g�̊e�l�̕� */
	int		VLSize;			/**< �l���X�g�̃T�C�Y�i���j */
	int		CharAreaSize;	/**< �l���X�g��������̏ꍇ�A������i�[�̈�̃T�C�Y */
	char	FilterName[D5_MAX_NAME_LENGTH + 8];	/**< ���ږ��� */
} TRFilterInfo;

/** ��������� */
typedef struct _TRMemInfo {
	INT64  TotalPhys;	/**< �g�[�^���������T�C�Y */
	INT64  AvailPhys;	/**< �g�p�\�������T�C�Y */
} TRMemInfo;

#define D5_MAX_STRING_LENGTH_CHAR_CODE 32

/** �T�[�o����� */
typedef struct _TREnvironment {
	char HostName[D5_MAX_STRING_LENGTH_OS];	/**< �R���s���[�^���� */
	int  OSType;						/**< OS�^�C�v */
	int  OSMajorVersion;				/**< OS�̃��W���[�E�o�[�W�����ԍ� */
	int  OSMinorVersion;				/**< OS�̃}�C�i�[�E�o�[�W�����ԍ� */
	int  MachineArchitecture;			/**< �V�X�e���̃v���Z�b�T��A�[�L�e�N�`�� */
	int  Endian;						/**< �V�X�e���̃G���f�B�A���E�^�C�v */
	int  ELF;							/**< LFM�G���W���̃r�b�g�� */
	int  ProcessorCount;				/**< �V�X�e���̃v���Z�b�T�� */
	int  ProcessType;					/**< ���g�p */
	char OSCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< OS�̊����R�[�h */
	char DBCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< DB�����R�[�h */
} TREnvironment;

/** D5�t�@�C����� */
typedef struct _D5FileInfo {
	unsigned char	OSType;										/**< D5D�t�@�C�����쐬����OS�^�C�v */
	unsigned char	Endian;										/**< D5D�t�@�C�����쐬�����V�X�e���̃G���f�B�A���E�^�C�v */
	unsigned char	ELF;										/**< D5D�t�@�C�����쐬�����ۂ�LFM�G���W���̃r�b�g�� */
	char			DBCharCode[D5_MAX_STRING_LENGTH_CHAR_CODE];	/**< D5D�t�@�C����DB�����R�[�h */
	int				Version[D5_VERSION_SIZE];					/**< D5D�t�@�C���̃o�[�W���� */
} D5FileInfo;

/** ���C�Z���X��� */
typedef struct _TLicenseData {
	char	LicenseMacAddr[D5_MAX_NAME_LENGTH];		/**< MAC�A�h���X */
	INT64	MaxRow;									/**< �ő�s���i�P�ʁF��s�j */
	INT64	MaxMemory;								/**< �ő僁�����ʁi�P�ʁFMB�j */
	int		CpuNum;									/**< ���C�Z���X��CPU�� */
	int		UserNum;								/**< �}���`���[�U�� */
	char	ExpirationDate[D5_LICENSE_DATE_SIZE];	/**< �L�������iYYYYMMDD�j */
} TLicenseData;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * �o�[�W��������A�R�s�[���C�g���b�Z�[�W���擾���܂��B
 * @param[out]	anVersion	�o�[�W�����z��
 * @param[out]	szCopyright	�R�s�[���C�g���b�Z�[�W
 * @retval	0	���0
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetVersionR1},{@link #RD5GetCopyRightR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetVersion(
		 int  anVersion[D5_VERSION_SIZE],
		 char szCopyright[D5_VERSION_STRING_SIZE]
		  );

/**
 * ���[�N�X�y�[�X���N���A���܂��B
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT  D5APICALL  RD5ClearDB();

/**
 * �w�肳�ꂽ�p�X����уt�@�C�����̂́A���[�N�X�y�[�X��ǂݍ��݂܂��B
 * @param[in]	szDBPath	D5D�t�@�C���̑��݂���p�X
 * @param[in]	szDBName	D5D�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5LoadDB(
		 const char szDBPath[D5_MAX_PATH],
		 const char szDBName[D5_MAX_PATH]
	   );

/**
 * �w�肳�ꂽ�p�X�Ɏw�肳�ꂽ�t�@�C�����̂ŁA���[�N�X�y�[�X��D5D�t�@�C���Ƃ��ď����o���܂��B
 * @param[in]	szDBPath	D5D�t�@�C���������o���p�X
 * @param[in]	szDBName	D5D�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SaveDBAs(
		 const char szDBPath[D5_MAX_PATH],
		 const char szDBName[D5_MAX_PATH]
		 );

/**
 * �J���}��؂�t�@�C���փf�[�^���G�N�X�|�[�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	anFilterIDList	����ID���X�g
 * @param[in]	nRowFrom		�o�͂��J�n����s
 * @param[in]	nRowTo			�o�͂̏I���s
 * @param[in]	nDateSep		���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szDBPath		�o�̓t�@�C���ւ̃p�X
 * @param[in]	szDBName		�o�̓t�@�C������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * TAB��؂�t�@�C���փf�[�^���G�N�X�|�[�g���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID	�Z�b�gID
 * @param[in]	anFilterIDList	����ID���X�g
 * @param[in]	nRowFrom	�o�͂��J�n����s
 * @param[in]	nRowTo	�o�͂̏I���s
 * @param[in]	nDateSep	���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szDBPath	�o�̓t�@�C���ւ̃p�X
 * @param[in]	szDBName	�o�̓t�@�C������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �e�[�u���̃f�[�^���J�^���O��`�t�@�C���փG�N�X�|�[�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	anFilterIDList	�o�͂��鍀��ID���X�g
 * @param[in]	nFileType		�o�͂���t�@�C���^�C�v
 * @param[in]	nRowFrom		�o�͂���s�̊J�n�ʒu
 * @param[in]	nRowTo			�o�͂���s�̏I���ʒu
 * @param[in]	nDateSep		���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szCatalogPath	�J�^���O��`�t�@�C�����o�͂���p�X
 * @param[in]	szCatalogName	�J�^���O��`�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �e�[�u���̃f�[�^���J�^���O��`�t�@�C���փG�N�X�|�[�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	anFilterIDList	�o�͂��鍀��ID���X�g
 * @param[in]	nFileType		�o�͂���t�@�C���^�C�v
 * @param[in]	nRowFrom		�o�͂���s�̊J�n�ʒu
 * @param[in]	nRowTo			�o�͂���s�̏I���ʒu
 * @param[in]	nDateSep		���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szCatalogPath	�\����`�t�@�C�����o�͂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
 * @param[in]	szSourcePath	���n�f�[�^�t�@�C���̑��݂���p�X
 * @param[in]	szSourceName	���n�f�[�^�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * ���[�N�X�y�[�X���㏑���ۑ����܂��B
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SaveDB();

/**
 * ���[�N�X�y�[�X�̃p�X�Ɩ��̂��擾���܂��B
 * @param[in]	szDBPath	D5D�t�@�C���̃p�X
 * @param[in]	szDBName	D5D�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetDBPathR1},{@link #RD5GetDBNameR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetPathName(
		 char szDBPath[D5_MAX_PATH],
		 char szDBName[D5_MAX_PATH]
		 );

/**
 * ���݂���e�[�u�������擾���܂��B
 * @retval	0�ȏ�	�e�[�u����
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetNTable();

/**
 * �e�[�u��ID�̈ꗗ���擾���܂��B
 * @param[out]	anTableIDList	�e�[�u��ID�̈ꗗ
 * @retval	0�ȏ�	�e�[�u����
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anTableIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetTableIDList(
			int anTableIDList[D5_MAX_TABLE_COUNT]
		  );

/**
 * �o�^�\�ȃe�[�u�����̂𐶐����܂��B
 * @param[in]	szSeedName	���������e�[�u�����̂̌��ƂȂ镶����
 * @param[out]	szGenName	�������ꂽ�o�^�\�ȃe�[�u������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GenerateTableNameR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GenerateTableName(
		 const char   szSeedName[D5_MAX_NAME_LENGTH],
		 char szGenName[D5_MAX_NAME_LENGTH]
		  );

/**
 * REAL�e�[�u�������[�h���܂��B
 * @param[in]	szTablePath		D5T�t�@�C���̑��݂���p�X
 * @param[in]	szTableName		�e�[�u������
 * @retval	1�ȏ�	���[�h���ꂽ�e�[�u����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5LoadRealTable(
		 const char   szTablePath[D5_MAX_PATH],
		 const char   szTableName[D5_MAX_PATH]
		 );

/**
 * REAL�e�[�u����V�K�쐬���܂��B
 * @param[in]	szTableName	�쐬����e�[�u������
 * @param[in]	nRowCount	�s��
 * @retval	1�ȏ�	�V�K�ɍ쐬���ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5AddRealTable(
		  const char szTableName[D5_MAX_NAME_LENGTH],
		  const int  nRowCount
		 );

/**
 * REAL�e�[�u����ۑ����܂��B
 * @param[in]	szTablePath	REAL�e�[�u����ۑ�����p�X
 * @param[in]	nTableID	�ۑ��������e�[�u����ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * JOIN�e�[�u�����쐬���܂��B
 * @param[in]	szTableName			�V�K�ɍ쐬����JOIN�e�[�u������
 * @param[in]	nIsOuter			�e�[�u���敪
 * @param[in]	nMasterTableID		�}�X�^�e�[�u��ID
 * @param[in]	nMasterSetID		�}�X�^�e�[�u���̃Z�b�gID
 * @param[in]	anMasterFilterIDs	JOIN�L�[�ƂȂ�}�X�^�e�[�u���̍���ID���X�g
 * @param[in]	nSlaveTableID		�X���[�u�e�[�u��ID
 * @param[in]	nSlaveSetID			�X���[�u�e�[�u���̃Z�b�gID
 * @param[in]	anSlaveFilterIDs	JOIN�L�[�ƂȂ�X���[�u�e�[�u���̍���ID���X�g
 * @retval	1�ȏ�	�쐬���ꂽJOIN�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anMasterFilterIDs,anSlaveFilterIDs�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * JOIN IN/OUT�Z�b�g�𐶐����܂��B
 * @param[in]	nDestTableID	JOIN IN/OUT�Z�b�g�����̃^�[�Q�b�g�̃e�[�u��ID
 * @param[in]	nDestSetID		JOIN IN/OUT�Z�b�g���Z�o����^�[�Q�b�g�̃Z�b�gID
 * @param[in]	nDestFilterID	JOIN IN/OUT�Z�b�g���Z�o����^�[�Q�b�g�̍���ID
 * @param[in]	nSrcTableID		JOIN IN/OUT�Z�b�g�̎Z�o���ɂȂ�[�u��ID
 * @param[in]	nSrcSetID		JOIN IN/OUT�Z�b�g�̎Z�o���ɂȂ�̃Z�b�gID
 * @param[in]	nSrcFilterID	JOIN IN/OUT�Z�b�g�̎Z�o���ɂȂ鍀��ID
 * @param[in]	nIsJoinIn		IN/OUT���w�肷��
 * @retval	0�ȏ�	�������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * JOIN�e�[�u����REAL�e�[�u���ɕϊ����܂��B
 * @param[in]	szTableName		�V�K�ɍ쐬����REAL�e�[�u������
 * @param[in]	nJoinTableID	JOIN�e�[�u��ID
 * @param[in]	nJoinSetID		JOIN�e�[�u���̃Z�b�gID
 * @param[in]	nIncludeRowNoM	�}�X�^���s�ԍ��̍��ډ��̐ݒ�
 * @param[in]	nIncludeRowNoS	�X���[�u���s�ԍ��̍��ډ��̐ݒ�
 * @param[in]	anFilterIDList	REAL�e�[�u���̍��ڂɕϊ����鍀��ID���X�g
 * @param[in]	nVLIsLinked		���0���w��
 * @retval	1�ȏ�	�쐬���ꂽREAL�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * JOIN�`�F�[�������̉����܂��B
 * @param[in]	szTableName		�V�K�e�[�u������
 * @param[in]	anJoinTableIDs	�`�F�[������e�[�u��ID���X�g
 * @param[out]	anRealTableIDs	�`�F�[�����ꂽ�e�[�u��ID���X�g
 * @param[out]	aanRealSetIDs	�`�F�[�����ꂽREAL�e�[�u��ID���X�g
 * @retval	1�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT  D5APICALL RD5RealizeJoinChain(
			const char  szTableName[D5_MAX_NAME_LENGTH],
			const int   anJoinTableIDs[D5_MAX_JOIN_CHAIN],
			int   anRealTableIDs[D5_MAX_JOIN_CHAIN + 1],
			int   aanRealSetIDs[J_SLAVE + 1][D5_MAX_JOIN_CHAIN]
	   );

/**
 * JOIN�`�F�[�������̉����A�������ꂽ�c���[�e�[�u���Ɍ��e�[�u���̐������ڂ�ǉ����܂��B
 * @param[in]	szTableName			�V�K�e�[�u������
 * @param[in]	anJoinTableIDs		�`�F�[������e�[�u��ID���X�g
 * @param[in]	nAssociation		�o�͂Ɋ܂߂�eREAL�e�[�u���̍���ID��
 * @param[in]	aanRealFilterIDs		�o�͂���eREAL�e�[�u���̍���ID���X�g
 * @param[out]	anRealTableIDs		�`�F�[�����ꂽ�e�[�u��ID���X�g
 * @param[out]	aanRealSetIDs		�`�F�[�����ꂽREAL�e�[�u��ID���X�g
 * @retval	1�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * ���̉����ꂽJOIN�`�F�[���Ƀ\�[�X����t�����܂��B
 * @param[in]	nTableID		�c���[�e�[�u����ID
 * @param[in]	nDepth			�^�[�Q�b�g�Ƃ���[��
 * @param[in]	nSrcTableID		�t�������񌳂̃e�[�u��ID
 * @param[in]	anSrcFilterIDs	�t�������񌳂̍���ID���X�g
 * @param[in]	nFillAncestor	���[�g�̏ꍇ�ɒl���[�����邩�ǂ������w��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT  D5APICALL RD5QualifyTree(
			const int	nTableID,
			const int	nDepth,
			const int	nSrcTableID,
			const int	anSrcFilterIDs[D5_MAX_TREE_QUALIFY],
			const int	nFillAncestor
			);

/**
 * JOIN�`�F�C���ő�l��ݒ肵�܂��B
 * @param[in]	nMaxJoinChain	�ő�K�w��(16�`510)
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT  D5APICALL RD5SetMaxJoinChain (
			const int	nMaxJoinChain
							 );

/**
 * �e�[�u�����폜���܂��B
 * @param[in]	nTableID	�폜����e�[�u��ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DeleteTable(
			const int nTableID
		   );

/**
 * �e�[�u�����̂��擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[out]	szTableName	�e�[�u������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetTableNameR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetTableName(
			const int nTableID,
			char szTableName[D5_MAX_NAME_LENGTH]
		   );

/**
 * �e�[�u���̏����擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[out]	pTableInfo	�e�[�u�����̃A�h���X
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * JOIN�e�[�u���̏����擾���܂��B
 * @param[in]	nTableID			�����擾����JOIN�e�[�u��ID
 * @param[out]	szTableName			�e�[�u������
 * @param[out]	pnIsOuter			JOIN�e�[�u���̎��
 * @param[out]	pnJoinKeyCount		JOIN�L�[�̐�
 * @param[out]	pnMasterTableID		�}�X�^�e�[�u��ID
 * @param[out]	pnMasterSetID		�}�X�^�e�[�u���Z�b�gID
 * @param[out]	anMasterFilterIDs	�}�X�^�e�[�u����JOIN�L�[�̈ꗗ
 * @param[out]	pnSlaveTableID		�X���[�u�e�[�u��ID
 * @param[out]	pnSlaveSetID		�X���[�u�e�[�u���Z�b�gID
 * @param[out]	anSlaveFilterIDs	�X���[�u�e�[�u����JOIN�L�[�̈ꗗ
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetJoinInfoExR1}���g�p���Ă��������B
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
 * JOIN�����擾���܂��B
 * @param[in]	nTableID		�w��̃e�[�u���̃e�[�u��ID
 * @param[out]	anJoinFilterIDs		�w��̃e�[�u���̃t�B���^ID���X�g
 * @param[out]	anSrcTableIDs	�w��̃e�[�u���̌��e�[�u��ID���X�g
 * @param[out]	anSrcFilterIDs	�w��̃e�[�u���̌��t�B���^ID���X�g
 * @retval	0�ȏ�	���ڐ��̍��v
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anJoinFilterIDs,anSrcTableIDs,anSrcFilterIDs�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetJoinSrcTblIDs(
		 const int nTableID,
		 int anJoinFilterIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int anSrcTableIDs[D5_MAX_FILTER_COUNT_JOIN],
		 int anSrcFilterIDs[D5_MAX_FILTER_COUNT_JOIN]
			);

/**
 * JOIN�e�[�u���̏����擾���܂��B
 * @param[in]	nTableID		�w��̃e�[�u���̃e�[�u��ID
 * @param[out]	pnNMasterFilter	�}�X�^���t�B���^�ɗR������t�B���^�̐�
 * @param[out]	pnNSlaveFilter	�X���C�u���e�[�u���ɗR������t�B���^�̐�
 * @param[out]	anJoinFilterIDs	�w��̃e�[�u���̃t�B���^ID[1..N]
 * @param[out]	anSrcTableIDs	�w��̃e�[�u���̃}�X�^�[�e�[�u��ID[Nm, Nm, ... Nm, Ns, Ns, ... Ns]
 * @param[out]	anSrcFilterIDs	�w��̃e�[�u���̃}�X�^�[�W��ID[FIDm1, FIDm2, ..., FIDs1, FIDs2, ...]
 * @retval	0�ȏ�	�擾�����t�B���^�̐�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnNMasterFilter,pnNSlaveFilter,anJoinFilterIDs,anSrcTableIDs,anSrcFilterIDs�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * REAL�e�[�u���𕡐����܂��B
 * @param[in]	szTableName		�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nTableID		�������̃e�[�u��ID
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT  D5APICALL RD5DuplicateRealTable(
		const char szTableName[D5_MAX_NAME_LENGTH],
		const int  nTableID
		);

/**
 * REAL�e�[�u���𒊏o���܂��B
 * @param[in]	szTableName				�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nTableID				���o���̃e�[�u��ID
 * @param[in]	nSetID					���o����Z�b�gID
 * @param[in]	anExtractFilterIDList	���o���鍀��ID���X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anExtractFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT  D5APICALL RD5ExtractRealTable(
		 const char  szTableName[D5_MAX_NAME_LENGTH],
		 const int   nTableID,
		 const int   nSetID,
		 const int   anExtractFilterIDList[D5_MAX_FILTER_COUNT_REAL]
		   );

/**
 * REAL�e�[�u���𒊏o���܂��B
 * @param[in]	szTableName				�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nTableID				���o���̃e�[�u��ID
 * @param[in]	nSetID					���o����Z�b�gID
 * @param[in]	nIncludeTableID			���o���e�[�u��ID�̍��ډ��ݒ�l
 * @param[in]	nIncludeRecNo			���o�����R�[�h�ԍ��̍��ډ��ݒ�l
 * @param[in]	anExtractFilterIDList	���o���鍀��ID���X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anExtractFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * REAL�e�[�u�����c�������܂��B
 * @param[in]	szTableName		�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nTableID1		��������1�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID1			��������1�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs1	��������1�Ԗڂ̍��ڃ��X�g
 * @param[in]	nTableID2		��������2�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID2			��������2�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs2	��������2�Ԗڂ̍��ڃ��X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDs1,anFilterIDs2�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * REAL�e�[�u�����c�������܂��B
 * @param[in]	szTableName		�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nIncludeTableID	���o���̃e�[�u��ID�̍��ډ��ݒ�l
 * @param[in]	nIncludeRecNo	���o���̃��R�[�h�ԍ��̍��ډ��ݒ�l
 * @param[in]	nTableID1		��������1�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID1			��������1�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs1	��������1�Ԗڂ̍��ڃ��X�g
 * @param[in]	nTableID2		��������2�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID2			��������2�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs2	��������2�Ԗڂ̍��ڃ��X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDs1,anFilterIDs2�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * REAL�e�[�u�����c�������܂��B
 * @param[in]	szTableName		�V�K�ɐݒ肷��e�[�u������
 * @param[in]	nIncludeTableID	���o���̃e�[�u��ID�̍��ډ��ݒ�l
 * @param[in]	nIncludeRecNo	���o���̃��R�[�h�ԍ��̍��ډ��ݒ�l
 * @param[in]	nTableID1		��������1�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID1			��������1�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs1	��������1�Ԗڂ̍��ڂ̃��X�g
 * @param[in]	nTableID2		��������2�Ԗڂ̃e�[�u��ID
 * @param[in]	nSetID2			��������2�Ԗڂ̃Z�b�gID
 * @param[in]	anFilterIDs2	��������2�Ԗڂ̍��ڂ̃��X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDs1,anFilterIDs2�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * ������REAL�e�[�u���̐������ڂ��������܂��B
 * @param[in]	szTableName			�V�K�ɐݒ肷��e�[�u������
 * @param[in]	anTableIDList		��������e�[�u��ID���X�g
 * @param[in]	anSetIDList			��������Z�b�gID���X�g
 * @param[in]	anIntFilterList0	�V�e�[�u����1�Ԗڂ̍��ڂɐݒ肷�鍀��ID���X�g
 * @param[in]	anIntFilterList1	�V�e�[�u����2�Ԗڂ̍��ڂɐݒ肷�鍀��ID���X�g
 * @param[in]	anIntFilterList2	�V�e�[�u����3�Ԗڂ̍��ڂɐݒ肷�鍀��ID���X�g
 * @param[in]	anIntFilterList3	�V�e�[�u����4�Ԗڂ̍��ڂɐݒ肷�鍀��ID���X�g
 * @retval	0�ȏ�	�������ꂽ�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anTableIDList,anSetIDList,anIntFilterList0,anIntFilterList1,anIntFilterList2,anIntFilterList3�́A
 * lfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * REAL�e�[�u�������k���܂��B
 * @param[in]	nTableID	���k����e�[�u��ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �w�肵���e�[�u���ɑ�����Z�b�g�����擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	1�ȏ�	�Z�b�g�̐�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetNSet(
			const int nTableID
		  );

/**
 * ���[�g�Z�b�g�̌������擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0�ȏ�	���[�g�Z�b�g�̃T�C�Y
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetTotalRows(
			const int nTableID
		  );

/**
 * ���[�g�Z�b�g�ȊO�̃Z�b�g���폜���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5PurgeSubsets(
			const int nTableID
		  );

/**
 * �Z�b�gID���w�肵�A�Z�b�g�T�C�Y���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @retval	0�ȏ�	�Z�b�g�̃T�C�Y
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetSetSize(
			const int nTableID,
			const int nSetID
		  );

/**
 * �w�肵��ID�̃Z�b�g���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[out]	pnSetSize	�Z�b�g�̍s��
 * @param[in]	nGetCount	�Z�b�g�z��ipnSetArray�j�̃T�C�Y
 * @param[out]	pnSetArray	�Z�b�g�z��
 * @retval	0�ȏ�	�Z�b�g�̃T�C�Y
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5GetSet(
            const int	nTableID,
            const int	nSetID,
            int			*pnSetSize,
            const int	nGetCount,
            int			*pnSetArray
          );

/**
 * �w�肵��ID�̃X���[�u�Z�b�g���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[out]	pnSetSize	�Z�b�g�̍s��
 * @param[in]	nGetCount	�Z�b�g�z��ipnSetArray�j�̃T�C�Y
 * @param[out]	pnSetArray	�Z�b�g�z��
 * @retval	0�ȏ�	�Z�b�g�̃T�C�Y
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5GetJoinSlaveSet(
            const int	nTableID,
            const int	nSetID,
            int			*pnSetSize,
            const int	nGetCount,
            int			*pnSetArray
          );

/**
 * �w�肵���Z�b�g��JOIN�̕������擾���܂��B
 * @param[in] nTableID	�e�[�u��ID
 * @param[in] nSetID	�Z�b�gID
 * @retval	0	�����E
 * @retval	1	�E����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetJoinDir(
			const int nTableID,
			const int nSetID
		  );

/**
 * �w�肳�ꂽJOIN�e�[�u���̗݌v���z����擾���܂��B
 * @param[in]		nTableID			�e�[�u��ID
 * @param[in]		nSetID				�Z�b�gID
 * @param[out]		pnMasterSize		�}�X�^���݌v���z��̃T�C�Y
 * @param[in]		nMasterGetCount		�}�X�^���擾�T�C�Y
 * @param[in,out]	pnMasterSetArray	�擾�����}�X�^���݌v���z��
 * @param[out]		pnSlaveSize			�X���[�u���݌v���z��̃T�C�Y
 * @param[in]		nSlaveGetCount		�X���[�u���擾�T�C�Y
 * @param[in,out]	pnSlaveSetArray		�擾�����X���[�u���݌v���z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnMasterSize,pnMasterSetArray,pnSlaveSize,pnSlaveSetArray�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �Z�b�gID�̈ꗗ���擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[out]	anSetIDList		�Z�b�gID���X�g
 * @retval	0�ȏ�	�Z�b�gID�̌�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anSetIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetSetList(
				const int nTableID,
				int anSetIDList[D5_MAX_SET_COUNT]
		  );

/**
 * �w�肳�ꂽ�e�[�u���̃Z�b�g�̂����w�肳�ꂽ���̃Z�b�g���擾���܂��B�i�Z�b�g�ԍ��̏����Ɏ��o���܂��B�j
 * @param[in]	nTableID	�Z�b�g���擾�������e�[�u���̃e�[�u��ID
 * @param[in]	nSize		�󂯎��Z�b�g�̌�
 * @param[out]	anSetIDList	�Z�b�g���󂯎��z��ւ̃|�C���^
 * @retval	0�ȏ�	�Z�b�g�̌�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anSetIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetSetIDList(
				const int nTableID,
				int nSize,
				int *anSetIDList
		  );

/**
 * �Z�b�g��ǉ����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetSize	�ǉ�����Z�b�g�̌�
 * @param[in]	pnSetArray	�ǉ�����Z�b�g���X�g
 * @retval	1�ȏ�	�ǉ������Z�b�g�̃Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5AddSetReal(
            const int	nTableID,
            const int	nSetSize,
            const int	*pnSetArray
          );

/**
 * �Z�b�g���폜���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DeleteSet(
			const int nTableID,
			const int nSetID
		  );

/**
 * �J�����g�̃Z�b�gID���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0�ȏ�	�J�����g�Z�b�g��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetCurrentSetID(
			const int nTableID
		  );

/**
 * �J�����g�Z�b�g��ݒ肵�܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�J�����g�Z�b�g�ɐݒ肷��Z�b�gID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5ChangeCurrentSetID(
			const int nTableID,
			const int nSetID
		  );

/**
 * �w�肵���T�u�Z�b�g�ȊO�̃��R�[�h����Ȃ�T�u�Z�b�g���쐬���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		��W�����쐬�������Z�b�gID
 * @retval	0�ȏ�	�쐬���ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL  RD5SetNotReal(
			const int nTableID,
			const int nSetID
		  );

/**
 * �Z�b�g�̋��ʏW���^�a�W���^���W�����쐬���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nOpeNo		�쐬�������Z�b�g�̎��
 * @param[in]	nSetAID		1�ԖڂɎw�肷��Z�b�gID�iA�j
 * @param[in]	nSetBID		2�Ԗڂɐݒ肷��Z�b�gID�iB�j
 * @retval	0�ȏ�	�쐬���ꂽ�W����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetOpeReal(
			const int nTableID,
			const int nOpeNo,
			const int nSetAID,
			const int nSetBID
		  );

/**
 * ���j�[�N�s�𒊏o���܂��B
 * @param[in]	nJBAHandle				���0
 * @param[in]	nTableID				�e�[�u��ID
 * @param[in]	nSetID					�Z�b�gID
 * @param[in]	anFilterIDs				����ID���X�g
 * @param[in]	nConserveOriginalOrder	True �܂��� False
 * @retval	1�ȏ�	�������ꂽ�Z�b�g��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDs�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL  RD5ExtractUniqueReal(
			const int		nJBAHandle,
			const int		nTableID,
			const int		nSetID,
			const int		anFilterIDs[D5_MAX_FILTER_COUNT_REAL],
			const int		nConserveOriginalOrder
			);

/**
 * JOIN�Ƀ}�b�`�����s�A�}�b�`���Ȃ������s���Z�b�g�Ƃ��Đ������܂��B
 * @param[in]	nJoinTableID		JOIN�e�[�u��ID
 * @param[in]	nPutSlave			�Z�b�g�𐶐�����e�[�u�����w��
 * @param[in]	nPutJoinOut			��������Z�b�g�̎�ނ��w��
 * @param[out]	pnTargetTableID		�Z�b�g���ǉ����ꂽ�e�[�u��ID
 * @param[out]	pnTargetSetID		�������ꂽ�Z�b�gID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnTargetTableID,pnTargetSetID�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL  RD5PutJoinSetToParent(
		 const int	nJoinTableID,
		 const int	nPutSlave,
		 const int	nPutJoinOut,
		 int	*pnTargetTableID,
		 int	*pnTargetSetID
	   );

/**
 * JOIN�Ƀ}�b�`�����X���[�u���̍s�̃Z�b�g�𐶐����܂��B
 * @param[in]	nJoinTableID		JOIN�e�[�u��IDJOIN���X���[�u�e�[�u��ID
 * @param[in]	pnTargetTableID		JOIN���X���[�u�e�[�u��ID
 * @retval	1�ȏ�	�������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnTargetTableID�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5ReturnSet2SlaveTable(
		 const int	nJoinTableID,
		 int	*pnTargetTableID
	   );

/**
 * ���ڂ̌����擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0�ȏ�	���ڂ̌�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetNFilter(
			const int nTableID
		  );

/**
 * ����ID�̈ꗗ���擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[out]	anFilterIDList	����ID���X�g
 * @retval	4byte	���ڂ̃f�[�^�^������
 * @retval	8byte	���ڂ̃f�[�^�^�����������_or���tor����or���t����
 * @retval	�ő咷�̕����񂩂�\0��������byte��	���ڂ̃f�[�^�^��������
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anFilterIDList�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetFilterIDList(
			const int nTableID,
			int anFilterIDList[D5_MAX_FILTER_COUNT_JOIN]
		  );

/**
 * ���ڂ̕����擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	0�ȏ�	���ڂ̕�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetFilterWidth(
			const int nTableID,
			const int nFilterID
		  );

/**
 * ���ڂ̃f�[�^�^���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	2�`7	5-1. �萔��`���Q��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetFilterType(
			const int nTableID,
			const int nFilterID
		  );

/**
 * ���ڂ̏����擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[out]	pFilterInfo	���ڏ��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * ���ڂ̃A�g���r���[�g�̈���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[out]	acAttrs		�A�g���r���[�g�z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����Alfmutil��{@link CFilterAttr}���g�p���Ă��������B
 */
D5RESULT	D5APICALL RD5GetFilterAttr(
		 const int	nTableID,
		 const int	nFilterID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * �Z�b�g�̃A�g���r���[�g�̈���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[out]	acAttrs		�A�g���r���[�g�z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����Alfmutil��{@link CSubsetAttr}���g�p���Ă��������B
 */
D5RESULT	D5APICALL RD5GetSubsetAttr(
		 const int	nTableID,
		 const int	nSetID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * ���ڂ̃A�g���r���[�g�̈�Ƀf�[�^���i�[���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	acAttrs		�A�g���r���[�g�z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����Alfmutil��{@link CFilterAttr}���g�p���Ă��������B
 */
D5RESULT	D5APICALL RD5SetFilterAttr(
		 const int	nTableID,
		 const int	nFilterID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * �Z�b�g�̃A�g���r���[�g�̈��ݒ肵�܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	acAttrs		�A�g���r���[�g�z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����Alfmutil��{@link CSubsetAttr}���g�p���Ă��������B
 */
D5RESULT	D5APICALL RD5SetSubsetAttr(
		 const int	nTableID,
		 const int	nSetID,
		 char acAttrs[D5_FILTER_ATTR_SIZE]
		  );

/**
 * �w�荀�ڂ��폜���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DeleteRealFilter(
			const int nTableID,
			const int nFilterID
		  );

/**
 * ���ڂ̈ʒu��ύX���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFromIndex	�ړ��Ώۂ̈ʒu
 * @param[in]	nToIndex	�}����̈ʒu
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5MoveRealFilter(
			const int nTableID,
			const int nFromIndex,
			const int nToIndex
		  );

/**
 * ���ڂ𕡐����܂��B
 * @param[in]	nTableID	�e�[�u��ID	
 * @param[in]	nFilterID	�������̍���ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DupRealFilter(
			const int nTableID,
			const int nFilterID
		  );

/**
 * �C�ӂ̃f�[�^�^�ɕϊ����č��ڂ𕡐����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	�������̍���ID
 * @param[in]	nDataType	�쐬����f�[�^�^
 * @retval	1�ȏ�	�������ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DupRealFilterEx(
			const int nTableID,
			const int nFilterID,
			const int nDataType
		  );

/**
 * �J�^���O��`�t�@�C������e�[�u���փf�[�^��ǉ����܂��B
 * @param[in]	nTableID		�ǉ�����e�[�u��ID
 * @param[in]	nAppendPos		�ǉ��J�n�ʒu
 * @param[in]	nDataArraySize	�ǉ�����s��
 * @param[in]	szCatalogPath	�J�^���O��`�t�@�C���̑��݂���p�X
 * @param[in]	szCatalogName	�J�^���O��`�t�@�C���̖���
 * @retval	0�ȏ�	�ǉ����ꂽ�s��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5AppendCatalogFile(
			const int	 nTableID,
			const int	 nAppendPos,
			const int	 nDataArraySize,
			const char   szCatalogPath[D5_MAX_PATH],
			const char   szCatalogName[D5_MAX_PATH]
			);

/**
 * �J�^���O��`�t�@�C������e�[�u���փf�[�^��ǉ����܂��B
 * @param[in]	nTableID		�ǉ�����e�[�u��ID
 * @param[in]	nAppendPos		�ǉ��J�n�ʒu
 * @param[in]	nDataArraySize	�ǉ�����s��
 * @param[in]	szCatalogPath	�\����`�t�@�C���̑��݂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
 * @param[in]	szSourcePath	���n�f�[�^�t�@�C���̑��݂���p�X
 * @param[in]	szSourceName	���n�f�[�^�t�@�C���̖���
 * @retval	0�ȏ�	�ǉ����ꂽ�s��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �J�^���O��`�t�@�C������e�[�u���𐶐����܂��B
 * @param[in]	szCatalogPath	�\����`�t�@�C���̑��݂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
 * @param[in]	szSourcePath	���n�f�[�^�t�@�C���̑��݂���p�X
 * @param[in]	szSourceName	���n�f�[�^�t�@�C���̖���
 * @param[in]	szTableName		�V�K�ɐ�������e�[�u������
 * @retval	0�ȏ�	�������ꂽ�e�[�u����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5AddCatalogFileEx2(
			const char   szCatalogPath[D5_MAX_PATH],
			const char   szCatalogName[D5_MAX_PATH],
			const char   szSourcePath[D5_MAX_PATH],
			const char   szSourceName[D5_MAX_PATH],
			const char   szTableName[D5_MAX_PATH]
			);

/**
 * �J�^���O��`�t�@�C������e�[�u���𐶐����܂��B
 * �����F�@�G���[�̔����ӏ��A�G���[�ƂȂ����f�[�^�A�����ւ��l�����O�t�@�C���Ƀ^�u��؂�̃f�[�^�Ƃ��ďo�͂���܂��B
 *            ���O�t�@�C���́A�ǂݍ���Ńe�[�u���ɂ��邱�Ƃ��ł��܂��̂ŁA�G���[�̌�������肵�A�C�����邱�Ƃ��e�ՂɂȂ�܂��B
 *            �Ȃ��A�{�@�\�́A�V���O���X���b�h�œ��삷�邽�ߏ������x���ᑬ�ł��B
 * @param[in]	szCatalogPath	�\����`�t�@�C���̑��݂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
								"structinfo.txt"���g�����Ƃ�����
 * @param[in]	szSourcePath	���n�f�[�^�t�@�C���̑��݂���p�X
 * @param[in]	szSourceName	���n�f�[�^�t�@�C���̖���
								"Sample.csv", "Sample.txt" �Ȃ�
 * @param[in]	szTableName		�V�K�ɐ�������e�[�u������
								�G���W���̖����K���ƁA���[�N�X�y�[�X���
								�����e�[�u�����̂ɂ��G���W���ɂ��ύX����邱�Ƃ�����
 * @retval	0�ȏ�	�������ꂽ�e�[�u����ID
 * @retval	��		�G���[�R�[�h
 			 ��Ƀt�@�C���֌W�̃G���[�i�I�[�v���ł��Ȃ��Ȃǁj���Ԃ���邪�A
			 �������s���A�t�H�[�}�b�g�ُ�Ȃǂ̃G���[���Ԃ���邱�Ƃ�����
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
 * ���ڂ�ǉ����܂��B
 * @param[in]	nTableID		�ǉ�����e�[�u��ID
 * @param[in]	nLoc			���ڑ}���ʒu
 * @param[in]	szFilterName	�V�K�ɒǉ����鍀�ږ���
 * @param[in]	nDataType		�ǉ����ڂ̃f�[�^�^
 * @param[in]	nDataArraySize	�ǉ����郌�R�[�h�z��̃T�C�Y
 * @param[in]	nDataUnitSize	1���R�[�h�̃T�C�Y(byte)
 * @param[in]	szFilePath		�ǉ�����f�[�^�̃t�@�C���p�X
 * @param[in]	szFileName		�ǉ�����f�[�^�̃t�@�C������
 * @retval	0�ȏ�	�������ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �J�^���O��`�t�@�C������e�[�u���𐶐����܂��B
 * @param[in]	szCatalogPath	�J�^���O��`�t�@�C���̑��݂���p�X
 * @param[in]	szCatalogName	�J�^���O��`�t�@�C���̖���
 * @retval	0�ȏ�	�������ꂽ�e�[�u����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5AddCatalogFile(
		 const char   szCatalogPath[D5_MAX_PATH],
		 const char   szCatalogName[D5_MAX_PATH]
		 );

/**
 * �X���[�u���e�[�u���̍��ڈꗗ���擾���܂��B
 * @param[in]	nJoinTableID		JOIN�e�[�u��ID
 * @param[out]	pnMasterTableID		�}�X�^�e�[�u��ID
 * @param[out]	pnMasterSetID		JOIN�쐬���Ɏg�p�����}�X�^�e�[�u���̃Z�b�gID
 * @param[out]	pnSlaveTableID		�X���[�u�e�[�u��ID
 * @param[out]	pnSlaveSetID		JOIN�쐬���Ɏg�p�����X���[�u�e�[�u���̃Z�b�gID
 * @param[out]	pnSlaveFilterCount	�X���[�u�e�[�u���̍��ڐ�
 * @param[out]	anSlaveFilterIDs	�X���[�u�e�[�u���̍���ID�ꗗ
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnMasterTableID,pnMasterSetID,pnSlaveTableID,pnSlaveSetID,pnSlaveFilterCount,anSlaveFilterIDs�́A
 * lfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �X���[�u�e�[�u���̍��ڂ��}�X�^�e�[�u���ɓ]�����܂��B
 * @param[in]	nJoinTableID	JOIN�e�[�u��ID
 * @param[in]	nSlaveFilterID	�]�����̃X���[�u�e�[�u���̍���ID
 * @retval	0�ȏ�	�ǉ��쐬���ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5MoveSlaveFlt2Master(
		 const	int	nJoinTableID,
		 const	int	nSlaveFilterID
		 );

/**
 * �s�ԍ�����Z�b�g�������ԍ����������܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nTargetRecNo	�����Ώۂ̍s�ԍ�
 * @retval	0		�����Ɉ�v����s��������Ȃ�����
 * @retval	1�ȏ�	�����Ɉ�v����Z�b�g�������ԍ�
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5FindRecNoReal(
		 const	int	   nTableID,
		 const	int	   nSetID,
		 const	int	   nTargetRecNo
		 );

/**
 * ������^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		��������e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ镶����^�̍���ID
 * @param[in]	nStrSrchKind	�������������w�肷��l
 * @param[in]	szSrchStr1		1�Ԗڂ̌�������������
 * @param[in]	szSrchStr2		2�Ԗڂ̌�������������
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5OpenStrFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nStrSrchKind,
		 const	char   szSrchStr1[D5_MAX_STRING_SIZE],
		 const	char   szSrchStr2[D5_MAX_STRING_SIZE]
		 );

/**
 * SJIS�R�[�h�̕�����^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ镶����^�̍���ID
 * @param[in]	nStrSrchKind	�������������w�肷��l
 * @param[in]	szSrchStr1		1�Ԗڂ̌�������������
 * @param[in]	szSrchStr2		2�Ԗڂ̌�������������
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5OpenStrFindRealSJIS(
			const	int		nTableID,
			const	int		nFilterID,
			const	int		nStrSrchKind,
			const	char	szSrchStr1[D5_MAX_STRING_SIZE],
			const	char	szSrchStr2[D5_MAX_STRING_SIZE]
		);

/**
 * ������^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ镶����^�̍���ID
 * @param[in]	nStrSrchKind	�������������w�肷��l
 * @param[in]	szSrchStr1		1�Ԗڂ̌�������������
 * @param[in]	szSrchStr2		2�Ԗڂ̌�������������
 * @param[in]	nLocaleID		�����R�[�hID
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �����^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		��������e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ鐮���^�̍���ID
 * @param[in]	nValSrchKind	�������������w�肷��l
 * @param[in]	nSrchVal1		1�Ԗڂ̌��������l
 * @param[in]	nSrchVal2		2�Ԗڂ̌��������l
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5OpenIntFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nValSrchKind,
		 const	int	   nSrchVal1,
		 const	int	   nSrchVal2
		 );

/**
 * ���������_�^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		��������e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ镂�������_�^�̍���ID
 * @param[in]	nValSrchKind	�������������w�肷��l
 * @param[in]	dSrchVal1		1�Ԗڂ̌��������l
 * @param[in]	dSrchVal2		2�Ԗڂ̌��������l
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5OpenFloatFindReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nValSrchKind,
		 const	double dSrchVal1,
		 const	double dSrchVal2
		 );

/**
 * �����X�e�[�^�X���擾���܂��B
 * @param[in]	nTableID	��������e�[�u��ID
 * @param[out]	pnHitCount	���[�g�Z�b�g�ŁA���������Ɉ�v��������
 * @param[out]	pnFilterID	�����Ώۂ̍���ID
 * @retval	0		�����������o�^����Ă��Ȃ�
 * @retval	1�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnHitCount,pnFilterID�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetFindStatus(
		 const int	nTableID,
		 int		*pnHitCount,
		 int		*pnFilterID
		 );

/**
 * �l�W�����v�ŏ����Ɉ�v����s�������܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSrchID		����ID
 * @param[in]	nSetID		�����Ώۂ̃Z�b�gID
 * @param[in]	nCurPos		���݂̈ʒu
 * @param[in]	nDir		��������
 * @param[out]	pnFilterID	�����Ώۂ̍���ID
 * @param[out]	pnNextPos	���������Ɉ�v����Z�b�g�������ԍ�
 * @retval	0	�����Ɉ�v����s��������Ȃ�����
 * @retval	1	�����Ɉ�v����s����������
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnFilterID,pnNextPos�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �l�W�����v���N���[�Y���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5CloseFindReal(
		 const	int	   nTableID
		 );

/**
 * �J�e�S����`�Ɋ�Â����ނ��s���܂��B
 * @param[in]	nTableID			�e�[�u��ID
 * @param[in]	nFilterID			����ID
 * @param[in]	nCategoryTableID	�J�e�S����`�e�[�u��ID
 * @retval	0�ȏ�	���ނ��A�V�K�ɍ쐬���ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5AddCategoryReal(
		 const	int	   nTableID,
		 const	int	   nFilterID,
		 const	int	   nCategoryTableID
		 );

/**
 * �v�Z�������s���܂��B
 * @param[in]	nTableID	�v�Z���s���e�[�u��ID
 * @param[in]	nSetID		�v�Z���s���Z�b�gID
 * @param[in]	nFilterID	�v�Z���s������ID
 * @param[in]	nCalStart	�v�Z�J�n�ʒu
 * @param[in]	nCalCount	�v�Z���郌�R�[�h��
 * @param[in]	szFormula	�v�Z��
 * @param[out]	szErrorRep	�G���[����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ErrorRep�͖����Ȃ̂ŋ󕶎�����w�肵�Ă��������B
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
 * �e�[�u�����ҏW�\�ł��邩�𒲂ׂ܂��B
 * @param[in]	nTableID	���ׂ�Ώۂ̃e�[�u��ID
 * @param[out]	anReferIDs	���̃e�[�u�����Q�Ƃ��Ă���e�[�u��ID�̈ꗗ
 * @retval	0		anReferIDs�̗L���T�C�Y�i�ҏW�\�j
 * @retval	1�ȏ�	anReferIDs�̗L���T�C�Y�i�ҏW�s�j
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anReferIDs�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5TableCanEdit(
			const int  nTableID,
			int  anReferIDs[D5_MAX_TABLE_COUNT]
		   );

/**
 * �s���폜���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nDelStart	�폜�J�n�s
 * @param[in]	nDelCount	�폜����s��
 * @retval	0�ȏ�	���ۂɍ폜���ꂽ��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DeleteRealRows(
			const int nTableID,
			const int nDelStart,
			const int nDelCount
		   );

/**
 * �s���폜���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nDelStart	�폜�J�n�s
 * @param[in]	nDelCount	�폜����s��
 * @retval	0�ȏ�	���ۂɍ폜���ꂽ��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5DeleteRealRowsEx(
			const int nTableID,
			const int nSetID,
			const int nDelStart,
			const int nDelCount
		   );

/**
 * �s��}�����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nInsPos		�}���ʒu
 * @param[in]	nInsCount	�}������s��
 * @retval	0�ȏ�	���ۂɍ폜���ꂽ��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5InsertRealRows(
			const int nTableID,
			const int nInsPos,
			const int nInsCount
		   );

/**
 * �f�[�^���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	pvWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pvWriteData�́A�f�[�^�^�ɍ��킹��lfmutil�̃N���X���g�p���Ĕz��ւ̃|�C���^���w�肵�Ă��������B
 * 1�f�[�^�݂̂̏ꍇ�́A{@link #RD5OverwriteRealExIntR1},{@link #RD5OverwriteRealExDblR1}
 * ,{@link #RD5OverwriteRealExNumericR1},{@link #RD5OverwriteRealExStrR1}���g�p���Ă��������B
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
 * �f�[�^���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	pvWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pvWriteData�́A�f�[�^�^�ɍ��킹��lfmutil�̃N���X���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �P��f�[�^���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pnDataType	�擾�����f�[�^�^
 * @param[out]	acBuf		�擾�����f�[�^
 * @retval	0�ȏ�	acBuf��Ŏg�p���ꂽ�̈撷
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetData1IntR1},{@link #RD5GetData1DblR1},{@link #RD5GetData1StrR1},{@link #RD5GetData1NumericR1}���g�p���Ă��������B
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
 * �����f�[�^���擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		����ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nRowNo			�Z�b�g�������ԍ�
 * @param[out]	pnDataType		�擾�����f�[�^�^
 * @param[out]	pnGotCount		�擾�����f�[�^��
 * @param[out]	acBuf			�擾����������^�ȊO�̃f�[�^ �܂��� ������^�f�[�^��acCharBuf���f�[�^�J�n�ʒu
 * @param[out]	acCharBuf		�擾����������f�[�^
 * @retval	0�ȏ�	�����E���������_�^�F�擾�����s�̂����A�P��ōő�̃f�[�^�T�C�Y(byte) ������^�FNULL�I�[���܂܂Ȃ��ŏI�s�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetData1MIntR1},{@link #RD5GetData1MDblR1},{@link #RD5GetData1MNumericR1},{@link #RD5GetData1MStrR1}���g�p���Ă��������B
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
 * ���[�g�Z�b�g�ɂ�����s�ʒu���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�擾�������Z�b�g�������ԍ�(1����n�܂�)
 * @param[out]	pnRow1		REAL�e�[�u���F�擾����s�ԍ� JOIN�e�[�u���F�}�X�^���̍s�ԍ�
 * @param[out]	pnRow2		REAL�e�[�u���F�g�p���Ȃ� JOIN�e�[�u���F�X���[�u���s�ԍ�
 * @retval	4	REAL�e�[�u���̏ꍇ�̐���
 * @retval	8	JOIN�e�[�u���̏ꍇ�̐���
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnRow1,pnRow2�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5GetRowNo1(
			const int nTableID,
			const int nSetID,
			const int nRowNo,
			int		*pnRow1,
			int		*pnRow2
		   );

/**
 * ���[�g�Z�b�g�ɂ����镡���̍s�ʒu���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�擾�������Z�b�g�������ԍ�(1����n�܂�)
 * @param[out]	pnGotCount	�擾�����s��
 * @param[out]	anRow1		REAL�e�[�u���F�擾����s�ԍ� JOIN�e�[�u���F�}�X�^���̍s�ԍ�
 * @param[out]	anRow2		REAL�e�[�u���F�g�p���Ȃ� JOIN�e�[�u���F�X���[�u���s�ԍ�
 * @retval	4	REAL�e�[�u���̏ꍇ�̐���
 * @retval	8	JOIN�e�[�u���̏ꍇ�̐���
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnGotCount,anRow1,anRow2�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �Z�b�g�������ԍ��ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	nX			1�Ԗڂ̌�������(�Z�b�g�������ԍ�)
 * @param[in]	nY			2�Ԗڂ̌�������(�Z�b�g�������ԍ�)
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SearchByDispRowNoReal(
			 const int nTableID,
			 const int nSetID,
			 const int nOpeNo,
			 const int nX,
			 const int nY
		 );

/**
 * ���[�g�Z�b�g�̍s�ԍ��ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nTableNo	�}�X�^�e�[�u�����A�X���[�u�e�[�u�����̐ݒ�
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	nX			1�Ԗڂ̌�������(�s�ԍ�)
 * @param[in]	nY			2�Ԗڂ̌�������(�s�ԍ�)
 * @retval	0�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �w�肵�����ڂ̃f�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	pvX			1�Ԗڂ̌��������f�[�^
 * @param[in]	pvY			2�Ԗڂ̌��������f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5SearchByFieldIntR1},{@link #RD5SearchByFieldDblR1},{@link #RD5SearchByFieldNumericR1},{@link #RD5SearchByFieldStrR1}���g�p���Ă��������B
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
 * �w�肵�����ڂ́A�}���`�o�C�g�����R�[�h���g�����������s���܂��B
 * �����񍀖ڈȊO�̌����ɂ�{@link #RD5SearchByField}���g�p���Ă��������B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	pvX			1�Ԗڂ̌��������f�[�^
 * @param[in]	pvY			2�Ԗڂ̌��������f�[�^
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5SearchByFieldSJISR1}���g�p���Ă��������B
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
 * �w�肵�����ڂ́A�}���`�o�C�g�����R�[�h���g�����������s���܂��B
 * �����񍀖ڈȊO�̌����ɂ�{@link #RD5SearchByField}���g�p���Ă��������B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	pvX			1�Ԗڂ̌��������f�[�^
 * @param[in]	pvY			2�Ԗڂ̌��������f�[�^
 * @param[in]	nLocaleID	�����R�[�hID
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5SearchByFieldLocaleR1}���g�p���Ă��������B
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
 * �w�肵�����ڂ́A���C���h�J�[�h���܂ރf�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	szText		����������
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SearchByFieldWildCard(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const char *szText
		);

/**
 * ������ŏ����ꂽ�������Ō������s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	szText		����������
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SearchByText(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE]
				);

/**
 * ������ŏ����ꂽ�������ɂ�錟�����A�}���`�o�C�g�����R�[�h���g�p����ꍇ�ɍs���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	szText		����������
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SearchByTextSJIS(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE]
				);

/**
 * ������ŏ����ꂽ�������ɂ�錟�����A�}���`�o�C�g�����R�[�h���g�p����ꍇ�ɍs���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	szText		����������
 * @param[in]	nLocaleID	�����R�[�hID
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SearchByTextLocale(
				const int nTableID,
				const int nSetID,
				const char szText[D5_MAX_SEARCH_TEXT_SIZE],
				const int nLocaleID
				);

/**
 * �w�肳�ꂽ���ڂŃ\�[�g�������s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nSortDir	�\�[�g�������
 * @retval	1�ȏ�	�\�[�g���ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SortByField(
			const int nTableID,
			const int nFilterID,
			const int nSetID,
			const int nSortDir
		  );

/**
 * �s�ԍ��ɂ��\�[�g�������s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nTableNo	�}�X�^�܂��̓X���[�u�e�[�u�����w��
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nSortDir	�\�[�g�������
 * @retval	1�ȏ�	�\�[�g���ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SortByRowNo(
			const int nTableID,
			const int nTableNo,
			const int nSetID,
			const int nSortDir
		  );

/**
 * ���ڏڍ׏��擾�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[out]	pnDataType		�f�[�^�^
 * @param[out]	pnRangeSize		�o�^����Ă���l�̑���
 * @param[out]	pnNonZeroCount	�[���łȂ��l�������R�[�h��
 * @retval	1�ȏ�	�����i�ڍו\���n���h���j
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnDataType,pnRangeSize,pnNonZeroCount�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �I�[�v���������ڏڍ׏��̍��ڒl���w�肵�������ɕ��ׁA�w�肵�������ԍ��̍��ڒl���擾���܂��B
 * �i�擪�̍��ڒl�̔ԍ���1�Ƃ��A���т̏��Ԃɔԍ��������܂��j
 * @param[in]	nHandle			�I�[�v�����Ɏ擾�����n���h��
 * @param[in]	nOrderByN		���ݐ����ɕ��ׂ邩�ǂ������w��
 * @param[in]	nReverse		�t���ɂ��邩�ǂ������w��
 * @param[in]	nZeroSuppress	���ݐ���0�̃f�[�^���܂߂邩�ǂ������w��
 * @param[in]	nRow			���ڒl�̏����ԍ�
 * @param[out]	pnDataType		�f�[�^�^
 * @param[out]	pvData			�擾�f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnDataType�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 * pvData�́A�f�[�^�^�ɍ��킹��lfmutil�̃N���X���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �I�[�v���������ڏڍ׏��̑��ݐ����擾���܂��B
 * @param[in]	nHandle			�I�[�v�����Ɏ擾�����n���h��
 * @param[in]	nOrderByN		���ݐ����ɕ��ׂ邩�ǂ������w��
 * @param[in]	nReverse		�t���ɂ��邩�ǂ������w��
 * @param[in]	nZeroSuppress	���ݐ���0�̃f�[�^���܂߂邩�ǂ������w��
 * @param[in]	nRow			���ڒl�̏����ԍ�
 * @param[out]	pnCount			�擾�f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnCount�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �I�[�v���������ڏڍ׏����N���[�Y���܂��B
 * @param[in]	nHandle	�I�[�v�����Ɏ擾�����n���h��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT	D5APICALL RD5CloseDetailInfo(
		  const int	 nHandle
		  );

/**
 * �W�v���s���A�W�v�e�[�u�����쐬���܂��B
 * @param[in]	nTableID			�e�[�u��ID
 * @param[in]	nSetID				�Z�b�gID
 * @param[in]	nDimCount			�W�v������
 * @param[in]	pnDimFilterIDs		�W�v�����ƂȂ鍀��ID�z��
 * @param[in]	nMeasureCount		�W�v���x�̐�
 * @param[in]	pnMeasureFilterIDs	�W�v���x�ƂȂ鍀��ID�z��
 * @param[in]	pnSummaryTypes		pnMeasureFilterIDs�̊e���ڂɏW�v��ʂ��w�肷��z��
 * @param[in]	pnFloatFormats		pnMeasureFilterIDs�̊e���ڂɌŒ菬���_���g�p���邩���Ȃ������w�肷��z��
 * @retval	1�ȏ�	�������ꂽ�W�v���ʂ̐V�K�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnDimFilterIDs,pnMeasureFilterIDs,pnSummaryTypes,pnFloatFormats�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
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
 * �e�[�u�����̂���e�[�u��ID���擾���܂��B
 * @param[in]	szTableName	�e�[�u������
 * @retval	0�ȏ�	�e�[�u��ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL  RD5GetTableIDFromName(
			const  char szTableName[D5_MAX_NAME_LENGTH]
		 );

/**
 * ���ږ��̂��獀��ID���擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	szFilterName	���ږ���
 * @retval	1�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL  RD5GetFilterIDFromName(
			const int nTableID,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * REAL�e�[�u������JOIN�e�[�u���̍��ږ��̂��獀��ID���擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID�iJOIN�e�[�u������REAL�e�[�u���j
 * @param[in]	nIsSlave		JOIN�e�[�u���̏ꍇ�A�}�X�^�����X���[�u�������w��
 * @param[in]	szFilterName	���ږ���
 * @retval	1�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL  RD5GetFilterIDFromName2(
			const int nTableID,
			const int nIsSlave,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * �e�[�u�����̂�ύX���܂��B
 * @param[in]	nTableID		�ύX����e�[�u��ID
 * @param[in]	szTableName		�V�K�ɐݒ肷��e�[�u������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetTableName(
			const int  nTableID,
			const char szTableName[D5_MAX_NAME_LENGTH]
			);

/**
 * ���ڂ̖��̂�ύX���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		����ID
 * @param[in]	szFilterName	���ڂ̐V�K����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetFilterName(
			const int  nTableID,
			const int  nFilterID,
			const char szFilterName[D5_MAX_NAME_LENGTH]
			);

/**
 * �Z�b�g���̂�ݒ肵�܂��B
 * @param[in]	nTableID	�Z�b�g�̑�����e�[�u������
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	szSetName	�ݒ肷��Z�b�g���̂��i�[���������z��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetSetName(
			const int  nTableID,
			const int  nSetID,
			const char szSetName[D5_MAX_NAME_LENGTH]
			);

/**
 * ����ID���獀�ږ��̂��擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		����ID
 * @param[out]	szFilterName	���ږ���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetFilterNameR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetFilterName(
			const int  nTableID,
			const int  nFilterID,
			char szFilterName[D5_MAX_NAME_LENGTH]
		   );

/**
 * �Z�b�g���̂��擾���܂��B
 * @param[in]	nTableID	�Z�b�g�̑�����e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[out]	szSetName	�Z�b�g����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetSetNameR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetSetName(
			const int nTableID,
			const int  nSetID,
			char szSetName[D5_MAX_NAME_LENGTH]
		   );

/**
 * ������̖����̃X�y�[�X���폜���邩�ǂ����ɂ��ăt���O��ݒ肵�܂��B
 * @param[in]	nFlag	�����񖖔��̃X�y�[�X�폜�`�F�b�N�t���O
 * @retval	0	���0
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetTailSpaceFlag(
		 const	int	nFlag
		 );

/**
 * �T�[�o��IP�A�h���X���擾���܂��B
 * @param[out]	szIPAddress	IP�A�h���X
 * @retval	0	���[�J���T�[�o
 * @retval	1	�����[�g�T�[�o
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5GetServerIPAddress(char szIPAddress[D5_MAX_NAME_LENGTH]);

/**
 * �T�[�o�̊������擾���܂��B
 * @param[out]	pEnvironment	�����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetEnvironment( TREnvironment *pEnvironment);

/**
 * �G���W����DB�����R�[�h��ݒ肵�܂��B
 * @param[in]	szDBCode	DB�����R�[�h
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetDBCharCode( const char *szDBCode );

/**
 * �w�肳�ꂽD5D�t�@�C���̃w�b�_����DB�R�[�h�A�o�[�W������ǂݏo���܂��B
 * @param[in]	szDBPath		D5D�t�@�C���̑��݂���p�X
 * @param[in]	szDBName		D5D�t�@�C���̖���
 * @param[out]	pD5FileInfo		D5D�t�@�C�����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pD5FileInfo->Version�̊e�v�f�擾�ɂ́Alfmutil��{@link #int_at}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetD5DFileInfo( const char szDBPath[D5_MAX_PATH],
										const char szDBName[D5_MAX_PATH],
										D5FileInfo	*pD5FileInfo
										);

/**
 * �w�肳�ꂽD5T�t�@�C���̃w�b�_����DB�R�[�h�A�o�[�W������ǂݏo���܂��B
 * @param[in]	szTablePath		D5T�t�@�C���̑��݂���p�X
 * @param[in]	szTableName		D5T�t�@�C���̖���
 * @param[out]	pD5FileInfo		D5T�t�@�C�����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pD5FileInfo->Version�̊e�v�f�擾�ɂ́Alfmutil��{@link #int_at}���g�p���Ă��������B
 */
D5RESULT D5APICALL RD5GetD5TFileInfo( const char szTablePath[D5_MAX_PATH],
										const char szTableName[D5_MAX_PATH],
										D5FileInfo	*pD5FileInfo
										);

/**
 * �T�[�o���̃J�����g�f�B���N�g�����擾���܂��B
 * @param[out]	szDirectory	�J�����g�f�B���N�g������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserGetCurrentDirectory(
			char	szDirectory[D5_MAX_PATH]
			);

/**
 * �T�[�o���̃J�����g�f�B���N�g����ύX���܂��B
 * @param[in]	szDirectory	�ύX��f�B���N�g������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserSetCurrentDirectory(
			const char	szDirectory[D5_MAX_PATH]
			);

/**
 * �T�[�o�̃t�@�C���T�C�Y���擾���܂��B
 * @param[in]	szFileName	�t�@�C������
 * @retval	0�ȏ�	�t�@�C���T�C�Y�i8btye�����^�j Windows�Fint64, Linux�Flong long
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULTL D5APICALL	RD5BrowserGetFileSize(
			const char	szFileName[D5_MAX_NAME_LENGTH]
		);

/**
 * �T�[�o�̃t�@�C���ꗗ���擾���܂��B
 * @param[in]	szFindCondition	�t�@�C����������
 * @param[in]	nStart			�擾�J�n�ʒu
 * @param[out]	pnExist			���������ɍ��v������
 * @param[out]	pnGotCount		�擾������
 * @param[out]	acAttrList		�t�@�C���A�g���r���[�g�̔z��
 * @param[out]	szListBuf		�t�@�C�����̈ꗗ
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * �T�[�o����t�@�C����ǂݍ��݂܂��B
 * @param[in]	szFileName	�t�@�C������
 * @param[in]	nStart		�Ǐo���J�n�ʒu
 * @param[out]	pnFileSize	�t�@�C���T�C�Y
 * @param[out]	pnGetLen	�ǂݏo�����T�C�Y(byte)
 * @param[out]	acFileBody	�t�@�C���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserGetFileEx(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const int	nStart,
			int			*pnFileSize,
			int			*pnGetLen,
			char		acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * �T�[�o����t�@�C����ǂݍ��݂܂��B
 * @param[in]	szFileName		�t�@�C������
 * @param[in]	n64Start		�Ǐo���J�n�ʒu
 * @param[out]	pn64FileSize	�t�@�C���T�C�Y
 * @param[out]	pnGetLen		�ǂݏo�����T�C�Y(byte)
 * @param[out]	acFileBody		�t�@�C���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserGetFileEx64(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const INT64	n64Start,
			INT64		*pn64FileSize,
			int			*pnGetLen,
			char		acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * �T�[�o����t�@�C����ǂݍ��݂܂��B
 * @param[in]	szFileName	�t�@�C������
 * @param[out]	pnFileSize	�t�@�C���T�C�Y
 * @param[out]	pnGetLen	�ǂݏo�����T�C�Y(byte)
 * @param[out]	acFileBody	�t�@�C���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserGetFile(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			int		*pnFileSize,
			int		*pnGetLen,
			char	acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * �T�[�o����t�@�C����ǂݍ��݂܂��B
 * @param[in]	szFileName		�t�@�C������
 * @param[out]	pn64FileSize	�t�@�C���T�C�Y
 * @param[out]	pnGetLen		�ǂݏo�����T�C�Y(byte)
 * @param[out]	acFileBody		�t�@�C���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserGetFile64(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			INT64	*pn64FileSize,
			int		*pnGetLen,
			char	acFileBody[D5_MAX_TEXT_SIZE]
		);

/**
 * �T�[�o�Ƀt�@�C�����쐬���܂��B
 * @param[in]	szFileName	�t�@�C������
 * @param[in]	nPutLen		�����o���f�[�^�T�C�Y(byte)
 * @param[in]	acFileBody	�����o���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserPutFile(
			const char	szFileName[D5_MAX_NAME_LENGTH],
			const int	nPutLen,
			const char	acFileBody[D5_MAX_TEXT_SIZE]
			);

/**
 * �T�[�o�̃t�@�C�����폜���܂��B
 * @param[in]	szFileName	�폜����t�@�C������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserDelFile(
			const char	szFileName[D5_MAX_PATH]
		);

/**
 * �T�[�o�Ƀf�B���N�g�����쐬���܂��B
 * @param[in]	szDirectory	�쐬�f�B���N�g������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL	RD5BrowserMakeDirectory(
			const char	szDirectory[D5_MAX_PATH]
		);

/**
 * �T�[�o�Ƀf�B���N�g�����쐬���܂��B
 * @param[in]	szDirectory	�폜����f�B���N�g������
 * @param[in]	nIsAll		�폜���e�ڍ�
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5BrowserDelDirectory(
			const char szDirectory[D5_MAX_PATH],
			const int  nIsAll
			);

/**
 * �T�[�o�̃t�@�C�����̓f�B���N�g�����̂�ύX���܂��B�܂��A�w��̃f�B���N�g���Ɉړ����܂��B
 * @param[in]	szOldName	�t�@�C������
 * @param[in]	szNewName	�쐬�ʒu
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5BrowserMove(
			const char szOldName[D5_MAX_PATH],
			const char szNewName[D5_MAX_PATH]
			);

// �T�[�o�[�ɏ��K�͂ȃt�@�C�����쐬���܂�
/**
 * �T�[�o�Ƀt�@�C�����쐬���܂��B
 * @param[in]	szFileName	�t�@�C������
 * @param[in]	nStart		�쐬�ʒu
 * @param[in]	nPutLen		�����o���f�[�^�T�C�Y(byte)
 * @param[in]	acFileBody	�����o���f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5BrowserPutFileEx(
			const char szFileName[D5_MAX_NAME_LENGTH],
			const int  nStart,
			const int  nPutLen,
			const char acFileBody[D5_MAX_TEXT_SIZE]
			); 

/**
 * �J���}��؂�t�@�C���փf�[�^���G�N�X�|�[�g���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	anIDList	����ID���X�g
 * @param[in]	nRowFrom	�o�͂��J�n����s
 * @param[in]	nRowTo		�o�͂̏I���s
 * @param[in]	nDateSep	���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szDBPath	�o�̓t�@�C���ւ̃p�X
 * @param[in]	szDBName	�o�̓t�@�C������
 * @param[in]	szDefFile	���������_�^�f�[�^�̒�`�t�@�C��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * TAB��؂�t�@�C���փf�[�^���G�N�X�|�[�g���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	anIDList	����ID���X�g
 * @param[in]	nRowFrom	�o�͂��J�n����s
 * @param[in]	nRowTo		�o�͂̏I���s
 * @param[in]	nDateSep	���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szDBPath	�o�̓t�@�C���ւ̃p�X
 * @param[in]	szDBName	�o�̓t�@�C������
 * @param[in]	szDefFile	���������_�^�f�[�^�̒�`�t�@�C��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * �e�[�u���̃f�[�^���A���������_�̌������w�肵�āA�J�^���O��`�t�@�C���փG�N�X�|�[�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	anIDList		�o�͂��鍀��ID���X�g
 * @param[in]	nType			�o�͂���t�@�C���^�C�v
 * @param[in]	nRowFrom		�o�͂���s�̊J�n�ʒu
 * @param[in]	nRowTo			�o�͂���s�̏I���ʒu
 * @param[in]	nDateSep		���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szCatalogPath	�\����`�t�@�C�����o�͂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
 * @param[in]	szDefFile		���������_�^�f�[�^�̒�`�t�@�C��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * �e�[�u���̃f�[�^���A���������_�̌������w�肵�āA�J�^���O��`�t�@�C���փG�N�X�|�[�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	anIDList		�o�͂��鍀��ID���X�g
 * @param[in]	nType			�o�͂���t�@�C���^�C�v
 * @param[in]	nRowFrom		�o�͂���s�̊J�n�ʒu
 * @param[in]	nRowTo			�o�͂���s�̏I���ʒu
 * @param[in]	nDateSep		���t�f�[�^�̋�؂蕶�����w��
 * @param[in]	szCatalogPath	�\����`�t�@�C�����o�͂���p�X
 * @param[in]	szCatalogName	�\����`�t�@�C���̖���
 * @param[in]	szDefFile		���������_�^�f�[�^�̒�`�t�@�C��
 * @param[in]	szSourcePath	���n�f�[�^�t�@�C���̑��݂���p�X
 * @param[in]	szSourceName	���n�f�[�^�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
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
 * D5D�f�[�^�����L�������̈悩��ǂݍ��݂܂��B
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5LoadDBFromSharedMemory();

/* */
D5RESULT D5APICALL RD5UnLoadSharedMemoryDB();

/* */
D5RESULT D5APICALL RD5UnMapSharedMemory();

/**
 * D5D�f�[�^�����L�������̈�֐������܂��B
 * @param[in]	szDBPath	D5D�t�@�C���̑��݂���p�X
 * @param[in]	szDBName	D5D�t�@�C���̖���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5CreateSharedMemoryDB(
			const char szDBPath[D5_MAX_PATH],
			const char szDBName[D5_MAX_PATH]
			 );

/**
 * D5D�f�[�^�����L�������̈悩�������܂��B
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5ReleaseSharedMemoryArea();

/**
 * �T�[�o�̃V�X�e���������T�C�Y���擾���܂��B
 * @param[out]	pMemInfo	�������T�C�Y���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5GetSystemMemInfo(TRMemInfo *pMemInfo);

/**
 * �e�[�u�������L��������ɂ��邩���ʂ��܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	1	���L����������Q�Ƃ���Ă���B
 * @retval	0	���L����������Q�Ƃ���Ă��Ȃ��B
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5IsSharedMemoryTable(int nTableID);

/**
 * ���ڏ����擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nGet			�����擾���鍀�ڐ�
 * @param[out]	pnFltCnt		�����擾�������ڐ�
 * @param[out]	aFilterInfo		���ڏ��
 * @param[out]	aacAttrs		�����_�ȉ��\�������̐ݒ���
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �X�N���v�g����ł̓T�|�[�g���܂���B
 */
D5RESULT D5APICALL RD5GetAllFilterInfo(
				const int nTableID,
				const int nGet,
				int *pnFltCnt,
				TRFilterInfo aFilterInfo[D5_MAX_FILTER_COUNT_JOIN],
				char aacAttrs[D5_MAX_FILTER_COUNT_JOIN][D5_FILTER_ATTR_SIZE]
				);

/**
 * �g�p�������T�C�Y���擾���܂��B
 * @retval	0�ȏ�	�������o�C�g��
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetTotalMemorySize();

/**
 * ���p���������܂߂��g�p�������T�C�Y���擾���܂��B
 * @retval	0�ȏ�	�������T�C�Y(8byte�����^) Windows�Fint64, Linux�Flong long
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetTotalMemorySizeWithShared();

/**
 * �e�[�u���̎g�p�������T�C�Y���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	0�ȏ�	�������o�C�g��(8byte�����^) Windows�Fint64, Linux�Flong long
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetTableMemorySize(const  int nTableID);

/**
 * ���ڂ̎g�p�������T�C�Y���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	0�ȏ�	�������o�C�g���i8byte�����j Windows�Fint64, Linux�Flong long
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetFilterMemorySize(const int nTableID, const int nFilterID);

/**
 * �Z�b�g�̎d�l�������T�C�Y���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[out]	nSetID		�Z�b�gID
 * @retval	0�ȏ�	�w�肵���Z�b�g�̎g�p�������T�C�Y(8byte�����^) Windows�Fint64, Linux�Flong long
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetSetMemorySize(const int nTableID, const int nSetID);

/**
 * �G���W���Ŏg�p�������������J�����܂��B
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT  D5APICALL RD5Shutdown();

/**
 * ���������̎��s�錾���s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nFilterID	����ID
 * @param[in]	nMark		���������w��t���O
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5HighSpeedSearchSetMark(
				const int nTableID,
				const int nSetID,
				const int nFilterID,
				const int nMark
				);

/**
 * ���������̑Ώۂ��ǂ������`�F�b�N���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nFilterID	����ID
 * @retval	1	���������̑Ώۂł���
 * @retval	0	���������̑ΏۂłȂ�
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5HighSpeedSearchHasMark(
				const int nTableID,
				const int nSetID,
				const int nFilterID
				);

/**
 * �ʏ팟���^����������Ԃ̐؂�ւ����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nEnable		������Ԃ̐؂�ւ��t���O
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5HighSpeedSearchEnable(
				const int nTableID,
				const int nFilterID,
				const int nEnable
				);

/**
 * �ʏ팟���^���������̏�Ԃ�₢���킹�܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	1	�����������
 * @retval	0	�ʏ팟�����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5HighSpeedSearchIsEnabled(
				const int nTableID,
				const int nFilterID
				);

/**
 * ���C�Z���X�L�[�̃p�X���[�h�F�؂��s���܂��B
 * @param[in]	szLicenseKey	���C�Z���X�L�[
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5SetPassword(
			const char szLicenseKey[D5_PASSWORD_LENGTH + 1]
);

/* */
D5RESULT D5APICALL RD5GetSerial(
			const char szSerial[D5_SERIALNUM_SIZE + 1]
			);

/**
 * �s�������l���擾���܂��B
 * @retval	0		������
 * @retval	1�ȏ�	�s�������l
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetLimitRowSize();

/**
 * �������g�p�ʐ����l���擾���܂��B
 * @retval	0�ȏ�	�������g�p�ʐ����l(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULTL D5APICALL RD5GetLimitMemSize();

/* */
D5RESULT  D5APICALL RD5GetLimitCPUSize();

/* */
D5RESULT D5APICALL	RD5GetLicenseInfo(
	TLicenseData *pLicenseInfo
);

/**
 * NUMERIC���ڏ����擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		�t�B���^ID
 * @param[out]	pNumericInfo	NUMERIC���ڏ��
 * @param[out]	szRoundMode		�ۂ߃��[�h������
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * �{API�͎g�p�����A{@link #RD5GetNumericInfoR1}���g�p���Ă��������B
 */
D5RESULT D5APICALL	RD5GetNumericInfo(
	const int nTableID,
	const int nFilterID,
	NumericInfo *pNumericInfo,
	char *szRoundMode
);

/**
 * NUMERIC���ڏ����Z�b�g���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		�t�B���^ID
 * @param[in]	pNumericInfo	NUMERIC���ڏ��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL	RD5SetNumericInfo(
	const int nTableID,
	const int nFilterID,
	NumericInfo *pNumericInfo
);

/**
 * ���������_�^�̍��ڂ������Ƃ��āA�l�W�����v�@�\���I�[�v�����܂��B
 * @param[in]	nTableID		��������e�[�u��ID
 * @param[in]	nFilterID		�����ΏۂƂȂ镂�������_�^�̍���ID
 * @param[in]	nValSrchKind	�������������w�肷��l
 * @param[in]	SrchVal1		1�Ԗڂ̌��������l
 * @param[in]	SrchVal2		2�Ԗڂ̌��������l
 * @retval	0�ȏ�	����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
D5RESULT D5APICALL RD5OpenNumericFindReal(
			const	int		nTableID,
			const	int		nFilterID,
			const	int		nValSrchKind,
			const	Numeric	SrchVal1,
			const	Numeric	SrchVal2
);

/**
 * NUMERIC�^�̍��ڂ�ǉ����܂��BNUMERIC�^�̍��ڂɕK�v��NumericInfo�\���̂𓯎��ɐݒ肵�܂��B
 * @param[in]	nTableID		�ǉ�����e�[�u��ID
 * @param[in]	nLoc			���ڑ}���ʒu
 * @param[in]	szFilterName	�V�K�ɒǉ����鍀�ږ���
 * @param[in]	nDataArraySize	�ǉ����郌�R�[�h�z��̃T�C�Y
 * @param[in]	nScale			NumericInfo�\���̂ɐݒ肷��Scale�l
 * @param[in]	nRoundMode		NumericInfo�\���̂ɐݒ肷��RoundMode�l
 * @param[in]	szFilePath		�ǉ�����f�[�^�̃t�@�C���p�X
 * @param[in]	szFileName		�ǉ�����f�[�^�̃t�@�C������
 * @retval	0�ȏ�	�������ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * NUMERIC�^�̃f�[�^�^�ɕϊ����č��ڂ𕡐����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	�������̍���ID
 * @param[in]	nScale		���ڂɐݒ肷��Scale�l
 * @param[in]	nRoundMode	���ڂɐݒ肷��RoundMode�l
 * @retval	1�ȏ�	�������ꂽ����ID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
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
 * �����f�[�^���擾���܂��B
 * @param[in]	TableID			�e�[�u��ID
 * @param[in]	FltID			����ID
 * @param[in]	SetID			�Z�b�gID
 * @param[in]	RowNo			�Z�b�g�������ԍ�
 * @param[in]	RCount			�擾���R�[�h��
 * @param[in]	BufSize			������f�[�^�G���A�̃T�C�Y
 * @param[out]	iDataType		�擾�����f�[�^�^
 * @param[out]	nGot			�擾�����f�[�^��
 * @param[out]	pOutBuf			�擾����������^�ȊO�̃f�[�^ �܂��� ������^�f�[�^��acCharBuf���f�[�^�J�n�ʒu
 * @param[out]	charbuf			�擾����������f�[�^
 * @retval	0�ȏ�	�����E���������_�^�F�擾�����s�̂����A�P��ōő�̃f�[�^�T�C�Y(byte) ������^�FNULL�I�[���܂܂Ȃ��ŏI�s�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 */
D5RESULT D5APICALL RD5GetData1MEx(
            const int	TableID,						//  IN:�e�[�u���h�c
            const int	FltID,							//  IN:FilterID
            const int	SetID,							//  IN:-1 �Ȃ�J�����g�Z�b�g
            const int	RowNo,							//  IN:�s�ԍ��i�P����n�܂�j
			const int	RCount,							//  IN:�擾���R�[�h��
			const int	BufSize,						//	INT:������f�[�^�G���A�̃T�C�Y
            int*		iDataType,						//  OUT:�f�[�^�̃^�C�v�ԍ�
			int*		nGot,							//	OUT:�擾�ł����f�[�^��
			void*		pOutBuf,						//	OUT:�f�[�^(�Ăяo�����ŗ̈�m��) ������̎��́Acharbuf���ł̊J�n�ʒu
			char*		charbuf							//  OUT:������f�[�^(�Ăяo�����ŗ̈�m��)
          );		 //  OUT:���̎��A�G���[

/**
 * �v�Z�������s���܂��B
 * @param[in]	nTableID	�v�Z���s���e�[�u��ID
 * @param[in]	nSetID		�v�Z���s���Z�b�gID
 * @param[in]	nCalStart	�v�Z�J�n�ʒu
 * @param[in]	nCalCount	�v�Z���郌�R�[�h��
 * @param[in]	szFormula	�v�Z��
 * @param[in]	iResultDataType	 �v�Z���ʃf�[�^�̃^�C�v
 * @param[out]	pvOutput		�v�Z���ʂ��o�͂���z��̈�
 * @param[in]	iStrAreaSize	pcStrArea�̈�̃T�C�Y�i�o�C�g�P�ʁj
 * @param[out]	pcStrArea	�v�Z���ʕ�������i�[����̈�
 * @param[out]	szErrorRep	�G���[����
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 *�@�v�Z���ʂ�z����炢�܂�
 * ErrorRep�͖����Ȃ̂ŋ󕶎�����w�肵�Ă��������B
 */
D5RESULT D5APICALL RD5CalcPtr (
        const int   TablelID,
        const int   SetID,
        const int   CalStart,
        const int   CalCount,
        const char  PCFormula[D5_MAX_STRING_SIZE],
        const int	iResultDataType,		//�v�Z���ʃf�[�^�̃^�C�v	int=3,�E�E�E
        void*   pvOutput,					//�v�Z���ʂ��o�͂���z��̈�
        size_t   iStrAreaSize,				//pcStrArea�̈�̃T�C�Y�i�o�C�g�P�ʁj
        char *   pcStrArea,					//�v�Z���ʕ�������i�[����̈�
        char       ErrorRep[D5_MAX_STRING_SIZE]
        );

/**
* REAL�e�[�u�����������Ɋi�[���܂��B
* @param[in]	nTableID	�i�[�������e�[�u����ID
* @param[in]	pMemPtr	�@�@�i�[���郁�����̃|�C���^
* @param[in]	szMemSize�@ �g�p�\�������T�C�Y
* @param[out]	pEndMemPtr	�I���ʒu�ւ̃|�C���^�B 
* @retval	0	����
* @retval	��	�G���[�R�[�h
* 
*/
D5RESULT D5APICALL RD5SaveRealTable2Mem(
										const int    nTableID, 
										const void*  pMemPtr, 
										const size_t szMemSize,
										 void** pEndMemPtr
										);
/**
* ���[�N�X�y�[�X���������Ɋi�[���܂��B
* @param[in]	pMemPtr	�@�@�i�[���郁�����̃|�C���^
* @param[in]	szMemSize�@ �g�p�\�������T�C�Y
* @param[out]	pEndMemPtr	�I���ʒu�ւ̃|�C���^�B 
* @retval	0	����
* @retval	��	�G���[�R�[�h
* 
*/
D5RESULT D5APICALL RD5SaveDB2Mem(
								 const  void*	pMemPtr, 
								 const size_t	szMemSize,
								 void**	pEndMemPtr
								 );


/**
* REAL�e�[�u�����w�肳�ꂽ���������烍�[�h���܂��B
* @param[in]	pMemPtr	�@�@�e�[�u�����i�[���Ă��郁�����̃|�C���^
* @param[out]	pEndMemPtr	�I���ʒu�ւ̃|�C���^�B 
* @retval	���[�h���ꂽ�e�[�u���h�c
* @retval	��	�G���[�R�[�h
* 
*/
D5RESULT D5APICALL RD5LoadRealTableFromMem(
											const void* pMemPtr,
											void** pEndMemPtr
											);

/**
* ���[�N�X�y�[�X���w�肳�ꂽ���������烍�[�h���܂��B
* @param[in]	pMemPtr	�@�@���[�N�X�y�[�X���i�[���Ă��郁�����̃|�C���^
* @param[out]	pEndMemPtr	�I���ʒu�ւ̃|�C���^�B 
* @retval	0	����
* @retval	��	�G���[�R�[�h
* 
*/
D5RESULT D5APICALL RD5LoadDBFromMem(
									const void* pMemPtr,
									void** pEndMemPtr
									);



/**
* �e�[�u����SetID�쐬��ݒ肷��set�h�c����n�߂�B
* @param[in]	�@nTableID	�i�[�������e�[�u����ID
* @param[in]	�@nNewSetID	�n�߂�r�����h�c�ԍ�
* @retval	0 �@����
* @retval	��	�G���[�R�[�h
* 
*/
D5RESULT D5APICALL RD5ResetSetID(const int nTableID,
								 const int nNewSetID
								 );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_RD5API_H
