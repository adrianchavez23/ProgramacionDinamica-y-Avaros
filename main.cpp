#include <iostream>
#include <vector>
using namespace std;

//Complejidad computacional: T(n) = O(n),   T(n) = Omega(1)
vector<int> avaro(vector<int> denominaciones, int n, int p, int q){  
    int cambio = q - p;
    vector<int> res;

    if (cambio == 0){
        res.push_back(0);
        return res;
    }

    //Escoge la mayor moneda que sea menor o igual a lo que quede de cambio
    while(cambio != 0){                                
        for(int i = 0; i < n; i++){   
            if(denominaciones[i] <= cambio){
                cambio = cambio - denominaciones[i];
                res.push_back(denominaciones[i]);
                break;
            }
        }
    } // Hace una cantidad constante de operaciones por moneda. O(n)
    return res;
}


 //Complejidad computacional: T(n) = O(Cambio*n),   T(n) = Omega(1)
vector<int> dinamica(vector<int> denominaciones, int n, int p, int q){ 
    int cambio = q - p;
    
    if(cambio == 0){
        vector<int> v{0};
        return v;
    }

    vector<int> dp(cambio + 1, INT_MAX);
    vector<int> ultimaMoneda(cambio + 1, -1);

    dp[0] = 0;


    for (int i = 1; i <= cambio; ++i) {   //Recorre todos los valores de 0 hasta el cambio. 
        for (int j = 0; j < n; ++j) {     // Recorre las denominaciones de monedas
            if (i >= denominaciones[j] && dp[i - denominaciones[j]] + 1 < dp[i]) {
                dp[i] = dp[i - denominaciones[j]] + 1;
                ultimaMoneda[i] = j;
            }
        }
    }  //Asi que para cada valor hasta llegar a el cambio, se determina el numero minimo 
       //de monedas para completar recorriendo todas monedas que hay. O(cambio*n).

    //Forma el vector de monedas utilizadas
    vector<int> monedasUtilizadas;    
    int idx = cambio;
    while (idx > 0) {
        int monedaIdx = ultimaMoneda[idx];
        monedasUtilizadas.push_back(denominaciones[monedaIdx]);
        idx -= denominaciones[monedaIdx];
    }

    return monedasUtilizadas;
  
}

void printVect(vector<int> i) {
    for (double x : i)
        cout << x << " ";
}


int main()
{
    vector<int> res;

    //CASO 1: Resultados diferentes
    vector<int> monedas1{4,3,1};
    int P1 = 50;
    int Q1 = 56;

    //CASO 2: Resultados diferentes
    vector<int> monedas2{5,4,1};
    int P2 = 32;
    int Q2 = 40 ;

    //CASO 3: El cambio es 0
    vector<int> monedas3{10,5,2,1};
    int P3 = 26;
    int Q3 = 26;

    //CASO 4: Mismos resultados
    vector<int> monedas4{64,32,16,8,4,2,1};
    int P4 = 127;
    int Q4 = 200;

    vector<vector<int>> casosMonedas{monedas1, monedas2, monedas3, monedas4};
    vector<int> casosPrecios{P1,P2,P3,P4};
    vector<int> casosPagos{Q1,Q2,Q3,Q4};
    
    for (int i = 0; i < 4; i++){
        cout << "CASO " << i+1 << endl;
        cout << "- Denominaciones: ";
        printVect(casosMonedas[i]);
        cout << "\n- Precio: " << casosPrecios[i] << endl;
        cout << "- Pagos: " << casosPagos[i] << endl;
        cout << "\n- Cambio: "<< casosPagos[i] - casosPrecios[i] << endl;
        res = avaro(casosMonedas[i], casosMonedas[i].size(), casosPrecios[i], casosPagos[i]);
        cout << "- Monedas usadas ALGORITMO AVARO: ";
        printVect(res);
        res = dinamica(casosMonedas[i], casosMonedas[i].size(), casosPrecios[i], casosPagos[i]);
        cout << "\n- Monedas usadas PROGRAMACION DINAMICA: ";
        printVect(res);
        cout << endl;
    }
}