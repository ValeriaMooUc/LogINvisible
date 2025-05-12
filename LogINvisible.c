/*
Programa:LogINvisible
Autores:Cetz Abarca Edgar Emanuel, Moo Uc Valeria Sarai, Vega Escoabar Erick Manuel.
Fecha: 12/05/2025
Version: 1.0
Compilador: ZingaI
*/

#include <conio.h>//Librería para entradas y salidas. 
#include <ctype.h>//Librería para manejo de caracteres individuales.  
#include <stdio.h>//Librería estándar. 
#include <stdlib.h>//Librería para manejo de memoria 
#include <string.h>//Librería para manejo de cadenas. 
 
struct usuarios{
	int es_admin;  //si es admin 1, si no es 0.
	char contrasena[20];
	char nombre_usuario[20];
}usuario;
/*Quitar salto de linea de fgets.
-regresa la cadena sin el salto de linea '/n'
*/
void Quitar_Salto(char *cadena){
	int tam = strlen(cadena);
	if(tam > 0 && cadena[tam-1]=='\n'){
		cadena[tam-1]='\0';
	}
}
/*Ocultar los caracteres introducidos al ingresar la contraseña.
-ingresa la contraseña y oculta los caracteres con **** hasta introducir '\n'
*/
void Ocultar_Contrasena(char contrasena[20] ){
	int i = 0, corriendo = 1;
	char caracter;
	while (corriendo){
		caracter = getch();
		if (caracter == 13){
			contrasena[i] = '\0';
			break;
		}
		else if (caracter == 8){
			if (i > 0){
				i--;
				printf("\b \b");
			}
		}
		else if (caracter == 9 || caracter == 32){
			continue;
		}
		else{
			contrasena[i++] = caracter;
			printf("*");
		}
	}
	printf("\n");
}
//-------------------------------------------------------------------------------------------------
/*Funcion inicializar archivo.
-Se crea un archivo binario para el registro de los datos
*/
void Iniciar_Archivo(char *direccion){
	FILE *archivo;
	archivo = fopen(direccion,"ab+"); //permite crear el archivo y agregar texto sin borrar
	if(archivo == NULL){
		printf("Error al abrir el archivo...\n");
		return;
	}
	fclose(archivo);
}
/*Funcion ver usuarios registrados.
-Se crea una lista con los usuarios registrados
*/
void Visualizar_Usuarios(char *direccion){
	system("cls");
	FILE *archivo;
	archivo = fopen(direccion,"rb"); 
	
	printf("\n--USUARIOS REGISTRADOS--\n");
	while(fread(&usuario,sizeof(struct usuarios),1,archivo)){
		printf("Usuario: %s - Rol: %s\n",usuario.nombre_usuario,usuario.es_admin ? "Admin" : "Normal");
	}
	printf("\nPresione enter para continuar."); getch();
	fclose(archivo);
}
/*Funcion verificar que el usuario exista.
-Se revisan los nombres de los usuarios verificando que el nombre exista = 1 o no = 0 
*/	
int Encontrar_Usuario(char *direccion,char *usuario_buscado){
	FILE *archivo;
	archivo = fopen(direccion,"rb");
	while(fread(&usuario,sizeof(struct usuarios),1,archivo)){
		if (strcmp(usuario.nombre_usuario, usuario_buscado) == 0){  //compara si el nombre de usuario ya existe
			fclose(archivo);
			return 1;  //existe
		}
	}
	fclose(archivo);
	return 0; //no existe
}
/*Funcion Para poder registrar un administrador.
-Se pide una contraseña para poder registrarse como administrador 
*/
int Registrar_Admin(){
	char contrasena_admin[]="ADMINISTRADOR1";//posteriormente se cifrara la contraseña.
	char contrasena_introducida[20];
	printf("Ingrese contraseña para ser administrador: ");
	Ocultar_Contrasena(contrasena_introducida);
	
	if(strcmp(contrasena_introducida, contrasena_admin)==0){
		return 1;
	}
	else{
	   printf("\nLa contraseña es incorrecta..."); getch();
	   return 0;
	}
}
/*Funcion para registrar un nuevo ususario.
-Se ingresan los datos de un nuevo usuario y se guarda en el archivo
*/	
void Registrar_Usuario(char *direccion){
	system("cls");
	FILE *archivo;
	struct usuarios nuevo;
	int administrador;
	printf("--Registrar nuevo usuario--\n");
		
	fflush(stdin);
	printf("Ingrese nombre de usuario : ");
	fgets(nuevo.nombre_usuario,20,stdin); Quitar_Salto(nuevo.nombre_usuario);
		
	if(Encontrar_Usuario(direccion,nuevo.nombre_usuario)){  //verificar que el nuevo usuario no exita
		printf("El nombre de usuario ya existe. Pruebe con otro\n");
		getch();
		return;
	}
	printf("Ingrese contraseña: ");
	Ocultar_Contrasena(nuevo.contrasena);
		
	do{
		printf("¿Es administrador?\n");
		printf("1) Sí\n");
		printf("2) No\n");
		scanf("%d",&nuevo.es_admin);
	}while(nuevo.es_admin > 2 || nuevo.es_admin < 1);
	
	fflush(stdin);
	
	if(nuevo.es_admin == 1){  // si se escoge admin se pide contraseña
		administrador = Registrar_Admin();
		if(administrador != 1){ //si se introduce mal la contraseña de administrador vuelve al menu
			return ;
		}
	}
	//aqui se cifraria la clave antes de guardar en el documento
		
	archivo = fopen(direccion,"ab"); //agregar datos de nuevo usuario al archivo
	if (archivo == NULL){
		printf("Error al abrir el archivo...\n");
		return;
	}
	fwrite(&nuevo,sizeof(struct usuarios),1,archivo); //escribir los datos en binario dentro del arcivo
	fclose(archivo);
	printf("Usuario registrado correctamente...\n");getch();
	}
	
//-------------------------------------------------------------------------------------------------
/*Menu principal del sistema.
-Se despliega el menu principal del sistema para los usuarios
*/
int main() {
	char opcion;
	char direccion[]="ARCHIVO_USUARIOS.dat";
	Iniciar_Archivo(direccion);
	do{
		system("cls");
		printf("\nMENU\n");
		printf("a) Registrar usuario\n");
		printf("b) Visualizar usuarios\n");
		printf("c) Iniciar sesion\n");
		printf("s) SALIR\n");
		printf("Seleccione opcion : ");
		scanf(" %c",&opcion);
		
		switch(opcion){
		case 'a':case'A': Registrar_Usuario(direccion);break;
		case 'b':case'B': Visualizar_Usuarios(direccion);break;
		case 'c':case'C': break;
		case 's':case'S':printf("Programa finalizado...");  break;
		default:printf("No existe esa opcion...\nPresione enter para continuar."); getch(); break;
		}
	} while(opcion != 's');
	return 0;
}

