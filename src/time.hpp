#ifndef TIME_CONTROLLER_HPP
#define TIME_CONTROLLER_HPP
#include <ctime>

class TimeController{
    private:
        int tick_inicial;
        int tick_actual;
        int ticks_perdidos;
    public:
        TimeController(int t_inicial=time(0)){
             tick_inicial=t_inicial;
             tick_actual=0;
             ticks_perdidos=0;
        };
        int getTickInicial(){
            return tick_inicial;
        };
        
        int getTickPerdidos(){
            return ticks_perdidos;
        };
        
        int getMiliSegundos(){
            return tick_actual;
        };
        void update(){
            tick_actual=time(0)-tick_inicial-ticks_perdidos;
        };

        void setTicksPerdidos(int nuevo){ticks_perdidos=nuevo;};
};

#endif
