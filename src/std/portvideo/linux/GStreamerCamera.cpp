//#include <QtCore>
#include <gst/app/gstappbuffer.h>
#include "tinyxml.h"
#include "GStreamerCamera.h"

#define CAPS "video/x-raw-rgb,width=640,height=480,pixel-aspect-ratio=1/1,bpp=(int)24,depth=(int)24,endianness=(int)4321,red_mask=(int)0xff0000, green_mask=(int)0x00ff00, blue_mask=(int)0x0000ff"

GstBuffer * GStreamerCamera::gstbuffer = NULL;
unsigned char * GStreamerCamera::cam_buffer = NULL;

GStreamerCamera::GStreamerCamera(const char *cfg) : CameraEngine(cfg)
{
    buffer = NULL;
    gsterror = NULL;
    running = false;
    cameraID = -1;
//    fprintf(stderr,"USING GSTREAMER...\n");
}

GStreamerCamera::~GStreamerCamera()
{
    if(buffer) {
        delete [] buffer;
    }
    closeCamera();
}

bool GStreamerCamera::initCamera()
{
    gst_init(NULL, NULL);

    TiXml::TiXmlDocument xml_settings( config_file );
    xml_settings.LoadFile();

    if( ! xml_settings.Error() ) {
        TiXml::TiXmlHandle docHandle( &xml_settings );
        TiXml::TiXmlHandle camera = docHandle.FirstChild("muan").FirstChild("camera");
        TiXml::TiXmlElement* camera_element = camera.Element();

        if( camera_element!=NULL ) {
            if(camera_element->Attribute("pipeline")!=NULL) {
                std::string pipe = camera_element->Attribute("pipeline");
//                pipe.append("\""); pipe.append(CAPS); pipe.append("\"");
                descr = g_strdup_printf ( "%s", pipe.c_str() );

            } else {

                /* create a new pipeline */
                descr =
                        g_strdup_printf ("v4l2src ! ffmpegcolorspace ! videoscale ! appsink name=sink caps=\"" CAPS "\"");
//                            g_strdup_printf ("dv1394src ! queue !  dvdemux name=d ! queue ! dvdec ! videorate ! video/x-raw-yuv,framerate=30/1 ! ffvideoscale ! " CAPS " ! ffmpegcolorspace ! appsink name=sink");
//                            g_strdup_printf ("hdv1394src ! queue ! mpegtsdemux name=demux demux. ! queue ! mpeg2dec ! videorate ! video/x-raw-yuv,framerate=30/1 ! ffvideoscale ! " CAPS " ! ffmpegcolorspace ! appsink name=sink caps=\"" CAPS "\"");
//                            g_strdup_printf ("videotestsrc ! appsink name=sink caps=\"" CAPS "\"");
            }
        }

    } else {
        std::cerr << "(GST) Error on contruct pipeline from config file." << std::endl;
        return false;
    }

    pipeline = gst_parse_launch (descr, &gsterror);

    fprintf(stderr, "(GST) PIPELINE: %s\n", descr);

    if (gsterror != NULL) {
        g_print ("could not construct pipeline: %s\n", gsterror->message);
        g_error_free (gsterror);
        return false;
    }

    /* get sink */
    videosink = gst_bin_get_by_name (GST_BIN (pipeline), "sink");

    GstAppSinkCallbacks callbacks = { NULL, new_preroll, new_buffer,
                                      new_buffer_list, { NULL } };
    gst_app_sink_set_callbacks (GST_APP_SINK(videosink), &callbacks, NULL, NULL);

    GstBus* bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    gst_bus_add_watch (bus, bus_call, NULL);
    gst_object_unref (bus);

    cam_buffer = new unsigned char[width*height*3];
    memset(cam_buffer, 0, width*height*3);

    return true;
}

bool GStreamerCamera::closeCamera()
{
    /* cleanup and exit */
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);

    return true;
}

bool GStreamerCamera::startCamera()
{
    gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);
    running = true;
    return true;
}

bool GStreamerCamera::stopCamera()
{
    gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_READY);
    running = false;
    return true;
}


unsigned char * GStreamerCamera::getFrame()
{
    return cam_buffer;
}

bool GStreamerCamera::findCamera()
{
    readSettings();
    //FIXME: Workaround!
    // Estas informacoes devem vir do driver
    width = 640; height = 480; colour = true;
    return true;
}

bool GStreamerCamera::stillRunning()
{
    return running;
}

