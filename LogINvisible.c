/*
Programa:LogINvisible
Autores:Cetz Abarca Edgar Emanuel, Moo Uc Valeria Sarai, Vega Escoabar Erick Manuel.
Fecha: 12/05/2025
Version: 2.0
Compilador: ZingaI
*/

#include <conio.h>//Librería para entradas y salidas. 
#include <ctype.h>//Librería para manejo de caracteres individuales.  
#include <stdio.h>//Librería estándar. 
#include <stdlib.h>//Librería para manejo de memoria 
#include <string.h>//Librería para manejo de cadenas. 
#include <time.h>// Para el historial de actividad.


struct usuarios{   //estructura de atributos del usuario
	int es_admin;  //si es admin 1, si no es 0.
	char contrasena[20];
	char nombre_usuario[20];
}usuario;

struct actividades {  // estructura para ver la actividad de los usuarios
	char usuario[20];
	char accion[50];
	time_t fecha_hora;
}actividad;
/*Quitar salto de linea de fgets.
-regresa la cadena sin el salto de linea '/n'
-No tiene funciones anidadas
*/
void Quitar_Salto(char *cadena){
	int tam = strlen(cadena);
	if(tam > 0 && cadena[tam-1]=='\n'){
		cadena[tam-1]='\0';  //elimina el salto de linea y lo reemplaza por valor nulo
	}
}
/*Cifra la contraseña con un metodo ROT13 y cesar jugando los ASCII de cada elemento.
	-No tiene funciones anidadas
*/
void Cifrar_Contrasena(char *contrasena) {
	int i, j=0, tam, digito;
	tam = strlen(contrasena);
	char auxiliar[tam + 1];
	
	for (i = tam-1; i > -1; i--) {
		auxiliar[j] = contrasena[i];
		j++;
	}
	auxiliar[tam] = '\0';
	strcpy(contrasena,auxiliar);
	//cambiar vocales
	for (i = 0; i < tam; i++) {
		if (contrasena[i] >= 'A' && contrasena[i] <= 'Z') {  
			contrasena[i] = 'A' + ((contrasena[i] - 'A' + 13) % 26);
		}
		else if (contrasena[i] >= 'a' && contrasena[i] <= 'z') { 
			contrasena[i] = 'a' + ((contrasena[i] - 'a' + 13) % 26);
		}
		else if (isdigit(contrasena[i])==1){
			digito = contrasena[i] - 48;
			digito += 3;
			digito %= 10;
			contrasena [i] = digito +48;
		}
	}
	for (i = 0; i < tam; i++) {
		contrasena[i] += tam;
	}
}	
/*Descifra la contraseña con el metodo de cifrado a la inversa para retornar a la origninal.
	-No tiene funciones anidadas
*/
void Descifrar_Contrasena(char *contrasena){
	int i, j=0, tam, digito;
	tam = strlen(contrasena);
	char auxiliar[tam + 1];
	
	for (i = 0; i < tam; i++) {
		contrasena[i] -= tam;
	}
	
	for (i = 0; i < tam; i++) {
		if (contrasena[i] >= 'A' && contrasena[i] <= 'Z') {  
			contrasena[i] = 'A' + ((contrasena[i] - 'A' + 13) % 26);
		}
		else if (contrasena[i] >= 'a' && contrasena[i] <= 'z') { 
			contrasena[i] = 'a' + ((contrasena[i] - 'a' + 13) % 26);
		}
		else if (isdigit(contrasena[i])==1){
			digito = contrasena[i] - 48;
			digito -= 3;
			digito %= 10;
			contrasena [i] = digito + 48;
		}
	}
	for (i = tam-1; i > -1; i--) {
		auxiliar[j] = contrasena[i];
		j++;
	}
	auxiliar[tam] = '\0';
	strcpy(contrasena,auxiliar);
}

