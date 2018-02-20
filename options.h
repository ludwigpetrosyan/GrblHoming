/****************************************************************
 * options.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QSettings>

#include "definitions.h"

#define SETTINGS_INVERSE_X                  "inverse.x"
#define SETTINGS_INVERSE_Y                  "inverse.y"
#define SETTINGS_INVERSE_Z                  "inverse.z"
#define SETTINGS_RESPONSE_WAIT_TIME         "responseWaitTime"
#define SETTINGS_Z_JOG_RATE                 "zJogRate"
#define SETTINGS_ENABLE_DEBUG_LOG           "debugLog"
#define SETTINGS_USE_AGGRESSIVE_PRELOAD     "aggressivePreload"
#define SETTINGS_USE_MM_FOR_MANUAL_CMDS     "useMMForManualCommands"
#define SETTINGS_ABSOLUTE_AFTER_AXIS_ADJ    "absCoordForManualAfterAxisAdj"
#define SETTINGS_Z_RATE_LIMIT               "zRateLimit"
#define SETTINGS_Z_RATE_LIMIT_AMOUNT        "zRateLimitAmount"
#define SETTINGS_XY_RATE_AMOUNT             "xyRateAmount"

#define SETTINGS_FILE_OPEN_DIALOG_STATE     "fileopendialogstate"
#define SETTINGS_NAME_FILTER                "namefilter"
#define SETTINGS_DIRECTORY                  "directory"
#define SETTINGS_PORT                       "port"
#define SETTINGS_PORT_BAUDRATE                       "9600"
#define SETTINGS_PORT_BAUDRATE                       "115200"



namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT
    
public:
    explicit Options(QWidget *parent = 0);
    ~Options();
    void accept();

signals:
    void setSettings();

private slots:
    void toggleUseMm(bool useMm);
    void toggleLimitZRate(bool limitZ);

private:
    Ui::Options *ui;
    //variables
    int settings;

};

#endif // OPTIONS_H
