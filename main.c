/* Copyright (C) 2016 Marcelo Serrano Zanetti - All Rights Reserved

 * Licensed under the GNU GPL V3.0 license. All conditions apply.

 * Powered by Allegro: http://liballeg.org/license.html

 */

/// Modifications added to the document are highlighted by line document comments
/// Parts of the original design were highlighted by normal line comments
/// Unused code is highlighted with a line comment and #


/// ADVISE!!

/// If you get an error on codeblocks like: 'for' loop initial declarations are only allowed in C99 or C11 mode
/// 1.Go under settings
/// 2.Compiler settings tab
/// 3.Mark the checkbox of: "Have gcc follow the 1999 ISO C language standard [-std=c99]"

/// ----------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>

#include <stdlib.h>

#include <allegro5/allegro.h>

#include <allegro5/allegro_image.h>

#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_font.h>



//const float FPS = 90;

//const int SCREEN_W = 1024;

//const int SCREEN_H = 768;

//const int BOLA_TAMANHO = 77;

//const int REBATEDOR_LARGURA = 257;

//const int REBATEDOR_ALTURA = 506;

/// DEFINE SCREEN SIZE
#define SCREEN_W  800
#define SCREEN_H  680
/// ----------------------------------------------------------------------------------------------------------------------------------------

/// DEFINE PLAYER SHIP VALUES
#define SHIP_W  40
#define SHIP_H 36
#define SHIP_EDGE_X 12
#define SHIP_EDGE_Y 13
#define SHIP_HEALTH 3
/// ----------------------------------------------------------------------------------------------------------------------------------------

/// DEFINE ENEMY SHIP VALUES
 #define ENEMY_W 40
 #define ENEMY_H 35
 /// ----------------------------------------------------------------------------------------------------------------------------------------

/// DEFINE MAX NUMBER OF ENEMIES
#define MAX_ENEMIES 1
/// ----------------------------------------------------------------------------------------------------------------------------------------

/// TYPEDEF STRUCTURE OF ENEMIES
typedef struct  {
 float x,y;
 bool active;
 int health;
}Enemy;
/// ----------------------------------------------------------------------------------------------------------------------------------------

/// DEFINE MAX NUMBER OF PROJECTILES
#define MAX_PROJECTILES 1
/// ----------------------------------------------------------------------------------------------------------------------------------------

/// TYPEDEF STRUCTURE OF PROJECTILES
typedef struct  {
 float x,y;
 bool active;
}Projectile;
/// ----------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)

