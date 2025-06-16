set(potd_windowsspotlightprovider_SRCS
    windowsspotlightprovider.cpp
)

add_library(plasma_potd_windowsspotlightprovider MODULE ${potd_windowsspotlightprovider_SRCS})
target_link_libraries(plasma_potd_windowsspotlightprovider
    Plasma::PotdProvider
    KF6::KIOCore
)

install(TARGETS plasma_potd_windowsspotlightprovider DESTINATION ${KDE_INSTALL_PLUGINDIR}/potd)
