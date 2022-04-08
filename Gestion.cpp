#include<iostream>
#include<vector>
#include<fstream>
#include <string>


using namespace std;

struct student {
 //attribute members
    string nom;
    vector <float> notes;
 //method members
    float moyenne(); //fonction moyenne qui calcule la moyenne des notes des eleves
    void display(); // affiche ses notes (que l'ecole lui affecta) mais ne peut pas les changer
};
void student :: display(){
    cout << nom;
    int taille = notes.size();
    for(int i=0; i<taille ; i++){
        cout << "\t" <<  notes[i] ;
    }
    cout << "\t" << moyenne() << endl;
}
float student :: moyenne(){
    float moyenne=0;
    int taille = notes.size();
    for(int i=0 ; i< taille ; i++){
        moyenne += notes[i];
    }
    return moyenne /= taille ;
}

struct school {
    //attribute members
    vector <student> eleves;
    int nbStuds;
    vector <string> topic;
    int nbTopics;
    bool gotData;
    ofstream outFile;
    ifstream inFile;
    //method members
    void initData();
    void addStudent();
    void displayResults();
    void saveData();
    void readData();
};
void school :: initData(){
    nbStuds = eleves.size();
    topic.push_back("Math");
    topic.push_back("Info");
    topic.push_back("Comm");
    nbTopics = 3;
    gotData = false;
}
void school :: addStudent(){
    initData();
    student etudiant;
    float temporaire;
    cout << "Entrer le nom de l'etudiant : " ;
    cin >> etudiant.nom;
    for (int i=0; i< nbTopics ; i++){
        cout << "Notes en " << topic[i] << "\t";
        cin >> temporaire;
        etudiant.notes.push_back(temporaire);
    }
    etudiant.display();
    eleves.push_back(etudiant);
    cout << "Etudiant ajoutee avec succes ";
    gotData = true;
    nbStuds++;
}
void school :: displayResults(){
    if(!gotData){
        cout << "Il n'y a pas encore de donnees " << endl;
    }
    else{
         cout << "Nom " << "\t Math" << "\t Info" << "\t Comm" << endl;
    for (int i=0; i<nbStuds ;i++){
        eleves[i].display();
     }
    }
}
void school :: saveData(){
    //fonction qui permet d'enregistrer les eleves dans un fichier "sortie2.txt"
    outFile.open("sortie2.txt", ios :: app);
    if(outFile){
        int i, j;
        for ( i=0; i<nbStuds ; i++)
        {
            outFile << eleves[i].nom << "\t" ;
            for(j=0;j <nbStuds ;j++)
            {
                outFile << eleves[i].notes[j] << "\t" ;
            }
            cout << endl ;
        } 
        cout << "Les donnees ont ete enregistrées dans votre fichier" << endl;    
    }
    else{
        cout << "Fichier introuvable" << endl;
    }
    outFile.close();
}
void school :: readData(){
    initData();
    int i, j;
    string mots;
    eleves.clear();
    student stud;
    float temp;
    inFile.open("sortie2.txt");
    if(inFile)
    {
        for(i=0 ; inFile >> mots ; i++)
        {
            stud.notes.clear(); 
            stud.nom = mots;
            for( j=0 ; j<nbTopics ;j++)
            {
                inFile >> temp;
                stud.notes.push_back(temp);
            }
            eleves.push_back(stud);
        }
    }
    else
    {
        cout << "Fichier introuvable" << endl;
    }
    inFile.close();
}

struct menu{
    //attribute members 
        vector <string> options;
        int choice;
        bool dataRead;
    //method members 
        void initMenu();
        void getChoice();
        void manageChoice(school& ecole, bool &done);

};
void menu :: initMenu(){
    choice = -1;
    dataRead = false;
    options.clear();
    options.push_back ("1 pour Afficher les resultats");
    options.push_back ("2 pour Lire les donnees sur disque");
    options.push_back ("3 pour Ajouter un eleve");
    options.push_back ("4 pour sauver les donnees");
    options.push_back ("5 pour Quitter le programe");
}
void menu :: getChoice(){
    initMenu();
    int temp = options.size();
    cout << "Tapez : " << endl;
    for(int i=0; i<temp ; i++){
        cout << "\t " << options[i] << endl ;
    }
    cout << " Votre choix SVP : " ;
    cin >> choice;
     while(choice>4 || choice<0)
    {
        cout << "Entrer votre choix entre 0 et 4" ;
        cin >> choice;
    }
}
void menu :: manageChoice(school& ecole, bool &done){
    switch (choice){
        case 0:
        done = true;
        break;
        case 1 :
        ecole.displayResults();
        break;
        case 2:
        ecole.readData();
        break;
        case 3:
        ecole.addStudent();
        break;
        case 4:
        ecole.saveData();
        break;
        default:
        break;
    }
}

int main()
{
    cout << "***Gestion de notes***" << endl;
    bool running = false;
    menu myMenu;
    school ecole;
    ecole.gotData= false; // pas de donnees au depart
    ecole.nbStuds =0;
    myMenu.initMenu();
    while(!running){
        myMenu.getChoice();
        myMenu.manageChoice(ecole,running);
    } 
    return 0;
}