#include "mainwindow.h"

#include <QApplication>
#include <QException>

//-----------------------------------------------------------------------------------------
//CONSTRUCTOR

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      doUseHotkeysPreset2(false),
      aboutWindow(nullptr)
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
    resize(1024, 820);
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
    actionPrint = new QAction(this);
    actionQuit = new QAction(this);

    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionOpenReadOnly);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionPrint);
    menuFile->addAction(actionQuit);

    //LANGUAGE MENU
    menuLanguage = new QMenu(menubar);

    actionEnglish = new QAction(this);
    actionRussian = new QAction(this);

    menuLanguage->addAction(actionEnglish);
    menuLanguage->addAction(actionRussian);

    //HOTKEYS MENU
    menuHotkeys = new QMenu(menubar);

    actionHotkeysPreset1 = new QAction(this);
    actionHotkeysPreset2 = new QAction(this);

    menuHotkeys->addAction(actionHotkeysPreset1);
    menuHotkeys->addAction(actionHotkeysPreset2);

    //THEMES MENU
    menuThemes = new QMenu(menubar);

    actionLightTheme = new QAction(this);
    actionDarkTheme = new QAction(this);

    menuThemes->addAction(actionLightTheme);
    menuThemes->addAction(actionDarkTheme);

    //HELP MENU
    menuHelp = new QMenu(menubar);

    actionAbout = new QAction(this);

    menuHelp->addAction(actionAbout);

    //------------
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuLanguage->menuAction());
    menubar->addAction(menuHotkeys->menuAction());
    menubar->addAction(menuThemes->menuAction());
    menubar->addAction(menuHelp->menuAction());

    setMenuBar(menubar);

    //MDI AREA
    mdiArea = new QMdiArea(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);


    //TOOLBAR
    toolBar = new QToolBar(this);

    actionFont = new QAction(this);

    toolBar->addAction(actionFont);
    addToolBar(Qt::TopToolBarArea, toolBar);

    //CONNECTING SLOTS
    connect(actionNew, &QAction::triggered, this, &MainWindow::onMenuActionNew);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::onMenuActionOpen);
    connect(actionOpenReadOnly, &QAction::triggered, this, &MainWindow::onMenuActionOpenReadOnly);
    connect(actionSave, &QAction::triggered, this, &MainWindow::onMenuActionSave);
    connect(actionPrint, &QAction::triggered, this, &MainWindow::onMenuActionPrint);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::onMenuActionQuit);

    connect(actionEnglish, &QAction::triggered, this, &MainWindow::onMenuActionEnglish);
    connect(actionRussian, &QAction::triggered, this, &MainWindow::onMenuActionRussian);

    connect(actionHotkeysPreset1, &QAction::triggered, this, &MainWindow::onMenuActionHotkeysPreset1);
    connect(actionHotkeysPreset2, &QAction::triggered, this, &MainWindow::onMenuActionHotkeysPreset2);

    connect(actionLightTheme, &QAction::triggered, this, &MainWindow::onMenuActionLightTheme);
    connect(actionDarkTheme, &QAction::triggered, this, &MainWindow::onMenuActionDarkTheme);

    connect(actionAbout, &QAction::triggered, this, &MainWindow::onMenuActionAbout);

    connect(actionFont, &QAction::triggered, this, &MainWindow::onToolbarActionFont);
    //-------------
    setElementsStrings();

    onMenuActionLightTheme();
}

//-----------------------------------------------------------------------------------------
//UTILS

void MainWindow::loadFile(const bool isReadOnly)
{
    QString openFilePath = QFileDialog::getOpenFileName(
                this,
                isReadOnly? tr("Open read only file") : tr("Open file"),
                QDir::current().path(),
                tr("Text file (*.txt)")
    );

    if (openFilePath.isEmpty())
        return;

    TextDocumentSubwindow* newTextDocumentSubwindow = new TextDocumentSubwindow(mdiArea, openFilePath, isReadOnly);
    mdiArea->addSubWindow(newTextDocumentSubwindow);
    newTextDocumentSubwindow->show();
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
    actionPrint->setText(tr("Print"));
    actionQuit->setText(tr("Quit"));

    menuLanguage->setTitle(tr("Language"));
    actionEnglish->setText(tr("English"));
    actionRussian->setText(tr("Russian"));

    menuHotkeys->setTitle(tr("Hotkeys Setup"));
    actionHotkeysPreset1->setText(tr("Preset 1"));
    actionHotkeysPreset2->setText(tr("Preset 2"));

    menuThemes->setTitle(tr("Themes"));
    actionLightTheme->setText(tr("Light"));
    actionDarkTheme->setText(tr("Dark"));

    menuHelp->setTitle(tr("Help"));
    actionAbout->setText(tr("About"));

    actionFont->setText(tr("Font"));
}

