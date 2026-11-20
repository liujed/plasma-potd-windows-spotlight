# Windows Spotlight picture-of-the-day provider for KDE Plasma 6

A KDE Plasma 6 POTD provider that downloads daily high-resolution wallpaper
from Windows 11's Spotlight API.

## Building

```
mkdir build
cd build
cmake ..
make
```

This needs the Plasma PoTD provider library (`libplasmapotdprovidercore`) and
its `PlasmaPotdProviderConfig.cmake` package, which on Arch is provided by
`plasma-workspace`. On Debian/Ubuntu-based distros (e.g. Kubuntu), the
`plasma-dataengines-addons` package ships the runtime library but not that
CMake package or its headers. In that case, CMake automatically falls back to
linking directly against the system's `libplasmapotdprovidercore.so`, paired
with a vendored copy of its upstream header under
[`compat/`](compat/plasma/potdprovider). This keeps the plugin
ABI-compatible with the already-loaded system library — building against a
from-scratch/incompatible copy of this header causes Plasma to fail silently
with `KPluginFactory could not create a PotdProvider instance`, which looks
like the wallpaper spinner hanging forever with no visible error.

## Installing

The above produces `bin/plasma_potd_windowsspotlightprovider.so`. Install this
alongside your other Plasma POTD providers and restart `plasmashell`. On my
Arch system, this was:
```
sudo install -m 755 \
  bin/plasma_potd_windowsspotlightprovider.so \
  /usr/lib/qt6/plugins/potd/
plasmashell --replace &>/dev/null & disown
```

Alternatively, from the `build` directory:
```
sudo cmake --install .
plasmashell --replace &>/dev/null & disown
```

## Usage

0. Ensure you have the KDE Plasma Addons installed.
1. Right-click on the KDE desktop and select **Desktop and Wallpaper**.
2. Under **Wallpaper type**, select **Picture of the Day**.
3. Under **Provider**, select **Windows Spotlight**.

## Acknowledgements

Adapted from the [Bing
provider](https://invent.kde.org/plasma/kdeplasma-addons/-/blob/a4c3aee27dbebdbe80421eb9257c4c7a99912b01/wallpapers/potd/plugins/providers/bingprovider.cpp)
by Weng Xuetian in the [KDE Plasma
Addons](https://invent.kde.org/plasma/kdeplasma-addons) library.

The vendored fallback header in [`compat/`](compat/plasma/potdprovider) is a
copy of kdeplasma-addons'
[`potdprovider.h`](https://invent.kde.org/plasma/kdeplasma-addons/-/blob/v6.6.7/wallpapers/potd/plugins/potdprovider.h)
(SPDX-FileCopyrightText 2007 Tobias Koenig, 2021 Guo Yunhe), used only when
the system doesn't provide a `PlasmaPotdProviderConfig.cmake` package.

This project benefited from the [Spotlight APIv4
analysis](https://github.com/ORelio/Spotlight-Downloader/blob/master/SpotlightAPI.md#api-v4)
by [ORelio](https://github.com/ORelio) of the [Spotlight Downloader
project](https://github.com/ORelio/Spotlight-Downloader).
