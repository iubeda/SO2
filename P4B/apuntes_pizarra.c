/// un solo productor y un solo consumidor

int vacio = 1;


/// productor

lock(llave)
    if(!vacio) wait(condP, llave) //condP de productor
    copiar a buffer
    vacio = 0;
    signal(condC)  //condC de consumidor
unlock(llave)



/// consumidor

lock(llave)
    if(vacio) wait(condC, llave)
    coger dato del buffer
    vacio = 1
    signal(condP)
unlock(llave)
/// varios productores y un solo consumidor

int vacio = 1;


/// productor

lock(llave)
    while(!vacio) wait(condP, llave) //condP de productor
    copiar a buffer
    vacio = 0;
    signal(condC)  //condC de consumidor
unlock(llave)



/// consumidor

lock(llave)
    while(vacio) wait(condC, llave)
    coger dato del buffer
    vacio = 1
    signal(condP)
unlock(llave)
