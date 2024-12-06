#include <iostream>
#include <stdexcept>

template <typename T>
class Dizionario {
private:
    static const int TABLE_SIZE = 100; // Dimensione fissa della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false;
    };

    Entry table[TABLE_SIZE];

    // Funzione hash di base
    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE; // Algoritmo di hashing semplice
        }
        return hash % TABLE_SIZE;
    }

    // Trova il prossimo slot disponibile utilizzando il linear probing
    int findSlot(int initialIndex) const {
        int index = initialIndex;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE; // Linear Probing: Si sposta alla posizione successiva
            if (index == initialIndex) {
                throw std::overflow_error("Table is full");
            }
        }
        return index;
    }

public:
    // Metodo per aggiungere una coppia chiave-valore
    void inserisci(const std::string& key, const T& value) {
        int index = hashFunction(key);

        if (table[index].isOccupied && table[index].key != key) {
            index = findSlot(index);
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    // Metodo per cancellare una coppia chiave-valore
    void cancella(const std::string& key) {
        int index = hashFunction(key);

        if (table[index].isOccupied && table[index].key != key) {
            while (table[index].isOccupied && table[index].key != key) {
                index = (index + 1) % TABLE_SIZE; // Linear Probing: Si sposta alla posizione successiva
                if (!table[index].isOccupied) {
                    std::cerr << "Key " << key << " not found.\n";
                    return;
                }
            }
        }

        if (table[index].isOccupied) {
            table[index].isOccupied = false;
            std::cout << "Key " << key << " removed.\n";
        } else {
            std::cerr << "Key " << key << " not found.\n";
        }
    }

    // Metodo per ottenere il valore associato a una chiave
    T recupera(const std::string& key) const {
        int index = hashFunction(key);

        if (table[index].isOccupied && table[index].key != key) {
            while (table[index].isOccupied && table[index].key != key) {
                index = (index + 1) % TABLE_SIZE; // Linear Probing: Si sposta alla posizione successiva
                if (!table[index].isOccupied) {
                    throw std::runtime_error("Key not found!");
                }
            }
        }

        if (table[index].isOccupied) {
            return table[index].value;
        } else {
            throw std::runtime_error("Key not found!");
        }
    }

    // Metodo per verificare se una chiave è presente nel dizionario
    bool appartiene(const std::string& key) const {
        int index = hashFunction(key);

        if (table[index].isOccupied && table[index].key != key) {
            while (table[index].isOccupied && table[index].key != key) {
                index = (index + 1) % TABLE_SIZE; // Linear Probing: Si sposta alla posizione successiva
                if (!table[index].isOccupied) {
                    return false;
                }
            }
        }

        return table[index].isOccupied;
    }

    // Metodo per stampare il contenuto del dizionario
    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};
