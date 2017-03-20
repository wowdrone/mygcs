/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/



/// @file
///     @brief Mixers Config Qml Controller
///     @author

#ifndef MixersComponentController_H
#define MixersComponentController_H

#include <QTimer>

#include "FactPanelController.h"
#include "UASInterface.h"
#include "QGCLoggingCategory.h"
#include "AutoPilotPlugin.h"
#include <FactMetaData.h>
#include "MixersManager.h"

Q_DECLARE_LOGGING_CATEGORY(MixersComponentControllerLog)
Q_DECLARE_LOGGING_CATEGORY(MixersComponentControllerVerboseLog)

namespace Ui {
    class MixersComponentController;
}


class MixersComponentController : public FactPanelController
{
    Q_OBJECT

public:
    MixersComponentController(void);
    ~MixersComponentController();

    Q_PROPERTY(QQuickItem* mixersManagerStatusText   MEMBER _mixersManagerStatusText      NOTIFY mixersManagerStatusTextChanged)

    Q_PROPERTY(QmlObjectListModel*  mixersList          MEMBER _mixers              CONSTANT)
    Q_PROPERTY(QmlObjectListModel*  groupsList          MEMBER _groups              CONSTANT)
    Q_PROPERTY(unsigned int         selectedGroup       MEMBER _selectedGroup       NOTIFY selectedGroupChanged)

    Q_INVOKABLE void guiUpdated(void);

    unsigned int groupValue(void);
    unsigned int mixerIndexValue(void);
    unsigned int submixerIndexValue(void);
    float        parameterValue(void);
        
    
signals:
    void mixersManagerStatusTextChanged(void);

    void selectedGroupChanged(unsigned int groupValue);
    void parameterValueChanged(float paramValue);
        
//    /// Signalled to QML to indicate reboot is required
//    void functionMappingChangedAPMReboot(void);

private slots:
//    void _rcChannelsChanged(int channelCount, int pwmValues[Vehicle::cMaxRcChannels]);
    void _updateMixers(bool dataReady);
    void _updateMixersManagerStatus(MixersManager::MIXERS_MANAGER_STATUS_e mixerManagerStatus);
    void _updateSelectedGroup(unsigned int group);

private:    
    static const int _updateInterval;   ///< Interval for ui update timer

    QQuickItem* _mixersManagerStatusText;

    QmlObjectListModel* _mixers;
    QmlObjectListModel* _groups;
    unsigned int        _selectedGroup;

//#ifdef UNITTEST_BUILD
//    // Nasty hack to expose controller to unit test code
//    static RadioComponentController*    _unitTestController;
//#endif
};

#endif // MixersComponentController_H
