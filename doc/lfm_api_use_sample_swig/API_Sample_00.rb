#!/usr/bin/env ruby -Ku

## @package API_Sample_00
# LFM APIサンプルプログラム
#
# @author Turbo Data Laboratories, Inc.
# @date 2009/07/01

require 'kconv'
require 'fileutils'
require 'bigdecimal'

# LFM
require 'lfmtblrb'
require 'lfmutilrb'


## OS文字コード
$ENC_OS = "MS932"
#$ENC_OS = "UTF8"

## DB文字コード
#$ENC_DB = "MS932"
$ENC_DB = "UTF8"

## 入力ファイルパス
PathIn = "./in"

## 出力ファイルパス
PathOut = "./out"

## サンプルデータファイル
SampleD5DFile   = "TypeTbl.D5D"
SampleD5TFile   = "TypeTbl.D5T"
SampleD5DFile_MS  = "TypeTbl_MS.D5D"
SampleD5DFile_JOIN  = "JoinTbl.D5D"
SampleD5DFile_SJIS  = "TypeTbl2_SJIS.D5D"
SampleCatalogFile = "RD5SaveAsCatalog"
SampleFilterData  = "fdata10.dat"
SampleSrcData   = "SrcDataEx.dat"
SampleD5DFile_X64 = "TypeTbl2_x64.D5D"


## 6-3-2 エンジン管理機能
def testEngine()
  funcName = "testEngine"
  printf "### %s ### start\n", funcName

  # RD5GetVersion -> RD5GetVersionR1
  # バージョン情報を取得します。
  _VArray = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_VERSION_SIZE)
  ret = Lfmtblrb.RD5GetVersionR1(_VArray.getPtr())
  printf "[RD5GetVersionR1] retval = %d [%d,%d,%d,%d]\n", ret, _VArray.at(0), _VArray.at(1), _VArray.at(2), _VArray.at(3)

  # RD5GetVersion -> RD5GetCopyRightR1
  # コピーライトメッセージを取得します。 
  ret = Lfmtblrb.RD5GetCopyRightR1()
  printf "[RD5GetCopyRightR1] retval = %s\n", ret

  # RD5Shutdown -> 後に移動(●)

  # RD5SetTailSpaceFlag
  # 文字列の末尾のスペースを削除するかどうかについてフラグを設定します
  _NewFlag = 1
  ret = Lfmtblrb.RD5SetTailSpaceFlag(_NewFlag)
  printf "[RD5SetTailSpaceFlag] retval = %d [NewFlag=%d]\n", ret, _NewFlag

  # RD5SetPassword
  # ライセンスキーのパスワード認証を行います。 
  _LicenseKey = ""
  ret = Lfmtblrb.RD5SetPassword(_LicenseKey)
  printf "[RD5SetPassword] retval = %d [LicenseKey=%s]\n", ret, _LicenseKey

  # RD5Shutdown
  # エンジンで使用したメモリを開放します
  ret = Lfmtblrb.RD5Shutdown()
  printf "[RD5Shutdown] retval = %d\n", ret

  printf "### %s ### end\n", funcName
  return
end

## 6-3-3 ワークスペース（ データベース）管理機能
def testWS(_Name)
  funcName = "testWS"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。 
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。 
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)

  # RD5LoadDB
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます
  #  [in]  szDBPath   D5Dファイルの存在するパス
  #  [in]  szDBName   D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5SaveDBAs
  # 指定されたパスに指定されたファイル名称で、ワークスペースをD5Dファイルとして書き出します。
  #  [in]   szDBPath  D5Dファイルを書き出すパス
  #  [in]   szDBName  D5Dファイルの名称
  #_Name = "testRD5SaveDBAs"
  ret = Lfmtblrb.RD5SaveDBAs(encode($ENC_OS, PathOut), encode($ENC_OS, _Name))
  printf "[RD5SaveDBAs] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathOut, _Name

  # RD5SaveDB
  # ワークスペースを上書き保存します。
  ret = Lfmtblrb.RD5SaveDB()
  printf "[RD5SaveDB] retval = %d\n", ret

  # RD5ClearDB -> 後に移動(●)

  # RD5GetPathName -> RD5GetDBPathR1
  # ワークスペースのパスを取得します。 
  ret = decode($ENC_OS, Lfmtblrb.RD5GetDBPathR1())
  printf "[RD5GetDBPathR1] retval = %s\n", ret

  # RD5GetPathName -> RD5GetDBNameR1
  # ワークスペースの名称を取得します。 
  ret = decode($ENC_OS, Lfmtblrb.RD5GetDBNameR1())
  printf "[RD5GetDBNameR1] retval = %s\n", ret

  # RD5GetLimitRowSize
  # 行数制限値を取得します。(0  無制限)
  ret = Lfmtblrb.RD5GetLimitRowSize()
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetLimitRowSize] retval = %d\n", ret
  end

  # RD5GetLimitMemSize
  # メモリ使用量制限値を取得します。 
  ret = Lfmtblrb.RD5GetLimitMemSize()
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetLimitMemSize] retval = %d\n", ret
  end

  # RD5GetTotalMemorySize
  # 使用メモリサイズを取得します。
  ret = Lfmtblrb.RD5GetTotalMemorySize()
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetTotalMemorySize] retval = %d\n", ret
  end

  # RD5GetTotalMemorySizeWithShared
  # 共用メモリを含めた使用メモリサイズを取得します。
  ret = Lfmtblrb.RD5GetTotalMemorySizeWithShared()
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetTotalMemorySizeWithShared] retval = %d\n", ret
  end

  # RD5ClearDB <- 前から移動
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  printf "[RD5ClearDB] retval = %d\n", ret
  printf "### %s ### end\n", funcName
  return
end

