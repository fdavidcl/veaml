/**
 * @file
 * @brief Header file for ReaderBase class
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENSHOT_READER_BASE_H
#define OPENSHOT_READER_BASE_H

#include <iostream>
#include <iomanip>
#include <tr1/memory>
#include <stdlib.h>
#include "Fraction.h"
#include "Frame.h"
#include "Json.h"
#include <QtCore/qstring.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;

namespace openshot
{
	/**
	 * @brief This struct contains info about a media file, such as height, width, frames per second, etc...
	 *
	 * Each derived class of ReaderBase is responsible for updating this struct to reflect accurate information
	 * about the streams. Derived classes of ReaderBase should call the InitFileInfo() method to initialize the
	 * default values of this struct.
	 */
	struct ReaderInfo
	{
		bool has_video;	///< Determines if this file has a video stream
		bool has_audio;	///< Determines if this file has an audio stream
		float duration;	///< Length of time (in seconds)
		long long file_size;	///< Size of file (in bytes)
		int height;		///< The height of the video (in pixels)
		int width;		///< The width of the video (in pixesl)
		int pixel_format;	///< The pixel format (i.e. YUV420P, RGB24, etc...)
		Fraction fps;		///< Frames per second, as a fraction (i.e. 24/1 = 24 fps)
		int video_bit_rate;	///< The bit rate of the video stream (in bytes)
		Fraction pixel_ratio;	///< The pixel ratio of the video stream as a fraction (i.e. some pixels are not square)
		Fraction display_ratio;	///< The ratio of width to height of the video stream (i.e. 640x480 has a ratio of 4/3)
		string vcodec;		///< The name of the video codec used to encode / decode the video stream
		long int video_length;	///< The number of frames in the video stream
		int video_stream_index;		///< The index of the video stream
		Fraction video_timebase;	///< The video timebase determines how long each frame stays on the screen
		bool interlaced_frame;	// Are the contents of this frame interlaced
		bool top_field_first;	// Which interlaced field should be displayed first
		string acodec;		///< The name of the audio codec used to encode / decode the video stream
		int audio_bit_rate;	///< The bit rate of the audio stream (in bytes)
		int sample_rate;	///< The number of audio samples per second (44100 is a common sample rate)
		int channels;		///< The number of audio channels used in the audio stream
		int audio_stream_index;		///< The index of the audio stream
		Fraction audio_timebase;	///< The audio timebase determines how long each audio packet should be played
	};

	/**
	 * @brief This abstract class is the base class, used by all readers in libopenshot.
	 *
	 * Readers are types of classes that read video, audio, and image files, and
	 * return openshot::Frame objects. The only requirements for a 'reader', are to
	 * derive from this base class, implement the GetFrame method, and call the InitFileInfo() method.
	 */
	class ReaderBase
	{
	protected:
		/// Section lock for multiple threads
	    CriticalSection getFrameCriticalSection;

	    /// Debug JSON root
	    Json::Value debug_root;

		/// Append debug information as JSON
		void AppendDebugItem(Json::Value debug_item);

		/// Append debug information as JSON
		void AppendDebugMethod(string method_name, string arg1_name, int arg1_value,
												   string arg2_name, int arg2_value,
												   string arg3_name, int arg3_value,
												   string arg4_name, int arg4_value,
												   string arg5_name, int arg5_value,
												   string arg6_name, int arg6_value);

	public:

		/// Constructor for the base reader, where many things are initialized.
	    ReaderBase();

		/// Enable or disable debug output. Output will display on the standard output, and you can
		/// optionally invoke the OutputDebugJSON() method, which will format the debug output as JSON.
		bool debug;

		/// Information about the current media file
		ReaderInfo info;

		/// Close the reader (and any resources it was consuming)
		virtual void Close() = 0;

		/// Display file information in the standard output stream (stdout)
		void DisplayInfo();

		/// Test method to draw a bitmap on a Qt QGraphicsScene
		void DrawFrameOnScene(string path, long _graphics_scene_address);

		/// This method is required for all derived classes of ReaderBase, and returns the
		/// openshot::Frame object, which contains the image and audio information for that
		/// frame of video.
		///
		/// @returns The requested frame of video
		/// @param[in] number The frame number that is requested.
		virtual tr1::shared_ptr<Frame> GetFrame(int number) = 0;

	    /// A thread safe version of GetFrame.
	    tr1::shared_ptr<Frame> GetFrameSafe(int number);

		/// Determine if reader is open or closed
		virtual bool IsOpen() = 0;

		/// Get and Set JSON methods
		virtual string Json() = 0; ///< Generate JSON string of this object
		virtual void SetJson(string value) throw(InvalidJSON) = 0; ///< Load JSON string into this object
		virtual Json::Value JsonValue() = 0; ///< Generate Json::JsonValue for this object
		virtual void SetJsonValue(Json::Value root) = 0; ///< Load Json::JsonValue into this object

		/// Open the reader (and start consuming resources, such as images or video files)
		virtual void Open() = 0;

		/// Output debug information as JSON
		string OutputDebugJSON();

	};

}

#endif
