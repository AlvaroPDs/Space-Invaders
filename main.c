/* Copyright (C) 2025 Alvaro Palma Da Silva - All Rights Reserved

 * Licensed under the GNU GPL V3.0 license. All conditions apply.

 * Powered by Allegro: http://liballeg.org/license.html

 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


 const float FPS = 90;
 const int SCREEN_W = 1024;
 const int SCREEN_H = 720;

 int main(int argc, char **argv)
 {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    //ALLEGRO_TIMER *timer = NULL;

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;

    }
    //timer = al_create_timer(1.0/FPS);
    //if(!timer)
    //{
    //    printf(stderr,("failed to create timer!\n"))
    //}
    bool redraw = true;

    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr,"failed to create display!\n");
        //al_destroy_timer(timer);
        return -1;
    }

return 0;

 }
