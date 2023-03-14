/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file
///     @author Gus Grubba <gus@auterion.com>

#include "PowerComponent.h"
#include "PX4AutoPilotPlugin.h"

PowerComponent::PowerComponent(Vehicle* vehicle, AutoPilotPlugin* autopilot, QObject* parent)
    : VehicleComponent(vehicle, autopilot, parent)
    , _name(tr("Power"))
{
}

QString PowerComponent::name(void) const { return _name; }

QString PowerComponent::description(void) const
{
    return tr("Power Setup is used to setup battery parameters as well as advanced settings for propellers.");
}

QString PowerComponent::iconResource(void) const { return "/qmlimages/PowerComponentIcon.png"; }

bool PowerComponent::requiresSetup(void) const { return true; }

bool PowerComponent::setupComplete(void) const
{
    if (!_vehicle->parameterManager()->parameterExists(FactSystem::defaultComponentId, "BAT1_SOURCE")
        || !_vehicle->parameterManager()->parameterExists(FactSystem::defaultComponentId, "BAT1_V_CHARGED")
        || !_vehicle->parameterManager()->parameterExists(FactSystem::defaultComponentId, "BAT1_V_EMPTY")
        || !_vehicle->parameterManager()->parameterExists(FactSystem::defaultComponentId, "BAT1_N_CELLS")) {
        return true;
    }
    return _vehicle->parameterManager()->getParameter(FactSystem::defaultComponentId, "BAT1_SOURCE")->rawValue().toInt()
        == -1
        || (_vehicle->parameterManager()
                    ->getParameter(FactSystem::defaultComponentId, "BAT1_V_CHARGED")
                    ->rawValue()
                    .toFloat()
                != 0.0f
            && _vehicle->parameterManager()
                    ->getParameter(FactSystem::defaultComponentId, "BAT1_V_EMPTY")
                    ->rawValue()
                    .toFloat()
                != 0.0f
            && _vehicle->parameterManager()
                    ->getParameter(FactSystem::defaultComponentId, "BAT1_N_CELLS")
                    ->rawValue()
                    .toInt()
                != 0);
}

QStringList PowerComponent::setupCompleteChangedTriggerList(void) const
{
    return {"BAT1_SOURCE", "BAT1_V_CHARGED", "BAT1_V_EMPTY", "BAT1_N_CELLS"};
}

QUrl PowerComponent::setupSource(void) const { return QUrl::fromUserInput("qrc:/qml/PowerComponent.qml"); }

QUrl PowerComponent::summaryQmlSource(void) const { return QUrl::fromUserInput("qrc:/qml/PowerComponentSummary.qml"); }
