#include "classecsv.h"
#include <QDebug>
#include <QFile>
#include <QDir>
using namespace std;

classeCSV::classeCSV(QObject *parent) : QObject(parent)
{

}

QString classeCSV::abrirCSV(QString arquivo)
{
    if (arquivo.isEmpty()){
        emit error("Não foi possível abrir o arquivo.");
        return QString();
    }

    QFile file(arquivo);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString linha;
        QTextStream t( &file );
        do {
            linha = t.readLine();
            if ( linha != ""){
                fileContent += linha + "$$$";
            }
        } while (!linha.isNull());

        file.close();
    } else {
        emit error("Não foi possivel abrir o arquivo selecionado.");
        return QString();
    }

    emit sucesso("Arquivo carregado com sucesso!");
    return fileContent;
}

bool classeCSV::salvarCSV(QString dados,QString nomeArquivo)
{
    QStringList linhas = dados.split("$$$");
    QString arquivo = m_arquivo + "/" + nomeArquivo+".csv";
    QDir dir;

    if (m_arquivo.isEmpty()){
        emit error("Erro no diretório fornecido!");
        return false;
    }

    if (nomeArquivo.isEmpty()){
        emit error("Insira o nome do arquivo a ser criado!");
        return false;
    }

    if (!dir.exists(m_arquivo))
        dir.mkpath(m_arquivo);

    QFile file(arquivo);
    //qDebug() << arquivo;
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream out(&file);
        //out << dados;
        for (int i = 0; i < linhas.size()-1; i++)
        {
            out << linhas[i] + '\n';           
        }
    } else {
        emit error("Não foi possivel abrir o arquivo selecionado.");
        return false;
    }

    file.close();

    emit sucesso("Arquivo salvo com sucesso!");
    return true;
}


QString classeCSV::arquivo(){
    return m_arquivo;
}

void classeCSV::setArquivo(QString file){
    m_arquivo = file;
    emit arquivoChanged();
}
