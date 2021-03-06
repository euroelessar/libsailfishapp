
/**
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 * All rights reserved.
 *
 * This file is part of libsailfishapp
 *
 * You may use this file under the terms of the GNU Lesser General
 * Public License version 2.1 as published by the Free Software Foundation
 * and appearing in the file license.lgpl included in the packaging
 * of this file.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file license.lgpl included in the packaging
 * of this file.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 **/


#include "sailfishapp_priv.h"

#include <QCoreApplication>
#include <QString>
#include <QFileInfo>
#include <QDir>


static QString applicationPath()
{
    QString argv0 = QCoreApplication::arguments()[0];

    if (argv0.startsWith("/")) {
        // First, try argv[0] if it's an absolute path (needed for booster)
        return argv0;
    } else {
        // If that doesn't give an absolute path, use /proc-based detection
        return QCoreApplication::applicationFilePath();
    }
}

static QString customAppName;

namespace SailfishAppPriv {

void _PrivateAPI_DoNotUse_setAppName(QString appName)
{
    // Set custom app name - used by the launcher
    customAppName = appName;
}

QString appName()
{
    if (!customAppName.isNull()) {
        return customAppName;
    }

    QFileInfo exe = QFileInfo(applicationPath());
    return exe.fileName();
}

QString dataDir()
{
    QFileInfo exe = QFileInfo(applicationPath());

    // "/usr/bin/<appname>" --> "/usr/share/<appname>/"
    return QDir::cleanPath(QString("%1/%2")
        .arg(exe.absoluteDir().filePath("../share"))
        .arg(appName()));
}

}; /* namespace SailfishAppPriv */
