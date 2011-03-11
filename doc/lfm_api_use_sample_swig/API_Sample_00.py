#!/usr/bin/env python
# -*- coding: utf-8 -*-

## @package API_Sample_00
# LFM APIサンプルプログラム
#
# @author Turbo Data Laboratories, Inc.
# @date 2009/07/01

import sys
import codecs
import os
import decimal

# LFM
import lfmtblpy
import lfmutilpy


## OS文字コード
ENC_OS = "MS932"
#ENC_OS = "UTF8"

## DB文字コード
#ENC_DB = "MS932"
ENC_DB = "UTF8"

# 標準入出力文字コード設定
sys.stdin  = codecs.getreader(ENC_OS)(sys.stdin)
sys.stdout = codecs.getwriter(ENC_OS)(sys.stdout)
sys.stderr = codecs.getwriter(ENC_OS)(sys.stderr)

## 入力ファイルパス
PathIn = u"./in"

## 出力ファイルパス
PathOut = u"./out"

## サンプルデータファイル
SampleD5DFile		= "TypeTbl.D5D"
SampleD5TFile		= "TypeTbl.D5T"
SampleD5DFile_MS	= "TypeTbl_MS.D5D"
SampleD5DFile_JOIN	= "JoinTbl.D5D"
SampleD5DFile_SJIS	= "TypeTbl2_SJIS.D5D"
SampleCatalogFile	= "RD5SaveAsCatalog"
SampleFilterData	= "fdata10.dat"
SampleSrcData		= "SrcDataEx.dat"
SampleD5DFile_X64	= "TypeTbl2_x64.D5D"


## 6-3-2 エンジン管理機能
def testEngine():
	funcName = "testEngine"
	print "### %s ### start" % funcName

	# RD5GetVersion -> RD5GetVersionR1
	VArray = lfmutilpy.CTypeIntAr(lfmtblpy.D5_VERSION_SIZE)
	ret = lfmtblpy.RD5GetVersionR1(VArray.getPtr())
	print "[RD5GetVersionR1] retval = %d [%d,%d,%d,%d]" % (ret, VArray.at(0), VArray.at(1), VArray.at(2), VArray.at(3))

	# RD5GetVersion -> RD5GetCopyRightR1
	ret = lfmtblpy.RD5GetCopyRightR1()
	print "[RD5GetCopyRightR1] retval = %s" % ret

	# RD5Shutdown -> 後に移動

	# RD5SetTailSpaceFlag
	NewFlag = 1
	ret = lfmtblpy.RD5SetTailSpaceFlag(NewFlag)
	print "[RD5SetTailSpaceFlag] retval = %d [NewFlag=%d]" % (ret, NewFlag)

	# RD5SetPassword
	LicenseKey = ""
	ret = lfmtblpy.RD5SetPassword(LicenseKey)
	print "[RD5SetPassword] retval = %d [LicenseKey=%s]" % (ret, LicenseKey)

	# RD5Shutdown
	ret = lfmtblpy.RD5Shutdown()
	print "[RD5Shutdown] retval = %d" % ret

	print "### %s ### end" % funcName
	return

## 6-3-3 ワークスペース（ データベース）管理機能
def testWS():
	funcName = "testWS"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)

	# RD5LoadDB
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5SaveDBAs
	Name = "testRD5SaveDBAs"
	ret = lfmtblpy.RD5SaveDBAs(PathOut.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5SaveDBAs] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathOut, Name)

	# RD5SaveDB
	ret = lfmtblpy.RD5SaveDB()
	print "[RD5SaveDB] retval = %d" % ret

	# RD5ClearDB -> 後に移動

	# RD5GetPathName -> RD5GetDBPathR1
	ret = lfmtblpy.RD5GetDBPathR1().decode(ENC_OS)
	print "[RD5GetDBPathR1] retval = %s" % ret

	# RD5GetPathName -> RD5GetDBNameR1
	ret = lfmtblpy.RD5GetDBNameR1().decode(ENC_OS)
	print "[RD5GetDBNameR1] retval = %s" % ret

	# RD5GetLimitRowSize
	ret = lfmtblpy.RD5GetLimitRowSize()
	print "[RD5GetLimitRowSize] retval = %d" % ret

	# RD5GetLimitMemSize
	ret = lfmtblpy.RD5GetLimitMemSize()
	print "[RD5GetLimitMemSize] retval = %d" % ret

	# RD5GetTotalMemorySize
	ret = lfmtblpy.RD5GetTotalMemorySize()
	print "[RD5GetTotalMemorySize] retval = %d" % ret

	# RD5GetTotalMemorySizeWithShared
	ret = lfmtblpy.RD5GetTotalMemorySizeWithShared()
	print "[RD5GetTotalMemorySizeWithShared] retval = %d" % ret

	# RD5ClearDB <- 前から移動
	ret = lfmtblpy.RD5ClearDB()
	print "[RD5ClearDB] retval = %d" % ret

	print "### %s ### end" % funcName
	return