/*Ocultar los caracteres introducidos al ingresar la contraseña.
-ingresa la contraseña y oculta los caracteres con **** hasta introducir '\n'
	-No tiene funciones anidadas
*/
void Ocultar_Contrasena(char contrasena[20] ){
	int i = 0, iniciar = 1;
	char caracter;
	while (iniciar){  //para que este activo siempre el ciclo
		caracter = getch();
		if (caracter == 13){ //rompe el ciclo si '/0'
			contrasena[i] = '\0';
			break;
		}
		else if (caracter == 8){  //para borrar 
			if (i > 0){
				i--;
				printf("\b \b"); //retrocede un lugar el cursor y elimina *
			}
		}
		else if (caracter == 9 || caracter == 32){ //si es espacio o tab no pasa nada
			continue;
		}
		else{
			contrasena[i++] = caracter;   //agrega caracter y muestra *
			printf("*");
		}
	}
	printf("\n");
}
/*Funcion Asegurar contraseña.
-Se asegura que la contraseña contenga numeros, mayusculas, minusculas y al menos 6 caracteres
	-No tiene funciones anidadas
*/
int Asegurar_Contrasena(char *contrasena){
	int i, tamano_contra = strlen(contrasena), es_valida = 0, mayus = 0, minus = 0, digito = 0;
	if(tamano_contra >= 6){ //verifica el tamaño de la contraseña
		for(i = 0; i < tamano_contra; i++){
			//verifica que tenga al menos una mayuscula, minuscula y un digito
			if(isupper(contrasena[i]) != 0){
				mayus = 1;
			}
			else if(isdigit(contrasena[i]) != 0){
				digito = 1;
			}
			else if(islower(contrasena[i]) != 0){
				minus = 1;
			}
		}
	}
	else{
		printf("Debe tener mínimo 6 caracteres\n"); //salida si es menor que 6
		return es_valida;
	}
	if( mayus == 1 && minus == 1 && digito == 1){ //si cumple los parametros es valida
		es_valida = 1;
		return es_valida;
	}
	else{  //si no cumple devuelve un mensaje con lo que no cumple
		if(mayus == 0){
			printf("Debe tener alguna mayúscula\n");
		}
		if(minus == 0){
			printf("Debe tener alguna minúscula\n");
		}
		if(digito == 0){
			printf("Debe tener algun número\n");
		}
		printf("\n\n");
		return es_valida;
	}
}
	
