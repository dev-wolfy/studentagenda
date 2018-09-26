#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QDate>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QDateEdit>
#include <QFile>
#include <QTextStream>
#include <QShortcut>
#include <QKeySequence>
#include <QTextFormat>
#include <QTextCharFormat>
#include <QTableWidget>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
//#include <QDebug>
#include <QtCore>

#include "cour.h"
#include "controle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<cour> listeOfCours;
    QList<controle> listOfControle;

private slots:
    void addNewCour();
    void addNewControle();

    void changeDateFieldContent();
    void changeCourTableContent();
    void changeControleTableContent();

private:
    void loadCour();
    void loadControle();

    void initCouleur();

    void createCalendar();
    void createTabWidget();
    void createFormCour();
    void createFormConcours();

    void createTableCours();
    void createTableControles();
    void createTableRevisionsCours();

    void createMenuBar();
    void createActions();

    void saveAllCours();
    void saveAllControle();



    QString getCoursForThisDate(QDate date);
    QString getControleForThisDate(QDate date);
    QTextCharFormat *red;
    QTextCharFormat *yellow;
    QTextCharFormat *blue;

    QWidget *dummy;

    QFile file;

    QGroupBox *calendarGroupBox;

    QGridLayout *calendarLayout;
    QCalendarWidget *calendar;

    int taille;

    QGroupBox *tabGroupBox;
    QGridLayout *tabLayout;
    QTabWidget *tabWidget;

    QVBoxLayout * formCourLayout;
    QWidget *divFormCour;
    QLineEdit *titreCourField;
    QTextEdit *commentaireCourField;
    QDateEdit *dateEdit;
    QPushButton *addFileRessource;
    QPushButton *addNewCourBtn;

    QVBoxLayout *formControlLayout;
    QWidget *divFormControl;
    QLineEdit *titreControlField;
    QTextEdit *areviserControlField;
    QDateEdit *dateEditControl;
    QPushButton *addNewControl;


    // - TableWidget
    QGroupBox *courTableGroupBox;
    QStringList *headersForCoursTable;
    QGridLayout *courTableLayout;
    QTableWidget *tableCours;

    QGroupBox *controleTableGroupBox;
    QStringList *headersForControleTable;
    QGridLayout *controleTableLayout;
    QTableWidget *controleTable;

    cour *tempCour;
    controle *tempControle;

    QShortcut *CTRL_S;

    // -- MenuBar --
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QActionGroup *alignementGroup;
    QAction *quitAct;
    QAction *configAct;
    QAction *interfaceAct;
    QAction *helpAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
