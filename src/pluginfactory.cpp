// VST3 plugin factory — registers both the processor and controller classes
// with the host via the standard BEGIN_FACTORY_DEF / DEF_CLASS2 / END_FACTORY
// macros from the Steinberg public.sdk.

#include "public.sdk/source/main/pluginfactory.h"

#include "processor.h"
#include "controller.h"
#include "cids.h"
#include "version.h"

BEGIN_FACTORY_DEF(
    TRUCLIP_PLUGIN_VENDOR,
    TRUCLIP_PLUGIN_URL,
    TRUCLIP_PLUGIN_EMAIL)

    // Audio processor
    DEF_CLASS2(
        INLINE_UID(0x5A4F3B2C, 0xD1E8F907, 0x62B5A4C3, 0x7D8E9F01),
        PClassInfo::kManyInstances,
        kVstAudioEffectClass,
        TRUCLIP_PLUGIN_NAME,
        Steinberg::Vst::kDistributable,
        Steinberg::Vst::PlugType::kFx,
        TRUCLIP_VERSION_STR,
        kVstVersionString,
        TruClipProcessor::createInstance)

    // Edit controller
    DEF_CLASS2(
        INLINE_UID(0x9B8A7C6D, 0x5E4F3021, 0xAB9C8D7E, 0x6F5A4B3C),
        PClassInfo::kManyInstances,
        kVstComponentControllerClass,
        TRUCLIP_PLUGIN_NAME "Controller",
        0, "",
        TRUCLIP_VERSION_STR,
        kVstVersionString,
        TruClipController::createInstance)

END_FACTORY
