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
    textEdit = new QTextEdit(this);
    setWidget(textEdit);
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
        textEdit->setPlainText(QTextStream(&openFile).readAll());
        textEdit->setReadOnly(false);
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
        textEdit->setPlainText(QTextStream(&openFile).readAll());
        textEdit->setReadOnly(true);
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
        QTextStream(&saveFile) << textEdit->toPlainText();
    }
}

void TextDocumentSubwindow::print()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    textEdit->document()->print(&printer);
}
