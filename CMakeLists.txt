cmake_minimum_required(VERSION 3.16)

project(potd-windows-spotlight-provider)

set(QT_MIN_VERSION "6.8.0")
set(KF6_MIN_VERSION "6.14.0")

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED
    COMPONENTS
        Core
        Gui
)

find_package(KF6 ${KF6_MIN_VERSION} REQUIRED
    COMPONENTS
        CoreAddons
        KIO
)

find_package(PlasmaPotdProvider CONFIG)
set_package_properties(PlasmaPotdProvider PROPERTIES
    DESCRIPTION "Plasma Picture-of-the-day Provider library"
    TYPE RECOMMENDED
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

# Some distros (e.g. Kubuntu/Debian) ship the Plasma PoTD provider runtime
# library (libplasmapotdprovidercore) but don't package a
# PlasmaPotdProviderConfig.cmake / Devel component with its headers, so
# find_package() above can't locate it. Fall back to linking directly
# against the system's runtime library, paired with a vendored copy of its
# upstream header (compat/plasma/potdprovider/) so plugins built this way
# stay ABI-compatible with the already-loaded system library.
if (NOT TARGET Plasma::PotdProvider)
    find_library(PlasmaPotdProviderCore_LIBRARY
        NAMES plasmapotdprovidercore libplasmapotdprovidercore.so.2
    )
    if (PlasmaPotdProviderCore_LIBRARY)
        message(STATUS "No PlasmaPotdProviderConfig.cmake found; using system "
            "${PlasmaPotdProviderCore_LIBRARY} with vendored compat headers instead.")
        add_library(Plasma::PotdProvider SHARED IMPORTED)
        set_target_properties(Plasma::PotdProvider PROPERTIES
            IMPORTED_LOCATION "${PlasmaPotdProviderCore_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/compat"
            INTERFACE_LINK_LIBRARIES "Qt6::Gui;KF6::CoreAddons"
        )
    else()
        message(FATAL_ERROR "Could not find the Plasma PoTD provider library "
            "(PlasmaPotdProviderConfig.cmake or libplasmapotdprovidercore). "
            "Install your distro's Plasma Workspace development package, or "
            "the plasma-dataengines-addons runtime package on Debian/Ubuntu.")
    endif()
endif()

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
