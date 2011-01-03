// File_Lxf - Info for LXF files
// Copyright (C) 2006-2011 MediaArea.net SARL, Info@MediaArea.net
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
// Information about Lxf files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_LxfH
#define MediaInfo_File_LxfH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <vector>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Lxf
//***************************************************************************

class File_Lxf : public File__Analyze
{
public :
    //Constructor/Destructor
    File_Lxf();

protected :
    //Streams management
    void Streams_Fill ();
    void Streams_Fill_PerStream (File__Analyze* Parser);
    void Streams_Finish ();

    //Buffer - Synchro
    bool Synchronize();
    bool Synched_Test();

    //Buffer - Global
    size_t Read_Buffer_Seek (size_t Method, int64u Value);
    void Read_Buffer_Unsynched();

    //Buffer - Per element
    void Header_Parse();
    void Data_Parse();

    //Elements
    void Header();
    void Header_Info();
    void Header_Meta();
    void Audio();
    bool Audio_Stream(size_t Pos);
    void Video();
    bool Video_Stream(size_t Pos);

    //Streams
    struct stream
    {
        File__Analyze*  Parser;
        int64u          BytesPerFrame;

        stream()
        {
            Parser=NULL;
            BytesPerFrame=(int64u)-1;
        }
    };
    std::vector<stream> Videos;
    std::vector<stream> Audios;
    struct stream_header
    {
        int64u          TimeStamp_Begin;
        int64u          TimeStamp_End;
        int64u          Duration;
        int8u           PictureType;

        stream_header()
        {
            TimeStamp_Begin=(int64u)-1;
            TimeStamp_End=(int64u)-1;
            Duration=(int64u)-1;
            PictureType=(int8u)-1;
        }
        stream_header(int64u TimeStamp_Begin_, int64u TimeStamp_End_, int64u Duration_, int8u PictureType_)
        {
            TimeStamp_Begin=TimeStamp_Begin_;
            TimeStamp_End=TimeStamp_End_;
            Duration=Duration_;
            PictureType=PictureType_;
        }
    };
    stream_header Videos_Header;
    stream_header Audios_Header;

    //Temp
    bool                    LookingForLastFrame;
    int64u                  Stream_Count;
    int64u                  Info_General_StreamSize;
    std::vector<int64u>     Header_Sizes;
    std::vector<int64u>     Audio_Sizes;
    size_t                  Audio_Sizes_Pos;
    std::vector<int64u>     Video_Sizes;
    int8u                   SampleSize;

    //Seek
    typedef std::map<int64u, stream_header> time_offsets;
    time_offsets            TimeOffsets;
    int64u                  SeekRequest_Divider;
    int64u                  SeekRequest;
    bool                    Duration_Detected;
};

} //NameSpace

#endif