## 6-3-4 テーブル管理機能
def testTable():
	funcName = "testTable"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile_JOIN
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5GetNTable
	ret = lfmtblpy.RD5GetNTable()
	print "[RD5GetNTable] retval = %d" % ret

	# RD5GetTableIDList
	TablIDList = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_TABLE_COUNT)
	ret = lfmtblpy.RD5GetTableIDList(TablIDList.getPtr())
	print "[RD5GetTableIDList] retval = ", ret, " [TablIDList=", Array2List(TablIDList, ret), "]"

	# RD5GenerateTableName -> RD5GenerateTableNameR1
	PCSeedName = "TblSeed"
	PCGenName = lfmtblpy.RD5GenerateTableNameR1(PCSeedName.encode(ENC_DB)).decode(ENC_DB)
	print "[RD5GenerateTableNameR1] PCGenName = %s [PCSeedName=%s]" % (PCGenName, PCSeedName)

	# RD5LoadRealTable
	PCTblName = u"TypeTbl"
	ret = lfmtblpy.RD5LoadRealTable(PathIn.encode(ENC_OS), PCTblName.encode(ENC_OS))
	print "[RD5LoadRealTable] retval = %d [PCTblPath=%s,PCTblName=%s]" % (ret, PathIn, PCTblName)

	# RD5AddRealTable
	PCTblName = "TEST_TABLE"
	RowCount = 10
	ret = lfmtblpy.RD5AddRealTable(PCTblName, RowCount)
	print "[RD5AddRealTable] retval = %d [PCTblName=%s,RowCount=%d]" % (ret, PCTblName, RowCount)

	# RD5SaveRealTable
	TableID = 3
	ret = lfmtblpy.RD5SaveRealTable(PathOut.encode(ENC_OS), TableID)
	print "[RD5SaveRealTable] retval = %d [PCTblPath=%s,TableID=%d]" % (ret, PathOut, TableID)

	# RD5AddJoinTable
	PCTblName		= "JoinTbl"
	IsOuter			= 0
	MasterTblID		= 1
	MasterSetID		= 1
	#nFlt			= lfmtblpy.D5_MAX_JOIN_KEY
	nFlt			= 2
	MasterFltIDs	= lfmutilpy.CTypeIntAr(nFlt)
	MasterFltIDs.put(0, 2)
	MasterFltIDs.put(1, 0)
	SlaveTblID		= 2
	SlaveSetID		= 1
	SlaveFltIDs		= lfmutilpy.CTypeIntAr(nFlt)
	SlaveFltIDs.put(0, 1)
	SlaveFltIDs.put(1, 0)
	ret = lfmtblpy.RD5AddJoinTable(PCTblName, IsOuter, MasterTblID, MasterSetID, MasterFltIDs.getPtr(), SlaveTblID, SlaveSetID, SlaveFltIDs.getPtr())
	print "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs="\
		% (ret, PCTblName, IsOuter, MasterTblID, MasterSetID)\
		, Array2List(MasterFltIDs, nFlt)\
		, ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=" % (SlaveTblID, SlaveSetID)\
		, Array2List(SlaveFltIDs, nFlt), "]"
	JoinTblID = ret

	# RD5ConvertJoinToReal
	PCTblName		= "Join2Real"
	JSetID			= -1
	IncludeRowNoM	= 1
	IncludeRowNoS	= 1
	#nFlt			= lfmtblpy.D5_MAX_FILTER_COUNT_REAL
	nFlt			= 4
	FltIDs			= lfmutilpy.CTypeIntAr(nFlt)
	FltIDs.put(0, 1)
	FltIDs.put(1, 2)
	FltIDs.put(2, 4)
	FltIDs.put(3, 0)
	VLIsLinked		= 0
	ret = lfmtblpy.RD5ConvertJoinToReal(PCTblName, JoinTblID, JSetID, IncludeRowNoM, IncludeRowNoS, FltIDs.getPtr(), VLIsLinked)
	print "[RD5ConvertJoinToReal] retval = %d [PCTblName=%s,JoinTblID=%d,JSetID=%d,IncludeRowNoM=%d,IncludeRowNoS=%d,FltIDs="\
		% (ret, PCTblName, JoinTblID, JSetID, IncludeRowNoM, IncludeRowNoS)\
		, Array2List(FltIDs, nFlt)\
		, ",VLIsLinked=%d]" % VLIsLinked

	# RD5ExtractJoinInOut
	DestTableID		= 2
	DestSetID		= 1
	DestFilterID	= 2
	SrcTableID		= 3
	SrcSetID		= 1
	SrcFilterID		= 1
	IsJoinIn		= 1
	ret = lfmtblpy.RD5ExtractJoinInOut(DestTableID, DestSetID, DestFilterID, SrcTableID, SrcSetID, SrcFilterID, IsJoinIn)
	print "[RD5ExtractJoinInOut] retval = %d [DestTableID=%d,DestSetID=%d,DestFilterID=%d,SrcTableID=%d,SrcSetID=%d,SrcFilterID=%d,IsJoinIn=%d]"\
		% (ret, DestTableID, DestSetID, DestFilterID, SrcTableID, SrcSetID, SrcFilterID, IsJoinIn)

	# RD5RealizeJoinChain → 未サポート
	# RD5RealizeJoinChainEx → 未サポート
	# RD5QualifyTree → 未サポート

	# RD5SetMaxJoinChain
	MaxJoinChain = 510
	ret = lfmtblpy.RD5SetMaxJoinChain(MaxJoinChain)
	print "[RD5SetMaxJoinChain] retval = %d [MaxJoinChain=%s]" % (ret, MaxJoinChain)

	# RD5DeleteTable
	TableID = 5
	ret = lfmtblpy.RD5DeleteTable(TableID)
	print "[RD5DeleteTable] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5GetTableName -> RD5GetTableNameR1
	TableID = 4
	TableName = lfmtblpy.RD5GetTableNameR1(TableID).decode(ENC_DB)
	print "[RD5GetTableNameR1] TableName = %s [TableID=%d]" % (TableName, TableID)

	# RD5GetTableProperty
	TableInfo = lfmtblpy.TTableInfo()
	ret = lfmtblpy.RD5GetTableProperty(TableID, TableInfo)
	print "[RD5GetTableProperty] retval = %d [TableID=%d,TableKind=%d,nFilter=%d,nSet=%d,TotalRows=%d,TableName=%s]"\
		% (ret, TableInfo.TableID, TableInfo.TableKind, TableInfo.nFilter, TableInfo.nSet, TableInfo.TotalRows, TableInfo.TableName)

	# RD5SetTableName
	TableName = "TypeTblRN"
	ret = lfmtblpy.RD5SetTableName(TableID, TableName)
	print "[RD5SetTableName] retval = %d [TableID=%d,TableName=%s]" % (ret, TableID, TableName)

	# RD5GetTableIDFromName
	ret = lfmtblpy.RD5GetTableIDFromName(TableName)
	print "[RD5GetTableIDFromName] retval = %d [TableName=%s]" % (ret, TableName)

	# RD5GetJoinInfoEx -> RD5GetJoinInfoExR1
	TableID			= JoinTblID
	IsOuter			= lfmutilpy.CTypeIntAr(1)
	nJoinKey		= lfmutilpy.CTypeIntAr(1)
	MasterTblID		= lfmutilpy.CTypeIntAr(1)
	MasterSetID		= lfmutilpy.CTypeIntAr(1)
	MasterFltIDs	= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_JOIN_KEY)
	SlaveTblID		= lfmutilpy.CTypeIntAr(1)
	SlaveSetID		= lfmutilpy.CTypeIntAr(1)
	SlaveFltIDs		= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_JOIN_KEY)
	ret = lfmtblpy.RD5GetJoinInfoExR1(TableID, IsOuter.getPtr(), nJoinKey.getPtr()\
								, MasterTblID.getPtr(), MasterSetID.getPtr(), MasterFltIDs.getPtr()\
								, SlaveTblID.getPtr(), SlaveSetID.getPtr(), SlaveFltIDs.getPtr())
	print "[RD5GetJoinInfoExR1] retval = %d [TableID=%d][IsOuter=%d,nJoinKey=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs="\
		% (ret, TableID, IsOuter.at(0), nJoinKey.at(0), MasterTblID.at(0), MasterSetID.at(0))\
		, Array2List(MasterFltIDs, nJoinKey.at(0))\
		, ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=" % (SlaveTblID.at(0), SlaveSetID.at(0))\
		, Array2List(SlaveFltIDs, nJoinKey.at(0)), "]"

	# RD5GetJoinSrcTblInfo
	TableID		= JoinTblID
	NMasterFlt	= lfmutilpy.CTypeIntAr(1)
	NSlaveFlt	= lfmutilpy.CTypeIntAr(1)
	JFltIDs		= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_JOIN)
	SrcTblIDs	= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_JOIN)
	SrcFltIDs	= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_JOIN)
	ret = lfmtblpy.RD5GetJoinSrcTblInfo(TableID, NMasterFlt.getPtr(), NSlaveFlt.getPtr(), JFltIDs.getPtr(), SrcTblIDs.getPtr(), SrcFltIDs.getPtr())
	print "[RD5GetJoinSrcTblInfo] retval = %d [TableID=%d][NMasterFlt=%d,NSlaveFlt=%d,JFltIDs="\
		% (ret, TableID, NMasterFlt.at(0), NSlaveFlt.at(0))\
		, Array2List(JFltIDs, ret) ,",SrcTblIDs=", Array2List(SrcTblIDs, ret), "SrcFltIDs=", Array2List(SrcFltIDs, ret), "]"

	# RD5GetJoinSrcTblIDs
	ret = lfmtblpy.RD5GetJoinSrcTblIDs(TableID, JFltIDs.getPtr(), SrcTblIDs.getPtr(), SrcFltIDs.getPtr())
	print "[RD5GetJoinSrcTblIDs] retval = %d [TableID=%d][JFltIDs=" % (ret, TableID)\
		, Array2List(JFltIDs, ret) ,",SrcTblIDs=", Array2List(SrcTblIDs, ret), ",SrcFltIDs=", Array2List(SrcFltIDs, ret), "]"


	# reset
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5DuplicateRealTable
	TableID = 1
	PCTblName = u"複製テーブル"
	ret = lfmtblpy.RD5DuplicateRealTable(PCTblName.encode(ENC_DB), TableID)
	print "[RD5DuplicateRealTable] retval = %d [PCTblName=%s,TableID=%d]" % (ret, PCTblName, TableID)

	# RD5ExtractRealTable
	PCTblName = u"Extractテーブル"
	SetID = -1
	ExtractFilterIDList = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_REAL)
	size = 3
	ExtractFilterIDList.put(0, 2)
	ExtractFilterIDList.put(1, 3)
	ExtractFilterIDList.put(2, 0)
	ret = lfmtblpy.RD5ExtractRealTable(PCTblName.encode(ENC_DB), TableID, SetID, ExtractFilterIDList.getPtr())
	print "[RD5ExtractRealTable] retval = %d [PCTblName=%s,TableID=%d,SetID=%d,ExtractFilterIDList=" % (ret, PCTblName, TableID, SetID)\
		, Array2List(ExtractFilterIDList, size), "]"

	# RD5ExtractRealTableEx
	PCTblName = u"ExtractテーブルEx"
	IncludeTableID = 1
	IncludeRecNo = 1
	ret = lfmtblpy.RD5ExtractRealTableEx(PCTblName.encode(ENC_DB), TableID, SetID, IncludeTableID, IncludeRecNo, ExtractFilterIDList.getPtr())
	print "[RD5ExtractRealTableEx] retval = %d [PCTblName=%s,TableID=%d,SetID=%d,IncludeTableID=%d,IncludeTableID=%d,ExtractFilterIDList="\
		% (ret, PCTblName, TableID, SetID, IncludeTableID, IncludeRecNo)\
		, Array2List(ExtractFilterIDList, size), "]"

	# RD5CombineRealTable
	PCTblName = u"結合テーブル"
	size = 3
	FltIDs1 = lfmutilpy.CTypeIntAr(size)
	FltIDs1.put(0, 6)
	FltIDs1.put(1, 5)
	FltIDs1.put(2, 0)
	TableID2 = 2
	SetID2 = -1
	FltIDs2 = lfmutilpy.CTypeIntAr(size)
	FltIDs2.put(0, 2)
	FltIDs2.put(1, 3)
	FltIDs2.put(2, 0)
	ret = lfmtblpy.RD5CombineRealTable(PCTblName.encode(ENC_DB), TableID, SetID, FltIDs1.getPtr(), TableID2, SetID2, FltIDs2.getPtr())
	print "[RD5CombineRealTable] retval = %d [PCTblName=%s,TableID1=%d,SetID1=%d,FltIDs1=" % (ret, PCTblName, TableID, SetID)\
		, Array2List(FltIDs1, size)\
		, ",TableID2=%d,SetID2=%d,FltIDs2=" % (TableID2, SetID2)\
		, Array2List(FltIDs2, size), "]"

	# RD5CombineRealTableEx
	PCTblName = u"結合テーブルEx"
	IncludeTableID = 1
	IncludeRecNo = 1
	ret = lfmtblpy.RD5CombineRealTableEx(PCTblName.encode(ENC_DB), IncludeTableID, IncludeRecNo, TableID, SetID, FltIDs1.getPtr()\
										, TableID2, SetID2, FltIDs2.getPtr())
	print "[RD5CombineRealTableEx] retval = %d [PCTblName=%s,IncludeTableID=%d,IncludeRecNo=%d,TableID1=%d,SetID1=%d,FltIDs1="\
		% (ret, PCTblName, IncludeTableID, IncludeRecNo, TableID, SetID)\
		, Array2List(FltIDs1, size)\
		, ",TableID2=%d,SetID2=%d,FltIDs2=" % (TableID2, SetID2)\
		, Array2List(FltIDs2, size), "]"

	# RD5CombineRealTableEx2
	PCTblName = u"結合テーブルEx2"
	ret = lfmtblpy.RD5CombineRealTableEx2(PCTblName.encode(ENC_DB), IncludeTableID, IncludeRecNo, TableID, SetID, FltIDs1.getPtr()\
										, TableID2, SetID2, FltIDs2.getPtr())
	print "[RD5CombineRealTableEx2] retval = %d [PCTblName=%s,IncludeTableID=%d,IncludeRecNo=%d,TableID1=%d,SetID1=%d,FltIDs1="\
		% (ret, PCTblName, IncludeTableID, IncludeRecNo, TableID, SetID)\
		, Array2List(FltIDs1, size)\
		, ",TableID2=%d,SetID2=%d,FltIDs2=" % (TableID2, SetID2)\
		, Array2List(FltIDs2, size), "]"

	# RD5CombineTableList
	PCTblName = u"RD5CombineTableList"
	TableIDList = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_COMBINE)
	size = 2
	TableIDList.put(0, 6)
	TableIDList.put(1, 7)
	TableIDList.put(2, 0)
	SetIDList = lfmutilpy.CTypeIntAr(size)
	IntFltList0 = lfmutilpy.CTypeIntAr(size)
	IntFltList1 = lfmutilpy.CTypeIntAr(size)
	for i in range(size):
		SetIDList.put(i, -1)
		IntFltList0.put(i, 1)
		IntFltList1.put(i, 2)
	IntFltList2 = None
	IntFltList3 = None
	ret = lfmtblpy.RD5CombineTableList(PCTblName.encode(ENC_DB), TableIDList.getPtr(), SetIDList.getPtr()\
									, IntFltList0.getPtr(), IntFltList1.getPtr(), IntFltList2, IntFltList3)
	print "[RD5CombineTableList] retval = %d [PCTblName=%s,TableIDList=" % (ret, PCTblName)\
		, Array2List(TableIDList, size), ",SetIDList=", Array2List(SetIDList, size), ",IntFltList0="\
		, Array2List(IntFltList0, size), ",IntFltList1=", Array2List(IntFltList1, size), ",IntFltList2="\
		, Array2List(IntFltList2, size), ",IntFltList3=", Array2List(IntFltList3, size), "]"
	TableID = 8

	# RD5CondenseRealTable
	ret = lfmtblpy.RD5CondenseRealTable(TableID)
	print "[RD5CondenseRealTable] retval = %d [TableID=%d]" % (ret, TableID)


	# reset
	ret = lfmtblpy.RD5ClearDB()

	# RD5AddCatalogFile
	FilePath = os.path.join(os.getcwd(), PathIn)
	FileName = SampleCatalogFile
	ret = lfmtblpy.RD5AddCatalogFile(FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddCatalogFile] retval = %d [FilePath=%s,FileName=%s]" % (ret, FilePath, FileName)

	# RD5AddCatalogFileEx2
	CatalogPath = PathIn
	CatalogName = SampleCatalogFile
	SourcePath  = CatalogPath
	SourceName  = SampleSrcData
	TableName   = "AddCatalogFileEx2"
	ret = lfmtblpy.RD5AddCatalogFileEx2(CatalogPath.encode(ENC_OS), CatalogName.encode(ENC_OS)\
									, SourcePath.encode(ENC_OS), SourceName.encode(ENC_OS)\
									, TableName.encode(ENC_DB))
	print "[RD5AddCatalogFileEx2] retval = %d [CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s,TableName=%s]"\
		% (ret, CatalogPath, CatalogName, SourcePath, SourceName, TableName)

	# RD5AppendCatalogFile
	TableID       = 2
	AppendPos     = -1
	DataArraySize = 10
	FilePath      = PathIn
	FileName      = SampleCatalogFile
	ret = lfmtblpy.RD5AppendCatalogFile(TableID, AppendPos, DataArraySize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AppendCatalogFile] retval = %d [TableID=%d,AppendPos=%d,DataArraySize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, AppendPos, DataArraySize, FilePath, FileName)

	# RD5AppendCatalogFileEx2
	TableID       = 2
	AppendPos     = 6
	DataArraySize = 5
	CatalogPath   = PathIn
	CatalogName   = SampleCatalogFile
	SourcePath    = PathIn
	SourceName    = SampleSrcData
	ret = lfmtblpy.RD5AppendCatalogFileEx2(TableID, AppendPos, DataArraySize\
										, CatalogPath.encode(ENC_OS), CatalogName.encode(ENC_OS)\
										, SourcePath.encode(ENC_OS), SourceName.encode(ENC_OS))
	print "[RD5AppendCatalogFileEx2] retval = %d [TableID=%d,AppendPos=%d,DataArraySize=%d,CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s]"\
		% (ret, TableID, AppendPos, DataArraySize, CatalogPath, CatalogName, SourcePath, SourceName)

	# RD5SaveAsCatalog
	TableID = 2
	SetID   = 1
	#nFlt = lfmtblpy.D5_MAX_FILTER_COUNT_JOIN
	nFlt = 8
	IDList  = lfmutilpy.CTypeIntAr(nFlt + 1)
	for i in range(nFlt):
		IDList.put(i, i + 1)
	IDList.put(nFlt, -1)
	type     = 0
	RowFrom  = -1
	RowTo    = -1
	Datesep  = '/'
	FilePath = PathOut
	FileName = "RD5SaveAsCatalog"
	ret = lfmtblpy.RD5SaveAsCatalog(TableID, SetID, IDList.getPtr(), type, RowFrom, RowTo, ord(Datesep), FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5SaveAsCatalog] retval = %d [TableID=%d,SetID=%d,IDList=" % (ret, TableID, SetID)\
		, Array2List(IDList, nFlt)\
		, ",type=%d,RowFrom=%d,RowTo=%d,Datesep=%s,FilePath=%s,FileName=%s]" % (type, RowFrom, RowTo, Datesep, FilePath, FileName)

	# RD5SaveAsCatalogEx
	CatalogPath = PathOut
	CatalogName = "RD5SaveAsCatalogEx"
	SourcePath  = PathOut
	SourceName  = SampleSrcData
	ret = lfmtblpy.RD5SaveAsCatalogEx(TableID, SetID, IDList.getPtr(), type, RowFrom, RowTo, ord(Datesep), CatalogPath.encode(ENC_OS), CatalogName.encode(ENC_OS)\
									, SourcePath.encode(ENC_OS), SourceName.encode(ENC_OS))
	print "[RD5SaveAsCatalogEx] retval = %d [TableID=%d,SetID=%d,IDList=" % (ret, TableID, SetID)\
		, Array2List(IDList, nFlt)\
		, ",type=%d,RowFrom=%d,RowTo=%d,Datesep=%s,CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s]"\
			% (type, RowFrom, RowTo, Datesep, CatalogPath, CatalogName, SourcePath, SourceName)

	# RD5SaveAsCatalogwithF → 未サポート
	# RD5SaveAsCatalogwithFEx → 未サポート

	# RD5ExportAsCSV
	DBPath  = PathOut
	DBName  = "ExportAsCSV.csv"
	ret = lfmtblpy.RD5ExportAsCSV(TableID, SetID, IDList.getPtr(), RowFrom, RowTo, ord(Datesep), DBPath.encode(ENC_OS), DBName.encode(ENC_OS))
	print "[RD5ExportAsCSV] retval = %d [TableID=%d,SetID=%d,IDList=" % (ret, TableID, SetID)\
		, Array2List(IDList, nFlt)\
		, ",RowFrom=%d,RowTo=%d,Datesep=%s,DBPath=%s,DBName=%s]" % (RowFrom, RowTo, Datesep, DBPath, DBName)

	# RD5ExportAsCSVwithF → 未サポート

	# RD5ExportAsTAB
	DBPath  = PathOut
	DBName  = "ExportAsTAB.csv"
	ret = lfmtblpy.RD5ExportAsTAB(TableID, SetID, IDList.getPtr(), RowFrom, RowTo, ord(Datesep), DBPath.encode(ENC_OS), DBName.encode(ENC_OS))
	print "[RD5ExportAsTAB] retval = %d [TableID=%d,SetID=%d,IDList=" % (ret, TableID, SetID)\
		, Array2List(IDList, nFlt)\
		, ",RowFrom=%d,RowTo=%d,Datesep=%s,DBPath=%s,DBName=%s]" % (RowFrom, RowTo, Datesep, DBPath, DBName)

	# RD5ExportAsTABwithF → 未サポート

	# RD5GetTableMemorySize
	ret = lfmtblpy.RD5GetTableMemorySize(TableID)
	print "[RD5GetTableMemorySize] retval = %d [TableID=%d]" % (ret, TableID)

	print "### %s ### end" % funcName
	return