## 6-3-4 テーブル管理機能
def testTable(_Name,_Name2)
  funcName = "testTable"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)

  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  #_Name2 = SampleD5DFile_JOIN
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name2))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name2

  # RD5GetNTable
  # 存在するテーブル数を取得します。
  ret = Lfmtblrb.RD5GetNTable()
  printf "[RD5GetNTable] retval = %d\n", ret

  # RD5GetTableIDList
  # テーブルIDの一覧を取得します。 
  #   [out]   anTableIDList   テーブルIDの一覧
  _TablIDList = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_TABLE_COUNT)
  ret = Lfmtblrb.RD5GetTableIDList(_TablIDList.getPtr())
  print "[RD5GetTableIDList] retval = ", ret, " [TablIDList=", Array2List(_TablIDList, ret), "]\n"

  # RD5GenerateTableName -> RD5GenerateTableNameR1
  # 登録可能なテーブル名称を生成します。 
  _PCSeedName = "TblSeed"
  _PCGenName = decode($ENC_DB, Lfmtblrb.RD5GenerateTableNameR1(encode($ENC_DB, _PCSeedName)))
  printf "[RD5GenerateTableNameR1] PCGenName = %s [PCSeedName=%s]\n", _PCGenName, _PCSeedName

  # RD5LoadRealTable
  # REALテーブルをロードします。.
  #   [in]  szTablePath   D5Tファイルの存在するパス
  #   [in]  szTableName   テーブル名称
  _PCTblName = "TypeTbl"
  ret = Lfmtblrb.RD5LoadRealTable(encode($ENC_OS, PathIn), encode($ENC_OS, _PCTblName))
  printf "[RD5LoadRealTable] retval = %d [PCTblPath=%s,PCTblName=%s]\n", ret, PathIn, _PCTblName

  # RD5AddRealTable
  # REALテーブルを新規作成します。
  #   [in]  szTableName   作成するテーブル名称
  #   [in]  nRowCount   行数
  _PCTblName = "TEST_TABLE"
  _RowCount = 10
  ret = Lfmtblrb.RD5AddRealTable(_PCTblName, _RowCount)
  printf "[RD5AddRealTable] retval = %d [PCTblName=%s,RowCount=%d]\n", ret, _PCTblName, _RowCount

  # RD5SaveRealTable
  # REALテーブルを保存します。.
  #   [in]  szTablePath   REALテーブルを保存するパス
  #   [in]  nTableID  保存したいテーブルのID
  _TableID = 3
  ret = Lfmtblrb.RD5SaveRealTable(encode($ENC_OS, PathOut), _TableID)
  printf "[RD5SaveRealTable] retval = %d [PCTblPath=%s,TableID=%d]\n", ret, PathOut, _TableID

  # RD5AddJoinTable
  # JOINテーブルを作成します。.
  #   [in]  szTableName   新規に作成するJOINテーブル名称
  #   [in]  nIsOuter  テーブル区分
  #   [in]  nMasterTableID  マスタテーブルID
  #   [in]  nMasterSetID  マスタテーブルのセットID
  #   [in]  anMasterFilterIDs   JOINキーとなるマスタテーブルの項目IDリスト
  #   [in]  nSlaveTableID   スレーブテーブルID
  #   [in]  nSlaveSetID   スレーブテーブルのセットID
  #   [in]  anSlaveFilterIDs  JOINキーとなるスレーブテーブルの項目IDリスト

  _PCTblName    = "JoinTbl"
  _IsOuter      = 0
  _MasterTblID  = 1
  _MasterSetID  = 1
  #_nFlt = Lfmtblrb::D5_MAX_JOIN_KEY
  _nFlt = 2
  _MasterFltIDs  = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _MasterFltIDs.put(0, 2)
  _MasterFltIDs.put(1, 0)
  _SlaveTblID    = 2
  _SlaveSetID    = 1
  _SlaveFltIDs   = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _SlaveFltIDs.put(0, 1)
  _SlaveFltIDs.put(1, 0)
  ret = Lfmtblrb.RD5AddJoinTable(_PCTblName, _IsOuter, _MasterTblID, _MasterSetID, _MasterFltIDs.getPtr(), _SlaveTblID, _SlaveSetID, _SlaveFltIDs.getPtr())
  printf "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs=" \
    , ret, _PCTblName, _IsOuter, _MasterTblID, _MasterSetID
  print Array2List(_MasterFltIDs, _nFlt)
  printf ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=", _SlaveTblID, _SlaveSetID
  print Array2List(_SlaveFltIDs, _nFlt), "]\n"
  _JoinTblID = ret

  # RD5ConvertJoinToReal
  # JOINテーブルを作成します。.
  #   [in]  szTableName   新規に作成するJOINテーブル名称
  #   [in]  nIsOuter  テーブル区分
  #   [in]  nMasterTableID  マスタテーブルID
  #   [in]  nMasterSetID  マスタテーブルのセットID
  #   [in]  anMasterFilterIDs   JOINキーとなるマスタテーブルの項目IDリスト
  #   [in]  nSlaveTableID   スレーブテーブルID
  #   [in]  nSlaveSetID   スレーブテーブルのセットID
  #   [in]  anSlaveFilterIDs  JOINキーとなるスレーブテーブルの項目IDリスト

  _PCTblName      = "Join2Real"
  _JSetID         = -1
  _IncludeRowNoM  = 1
  _IncludeRowNoS  = 1
  #_nFlt = Lfmtblrb::D5_MAX_FILTER_COUNT_REAL
  _nFlt = 4
  _FltIDs = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _FltIDs.put(0, 1)
  _FltIDs.put(1, 2)
  _FltIDs.put(2, 4)
  _FltIDs.put(3, 0)
  _VLIsLinked = 0
  ret = Lfmtblrb.RD5ConvertJoinToReal(_PCTblName, _JoinTblID, _JSetID, _IncludeRowNoM, _IncludeRowNoS, _FltIDs.getPtr(), _VLIsLinked)
  printf "[RD5ConvertJoinToReal] retval = %d [PCTblName=%s,JoinTblID=%d,JSetID=%d,IncludeRowNoM=%d,IncludeRowNoS=%d,FltIDs=" \
    , ret, _PCTblName, _JoinTblID, _JSetID, _IncludeRowNoM, _IncludeRowNoS
  print Array2List(_FltIDs, _nFlt)
  printf ",VLIsLinked=%d]\n", _VLIsLinked

  # RD5ExtractJoinInOut
  # JOIN IN/OUTセットを生成します。.
  #   [in]  nDestTableID  JOIN IN/OUTセット生成のターゲットのテーブルID
  #   [in]  nDestSetID  JOIN IN/OUTセットを算出するターゲットのセットID
  #   [in]  nDestFilterID   JOIN IN/OUTセットを算出するターゲットの項目ID
  #   [in]  nSrcTableID   JOIN IN/OUTセットの算出元になるーブルID
  #   [in]  nSrcSetID   JOIN IN/OUTセットの算出元になるのセットID
  #   [in]  nSrcFilterID  JOIN IN/OUTセットの算出元になる項目ID
  #   [in]  nIsJoinIn   IN/OUTを指定する

  _DestTableID  = 2
  _DestSetID    = 1
  _DestFilterID = 2
  _SrcTableID   = 3
  _SrcSetID     = 1
  _SrcFilterID  = 1
  _IsJoinIn     = 1
  ret = Lfmtblrb.RD5ExtractJoinInOut(_DestTableID, _DestSetID, _DestFilterID, _SrcTableID, _SrcSetID, _SrcFilterID, _IsJoinIn)
  printf "[RD5ExtractJoinInOut] retval = %d [DestTableID=%d,DestSetID=%d,DestFilterID=%d,SrcTableID=%d,SrcSetID=%d,SrcFilterID=%d,IsJoinIn=%d]\n" \
    , ret, _DestTableID, _DestSetID, _DestFilterID, _SrcTableID, _SrcSetID, _SrcFilterID, _IsJoinIn

  # RD5RealizeJoinChain → 未サポート
  #   JOINチェーンを実体化します。
  # RD5RealizeJoinChainEx → 未サポート
  #   JOINチェーンを実体化し、生成されたツリーテーブルに元テーブルの整数項目を追加します。.
  # RD5QualifyTree → 未サポート
  #   実体化されたJOINチェーンにソース情報を付加します。 

  # RD5SetMaxJoinChain
  # JOINチェイン最大値を設定します。.
  #   [in]  nMaxJoinChain   最大階層数(16〜510)
  _MaxJoinChain = 510
  ret = Lfmtblrb.RD5SetMaxJoinChain(_MaxJoinChain)
  printf "[RD5SetMaxJoinChain] retval = %d [MaxJoinChain=%s]\n", ret, _MaxJoinChain

  # RD5DeleteTable
  # テーブルを削除します。 
  #   [in]  nTableID  削除するテーブルID
  _TableID = 5
  ret = Lfmtblrb.RD5DeleteTable(_TableID)
  printf "[RD5DeleteTable] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5GetTableName -> RD5GetTableNameR1
  # テーブル名称を取得します。
  _TableID = 4
  _TableName = decode($ENC_DB, Lfmtblrb.RD5GetTableNameR1(_TableID))
  printf "[RD5GetTableNameR1] TableName = %s [TableID=%d]\n", _TableName, _TableID

  # RD5GetTableProperty
  # テーブルの情報を取得します
  #   [in]  nTableID  テーブルID
  #   [out]   pTableInfo  テーブル情報のアドレス
  _TableInfo = Lfmtblrb::TTableInfo.new()
  ret = Lfmtblrb.RD5GetTableProperty(_TableID, _TableInfo)
  printf "[RD5GetTableProperty] retval = %d [TableID=%d,TableKind=%d,nFilter=%d,nSet=%d,TotalRows=%d,TableName=%s]\n" \
    , ret, _TableInfo.TableID, _TableInfo.TableKind, _TableInfo.nFilter, _TableInfo.nSet, _TableInfo.TotalRows, _TableInfo.TableName

  # RD5SetTableName
  # テーブル名称を変更します。
  #   [in]  nTableID  変更するテーブルID
  #   [in]  szTableName   新規に設定するテーブル名称
  _TableName = "TypeTblRN"
  ret = Lfmtblrb.RD5SetTableName(_TableID, _TableName)
  printf "[RD5SetTableName] retval = %d [TableID=%d,TableName=%s]\n", ret, _TableID, _TableName

  # RD5GetTableIDFromName
  # テーブル名称からテーブルIDを取得します。
  ret = Lfmtblrb.RD5GetTableIDFromName(_TableName)
  printf "[RD5GetTableIDFromName] retval = %d [TableName=%s]\n", ret, _TableName

  # RD5GetJoinInfoEx -> RD5GetJoinInfoExR1
  # JOINテーブルの情報を取得します。.
  #   [in]  nTableID  情報を取得するJOINテーブルID
  #   [out]   pnIsOuter   JOINテーブルの種類
  #   [out]   pnJoinKeyCount  JOINキーの数
  #   [out]   pnMasterTableID   マスタテーブルID
  #   [out]   pnMasterSetID   マスタテーブルセットID
  #   [out]   anMasterFilterIDs   マスタテーブルのJOINキーの一覧
  #   [out]   pnSlaveTableID  スレーブテーブルID
  #   [out]   pnSlaveSetID  スレーブテーブルセットID
  #   [out]   anSlaveFilterIDs  スレーブテーブルのJOINキーの一覧
  _TableID      = _JoinTblID
  _IsOuter      = Lfmutilrb::CTypeIntAr.new(1)
  _nJoinKey     = Lfmutilrb::CTypeIntAr.new(1)
  _MasterTblID  = Lfmutilrb::CTypeIntAr.new(1)
  _MasterSetID  = Lfmutilrb::CTypeIntAr.new(1)
  _MasterFltIDs = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_JOIN_KEY)
  _SlaveTblID   = Lfmutilrb::CTypeIntAr.new(1)
  _SlaveSetID   = Lfmutilrb::CTypeIntAr.new(1)
  _SlaveFltIDs  = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_JOIN_KEY)
  ret = Lfmtblrb.RD5GetJoinInfoExR1(_TableID, _IsOuter.getPtr(), _nJoinKey.getPtr() \
                , _MasterTblID.getPtr(), _MasterSetID.getPtr(), _MasterFltIDs.getPtr() \
                , _SlaveTblID.getPtr(), _SlaveSetID.getPtr(), _SlaveFltIDs.getPtr())
  printf "[RD5GetJoinInfoExR1] retval = %d [TableID=%d][IsOuter=%d,nJoinKey=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs=" \
    , ret, _TableID, _IsOuter.at(0), _nJoinKey.at(0), _MasterTblID.at(0), _MasterSetID.at(0)
  print Array2List(_MasterFltIDs, _nJoinKey.at(0))
  printf ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=", _SlaveTblID.at(0), _SlaveSetID.at(0)
  print Array2List(_SlaveFltIDs, _nJoinKey.at(0)), "]\n"

  # RD5GetJoinSrcTblInfo
  # JOINテーブルの情報を取得します
  #   [in]  nTableID  指定のテーブルのテーブルID
  #   [out]   pnNMasterFilter   マスタ側フィルタに由来するフィルタの数
  #   [out]   pnNSlaveFilter  スレイブ側テーブルに由来するフィルタの数
  #   [out]   anJoinFilterIDs   指定のテーブルのフィルタID[1..N]
  #   [out]   anSrcTableIDs   指定のテーブルのマスターテーブルID[Nm, Nm, ... Nm, Ns, Ns, ... Ns]
  #   [out]   anSrcFilterIDs  指定のテーブルのマスター集合ID[FIDm1, FIDm2, ..., FIDs1, FIDs2, ...]
  _TableID    = _JoinTblID
  _NMasterFlt = Lfmutilrb::CTypeIntAr.new(1)
  _NSlaveFlt  = Lfmutilrb::CTypeIntAr.new(1)
  _JFltIDs    = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_JOIN)
  _SrcTblIDs  = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_JOIN)
  _SrcFltIDs  = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_JOIN)
  ret = Lfmtblrb.RD5GetJoinSrcTblInfo(_TableID, _NMasterFlt.getPtr(), _NSlaveFlt.getPtr(), _JFltIDs.getPtr(), _SrcTblIDs.getPtr(), _SrcFltIDs.getPtr())
  printf "[RD5GetJoinSrcTblInfo] retval = %d [TableID=%d][NMasterFlt=%d,NSlaveFlt=%d,JFltIDs=" \
    , ret, _TableID, _NMasterFlt.at(0), _NSlaveFlt.at(0)
  print Array2List(_JFltIDs, ret), ",SrcTblIDs=", Array2List(_SrcTblIDs, ret), "SrcFltIDs=", Array2List(_SrcFltIDs, ret), "]\n"

  # RD5GetJoinSrcTblIDs
  # JOIN情報を取得します
  #   [in]  nTableID  指定のテーブルのテーブルID
  #   [out]   anJoinFilterIDs   指定のテーブルのフィルタIDリスト
  #   [out]   anSrcTableIDs   指定のテーブルの元テーブルIDリスト
  #   [out]   anSrcFilterIDs  指定のテーブルの元フィルタIDリスト
  ret = Lfmtblrb.RD5GetJoinSrcTblIDs(_TableID, _JFltIDs.getPtr(), _SrcTblIDs.getPtr(), _SrcFltIDs.getPtr())
  printf "[RD5GetJoinSrcTblIDs] retval = %d [TableID=%d][JFltIDs=", ret, _TableID
  print Array2List(_JFltIDs, ret), ",SrcTblIDs=", Array2List(_SrcTblIDs, ret), ",SrcFltIDs=", Array2List(_SrcFltIDs, ret), "]\n"


  # reset

  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  #_Name = SampleD5DFile
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5DuplicateRealTable
  # REALテーブルを複製します。.
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nTableID  複製元のテーブルID
  _TableID = 1
  _PCTblName = "複製テーブル"
  ret = Lfmtblrb.RD5DuplicateRealTable(encode($ENC_DB, _PCTblName), _TableID)
  printf "[RD5DuplicateRealTable] retval = %d [PCTblName=%s,TableID=%d]\n", ret, _PCTblName, _TableID

  # RD5ExtractRealTable
  # REALテーブルを抽出します。
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nTableID  抽出元のテーブルID
  #   [in]  nSetID  抽出するセットID
  #   [in]  anExtractFilterIDList   抽出する項目IDリスト
  _PCTblName = "Extractテーブル"
  _SetID = -1
  _ExtractFilterIDList = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_REAL)
  _size = 3
  _ExtractFilterIDList.put(0, 2)
  _ExtractFilterIDList.put(1, 3)
  _ExtractFilterIDList.put(2, 0)
  ret = Lfmtblrb.RD5ExtractRealTable(encode($ENC_DB, _PCTblName), _TableID, _SetID, _ExtractFilterIDList.getPtr())
  printf "[RD5ExtractRealTable] retval = %d [PCTblName=%s,TableID=%d,SetID=%d,ExtractFilterIDList=" \
    , ret, _PCTblName, _TableID, _SetID
  print Array2List(_ExtractFilterIDList, _size), "]\n"

  # RD5ExtractRealTableEx
  # REALテーブルを抽出します。.
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nTableID  抽出元のテーブルID
  #   [in]  nSetID  抽出するセットID
  #   [in]  nIncludeTableID   抽出元テーブルIDの項目化設定値
  #   [in]  nIncludeRecNo   抽出元レコード番号の項目化設定値
  #   [in]  anExtractFilterIDList   抽出する項目IDリスト
  _PCTblName = "ExtractテーブルEx"
  _IncludeTableID = 1
  _IncludeRecNo = 1
  ret = Lfmtblrb.RD5ExtractRealTableEx(encode($ENC_DB, _PCTblName), _TableID, _SetID, _IncludeTableID, _IncludeRecNo, _ExtractFilterIDList.getPtr())
  printf "[RD5ExtractRealTableEx] retval = %d [PCTblName=%s,TableID=%d,SetID=%d,IncludeTableID=%d,IncludeTableID=%d,ExtractFilterIDList=" \
    , ret, _PCTblName, _TableID, _SetID, _IncludeTableID, _IncludeRecNo
  print Array2List(_ExtractFilterIDList, _size), "]\n"

  # RD5CombineRealTable
  # REALテーブルを縦結合します。.
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nTableID1   結合する1番目のテーブルID
  #   [in]  nSetID1   結合する1番目のセットID
  #   [in]  anFilterIDs1  結合する1番目の項目リスト
  #   [in]  nTableID2   結合する2番目のテーブルID
  #   [in]  nSetID2   結合する2番目のセットID
  #   [in]  anFilterIDs2  結合する2番目の項目リスト

  _PCTblName = "結合テーブル"
  _size = 3
  _FltIDs1 = Lfmutilrb::CTypeIntAr.new(_size)
  _FltIDs1.put(0, 6)
  _FltIDs1.put(1, 5)
  _FltIDs1.put(2, 0)
  _TableID2 = 2
  _SetID2 = -1
  _FltIDs2 = Lfmutilrb::CTypeIntAr.new(_size)
  _FltIDs2.put(0, 2)
  _FltIDs2.put(1, 3)
  _FltIDs2.put(2, 0)
  ret = Lfmtblrb.RD5CombineRealTable(encode($ENC_DB, _PCTblName), _TableID, _SetID, _FltIDs1.getPtr(), _TableID2, _SetID2, _FltIDs2.getPtr())
  printf "[RD5CombineRealTable] retval = %d [PCTblName=%s,TableID1=%d,SetID1=%d,FltIDs1=" \
    , ret, _PCTblName, _TableID, _SetID
  print Array2List(_FltIDs1, _size)
  printf ",TableID2=%d,SetID2=%d,FltIDs2=", _TableID2, _SetID2
  print Array2List(_FltIDs2, _size), "]\n"

  # RD5CombineRealTableEx
  # REALテーブルを縦結合します。.
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nIncludeTableID   抽出元のテーブルIDの項目化設定値
  #   [in]  nIncludeRecNo   抽出元のレコード番号の項目化設定値
  #   [in]  nTableID1   結合する1番目のテーブルID
  #   [in]  nSetID1   結合する1番目のセットID
  #   [in]  anFilterIDs1  結合する1番目の項目リスト
  #   [in]  nTableID2   結合する2番目のテーブルID
  #   [in]  nSetID2   結合する2番目のセットID
  #   [in]  anFilterIDs2  結合する2番目の項目リスト
  _PCTblName = "結合テーブルEx"
  _IncludeTableID = 1
  _IncludeRecNo = 1
  ret = Lfmtblrb.RD5CombineRealTableEx(encode($ENC_DB, _PCTblName), _IncludeTableID, _IncludeRecNo, _TableID, _SetID, _FltIDs1.getPtr() \
    , _TableID2, _SetID2, _FltIDs2.getPtr())
  printf "[RD5CombineRealTableEx] retval = %d [PCTblName=%s,IncludeTableID=%d,IncludeRecNo=%d,TableID1=%d,SetID1=%d,FltIDs1=" \
    , ret, _PCTblName, _IncludeTableID, _IncludeRecNo, _TableID, _SetID
  print Array2List(_FltIDs1, _size)
  printf ",TableID2=%d,SetID2=%d,FltIDs2=", _TableID2, _SetID2
  print Array2List(_FltIDs2, _size), "]\n"

  # RD5CombineRealTableEx2
  # REALテーブルを縦結合します。.
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  nIncludeTableID   抽出元のテーブルIDの項目化設定値
  #   [in]  nIncludeRecNo   抽出元のレコード番号の項目化設定値
  #   [in]  nTableID1   結合する1番目のテーブルID
  #   [in]  nSetID1   結合する1番目のセットID
  #   [in]  anFilterIDs1  結合する1番目の項目のリスト
  #   [in]  nTableID2   結合する2番目のテーブルID
  #   [in]  nSetID2   結合する2番目のセットID
  #   [in]  anFilterIDs2  結合する2番目の項目のリスト
  _PCTblName = "結合テーブルEx2"
  ret = Lfmtblrb.RD5CombineRealTableEx2(encode($ENC_DB, _PCTblName), _IncludeTableID, _IncludeRecNo, _TableID, _SetID, _FltIDs1.getPtr() \
    , _TableID2, _SetID2, _FltIDs2.getPtr())
  printf "[RD5CombineRealTableEx2] retval = %d [PCTblName=%s,IncludeTableID=%d,IncludeRecNo=%d,TableID1=%d,SetID1=%d,FltIDs1=" \
    , ret, _PCTblName, _IncludeTableID, _IncludeRecNo, _TableID, _SetID
  print Array2List(_FltIDs1, _size)
  printf ",TableID2=%d,SetID2=%d,FltIDs2=", _TableID2, _SetID2
  print Array2List(_FltIDs2, _size), "]\n"

  # RD5CombineTableList
  # 複数のREALテーブルの整数項目を結合します。
  #   [in]  szTableName   新規に設定するテーブル名称
  #   [in]  anTableIDList   結合するテーブルIDリスト
  #   [in]  anSetIDList   結合するセットIDリスト
  #   [in]  anIntFilterList0  新テーブルの1番目の項目に設定する項目IDリスト
  #   [in]  anIntFilterList1  新テーブルの2番目の項目に設定する項目IDリスト
  #   [in]  anIntFilterList2  新テーブルの3番目の項目に設定する項目IDリスト
  #   [in]  anIntFilterList3  新テーブルの4番目の項目に設定する項目IDリスト
  _PCTblName = "RD5CombineTableList"
  _TableIDList = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_COMBINE)
  _size = 2
  _TableIDList.put(0, 6)
  _TableIDList.put(1, 7)
  _TableIDList.put(2, 0)
  _SetIDList = Lfmutilrb::CTypeIntAr.new(_size)
  _IntFltList0 = Lfmutilrb::CTypeIntAr.new(_size)
  _IntFltList1 = Lfmutilrb::CTypeIntAr.new(_size)
  for i in 0..._size
    _SetIDList.put(i, -1)
    _IntFltList0.put(i, 1)
    _IntFltList1.put(i, 2)
  end
  _IntFltList2 = nil
  _IntFltList3 = nil
  ret = Lfmtblrb.RD5CombineTableList(encode($ENC_DB, _PCTblName), _TableIDList.getPtr(), _SetIDList.getPtr() \
    , _IntFltList0.getPtr(), _IntFltList1.getPtr(), _IntFltList2, _IntFltList3)
  printf "[RD5CombineTableList] retval = %d [PCTblName=%s,TableIDList=", ret, _PCTblName
  print Array2List(_TableIDList, _size), ",SetIDList=", Array2List(_SetIDList, _size), ",IntFltList0=" \
    , Array2List(_IntFltList0, _size), ",IntFltList1=", Array2List(_IntFltList1, _size), ",IntFltList2=" \
    , Array2List(_IntFltList2, _size), ",IntFltList3=", Array2List(_IntFltList3, _size), "]\n"
  _TableID = 8

  # RD5CondenseRealTable
  # REALテーブルを圧縮します。.
  ret = Lfmtblrb.RD5CondenseRealTable(_TableID)
  printf "[RD5CondenseRealTable] retval = %d [TableID=%d]\n", ret, _TableID

  # reset
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()

  # RD5AddCatalogFile
  # カタログ定義ファイルからテーブルを生成します。
  #   [in]  szCatalogPath   構造定義ファイルの存在するパス
  #   [in]  szCatalogName   構造定義ファイルの名称
  #   [in]  szSourcePath  原始データファイルの存在するパス
  #   [in]  szSourceName  原始データファイルの名称
  #   [in]  szTableName   新規に生成するテーブル名称
  _FilePath = File.expand_path(PathIn)
  _FileName = SampleCatalogFile
  ret = Lfmtblrb.RD5AddCatalogFile(encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddCatalogFile] retval = %d [FilePath=%s,FileName=%s]\n", ret, _FilePath, _FileName

  # RD5AddCatalogFileEx2
  # カタログ定義ファイルからテーブルを生成します。
  #   [in]  szCatalogPath   構造定義ファイルの存在するパス
  #   [in]  szCatalogName   構造定義ファイルの名称
  #   [in]  szSourcePath  原始データファイルの存在するパス
  #   [in]  szSourceName  原始データファイルの名称
  #   [in]  szTableName   新規に生成するテーブル名称
  _CatalogPath = PathIn
  _CatalogName = SampleCatalogFile
  _SourcePath  = _CatalogPath
  _SourceName  = SampleSrcData
  _TableName   = "AddCatalogFileEx2"
  ret = Lfmtblrb.RD5AddCatalogFileEx2(encode($ENC_OS, _CatalogPath), encode($ENC_OS, _CatalogName) \
    , encode($ENC_OS, _SourcePath), encode($ENC_OS, _SourceName), encode($ENC_DB, _TableName))
  printf "[RD5AddCatalogFileEx2] retval = %d [CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s,TableName=%s]\n" \
    , ret, _CatalogPath, _CatalogName, _SourcePath, _SourceName, _TableName

  # RD5AppendCatalogFile
  # カタログ定義ファイルからテーブルへデータを追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nAppendPos  追加開始位置
  #   [in]  nDataArraySize  追加する行数
  #   [in]  szCatalogPath   カタログ定義ファイルの存在するパス
  #   [in]  szCatalogName   カタログ定義ファイルの名称
  _TableID       = 2
  _AppendPos     = -1
  _DataArraySize = 10
  _FilePath      = PathIn
  _FileName      = SampleCatalogFile
  ret = Lfmtblrb.RD5AppendCatalogFile(_TableID, _AppendPos, _DataArraySize, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AppendCatalogFile] retval = %d [TableID=%d,AppendPos=%d,DataArraySize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _AppendPos, _DataArraySize, _FilePath, _FileName

  # RD5AppendCatalogFileEx2
  # カタログ定義ファイルからテーブルへデータを追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nAppendPos  追加開始位置
  #   [in]  nDataArraySize  追加する行数
  #   [in]  szCatalogPath   構造定義ファイルの存在するパス
  #   [in]  szCatalogName   構造定義ファイルの名称
  #   [in]  szSourcePath  原始データファイルの存在するパス
  #   [in]  szSourceName  原始データファイルの名称

  _TableID       = 2
  _AppendPos     = 6
  _DataArraySize = 5
  _CatalogPath   = PathIn
  _CatalogName   = SampleCatalogFile
  _SourcePath    = PathIn
  _SourceName    = SampleSrcData
  ret = Lfmtblrb.RD5AppendCatalogFileEx2(_TableID, _AppendPos, _DataArraySize \
                    , encode($ENC_OS, _CatalogPath), encode($ENC_OS, _CatalogName) \
                    , encode($ENC_OS, _SourcePath), encode($ENC_OS, _SourceName))
  printf "[RD5AppendCatalogFileEx2] retval = %d [TableID=%d,AppendPos=%d,DataArraySize=%d,CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s]\n" \
    , ret, _TableID, _AppendPos, _DataArraySize, _CatalogPath, _CatalogName, _SourcePath, _SourceName

  # RD5SaveAsCatalog
  # テーブルのデータをカタログ定義ファイルへエクスポートします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  anFilterIDList  出力する項目IDリスト
  #   [in]  nFileType   出力するファイルタイプ
  #   [in]  nRowFrom  出力する行の開始位置
  #   [in]  nRowTo  出力する行の終了位置
  #   [in]  nDateSep  日付データの区切り文字を指定
  #   [in]  szCatalogPath   カタログ定義ファイルを出力するパス
  #   [in]  szCatalogName   カタログ定義ファイルの名称
  _TableID = 2
  _SetID   = 1
  #_nFlt = Lfmtblrb::D5_MAX_FILTER_COUNT_JOIN
  _nFlt = 8
  _IDList  = Lfmutilrb::CTypeIntAr.new(_nFlt + 1)
  for i in 0..._nFlt
    _IDList.put(i, i + 1)
  end
  _IDList.put(_nFlt, -1)
  _type     = 0
  _RowFrom  = -1
  _RowTo    = -1
  _Datesep  = '/'
  _FilePath = PathOut
  _FileName = "RD5SaveAsCatalog"
  ret = Lfmtblrb.RD5SaveAsCatalog(_TableID, _SetID, _IDList.getPtr(), _type, _RowFrom, _RowTo, ord(_Datesep), encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5SaveAsCatalog] retval = %d [TableID=%d,SetID=%d,IDList=", ret, _TableID, _SetID
  print Array2List(_IDList, _nFlt)
  printf ",type=%d,RowFrom=%d,RowTo=%d,Datesep=%s,FilePath=%s,FileName=%s]\n", _type, _RowFrom, _RowTo, _Datesep, _FilePath, _FileName

  # RD5SaveAsCatalogEx
  # テーブルのデータをカタログ定義ファイルへエクスポートします
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  anFilterIDList  出力する項目IDリスト
  #   [in]  nFileType   出力するファイルタイプ
  #   [in]  nRowFrom  出力する行の開始位置
  #   [in]  nRowTo  出力する行の終了位置
  #   [in]  nDateSep  日付データの区切り文字を指定
  #   [in]  szCatalogPath   構造定義ファイルを出力するパス
  #   [in]  szCatalogName   構造定義ファイルの名称
  #   [in]  szSourcePath  原始データファイルの存在するパス
  #   [in]  szSourceName  原始データファイルの名称
  _CatalogPath = PathOut
  _CatalogName = "RD5SaveAsCatalogEx"
  _SourcePath  = PathOut
  _SourceName  = SampleSrcData
  ret = Lfmtblrb.RD5SaveAsCatalogEx(_TableID, _SetID, _IDList.getPtr(), _type, _RowFrom, _RowTo, ord(_Datesep), encode($ENC_OS, _CatalogPath), encode($ENC_OS, _CatalogName) \
    , encode($ENC_OS, _SourcePath), encode($ENC_OS, _SourceName))
  printf "[RD5SaveAsCatalogEx] retval = %d [TableID=%d,SetID=%d,IDList=", ret, _TableID, _SetID
  print Array2List(_IDList, _nFlt)
  printf ",type=%d,RowFrom=%d,RowTo=%d,Datesep=%s,CatalogPath=%s,CatalogName=%s,SourcePath=%s,SourceName=%s]\n" \
    , _type, _RowFrom, _RowTo, _Datesep, _CatalogPath, _CatalogName, _SourcePath, _SourceName

  # RD5SaveAsCatalogwithF → 未サポート
  #   テーブルのデータを、浮動小数点の桁数を指定して、カタログ定義ファイルへエクスポートします。
  # RD5SaveAsCatalogwithFEx → 未サポート
  #   テーブルのデータを、浮動小数点の桁数を指定して、カタログ定義ファイルへエクスポートします。

  # RD5ExportAsCSV
  # カンマ区切りファイルへデータをエクスポートします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  anFilterIDList  項目IDリスト
  #   [in]  nRowFrom  出力を開始する行
  #   [in]  nRowTo  出力の終了行
  #   [in]  nDateSep  日付データの区切り文字を指定
  #   [in]  szDBPath  出力ファイルへのパス
  #   [in]  szDBName  出力ファイル名称
  _DBPath  = PathOut
  _DBName  = "ExportAsCSV.csv"
  ret = Lfmtblrb.RD5ExportAsCSV(_TableID, _SetID, _IDList.getPtr(), _RowFrom, _RowTo, ord(_Datesep), encode($ENC_OS, _DBPath), encode($ENC_OS, _DBName))
  printf "[RD5ExportAsCSV] retval = %d [TableID=%d,SetID=%d,IDList=", ret, _TableID, _SetID
  print Array2List(_IDList, _nFlt)
  printf ",RowFrom=%d,RowTo=%d,Datesep=%s,DBPath=%s,DBName=%s]\n", _RowFrom, _RowTo, _Datesep, _DBPath, _DBName

  # RD5ExportAsCSVwithF → 未サポート
  #   カンマ区切りファイルへデータをエクスポートします。

  # RD5ExportAsTAB
  # TAB区切りファイルへデータをエクスポートします。.
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  anFilterIDList  項目IDリスト
  #   [in]  nRowFrom  出力を開始する行
  #   [in]  nRowTo  出力の終了行
  #   [in]  nDateSep  日付データの区切り文字を指定
  #   [in]  szDBPath  出力ファイルへのパス
  #   [in]  szDBName  出力ファイル名称
  _DBPath  = PathOut
  _DBName  = "ExportAsTAB.csv"
  ret = Lfmtblrb.RD5ExportAsTAB(_TableID, _SetID, _IDList.getPtr(), _RowFrom, _RowTo, ord(_Datesep), encode($ENC_OS, _DBPath), encode($ENC_OS, _DBName))
  printf "[RD5ExportAsTAB] retval = %d [TableID=%d,SetID=%d,IDList=", ret, _TableID, _SetID
  print Array2List(_IDList, _nFlt)
  printf ",RowFrom=%d,RowTo=%d,Datesep=%s,DBPath=%s,DBName=%s]\n", _RowFrom, _RowTo, _Datesep, _DBPath, _DBName

  # RD5ExportAsTABwithF → 未サポート
  #   TAB区切りファイルへデータをエクスポートします。.

  # RD5GetTableMemorySize
  #   テーブルの使用メモリサイズを取得します。
  ret = Lfmtblrb.RD5GetTableMemorySize(_TableID)
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetTableMemorySize] retval = %d [TableID=%d]\n", ret, _TableID
  end

  printf "### %s ### end\n", funcName
  return
end

## 6-3-5 順序付き集合管理機能
def testSet(_Name)
  funcName = "testSet"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile_MS
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5GetNSet
  # 指定したテーブルに属するセット数を取得します。
  _TableID = 1
  ret = Lfmtblrb.RD5GetNSet(_TableID)
  printf "[RD5GetNSet] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5GetTotalRows
  # ルートセットの件数を取得します。
  ret = Lfmtblrb.RD5GetTotalRows(_TableID)
  printf "[RD5GetTotalRows] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5GetSetSize
  # セットIDを指定し、セットサイズを取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  _SetID = 1
  ret = Lfmtblrb.RD5GetSetSize(_TableID, _SetID)
  printf "[RD5GetSetSize] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5PurgeSubsets
  # ルートセット以外のセットを削除します。
  ret = Lfmtblrb.RD5PurgeSubsets(_TableID)
  printf "[RD5PurgeSubsets] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5GetSet → 未サポート
  # 指定したIDのセットを取得します。

  # RD5GetSetName -> RD5GetSetNameR1
  # セット名称を取得します。
  #   [in]  nTableID  セットの属するテーブルID
  #   [in]  nSetID  セットID

  ret = Lfmtblrb.RD5GetSetNameR1(_TableID, _SetID)
  printf "[RD5GetSetNameR1] Name = %s [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5SetSetName
  # セット名称を設定します。
  #   [in]  nTableID  セットの属するテーブル名称
  #   [in]  nSetID  セットID
  #   [in]  szSetName   設定するセット名称を格納した文字配列

  _Name = "RD5SetSetName"
  ret = Lfmtblrb.RD5SetSetName(_TableID, _SetID, encode($ENC_DB, _Name))
  printf "[RD5SetSetName] retval = %d [TableID=%d,SetID=%d,Name=%s]\n", ret, _TableID, _SetID, _Name

  # RD5GetSetName -> RD5GetSetNameR1（確認）
  # セット名称を取得します。
  #   [in]  nTableID  セットの属するテーブルID
  #   [in]  nSetID  セットID
  ret = Lfmtblrb.RD5GetSetNameR1(_TableID, _SetID)
  printf "[RD5GetSetNameR1] Name = %s [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID


  # reset
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  #   [in]  szDBName  D5Dファイルの名称
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile_JOIN
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # JOIN
  _PCTblName    = "JoinTbl"
  _IsOuter      = 0
  _MasterTblID  = 1
  _MasterSetID  = 1
  #_nFlt = Lfmtblrb::D5_MAX_JOIN_KEY
  _nFlt = 2
  _MasterFltIDs = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _MasterFltIDs.put(0, 2)
  _MasterFltIDs.put(1, 0)
  _SlaveTblID   = 2
  _SlaveSetID   = 1
  _SlaveFltIDs  = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _SlaveFltIDs.put(0, 1)
  _SlaveFltIDs.put(1, 0)
  # RD5AddJoinTable
  # JOINテーブルを作成します。.
  #   [in]  szTableName   新規に作成するJOINテーブル名称
  #   [in]  nIsOuter  テーブル区分
  #   [in]  nMasterTableID  マスタテーブルID
  #   [in]  nMasterSetID  マスタテーブルのセットID
  #   [in]  anMasterFilterIDs   JOINキーとなるマスタテーブルの項目IDリスト
  #   [in]  nSlaveTableID   スレーブテーブルID
  #   [in]  nSlaveSetID   スレーブテーブルのセットID
  #   [in]  anSlaveFilterIDs  JOINキーとなるスレーブテーブルの項目IDリス
  ret = Lfmtblrb.RD5AddJoinTable(_PCTblName, _IsOuter, _MasterTblID, _MasterSetID, _MasterFltIDs.getPtr(), _SlaveTblID, _SlaveSetID, _SlaveFltIDs.getPtr())
  printf "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs=" \
    , ret, _PCTblName, _IsOuter, _MasterTblID, _MasterSetID
  print Array2List(_MasterFltIDs, _nFlt)
  printf ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=", _SlaveTblID, _SlaveSetID
  print Array2List(_SlaveFltIDs, _nFlt), "]\n"

  _TableID = ret
  _SetID  = -1

  # RD5GetJoinSlaveSet → 未サポート
  #   指定したIDのスレーブセットを取得します。 

  # RD5GetJoinDir
  # 指定したセットのJOINの方向を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  ret = Lfmtblrb.RD5GetJoinDir(_TableID, _SetID)
  printf "[RD5GetJoinDir] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5GetJoinProjectionSets
  # 指定されたJOINテーブルの累計数配列を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [out]   pnMasterSize  マスタ側累計数配列のサイズ
  #   [in]  nMasterGetCount   マスタ側取得サイズ
  #   [in,out]  pnMasterSetArray  取得されるマスタ側累計数配列
  #   [out]   pnSlaveSize   スレーブ側累計数配列のサイズ
  #   [in]  nSlaveGetCount  スレーブ側取得サイズ
  #   [in,out]  pnSlaveSetArray   取得されるスレーブ側累計数配列
  _MasterSize = Lfmutilrb::CTypeIntAr.new(1)
  _MGetCount  = 20
  _MSetArray  = Lfmutilrb::CTypeIntAr.new(_MGetCount)
  _SlaveSize  = Lfmutilrb::CTypeIntAr.new(1)
  _SGetCount  = 20
  _SSetArray  = Lfmutilrb::CTypeIntAr.new(_SGetCount)
  ret = Lfmtblrb.RD5GetJoinProjectionSets(_TableID, _SetID, _MasterSize.getPtr(), _MGetCount, _MSetArray.getPtr(), _SlaveSize.getPtr(), _SGetCount, _SSetArray.getPtr())
  printf "[RD5GetJoinProjectionSets] retval = %d [TableID=%d,SetID=%d,MasterSize=%d,MGetCount=%d,SlaveSize=%d,SGetCount=%d]\n" \
    , ret, _TableID, _SetID, _MasterSize.at(0), _MGetCount, _SlaveSize.at(0), _SGetCount
  print " MSetArray = ", Array2List(_MSetArray, _MasterSize.at(0)), "\n"
  print " SSetArray = ", Array2List(_SSetArray, _SlaveSize.at(0)), "\n"


  # RD5PutJoinSetToParent <- 後から移動
  # JOINにマッチした行、マッチしなかった行をセットとして生成します。.
  #   [in]  nJoinTableID  JOINテーブルID
  #   [in]  nPutSlave   セットを生成するテーブルを指定
  #   [in]  nPutJoinOut   生成するセットの種類を指定
  #   [out]   pnTargetTableID   セットが追加されたテーブルID
  #   [out]   pnTargetSetID   生成されたセットID
  _PutSlave      = 1
  _PutJoinOut    = 1
  _TargetTableID = Lfmutilrb::CTypeIntAr.new(1)
  _TargetSetID   = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5PutJoinSetToParent(_TableID, _PutSlave, _PutJoinOut, _TargetTableID.getPtr(), _TargetSetID.getPtr())
  printf "[RD5PutJoinSetToParent] retval = %d [JTableID=%d,PutSlave=%d,PutJoinOut=%d][TargetTableID=%d,TargetSetID=%d]\n" \
    , ret, _TableID, _PutSlave, _PutJoinOut, _TargetTableID.at(0), _TargetSetID.at(0)

  # RD5ReturnSet2SlaveTable <- 後から移動
  # JOINにマッチしたスレーブ側の行のセットを生成します。.
  #   [in]  nJoinTableID  JOINテーブルIDJOIN元スレーブテーブルID
  #   [in]  pnTargetTableID   JOIN元スレーブテーブルID
  _pTargetTableID = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5ReturnSet2SlaveTable(_TableID, _pTargetTableID.getPtr())
  printf "[RD5ReturnSet2SlaveTable] retval = %d [TableID=%d][pTargetTableID=%d]\n", ret, _TableID, _pTargetTableID.at(0)


  # reset
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()

  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile_MS
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5GetSetList
  # セットIDの一覧を取得します。
  #   [in]  nTableID  テーブルID
  #   [out]   anSetIDList   セットIDリスト
  _TableID = 1
  _SetIDList = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_SET_COUNT)
  ret = Lfmtblrb.RD5GetSetList(_TableID, _SetIDList.getPtr())
  printf "[RD5GetSetList] retval = %d [TableID=%d,SetIDList=", ret, _TableID
  print Array2List(_SetIDList, ret), "]\n"
  _nSet = ret

  # RD5GetSetIDList
  # 指定されたテーブルのセットのうち指定された個数のセットを取得します。（セット番号の昇順に取り出します。）
  #   [in]  nTableID  セットを取得したいテーブルのテーブルID
  #   [in]  nSize   受け取るセットの個数
  #   [out]   anSetIDList   セットを受け取る配列へのポインタ
  ret = Lfmtblrb.RD5GetSetIDList(_TableID, _nSet, _SetIDList.getPtr())
  printf "[RD5GetSetIDList] retval = %d [TableID=%d,Size=%d,SetIDList=", ret, _TableID, _nSet
  print Array2List(_SetIDList, ret), "]\n"

  # RD5AddSetReal → 未サポート
  # セットを追加します

  # RD5DeleteSet
  # セットを削除します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  _SetID = 3
  ret = Lfmtblrb.RD5DeleteSet(_TableID, _SetID)
  printf "[RD5DeleteSet] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5GetCurrentSetID
  # カレントのセットIDを取得します。
  ret = Lfmtblrb.RD5GetCurrentSetID(_TableID)
  printf "[RD5GetCurrentSetID] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5ChangeCurrentSetID
  # カレントセットを設定します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  カレントセットに設定するセットID
  _NewSetID = 2
  ret = Lfmtblrb.RD5ChangeCurrentSetID(_TableID, _NewSetID)
  printf "[RD5ChangeCurrentSetID] retval = %d [TableID=%d,NewSetID=%d]\n", ret, _TableID, _NewSetID

  # RD5GetCurrentSetID（確認）
  # カレントのセットIDを取得します。
  ret = Lfmtblrb.RD5GetCurrentSetID(_TableID)
  printf "[RD5GetCurrentSetID] retval = %d [TableID=%d]\n", ret, _TableID

  # RD5SetNotReal
  # 指定したサブセット以外のレコードからなるサブセットを作成します。
  # [in]  nTableID  テーブルID
  # [in]  nSetID  補集合を作成したいセットID
  _SetID = 2
  ret = Lfmtblrb.RD5SetNotReal(_TableID, _SetID)
  printf "[RD5SetNotReal] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5SetOpeReal
  # セットの共通集合／和集合／差集合を作成します
  #   [in]  nTableID  テーブルID
  #   [in]  nOpeNo  作成したいセットの種類
  #   [in]  nSetAID   1番目に指定するセットID（A）
  #   [in]  nSetBID   2番目に設定するセットID（B）
  _OpeNo = 1 # OR
  _SetAID = 2
  _SetBID = 4
  ret = Lfmtblrb.RD5SetOpeReal(_TableID, _OpeNo, _SetAID, _SetBID)
  printf "[RD5SetOpeReal] retval = %d [TableID=%d,OpeNo=%d,SetAID=%d,SetBID=%d]\n", ret, _TableID, _OpeNo, _SetAID, _SetBID

  # RD5PutJoinSetToParent -> 前に移動
  #   JOINにマッチした行、マッチしなかった行をセットとして生成します。.
  # RD5ReturnSet2SlaveTable -> 前に移動
  #   JOINにマッチしたスレーブ側の行のセットを生成します。.

  # RD5GetSetMemorySize
  #   セットの仕様メモリサイズを取得します。 (使用?)
  #   [in]  nTableID  テーブルID
  #   [out]   nSetID  セットID
  _SetID = 5
  ret = Lfmtblrb.RD5GetSetMemorySize(_TableID, _SetID)
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetSetMemorySize] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID
  end

  # RD5GetSubsetAttr  (★D5の関数呼んでない?)
  # セットのアトリビュート領域を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [out]   acAttrs   アトリビュート配列

  _ATTR_MAX = 8
  _Attrs = Lfmutilrb::CSubsetAttr.new()
  ret = _Attrs.getAttr(_TableID, _SetID)
  printf "[RD5GetSubsetAttr] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID
  for i in 0..._ATTR_MAX
    printf " Attrs.at(%d)=%d\n", i, _Attrs.at(i)
  end

  # RD5SetSubsetAttr  (★D5の関数呼んでない?)
  # セットのアトリビュート領域を設定します。 
  idx = 5
  val = 6
  _Attrs.put(idx, val)
  printf " Attrs.put(%d, %d)\n", idx, val
  ret = _Attrs.setAttr(_TableID, _SetID)
  printf "[RD5SetSubsetAttr] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID

  # RD5GetSubsetAttr（確認）  (★D5の関数呼んでない?)
  # セットのアトリビュート領域を設定します。 
  ret = _Attrs.getAttr(_TableID, _SetID)
  printf "[RD5GetSubsetAttr] retval = %d [TableID=%d,SetID=%d]\n", ret, _TableID, _SetID
  for i in 0..._ATTR_MAX
    printf " Attrs.at(%d)=%d\n", i, _Attrs.at(i)
  end

  print "### %s ### end\n" % funcName
  return
