/*
*******************************************************************************
�Que hace el Programa?        
     Progrma que tiene el siguiente menu:
    - Crear Archivo( Lo unico que hace es crear un archivo: agenda.dat y borrar su contenido, claro si esta ya creado)
    - Agregar (Agrega en el Archivo Binario)
    - Eliminar(Elimina en el Archivo Binario)
    - Listar (Munestra los elementos por medio del Arhcivo Binario)
    - Bucar un Amigo (Busca algun elemento del Archivo, por medio del Archivo Binario) 
    con la sig. informaci�n:     Nombre, Edad, Telefono y Direccion
*******************************************************************************
*/

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>

typedef struct {   
    char nom[25];
    int edad;
    char tel[15];
    char dir[35];
    char cedu[15];
    int estado;
}Amigo;

/*Funciones de Archivo*/
void Crear(void);
void Listar(void);
void Agregar(void);
void Modificar(void);
/*void Borrar(void);*/
void Borradorlog(void);
void Encontrar(void);
void Recuperar(void);
FILE *abrir_fichero_b(char cadena[], int);

/*Nombre del Archivo a guardar*/
char nombre_fichero[] = "agenda.dat";
char borrar_fichero[] = "paso.$$$"; //temporal o de paso para verificar.

FILE *abrir_fichero_b(char cadena[], int metodo);  //abrir archivo y enviamos un numero 

int main()
{
    FILE *fp;
    int opc;
    char cad[3];
    
    fp = abrir_fichero_b(nombre_fichero,0);
    if( fp )  //verificamos si el archivo esta o no esta creado // si esta creado.
    {
        fclose(fp);  //cerramos el archivo
    }
    else
    {
        printf( "Error (NO ABIERTO)\n" ); 
        puts("Presiona cualquier tecla para continuar.... y Crear el Archivo"); //puts=formato para mostrar
        fp = abrir_fichero_b(nombre_fichero,1); //creamos el archivo 
        fclose(fp); //cerramos el archivo
        getch();    }
    
    do{
    system("cls");
        puts("1. Crear Archivo (Cuidado, elimina lo que ya se tiene en el Archivo)");
        puts("2. Agregar\n3. Eliminar\n4. Borrado Logico\n5. Listar\n6. Encontrar\n7. Modificar\n9. Salir");
        puts("?Introduce tu opcion y depues enter.");
        
        opc = atoi(gets(cad));  //atoi funcion propia, convertir en un numero. 
        while(opc<0 || opc>9) /*Limitando la entrada de las opciones*/    
            opc = atoi(gets(cad));
        system("cls");    
        switch(opc)
        {
        case 1:
                Crear();
                break;
        case 2:    
                Agregar();
                break;
        /*case 3:
                Borrar();
                break;*/
        case 4:
                Borradorlog();
                break;
        case 5:
                Listar();
                break;
        case 6:
                 Encontrar();
                break;
        case 7:
        	     Modificar();
        	     break;
        case 8:
		        Recuperar();
				break;
        }
        /*Solo parar cuando sea una de las opciones*/
        if(opc<9)
        {
            puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
            getch();
        }
    }
    while(opc!=9);
    
    return 0;
}

// FUNCION PARA CREAR UN ARCHIVO
/*****************************************************************
Funcion que sirve para borrar todo el Contenido del Archivo Binario*/

void Crear(){      //crea el espacio fisico 
   FILE *fp;

   fp = abrir_fichero_b(nombre_fichero,0);
   if(fp)
   {
        printf("\n Error de apuertura del archivo agenda.dat\n");
        fclose(fp);  
   }
}


/********************************************************
Funcion que sirve para imprimir todos los  un registros del Archivo Binario*/
void Listar(void){
   FILE *fp; //creamos el archivo
   int i=1; 
   Amigo aux;  //amigo es una estructura.
    fp = abrir_fichero_b(nombre_fichero,0);  
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
      printf("\n U S U A R I O S  E N  L A  A G E N D A\n");
      printf("---------------------------------------------------------------\n");
      while ((fread(&aux, sizeof(aux), 1, fp))!=0){
      	if(aux.estado==1){
         printf("=> Datos del Amigo %d\n",i);
         printf("Nombre: %s | Edad: %d | Telefono: %s | Identificacion: %s\n",aux.nom,aux.edad,aux.tel,aux.cedu);
         printf("Direccion: %s\n",aux.dir);
         i++; 
        }
      }
      printf("---------------------------------------------------------------\n");
      fclose(fp);
   }
}