## 6-3-5 順序付き集合管理機能
def testSet():
	funcName = "testSet"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile_MS
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5GetNSet
	TableID = 1
	ret = lfmtblpy.RD5GetNSet(TableID)
	print "[RD5GetNSet] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5GetTotalRows
	ret = lfmtblpy.RD5GetTotalRows(TableID)
	print "[RD5GetTotalRows] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5GetSetSize
	SetID = 1
	ret = lfmtblpy.RD5GetSetSize(TableID, SetID)
	print "[RD5GetSetSize] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5PurgeSubsets
	ret = lfmtblpy.RD5PurgeSubsets(TableID)
	print "[RD5PurgeSubsets] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5GetSet → 未サポート

	# RD5GetSetName -> RD5GetSetNameR1
	ret = lfmtblpy.RD5GetSetNameR1(TableID, SetID)
	print "[RD5GetSetNameR1] Name = %s [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5SetSetName
	Name = "RD5SetSetName"
	ret = lfmtblpy.RD5SetSetName(TableID, SetID, Name.encode(ENC_DB))
	print "[RD5SetSetName] retval = %d [TableID=%d,SetID=%d,Name=%s]" % (ret, TableID, SetID, Name)

	# RD5GetSetName -> RD5GetSetNameR1（確認）
	ret = lfmtblpy.RD5GetSetNameR1(TableID, SetID)
	print "[RD5GetSetNameR1] Name = %s [TableID=%d,SetID=%d]" % (ret, TableID, SetID)


	# reset
	ret = lfmtblpy.RD5ClearDB()
	Name = SampleD5DFile_JOIN
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# JOIN
	PCTblName		= "JoinTbl"
	IsOuter			= 0
	MasterTblID		= 1
	MasterSetID		= 1
	#nFlt 			= lfmtblpy.D5_MAX_JOIN_KEY
	nFlt 			= 2
	MasterFltIDs	= lfmutilpy.CTypeIntAr(nFlt)
	MasterFltIDs.put(0, 2)
	MasterFltIDs.put(1, 0)
	SlaveTblID		= 2
	SlaveSetID		= 1
	SlaveFltIDs		= lfmutilpy.CTypeIntAr(nFlt)
	SlaveFltIDs.put(0, 1)
	SlaveFltIDs.put(1, 0)
	ret = lfmtblpy.RD5AddJoinTable(PCTblName, IsOuter, MasterTblID, MasterSetID, MasterFltIDs.getPtr(), SlaveTblID, SlaveSetID, SlaveFltIDs.getPtr())
	print "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs="\
		% (ret, PCTblName, IsOuter, MasterTblID, MasterSetID)\
		, Array2List(MasterFltIDs, nFlt)\
		, ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=" % (SlaveTblID, SlaveSetID)\
		, Array2List(SlaveFltIDs, nFlt), "]"

	TableID	= ret
	SetID	= -1

	# RD5GetJoinSlaveSet → 未サポート

	# RD5GetJoinDir
	ret = lfmtblpy.RD5GetJoinDir(TableID, SetID)
	print "[RD5GetJoinDir] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5GetJoinProjectionSets
	MasterSize	= lfmutilpy.CTypeIntAr(1)
	MGetCount	= 20
	MSetArray	= lfmutilpy.CTypeIntAr(MGetCount)
	SlaveSize	= lfmutilpy.CTypeIntAr(1)
	SGetCount	= 20
	SSetArray	= lfmutilpy.CTypeIntAr(SGetCount)
	ret = lfmtblpy.RD5GetJoinProjectionSets(TableID, SetID, MasterSize.getPtr(), MGetCount, MSetArray.getPtr(), SlaveSize.getPtr(), SGetCount, SSetArray.getPtr())
	print "[RD5GetJoinProjectionSets] retval = %d [TableID=%d,SetID=%d,MasterSize=%d,MGetCount=%d,SlaveSize=%d,SGetCount=%d]"\
		% (ret, TableID, SetID, MasterSize.at(0), MGetCount, SlaveSize.at(0), SGetCount)
	print " MSetArray = ", Array2List(MSetArray, MasterSize.at(0))
	print " SSetArray = ", Array2List(SSetArray, SlaveSize.at(0))

	# RD5PutJoinSetToParent <- 後から移動
	PutSlave		= 1
	PutJoinOut		= 1
	TargetTableID	= lfmutilpy.CTypeIntAr(1)
	TargetSetID		= lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5PutJoinSetToParent(TableID, PutSlave, PutJoinOut, TargetTableID.getPtr(), TargetSetID.getPtr())
	print "[RD5PutJoinSetToParent] retval = %d [JTableID=%d,PutSlave=%d,PutJoinOut=%d][TargetTableID=%d,TargetSetID=%d]"\
		% (ret, TableID, PutSlave, PutJoinOut, TargetTableID.at(0), TargetSetID.at(0))

	# RD5ReturnSet2SlaveTable <- 後から移動
	pTargetTableID = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5ReturnSet2SlaveTable(TableID, pTargetTableID.getPtr())
	print "[RD5ReturnSet2SlaveTable] retval = %d [TableID=%d][pTargetTableID=%d]" % (ret, TableID, pTargetTableID.at(0))


	# reset
	ret = lfmtblpy.RD5ClearDB()
	Name = SampleD5DFile_MS
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5GetSetList
	TableID = 1
	SetIDList = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_SET_COUNT)
	ret = lfmtblpy.RD5GetSetList(TableID, SetIDList.getPtr())
	print "[RD5GetSetList] retval = %d [TableID=%d,SetIDList=" % (ret, TableID), Array2List(SetIDList, ret), "]"
	nSet = ret

	# RD5GetSetIDList
	ret = lfmtblpy.RD5GetSetIDList(TableID, nSet, SetIDList.getPtr())
	print "[RD5GetSetIDList] retval = %d [TableID=%d,Size=%d,SetIDList=" % (ret, TableID, nSet), Array2List(SetIDList, ret), "]"

	# RD5AddSetReal → 未サポート

	# RD5DeleteSet
	SetID = 3
	ret = lfmtblpy.RD5DeleteSet(TableID, SetID)
	print "[RD5DeleteSet] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5GetCurrentSetID
	ret = lfmtblpy.RD5GetCurrentSetID(TableID)
	print "[RD5GetCurrentSetID] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5ChangeCurrentSetID
	NewSetID = 2
	ret = lfmtblpy.RD5ChangeCurrentSetID(TableID, NewSetID)
	print "[RD5ChangeCurrentSetID] retval = %d [TableID=%d,NewSetID=%d]" % (ret, TableID, NewSetID)

	# RD5GetCurrentSetID（確認）
	ret = lfmtblpy.RD5GetCurrentSetID(TableID)
	print "[RD5GetCurrentSetID] retval = %d [TableID=%d]" % (ret, TableID)

	# RD5SetNotReal
	SetID = 2
	ret = lfmtblpy.RD5SetNotReal(TableID, SetID)
	print "[RD5SetNotReal] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5SetOpeReal
	OpeNo = 1 # OR
	SetAID = 2
	SetBID = 4
	ret = lfmtblpy.RD5SetOpeReal(TableID, OpeNo, SetAID, SetBID)
	print "[RD5SetOpeReal] retval = %d [TableID=%d,OpeNo=%d,SetAID=%d,SetBID=%d]" % (ret, TableID, OpeNo, SetAID, SetBID)

	# RD5PutJoinSetToParent -> 前に移動
	# RD5ReturnSet2SlaveTable -> 前に移動

	# RD5GetSetMemorySize
	SetID = 5
	ret = lfmtblpy.RD5GetSetMemorySize(TableID, SetID)
	print "[RD5GetSetMemorySize] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5GetSubsetAttr
	ATTR_MAX = 8
	Attrs = lfmutilpy.CSubsetAttr()
	ret = Attrs.getAttr(TableID, SetID)
	print "[RD5GetSubsetAttr] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)
	for i in range(ATTR_MAX):
		print " Attrs.at(%d)=%d" % (i, Attrs.at(i))

	# RD5SetSubsetAttr
	idx = 5
	val = 6
	Attrs.put(idx, val)
	print " Attrs.put(%d, %d)" % (idx, val)
	ret = Attrs.setAttr(TableID, SetID)
	print "[RD5SetSubsetAttr] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)

	# RD5GetSubsetAttr（確認）
	ret = Attrs.getAttr(TableID, SetID)
	print "[RD5GetSubsetAttr] retval = %d [TableID=%d,SetID=%d]" % (ret, TableID, SetID)
	for i in range(ATTR_MAX):
		print " Attrs.at(%d)=%d" % (i, Attrs.at(i))

	print "### %s ### end" % funcName
	return

