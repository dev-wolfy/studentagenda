#include <QWidget>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //qDebug() << "1";
    loadCour();
    //qDebug() << "2";
    loadControle();
    //qDebug() << "3";
    initCouleur();
    //qDebug() << "4";
    createCalendar();
    //qDebug() << "5";
    createFormCour();
    //qDebug() << "6";
    createFormConcours();
    //qDebug() << "7";
    createTabWidget();
    //qDebug() << "9";
    //createDisplayControles();
    //qDebug() << "10";
    createTableCours();
    //qDebug() << "11";
    createTableControles();
    //qDebug() << "12";

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(calendarGroupBox, 0, 0, 1, 1);
    layout->addWidget(tabGroupBox, 0, 1, 1, 1);
    layout->addWidget(courTableGroupBox, 1, 0, 1, 1);
    layout->addWidget(controleTableGroupBox, 1, 1, 1, 3);

    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setSizeConstraint(QLayout::SetMaximumSize);

    QWidget *dummy = new QWidget;
    dummy->setLayout(layout);
    setCentralWidget(dummy);

    calendarLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
    calendarLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());

    connect(addNewCourBtn, SIGNAL(clicked()),
            this, SLOT(addNewCour()) );
    connect(addNewControl, SIGNAL(clicked()),
            this, SLOT(addNewControle()) );
    connect(calendar, SIGNAL(selectionChanged()),
            this, SLOT(changeDateFieldContent()) );
    connect(calendar, SIGNAL(selectionChanged()),
            this, SLOT(changeCourTableContent()) );
    connect(calendar, SIGNAL(selectionChanged()),
            this, SLOT(changeControleTableContent()) );

    setWindowIcon(QIcon(":calendar.png"));
    setWindowTitle(tr("StudentMemory!!"));
}

void MainWindow::loadCour()
{
    bool continuer = true;
    QFile file("D:/cours.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString *line = new QString;
        QString tempString = "";

        while(!in.atEnd() || (continuer != false))
        {
            *line = in.readLine();
            if (*line == "------NEW------") {
                cour *tempCour = new cour;

                *line = in.readLine();
                tempCour->setCTitre(*line);

                *line = "";
                do {
                    tempString = in.readLine();
                    if (tempString != "[=][=][=][=]") {
                        *line += tempString;
                    }
                } while (tempString != "[=][=][=][=]");
                tempCour->setCCommentaire(*line);
                *line = in.readLine();
                tempCour->setCDateCour(QDate::fromString(*line,"dd/MM/yyyy"));
                *line = in.readLine();
                tempCour->setCRappel1(QDate::fromString(*line,"dd/MM/yyyy"));
                *line = in.readLine();
                tempCour->setCRappel2(QDate::fromString(*line,"dd/MM/yyyy"));
                *line = in.readLine();
                tempCour->setCRappel3(QDate::fromString(*line,"dd/MM/yyyy"));
                *line = in.readLine();
                tempCour->setCRappel4(QDate::fromString(*line,"dd/MM/yyyy"));
                *line = in.readLine();
                tempCour->setCRappel5(QDate::fromString(*line,"dd/MM/yyyy"));
                listeOfCours.append(*tempCour);
            }
            else
            {
                continuer = false;
            }

        }
    }
    else
    {
        QMessageBox::information(this,"Danger!!" ,"Problème dans le chargement des cours");
    }
}

