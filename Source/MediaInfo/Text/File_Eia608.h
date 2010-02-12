// File_Eia608 - Info for EIA-608 files
// Copyright (C) 2009-2010 MediaArea.net SARL, Info@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Information about PGS files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_Eia608H
#define MediaInfo_File_Eia608H
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <vector>
#include <bitset>
using namespace std;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Eia608
//***************************************************************************

class File_Eia608 : public File__Analyze
{
public :
    //In
    int8u   cc_type;

    //Out

    //Constructor/Destructor
    File_Eia608();

private :
    //Streams management
    void Streams_Fill();

    //Buffer - Global
    void Read_Buffer_Continue();

    //Temp
    std::wstring Captions;

    //Function
    void Characters_Eia608   (int8u Character);

    std::vector<int8u> XDS_Data;
    bool TextMode;
    bool DataChannelMode;
    bool InBack; //The back buffer is written
    bool HasChanged;

    void XDS();
    void XDS_Current();
    void XDS_Current_ContentAdvisory();
    void XDS_Current_CopyAndRedistributionControlPacket();
    void XDS_PublicService();
    void XDS_PublicService_NationalWeatherService();
    void Special(int8u cc_data_1, int8u cc_data_2);
    void Special_11(int8u cc_data_2);
    void Special_14(int8u cc_data_2);
    void Special_17(int8u cc_data_2);
    void PAC(int8u cc_data_1, int8u cc_data_2);

    //An attribute consists of Attribute_Color_*, optionally OR'd with Attribute_Underline and/or Attribute_Italic
    enum attributes
    {
        Attribute_Color_White   =0x00,
        Attribute_Color_Green   =0x01,
        Attribute_Color_Blue    =0x02,
        Attribute_Color_Cyan    =0x03,
        Attribute_Color_Red     =0x04,
        Attribute_Color_Yellow  =0x05,
        Attribute_Color_Magenta =0x06,
        Attribute_Underline     =0x10,
        Attribute_Italic        =0x20,
    };

    struct character
    {
        wchar_t Value;
        int8u   Attribute;

        character()
        {
            Value=L' ';
        }
    };
    vector<vector<character> > Characters_Front;
    vector<vector<character> > Characters_Back;
    int8u Attribute_Current;

    size_t x;
    size_t y;
    size_t RollUpLines;
};

} //NameSpace

#endif