{


    ALLEGRO_DISPLAY *display = NULL;

    /// RENAMED "event_queue" to "queue"

    ALLEGRO_EVENT_QUEUE *queue = NULL;

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    ALLEGRO_TIMER *timer = NULL;

    /// SET FONT

    ALLEGRO_FONT *font = NULL;
   /// ----------------------------------------------------------------------------------------------------------------------------------------

    if(!al_init())

    {

        fprintf(stderr, "failed to initialize allegro!\n");

        return -1;

    }
    /// CHECK PRIMITIVES
    if(!al_init_primitives_addon()) {

        fprintf(stderr,"failed to initialize primitives!\n");

    return -1;
    }
    /// ----------------------------------------------------------------------------------------------------------------------------------------


    /// CREATE AND CHECK FONT

   font = al_create_builtin_font();

   if(!font) {
     fprintf(stderr,"failed to initialize fonts!\n");

    return -1;
   }
   /// ----------------------------------------------------------------------------------------------------------------------------------------

    timer = al_create_timer(1.0 / 30.0);

    if(!timer)

    {

        fprintf(stderr, "failed to create timer!\n");

        return -1;

    }



    bool redraw = true;

    /// BOOLEAN OF RUNNING SETUP

    bool done = false;

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// BOOLEAN SET OF ALLEGRO KEYCODES

    bool key[ALLEGRO_KEY_MAX] = {false};

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// DEFINE POSITION VALUE OF PLAYER'S SHIP

    float ship_x = SCREEN_W/2 - SHIP_W/2;
    float ship_y = SCREEN_H/2 - SHIP_H + 100;

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    ///  DEFINE POSITION VALUE OF ENEMY SHIP

    float enemy_ship_x = SCREEN_W/2 - ENEMY_W/2;
    float enemy_ship_y = SCREEN_W/2 - ENEMY_H  - 300;

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// SET ENEMY NUMBER

    Enemy enemies[MAX_ENEMIES];

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// SET PROJECTILES NUMBER

    Projectile projectiles[MAX_PROJECTILES];

    /// ----------------------------------------------------------------------------------------------------------------------------------------

   // al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);

    /// SET ANTIANALISING FOR PRIMITIVES

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

   /// ----------------------------------------------------------------------------------------------------------------------------------------

    display = al_create_display(SCREEN_W, SCREEN_H);

    if(!display)

    {

        fprintf(stderr, "failed to create display!\n");

        al_destroy_timer(timer);

        return -1;

    }

    if(!al_install_keyboard())

    {

        fprintf(stderr, "failed to initialize the keyboard!\n");

        return -1;

    }

    if(!al_install_mouse())

    {

        fprintf(stderr, "failed to initialize the mouse!\n");

        return -1;

    }

    if(!al_init_image_addon())

    {

        fprintf(stderr, "failed to initialize the image addon!\n");

        return -1;

    }

 //   ALLEGRO_BITMAP *bola = NULL;

   // ALLEGRO_BITMAP *rebatedorEsquerda = NULL;

   // ALLEGRO_BITMAP *rebatedorDireita = NULL;

   // ALLEGRO_BITMAP *background = NULL;



   // float bola_pos_x = SCREEN_W / 2.0 - BOLA_TAMANHO / 2.0;

   // float bola_pos_y = SCREEN_H / 2.0 - BOLA_TAMANHO / 2.0;

  //  float bola_vx = -4;

    //float bola_vy = -4;



   // float rebatedorEsquerda_pos_x = 0;

  //  float rebatedorEsquerda_pos_y = SCREEN_H / 2.0 - REBATEDOR_ALTURA / 2.0;

    //float rebatedorEsquerda_vy = 0;



   // float rebatedorDireita_pos_x = SCREEN_W - REBATEDOR_LARGURA;

   // float rebatedorDireita_pos_y = SCREEN_H / 2.0 - REBATEDOR_ALTURA / 2.0;

   // float rebatedorDireita_vy = 0;



  //  int click=0;

   // int savebvx;

   // int savebvy;



//    bola              =  al_load_bitmap("imagens/bola.png");

//    rebatedorEsquerda = al_load_bitmap("imagens/maradona.png");

//    rebatedorDireita  = al_load_bitmap("imagens/pele.png");

//    background        = al_load_bitmap("imagens/campo.png");



//    if(!bola)

 //   {

 //       fprintf(stderr, "falhou ao criar a bola bitmap!\n");

    //    al_destroy_display(display);

   //     al_destroy_timer(timer);

   //     return -1;

   // }

//    if(!rebatedorEsquerda)

 //   {

   //     fprintf(stderr, "falhou ao criar o rebatedoresquerda bitmap!\n");

    //    al_destroy_display(display);

     //   al_destroy_timer(timer);

//        al_destroy_bitmap(bola);

     //   return -1;

  //  }

//    if(!rebatedorDireita)

  //  {

       // fprintf(stderr, "falhou ao criar o rebatedordireita bitmap!\n");

      //  al_destroy_display(display);

       // al_destroy_timer(timer);

     //   al_destroy_bitmap(bola);

     //   al_destroy_bitmap(rebatedorEsquerda);

     //   return -1;

   // }

//    if(!background)

    //{

    //    fprintf(stderr, "falhou ao criar o background bitmap!\n");

    //    al_destroy_display(display);

     //   al_destroy_timer(timer);

//        al_destroy_bitmap(bola);

//        al_destroy_bitmap(rebatedorEsquerda);

//        al_destroy_bitmap(rebatedorDireita);

        //return -1;

   // }



    //al_set_target_bitmap(al_get_backbuffer(display));



    queue = al_create_event_queue();

    if(!queue)

    {

        fprintf(stderr, "failed to create event_queue!\n");

//        al_destroy_bitmap(bola);

//        al_destroy_bitmap(rebatedorEsquerda);

//        al_destroy_bitmap(rebatedorDireita);

//        al_destroy_bitmap(background);

        al_destroy_display(display);

        al_destroy_timer(timer);

        return -1;

    }

    al_register_event_source(queue, al_get_display_event_source(display));

    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_register_event_source(queue, al_get_keyboard_event_source());

    al_register_event_source(queue, al_get_mouse_event_source());



    al_clear_to_color(al_map_rgb(0,0,0));



    al_flip_display();






   /// FOR LOOP TO SET PŔOJECTILES FALSE
   for ( int i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].active = false;
    }
   /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// FOR LOOP TO SET ENEMIES FALSE
   for ( int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
    }
   /// ----------------------------------------------------------------------------------------------------------------------------------------



    al_start_timer(timer);

    while(1)

    {

    /// RENAMED "ALLEGRO_EVENT ev;" to "ALLEGRO_EVENT event; "
        ALLEGRO_EVENT event;
    /// ----------------------------------------------------------------------------------------------------------------------------------------

    al_wait_for_event(queue, &event);


   /// NEW MOVEMENT CODE USED FOR PRIMITIVES
    switch(event.type)
    {

    case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = true;
            break;

    case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] = false;
            break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;

    case ALLEGRO_EVENT_TIMER:
      if(key[ALLEGRO_KEY_UP] && ship_y> 0)
          ship_y-= 8;
      if(key[ALLEGRO_KEY_DOWN] && ship_y < SCREEN_W - SHIP_H)
          ship_y+= 8;
      if(key[ALLEGRO_KEY_LEFT] && ship_x > 0)
          ship_x-= 8;
      if(key[ALLEGRO_KEY_RIGHT] && ship_x < SCREEN_H - SHIP_W)
          ship_x+= 8;

      /// ----------------------------------------------------------------------------------------------------------------------------------------

      /// FIRE PROJECTILE
      if(key[ALLEGRO_KEY_SPACE]) {   /// makes a condition to only activate projectiles if a key is pressed
      for( int i = 0; i < MAX_PROJECTILES; i++) {
        if (!projectiles[i].active) {
                        projectiles[i].x = ship_x + SHIP_W / 2;
                        projectiles[i].y = ship_y;
                        projectiles[i].active = true;
                        break;
        }
      }

      }


      /// ----------------------------------------------------------------------------------------------------------------------------------------

      /// SPAWN ENEMIES

       for( int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
                        enemies[i].x = enemy_ship_x;
                        enemies[i].y = enemy_ship_y;
                        enemies[i].active = true;
                        break;
        }
      }

      /// MOVE PROJECTILES UP AND DELETE
      for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) {
           projectiles[i].y -= 20; /// move up at some velocity y  -= n when spawn on screen
        if (projectiles[i].y < 0) {
            projectiles[i].active = false;
        }
    }
}

    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// MOVE ENEMIES DOWN AND DELETE
      for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
           enemies[i].y += 1; /// move down at some velocity y += n when spawn on screen
        if (enemies[i].y < 0) {
            enemies[i].active = false;
        }
    }
}
    /// ----------------------------------------------------------------------------------------------------------------------------------------


    /// IF KEY IS PRESSED GAME ENDS

      if(key[ALLEGRO_KEY_ESCAPE])
          done = true;
    /// ----------------------------------------------------------------------------------------------------------------------------------------

       redraw = true;
       break;





}




    if(done)
        break;
      //  if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)

      //  {

          //  switch(ev.mouse.button)

           // {

          //  case 1:

             //   printf("x:%d y:%d\n",ev.mouse.x, ev.mouse.y);

             //   if(click==0)

              //  {