end

## 6-3-6 項目管理機能
def testFilter()
  funcName = "testFilter"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)

  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5GetNFilter
  # 項目の個数を取得します。
  _TableID = 1
  ret = Lfmtblrb.RD5GetNFilter(_TableID)
  printf "[RD5GetNFilter] retval = %d [TableID=%d]\n", ret, _TableID
  _nFlt = ret

  # RD5GetFilterIDList
  # 項目IDの一覧を取得します。
  #   [in]  nTableID  テーブルID
  #   [out]   anFilterIDList  項目IDリスト
  _IDList = Lfmutilrb::CTypeIntAr.new(_nFlt)
  ret = Lfmtblrb.RD5GetFilterIDList(_TableID, _IDList.getPtr())
  printf "[RD5GetFilterIDList] retval = %d [TableID=%d,IDList=", ret, _TableID
  print Array2List(_IDList, ret), "]\n"
  _nFlt = ret

  # RD5GetFilterWidth
  # 項目の幅を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  for i in 0..._nFlt
    ret = Lfmtblrb.RD5GetFilterWidth(_TableID, _IDList.at(i))
    printf "[RD5GetFilterWidth] retval = %d [TableID=%d,FltID=%d]\n", ret, _TableID, _IDList.at(i)
  end

  # RD5GetFilterType
  # 項目のデータ型を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  for i in 0..._nFlt
    ret = Lfmtblrb.RD5GetFilterType(_TableID, _IDList.at(i))
    printf "[RD5GetFilterType] retval = %d [TableID=%d,FltID=%d]\n", ret, _TableID, _IDList.at(i)
  end

  # RD5GetFilterInfo
  # 項目の情報を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [out]   pFilterInfo   項目情報
  for i in 0..._nFlt
    _FiltInfo = Lfmtblrb::TRFilterInfo.new()
    ret = Lfmtblrb.RD5GetFilterInfo(_TableID, _IDList.at(i), _FiltInfo)
    printf "[RD5GetFilterInfo] retval = %d [TableID=%d,FltID=%d][PVSize=%d,VLType=%d,VLWidth=%d,VLSize=%d,CharAreaSize=%d,FilterName=%s]\n" \
      , ret, _TableID, _IDList.at(i), _FiltInfo.PVSize, _FiltInfo.VLType, _FiltInfo.VLWidth, _FiltInfo.VLSize, _FiltInfo.CharAreaSize, _FiltInfo.FilterName
  end

  # RD5GetFilterAttr  (★D5の関数呼んでない?)
  # 項目のアトリビュート領域を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [out]   acAttrs   アトリビュート配列
  _ATTR_MAX = 8
  _FilterID = 6 # double
  _Attrs = Lfmutilrb::CFilterAttr.new()
  ret = _Attrs.getAttr(_TableID, _FilterID)
  printf "[RD5GetFilterAttr] retval = %d [TableID=%d,FilterID=%d]\n", ret, _TableID, _FilterID
  for i in 0..._ATTR_MAX
    printf " Attrs.at(%d)=%d\n", i, _Attrs.at(i)
  end

  # RD5GetFilterAttr  (★D5の関数呼んでない?)
  # 項目のアトリビュート領域を取得します。
  idx = 5 # 浮動小数項目の小数点以下グリッド表示桁数
  val = 6 # 桁数-3
  _Attrs.put(idx, val)
  printf " Attrs.put(%d, %d)\n", idx, val
  ret = _Attrs.setAttr(_TableID, _FilterID)
  printf "[RD5SetFilterAttr] retval = %d [TableID=%d,FilterID=%d]\n", ret, _TableID, _FilterID

  # RD5GetFilterAttr  (★D5の関数呼んでない?)
  # 項目のアトリビュート領域を取得します。
  ret = _Attrs.getAttr(_TableID, _FilterID)
  printf "[RD5GetFilterAttr] retval = %d [TableID=%d,FilterID=%d]\n", ret, _TableID, _FilterID
  for i in 0..._ATTR_MAX
    printf " Attrs.at(%d)=%d\n", i, _Attrs.at(i)
  end

  # RD5DeleteRealFilter -> 後に移動
  # 指定項目を削除します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID

  # RD5MoveRealFilter
  # 項目の位置を変更します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFromIndex  移動対象の位置
  #   [in]  nToIndex  挿入先の位置
  _FromIndex = 0
  _ToIndex = _nFlt
  for i in 0...3
    ret = Lfmtblrb.RD5MoveRealFilter(_TableID, _FromIndex, _ToIndex)
    printf "[RD5MoveRealFilter] retval = %d [TableID=%d,FromIndex=%d,ToIndex=%d]\n", ret, _TableID, _FromIndex, _ToIndex
  end

  # RD5DupRealFilter
  # 項目を複製します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   複製元の項目ID
  for i in 0..._nFlt
    ret = Lfmtblrb.RD5DupRealFilter(_TableID, _IDList.at(i))
    printf "[RD5DupRealFilter] retval = %d [TableID=%d,FltID=%d]\n", ret, _TableID, _IDList.at(i)
  end

  # RD5DupRealFilterEx
  # 任意のデータ型に変換して項目を複製します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   複製元の項目ID
  #   [in]  nDataType   作成するデータ型
  for i in 0..._nFlt
    _DestType = Lfmtblrb::D5_DT_STRING
    ret = Lfmtblrb.RD5DupRealFilterEx(_TableID, _IDList.at(i), _DestType)
    printf "[RD5DupRealFilterEx] retval = %d [TableID=%d,FltID=%d,DestType=%d]\n", ret, _TableID, _IDList.at(i), _DestType
  end

  # RD5DupRealFilterExNumeric
  # NUMERIC型のデータ型に変換して項目を複製します。.
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   複製元の項目ID
  #   [in]  nScale  項目に設定するScale値
  #   [in]  nRoundMode  項目に設定するRoundMode値
  _SrcFltID  = 16
  _Scale     = 20
  _RoundMode = 6
  ret = Lfmtblrb.RD5DupRealFilterExNumeric(_TableID, _SrcFltID, _Scale, _RoundMode)
  printf "[RD5DupRealFilterExNumeric] retval = %d [TableID=%d,SrcFltID=%d,Scale=%d,RoundMode=%d]\n" \
    , ret, _TableID, _SrcFltID, _Scale, _RoundMode

  # RD5AddRealFilter2
  # 項目を追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称

  _Loc           = 0
  _FilterName    = "add_dbl"
  _DataTypeNo    = Lfmtblrb::D5_DT_DOUBLE
  _DataArraySize = 10
  _DataUnitSize  = 4
  _FilePath      = PathIn
  _FileName      = SampleFilterData
  ret = Lfmtblrb.RD5AddRealFilter2(_TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, _FilePath, _FileName

  # RD5AddRealFilter2Numeric
  # NUMERIC型の項目を追加します。NUMERIC型の項目に必要なNumericInfo構造体を同時に設定します。.
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nScale  NumericInfo構造体に設定するScale値
  #   [in]  nRoundMode  NumericInfo構造体に設定するRoundMode値
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  _FilterName   = "add_num"
  _DataTypeNo   = Lfmtblrb::D5_DT_DECIMAL
  _DataUnitSize = 16
  _Scale        = 3
  _RoundMode    = 4
  ret = Lfmtblrb.RD5AddRealFilter2Numeric(_TableID, _Loc, _FilterName, _DataArraySize, _Scale, _RoundMode, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2Numeric] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataArraySize=%d,Scale=%d,RoundMode=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataArraySize, _Scale, _RoundMode, _FilePath, _FileName

  # RD5DeleteRealFilter
  # 指定項目を削除します
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  _FltID = 20
  ret = Lfmtblrb.RD5DeleteRealFilter(_TableID, _FltID)
  printf "[RD5DeleteRealFilter] retval = %d [TableID=%d,FltID=%d]\n", ret, _TableID, _FltID

  # RD5GetSlaveInfo -> 後に移動
  # スレーブ側テーブルの項目一覧を取得します。
  # RD5MoveSlaveFlt2Master -> 後に移動
  #   スレーブテーブルの項目をマスタテーブルに転送します。
  # RD5GetFilterIDFromName
  # 項目名称から項目IDを取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  szFilterName  項目名称
  _FilterName = "add_num"
  ret = Lfmtblrb.RD5GetFilterIDFromName(_TableID, _FilterName)
  printf "[RD5GetFilterIDFromName] retval = %d [TableID=%d,FilterName=%s]\n", ret, _TableID, _FilterName
  _FilterID = ret

  # RD5GetFilterIDFromName2
  # REALテーブル又はJOINテーブルの項目名称から項目IDを取得します。.
  #   [in]  nTableID  テーブルID（JOINテーブル又はREALテーブル）
  #   [in]  nIsSlave  JOINテーブルの場合、マスタ側かスレーブ側かを指定
  #   [in]  szFilterName  項目名称
  _isSlave = 0
  ret = Lfmtblrb.RD5GetFilterIDFromName2(_TableID, _isSlave, _FilterName)
  printf "[RD5GetFilterIDFromName2] retval = %d [TableID=%d,isSlave=%d,FilterName=%s]\n", ret, _TableID, _isSlave, _FilterName

  # RD5SetFilterName
  # 項目の名称を変更します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  szFilterName  項目の新規名称
  _FilterName = "add_num_RN"
  ret = Lfmtblrb.RD5SetFilterName(_TableID, _FilterID, _FilterName)
  printf "[RD5SetFilterName] retval = %d [TableID=%d,FilterID=%d,FilterName=%s]\n", ret, _TableID, _FilterID, _FilterName

  # RD5GetFilterName -> RD5GetFilterNameR1
  # 項目IDから項目名称を取得します。 
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  ret = decode($ENC_DB, Lfmtblrb.RD5GetFilterNameR1(_TableID, _FilterID))
  printf "[RD5GetFilterNameR1] retval = %s [TableID=%d,FilterID=%d]\n", ret, _TableID, _FilterID

  # RD5GetFilterMemorySize
  # 項目の使用メモリサイズを取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  ret = Lfmtblrb.RD5GetFilterMemorySize(_TableID, _FilterID)
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetFilterMemorySize] retval = %d [TableID=%d,FilterID=%d]\n", ret, _TableID, _FilterID
  end

  # RD5GetAllFilterInfo → 未サポート
  #   項目情報を取得します

  # RD5SetNumericInfo
  # NUMERIC項目情報をセットします。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   フィルタID
  #   [in]  pNumericInfo  NUMERIC項目情報
  _NInfo = Lfmutilrb::CNumericInfo.new(10, 6)
  ret = Lfmtblrb.RD5SetNumericInfo(_TableID, _FilterID, _NInfo.getPtr())
  printf "[RD5SetNumericInfo] retval = %d [TableID=%d,FilterID=%d,scale=%d,rounding_mode=%d]\n" \
    , ret, _TableID, _FilterID, _NInfo.getScale(), _NInfo.getRoundingMode()

  # RD5GetNumericInfo -> RD5GetNumericInfoR1
  # NUMERIC項目情報を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   フィルタID
  #   [out]   pNumericInfo  NUMERIC項目情報
  ret = Lfmtblrb.RD5GetNumericInfoR1(_TableID, _FilterID, _NInfo.getPtr())
  printf "[RD5GetNumericInfoR1] retval = %d [TableID=%d,FilterID=%d,scale=%d,rounding_mode=%d]\n" \
    , ret, _TableID, _FilterID, _NInfo.getScale(), _NInfo.getRoundingMode()


  # reset
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  _Name = SampleD5DFile_JOIN
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # JOIN
  _PCTblName   = "JoinTbl"
  _IsOuter     = 0
  _MasterTblID = 1
  _MasterSetID = 1
  #_nFlt = Lfmtblrb::D5_MAX_JOIN_KEY
  _nFlt = 2
  _MasterFltIDs = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _MasterFltIDs.put(0, 2)
  _MasterFltIDs.put(1, 0)
  _SlaveTblID   = 2
  _SlaveSetID   = 1
  _SlaveFltIDs  = Lfmutilrb::CTypeIntAr.new(_nFlt)
  _SlaveFltIDs.put(0, 1)
  _SlaveFltIDs.put(1, 0)
  # RD5AddJoinTable
  # JOINテーブルを作成します。.
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  ret = Lfmtblrb.RD5AddJoinTable(_PCTblName, _IsOuter, _MasterTblID, _MasterSetID, _MasterFltIDs.getPtr(), _SlaveTblID, _SlaveSetID, _SlaveFltIDs.getPtr())
  printf "[RD5AddJoinTable] retval = %d [PCTblName=%s,IsOuter=%d,MasterTblID=%d,MasterSetID=%d,MasterFltIDs=" \
    , ret, _PCTblName, _IsOuter, _MasterTblID, _MasterSetID
  print Array2List(_MasterFltIDs, _nFlt)
  printf ",SlaveTblID=%d,SlaveSetID=%d,SlaveFltIDs=", _SlaveTblID, _SlaveSetID
  print Array2List(_SlaveFltIDs, _nFlt), "]\n"


  _TableID  = ret

  # RD5GetSlaveInfo <- 前から移動
  # スレーブ側テーブルの項目一覧を取得します。
  #   [in]  nJoinTableID  JOINテーブルID
  #   [out]   pnMasterTableID   マスタテーブルID
  #   [out]   pnMasterSetID   JOIN作成時に使用したマスタテーブルのセットID
  #   [out]   pnSlaveTableID  スレーブテーブルID
  #   [out]   pnSlaveSetID  JOIN作成時に使用したスレーブテーブルのセットID
  #   [out]   pnSlaveFilterCount  スレーブテーブルの項目数
  #   [out]   anSlaveFilterIDs  スレーブテーブルの項目ID一覧
  _MasterTableID  = Lfmutilrb::CTypeIntAr.new(1)
  _MasterSetID    = Lfmutilrb::CTypeIntAr.new(1)
  _SlaveTableID   = Lfmutilrb::CTypeIntAr.new(1)
  _SlaveSetID     = Lfmutilrb::CTypeIntAr.new(1)
  _nSlaveFilters  = Lfmutilrb::CTypeIntAr.new(1)
  _SlaveFilterIDs = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_REAL)
  ret = Lfmtblrb.RD5GetSlaveInfo(_TableID, _MasterTableID.getPtr(), _MasterSetID.getPtr() \
                , _SlaveTableID.getPtr(), _SlaveSetID.getPtr(), _nSlaveFilters.getPtr(), _SlaveFilterIDs.getPtr())
  printf "[RD5GetSlaveInfo] retval = %d [JoinTableID=%d][MasterTableID=%d,MasterSetID=%d,SlaveTableID=%d,SlaveSetID=%d,nSlaveFilters=%d,SlaveFilterIDs=" \
    , ret, _TableID, _MasterTableID.at(0), _MasterSetID.at(0), _SlaveTableID.at(0), _SlaveSetID.at(0), _nSlaveFilters.at(0)
  print Array2List(_SlaveFilterIDs, _nSlaveFilters.at(0)), "]\n"

  # RD5MoveSlaveFlt2Master <- 前から移動
  # スレーブテーブルの項目をマスタテーブルに転送します。
  #   [in]  nJoinTableID  JOINテーブルID
  #   [in]  nSlaveFilterID  転送元のスレーブテーブルの項目ID
  _SlaveFltID = 2
  ret = Lfmtblrb.RD5MoveSlaveFlt2Master(_TableID, _SlaveFltID)
  printf "[RD5MoveSlaveFlt2Master] retval = %d [JoinTableID=%d,SlaveFltID=%d]\n", ret, _TableID, _SlaveFltID

  printf "### %s ### end\n", funcName
  return
