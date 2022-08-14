#ifndef _FANTASMAAZUL_HPP_
#define _FANTASMAAZUL_HPP_

#include "Fantasma.hpp"

enum FantasmAzulTile
{
	FANTASMAAZUL_NORMAL = 13

};


class FantasmaAzul: public Fantasma
{
	public:
		FantasmaAzul(Pacman *_pacman, Tablero *_tablero);
		virtual ~FantasmaAzul();
		void Actualizar();
		void Dibujar();
	
	private:
		int temporizadorCambioDireccion;
		const int tiempoCambioDireccionMin = 8;
		const int tiempoCambioDireccionMax = 24;
		
		
		
	
};

#endif