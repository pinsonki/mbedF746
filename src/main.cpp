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

    /*Mise en place du fond d'écran*/
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    static lv_grad_dsc_t grad;
    grad.dir = LV_GRAD_DIR_VER;
    grad.stops_count = 2;
    grad.stops[0].color = lv_palette_lighten(LV_PALETTE_GREY, 1);
    grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);

    /*Mise en place du dégradé*/
    grad.stops[0].frac  = 128;
    grad.stops[1].frac  = 192;

    lv_style_set_bg_grad(&style, &grad);

    /*Création de l'objet pour le fond d'écran*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
    lv_obj_set_size(obj, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));

    /*Créaation du menu*/
    lv_obj_t * menu = lv_menu_create(lv_scr_act());
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_width(menu, 370);
    lv_obj_set_height(menu, 118);
    lv_obj_center(menu);

    /*Modification de l'en-tête*/
    lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_t * back_btn_label = lv_label_create(back_btn);
    lv_label_set_text(back_btn_label, "Back");

    lv_obj_t * cont;
    lv_obj_t * label;

    /*Création des sous-pages*/
    lv_obj_t * sub_1_page = lv_menu_page_create(menu, "Regles d'utilisation du capteur de mouvement");

    cont = lv_menu_cont_create(sub_1_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Regles d'utilisation du capteur de mouvement");

    lv_obj_t * sub_2_page = lv_menu_page_create(menu, "Suivre les dessins");

    cont = lv_menu_cont_create(sub_2_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Suivre les dessins");

    lv_obj_t * sub_3_page = lv_menu_page_create(menu, "Afficher des dessins");

    cont = lv_menu_cont_create(sub_3_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Afficher des dessins");

    /*Mise en place de la page principale*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Regles d'utilisation du capteur de mouvement");
    lv_menu_set_load_page_event(menu, cont, sub_1_page);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Suivre les dessins");
    lv_menu_set_load_page_event(menu, cont, sub_2_page);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Afficher des dessins");
    lv_menu_set_load_page_event(menu, cont, sub_3_page);

    lv_menu_set_page(menu, main_page);

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
 }