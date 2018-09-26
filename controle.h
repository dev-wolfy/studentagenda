#ifndef CONTROLE_H
#define CONTROLE_H

#include <QString>
#include <QDate>
#include <QList>

class controle
{
public:
    controle();
    QList<QDate> cListDateRevisions;

    QString getCoTitre() const;
    void setCoTitre(const QString &value);

    QString getCoAReviser() const;
    void setCoAReviser(const QString &value);

    QDate getCDateControle() const;
    void setCDateControle(const QDate &value);

    QList<QDate> getCListDateRevisions() const;
    void setCListDateRevisions(const QList<QDate> &value);

private:
    QString coTitre;
    QString coAReviser;

    QDate cDateControle;

};

#endif // CONTROLE_H
