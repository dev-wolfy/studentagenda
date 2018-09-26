#include "controle.h"

controle::controle()
{

}

QString controle::getCoTitre() const
{
    return coTitre;
}

void controle::setCoTitre(const QString &value)
{
    coTitre = value;
}

QString controle::getCoAReviser() const
{
    return coAReviser;
}

void controle::setCoAReviser(const QString &value)
{
    coAReviser = value;
}

QDate controle::getCDateControle() const
{
    return cDateControle;
}

void controle::setCDateControle(const QDate &value)
{
    cDateControle = value;
}

QList<QDate> controle::getCListDateRevisions() const
{
    return cListDateRevisions;
}

void controle::setCListDateRevisions(const QList<QDate> &value)
{
    cListDateRevisions = value;
}
