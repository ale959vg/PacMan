#ifndef _FANTASMA_HPP_
#define _FANTASMA_HPP_

#include "Tablero.hpp"
#include "Pacman.hpp"

enum FantasmaTile
{
	FANTASMA_NORMAL = 13

};

enum FantasmaDireccion
{
	FANTASMA_DIRECCION_DERECHA,
	FANTASMA_DIRECCION_ABAJO,
	FANTASMA_DIRECCION_IZQUIERDA,
	FANTASMA_DIRECCION_ARRIBA,
	
};

class Fantasma
{
	public:
		Fantasma(Pacman *_pacman, Tablero *_tablero);
		virtual ~Fantasma();
		virtual void Actualizar();
		virtual void Dibujar();
		int ObtenerPosicionX();
		int ObtenerPosicionY();

	protected:
		int posicionX;
		int posicionY;
		FantasmaDireccion direccion;
		
		Pacman *pacman;
		Tablero *tablero;
		
		const int tilemap = 1;
	
};

#endif