/*
    Copyright (C) 2019 - 2020 Andrea Zanellato <redtid3@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For a full copy of the GNU General Public License see the LICENSE file
*/
#pragma once

#include "src/settings.h"
#include <QMainWindow>
#include <array>
#include <jack/jack.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ServiceControl;
class ServiceLogger;
class QRadioButton;
class QSystemTrayIcon;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QSystemTrayIcon* icon, QWidget* parent = nullptr);
    ~MainWindow();

    void addXrun();

private:
    void closeEvent(QCloseEvent*);

    void createTrayIcon();

    void loadSettings();
    void saveSettings();

    void onClickedCancel();
    void onClickedReset();
    void onClickedSave();
    void setEnabledButtons(bool enable);
    void onSettingsChanged();

    void onAboutToQuit();

    void resetJackStatus();
    void updateJackStatus();

    void onA2jActiveStateChanged();
    void onA2jStartStop();

    void onJackActiveStateChanged();
    void onJackStartStop();

    void updateJackSettingsUI();
    void updateDriverSettingsUI();

    void updateJackSettings();
    void updateDriverSettings();

    void setOsPixmap(const QString& osName);

    void enumerateProfiles();

    void createAutostartFile();
    void deleteAutostartFile();

    Ui::MainWindow* ui;

    QAction* actA2j;
    QAction* actJack;
    QAction* actQuit;
    QMenu* mnuTray;
    QSystemTrayIcon* icoTray;
    ServiceLogger* txtLog;

    std::array<QRadioButton*, 2> grpClockSource;
    std::array<QRadioButton*, 5> grpAutoConnect;

    ServiceControl* jackService;
    ServiceControl* a2jService;

    jack_client_t* jackClient;
    int xRunCount;

    typedef QSharedPointer<jack::Settings> settingsPtr;
    settingsPtr settings;

    QString currProfileName;
};
