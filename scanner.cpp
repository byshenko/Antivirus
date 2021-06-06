#include "scanner.h"

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    this->m_scanProgress = "No logged information";
}

Scanner::~Scanner()
{

}

void Scanner::scan(const QString &path)
{
    if(QDir(path).exists())
    {
        qDebug() << path << " is Dir";

        if (scanDir(path))
        {
            // #TODO: Dir was scanned
        }
        else
        {
            // #TODO: Dir wasn't scanned
        }

        return;
    }

    if(QFile(path).exists())
    {
        qDebug() << path << " is File";

        if(scanFile(path))
        {
            // #TODO: File was scanned
        }
        else
        {
            // #TODO: File wasn't scanned
        }

        return;
    }

    qDebug() << "Object doesn't exists";

    this->m_scanProgress = "Object doesn't exists";

    return;// 0;
}

uint32_t Scanner::scanFile(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
      qDebug() << "Can't open File\n";
      return 0;
    }

    QByteArray pattern("\x41\x0E\x28\x42\x0E\x20");
    QByteArrayMatcher matcher(pattern);

    auto offset = 0;
    auto pos = 0;

    while (!file.atEnd())
    {
        QByteArray data = file.read(2048);//.toHex();

        if (data.contains(pattern))
        {
            qDebug() << "data contains pattern";
        }

        while((pos = matcher.indexIn(data, 0)) != -1)
        {
          qDebug() << "pattern found at pos" << offset + pos;
          qDebug() << data;
          file.close();
          return 1;
        }

        offset += 2048;
    }

    file.close();
    qDebug() << "pattern was not found";

    return 0;
}

uint32_t Scanner::scanDir(const QString &path)
{
    return 0;
}

void Scanner::setScanProgress(QString newScanProgress)
{
    if(this->m_scanProgress != newScanProgress)
    {
        this->m_scanProgress = newScanProgress;

        // NOTIFY that m_scanProgree was Changed
        emit scanProgressChanged();
    }
}

QString Scanner::scanProgress() const
{
    return m_scanProgress;
}
