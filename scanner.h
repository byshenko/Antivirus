#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>

#include <QNetworkAccessManager>
#include <QByteArrayMatcher>
#include <QNetworkReply>
#include <QByteArray>
#include <QArrayData>
#include <QBitArray>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QUrl>

class Scanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString scanProgress READ scanProgress NOTIFY scanProgressChanged)

public:
    explicit Scanner(QObject *parent = nullptr);
    ~Scanner();

    QString scanProgress() const; // READ scanProgress

signals:
    void scanProgressChanged(); // NOTIFY scanProgress

public slots:
    void scan(const QString &path);
    void getRequestToVirustotal(QString apiKey, QString sha256);
    void getResponseFromVirustotal(QNetworkReply *reply); // this SIGNAL was called from getRequestToVirustotal()

protected:
    uint32_t scanFile(const QString &path);
    uint32_t scanDir(const QString &path);

    void setScanProgress(QString newScanProgress); // WRITE scanProgress with NOTIFY

    void sendGet(QString Url);

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