## 6-3-6 項目管理機能
def testFilter():
	funcName = "testFilter"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5GetNFilter
	TableID = 1
	ret = lfmtblpy.RD5GetNFilter(TableID)
	print "[RD5GetNFilter] retval = %d [TableID=%d]" % (ret, TableID)
	nFlt = ret

	# RD5GetFilterIDList
	IDList = lfmutilpy.CTypeIntAr(nFlt)
	ret = lfmtblpy.RD5GetFilterIDList(TableID, IDList.getPtr())
	print "[RD5GetFilterIDList] retval = %d [TableID=%d,IDList=" % (ret, TableID), Array2List(IDList, ret), "]"
	nFlt = ret

	# RD5GetFilterWidth
	for i in range(nFlt):
		ret = lfmtblpy.RD5GetFilterWidth(TableID, IDList.at(i))
		print "[RD5GetFilterWidth] retval = %d [TableID=%d,FltID=%d]" % (ret, TableID, IDList.at(i))

	# RD5GetFilterType
	for i in range(nFlt):
		ret = lfmtblpy.RD5GetFilterType(TableID, IDList.at(i))
		print "[RD5GetFilterType] retval = %d [TableID=%d,FltID=%d]" % (ret, TableID, IDList.at(i))

	# RD5GetFilterInfo
	for i in range(nFlt):
		FiltInfo = lfmtblpy.TRFilterInfo()
		ret = lfmtblpy.RD5GetFilterInfo(TableID, IDList.at(i), FiltInfo)
		print "[RD5GetFilterInfo] retval = %d [TableID=%d,FltID=%d][PVSize=%d,VLType=%d,VLWidth=%d,VLSize=%d,CharAreaSize=%d,FilterName=%s]"\
			% (ret, TableID, IDList.at(i), FiltInfo.PVSize, FiltInfo.VLType, FiltInfo.VLWidth, FiltInfo.VLSize, FiltInfo.CharAreaSize, FiltInfo.FilterName)

	# RD5GetFilterAttr
	ATTR_MAX = 8
	FilterID = 6 # double
	Attrs = lfmutilpy.CFilterAttr()
	ret = Attrs.getAttr(TableID, FilterID)
	print "[RD5GetFilterAttr] retval = %d [TableID=%d,FilterID=%d]" % (ret, TableID, FilterID)
	for i in range(ATTR_MAX):
		print " Attrs.at(%d)=%d" % (i, Attrs.at(i))

	# RD5SetFilterAttr
	idx = 5 # 浮動小数項目の小数点以下グリッド表示桁数
	val = 6 # 桁数-3
	Attrs.put(idx, val)
	print " Attrs.put(%d, %d)" % (idx, val)
	ret = Attrs.setAttr(TableID, FilterID)
	print "[RD5SetFilterAttr] retval = %d [TableID=%d,FilterID=%d]" % (ret, TableID, FilterID)

	# RD5GetFilterAttr（確認）
	ret = Attrs.getAttr(TableID, FilterID)
	print "[RD5GetFilterAttr] retval = %d [TableID=%d,FilterID=%d]" % (ret, TableID, FilterID)
	for i in range(ATTR_MAX):
		print " Attrs.at(%d)=%d" % (i, Attrs.at(i))

	# RD5DeleteRealFilter -> 後に移動

	# RD5MoveRealFilter
	FromIndex = 0
	ToIndex = nFlt
	for i in range(3):
		ret = lfmtblpy.RD5MoveRealFilter(TableID, FromIndex, ToIndex)
		print "[RD5MoveRealFilter] retval = %d [TableID=%d,FromIndex=%d,ToIndex=%d]" % (ret, TableID, FromIndex, ToIndex)

	# RD5DupRealFilter
	for i in range(nFlt):
		ret = lfmtblpy.RD5DupRealFilter(TableID, IDList.at(i))
		print "[RD5DupRealFilter] retval = %d [TableID=%d,FltID=%d]" % (ret, TableID, IDList.at(i))

	# RD5DupRealFilterEx
	for i in range(nFlt):
		DestType = lfmtblpy.D5_DT_STRING
		ret = lfmtblpy.RD5DupRealFilterEx(TableID, IDList.at(i), DestType)
		print "[RD5DupRealFilterEx] retval = %d [TableID=%d,FltID=%d,DestType=%d]" % (ret, TableID, IDList.at(i), DestType)

	# RD5DupRealFilterExNumeric
	SrcFltID  = 16
	Scale     = 20
	RoundMode = 6
	ret = lfmtblpy.RD5DupRealFilterExNumeric(TableID, SrcFltID, Scale, RoundMode)
	print "[RD5DupRealFilterExNumeric] retval = %d [TableID=%d,SrcFltID=%d,Scale=%d,RoundMode=%d]" % (ret, TableID, SrcFltID, Scale, RoundMode)

	# RD5AddRealFilter2
	Loc           = 0
	FilterName    = "add_dbl"
	DataTypeNo    = lfmtblpy.D5_DT_DOUBLE
	DataArraySize = 10
	DataUnitSize  = 4
	FilePath      = PathIn
	FileName      = SampleFilterData
	ret = lfmtblpy.RD5AddRealFilter2(TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath, FileName)

	# RD5AddRealFilter2Numeric
	FilterName   = "add_num"
	DataTypeNo   = lfmtblpy.D5_DT_DECIMAL
	DataUnitSize = 16
	Scale        = 3
	RoundMode    = 4
	ret = lfmtblpy.RD5AddRealFilter2Numeric(TableID, Loc, FilterName, DataArraySize, Scale, RoundMode, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2Numeric] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataArraySize=%d,Scale=%d,RoundMode=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataArraySize, Scale, RoundMode, FilePath, FileName)

	# RD5DeleteRealFilter
	FltID = 20
	ret = lfmtblpy.RD5DeleteRealFilter(TableID, FltID)
	print "[RD5DeleteRealFilter] retval = %d [TableID=%d,FltID=%d]" % (ret, TableID, FltID)

	# RD5GetSlaveInfo -> 後に移動
	# RD5MoveSlaveFlt2Master -> 後に移動

	# RD5GetFilterIDFromName
	FilterName = "add_num"
	ret = lfmtblpy.RD5GetFilterIDFromName(TableID, FilterName)
	print "[RD5GetFilterIDFromName] retval = %d [TableID=%d,FilterName=%s]" % (ret, TableID, FilterName)
	FilterID = ret

	# RD5GetFilterIDFromName2
	isSlave = 0
	ret = lfmtblpy.RD5GetFilterIDFromName2(TableID, isSlave, FilterName)
	print "[RD5GetFilterIDFromName2] retval = %d [TableID=%d,isSlave=%d,FilterName=%s]" % (ret, TableID, isSlave, FilterName)

	# RD5SetFilterName
	FilterName = "add_num_RN"
	ret = lfmtblpy.RD5SetFilterName(TableID, FilterID, FilterName)
	print "[RD5SetFilterName] retval = %d [TableID=%d,FilterID=%d,FilterName=%s]" % (ret, TableID, FilterID, FilterName)

	# RD5GetFilterName -> RD5GetFilterNameR1
	ret = lfmtblpy.RD5GetFilterNameR1(TableID, FilterID).decode(ENC_DB)
	print "[RD5GetFilterNameR1] retval = %s [TableID=%d,FilterID=%d]" % (ret, TableID, FilterID)

	# RD5GetFilterMemorySize
	ret = lfmtblpy.RD5GetFilterMemorySize(TableID, FilterID)
	print "[RD5GetFilterMemorySize] retval = %d [TableID=%d,FilterID=%d]" % (ret, TableID, FilterID)

	# RD5GetAllFilterInfo → 未サポート

	# RD5SetNumericInfo
	NInfo = lfmutilpy.CNumericInfo(10, 6)
	ret = lfmtblpy.RD5SetNumericInfo(TableID, FilterID, NInfo.getPtr())
	print "[RD5SetNumericInfo] retval = %d [TableID=%d,FilterID=%d,scale=%d,rounding_mode=%d]"\
		% (ret, TableID, FilterID, NInfo.getScale(), NInfo.getRoundingMode())

	# RD5GetNumericInfo -> RD5GetNumericInfoR1
	ret = lfmtblpy.RD5GetNumericInfoR1(TableID, FilterID, NInfo.getPtr())
	print "[RD5GetNumericInfoR1] retval = %d [TableID=%d,FilterID=%d,scale=%d,rounding_mode=%d]"\
		% (ret, TableID, FilterID, NInfo.getScale(), NInfo.getRoundingMode())


	# reset
	ret = lfmtblpy.RD5ClearDB()
	Name = SampleD5DFile_JOIN
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# JOIN
	PCTblName		= "JoinTbl"
	IsOuter			= 0
	MasterTblID		= 1
	MasterSetID		= 1
	#nFlt = lfmtblpy.D5_MAX_JOIN_KEY
	nFlt = 2
	MasterFltIDs	= lfmutilpy.CTypeIntAr(nFlt)
	MasterFltIDs.put(0, 2)
	MasterFltIDs.put(1, 0)
	SlaveTblID		= 2
	SlaveSetID		= 1
	SlaveFltIDs		= lfmutilpy.CTypeIntAr(nFlt)
	SlaveFltIDs.put(0, 1)
	SlaveFltIDs.put(1, 0)
	ret = lfmtblpy.RD5AddJoinTable(PCTblName, IsOuter, MasterTblID, MasterSetID, MasterFltIDs.getPtr(), SlaveTblID, SlaveSetID, SlaveFltIDs.getPtr())
	print "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs="\
		% (ret, PCTblName, IsOuter, MasterTblID, MasterSetID)\
		, Array2List(MasterFltIDs, nFlt)\
		, ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=" % (SlaveTblID, SlaveSetID)\
		, Array2List(SlaveFltIDs, nFlt), "]"

	TableID	= ret
	SetID	= -1

	# RD5GetSlaveInfo <- 前から移動
	MasterTableID	= lfmutilpy.CTypeIntAr(1)
	MasterSetID		= lfmutilpy.CTypeIntAr(1)
	SlaveTableID	= lfmutilpy.CTypeIntAr(1)
	SlaveSetID		= lfmutilpy.CTypeIntAr(1)
	nSlaveFilters	= lfmutilpy.CTypeIntAr(1)
	SlaveFilterIDs	= lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_REAL)
	ret = lfmtblpy.RD5GetSlaveInfo(TableID, MasterTableID.getPtr(), MasterSetID.getPtr()\
								, SlaveTableID.getPtr(), SlaveSetID.getPtr(), nSlaveFilters.getPtr(), SlaveFilterIDs.getPtr())
	print "[RD5GetSlaveInfo] retval = %d [JoinTableID=%d][MasterTableID=%d,MasterSetID=%d,SlaveTableID=%d,SlaveSetID=%d,nSlaveFilters=%d,SlaveFilterIDs="\
		% (ret, TableID, MasterTableID.at(0), MasterSetID.at(0), SlaveTableID.at(0), SlaveSetID.at(0), nSlaveFilters.at(0))\
		, Array2List(SlaveFilterIDs, nSlaveFilters.at(0)), "]"

	# RD5MoveSlaveFlt2Master <- 前から移動
	SlaveFltID = 2
	ret = lfmtblpy.RD5MoveSlaveFlt2Master(TableID, SlaveFltID)
	print "[RD5MoveSlaveFlt2Master] retval = %d [JoinTableID=%d,SlaveFltID=%d]" % (ret, TableID, SlaveFltID)

	print "### %s ### end" % funcName
	return

