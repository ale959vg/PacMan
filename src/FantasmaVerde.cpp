#include "FantasmaVerde.hpp"
#include "NoEntiendo.hpp"
#include <stdlib.h>

FantasmaVerde::FantasmaVerde(Pacman *_pacman, Tablero *_tablero):Fantasma(_pacman, _tablero)
{
	temporizadorCambioDireccion = 0;
}

FantasmaVerde::~FantasmaVerde()
{
}

void FantasmaVerde::Actualizar()
{
	bool quiereCambiarDireccion = false;

	// Actualizar temporizador

	temporizadorCambioDireccion --;
	
	if(temporizadorCambioDireccion <= 0)
	{
		quiereCambiarDireccion = true;
		temporizadorCambioDireccion = NoEntiendo::ObtenerNumeroAleatorio(tiempoCambioDireccionMin, tiempoCambioDireccionMax);
		
	}
	
	
	// Comprueba que direcciones tiene disponibles
	
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
	
	int numSalidas = 0;
	if(puedeIzquierda) { numSalidas ++;  }
	if(puedeDerecha) { numSalidas ++;  }
	if(puedeArriba) { numSalidas ++;  }
	if(puedeAbajo) { numSalidas ++;  }

	// Miramos si estamos en un pasillo o no
	
	bool pasilloVertical;
	
	if(puedeArriba && puedeAbajo && !puedeIzquierda && !puedeDerecha)
	{
		pasilloVertical = true;
	}
	else
	{
		pasilloVertical = false;
	}
	
	bool pasilloHorizontal;
	
	if(puedeIzquierda && puedeDerecha && !puedeArriba && !puedeAbajo)
	{
		pasilloHorizontal = true;
	}
	else
	{
		pasilloHorizontal = false;
	}
	
	
	// Decidir hacia donde queremos movernos
	
	bool quiereIzquierda;
	bool quiereDerecha;
	bool quiereArriba;
	bool quiereAbajo;
	
	//printf("pasillo h=%d  v=%d cambio=%d\n", (int)pasilloHorizontal, (int)pasilloVertical, (int)quiereCambiarDireccion);
	
	if(pasilloHorizontal || pasilloVertical)
	{	
		// Esta en un pasillo
	
		if(quiereCambiarDireccion)
		{
			if(NoEntiendo::ObtenerNumeroAleatorio(0, 1) == 0)
			{
				// Seguimos al pacman
				
				if(pasilloHorizontal)
				{
					if(pacman->ObtenerPosicionX() < posicionX)
					{
						direccion = FANTASMA_DIRECCION_IZQUIERDA;
						printf("Player mas cerca a la izquierda \n");
					}
					else
					{
						direccion = FANTASMA_DIRECCION_DERECHA;
						printf("Player mas cerca a la derecha \n");
					}						
					
				}
				else // pasilloVertical
				{
					if(pacman->ObtenerPosicionY() < posicionY)
					{
						direccion = FANTASMA_DIRECCION_ARRIBA;
					}
					else
					{
						direccion = FANTASMA_DIRECCION_ABAJO;
					}	
				}
			}
			else
			{
				// Comportamiento como el azul
				
				if(pasilloHorizontal)
				{
					if(direccion == FANTASMA_DIRECCION_DERECHA)
					{
						direccion = FANTASMA_DIRECCION_IZQUIERDA;
					}
					else
					{
						direccion = FANTASMA_DIRECCION_DERECHA;
					}
				}
				else // pasilloVertical
				{
					if(direccion == FANTASMA_DIRECCION_ARRIBA)
					{
						direccion = FANTASMA_DIRECCION_ABAJO;
					}
					else
					{
						direccion = FANTASMA_DIRECCION_ARRIBA;
					}				
				}
			}			
			
		}
	}
	else
	{
		// Esta en un cruce		
			
		if(numSalidas == 0)
		{
			// Nada
		}
		else if(numSalidas == 1)
		{
			if(puedeDerecha) { direccion = FANTASMA_DIRECCION_DERECHA; }
			else if(puedeAbajo) { direccion = FANTASMA_DIRECCION_ABAJO; }
			else if(puedeIzquierda) { direccion = FANTASMA_DIRECCION_IZQUIERDA; }
			else // puedeArriba
			{ direccion = FANTASMA_DIRECCION_ARRIBA; }
		}
		else
		{
			bool movimientoInteligente = false;
			
			if(NoEntiendo::ObtenerNumeroAleatorio(0, 1) == 0)
			{
				int diferenciaX = abs(pacman->ObtenerPosicionX() - posicionX);
				int diferenciaY = abs(pacman->ObtenerPosicionY() - posicionY);
				bool mejorHorizontal = false;
				bool mejorVertical = false;
				
				if(diferenciaY == 0)
				{ 
					mejorHorizontal = true;
				}
				else if(diferenciaX == 0)
				{ 
					mejorVertical = true;
				}
				else if(diferenciaX < diferenciaY)
				{
					mejorHorizontal = true;
				}
				if(diferenciaY < diferenciaX)
				{
					mejorVertical = true;
				}
				
				// printf("Mejor h: %d v: %d dx: %d dy: %d\n", (int)mejorHorizontal, (int)mejorVertical, diferenciaX, diferenciaY);
				if(pacman->ObtenerPosicionX() < posicionX && puedeIzquierda && mejorHorizontal)
				{
					direccion = FANTASMA_DIRECCION_IZQUIERDA;
					movimientoInteligente = true;
				}
				else if(pacman->ObtenerPosicionX() >= posicionX && puedeDerecha && mejorHorizontal)
				{
					direccion = FANTASMA_DIRECCION_DERECHA;
					movimientoInteligente = true;
				}
				else if(pacman->ObtenerPosicionY() < posicionY && puedeArriba && mejorVertical)
				{
					direccion = FANTASMA_DIRECCION_ARRIBA;
					movimientoInteligente = true;
					
				}
				else if(pacman->ObtenerPosicionY() >= posicionY && puedeAbajo && mejorVertical)
				{
					direccion = FANTASMA_DIRECCION_ABAJO;
					movimientoInteligente = true;
					
				}
			}
			
			if(!movimientoInteligente)
			{
				// Comportamiento como el fantasma azul
				
				FantasmaDireccion direccionNueva = (FantasmaDireccion)NoEntiendo::ObtenerNumeroAleatorio((int)FANTASMA_DIRECCION_DERECHA, (int)FANTASMA_DIRECCION_ARRIBA);
				
				// Seguimos sorteando direcciones mientras lo que nos salga:
				// Sea una media vuelta
				// O sea una direccion bloqueada
				
				while(
					direccion == FANTASMA_DIRECCION_DERECHA && direccionNueva == FANTASMA_DIRECCION_IZQUIERDA && puedeIzquierda ||
					direccion == FANTASMA_DIRECCION_IZQUIERDA && direccionNueva == FANTASMA_DIRECCION_DERECHA && puedeDerecha ||
					direccion == FANTASMA_DIRECCION_ARRIBA && direccionNueva == FANTASMA_DIRECCION_ABAJO && puedeAbajo ||
					direccion == FANTASMA_DIRECCION_ABAJO && direccionNueva == FANTASMA_DIRECCION_ARRIBA && puedeArriba ||
					direccionNueva == FANTASMA_DIRECCION_DERECHA && !puedeDerecha ||
					direccionNueva == FANTASMA_DIRECCION_IZQUIERDA && !puedeIzquierda ||
					direccionNueva == FANTASMA_DIRECCION_ARRIBA && !puedeArriba ||
					direccionNueva == FANTASMA_DIRECCION_ABAJO && !puedeAbajo
					)
				{
					direccionNueva = (FantasmaDireccion)NoEntiendo::ObtenerNumeroAleatorio((int)FANTASMA_DIRECCION_DERECHA, (int)FANTASMA_DIRECCION_ARRIBA);
				}
				
				direccion = direccionNueva;
			}

			

		}	
		
	
	}
	
	
	// Matamos al pacman si chocamos con el
	// NOTA: Esto evita que nos crucemos con el
	
	if(pacman->ObtenerPosicionX() == posicionX && pacman->ObtenerPosicionY() == posicionY)
	{
		pacman->Matar();
	}

	
	// Realizar el movimiento en la direccion, si es posible
	
	if(direccion == FANTASMA_DIRECCION_IZQUIERDA && puedeIzquierda)
	{
		posicionX --;
	}
	else if(direccion == FANTASMA_DIRECCION_DERECHA && puedeDerecha)
	{
		posicionX ++;
	}
	else if(direccion == FANTASMA_DIRECCION_ARRIBA && puedeArriba)
	{
		posicionY --;
	}
	else if(direccion == FANTASMA_DIRECCION_ABAJO && puedeAbajo)
	{
		posicionY ++;
	}

	// Matamos al pacman si chocamos con el en la nueva posicion
	
	if(pacman->ObtenerPosicionX() == posicionX && pacman->ObtenerPosicionY() == posicionY)
	{
		pacman->Matar();
	}	

	
}

void FantasmaVerde::Dibujar()
{
	NoEntiendo::PonerTipoTile(tilemap, posicionX, posicionY, FANTASMAVERDE_NORMAL);
}
