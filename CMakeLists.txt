cmake_minimum_required(VERSION 3.5)
project(Bomberman)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(SOURCE_FILES src/main.cpp src/engine/sprites/animacion/animacion.cpp src/personajes/bloque.cpp  src/constantes.hpp src/engine/sprites/animacion/Control_Animacion.cpp src/control_player.cpp src/engine/util/CMetaData.cpp src/editor.cpp src/explosion.cpp src/fuente_imagen.cpp src/galeria.cpp src/engine/util/game_manager.cpp src/personajes/globo.cpp src/engine/interfaces/InterfazUI.hpp src/item.cpp src/item.hpp src/Interfaces/juego.cpp src/Interfaces/juego_batalla.cpp src/Interfaces/juego_historia.cpp src/Interfaces/juego_mostrar_gan.cpp src/niveles/mapa.cpp src/menu.cpp src/menu_text.hpp src/personajes/player.cpp src/time.hpp src/util.cpp src/engine/sprites/CGroup.cpp src/engine/sprites/CSprite.cpp src/engine/layout/Componentes/BotonComponent.hpp src/engine/util/LTexture.cpp src/engine/util/LTexture.hpp src/engine/util/LTimer.cpp src/engine/util/LTimer.hpp src/engine/util/CFont.hpp src/engine/util/CFont.cpp src/Interfaces/MenuPrincipal.hpp src/engine/layout/Componentes/TextLabelComponent.hpp src/engine/layout/LayoutManager/LayoutVertical.hpp src/engine/layout/LayoutManager/LayoutComponent.hpp src/Interfaces/MenuNuevoJuego.hpp src/engine/interfaces/MenuListLabel.hpp src/Interfaces/MenuModoMultijugador.hpp src/engine/layout/LayoutManager/LayoutAbsolute.hpp src/engine/layout/Componentes/Component.hpp src/engine/layout/LayoutManager/LayoutParent.hpp src/engine/layout/Componentes/ImageComponent.hpp src/engine/sprites/CDrawGroup.hpp src/engine/sprites/CUpdateGrow.hpp src/engine/interfaces/InterfazSpriteGroup.hpp src/engine/util/SpriteSheet.hpp src/engine/mapa/include/TMXParser.cpp src/engine/mapa/include/TMXParser.h src/engine/mapa/include/rapidxml/rapidxml.hpp  src/engine/mapa/include/rapidxml/rapidxml_utils.hpp  src/engine/mapa/include/rapidxml/rapidxml_print.hpp  src/engine/mapa/include/rapidxml/rapidxml_iterators.hpp src/engine/interfaces/InterfazGaleria.hpp src/engine/sprites/SpriteContainer.hpp)

add_executable(Bomberman ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2IMIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2IMIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})
