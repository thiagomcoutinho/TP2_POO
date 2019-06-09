#include "./../Headers/Interface.h"
#include<iostream>
#include<map>

#include <string>

using namespace std;

vector<string> split_string(string str_date){

    vector<string> date_split;
    string aux;

    for(int i=0; i<str_date.size(); i++){
        if(str_date[i] == '-'){
            date_split.push_back(aux);
            aux.clear();
        }else{
            aux.push_back(str_date[i]);
        }
    }
    date_split.push_back(aux);

    cout << date_split[0] << endl;
    cout << date_split[1] << endl;
    cout << date_split[2] << endl;

    /* if(date_split.size() != 3 || date_split[0].size() != 2 || date_split[1].size() != 2 || date_split[2].size() != 4){
        throw Excecao("Formato de data invalido!");
    }*/

    int dia, mes, ano;
    dia = stoi(date_split[0]);
    mes = stoi(date_split[1]);
    ano = stoi(date_split[2]);

    return(date_split);
}

int main(int argc, char **arvg){

    //split_string("10-11-1995");


    Interface i;

    map<string, Plano*> hash_planos;

    Date d(2019, 10, 11);
    PosPago p1("TIM", 10, 100, 10, 10, d);

    Plano* p = &p1;

    hash_planos.insert(make_pair("TIM", p));
    if(hash_planos.find("TIM") != hash_planos.end()){
        std::cout<<"Plano 'TIM' found"<<std::endl;
    }else{
        cout << "FOI" << endl;
    }

    Plano *p2;
    p2 = p;
    p->cobraCusto(1000);
    PosPago* ptr_plano = dynamic_cast<PosPago*>(p);
    cout << ptr_plano->getValor() << endl;

    PosPago* ptr_plano2 = dynamic_cast<PosPago*>(p2);
    cout << ptr_plano->getValor() << endl;

    cout << stoi("123");


    // CLIENTE OK
    /*
    Cliente c("120.704", "Thiago", "Viotti");
    cout << c.getNome() << endl;
    cout << c.getCPF() << endl;
    cout << c.getEndereco() << endl;

    Cliente* ptr_client;
    ptr_client = &c;

    // DATE
    Date d(2019, 10, 11);

    // PLANO
    PosPago p1("TIM", 10, 100, 10, 10, d);
    cout << p1.getFranquia() << endl;

    Plano* p = &p1;

    // CELULAR
    Celular t(*ptr_client, *p);
    cout << t.getProxNumCelular() << endl;

    t.ligar(d, 100, 87448327);
    vector<Ligacao> l = t.getLigacoes();
    cout << l[0].getCusto() << endl;

    tipoDados down = download;
    tipoDados up = upload;

    t.ligar(100, download, d);
    vector<Ligacao> k = t.getLigacoes();
    cout << k[1].getCusto() << endl;

    cout << p->getFranquiaGasta() << endl;
    //Interface i;

    */

    /* FUNCAO DE SALVAR E LER OBJETOS ( SALVAR UM VECTOR, MELHOR )


        // C++ program to demonstrate read/write of class 
        // objects in C++. 
        #include <iostream> 
        #include <fstream> 
        using namespace std; 
        
        // Class to define the properties 
        class Contestant { 
        public: 
            // Instance variables 
            string Name; 
            int Age, Ratings; 
        
            // Function declaration of input() to input info 
            int input(); 
        
            // Function declaration of output_highest_rated() to 
            // extract info from file Data Base 
            int output_highest_rated(); 
        }; 
        
        // Function definition of input() to input info 
        int Contestant::input() 
        { 
            // Object to write in file 
            ofstream file_obj; 
        
            // Opening file in append mode 
            file_obj.open("Input.txt", ios::app); 
        
            // Object of class contestant to input data in file 
            Contestant obj; 
        
            // Feeding appropriate data in variables 
            string str = "Micheal"; 
            int age = 18, ratings = 2500; 
        
            // Assigning data into object 
            obj.Name = str; 
            obj.Age = age; 
            obj.Ratings = ratings; 
        
            // Writing the object's data in file 
            file_obj.write((char*)&obj, sizeof(obj)); 
        
            // Feeding appropriate data in variables 
            str = "Terry"; 
            age = 21; 
            ratings = 3200; 
        
            // Assigning data into object 
            obj.Name = str; 
            obj.Age = age; 
            obj.Ratings = ratings; 
        
            // Writing the object's data in file 
            file_obj.write((char*)&obj, sizeof(obj)); 
        
            return 0; 
        } 
        
        // Function definition of output_highest_rated() to 
        // extract info from file Data Base 
        int Contestant::output_highest_rated() 
        { 
            // Object to read from file 
            ifstream file_obj; 
        
            // Opening file in input mode 
            file_obj.open("Input.txt", ios::in); 
        
            // Object of class contestant to input data in file 
            Contestant obj; 
        
            // Reading from file into object "obj" 
            file_obj.read((char*)&obj, sizeof(obj)); 
        
            // max to store maximum ratings 
            int max = 0; 
        
            // Highest_rated stores the name of highest rated contestant 
            string Highest_rated; 
        
            // Checking till we have the feed 
            while (!file_obj.eof()) { 
                // Assigning max ratings 
                if (obj.Ratings > max) { 
                    max = obj.Ratings; 
                    Highest_rated = obj.Name; 
                } 
        
                // Checking further 
                file_obj.read((char*)&obj, sizeof(obj)); 
            } 
        
            // Output is the highest rated contestant 
            cout << Highest_rated; 
            return 0; 
        } 
        
        // Driver code 
        int main() 
        { 
            // Creating object of the class 
            Contestant object; 
        
            // Inputting the data 
            object.input(); 
        
            // Extracting the max rated contestant 
            object.output_highest_rated(); 
        
            return 0; 
        } 


    */

    return 0;
}