
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Contador{

private:
bool docVacio(ifstream& doc){

    if ( doc.peek() == ifstream::traits_type::eof() )
        {
          return true;
        }
    return false;

}
public:
    string S;
    int lBlanco = 0;
    int lCom = 0;
    int lCod = 0;
    int lCorchetes = 0;
    int m = 0;
    int item = 0;
    int b = 0;
    int t = 0;
    int A = 0;
    int d =0 ;
    bool com = false;
    bool iCom =  false;
    bool eof = true;
    bool vacio =false;
    bool blancof =false;
    bool corchetesF = false;
    bool abierto = false;

    void lector(ifstream& doc,string name){

        vacio = docVacio(doc);
        while (getline(doc, S)  || (doc.eof() && eof)) {
            lCod++;

            if(doc.eof()){
                eof = false;

            }
            if(eof== false && (S.empty()== true)  ){
                vacio == true;
            }




    // --------------------------------------------- lab 2----------------------------------------
            for(int i =0; i <= S.size(); i ++){

                // checa comentarios simples
                if(S[i] == '/' && S[i+1] == '/' && S[i+2] != '.' && !(S[i+2] == 'w' && S[i+3] == 'w' && S[i+4] == 'w')){

                    lCom ++;
                    break;
                }

                // checa lineas modificadas (m)
                else if(S[i] == '/' && S[i+1] == '/' && S[i+2] == '.' && S[i+3] == 'm' && !com){


                    for(int j = i-1; j >= 0; j --){
                      if(!isspace(S[j])  ){
                            m++;

                            break;
                        }else if(j == 0){
                            m++;

                            lCom ++;
                            break;
                        }
                    }
                }
                // checa numero de items (i)
               else if(S[i] == '/' && S[i+1] == '/' && S[i+2] == '.' && S[i+3] == 'i' && !com){

                    int si =  S.size();
                    if(!isspace(S[0])){

                        for(int x = 0; x <= S.size(); x++){
                                S[si] = S[si -1];
                                si --;
                               if(si == 0){
                                    S[0] = ' ';
                                }

                        }
                    }
                    for(int j = i-1; j >= 0; j --){


                        if(!isspace(S[j])){
                            item++;
                            //cout << "item es: " << item << "\n";
                            break;
                        }else if(j == 0){
                            item++;
                           // cout << "item es: " << item << "\n";
                           // cout<<"entre a comentarios item \n";
                            lCom ++;
                            break;
                        }
                    }
                }
                // checa numero de lineas borradas (d)
                else if(S[i] == '/' && S[i+1] == '/' && S[i+2] == '.' && S[i+3] == 'd' && !com){


                    string q="";

                    q += S[i+5] ;
                    int n = 6;
                    while( (S[i+n] == '0') || (S[i+n] == '1')|| (S[i+n] == '2')|| (S[i+n] == '3') || (S[i+n] == '4')|| (S[i+n] == '5')|| (S[i+n] == '6')|| (S[i+n] == '7')|| (S[i+n] == '8')|| (S[i+n] == '9')){
                        q += S[i+n] ;
                        n++;
                    }
                    int dTemp = stoi(q);
                    for(int j = i-1; j >= 0; j --){

                        if(!isspace(S[j]) ){
                            d+= dTemp;
                           // cout << "deleted es: " << d << "\n";
                            break;
                        }else if(j == 0){
                            d+= dTemp;
                          //  cout << "deleted es: " << d << "\n";
                            lCom ++;
                            break;
                        }
                    }
                }
                // checa numero de lineas base (b)
                else if(S[i] == '/' && S[i+1] == '/' && S[i+2] == '.' && S[i+3] == 'b' && !com){//intentar ingresar '\.'

                    string w="";
                    int n = 6;
                    int si =  S.size();
                    if(!isspace(S[0])){

                        for(int x = 0; x <= S.size(); x++){
                                S[si] = S[si -1];
                                si --;
                                if(si == 0){
                                    S[0] = ' ';
                                }
                        }
                        n= 7;
                        w += S[i+6] ;
                    }else{

                        w += S[i+5] ;
                    }

                    while( (S[i+n] == '0') || (S[i+n] == '1')|| (S[i+n] == '2')|| (S[i+n] == '3') || (S[i+n] == '4')|| (S[i+n] == '5')|| (S[i+n] == '6')|| (S[i+n] == '7')|| (S[i+n] == '8')|| (S[i+n] == '9')){
                        w += S[i+n] ;
                        n++;
                    }
                    int bTemp = stoi(w);
                    for(int j = i-1; j >= 0; j --){
                        if(!isspace(S[j]) ){
                            b+= bTemp;
                           // cout << "base es: " << b << "\n";
                            break;
                        }else if(j == 0){
                           // cout<<"entre a comentarios base \n";
                            b+= bTemp;
                           // cout << "base es: " << b << "\n";
                            lCom ++;
                            break;
                        }
                    }
                }
            }

       //----------------------------------- coments ------------------------------

            for(int i = 0; i < S.size(); i++){
                if (com && ( S.empty())){// com ----> bandera para saber si entro a coment
                    lCom ++;
                    lBlanco --;
                    break;
                }else if(com){
                    lCom ++;
                   // lCod--;//--------------checar
                    break;
                }
             }

            for(int i = 0; i < S.size(); i++){
            if(S[i+1] == '/' && S[i] ==  '*'){//-------------------- */
                  //  cout<<"entre a comentario */ \n" ;
                    com = false;

                    break;
                }

            }
           for(int i = 0; i < S.size(); i++){


                if(S[i+1] == '*' && S[i] ==  '/'){//------------------- /*
                      //  cout<<"entre a comentario /* \n" ;
                        com = true;
                        abierto = true;
                        lCom ++;//-------------------------------------checar
                        break;
                    }
             }

             if(abierto){
                 for(int i = 0; i < S.size(); i++){
                    if(S[i+1] == '/' && S[i] ==  '*'){
                        com= false;

                    }
                 }


             }


//------------------------------ lineas en blanco-------------------------------

        if(S.empty() ){
            lBlanco ++;

        }

      //  blancof =false;
        for(int i = 0; i < S.size(); i++){
            if(isspace(S[i]) ){
                blancof = true;
            }else{
                blancof =false;
                break;
            }

        }

        if(blancof)
        {
            lBlanco++;
        }

 //----------------------------------- corchetes ------------------------------
            int j =0;
            bool corcheteExiste = false;
            j = 0;
            corcheteExiste = false;
            corchetesF = false;
            for(int i = 0; i < S.size(); i++){//-----------------------checa que el corchete exista en la linea de codigo
                if((S[i] == '{') || (S[i] == '}')){
                    j =i;
                    corcheteExiste = true;
                    break;
                }
            }

            if(corcheteExiste ){// -------------------checar antes del corchete
                if( j == 0 ){
                    corchetesF = true;
                }
                for(int r = j - 1; r >=0; r--){
                    if( isspace(S[r]) ){
                    corchetesF = true;
                }else{
                    corchetesF =false;
                    corcheteExiste = false;
                    break;
                    }
                }
            }


            if(corcheteExiste ){
            for(int i = j +1; i < S.size(); i++){ //----------- checar despues del corchete
                if( (S[i] == ';') || (isspace(S[i]) )){
                    corchetesF = true;
                }else{
                    corchetesF =false;
                    break;
                    }
             }
        }

        if(corchetesF)
        {
                lCorchetes++;
        }

//-------------------------------------------------------------------------------------------------------------------
        }

        lCod = lCod - lBlanco - lCom - lCorchetes;
        t = lCod;
        A = t-b+d;


    }
};

