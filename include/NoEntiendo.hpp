#ifndef NOENTIENDO_HPP
#define NOENTIENDO_HPP

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#define MAX_RUTA 200
#define TITULO_VENTANA "NoEntiendo 1.0"
#define RUTA_RECURSOS "Recursos/"
#define RUTA_TIPOS_TILE "TiposTile/"
		
enum Tecla
{
	TECLA_A,
	TECLA_B,
	TECLA_C,
	TECLA_D,
	TECLA_E,
	TECLA_F,
	TECLA_G,
	TECLA_H,
	TECLA_I,
	TECLA_J,
	TECLA_K,
	TECLA_L,
	TECLA_M,
	TECLA_N,
	TECLA_O,
	TECLA_P,
	TECLA_Q,
	TECLA_R,
	TECLA_S,
	TECLA_T,
	TECLA_U,
	TECLA_V,
	TECLA_W,
	TECLA_X,
	TECLA_Y,
	TECLA_Z,
	TECLA_ESPACIO,
	TECLA_ESCAPE
	
	
};


class NoEntiendo
{
	public:
	
		// Inicializacion y terminacion
		
		static bool Iniciar();
		static void Finalizar();

		// Bucle de juego

		static bool EstaVentanaAbierta();
		static void Actualizar();
		static void Dibujar();
		
		// Tilemaps y tipos de tile
		
		
		static int ObtenerAnchoTilemap();
		static int ObtenerAltoTilemap();
		
		static int ObtenerNumeroTilemaps();
		static int ObtenerNumeroTiposTile();
				
		static const int tipoTileVacio    = 0;

		static int ObtenerTipoTile(int tilemap, int posicionX, int posicionY);
		static void PonerTipoTile(int tilemap, int posicionX, int posicionY, int tipoTile);
		
		static void LimpiarTilemap(int tilemap);
		
		// Tiempo
		
		static void Esperar(int tiempo);
		
		// Aleatoriedad
		
		static int ObtenerNumeroAleatorio(int minimo, int maximo);
		
		// Entrada
		
		static bool EstaTeclaPulsada(Tecla tecla);
		static int  ObtenerPosicionXRaton();
		static int  ObtenerPosicionYRaton();
		static bool EstaBotonRatonPulsado();
		
	private:
	
		static const int bpp = 32;

		static const int colorFondoR = 0;
		static const int colorFondoG = 0;
		static const int colorFondoB = 0;
		
		static const int tamanyoTile = 32;
		static const int anchoTilemap = 16;
		static const int altoTilemap  = 16;
		
		static const int numTiposTile = 19;
		static const int numTilemaps = 3;	
	
		static sfRenderWindow* ventana;
		static sfImage* icono;	
		static sfSprite **tiposTile;
		static int ***tilemaps;
		
		static sfKeyCode codigosTecla[];
		
		static bool EstaEnTilemap(int x, int y);
		static void RellenarAreaTilemap(int capa, int posicionX, int posicionY, int ancho, int alto, int tipoBloque);
		static void RellenarTilemap(int tilemap, int tipoBloque);
		

		
};


#endif

