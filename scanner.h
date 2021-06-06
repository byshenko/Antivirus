#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QString>
#include <QArrayData>
#include <QBitArray>
#include <QByteArray>
#include <QDebug>
#include <QByteArrayMatcher>

class Scanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString scanProgress READ scanProgress NOTIFY scanProgressChanged)

public:
    explicit Scanner(QObject *parent = nullptr);
    ~Scanner();

    QString scanProgress() const; // READ

signals:
    void scanProgressChanged();

public slots:
    void scan(const QString &path);

protected:
    uint32_t scanFile(const QString &path);
    uint32_t scanDir(const QString &path);

    void setScanProgress(QString newScanProgress);

private:
    QString m_scanProgress; // scan progress
    QList<QString> m_signatures; // scan result


    struct scanResult
    {
        QString filePath; // path + name of file
        QByteArray signature; // may be empty (if file is clear)
        QString warning; // what type of a virus
        uint dangerousLevel;
    };
};

#endif // SCANNER_H
