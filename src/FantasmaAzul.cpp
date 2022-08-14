#include "FantasmaAzul.hpp"
#include "NoEntiendo.hpp"

FantasmaAzul::FantasmaAzul(Pacman *_pacman, Tablero *_tablero):Fantasma(_pacman, _tablero)
{
	temporizadorCambioDireccion = 0;
}

FantasmaAzul::~FantasmaAzul()
{
}

void FantasmaAzul::Actualizar()
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
	
	printf("pasillo h=%d  v=%d cambio=%d\n", (int)pasilloHorizontal, (int)pasilloVertical, (int)quiereCambiarDireccion);
	
	if(pasilloHorizontal || pasilloVertical)
	{
		// Esta en un pasillo
		
		if(quiereCambiarDireccion)
		{
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

void FantasmaAzul::Dibujar()
{
	NoEntiendo::PonerTipoTile(tilemap, posicionX, posicionY, FANTASMAAZUL_NORMAL);
}