//                    savebvx=bola_vx;

//                    savebvy=bola_vy;

//                    bola_vx=0;

//                    bola_vy=0;

                  //  click=1;

             //   }

               // else

              //  {

//                    bola_vx=savebvx;

//                    bola_vy=savebvy;

                 //   click=0;

              //  }

              //  break;

           // }

       // }

//        else if(ev.type == ALLEGRO_EVENT_TIMER)

     //   {

//            if(bola_pos_y < 0 || bola_pos_y > SCREEN_H - BOLA_TAMANHO)

   //         {

     //           bola_vy = -bola_vy;

      //      }



//            if(bola_pos_x < 0 || bola_pos_x > SCREEN_W - BOLA_TAMANHO)

 //           {

  //              bola_pos_x = SCREEN_W / 2.0 - BOLA_TAMANHO / 2.0;

     //           bola_pos_y = SCREEN_H / 2.0 - BOLA_TAMANHO / 2.0;

       //         bola_vx = -4, bola_vy = -4;

       //     }



      //      if(bola_pos_x <= rebatedorEsquerda_pos_x + REBATEDOR_LARGURA)

        //        if(bola_pos_y+BOLA_TAMANHO>=rebatedorEsquerda_pos_y)

         //           if(bola_pos_y-BOLA_TAMANHO<=rebatedorEsquerda_pos_y+REBATEDOR_ALTURA)

          //              bola_vx = -bola_vx;



          //  if(bola_pos_x + BOLA_TAMANHO >= rebatedorDireita_pos_x )

            //    if(bola_pos_y+BOLA_TAMANHO>=rebatedorDireita_pos_y)

             //       if(bola_pos_y-BOLA_TAMANHO<=rebatedorDireita_pos_y+REBATEDOR_ALTURA)

              //          bola_vx = -bola_vx;



           // bola_pos_x              += bola_vx;

