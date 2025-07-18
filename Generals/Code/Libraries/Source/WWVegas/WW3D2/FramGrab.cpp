/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FramGrab.cpp: implementation of the FrameGrabClass class.
//
//////////////////////////////////////////////////////////////////////

#include "WWprecompiled.h"
#include "framgrab.h"

// BEATO Begin:
extern "C" 
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
}
// BEATO End

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FrameGrabClass::FrameGrabClass(const char *filename, MODE mode, int width, int height, int bitcount, float framerate)
{
	int hr = 0; //HRESULT          hr; 
	
	int fps = framerate;
	Mode = mode;
	Filename = filename;
	FrameRate = framerate;
	Counter = 0;
	Width = width;
	Height = height;

	//Stream = 0;
	//AVIFile = 0;

	if( Mode != AVI )
		return;

	// Not portable Windows AVI library
	// AVIFileInit();          // opens AVIFile library  
	avformat_network_init();

	// find the first free file with this prefix
	int counter = 0;
	int result;
	char file[256];
	do 
	{
		sprintf(file, "%s%d.AVI", filename, counter++);
		
		//result = _access(file, 0);
		result = std::filesystem::exists( std::filesystem::path( file ) ) ?  0 : -1; 

	} while(result != -1);

	// Create new AVI file using AVIFileOpen. 
    // hr = AVIFileOpen(&AVIFile, file, OF_WRITE | OF_CREATE, nullptr );
	hr = avformat_alloc_output_context2( &fmt_ctx, nullptr, "avi", file );
    if ( hr < 0 ) 
	{
		char buf[256];
		sprintf(buf, "Unable to open %s\n", Filename);
		OutputDebugString(buf);
		CleanupAVI();
		return;
	}
    

    // Create a stream using AVIFileCreateStream. 
	//AVIStreamInfo.fccType = streamtypeVIDEO;
	//AVIStreamInfo.fccHandler = mmioFOURCC('M','S','V','C');
	//AVIStreamInfo.dwFlags = 0;
	//AVIStreamInfo.dwCaps = 0;
	//AVIStreamInfo.wPriority = 0;
	//AVIStreamInfo.wLanguage = 0;
	//AVIStreamInfo.dwScale = 1;
	//AVIStreamInfo.dwRate = (int)FrameRate;
	//AVIStreamInfo.dwStart = 0;
	//AVIStreamInfo.dwLength = 0;
	//AVIStreamInfo.dwInitialFrames = 0;
	//AVIStreamInfo.dwSuggestedBufferSize = 0;
	//AVIStreamInfo.dwQuality = 0;
	//AVIStreamInfo.dwSampleSize = 0;
	//SetRect(&AVIStreamInfo.rcFrame, 0, 0, width, height);  
	//AVIStreamInfo.dwEditCount = 0;
	//AVIStreamInfo.dwFormatChangeCount = 0;
	//sprintf(AVIStreamInfo.szName,"G");
    //hr = AVIFileCreateStream(AVIFile, &Stream, &AVIStreamInfo);
	//if ( hr != 0 ) 
	//{
	//	CleanupAVI();
	//	return;     
	//}


	const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);
	if ( codec )
    {
		char buf[256];
		sprintf(buf, "Unable to open %s\n", Filename);
		OutputDebugString(buf);
		CleanupAVI();
		return;
	}
		
	stream = avformat_new_stream(fmt_ctx, codec);
    codec_ctx = avcodec_alloc_context3(codec);
    codec_ctx->codec_id = codec->id;
    codec_ctx->bit_rate = 400000;
    codec_ctx->width = width;
    codec_ctx->height = height;
    codec_ctx->time_base = {1, fps};
    codec_ctx->framerate = {fps, 1};
    codec_ctx->gop_size = 10;
    codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

	if ( fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER )
		codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	
    // Set format of new stream
	//BitmapInfoHeader.biWidth = width;
	//BitmapInfoHeader.biHeight = height; 
	//BitmapInfoHeader.biBitCount = (unsigned short)bitcount;
    //BitmapInfoHeader.biSizeImage = ((((UINT)BitmapInfoHeader.biBitCount * BitmapInfoHeader.biWidth + 31) & ~31) / 8) * BitmapInfoHeader.biHeight; 
	//BitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER); // size of structure
	//BitmapInfoHeader.biPlanes = 1; // must be set to 1
	//BitmapInfoHeader.biCompression = BI_RGB; // uncompressed
 	//BitmapInfoHeader.biXPelsPerMeter = 1; // not used
	//BitmapInfoHeader.biYPelsPerMeter = 1; // not used
	//BitmapInfoHeader.biClrUsed = 0; // all colors are used
	//BitmapInfoHeader.biClrImportant = 0; // all colors are important
    //hr = AVIStreamSetFormat(Stream, 0, &BitmapInfoHeader, sizeof(BitmapInfoHeader)); 
    //if (hr != 0) 
	//{
		//CleanupAVI();
		//return;     
	//}  
	avcodec_open2(codec_ctx, codec, nullptr);
    avcodec_parameters_from_context(stream->codecpar, codec_ctx);

    avio_open(&fmt_ctx->pb, file, AVIO_FLAG_WRITE);
    avformat_write_header(fmt_ctx, nullptr);

    frame = av_frame_alloc();
    frame->format = codec_ctx->pix_fmt;
    frame->width = codec_ctx->width;
    frame->height = codec_ctx->height;
    av_frame_get_buffer(frame, 32);

    sws_ctx = sws_getContext(width, height, AV_PIX_FMT_RGB24, width, height, AV_PIX_FMT_YUV420P, SWS_BILINEAR, nullptr, nullptr, nullptr );

    //Bitmap = (long *) GlobalAllocPtr(GMEM_MOVEABLE, BitmapInfoHeader.biSizeImage); 
}

