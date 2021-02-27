template<typename T>
string_map<T>::string_map() {
    raiz = new Nodo();
    _size = 0;
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.



template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {

    // borro el contenido del trie this., por si viene con basura
    destruir(this->raiz);
    this->raiz = new Nodo();
    this->_size = 0;

    igualarNodos(this->raiz, d.raiz);
    this->_size = d._size;
    return *this;
}


template<typename T>
void string_map<T>::igualarNodos(Nodo *aCopiar, const Nodo *original) {
    if (original != nullptr) {
        for (int i = 0; i < 255; ++i) {
            if (original->siguientes[i] != nullptr) {
                if (original->siguientes[i]->definicion != nullptr) {
                    T tCopia = *original->siguientes[i]->definicion;
                    Nodo *nodo = new Nodo(new T(tCopia), aCopiar); //error
                    aCopiar->siguientes[i] = nodo;
                    igualarNodos(nodo, original->siguientes[i]);
                } else {
                    Nodo *nodo = new Nodo(aCopiar); //error
                    aCopiar->siguientes[i] = nodo;
                    igualarNodos(nodo, original->siguientes[i]);
                }
            }
        }
    }
}


template<typename T>
string_map<T>::~string_map() {
    destruir(raiz);
}


template<typename T>
void string_map<T>::destruir(Nodo *actuall) {
    if (actuall != nullptr) {
        for (int i = 0; i < 255; ++i) {
            destruir(actuall->siguientes[i]);
        }
        if (actuall->definicion != nullptr) {
            delete actuall->definicion;
        }
    }
    delete actuall;
}



template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR, ,si me queda tiempo despues, lo hago
}



template<typename T>
void string_map<T>::insert(const pair<string, T> &par) {
    Nodo *actual = new Nodo;
    actual->siguientes[0] = raiz;
    //actual->siguientes[0] = raiz;
    for (int i = 0; i < par.first.size(); ++i) { // recorro la palabra VER BIEN ESTO, EXPLOTA AL REDEFINIR
        const char c = par.first[i];
        int ascii = int(c);

        // si queriendo agregar la ultima letra de la clave
        if (i == par.first.size() - 1) {
            if (actual->siguientes[0]->siguientes[int(c)] == nullptr) {
                Nodo *nodo = new Nodo(new T(par.second), actual->siguientes[0]);
                actual->siguientes[0]->siguientes[int(
                        c)] = nodo; // me puede lleagar a perder memoria cuando la def ya estaba
                _size++;

            } else {
                // if (actual->siguientes[0]->siguientes[int(c)]->definicion == nullptr) {
                delete actual->siguientes[0]->siguientes[int(c)]->definicion;
                actual->siguientes[0]->siguientes[int(c)]->definicion = new T(
                        par.second); // ver memoria con la T que ya estaba
                //}
            }
        } else {

            // if el caracter no esta definido
            if (actual->siguientes[0]->siguientes[int(c)] == nullptr) {
                Nodo *nodo = new Nodo(actual->siguientes[0]);
                actual->siguientes[0]->siguientes[int(c)] = nodo;
                actual->siguientes[0] = nodo;
            }
                // si el c no esta def
            else {
                actual->siguientes[0] = actual->siguientes[0]->siguientes[int(c)];
            }
        }
    }
    delete actual;
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    Nodo *actual = new Nodo(); // ver como hacerlo sin new
    actual->siguientes[0] = raiz;


    if (_size == 0) {
        delete actual;
        return 0;
    }

    for (int i = 0; i < clave.size(); ++i) {
        char c = clave[i];
        if (i == clave.size() - 1) {
            if (actual->siguientes[0]->siguientes[int(c)]->definicion == nullptr) { // aca exploto
                delete actual;
                return 0;
            } else {
                delete actual;
                return 1;
            }
        } else if (actual->siguientes[0]->siguientes[int(c)] == nullptr) {
            delete actual;
            return 0;
        } else {
            actual->siguientes[0] = actual->siguientes[0]->siguientes[int(c)];
        }
    }
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *actual = new Nodo;
    actual->siguientes[0] = raiz;
    for (int i = 0; i < clave.size() - 1; ++i) {
        const char c = clave[i];
        actual->siguientes[0] = actual->siguientes[0]->siguientes[int(c)];
    }
//    const T t = actual->definicion;
    const T t = actual->siguientes[0]->siguientes[int(clave[clave.size() - 1])]->definicion;
    delete actual;
    return t;

}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *actual = new Nodo;
    actual->siguientes[0] = raiz;
    for (int i = 0; i < clave.size() - 1; ++i) {
        const char c = clave[i];
        actual->siguientes[0] = actual->siguientes[0]->siguientes[int(c)]; // ROMPEE
    }
    //T t = actual->definicion;
    T *t = actual->siguientes[0]->siguientes[int(clave[clave.size() - 1])]->definicion;
    //t = actual->definicion;
    delete actual;
    return *t;
}


template<typename T>
void string_map<T>::erase(const string &clave) {
    Nodo *actual = new Nodo;
    actual->siguientes[0] = raiz;

    // apunto con el actual al ultimo nodo de la clave
    for (int i = 0; i < clave.size(); ++i) {
        char c = clave[i];
        actual->siguientes[0] = actual->siguientes[0]->siguientes[int(c)];
    }
    //si es la palabra es intermedia
    if (cantidadHijos(actual->siguientes[0]) > 0) {
        delete actual->siguientes[0]->definicion; // borro la definicion que tenia
        actual->siguientes[0]->definicion = nullptr; // como apunta a basura, ahora la seteo en null
    } else {

        //Si la denicion esta en una hoja, borrar todo el camino hasta
        //la hoja que no sea necesario para alguna otra definicion y
        //Si es la unica denicion del Trie, borrar todo y dejar la raz
        //apuntando a NULL

        borrado_recursivo(actual, clave, clave.size() - 1);
    }
    delete actual;
    _size--;
}

template<typename T>
void string_map<T>::borrado_recursivo(Nodo *actuall, const string &clave, int posChar) {

    // caso base, si el padre es raiz o el padre tiene mas hijos
    if (actuall->siguientes[0]->padre->padre == nullptr || cantidadHijos(actuall->siguientes[0]->padre) > 1) {
        actuall->siguientes[0]->padre->siguientes[int(clave[posChar])] = nullptr; // nulleo el lazo de padre a hijo
        delete actuall->siguientes[0]->definicion;
        delete actuall->siguientes[0];
    } else {
        actuall->siguientes[1] = actuall->siguientes[0]; //apunto al elemento ue voy a borrar
        actuall->siguientes[0] = actuall->siguientes[0]->padre; // seteo el padre
        delete actuall->siguientes[1]->definicion; // borro la def
        delete actuall->siguientes[1]; // borro al nodo
        borrado_recursivo(actuall, clave, posChar - 1);

    }
}

template<typename T>
int string_map<T>::cantidadHijos(const Nodo *actual) {
    int hijos = 0;
    for (int i = 0; i < 255; ++i) {
        if (actual->siguientes[i] != nullptr) {
            hijos++;
        }
    }
    return hijos;
}


template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}