end

## 6-3-7 値ジャンプ機能
def testFind()
  funcName = "testFind"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()

  # エンジンのDB文字コードを設定します。
  _ENC_DB = "Shift_JIS"
  ret = Lfmtblrb.RD5SetDBCharCode(_ENC_DB)

  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile_SJIS
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5FindRecNoReal
  # 行番号からセット内順序番号を検索します。 
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nTargetRecNo  検索対象の行番号
  _RealTblID   = 1
  _SetID       = -1
  _TargetRecNo = 10
  ret = Lfmtblrb.RD5FindRecNoReal(_RealTblID, _SetID, _TargetRecNo)
  printf "[RD5FindRecNoReal] retval = %d [RealTblID=%d,SetID=%d,TargetRecNo=%d]\n", ret, _RealTblID, _SetID, _TargetRecNo

  # RD5OpenStrFindReal
  # 文字列型の項目を条件として、値ジャンプ機能をオープンします。
  #   [in]  nTableID  検索するテーブルID
  #   [in]  nFilterID   検索対象となる整数型の項目ID
  #   [in]  nValSrchKind  検索条件式を指定する値
  #   [in]  nSrchVal1   1番目の検索条件値
  #   [in]  nSrchVal2   2番目の検索条件値
  _SrchFltID   = 8
  _StrSrchKind = Lfmtblrb::D5_OPETYPE_STR_MID
  _SrchStr1    = "t"
  _SrchStr2    = ""
  ret = Lfmtblrb.RD5OpenStrFindReal(_RealTblID, _SrchFltID, _StrSrchKind, encode(_ENC_DB, _SrchStr1), encode(_ENC_DB, _SrchStr2))
  printf "[RD5OpenStrFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s]\n" \
    , ret, _RealTblID, _SrchFltID, _StrSrchKind, _SrchStr1, _SrchStr2

  # RD5OpenIntFindReal
  # 整数型の項目を条件として、値ジャンプ機能をオープンします。
  #   [in]  nTableID  検索するテーブルID
  #   [in]  nFilterID   検索対象となる整数型の項目ID
  #   [in]  nValSrchKind  検索条件式を指定する値
  #   [in]  nSrchVal1   1番目の検索条件値
  #   [in]  nSrchVal2   2番目の検索条件値
  _SrchFltID   = 1
  _ValSrchKind = Lfmtblrb::D5_OPETYPE_BETWEEN
  _SrchVal1    = 3
  _SrchVal2    = 7
  ret = Lfmtblrb.RD5OpenIntFindReal(_RealTblID, _SrchFltID, _ValSrchKind, _SrchVal1, _SrchVal2)
  printf "[RD5OpenIntFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%d,SrchVal2=%d]\n" \
    , ret, _RealTblID, _SrchFltID, _ValSrchKind, _SrchVal1, _SrchVal2

  # RD5OpenFloatFindReal
  # 浮動小数点型の項目を条件として、値ジャンプ機能をオープンします。
  #   [in]  nTableID  検索するテーブルID
  #   [in]  nFilterID   検索対象となる浮動小数点型の項目ID
  #   [in]  nValSrchKind  検索条件式を指定する値
  #   [in]  dSrchVal1   1番目の検索条件値
  #   [in]  dSrchVal2   2番目の検索条件値
  _SrchFltID   = 6
  _ValSrchKind = Lfmtblrb::D5_OPETYPE_BETWEEN
  _SrchVal1    = 0.3
  _SrchVal2    = 0.7
  ret = Lfmtblrb.RD5OpenFloatFindReal(_RealTblID, _SrchFltID, _ValSrchKind, _SrchVal1, _SrchVal2)
  printf "[RD5OpenFloatFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%f,SrchVal2=%f]\n" \
    , ret, _RealTblID, _SrchFltID, _ValSrchKind, _SrchVal1, _SrchVal2

  # RD5GetFindStatus
  # 検索ステータスを取得します。
  #   [in]  nTableID  検索するテーブルID
  #   [out]   pnHitCount  ルートセットで、検索条件に一致した件数
  #   [out]   pnFilterID  検索対象の項目ID
  _nHit = Lfmutilrb::CTypeIntAr.new(1)
  _FindFltID = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5GetFindStatus(_RealTblID, _nHit.getPtr(), _FindFltID.getPtr())
  printf "[RD5GetFindStatus] retval = %d [RealTblID=%d,nHit=%d,FindFltID=%d]\n" \
    , ret, _RealTblID, _nHit.at(0), _FindFltID.at(0)
  _SrchID = ret

  # RD5GetNextHitReal
  # 値ジャンプで条件に一致する行を見つけます。
  #   [in]  nTableID  テーブルID
  #   [in]  nSrchID   検索ID
  #   [in]  nSetID  検索対象のセットID
  #   [in]  nCurPos   現在の位置
  #   [in]  nDir  検索方向
  #   [out]   pnFilterID  検索対象の項目ID
  #   [out]   pnNextPos   検索条件に一致するセット内順序番号
  _CurPos  = 0
  _Dir     = 0
  _FltID   = Lfmutilrb::CTypeIntAr.new(1)
  _NextPos = Lfmutilrb::CTypeIntAr.new(1)
  while ret > 0
    ret = Lfmtblrb.RD5GetNextHitReal(_RealTblID, _SrchID, _SetID, _CurPos, _Dir, _FltID.getPtr(), _NextPos.getPtr())
    printf "[RD5GetNextHitReal] retval = %d [RealTblID=%d,SrchID=%d,SetID=%d,CurPos=%d,Dir=%d,FltID=%d,NextPos=%d]\n" \
      , ret, _RealTblID, _SrchID, _SetID, _CurPos, _Dir, _FltID.at(0), _NextPos.at(0)
    _CurPos = _NextPos.at(0)
  end

  # RD5CloseFindReal
  # 値ジャンプをクローズします。
  #   [in]  nTableID  テーブルID
  ret = Lfmtblrb.RD5CloseFindReal(_RealTblID)
  printf "[RD5CloseFindReal] retval = %d [RealTblID=%d]\n", ret, _RealTblID

  # RD5OpenStrFindRealLocale
  # 文字列型の項目を条件として、値ジャンプ機能をオープンします。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   検索対象となる文字列型の項目ID
  #   [in]  nStrSrchKind  検索条件式を指定する値
  #   [in]  szSrchStr1  1番目の検索条件文字列
  #   [in]  szSrchStr2  2番目の検索条件文字列
  #   [in]  nLocaleID   文字コードID
  _SrchFltID   = 2
  _StrSrchKind = Lfmtblrb::D5_OPETYPE_BETWEEN
  _SrchStr1    = "０３"
  _SrchStr2    = "０７"
  _LocaleID    = 0
  ret = Lfmtblrb.RD5OpenStrFindRealLocale(_RealTblID, _SrchFltID, _StrSrchKind, encode(_ENC_DB, _SrchStr1), encode(_ENC_DB, _SrchStr2), _LocaleID)
  printf "[RD5OpenStrFindRealLocale] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s,LocaleID=%d]\n" \
    , ret, _RealTblID, _SrchFltID, _StrSrchKind, _SrchStr1, _SrchStr2, _LocaleID

  # RD5OpenStrFindRealSJIS
  # SJISコードの文字列型の項目を条件として、値ジャンプ機能をオープンします。.
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   検索対象となる文字列型の項目ID
  #   [in]  nStrSrchKind  検索条件式を指定する値
  #   [in]  szSrchStr1  1番目の検索条件文字列
  #   [in]  szSrchStr2  2番目の検索条件文字列
  ret = Lfmtblrb.RD5OpenStrFindRealSJIS(_RealTblID, _SrchFltID, _StrSrchKind, encode(_ENC_DB, _SrchStr1), encode(_ENC_DB, _SrchStr2))
  printf "[RD5OpenStrFindRealSJIS] retval = %d [RealTblID=%d,SrchFltID=%d,StrSrchKind=%d,SrchStr1=%s,SrchStr2=%s]\n" \
    , ret, _RealTblID, _SrchFltID, _StrSrchKind, _SrchStr1, _SrchStr2

  # RD5OpenNumericFindReal
  # 浮動小数点型の項目を条件として、値ジャンプ機能をオープンします。
  #   [in]  nTableID  検索するテーブルID
  #   [in]  nFilterID   検索対象となる浮動小数点型の項目ID
  #   [in]  nValSrchKind  検索条件式を指定する値
  #   [in]  SrchVal1  1番目の検索条件値
  #   [in]  SrchVal2  2番目の検索条件値
  _SrchFltID    = 7
  _ValSrchKind  = Lfmtblrb::D5_OPETYPE_BETWEEN
  _SrchVal1     = "0.03"
  _SrchVal2     = "0.07"
  _NInfo = Lfmutilrb::CNumericInfo.new()
  # NUMERIC項目情報を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   フィルタID
  #   [out]   pNumericInfo  NUMERIC項目情報
  ret = Lfmtblrb.RD5GetNumericInfoR1(_RealTblID, _SrchFltID, _NInfo.getPtr())
  _nSrchVal1 = Lfmutilrb::CNumeric.new(_SrchVal1, _NInfo.getScale(), _NInfo.getRoundingMode())
  _nSrchVal2 = Lfmutilrb::CNumeric.new(_SrchVal2, _NInfo.getScale(), _NInfo.getRoundingMode())
  ret = Lfmtblrb.RD5OpenNumericFindReal(_RealTblID, _SrchFltID, _ValSrchKind, _nSrchVal1.getPtr(), _nSrchVal2.getPtr())
  printf "[RD5OpenNumericFindReal] retval = %d [RealTblID=%d,SrchFltID=%d,ValSrchKind=%d,SrchVal1=%s,SrchVal2=%s]\n" \
    , ret, _RealTblID, _SrchFltID, _ValSrchKind, _SrchVal1, _SrchVal2

  printf "### %s ### end\n", funcName
  return
