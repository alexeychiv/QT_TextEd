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

    QMenu *menuLanguage;
    QAction *actionEnglish;
    QAction *actionRussian;

    QMenu *menuHelp;
    QAction *actionAbout;

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

public slots:
    void onMenuActionNew();
    void onMenuActionOpen();
    void onMenuActionOpenReadOnly();
    void onMenuActionSave();
    void onMenuActionQuit();

    void onMenuActionEnglish();
    void onMenuActionRussian();

    void onMenuActionAbout();

};
#endif // MAINWINDOW_H
