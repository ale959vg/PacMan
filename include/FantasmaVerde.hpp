#ifndef _FANTASMAVERDE_HPP_
#define _FANTASMAVERDE_HPP_

#include "Fantasma.hpp"

enum FantasmVerdeTile
{
	FANTASMAVERDE_NORMAL = 14

};


class FantasmaVerde: public Fantasma
{
	public:
		FantasmaVerde(Pacman *_pacman, Tablero *_tablero);
		virtual ~FantasmaVerde();
		void Actualizar();
		void Dibujar();
	
	private:
		int temporizadorCambioDireccion;
		const int tiempoCambioDireccionMin = 8;
		const int tiempoCambioDireccionMax = 24;
		
		
		
	
};

#endif