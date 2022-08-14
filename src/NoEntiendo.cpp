#include "NoEntiendo.hpp"

sfRenderWindow* NoEntiendo::ventana;
sfImage* NoEntiendo::icono;	
sfSprite** NoEntiendo::tiposTile;
int*** NoEntiendo::tilemaps;

bool NoEntiendo::Iniciar()
{
	// Iniciar ventana
	
    sfVideoMode mode = { tamanyoTile * anchoTilemap,
	                     tamanyoTile * altoTilemap,
						 bpp };
	
    ventana = sfRenderWindow_create(mode, TITULO_VENTANA, sfClose, NULL);
    if(!ventana) { return false; }
	
	char ruta[MAX_RUTA];
	sprintf(ruta, "%s%s", RUTA_RECURSOS, "icono.png");
	
	icono = sfImage_createFromFile(ruta);
	
	sfRenderWindow_setIcon(ventana, sfImage_getSize(icono).y, sfImage_getSize(icono).y, sfImage_getPixelsPtr(icono));
	
	// Cargar recursos
	
	tiposTile = new sfSprite*[numTiposTile];
	
	for(int i = 0; i < numTiposTile; i ++)
	{
		sfTexture* texture;
		
		sprintf(ruta, "%s%s%02d.png", RUTA_RECURSOS, RUTA_TIPOS_TILE, i);
		texture = sfTexture_createFromFile(ruta, NULL);

		tiposTile[i] = sfSprite_create();
		sfSprite_setTexture(tiposTile[i], texture, sfTrue);
		
	}
		
	// Iniciar tilemaps
	
	tilemaps = new int**[numTilemaps];
	
	for(int t = 0; t < numTilemaps; t++)
	{
		tilemaps[t] = new int *[altoTilemap];
		
		for(int y = 0; y < altoTilemap; y ++)
		{
			tilemaps[t][y] = new int[anchoTilemap];
			
			for(int x = 0; x < anchoTilemap; x ++)
			{
				tilemaps[t][y][x] = tipoTileVacio;
			}
		}
		
	}
	
	// Iniciar generador numeros aleatorios
	
	srand(getpid());
		
	return true;
	
}

bool NoEntiendo::EstaVentanaAbierta()
{
	return sfRenderWindow_isOpen(ventana);
	
}

void NoEntiendo::Actualizar()
{
    sfEvent event;

	/* Process events */
	while (sfRenderWindow_pollEvent(ventana, &event))
	{
		/* Close ventana : exit */
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(ventana);
	}
	
}


void NoEntiendo::Finalizar()
{
	// Liberar recursos

    sfRenderWindow_destroy(ventana);
	sfImage_destroy(icono);
		
	
}

void NoEntiendo::Esperar(int tiempo)
{
	sfTime t = sfMilliseconds(tiempo);
	sfSleep(t);
	
}

int NoEntiendo::ObtenerNumeroAleatorio(int minimo, int maximo)
{
	return minimo + rand() % (maximo - minimo + 1);
}

sfKeyCode NoEntiendo::codigosTecla[] = 
{
	sfKeyA,
	sfKeyB,
	sfKeyC,
	sfKeyD,
	sfKeyE,
	sfKeyF,
	sfKeyG,
	sfKeyH,
	sfKeyI,
	sfKeyJ,
	sfKeyK,
	sfKeyL,
	sfKeyM,
	sfKeyN,
	sfKeyO,
	sfKeyP,
	sfKeyQ,
	sfKeyR,
	sfKeyS,
	sfKeyT,
	sfKeyU,
	sfKeyV,
	sfKeyW,
	sfKeyX,
	sfKeyY,
	sfKeyZ,
	sfKeySpace,
	sfKeyEscape
};

bool NoEntiendo::EstaTeclaPulsada(Tecla tecla)
{
	return sfKeyboard_isKeyPressed(codigosTecla[tecla]);
}

int NoEntiendo::ObtenerPosicionXRaton()
{
	return sfMouse_getPosition((const sfWindow*)ventana).x / tamanyoTile;
}

int NoEntiendo::ObtenerPosicionYRaton()
{
	return sfMouse_getPosition((const sfWindow*)ventana).y / tamanyoTile;
}

bool NoEntiendo::EstaBotonRatonPulsado()
{
	return sfMouse_isButtonPressed(sfMouseLeft);
}

bool NoEntiendo::EstaEnTilemap(int posicionX, int posicionY)
{
	return posicionX >= 0 && posicionX < anchoTilemap && posicionY >= 0 && posicionY < altoTilemap;
}

void NoEntiendo::RellenarAreaTilemap(int tilemap, int posicionX, int posicionY, int ancho, int alto, int tipoBloque)
{
	for(int y = 0; y < alto; y++)
	{
		for(int x = 0; x < ancho; x++)
		{
			if(EstaEnTilemap(posicionX + x, posicionY + y))
			{
				tilemaps[tilemap][posicionY + y][posicionX + x] = tipoBloque;
			}
		}
	}

}

void NoEntiendo::RellenarTilemap(int tilemap, int tipoBloque)
{
	RellenarAreaTilemap(tilemap, 0, 0, anchoTilemap, altoTilemap, tipoBloque);
}

void NoEntiendo::LimpiarTilemap(int tilemap)
{
	RellenarTilemap(tilemap, tipoTileVacio);
}


void NoEntiendo::PonerTipoTile(int tilemap, int posicionX, int posicionY, int tipo)
{
	if(EstaEnTilemap(posicionX, posicionY))
	{
		tilemaps[tilemap][posicionY][posicionX] = tipo;
	}
}

int NoEntiendo::ObtenerTipoTile(int tilemap, int posicionX, int posicionY)
{
	if(EstaEnTilemap(posicionX, posicionY))
	{
		return tilemaps[tilemap][posicionY][posicionX];
	}
	else
	{
		return tipoTileVacio;
	}
}

int NoEntiendo::ObtenerAnchoTilemap()
{
	return anchoTilemap;
}

int NoEntiendo::ObtenerAltoTilemap()
{
	return altoTilemap;
}

void NoEntiendo::Dibujar()
{
	// Limpiar pantalla
	
	sfColor color = sfColor_fromRGB(colorFondoR,
	                                colorFondoG,
									colorFondoB);
									
   sfRenderWindow_clear(ventana, color);

	// Dibujar tilemaps

	for(int t = 0; t < numTilemaps; t++)
	{
	   for(int y = 0; y < altoTilemap; y++)
		{
			for(int x = 0; x < anchoTilemap; x++)
			{
				int tipoTile = tilemaps[t][y][x];
				if(tipoTile != tipoTileVacio)
				{
					sfSprite* sprite = tiposTile[tipoTile];
					
					sfVector2f position = { (float)x * tamanyoTile, (float)y * tamanyoTile };
					sfSprite_setPosition(sprite, position);
					
					const sfTexture* textura = sfSprite_getTexture(sprite);
					sfVector2u tamanyo = sfTexture_getSize(textura);

					sfVector2f escala = { (float)tamanyoTile / tamanyo.x, (float)tamanyoTile / tamanyo.y  };
					sfSprite_setScale(sprite, escala);

					sfRenderWindow_drawSprite(ventana, sprite, NULL);
				}
			}
		}
		
	}
	
	sfRenderWindow_display(ventana);

}

