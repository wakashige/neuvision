/* * Z3D - A structured light 3D scanner
 * Copyright (C) 2013-2016 Nicolas Ulrich <nikolaseu@gmail.com>
 *
 * This file is part of Z3D.
 *
 * Z3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Z3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Z3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Z3D_CAMERAACQUISITION_PLUGIN___OPENCVVIDEOCAPTURECAMERA_H
#define Z3D_CAMERAACQUISITION_PLUGIN___OPENCVVIDEOCAPTURECAMERA_H

#include "zcamerainterface_p.h"

#include <QMutex>

namespace Z3D
{

class OpenCVVideoCaptureCamera : public ZCameraBase
{
    Q_OBJECT

public:
    explicit OpenCVVideoCaptureCamera(int deviceId, QObject *parent = 0);
    ~OpenCVVideoCaptureCamera();

signals:

public slots:
    /// acquisition control
    virtual bool startAcquisition();
    virtual bool stopAcquisition();

    /// camera attributes (settings)
    virtual QList<ZCameraAttribute> getAllAttributes();
    virtual QVariant getAttribute(const QString &deviceID) const;

protected slots:
    virtual bool setAttribute(const QString &name, const QVariant &value, bool notify);

    void grabLoop();

private:
    cv::VideoCapture *m_capture;

    bool m_stopThreadRequested;

    QMutex m_mutex;

    QList<QSize> m_frameSizes;

    static QMap<int, QString> m_opencvAttributeNames;
};

} // namespace Z3D

#endif // Z3D_CAMERAACQUISITION_PLUGIN___OPENCVVIDEOCAPTURECAMERA_H
