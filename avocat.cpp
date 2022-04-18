#include<iostream>
#include<string>
using namespace std;

///Avocat
class Avocat{
    static int nrAvocati;
    int cod, nr_procese, *vector_procese;
    string nume;
public:
    //constructori si destructori
    Avocat();
    Avocat(string nume, int cod, int nr_procese, int *vector_procese);
    Avocat(const Avocat& a);
    ~Avocat();
    //supraincarcare operatori
    friend istream& operator>>( istream& in, Avocat& a);
    friend ostream& operator<<( ostream& out,const Avocat& a);
    Avocat& operator=(const Avocat& a);
    friend bool operator>(const Avocat& a, const Avocat& b);


    virtual void afisare(){
        cout<<"\n-----------------------------\n";
        cout<<"Nume:"<<nume<<endl<<"Cod:"<<cod<<endl<<"NrProcese:"<<nr_procese<<endl;
        for(int i=0;i<nr_procese;i++)
            cout<<"Suma proces "<<i+1<<":"<<vector_procese[i]<<endl;

    }
    static void afisareNrAvocati(){
        cout<<"\nNumarul total de avocati este:"<<nrAvocati<<endl;
    }

};
int Avocat::nrAvocati;

Avocat::Avocat(){
    nume="Necunoscut";
    cod=-1;
    nr_procese=-1;
    nrAvocati++;
}
Avocat::Avocat(string nume, int cod, int nr_procese, int *vect){
    this->nume=nume;
    this->cod=cod;
    this->nr_procese=nr_procese;
    vector_procese=new int[nr_procese];
    for(int i=0;i<nr_procese;i++)
        vector_procese[i]=vect[i];
    nrAvocati++;
}
Avocat::Avocat(const Avocat& a){
    nume=a.nume;
    cod=a.cod;
    nr_procese=a.nr_procese;
    for(int i=0;i<nr_procese;i++)
        vector_procese[i]=a.vector_procese[i];
    nrAvocati++;
}
Avocat::~Avocat(){
    delete[] vector_procese;
    //cout<<"\nDestructor clasa de baza\n";
}

istream& operator>>( istream& in, Avocat& a){
    cout<<"Numele avocatului:";
    in>>a.nume;
    cout<<"Codul avocatului:";
    in>>a.cod;
    cout<<"Numarul de procese al avocatului:";
    in>>a.nr_procese;
    a.vector_procese=new int[a.nr_procese];
    for(int i=0;i<a.nr_procese;i++)
    {
        try{
            cout << "Suma procesului " << i+1 << " este: ";
            in >> a.vector_procese[i];
            if(a.vector_procese[i]<0)
                throw 0;
        }
        catch(int x){
            cout<<"ERROR.Suma procesului nu poate fi negativa."<<endl;
            exit(EXIT_FAILURE);
        }


    }
    return in;
}
ostream& operator<<(ostream& out, const Avocat& a){
    out << "\nNume:"<<a.nume;
    out << "\nCod: " << a.cod;
    out << "\nNr procese: " << a.nr_procese;
    for(int i = 0; i < a.nr_procese; i++)
        out << "\nSuma proces " << i+1 << ": " << a.vector_procese[i];
    return out;
}
Avocat& Avocat::operator=(const Avocat& a){
    nume=a.nume;
    cod=a.cod;
    nr_procese=a.nr_procese;
    vector_procese = new int[a.nr_procese];
    for(int i = 0; i < a.nr_procese; i++)
        vector_procese[i] = a.vector_procese[i];
    return *this;
}
bool operator>(const Avocat& a, const Avocat& b){
    if(a.nr_procese>b.nr_procese) return 1;
    return 0;
}

///Avocat oficiu
class Avocat_Oficiu:public Avocat{
    static int NrAvocatiOficiu;
    int durata;
    string nume_client;
public:
    //constructori si destructori
    Avocat_Oficiu(){
        durata=0; nume_client="Client necunoscut"; NrAvocatiOficiu++;
    }
    Avocat_Oficiu(string nume, int cod, int nr_procese, int* vect, int durata, string nume_client): Avocat(nume, cod, nr_procese, vect){
        this->durata=durata;
        this->nume_client=nume_client;
        NrAvocatiOficiu++;
    }
    Avocat_Oficiu(const Avocat_Oficiu& a): Avocat(a){
        nume_client=a.nume_client;
        durata=a.durata;
        NrAvocatiOficiu++;
    }
    ~Avocat_Oficiu(){
        //cout<<"\nDestructor clasa derivata\n";
    }

    //Supraincarcare de operatori
    friend istream& operator>>(istream& in, Avocat_Oficiu& a);
    friend ostream& operator<<(ostream& out, const Avocat_Oficiu& a);
    Avocat_Oficiu& operator=(const Avocat_Oficiu& a);

    static void afisNrAvocatiOficiu(){
        cout<<"\nNumarul de avocati din oficiu este:"<<NrAvocatiOficiu<<endl;
    }
    void afisare(){
        this->Avocat::afisare();
        cout<<"\nNume client:"<<nume_client<<"\nDurata petrecuta cu clientul:"<<durata;
    }
    int get_durata() { return durata; }


};
int Avocat_Oficiu::NrAvocatiOficiu;

