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

#pragma once

#include "zcameraacquisition_global.h"
#include "zcamerainterface.h"

#include <QtProperty>
#include <QtStringPropertyManager>

#include <QWidget>

namespace Z3D
{

namespace Ui {
class ZCameraSettingsWidget;
}

class Z3D_CAMERAACQUISITION_SHARED_EXPORT ZCameraSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZCameraSettingsWidget(ZCameraInterface::WeakPtr camera, QWidget *parent = 0);
    ~ZCameraSettingsWidget();

protected slots:
    void propertyChanged(QtProperty *property);
    void updateProperties();

    void onCameraAttributeChanged(QString name, QVariant value);

private:
    Ui::ZCameraSettingsWidget *ui;

    ZCameraInterface::WeakPtr m_camera;

    QMap<QString, QtProperty*> m_propertiesList;

    QtAbstractPropertyBrowser *m_propertyBrowser;
    QtGroupPropertyManager *m_groupManager;
    QtBoolPropertyManager *m_boolPropertyManager;
    QtStringPropertyManager *m_stringPropertyManager;
    QtIntPropertyManager *m_intPropertyManager;
    QtStringPropertyManager *m_longPropertyManager;
    QtDoublePropertyManager *m_floatPropertyManager;
    QtEnumPropertyManager *m_enumPropertyManager;
    QtBoolPropertyManager *m_commandPropertyManager;
};

} // namespace Z3D