/********************************************************
Funcion que sirve para agregar un registro dentro del Archivo Binario*/
void Agregar(void){
   FILE *fp; //creamos un archivo llamado fp
   Amigo aux;  //una variable auxiliar
   char cad[3];

   printf("\n Agregando un Amigo Nuevo al archivo binario agenda.dat\n");
   fp=abrir_fichero_b(nombre_fichero,2);
   if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
        /*Introduciendo los Datos del Amigo*/
        printf("Dame el nombre del Amigo: ");
        gets(aux.nom);
        printf("Dame la Edad del Amigo: ");
        aux.edad=atoi(gets(cad));
        printf("Dame el telefono del Amigo: ");
        gets(aux.tel);
        printf("Dame la direccion del Amigo: ");
        gets(aux.dir);
        printf("Dame la identificacion del Amigo: ");
        gets(aux.cedu);
        
        aux.estado=1;
		fwrite(&aux, sizeof(aux), 1, fp); //fwrite=escribir o grabar el registro aux, &direccion de aux, vamos a grabar sizeof o de un tama�o
        fclose(fp);                       //aux , cuantos registros quiero grabar y la variable donde se guardo. y cerramos el archivo.
   }
}

/*
/********************************************************
Funcion que sirve para Modificar un registro dentro del Archivo Binario*/
void Modificar(void)
{	
   FILE *fp;
   Amigo    aux;
   int n, opcion1;
   char cadena[25],cad[2],cadenaux[25];
    fp=abrir_fichero_b(nombre_fichero,3);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
        printf("Cual es la identificacion del amigo que quieres Modificar: ");
        gets(cadena);
        
        //Buscando el Amigo dentro del Archivo
      while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.cedu,cadena)!=0);
      if (n==0)
         printf("No existe el cuate llamado: %s ",cadena);
      else
	  {
	  	if(n!=0)
		{
	  	printf("\n Amigo encontrado....!!!\n");
	    printf("Nombre: %s ",aux.nom);
        printf("Edad: %d ",aux.edad);
        printf("Telefono %s ",aux.tel);
        printf("Direccion: %s\n",aux.dir);
        printf("Identificacion: %s\n ",aux.cedu);
        puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
        getch();
        
	  	do{
            system("cls");
	  	    puts("\n\nElige el dato que quieras modificar\n\n");
            puts("1. Nombre\n2. Edad\n3. Telefono\n4. Direccion\n5. Identificacion\n6. Salir");
            puts("?Introduce tu opcion y despues enter.");
            opcion1 = atoi(gets(cadenaux));
            while(opcion1<0 || opcion1>6) /*Limitando la entrada de las opciones*/    
            opcion1 = atoi(gets(cadenaux));
            system("cls");
            switch(opcion1)
            {
           case 1:
           	       printf("\n CAMBIANDO VALORES \n");
                   printf("Dame el nombre nuevo del Amigo: ");
                   gets(aux.nom);
                   printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
                   fseek(fp,-1*sizeof(aux),SEEK_CUR);
                   fwrite(&aux, sizeof(aux), 1, fp);
                   break;
            case 2:    
                   printf("\n CAMBIANDO VALORES \n");
                   printf("Dame la nueva Edad del Amigo: ");
                   aux.edad=atoi(gets(cad));
                   printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
                   fseek(fp,-1*sizeof(aux),SEEK_CUR);
                   fwrite(&aux, sizeof(aux), 1, fp);
                   break;
            case 3:
            	   printf("\n CAMBIANDO VALORES \n");
                   printf("Dame el nuevo telefono del Amigo: ");
                   gets(aux.tel);
                   printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
                   fseek(fp,-1*sizeof(aux),SEEK_CUR);
                   fwrite(&aux, sizeof(aux), 1, fp);
                   break;
            case 4:
            	   printf("\n CAMBIANDO VALORES \n");
                   printf("Dame la nueva direccion del Amigo: ");
                   gets(aux.dir);
                   printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
                   fseek(fp,-1*sizeof(aux),SEEK_CUR);
                   fwrite(&aux, sizeof(aux), 1, fp);
                   break;
            case 5:
            	   printf("\n CAMBIANDO VALORES \n");
            	   printf("Dame la nueva identificacion del Amigo: ");
            	   gets(aux.cedu);
            	   printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
                   fseek(fp,-1*sizeof(aux),SEEK_CUR);
                   fwrite(&aux, sizeof(aux), 1, fp);
                   break;
            } 
            if(opcion1<6)
            {
                puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
                getch();
            }
		  }
		  while(opcion1!=6);
		  fclose(fp);   //Cerramos el archivo
		  return;
	  	
	  	
         /*printf("\n Amigo encontrado....!!!\n");
         printf("Nombre: %s ",aux.nom);
         printf("Edad: %d ",aux.edad);
         printf("Telefono %s ",aux.tel);
         printf("Direccion: %s\n",aux.dir);
        
         printf("\n CAMBIANDO VALORES \n");
        
         printf("Dame el nombre nuevo del Amigo: ");
         gets(aux.nom);
         printf("Dame la nueva Edad del Amigo: ");
         aux.edad=atoi(gets(cad));
         printf("Dame el nuevo telefono del Amigo: ");
         gets(aux.tel);
         printf("Dame la nueva direccion del Amigo: ");
         gets(aux.dir);
         printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
         fseek(fp,-1*sizeof(aux),SEEK_CUR); //fseek, ubiquese en el archivo -1 se ubica un bloque atras, seek_cur->ubicarlo.
         fwrite(&aux, sizeof(aux), 1, fp);
       }*/
       }
   }
  }
}