## 6-3-7 値ジャンプ機能
def testFind():
	funcName = "testFind"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ENC_DB = "Shift_JIS"
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile_SJIS
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5FindRecNoReal
	RealTblID   = 1
	SetID       = -1
	TargetRecNo = 10
	ret = lfmtblpy.RD5FindRecNoReal(RealTblID, SetID, TargetRecNo)
	print "[RD5FindRecNoReal] retval = %d [RealTblID=%d,SetID=%d,TargetRecNo=%d]" % (ret, RealTblID, SetID, TargetRecNo)

	# RD5OpenStrFindReal
	SrchFltID   = 8
	StrSrchKind = lfmtblpy.D5_OPETYPE_STR_MID
	SrchStr1    = "t"
	SrchStr2    = ""
	ret = lfmtblpy.RD5OpenStrFindReal(RealTblID, SrchFltID, StrSrchKind, SrchStr1.encode(ENC_DB), SrchStr2.encode(ENC_DB))
	print "[RD5OpenStrFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s]"\
		% (ret, RealTblID, SrchFltID, StrSrchKind, SrchStr1, SrchStr2)

	# RD5OpenIntFindReal
	SrchFltID   = 1
	ValSrchKind = lfmtblpy.D5_OPETYPE_BETWEEN
	SrchVal1    = 3
	SrchVal2    = 7
	ret = lfmtblpy.RD5OpenIntFindReal(RealTblID, SrchFltID, ValSrchKind, SrchVal1, SrchVal2)
	print "[RD5OpenIntFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%d,SrchVal2=%d]"\
		% (ret, RealTblID, SrchFltID, ValSrchKind, SrchVal1, SrchVal2)

	# RD5OpenFloatFindReal
	SrchFltID   = 6
	ValSrchKind = lfmtblpy.D5_OPETYPE_BETWEEN
	SrchVal1    = 0.3
	SrchVal2    = 0.7
	ret = lfmtblpy.RD5OpenFloatFindReal(RealTblID, SrchFltID, ValSrchKind, SrchVal1, SrchVal2)
	print "[RD5OpenFloatFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%f,SrchVal2=%f]"\
		% (ret, RealTblID, SrchFltID, ValSrchKind, SrchVal1, SrchVal2)

	# RD5GetFindStatus
	nHit = lfmutilpy.CTypeIntAr(1)
	FindFltID = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5GetFindStatus(RealTblID, nHit.getPtr(), FindFltID.getPtr())
	print "[RD5GetFindStatus] retval = %d [RealTblID=%d,nHit=%d,FindFltID=%d]"\
		% (ret, RealTblID, nHit.at(0), FindFltID.at(0))
	SrchID = ret

	# RD5GetNextHitReal
	CurPos  = 0
	Dir     = 0
	FltID   = lfmutilpy.CTypeIntAr(1)
	NextPos = lfmutilpy.CTypeIntAr(1)
	while ret > 0:
		ret = lfmtblpy.RD5GetNextHitReal(RealTblID, SrchID, SetID, CurPos, Dir, FltID.getPtr(), NextPos.getPtr())
		print "[RD5GetNextHitReal] retval = %d [RealTblID=%d,SrchID=%d,SetID=%d,CurPos=%d,Dir=%d,FltID=%d,NextPos=%d]"\
			% (ret, RealTblID, SrchID, SetID, CurPos, Dir, FltID.at(0), NextPos.at(0))
		CurPos = NextPos.at(0)

	# RD5CloseFindReal
	ret = lfmtblpy.RD5CloseFindReal(RealTblID)
	print "[RD5CloseFindReal] retval = %d [RealTblID=%d]" % (ret, RealTblID)

	# RD5OpenStrFindRealLocale
	SrchFltID   = 2
	StrSrchKind = lfmtblpy.D5_OPETYPE_BETWEEN
	SrchStr1    = u"０３"
	SrchStr2    = u"０７"
	LocaleID    = 0
	ret = lfmtblpy.RD5OpenStrFindRealLocale(RealTblID, SrchFltID, StrSrchKind, SrchStr1.encode(ENC_DB), SrchStr2.encode(ENC_DB), LocaleID)
	print "[RD5OpenStrFindRealLocale] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s,LocaleID=%d]"\
		% (ret, RealTblID, SrchFltID, StrSrchKind, SrchStr1, SrchStr2, LocaleID)

	# RD5OpenStrFindRealSJIS
	ret = lfmtblpy.RD5OpenStrFindRealSJIS(RealTblID, SrchFltID, StrSrchKind, SrchStr1.encode(ENC_DB), SrchStr2.encode(ENC_DB))
	print "[RD5OpenStrFindRealSJIS] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s]"\
		% (ret, RealTblID, SrchFltID, StrSrchKind, SrchStr1, SrchStr2)

	# RD5OpenNumericFindReal
	SrchFltID    = 7
	ValSrchKind  = lfmtblpy.D5_OPETYPE_BETWEEN
	SrchVal1     = "0.03"
	SrchVal2     = "0.07"
	NInfo = lfmutilpy.CNumericInfo()
	ret = lfmtblpy.RD5GetNumericInfoR1(RealTblID, SrchFltID, NInfo.getPtr())
	nSrchVal1 = lfmutilpy.CNumeric(SrchVal1, NInfo.getScale(), NInfo.getRoundingMode())
	nSrchVal2 = lfmutilpy.CNumeric(SrchVal2, NInfo.getScale(), NInfo.getRoundingMode())
	ret = lfmtblpy.RD5OpenNumericFindReal(RealTblID, SrchFltID, ValSrchKind, nSrchVal1.getPtr(), nSrchVal2.getPtr())
	print "[RD5OpenNumericFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%s,SrchVal2=%s]"\
		% (ret, RealTblID, SrchFltID, ValSrchKind, SrchVal1, SrchVal2)

	print "### %s ### end" % funcName
	return

## 6-3-8 数値のカテゴライズ
def testCategory():
	funcName = "testCategory"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# カテゴリ定義テーブル作成 開始 --------------------------------------------------
	# Table
	PCTblName = "CATEGORY_TABLE"
	RowCount  = 3
	ret = lfmtblpy.RD5AddRealTable(PCTblName, RowCount)
	print "[RD5AddRealTable] retval = %d [PCTblName=%s,RowCount=%d]" % (ret, PCTblName, RowCount)
	TableID = ret
	SetID   = 1
	DataArraySize = RowCount

	# オペコード項目
	Loc = 0
	FilterName   = u"オペコード"
	DataTypeNo   = lfmtblpy.D5_DT_STRING
	DataUnitSize = 0
	FilePath     = ""
	FileName     = ""
	ret = lfmtblpy.RD5AddRealFilter2(TableID, Loc, FilterName.encode(ENC_DB), DataTypeNo, DataArraySize, DataUnitSize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath, FileName)
	FltID = ret
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 1, "<")
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 2, "<=>")
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 3, ">")

	# 第1引数
	Loc = 1
	FilterName   = u"第1引数"
	DataTypeNo   = lfmtblpy.D5_DT_DOUBLE
	DataUnitSize = 4
	ret = lfmtblpy.RD5AddRealFilter2(TableID, Loc, FilterName.encode(ENC_DB), DataTypeNo, DataArraySize, DataUnitSize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath, FileName)
	FltID = ret
	ret = lfmtblpy.RD5OverwriteRealExDblR1(TableID, SetID, FltID, 1, 3)
	ret = lfmtblpy.RD5OverwriteRealExDblR1(TableID, SetID, FltID, 2, 3)
	ret = lfmtblpy.RD5OverwriteRealExDblR1(TableID, SetID, FltID, 3, 7)

	# 第2引数
	Loc = 2
	FilterName   = u"第2引数"
	DataTypeNo   = lfmtblpy.D5_DT_DOUBLE
	DataUnitSize = 4
	ret = lfmtblpy.RD5AddRealFilter2(TableID, Loc, FilterName.encode(ENC_DB), DataTypeNo, DataArraySize, DataUnitSize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath, FileName)
	FltID = ret
	ret = lfmtblpy.RD5OverwriteRealExDblR1(TableID, SetID, FltID, 2, 7)

	# 分類名称
	Loc = 3
	FilterName   = u"分類名称"
	DataTypeNo   = lfmtblpy.D5_DT_STRING
	DataUnitSize = 0
	ret = lfmtblpy.RD5AddRealFilter2(TableID, Loc, FilterName.encode(ENC_DB), DataTypeNo, DataArraySize, DataUnitSize, FilePath.encode(ENC_OS), FileName.encode(ENC_OS))
	print "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]"\
		% (ret, TableID, Loc, FilterName, DataTypeNo, DataArraySize, DataUnitSize, FilePath, FileName)
	FltID = ret
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 1, u"～2".encode(ENC_DB))
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 2, u"3～7".encode(ENC_DB))
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, 3, u"8～".encode(ENC_DB))
	# カテゴリ定義テーブル作成 終了 --------------------------------------------------

	# RD5AddCategoryReal
	TargetTblID   = 1
	TargetFltID   = 1
	CategoryTblID = TableID
	ret = lfmtblpy.RD5AddCategoryReal(TargetTblID, TargetFltID, CategoryTblID)
	print "[RD5AddCategoryReal] retval = %d [TargetTblID=%d,TargetFltID=%d,CategoryTblID=%d]" % (ret, TargetTblID, TargetFltID, CategoryTblID)

	print "### %s ### end" % funcName
	return

## 6-3-9 計算機能
def testCalc():
	funcName = "testCalc"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5CalcReal
	TargetTblID = 1
	TargetSetID = -1
	TargetFID   = 7
	CalStart    = 1
	CalCount    = 10
	PCFormula   = "+(@int,@dbl)"
	ErrorRep    = "                                                                "
	ret = lfmtblpy.RD5CalcReal(TargetTblID, TargetSetID, TargetFID, CalStart, CalCount, PCFormula, ErrorRep)
	print "[RD5CalcReal] retval = %d [TargetTblID=%d,TargetSetID=%d,TargetFID=%d,CalStart=%d,CalCount=%d,PCFormula=%s,ErrorRep=%s]"\
		% (ret, TargetTblID, TargetSetID, TargetFID, CalStart, CalCount, PCFormula, ErrorRep)

	print "### %s ### end" % funcName
	return

