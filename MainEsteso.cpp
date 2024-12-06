#include <iostream>
#include "DizionarioEsteso.cpp"

int main() {
    DizionarioEsteso<std::string> dizionario;

    dizionario.inserisci("leone", "savanna");
    dizionario.inserisci("orso", "foresta");
    dizionario.inserisci("pinguino", "antartide");
    dizionario.inserisci("delfino", "oceano");  
    dizionario.inserisci("canguro", "australia");   

    
    dizionario.stampa();

    
    std::cout << "Recupera 'orso': " << dizionario.recupera("orso") << std::endl;

    
    dizionario.cancella("delfino");
    dizionario.stampa();

    
    std::cout << "Appartiene 'canguro': " << dizionario.appartiene("canguro") << std::endl;

    return 0;
}
