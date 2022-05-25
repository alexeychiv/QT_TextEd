#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <QTranslator>

#include <QMdiArea>
#include "textdocumentsubwindow.h"

#include <QToolBar>
#include <QFontDialog>
#include <QTextCharFormat>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTranslator translator;

    QMenuBar *menubar;

    QMenu *menuFile;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpenReadOnly;
    QAction *actionSave;
    QAction *actionPrint;
    QAction *actionQuit;

    QMenu *menuLanguage;
    QAction *actionEnglish;
    QAction *actionRussian;

    bool doUseHotkeysPreset2;

    QMenu *menuHotkeys;
    QAction *actionHotkeysPreset1;
    QAction *actionHotkeysPreset2;

    QMenu *menuThemes;
    QAction *actionLightTheme;
    QAction *actionDarkTheme;

    QMenu *menuHelp;
    QAction *actionAbout;

    QMainWindow* aboutWindow;

    QMdiArea* mdiArea;

    QToolBar* toolBar;
    QAction* actionFont;
    QAction* actionBold;
    QAction* actionItalic;
    QAction* actionAlignLeft;
    QAction* actionAlignCenter;
    QAction* actionAlignRight;
    QAction* actionCopyFormat;
    QAction* actionApplyFormat;
    QAction* actionInsertDateTime;


    QTextCharFormat formatBuffer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    //UTILS
    void loadFile(const bool isReadOnly);
    void retranslate(const QString& languageCode);
    void setElementsStrings();

    void processEventByPreset1(QKeyEvent *event);
    void processEventByPreset2(QKeyEvent *event);

public slots:
    void onMenuActionNew();
    void onMenuActionOpen();
    void onMenuActionOpenReadOnly();
    void onMenuActionSave();
    void onMenuActionPrint();
    void onMenuActionQuit();

    void onMenuActionEnglish();
    void onMenuActionRussian();

    void onMenuActionHotkeysPreset1();
    void onMenuActionHotkeysPreset2();

    void onMenuActionLightTheme();
    void onMenuActionDarkTheme();

    void onMenuActionAbout();

    void onToolbarActionFont();
    void onToolbarActionBold();
    void onToolbarActionItalic();
    void onToolbarActionAlignLeft();
    void onToolbarActionAlignCenter();
    void onToolbarActionAlignRight();
    void onToolbarActionCopyFormat();
    void onToolbarActionApplyFormat();
    void onToolbarActionInstertDateTime();

    //EVENTS

    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
