#include "scanner.h"

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    this->m_scanProgress = "No logged information\n";
    this->m_networkAccessManager = new QNetworkAccessManager(this);
}

Scanner::~Scanner()
{
    delete this->m_networkAccessManager;
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

QByteArray Scanner::readFile(QFile *file)
{
    QByteArray fileBytes;

    if (file->open(QIODevice::ReadOnly))
    {
       while (!file->atEnd())
       {
          fileBytes += file->readLine();
       }
       file->close();
    }

    return fileBytes;
}

void Scanner::getRequestToVirustotal(QString filePath)
{
    if(this->m_apiKey.length() != 64)
    {
        setScanProgress(scanProgress() +  "Incorrect API Key. Go Settings to Fix");
        return;
    }

    QFile file(filePath);

    if(!file.exists())
    {
        setScanProgress(scanProgress() + filePath +  ": not a File");
        return;
    }

    QByteArray fileBytes = readFile(&file);

    setScanProgress(scanProgress() + QString("https://www.virustotal.com/vtapi/v2/file/report?apikey=" + this->m_apiKey +
                                          "&resource=" + QCryptographicHash::hash(fileBytes, QCryptographicHash::Sha256).toHex()));

    QNetworkRequest request(QUrl(QString("https://www.virustotal.com/vtapi/v2/file/report?apikey=" + this->m_apiKey +
                                 "&resource=" + QCryptographicHash::hash(fileBytes, QCryptographicHash::Sha256).toHex())));

    // look at `Scanner::Scanner` for `m_networkAccessManager = new QNetworkAccessManager(this)`
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(getResponseFromVirustotal(QNetworkReply*)));
    m_networkAccessManager->get(request);
}

void Scanner::getResponseFromVirustotal(QNetworkReply *reply)
{
    if(reply->error())
    {
        setScanProgress(scanProgress() + "Request To VirusTotal error");
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    int positives = root.value("positives").toInt(); // get from VirusTotal-JSON number of positives results

    setScanProgress(scanProgress() + "VirusTotal positives: " + QString::number(positives));
    qDebug() << "positives: " << positives;

    // qDebug() << reply->readAll();
}

void Scanner::saveVirustotalApiKey(QString apiKey)
{
    if(apiKey.length() != 64)
    {
        setScanProgress(scanProgress() + "API Key must be of length 64 chars (bytes)");
        return;
    }

    this->m_apiKey = apiKey;
    setScanProgress(scanProgress() + "API Key was saved");
}


QString Scanner::scanProgress() const
{
    return m_scanProgress;
}
