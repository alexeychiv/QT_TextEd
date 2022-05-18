#ifndef TEXTDOCUMENTSUBWINDOW_H
#define TEXTDOCUMENTSUBWINDOW_H

#include <QMdiSubWindow>
#include <QTextEdit>

#include <QPrinter>
#include <QPrintDialog>

#include <QFont>

class TextDocumentSubwindow : public QMdiSubWindow
{
    Q_OBJECT

    bool isReadOnly;
    QTextEdit* textEdit;

public:
    explicit TextDocumentSubwindow(QWidget *parent);
    explicit TextDocumentSubwindow(QWidget *parent, const QString& openFilePath, bool isReadOnly);

    void setupUI();

    bool isReadOnlyState() const { return isReadOnly; }

    void openFile(const QString& openFilePath);
    void openFileReadOnly(const QString& openFilePath);
    void saveToFile(const QString& saveFilePath);
    void print();

    void setFont(const QFont& newFont) { textEdit->setFont(newFont); }
    const QFont& getFont() const { return textEdit->font(); }
};

#endif // TEXTDOCUMENTSUBWINDOW_H
