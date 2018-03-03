/****************************************************************
 * mainwindow.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include <QCloseEvent>
#include <QItemDelegate>
#include <QListView>
#include "about.h"
#include "definitions.h"
#include "grbldialog.h"
#include "options.h"
//#include "filesender.h"
#include "timer.h"
#include "positem.h"
#include "gcode.h"
#include "renderarea.h"

#define COMPANY_NAME "zapmaker"
#define APPLICATION_NAME "GrblController"
#define DOMAIN_NAME "org.zapmaker"

#define TAB_AXIS_INDEX          0
#define TAB_VISUALIZER_INDEX    1


/* testing optimizing scrollbar, doesn't work right
class MyItemDelegate : public QItemDelegate
{
private:
    int width;
    QAbstractItemView *parentWidget;

public:

    MyItemDelegate(QAbstractItemView *p) : parentWidget(p) {}

    void setWidth(int w)
    {
        width = w;
    }

    void drawDisplay(QPainter *painter,const
    QStyleOptionViewItem &option,const QRect &rect,const QString &text) const{

        QRect tempRect(rect);
        tempRect.setWidth(parentWidget->width());
        QItemDelegate::drawDisplay(painter,option,tempRect,text);

    }

    QSize sizeHint(const QStyleOptionViewItem & option, const
    QModelIndex & index ) const  {

        QListView *list = qobject_cast<QListView*>(parentWidget);
        QSize newSize(QItemDelegate::sizeHint(option,index));
        if( list ) newSize.setWidth( width );
        return newSize;
    }
};
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

    //variables
    int delete_nr;

signals:
    //threads
    //void openPort(QString port);
    void openPort(QString port, int baudrate = 115200);
    void closePort(bool reopen);
    void shutdown();
    void sendGcode(QString line, bool recordResponseOnFail = false, int waitCount = SHORT_WAIT_SEC);
    void sendFile(QString path);
    void gotoXYZ(QString line);
    void axisAdj(char axis, float coord, bool inv, bool absoluteAfterAxisAdj);
    void setResponseWait(int waitTime, double zJogRate, bool useMm, bool zRateLimit, double zRateLimitAmount, double xyRateAmount, bool useAggressivePreload);
    void setProgress(int percent);
    void setRuntime(QString runtime);
    void sendSetHome();
    void sendSetZ0();
    void sendSetXY0();
    void sendSetProbe();
    void sendGrblReset();
    void sendGrblUnlock();
    void goToHome();
    void goToZHome();
    void setItems(QList<PosItem>);
    void setLabLines(int numLines);

private slots:
    //buttons
    void openPort();
    void setGRBL();
        //Adjust
    void decX();
    void decY();
    void decZ();
    void incX();
    void incY();
    void incZ();
    void setHome();
    void setZ0();
    void setXY0();
    void setProbe();
        //manual
    void gotoXYZ();
        //send Gcode
    void begin();
    void openFile();
    void stop();
    void stopSending();
    //
    void portIsOpen(bool sendCode);
    void portIsClosed(bool reopen);
    void adjustedAxis();

    //check boxes
    void toggleSpindle();
    void toggleRestoreAbsolute();

    //communications
        //options
    void setSettings();
        //thread
    void receiveList(QString msg);
    void receiveListFull(QStringList list);
    void receiveListOut(QString msg);
    void receiveMsg(QString msg);
    //menu bar
    void getOptions();
    void showAbout();
    void enableGrblDialogButton();
    void grblReset();
    void grblUnlock();
    void updateCoordinates(Coord3D machineCoord, Coord3D workCoord);
    void goHomeSafe();
    void goZHomeSafe();

private:
    // enums
    enum
    {
        NO_ITEM = 0,
        X_ITEM,
        Y_ITEM,
        I_ITEM,
        J_ITEM,
    };
    //objects
    Ui::MainWindow *ui;
    //FileSender fileSender;
    //QThread fileSenderThread;
    GCode gcode;
    QThread gcodeThread;
    Timer timer;
    QThread timerThread;

    //variables
    bool invX;
    bool invY;
    bool invZ;
    QString styleSheet;
    QString directory;
    QString nameFilter;
    QString lastOpenPort;
    QString lastOpenPortBR;
    QByteArray fileOpenDialogState;
    int waitTime;
    double zJogRate;
    Coord3D machineCoordinates;
    Coord3D workCoordinates;
    bool absoluteAfterAxisAdj;
    bool useMm;
    bool zRateLimiting;
    double zRateLimitAmount;
    double xyRateAmount;
    bool useAggressivePreload;
    bool checkLogWrite;
    QTime scrollStatusTimer;
    QList<PosItem> posList;
  
    //methods
    int SendJog(QString strline);
    void readSettings();
    void writeSettings();
    void addToStatusList(bool in, QString msg);
    void addToStatusList(QStringList& list);
    void disableAllButtons();
    void openPortCtl(bool reopen);
    void resetProgress();
    void refreshLcd();
    void lcdDisplay(char axis, bool workCoord, float value);
    void updateSettingsFromOptionDlg(QSettings& settings);
    void doScroll();
    int computeListViewMinimumWidth(QAbstractItemView* view);
    void preProcessFile(QString filepath);
    bool processGCode(QString inputLine, double& x, double& y, double& i, double& j, bool& arc, bool& cw, bool& mm, int& g);
    double decodeLineItem(const QString& item, const int next, bool& valid, int& nextIsValue);
    double decodeDouble(QString value, bool& valid);
};


#endif // MAINWINDOW_H
