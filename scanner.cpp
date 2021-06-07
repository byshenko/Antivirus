#include "scanner.h"

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    this->m_scanProgress = "No logged information\n";
}

Scanner::~Scanner()
{

}

void Scanner::scan(const QString &path)
{
    if(QDir(path).exists())
    {
        qDebug() << path << " is Dir";
        scanDir(path);

        return;
    }

    if(QFile(path).exists())
    {
        qDebug() << path << " is File";
        scanFile(path);

        return;
    }

    qDebug() << "Object doesn't exists";
    setScanProgress(scanProgress() + path + ": Object doesn't exists");
}

uint32_t Scanner::scanFile(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
        setScanProgress(scanProgress() + path + ": Can't open File");
        qDebug() << "Can't open File\n";
        return 0;
    }

    QByteArray pattern("\x41\x0E\x28\x42\x0E\x20");
    QByteArrayMatcher matcher(pattern);

    int offset = 0;
    int pos = 0;

    while (!file.atEnd())
    {
        QByteArray data = file.read(2048);//.toHex();

        if (data.contains(pattern))
        {
            setScanProgress(scanProgress() + path + ": File contains pattern");
            qDebug() << "data contains pattern";
            return 1;
        }

        if((pos = matcher.indexIn(data, 0)) != -1)
        {
          qDebug() << "pattern found at pos" << offset + pos;
          setScanProgress(scanProgress() + path + ": Pattern found at pos [" + QString(offset + pos) + "]");
          file.close();
          return offset + pos;
        }

        offset += 2048;
    }

    file.close();
    setScanProgress(scanProgress() + path + ": File doesn't contain pattern");
    qDebug() << "pattern was not found";

    return 0;
}

uint32_t Scanner::scanDir(const QString &path)
{
    setScanProgress(scanProgress() + path +  ": Dir was Found");
    return 0;
}

void Scanner::setScanProgress(QString newScanProgress)
{
    if(this->m_scanProgress != newScanProgress)
    {
        this->m_scanProgress = newScanProgress + "\n";

        // NOTIFY that m_scanProgree was Changed
        emit scanProgressChanged();
    }
}

void Scanner::getRequestToVirustotal(QString apiKey, QString sha256)
{
    QNetworkRequest request(QUrl("https://www.virustotal.com/vtapi/v2/file/report?apikey=" + apiKey + "&resource=" + sha256));
    QNetworkAccessManager mngr;
    connect(&mngr, SIGNAL(finished(QNetworkReply*)), SLOT(getResponseFromVirustotal(QNetworkReply*)));
    mngr.get(request);
}

void Scanner::getResponseFromVirustotal(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}


QString Scanner::scanProgress() const
{
    return m_scanProgress;
}
