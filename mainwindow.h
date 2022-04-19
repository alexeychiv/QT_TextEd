#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenuBar *menubar;

    QMenu *menuFile;
    QAction *actionOpen;
    QAction *actionSave;

    QMenu *menuHelp;
    QAction *actionAbout;

    QPlainTextEdit *textEdit;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void showAboutWindow();

public slots:
    void onMenuActionOpen();
    void onMenuActionSave();
    void onMenuActionAbout();

};
#endif // MAINWINDOW_H