class Tipos{
public:

    string tipo( int A, int  B, int M , int D){
        if(B > 0 && ( M >0 || D> 0 || A> 0)){
            return "Base";
        }else if(B == 0 &&  M  == 0 && D ==  0 && A > 0){
            return "Nueva";
        }else if(B > 0 &&  M  == 0 && D ==  0 && A == 0){
            return "Reusada";
        }

    };


};


class Respuesta{

    public:
        void resultados(int lCod,int lBlanco, int lCom, int T, int I,int B, int D,int M, int A, string nombre, bool vacio, string base){
        int total= lCod + lBlanco + lCom;
        if(total == 0){
            cout << "Nombre del archivo: " << nombre<< "\n";
            cout << "--------------------------------------------"<<"\n";
            cout << "---------------- Archivo inexistente -------------"<< "\n";

        }
        else if(vacio == true){
            cout << "Nombre del archivo: " << nombre<< "\n";
            cout << "--------------------------------------------"<<"\n";
            cout << "---------------- Archivo vacio -------------"<< "\n";

        }else {
            cout << "ClaseS " << base << ":\n";
            cout << '\t'<<nombre << ": " << " T="<< T<< "," << " I="<<I << ","<<" B=" << B << ","<<" D="<< D << ","<< " M="<< M << ","<< " A="<< A <<"\n";
            cout << "----------------------------------------------------------------------------"<<"\n";

        }
    }

};


