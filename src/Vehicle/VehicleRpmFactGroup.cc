/****************************************************************************
 *
 * (c) 2009-2023 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehicleSetpointFactGroup.h"
#include "Vehicle.h"

//const char* VehicleRpmFactGroup::_rpmFactName =      "rpm";
const char* VehicleRpmFactGroup::_rpm1FactName =      "rpm1";
const char* VehicleRpmFactGroup::_rpm2FactName =      "rpm2";
const char* VehicleRpmFactGroup::_rpm3FactName =      "rpm3";
const char* VehicleRpmFactGroup::_rpm4FactName =      "rpm4";

VehicleRpmFactGroup::VehicleRpmFactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/RpmFact.json", parent)
  //  , _rpmFact    (0, _rpmFactName,     FactMetaData::valueTypeDouble)
    , _rpm1Fact    (0, _rpm1FactName,     FactMetaData::valueTypeDouble)
    , _rpm2Fact    (0, _rpm2FactName,     FactMetaData::valueTypeDouble)
    , _rpm3Fact    (0, _rpm3FactName,     FactMetaData::valueTypeDouble)
    , _rpm4Fact    (0, _rpm4FactName,     FactMetaData::valueTypeDouble)
{
  //  _addFact(&_rpmFact,       _rpmFactName);
    _addFact(&_rpm1Fact,       _rpm1FactName);
    _addFact(&_rpm2Fact,       _rpm2FactName);
    _addFact(&_rpm3Fact,       _rpm3FactName);
    _addFact(&_rpm4Fact,       _rpm4FactName);

    // Start out as not available "--.--"
   // _rpmFact.setRawValue      (qQNaN());
    _rpm1Fact.setRawValue      (qQNaN());
    _rpm2Fact.setRawValue      (qQNaN());
    _rpm3Fact.setRawValue      (qQNaN());
    _rpm4Fact.setRawValue      (qQNaN());
}

void VehicleRpmFactGroup::handleMessage(Vehicle* /* vehicle */, mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_RAW_RPM:
        _handleRawRPM(message);
        break;
    default:
        break;
    }
}

void VehicleRpmFactGroup::_handleRawRPM(mavlink_message_t& message)
{
    mavlink_raw_rpm_t raw_rpm;
    mavlink_msg_raw_rpm_decode(&message, &raw_rpm);
    //rpm()->setRawValue(raw_rpm.frequency);
    switch (raw_rpm.index) {
        case 0:
            rpm1()->setRawValue(raw_rpm.frequency);
            break;
        case 1:
            rpm2()->setRawValue(raw_rpm.frequency);
            break;
        case 2: 
            rpm3()->setRawValue(raw_rpm.frequency);
            break;
        case 3: 
            rpm4()->setRawValue(raw_rpm.frequency);
            break;
        default:
            break;

    }
    _setTelemetryAvailable(true);
}

