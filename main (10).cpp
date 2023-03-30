#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
using namespace std;


struct wierzcholek{

    string oligo;
    int skad;
    int poczatek;

};

bool porownaj(wierzcholek a, wierzcholek b)
{
    if((a.oligo == b.oligo) && (a.skad == b.skad) && (a.poczatek == b.poczatek))
        return true;
    else
        return false;

}
void odczyt1(vector<char> sekwencje[], vector<int> wiar[], vector<string> nazwy[])
{

    vector<int> temp1;
    vector<string> temp2;
    string tekst;
    string temp = "";


    ifstream fasta("instancja1.fasta");
    ifstream qual("instancja2.qual");

    int m, n=0;
    char c;



    while(getline(fasta, tekst)){

        if(tekst[0] == '>'){

            tekst = tekst.substr(0, tekst.find(" ", 0));
            nazwy[n].push_back(tekst);
            n++;

            if(temp.size() != 0){

                for(int i=0; i<temp.size(); i++){

                    sekwencje[m].push_back(temp[i]);
                }
                m++;
                temp.clear();
            }

        }
        else{
            temp.append(tekst);
        }

    }
    //cout<<temp;

    for(int i=0; i<temp.size(); i++){
        sekwencje[m].push_back(temp[i]);
    }

    int liczba;
    int k = -1;

    //cout<<sekwencje[0].size();

    while(getline(qual, tekst)){

        stringstream text_stream(tekst);
        string liczba;

        if(tekst[0] == '>'){
            k++;
        }

        if(tekst[0] != '>'){

            while(getline(text_stream, liczba, ' ')){
                temp1.push_back(stoi(liczba));

            }

            for(int i=0; i<temp1.size(); i++){

                //cout<<i<<endl;

                //cout<<sekwencje[i].size();
                //cout<<endl;
                wiar[k].push_back(temp1.at(i));
            }

        }


        temp1.clear();
    }

    fasta.close();
    qual.close();


}

void usuwanie(vector<char> sekwencje[], vector<int> wiar[], int prog, vector<char> nowe_sekwencje[], vector<int> index[]){

    for(int i=0; i<5; i++){

        for(int j=0; j<wiar[i].size(); j++){

            if(wiar[i].at(j) >= prog){

                index[i].push_back(j+1);

                nowe_sekwencje[i].push_back(sekwencje[i].at(j));


            }

        }

    }


}


void sasiedzi(vector<wierzcholek> kandydaci, vector<wierzcholek> graph[], int N)
{

    vector<wierzcholek> sasiedzi[kandydaci.size()];

    vector<bool> czy_wystepuje;


    bool test;
    wierzcholek sasiad;


    //vector<wierzcholek> klika
    for(int i=0; i<kandydaci.size(); i++){

        for(int j=0; j<N; j++){

            test = porownaj(graph[j][0], kandydaci[i]);

            if( test == true ){

                for(int m=0; m<graph[j].size(); m++){

                    sasiad.oligo = graph[j][m].oligo;
                    sasiad.skad = graph[j][m].skad;
                    sasiad.poczatek = graph[j][m].poczatek;
                    sasiedzi[i].push_back(sasiad);

                    cout<<sasiedzi[i][m].oligo<<" "<<sasiedzi[i][m].skad<<" "<<sasiedzi[i][m].poczatek<<" ";

                }
                cout<<endl;
            }

        }

    }
}


int klika(vector<wierzcholek> graph[], int N)
{



    //cout<<endl<<"SZUKANY MOTYW: "<<motyw<<endl;
    bool sek_1, sek_2, sek_3, sek_4, sek_5;

    int licznik = 0;

    vector<wierzcholek> kandydaci;
    wierzcholek kandydat;
    vector<bool> czy_po4;
    vector<wierzcholek> klika1;

    for(int i=0; i<N; i++){

        if(graph[i].size() > 4){
            //cout<<graph[i][0].oligo<<" "<<graph[i][0].skad<<" "<<graph[i][0].poczatek<<endl;

            for(int j=0; j<graph[i].size(); j++){

                if(graph[i][j].skad == 0)
                    sek_1 = true;
                else if(graph[i][j].skad == 1)
                    sek_2 = true;
                else if(graph[i][j].skad == 2)
                    sek_3 = true;
                else if(graph[i][j].skad == 3)
                    sek_4 = true;
                else if(graph[i][j].skad == 4)
                    sek_5 = true;
            }

            if((sek_1 == true) && (sek_2 == true) && (sek_3 == true) && (sek_4 == true) && (sek_5 == true)){

                for(int j=0; j<graph[i].size(); j++){
                    kandydat.oligo = graph[i][j].oligo;
                    kandydat.skad = graph[i][j].skad;
                    kandydat.poczatek = graph[i][j].poczatek;
                    kandydaci.push_back(kandydat);

                }

                    kandydaci.clear();

                    cout<<"Podciag: "<<graph[i][0].oligo<<" "<<endl;

                    for(int m=0; m<graph[i].size(); m++){

                    cout<<"Nr sekwencji wejsciowej: "<<graph[i][m].skad<<" "<<" || ";
                    cout<<"Nr pozycji: "<<graph[i][m].poczatek<<" "<<" || ";

                    cout<<endl;
                }



                    return 0;







            }
        }
        sek_1 = false;
        sek_2 = false;
        sek_3 = false;
        sek_4 = false;
        sek_5 = false;
    }

}


