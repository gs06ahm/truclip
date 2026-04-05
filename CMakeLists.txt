cmake_minimum_required(VERSION 3.22)

project(truclip
    VERSION     1.0.0
    DESCRIPTION "TruClip — no-op VST3 audio plugin"
    LANGUAGES   CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# VST3 SDK options — disable everything we don't need so the SDK builds fast.
# These MUST be set before FetchContent_MakeAvailable.
# ---------------------------------------------------------------------------
set(SMTG_ADD_VSTGUI                   OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES  OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VSTGUI_SUPPORT        OFF CACHE BOOL "" FORCE)
set(SMTG_RUN_VST_VALIDATOR_TESTS      OFF CACHE BOOL "" FORCE)
set(SMTG_CREATE_PLUGIN_LINK           OFF CACHE BOOL "" FORCE)
set(SMTG_PLUGIN_TARGET_USER_PROGRAM_FILES_COMMON OFF CACHE BOOL "" FORCE)

# ---------------------------------------------------------------------------
# Fetch the Steinberg VST3 SDK (only the submodules we actually need)
# ---------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    vst3sdk
    GIT_REPOSITORY https://github.com/steinbergmedia/vst3sdk.git
    GIT_TAG        v3.7.9_build_61
    GIT_SUBMODULES "base;cmake;pluginterfaces;public.sdk"
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(vst3sdk)

# ---------------------------------------------------------------------------
# TruClip VST3 plugin target
# ---------------------------------------------------------------------------
smtg_add_vst3plugin(truclip
    PACKAGE_NAME    "TruClip"
    PACKAGE_VERSION "${PROJECT_VERSION}"
    SOURCES_LIST
        src/version.h
        src/cids.h
        src/processor.h
        src/processor.cpp
        src/controller.h
        src/controller.cpp
        src/pluginfactory.cpp
)

target_include_directories(truclip PRIVATE src)

target_link_libraries(truclip
    PRIVATE
        sdk
)
