#ifndef SCANNER_H
#define SCANNER_H

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

    /* Using in QML for information about scan progress. Data is logged to TexView */
    Q_PROPERTY(QString scanProgress READ scanProgress NOTIFY scanProgressChanged)

public:
    explicit Scanner(QObject *parent = nullptr);
    ~Scanner();

    /* READ Q_PROPERTY `scanProgress` */
    QString scanProgress() const;

signals:

    /* NOTIFY qml about changing Q_PROPERTY `scanProgress` */
    void scanProgressChanged();

public slots:
    /* Scan File or Dir. Called from QML */
    void scan(const QString &path);

    /* Send GET-Request to VirusTotal */
    void getRequestToVirustotal(QString apiKey, QString sha256);

    /* this SIGNAL was called from getRequestToVirustotal() */
    void getResponseFromVirustotal(QNetworkReply *reply);

protected:
    /* Called from scan() is the case of File scanning */
    uint scanFile(const QString &path);

    /* Called from scan() is the case of Dir scanning */
    uint scanDir(const QString &path);

    /* WRITE `scanProgress` with calling NOTIFY */
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
