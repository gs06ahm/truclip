#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

// TruClipProcessor — a no-op VST3 audio processor that copies every input
// sample verbatim to the corresponding output channel.
class TruClipProcessor : public Steinberg::Vst::AudioEffect
{
public:
    TruClipProcessor();
    ~TruClipProcessor() override = default;

    // Factory function called by the VST3 host to create a new instance.
    static Steinberg::FUnknown* createInstance(void*)
    {
        return static_cast<Steinberg::Vst::IAudioProcessor*>(new TruClipProcessor());
    }

    // IPluginBase
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override;

    // IAudioProcessor
    Steinberg::tresult PLUGIN_API setBusArrangements(
        Steinberg::Vst::SpeakerArrangement* inputs,  Steinberg::int32 numIns,
        Steinberg::Vst::SpeakerArrangement* outputs, Steinberg::int32 numOuts) override;

    Steinberg::tresult PLUGIN_API setupProcessing(
        Steinberg::Vst::ProcessSetup& setup) override;

    Steinberg::tresult PLUGIN_API canProcessSampleSize(
        Steinberg::int32 symbolicSampleSize) override;

    Steinberg::tresult PLUGIN_API process(
        Steinberg::Vst::ProcessData& data) override;
};
