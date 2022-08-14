#include "Tablero.hpp"
#include "NoEntiendo.hpp"

Tablero::Tablero()
{
	// Poner paredes
	
	PonerLineaHorizontalParedes(0,0, 16);
	PonerLineaHorizontalParedes(0,15, 16);
	PonerLineaHorizontalParedes(2,2, 5);
	PonerLineaHorizontalParedes(8,2, 6);
	PonerLineaHorizontalParedes(2,13, 5);
	PonerLineaHorizontalParedes(8,13, 6);
	PonerLineaHorizontalParedes(4,4, 8);
	PonerLineaHorizontalParedes(4,11, 8);
	PonerLineaHorizontalParedes(6,9, 4);
	
	PonerLineaVerticalParedes(0, 1, 14);	
	PonerLineaVerticalParedes(15, 1, 14);
	PonerLineaVerticalParedes(2, 3, 4);	
	PonerLineaVerticalParedes(2, 8, 5);	
	PonerLineaVerticalParedes(13, 3, 4);	
	PonerLineaVerticalParedes(13, 8, 5);	

	PonerLineaVerticalParedes(4, 5, 2);	
	PonerLineaVerticalParedes(4, 8, 3);	
	PonerLineaVerticalParedes(11, 5, 2);	
	PonerLineaVerticalParedes(11, 8, 3);	
	PonerLineaVerticalParedes(6, 6, 3);	
	PonerLineaVerticalParedes(9, 6, 3);
	
	// Poner cocos
	
	int ancho = NoEntiendo::ObtenerAnchoTilemap();
	int alto  = NoEntiendo::ObtenerAnchoTilemap();
	
	numCocos = 0;
	
	for(int x = 0; x < ancho; x ++)
	{
		for(int y = 0; y < alto; y ++)
		{
			int tipoTile = NoEntiendo::ObtenerTipoTile(tilemap, x, y);
			if(tipoTile != TABLERO_PARED)
			{
				NoEntiendo::PonerTipoTile(tilemap, x, y, TABLERO_COCO);
				numCocos ++;
			}
		}
	}
	
	
	
}

Tablero::~Tablero()
{
}

void Tablero::Dibujar()
{


	
}

bool Tablero::EsPared(int posX, int posY)
{
	return false;
}

bool Tablero::ComerCoco(int posX, int posY)
{
	if(NoEntiendo::ObtenerTipoTile(tilemap, posX, posY) == TABLERO_COCO)
	{
		NoEntiendo::PonerTipoTile(tilemap, posX, posY, NoEntiendo::tipoTileVacio);
		numCocos --;
		
		return true;
	}
	else
	{
		return false;
	}
}

bool Tablero::TodosCocosComidos()
{
	if(numCocos <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tablero::PonerLineaHorizontalParedes(int x, int y, int longitud)
{
	for(int i = 0; i < longitud; i ++)
	{
		NoEntiendo::PonerTipoTile(tilemap, x + i, y, TABLERO_PARED);
	}
}

void Tablero::PonerLineaVerticalParedes(int x, int y, int longitud)
{
	for(int i = 0; i < longitud; i ++)
	{
		NoEntiendo::PonerTipoTile(tilemap, x, y + i, TABLERO_PARED);
	}
}
