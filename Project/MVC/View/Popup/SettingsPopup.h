#ifndef SETTINGSPOPUP_H
#define SETTINGSPOPUP_H

#include "Popup.h"

class SettingsPopup : public Popup
{
    Q_OBJECT
public:
    SettingsPopup(QWidget *parent = nullptr);
    ~SettingsPopup();
};

#endif // SETTINGSPOPUP_H