//-------------------------------------------------------------------------------------------------
/*Funcion inicializar archivo.
-Se crea un archivo binario para el registro de los datos
	-No tiene funciones anidadas
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
	-no tiene funciones anidadas
*/
void Visualizar_Usuarios(char *direccion){
	system("cls");
	FILE *archivo;
	archivo = fopen(direccion,"rb");
	if(archivo == NULL){
		printf("Error al abrir archivo");
	}
		
	const int filas = 30, columnas = 21;
	char nombres_normal[filas][columnas], nombres_admin[filas][columnas], aux[columnas];
	int normales=0,admins=0, usuarios_totales = 0;
		
	while(fread(&usuario,sizeof(struct usuarios),1,archivo)){  // lee el archivo 
		if(usuario.es_admin == 1){
			strcpy(nombres_admin[admins],usuario.nombre_usuario);
			admins++;  // cuenta cuantos administradores hay
		}else if(usuario.es_admin == 0){
			strcpy(nombres_normal[normales],usuario.nombre_usuario);
			normales++; // cuenta cuantos usuarios normales hay
		}
	}
	fclose(archivo); //cierra el archivo
	
	usuarios_totales = admins + normales;

	//ordenar usuarios administradores en orden alfabetico metodo burbuja
	for (int i = 0; i < normales-1; i++) {
		for (int j = 0; j < normales-1 ; j++) {
			if(strcmp(nombres_normal[j],nombres_normal[j+1]) > 0 ){
				strcpy(aux,nombres_normal[j]);
				strcpy(nombres_normal[j],nombres_normal[j+1]);
				strcpy(nombres_normal[j+1],aux);
			}
		}
	}
	//ordenar usuarios normales en orden alfabetico metodo burbuja
	for (int i = 0; i < admins-1; i++) {
		for (int j = 0; j < admins-1 ; j++) {
			if(strcmp(nombres_admin[j],nombres_admin[j+1]) > 0 ){
				strcpy(aux,nombres_admin[j]);
				strcpy(nombres_admin[j],nombres_admin[j+1]);
				strcpy(nombres_admin[j+1],aux);
			}
		}
	}
	//imprimir salida en forma de reporte
	printf("\n   --USUARIOS REGISTRADOS--\n");
	printf("El numero de usuarios es: %d\n",usuarios_totales); 
	for (int i = 0; i < admins; i++) {
		printf("Usuario: %s - Rol: [Admin] \n",nombres_admin[i]);
	}
	for (int i = 0; i < normales; i++) {
		printf("Usuario: %s - Rol: [Normal] \n",nombres_normal[i]);
	}
	printf("\nPresione enter para continuar."); getch();
}
/*Funcion verificar que el usuario exista.
-Se revisan los nombres de los usuarios verificando que el nombre exista = 1 o no = 0 
	-No tiene funciones anidadas:
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

void Registrar_Actividad(char *usuario, char *accion); //se referencia la funcion Ver_Actividad para poder guardar actividad en las demas funciones.

/*Funcion Para poder registrar un administrador.
-Se pide una contraseña para poder registrarse como administrador 
	-Funciones anidadas:
	Ocultar_Contrasena 
	Descifrar_Contrasena
*/
int Registrar_Admin(){
	char contrasena_admin[]="BSP_\\SUTdOdh_\\";//contraseña ADMINISTRADOR1 cifrada.
	char contrasena_introducida[20];
	printf("Ingrese contraseña para ser administrador: ");
	Ocultar_Contrasena(contrasena_introducida);
	Descifrar_Contrasena(contrasena_admin);
	
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
	-Funciones anidadas:
	Ocultar_Contrasena 
	Cifrar_Contrasena
	Encontrar_Usuario
	Registrar_Actividad
*/	
void Registrar_Usuario(char *direccion){
	system("cls");
	FILE *archivo;
	struct usuarios nuevo;
	int administrador, contrasena_valida = 0;
	printf("\n--Registrar nuevo usuario--\n");
		
	fflush(stdin);
	do{
		printf("Ingrese nombre de usuario : ");
		fgets(nuevo.nombre_usuario,20,stdin); Quitar_Salto(nuevo.nombre_usuario);
	} while(strlen(nuevo.nombre_usuario) < 1); 
	
	
	if(Encontrar_Usuario(direccion,nuevo.nombre_usuario)){  //verificar que el nuevo usuario no exita
		printf("El nombre de usuario ya existe. Pruebe con otro\n");
		getch();
		return;
	}
	do{
		printf("Ingrese contraseña: ");
		Ocultar_Contrasena(nuevo.contrasena);
		contrasena_valida = Asegurar_Contrasena(nuevo.contrasena); //Valida contraseña
	} while(contrasena_valida == 0);
	
	do{
		printf("¿Es administrador?\n");
		printf("1) Sí\n");
		printf("2) No\n");
		scanf("%d",&nuevo.es_admin);
	}while(nuevo.es_admin > 2 || nuevo.es_admin < 1);
	
	if(nuevo.es_admin==2){
		nuevo.es_admin = 0;  // si escoge 2 no es admin 
	}
	fflush(stdin);
	
	if(nuevo.es_admin == 1){  // si se escoge admin se pide contraseña
		administrador = Registrar_Admin();
		if(administrador != 1){ //si se introduce mal la contraseña de administrador vuelve al menu
			return ;
		}
	}
	//aqui se cifraria la clave antes de guardar en el documento
	Cifrar_Contrasena(nuevo.contrasena);
	
	archivo = fopen(direccion,"ab"); //agregar datos de nuevo usuario al archivo
	if (archivo == NULL){
		printf("Error al abrir el archivo...\n");
		return;
	}
	fwrite(&nuevo,sizeof(struct usuarios),1,archivo); //escribir los datos en binario dentro del arcivo
	fclose(archivo);
	printf("Usuario registrado correctamente...\n");
	Registrar_Actividad(nuevo.nombre_usuario, "Se registró"); 
	getch();
}
//-------------------------------------------------------------------------------------------------
/*Funcion para poder iniciar sesion valida que la contraseña y el usuario sean válidos.
-Se ingresan los datos de un usuario registrado y se valida para Iniciar sesión
	-Funciones anidadas:
	Ocultar_Contrasena 
	Descifrar_Contrasena
*/	
int Validar_Usuario(char *direccion,struct usuarios *usuario_iniciado){
	FILE *archivo;
	char nombre_usuario[20], clave[20];
	int encontrado = 0;
	
	fflush(stdin);
	system("cls");
	printf("Ingrese nombre de usuario : ");
	fgets(nombre_usuario,20,stdin); Quitar_Salto(nombre_usuario);
	printf("Ingrese contraseña : ");
	Ocultar_Contrasena(clave);
	
	archivo = fopen(direccion,"rb");
	if (archivo == NULL){
		printf("Error al abrir el archivo...\n");
		return 0;
	}
	
	while(fread(&usuario,sizeof(struct usuarios),1,archivo)){  //leer el archivo binario
		if(strcmp(usuario.nombre_usuario,nombre_usuario) == 0){ // comparar el nombre, si es igual, descifrar clave, si no regresar al menu
			char clave_original[20];  //una nueva cadena para guardar la clave de usuario
			strcpy(clave_original,usuario.contrasena); //copiar la clave del usuario
			Descifrar_Contrasena(clave_original); // descifrar clave en nueva cadena
			
			if(strcmp(clave,clave_original)== 0){ // si la clave ingresada es igual a la descifrada
				*usuario_iniciado = usuario;   //pasar datos del usuario a un puntero
				encontrado = 1;  //marcar como usuario encontrado
				break;
			}else{
				printf("La contraseña es incorrecta.\n"); getch();
				fclose(archivo);
				return 0;  //devolver 0 contraseña incorrecta
			}
		}
	}
	fclose(archivo); 
	if(encontrado != 1){
		printf("Usuario no existe.\n"); getch();
		return 0; //devolver 0 ususario invalido
	}
	return 1;//devolver 1 usuario encontrado
}

/*Funcion para iniciar sesion.
-Valida que el usuario existe con una funcion
-Si el usuario es valido revisa si es administrador o no y abre el respectivo menu
	-Funciones anidadas:
	Abrir_MenuAdministrador
	Abrir_MenuNormal
	Registrar_Actividad
*/
void Abrir_MenuAdministrador(char *direccion,struct usuarios *usuario);
void Abrir_MenuNormal(char *direccion,struct usuarios *usuario);

void Iniciar_Sesion(char *direccion, struct usuarios *usuario){
	if(Validar_Usuario(direccion,usuario) == 1){
		//abre un menu segun los privilegios del usuario
		Registrar_Actividad(usuario->nombre_usuario, "Inició Sesión");
		if(usuario->es_admin == 1){
			Abrir_MenuAdministrador(direccion,usuario);
		}
		else{
			Abrir_MenuNormal(direccion,usuario);
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*Actualiza datos del usuario.
-Esta funcion unicamente modifica la contraseña del usuario en el archivo.
	No tiene funciones anidadas
*/
int Actualizar_Contrasena(char *direccion, struct usuarios nuevo){  //reescribir los datos del usuario
	FILE *archivo = fopen(direccion,"rb");
	FILE *temp = fopen("ARCHIVO_TEMPORAL.dat","ab");  //abrir un archivo temporal binario
		
	if(archivo == NULL || temp == NULL){
		printf("Error al abrir archivos...\n");
		return 0;
	}
	
	int actualizado = 0; //bandera de actualizado
	struct usuarios temporal; //nueva variable temporal de estructura
	
	while(fread(&temporal, sizeof(struct usuarios),1,archivo)){
		if(strcmp(temporal.nombre_usuario,nuevo.nombre_usuario)==0){  	//si el dato del archivo coincide con el usuario actual
			fwrite(&nuevo, sizeof(struct usuarios),1,temp); //guardar nuevos datos
			actualizado = 1;
		}else{
			fwrite(&temporal, sizeof(struct usuarios),1,temp); //reescribir lo que ya estaba en el texto
		}
	}
	fclose(archivo);
	fclose(temp);
		
	remove(direccion);   //eliminar original
	rename("ARCHIVO_TEMPORAL.dat",direccion);  //renombrar temporal (nuevo original)
	return actualizado;
}
/*Cambiar contraseña del usuario
-Se cambia la contraseña del usuario.
	-Funciones anidadas:
	Ocultar_Contrasena 
	Cifrar_Contrasena
	Descifrar_Contrasena
	Actualizar_Contrasena
*/
void Cambiar_Contrasena(char*direccion, struct usuarios *usuario_actual){
	
	char contrasena_actual[20], contrasena_nueva[20], confirmar[20];
	fflush(stdin);
	printf("--Cambiar contraseña--\n");
	printf("Ingresa contraseña actual: ");
	Ocultar_Contrasena(contrasena_actual);
	//desciframos la clave para comparar con la ingresada
	char pass_des[20];
	strcpy(pass_des, usuario_actual->contrasena); // copiamos la clave del usuario actual 
	Descifrar_Contrasena(pass_des); // la desciframos
		
	if(strcmp(contrasena_actual,pass_des) != 0){  //comparar ambas claves
		printf("contraseña incorrecta\n");
		return;
	}
		
	printf("Ingresa la nueva contraseña: ");
	fgets(contrasena_nueva,20,stdin); Quitar_Salto(contrasena_nueva);
	printf("Confirmar nueva contraseña: ");
	Ocultar_Contrasena(confirmar);
	
	if(strcmp(contrasena_nueva,confirmar) != 0){
		printf("Las contraseñas no coinciden \n");  //comparar ambas claves
		return;
	}
	
	strcpy(usuario_actual ->contrasena,contrasena_nueva);
	Cifrar_Contrasena(usuario_actual->contrasena);// se cifra la contraseña antes de guardar en el documento
	
	if(Actualizar_Contrasena(direccion,*usuario_actual) == 1){
		printf("La contraseña cambio correctamente \n");
	}else{
		printf("Error al cambiar contraseña \n");
	}
	getch();
}
//-------------------------------------------------------------------------------------------------
/*Funcion Realizar Eliminacion.
-Se elimina el usuario ingresado en el archivo.
	No tiene funciones anidadas
*/
int Realizar_Eliminacion(char *direccion, char *nombre){
	FILE *archivo = fopen(direccion,"rb");
	FILE *temporal = fopen("ARCHIVO_TEMPORAL.dat","wb");  //abrir un archivo temporal binario
		
	if(archivo == NULL || temporal == NULL){
		printf("Error al abrir archivos...\n");
		return 0;
	}
		
	int eliminado = 0; //bandera de borrado
	struct usuarios usuario; //variable de estructura para leer los datos
		
	while(fread(&usuario, sizeof(struct usuarios),1,archivo)){
		if(strcmp(usuario.nombre_usuario,nombre)==0){  	//si el dato del archivo coincide con el usuario actual
			eliminado = 1;               // no escribe sus datos en el nuevo archivo
			continue;
		}else{
			fwrite(&usuario, sizeof(struct usuarios),1,temporal); //reescribir lo que ya estaba en el texto
		}
	}
		
	
	fclose(archivo);
	fclose(temporal);
	
	remove(direccion);   //eliminar original
	rename("ARCHIVO_TEMPORAL.dat",direccion);  //renombrar temporal (nuevo original)
	
	return eliminado;
}

/*Funcion Eliminar usuario.
-Se elimina el usuario que sea ingresado por el administrador o el usuario propio para usuario normal.
	-Funciones anidadas:
	Realizar_Eliminacion
	Registrar_Actividad
*/

void Eliminar_Usuario(char *direccion, struct usuarios *usuario){
	int eliminado = 0, existe = 0;
	char nombre[20], confirmar;
	
	if(usuario->es_admin == 1){ // si el usuario es administrador
		fflush(stdin);
		system("cls");
		printf("Ingrese nombre de usuario a eliminar : "); //pide nombre de usuario a eliminar
		fgets(nombre,20,stdin); Quitar_Salto(nombre);  //
		
		printf("Seguro de eliminar la cuenta? s/n\n");
		scanf(" %c",&confirmar); 
		fflush(stdin);
		
		switch(confirmar){
		case 's':case'S': existe = Encontrar_Usuario(direccion,nombre); 
		if (existe != 1){  //verifica que el usuario existe con la funcion ya creada
			printf("Usuario no existe"); getch();
			return ;
		}
		eliminado = Realizar_Eliminacion(direccion, nombre); //se elimina del archivo al usuario
		if(eliminado == 1){
			printf("Usuario eliminado correctamente..."); Registrar_Actividad(nombre, "Se ha eliminado por Admin"); getch(); //se regresa al menu
			return ;
		}
		break;
		
		case 'n':case'N': printf("Eliminacion cancelada"); getch(); return; break;
		
		default:printf("No existe esa opcion\n\n");getch(); return;break;
		}
		
	}else{ //si no es admin
		printf("Seguro de eliminar la cuenta? s/n\n"); 
		scanf(" %c",&confirmar); 
		fflush(stdin);
		
		strcpy(nombre,usuario->nombre_usuario); //se copia el nombre del usuario en una cadena
		
		switch(confirmar){
		case 's':case'S': eliminado = Realizar_Eliminacion(direccion, nombre); //se elimina en archivo
		if(eliminado == 1){
			printf("Usuario eliminado correctamente..."); Registrar_Actividad(nombre, "Eliminó su cuenta");
			getch();
			return ; //regresa al menú
		}
		break;
		
		case 'n':case'N': printf("Eliminacion cancelada"); getch(); return; break;
		
		default:printf("No existe esa opcion\n\n");getch(); return;break;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*Registrar Actividad.
	Se escribe la actividad en el archivo;
	Se escribe lo que realizo el usuario, si inicio o cerro sesion y si se registro o elimino el usuario.
	-No contiene funciones anidadas.
*/
void Registrar_Actividad(char *usuario, char *accion){
	FILE *archivo = fopen("ARCHIVO_ACTIVIDADES.dat", "ab");
	if (archivo == NULL) {
		printf("Error al abrir el archivo...\n");
		return;
	}
	struct actividad;
	strcpy(actividad.usuario,usuario); // se copia el nombre del usuario y la accion a la estructura
	strcpy(actividad.accion,accion);
	
	actividad.fecha_hora = time(NULL); //se guarda fecha y hora actual en la estructura
	
	fwrite(&actividad, sizeof(struct actividades), 1, archivo); // se escribe en el archivo
	fclose(archivo);
}
/*Registrar Actividad.
Se mustra la actividad del sistema en formato de reporte
Se escribe lo que realizo el usuario, si inicio o cerro sesion y si se registro o elimino el usuario.
	-No contiene funciones anidadas.
*/
void Ver_Actividad() {
	system("cls");
	FILE *archivo = fopen("ARCHIVO_ACTIVIDADES.dat", "rb");
	if (archivo == NULL) {
		printf("Error al abrir el archivo...\n");
		getch();
		return;
	}
		
	printf("\n--- ACTIVIDAD DEL SISTEMA ---\n\n");
		
	struct actividad;
	char fecha[20];
		
	while(fread(&actividad, sizeof(struct actividades), 1, archivo)) { //se lee el archivo
		struct tm *info = localtime(&actividad.fecha_hora); //se guarda la fecha y hora en formato de estructura
		strftime(fecha, 20, "%d/%m/%Y %H:%M", info); //se formatea el campo de hora y fecha
			
		//salida de datos
		printf("Usuario: %s\n", actividad.usuario); 
		printf("Accion: %s\n", actividad.accion);
		printf("Fecha y Hora: %s\n\n", fecha);
	}
		
	fclose(archivo); //se cierra el archivo
	printf("\nPresione una tecla para continuar...\n");
	getch();
}
	
//-------------------------------------------------------------------------------------------------
/*Menu de Administrador.
-Se despliega el menu para Administradores del sistema.
	-Funciones anidadas:
	Cambiar_Contrasena
	Visualizar_Usuarios
	Eliminar_Usuario
	Registrar_Actividad
*/
void Abrir_MenuAdministrador(char *direccion,struct usuarios *usuario){
	char opcion;
	do{  //menu del programa
		system("cls");
		printf("Bienvenido %s [%s] \n",usuario->nombre_usuario,usuario->es_admin? "Admin" : "Normal" );
		printf("\nMENU DE ADMINISTRADOR\n");
		printf("a) Cambiar contraseña \n");
		printf("b) Visualizar usuarios\n");
		printf("c) Remover usuarios \n");
		printf("d) Ver actividad del sistema \n");
		printf("s) Cerrar sesion\n");
		printf("Seleccione opcion : ");
		scanf(" %c",&opcion);
		printf("\n");
			
		switch(opcion){
		case 'a':case'A': Cambiar_Contrasena(direccion,usuario); break;
		case 'b':case'B': Visualizar_Usuarios(direccion);break;
		case 'c':case'C': Eliminar_Usuario(direccion,usuario); return; break;
		case 'd':case'D': Ver_Actividad(); break;
		case 's':case'S': printf("Sesion cerrada..."); getch(); Registrar_Actividad(usuario->nombre_usuario, "Cerró Sesión"); break;
		default:printf("No existe esa opcion...\nPresione enter para continuar."); getch(); break;
		}
	} while(opcion != 's' && opcion !='S');
}
/*Menu de usuarrio normal.
-Se despliega el menu para usuarios normales del sistema.
	-Funciones anidadas:
	Cambiar_Contrasena
	Visualizar_Usuarios
	Eliminar_Usuario
	Registrar_Actividad
*/
void Abrir_MenuNormal(char *direccion,struct usuarios *usuario){
	char opcion;
	do{   //menu del programa
		system("cls");
		printf("Bienvenido %s [%s] \n",usuario->nombre_usuario,usuario->es_admin? "Admin" : "Normal" );
		printf("\nMENU DE USUARIO\n");
		printf("a) Cambiar contraseña \n");
		printf("b) Visualizar usuarios\n");
		printf("c) Eliminar cuenta \n");
		printf("s) Cerrar sesion\n");
		printf("Seleccione opcion : ");
		scanf(" %c",&opcion);
		printf("\n");
			
		switch(opcion){
		case 'a':case'A': Cambiar_Contrasena(direccion,usuario); break;
		case 'b':case'B': Visualizar_Usuarios(direccion); break;
		case 'c':case'C': Eliminar_Usuario(direccion,usuario); return; break;
		case 's':case'S': printf("Sesion cerrada..."); getch(); Registrar_Actividad(usuario->nombre_usuario, "Cerró Sesión"); break;
		default: printf("No existe esa opcion...\nPresione enter para continuar."); getch(); break;
		}
	} while(opcion != 's' && opcion !='S');
}
/*Menu principal del sistema.
-Se despliega el menu principal del sistema para los todos los usuarios
	-Funciones anidadas:
	Registrar_Usuario
	Visualizar_Usuarios
	Iniciar_Sesion
	Iniciar_Archivo
*/
int main() {
	struct usuario;
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
		case 'c':case'C': Iniciar_Sesion(direccion,&usuario); break;
		case 's':case'S': printf("Programa finalizado..."); break;
	
		default: printf("No existe esa opcion...\nPresione enter para continuar."); getch(); break;
		}
	} while(opcion != 's' && opcion !='S');
	
	return 0;
}

