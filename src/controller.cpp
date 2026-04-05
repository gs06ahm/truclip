#include "controller.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

tresult PLUGIN_API TruClipController::initialize(FUnknown* context)
{
    return EditController::initialize(context);
}
