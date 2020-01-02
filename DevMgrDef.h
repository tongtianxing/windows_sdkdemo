#pragma once

class CDevBase;
//class CVDvsDevice;
class CVDevGroup;
class CVehicleBase;
typedef std::map<int, CDevBase*>			mapDvsDevice;
typedef mapDvsDevice::iterator				mapDvsDevIter;
typedef std::map<std::string, CDevBase*>			mapStrDevice;
typedef mapStrDevice::iterator				mapStrDevIter;
typedef std::map<int, CVDevGroup*>			mapDevGroup;
typedef mapDevGroup::iterator				mapDevGroupIter;

typedef std::list<CDevBase*>				lstDevice;
typedef lstDevice::iterator					lstDeviceIter;

typedef std::map<std::string, CVehicleBase*>		mapVehicleBase;
typedef mapVehicleBase::iterator			mapVehicleBaseIter;

typedef std::map<int, GPSDEVGroup_S>		mapIDIRDEVGroup;
typedef mapIDIRDEVGroup::iterator			mapIDIRGroupIter;
typedef std::map<int, GPSDevInfo_S>			mapIDIRDEVInfo;
typedef mapIDIRDEVInfo::iterator			mapIDIRDEVIter;


class CDevCtrl;
class CDevTreeCtrl;
typedef std::vector<CDevCtrl*>				vecDevCtrl;
typedef vecDevCtrl::iterator				vecDevCtrlIter;

typedef std::map<int, int>	mapInt;
typedef mapInt::iterator	mapIntIter;