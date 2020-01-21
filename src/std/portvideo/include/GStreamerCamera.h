#ifndef GSTREAMERCAMERA_H
#define GSTREAMERCAMERA_H

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include "CameraEngine.h"

class GStreamerCamera : public CameraEngine
{
public:
    GStreamerCamera(const char *cfg);
    ~GStreamerCamera();

    bool findCamera();
    bool initCamera();
    bool startCamera();
    unsigned char* getFrame();
    bool stopCamera();
    bool stillRunning();
    bool resetCamera();
    bool closeCamera();

    int getCameraSettingStep(int mode);
    bool setCameraSettingAuto(int mode, bool flag);
    bool setCameraSetting(int mode, int value);
    int getCameraSetting(int mode);
    int getMaxCameraSetting(int mode);
    int getMinCameraSetting(int mode);

private:
    static GstFlowReturn new_buffer_list (GstAppSink *videosink, gpointer user_data);
    static GstFlowReturn new_preroll (GstAppSink *videosink, gpointer user_data);
    static GstFlowReturn new_buffer(GstAppSink *videosink, gpointer user_data);
    static void print_buffer (GstBuffer *gstbuffer, const char *title);
    static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer user_data);

private:
    GstElement *pipeline, *videosink;
    static GstBuffer *gstbuffer;
    static unsigned char *cam_buffer;
    gchar *descr;
    GError *gsterror;
    gint64 duration, position;
    GstFormat format;
    GstStateChangeReturn ret;
    gboolean res;
};

#endif // GSTREAMERCAMERA_H
