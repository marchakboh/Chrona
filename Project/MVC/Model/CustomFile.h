#ifndef CUSTOMFILE_H
#define CUSTOMFILE_H

#include <QObject>

class CustomFile : public QObject
{
    Q_OBJECT
public:
    explicit CustomFile(QObject *parent = nullptr);
    ~CustomFile();

    void SetName(QString);
    void SetPath(QString);
    void SetPreRunArguments(QString);
    void SetRunArguments(QString);
    void SetIndexType(int);
    void SetStatus(bool);

    QString& GetName();
    QString& GetPath();
    QString& GetPreRunArguments();
    QString& GetRunArguments();
    int GetIndexType();
    bool GetStatus();

    void Reset();

private:
    QString _name;
    QString _path;
    QString _preRunArguments;
    QString _runArguments;
    int indexType;

    bool _status;
};

#endif // CUSTOMFILE_H
