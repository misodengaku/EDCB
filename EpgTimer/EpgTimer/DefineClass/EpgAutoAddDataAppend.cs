using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

using CtrlCmdCLI;
using CtrlCmdCLI.Def;

namespace EpgTimer
{
    public class EpgAutoAddDataAppend
    {
        public EpgAutoAddDataAppend(EpgAutoAddData master1,bool LoadList=true)
        {
            master = master1;
            updateSearchItemList = LoadList;
	    }

        private EpgAutoAddData master = null;
        private List<SearchItem> searchItemList = new List<SearchItem>();
        private uint onCount = 0;
        private uint offCount = 0;

        public EpgAutoAddData Master
        {
            get 
            { 
                return master;
            } 
        }
        public uint dataID
        {
            get
            {
                return (master != null ? master.dataID : 0);
            }
        }
        public List<SearchItem> SearchItemList
        { 
            get 
            {
                RefreshData();
                return searchItemList;
            }
        }
        public uint SearchCount
        { 
            get 
            {
                RefreshData();
                return (uint)searchItemList.Count;
            }
        }
        public uint ReserveCount 
        { 
            get
            {
                RefreshData();
                return onCount + offCount;
            }
        }
        public uint OnCount
        {
            get
            {
                RefreshData();
                return onCount;
            }
        }
        public uint OffCount
        {
            get
            {
                RefreshData();
                return offCount;
            }
        }

        //予約情報の更新があったとき、CommonManager.Instance.DB.epgAutoAddAppendList()に入っていればフラグを立ててもらえる。
        public bool updateCounts = false;

        //リストの更新が必要なとき。
        public bool updateSearchItemList = false;

        //必要なら情報の更新をする。
        //通常は、予約情報との突き合わせのみやり直す。
        private void RefreshData()
        {
            if (master == null) return;

            if (updateSearchItemList == true)
            {
                ReloadSearchItemList();
                //updateSearchItemList = false;
                //updateCounts = true;
            }

            if (updateCounts == false) return;

            onCount = 0;
            offCount = 0;

            foreach (SearchItem item in searchItemList)
            {
                //予約情報との突き合わせ
                item.ReserveInfo = null;

                foreach (ReserveData info2 in CommonManager.Instance.DB.ReserveList.Values)
                {

                    if (item.EventInfo.original_network_id == info2.OriginalNetworkID &&
                        item.EventInfo.transport_stream_id == info2.TransportStreamID &&
                        item.EventInfo.service_id == info2.ServiceID &&
                        item.EventInfo.event_id == info2.EventID)
                    {
                        item.ReserveInfo = info2;
                        break;
                    }
                }

                if (item.IsReserved == true)
                {
                    if (item.ReserveInfo.RecSetting.RecMode == 5)
                    {
                        offCount++;
                    }
                    else
                    {
                        onCount++;
                    }
                }
            }

            updateCounts = false;
        }

        //区別付く形でSendSearchPg()がリストを返してきてくれたらいいのに
        //public static void LoadSearchItemList(List<EpgAutoAddDataAppend> lists){}

        private void ReloadSearchItemList()
        {
            if (this.master == null) return;

            CtrlCmdUtil cmd = CommonManager.Instance.CtrlCmd;

            this.searchItemList.Clear();
            this.searchItemList = null;
            this.searchItemList = new List<SearchItem>();

            EpgSearchKeyInfo key = new EpgSearchKeyInfo();
            EpgSearchKeyInfo key2 = this.master.searchInfo;
            //「検索無効」の対応のため、コピーする。
            //CtrlCmdUtil.CopyData()が使えるかコピーコンストラクタでもあれば簡単だが
            key.aimaiFlag = key2.aimaiFlag;
            key.andKey = key2.andKey;
            key.audioList = key2.audioList;
            key.chkRecDay = key2.chkRecDay;
            key.chkRecEnd = key2.chkRecEnd;
            key.contentList = key2.contentList;
            key.dateList = key2.dateList;
            key.freeCAFlag = key2.freeCAFlag;
            key.notContetFlag = key2.notContetFlag;
            key.notDateFlag = key2.notDateFlag;
            key.notKey = key2.notKey;
            key.regExpFlag = key2.regExpFlag;
            key.serviceList = key2.serviceList;
            key.titleOnlyFlag = key2.titleOnlyFlag;
            key.videoList = key2.videoList;

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
                        UInt64 serviceKey = CommonManager.Create64Key(info.original_network_id, info.transport_stream_id, info.service_id);
                        if (ChSet5.Instance.ChList.ContainsKey(serviceKey) == true)
                        {
                            item.ServiceName = ChSet5.Instance.ChList[serviceKey].ServiceName;
                        }

                        this.searchItemList.Add(item);
                    }
                }

                //予約情報との突き合わせは、必要時点で実施される。
                this.updateCounts = true;
                this.updateSearchItemList = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
            }

            return;
        }

    }
}
