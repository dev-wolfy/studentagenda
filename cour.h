#ifndef COUR_H
#define COUR_H

#include <QString>
#include <QDate>
#include <QList>
#include <vector>

class cour
{
public:
    cour();
    cour(QString titre, QString commentaire);
    void addRessources(QString ressource);

    QString getCTitre() const;
    void setCTitre(const QString &value);

    QString getCCommentaire() const;
    void setCCommentaire(const QString &value);

    QDate getCDateCour() const;
    void setCDateCour(const QDate &value);

    QDate getCRappel1() const;
    void setCRappel1(const QDate &value);

    QDate getCRappel2() const;
    void setCRappel2(const QDate &value);

    QDate getCRappel3() const;
    void setCRappel3(const QDate &value);

    QDate getCRappel4() const;
    void setCRappel4(const QDate &value);

    QDate getCRappel5() const;
    void setCRappel5(const QDate &value);

    QList<QString> getCDocuments() const;
    void setCDocuments(const QList<QString> &value);
    void appendCDocuments(const QString &value);

private:
    QString cTitre;
    QString cCommentaire;
    QList<QString> cDocuments;

    QDate cDateCour;

    QDate cRappel1;
    QDate cRappel2;
    QDate cRappel3;
    QDate cRappel4;
    QDate cRappel5;
};

#endif // COUR_H
