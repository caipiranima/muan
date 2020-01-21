/*  portVideo, a cross platform camera framework
    Copyright (C) 2005-2009 Martin Kaltenbrunner <modin@yuri.at>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <pthread.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>

#include "DV1394Camera.h"
#include "raw1394util.h"

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <mpeg2dec/mpeg2.h>
#include <mpeg2dec/mpeg2convert.h>

#ifdef __cplusplus
}
#endif

#ifdef HAVE_LIBDV

#include <libdv/dv.h>
#include <libdv/dv_types.h>

#endif

using namespace std;


// Constants.
#define HdvW 1440
#define HdvH 1080


/** Constructor
 * @param cfg
 */
DV1394Camera::DV1394Camera (const char *cfg) : CameraEngine (cfg), hdv(false)
{
    reader = NULL;
    pixels = new unsigned char[dvW*dvH*3];
    memset(pixels, 0, sizeof (pixels));

}


/** Captures a new frame.
 * @return The frame captured.
 */
unsigned char* DV1394Camera::getFrame()
{
    if(reader->WaitForAction()) {
        Frame *f = reader->GetFrame();
        if(f->IsHDV()) {

            HDVFrame* frame = static_cast<HDVFrame*>(f);
            reader->DoneWithFrame(frame);

        } else {

            DVFrame *frame = static_cast<DVFrame*>(f);
            reader->DoneWithFrame(frame);
            frame->ExtractRGB(pixels);
        }
    }

    return pixels;
}


/** Open DV video
 * @return true if camera is opened
 */
bool DV1394Camera::dv_video_open(void)
{
    if (reader == NULL)  {
        AVC *avc;
        octlet_t guid=0;
        int node=-1;
        int port=-1;
        int channel;
        int buffers=100;

        node = discoverAVC(&port, &guid);

        if(node == -1) {
            std::cerr <<  std::string("no camera exists") << std::endl;
            return false;
        }

        if(port != -1) {
            iec61883Connection::CheckConsistency(port, node);
            avc = new AVC(port);
            if(! avc) {
                std::cerr << std::string("failed to initialize AV/C") << std::endl;
                return false;
            }
            if(avc->isHDV(node)) {
                hdv = true;
                std::cerr << "For while HDV is not supported!!" << std::endl;
                return false;
            }
        }

        iec61883Connection *connection = new iec61883Connection(port, node);
        if(! connection) {
            std::cerr <<  std::string("failed to estabilish isochonous connection") << std::endl;
            return false;
        }

        channel = connection->GetChannel();
        reader = new iec61883Reader(port, channel, buffers, 0, 0, hdv);

    }

    return reader->StartThread();
}

DV1394Camera::~DV1394Camera()
{
    closeCamera();
}

bool DV1394Camera::findCamera()
{
    readSettings();
    if (dv_video_open()) {
        return true;
    }

    return false;
}

bool DV1394Camera::initCamera()
{
    colour = true;

    if(dv_video_open())  {
        startCamera();
        if(reader->WaitForAction())
        {
            Frame *frame = reader->GetFrame();
            width = frame->GetWidth();
            height = frame->GetHeight();
            reader->DoneWithFrame(frame);
            if(frame->IsHDV()) {
                //FIXME: if its a hdv frame the width and height are 0!!
                // so we force it to hdv resolution.
                width = HdvW; height = HdvH;
            }
        }
        if(pixels != NULL)
            delete []pixels;
        pixels = new unsigned char[width*height*3];
        memset(pixels, 0, sizeof (pixels));

        return true;
    }

    return false;
}

bool DV1394Camera::startCamera()
{
    if(reader != NULL) {
        reader->StartThread();
    }
    return true;
}

bool DV1394Camera::stopCamera()
{
    if (reader != NULL)  {
        reader->StopThread();
    }
    return true;
}

bool DV1394Camera::stillRunning()
{
    if (reader != NULL)
        return true;
    return false;
}

bool DV1394Camera::resetCamera()
{
    return (stopCamera() && startCamera());
}

bool DV1394Camera::closeCamera()
{
    if(reader != NULL) {
        reader->StopThread();
        delete reader;
        reader = NULL;
    }
    return true;
}

bool DV1394Camera::setCameraSettingAuto(int mode, bool flag)
{
    return true;
}

bool DV1394Camera::setCameraSetting(int mode, int setting)
{
    return true;
}

int DV1394Camera::getCameraSetting(int mode)
{
    return 1;
}

int DV1394Camera::getMaxCameraSetting(int mode)
{
    return 1;
}

int DV1394Camera::getMinCameraSetting(int mode)
{
    return 1;
}

int DV1394Camera::getCameraSettingStep(int mode)
{
    return 1;
}
