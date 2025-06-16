/*
 *   SPDX-FileCopyrightText: 2025 Jed Liu <liujed@users.noreply.github.com>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "windowsspotlightprovider.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>

#include <KIO/StoredTransferJob>
#include <KPluginFactory>


WindowsSpotlightProvider::WindowsSpotlightProvider(QObject *parent, const KPluginMetaData &data, const QVariantList &args)
    : PotdProvider(parent, data, args)
    , m_screenWidth(args.size() >= 2 ? args[0].toInt() : 0)
    , m_screenHeight(args.size() >= 2 ? args[1].toInt() : 0)
{
    const QUrl url(QStringLiteral("https://fd.api.iris.microsoft.com/v4/api/selection?&placement=88000820&bcnt=1&country=CA&locale=en-CA&fmt=json"));

    KIO::StoredTransferJob* job = KIO::storedGet(url, KIO::NoReload, KIO::HideProgressInfo);
    connect(job, &KIO::StoredTransferJob::finished,
            this, &WindowsSpotlightProvider::pageRequestFinished);
}

void WindowsSpotlightProvider::pageRequestFinished(KJob *_job)
{
    KIO::StoredTransferJob *job = static_cast<KIO::StoredTransferJob*>(_job);
    if (job->error()) {
        Q_EMIT error(this);
        return;
    }

    auto json = QJsonDocument::fromJson(job->data());
    do {
        if (json.isNull()) break;

        // Extract 'batchrsp.items[0].item' as a string-encoded JSON object.
        const auto batchResponseObj =
            json.object().value(QLatin1String("batchrsp"));
        if (!batchResponseObj.isObject()) break;
        const QJsonObject batchResponseObject = batchResponseObj.toObject();

        const auto itemsArray =
            batchResponseObject.value(QLatin1String("items"));
        if (!itemsArray.isArray() || itemsArray.toArray().size() <= 0) break;

        const auto itemObj = itemsArray.toArray().at(0);
        if (!itemObj.isObject()) break;
        const QJsonObject itemObject = itemObj.toObject();

        const auto itemString =
            itemObject.value(QLatin1String("item")).toString();
        if (itemString.isEmpty()) break;

        const auto itemJson = QJsonDocument::fromJson(itemString.toUtf8());
        if (itemJson.isNull()) break;

        // The 'ad' field has everything that we're interested in.
        const auto adObj = itemJson.object().value(QLatin1String("ad"));
        if (!adObj.isObject()) break;
        const QJsonObject adObject = adObj.toObject();

        // Use 'landscapeImage.asset' as the image's URL.
        //
        // TODO: select between landscapeImage and portraitImage.
        const auto imageObj = adObject.value(QLatin1String("landscapeImage"));
        if (!imageObj.isObject()) break;
        const QJsonObject imageObject = imageObj.toObject();

        const auto assetString =
            imageObject.value(QLatin1String("asset")).toString();
        if (assetString.isEmpty()) break;

        m_remoteUrl = QUrl(assetString);

        // Extract an image title from 'iconHoverText'. While there is a
        // 'title' field, it is often less informative about what the image is
        // showing.
        const auto iconHoverTextString =
            adObject.value(QLatin1String("iconHoverText")).toString();
        if (!iconHoverTextString.isEmpty()) {
            auto idx = iconHoverTextString.indexOf(QLatin1String("\r\n"));
            if (idx > 0) {
                m_title = iconHoverTextString.first(idx).trimmed();
            }
        }

        // Extract the author from 'copyright'.
        const auto copyrightString =
            adObject.value(QLatin1String("copyright")).toString();
        const QRegularExpression copyrightRegex(QStringLiteral("©([^/]+)/"));
        if (const auto match = copyrightRegex.match(copyrightString);
                match.hasMatch()) {
            m_author = match.captured(1).trimmed();
        }

        KIO::StoredTransferJob *imageJob = KIO::storedGet(m_remoteUrl, KIO::NoReload, KIO::HideProgressInfo);
        connect(imageJob, &KIO::StoredTransferJob::finished,
                this, &WindowsSpotlightProvider::imageRequestFinished);
        return;
    } while(0);

    Q_EMIT error(this);
    return;
}

void WindowsSpotlightProvider::imageRequestFinished(KJob *_job)
{
    KIO::StoredTransferJob *job = static_cast<KIO::StoredTransferJob*>(_job);
    if (job->error()) {
        Q_EMIT error(this);
        return;
    }
    QByteArray data = job->data();
    Q_EMIT finished(this, QImage::fromData(data));
}


K_PLUGIN_CLASS_WITH_JSON(WindowsSpotlightProvider, "windowsspotlightprovider.json")

#include "windowsspotlightprovider.moc"