## 6-3-10 編集機能
def testEdit():
	funcName = "testEdit"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5TableCanEdit
	TableID = 1
	PReferIDs = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_TABLE_COUNT)
	ret = lfmtblpy.RD5TableCanEdit(TableID, PReferIDs.getPtr())
	print "[RD5TableCanEdit] retval = %d [TableID=%d,PReferIDs=" % (ret, TableID), Array2List(PReferIDs, ret), "]"

	# RD5DeleteRealRows
	DelStart = 5
	DelCount = 3
	ret = lfmtblpy.RD5DeleteRealRows(TableID, DelStart, DelCount)
	print "[RD5DeleteRealRows] retval = %d [TableID=%d,DelStart=%d,DelCount=%d]" % (ret, TableID, DelStart, DelCount)

	# RD5DeleteRealRowsEx
	SetID = 1
	ret = lfmtblpy.RD5DeleteRealRowsEx(TableID, SetID, DelStart, DelCount)
	print "[RD5DeleteRealRowsEx] retval = %d [TableID=%d,SetID=%d,DelStart=%d,DelCount=%d]" % (ret, TableID, SetID, DelStart, DelCount)

	# RD5InsertRealRows
	InsPos   = 5
	InsCount = 6
	ret = lfmtblpy.RD5InsertRealRows(TableID, InsPos, InsCount)
	print "[RD5InsertRealRows] retval = %d [TableID=%d,InsPos=%d,InsCount=%d]" % (ret, TableID, InsPos, InsCount)


	RowCount = 10

	# RD5OverwriteRealEx
	TableID		= 1
	SetID		= 1
	WriteStart	= 1
	WriteCount	= 10

	# int
	FltID = 1
	PWData = lfmutilpy.CTypeIntAr(WriteCount)
	for i in range(WriteCount):
		PWData.put(i, i + 10)
	ret = lfmtblpy.RD5OverwriteRealEx(TableID, SetID, FltID, WriteStart, WriteCount, PWData.getVPtr())
	print "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount)

	# double
	FltID = 6
	PWData = lfmutilpy.CTypeDblAr(WriteCount)
	for i in range(WriteCount):
		PWData.put(i, i + 10.0)
	ret = lfmtblpy.RD5OverwriteRealEx(TableID, SetID, FltID, WriteStart, WriteCount, PWData.getVPtr())
	print "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount)

	# Numeric
	FltID = 7
	NInfo = lfmutilpy.CNumericInfo()
	ret = lfmtblpy.RD5GetNumericInfoR1(TableID, FltID, NInfo.getPtr())
	PWData = lfmutilpy.CTypeNumAr(WriteCount, NInfo.getScale(), NInfo.getRoundingMode())
	for i in range(WriteCount):
		PWData.put(i, str(i + 10))
	ret = lfmtblpy.RD5OverwriteRealEx(TableID, SetID, FltID, WriteStart, WriteCount, PWData.getVPtr())
	print "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount)

	# string
	FltID = 2
	PWData = lfmutilpy.CTypeStrAr(WriteCount)
	for i in range(WriteCount):
		PWData.put(i, str(i + 10).encode(ENC_OS))
	ret = lfmtblpy.RD5OverwriteRealEx(TableID, SetID, FltID, WriteStart, WriteCount, PWData.getVPtr())
	print "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount)


	WritePos = 5

	# RD5OverwriteRealExIntR1
	FltID = 1
	nData = -WritePos
	ret = lfmtblpy.RD5OverwriteRealExIntR1(TableID, SetID, FltID, WritePos, nData)
	print "[RD5OverwriteRealExIntR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%d]"\
		% (ret, TableID, SetID, FltID, WritePos, nData)

	# RD5OverwriteRealExDblR1
	FltID = 6
	nData = float(-WritePos) / 10
	ret = lfmtblpy.RD5OverwriteRealExDblR1(TableID, SetID, FltID, WritePos, nData)
	print "[RD5OverwriteRealExDblR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%f]" % (ret, TableID, SetID, FltID, WritePos, nData)

	# RD5OverwriteRealExNumericR1
	FltID = 7
	sData = str(float(-WritePos) / 10)
	nData = lfmutilpy.CNumeric(sData, NInfo.getScale(), NInfo.getRoundingMode())
	ret = lfmtblpy.RD5OverwriteRealExNumericR1(TableID, SetID, FltID, WritePos, nData.getPtr())
	print "[RD5OverwriteRealExNumericR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%s]" % (ret, TableID, SetID, FltID, WritePos, sData)

	# RD5OverwriteRealExStrR1
	FltID = 2
	nData = str(float(-WritePos) / 10)
	ret = lfmtblpy.RD5OverwriteRealExStrR1(TableID, SetID, FltID, WritePos, nData)
	print "[RD5OverwriteRealExStrR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%s]" % (ret, TableID, SetID, FltID, WritePos, nData)


	WriteStart = 1
	WriteCount = RowCount

	# RD5FillRealEx -> RD5FillRealExIntR1
	FltID = 1
	nData = RowCount - 5
	ret = lfmtblpy.RD5FillRealExIntR1(TableID, SetID, FltID, WriteStart, WriteCount, nData)
	print "[RD5FillRealExIntR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%d]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount, nData)

	# RD5FillRealEx -> RD5FillRealExDblR1
	FltID = 6
	nData = (float(RowCount) - 5) / 10
	ret = lfmtblpy.RD5FillRealExDblR1(TableID, SetID, FltID, WriteStart, WriteCount, nData)
	print "[RD5FillRealExDblR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%f]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount, nData)

	# RD5FillRealEx -> RD5FillRealExNumericR1
	FltID = 7
	sData = str((float(RowCount) - 5) / 10)
	nData = lfmutilpy.CNumeric(sData, NInfo.getScale(), NInfo.getRoundingMode())
	ret = lfmtblpy.RD5FillRealExNumericR1(TableID, SetID, FltID, WriteStart, WriteCount, nData.getPtr())
	print "[RD5FillRealExNumericR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%s]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount, sData)

	# RD5FillRealEx -> RD5FillRealExStrR1
	FltID = 2
	nData = str((float(RowCount) - 5) / 10)
	ret = lfmtblpy.RD5FillRealExStrR1(TableID, SetID, FltID, WriteStart, WriteCount, nData)
	print "[RD5FillRealExStrR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%s]"\
		% (ret, TableID, SetID, FltID, WriteStart, WriteCount, nData)

	print "### %s ### end" % funcName
	return

## 6-3-11 データ取得機能
def testGetData():
	funcName = "testGetData"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	TableID  = 1
	SetID    = 1
	RowCount = 10

	# RD5GetData1 -> RD5GetData1IntR1
	FltID = 1
	for RowNo in range(1, RowCount + 1):
		ret = lfmtblpy.RD5GetData1IntR1(TableID, FltID, SetID, RowNo)
		print "[RD5GetData1IntR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]" % (ret, TableID, FltID, SetID, RowNo)

	# RD5GetData1 -> RD5GetData1DblR1
	FltID = 6
	for RowNo in range(1, RowCount + 1):
		ret = lfmtblpy.RD5GetData1DblR1(TableID, FltID, SetID, RowNo)
		print "[RD5GetData1DblR1] retval = %f [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]" % (ret, TableID, FltID, SetID, RowNo)

	# RD5GetData1 -> RD5GetData1NumericR1
	FltID = 7
	NInfo = lfmutilpy.CNumericInfo()
	ret = lfmtblpy.RD5GetNumericInfoR1(TableID, FltID, NInfo.getPtr())
	ndata = lfmutilpy.CNumeric()
	for RowNo in range(1, RowCount + 1):
		ret = lfmtblpy.RD5GetData1NumericR1(TableID, FltID, SetID, RowNo, ndata.getPtr())
		sdata = lfmtblpy.RD5NumericNum2StrR1(ndata.getPtr(), NInfo.getPtr(), 0, NInfo.getScale())
		data = decimal.Decimal(sdata)
		print "[RD5GetData1NumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,RowNo=%d,numVal=[%s]->[%f]]"\
			% (ret, TableID, FltID, SetID, RowNo, sdata, data)

	# RD5GetData1 -> RD5GetData1StrR1
	FltID = 2
	for RowNo in range(1, RowCount + 1):
		ret = lfmtblpy.RD5GetData1StrR1(TableID, FltID, SetID, RowNo).decode(ENC_DB)
		print "[RD5GetData1StrR1] retval = %s [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]"\
			% (ret, TableID, FltID, SetID, RowNo)


	RowNo = 1
	nGot = lfmutilpy.CTypeIntAr(1)
	MAX_CACHE = lfmtblpy.D5_MAX_CACHE

	# RD5GetData1M -> RD5GetData1MIntR1
	FltID = 1
	buf = lfmutilpy.CTypeIntAr(MAX_CACHE * 2)
	ret = lfmtblpy.RD5GetData1MIntR1(TableID, FltID, SetID, RowNo, nGot.getPtr(), buf.getPtr())
	print "[RD5GetData1MIntR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]"\
		% (ret, TableID, FltID, SetID, RowNo, nGot.at(0))
	print " buf = ", Array2List(buf, nGot.at(0))

	# RD5GetData1M -> RD5GetData1MDblR1
	FltID = 6
	buf = lfmutilpy.CTypeDblAr(MAX_CACHE)
	ret = lfmtblpy.RD5GetData1MDblR1(TableID, FltID, SetID, RowNo, nGot.getPtr(), buf.getPtr())
	print "[RD5GetData1MDblR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]"\
		% (ret, TableID, FltID, SetID, RowNo, nGot.at(0))
	print " buf = ", Array2List(buf, nGot.at(0))

	# RD5GetData1M -> RD5GetData1MNumericR1
	FltID = 7
	buf = lfmutilpy.CTypeNumAr(MAX_CACHE, NInfo.getScale(), NInfo.getRoundingMode())
	ret = lfmtblpy.RD5GetData1MNumericR1(TableID, FltID, SetID, RowNo, nGot.getPtr(), buf.getPtr())
	print "[RD5GetData1MNumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]"\
		% (ret, TableID, FltID, SetID, RowNo, nGot.at(0))
	print " buf = [",
	for i in range(nGot.at(0)):
		print buf.at(i),
	print "]"

	# RD5GetData1M -> RD5GetData1MStrR1
	FltID = 2
	offset	= lfmutilpy.CTypeIntAr(MAX_CACHE)
	buf		= lfmutilpy.CTypeCharAr(lfmtblpy.D5_MAX_STRING_SIZE)
	ret = lfmtblpy.RD5GetData1MStrR1(TableID, FltID, SetID, RowNo, nGot.getPtr(), offset.getPtr(), buf.getVPtr())
	print "[RD5GetData1MStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]"\
		% (ret, TableID, FltID, SetID, RowNo, nGot.at(0))
	print " offset = ", Array2List(offset, nGot.at(0))
	print " buf = [", 
	for i in range(nGot.at(0)):
		print "'%s'" % buf.getPtr(offset.at(i)).decode(ENC_DB),
	print "]"

	# RD5GetRowNo1
	Row1 = lfmutilpy.CTypeIntAr(MAX_CACHE)
	Row2 = lfmutilpy.CTypeIntAr(MAX_CACHE)
	for RowNo in range(1, RowCount + 1):
		ret = lfmtblpy.RD5GetRowNo1(TableID, SetID, RowNo, Row1.getPtr(), Row2.getPtr())
		print "[RD5GetRowNo1] retval = %d [TableID=%d,SetID=%d,RowNo=%d][Row1=%d,Row2=%d]" % (ret, TableID, SetID, RowNo, Row1.at(0), Row2.at(0))

	# RD5GetRowNo1M
	RowNo = 1
	ret = lfmtblpy.RD5GetRowNo1M(TableID, SetID, RowNo, nGot.getPtr(), Row1.getPtr(), Row2.getPtr())
	print "[RD5GetRowNo1M] retval = %d [TableID=%d,SetID=%d,RowNo=%d][nGot=%d]" % (ret, TableID, SetID, RowNo, nGot.at(0))
	for i in range(nGot.at(0)):
		print " [%d] Row1=%d,Row2=%d" % (i, Row1.at(i), Row2.at(i))

	# RD5ExtractUniqueReal
	FltIDs = lfmutilpy.CTypeIntAr(lfmtblpy.D5_MAX_FILTER_COUNT_REAL)
	FltIDs.put(0, 1)
	FltIDs.put(1, 0)
	ConserveOriginalOrder = 1
	ret = lfmtblpy.RD5ExtractUniqueReal(0, TableID, SetID, FltIDs.getPtr(), ConserveOriginalOrder)
	print "[RD5ExtractUniqueReal] retval = %d [TableID=%d,SetID=%d,FltIDs=" % (ret, TableID, SetID),
	print Array2List(FltIDs, 2),
	print ",ConserveOriginalOrder=%d]" % ConserveOriginalOrder

	print "### %s ### end" % funcName
	return