istream& operator >>(istream& in, Avocat_Oficiu& a)
{
    in >> (Avocat&) a;
    cout << "\nNumele clientului: ";
    in >> a.nume_client;
    cout << "\nTimpul petrecut cu clientul: ";
    in >> a.durata;
    return in;
}
ostream& operator <<(ostream& out, const Avocat_Oficiu& a)
{
    out << (Avocat&) a;
    out << "\nNume client: " << a.nume_client;
    out << "\nTimpul petrecut cu clientul: " << a.durata;
    return out;
}
Avocat_Oficiu& Avocat_Oficiu::operator =(const Avocat_Oficiu& a)
{
    Avocat::operator=(a);
    nume_client = a.nume_client;
    durata = a.durata;
    return *this;
}


void TimpMaxim(Avocat_Oficiu *v,int n)
    {
        int vmax = -1, d, poz;
        Avocat_Oficiu rasp;
        for(int i = 0; i < n; i++)
        {
            d = v[i].get_durata();
            if(d > vmax)
            {
                vmax = d;
                rasp = v[i];
                poz = i+1;
            }
        }
        cout << "\nAvocatul " << poz << " a petrecut cel mai mult timp cu clientul sau: " << vmax << "\nDatele despre avocat si client:"<<rasp;
    }

void cerinta1(){
    Avocat **v;
    int n;
    try
    {
        cout << "Dati numarul de avocati: ";
        cin >> n;
        if(n <= 0) throw 0;
    }
    catch(int x)
    {
        cout << "Dimensiunea vectorului nu poate fi nula sau negativa!";
        exit(EXIT_FAILURE);
    }
    v=new Avocat*[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Introduceti datele despre avocatul "<<i+1<<":"<<endl;
        v[i]= new Avocat();
        cin>>*v[i];
    }
    int ordonat=0;
    do
    {
        ordonat=1;
        for(int i=0;i<n-1;i++)
            if(*v[i]>*v[i+1])
            {
                Avocat *aux;
                aux = new Avocat();
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                ordonat = 0;
            }

    }
    while(ordonat==0);
    cout<<endl<<"Avocatii sortati crescator in functie de numarul de procese sunt:";
    for(int i=0;i<n;i++)
        v[i]->afisare();
}

void cerinta2(){
    Avocat_Oficiu **v;
    int n;
    try
    {
        cout << "Dati numarul de avocati: ";
        cin >> n;
        if(n <= 0) throw 0;
    }
    catch(int x)
    {
        cout << "Dimensiunea vectorului nu poate fi nula sau negativa!";
        exit(EXIT_FAILURE);
    }
    v=new Avocat_Oficiu*[n];
    for(int i=0;i<n;i++)
    {
        v[i]=new Avocat_Oficiu();
        cout<<"Introduceti datele despre avocatul din oficiu "<<i+1<<":"<<endl;
        cin>>*v[i];
    }
    TimpMaxim(v[0],n);
}

void cerinta3(){ ///Ilustrarea conceptelor de up-casting si down-casting
    // upcasting
    cout << "Exemplu de upcasting:\n";
    Avocat **persoane;
    int n, optiune;
    try
    {
        cout << "Dati numarul de avocati: ";
        cin >> n;
        cout << "\n";
        if(n <= 0) throw 0;
    }
    catch(int x)
    {
        cout << "Dimensiunea vectorului nu poate fi nula sau negativa! Mai incercati o data.\n";
        return;
    }
    try
    {
        persoane = new Avocat* [n];
    }
    catch(bad_alloc v)
    {
        cout << "AllocationFailure\n";
        exit(EXIT_FAILURE);
    }
    // citire
    for(int i = 0; i < n; i++)
    {
        cout << "\nDati un numar (par-avocat-oficiu, impar-avocat): ";
        cin >> optiune;
        if(optiune % 2 == 0)
        {
            persoane[i]=new Avocat_Oficiu(); ///upcast -memoria heap
            cin >> *dynamic_cast<Avocat_Oficiu*>(persoane[i]); /// downcasting

        }
        else
        {
            persoane[i] = new Avocat();
            cin >> *persoane[i];
        }
    }
    for(int i = 0; i < n; i++)
    {
        persoane[i] -> afisare();
        cout << "\n";
    }
}

int main()
{
    int cerinta;
    cout<<"Cerinta 1:Sortare avocati dupa nr de procese"<<endl;
    cout<<"Cerinta 2:Avocatul din oficiu care a petrecut timpul maxim cu un client"<<endl;
    cout<<"Cerinta 3:Ilustrarea conceptelor de up-casting si down-casting"<<endl;
    cout<<endl<<"Alegeti una dintre cerinte: 1/2/3: ";
    cin>>cerinta;
    if(cerinta==1)
        cerinta1();
    else if(cerinta==2)
            cerinta2();
        else if(cerinta==3)
            cerinta3();
            else cout<<"Cerinta inexistenta!";
    return 0;


}