void MainWindow::loadControle()
{
    bool continuer = true;
    QFile file("D:/controles.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString *line = new QString;
        QString tempString = "";

        while(!in.atEnd() || (continuer != false))
        {
            *line = in.readLine();
            if (*line == "------NEW------") {
                tempControle = new controle;
                *line = in.readLine();
                tempControle->setCoTitre(*line);

                *line = "";
                do {
                    tempString = in.readLine();
                    if (tempString != "[=][=][=][=]") {
                        *line += tempString;
                    }
                } while (tempString != "[=][=][=][=]");
                tempControle->setCoAReviser(*line);
                *line = in.readLine();
                tempControle->setCDateControle(QDate::fromString(*line,"dd/MM/yyyy"));
                do {
                    tempString = in.readLine();
                    if (tempString != "[=][=][=][=]") {
                        tempControle->cListDateRevisions.append(QDate::fromString(tempString,"dd/MM/yyyy"));
                    }
                } while (tempString != "[=][=][=][=]");

                listOfControle.append(*tempControle);
            }
            else
            {
                continuer = false;
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Danger!!" ,"Problème dans le chargement des cours");
    }
}

void MainWindow::initCouleur()
{
    red = new QTextCharFormat;
    red->setForeground(Qt::black);
    red->setBackground(Qt::red);

    yellow = new QTextCharFormat;
    yellow->setForeground(Qt::black);
    yellow->setBackground(Qt::yellow);

    blue = new QTextCharFormat;
    blue->setForeground(Qt::white);
    blue->setBackground(Qt::blue);
}

void MainWindow::createCalendar()
{
    int  i(0);
    taille = listOfControle.size();
    calendarGroupBox = new QGroupBox(tr("Calendrier"));

    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(2000, 1, 1));
    calendar->setMaximumDate(QDate(2050, 1, 1));
    calendar->setSelectedDate(QDate(QDate::currentDate()));
    calendar->setDateTextFormat(calendar->selectedDate(), *blue);
    calendar->setGridVisible(false);

    for (i = 0; i < taille; ++i) {
        calendar->setDateTextFormat(listOfControle.at(i).getCDateControle(), *red);
    }

    calendarLayout = new QGridLayout;
    calendarLayout->addWidget(calendar, 0, 0, Qt::AlignTop);
    calendarGroupBox->setLayout(calendarLayout);
}

void MainWindow::createFormCour()
{
    divFormCour = new QWidget;

    titreCourField = new QLineEdit;
    titreCourField->setPlaceholderText("Titre du cour");
    titreCourField->setTextMargins(5, 5, 5, 5);
    commentaireCourField = new QTextEdit;
    commentaireCourField->setPlaceholderText("Description / Contenu / Commentaire");
    dateEdit = new QDateEdit;
    dateEdit->setDate(calendar->selectedDate());
    dateEdit->setDisabled(true);
    addFileRessource = new QPushButton("Ajouter un fichier...");
    addNewCourBtn = new QPushButton("Enregistrer");

    formCourLayout = new QVBoxLayout;
    formCourLayout->addWidget(titreCourField);
    formCourLayout->addWidget(commentaireCourField);
    formCourLayout->addWidget(dateEdit);
    formCourLayout->addWidget(addFileRessource);
    formCourLayout->addWidget(addNewCourBtn);
    divFormCour->setLayout(formCourLayout);
}

void MainWindow::createFormConcours()
{
    divFormControl = new QWidget;

    titreControlField = new QLineEdit;
    titreControlField->setPlaceholderText("Titre du controle");
    titreControlField->setTextMargins(5, 5, 5, 5);
    areviserControlField = new QTextEdit;
    areviserControlField->setPlaceholderText("A reviser!!");
    dateEditControl = new QDateEdit(calendar->selectedDate());
    dateEditControl->setDisabled(true);
    addNewControl = new QPushButton("Ajouter...");

    formControlLayout = new QVBoxLayout;
    formControlLayout->addWidget(titreControlField);
    formControlLayout->addWidget(areviserControlField);
    formControlLayout->addWidget(dateEditControl);
    formControlLayout->addWidget(addNewControl);

    divFormControl->setLayout(formControlLayout);
}

void MainWindow::createTabWidget()
{
    tabGroupBox = new QGroupBox(tr("Ajouter :"));

    tabWidget = new QTabWidget;
    tabWidget->addTab(divFormCour, "Nouveau Cour");
    tabWidget->addTab(divFormControl, "Controle");

    tabLayout = new QGridLayout();
    tabLayout->addWidget(tabWidget, 0, 0, Qt::AlignTop);
    tabGroupBox->setLayout(tabLayout);
}

void MainWindow::createMenuBar()
{

}

void MainWindow::createActions()
{
    /*fileMenu = new QAction(tr("&Fichier"));*/
}

// --TABLE--
void MainWindow::createTableCours()
{
    int nb_max_cours = listeOfCours.size();
    int i = 0;
    int id = 0;
    QDate date = calendar->selectedDate();

    courTableGroupBox = new QGroupBox;

    headersForCoursTable = new QStringList;
    headersForCoursTable->append("#");
    headersForCoursTable->append("Titre");
    headersForCoursTable->append("Date du cour");
    headersForCoursTable->append("Contenu / description");

    tableCours = new QTableWidget;
    tableCours->setColumnCount(4);
    tableCours->setShowGrid(true);
    tableCours->setSelectionMode(QAbstractItemView::SingleSelection);
    tableCours->setSelectionBehavior(QAbstractItemView::SelectRows);


    for (i = 0; i < nb_max_cours; ++i) {
        if (listeOfCours.at(i).getCRappel1() == date || listeOfCours.at(i).getCRappel2() == date || listeOfCours.at(i).getCRappel3() == date || listeOfCours.at(i).getCRappel4() == date || listeOfCours.at(i).getCRappel5() == date) {
            tableCours->insertRow(id);
            tableCours->setItem(id, 1, new QTableWidgetItem(listeOfCours.at(i).getCTitre()));
            tableCours->setItem(id, 2, new QTableWidgetItem(listeOfCours.at(i).getCDateCour().toString()));
            tableCours->setItem(id, 3, new QTableWidgetItem(listeOfCours.at(i).getCCommentaire()));
            ++id;
        }
    }

    tableCours->setHorizontalHeaderLabels(*headersForCoursTable);

    courTableLayout = new QGridLayout;
    courTableLayout->addWidget(tableCours);
    courTableGroupBox->setLayout(courTableLayout);

    tableCours->resizeColumnsToContents();

}
void MainWindow::changeCourTableContent()
{
    int i = 0;
    int id = 0;
    int nb_max_cours = listeOfCours.size();

    tableCours->setRowCount(0);
    QDate date = calendar->selectedDate();
    for (i = 0; i < nb_max_cours; ++i) {
        if (listeOfCours.at(i).getCRappel1() == date || listeOfCours.at(i).getCRappel2() == date || listeOfCours.at(i).getCRappel3() == date || listeOfCours.at(i).getCRappel4() == date || listeOfCours.at(i).getCRappel5() == date) {
            tableCours->insertRow(id);
            tableCours->setItem(id, 1, new QTableWidgetItem(listeOfCours.at(i).getCTitre()));
            tableCours->setItem(id, 2, new QTableWidgetItem(listeOfCours.at(i).getCDateCour().toString()));
            tableCours->setItem(id, 3, new QTableWidgetItem(listeOfCours.at(i).getCCommentaire()));
            ++id;
        }
    }
}

void MainWindow::createTableControles()
{
    int nb_max_controle = listOfControle.size();
    int nb_max_date = 0;
    int i = 0;
    int j = 0;
    int id = 0;
    QDate date = calendar->selectedDate();

    controleTableGroupBox = new QGroupBox;

    headersForControleTable = new QStringList;
    headersForControleTable->append("#");
    headersForControleTable->append("Contrôle");
    headersForControleTable->append("Date du contrôle");
    headersForControleTable->append("A réviser");

    controleTable = new QTableWidget;
    controleTable->setColumnCount(4);
    controleTable->setShowGrid(true);
    controleTable->setSelectionMode(QAbstractItemView::SingleSelection);
    controleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    controleTable->setHorizontalHeaderLabels(*headersForControleTable);

    for (i = 0; i < nb_max_controle; ++i) {
        nb_max_date = listOfControle.at(i).cListDateRevisions.size();
        for (j = 0; j < nb_max_date; ++j) {
            if (listOfControle.at(i).cListDateRevisions.at(j) == date) {
                controleTable->insertRow(id);
                controleTable->setItem(id, 1, new QTableWidgetItem(listOfControle.at(i).getCoTitre()));
                controleTable->setItem(id, 2, new QTableWidgetItem(listOfControle.at(i).getCDateControle().toString()));
                controleTable->setItem(id, 3, new QTableWidgetItem(listOfControle.at(i).getCoAReviser()));
                ++id;
            }

        }
    }

    controleTableLayout = new QGridLayout;
    controleTableLayout->addWidget(controleTable);
    controleTableGroupBox->setLayout(controleTableLayout);

    controleTable->resizeColumnsToContents();
}
void MainWindow::changeControleTableContent()
{
    int nb_max_controle = listOfControle.size();
    int nb_max_date = 0;
    int i = 0;
    int j = 0;
    int id = 0;

    controleTable->setRowCount(0);
    QDate date = calendar->selectedDate();

    for (i = 0; i < nb_max_controle; ++i) {
        nb_max_date = listOfControle.at(i).cListDateRevisions.size();
        for (j = 0; j < nb_max_date; ++j) {
            if (listOfControle.at(i).cListDateRevisions.at(j) == date) {
                controleTable->insertRow(id);
                controleTable->setItem(id, 1, new QTableWidgetItem(listOfControle.at(i).getCoTitre()));
                controleTable->setItem(id, 2, new QTableWidgetItem(listOfControle.at(i).getCDateControle().toString()));
                controleTable->setItem(id, 3, new QTableWidgetItem(listOfControle.at(i).getCoAReviser()));
                ++id;
            }

        }
    }
}

// --ADD--
void MainWindow::addNewCour()
{
    if(titreCourField->text() != NULL && commentaireCourField->toPlainText() != NULL)
    {
        tempCour = new cour;
        tempCour->setCTitre(titreCourField->text());
        tempCour->setCCommentaire(commentaireCourField->toPlainText());
        tempCour->setCDateCour(calendar->selectedDate());
        tempCour->setCRappel1(tempCour->getCDateCour().addDays(1));
        tempCour->setCRappel2(tempCour->getCDateCour().addDays(7));
        tempCour->setCRappel3(tempCour->getCDateCour().addMonths(1));
        tempCour->setCRappel4(tempCour->getCDateCour().addMonths(3));
        tempCour->setCRappel5(tempCour->getCDateCour().addMonths(6));

        listeOfCours.append(*tempCour);

        saveAllCours();

        titreCourField->setText("");
        commentaireCourField->setPlainText("");

    }
    else
    {
        QMessageBox::information(this, "Attention", "Veuillez remplir un titre et un commentaire");
    }
}

void MainWindow::addNewControle()
{
    QDate tempDate;
    if(titreControlField->text() != NULL && areviserControlField->toPlainText() != NULL)
    {
        tempControle = new controle;
        tempControle->setCoTitre(titreControlField->text());
        tempControle->setCoAReviser(areviserControlField->toPlainText());
        tempControle->setCDateControle(calendar->selectedDate());

        if (QDate(QDate::currentDate()) < calendar->selectedDate()) {
            for (int i = 0; i < 5; ++i) {
                tempDate = calendar->selectedDate().addDays(-(1+(2*i)));
                if (tempDate < QDate(QDate::currentDate())) {
                    i = 6;
                }
                else
                {
                    tempControle->cListDateRevisions.append(tempDate);

                }
            }
        }


        listOfControle.append(*tempControle);

        saveAllControle();

        titreControlField->setText("");
        areviserControlField->setPlainText("");
        calendar->setDateTextFormat(tempControle->getCDateControle(), *red);
    }
    else
    {
        QMessageBox::information(this, "Attention", "Veuillez remplir un titre et des notions à réviser");
    }
}

void MainWindow::changeDateFieldContent()
{
    dateEdit->setDate(calendar->selectedDate());
    dateEditControl->setDate(calendar->selectedDate());
}

QString MainWindow::getCoursForThisDate(QDate date)
{
    int nb_max = listeOfCours.size();
    QString returnString = "";
    for (int i = 0; i < nb_max; ++i) {
        if (listeOfCours.at(i).getCRappel1() == date || listeOfCours.at(i).getCRappel2() == date || listeOfCours.at(i).getCRappel3() == date || listeOfCours.at(i).getCRappel4() == date || listeOfCours.at(i).getCRappel5() == date) {
            returnString += listeOfCours.at(i).getCTitre() + " - " + listeOfCours.at(i).getCDateCour().toString() + "\n" + listeOfCours.at(i).getCCommentaire() + "\n\r";
        }
    }

    return returnString;
}

QString MainWindow::getControleForThisDate(QDate date)
{
    int nb_max = listOfControle.size();
    QString returnString = "";

    for (int i = 0; i < nb_max; ++i) {
        if (listOfControle.at(i).getCDateControle() == date) {
            returnString += listOfControle.at(i).getCoTitre() + "\n" + listOfControle.at(i).getCoAReviser() + "\n\r";
        }
    }

    return returnString;
}

// - SAVE -
void MainWindow::saveAllCours()
{
    int i = 0;
    int taille = 0;
    QFile file("D:/cours.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        taille = listeOfCours.size();

        for (i = 0; i < taille; ++i) {
            out << "------NEW------" << endl;
            out << listeOfCours.at(i).getCTitre() << endl;
            out << listeOfCours.at(i).getCCommentaire() << endl;
            out << "[=][=][=][=]" << endl;
            out << listeOfCours.at(i).getCDateCour().toString("dd/MM/yyyy") << endl;

            out << listeOfCours.at(i).getCRappel1().toString("dd/MM/yyyy") << endl;
            out << listeOfCours.at(i).getCRappel2().toString("dd/MM/yyyy") << endl;
            out << listeOfCours.at(i).getCRappel3().toString("dd/MM/yyyy") << endl;
            out << listeOfCours.at(i).getCRappel4().toString("dd/MM/yyyy") << endl;
            out << listeOfCours.at(i).getCRappel5().toString("dd/MM/yyyy") << endl;
        }

        file.close();
    }
    else
    {
        QMessageBox::information(this,"Danger!!" ,"Impossible de sauvegarder les Cours");
    }
}

void MainWindow::saveAllControle()
{
    int i = 0;
    int j = 0;
    int taille = 0;
    int tailleListOfDate = 0;

    QFile file("D:/controles.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        taille = listOfControle.size();

        for (i = 0; i < taille; ++i) {
            out << "------NEW------" << endl;
            out << listOfControle.at(i).getCoTitre() << endl;
            out << listOfControle.at(i).getCoAReviser() << endl;
            out << "[=][=][=][=]" << endl;
            out << listOfControle.at(i).getCDateControle().toString("dd/MM/yyyy") << endl;

            tailleListOfDate = listOfControle.at(i).cListDateRevisions.size();
            for (j = 0; j < tailleListOfDate; ++j) {
                out << listOfControle.at(i).cListDateRevisions.at(j).toString("dd/MM/yyyy") << endl;
            }
            out << "[=][=][=][=]" << endl;
        }

        file.close();
    }
    else
    {
        QMessageBox::information(this,"Danger!!" ,"Impossible de sauvegarder les Cours");
    }
}

MainWindow::~MainWindow()
{

}