## 6-3-12 検索機能
def testSearch():
	funcName = "testSearch"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	TableID  = 1
	SetID    = 1
	OpeNo    = lfmtblpy.D5_OPETYPE_BETWEEN
	LocaleID = lfmtblpy.D5_LOCALE_UTF8
	ix = 3
	iy = 7

	# RD5SearchByDispRowNoReal
	ret = lfmtblpy.RD5SearchByDispRowNoReal(TableID, SetID, OpeNo, ix, iy)
	print "[RD5SearchByDispRowNoReal] retval = %d [TableID=%d,SetID=%d,OpeNo=%d,ix=%d,iy=%d]" % (ret, TableID, SetID, OpeNo, ix, iy)

	# RD5SearchByRowNo
	TableNo = 0
	ret = lfmtblpy.RD5SearchByRowNo(TableID, TableNo, SetID, OpeNo, ix, iy)
	print "[RD5SearchByRowNo] retval = %d [TableID=%d,TableNo=%d,SetID=%d,OpeNo=%d,ix=%d,iy=%d]" % (ret, TableID, TableNo, SetID, OpeNo, ix, iy)

	# RD5SearchByField -> RD5SearchByFieldIntR1
	FltID = 1
	pcX   = 3
	pcY   = 7
	ret = lfmtblpy.RD5SearchByFieldIntR1(TableID, FltID, SetID, OpeNo, pcX, pcY)
	print "[RD5SearchByFieldIntR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%d,pcY=%d]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByField -> RD5SearchByFieldDblR1
	FltID = 6
	pcX   = 0.3
	pcY   = 0.7
	ret = lfmtblpy.RD5SearchByFieldDblR1(TableID, FltID, SetID, OpeNo, pcX, pcY)
	print "[RD5SearchByFieldDblR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%f,pcY=%f]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByField -> RD5SearchByFieldNumericR1
	FltID = 7
	pcX   = "0.03"
	pcY   = "0.07"
	NInfo = lfmutilpy.CNumericInfo()
	ret   = lfmtblpy.RD5GetNumericInfoR1(TableID, FltID, NInfo.getPtr())
	pcX_Num = lfmutilpy.CNumeric(pcX, NInfo.getScale(), NInfo.getRoundingMode())
	pcY_Num = lfmutilpy.CNumeric(pcY, NInfo.getScale(), NInfo.getRoundingMode())
	ret = lfmtblpy.RD5SearchByFieldNumericR1(TableID, FltID, SetID, OpeNo, pcX_Num.getPtr(), pcY_Num.getPtr())
	print "[RD5SearchByFieldNumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByField -> RD5SearchByFieldStrR1
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldStrR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB))
	print "[RD5SearchByFieldStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByFieldSJIS -> RD5SearchByFieldLocaleに統合
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldSJISR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB))
	print "[RD5SearchByFieldSJISR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByFieldLocale -> RD5SearchByFieldLocaleR1
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldLocaleR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB), LocaleID)
	print "[RD5SearchByFieldLocaleR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s,LocaleID=%s]"\
		% (ret, TableID, FltID, SetID, OpeNo, pcX, pcY, LocaleID)

	# RD5SearchByText
	Text = "int BETWEEN 3 AND 7"
	ret = lfmtblpy.RD5SearchByText(TableID, SetID, Text)
	print "[RD5SearchByText] retval = %d [TableID=%d,FltID=%d,SetID=%d,Text=%s]" % (ret, TableID, FltID, SetID, Text)

	# RD5SearchByTextSJIS
	Text = u"str BETWEEN '０３' AND '０７'"
	ret = lfmtblpy.RD5SearchByTextSJIS(TableID, SetID, Text.encode(ENC_DB))
	print "[RD5SearchByTextSJIS] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s]" % (ret, TableID, FltID, SetID, Text)

	# RD5SearchByTextLocale
	Text = u"str BETWEEN '０３' AND '０７'"
	ret = lfmtblpy.RD5SearchByTextLocale(TableID, SetID, Text.encode(ENC_DB), LocaleID)
	print "[RD5SearchByTextLocale] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s,LocaleID=%d]" % (ret, TableID, FltID, SetID, Text, LocaleID)

	# RD5SearchByFieldWildCard
	pc = u"*０*"
	ret = lfmtblpy.RD5SearchByFieldWildCard(TableID, FltID, SetID, pc.encode(ENC_DB))
	print "[RD5SearchByFieldWildCard] retval = %d [TableID=%d,FltID=%d,SetID=%d,pc=%s]" % (ret, TableID, FltID, SetID, pc)

	# RD5HighSpeedSearchSetMark
	mark = 1
	ret = lfmtblpy.RD5HighSpeedSearchSetMark(TableID, FltID, SetID, mark)
	print "[RD5HighSpeedSearchSetMark] retval = %d [TableID=%d,SetID=%d,FilterID=%d,mark=%d]" % (ret, TableID, FltID, SetID, mark)

	# RD5HighSpeedSearchHasMark
	ret = lfmtblpy.RD5HighSpeedSearchHasMark(TableID, FltID, SetID)
	print "[RD5HighSpeedSearchHasMark] retval = %d [TableID=%d,SetID=%d,FilterID=%d]" % (ret, TableID, FltID, SetID)

	# RD5HighSpeedSearchEnable
	enable = 1
	ret = lfmtblpy.RD5HighSpeedSearchEnable(TableID, FltID, enable)
	print "[RD5HighSpeedSearchEnable] retval = %d [TableID=%d,FilterID=%d,enable=%d]" % (ret, TableID, FltID, enable)

	# RD5HighSpeedSearchIsEnabled
	ret = lfmtblpy.RD5HighSpeedSearchIsEnabled(TableID, FltID)
	print "[RD5HighSpeedSearchIsEnabled] retval = %d [TableID=%d,FilterID=%d]" % (ret, TableID, FltID)

	print "### %s ### end" % funcName
	return

def testSearchSJIS():
	funcName = "testSearchSJIS"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ENC_DB = "Shift_JIS"
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile_SJIS
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	TableID  = 1
	SetID    = 1
	OpeNo    = lfmtblpy.D5_OPETYPE_BETWEEN
	LocaleID = lfmtblpy.D5_LOCALE_SJIS

	# RD5SearchByField -> RD5SearchByFieldStrR1
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldStrR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB))
	print "[RD5SearchByFieldStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByFieldSJIS -> RD5SearchByFieldLocaleに統合
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldSJISR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB))
	print "[RD5SearchByFieldSJISR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]" % (ret, TableID, FltID, SetID, OpeNo, pcX, pcY)

	# RD5SearchByFieldLocale -> RD5SearchByFieldLocaleR1
	FltID = 2
	pcX   = u"０３"
	pcY   = u"０７"
	ret = lfmtblpy.RD5SearchByFieldLocaleR1(TableID, FltID, SetID, OpeNo, pcX.encode(ENC_DB), pcY.encode(ENC_DB), LocaleID)
	print "[RD5SearchByFieldLocaleR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s,LocaleID=%s]"\
		% (ret, TableID, FltID, SetID, OpeNo, pcX, pcY, LocaleID)

	# RD5SearchByText
	Text = "int BETWEEN 3 AND 7"
	ret = lfmtblpy.RD5SearchByText(TableID, SetID, Text)
	print "[RD5SearchByText] retval = %d [TableID=%d,FltID=%d,SetID=%d,Text=%s]" % (ret, TableID, FltID, SetID, Text)

	# RD5SearchByTextSJIS
	Text = u"str BETWEEN '０３' AND '０７'"
	ret = lfmtblpy.RD5SearchByTextSJIS(TableID, SetID, Text.encode(ENC_DB))
	print "[RD5SearchByTextSJIS] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s]" % (ret, TableID, FltID, SetID, Text)

	# RD5SearchByTextLocale
	Text = u"str BETWEEN '０３' AND '０７'"
	ret = lfmtblpy.RD5SearchByTextLocale(TableID, SetID, Text.encode(ENC_DB), LocaleID)
	print "[RD5SearchByTextLocale] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s,LocaleID=%d]" % (ret, TableID, FltID, SetID, Text, LocaleID)

	# RD5SearchByFieldWildCard
	pc = u"*０*"
	ret = lfmtblpy.RD5SearchByFieldWildCard(TableID, FltID, SetID, pc.encode(ENC_DB))
	print "[RD5SearchByFieldWildCard] retval = %d [TableID=%d,FltID=%d,SetID=%d,pc=%s]" % (ret, TableID, FltID, SetID, pc)

	print "### %s ### end" % funcName
	return


## 6-3-13 ソート機能
def testSort():
	funcName = "testSort"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5SortByField
	TableID = 1
	FltID   = 1
	SetInID = -1
	SortDir = 0
	ret = lfmtblpy.RD5SortByField(TableID, FltID, SetInID, SortDir)
	print "[RD5SortByField] retval = %d [TableID=%d,FltID=%d,SetInID=%d,SortDir=%d]" % (ret, TableID, FltID, SetInID, SortDir)

	# RD5SortByRowNo
	TableNo = 0
	ret = lfmtblpy.RD5SortByRowNo(TableID, TableNo, SetInID, SortDir)
	print "[RD5SortByRowNo] retval = %d [TableID=%d,TableNo=%d,SetInID=%d,SortDir=%d]" % (ret, TableID, TableNo, SetInID, SortDir)

	print "### %s ### end" % funcName
	return