FrameGrabClass::~FrameGrabClass( void )
{
	if(Mode == AVI) 
		CleanupAVI();
}

void FrameGrabClass::CleanupAVI( void ) 
{
#if 0
	if(Bitmap != 0) { GlobalFreePtr(Bitmap); Bitmap = 0; }
	if(Stream != 0) { AVIStreamRelease(Stream); Stream = 0; }
	if(AVIFile != 0) { AVIFileRelease(AVIFile); AVIFile = 0; }
	
	AVIFileExit();
#else
	av_write_trailer(fmt_ctx);
    if (sws_ctx) 
		sws_freeContext(sws_ctx);
    
	if (frame)
		av_frame_free(&frame);
    
	if (codec_ctx)
		avcodec_free_context(&codec_ctx);
    
	if (fmt_ctx)	
	{
        avio_closep(&fmt_ctx->pb);
        avformat_free_context(fmt_ctx);
    }
#endif
	Mode = RAW;
}

void FrameGrabClass::GrabAVI(void *BitmapPointer)
{
	int hr = 0;
#if 0
    // CompressDIB(&bi, lpOld, &biNew, lpNew);  

    // Save the compressed data using AVIStreamWrite. 
    HRESULT hr = AVIStreamWrite(Stream, Counter++, 1, BitmapPointer, BitmapInfoHeader.biSizeImage, AVIIF_KEYFRAME, nullptr, nullptr );     
	if(hr != 0) 
	{
		char buf[256];
		sprintf(buf, "avi write error %x/%d\n", hr, hr);
		OutputDebugString(buf);
	}
#else
	av_frame_make_writable( frame );

    uint8_t* src_slices =  static_cast<uint8_t*>( BitmapPointer );
    int src_stride = 3 * Width;

    sws_scale(sws_ctx, &src_slices, &src_stride, 0, Height, frame->data, frame->linesize );

    frame->pts = Counter++;

    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = nullptr;
    pkt.size = 0;

    avcodec_send_frame(codec_ctx, frame);
	hr = avcodec_receive_packet(codec_ctx, &pkt);
    if ( hr == 0 ) 
	{
        pkt.stream_index = stream->index;
        av_interleaved_write_frame(fmt_ctx, &pkt);
        av_packet_unref(&pkt);

		char buf[256];
		sprintf(buf, "avi write error %x/%d\n", hr, hr);
		OutputDebugString(buf);
	}
#endif
}

void FrameGrabClass::GrabRawFrame(void * /*BitmapPointer*/)
{

}


void FrameGrabClass::ConvertGrab(void *BitmapPointer) 
{
	ConvertFrame(BitmapPointer);
	Grab( Bitmap );
}


void FrameGrabClass::Grab(void *BitmapPointer) 
{
	if(Mode == AVI) 
		GrabAVI(BitmapPointer);
	else
		GrabRawFrame(BitmapPointer);
}


void FrameGrabClass::ConvertFrame(void *BitmapPointer) 
{
	long *image = (long *) BitmapPointer;

	// copy the data, doing a vertical flip & byte re-ordering of the pixel longwords
	int y = height;
	while(y--) 
	{
		int x = width;
		int yoffset = y * width;
		int yoffset2 = (height - y) * width;
		while(x--) {
			long *source = &image[yoffset + x];
			long *dest = &Bitmap[yoffset2 + x];
			*dest = *source;
			unsigned char *c = (unsigned char *) dest;
			c[3] = c[0];
			c[0] = c[2];
			c[2] = c[3];
			c[3] = 0;
		}
	}
}
