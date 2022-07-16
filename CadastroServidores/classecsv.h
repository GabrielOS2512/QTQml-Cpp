#ifndef CLASSECSV_H
#define CLASSECSV_H

#include <QObject>

class classeCSV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString arquivo READ arquivo WRITE setArquivo NOTIFY arquivoChanged)
public:
    explicit classeCSV(QObject *parent = nullptr);
    QString arquivo();

signals:
    void arquivoChanged();
    void error(const QString& msg);
    void sucesso(const QString& msg);

public slots:
    QString abrirCSV(QString);
    bool salvarCSV(QString,QString);
    void setArquivo(QString);

private:
    QString m_arquivo;
};

#endif // CLASSECSV_H
