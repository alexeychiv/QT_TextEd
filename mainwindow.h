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
    QAction *actionQuit;

    bool isReadOnlyLoaded;

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

    QPlainTextEdit *textEdit;

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
    void onMenuActionQuit();

    void onMenuActionEnglish();
    void onMenuActionRussian();

    void onMenuActionHotkeysPreset1();
    void onMenuActionHotkeysPreset2();

    void onMenuActionLightTheme();
    void onMenuActionDarkTheme();

    void onMenuActionAbout();

    //EVENTS

    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
