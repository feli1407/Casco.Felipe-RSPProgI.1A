#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
int id;
char marca[20];
int tipo;
float peso;
}eVehiculo;

eVehiculo* vehiculo_new();
void vehiculo_delete(eVehiculo* p);
eVehiculo* vehiculo_newParametros(char* idStr,char* marcaStr,char* tipoStr,char* pesoStr);

int vehiculo_setId(eVehiculo* this,int id);
int vehiculo_getId(eVehiculo* this,int* id);
int vehiculo_setMarca(eVehiculo* this,char* marca);
int vehiculo_getMarca(eVehiculo* this,char* marca);
int vehiculo_setTipo(eVehiculo* this,int tipo);
int vehiculo_getTipo(eVehiculo* this,int* tipo);
int vehiculo_setPeso(eVehiculo* this,float peso);
int vehiculo_getPeso(eVehiculo* this,float* peso);

int saveAsText(char* path, eVehiculo* vehiculo);
int saveAsBinary(char* path, eVehiculo* vehiculo);

int main()
{
    eVehiculo* nuevoVehiculo = vehiculo_newParametros("1234","Pirulo","5","49.6");

    saveAsText("vehiculos",nuevoVehiculo);
    saveAsBinary("vehiculosbin",nuevoVehiculo);

    return 0;
}

eVehiculo* vehiculo_new()
{
    eVehiculo* nuevoVehiculo = (eVehiculo*) malloc(sizeof(eVehiculo));

    if(nuevoVehiculo!=NULL)
    {
        nuevoVehiculo->id=0;
        strcpy(nuevoVehiculo->marca, "");
        nuevoVehiculo->tipo=0;
        nuevoVehiculo->peso=0;
    }

    return nuevoVehiculo;
}

void vehiculo_delete(eVehiculo* p)
{
    free(p);
}

eVehiculo* vehiculo_newParametros(char* idStr,char* marcaStr,char* tipoStr,char* pesoStr)
{
    eVehiculo* nuevoVehiculo = vehiculo_new();
    if(nuevoVehiculo!=NULL)
    {
        if(!(vehiculo_setId(nuevoVehiculo,atoi(idStr)) &&
                vehiculo_setMarca(nuevoVehiculo,marcaStr) &&
                vehiculo_setTipo(nuevoVehiculo,atoi(tipoStr)) &&
                vehiculo_setPeso(nuevoVehiculo,atof(pesoStr))
            ))
        {
            vehiculo_delete(nuevoVehiculo);
            nuevoVehiculo = NULL;
        }
    }

    return nuevoVehiculo;
}

int vehiculo_setId(eVehiculo* this,int id)
{
    int todoOk=0;
    if(this!=NULL && id > 0)
    {
        this->id=id;
        todoOk=1;
    }
    return todoOk;
}
int vehiculo_getId(eVehiculo* this,int* id)
{
    int todoOk=0;
    if(this!=NULL && id !=NULL)
    {
        *id = this->id;
        todoOk=1;
    }
    return todoOk;
}

int vehiculo_setMarca(eVehiculo* this,char* marca)
{
    int todoOk=0;
    if(this!=NULL && marca != NULL && strlen(marca)<128 && strlen(marca)>2)//validacion 20 caracteres y no menos de 2 caracteres
    {
        strcpy(this->marca, marca);
        todoOk=1;
    }
    return todoOk;
}
int vehiculo_getMarca(eVehiculo* this,char* marca)
{
    int todoOk = 0;
    if(marca != NULL && this != NULL)
    {
        strcpy(marca, this->marca);
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_setTipo(eVehiculo* this,int tipo)
{
    int todoOk=0;
    if(this!=NULL && tipo > 0)
    {
        this->tipo=tipo;
        todoOk=1;
    }
    return todoOk;
}
int vehiculo_getTipo(eVehiculo* this,int* tipo)
{
    int todoOk=0;
    if(this!=NULL && tipo !=NULL)
    {
        *tipo = this->tipo;
        todoOk=1;
    }
    return todoOk;
}

int vehiculo_setPeso(eVehiculo* this,float peso)
{
    int todoOk=0;
    if(this!=NULL && peso > 0)
    {
        this->peso=peso;
        todoOk=1;
    }
    return todoOk;
}
int vehiculo_getPeso(eVehiculo* this,float* peso)
{
    int todoOk=0;
    if(this!=NULL && peso !=NULL)
    {
        *peso = this->peso;
        todoOk=1;
    }
    return todoOk;
}

int saveAsText(char* path, eVehiculo* vehiculo)
{
    FILE* f;
    int todoOk=0;
    int auxId;
    char auxMarca[20];
    int auxTipo;
    float auxPeso;

    if(vehiculo!=NULL && path!=NULL)
    {


        f=fopen(path,"w");

        vehiculo_getId(vehiculo,&auxId);
        vehiculo_getMarca(vehiculo,auxMarca);
        vehiculo_getTipo(vehiculo,&auxTipo);
        vehiculo_getPeso(vehiculo,&auxPeso);

        fprintf(f,"%d,%s,%d,%f\n",auxId,auxMarca,auxTipo,auxPeso);


        todoOk=1;
        fclose(f);
    }

    return todoOk;
}
int saveAsBinary(char* path, eVehiculo* vehiculo)
{
    FILE* f =NULL;
    int todoOk=0;

    f=fopen(path,"wb");
    if(vehiculo != NULL && f!=NULL)
    {
        fwrite(vehiculo,sizeof(eVehiculo),1,f);
        todoOk=1;
        fclose(f);
    }
    return todoOk;
}
