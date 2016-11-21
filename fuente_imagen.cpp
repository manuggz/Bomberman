#include "fuente_imagen.hpp"

FuenteImagen::FuenteImagen(SDL_Surface *imagen,char orden[]){
    ima=imagen;
    strncpy(this->ordenLetras,orden,MAX_LETRAS_RECONOCIDAS);
    identificarRects();
}

/* 
 * Informa si la columna (par�metro 2) es una linea completa de pixeles
 * transparentes en la superficie ima (par�metro 1)
 *
 * Se asume que el color transparente es aquel que coincide con el pixel
 * situado en la posicion (0,0) de la superficie.
 */
bool FuenteImagen::esColumnaVacia(int columna){
	Uint32 pixel_transparente = get_pixel (ima, 0, 0);
	int fila;
	
	/* busca un pixel opaco */
	for (fila = 0; fila < ima->h; fila ++){
		if (pixel_transparente != get_pixel (ima, columna, fila))
			return false;
	}

	return true;
}

/*
 * Analiza la superficie ima buscando letras para registrarlas en el 
 * vector de rect�ngulos fuentes (segundo par�metro)
 *
 * Para analizar, el programa recorre la im�gen de izquierda a derecha
 * 'leyendo' barras verticales de p�xeles. As� determina donde comienza
 * y termina cada letra (debe existir una separaci�n de, al menos, un 
 * pixel entre cada caracter)
 */
void FuenteImagen::identificarRects (){
	int indice_letra = 0;
	bool esta_recorriendo_letra = false;
	int w = 0; /* ancho de la letra actual */

	for (int i = 0; i < ima->w; i ++)
	{
		if (esColumnaVacia ( i))
		{
			
			/* si estaba leyendo una letra entonces encontr� 
			 * el ancho de la misma */
			if (esta_recorriendo_letra)
			{
				fuentes[indice_letra].x=i - w;
                fuentes[indice_letra].y=0;
                fuentes[indice_letra].w=w;
                fuentes[indice_letra].h=ima->h;
				esta_recorriendo_letra = false;
				indice_letra ++;
			}
		}
		else
		{
			/* si est� recorriendo una letra aumenta el contador
			 * de ancho, en caso contrario encontr� donde comienza
			 * la siguiente letra
			 */
			if (esta_recorriendo_letra)
				w ++;
			else
			{
				w = 1;
				esta_recorriendo_letra = true;
			}
		}
	}

	std::cout<<"Econtr� " <<indice_letra <<" letras en el archivo de fuentes\n";
}


/*
 * Relaciona un caracter con un n�mero entero
 */
int FuenteImagen::obtener_indice (char caracter){
	int i;
	
	if (caracter == ' ')
		return 1;

	for (i = 0; ordenLetras [i]; i ++)
	{
		if (caracter == ordenLetras [i])
			return i;
	}
	
	std::cout <<"No se puede encontrar el �ndice de:"<<caracter<<std::endl;
	return -1;
}


/*
 * imprime un caracter sobre la superficie dst (generalmente screen)
 */
int FuenteImagen::imprimir_letra (SDL_Surface * dst,int x, int y, char letra){
	SDL_Rect srcrect;
	SDL_Rect dstrect = {x, y, 0, 0};
	int indice = obtener_indice (letra);

	if (letra == ' ')
		return fuentes [0].w;

	
	if (indice != -1)
	{
		srcrect = fuentes [indice];
		SDL_BlitSurface(ima, &srcrect, dst, &dstrect);
	}
	return srcrect.w;
}

/*
 * imprime una cadena de textos completa sobre la superficie referenciada
 * por el primer par�metro
 */
void FuenteImagen::draw (SDL_Surface * screen, int x, int y, char * cadena)
{
	int i;
	int dx = x;

	for (i = 0; cadena [i]; i ++)
		dx += imprimir_letra (screen, dx, y, cadena [i]);
}
