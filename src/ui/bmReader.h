#include <QThread>

class bmReader : public QThread
{
    Q_OBJECT
    void run() override;
    QString charToHexStr(char chr);
    QString getBmID(const QByteArray &bmDataPkg);
    bool checkPkgValid(const QByteArray &bmDataPkg);
public:
    bmReader(QObject *parent = nullptr);
signals:
    void serialPortErro(const QString &s);
    void bmDataGot(const QString &bmID, const int Breathe, const int HeartRate);
    void finished();
};
