/**
 * @file
 * @brief Header file for ImageReader class
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

#ifndef OPENSHOT_IMAGE_READER_H
#define OPENSHOT_IMAGE_READER_H

#include "ReaderBase.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <tr1/memory>
#include "Magick++.h"
#include "Cache.h"
#include "Exceptions.h"

using namespace std;

namespace openshot
{

	/**
	 * @brief This class uses the ImageMagick++ libraries, to open image files, and return
	 * openshot::Frame objects containing the image.
	 *
	 * @code
	 * // Create a reader for a video
	 * ImageReader r("MyAwesomeImage.jpeg");
	 * r.Open(); // Open the reader
	 *
	 * // Get frame number 1 from the video
	 * tr1::shared_ptr<Frame> f = r.GetFrame(1);
	 *
	 * // Now that we have an openshot::Frame object, lets have some fun!
	 * f->Display(); // Display the frame on the screen
	 *
	 * // Close the reader
	 * r.Close();
	 * @endcode
	 */
	class ImageReader : public ReaderBase
	{
	private:
		string path;
		tr1::shared_ptr<Magick::Image> image;
		bool is_open;

	public:

		/// Constructor for ImageReader.  This automatically opens the media file and loads
		/// frame 1, or it throws one of the following exceptions.
		ImageReader(string path) throw(InvalidFile);

		/// Close File
		void Close();

		/// Get an openshot::Frame object for a specific frame number of this reader.  All numbers
		/// return the same Frame, since they all share the same image data.
		///
		/// @returns The requested frame (containing the image)
		/// @param requested_frame The frame number that is requested.
		tr1::shared_ptr<Frame> GetFrame(int requested_frame) throw(ReaderClosed);

		/// Determine if reader is open or closed
		bool IsOpen() { return is_open; };

		/// Get and Set JSON methods
		string Json(); ///< Generate JSON string of this object
		void SetJson(string value) throw(InvalidJSON); ///< Load JSON string into this object
		Json::Value JsonValue(); ///< Generate Json::JsonValue for this object
		void SetJsonValue(Json::Value root) throw(InvalidFile); ///< Load Json::JsonValue into this object

		/// Open File - which is called by the constructor automatically
		void Open() throw(InvalidFile);
	};

}

#endif