/********************************************************
Funcion que sirve para borrar un registro dentro del Archivo Binario*/
/*void Borrar(void){
   FILE *fp,*fd;
   Amigo    aux;
   int encontrado=0;
    char cadena[25];
   
   printf("Introduce el nombre del Amigo a borrar: ");
   gets(cadena);
   
   printf("\n BORRANDO REGISTROS  \n");
   fp=abrir_fichero_b(nombre_fichero,0);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
        fd=abrir_fichero_b(borrar_fichero,1);
      if(!(fd))
         printf("\n Error Imposible crear archivo auxiliar\n");
      else{
         while ((fread(&aux, sizeof(aux), 1, fp))!=0)  //fread=leer aux y le decimos el tama�o y cuantas estructuras vamos a leer y la variable donde se guardo
            if(stricmp(aux.nom,cadena)!=0)             //stricmp=funcion propia para comprar aux nombre con cadena //si es igual a cero, son iguales, si no, son diferentes.
              fwrite(&aux, sizeof(aux), 1, fd);
            else
              encontrado=1;
         fclose(fd);
      }
      fclose(fp);
      if(encontrado){  //que tiene un registro y no esta vacio.
         system("del agenda.dat");
         system("ren paso.$$$ agenda.dat");
         printf("\n Registro BORRADO con Exito!!!\n");
      }
      else{
         system("del paso.$$$");
         printf("\n El Registro NO SE ENCONTRO, no fue borrado!!!");
      }
   }
}

/****************************************
Funcion para hacer un backup de un amigo*/
void Borradorlog(void)
{
	FILE *fp,*fd;
   Amigo    aux;
   Amigo    estado;
   int n=0;
   int opcion1;
   char cadena[25];
      
   fp=abrir_fichero_b(nombre_fichero,3);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
        printf("Cual es la identificacion del amigo que quieres borrar: ");
        gets(cadena);
        
        //Buscando el Amigo dentro del Archivo
      while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.cedu,cadena)!=0);
      if (n==0)
         printf("No existe el cuate llamado: %s ",cadena);
      else
	  {
	  	if(n!=0)
		{
	  	printf("\n Amigo encontrado....!!!\n");
	    printf("Nombre: %s ",aux.nom);
        printf("Edad: %d ",aux.edad);
        printf("Telefono %s ",aux.tel);
        printf("Direccion: %s\n",aux.dir);
        printf("Identificacion: %s\n ",aux.cedu);
        
	  	do{
            system("cls");
	  	    printf("\n\n�Estas seguro que deseas borrar al amigo?\n\n");
            printf("1.si \n");
            printf("2.no \n");
            printf("?Introduce tu opcion y despues enter.");
            scanf("%d", &opcion1);
            while(opcion1<1 || opcion1>2); /*Limitando la entrada de las opciones*/    
            system("cls");
            switch(opcion1)
            {
            	case 1:
            		printf("\ Borrando Registros \n");
            		aux.estado=0;
            		break;
            	case 2:
            		printf("\ Borrando Registros \n");
            		aux.estado=1;
            		break;
            } 
            fseek(fp,-1*sizeof(aux),SEEK_CUR);
            fwrite(&aux, sizeof(aux), 1, fp);
            if(opcion1<2)
            {
                puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
                getch();
            }
            
			}
		      while(opcion1!=1);
		      fclose(fp);   //Cerramos el archivo
		      return;
            }
        }
    }
}