//            bola_pos_y              += bola_vy;

//            rebatedorEsquerda_pos_y += rebatedorEsquerda_vy;

//            rebatedorDireita_pos_y  += rebatedorDireita_vy;

        //    redraw = true;

       // }

     //   else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)

     //   {

    //        switch(ev.keyboard.keycode)

      //      {

   //         case ALLEGRO_KEY_UP:

//                rebatedorDireita_vy=-4;

      //          break;



       //     case ALLEGRO_KEY_DOWN:

//                rebatedorDireita_vy=4;

         //       break;


          //  case ALLEGRO_KEY_W:

//                rebatedorEsquerda_vy=-4;

              //  break;

           // case ALLEGRO_KEY_S:

//                rebatedorEsquerda_vy=4;

            //    break;





           // case ALLEGRO_KEY_ESCAPE:

             //   return 0;

              //  break;

          //  }

       // }

     //   else if(ev.type == ALLEGRO_EVENT_KEY_UP)

     //   {

       //     switch(ev.keyboard.keycode)

      //      {

         //   case ALLEGRO_KEY_UP:

         //   case ALLEGRO_KEY_DOWN:

//                rebatedorDireita_vy=0;

            //    break;



            //case ALLEGRO_KEY_W:

            //case ALLEGRO_KEY_S:

