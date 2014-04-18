using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class EpgAutoDataItem
    {
        public EpgAutoDataItem(EpgAutoAddData item)
        {
            //this.pEpgAutoAddInfo=item;ではisChangeが動かないので×。
            this.EpgAutoAddInfo = item;
        }

        public EpgAutoAddData EpgAutoAddInfo
        {
            //元コード。class EpgAutoAddData(CtrlCmdCLI)側で実装するなら元のままで良い。
            //get;
            //set;

            //クラス内で実装する場合用の定義。変更を検知する。
            get
            {
                return this.pEpgAutoAddInfo;
            }
            set
            {
                isChange = true;
                this.pEpgAutoAddInfo = value;
            }
        }

        //クラス内で実装する場合用の定義。
        private EpgAutoAddData pEpgAutoAddInfo;

        public String AndKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.searchInfo.andKey.Substring(EpgAutoAddInfo.searchInfo.andKey.StartsWith("^!{999}") ? 7 : 0);
                }
                return view;
            }
        }
        public String NotKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.searchInfo.notKey;
                }
                return view;
            }
        }
        public String RegExp
        {
            get
            {
                String view = "×";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.regExpFlag == 1)
                    {
                        view = "○";
                    }
                }
                return view;
            }
        }
        public String TitleOnly
        {
            get
            {
                String view = "×";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.titleOnlyFlag == 1)
                    {
                        view = "○";
                    }
                }
                return view;
            }
        }
        public String DateKey
        {
            get
            {
                String view = "なし";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.dateList.Count == 1)
                    {
                        EpgSearchDateInfo info = EpgAutoAddInfo.searchInfo.dateList[0];
                        view = CommonManager.Instance.DayOfWeekDictionary[info.startDayOfWeek] + " " + info.startHour.ToString("00") + ":" + info.startMin.ToString("00") +
                            " ～ " + CommonManager.Instance.DayOfWeekDictionary[info.endDayOfWeek] + " " + info.endHour.ToString("00") + ":" + info.endMin.ToString("00");
                    }
                    else if (EpgAutoAddInfo.searchInfo.dateList.Count > 1)
                    {
                        view = "複数指定";
                    }
                }
                return view;
            }
        }
        public String RecMode
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    switch (EpgAutoAddInfo.recSetting.RecMode)
                    {
                        case 0:
                            view = "全サービス";
                            break;
                        case 1:
                            view = "指定サービス";
                            break;
                        case 2:
                            view = "全サービス（デコード処理なし）";
                            break;
                        case 3:
                            view = "指定サービス（デコード処理なし）";
                            break;
                        case 4:
                            view = "視聴";
                            break;
                        case 5:
                            view = "無効";
                            break;
                        default:
                            break;
                    }
                }
                return view;
            }
        }
        public String Priority
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.recSetting.Priority.ToString();
                }
                return view;
            }
        }
        public String Tuijyu
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.recSetting.TuijyuuFlag == 0)
                    {
                        view = "しない";
                    }
                    else if (EpgAutoAddInfo.recSetting.TuijyuuFlag == 1)
                    {
                        view = "する";
                    }
                }
                return view;
            }
        }
        public String AddCount
        {
            get
            {
                String view = "0";
                if (EpgAutoAddInfo != null)
                {
                    view = EpgAutoAddInfo.addCount.ToString();
                }
                return view;
            }
        }

        //ここから追加カウント関係のコード。
        //本体側では問題無いが、リモートのNWでは
        //class EpgAutoAddData(CtrlCmdCLI)側で実装しない限り、重すぎて実用は無理ぽい。
        
        //詳細ウィンドウを開いたときの項目数と同じもの。
        //無効時でも有効時のAddCountと同じ数字が入る。
        public String SearchCount 
        {
            get
            {
                return getItemCounts(itemCountsMode.Search).ToString();
                //元クラスを変更する場合
                //String view = "0";
                //if (EpgAutoAddInfo != null)
                //{
                //    view = EpgAutoAddInfo.searchCount.ToString(); 
                //}
                //return view;
            }
        }
        //"SearchCount"のうち、予約アイテム数
        //検索の無効・有効によってAddCountやSearchCountと異なる値になる。
        public String ReserveCount 
        {
            get
            {
                return getItemCounts(itemCountsMode.Reserve).ToString();
                //元クラスを変更する場合
                //String view = "0";
                //if (EpgAutoAddInfo != null)
                //{
                //    view = EpgAutoAddInfo.reserveCount.ToString(); 
                //}
                //return view;
            }
        }
        //"ReserveCount"のうち、有効な予約アイテム数
        public String OnCount
        {
            get
            {
                return getItemCounts(itemCountsMode.On).ToString();
                //元クラスを変更する場合
                //元クラスで実装するなら、onCountなしで、reserveCount-offCountでもいいかも。
                //String view = "0";
                //if (EpgAutoAddInfo != null)
                //{
                //    view = EpgAutoAddInfo.onCount.ToString(); 
                //}
                //return view;
            }
        }
        //"ReserveCount"のうち、無効な予約アイテム数
        public String OffCount
        {
            get
            {
                return getItemCounts(itemCountsMode.Off).ToString();
                //元クラスを変更する場合
                //String view = "0";
                //if (EpgAutoAddInfo != null)
                //{
                //    view = EpgAutoAddInfo.offCount.ToString(); 
                //}
                //return view;
            }
        }

        //以下はこのクラス内で実装する場合のコード
        //NWでは重すぎてほぼ使い物にならない。
        private bool isChange;
        private uint[] itemCounts = new uint[] { 0, 0, 0, 0, 0 };
        private enum itemCountsMode :byte 
        {
            /// <summary>登録数</summary>
            Add=0,
            /// <summary>検索数</summary>
            Search,
            /// <summary>予約数</summary>
            Reserve,
            /// <summary>有効予約数</summary>
            On,
            /// <summary>無効予約数</summary>
            Off
        }
        private uint getItemCounts(itemCountsMode Mode=itemCountsMode.Add )
        {
            //範囲外
            if ((int)Mode > itemCounts.Length)
            {
                return 0;
            }

            if (EpgAutoAddInfo == null)
            {
                return 0;
            }

            if (isChange == true)
            {
                itemCounts[(uint)itemCountsMode.Add] = EpgAutoAddInfo.addCount;
                
                List<SearchItem> itemlist = new List<SearchItem>();

                //この関数の負荷がNWで高過ぎる。通信時間で相当待たされてしまう。
                //列項目1個表示されるごとにEpgAutoDataItemが生成されるため、itemCountsでの保持も役に立たず。
                //結果の数字だけ返すメソッドをcmdに追加して(通信量削減)、結果を外部保存すれば(通信回数削減)、
                //待ち時間を10分の1くらいには出来そうだが‥そのくらいなら元クラスを変更した方がいいかも？
                getSearchItemList(ref itemlist); 

                itemCounts[(int)itemCountsMode.Search] = (uint)itemlist.Count;

                //自動予約が無効の時は、SearchCount≠OnCountなので両方カウントする
                int OnCount = 0;
                int OffCount = 0;
                foreach (SearchItem item in itemlist)
                {
                    if (item.IsReserved == true)
                    {
                        if (item.ReserveInfo.RecSetting.RecMode == 5)
                        {
                            OffCount++;
                        }
                        else
                        {
                            OnCount++;
                        }
                    }
                }
                itemCounts[(int)itemCountsMode.Reserve ] = (uint)(OnCount+OffCount);
                itemCounts[(int)itemCountsMode.On] = (uint)OnCount;
                itemCounts[(int)itemCountsMode.Off] = (uint)OffCount;
            }

            return itemCounts[(int)Mode];
        }

        private void getSearchItemList(ref List<SearchItem> itemlist)
        {

            CtrlCmdUtil cmd = CommonManager.Instance.CtrlCmd;

            EpgSearchKeyInfo key = new EpgSearchKeyInfo();
            EpgSearchKeyInfo key2 = this.EpgAutoAddInfo.searchInfo;
            //代入すると参照コピーになり、「検索無効」が消去されてしまう。
            //条件保存して後で復元するのは、エラー時に対応出来ないのでNG。
            //何とも美しくないが。
            key.aimaiFlag=key2.aimaiFlag;
            key.andKey=key2.andKey;
            key.audioList=key2.audioList;
            key.chkRecDay=key2.chkRecDay;
            key.chkRecEnd=key2.chkRecEnd;
            key.contentList=key2.contentList;
            key.dateList=key2.dateList;
            key.freeCAFlag=key2.freeCAFlag;
            key.notContetFlag=key2.notContetFlag;
            key.notDateFlag=key2.notDateFlag;
            key.notKey=key2.notKey;
            key.regExpFlag=key2.regExpFlag;
            key.serviceList=key2.serviceList;
            key.titleOnlyFlag=key2.titleOnlyFlag;
            key.videoList=key2.videoList;

            key.andKey = key.andKey.Substring(key.andKey.StartsWith("^!{999}") ? 7 : 0);

            List<EpgEventInfo> list = new List<EpgEventInfo>();
            List<EpgSearchKeyInfo> keyList = new List<EpgSearchKeyInfo>();
            keyList.Add(key);
            
            try
            {
                cmd.SendSearchPg(keyList, ref list);

                foreach (EpgEventInfo info in list)
                {
                    SearchItem item = new SearchItem();
                    item.EventInfo = info;

                    if (info.start_time.AddSeconds(info.durationSec) > DateTime.Now)
                    {
                        //予約情報との突き合わせ
                        foreach (ReserveData info2 in CommonManager.Instance.DB.ReserveList.Values)
                        {
                            if (info.original_network_id == info2.OriginalNetworkID &&
                                info.transport_stream_id == info2.TransportStreamID &&
                                info.service_id == info2.ServiceID &&
                                info.event_id == info2.EventID)
                            {
                                item.ReserveInfo = info2;
                                break;
                            }
                        }
                        itemlist.Add(item);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }

            //テストコード
            //SearchItem item1 = new SearchItem();
            //SearchItem item2 = new SearchItem();
            //SearchItem item3 = new SearchItem();
            //SearchItem item4 = new SearchItem();
            //itemlist.Add(item1);
            //itemlist.Add(item2);
            //item3.ReserveInfo = new ReserveData();
            //itemlist.Add(item3);
            //item4.ReserveInfo = new ReserveData();
            //item4.ReserveInfo.RecSetting.RecMode = 5;
            //itemlist.Add(item4);
            return;

        }

        //ここまで追加カウント関係のコード

        public String JyanruKey
        {
            get
            {
                String view = "";
                if (this.EpgAutoAddInfo != null)
                {
                    Dictionary<int, List<int>> nibbleDict1 = new Dictionary<int, List<int>>();  // 小ジャンルを大ジャンルでまとめる
                    foreach (EpgContentData ecd1 in this.EpgAutoAddInfo.searchInfo.contentList)
                    {
                        if (nibbleDict1.ContainsKey(ecd1.content_nibble_level_1))
                        {
                            nibbleDict1[ecd1.content_nibble_level_1].Add(ecd1.content_nibble_level_2);
                        }
                        else
                        {
                            nibbleDict1.Add(ecd1.content_nibble_level_1, new List<int>() { ecd1.content_nibble_level_2 });
                        }
                    }
                    foreach (KeyValuePair<int, List<int>> kvp1 in nibbleDict1)
                    {
                        int nibble1 = kvp1.Key;
                        UInt16 contentKey1 = (UInt16)(nibble1 << 8 | 0xFF);
                        //
                        string smallCategory1 = "";
                        foreach (int nibble2 in kvp1.Value)
                        {
                            UInt16 contentKey2 = (UInt16)(nibble1 << 8 | nibble2);
                            if (nibble2 != 0xFF)
                            {
                                if (smallCategory1 != "") { smallCategory1 += ", "; }
                                if (CommonManager.Instance.ContentKindDictionary.ContainsKey(contentKey2))
                                {
                                    smallCategory1 += CommonManager.Instance.ContentKindDictionary[contentKey2].ToString().Trim();
                                }
                            }
                        }
                        //
                        if (view != "") { view += ", "; }
                        if (CommonManager.Instance.ContentKindDictionary.ContainsKey(contentKey1))
                        {
                            view += "[" + CommonManager.Instance.ContentKindDictionary[contentKey1].ToString().Trim();
                            if (smallCategory1 != "") { view += " - " + smallCategory1; }
                            view += "]";
                        }
                    }
                }
                else
                {
                    view = "なし";
                }
                return view;
            }
        }

        /// <summary>
        /// NHK総合１・東京、NHKBS1
        /// </summary>
        public String ServiceKey
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    foreach (ulong service1 in EpgAutoAddInfo.searchInfo.serviceList)
                    {
                        try
                        {
                            if (view != "") { view += ", "; }
                            view += ChSet5.Instance.ChList[service1].ServiceName;
                        }
                        catch
                        {
                            view += "(x_x)";
                        }
                    }
                    //if (EpgAutoAddInfo.searchInfo.serviceList.Count == 1)
                    //{
                    //    try
                    //    {
                    //        view = ChSet5.Instance.ChList[(ulong)EpgAutoAddInfo.searchInfo.serviceList[0]].ServiceName;
                    //    }
                    //    catch
                    //    {
                    //        view = "検索エラー";
                    //    }
                    //}
                    //else if (EpgAutoAddInfo.searchInfo.serviceList.Count > 1)
                    //{
                    //    view = "複数指定";
                    //}
                }
                if (view == "")
                {
                    view = "なし";
                }
                return view;
            }
        }

        /// <summary>
        /// 地デジ、BS、CS
        /// </summary>
        public String NetworkKey
        {
            get
            {
                String view1 = "";
                if (this.EpgAutoAddInfo != null)
                {
                    List<string> networkKeyList1 = new List<string>();
                    foreach (ulong service1 in this.EpgAutoAddInfo.searchInfo.serviceList)
                    {
                        string network1 = "";
                        try
                        {
                            ChSet5Item chSet5Item1 = ChSet5.Instance.ChList[service1];
                            // SearchKeyDescViewよりコピペ
                            if ((0x7880 <= chSet5Item1.ONID && chSet5Item1.ONID <= 0x7FE8) &&
                                (chSet5Item1.ServiceType == 0x01 || chSet5Item1.ServiceType == 0xA5))
                            {
                                network1 = "地デジ";
                            }
                            else if (chSet5Item1.ONID == 0x04 &&
                              (chSet5Item1.ServiceType == 0x01 || chSet5Item1.ServiceType == 0xA5))
                            {
                                network1 = "BS";
                            }
                            else if ((chSet5Item1.ONID == 0x06 || chSet5Item1.ONID == 0x07) &&
                              (chSet5Item1.ServiceType == 0x01 || chSet5Item1.ServiceType == 0xA5))
                            {
                                network1 = "CS";
                            }
                            else
                            {
                                network1 = "(?_?)";
                            }
                            //network1 = ChSet5.Instance.ChList[service1].NetworkName;
                        }
                        catch
                        {
                            network1 = "(x_x)";
                        }
                        if (!networkKeyList1.Contains(network1))
                        {
                            networkKeyList1.Add(network1);
                        }
                    }
                    foreach (string network1 in networkKeyList1)
                    {
                        if (view1 != "") { view1 += ", "; }
                        view1 += network1;
                    }
                }
                if (view1 == "")
                {
                    view1 = "なし";
                }
                return view1;
            }
        }

        public String Pittari
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.recSetting.PittariFlag == 0)
                    {
                        view = "しない";
                    }
                    else if (EpgAutoAddInfo.recSetting.PittariFlag == 1)
                    {
                        view = "する";
                    }
                }
                return view;
            }
        }

        public String KeyEnabled
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.andKey.StartsWith("^!{999}"))
                    {
                        view = "いいえ";
                    }
                    else
                    {
                        view = "はい";
                    }
                }
                return view;
            }
        }

        public SolidColorBrush BackColor
        {
            get
            {
                SolidColorBrush color = CommonManager.Instance.ResDefBackColor;
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo.andKey.StartsWith("^!{999}"))
                    {
                        color = CommonManager.Instance.ResNoBackColor;
                    }
                }
                return color;
            }
        }

        public TextBlock ToolTipView
        {
            get
            {
                if (Settings.Instance.NoToolTip == true)
                {
                    return null;
                }
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo != null)
                    {
                        view += "検索条件\r\n";
                        view += "Andキーワード：" + AndKey + "\r\n";
                        view += "Notキーワード：" + NotKey + "\r\n";
                        view += "正規表現モード：" + RegExp + "\r\n";
                        view += "番組名のみ検索対象：" + TitleOnly + "\r\n";
                        view += "ジャンル絞り込み：" + JyanruKey + "\r\n";
                        view += "時間絞り込み：" + DateKey + "\r\n";
                        view += "検索対象サービス：" + ServiceKey + "\r\n";

                        view += "\r\n";
                    }
                    if (EpgAutoAddInfo.recSetting != null)
                    {
                        view += "録画設定\r\n";
                        view += "録画モード：" + RecMode + "\r\n";
                        view += "優先度：" + Priority + "\r\n";
                        view += "追従：" + Tuijyu + "\r\n";

                        if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x01) == 0)
                        {
                            view += "指定サービス対象データ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "指定サービス対象データ : ";
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x10) > 0)
                            {
                                view += "字幕含む ";
                            }
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x20) > 0)
                            {
                                view += "データカルーセル含む";
                            }
                            view += "\r\n";
                        }

                        view += "録画実行bat : " + EpgAutoAddInfo.recSetting.BatFilePath + "\r\n";

                        if (EpgAutoAddInfo.recSetting.RecFolderList.Count == 0)
                        {
                            view += "録画フォルダ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画フォルダ : \r\n";
                            foreach (RecFileSetInfo info in EpgAutoAddInfo.recSetting.RecFolderList)
                            {
                                view += info.RecFolder + " (WritePlugIn:" + info.WritePlugIn + ")\r\n";
                            }
                        }

                        if (EpgAutoAddInfo.recSetting.UseMargineFlag == 0)
                        {
                            view += "録画マージン : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画マージン : 開始 " + EpgAutoAddInfo.recSetting.StartMargine.ToString() +
                                " 終了 " + EpgAutoAddInfo.recSetting.EndMargine.ToString() + "\r\n";
                        }

                        if (EpgAutoAddInfo.recSetting.SuspendMode == 0)
                        {
                            view += "録画後動作 : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画後動作 : ";
                            switch (EpgAutoAddInfo.recSetting.SuspendMode)
                            {
                                case 1:
                                    view += "スタンバイ";
                                    break;
                                case 2:
                                    view += "休止";
                                    break;
                                case 3:
                                    view += "シャットダウン";
                                    break;
                                case 4:
                                    view += "何もしない";
                                    break;
                            }
                            if (EpgAutoAddInfo.recSetting.RebootFlag == 1)
                            {
                                view += " 復帰後再起動する";
                            }
                            view += "\r\n";
                        }
                    }
                }

                TextBlock block = new TextBlock();
                block.Text = view;
                block.MaxWidth = 400;
                block.TextWrapping = TextWrapping.Wrap;
                return block;
            }
        }

        /// <summary>
        /// ToolTipViewからコピペ
        /// </summary>
        public String SearchInfoText
        {
            get
            {
                String view = "";
                if (EpgAutoAddInfo != null)
                {
                    if (EpgAutoAddInfo.searchInfo != null)
                    {
                        view += "検索条件\r\n";
                        view += "Andキーワード：" + AndKey + "\r\n";
                        view += "Notキーワード：" + NotKey + "\r\n";
                        view += "正規表現モード：" + RegExp + "\r\n";
                        view += "番組名のみ検索対象：" + TitleOnly + "\r\n";
                        view += "ジャンル絞り込み：" + JyanruKey + "\r\n";
                        view += "時間絞り込み：" + DateKey + "\r\n";
                        view += "検索対象サービス：" + ServiceKey + "\r\n";

                        view += "\r\n";
                    }
                    if (EpgAutoAddInfo.recSetting != null)
                    {
                        view += "録画設定\r\n";
                        view += "録画モード：" + RecMode + "\r\n";
                        view += "優先度：" + Priority + "\r\n";
                        view += "追従：" + Tuijyu + "\r\n";

                        if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x01) == 0)
                        {
                            view += "指定サービス対象データ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "指定サービス対象データ : ";
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x10) > 0)
                            {
                                view += "字幕含む ";
                            }
                            if ((EpgAutoAddInfo.recSetting.ServiceMode & 0x20) > 0)
                            {
                                view += "データカルーセル含む";
                            }
                            view += "\r\n";
                        }

                        view += "録画実行bat : " + EpgAutoAddInfo.recSetting.BatFilePath + "\r\n";

                        if (EpgAutoAddInfo.recSetting.RecFolderList.Count == 0)
                        {
                            view += "録画フォルダ : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画フォルダ : \r\n";
                            foreach (RecFileSetInfo info in EpgAutoAddInfo.recSetting.RecFolderList)
                            {
                                view += info.RecFolder + " (WritePlugIn:" + info.WritePlugIn + ")\r\n";
                            }
                        }

                        if (EpgAutoAddInfo.recSetting.UseMargineFlag == 0)
                        {
                            view += "録画マージン : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画マージン : 開始 " + EpgAutoAddInfo.recSetting.StartMargine.ToString() +
                                " 終了 " + EpgAutoAddInfo.recSetting.EndMargine.ToString() + "\r\n";
                        }

                        if (EpgAutoAddInfo.recSetting.SuspendMode == 0)
                        {
                            view += "録画後動作 : デフォルト\r\n";
                        }
                        else
                        {
                            view += "録画後動作 : ";
                            switch (EpgAutoAddInfo.recSetting.SuspendMode)
                            {
                                case 1:
                                    view += "スタンバイ";
                                    break;
                                case 2:
                                    view += "休止";
                                    break;
                                case 3:
                                    view += "シャットダウン";
                                    break;
                                case 4:
                                    view += "何もしない";
                                    break;
                            }
                            if (EpgAutoAddInfo.recSetting.RebootFlag == 1)
                            {
                                view += " 復帰後再起動する";
                            }
                            view += "\r\n";
                        }
                    }
                }

                return view;
            }
        }

        public Brush BorderBrush
        {
            get
            {
                Brush color1 = Brushes.Gainsboro;
                if (this.EpgAutoAddInfo.searchInfo.contentList.Count > 0)
                {
                    byte content_nibble_level_1 = this.EpgAutoAddInfo.searchInfo.contentList[0].content_nibble_level_1;
                    if (content_nibble_level_1 <= 0x0B || content_nibble_level_1 == 0x0F && Settings.Instance.ContentColorList.Count > content_nibble_level_1)
                    {
                        try
                        {
                            color1 = CommonManager.Instance.CustContentColorList[content_nibble_level_1];
                        }
                        catch
                        {
                            ;
                        }
                    }
                }

                return color1;
            }
        }

    }
}
