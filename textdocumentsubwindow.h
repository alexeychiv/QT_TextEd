#ifndef TEXTDOCUMENTSUBWINDOW_H
#define TEXTDOCUMENTSUBWINDOW_H

#include <QMdiSubWindow>
#include <QTextEdit>

#include <QPrinter>
#include <QPrintDialog>

#include <QFont>
#include <QTextCharFormat>

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

    QTextCharFormat getFormatFromSelection() { return textEdit->textCursor().charFormat(); }
    void applyFormatToSelection(const QTextCharFormat& newFormat) { textEdit->textCursor().setCharFormat(newFormat); }

    void setAligment(Qt::AlignmentFlag alignmentFlag)
    {
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(alignmentFlag);
        cursor.mergeBlockFormat(textBlockFormat);
        textEdit->setTextCursor(cursor);
    }
};

#endif // TEXTDOCUMENTSUBWINDOW_H
