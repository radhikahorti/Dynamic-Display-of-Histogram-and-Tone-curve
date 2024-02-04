

/*
 * Copyright (c) 2016 - 2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ArgusHelpers.h"
#include <gst/gst.h>
#include "CommonOptions.h"
#include "Error.h"
#include "EGLGlobal.h"
#include "GLContext.h"
#include "Window.h"
#include "Thread.h"
#include "Argus/Settings.h"
#include <Argus/Argus.h>
#include <EGLStream/EGLStream.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <queue>
#include<math.h>
std ::vector<float> RED, GREEN, BLUE;
std::vector<float> curve(129);
	 float expo[129];
  		 float a = 4.5;
		float b = 0.5;
	         float c = 0;
		int i=0;

float linear[129] = {
    0.000000,
    0.007813,
    0.015625,
    0.023438,
    0.031250,
    0.039063,
    0.046875,
    0.054688,
    0.062500,
    0.070313,
    0.078125,
    0.085938,
    0.093750,
    0.101563,
    0.109375,
    0.117188,
    0.125000,
    0.132813,
    0.140625,
    0.148438,
    0.156250,
    0.164063,
    0.171875,
    0.179688,
    0.187500,
    0.195313,
    0.203125,
    0.210938,
    0.218750,
    0.226563,
    0.234375,
    0.242188,
    0.250000,
    0.257813,
    0.265625,
    0.273438,
    0.281250,
    0.289063,
    0.296875,
    0.304688,
    0.312500,
    0.320313,
    0.328125,
    0.335938,
    0.343750,
    0.351563,
    0.359375,
    0.367188,
    0.375000,
    0.382813,
    0.390625,
    0.398438,
    0.406250,
    0.414063,
    0.421875,
    0.429688,
    0.437500,
    0.445313,
    0.453125,
    0.460938,
    0.468750,
    0.476563,
    0.484375,
    0.492188,
    0.500000,
    0.507813,
    0.515625,
    0.523438,
    0.531250,
    0.539063,
    0.546875,
    0.554688,
    0.562500,
    0.570313,
    0.578125,
    0.585938,
    0.593750,
    0.601563,
    0.609375,
    0.617188,
    0.625000,
    0.632813,
    0.640625,
    0.648438,
    0.656250,
    0.664063,
    0.671875,
    0.679688,
    0.687500,
    0.695313,
    0.703125,
    0.710938,
    0.718750,
    0.726563,
    0.734375,
    0.742188,
    0.750000,
    0.757813,
    0.765625,
    0.773438,
    0.781250,
    0.789063,
    0.796875,
    0.804688,
    0.812500,
    0.820313,
    0.828125,
    0.835938,
    0.843750,
    0.851563,
    0.859375,
    0.867188,
    0.875000,
    0.882813,
    0.890625,
    0.898438,
    0.906250,
    0.914063,
    0.921875,
    0.929688,
    0.937500,
    0.945313,
    0.953125,
    0.960938,
    0.968750,
    0.976563,
    0.984375,
    0.992188,
    1.000000};
float polynomial[129] = {
    0.000000,
    0.022725,
    0.045091,
    0.067099,
    0.088753,
    0.110057,
    0.131012,
    0.151623,
    0.171891,
    0.191820,
    0.211413,
    0.230673,
    0.249603,
    0.268205,
    0.286484,
    0.304441,
    0.322080,
    0.339404,
    0.356415,
    0.373117,
    0.389513,
    0.405606,
    0.421398,
    0.436892,
    0.452093,
    0.467001,
    0.481622,
    0.495957,
    0.510009,
    0.523782,
    0.537278,
    0.550501,
    0.563453,
    0.576138,
    0.588558,
    0.600716,
    0.612616,
    0.624259,
    0.635651,
    0.646792,
    0.657687,
    0.668338,
    0.678748,
    0.688920,
    0.698858,
    0.708563,
    0.718040,
    0.727291,
    0.736318,
    0.745126,
    0.753717,
    0.762094,
    0.770260,
    0.778218,
    0.785971,
    0.793521,
    0.800873,
    0.808028,
    0.814991,
    0.821763,
    0.828348,
    0.834748,
    0.840968,
    0.847009,
    0.852875,
    0.858569,
    0.864093,
    0.869451,
    0.874646,
    0.879680,
    0.884557,
    0.889279,
    0.893850,
    0.898272,
    0.902549,
    0.906684,
    0.910679,
    0.914537,
    0.918262,
    0.921856,
    0.925322,
    0.928664,
    0.931884,
    0.934986,
    0.937972,
    0.940845,
    0.943608,
    0.946264,
    0.948817,
    0.951269,
    0.953623,
    0.955882,
    0.958050,
    0.960128,
    0.962120,
    0.964030,
    0.965859,
    0.967612,
    0.969290,
    0.970898,
    0.972437,
    0.973912,
    0.975324,
    0.976677,
    0.977974,
    0.979218,
    0.980411,
    0.981558,
    0.982660,
    0.983721,
    0.984743,
    0.985731,
    0.986686,
    0.987611,
    0.988510,
    0.989386,
    0.990242,
    0.991080,
    0.991904,
    0.992716,
    0.993519,
    0.994317,
    0.995113,
    0.995909,
    0.996708,
    0.997514,
    0.998330,
    0.999157,
    1.000000};
float sigmoid[129] = {

    0.000000,
    0.003937,
    0.007935,
    0.011993,
    0.016113,
    0.020294,
    0.024536,
    0.028839,
    0.033203,
    0.037628,
    0.042114,
    0.046661,
    0.051270,
    0.055939,
    0.060669,
    0.065460,
    0.070313,
    0.075226,
    0.080200,
    0.085236,
    0.090332,
    0.095490,
    0.100708,
    0.105988,
    0.111328,
    0.116730,
    0.122192,
    0.127716,
    0.133301,
    0.138947,
    0.144653,
    0.150421,
    0.156250,
    0.162140,
    0.168091,
    0.174103,
    0.180176,
    0.186310,
    0.192505,
    0.198761,
    0.205078,
    0.211456,
    0.217896,
    0.224396,
    0.230957,
    0.237579,
    0.244263,
    0.251007,
    0.257813,
    0.264679,
    0.271606,
    0.278595,
    0.285645,
    0.292755,
    0.299927,
    0.307159,
    0.314453,
    0.321808,
    0.329224,
    0.336700,
    0.344238,
    0.351837,
    0.359497,
    0.367218,
    0.375000,
    0.382843,
    0.390747,
    0.398712,
    0.406738,
    0.414825,
    0.422974,
    0.431183,
    0.439453,
    0.447784,
    0.456177,
    0.464630,
    0.473145,
    0.481720,
    0.490356,
    0.499054,
    0.507813,
    0.516632,
    0.525513,
    0.534454,
    0.543457,
    0.552521,
    0.561646,
    0.570831,
    0.580078,
    0.589386,
    0.598755,
    0.608185,
    0.617676,
    0.627228,
    0.636841,
    0.646515,
    0.656250,
    0.666046,
    0.675903,
    0.685822,
    0.695801,
    0.705841,
    0.715942,
    0.726105,
    0.736328,
    0.746613,
    0.756958,
    0.767365,
    0.777832,
    0.788361,
    0.798950,
    0.809601,
    0.820313,
    0.831085,
    0.841919,
    0.852814,
    0.863770,
    0.874786,
    0.885864,
    0.897003,
    0.908203,
    0.919464,
    0.930786,
    0.942169,
    0.953613,
    0.965118,
    0.976685,
    0.988312,
    1.000000};
    
float Expo_increase[129] = {
0,
0.03306145196420088,
0.033968322509409746,
0.03490006837427058,
0.03585737188497761,
0.03684093408382773,
0.03785147524260023,
0.03888973539001861,
0.0399564748536805,
0.04105247481685263,
0.042178537890538714,
0.04333548870123885,
0.044524174494831315,
0.04574546575701858,
0.04700025685079212,
0.0482894666713828,
0.0496140393191764,
0.05097494479108716,
0.052373179690895576,
0.05380976795907065,
0.05528576162261102,
0.05680224156545424,
0.058360318320018055,
0.05996113288045373,
0.061605857538206764,
0.06329569674049675,
0.06503188797234535,
0.06681570266279821,
0.0686484471160042,
0.07053146346783423,
0.07246613066873979,
0.07445386549357133,
0.07649612357909563,
0.07859440048997227,
0.08075023281396948,
0.08296519928722182,
0.08524092195035332,
0.08757906733631299,
0.08998134769079244,
0.09244952222611948,
0.0949853984095455,
0.09759083328687086,
0.10026773484237675,
0.10301806339605986,
0.10584383303919312,
0.10874711310926337,
0.11173002970536669,
0.1147947672451706,
0.11794357006458328,
0.12117874406130207,
0.1245026583834435,
0.12791774716449292,
0.13142651130584296,
0.1350315203082269,
0.13873541415338833,
0.14254090523736418,
0.14645078035679765,
0.15046790274973562,
0.15459521419240432,
0.15883573715349975,
0.16319257700756964,
0.16766892430910812,
0.17226805712902873,
0.1769933434552263,
0.1818482436589857,
0.1868363130290445,
0.19196120437516354,
0.19722667070311414,
0.2026365679630389,
0.20819485787320002,
0.21390561082118287,
0.2197730088446783,
0.22580134869402838,
0.23199504497877665,
0.2383586334005274,
0.2448967740744832,
0.25161425494208994,
0.2585159952772917,
0.2656070492889601,
0.27289260982213975,
0.28037801216081637,
0.2880687379349954,
0.2959704191349504,
0.3040888422355826,
0.3124299524339102,
0.32099985800279196,
0.3298048347640719,
0.3388513306844226,
0.34814597059725144,
0.3576955610541276,
0.3675070953092834,
0.3775877584408403,
0.3879449326125075,
0.39858620247961063,
0.40951936074340417,
0.4207524138577408,
0.4322935878922714,
0.4441513345564729,
0.4563343373889142,
0.46885151811629167,
0.48171204318689415,
0.49492533048327786,
0.5085010562190698,
0.5224491620249494,
0.536779862228997,
0.5515036513367424,
0.566631311716389,
0.5821739214948425,
0.5981428626703265,
0.6145498294475266,
0.6314068368013643,
0.648726229275678,
0.6665206900232443,
0.6848032500937722,
0.7035872979766603,
0.722886589405513,
0.7427152574315937,
0.7630878227735894,
0.7840192044512682,
0.8055247307108176,
0.8276201502498609,
0.8503216437503772,
0.8736458357279645,
0.8976098067061287,
0.9222311057245091,
0.9475277631902058,
0.9735183040816124,
1,
1
};
float s[129]={1,
1.34,
1.78,
2.37,
3.16,
4.19,
5.55,
7.32,
9.62,
12.55,
16.27,
20.88,
26.48,
33.13,
40.78,
49.27,
58.36,
67.67,
76.83,
85.48,
93.32,
100.19,
106.02,
110.83,
114.73,
117.82,
120.24,
122.11,
123.55,
124.65,
125.48,
126.11,
126.58,
126.94,
127.2,
127.4,
127.55,
127.67,
127.75,
127.81,
127.86,
127.9,
127.92,
127.94,
127.96,
127.97,
127.98,
127.98,
127.99,
127.99,
127.99,
127.99,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,128};
float s1[129]={
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1.34,
1.78,
2.37,
3.16,
4.19,
5.55,
7.32,
9.62,
12.55,
16.27,
20.88,
26.48,
33.13,
40.78,
49.27,
58.36,
67.67,
76.83,
85.48,
93.32,
100.19,
106.02,
110.83,
114.73,
117.82,
120.24,
122.11,
123.55,
124.65,
125.48,
126.11,
126.58,
126.94,
127.2,
127.4,
127.55,
127.67,
127.75,
127.81,
127.86,
127.9,
127.92,
127.94,
127.96,
127.97,
127.98,
127.98,
127.99,
127.99,
127.99,
127.99,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128,
128};
using namespace Argus;
void clear()
{
    std::ofstream file("a.text");
    file << "";
}
namespace ArgusSamples
{

    // Constants.
    static const uint32_t DEFAULT_CAPTURE_TIME = 10; // In seconds.
    static const uint32_t DEFAULT_CAMERA_INDEX = 0;
    static const Rectangle<uint32_t> DEFAULT_WINDOW_RECT(0, 0, 1024, 768);
    static const Size2D<uint32_t> STREAM_SIZE(640, 480);

    // Due to clipping and differences in color correction algorithms, the
    // upper-most bins may negatively affect the graph scaling. This constant
    // specifies how many of the upper-most bins are excluded from the graphs.
    static const uint32_t CLIP_BINS = 10;

    // Globals.
    UniqueObj<CameraProvider> g_cameraProvider;
    EGLDisplayHolder g_display;

// Debug print macros.
#define PRODUCER_PRINT(...) printf("PRODUCER: " __VA_ARGS__)
#define CONSUMER_PRINT(...) printf("CONSUMER: " __VA_ARGS__)

    /*******************************************************************************
     * Extended options class to add additional options specific to this sample.
     ******************************************************************************/
    class HistogramSampleOptions : public CommonOptions
    {
    public:
        HistogramSampleOptions(const char *programName)
            : CommonOptions(programName,
                            ArgusSamples::CommonOptions::Option_D_CameraDevice |
                                ArgusSamples::CommonOptions::Option_M_SensorMode |
                                ArgusSamples::CommonOptions::Option_R_WindowRect |
                                ArgusSamples::CommonOptions::Option_T_CaptureTime)

              ,
              m_path("./"), m_filename("argus_histo"), m_Tone_curves(0)
        {
           addOption(createValueOption("Tonecurves", 'c', "0 or 1 or 2 or 3 or 4 or 5 or 6", "\n0.Default capture \n1.Linear  \n2.Reinhard \n3.Non-Linear \n4.exponential_increase \n5.S-shape \n6.Delayed_S-shape", m_Tone_curves));
            addOption(createValueOption
            ("path", 0, "PATH", "Output path (directory) for the output file(s). This path must be "
             "writable by the application, and files will be written to this location regardless"
             "of whether or not files are being sent to a remote server. See --keeplocal.",
             m_path));
        addOption(createValueOption
            ("file", 0, "FILE", "Filename for the output file(s). This will be prefixed to "
             "the part number and file type suffix (i.e. '.mkv') that will be appended by the app.",
             m_filename));
        }

        uint32_t Tone_curves() const { return m_Tone_curves; }
        const std::string &path() const { return m_path.get(); }
        const std::string &filename() const { return m_filename.get(); }

    protected:
        Value<uint32_t> m_Tone_curves;
        Value<std::string> m_path;
        Value<std::string> m_filename;
    };

    /*******************************************************************************
     * Histogram Consumer thread:
     *   Opens an on-screen GL window, and renders a live camera preview with
     *   histogram overlays.
     ******************************************************************************/
    class ConsumerThread : public Thread
    {
    public:
        explicit ConsumerThread(const HistogramSampleOptions &options, EGLStreamKHR stream, IRequest *request)
            : m_options(options), m_stream(stream), m_streamTexture(0), m_textureProgram(0), m_histogramProgram(0), m_histogramTexture(0), m_colorMaskLoc(0), m_binMaxLoc(0), m_request(request)

        //,m_outputStream(outputStream)
        {
            uint32_t yDiv = HISTOGRAM_COUNT + 1;
            m_histogramSpacing = options.windowRect().height() / (yDiv * yDiv);
            m_histogramSize = Size2D<uint32_t>(
                options.windowRect().width() / 2 - (m_histogramSpacing * 2),
                options.windowRect().height() / yDiv);
        }
        ~ConsumerThread()
        {
            //shutdown();
        }

        enum HistogramType
        {
            HISTOGRAM_R,
            HISTOGRAM_G,
            HISTOGRAM_B,
            HISTOGRAM_RGB,
            // HISTOGRAM_COMBINED,
            Tonecurve_RGB,
            HISTOGRAM_COUNT
        };

    private:
        /** @name Thread methods */
        /**@{*/
        virtual bool threadInitialize();
        virtual bool threadExecute();
        virtual bool threadShutdown();
        /**@}*/

        /**
         * Renders a single histogram to the display.
         * @param[in] type The HistogramType being rendered.
         * @param[in] label The label/title for the histogram.
         * @param[in] max The maximum value containined in the histogram.
         * @param[in] colorMask The color mask to use for the shader.
         */
        void renderHistogram(HistogramType type, const char *label,
                             uint32_t max, RGBTuple<float> colorMask);
         void renderTonecurve(HistogramType type, const char *label,
                             uint32_t max, RGBTuple<float> colorMask);
        

        const HistogramSampleOptions &m_options;
        EGLStreamKHR m_stream;
        GLContext m_context;
        GLuint m_streamTexture;
        GLuint m_textureProgram;
        GLuint m_histogramProgram;
        GLuint m_histogramTexture;
        GLuint m_colorMaskLoc;
        GLuint m_binMaxLoc;
        Size2D<uint32_t> m_histogramSize;
        uint32_t m_histogramSpacing;
        IRequest *m_request;
    };
    class GstVideoEncoder
    {
    public:
        GstVideoEncoder(const HistogramSampleOptions &options)
            :m_options(options), m_state(GST_STATE_NULL), m_pipeline(NULL), m_videoEncoder(NULL),m_totalBytesWritten(0)
        {
        }

        ~GstVideoEncoder()
        {
            shutdown();
        }
        const HistogramSampleOptions &m_options;
        bool initialize(EGLStreamKHR eglStream, Argus::Size2D<uint32_t> resolution, int32_t framerate)
        {
            // Initialize GStreamer.
            gst_init(NULL, NULL);
            m_pipeline = gst_pipeline_new("video_pipeline");
            if (!m_pipeline)
                ORIGINATE_ERROR("Failed to create video pipeline");

            // Create EGLStream video source.
            GstElement *videoSource = gst_element_factory_make("nveglstreamsrc", NULL);
            if (!videoSource)
                ORIGINATE_ERROR("Failed to create EGLStream video source");
            if (!gst_bin_add(GST_BIN(m_pipeline), videoSource))
            {
                gst_object_unref(videoSource);
                ORIGINATE_ERROR("Failed to add video source to pipeline");
            }
            g_object_set(G_OBJECT(videoSource), "display", g_display.get(), NULL);
            g_object_set(G_OBJECT(videoSource), "eglstream", eglStream, NULL);

            // Create queue.
            GstElement *queue = gst_element_factory_make("queue", NULL);
            if (!queue)
                ORIGINATE_ERROR("Failed to create queue");
            if (!gst_bin_add(GST_BIN(m_pipeline), queue))
            {
                gst_object_unref(queue);
                ORIGINATE_ERROR("Failed to add queue to pipeline");
            }

            // Create encoder.
            const char *encoder = "nvv4l2h264enc";
             m_videoEncoder = gst_element_factory_make(encoder, NULL);
            if (!m_videoEncoder)
                ORIGINATE_ERROR("Failed to create video encoder");
            if (!gst_bin_add(GST_BIN(m_pipeline), m_videoEncoder))
            {
                gst_object_unref(m_videoEncoder);
                ORIGINATE_ERROR("Failed to add video encoder to pipeline");
            }
            g_object_set(G_OBJECT(m_videoEncoder), "bitrate", 14000000, NULL);
            // If the video stream is going to be divided into parts then it will be output as a raw
        // video stream via the writeFileParts() callback, otherwise it is muxed to a container
        // format for file output (i.e. MKV or MP4).
        GstElement *encoderQueue = NULL;
        GstElement *fakeSink = NULL;
        GstElement *fileSink = NULL;
        GstElement *videoMuxer = NULL;
        GstElement *videoParse = NULL;
            videoParse = gst_element_factory_make("h264parse", NULL);
            if (!videoParse)
                ORIGINATE_ERROR("Failed to create video parser");
            if (!gst_bin_add(GST_BIN(m_pipeline), videoParse))
            {
                gst_object_unref(videoParse);
                ORIGINATE_ERROR("Failed to add video parser to pipeline");
            }
            // Create muxer.
            const char *muxer = "qtmux";
            const char *suffix = ".mp4";
             videoMuxer = gst_element_factory_make(muxer, NULL);
            if (!videoMuxer)
                ORIGINATE_ERROR("Failed to create video muxer");
            if (!gst_bin_add(GST_BIN(m_pipeline), videoMuxer))
            {
                gst_object_unref(videoMuxer);
                ORIGINATE_ERROR("Failed to add video muxer to pipeline");
            }
            // Create file sink as the final destination for the output file.
            fileSink = gst_element_factory_make("filesink", NULL);
            if (!fileSink)
                ORIGINATE_ERROR("Failed to create file sink");
            if (!gst_bin_add(GST_BIN(m_pipeline), fileSink))
            {
                gst_object_unref(fileSink);
                ORIGINATE_ERROR("Failed to add file sink to pipeline");
            }
            m_currentPartName = m_options.path() + m_options.filename() + suffix;
            printf("Writing output to %s\n", m_currentPartName.c_str());
            g_object_set(G_OBJECT(fileSink), "location", m_currentPartName.c_str(), NULL);
            // Create caps filter to describe EGLStream image format.
            GstCaps *caps = gst_caps_new_simple("video/x-raw",
                                                "format", G_TYPE_STRING, "NV12",
                                                "width", G_TYPE_INT, resolution.width(),
                                                "height", G_TYPE_INT, resolution.height(),
                                                "framerate", GST_TYPE_FRACTION, framerate, 1,
                                                NULL);
            if (!caps)
                ORIGINATE_ERROR("Failed to create caps");
            GstCapsFeatures *features = gst_caps_features_new("memory:NVMM", NULL);
            if (!features)
            {
                gst_caps_unref(caps);
                ORIGINATE_ERROR("Failed to create caps feature");
            }
            gst_caps_set_features(caps, 0, features);

            // Link EGLStream source to queue via caps filter.
            if (!gst_element_link_filtered(videoSource, queue, caps))
            {
                gst_caps_unref(caps);
                ORIGINATE_ERROR("Failed to link EGLStream source to queue");
            }
            gst_caps_unref(caps);

            // Link queue to encoder
            if (!gst_element_link(queue, m_videoEncoder))
                ORIGINATE_ERROR("Failed to link queue to encoder");

            if (!gst_element_link(m_videoEncoder, videoParse))
                ORIGINATE_ERROR("Failed to link encoder to parser");

            if (!gst_element_link(videoParse, videoMuxer))
                ORIGINATE_ERROR("Failed to link parser to muxer");

            // Link muxer to sink.
            if (!gst_element_link(videoMuxer, fileSink))
                ORIGINATE_ERROR("Failed to link muxer to sink");

            return true;
        }
        /**
         * Shutdown the GStreamer pipeline.
         */
        void shutdown()
        {
            if (m_state == GST_STATE_PLAYING)
                stopRecording();

            if (m_pipeline)
                gst_object_unref(GST_OBJECT(m_pipeline));
            m_pipeline = NULL;
        }

        /**
         * Start recording video.
         */
        bool startRecording()
        {
            if (!m_pipeline || !m_videoEncoder)
                ORIGINATE_ERROR("Video encoder not initialized");

            if (m_state != GST_STATE_NULL)
                ORIGINATE_ERROR("Video encoder already recording");

            // Start the pipeline.
            if (gst_element_set_state(m_pipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
                ORIGINATE_ERROR("Failed to start recording.");

            // time(&m_startTime);
            // m_lastPrintTime = 0;
            m_state = GST_STATE_PLAYING;
            return true;
        }

        /**
         * Stop recording video.
         */
        bool stopRecording()
        {
            if (!m_pipeline || !m_videoEncoder)
                ORIGINATE_ERROR("Video encoder not initialized");

            if (m_state != GST_STATE_PLAYING)
                ORIGINATE_ERROR("Video encoder not recording");

            // Send the end-of-stream event.
            GstPad *pad = gst_element_get_static_pad(m_videoEncoder, "sink");
            if (!pad)
                ORIGINATE_ERROR("Failed to get 'sink' pad");
            bool result = gst_pad_send_event(pad, gst_event_new_eos());
            gst_object_unref(pad);
            if (!result)
                ORIGINATE_ERROR("Failed to send end of stream event to encoder");

            // Wait for the event to complete.
            GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(m_pipeline));
            if (!bus)
                ORIGINATE_ERROR("Failed to get bus");
            result = gst_bus_poll(bus, GST_MESSAGE_EOS, GST_CLOCK_TIME_NONE);
            gst_object_unref(bus);
            if (!result)
                ORIGINATE_ERROR("Failed to wait for the EOF event");

            // Stop the pipeline.
            if (gst_element_set_state(m_pipeline, GST_STATE_NULL) == GST_STATE_CHANGE_FAILURE)
                ORIGINATE_ERROR("Failed to stop recording.");

            m_state = GST_STATE_NULL;
            return true;
        }
        
    protected:
        // const GstVideoEncodeSampleOptions& m_options;

        GstState m_state;
        GstElement *m_pipeline;
        GstElement *m_videoEncoder;
        uint32_t m_currentPartNumber;
        std::string m_currentPartName;
        FILE *m_currentPartFile;
        uint64_t m_totalBytesWritten;
    };
    bool ConsumerThread::threadInitialize()
    {

        Window &window = Window::getInstance();

        // Create the context and make it current.
        CONSUMER_PRINT("Creating context.\n");
        PROPAGATE_ERROR(m_context.initialize(&window));
        PROPAGATE_ERROR(m_context.makeCurrent());

        // Create the shader program to render the texture.
        {
            static const char vtxSrc[] =
                "#version 300 es\n"
                "in layout(location = 0) vec2 coord;\n"
                "out vec2 texCoord;\n"
                "void main() {\n"
                "  gl_Position = vec4((coord * 2.0) - 1.0, 0.0, 1.0);\n"
                "  texCoord = vec2(coord.x, 1.0 - coord.y);\n"
                "}\n";
            static const char frgSrc[] =
                "#version 300 es\n"
                "#extension GL_OES_EGL_image_external : require\n"
                "precision highp float;\n"
                "uniform samplerExternalOES texSampler;\n"
                "in vec2 texCoord;\n"
                "out vec4 fragColor;\n"
                "void main() {\n"
                "  fragColor = texture2D(texSampler, texCoord);\n"
                "}\n";
            PROPAGATE_ERROR(m_context.createProgram(vtxSrc, frgSrc, &m_textureProgram));
            glUseProgram(m_textureProgram);
            glUniform1i(glGetUniformLocation(m_textureProgram, "texSampler"), 0);
        }

        // Create the shader program to render the histograms.
        {
            static const char vtxSrc[] =
                "#version 300 es\n"
                "in layout(location = 0) vec2 coord;\n"
                "out vec2 binCoord;\n"
                "void main() {\n"
                "  gl_Position = vec4((coord * 2.0) - 1.0, 0.0, 1.0);\n"
                "  binCoord = coord;\n"
                "}\n";
            static const char frgSrc[] =
                "#version 300 es\n"
                "precision highp float;\n"
                "uniform usampler2D histogramSampler;\n"
                "uniform float binMax;\n"
                "uniform vec4 colorMask;\n"
                "uniform bool combined;\n"
                "in vec2 binCoord;\n"
                "out vec4 fragColor;\n"
                "void main() {\n"

                "    uvec3 rgbCounts = texture2D(histogramSampler, binCoord).rgb;\n"
                "    vec3 binValues = vec3(rgbCounts) / binMax;\n"
                "    fragColor = colorMask * vec4(step(binCoord.y, binValues), 1.0);\n"
                "  \n"
                "}\n";
            PROPAGATE_ERROR(m_context.createProgram(vtxSrc, frgSrc, &m_histogramProgram));
            glUseProgram(m_textureProgram);
            glUniform1i(glGetUniformLocation(m_histogramProgram, "histogramSampler"), 0);
            m_binMaxLoc = glGetUniformLocation(m_histogramProgram, "binMax");
            m_colorMaskLoc = glGetUniformLocation(m_histogramProgram, "colorMask");
            //  m_combinedLoc = glGetUniformLocation(m_histogramProgram, "combined");
        }

        // Initialize the vertex attrib state (used for both shader programs).
        static const GLfloat quadCoords[] = {1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, quadCoords);
        glEnableVertexAttribArray(0);

        // Enable alpha blending.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set text parameters.
        m_context.setTextSize(16.0f / m_histogramSize.height(),
                              (float)m_histogramSize.height() / (float)m_histogramSize.width());
        m_context.setTextColor(1.0f, 1.0f, 1.0f);
        m_context.setTextBackground(0.0f, 0.0f, 0.0f, 0.5f);

        // Create a 1D integer texture to store the histogram values.
        glGenTextures(1, &m_histogramTexture);
        glBindTexture(GL_TEXTURE_2D, m_histogramTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, 1, 1, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Create an external texture and connect it to the stream as the consumer.
        CONSUMER_PRINT("Connecting to stream.\n");
        glGenTextures(1, &m_streamTexture);
        glBindTexture(GL_TEXTURE_EXTERNAL_OES, m_streamTexture);
        if (!eglStreamConsumerGLTextureExternalKHR(g_display.get(), m_stream))
            ORIGINATE_ERROR("Unable to connect GL as consumer");
        CONSUMER_PRINT("Connected to stream.\n");

        // Set the acquire timeout to infinite.
        eglStreamAttribKHR(g_display.get(), m_stream, EGL_CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR, -1);

        return true;
    }

    bool ConsumerThread::threadExecute()
    {
        // Wait until the Argus producer is connected.
        CONSUMER_PRINT("Waiting until producer is connected...\n");
        while (true)
        {
            EGLint state = EGL_STREAM_STATE_CONNECTING_KHR;
            if (!eglQueryStreamKHR(g_display.get(), m_stream, EGL_STREAM_STATE_KHR, &state))
                ORIGINATE_ERROR("Failed to query stream state (possible producer failure).");
            if (state != EGL_STREAM_STATE_CONNECTING_KHR)
                break;
            usleep(1000);
        }
        CONSUMER_PRINT("Producer is connected; continuing.\n");

        // Render until there are no more frames (the producer has disconnected).
        uint32_t frame = 0;
        while (eglStreamConsumerAcquireKHR(g_display.get(), m_stream))
        {
            frame++;
            CONSUMER_PRINT("Acquired frame %d. Rendering.\n", frame);

            // Render the image.
            glViewport(0, 0, m_options.windowRect().width(), m_options.windowRect().height());
            glUseProgram(m_textureProgram);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            // Get the metadata from the current EGLStream frame.
            // Note: This will likely fail for the last frame since the producer has
            //       already disconected from the EGLStream, so we need to handle
            //       failure gracefully.
            UniqueObj<EGLStream::MetadataContainer> metadataContainer(
                EGLStream::MetadataContainer::create(g_display.get(), m_stream));
            EGLStream::IArgusCaptureMetadata *iArgusCaptureMetadata =
                interface_cast<EGLStream::IArgusCaptureMetadata>(metadataContainer);
            if (iArgusCaptureMetadata)
            {
                CaptureMetadata *metadata = iArgusCaptureMetadata->getMetadata();
                const ICaptureMetadata *iMetadata = interface_cast<const ICaptureMetadata>(metadata);
                if (!iMetadata)
                    ORIGINATE_ERROR("Failed to get Argus metadata\n");
                // IRequest *iRequest = interface_cast<IRequest>(iRequest->getAutoControlSettings());

                //  uint32_t curve_size = iCaptureMetadata->getToneMapCurveSize(RGB_CHANNEL_R);
                // std::cout << curve_size << std::endl;

                std::vector<Tuple<4, uint32_t>> rgbaData;
                std::vector<Tuple<4, uint32_t>> rgbaData1;

                // Read the Bayer histogram.
                std::vector<BayerTuple<uint32_t>> histogram;
                const IBayerHistogram *bayerHistogram =
                    interface_cast<const IBayerHistogram>(iMetadata->getBayerHistogram());
                if (!bayerHistogram || bayerHistogram->getHistogram(&histogram) != STATUS_OK)
                    ORIGINATE_ERROR("Failed to get histogram data\n");

                // Generate RGBA data by combining gEven/Odd channels and putting
                // combined totals into alpha channel.
                rgbaData.resize(histogram.size() - CLIP_BINS);
                for (uint32_t i = 0; i < histogram.size() - CLIP_BINS; i++)
                {
                    rgbaData[i][0] = histogram[i].r();
                    // std::cout<<rgbaData[i][0]<<std::endl;
                    rgbaData[i][1] = (histogram[i].gEven() + histogram[i].gOdd()) / 2;
                    rgbaData[i][2] = histogram[i].b();
                    rgbaData[i][3] = rgbaData[i][0] + rgbaData[i][1] + rgbaData[i][2];
                }
                Tuple<4, uint32_t> maxValues(0);
                Tuple<4, uint32_t> maxvalues(0);
                for (uint32_t i = 0; i < rgbaData.size(); i++)
                {
                    maxValues[0] = std::max(rgbaData[i][0], maxValues[0]);
                    maxValues[1] = std::max(rgbaData[i][1], maxValues[1]);
                    maxValues[2] = std::max(rgbaData[i][2], maxValues[2]);
                    maxValues[3] = std::max(rgbaData[i][3], maxValues[3]);
                }

                // std::cout<<maxValues[0]<<std::endl;
                uint rgbMax = std::max(maxValues[0], std::max(maxValues[1], maxValues[2]));
                for (uint32_t i = 0; i < histogram.size() - CLIP_BINS; i++)
                {

                    rgbaData[i][0] = (rgbaData[i][0] * 10000) / maxValues[0];

                    rgbaData[i][1] = (rgbaData[i][1] * 10000) / maxValues[1];
                    rgbaData[i][2] = (rgbaData[i][2] * 10000) / maxValues[2];
                    rgbaData[i][3] = (rgbaData[i][0] + rgbaData[i][1] + rgbaData[i][2]);
                }

                for (uint32_t i = 0; i < rgbaData.size(); i++)
                {
                    maxvalues[0] = std::max(rgbaData[i][0], maxvalues[0]);
                    maxvalues[1] = std::max(rgbaData[i][1], maxvalues[1]);
                    maxvalues[2] = std::max(rgbaData[i][2], maxvalues[2]);
                    maxvalues[3] = std::max(rgbaData[i][3], maxvalues[3]);
                }
                rgbMax = std::max(maxvalues[0], std::max(maxvalues[1], maxvalues[2]));

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, rgbaData.size(), 1, 0,
                             GL_RGBA_INTEGER, GL_UNSIGNED_INT, &rgbaData[0]);

                // Render histograms.
                //   renderHistogram(HISTOGRAM_R, "Red", maxValues[0], RGBTuple<float>(1.0f, 0.0f, 0.0f));
                //   renderHistogram(HISTOGRAM_G, "Green", maxValues[1], RGBTuple<float>(0.0f, 1.0f, 0.0f));
                //  renderHistogram(HISTOGRAM_B, "Blue", maxValues[2], RGBTuple<float>(0.0f, 0.0f, 1.0f));
                renderHistogram(HISTOGRAM_RGB, "Histogram", rgbMax, RGBTuple<float>(1.0f, 1.0f, 1.0f));
                //   renderHistogram(TONECURVE,"Tonecurve",1,RGBTuple<float>(1.0f, 1.0f, 1.0f));
                IAutoControlSettings *settings = interface_cast<IAutoControlSettings>(m_request->getAutoControlSettings());
                settings->getToneMapCurve(RGB_CHANNEL_R, &RED);
                settings->getToneMapCurve(RGB_CHANNEL_B, &BLUE);
                settings->getToneMapCurve(RGB_CHANNEL_G, &GREEN);
                for (int i = 0; i < 129; i++)
                {
                    rgbaData[i][0] = RED[i] * 10000;
                    rgbaData[i][1] = GREEN[i] * 10000;
                    rgbaData[i][2] = BLUE[i] * 10000;
                    rgbaData[i][3] = rgbaData[i][0] + rgbaData[i][1] + rgbaData[i][2];
                }

                maxValues[0] = 0;
                maxValues[1] = 0;
                maxValues[2] = 0;
                maxValues[3] = 0;
                for (uint32_t i = 0; i < rgbaData.size(); i++)
                {
                    maxValues[0] = std::max(rgbaData[i][0], maxValues[0]);
                    maxValues[1] = std::max(rgbaData[i][1], maxValues[1]);
                    maxValues[2] = std::max(rgbaData[i][2], maxValues[2]);
                    maxValues[3] = std::max(rgbaData[i][3], maxValues[3]);
                }
                rgbMax = std::max(maxValues[0], std::max(maxValues[1], maxValues[2]));
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, 129, 1, 0,
                             GL_RGBA_INTEGER, GL_UNSIGNED_INT, &rgbaData[0]);
                renderTonecurve(Tonecurve_RGB, "Tonecurve", rgbMax, RGBTuple<float>(1.0f, 0.0f, 0.0f));
                system(" ps -C argus_histogram -o %cpu>>a.text");

                // Reinhard Tone mapping
            }

            PROPAGATE_ERROR(m_context.swapBuffers());
        }
        CONSUMER_PRINT("No more frames. Cleaning up.\n");

        PROPAGATE_ERROR(requestShutdown());

        return true;
    }

    void ConsumerThread::renderHistogram(HistogramType type, const char *label,
                                         uint32_t max, RGBTuple<float> colorMask)
    {
        using namespace std;
        const Rectangle<uint32_t> &window = m_options.windowRect();
        const Point2D<uint32_t> origin(
            window.width() / 2 + m_histogramSpacing,
            window.height() - (m_histogramSpacing + m_histogramSize.height()) * (type + 1));
        std::fstream fio;

        std::string line;
        fio.open("a.text", ios::out | ios::in);
        int i = 1;

        while (fio)
        {

            // Read a Line from File

            getline(fio, line);

            if (i % 2 == 0)
            {

                // glUniform1i(m_combinedLoc, type == HISTOGRAM_COMBINED);

                /*  std::ostringstream stream;
              stream<<std::setw(7) << line<<"%";
              m_context.setTextPosition(0.0f, 0.1f);
              //m_context.renderText("CPU");
              m_context.setTextPosition(0.01f, 0.09f);
              m_context.renderText(stream.str().c_str());
                  // Print line in Console*/
                cout << line << endl;
            }
            i++;

            // Close the file

            // Render histogram
            glUseProgram(m_histogramProgram);
            // glUniform1i(m_combinedLoc, type == HISTOGRAM_COMBINED);
            glUniform1f(m_binMaxLoc, max);
            glUniform4f(m_colorMaskLoc, colorMask.r(), colorMask.g(), colorMask.b(), 0.5f);
            glViewport(origin.x(), origin.y(), m_histogramSize.width(), m_histogramSize.height());
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            // Render text.
            std::ostringstream stream;
            stream << "CPU:" << line;

            m_context.setTextPosition(0.02f, 0.98f);
            m_context.renderText(label);
            m_context.setTextPosition(0.75f, 0.96f);

            m_context.renderText(stream.str().c_str());

            // cout << line << endl;
        }
        fio.close();
        clear();
    }
    void ConsumerThread::renderTonecurve(HistogramType type, const char *label,
                                         uint32_t max, RGBTuple<float> colorMask)
    {
       system(" ps -C argus_histogram -o %cpu>>a.text");
        using namespace std;
        const Rectangle<uint32_t> &window = m_options.windowRect();
        const Point2D<uint32_t> origin(
            window.width() / 2 + m_histogramSpacing,
            window.height() - (m_histogramSpacing + m_histogramSize.height()) * (type + 1));
        std::fstream fio1;

        std::string line;
        fio1.open("a.text", ios::out | ios::in);
        int i = 1;

        while (fio1)
        {

            // Read a Line from File

            
        // Read a Line from File
        
        getline(fio1, line);
        
        if (i%2==0){
        
  // glUniform1i(m_combinedLoc, type == HISTOGRAM_COMBINED);
    
    
      /*  std::ostringstream stream;
 	stream<<std::setw(7) << line<<"%";
	m_context.setTextPosition(0.0f, 0.1f);
	//m_context.renderText("CPU");
	m_context.setTextPosition(0.01f, 0.09f);
    m_context.renderText(stream.str().c_str());
        // Print line in Console*/
       cout << line << endl;
        
        }i++;
    

            
                // glUniform1i(m_combinedLoc, type == HISTOGRAM_COMBINED);

                 /*std::ostringstream stream;
              stream<<std::setw(7) << line<<"%";
              m_context.setTextPosition(0.7f, 0.96f);
              //m_context.renderText("CPU");
              m_context.setTextPosition(0.01f, 0.09f);
              m_context.renderText(stream.str().c_str());
                  // Print line in Console*/
                //cout << line << endl;
            
        

            // Close the file

            // Render histogram
            glUseProgram(m_histogramProgram);
            // glUniform1i(m_combinedLoc, type == HISTOGRAM_COMBINED);
            glUniform1f(m_binMaxLoc, max);
            glUniform4f(m_colorMaskLoc, colorMask.r(), colorMask.g(), colorMask.b(), 0.5f);
            glViewport(origin.x(), origin.y(), m_histogramSize.width(), m_histogramSize.height());
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            // Render text.
            std::ostringstream stream;
            stream << "CPU:" << line;

            m_context.setTextPosition(0.02f, 0.98f);
            m_context.renderText(label);
            m_context.setTextPosition(0.75f, 0.96f);

            m_context.renderText(stream.str().c_str());

            // cout << line << endl;
        }
        fio1.close();
        clear();
    }
    

    bool ConsumerThread::threadShutdown()
    {
        glDeleteProgram(m_textureProgram);
        glDeleteProgram(m_histogramProgram);
        glDeleteTextures(1, &m_streamTexture);
        glDeleteTextures(1, &m_histogramTexture);
        m_context.cleanup();

        CONSUMER_PRINT("Done.\n");

        return true;
    }

    /*******************************************************************************
     * Argus Producer thread:
     *   Opens the Argus camera driver, creates an OutputStream to be consumed by
     *   the GL consumer, then performs repeating capture requests for CAPTURE_TIME
     *   seconds before closing the producer and Argus driver.
     ******************************************************************************/
    static bool execute(const HistogramSampleOptions &options)
    {
        // Initialize the window and EGL display.
        Window &window = Window::getInstance();
        window.setWindowRect(options.windowRect());
        PROPAGATE_ERROR(g_display.initialize(window.getEGLNativeDisplay()));

        // Initialize the Argus camera provider.
        g_cameraProvider = UniqueObj<CameraProvider>(CameraProvider::create());
        ICameraProvider *iCameraProvider = interface_cast<ICameraProvider>(g_cameraProvider);
        if (!iCameraProvider)
            ORIGINATE_ERROR("Failed to get ICameraProvider interface");
        printf("Argus Version: %s\n", iCameraProvider->getVersion().c_str());

        // Get the selected camera device and sensor mode.
        CameraDevice *cameraDevice = ArgusHelpers::getCameraDevice(
            g_cameraProvider.get(), options.cameraDeviceIndex());
        if (!cameraDevice)
            ORIGINATE_ERROR("Selected camera device is not available");
        SensorMode *sensorMode = ArgusHelpers::getSensorMode(cameraDevice, options.sensorModeIndex());
        ISensorMode *iSensorMode = interface_cast<ISensorMode>(sensorMode);
        if (!iSensorMode)
            ORIGINATE_ERROR("Selected sensor mode not available");

        // Create the capture session using the specified device and get its interfaces.
        UniqueObj<CaptureSession> captureSession(iCameraProvider->createCaptureSession(cameraDevice));
        ICaptureSession *iCaptureSession = interface_cast<ICaptureSession>(captureSession);
        IEventProvider *iEventProvider = interface_cast<IEventProvider>(captureSession);
        if (!iCaptureSession || !iEventProvider)
            ORIGINATE_ERROR("Failed to create CaptureSession");

        // Create the OutputStream.
        PRODUCER_PRINT("Creating output stream\n");
        UniqueObj<OutputStreamSettings> streamSettings(
            iCaptureSession->createOutputStreamSettings(STREAM_TYPE_EGL));
        IEGLOutputStreamSettings *iEGLStreamSettings =
            interface_cast<IEGLOutputStreamSettings>(streamSettings);
        if (iEGLStreamSettings)
        {
            iEGLStreamSettings->setPixelFormat(PIXEL_FMT_YCbCr_420_888);
            iEGLStreamSettings->setResolution(Size2D<uint32_t>(options.windowRect().width(),
                                                               options.windowRect().height()));
            iEGLStreamSettings->setEGLDisplay(g_display.get());
            iEGLStreamSettings->setMetadataEnable(true);
        }

        // Create video encoder stream using the sensor mode resolution.
        iEGLStreamSettings->setResolution(iSensorMode->getResolution());
        UniqueObj<OutputStream> videoStream(iCaptureSession->createOutputStream(streamSettings.get()));
        IEGLOutputStream *iVideoStream = interface_cast<IEGLOutputStream>(videoStream);
        if (!iVideoStream)
            ORIGINATE_ERROR("Failed to create video stream");
        UniqueObj<OutputStream> outputStream(iCaptureSession->createOutputStream(streamSettings.get()));
        IEGLOutputStream *iEGLOutputStream = interface_cast<IEGLOutputStream>(outputStream);
        if (!iEGLOutputStream)
            ORIGINATE_ERROR("Failed to create EGLOutputStream");
        UniqueObj<Request> request(iCaptureSession->createRequest());
        IRequest *iRequest = interface_cast<IRequest>(request);
        if (!iRequest)
            ORIGINATE_ERROR("Failed to create Request");
        iRequest->enableOutputStream(outputStream.get());
        iRequest->enableOutputStream(videoStream.get());

        // Determine the framerate (0 indicates max framerate for sensor mode).
        uint32_t maxFramerate = (1000000000 / (iSensorMode->getFrameDurationRange().min() - 1));
        uint32_t minFramerate = (1000000000 / iSensorMode->getFrameDurationRange().max()) + 1;
        uint32_t framerate = maxFramerate;
        IAutoControlSettings *settings = interface_cast<IAutoControlSettings>(iRequest->getAutoControlSettings());
        //    IStreamSettings *streamsettings = interface_cast<IStreamSettings>(m_request->getStreamSettings(outputStream)));
        if (options.Tone_curves() == 0)
        {
        }
        else if (options.Tone_curves() == 7)
        {
        
            for (int i = 0; i < 129; i++)
            {
           
               
	            expo[i]=(a*pow(2.7,(b*i)))+c;
	            expo[i]=(expo[i]/((a*pow(2.7,(b*128)))+c));


                curve[i] = expo[i];
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 1)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = linear[i];
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 2)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = polynomial[i];
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 3)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = sigmoid[i];
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 4)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = Expo_increase[i];
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 5)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = s[i]/128;
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        else if (options.Tone_curves() == 6)
        {
            for (int i = 0; i < 129; i++)
            {
                curve[i] = s1[i]/128;
                settings->setToneMapCurveEnable(true);
                settings->setToneMapCurve(RGB_CHANNEL_R, curve);
                settings->setToneMapCurve(RGB_CHANNEL_G, curve);
                settings->setToneMapCurve(RGB_CHANNEL_B, curve);
            }
        }
        // Set the sensor mode in the request.
        ISourceSettings *iSourceSettings = interface_cast<ISourceSettings>(request);
        if (!iSourceSettings)
            ORIGINATE_ERROR("Failed to get source settings request interface");
        iSourceSettings->setSensorMode(sensorMode);
        // Initialize the GStreamer video encoder consumer.

        GstVideoEncoder gstVideoEncoder(options);
        if (!gstVideoEncoder.initialize(iVideoStream->getEGLStream(), iSensorMode->getResolution(), framerate))
        {
            ORIGINATE_ERROR("Failed to initialize GstVideoEncoder EGLStream consumer");
        }
        if (!gstVideoEncoder.startRecording())
        {
            ORIGINATE_ERROR("Failed to start video recording");
        }

        // Launch the consumer thread to consume frames from the OutputStream's EGLStream.
        PRODUCER_PRINT("Launching consumer thread\n");
        ConsumerThread consumerThread(options, iEGLOutputStream->getEGLStream(), iRequest);
        PROPAGATE_ERROR(consumerThread.initialize());
        // Wait until the consumer is connected to the stream.
        PROPAGATE_ERROR(consumerThread.waitRunning());

        // Create capture request and enable output stream.

        ;

        // Submit capture requests.
        PRODUCER_PRINT("Starting repeat capture requests.\n");
        if (iCaptureSession->repeat(request.get()) != STATUS_OK)
            ORIGINATE_ERROR("Failed to start repeat capture request");

        // Wait for specified number of seconds.
        PROPAGATE_ERROR(window.pollingSleep(options.captureTime()));

        // Stop the repeating request and wait for idle.
        iCaptureSession->stopRepeat();
        iCaptureSession->waitForIdle();

        // Destroy the output stream. This destroys the EGLStream which causes
        // the GL consumer acquire to fail and the consumer thread to end.
        outputStream.reset();

        // Wait for the consumer thread to complete.
        PROPAGATE_ERROR(consumerThread.shutdown());

        // Shut down Argus.
        g_cameraProvider.reset();

        // Shut down the window (destroys window's EGLSurface).
        window.shutdown();

        // Cleanup the EGL display
        PROPAGATE_ERROR(g_display.cleanup());

        PRODUCER_PRINT("Done -- exiting.\n");
        return true;
    }

}; // namespace ArgusSamples

int main(int argc, char **argv)

{

    ArgusSamples::HistogramSampleOptions options(basename(argv[0]));
    if (!options.parse(argc, argv))
        return EXIT_FAILURE;
    if (options.requestedExit())
        return EXIT_SUCCESS;

    if (!ArgusSamples::execute(options))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}



