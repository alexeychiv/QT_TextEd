#include "mainwindow.h"

#include <QApplication>


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
    menubar->setGeometry(QRect(0, 0, 800, 21));

    //FILE MENU
    menuFile = new QMenu(menubar);

    actionNew = new QAction(this);
    actionOpen = new QAction(this);
    actionOpenReadOnly = new QAction(this);
    actionSave = new QAction(this);
    actionQuit = new QAction(this);

    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionOpenReadOnly);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionQuit);

    //LANGUAGE MENU
    menuLanguage = new QMenu(menubar);

    actionEnglish = new QAction(this);
    actionRussian = new QAction(this);

    menuLanguage->addAction(actionEnglish);
    menuLanguage->addAction(actionRussian);

    //HELP MENU
    menuHelp = new QMenu(menubar);

    actionAbout = new QAction(this);

    menuHelp->addAction(actionAbout);

    //------------
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuLanguage->menuAction());
    menubar->addAction(menuHelp->menuAction());

    setMenuBar(menubar);

    QWidget::connect(actionNew, &QAction::triggered, this, &MainWindow::onMenuActionNew);
    QWidget::connect(actionOpen, &QAction::triggered, this, &MainWindow::onMenuActionOpen);
    QWidget::connect(actionOpenReadOnly, &QAction::triggered, this, &MainWindow::onMenuActionOpenReadOnly);
    QWidget::connect(actionSave, &QAction::triggered, this, &MainWindow::onMenuActionSave);
    QWidget::connect(actionQuit, &QAction::triggered, this, &MainWindow::onMenuActionQuit);

    QWidget::connect(actionEnglish, &QAction::triggered, this, &MainWindow::onMenuActionEnglish);
    QWidget::connect(actionRussian, &QAction::triggered, this, &MainWindow::onMenuActionRussian);

    QWidget::connect(actionAbout, &QAction::triggered, this, &MainWindow::onMenuActionAbout);

    textEdit = new QPlainTextEdit(this);
    setCentralWidget(textEdit);
    setElementsStrings();
}

//-----------------------------------------------------------------------------------------
//UTILS

void MainWindow::loadFile(const bool isReadOnly)
{
    QString openFilePath = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                QDir::current().path(),
                tr("Text file (*.txt)")
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
            setWindowTitle(tr("TextEd - **READ ONLY** ") + QFileInfo(openFilePath).fileName());
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

void MainWindow::retranslate(const QString &languageCode)
{
    static QString currentLanguageCode = "";

    if (currentLanguageCode == languageCode)
        return;

    currentLanguageCode = languageCode;

    if (languageCode == "en")
        qApp->removeTranslator(&translator);
    else
    {
        if (!translator.load(":/QtLanguage_" + languageCode))
           qDebug("ERROR: unable to load translation!");
        qApp->installTranslator(&translator);
    }

    setElementsStrings();
}

void MainWindow::setElementsStrings()
{
    menuFile->setTitle(tr("File"));
    actionNew->setText(tr("New"));
    actionOpen->setText(tr("Open"));
    actionOpenReadOnly->setText(tr("Open Read Only"));
    actionSave->setText(tr("Save"));
    actionQuit->setText(tr("Quit"));
    menuLanguage->setTitle(tr("Language"));
    actionEnglish->setText(tr("English"));
    actionRussian->setText(tr("Russian"));
    menuHelp->setTitle(tr("Help"));
    actionAbout->setText(tr("About"));
}

//-----------------------------------------------------------------------------------------
//SLOTS

void MainWindow::onMenuActionNew()
{
    setWindowTitle("TextEd");
    actionSave->setDisabled(false);
    textEdit->setReadOnly(false);
    textEdit->setPlainText("");
}

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
                tr("Save file"),
                QDir::current().path(),
                tr("Text file (*.txt)")
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

void MainWindow::onMenuActionEnglish()
{
    retranslate("en");
}

void MainWindow::onMenuActionRussian()
{
    retranslate("ru");
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
                aboutWindow->setWindowTitle(tr("About TextEd"));
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
