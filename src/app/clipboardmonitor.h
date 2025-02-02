// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CLIPBOARDMONITOR_H
#define CLIPBOARDMONITOR_H

#include "common/common.h"
#include "platform/platformnativeinterface.h"
#include "platform/platformclipboard.h"

#include <QVariantMap>

enum class ClipboardOwnership {
    Foreign,
    Own,
    Hidden,
};

class ClipboardMonitor final : public QObject
{
    Q_OBJECT

public:
    explicit ClipboardMonitor(const QStringList &formats);
    void startMonitoring();

signals:
    void clipboardChanged(const QVariantMap &data, ClipboardOwnership ownership);
    void clipboardUnchanged(const QVariantMap &data);
    void synchronizeSelection(ClipboardMode sourceMode, uint sourceTextHash, uint targetTextHash);

private:
    void onClipboardChanged(ClipboardMode mode);

    QVariantMap m_clipboardData;
    QVariantMap m_selectionData;

    PlatformClipboardPtr m_clipboard;
    QStringList m_formats;

    QString m_clipboardTab;
    bool m_storeClipboard;

#ifdef HAS_MOUSE_SELECTIONS
    bool m_storeSelection;
    bool m_runSelection;
    bool m_clipboardToSelection;
    bool m_selectionToClipboard;
#endif
};

#endif // CLIPBOARDMONITOR_H
