#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QString>

class SettingManager
{

public:
    SettingManager();

private:
    QString dbname;

    void loadSettings();
};

#endif // SETTINGMANAGER_H