bool GStreamerCamera::resetCamera()
{
    return true;
}

int GStreamerCamera::getCameraSettingStep(int mode)
{
    return 0;
}

bool GStreamerCamera::setCameraSettingAuto(int mode, bool flag)
{
    return true;
}

bool GStreamerCamera::setCameraSetting(int mode, int value)
{
    return true;
}

int GStreamerCamera::getCameraSetting(int mode)
{
    return 0;
}

int GStreamerCamera::getMaxCameraSetting(int mode)
{
    return 0;
}

int GStreamerCamera::getMinCameraSetting(int mode)
{
    return 0;
}


GstFlowReturn GStreamerCamera::new_buffer_list (GstAppSink *sink, gpointer user_data)
{

//    GstBufferList *list = gst_app_sink_pull_buffer_list (sink);
//    GstBufferListIterator *it = gst_buffer_list_iterate (list);
//    GstBuffer *buffer;
//    while (gst_buffer_list_iterator_next_group (it))
//        while ((buffer = gst_buffer_list_iterator_next (it)) != NULL)
//            print_buffer(buffer, "new_buffer_list");
//    gst_buffer_list_iterator_free (it);

    return GST_FLOW_OK;
}

GstFlowReturn GStreamerCamera::new_preroll (GstAppSink *sink, gpointer user_data)
{

//    gstbuffer =  gst_app_sink_pull_preroll (sink);
//    GstBuffer *buffer =  gst_app_sink_pull_preroll (sink);
//    if (buffer)
//        print_buffer(buffer, "preroll");

//    gst_buffer_unref(buffer);

    return GST_FLOW_OK;
}

GstFlowReturn GStreamerCamera::new_buffer(GstAppSink *sink, gpointer user_data)
{

    GstBuffer *buffer =  gst_app_sink_pull_buffer (sink);
//    if (buffer)
//        print_buffer(buffer, "buffer");

    memcpy(cam_buffer, buffer->data, buffer->size);
    gst_buffer_unref(buffer);

    return GST_FLOW_OK;
}

void GStreamerCamera::print_buffer(GstBuffer *buffer, const char *title)
{
//    GstCaps *caps = gst_buffer_get_caps(buffer);
//    for (uint j = 0; j < gst_caps_get_size(caps); ++j) {
//        GstStructure *structure = gst_caps_get_structure(caps, j);
//        QString serialized = QString("%1{%2}: ").arg(title)
//                                                .arg(gst_structure_get_name(structure));
//        for (int i = 0; i < gst_structure_n_fields(structure); ++i) {
//            if (i != 0)
//                serialized.append(", ");
//            const char *name = gst_structure_nth_field_name(structure, i);
//            GType type = gst_structure_get_field_type(structure, name);
//            serialized.append(QString("%1[%2]").arg(name).arg(g_type_name(type)));
//        }
//        qCritical() << serialized;
//    }
}

gboolean GStreamerCamera::bus_call(GstBus *bus, GstMessage *msg, gpointer user_data)
{
    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_STATE_CHANGED: {
//        GstState old_state, new_state;

//        gst_message_parse_state_changed (msg, &old_state, &new_state, NULL);
//        qCritical ("[%s]: %s -> %s", GST_OBJECT_NAME (msg->src),
//                                    gst_element_state_get_name (old_state),
//                                    gst_element_state_get_name (new_state));
        break;
    }
    case GST_MESSAGE_ERROR: {
        gchar *debug;
        GError *err;

        gst_message_parse_error (msg, &err, &debug);
//        qCritical ("[%s]: %s %s", GST_OBJECT_NAME (msg->src), err->message, debug);
        g_free (debug);
        g_error_free (err);

        break;
    }
    default: {
//        const GstStructure *structure = msg->structure;
//        if (structure) {
//                QString serialized = QString("%1{%2}: ")
//                        .arg(gst_message_type_get_name (msg->type))
//                        .arg(gst_structure_get_name(structure));
//            for (int i = 0; i < gst_structure_n_fields(structure); ++i) {
//                if (i != 0)
//                    serialized.append(", ");
//                const char *name = gst_structure_nth_field_name(structure, i);
//                GType type = gst_structure_get_field_type(structure, name);
//                serialized.append(name);
//                serialized.append(QString("[%1]").arg(g_type_name(type)));
//            }
//            qCritical () << serialized;
//        } else {
//            qCritical ("%s{}", gst_message_type_get_name (msg->type));
//        }
        break;
    }
    }
    return true;
}