end

## 6-3-8 数値のカテゴライズ
def testCategory()
  funcName = "testCategory"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  _Name = SampleD5DFile
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # カテゴリ定義テーブル作成 開始 --------------------------------------------------
  # Table
  _PCTblName = "CATEGORY_TABLE"
  _RowCount  = 3
  # REALテーブルを新規作成します。. 
  #   [in]  szTableName   作成するテーブル名称
  #   [in]  nRowCount   行数
  ret = Lfmtblrb.RD5AddRealTable(_PCTblName, _RowCount)
  printf "[RD5AddRealTable] retval = %d [PCTblName=%s,RowCount=%d]\n", ret, _PCTblName, _RowCount
  _TableID = ret
  _SetID   = 1
  _DataArraySize = _RowCount

  # オペコード項目
  _Loc = 0
  _FilterName   = "オペコード"
  _DataTypeNo   = Lfmtblrb::D5_DT_STRING
  _DataUnitSize = 0
  _FilePath     = ""
  _FileName     = ""
  # 項目を追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  ret = Lfmtblrb.RD5AddRealFilter2(_TableID, _Loc, encode($ENC_DB, _FilterName), _DataTypeNo, _DataArraySize, _DataUnitSize, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, _FilePath, _FileName
  _FltID = ret
  # データ(文字列)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  szWriteData   書き込みデータ
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 1, "<")
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 2, "<=>")
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 3, ">")

  # 第1引数
  _Loc = 1
  _FilterName   = "第1引数"
  _DataTypeNo   = Lfmtblrb::D5_DT_DOUBLE
  _DataUnitSize = 4
  # 項目を追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  ret = Lfmtblrb.RD5AddRealFilter2(_TableID, _Loc, encode($ENC_DB, _FilterName), _DataTypeNo, _DataArraySize, _DataUnitSize, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, _FilePath, _FileName
  _FltID = ret
  # データ(浮動少数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  dWriteData  書き込みデータ
  ret = Lfmtblrb.RD5OverwriteRealExDblR1(_TableID, _SetID, _FltID, 1, 3)
  ret = Lfmtblrb.RD5OverwriteRealExDblR1(_TableID, _SetID, _FltID, 2, 3)
  ret = Lfmtblrb.RD5OverwriteRealExDblR1(_TableID, _SetID, _FltID, 3, 7)

  # 第2引数
  _Loc = 2
  _FilterName   = "第2引数"
  _DataTypeNo   = Lfmtblrb::D5_DT_DOUBLE
  _DataUnitSize = 4
  # 項目を追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  ret = Lfmtblrb.RD5AddRealFilter2(_TableID, _Loc, encode($ENC_DB, _FilterName), _DataTypeNo, _DataArraySize, _DataUnitSize,encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, _FilePath, _FileName
  _FltID = ret
  # データ(浮動少数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  dWriteData  書き込みデータ
  ret = Lfmtblrb.RD5OverwriteRealExDblR1(_TableID, _SetID, _FltID, 2, 7)

  # 分類名称
  _Loc = 3
  _FilterName   = "分類名称"
  _DataTypeNo   = Lfmtblrb::D5_DT_STRING
  _DataUnitSize = 0
  # 項目を追加します。
  #   [in]  nTableID  追加するテーブルID
  #   [in]  nLoc  項目挿入位置
  #   [in]  szFilterName  新規に追加する項目名称
  #   [in]  nDataType   追加項目のデータ型
  #   [in]  nDataArraySize  追加するレコード配列のサイズ
  #   [in]  nDataUnitSize   1レコードのサイズ(byte)
  #   [in]  szFilePath  追加するデータのファイルパス
  #   [in]  szFileName  追加するデータのファイル名称
  ret = Lfmtblrb.RD5AddRealFilter2(_TableID, _Loc, encode($ENC_DB, _FilterName), _DataTypeNo, _DataArraySize, _DataUnitSize, encode($ENC_OS, _FilePath), encode($ENC_OS, _FileName))
  printf "[RD5AddRealFilter2] retval = %d [TableID=%d,Loc=%d,FilterName=%s,DataTypeNo=%d,DataArraySize=%d,DataUnitSize=%d,FilePath=%s,FileName=%s]\n" \
    , ret, _TableID, _Loc, _FilterName, _DataTypeNo, _DataArraySize, _DataUnitSize, _FilePath, _FileName
  _FltID = ret

  # データ(文字列)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  szWriteData   書き込みデータ
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 1, encode($ENC_DB, "～2"))
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 2, encode($ENC_DB, "3～7"))
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, 3, encode($ENC_DB, "8～"))
  # カテゴリ定義テーブル作成 終了 --------------------------------------------------

  # RD5AddCategoryReal
  # カテゴリ定義に基づき分類を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nCategoryTableID  カテゴリ定義テーブルID
  _TargetTblID   = 1
  _TargetFltID   = 1
  _CategoryTblID = _TableID
  ret = Lfmtblrb.RD5AddCategoryReal(_TargetTblID, _TargetFltID, _CategoryTblID)
  printf "[RD5AddCategoryReal] retval = %d [TargetTblID=%d,TargetFltID=%d,CategoryTblID=%d]\n", ret, _TargetTblID, _TargetFltID, _CategoryTblID

  printf "### %s ### end\n", funcName
  return
end

## 6-3-9 計算機能
def testCalc()
  funcName = "testCalc"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5CalcReal
  # 計算処理を行います。
  #   [in]  nTableID  計算を行うテーブルID
  #   [in]  nSetID  計算を行うセットID
  #   [in]  nFilterID   計算を行う項目ID
  #   [in]  nCalStart   計算開始位置
  #   [in]  nCalCount   計算するレコード数
  #   [in]  szFormula   計算式
  #   [out]   szErrorRep  エラー説明
  _TargetTblID = 1
  _TargetSetID = -1
  _TargetFID   = 7
  _CalStart    = 1
  _CalCount    = 10
  _PCFormula   = "+(@int,@dbl)"
  _ErrorRep    = "                                                                "
  ret = Lfmtblrb.RD5CalcReal(_TargetTblID, _TargetSetID, _TargetFID, _CalStart, _CalCount, _PCFormula, _ErrorRep)
  printf "[RD5CalcReal] retval = %d [TargetTblID=%d,TargetSetID=%d,TargetFID=%d,CalStart=%d,CalCount=%d,PCFormula=%s,ErrorRep=%s]\n" \
    , ret, _TargetTblID, _TargetSetID, _TargetFID, _CalStart, _CalCount, _PCFormula, _ErrorRep

  printf "### %s ### end\n", funcName
  return
end