void MainWindow::processEventByPreset1(QKeyEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier)
        switch (event->key())
        {
            case Qt::Key_N:
                qDebug("CTRL+N");
                onMenuActionNew();
            break;
            case Qt::Key_O:
                if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
                {
                    qDebug("CTRL+SHIFT+O");
                    onMenuActionOpenReadOnly();
                }
                else
                {
                    qDebug("CTRL+O");
                    onMenuActionOpen();
                }
            break;
            case Qt::Key_S:
                qDebug("CTRL+S");
                onMenuActionSave();
            break;
        }
}

void MainWindow::processEventByPreset2(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_F2:
            qDebug("F2");
            onMenuActionNew();
            break;
        case Qt::Key_F3:
            qDebug("F3");
            onMenuActionOpen();
            break;
        case Qt::Key_F4:
            qDebug("F4");
            onMenuActionOpenReadOnly();
            break;
        case Qt::Key_F5:
            qDebug("F5");
            onMenuActionSave();
            break;
    }
}

//-----------------------------------------------------------------------------------------
//SLOTS

void MainWindow::onMenuActionNew()
{
    TextDocumentSubwindow* newTextDocumentSubwindow = new TextDocumentSubwindow(mdiArea);
    mdiArea->addSubWindow(newTextDocumentSubwindow);
    newTextDocumentSubwindow->show();
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
    TextDocumentSubwindow* currentActiveSubwindow = qobject_cast<TextDocumentSubwindow*>(mdiArea->activeSubWindow());

    if (!currentActiveSubwindow)
        return;

    if (currentActiveSubwindow->isReadOnlyState())
        return;

    QString saveFilePath = QFileDialog::getSaveFileName(
                this,
                tr("Save file"),
                QDir::current().path(),
                tr("Text file (*.txt)")
    );

    if (saveFilePath.isEmpty())
        return;

    currentActiveSubwindow->saveToFile(saveFilePath);
}

void MainWindow::onMenuActionPrint()
{
    TextDocumentSubwindow* currentActiveSubwindow = qobject_cast<TextDocumentSubwindow*>(mdiArea->activeSubWindow());
    if (currentActiveSubwindow)
        currentActiveSubwindow->print();
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

void MainWindow::onMenuActionHotkeysPreset1()
{
    doUseHotkeysPreset2 = false;
}

void MainWindow::onMenuActionHotkeysPreset2()
{
    doUseHotkeysPreset2 = true;
}

void MainWindow::onMenuActionLightTheme()
{
    setStyleSheet(
                "QWidget {"
                "   color: black;"
                "   background-color: white;"
                "}"
    );
}

void MainWindow::onMenuActionDarkTheme()
{
    setStyleSheet(
                "QWidget {"
                "   color: white;"
                "   background-color: black;"
                "}"
    );
}

void MainWindow::onMenuActionAbout()
{
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

void MainWindow::onToolbarActionFont()
{
    TextDocumentSubwindow* currentActiveSubwindow = qobject_cast<TextDocumentSubwindow*>(mdiArea->activeSubWindow());
    if (!currentActiveSubwindow)
        return;

    QFont font = currentActiveSubwindow->getFont();
    QFontDialog fontDialog(font, this);

    bool b[] = {true};
    font = fontDialog.getFont(b);
    if (b[0])
    {
        currentActiveSubwindow->setFont(font);
    }

}

//-----------------------------------------------------------------------------------------
//EVENTS

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (doUseHotkeysPreset2)
        processEventByPreset2(event);
    else
        processEventByPreset1(event);
}

//-----------------------------------------------------------------------------------------
