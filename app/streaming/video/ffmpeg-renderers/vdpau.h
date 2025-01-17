#pragma once

#include "renderer.h"

extern "C" {
#include <vdpau/vdpau.h>
#include <vdpau/vdpau_x11.h>
#include <libavutil/hwcontext_vdpau.h>
}

class VDPAURenderer : public IFFmpegRenderer
{
public:
    VDPAURenderer();
    virtual ~VDPAURenderer() override;
    virtual bool initialize(PDECODER_PARAMETERS params) override;
    virtual bool prepareDecoderContext(AVCodecContext* context) override;
    virtual void renderFrame(AVFrame* frame) override;
    virtual bool needsTestFrame() override;

private:
    uint32_t m_VideoWidth, m_VideoHeight;
    uint32_t m_DisplayWidth, m_DisplayHeight;
    AVBufferRef* m_HwContext;
    VdpPresentationQueueTarget m_PresentationQueueTarget;
    VdpPresentationQueue m_PresentationQueue;
    VdpVideoMixer m_VideoMixer;
    VdpRGBAFormat m_OutputSurfaceFormat;
    VdpDevice m_Device;

#define OUTPUT_SURFACE_COUNT 3
    VdpOutputSurface m_OutputSurface[OUTPUT_SURFACE_COUNT];
    int m_NextSurfaceIndex;

#define OUTPUT_SURFACE_FORMAT_COUNT 2
    static const VdpRGBAFormat k_OutputFormats8Bit[OUTPUT_SURFACE_FORMAT_COUNT];
    static const VdpRGBAFormat k_OutputFormats10Bit[OUTPUT_SURFACE_FORMAT_COUNT];

    VdpGetErrorString* m_VdpGetErrorString;
    VdpPresentationQueueTargetDestroy* m_VdpPresentationQueueTargetDestroy;
    VdpVideoMixerCreate* m_VdpVideoMixerCreate;
    VdpVideoMixerDestroy* m_VdpVideoMixerDestroy;
    VdpVideoMixerRender* m_VdpVideoMixerRender;
    VdpPresentationQueueCreate* m_VdpPresentationQueueCreate;
    VdpPresentationQueueDestroy* m_VdpPresentationQueueDestroy;
    VdpPresentationQueueDisplay* m_VdpPresentationQueueDisplay;
    VdpPresentationQueueSetBackgroundColor* m_VdpPresentationQueueSetBackgroundColor;
    VdpPresentationQueueBlockUntilSurfaceIdle* m_VdpPresentationQueueBlockUntilSurfaceIdle;
    VdpOutputSurfaceCreate* m_VdpOutputSurfaceCreate;
    VdpOutputSurfaceDestroy* m_VdpOutputSurfaceDestroy;
    VdpOutputSurfaceQueryCapabilities* m_VdpOutputSurfaceQueryCapabilities;
    VdpVideoSurfaceGetParameters* m_VdpVideoSurfaceGetParameters;
    VdpGetInformationString* m_VdpGetInformationString;

    // X11 stuff
    VdpPresentationQueueTargetCreateX11* m_VdpPresentationQueueTargetCreateX11;
};