void graf(vector<char> nowe_sekwencje[], vector<int> index[], vector<string> adj[], vector<int> ind_oligo[], int podciag)
{

    string sekw;
    string temp;

    //cout<<index[0].size();

    for(int i=0; i<5; i++){
        for(int j=0; j<nowe_sekwencje[i].size(); j++){

           temp.push_back(nowe_sekwencje[i].at(j));

        }



        //cout<<temp<<endl;
        //powyzej dostalem string calej sekwencji (wczesniej byl w char)


        for(int m=0; m<temp.size() - podciag + 1; m++){

            sekw = temp.substr(m, podciag);

            adj[i].push_back(sekw);
        }

         temp = "";
         //cout<<endl;

    }

    //po powyzyszch operacjach mam wektor oligonukleotydow dla kazdej z instancji



    //vector<int> ind_oligo[5]; //tu znajda sie pierwsze indeksy kazdego z oligonukleotydow

    for(int i=0; i<5; i++){
        for(int j=0; j<adj[i].size(); j++){
            ind_oligo[i].push_back(index[i].at(j));

        }

    }




    int m = 0;

    int suma = 0;

    for(int i=0; i<5; i++){
        suma = suma + adj[i].size();
    }

    vector<wierzcholek> graph[suma];

    wierzcholek nowy;

    for(int i=0; i<5; i++){
        for(int j=0; j<adj[i].size(); j++){

            nowy.oligo = adj[i].at(j);
            nowy.poczatek = ind_oligo[i].at(j);
            nowy.skad = i;

            graph[m].push_back(nowy);
            m++;

        }
    }

    for(int i=0; i<suma; i++){
        //cout<<graph[i][0].oligo<<" "<<graph[i][0].poczatek<<" "<<graph[i][0].skad<<endl;
    }

    wierzcholek nowy1;

    //cout<<graph[0][0].oligo<<endl;

    for(int i=0; i<suma; i++){
        for(int j=0; j<suma; j++){

            if( i != j &&((graph[i][0].oligo == graph[j][0].oligo) && (graph[i][0].skad != graph[j][0].skad) && (abs(graph[i][0].poczatek - graph[j][0].poczatek) <= podciag*10))){

                nowy1.oligo = graph[j][0].oligo;
                nowy1.poczatek = graph[j][0].poczatek;
                nowy1.skad = graph[j][0].skad;

                graph[i].push_back(nowy1);
            }
        }
    }


    vector<wierzcholek> kandydaci;
    wierzcholek kandydat;


    for(int i=0; i<suma; i++){
        kandydat.oligo = graph[i][0].oligo;
        kandydat.poczatek = graph[i][0].poczatek;
        kandydat.skad = graph[i][0].skad;

        kandydaci.push_back(kandydat);

    }


    klika(graph, suma);
    //return graph;

}




int main()
{


    vector<char> sekwencje[5];
    vector<int> wiar[5];
    vector<string> nazwy[5];

    odczyt1(sekwencje, wiar, nazwy);


    int prog;
    int podciag;



    //fflush(stdin);

    cout<<"Podaj prog: ";
    cin>>prog;

    vector<int> index[5];

    vector<char> nowe_sekwencje[5];
    vector<string> adj[5];
    vector<int> ind_oligo[5];


    usuwanie(sekwencje, wiar, prog, nowe_sekwencje, index);


    cout<<"Podaj dlugosc podciagu (zakres od 4 do 9): ";
    cin>>podciag;

    while(podciag < 4 || podciag > 9){
        cout<<"Podaj dlugosc podciagu (zakres od 4 do 9): ";
        cin>>podciag;
    }



    int suma = 0; //tyle wierzcholkow bedzie w grafie


    graf(nowe_sekwencje, index, adj, ind_oligo, podciag);





    return 0;
}
