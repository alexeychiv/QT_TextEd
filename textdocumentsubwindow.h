#ifndef TEXTDOCUMENTSUBWINDOW_H
#define TEXTDOCUMENTSUBWINDOW_H

#include <QMdiSubWindow>
#include <QPlainTextEdit>


class TextDocumentSubwindow : public QMdiSubWindow
{
    Q_OBJECT

    bool isReadOnly;
    QPlainTextEdit* plainTextEdit;

public:
    explicit TextDocumentSubwindow(QWidget *parent);
    explicit TextDocumentSubwindow(QWidget *parent, const QString& openFilePath, bool isReadOnly);

    void setupUI();

    bool isReadOnlyState() const { return isReadOnly; }

    void openFile(const QString& openFilePath);
    void openFileReadOnly(const QString& openFilePath);
    void saveToFile(const QString& saveFilePath);
};

#endif // TEXTDOCUMENTSUBWINDOW_H