void Recuperar(void)
{
  FILE *fp; //creamos el archivo
   int i=1; 
   Amigo aux;
   Amigo estado;  //amigo es una estructura.
   char cadena[25];
   int n=0;
   int opcion1;
    fp = abrir_fichero_b(nombre_fichero,0);  
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
      else{
           printf("\n U S U A R I O S  E N  L A  A G E N D A I N A C T I V O S\n");
           printf("---------------------------------------------------------------\n");
           while ((fread(&aux, sizeof(aux), 1, fp))!=0)
		   {
      	    if(aux.estado==0)
			    {
                  printf("=> Datos del Amigo %d\n",i);
                  printf("Nombre: %s | Edad: %d | Telefono: %s | Identificacion: %s\n",aux.nom,aux.edad,aux.tel,aux.cedu);
                  printf("Direccion: %s\n",aux.dir);
                  i++; 
                }
            }
            fclose(fp);
        }
        fp = abrir_fichero_b(nombre_fichero,3); 
        if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
        else{
        	
            printf("Cual es la identificacion del amigo que quieres recuperar: ");
            gets(cadena);
            while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.cedu,cadena)!=0);
            if (n==0)
              printf("No existe el cuate llamado: %s ",cadena);
           else
	        {
	  	      if(n!=0)
		       {
	  	          printf("\n Amigo encontrado....!!!\n");
	              printf("Nombre: %s ",aux.nom);
                  printf("Edad: %d ",aux.edad);
                  printf("Telefono %s ",aux.tel);
                  printf("Direccion: %s\n",aux.dir);
                  printf("Identificacion: %s\n ",aux.cedu);
                  puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
                  getch();
                     
	  	    do{  
                 system("cls");
	  	         printf("\n\n�Estas seguro que deseas restaurar al amigo?\n\n");
                 printf("1.si \n");
                 printf("2.no \n");
                 printf("?Introduce tu opcion y despues enter.");
                 scanf("%d", &opcion1);
                 while(opcion1<1 || opcion1>2); /*Limitando la entrada de las opciones*/    
                 system("cls");
                 switch(opcion1)
                {
            	case 1:
            		printf("\ Borrando Registros \n");
            		aux.estado=1;
            		break;
            	case 2:
            		printf("\ Borrando Registros \n");
            		aux.estado=0;
            		break;
                } 
                fseek(fp,-1*sizeof(aux),SEEK_CUR);
                fwrite(&aux, sizeof(aux), 1, fp);
                /*if(opcion1<2)
                {
                   puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
                   getch();
                }*/
                
			    }
		          while(opcion1!=1);
		          fclose(fp);   //Cerramos el archivo
		          return;
                }
            }
		}   
	}  

/******************************************
Funcion para Encontrar un Amigo e imprimir sus datos*/
void Encontrar(void){
    FILE *fp;
    Amigo    aux;
    int n;
    char cadena[25];

    printf("Introduce la identificacion del Amigo que buscas: ");
    gets(cadena);

    printf("\n Buscando a un Amigo  \n");
    fp=abrir_fichero_b(nombre_fichero,0);
    if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
    else{
        while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.cedu,cadena)!=0);
      if (n==0)
         printf("No existe el cuate con la identificacion: %s ",cadena);
      else{
         printf("\n Amigo encontrado....!!!\n");
         printf("Nombre: %s | Edad: %d | Telefono: %s | Identificacion: %s\n",aux.nom,aux.edad,aux.tel,aux.cedu);
         printf("Direccion: %s\n",aux.dir);
        
        /* getch();*/
        
        }
    }


}

/*************************************************
Funcion que Carga el Archivo y regresa un apuntador con que se va ha manejar el Archivo
Recibe:     El nombre del Archivo , Y el m�todo con que se va abrir el Archivo
        Un Apuntador tipo Archivo, 0 - Solo Lectura , 1 - Para crearlo de nuevo desde cero, 
        2 - Anhadir Informacion, 3 - para Lectura y Escritura.        
 Regresa:    El apuntador de Tipo FILE, con el cual se abrio*/
FILE *abrir_fichero_b(char cadena[], int metodo){  //*va a devolver la direccion  de lo que estamos trabajando, devuelve una varibale tipo archivo
    FILE *x;
    switch(metodo){
        case 0:
            x = fopen(cadena,"rb"); //para crear 
            break;
        case 1:
            x = fopen(cadena,"wb"); // para escribir
            break;
        case 2:
            x = fopen(cadena,"ab");   //ab= adicionar informaci�n
            break;
        case 3:
            x = fopen(cadena,"r+b");  //lectura y escritura
            break;
    }
    return x;
}