//                rebatedorEsquerda_vy=0;

             //   break;

        //    }

       // }

       // else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

      //  {

        //    break;







        if(redraw && al_is_event_queue_empty(queue))

        {




            al_clear_to_color(al_map_rgb(0,0,0));


            /// DRAW PLAYER'S SHIP
            al_draw_filled_triangle(
            ship_x, ship_y + SHIP_H,                         /// left base
            ship_x + SHIP_W, ship_y + SHIP_H,                /// right base
            ship_x + SHIP_W / 2, ship_y,                     /// top (tip of triangle)
            al_map_rgb(0, 255, 0));




            /// ----------------------------------------------------------------------------------------------------------------------------------------

            /// DRAW ENEMIES
           for (int i = 0; i < MAX_ENEMIES; i++) {
                if(enemies[i].active){
                  al_draw_filled_triangle(enemies[i].x, enemies[i].y + 30,
                                          enemies[i].x - 20, enemies[i].y,
                                          enemies[i].x + 20, enemies[i].y,
                                           al_map_rgb(255,0,0));
              }
           }
           // al_draw_filled_triangle(enemy_ship_x, enemy_ship_y + ENEMY_H,
          //                           enemy_ship_x + ENEMY_W,
           //                          enemy_ship_y + ENEMY_H,
            //                         enemy_ship_x + ENEMY_W/2, enemy_ship_y + 70, al_map_rgb(0,255,0));

            /// ----------------------------------------------------------------------------------------------------------------------------------------





            /// Draw projectiles
            for ( int i = 0; i < MAX_PROJECTILES; i++) {
                if (projectiles[i].active) {
                    al_draw_filled_rectangle(projectiles[i].x - 2, projectiles[i].y - 10,
                                             projectiles[i].x + 2, projectiles[i].y,
                                             al_map_rgb(255, 255, 0));
                }
            }
            ///----------------------------------------------------------------------------------------------------------------------------------------

//            al_draw_bitmap(background, 0, 0, 0);

//            al_draw_bitmap(rebatedorEsquerda,rebatedorEsquerda_pos_x, rebatedorEsquerda_pos_y, 0);

//            al_draw_bitmap(rebatedorDireita,rebatedorDireita_pos_x, rebatedorDireita_pos_y, 0);

          //  al_draw_bitmap(bola, bola_pos_x, bola_pos_y, 0);


            al_flip_display();

            redraw = false;

        }

    }

     /// INFORMATIONS

    printf("POSICAO X DA NAVE: %.1f\n",ship_x);
    printf("POSICAO Y DA NAVE: %.1f\n",ship_y);




    /// ----------------------------------------------------------------------------------------------------------------------------------------

    /// UNUSED CODE

      // # /// DEFINING POSITION OF THE PRIMITIVE
   // #  float x,y;
   // #  x = 100;
   // #  y = 100;
   //   /// ----------------------------------------------------------------------------------------------------------------------------------------

   // # /// DEFINING KEY STATE WHILE NOT PRESSED AND NUMBERS OF KEYCODES SET IN THE ARRAY "key"

  //  #define KEY_SEEN     1
   // #define KEY_DOWN    2

  // #  unsigned char key[ALLEGRO_KEY_MAX];
  // #  memset(key, 0, sizeof(key));
 //  /// ----------------------------------------------------------------------------------------------------------------------------------------

         // # int i;
     // # for( i = 0; i < ALLEGRO_KEY_MAX; i++)
      //            key[i] &= ~KEY_SEEN;


     // # /// VERTEX GRAPHIC
            //ALLEGRO_VERTEX v[] = {
             //   { .x = 210, .y = 320, .z = 0, .color = al_map_rgb_f(1, 0, 0) },
              //  { .x = 330, .y = 320, .z = 0, .color = al_map_rgb_f(0, 1, 0) },
               // { .x = 210, .y = 420, .z = 0, .color = al_map_rgb_f(0, 0, 1) },
                //{ .x = 330, .y = 420, .z = 0, .color = al_map_rgb_f(1, 1, 0) },
            //};
           // /// ----------------------------------------------------------------------------------------------------------------------------------------


     // # al_draw_filled_circle(35,250,5, al_map_rgb_f(0,1,0));
            // # al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f  Y: %.1f ", x, y);

    // #  ///  VERTEX CALL
            //al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);
          //  /// ----------------------------------------------------------------------------------------------------------------------------------------

          //   # printf("POSICAO X DO INIMIGO: %.1f\n",enemy_ship_x);
//  #  printf("POSICAO Y DO INIMIGO: %.1f\n",enemy_ship_y);

    /// ----------------------------------------------------------------------------------------------------------------------------------------

//    al_destroy_bitmap(bola);

//    al_destroy_bitmap(rebatedorEsquerda);

//    al_destroy_bitmap(rebatedorDireita);

    al_destroy_font(font);

    al_destroy_timer(timer);

    al_destroy_display(display);

    al_destroy_event_queue(queue);



    return 0;

}


