#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

// TruClipController — a minimal edit controller with no parameters.
// v1 of TruClip requires no user-editable parameters.
class TruClipController : public Steinberg::Vst::EditController
{
public:
    static Steinberg::FUnknown* createInstance(void*)
    {
        return static_cast<Steinberg::Vst::IEditController*>(new TruClipController());
    }

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override;
};
