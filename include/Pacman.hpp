#ifndef _PACMAN_HPP_
#define _PACMAN_HPP_

#include "Tablero.hpp"

enum PacmanTile
{
	PACMAN_NORMAL = 3,
	PACMAN_DERECHA,
	PACMAN_ABAJO,
	PACMAN_IZQUIERDA,
	PACMAN_ARRIBA

};

enum PacmanDireccion
{
	PACMAN_DIRECCION_DERECHA,
	PACMAN_DIRECCION_ABAJO,
	PACMAN_DIRECCION_IZQUIERDA,
	PACMAN_DIRECCION_ARRIBA
	
};

class Pacman
{
	public:
		Pacman(Tablero *_tablero);
		~Pacman();
		void Actualizar();
		void Dibujar();
		int ObtenerPosicionX();
		int ObtenerPosicionY();
		void Matar();
		bool EstaMuerto();
	private:
		int posicionX;
		int posicionY;
		bool bocaAbierta;
		bool muerto;
		PacmanDireccion direccion;
		
		
		Tablero *tablero;
		
		const int tilemap = 2;
		const int posicionInicialX = 7;
		const int posicionInicialY = 10;
	
};

#endif