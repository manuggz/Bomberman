//#include "editor.hpp"
//
//
//Editor::Editor(GameManager * game):
//    botonBorrar(game->getImagen(IMG_BOTON_BORRAR_MAPA),this){
//    #ifdef DEBUG
//        cout << "Constructor de Editor: "<<this<<endl;
//    #endif
//    //,150,221
//    this->game=game;
//
//    rects_botones[0][EDITOR_BOTON_FLECHA].x=57;
//    rects_botones[0][EDITOR_BOTON_FLECHA].y=16;
//    rects_botones[0][EDITOR_BOTON_FLECHA].w=21;
//    rects_botones[0][EDITOR_BOTON_FLECHA].h=19;
//    estados_botones[0][EDITOR_BOTON_FLECHA]=BOTON_NORMAL;
//
//    rects_botones[0][EDITOR_BOTON_GUARDAR].x=235;
//    rects_botones[0][EDITOR_BOTON_GUARDAR].y=221;
//    rects_botones[0][EDITOR_BOTON_GUARDAR].w=81;
//    rects_botones[0][EDITOR_BOTON_GUARDAR].h=18;
//    estados_botones[0][EDITOR_BOTON_GUARDAR]=BOTON_NORMAL;
//
//    botonBorrar.bindAccion(&Editor::borrarMapa);
////    botonBorrar.bindAccion(borrarMapaNoEstatico);
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MAS].x=88;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MAS].y=5;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MAS].w=17;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MAS].h=10;
//    estados_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MAS]=BOTON_NORMAL;
//
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MENOS].x=111;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MENOS].y=5;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MENOS].w=17;
//    rects_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MENOS].h=10;
//    estados_botones[EDITOR_MODIF_BOMBA][EDITOR_BOTON_MENOS]=BOTON_NORMAL;
//
//
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MAS].x=151;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MAS].y=5;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MAS].w=17;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MAS].h=10;
//    estados_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MAS]=BOTON_NORMAL;
//
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MENOS].x=173;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MENOS].y=5;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MENOS].w=17;
//    rects_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MENOS].h=10;
//    estados_botones[EDITOR_MODIF_EXPLOSION][EDITOR_BOTON_MENOS]=BOTON_NORMAL;
//
//
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MAS].x=215;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MAS].y=5;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MAS].w=17;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MAS].h=10;
//    estados_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MAS]=BOTON_NORMAL;
//
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MENOS].x=237;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MENOS].y=5;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MENOS].w=17;
//    rects_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MENOS].h=10;
//    estados_botones[EDITOR_MODIF_VIDAS][EDITOR_BOTON_MENOS]=BOTON_NORMAL;
//
//
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MAS].x=269;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MAS].y=5;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MAS].w=17;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MAS].h=10;
//    estados_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MAS]=BOTON_NORMAL;
//
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MENOS].x=292;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MENOS].y=5;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MENOS].w=17;
//    rects_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MENOS].h=10;
//    estados_botones[EDITOR_MODIF_ITEMS][EDITOR_BOTON_MENOS]=BOTON_NORMAL;
//
//    //para la ventana 1
//    rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].x=17;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].y=67;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].w=60;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].h=27;
//    estados_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA]=BOTON_NORMAL;
//
//    rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].x=239;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].y=67;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].w=60;
//    rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].h=27;
//    estados_botones_elegir_terreno[EDITOR_FLECHA_DERECHA]=BOTON_NORMAL;
//
//    rects_botones_elegir_terreno[EDITOR_MAPA_1].x=26;
//    rects_botones_elegir_terreno[EDITOR_MAPA_1].y=102;
//    rects_botones_elegir_terreno[EDITOR_MAPA_1].w=111;
//    rects_botones_elegir_terreno[EDITOR_MAPA_1].h=121;
//    estados_botones_elegir_terreno[EDITOR_MAPA_1]=BOTON_NORMAL;
//
//    rects_botones_elegir_terreno[EDITOR_MAPA_2].x=177;
//    rects_botones_elegir_terreno[EDITOR_MAPA_2].y=102;
//    rects_botones_elegir_terreno[EDITOR_MAPA_2].w=111;
//    rects_botones_elegir_terreno[EDITOR_MAPA_2].h=121;
//    estados_botones_elegir_terreno[EDITOR_MAPA_2]=BOTON_NORMAL;
//    boton_visible[EDITOR_MAPA_1]=1;
//
//    SDL_ShowCursor(SDL_ENABLE);
//
//    tile_activo=-1;
//    id_nivel=0;
//
//
//    maxTerrenoBatalla=std::stoi(buscar_dato(RUTA_CONFIG_BASE,"MaxTerreno"));
//    //realizamos las previews de los niveles ya creados
//    player_activo=PLAYER_NONE;
//    previews_niveles=0;
//    crearReferencias();
//    game->playSonido(SND_EDITOR);
//
//    cambiarVentana(EDITOR_ABRIR_NIVEL);
//
//}
//
//void Editor::crearReferencias(){
//    char ruta[50];
//    if(previews_niveles){
//         for(int i=0;i<maxTerrenoBatalla;i++){
//            #ifdef DEBUG
//                cout << "liberando Surface:"<<previews_niveles[i]<<endl;
//            #endif
//             SDL_DestroyTexture(previews_niveles[i]);
//            previews_niveles[i]=NULL;
//         }
//        #ifdef DEBUG
//            cout << "liberando Surface:"<<previews_niveles[mMaxTerrenoBatalla]<<endl;
//        #endif
//         if(botonBorrar.getVisible())SDL_DestroyTexture(previews_niveles[maxTerrenoBatalla]);
//         previews_niveles[maxTerrenoBatalla]=NULL;
//        #ifdef DEBUG
//            cout << "liberando Previews:"<<previews_niveles<<endl;
//        #endif
//        delete [] previews_niveles;
//        previews_niveles=NULL;
//    }
//    previews_niveles=new SDL_Texture*[maxTerrenoBatalla + 1];
//    #ifdef DEBUG
//        cout << "creada Previews:"<<previews_niveles<<endl;
//    #endif
//
//    MetaData * data2;
//    LTexture * img_players[5]={game->getImagen(IMG_PLAYER_1),
//                                  game->getImagen(IMG_PLAYER_2),
//                                  game->getImagen(IMG_PLAYER_3),
//                                  game->getImagen(IMG_PLAYER_4),
//                                  game->getImagen(IMG_PLAYER_5)};
//    for(int i=0;i<maxTerrenoBatalla;i++){
//        sprintf(ruta,"data/niveles/batalla/%d.txt",i+ 1);
//        data2=new MetaData(ruta);
//        sprintf(ruta,"data/niveles/batalla/%d.map",i+ 1);
//        previews_niveles[i]=Mapa::getPreviewTerreno(ruta,data2,game->getImagen(IMG_TILES),img_players,8,40);
//    #ifdef DEBUG
//        cout << "Creada Surface: "<<previews_niveles[i]<<endl;
//    #endif
//        delete data2;
//    }
//    //realizamos la preview del "nuevo nivel"
//
//    sprintf(ruta,"data/niveles/batalla/%d.map",NIVEL_BASE);
//    previews_niveles[maxTerrenoBatalla]=Mapa::getPreviewTerreno(ruta,NULL,game->getImagen(IMG_TILES),NULL,8,40);
//    #ifdef DEBUG
//        cout << "Creada Surface: "<<previews_niveles[mMaxTerrenoBatalla]<<endl;
//    #endif
//
//}
//void Editor::cambiarVentana(int nueva){
//    ventana=nueva;
//
//    if(ventana==EDITOR_ABRIR_NIVEL)cambiarPagina(1);
//}
//
//void Editor::cambiarPagina(unsigned int num_pagina){
//        pagina=num_pagina;
//
//        if(pagina==1){
//            boton_visible[EDITOR_FLECHA_IZQUIERDA]=false;
//        }else{
//            boton_visible[EDITOR_FLECHA_IZQUIERDA]=true;
//            }
//
//        if((maxTerrenoBatalla+1)-pagina*2<=0){
//            boton_visible[EDITOR_FLECHA_DERECHA]=false;
//        }else{
//            boton_visible[EDITOR_FLECHA_DERECHA]=true;
//            }
//
//        if((maxTerrenoBatalla+1)-pagina*2==-1){
//            boton_visible[EDITOR_MAPA_2]=false;
//        }else{
//            boton_visible[EDITOR_MAPA_2]=true;
//            }
//
//}
//
//void Editor::iniciarEdicion(int id){
//    tile_activo=-1;
//    player_activo=PLAYER_NONE;
//    mantiene_presionado=false;
//    id_nivel=id;
//    char ruta[40];
//
//    if(id !=NIVEL_BASE){
//        sprintf(ruta,"data/niveles/batalla/%d.map",id + 1);
//        Mapa::cargarMapaDeArchivoBin(ruta,mapa);
//        sprintf(ruta,"data/niveles/batalla/%d.txt",id + 1);
//
//        if(data)delete data;
//        data=new MetaData(ruta);
//        botonBorrar.setVisible(true);
//        leerInfTile();
//
//    }else{
//        botonBorrar.setVisible(false);
//        sprintf(ruta,"data/niveles/batalla/%d.map",NIVEL_BASE);
//        Mapa::cargarMapaDeArchivoBin(ruta,mapa);
//        if(data)delete data;
//        data=new MetaData();
//        sprintf(ruta,"data/niveles/batalla/%d.map",NIVEL_BASE + 1);
//        data->setBombas(1);
//        data->setAlcanceBombas(1);
//
//        data->setX(PLAYER_1,X_INIT_PLAYER_1);
//        data->setY(PLAYER_1,Y_INIT_PLAYER_1);
//
//        data->setX(PLAYER_2,X_INIT_PLAYER_2);
//        data->setY(PLAYER_2,Y_INIT_PLAYER_2);
//
//        data->setX(PLAYER_3,X_INIT_PLAYER_3);
//        data->setY(PLAYER_3,Y_INIT_PLAYER_3);
//
//        data->setX(PLAYER_4,X_INIT_PLAYER_4);
//        data->setY(PLAYER_4,Y_INIT_PLAYER_4);
//
//        data->setX(PLAYER_5,X_INIT_PLAYER_5);
//        data->setY(PLAYER_5,Y_INIT_PLAYER_5);
//        EjeX=25;
//        EjeY=58;
//        yTablero=8;
//        idFondo=IMG_FONDO_METAL;
//
//     }
//
//    cambiarVentana(EDICION_NIVEL);
//}
//void Editor::leerInfTile(){
//    char key[50],valor[50];
//    sprintf(key,"data/imagenes/objetos/tile_%d.txt",data->getIdTile() + 1);
//    ifstream ftile(key);
//    while(!ftile.eof()){
//        ftile >>key;
//        if(!strcmp(key,"IMG_FONDO")){
//            ftile>>valor;
//            if(!strcmp(valor,"FONDO_1"))
//                idFondo=IMG_FONDO_PARTI;
//            else if(!strcmp(valor,"FONDO_2"))
//                idFondo=IMG_FONDO_EDIFICIOS;
//            else if(!strcmp(valor,"FONDO_3"))
//                idFondo=IMG_FONDO_METAL;
//        }else if(!strcmp(key,"EJES")){
//            ftile>>EjeX>>EjeY;
//        }else if(!strcmp(key,"Y_TABLERO")){
//            ftile>>yTablero;
//        }else{
//            ftile>>valor;
//        }
//    }
//    ftile.close();
//
//}
//void Editor::guardarMapa(){
//    char ruta[50];
//    int id_file=id_nivel+1;
//    if(id_nivel ==NIVEL_BASE){
//        id_file=++maxTerrenoBatalla;
//    }
//
//    sprintf(ruta,"data/niveles/batalla/%d.map",id_file);
//    ofstream fs2(ruta,ios::out|ios::binary);
//    if(!fs2){cout << "Error guardando mapa en archivo:"<<ruta<<endl;return;}
//
//    fs2.write(reinterpret_cast<char *> (mapa),Mapa::MAXMAP);
//    fs2.close();
//
//    sprintf(ruta,"data/niveles/batalla/%d.txt",id_file);
//    data->guardar(ruta);
//
//    int puntaje=std::stoi(buscar_dato(RUTA_CONFIG_BASE,"Puntaje"));
//    ofstream file(RUTA_CONFIG_BASE);
//    file << "MaxTerreno:"<<maxTerrenoBatalla<<endl;
//    file << "Puntaje:"<<puntaje<<endl;
//    file.close();
//    crearReferencias();
//}
//
//void Editor::borrarMapa(){
//    char ruta[50],nuevaRuta[50];
//    int id_file=id_nivel+1;
//
//    sprintf(ruta,"data/niveles/batalla/%d.map",id_file);
//    //cout << "Borrar:"<<ruta<<endl;
//    if(remove(ruta)){
//        cout <<"Error borrando: "<<ruta<<endl;
//    }
//
//    sprintf(ruta,"data/niveles/batalla/%d.txt",id_file);
//    //cout << "Borrar:"<<ruta<<endl;
//    if(remove(ruta)){
//        cout <<"Error borrando: "<<ruta<<endl;
//        return;
//    }
//    /*Funci�n auxiliar no estatica para poder usar el boton*/
//    maxTerrenoBatalla--;
//    int puntaje=std::stoi(buscar_dato(RUTA_CONFIG_BASE,"Puntaje"));
//    ofstream file(RUTA_CONFIG_BASE);
//    file << "MaxTerreno:"<<maxTerrenoBatalla<<endl;
//    file << "Puntaje:"<<puntaje<<endl;
//    file.close();
//
//    for(int i=0;i<maxTerrenoBatalla+1-id_file;i++){
//        sprintf(ruta,"data/niveles/batalla/%d.map",id_file+i+1);
//        sprintf(nuevaRuta,"data/niveles/batalla/%d.map",id_file+i);
//        //cout << "Renombrando:"<<ruta<<" a :"<<nuevaRuta<<endl;
//	    rename(ruta,nuevaRuta);
//
//        sprintf(ruta,"data/niveles/batalla/%d.txt",id_file+i+1);
//        sprintf(nuevaRuta,"data/niveles/batalla/%d.txt",id_file+i);
//        //cout << "Renombrando:"<<ruta<<" a :"<<nuevaRuta<<endl;
//	    rename(ruta,nuevaRuta);
//
//    }
//
//    crearReferencias();
//    cambiarVentana(EDITOR_ABRIR_NIVEL);
//
//}
//
//
//
//bool Editor::EditPointMap(SDL_Event * evento){
//
//    if(punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,EjeX,EjeY,272,176)&&tile_activo!=-1){
//        int x=(evento->motion.x- EjeX)/16 ,y=(evento->motion.y - EjeY)/16 ; //calculamos la posicion del cursor respecto a los tiles
//        if(mapa[y*Mapa::COLUMNAS+x]!=tile_activo){//si no es el mismo
//            /*reproducimos un sonido de acuerdo al mGrpBloques anterior que estaba ahy*/
//            if(mapa[y*Mapa::COLUMNAS+x]!=Mapa::BLOQUE_PISO&&mapa[y*Mapa::COLUMNAS+x]!=Mapa::BLOQUE_PISO_SOMBRA){//si ya estaba ocupado
//                game->play(SFX_TONO_SECO);
//            }
//            game->play(SFX_TONO_ACUATICO);
//            if((tile_activo==Mapa::BLOQUE_PISO&&evento->motion.y-16>=EjeY&&mapa[((evento->motion.y -16- EjeY)/16)*Mapa::COLUMNAS+x]!=Mapa::BLOQUE_PISO&&mapa[((evento->motion.y -16- EjeY)/16)*Mapa::COLUMNAS+x]!=Mapa::BLOQUE_PISO_SOMBRA)||(y==0&&tile_activo==Mapa::BLOQUE_PISO)||(tile_activo==Mapa::BLOQUE_PISO&&mapa[y*Mapa::COLUMNAS+x]==Mapa::BLOQUE_PISO_SOMBRA))
//                mapa[y*Mapa::COLUMNAS+x]=Mapa::BLOQUE_PISO_SOMBRA;
//            else
//                mapa[y*Mapa::COLUMNAS+x]=tile_activo;//MODIFICAMOS EL MAPA
//
//            if(tile_activo!=Mapa::BLOQUE_PISO){
//                if(evento->motion.y+16!=EjeY+Mapa::FILAS*16&&mapa[((evento->motion.y +16- EjeY)/16)*Mapa::COLUMNAS+x]==Mapa::BLOQUE_PISO){
//                    mapa[((evento->motion.y +16- EjeY)/16)*Mapa::COLUMNAS+x]=Mapa::BLOQUE_PISO_SOMBRA;
//                }
//            }else{
//                if(evento->motion.y+16<=EjeY+Mapa::FILAS*16&&mapa[((evento->motion.y +16- EjeY)/16)*Mapa::COLUMNAS+x]==Mapa::BLOQUE_PISO_SOMBRA){
//                    mapa[((evento->motion.y +16- EjeY)/16)*Mapa::COLUMNAS+x]=Mapa::BLOQUE_PISO;
//                }
//            }
//            return true;
//        }else
//            return true;//REGRESAMOS "TRUE" PORQUE AL MENOS PASO LA PRIMERA PRUEBA SOLO QUE EN ESE PUNTO YA ESTABA EL MISMO TILE
//    }
//    return false;
//}
//void Editor::procesarEvento(SDL_Event * evento){
//        static int i,j;
//
//        switch(ventana){
//
//            case EDICION_NIVEL:
//                botonBorrar.procesarEvento(evento);
//                if(evento->type==SDL_KEYDOWN&&evento->key.keysym.sym==SDLK_ESCAPE){
//                    cambiarVentana(EDITOR_ABRIR_NIVEL);
//                }else if(evento->type == SDL_MOUSEMOTION){
//                    for(i=0;i<5;i++){
//                        for(j=0;j<2;j++){
//                            if(i==0&&j==EDITOR_BOTON_GUARDAR)continue;
//                        	if(punto_en_rect(evento->motion.x,evento->motion.y-yTablero,&rects_botones[i][j])){
//                                if(estados_botones[i][j]!=BOTON_PRESIONADO)
//                        				estados_botones[i][j]=BOTON_RESALTADO;
//                            }
//                			else
//                				estados_botones[i][j]=BOTON_NORMAL;
//                        }
//                    }
//
//                	if(punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones[0][EDITOR_BOTON_GUARDAR])){
//                        if(estados_botones[0][EDITOR_BOTON_GUARDAR]!=BOTON_PRESIONADO)
//                				estados_botones[0][EDITOR_BOTON_GUARDAR]=BOTON_RESALTADO;
//                    }
//        			else
//        				estados_botones[0][EDITOR_BOTON_GUARDAR]=BOTON_NORMAL;
//
//                    if(player_activo>=0){
//
//                        if(evento->motion.y+10<EjeY||evento->motion.y+10+10>EjeY+Mapa::FILAS*16||evento->motion.x+3<EjeX||evento->motion.x+3 + 10>EjeX+Mapa::COLUMNAS*16){
//                            int x=evento->motion.x,y=evento->motion.y;
//
//                            if(evento->motion.y+10<EjeY){
//                                y=EjeY-10;
//                            }else if(evento->motion.y+21>EjeY+Mapa::FILAS*16){
//                                y=EjeY+Mapa::FILAS*16-21;
//                            }
//
//                            if(evento->motion.x+3<EjeX){
//                                x=EjeX-3;
//                            }else if(evento->motion.x+13>EjeX+Mapa::COLUMNAS*16){
//                                x=EjeX+Mapa::COLUMNAS*16-13;
//                            }
//
//                            //SDL_WarpMouse(x,y);
//                        }
//
//
//                    }
//
//                    if(mantiene_presionado&&tile_activo!=-1)
//                        EditPointMap(evento);
//
//                }else if(evento->type == SDL_MOUSEBUTTONDOWN) {
//                    if(evento->button.button==SDL_BUTTON_LEFT){
//                            for(i=0;i<5;i++)
//                                for(j=0;j<2;j++){
//                                    if(i==0&&j==EDITOR_BOTON_GUARDAR)continue;
//                                	if(punto_en_rect(evento->motion.x,evento->motion.y-yTablero,&rects_botones[i][j])){
//                            			estados_botones[i][j]=BOTON_PRESIONADO;
//                                        game->play(SFX_ESTRANYO);
//                                    }
//                                }
//
//                        	if(punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones[0][EDITOR_BOTON_GUARDAR])){
//                    			estados_botones[0][EDITOR_BOTON_GUARDAR]=BOTON_PRESIONADO;
//                                game->play(SFX_ESTRANYO);
//                            }
//
//
//
//                            if(punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,6,20+yTablero,47,16)){
//                                tile_activo=(evento->motion.x-6)/16;
//                                if(tile_activo==2)tile_activo=3;
//                                player_activo=PLAYER_NONE;
//                                game->play(SFX_CAMPANADA);
//                            }
//                            else
//                                if(EditPointMap(evento))
//                                    mantiene_presionado=1;
//
//
//                        }else if(evento->button.button==SDL_BUTTON_RIGHT) {
//                            for(i=0;i<_PLAYERS;i++)
//                                if(punto_en_rect_coordenadas(evento->motion.x,evento->motion.y,data->getX((IdPlayer)i),data->getY((IdPlayer)i),15,15)){
//                                    player_activo=(IdPlayer)i;
//                                    tile_activo=-1;
//                                    return;
//                                }
//
//                            if(player_activo!=PLAYER_NONE){
//                                data->setX(player_activo,evento->motion.x);
//                                data->setY(player_activo,evento->motion.y);
//                                player_activo=PLAYER_NONE;
//                            }
//                        }
//
//
//            	}
//            	else if(evento->type == SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT) {
//                    mantiene_presionado=false;
//                        for(i=0;i<5;i++)
//                            for(j=0;j<2;j++){
//                            	if(punto_en_rect(evento->motion.x,evento->motion.y-yTablero,&rects_botones[i][j])){
//                                        switch(i){
//                                            case 0:
//                                                if(j==EDITOR_BOTON_FLECHA){
//                                                    if(data->getIdTile() < 5){
//                                                        data->setIdTile(data->getIdTile()+1);
//                                                        if(data->getIdTile()==4){
//                                                            data->setIdTile(0);
//                                                        }
//                                                        leerInfTile();
//                                                    }
//                                                }
//                                                break;
//                                            case EDITOR_MODIF_BOMBA:
//                                                if(j==EDITOR_BOTON_MAS){
//                                                    data->setBombas(data->getBombasDisponibles()+1);
//                                                    if(data->getBombasDisponibles()>MAX_BOMBAS)
//                                                        data->setBombas(MAX_BOMBAS);
//                                                }else{
//                                                    data->setBombas(data->getBombasDisponibles()-1);
//                                                    if(data->getBombasDisponibles()<0)
//                                                        data->setBombas(0);
//                                                }
//
//                                                break;
//                                            case EDITOR_MODIF_EXPLOSION:
//                                                if(j==EDITOR_BOTON_MAS){
//                                                    data->setAlcanceBombas(data->getAlcanceBombas()+1);
//                                                    if(data->getAlcanceBombas()>12)
//                                                        data->setAlcanceBombas(12);
//                                                }else{
//                                                    data->setAlcanceBombas(data->getAlcanceBombas()-1);
//                                                    if(data->getAlcanceBombas()<0)
//                                                        data->setAlcanceBombas(0);
//                                                }
//                                                break;
//                                            case EDITOR_MODIF_VIDAS:
//                                                if(j==EDITOR_BOTON_MAS){
//                                                    data->setVidas(data->getVidas()+1);
//                                                    if(data->getVidas()>5)
//                                                        data->setVidas(5);
//                                                }else{
//                                                    data->setVidas(data->getVidas()-1);
//                                                    if(data->getVidas()<0)
//                                                        data->setVidas(0);
//                                                }
//                                                break;
//                                            case EDITOR_MODIF_ITEMS:
//                                                if(j==EDITOR_BOTON_MAS){
//                                                    data->setNumItems(data->getNumItems()+1);
//                                                    if(data->getNumItems()>30)
//                                                        data->setNumItems(30);
//                                                }else{
//                                                    data->setNumItems(data->getNumItems()-1);
//                                                    if(data->getNumItems()<0)
//                                                        data->setNumItems(0);
//                                                }
//                                                break;
//                                        }
//                            			estados_botones[i][j]=BOTON_NORMAL;
//                                }//fin si punto rect
//                        }//seg for
//                    if(punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones[0][EDITOR_BOTON_GUARDAR])){
//                        guardarMapa();
//                        cambiarVentana(EDITOR_ABRIR_NIVEL);
//                    }
//                }//fin else if
//
//            break;
//
//        case EDITOR_ABRIR_NIVEL:
//                if(evento->type==SDL_KEYDOWN){
//                    switch(evento->key.keysym.sym){
//                            case SDLK_ESCAPE:
//                                game->cambiarInterfaz(new Menu(game));
//                                break;
//                            case SDLK_1:
//                                 if(boton_visible[EDITOR_MAPA_1]){
//                                    if((maxTerrenoBatalla+1)-pagina*2!=-1)
//                                        iniciarEdicion((pagina-1)*2);
//                                    else
//                                        iniciarEdicion(NIVEL_BASE);
//                                 }
//                                break;
//                            case SDLK_2:
//                                 if(boton_visible[EDITOR_MAPA_2]){
//                                    if((maxTerrenoBatalla+1)-pagina*2>0)
//                                        iniciarEdicion((pagina-1)*2+1);
//                                    else
//                                        iniciarEdicion(NIVEL_BASE);
//                                    }
//                                break;
//                            case SDLK_LEFT:
//                                 if(boton_visible[EDITOR_FLECHA_IZQUIERDA])
//                                       cambiarPagina(pagina - 1);
//                                break;
//                            case SDLK_RIGHT:
//                                 if(boton_visible[EDITOR_FLECHA_DERECHA])
//                                       cambiarPagina(pagina + 1);
//                                break;
//                            default:
//                                break;
//                    }
//
//                }else if(evento->type == SDL_MOUSEMOTION){
//                            if(boton_visible[EDITOR_FLECHA_IZQUIERDA])
//                            {
//                                if(punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA]))
//                                    estados_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA]=BOTON_RESALTADO;
//                                else
//                                    estados_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA]=BOTON_NORMAL;
//                            }
//
//                            if(boton_visible[EDITOR_FLECHA_DERECHA])
//                            {
//                                if(punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA]))
//                                    estados_botones_elegir_terreno[EDITOR_FLECHA_DERECHA]=BOTON_RESALTADO;
//                                else
//                                    estados_botones_elegir_terreno[EDITOR_FLECHA_DERECHA]=BOTON_NORMAL;
//                            }
//
//
//
//                }else if(evento->type == SDL_MOUSEBUTTONDOWN&&evento->button.button==SDL_BUTTON_LEFT) {
//                        for(i=0;i<4;i++)
//                            	if(boton_visible[i] && punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones_elegir_terreno[i])){
//                            			estados_botones_elegir_terreno[i]=BOTON_PRESIONADO;
//                                        game->play(SFX_TONO_SECO);
//                                }
//            	}
//            	else if(evento->type == SDL_MOUSEBUTTONUP&&evento->button.button==SDL_BUTTON_LEFT) {
//                        for(i=0;i<4;i++){
//                                if(boton_visible[i] && punto_en_rect(evento->motion.x,evento->motion.y,&rects_botones_elegir_terreno[i])){
//                                    switch(i){
//
//                                        case EDITOR_FLECHA_IZQUIERDA:
//                                            cambiarPagina(pagina - 1);
//                                            break;
//                                        case EDITOR_FLECHA_DERECHA:
//                                            cambiarPagina(pagina + 1);
//                                            break;
//                                        case EDITOR_MAPA_1:
//                                                if((maxTerrenoBatalla+1)-pagina*2!=-1)
//                                                    iniciarEdicion((pagina-1)*2);
//                                                else
//                                                    iniciarEdicion(NIVEL_BASE);
//                                            break;
//                                        case EDITOR_MAPA_2:
//                                                if((maxTerrenoBatalla+1)-pagina*2>0)
//                                                    iniciarEdicion((pagina-1)*2+1);
//                                                else
//                                                    iniciarEdicion(NIVEL_BASE);
//
//                                            break;
//
//                                    }
//                                    estados_botones_elegir_terreno[i]=BOTON_NORMAL;
//                                }
//                            }
//                }
//            break;
//    }
//
//}
//
//void Editor::draw(SDL_Renderer * gRenderer){
//    static int i,j;
//    static char stock[30];
//
//    switch(ventana){
//        case EDICION_NIVEL:
//                game->getImagen((CodeImagen)(idFondo))->render(gRenderer);
//                Mapa::draw(gRenderer,game->getImagen(IMG_TILES),mapa,EjeX,EjeY,data->getIdTile());
//
//                game->getImagen(IMG_TABLERO)->render(gRenderer,0,yTablero);
//
//                for(i=1;i<5;i++){
//                    for(j=0;j<2;j++){
//                        imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_BOTON_MAS +j)),estados_botones[i][j],gRenderer,rects_botones[i][j].x,rects_botones[i][j].y+yTablero,3,1,0);
//                        }
//                    }
//
//
//                game->getImagen(IMG_LLAMA)->render(gRenderer,143,20+yTablero);//explosion
//                game->getImagen(IMG_BOMBA_PEQUE)->render(gRenderer,91,20+yTablero);//bomba
//                game->getImagen(IMG_CORAZON)->render(gRenderer,217,20+yTablero);//vidas
//                game->getImagen(IMG_PREGUNTA)->render(gRenderer,270,21+yTablero);//item
//
//                game->getImagen(IMG_TXT_TILES)->render(gRenderer,6,3+yTablero);
//
//                //dibujamos la cantidad de bombas iniciales
//                sprintf(stock,"x%d",data->getBombasDisponibles());
//                //imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_2),107,21+yTablero,stock,STR_NORMAL);
//
//                //dibujamos el alcance de las bombas iniciales
//                sprintf(stock,"x%d",data->getAlcanceBombas());
//                //imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_2),177,21+yTablero,stock,STR_NORMAL);
//
//                //dibujamos las vidas iniciales
//                sprintf(stock,"x%d",data->getVidas());
//                //imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_2),237,21+yTablero,stock,STR_NORMAL);
//
//                //dibujamos la cantidad de mGrpItems iniciales
//                sprintf(stock,"x%d",data->getNumItems());
//                //imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_2),288,21+yTablero,stock,STR_NORMAL);
//
//                for(int j=0;j<3;j++)
//                    imprimir_desde_grilla(game->getImagen(IMG_TILES),data->getIdTile()*4+((j!=2)?j:Mapa::BLOQUE_PISO),gRenderer,j*16+6,20+yTablero,4,4,0);
//
//                imprimir_desde_grilla(game->getImagen(IMG_BOTON_FLECHA_PEQUE_DERECHA),estados_botones[0][0],gRenderer,rects_botones[0][0].x,rects_botones[0][0].y+yTablero,3,1,0);
//
//                static int x,y;
//                SDL_GetMouseState(&x,&y);
//
//                for(i=0;i<_PLAYERS;i++){
//                    if(i!=player_activo){
//                        imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_PLAYER_1 +i)),6,gRenderer,data->getX((IdPlayer)i),data->getY((IdPlayer)i),1,12,1);
//                    }else{
//                        imprimir_desde_grilla(game->getImagen((CodeImagen)(IMG_PLAYER_1 +i)),6,gRenderer,x,y,1,12,1);
//                    }
//                }
//
//                if(tile_activo>=0&&punto_en_rect_coordenadas(x,y,EjeX,EjeY,272,176)){
//                    static SDL_Rect rect;
//                    rect.x=(x-EjeX)/16*16 + EjeX;
//                    rect.y=(y-EjeY)/16*16 + EjeY;
//                    imprimir_desde_grilla(game->getImagen(IMG_TILES),data->getIdTile()*4+tile_activo,gRenderer,rect.x,rect.y,4,4,1);
//
//                }
//
//                imprimir_desde_grilla(game->getImagen(IMG_BOTON_GUARDAR),estados_botones[0][1],gRenderer,rects_botones[0][1].x,rects_botones[0][1].y,3,1,0);
//                botonBorrar.draw(gRenderer); // TODO ERRADO ARREGLAR
//            break;
//        case EDITOR_ABRIR_NIVEL:
//
//                game->getImagen(IMG_FONDO_EDITOR_SELECT_FILE)->render(gRenderer,0,0);
//
//
//                if(boton_visible[EDITOR_FLECHA_IZQUIERDA])
//                    imprimir_desde_grilla(game->getImagen(IMG_BOTON_FLECHA_GRANDE_IZQUIERDA),estados_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA],gRenderer,rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].x,rects_botones_elegir_terreno[EDITOR_FLECHA_IZQUIERDA].y,3,1,0);
//
//                if(boton_visible[EDITOR_FLECHA_DERECHA])
//                    imprimir_desde_grilla(game->getImagen(IMG_BOTON_FLECHA_GRANDE_DERECHA),estados_botones_elegir_terreno[EDITOR_FLECHA_DERECHA],gRenderer,rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].x,rects_botones_elegir_terreno[EDITOR_FLECHA_DERECHA].y,3,1,0);
//
//
//                imprimir_desde_grilla(game->getImagen(IMG_BOTON_ESTRANIO),(estados_botones_elegir_terreno[EDITOR_MAPA_1]==BOTON_PRESIONADO)?1:0,gRenderer,rects_botones_elegir_terreno[EDITOR_MAPA_1].x,rects_botones_elegir_terreno[EDITOR_MAPA_1].y,2,1,0);
//
//                SDL_Rect rect_dest = {rects_botones_elegir_terreno[EDITOR_MAPA_1].x+7,
//                                      rects_botones_elegir_terreno[EDITOR_MAPA_1].y+5,0,0};
//                SDL_QueryTexture(previews_niveles[(pagina-1)*2],NULL,NULL,&rect_dest.w,&rect_dest.h);
//                SDL_RenderCopy(gRenderer,previews_niveles[(pagina-1)*2],NULL,&rect_dest);
//
//
//                if((maxTerrenoBatalla+1)-pagina*2==-1){
//                    /*imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_5),
//                                    rects_botones_elegir_terreno[EDITOR_MAPA_1].x+2,
//                                    rects_botones_elegir_terreno[EDITOR_MAPA_1].y+50,
//                                    "nuevo",STR_NORMAL);*/
//
//                }
//                if(boton_visible[EDITOR_MAPA_2]){
//                        imprimir_desde_grilla(game->getImagen(IMG_BOTON_ESTRANIO),(estados_botones_elegir_terreno[EDITOR_MAPA_2]==BOTON_PRESIONADO)?1:0,gRenderer,rects_botones_elegir_terreno[EDITOR_MAPA_2].x,rects_botones_elegir_terreno[EDITOR_MAPA_2].y,2,1,0);
//
//                        rect_dest.x = rects_botones_elegir_terreno[EDITOR_MAPA_2].x+7;
//                        rect_dest.y = rects_botones_elegir_terreno[EDITOR_MAPA_2].y+5;
//                        SDL_QueryTexture(previews_niveles[(pagina-1)*2 + 1],NULL,NULL,&rect_dest.w,&rect_dest.h);
//                        SDL_RenderCopy(gRenderer,previews_niveles[(pagina-1)*2 + 1],NULL,&rect_dest);
//
//                        /*if((mMaxTerrenoBatalla+1)-pagina*2<=0)
//                            imprimir_palabra(gRenderer,game->getImagen(IMG_FUENTE_5),
//                                            rects_botones_elegir_terreno[EDITOR_MAPA_2].x+2,
//                                            rects_botones_elegir_terreno[EDITOR_MAPA_2].y+50,
//                                                "nuevo",STR_NORMAL);*/
//                }
//            break;
//    }
//}
//
//Editor::~Editor(){
//    #ifdef DEBUG
//        cout << "Llamando al destructor de Editor: "<<this<<endl;
//    #endif
//     int i;
//     for(i=0;i<=maxTerrenoBatalla;i++){
//        #ifdef DEBUG
//         cout << "Liberando Surface: "<<previews_niveles[i]<<endl;
//        #endif
//         SDL_DestroyTexture(previews_niveles[i]);
//     }
//    #ifdef DEBUG
//     cout << "Liberando Preview: "<<previews_niveles<<endl;
//    #endif
//    delete [] previews_niveles;
//    delete data;
//}
//
//void Editor::crearTexturas(SDL_Renderer * gr) {
//
//}
//
//bool Editor::isPaused() {
//    return false;
//}
//
//void Editor::pause() {
//
//}
//
//void Editor::resume() {
//
//}
