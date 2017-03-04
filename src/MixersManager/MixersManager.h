/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#ifndef MixersManager_H
#define MixersManager_H

#include <QObject>
#include <QLoggingCategory>
#include <QThread>
#include <QMutex>
#include <QTimer>

#include "QGCMAVLink.h"
#include "QGCLoggingCategory.h"
#include "LinkInterface.h"

class Vehicle;

Q_DECLARE_LOGGING_CATEGORY(MixersManagerLog)

class MixersManager : public QObject
{
    Q_OBJECT
    
public:
    MixersManager(Vehicle* vehicle);
    ~MixersManager();
    
    bool inProgress(void);

    bool requestMixerCount(unsigned int group);
    bool requestSubmixerCount(unsigned int group, unsigned int mixer);
    bool requestMixerType(unsigned int group, unsigned int mixer, unsigned int submixer);
    bool requestParameterCount(unsigned int group, unsigned int mixer, unsigned int submixer);
    bool requestParameter(unsigned int group, unsigned int mixer, unsigned int submixer, unsigned int parameter);
    bool requestMixerAll(unsigned int group);
    bool requestMissingData(unsigned int group);
    bool requestConnectionCount(unsigned int group, unsigned int mixer, unsigned int submixer, unsigned connType);
    bool requestConnection(unsigned int group, unsigned int mixer, unsigned int submixer, unsigned connType, unsigned conn);

    // These values are public so the unit test can set appropriate signal wait times
    static const int _ackTimeoutMilliseconds = 1000;
    static const int _maxRetryCount = 5;
    
signals:
    void newMixerItemsAvailable(void);
    
private slots:
    void _mavlinkMessageReceived(const mavlink_message_t& message);
    void _ackTimeout(void);

private:
    typedef enum {
        AckNone,            ///< State machine is idle
        AckMixersCount,     ///< MIXER_DATA mixers count message expected
        AckSubmixersCount,  ///< MIXER_DATA submixers count message expected
        AckMixerType,       ///< MIXER_DATA mixer type value message expected
        AckParameterCount,  ///< MIXER_DATA parameter value message expected
        AckGetParameter,    ///< MIXER_DATA parameter value message expected
        AckSetParameter,    ///< MIXER_DATA parameter value message expected
        AckAll,             ///< ALL mixer data expected
    } AckType_t;


private:
    Vehicle*            _vehicle;
    LinkInterface*      _dedicatedLink;

    QList<mavlink_mixer_data_t*> _mixerDataMessages;
    QTimer*             _ackTimeoutTimer;
    AckType_t           _expectedAck;
    int                 _retryCount;
    bool                _getMissing;
    unsigned int        _requestGroup;

    void _startAckTimeout(AckType_t ack);

    //* Return index of matching message,group,mixer,submixer and parameter etc..*/
    int _getMessageOfKind(const mavlink_mixer_data_t* data);

    //* collect mixer data into a list.  Only one list entry per group, data_type, mixer, submixer etc...*/
    bool _collectMixerData(const mavlink_mixer_data_t* data);

    //* Request a missing messages. true if there is missing data */
    bool _requestMissingData(unsigned int group);


//    bool _checkForExpectedAck(AckType_t receivedAck);

//    void _handleMissionAck(const mavlink_message_t& message);

//    bool        _readTransactionInProgress;
//    bool        _writeTransactionInProgress;
//    QList<int>  _itemIndicesToRead;     ///< List of mission items which still need to be requested from vehicle
    
//    QMutex _dataMutex;
    
//    QList<MissionItem*> _missionItems;
};

#endif