struct Vertex{
    int lCod;
    int lBlanco;
    int lCom;
    int T;
    int I;
    int B;
    int D;
    int M;
    int A;
    string nombre;
    bool vacio;
    string base;
    string nombreSinTerminacion;

};


int main ()
{
string type;
string archivo;
string exit = " ";
cin >> archivo ;
string temp = "";
vector<Vertex> r;
Respuesta respuesta;
int unica = 0;
string baseUnica;
string nombreSinTerminacion;
int LCD =0;
    while( exit != "exit"){
    nombreSinTerminacion = "";

        ifstream doc(archivo);
//--------------- extraer nombre sin terminacion

        string f= " ";
        for(int i = 0 ; i < archivo.size(); i++){

            f = archivo[i];
            nombreSinTerminacion.append(f);

            if(archivo[i+1] == '.'){
                break;
            }
        }

// ------------ clases

        Contador contador;
        contador.lector(doc, archivo);


        Tipos tipos;
        type =tipos.tipo(contador.A,contador.b, contador.m, contador.d);

         r.push_back({contador.lBlanco,contador.lCom , contador.lCod,contador.t,contador.item,contador.b,contador.d, contador.m,contador.A, archivo, contador.vacio,type, nombreSinTerminacion});


//------------ checo si ya es el fin de los archivos

        cin >> temp ;
        if(temp == "exit"){
            exit = temp;
        }else{
            archivo = temp;
        }
    }
LCD = 0;
        for(int i = 0; i < r.size(); i++){

            if(r[i].nombreSinTerminacion == r[i+1].nombreSinTerminacion && i != r.size() -1){
                r[i+1].lBlanco += r[i].lBlanco;
                r[i+1].lCom += r[i].lCom;
                r[i+1].lCod += r[i].lCod;
                r[i+1].T += r[i].T;
                r[i+1].I += r[i].I;
                r[i+1].B += r[i].B;
                r[i+1].D += r[i].D;
                r[i+1].M += r[i].M;
                r[i+1].A += r[i].A;


                //r[i+1].nombre = r[i+1]nombreSinTerminacion;
               // respuesta.resultados(r[i+1].lBlanco ,r[i+1].lCom , r[i+1].lCod,r[i+1].T,r[i+1].I,r[i+1].B,r[i+1].D, r[i+1].M,r[i+1].A ,r[i+1].nombreSinTerminacion, r[i+1].vacio,r[i+1].base);
                //break;
            }else{
               respuesta.resultados(r[i].lBlanco ,r[i].lCom , r[i].lCod,r[i].T,r[i].I,r[i].B,r[i].D, r[i].M,r[i].A ,r[i].nombreSinTerminacion, r[i].vacio,r[i].base);

            }
             LCD = LCD + r[i].T;
        }

        cout<< "Total de LCD=" << LCD;
    }