## 6-3-14 項目詳細情報取得機能
def testDetail():
	funcName = "testDetail"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5OpenDetailInfo
	TableID   = 1
	SetID     = 1
	FilterID  = 1 # int
	DataType  = lfmutilpy.CTypeIntAr(1)
	RangeSize = lfmutilpy.CTypeIntAr(1)
	nNonZero  = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5OpenDetailInfo(TableID, SetID, FilterID, DataType.getPtr(), RangeSize.getPtr(), nNonZero.getPtr())
	print "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]" \
		% (ret, TableID, SetID, FilterID, DataType.at(0), RangeSize.at(0), nNonZero.at(0))

	hDetail      = ret
	OrderByN     = 0
	Reverse      = 0
	ZeroSuppress = 0
	Row          = 11

	# RD5GetDetailValue
	Data = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5GetDetailValue(hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.getPtr(), Data.getPtr())
	print "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%d]"\
		% (ret, hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.at(0), Data.at(0))

	# RD5GetDetailCount
	Count = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5GetDetailCount(hDetail, OrderByN, Reverse, ZeroSuppress, Row, Count.getPtr())
	print "[RD5GetDetailCount] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][Count=%d]"\
		% (ret, hDetail, OrderByN, Reverse, ZeroSuppress, Row, Count.at(0))

	# RD5CloseDetailInfo
	ret = lfmtblpy.RD5CloseDetailInfo(hDetail)
	print "[RD5CloseDetailInfo] retval = %d [Handle=%d]" % (ret, hDetail)


	FilterID  = 6 # double
	ret = lfmtblpy.RD5OpenDetailInfo(TableID, SetID, FilterID, DataType.getPtr(), RangeSize.getPtr(), nNonZero.getPtr())
	print "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]"\
		% (ret, TableID, SetID, FilterID, DataType.at(0), RangeSize.at(0), nNonZero.at(0))
	hDetail = ret
	Data = lfmutilpy.CTypeDblAr(1)
	ret = lfmtblpy.RD5GetDetailValue(hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.getPtr(), Data.getPtr())
	print "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%f]"\
		% (ret, hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.at(0), Data.at(0))
	ret = lfmtblpy.RD5CloseDetailInfo(hDetail)
	print "[RD5CloseDetailInfo] retval = %d [Handle=%d]" % (ret, hDetail)


	FilterID  = 7 # Numeric
	ret = lfmtblpy.RD5OpenDetailInfo(TableID, SetID, FilterID, DataType.getPtr(), RangeSize.getPtr(), nNonZero.getPtr())
	print "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]" \
		% (ret, TableID, SetID, FilterID, DataType.at(0), RangeSize.at(0), nNonZero.at(0))
	hDetail = ret
	Data = lfmutilpy.CNumericInfoData()
	ret = lfmtblpy.RD5GetDetailValue(hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.getPtr(), Data.getPtr())
	print "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%s]"\
		% (ret, hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.at(0), Data.toString())
	ret = lfmtblpy.RD5CloseDetailInfo(hDetail)
	print "[RD5CloseDetailInfo] retval = %d [Handle=%d]" % (ret, hDetail)


	FilterID  = 2 # string
	ret = lfmtblpy.RD5OpenDetailInfo(TableID, SetID, FilterID, DataType.getPtr(), RangeSize.getPtr(), nNonZero.getPtr())
	print "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]" \
		% (ret, TableID, SetID, FilterID, DataType.at(0), RangeSize.at(0), nNonZero.at(0))
	hDetail = ret
	Data = lfmutilpy.CTypeCharAr(lfmtblpy.D5_MAX_STRING_SIZE)
	ret = lfmtblpy.RD5GetDetailValue(hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.getPtr(), Data.getVPtr())
	print "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%s]"\
		% (ret, hDetail, OrderByN, Reverse, ZeroSuppress, Row, DataType.at(0), Data.getPtr().decode(ENC_DB))
	ret = lfmtblpy.RD5CloseDetailInfo(hDetail)
	print "[RD5CloseDetailInfo] retval = %d [Handle=%d]" % (ret, hDetail)

	print "### %s ### end" % funcName
	return

## 6-3-15 集計機能
def testSum():
	funcName = "testSum"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	Name = SampleD5DFile
	ret = lfmtblpy.RD5LoadDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
	print "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

	# RD5NonCubeSum
	TableID = 1
	SetID   = 1
	nDim    = 1
	DimFltIDs = lfmutilpy.CTypeIntAr(1)
	DimFltIDs.put(0, 1)
	nMeasure  = 1
	MsrFltIDs = lfmutilpy.CTypeIntAr(nMeasure)
	MsrFltIDs.put(0, 1)
	SummaryTypes = lfmutilpy.CTypeIntAr(nMeasure)
	SummaryTypes.put(0, lfmtblpy.D5_SUMMARY_COUNT | lfmtblpy.D5_SUMMARY_MAX | lfmtblpy.D5_SUMMARY_MIN | lfmtblpy.D5_SUMMARY_SUM)
	FloatFormats = lfmutilpy.CTypeIntAr(1)
	ret = lfmtblpy.RD5NonCubeSum(TableID, SetID, nDim, DimFltIDs.getPtr(), nMeasure, MsrFltIDs.getPtr(), SummaryTypes.getPtr(), FloatFormats.getPtr())
	print "[RD5NonCubeSum] retval = %d [TableID=%d,SetID=%d,nDim=%d,nMeasure=%d]" % (ret, TableID, SetID, nDim, nMeasure)

	print "### %s ### end" % funcName
	return

## 6-3-16 データ変換処理機能
def testDB():
	funcName = "testDB"
	print "### %s ### start" % funcName

	# init
	ret = lfmtblpy.RD5ClearDB()

	# RD5SetDBCharCode
	ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
	print "[RD5SetDBCharCode] retval = %d [DBCode=%s]" % (ret, ENC_DB)

	# RD5GetD5DFileInfo
	DBPath = PathIn
	DBName = SampleD5DFile
	Env = lfmtblpy.D5FileInfo()
	ret = lfmtblpy.RD5GetD5DFileInfo(DBPath.encode(ENC_OS), DBName.encode(ENC_OS), Env)
	print "[RD5GetD5DFileInfo] retval = %d [DBPath=%s,DBName=%s][OSType=%d,Endian=%d,ELF=%d,DBCharCode=%s]"\
		% (ret, DBPath, DBName, Env.OSType, Env.Endian, Env.ELF, Env.DBCharCode)
	for i in range(4):
		print " Version[%d]=%d"  % (i, lfmutilpy.int_at(Env.Version, i))

	# RD5GetD5TFileInfo
	DBName = SampleD5TFile
	Env = lfmtblpy.D5FileInfo()
	ret = lfmtblpy.RD5GetD5TFileInfo(DBPath.encode(ENC_OS), DBName.encode(ENC_OS), Env)
	print "[RD5GetD5TFileInfo] retval = %d [DBPath=%s,DBName=%s][OSType=%d,Endian=%d,ELF=%d,DBCharCode=%s]"\
		% (ret, DBPath, DBName, Env.OSType, Env.Endian, Env.ELF, Env.DBCharCode)
	for i in range(4):
		print " Version[%d]=%d"  % (i, lfmutilpy.int_at(Env.Version, i))

	print "### %s ### end" % funcName
	return

## 6-3-17 サーバ情報取得機能
def testServer():
	funcName = "testServer"
	print "### %s ### start" % funcName

	# RD5GetServerIPAddress → 未サポート

	# RD5GetEnvironment
	Env = lfmtblpy.TREnvironment()
	ret = lfmtblpy.RD5GetEnvironment(Env)
	print "[RD5GetEnvironment] retval = %d [HostName=%s,OSType=%d,OSMajorVersion=%d,OSMinorVersion=%d,MachineArchitecture=%d,Endian=%d,ELF=%d,ProcessorCount=%d,ProcessType=%d,OSCharCode=%s]"\
		% (ret, Env.HostName, Env.OSType, Env.OSMajorVersion, Env.OSMinorVersion, Env.MachineArchitecture\
		, Env.Endian, Env.ELF, Env.ProcessorCount, Env.ProcessType, Env.DBCharCode)

	# RD5BrowserGetCurrentDirectory → 未サポート
	# RD5BrowserSetCurrentDirectory → 未サポート
	# RD5BrowserMakeDirectory → 未サポート
	# RD5BrowserGetFileList → 未サポート
	# RD5BrowserGetFileSize → 未サポート
	# RD5BrowserGetFile → 未サポート
	# RD5BrowserGetFileEx → 未サポート
	# RD5BrowserPutFile → 未サポート
	# RD5BrowserPutFileEx → 未サポート
	# RD5BrowserDelFile → 未サポート
	# RD5BrowserMove → 未サポート
	# RD5BrowserDelDirectory → 未サポート

	# RD5GetSystemMemInfo
	MemInfo = lfmtblpy.TRMemInfo()
	ret = lfmtblpy.RD5GetSystemMemInfo(MemInfo)
	print "[RD5GetSystemMemInfo] retval = %d [TotalPhys=%d,AvailPhys=%d]"\
		% (ret, MemInfo.TotalPhys, MemInfo.AvailPhys)

	# RD5BrowserGetFile64 → 未サポート
	# RD5BrowserGetFileEx64 → 未サポート

	print "### %s ### end" % funcName
	return

## 6-3-18 共有メモリ関連機能
def testSharedMemory():
	funcName = "testSharedMemory"
	print "### %s ### start" % funcName

	# 64bit OS限定
	Env = lfmtblpy.TREnvironment()
	ret = lfmtblpy.RD5GetEnvironment(Env)
	if Env.ELF == 64:
		# init
		ret = lfmtblpy.RD5ClearDB()
		ret = lfmtblpy.RD5SetDBCharCode(ENC_DB)
		Name = SampleD5DFile_X64

		# RD5CreateSharedMemoryDB
		ret = lfmtblpy.RD5CreateSharedMemoryDB(PathIn.encode(ENC_OS), Name.encode(ENC_OS))
		print "[RD5CreateSharedMemoryDB] retval = %d [DBPath=%s,DBName=%s]" % (ret, PathIn, Name)

		# RD5LoadDBFromSharedMemory
		ret = lfmtblpy.RD5LoadDBFromSharedMemory()
		print "[RD5LoadDBFromSharedMemory] retval = %d" % ret

		# RD5ReleaseSharedMemoryArea -> 後に移動

		# RD5IsSharedMemoryTable
		TableID = 1
		ret = lfmtblpy.RD5IsSharedMemoryTable(TableID)
		print "[RD5IsSharedMemoryTable] retval = %d [TableID=%d]" % (ret, TableID)

		# RD5ReleaseSharedMemoryArea <- 前から移動
		ret = lfmtblpy.RD5ReleaseSharedMemoryArea()
		print "[RD5ReleaseSharedMemoryArea] retval = %d" % ret

	print "### %s ### end" % funcName
	return

## 配列をリスト化
# @param arry	at()メソッドで要素アクセスする配列クラス
# @param size	要素数
# @retval リスト
def Array2List(arry, size):
	list = []
	if (arry != None) & (size > 0):
		for i in range(size):
			list.append(arry.at(i))

	return list


## メイン
if __name__ == "__main__":
	print "Start\n"

	# 引数
	argvs = sys.argv
	argc = len(argvs)
	if argc > 1:
		ENC_OS = argvs[1]
	if argc > 2:
		ENC_DB = argvs[2]
	print "ENC_OS[%s],ENC_DB[%s]" % (ENC_OS, ENC_DB)

	# 出力先
	if not os.path.exists(PathOut):
		os.makedirs(PathOut)

	testWS()
	testTable()
	testSet()
	testFilter()
	testFind()
	testCategory()
	testCalc()
	testEdit()
	testGetData()
	testSearch()
	testSearchSJIS()
	testSort()
	testDetail()
	testSum()
	testDB()
	testServer()
	testSharedMemory()
	testEngine()

	print "\nEnd"