## 6-3-10 編集機能
def testEdit()
  funcName = "testEdit"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5TableCanEdit
  # テーブルが編集可能であるかを調べます。
  # [in]  nTableID  調べる対象のテーブルID
  # [out]   anReferIDs  このテーブルを参照しているテーブルIDの一覧
  _TableID = 1
  _PReferIDs = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_TABLE_COUNT)
  ret = Lfmtblrb.RD5TableCanEdit(_TableID, _PReferIDs.getPtr())
  printf "[RD5TableCanEdit] retval = %d [TableID=%d,PReferIDs=", ret, _TableID
  print Array2List(_PReferIDs, ret), "]\n"

  # RD5DeleteRealRows
  # 行を削除します。
  # [in]  nTableID  テーブルID
  # [in]  nDelStart   削除開始行
  # [in]  nDelCount   削除する行数

  _DelStart = 5
  _DelCount = 3
  ret = Lfmtblrb.RD5DeleteRealRows(_TableID, _DelStart, _DelCount)
  printf "[RD5DeleteRealRows] retval = %d [TableID=%d,DelStart=%d,DelCount=%d]\n", ret, _TableID, _DelStart, _DelCount

  # RD5DeleteRealRowsEx
  # 行を削除します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nDelStart   削除開始行
  #   [in]  nDelCount   削除する行数
  _SetID = 1
  ret = Lfmtblrb.RD5DeleteRealRowsEx(_TableID, _SetID, _DelStart, _DelCount)
  printf "[RD5DeleteRealRowsEx] retval = %d [TableID=%d,SetID=%d,DelStart=%d,DelCount=%d]\n", ret, _TableID, _SetID, _DelStart, _DelCount

  # RD5InsertRealRows
  # 行を挿入します。
  #   [in]  nTableID  テーブルID
  #   [in]  nInsPos   挿入位置
  #   [in]  nInsCount   挿入する行数
  _InsPos   = 5
  _InsCount = 6
  ret = Lfmtblrb.RD5InsertRealRows(_TableID, _InsPos, _InsCount)
  printf "[RD5InsertRealRows] retval = %d [TableID=%d,InsPos=%d,InsCount=%d]\n", ret, _TableID, _InsPos, _InsCount


  _RowCount = 10

  # RD5OverwriteRealEx
  # データを上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWriteStart   書き込み開始位置
  #   [in]  nWriteCount   書き込み数
  #   [in]  pvWriteData   書き込みデータ
  _TableID    = 1
  _SetID      = 1
  _WriteStart = 1
  _WriteCount = 10

  # int
  _FltID = 1
  _PWData = Lfmutilrb::CTypeIntAr.new(_WriteCount)
  for i in 0..._WriteCount
    _PWData.put(i, i + 10)
  end
  ret = Lfmtblrb.RD5OverwriteRealEx(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _PWData.getVPtr())
  printf "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount

  # double
  _FltID = 6
  _PWData = Lfmutilrb::CTypeDblAr.new(_WriteCount)
  for i in 0..._WriteCount
    _PWData.put(i, i + 10.0)
  end
  ret = Lfmtblrb.RD5OverwriteRealEx(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _PWData.getVPtr())
  printf "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount

  # Numeric
  _FltID = 7
  _NInfo = Lfmutilrb::CNumericInfo.new()
  ret = Lfmtblrb.RD5GetNumericInfoR1(_TableID, _FltID, _NInfo.getPtr())
  _PWData = Lfmutilrb::CTypeNumAr.new(_WriteCount, _NInfo.getScale(), _NInfo.getRoundingMode())
  for i in 0..._WriteCount
    _PWData.put(i, (i + 10).to_s)
  end
  ret = Lfmtblrb.RD5OverwriteRealEx(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _PWData.getVPtr())
  printf "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount

  # string
  _FltID = 2
  _PWData = Lfmutilrb::CTypeStrAr.new(_WriteCount)
  for i in 0..._WriteCount
    _PWData.put(i, encode($ENC_OS, (i + 10).to_s))
  end
  ret = Lfmtblrb.RD5OverwriteRealEx(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _PWData.getVPtr())
  printf "[RD5OverwriteRealEx] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount


  _WritePos = 5

  # RD5OverwriteRealExIntR1
  # データ(整数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  nWriteData  書き込みデータ
  _FltID = 1
  _nData = -_WritePos
  ret = Lfmtblrb.RD5OverwriteRealExIntR1(_TableID, _SetID, _FltID, _WritePos, _nData)
  printf "[RD5OverwriteRealExIntR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WritePos, _nData

  # RD5OverwriteRealExDblR1
  # データ(浮動少数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  dWriteData  書き込みデータ
  _FltID = 6
  _nData = -_WritePos.to_f / 10
  ret = Lfmtblrb.RD5OverwriteRealExDblR1(_TableID, _SetID, _FltID, _WritePos, _nData)
  printf "[RD5OverwriteRealExDblR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%f]\n" \
    , ret, _TableID, _SetID, _FltID, _WritePos, _nData

  # RD5OverwriteRealExNumericR1
  # データ(Numeric)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  pWriteData  書き込みデータ
  _FltID = 7
  _sData = (-_WritePos.to_f / 10).to_s
  _nData = Lfmutilrb::CNumeric.new(_sData, _NInfo.getScale(), _NInfo.getRoundingMode())
  ret = Lfmtblrb.RD5OverwriteRealExNumericR1(_TableID, _SetID, _FltID, _WritePos, _nData.getPtr())
  printf "[RD5OverwriteRealExNumericR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%s]\n" \
    , ret, _TableID, _SetID, _FltID, _WritePos, _sData;

  # RD5OverwriteRealExStrR1
  # データ(文字列)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWritePos   書き込み位置
  #   [in]  szWriteData   書き込みデータ
  _FltID = 2
  _nData = (-_WritePos.to_f / 10).to_s
  ret = Lfmtblrb.RD5OverwriteRealExStrR1(_TableID, _SetID, _FltID, _WritePos, _nData)
  printf "[RD5OverwriteRealExStrR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WritePos=%d,nData=%s]\n" \
    , ret, _TableID, _SetID, _FltID, _WritePos, _nData


  _WriteStart = 1
  _WriteCount = _RowCount

  # RD5FillRealEx -> RD5FillRealExIntR1
  # データ(整数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWriteStart   書き込み開始位置
  #   [in]  nWriteCount   書き込み数
  #   [in]  nWriteData  書き込みデータ
  _FltID = 1
  _nData = _RowCount - 5
  ret = Lfmtblrb.RD5FillRealExIntR1(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData)
  printf "[RD5FillRealExIntR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%d]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData

  # RD5FillRealEx -> RD5FillRealExDblR1
  # データ(浮動少数)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWriteStart   書き込み開始位置
  #   [in]  nWriteCount   書き込み数
  #   [in]  dWriteData  書き込みデータ
  _FltID = 6
  _nData = (_RowCount.to_f - 5) / 10
  ret = Lfmtblrb.RD5FillRealExDblR1(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData)
  printf "[RD5FillRealExDblR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%f]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData

  # RD5FillRealEx -> RD5FillRealExNumericR1
  # データ(Numeric)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWriteStart   書き込み開始位置
  #   [in]  nWriteCount   書き込み数
  #   [in]  pWriteData  書き込みデータ
  _FltID = 7
  _sData = ((_RowCount.to_f - 5) / 10).to_s
  _nData = Lfmutilrb::CNumeric.new(_sData, _NInfo.getScale(), _NInfo.getRoundingMode())
  ret = Lfmtblrb.RD5FillRealExNumericR1(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData.getPtr())
  printf "[RD5FillRealExNumericR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%s]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount, _sData

  # RD5FillRealEx -> RD5FillRealExStrR1
  # データ(文字列)を上書きします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nWriteStart   書き込み開始位置
  #   [in]  nWriteCount   書き込み数
  #   [in]  szWriteData   書き込みデータ
  _FltID = 2
  _nData = ((_RowCount.to_f - 5) / 10).to_s
  ret = Lfmtblrb.RD5FillRealExStrR1(_TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData)
  printf "[RD5FillRealExStrR1] retval = %d [TableID=%d,SetID=%d,FltID=%d,WriteStart=%d,WriteCount=%d,nData=%s]\n" \
    , ret, _TableID, _SetID, _FltID, _WriteStart, _WriteCount, _nData

  printf "### %s ### end\n", funcName
  return
end

## 6-3-11 データ取得機能
def testGetData()
  funcName = "testGetData"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  _TableID  = 1
  _SetID    = 1
  _RowCount = 10

  # RD5GetData1 -> RD5GetData1IntR1
  # 単一データ(整数)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  _FltID = 1
  for _RowNo in 1.._RowCount
    ret = Lfmtblrb.RD5GetData1IntR1(_TableID, _FltID, _SetID, _RowNo)
    printf "[RD5GetData1IntR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]\n", ret, _TableID, _FltID, _SetID, _RowNo
  end

  # RD5GetData1 -> RD5GetData1DblR1
  # 単一データ(浮動少数)を取得します。 
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  _FltID = 6
  for _RowNo in 1.._RowCount
    ret = Lfmtblrb.RD5GetData1DblR1(_TableID, _FltID, _SetID, _RowNo)
    printf "[RD5GetData1DblR1] retval = %f [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]\n", ret, _TableID, _FltID, _SetID, _RowNo
  end

  # RD5GetData1 -> RD5GetData1NumericR1
  # 単一データ(Numeric)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  #   [out]   pNumeric  取得したデータ
  _FltID = 7
  _NInfo = Lfmutilrb::CNumericInfo.new()
  ret = Lfmtblrb.RD5GetNumericInfoR1(_TableID, _FltID, _NInfo.getPtr())
  _ndata = Lfmutilrb::CNumeric.new()
  for _RowNo in 1.._RowCount
    ret = Lfmtblrb.RD5GetData1NumericR1(_TableID, _FltID, _SetID, _RowNo, _ndata.getPtr())
    _sdata = Lfmtblrb.RD5NumericNum2StrR1(_ndata.getPtr(), _NInfo.getPtr(), 0, _NInfo.getScale())
    _data = BigDecimal(_sdata)
    printf "[RD5GetData1NumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,RowNo=%d,numVal=[%s]->[%f]]\n" \
      , ret, _TableID, _FltID, _SetID, _RowNo, _sdata, _data
  end

  # RD5GetData1 -> RD5GetData1StrR1
  # 単一データ(文字列)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  _FltID = 2
  for _RowNo in 1.._RowCount
    ret = decode($ENC_DB, Lfmtblrb.RD5GetData1StrR1(_TableID, _FltID, _SetID, _RowNo))
    printf "[RD5GetData1StrR1] retval = %s [TableID=%d,FltID=%d,SetID=%d,RowNo=%d]\n" \
      , ret, _TableID, _FltID, _SetID, _RowNo
  end


  _RowNo = 1
  _nGot = Lfmutilrb::CTypeIntAr.new(1)
  _MAX_CACHE = Lfmtblrb::D5_MAX_CACHE

  # RD5GetData1M -> RD5GetData1MIntR1
  # 複数データ(整数)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  #   [out]   pnGotCount  取得したデータ数
  #   [out]   pnBuf   取得したデータ格納領域へのポインタ
  _FltID = 1
  _buf = Lfmutilrb::CTypeIntAr.new(_MAX_CACHE * 2)
  ret = Lfmtblrb.RD5GetData1MIntR1(_TableID, _FltID, _SetID, _RowNo, _nGot.getPtr(), _buf.getPtr())
  printf "[RD5GetData1MIntR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _RowNo, _nGot.at(0)
  print " buf = ", Array2List(_buf, _nGot.at(0)), "\n"

  # RD5GetData1M -> RD5GetData1MDblR1
  # 複数データ(浮動少数)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  #   [out]   pnGotCount  取得したデータ数
  #   [out]   pdBuf   取得したデータ格納領域へのポインタ
  _FltID = 6
  _buf = Lfmutilrb::CTypeDblAr.new(_MAX_CACHE)
  ret = Lfmtblrb.RD5GetData1MDblR1(_TableID, _FltID, _SetID, _RowNo, _nGot.getPtr(), _buf.getPtr())
  printf "[RD5GetData1MDblR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _RowNo, _nGot.at(0)
  print " buf = ", Array2List(_buf, _nGot.at(0)), "\n"

  # RD5GetData1M -> RD5GetData1MNumericR1
  # 複数データ(Numeric)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  #   [out]   pnGotCount  取得したデータ数
  #   [out]   pNumericBuf   取得したデータ格納領域へのポインタ
  _FltID = 7
  _buf = Lfmutilrb::CTypeNumAr.new(_MAX_CACHE, _NInfo.getScale(), _NInfo.getRoundingMode())
  ret = Lfmtblrb.RD5GetData1MNumericR1(_TableID, _FltID, _SetID, _RowNo, _nGot.getPtr(), _buf.getPtr())
  printf "[RD5GetData1MNumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _RowNo, _nGot.at(0)
  print " buf = [ "
  for i in 0..._nGot.at(0)
    print _buf.at(i), " "
  end
  print "]\n"

  # RD5GetData1M -> RD5GetData1MStrR1
  # 複数データ(文字列)を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  セット内順序番号
  #   [out]   pnGotCount  取得したデータ数
  #   [out]   pnOffset  buf内での単一データの開始位置(4バイト)の配列
  #   [out]   pvBuf   取得したデータ格納領域へのポインタ
  _FltID  = 2
  _offset = Lfmutilrb::CTypeIntAr.new(_MAX_CACHE)
  _buf    = Lfmutilrb::CTypeCharAr.new(Lfmtblrb::D5_MAX_STRING_SIZE)
  ret = Lfmtblrb.RD5GetData1MStrR1(_TableID, _FltID, _SetID, _RowNo, _nGot.getPtr(), _offset.getPtr(), _buf.getVPtr())
  printf "[RD5GetData1MStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%s,RowNo=%d][nGot=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _RowNo, _nGot.at(0)
  print " offset = ", Array2List(_offset, _nGot.at(0)), "\n"
  print " buf = ["
  for i in 0..._nGot.at(0)
    printf "'%s' ", decode($ENC_DB, _buf.getPtr(_offset.at(i)))
  end
  print "]\n"

  # RD5GetRowNo1
  # ルートセットにおける行位置を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  取得したいセット内順序番号(1から始まる)
  #   [out]   pnRow1  REALテーブル：取得する行番号 JOINテーブル：マスタ側の行番号
  #   [out]   pnRow2  REALテーブル：使用しない JOINテーブル：スレーブ側行番号
  _Row1 = Lfmutilrb::CTypeIntAr.new(_MAX_CACHE)
  _Row2 = Lfmutilrb::CTypeIntAr.new(_MAX_CACHE)
  for _RowNo in 1.._RowCount
    ret = Lfmtblrb.RD5GetRowNo1(_TableID, _SetID, _RowNo, _Row1.getPtr(), _Row2.getPtr())
    printf "[RD5GetRowNo1] retval = %d [TableID=%d,SetID=%d,RowNo=%d][Row1=%d,Row2=%d]\n" \
      , ret, _TableID, _SetID, _RowNo, _Row1.at(0), _Row2.at(0)
  end

  # RD5GetRowNo1M
  # ルートセットにおける複数の行位置を取得します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nRowNo  取得したいセット内順序番号(1から始まる)
  #   [out]   pnGotCount  取得した行数
  #   [out]   anRow1  REALテーブル：取得する行番号 JOINテーブル：マスタ側の行番号
  #   [out]   anRow2  REALテーブル：使用しない JOINテーブル：スレーブ側行番号
  _RowNo = 1
  ret = Lfmtblrb.RD5GetRowNo1M(_TableID, _SetID, _RowNo, _nGot.getPtr(), _Row1.getPtr(), _Row2.getPtr())
  printf "[RD5GetRowNo1M] retval = %d [TableID=%d,SetID=%d,RowNo=%d][nGot=%d]\n", ret, _TableID, _SetID, _RowNo, _nGot.at(0)
  for i in 0..._nGot.at(0)
    printf " [%d] Row1=%d,Row2=%d\n", i, _Row1.at(i), _Row2.at(i)
  end

  # RD5ExtractUniqueReal
  # ユニーク行を抽出します。
  #   [in]  nJBAHandle  常に0
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  anFilterIDs   項目IDリスト
  #   [in]  nConserveOriginalOrder  True または False
  _FltIDs = Lfmutilrb::CTypeIntAr.new(Lfmtblrb::D5_MAX_FILTER_COUNT_REAL)
  _FltIDs.put(0, 1)
  _FltIDs.put(1, 0)
  _ConserveOriginalOrder = 1
  ret = Lfmtblrb.RD5ExtractUniqueReal(0, _TableID, _SetID, _FltIDs.getPtr(), _ConserveOriginalOrder)
  printf "[RD5ExtractUniqueReal] retval = %d [TableID=%d,SetID=%d,FltIDs=", ret, _TableID, _SetID
  print Array2List(_FltIDs, 2)
  printf ",ConserveOriginalOrder=%d]\n", _ConserveOriginalOrder

  printf "### %s ### end\n", funcName
  return
end

