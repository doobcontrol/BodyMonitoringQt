#include <QThread>

class bmReader : public QThread
{
    Q_OBJECT
    void run() override;
    QString charToHexStr(char chr);
    QString getBmID(const QByteArray &bmDataPkg);
public:

signals:
    void serialPortErro(const QString &s);
    void bmDataGot(const QString &bmID, const int Breathe, const int HeartRate);
    void finished();
};
