/*
 *   SPDX-FileCopyrightText: 2025 Jed Liu <liujed@users.noreply.github.com>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef WINDOWS_SPOTLIGHT_PROVIDER_H
#define WINDOWS_SPOTLIGHT_PROVIDER_H

#include <plasma/potdprovider/potdprovider.h>

class KJob;

class WindowsSpotlightProvider : public PotdProvider
{
    Q_OBJECT

public:
    explicit WindowsSpotlightProvider(QObject *parent, const KPluginMetaData &data, const QVariantList &args);

private:
    void pageRequestFinished(KJob *job);
    void imageRequestFinished(KJob *job);

    int m_screenWidth;
    int m_screenHeight;
};

#endif
