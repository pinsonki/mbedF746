#include <mbed.h>
#include <threadLvgl.h>

#include "demos/lv_demos.h"
#include <cstdio>

ThreadLvgl threadLvgl(30);

int main() {

    threadLvgl.lock();

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    static lv_grad_dsc_t grad;
    grad.dir = LV_GRAD_DIR_VER;
    grad.stops_count = 2;
    grad.stops[0].color = lv_palette_lighten(LV_PALETTE_GREY, 1);
    grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);

    /*Shift the gradient to the bottom*/
    grad.stops[0].frac  = 128;
    grad.stops[1].frac  = 192;

    lv_style_set_bg_grad(&style, &grad);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
    lv_obj_set_size(obj, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    
    /// Création du menu pour permettre à l'utilisateur de changer de page
    /*Create a menu object*/
    lv_obj_t * menu = lv_menu_create(lv_scr_act());
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    lv_obj_t * cont;
    lv_obj_t * label;

    /*Create a sub page*/
    lv_obj_t * sub_page = lv_menu_page_create(menu, NULL);
    lv_obj_t * page_regle = lv_menu_page_create(menu, NULL);
    lv_obj_t * page_dessin = lv_menu_page_create(menu, NULL);
    lv_obj_t * page_affiche = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(sub_page);
    cont = lv_menu_cont_create(page_regle);
    cont = lv_menu_cont_create(page_dessin);
    cont = lv_menu_cont_create(page_affiche);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here");

    /*Create a main page*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Regles d'utilisation du capteur de mouvement");
    lv_menu_set_load_page_event(menu, cont, page_regle);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Suivre les dessins");
    lv_menu_set_load_page_event(menu, cont, page_dessin);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Afficher des dessins");
    lv_menu_set_load_page_event(menu, cont, page_affiche);

    lv_menu_set_page(menu, main_page);

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}