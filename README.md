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

This project benefited from the [Spotlight APIv4
analysis](https://github.com/ORelio/Spotlight-Downloader/blob/master/SpotlightAPI.md#api-v4)
by [ORelio](https://github.com/ORelio) of the [Spotlight Downloader
project](https://github.com/ORelio/Spotlight-Downloader).
