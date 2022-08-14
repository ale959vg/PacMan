#include "Fantasma.hpp"
#include "NoEntiendo.hpp"

Fantasma::Fantasma(Pacman *_pacman, Tablero *_tablero)
{
	posicionX = NoEntiendo::ObtenerNumeroAleatorio(0, NoEntiendo::ObtenerAnchoTilemap() - 1);
	posicionY = NoEntiendo::ObtenerNumeroAleatorio(0, NoEntiendo::ObtenerAltoTilemap() - 1);

	while(NoEntiendo::ObtenerTipoTile(_tablero->tilemap, posicionX, posicionY) == TABLERO_PARED)
	{
		posicionX = NoEntiendo::ObtenerNumeroAleatorio(0, NoEntiendo::ObtenerAnchoTilemap() - 1);
		posicionY = NoEntiendo::ObtenerNumeroAleatorio(0, NoEntiendo::ObtenerAltoTilemap() - 1);
	}
	
	pacman = _pacman;
	tablero = _tablero;
	direccion = (FantasmaDireccion)NoEntiendo::ObtenerNumeroAleatorio((int)FANTASMA_DIRECCION_DERECHA, (int)FANTASMA_DIRECCION_ARRIBA);
}

Fantasma::~Fantasma()
{
}

void Fantasma::Actualizar()
{
	direccion = (FantasmaDireccion)NoEntiendo::ObtenerNumeroAleatorio((int)FANTASMA_DIRECCION_DERECHA, (int)FANTASMA_DIRECCION_ARRIBA);
	if(direccion == FANTASMA_DIRECCION_DERECHA) { posicionX ++; }
	else if(direccion == FANTASMA_DIRECCION_ABAJO) { posicionY ++; }
	else if(direccion == FANTASMA_DIRECCION_IZQUIERDA) { posicionX --; }
	else if(direccion == FANTASMA_DIRECCION_ARRIBA) { posicionY --; }
	
	int ancho = NoEntiendo::ObtenerAnchoTilemap();
	int alto  = NoEntiendo::ObtenerAltoTilemap();
	
	if(posicionX < 0) { posicionX = 0; }
	if(posicionX > ancho - 1) { posicionX = ancho - 1; }
	if(posicionY < 0) { posicionY = 0; }
	if(posicionY > alto - 1) { posicionY = alto - 1; }
	
}

void Fantasma::Dibujar()
{
	NoEntiendo::PonerTipoTile(tilemap, posicionX, posicionY, FANTASMA_NORMAL);
}

int Fantasma::ObtenerPosicionX()
{
	return posicionX;

}

int Fantasma::ObtenerPosicionY()
{
	return posicionY;

}