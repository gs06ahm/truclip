#include "processor.h"
#include "cids.h"

#include <algorithm>
#include <cstring>

using namespace Steinberg;
using namespace Steinberg::Vst;

TruClipProcessor::TruClipProcessor()
{
    // Tell the base class which controller class to pair with this processor.
    setControllerClass(TruClipControllerUID);
}

tresult PLUGIN_API TruClipProcessor::initialize(FUnknown* context)
{
    tresult result = AudioEffect::initialize(context);
    if (result != kResultOk)
        return result;

    addAudioInput (STR16("Stereo In"),  SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Out"), SpeakerArr::kStereo);

    return kResultOk;
}

tresult PLUGIN_API TruClipProcessor::setBusArrangements(
    SpeakerArrangement* inputs,  int32 numIns,
    SpeakerArrangement* outputs, int32 numOuts)
{
    // Accept any symmetric arrangement where in == out for each bus.
    if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
        return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);

    return kResultFalse;
}

tresult PLUGIN_API TruClipProcessor::setupProcessing(ProcessSetup& setup)
{
    return AudioEffect::setupProcessing(setup);
}

tresult PLUGIN_API TruClipProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
    return (symbolicSampleSize == kSample32) ? kResultTrue : kResultFalse;
}

tresult PLUGIN_API TruClipProcessor::process(ProcessData& data)
{
    if (data.numInputs == 0 || data.numOutputs == 0)
        return kResultOk;

    AudioBusBuffers& in  = data.inputs[0];
    AudioBusBuffers& out = data.outputs[0];

    int32 numChannels = std::min(in.numChannels, out.numChannels);

    for (int32 ch = 0; ch < numChannels; ++ch)
    {
        Sample32* src = in.channelBuffers32[ch];
        Sample32* dst = out.channelBuffers32[ch];

        if (src && dst && src != dst)
            std::memcpy(dst, src, static_cast<std::size_t>(data.numSamples) * sizeof(Sample32));
        // In-place processing (src == dst): the output buffer IS the input buffer,
        // so no copy is needed — the data is already in the right place.
    }

    return kResultOk;
}
