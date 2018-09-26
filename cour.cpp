#include "cour.h"

cour::cour()
{

}

cour::cour(QString c_titre, QString c_commentaire)
{

}


/**************************
    GETTERs AND SETTERs
***************************/


QString cour::getCTitre() const
{
    return cTitre;
}

void cour::setCTitre(const QString &value)
{
    cTitre = value;
}

QString cour::getCCommentaire() const
{
    return cCommentaire;
}

void cour::setCCommentaire(const QString &value)
{
    cCommentaire = value;
}

QList<QString> cour::getCDocuments() const
{
    return cDocuments;
}

void cour::setCDocuments(const QList<QString> &value)
{
    cDocuments = value;
}

void cour::appendCDocuments(const QString &value)
{
    this->cDocuments.append(value);
}

/* std::vector<QString> cour::getCRessources() const
{
    return cRessources;
}

void cour::setCRessources(const std::vector<QString> &value)
{
    cRessources = value;
}*/

QDate cour::getCDateCour() const
{
    return cDateCour;
}

void cour::setCDateCour(const QDate &value)
{
    cDateCour = value;
}

QDate cour::getCRappel1() const
{
    return cRappel1;
}

void cour::setCRappel1(const QDate &value)
{
    cRappel1 = value;
}

QDate cour::getCRappel2() const
{
    return cRappel2;
}

void cour::setCRappel2(const QDate &value)
{
    cRappel2 = value;
}

QDate cour::getCRappel3() const
{
    return cRappel3;
}

void cour::setCRappel3(const QDate &value)
{
    cRappel3 = value;
}

QDate cour::getCRappel4() const
{
    return cRappel4;
}

void cour::setCRappel4(const QDate &value)
{
    cRappel4 = value;
}

QDate cour::getCRappel5() const
{
    return cRappel5;
}

void cour::setCRappel5(const QDate &value)
{
    cRappel5 = value;
}
