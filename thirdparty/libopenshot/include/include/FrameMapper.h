/**
 * @file
 * @brief Header file for the FrameMapper class
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

#ifndef OPENSHOT_FRAMEMAPPER_H
#define OPENSHOT_FRAMEMAPPER_H

#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <tr1/memory>
#include "../include/Cache.h"
#include "../include/ReaderBase.h"
#include "../include/Frame.h"
#include "../include/Fraction.h"
#include "../include/Exceptions.h"
#include "../include/KeyFrame.h"

using namespace std;

namespace openshot
{
	/**
	 * @brief This enumeration determines how frame rates are increased or decreased.
	 *
	 * Pull-down techniques are only needed to remove artificial fields added when converting
	 * between 24 fps (film) and television fps (29.97 fps NTSC or 25 fps PAL).
	 */
	enum PulldownType
	{
		PULLDOWN_CLASSIC,	///< Classic 2:3:2:3 pull-down
		PULLDOWN_ADVANCED,	///< Advanced 2:3:3:2 pull-down (minimal dirty frames)
		PULLDOWN_NONE,		///< Do not apply pull-down techniques, just repeat or skip entire frames
	};

	/**
	 * @brief This struct holds a single field (half a frame).
	 *
	 * A frame of video is made up of 2 fields (half a frame).  This struct points to which original
	 * frame, and whether this is the ODD or EVEN lines (i.e. top or bottom).
	 */
	struct Field
	{
		int Frame;
		bool isOdd;

		Field() : Frame(0), isOdd(true) { };

		Field(int frame, bool isodd)
		{
			Frame = frame;
			isOdd = isodd;
		}
	};

	/**
	 * @brief This struct holds a the range of samples needed by this frame
	 *
	 * When frame rate is changed, the audio needs to be redistributed among the remaining
	 * frames.  This struct holds the range samples needed by the this frame.
	 */
	struct SampleRange
	{
		int frame_start;
		int sample_start;

		int frame_end;
		int sample_end;

		int total;
	};

	/**
	 * @brief This struct holds two fields which together make up a complete video frame.
	 *
	 * These fields can point at different original frame numbers, for example the odd lines from
	 * frame 3, and the even lines of frame 4, if required by a pull-down technique.
	 */
	struct MappedFrame
	{
		Field Odd;
		Field Even;
		SampleRange Samples;
	};


	/**
	 * @brief This class creates a mapping between 2 different frame rates, applying a specific pull-down technique.
	 *
	 * This class creates a mapping between 2 different video files, and supports many pull-down techniques,
	 * such as 2:3:2:3 or 2:3:3:2, and also supports inverse telecine. Pull-down techniques are only needed to remove
	 * artificial fields added when converting between 24 fps (film) and television fps (29.97 fps NTSC or 25 fps PAL).
	 *
	 * The <b>following graphic</b> displays a how frame rates are mapped, and how time remapping affects the order
	 * of frames returned from the FrameMapper.
	 * \image html /doc/images/FrameMapper.png
	 *
	 * Please see the following <b>Example Code</b>:
	 * \code
	 * // Create a frame mapper for a clip with 100 frames, and convert the frame rate (from 24 fps to 29.97 fps)
	 * FrameMapper mapping(100, Fraction(24, 1), Fraction(30000, 1001), PULLDOWN_CLASSIC);
	 * Frame frame2 = mapping.GetFrame(2);
	 * assert(frame2.Odd.Frame == 2);
	 * \endcode
	 */
	class FrameMapper : public ReaderBase {
	private:
		bool is_open;
		bool field_toggle;			// Internal odd / even toggle (used when building the mapping)
		Fraction original;		// The original frame rate
		Fraction target;			// The target frame rate
		PulldownType pulldown;	// The pull-down technique
		ReaderBase *reader;	// The source video reader
		Cache final_cache; // Cache of actual Frame objects

		// Internal methods used by init
		void AddField(int frame);
		void AddField(Field field);

		// Use the original and target frame rates and a pull-down technique to create
		// a mapping between the original fields and frames or a video to a new frame rate.
		// This might repeat or skip fields and frames of the original video, depending on
		// whether the frame rate is increasing or decreasing.
		void Init();

	public:
		// Init some containers
		vector<Field> fields;		// List of all fields
		vector<MappedFrame> frames;	// List of all frames

		/// Default constructor for FrameMapper class
		FrameMapper(ReaderBase *reader, Fraction target, PulldownType pulldown);

		/// Close the internal reader
		void Close();

		/// Get a frame based on the target frame rate and the new frame number of a frame
		MappedFrame GetMappedFrame(int TargetFrameNumber) throw(OutOfBoundsFrame);

		/// @brief This method is required for all derived classes of ReaderBase, and return the
		/// openshot::Frame object, which contains the image and audio information for that
		/// frame of video.
		///
		/// @returns The requested frame of video
		/// @param requested_frame The frame number that is requested.
		tr1::shared_ptr<Frame> GetFrame(int requested_frame) throw(ReaderClosed);

		/// Determine if reader is open or closed
		bool IsOpen();

		/// Get and Set JSON methods
		string Json(); ///< Generate JSON string of this object
		void SetJson(string value) throw(InvalidJSON); ///< Load JSON string into this object
		Json::Value JsonValue(); ///< Generate Json::JsonValue for this object
		void SetJsonValue(Json::Value root) throw(InvalidFile); ///< Load Json::JsonValue into this object

		/// Get the target framerate
		Fraction TargetFPS() { return target; };

		/// Get the source framerate
		Fraction SourceFPS() { return original; };

		/// Set the target framerate
		void TargetFPS(Fraction new_fps) { target = new_fps; };

		/// Set the source framerate
		void SourceFPS(Fraction new_fps) { original = new_fps; };

		/// Open the internal reader
		void Open() throw(InvalidFile);

		/// Print all of the original frames and which new frames they map to
		void PrintMapping();

	};
}

#endif
