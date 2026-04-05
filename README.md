# TruClip

[![Build](https://github.com/gs06ahm/truclip/actions/workflows/build.yml/badge.svg)](https://github.com/gs06ahm/truclip/actions/workflows/build.yml)
[![Latest Release](https://img.shields.io/github/v/release/gs06ahm/truclip)](https://github.com/gs06ahm/truclip/releases/latest)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

A minimal, open-source Windows VST3 audio plugin for Ableton Live 11.

**TruClip v1** is a no-op plugin: every input sample is reproduced at the
output unchanged. It serves as a verified, reproducible foundation for future
DSP development.

---

## Latest Download

<!-- LATEST_RELEASE_URL -->https://github.com/gs06ahm/truclip/releases/latest<!-- /LATEST_RELEASE_URL -->

Download the latest Windows MSI installer from the
[Releases page](https://github.com/gs06ahm/truclip/releases/latest).

---

## Requirements

| Requirement | Version |
|---|---|
| Windows | 10 (x64 / AMD64) |
| Ableton Live | 11 (or any VST3-compatible host) |
| CPU | x86-64 (AMD Ryzen 5 or equivalent) |

---

## Installation

1. Download `truclip-<version>-windows.msi` from the
   [Releases page](https://github.com/gs06ahm/truclip/releases).
2. Run the installer (double-click the MSI file).  
   The plugin is installed to:
   ```
   C:\Program Files\Common Files\VST3\truclip.vst3\
   ```
3. Restart your DAW and re-scan for VST3 plugins.

---

## Development Setup

### Prerequisites

| Tool | Version | Notes |
|---|---|---|
| [Visual Studio Build Tools 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) | 17.x | Select the **"Desktop development with C++"** workload |
| [CMake](https://cmake.org/download/) | 3.22+ | Ensure `cmake` is on `PATH` |
| [Git](https://git-scm.com/) | any | Required for FetchContent (VST3 SDK) |
| [Visual Studio Code](https://code.visualstudio.com/) | 1.114.0+ | Recommended IDE |
| [.NET SDK](https://dotnet.microsoft.com/download) | 6+ | Required for WiX installer builds only |

> **WiX Toolset v4** is only needed if you want to build the MSI installer
> locally.  Install it after the .NET SDK:
> ```powershell
> dotnet tool install --global wix --version 4.0.5
> ```

### Recommended VS Code Extensions

Open the repository in VS Code and accept the prompt to install the
recommended extensions, or install them manually:

- **ms-vscode.cpptools** — C/C++ IntelliSense & debugging  
- **ms-vscode.cmake-tools** — CMake integration  
- **ms-vscode.cpptools-extension-pack** — Full C++ pack  
- **twxs.cmake** — CMake syntax highlighting

### Clone

```bash
git clone https://github.com/gs06ahm/truclip.git
cd truclip
```

### Configure & Build (Debug)

```powershell
cmake --preset windows-debug
cmake --build --preset windows-debug
```

The VST3 bundle is written to `build-debug\VST3\Debug\truclip.vst3\`.

Or use the VS Code task **Terminal › Run Build Task** (`Ctrl+Shift+B`),
which runs *CMake Build (Debug)* automatically.

### Configure & Build (Release)

```powershell
cmake --preset windows-release
cmake --build --preset windows-release
```

Output: `build\VST3\Release\truclip.vst3\`

### Build MSI Installer (local)

```powershell
# After a Release build:
wix build installer\truclip.wxs `
  -d "ProductVersion=1.0.0" `
  -d "VST3Dir=build\VST3\Release\truclip.vst3" `
  -o truclip-1.0.0-windows.msi
```

---

## Project Structure

```
truclip/
├── .github/
│   └── workflows/
│       ├── build.yml       # CI: build on push / pull request
│       └── release.yml     # CD: build MSI + publish release on tag
├── .vscode/
│   ├── extensions.json     # Recommended VS Code extensions
│   ├── settings.json       # Project-level VS Code settings
│   └── tasks.json          # Build tasks (Ctrl+Shift+B)
├── installer/
│   └── truclip.wxs         # WiX v4 MSI installer definition
├── src/
│   ├── cids.h              # Processor & controller UIDs
│   ├── controller.h/.cpp   # Minimal VST3 edit controller
│   ├── pluginfactory.cpp   # VST3 plugin factory entry point
│   ├── processor.h/.cpp    # No-op audio processor
│   └── version.h           # Version & metadata macros
├── CMakeLists.txt          # CMake build (fetches VST3 SDK via FetchContent)
├── CMakePresets.json       # Debug & Release presets for Windows x64
├── LICENSE                 # MIT
└── README.md
```

---

## CI / CD

| Event | Workflow | Result |
|---|---|---|
| Push or PR (any branch) | `build.yml` | Builds plugin; uploads VST3 bundle as a workflow artifact |
| Push of a `v*` tag | `release.yml` | Builds plugin + MSI; updates README download link; publishes GitHub Release |

### Publishing a Release

```powershell
git tag v1.0.0
git push origin v1.0.0
```

GitHub Actions will:
1. Build `truclip.vst3` in Release mode.
2. Build `truclip-1.0.0-windows.msi` with WiX v4.
3. Update the download link in this README on the `main` branch.
4. Create a GitHub Release named **TruClip v1.0.0** with the MSI attached.

---

## Architecture Notes

- **VST3 SDK** is fetched at configure time via CMake `FetchContent`
  (no submodules required in the clone).
- **No GUI** — v1 has zero parameters and no editor window; this keeps
  the plugin small and the build reproducible.
- **No-op processing** — `TruClipProcessor::process()` copies every input
  sample to the matching output channel with `std::memcpy`.
- The MSI installs the plugin bundle into the system-wide VST3 directory
  (`C:\Program Files\Common Files\VST3\`) so all DAWs can find it.

---

## License

[MIT](LICENSE) © TruClip Audio
