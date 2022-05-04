#include "textdocumentsubwindow.h"

#include <QFile>


TextDocumentSubwindow::TextDocumentSubwindow(QWidget *parent)
    :
      QMdiSubWindow(parent),
      isReadOnly(false)
{
    setupUI();
}

TextDocumentSubwindow::TextDocumentSubwindow(QWidget *parent, const QString &openFilePath, bool isReadOnly)
    :
      QMdiSubWindow(parent),
      isReadOnly(false)
{
    setupUI();

    if (isReadOnly)
        openFileReadOnly(openFilePath);
    else
        openFile(openFilePath);
}

void TextDocumentSubwindow::setupUI()
{
    resize(320, 240);
    setWindowTitle(tr("New"));
    plainTextEdit = new QPlainTextEdit(this);
    setWidget(plainTextEdit);
}

void TextDocumentSubwindow::openFile(const QString &openFilePath)
{
    if (openFilePath.isEmpty())
        return;

    QFile openFile(openFilePath);

    if (openFile.open(QFile::ReadOnly))
    {
        isReadOnly = false;
        setWindowTitle(openFilePath);
        plainTextEdit->setPlainText(QTextStream(&openFile).readAll());
        plainTextEdit->setReadOnly(false);
    }
}

void TextDocumentSubwindow::openFileReadOnly(const QString &openFilePath)
{
    if (openFilePath.isEmpty())
        return;

    QFile openFile(openFilePath);

    if (openFile.open(QFile::ReadOnly))
    {
        isReadOnly = true;
        setWindowTitle("**READ ONLY** " + openFilePath);
        plainTextEdit->setPlainText(QTextStream(&openFile).readAll());
        plainTextEdit->setReadOnly(true);
    }
}

void TextDocumentSubwindow::saveToFile(const QString &saveFilePath)
{
    if (saveFilePath.isEmpty())
        return;

    if (isReadOnly)
        return;

    QFile saveFile(saveFilePath);

    if (saveFile.open(QFile::WriteOnly))
    {
        setWindowTitle(saveFilePath);
        QTextStream(&saveFile) << plainTextEdit->toPlainText();
    }
}