## 6-3-12 検索機能
def testSearch()
  funcName = "testSearch"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  _TableID  = 1
  _SetID    = 1
  _OpeNo    = Lfmtblrb::D5_OPETYPE_BETWEEN
  _LocaleID = Lfmtblrb::D5_LOCALE_UTF8
  _ix = 3
  _iy = 7

  # RD5SearchByDispRowNoReal
  # セット内順序番号による検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  nX  1番目の検索条件(セット内順序番号)
  #   [in]  nY  2番目の検索条件(セット内順序番号)
  ret = Lfmtblrb.RD5SearchByDispRowNoReal(_TableID, _SetID, _OpeNo, _ix, _iy)
  printf "[RD5SearchByDispRowNoReal] retval = %d [TableID=%d,SetID=%d,OpeNo=%d,ix=%d,iy=%d]\n" \
    , ret, _TableID, _SetID, _OpeNo, _ix, _iy

  # RD5SearchByRowNo
  # ルートセットの行番号による検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nTableNo  マスタテーブルか、スレーブテーブルかの設定
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  nX  1番目の検索条件(行番号)
  #   [in]  nY  2番目の検索条件(行番号)
  _TableNo = 0
  ret = Lfmtblrb.RD5SearchByRowNo(_TableID, _TableNo, _SetID, _OpeNo, _ix, _iy)
  printf "[RD5SearchByRowNo] retval = %d [TableID=%d,TableNo=%d,SetID=%d,OpeNo=%d,ix=%d,iy=%d]\n" \
    , ret, _TableID, _TableNo, _SetID, _OpeNo, _ix, _iy

  # RD5SearchByField -> RD5SearchByFieldIntR1
  # 指定した項目(整数)のデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  nX  1番目の検索条件データ
  #   [in]  nY  2番目の検索条件データ
  _FltID = 1
  _pcX   = 3
  _pcY   = 7
  ret = Lfmtblrb.RD5SearchByFieldIntR1(_TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY)
  printf "[RD5SearchByFieldIntR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%d,pcY=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByField -> RD5SearchByFieldDblR1
  # 指定した項目(浮動少数)のデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  dX  1番目の検索条件データ
  #   [in]  dY  2番目の検索条件データ
  _FltID = 6
  _pcX   = 0.3
  _pcY   = 0.7
  ret = Lfmtblrb.RD5SearchByFieldDblR1(_TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY)
  printf "[RD5SearchByFieldDblR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%f,pcY=%f]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByField -> RD5SearchByFieldNumericR1
  # 指定した項目(Numeric)のデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  pNumericX   1番目の検索条件データ
  #   [in]  pNumericY   2番目の検索条件データ
  _FltID = 7
  _pcX   = "0.03"
  _pcY   = "0.07"
  _NInfo = Lfmutilrb::CNumericInfo.new()
  ret   = Lfmtblrb.RD5GetNumericInfoR1(_TableID, _FltID, _NInfo.getPtr())
  _pcX_Num = Lfmutilrb::CNumeric.new(_pcX, _NInfo.getScale(), _NInfo.getRoundingMode())
  _pcY_Num = Lfmutilrb::CNumeric.new(_pcY, _NInfo.getScale(), _NInfo.getRoundingMode())
  ret = Lfmtblrb.RD5SearchByFieldNumericR1(_TableID, _FltID, _SetID, _OpeNo, _pcX_Num.getPtr(), _pcY_Num.getPtr())
  printf "[RD5SearchByFieldNumericR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByField -> RD5SearchByFieldStrR1
  # 指定した項目(文字列)のデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  ret = Lfmtblrb.RD5SearchByFieldStrR1(_TableID, _FltID, _SetID, _OpeNo, encode($ENC_DB, _pcX), encode($ENC_DB, _pcY))
  printf "[RD5SearchByFieldStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByFieldSJIS -> RD5SearchByFieldLocaleに統合
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  # 指定した項目の、マルチバイト文字コードを使った検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  ret = Lfmtblrb.RD5SearchByFieldSJISR1(_TableID, _FltID, _SetID, _OpeNo, encode($ENC_DB, _pcX), encode($ENC_DB, _pcY))
  printf "[RD5SearchByFieldSJISR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByFieldLocale -> RD5SearchByFieldLocaleR1
  # 指定した項目の、マルチバイト文字コードを使った検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  #   [in]  nLocaleID   文字コードID
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  ret = Lfmtblrb.RD5SearchByFieldLocaleR1(_TableID, _FltID, _SetID, _OpeNo, encode($ENC_DB, _pcX), encode($ENC_DB, _pcY), _LocaleID)
  printf "[RD5SearchByFieldLocaleR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s,LocaleID=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY, _LocaleID

  # RD5SearchByText
  # 文字列で書かれた検索式で検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  _Text = "int BETWEEN 3 AND 7"
  ret = Lfmtblrb.RD5SearchByText(_TableID, _SetID, _Text)
  printf "[RD5SearchByText] retval = %d [TableID=%d,FltID=%d,SetID=%d,Text=%s]\n", ret, _TableID, _FltID, _SetID, _Text

  # RD5SearchByTextSJIS
  # 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  _Text = "str BETWEEN '０３' AND '０７'"
  ret = Lfmtblrb.RD5SearchByTextSJIS(_TableID, _SetID, encode($ENC_DB, _Text))
  printf "[RD5SearchByTextSJIS] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s]\n", ret, _TableID, _FltID, _SetID, _Text

  # RD5SearchByTextLocale
  # 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  #   [in]  nLocaleID   文字コードID
  _Text = "str BETWEEN '０３' AND '０７'"
  ret = Lfmtblrb.RD5SearchByTextLocale(_TableID, _SetID, encode($ENC_DB, _Text), _LocaleID)
  printf "[RD5SearchByTextLocale] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s,LocaleID=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _Text, _LocaleID

  # RD5SearchByFieldWildCard
  # 指定した項目の、ワイルドカードを含むデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索条件式
  _pc = "*０*"
  ret = Lfmtblrb.RD5SearchByFieldWildCard(_TableID, _FltID, _SetID, encode($ENC_DB, _pc))
  printf "[RD5SearchByFieldWildCard] retval = %d [TableID=%d,FltID=%d,SetID=%d,pc=%s]\n", ret, _TableID, _FltID, _SetID, _pc

  # RD5HighSpeedSearchSetMark
  # 高速検索の実行宣言を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [in]  nMark   高速検索指定フラグ
  _mark = 1
  ret = Lfmtblrb.RD5HighSpeedSearchSetMark(_TableID, _FltID, _SetID, _mark)
  printf "[RD5HighSpeedSearchSetMark] retval = %d [TableID=%d,SetID=%d,FilterID=%d,mark=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _mark

  # RD5HighSpeedSearchHasMark
  # 高速検索の対象かどうかをチェックします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  ret = Lfmtblrb.RD5HighSpeedSearchHasMark(_TableID, _FltID, _SetID)
  printf "[RD5HighSpeedSearchHasMark] retval = %d [TableID=%d,SetID=%d,FilterID=%d]\n" \
    , ret, _TableID, _FltID, _SetID

  # RD5HighSpeedSearchEnable
  # 通常検索／高速検索状態の切り替えを行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nEnable   検索状態の切り替えフラグ
  _enable = 1
  ret = Lfmtblrb.RD5HighSpeedSearchEnable(_TableID, _FltID, _enable)
  printf "[RD5HighSpeedSearchEnable] retval = %d [TableID=%d,FilterID=%d,enable=%d]\n" \
    , ret, _TableID, _FltID, _enable

  # RD5HighSpeedSearchIsEnabled
  # 通常検索／高速検索の状態を問い合わせます
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  ret = Lfmtblrb.RD5HighSpeedSearchIsEnabled(_TableID, _FltID)
  printf "[RD5HighSpeedSearchIsEnabled] retval = %d [TableID=%d,FilterID=%d]\n" \
    , ret, _TableID, _FltID

  printf "### %s ### end\n", funcName
  return
end

