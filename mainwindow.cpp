#include "mainwindow.h"


//-----------------------------------------------------------------------------------------
//CONSTRUCTOR

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

//-----------------------------------------------------------------------------------------
//DESTRUCTOR

MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------------------
//SETUP UI

void MainWindow::setupUI()
{
    resize(800, 600);
    setWindowTitle("TextEd");

    //MAIN MENU
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 21));

    //FILE MENU
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuFile->setTitle("File");

    actionOpen = new QAction(this);
    actionOpen->setText("Open");

    actionOpenReadOnly = new QAction(this);
    actionOpenReadOnly->setText("Open Read Only");

    actionSave = new QAction(this);
    actionSave->setText("Save");

    actionQuit = new QAction(this);
    actionQuit->setText("Quit");

    menuFile->addAction(actionOpen);
    menuFile->addAction(actionOpenReadOnly);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionQuit);

    //HELP MENU
    menuHelp = new QMenu(menubar);
    menuHelp->setTitle("Help");

    actionAbout = new QAction(this);
    actionAbout->setText("About");

    menuHelp->addAction(actionAbout);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuHelp->menuAction());

    setMenuBar(menubar);

    QWidget::connect(actionOpen, &QAction::triggered, this, &MainWindow::onMenuActionOpen);
    QWidget::connect(actionOpenReadOnly, &QAction::triggered, this, &MainWindow::onMenuActionOpenReadOnly);
    QWidget::connect(actionSave, &QAction::triggered, this, &MainWindow::onMenuActionSave);
    QWidget::connect(actionQuit, &QAction::triggered, this, &MainWindow::onMenuActionQuit);
    QWidget::connect(actionAbout, &QAction::triggered, this, &MainWindow::onMenuActionAbout);

    textEdit = new QPlainTextEdit(this);
    setCentralWidget(textEdit);
}

//-----------------------------------------------------------------------------------------
//UTILS

void MainWindow::loadFile(bool isReadOnly)
{
    QString openFilePath = QFileDialog::getOpenFileName(
                this,
                "Open file",
                QDir::current().path(),
                "Text file (*.txt)"
    );

    qDebug() << openFilePath;

    if (openFilePath.isEmpty())
        return;

    QFile openFile(openFilePath);

    if (openFile.open(QFile::ReadOnly))
    {
        textEdit->setPlainText(QTextStream(&openFile).readAll());

        if (isReadOnly)
        {
            setWindowTitle("TextEd - **READ ONLY** " + QFileInfo(openFilePath).fileName());
            actionSave->setDisabled(true);
            textEdit->setReadOnly(true);
        }
        else
        {
            setWindowTitle("TextEd - " + QFileInfo(openFilePath).fileName());
            actionSave->setDisabled(false);
            textEdit->setReadOnly(false);
        }
    }
}

//-----------------------------------------------------------------------------------------
//SLOTS

void MainWindow::onMenuActionOpen()
{
    loadFile(false);
}

void MainWindow::onMenuActionOpenReadOnly()
{
    loadFile(true);
}

void MainWindow::onMenuActionSave()
{
    QString saveFilePath = QFileDialog::getSaveFileName(
                this,
                "Save file",
                QDir::current().path(),
                "Text file (*.txt)"
    );

    qDebug() << saveFilePath;

    if (saveFilePath.isEmpty())
        return;

    QFile saveFile(saveFilePath);

    if (saveFile.open(QFile::WriteOnly))
    {
        QTextStream(&saveFile) << textEdit->toPlainText();
    }
}

void MainWindow::onMenuActionQuit()
{
    this->close();
}

void MainWindow::onMenuActionAbout()
{
    static QMainWindow* aboutWindow = nullptr;

    if (aboutWindow == nullptr)
    {
        QFile aboutFile(":/about.txt");

        if (aboutFile.open(QFile::ReadOnly))
        {
            if (aboutWindow == nullptr)
            {
                aboutWindow = new QMainWindow(this);
                aboutWindow->setWindowTitle("About TextEd");
                aboutWindow->resize(320, 240);

                QPlainTextEdit* aboutTextEdit = new QPlainTextEdit(aboutWindow);
                aboutTextEdit->setPlainText(QTextStream(&aboutFile).readAll());
                aboutTextEdit->setReadOnly(true);

                aboutWindow->setCentralWidget(aboutTextEdit);
                aboutWindow->show();
                return;
            }
        }
    }
    else
        aboutWindow->show();
}

//-----------------------------------------------------------------------------------------
