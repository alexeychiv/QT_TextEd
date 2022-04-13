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

    //FILE MENU
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuFile->setTitle("File");

    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionOpen->setText("Open");

    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave->setText("Save");

    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);

    //HELP MENU
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuHelp->setTitle("Help");

    actionAbout = new QAction(this);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    actionAbout->setText("About");

    menuHelp->addAction(actionAbout);

    //MAIN MENU
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 21));

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuHelp->menuAction());

    setMenuBar(menubar);

    QWidget::connect(actionOpen, &QAction::triggered, this, &MainWindow::onMenuActionOpen);
    QWidget::connect(actionSave, &QAction::triggered, this, &MainWindow::onMenuActionSave);
    QWidget::connect(actionAbout, &QAction::triggered, this, &MainWindow::onMenuActionAbout);

    textEdit = new QPlainTextEdit(this);
    setCentralWidget(textEdit);
}

void MainWindow::onMenuActionOpen()
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
    }
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

void MainWindow::onMenuActionAbout()
{
    QFile aboutFile(":/about.txt");

    if (aboutFile.open(QFile::ReadOnly))
    {
        QMainWindow* aboutWindow = new QMainWindow(this);
        aboutWindow->setWindowTitle("About TextEd");

        QPlainTextEdit* aboutTextEdit = new QPlainTextEdit(aboutWindow);
        aboutTextEdit->setPlainText(QTextStream(&aboutFile).readAll());

        aboutWindow->setCentralWidget(aboutTextEdit);

        aboutWindow->show();
    }
}

//-----------------------------------------------------------------------------------------
