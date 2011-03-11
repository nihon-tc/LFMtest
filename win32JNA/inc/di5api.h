/*--------------------------------------------------------------------------
*		di5api.h
*
*       DI5 DLL API DEFINITION   version 2.00 
*             
*           (C)2001-2009 Turbo Data Laboratories, Inc.
* 
----------------------------------------------------------------------------*/
#ifndef _D5API_H
#define _D5API_H

#include 	"di5error.h"
#include	"numeric.h"


#if defined(D5_WINDOWS)
	#define INT64					__int64 
#else
	#define INT64					long long
#endif 

#define  D5_VERSION_SIZE			4
#define  D5_VERSION_STRING_SIZE     64
#define  D5_MAX_PATH				512
#define	 D5_MAX_STRING_LENGTH_OS	256
#define  RD5_MAX_CATSIZE			256

// ���C�Z���X���擾����
#define	D5_LICENSE_DATE_SIZE		(9)

#define D5RESULT					int
#define D5RESULTL					INT64

#define D5_MAX_STRING_SIZE      (4096)		//  ������̍ő咷
#define	D5_MAX_TEXT_SIZE		(8192)		//	Browser�ň�����Text�f�[�^�̍ő咷
#define D5_MAX_NAME_LENGTH      (256)       //  �e�[�u�����Ȃǂ̖��̂̍ő咷  32->256 2001.10.16
#define	D5_MAX_JOIN_KEY			(32)		//	JOIN�L�[���̍ő�l
#define	D5_MAX_COMBINE			(64)		//	D5CombineTableList�̍ő�ð��ِ�

#if defined(WIN32) || defined(WIN64)
  #define D5APICALL   __stdcall
#else
//UNIX
#define D5APICALL   
#endif

#define D5_MAX_SET_COUNT         (10000)		
#define D5_MAX_FILTER_COUNT_REAL (512)
#define D5_MAX_FILTER_COUNT_JOIN (1024)
#define D5_MAX_FILTER_COUNT      (1024)		
#define D5_MAX_TABLE_COUNT       (10000)	
#define D5_SHORT_STRING_SZ       (128)

#define D5_MAX_LONG_STRING_SIZE (1024*1024)	//  ������̍ő咷 (1M)


// ---- �f�[�^��� ----
#define D5_DT_ERROR             (0)
#define D5_DT_BLANK             (1)
#define D5_DT_INTEGER           (2)
#define D5_DT_DOUBLE            (3)
#define D5_DT_DATE              (4)
#define D5_DT_TIME              (5)
#define D5_DT_STRING            (6)
#define D5_DT_DATETIME          (7)
#define D5_DT_DECIMAL           (8)		


// ----	JOIN-CHAIN	----
#define	D5_MAX_CHAIN_ASSOCIATION	(4)
#define	D5_MAX_TREE_QUALIFY			(D5_MAX_JOIN_CHAIN)

// ---- �e�[�u���̎�� ----
#define D5_TABLEKIND_REAL       (0)
#define D5_TABLEKIND_MASTER     (1)
#define D5_TABLEKIND_JOIN       (2)

// ----	�t�B���^�[�̃A�g���r���[�g�̈�T�C�Y ----
#define	D5_FILTER_ATTR_SIZE		(64)

#define	D5_MAX_CACHE			(128)		//	��ٸ�Ǐo���̍ő廲��

// ----- �����ڂ̌�������������̍ő咷
#define D5_MAX_SEARCH_TEXT_SIZE 4096

//#define	D5_N_SUMMARY_DIM		(4)
#define	D5_N_SUMMARY_DIM		(32)

#define D5_PASSWORD_LENGTH		(92)	
#define D5_SERIALNUM_SIZE		(60)	


//  �g���q�ꗗ
#define  DB_FILE_EXTENSION      ".D5D"
#define  TABLE_FILE_EXTENSION   ".D5T"


// ---- �������@ ----
#define D5_OPETYPE_EQUAL        (0)         // pcX == v
#define D5_OPETYPE_BETWEEN      (1)         // pcX =< v && v= < pcY
#define D5_OPETYPE_LESSEQUAL    (2)         // v =< pcX
#define D5_OPETYPE_GREATEREQUAL (3)         // pcX =< v
#define D5_OPETYPE_NOTEQUAL     (4)         // pcX <> v
#define D5_OPETYPE_WITHIN       (5)         // pcX < v && v < pcY
#define D5_OPETYPE_LESS         (6)         // v < pcX
#define D5_OPETYPE_GREATER      (7)         // pcX < v
#define	D5_OPETYPE_STR_LEFT		(8)			//	STRING	�O����v
#define	D5_OPETYPE_STR_MID		(9)			//	STRING	���Ԉ�v
#define	D5_OPETYPE_STR_RIGHT	(10)		//	STRING	�����v

// ---- �\�[�g���@ ----
#define D5_SORT_ASCENDANT       (0)
#define D5_SORT_DESCENDANT      (1)

// LocaleID��`
#define D5_LOCALE_SJIS			(0)
#define D5_LOCALE_MS932			(1)
#define D5_LOCALE_MS949			(2)
#define D5_LOCALE_UTF8			(3)
#define D5_LOCALE_EUC			(4)
#define D5_LOCALE_CP1252		(5)
#define D5_LOCALE_MS936			(6)
#define D5_LOCALE_DEFAULT		(99)


// DBCharCode�����R�[�h��`
#define D5_DBCODE_SJIS			"Shift_JIS"
#define D5_DBCODE_MS932			"MS932"
#define D5_DBCODE_MS949			"MS949"
#define D5_DBCODE_UTF8			"UTF8"
#define D5_DBCODE_EUC			"EUC_JP"	// forDBCC7
#define D5_DBCODE_CP1252		"Cp1252"	// forDBCC7	// forDBbf01
#define D5_DBCODE_MS936			"MS936"		// forDBCC7
#define D5_DBCODE_UNKNOWN		"NotDefined"	// forDBCC8


#define	D5_SUMMARY_NONE		(0)		// �W�v���@��������`����Ă��Ȃ�
#define	D5_SUMMARY_COUNT	(1)		// ���̏W�v
#define	D5_SUMMARY_MAX		(2)		// �ő�l�̏W�v
#define	D5_SUMMARY_MIN		(4)		// �ŏ��l�̏W�v
#define	D5_SUMMARY_SUM		(8)		// ���v�l�̏W�v
#define	D5_SUMMARY_AVERAGE	(16)	// ���ϒl�̏W�v


// ---- �W�����Z�̕��@ ----
#define D5_SETOPE_AND           (0)
#define D5_SETOPE_OR            (1)
#define D5_SETOPE_SUB           (2)


#ifndef	J_MASTER
#define	J_MASTER	0
#endif

#ifndef	J_SLAVE
#define	J_SLAVE	1
#endif

#define	D5_MIN_JOIN_CHAIN		16
#define	D5_MAX_JOIN_CHAIN		510 // �ő�Join�`�F�[���ݒ�

#define MAX_SHMTBL_ENTRIES		(20000)


// ---- �e�[�u����� ----
typedef struct _TTableInfo{
    int TableID;            //  Table ��ID�ԍ�
    int TableKind;          //  Table�̎�� 0:Real 1:Master 2:Join
    int nFilter;            //  ���݂���t�B���^�[�̐�
    int nSet;               //  �ێ�����W���̐�(���ݒl)
    int TotalRows;          //  �S�s��
    char TableName[D5_MAX_NAME_LENGTH + 8];     //  �e�[�u������(0�ŏI��镶����)
}TTableInfo;

#endif //_D5API_H
