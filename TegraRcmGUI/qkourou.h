#ifndef QKOUROU_H
#define QKOUROU_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "kourou/kourou.h"
#include "tegrarcmgui.h"

typedef enum _qKourouAction : int
{
    INIT_DEVICE,
    AUTO_INJECT,
    PAYLOAD_INJECT

} qKourouAction;


class TegraRcmGUI;

///
/// \brief The QKourou class is a Qt thread safe reimplemented class of Kourou class, for TegraRcmGUI
///

class QKourou : public QWidget {
    Q_OBJECT

public:
    QKourou(QWidget *parent, Kourou* device, TegraRcmGUI* gui);
    bool isLocked() { return m_locked; }
    QByteArray ariane_bin;
    bool autoLaunchAriane = true;
    bool autoInjectPayload = false;
    bool arianeIsLoading = false;

private:
    QWidget *parent;
    Kourou *m_device;
    TegraRcmGUI *m_gui;
    bool m_locked = false;
    bool m_force_lock = false;
    bool m_askForDriverInstall = true;
    bool m_APX_device_reconnect = true;    
    std::string tmp_string;
    QByteArray m_hekate_ini;

    void hack(const char* payload_path, u8 *payload_buff, u32 buff_size);
    void setLockEnabled(bool enable) { m_locked = enable; }
    bool waitUntilUnlock(uint timeout_s = 10);
    bool waitUntilRcmReady(uint timeout_s = 10);
    bool waitUntilInit(uint timeout_s = 10);
    bool rebootToRcm();
    DWORD autoInject();

public slots:
    void initDevice(bool silent, KLST_DEVINFO_HANDLE deviceInfo = nullptr);
    void getDeviceInfo();
    void hack(const char* payload_path);
    void hack(u8 *payload_buff, u32 buff_size);
    void initNoDriverDeviceLookUpLoop();
    void noDriverDeviceLookUp();
    void setAutoRcmEnabled(bool state);

signals:
    void clb_deviceInfo(UC_DeviceInfo di);
    void clb_error(int error);
    void clb_deviceStateChange();
    void clb_finished(int res);
    void clb_driverMissing();
    void pushMessage(QString);
};

#endif // QKOUROU_H
