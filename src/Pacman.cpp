#include "Pacman.hpp"
#include "NoEntiendo.hpp"

Pacman::Pacman(Tablero *_tablero)
{
	posicionX = posicionInicialX;
	posicionY = posicionInicialY;
	direccion = PACMAN_DIRECCION_DERECHA;
	bocaAbierta = false;
	muerto = false;
	
	tablero = _tablero;
}

Pacman::~Pacman()
{
}

void Pacman::Actualizar()
{
	if(!muerto)
	{	
		// Obtener intencion del jugador
		
		bool quiereIzquierda = NoEntiendo::EstaTeclaPulsada(TECLA_A);
		bool quiereDerecha = NoEntiendo::EstaTeclaPulsada(TECLA_D);
		bool quiereArriba = NoEntiendo::EstaTeclaPulsada(TECLA_W);
		bool quiereAbajo = NoEntiendo::EstaTeclaPulsada(TECLA_S);

		// Obtener informacion del entorno

		bool puedeIzquierda = true;
		bool puedeDerecha = true;
		bool puedeArriba = true;
		bool puedeAbajo = true;
		
		if(NoEntiendo::ObtenerTipoTile(tablero->tilemap, posicionX - 1, posicionY) == TABLERO_PARED)
		{
			puedeIzquierda = false;
		}
		
		if(NoEntiendo::ObtenerTipoTile(tablero->tilemap, posicionX + 1, posicionY) == TABLERO_PARED)
		{
			puedeDerecha = false;
		}
		
		if(NoEntiendo::ObtenerTipoTile(tablero->tilemap, posicionX, posicionY  - 1) == TABLERO_PARED)
		{
			puedeArriba = false;
		}
		
		if(NoEntiendo::ObtenerTipoTile(tablero->tilemap, posicionX, posicionY  + 1) == TABLERO_PARED)
		{
			puedeAbajo = false;
		}
		
		// Tomar la decision de cambiar la direccion
		
		if(quiereIzquierda && puedeIzquierda)
		{
			direccion = PACMAN_DIRECCION_IZQUIERDA;
		}
		else if(quiereDerecha && puedeDerecha)
		{
			direccion = PACMAN_DIRECCION_DERECHA;
		}
		else if(quiereArriba && puedeArriba)
		{
			direccion = PACMAN_DIRECCION_ARRIBA;
		}
		else if(quiereAbajo && puedeAbajo)
		{
			direccion = PACMAN_DIRECCION_ABAJO;
		}
		
		// Realizar el movimiento en la direccion, si es posible
		
		if(direccion == PACMAN_DIRECCION_IZQUIERDA && puedeIzquierda)
		{
			posicionX --;
		}
		else if(direccion == PACMAN_DIRECCION_DERECHA && puedeDerecha)
		{
			posicionX ++;
		}
		else if(direccion == PACMAN_DIRECCION_ARRIBA && puedeArriba)
		{
			posicionY --;
		}
		else if(direccion == PACMAN_DIRECCION_ABAJO && puedeAbajo)
		{
			posicionY ++;
		}
		
		if(bocaAbierta) { bocaAbierta = false; }
		else { bocaAbierta = true; }
		
		tablero->ComerCoco(posicionX, posicionY);
	}
}

void Pacman::Dibujar()
{
	int tile;
	if(bocaAbierta)
	{
		if(direccion == PACMAN_DIRECCION_IZQUIERDA)
		{
			tile = PACMAN_IZQUIERDA;
		}
		else if(direccion == PACMAN_DIRECCION_DERECHA)
		{
			tile = PACMAN_DERECHA;
		}
		else if(direccion == PACMAN_DIRECCION_ARRIBA)
		{
			tile = PACMAN_ARRIBA;
		}
		else // direccion == PACMAN_DIRECCION_ABAJO
		{
			tile = PACMAN_ABAJO;
		}
	}
	else
	{
		tile = PACMAN_NORMAL;
	}
	
	NoEntiendo::PonerTipoTile(tilemap, posicionX, posicionY, tile);

}

int Pacman::ObtenerPosicionX()
{
	return posicionX;

}

int Pacman::ObtenerPosicionY()
{
	return posicionY;

}

void Pacman::Matar()
{
	muerto = true;
}

bool Pacman::EstaMuerto()
{
	return muerto;
}