def testSearchSJIS()
  funcName = "testSearchSJIS"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  _ENC_DB = "Shift_JIS"
  ret = Lfmtblrb.RD5SetDBCharCode(_ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile_SJIS
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  _TableID  = 1
  _SetID    = 1
  _OpeNo    = Lfmtblrb::D5_OPETYPE_BETWEEN
  _LocaleID = Lfmtblrb::D5_LOCALE_SJIS

  # RD5SearchByField -> RD5SearchByFieldStrR1
  # 指定した項目(文字列)のデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  ret = Lfmtblrb.RD5SearchByFieldStrR1(_TableID, _FltID, _SetID, _OpeNo, encode(_ENC_DB, _pcX), encode(_ENC_DB, _pcY))
  printf "[RD5SearchByFieldStrR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByFieldSJIS -> RD5SearchByFieldLocaleに統合
  # 指定した項目の、マルチバイト文字コードを使った検索を行います
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  ret = Lfmtblrb.RD5SearchByFieldSJISR1(_TableID, _FltID, _SetID, _OpeNo, encode(_ENC_DB, _pcX), encode(_ENC_DB, _pcY))
  printf "[RD5SearchByFieldSJISR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY

  # RD5SearchByFieldLocale -> RD5SearchByFieldLocaleR1
  # 指定した項目の、マルチバイト文字コードを使った検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nOpeNo  検索条件式
  #   [in]  szX   1番目の検索条件データ
  #   [in]  szY   2番目の検索条件データ
  #   [in]  nLocaleID   文字コードID
  _FltID = 2
  _pcX   = "０３"
  _pcY   = "０７"
  ret = Lfmtblrb.RD5SearchByFieldLocaleR1(_TableID, _FltID, _SetID, _OpeNo, encode(_ENC_DB, _pcX), encode(_ENC_DB, _pcY), _LocaleID)
  printf "[RD5SearchByFieldLocaleR1] retval = %d [TableID=%d,FltID=%d,SetID=%d,OpeNo=%d,pcX=%s,pcY=%s,LocaleID=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _OpeNo, _pcX, _pcY, _LocaleID

  # RD5SearchByText
  # 文字列で書かれた検索式で検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  _Text = "int BETWEEN 3 AND 7"
  ret = Lfmtblrb.RD5SearchByText(_TableID, _SetID, _Text)
  printf "[RD5SearchByText] retval = %d [TableID=%d,FltID=%d,SetID=%d,Text=%s]\n", ret, _TableID, _FltID, _SetID, _Text

  # RD5SearchByTextSJIS
  # 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  _Text = "str BETWEEN '０３' AND '０７'"
  ret = Lfmtblrb.RD5SearchByTextSJIS(_TableID, _SetID, encode(_ENC_DB, _Text))
  printf "[RD5SearchByTextSJIS] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s]\n", ret, _TableID, _FltID, _SetID, _Text

  # RD5SearchByTextLocale
  # 文字列で書かれた検索式による検索を、マルチバイト文字コードを使用する場合に行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索文字列
  #   [in]  nLocaleID   文字コードID
  _Text = "str BETWEEN '０３' AND '０７'"
  ret = Lfmtblrb.RD5SearchByTextLocale(_TableID, _SetID, encode(_ENC_DB, _Text), _LocaleID)
  printf "[RD5SearchByTextLocale] retval = %d [TableID=%d,FltID=%d,SetID=%d,text=%s,LocaleID=%d]\n" \
    , ret, _TableID, _FltID, _SetID, _Text, _LocaleID

  # RD5SearchByFieldWildCard
  # 指定した項目の、ワイルドカードを含むデータによる検索を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  szText  検索条件式
  _pc = "*０*"
  ret = Lfmtblrb.RD5SearchByFieldWildCard(_TableID, _FltID, _SetID, encode(_ENC_DB, _pc))
  printf "[RD5SearchByFieldWildCard] retval = %d [TableID=%d,FltID=%d,SetID=%d,pc=%s]\n" \
    , ret, _TableID, _FltID, _SetID, _pc

  printf "### %s ### end\n", funcName
  return
end

## 6-3-13 ソート機能
def testSort()
  funcName = "testSort"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5SortByField
  # 指定された項目でソート処理を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nFilterID   項目ID
  #   [in]  nSetID  セットID
  #   [in]  nSortDir  ソートする方向
  _TableID = 1
  _FltID   = 1
  _SetInID = -1
  _SortDir = 0
  ret = Lfmtblrb.RD5SortByField(_TableID, _FltID, _SetInID, _SortDir)
  printf "[RD5SortByField] retval = %d [TableID=%d,FltID=%d,SetInID=%d,SortDir=%d]\n" \
    , ret, _TableID, _FltID, _SetInID, _SortDir

  # RD5SortByRowNo
  # 行番号によるソート処理を行います。
  #   [in]  nTableID  テーブルID
  #   [in]  nTableNo  マスタまたはスレーブテーブルを指定
  #   [in]  nSetID  セットID
  #   [in]  nSortDir  ソートする方向
  _TableNo = 0
  ret = Lfmtblrb.RD5SortByRowNo(_TableID, _TableNo, _SetInID, _SortDir)
  printf "[RD5SortByRowNo] retval = %d [TableID=%d,TableNo=%d,SetInID=%d,SortDir=%d]\n" \
    , ret, _TableID, _TableNo, _SetInID, _SortDir

  printf "### %s ### end\n", funcName
  return
end

## 6-3-14 項目詳細情報取得機能
def testDetail()
  funcName = "testDetail"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5OpenDetailInfo
  # 項目詳細情報取得機能をオープンします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [out]   pnDataType  データ型
  #   [out]   pnRangeSize   登録されている値の総数
  #   [out]   pnNonZeroCount  ゼロでない値を持つレコード数
  _TableID   = 1
  _SetID     = 1
  _FilterID  = 1 # int
  _DataType  = Lfmutilrb::CTypeIntAr.new(1)
  _RangeSize = Lfmutilrb::CTypeIntAr.new(1)
  _nNonZero  = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5OpenDetailInfo(_TableID, _SetID, _FilterID, _DataType.getPtr(), _RangeSize.getPtr(), _nNonZero.getPtr())
  printf "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]\n"  \
    , ret, _TableID, _SetID, _FilterID, _DataType.at(0), _RangeSize.at(0), _nNonZero.at(0)

  _hDetail      = ret
  _OrderByN     = 0
  _Reverse      = 0
  _ZeroSuppress = 0
  _Row          = 11

  # RD5GetDetailValue
  # オープンした項目詳細情報の項目値を指定した順序に並べ、指定した順序番号の項目値を取得します。 （先頭の項目値の番号を1とし、並びの順番に番号がつけられます）
  #   [in]  nHandle   オープン時に取得したハンドル
  #   [in]  nOrderByN   存在数順に並べるかどうかを指定
  #   [in]  nReverse  逆順にするかどうかを指定
  #   [in]  nZeroSuppress   存在数が0のデータを含めるかどうかを指定
  #   [in]  nRow  項目値の順序番号
  #   [out] pnDataType  データ型
  #   [out] pvData  取得データ
  _Data = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5GetDetailValue(_hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.getPtr(), _Data.getPtr())
  printf "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%d]\n" \
    , ret, _hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.at(0), _Data.at(0)

  # RD5GetDetailCount
  # オープンした項目詳細情報の存在数を取得します。
  #   [in]  nHandle   オープン時に取得したハンドル
  #   [in]  nOrderByN   存在数順に並べるかどうかを指定
  #   [in]  nReverse  逆順にするかどうかを指定
  #   [in]  nZeroSuppress   存在数が0のデータを含めるかどうかを指定
  #   [in]  nRow  項目値の順序番号
  #   [out]   pnCount   取得データ
  _Count = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5GetDetailCount(_hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _Count.getPtr())
  printf "[RD5GetDetailCount] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][Count=%d]\n" \
    , ret, _hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _Count.at(0)

  # RD5CloseDetailInfo
  # オープンした項目詳細情報をクローズします。
  ret = Lfmtblrb.RD5CloseDetailInfo(_hDetail)
  printf "[RD5CloseDetailInfo] retval = %d [Handle=%d]\n", ret, _hDetail


  _FilterID  = 6 # double
  # RD5OpenDetailInfo
  # 項目詳細情報取得機能をオープンします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [out]   pnDataType  データ型
  #   [out]   pnRangeSize   登録されている値の総数
  #   [out]   pnNonZeroCount  ゼロでない値を持つレコード数
  ret = Lfmtblrb.RD5OpenDetailInfo(_TableID, _SetID, _FilterID, _DataType.getPtr(), _RangeSize.getPtr(), _nNonZero.getPtr())
  printf "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]\n" \
    , ret, _TableID, _SetID, _FilterID, _DataType.at(0), _RangeSize.at(0), _nNonZero.at(0)
  # RD5GetDetailValue
  # オープンした項目詳細情報の項目値を指定した順序に並べ、指定した順序番号の項目値を取得します。 （先頭の項目値の番号を1とし、並びの順番に番号がつけられます）
  #   [in]  nHandle   オープン時に取得したハンドル
  #   [in]  nOrderByN   存在数順に並べるかどうかを指定
  #   [in]  nReverse  逆順にするかどうかを指定
  #   [in]  nZeroSuppress   存在数が0のデータを含めるかどうかを指定
  #   [in]  nRow  項目値の順序番号
  #   [out] pnDataType  データ型
  #   [out] pvData  取得データ
  _hDetail = ret
  _Data = Lfmutilrb::CTypeDblAr.new(1)
  ret = Lfmtblrb.RD5GetDetailValue(_hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.getPtr(), _Data.getPtr())
  printf "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%f]\n" \
    , ret, _hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.at(0), _Data.at(0)
  # RD5CloseDetailInfo
  # オープンした項目詳細情報をクローズします。
  ret = Lfmtblrb.RD5CloseDetailInfo(_hDetail)
  printf "[RD5CloseDetailInfo] retval = %d [Handle=%d]\n", ret, _hDetail


  _FilterID  = 7 # Numeric
  # RD5OpenDetailInfo
  # 項目詳細情報取得機能をオープンします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [out]   pnDataType  データ型
  #   [out]   pnRangeSize   登録されている値の総数
  #   [out]   pnNonZeroCount  ゼロでない値を持つレコード数
  ret = Lfmtblrb.RD5OpenDetailInfo(_TableID, _SetID, _FilterID, _DataType.getPtr(), _RangeSize.getPtr(), _nNonZero.getPtr())
  printf "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]\n" \
    , ret, _TableID, _SetID, _FilterID, _DataType.at(0), _RangeSize.at(0), _nNonZero.at(0)
  # RD5GetDetailValue
  # オープンした項目詳細情報の項目値を指定した順序に並べ、指定した順序番号の項目値を取得します。 （先頭の項目値の番号を1とし、並びの順番に番号がつけられます）
  #   [in]  nHandle   オープン時に取得したハンドル
  #   [in]  nOrderByN   存在数順に並べるかどうかを指定
  #   [in]  nReverse  逆順にするかどうかを指定
  #   [in]  nZeroSuppress   存在数が0のデータを含めるかどうかを指定
  #   [in]  nRow  項目値の順序番号
  #   [out] pnDataType  データ型
  #   [out] pvData  取得データ
  _hDetail = ret
  _Data = Lfmutilrb::CNumericInfoData.new()
  ret = Lfmtblrb.RD5GetDetailValue(_hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.getPtr(), _Data.getPtr())
  printf "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%s]\n" \
    , ret, _hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.at(0), _Data.toString()
  # RD5CloseDetailInfo
  # オープンした項目詳細情報をクローズします。
  ret = Lfmtblrb.RD5CloseDetailInfo(_hDetail)
  printf "[RD5CloseDetailInfo] retval = %d [Handle=%d]\n", ret, _hDetail


  _FilterID  = 2 # string
  # RD5OpenDetailInfo
  # 項目詳細情報取得機能をオープンします。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nFilterID   項目ID
  #   [out]   pnDataType  データ型
  #   [out]   pnRangeSize   登録されている値の総数
  #   [out]   pnNonZeroCount  ゼロでない値を持つレコード数
  ret = Lfmtblrb.RD5OpenDetailInfo(_TableID, _SetID, _FilterID, _DataType.getPtr(), _RangeSize.getPtr(), _nNonZero.getPtr())
  printf "[RD5OpenDetailInfo] retval = %d [TableID=%d,SetID=%d,FilterID=%d][DataType=%d,RangeSize=%d,nNonZero=%d]\n" \
    , ret, _TableID, _SetID, _FilterID, _DataType.at(0), _RangeSize.at(0), _nNonZero.at(0)
  # RD5GetDetailValue
  # オープンした項目詳細情報の項目値を指定した順序に並べ、指定した順序番号の項目値を取得します。 （先頭の項目値の番号を1とし、並びの順番に番号がつけられます）
  #   [in]  nHandle   オープン時に取得したハンドル
  #   [in]  nOrderByN   存在数順に並べるかどうかを指定
  #   [in]  nReverse  逆順にするかどうかを指定
  #   [in]  nZeroSuppress   存在数が0のデータを含めるかどうかを指定
  #   [in]  nRow  項目値の順序番号
  #   [out] pnDataType  データ型
  #   [out] pvData  取得データ
  _hDetail = ret
  _Data = Lfmutilrb::CTypeCharAr.new(Lfmtblrb::D5_MAX_STRING_SIZE)
  ret = Lfmtblrb.RD5GetDetailValue(_hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.getPtr(), _Data.getVPtr())
  printf "[RD5GetDetailValue] retval = %d [Handle=%d,OrderByN=%d,Reverse=%d,ZeroSuppress=%d,Row=%d][DataType=%d,Data=%s]\n" \
    , ret, _hDetail, _OrderByN, _Reverse, _ZeroSuppress, _Row, _DataType.at(0), decode($ENC_DB, _Data.getPtr())
  # RD5CloseDetailInfo
  # オープンした項目詳細情報をクローズします。
  ret = Lfmtblrb.RD5CloseDetailInfo(_hDetail)
  printf "[RD5CloseDetailInfo] retval = %d [Handle=%d]\n", ret, _hDetail

  printf "### %s ### end\n", funcName
  return
end

## 6-3-15 集計機能
def testSum()
  funcName = "testSum"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  # 指定されたパスおよびファイル名称の、ワークスペースを読み込みます。 
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  _Name = SampleD5DFile
  ret = Lfmtblrb.RD5LoadDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
  printf "[RD5LoadDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

  # RD5NonCubeSum
  # 集計を行い、集計テーブルを作成します。
  #   [in]  nTableID  テーブルID
  #   [in]  nSetID  セットID
  #   [in]  nDimCount   集計次元数
  #   [in]  pnDimFilterIDs  集計次元となる項目ID配列
  #   [in]  nMeasureCount   集計測度の数
  #   [in]  pnMeasureFilterIDs  集計測度となる項目ID配列
  #   [in]  pnSummaryTypes  pnMeasureFilterIDsの各項目に集計種別を指定する配列
  #   [in]  pnFloatFormats  pnMeasureFilterIDsの各項目に固定小数点を使用するかしないかを指定する配列
  _TableID = 1
  _SetID   = 1
  _nDim    = 1
  _DimFltIDs = Lfmutilrb::CTypeIntAr.new(1)
  _DimFltIDs.put(0, 1)
  _nMeasure  = 1
  _MsrFltIDs = Lfmutilrb::CTypeIntAr.new(_nMeasure)
  _MsrFltIDs.put(0, 1)
  _SummaryTypes = Lfmutilrb::CTypeIntAr.new(_nMeasure)
  _SummaryTypes.put(0, Lfmtblrb::D5_SUMMARY_COUNT | Lfmtblrb::D5_SUMMARY_MAX | Lfmtblrb::D5_SUMMARY_MIN | Lfmtblrb::D5_SUMMARY_SUM)
  _FloatFormats = Lfmutilrb::CTypeIntAr.new(1)
  ret = Lfmtblrb.RD5NonCubeSum(_TableID, _SetID, _nDim, _DimFltIDs.getPtr(), _nMeasure, _MsrFltIDs.getPtr(), _SummaryTypes.getPtr(), _FloatFormats.getPtr())
  printf "[RD5NonCubeSum] retval = %d [TableID=%d,SetID=%d,nDim=%d,nMeasure=%d]\n", ret, _TableID, _SetID, _nDim, _nMeasure

  printf "### %s ### end\n", funcName
  return
end

## 6-3-16 データ変換処理機能
def testDB()
  funcName = "testDB"
  printf "### %s ### start\n", funcName

  # init
  # ワークスペースをクリアします。
  ret = Lfmtblrb.RD5ClearDB()

  # RD5SetDBCharCode
  # エンジンのDB文字コードを設定します。
  ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
  printf "[RD5SetDBCharCode] retval = %d [DBCode=%s]\n", ret, $ENC_DB

  # RD5GetD5DFileInfo
  # 指定されたD5DファイルのヘッダからDBコード、バージョンを読み出します。
  #   [in]  szDBPath  D5Dファイルの存在するパス
  #   [in]  szDBName  D5Dファイルの名称
  #   [out]   pD5FileInfo   D5Dファイル情報
  _DBPath = PathIn
  _DBName = SampleD5DFile
  _Env = Lfmtblrb::D5FileInfo.new()
  ret = Lfmtblrb.RD5GetD5DFileInfo(encode($ENC_OS, _DBPath), encode($ENC_OS, _DBName), _Env)
  printf "[RD5GetD5DFileInfo] retval = %d [DBPath=%s,DBName=%s][OSType=%d,Endian=%d,ELF=%d,DBCharCode=%s]\n" \
    , ret, _DBPath, _DBName, _Env.OSType, _Env.Endian, _Env.ELF, _Env.DBCharCode
  for i in 0..3
    printf " Version[%d]=%d\n", i, Lfmutilrb.int_at(_Env.Version, i)
  end

  # RD5GetD5TFileInfo
  # 指定されたD5TファイルのヘッダからDBコード、バージョンを読み出します。
  #   [in]  szTablePath   D5Tファイルの存在するパス
  #   [in]  szTableName   D5Tファイルの名称
  #   [out]   pD5FileInfo   D5Tファイル情報
  _DBName = SampleD5TFile
  _Env = Lfmtblrb::D5FileInfo.new()
  ret = Lfmtblrb.RD5GetD5TFileInfo(encode($ENC_OS, _DBPath), encode($ENC_OS, _DBName), _Env)
  printf "[RD5GetD5TFileInfo] retval = %d [DBPath=%s,DBName=%s][OSType=%d,Endian=%d,ELF=%d,DBCharCode=%s]\n" \
    , ret, _DBPath, _DBName, _Env.OSType, _Env.Endian, _Env.ELF, _Env.DBCharCode
  for i in 0..3
    printf " Version[%d]=%d\n", i, Lfmutilrb.int_at(_Env.Version, i)
  end

  printf "### %s ### end\n", funcName
  return
end

## 6-3-17 サーバ情報取得機能
def testServer()
  funcName = "testServer"
  printf "### %s ### start\n", funcName

  # RD5GetServerIPAddress → 未サポート
  # サーバのIPアドレスを取得します。

  # RD5GetEnvironment
  # サーバの環境情報を取得します。
  _Env = Lfmtblrb::TREnvironment.new()
  ret = Lfmtblrb.RD5GetEnvironment(_Env)
  printf "[RD5GetEnvironment] retval = %d [HostName=%s,OSType=%d,OSMajorVersion=%d,OSMinorVersion=%d,MachineArchitecture=%d,Endian=%d,ELF=%d,ProcessorCount=%d,ProcessType=%d,OSCharCode=%s]\n" \
    , ret, _Env.HostName, _Env.OSType, _Env.OSMajorVersion, _Env.OSMinorVersion, _Env.MachineArchitecture \
    , _Env.Endian, _Env.ELF, _Env.ProcessorCount, _Env.ProcessType, _Env.DBCharCode

  # RD5BrowserGetCurrentDirectory → 未サポート
  #   サーバ側のカレントディレクトリを取得します。 
  # RD5BrowserSetCurrentDirectory → 未サポート
  #   サーバ側のカレントディレクトリを変更します。
  # RD5BrowserMakeDirectory → 未サポート
  #   サーバにディレクトリを作成します。 
  # RD5BrowserGetFileList → 未サポート
  #   サーバのファイル一覧を取得します。 
  # RD5BrowserGetFileSize → 未サポート
  #   サーバのファイルサイズを取得します。
  # RD5BrowserGetFile → 未サポート
  #   サーバからファイルを読み込みます。
  # RD5BrowserGetFileEx → 未サポート
  #   サーバからファイルを読み込みます。
  # RD5BrowserPutFile → 未サポート
  #   サーバにファイルを作成します
  # RD5BrowserPutFileEx → 未サポート
  #   サーバにファイルを作成します。
  # RD5BrowserDelFile → 未サポート
  #   サーバのファイルを削除します。
  # RD5BrowserMove → 未サポート
  #   サーバのファイル又はディレクトリ名称を変更します。また、指定のディレクトリに移動します。 
  # RD5BrowserDelDirectory → 未サポート
  #   サーバにディレクトリを作成します。

  # RD5GetSystemMemInfo
  # サーバのシステムメモリサイズを取得します。
  _MemInfo = Lfmtblrb::TRMemInfo.new()
  ret = Lfmtblrb.RD5GetSystemMemInfo(_MemInfo)
  if RUBY_PLATFORM != "i386-mswin32"
    printf "[RD5GetSystemMemInfo] retval = %d [TotalPhys=%d,AvailPhys=%d]\n" \
      , ret, _MemInfo.TotalPhys, _MemInfo.AvailPhys
  end

  # RD5BrowserGetFile64 → 未サポート
  # RD5BrowserGetFileEx64 → 未サポート

  printf "### %s ### end\n", funcName
  return
end

## 6-3-18 共有メモリ関連機能
def testSharedMemory()
  funcName = "testSharedMemory"
  printf "### %s ### start\n", funcName

  # 64bit OS限定
  _Env = Lfmtblrb::TREnvironment.new()
  # サーバの環境情報を取得します。
  ret = Lfmtblrb.RD5GetEnvironment(_Env)
  if _Env.ELF == 64
    # init
    # ワークスペースをクリアします。
    ret = Lfmtblrb.RD5ClearDB()
    # エンジンのDB文字コードを設定します。
    ret = Lfmtblrb.RD5SetDBCharCode($ENC_DB)
    # RD5CreateSharedMemoryDB
    # D5Dデータを共有メモリ領域へ生成します。. 
    #   [in]  szDBPath  D5Dファイルの存在するパス
    #   [in]  szDBName  D5Dファイルの名称
    _Name = SampleD5DFile_X64
    ret = Lfmtblrb.RD5CreateSharedMemoryDB(encode($ENC_OS, PathIn), encode($ENC_OS, _Name))
    printf "[RD5CreateSharedMemoryDB] retval = %d [DBPath=%s,DBName=%s]\n", ret, PathIn, _Name

    # RD5LoadDBFromSharedMemory
    # D5Dデータを共有メモリ領域から読み込みます。.
    ret = Lfmtblrb.RD5LoadDBFromSharedMemory()
    printf "[RD5LoadDBFromSharedMemory] retval = %d\n", ret

    # RD5ReleaseSharedMemoryArea -> 後に移動
    # D5Dデータを共有メモリ領域から解放します。.

    # RD5IsSharedMemoryTable
    # テーブルが共有メモリ上にあるか判別します。
    _TableID = 1
    ret = Lfmtblrb.RD5IsSharedMemoryTable(_TableID)
    printf "[RD5IsSharedMemoryTable] retval = %d [TableID=%d]\n", ret, _TableID

    # RD5ReleaseSharedMemoryArea <- 前から移動
    # D5Dデータを共有メモリ領域から解放します。.
    ret = Lfmtblrb.RD5ReleaseSharedMemoryArea()
    printf "[RD5ReleaseSharedMemoryArea] retval = %d\n", ret
  end

  printf "### %s ### end\n", funcName
  return
end


## 配列をリスト化
# @param arry  at()メソッドで要素アクセスする配列クラス
# @param size  要素数
# @retval リスト
def Array2List(arry, size)
  list = " ["
  if (arry != nil) && (size > 0)
    list << arry.at(0).to_s
    for i in 1...size
      list << ", " << arry.at(i).to_s
    end
  end
  list << "] "

  return list
end

## エンコード文字列からID取得
# @param enc  エンコード文字列
# @retval ID
def encodeId(enc)
  encId = Kconv::NOCONV
  case enc
    when "UTF8"
      encId = Kconv::UTF8
    when "MS932"
      encId = Kconv::SJIS
    when "SJIS"
      encId = Kconv::SJIS
    when "Shift_JIS"
      encId = Kconv::SJIS
    when "EUC"
      encId = Kconv::EUC
  end
  return encId
end

## エンコード（UTF8からの変換）
# @param enc  エンコード文字列
# @param str  変換対象文字列
# @retval 変換後文字列
def encode(enc, str)
  return str.kconv(encodeId(enc), Kconv::UTF8)
end

## デコード（UTF8への変換）
# @param enc  エンコード文字列
# @param str  変換対象文字列
# @retval 変換後文字列
def decode(enc, str)
  return str.kconv(Kconv::UTF8, encodeId(enc))
end

## キャラクタコード取得（Rubyバージョン差異吸収）
# @param s  文字列（先頭文字が対象）
# @retval キャラクタコード
def ord(s)
  if RUBY_VERSION >= "1.9"
    ccode = s.ord
  else
    ccode = s[0]
  end
  return ccode
end


## メイン
if __FILE__ == $0
  print "Start\n\n"

  # 引数
  argvs = ARGV
  argc  = argvs.length
  if argc > 0
    $ENC_OS = argvs[0]
  end
  if argc > 1
    $ENC_DB = argvs[1]
  end
  printf "ENC_OS[%s],ENC_DB[%s]\n", $ENC_OS, $ENC_DB

  # 出力先
  if !File.exist?(PathOut)
    FileUtils.makedirs(PathOut)
  end
## 6-3-3 ワークスペース（ データベース）管理機能
  testWS(SampleD5DFile)
## 6-3-4 テーブル管理機能
  testTable(SampleD5DFile,SampleD5DFile_JOIN)
## 6-3-5 順序付き集合管理機能
  testSet()
## 6-3-6 項目管理機能
  testFilter()
## 6-3-7 値ジャンプ機能
  testFind()
## 6-3-8 数値のカテゴライズ
  testCategory()
## 6-3-9 計算機能
  testCalc()
## 6-3-10 編集機能
  testEdit()
## 6-3-11 データ取得機能
  testGetData()
## 6-3-12 検索機能
  testSearch()
  testSearchSJIS()
## 6-3-13 ソート機能
  testSort()
## 6-3-14 項目詳細情報取得機能
  testDetail()
## 6-3-15 集計機能
  testSum()
## 6-3-16 データ変換処理機能
  testDB()
## 6-3-17 サーバ情報取得機能
  testServer()
## 6-3-18 共有メモリ関連機能
  testSharedMemory()
  testEngine()

  print "\nEnd\n"
end
