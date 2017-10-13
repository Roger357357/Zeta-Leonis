#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>

const int LARGURA_TELA = 929;
const int ALTURA_TELA = 720;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_SAMPLE *musica_capa = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *imagem = NULL;
ALLEGRO_BITMAP *bexit = NULL;
ALLEGRO_BITMAP *bsettings = NULL;
ALLEGRO_BITMAP *bplay = NULL;
ALLEGRO_SAMPLE_ID *id_music = NULL;


bool inicializar();

int main(void)
{
    // Flag que condicionará nosso looping
    int sair = 0;
    bool saire = false;

    if (!inicializar())
    {
        return -1;
    }


    al_set_sample_instance_playing(musica_capa, true);
    al_init_image_addon();
    al_init_primitives_addon();
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_install_keyboard();

    imagem = al_load_bitmap("capa.jpg");
    bexit = al_load_bitmap("exit.png");
    bsettings = al_load_bitmap("Settings.png");
    bplay = al_load_bitmap("Play1.png");

    // Desenha a imagem na tela
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_bitmap(bexit, 602, 507, 0);
    al_draw_bitmap(bsettings, 330, 509, 0);
    al_draw_bitmap(bplay, 45, 510, 0);

    // Atualiza a tela
    al_flip_display();

    while (!saire)
    {
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_SPACE:
                      imagem = al_load_bitmap("capa.jpg");
                      al_draw_bitmap(imagem, 0, 0, 0);
                      al_flip_display();
                    //al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                saire = true;
            }
            // Se o evento foi de movimentação do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bexit) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bexit) - 50)
                {
                      bexit = al_load_bitmap("exit maior.png");
                      al_draw_bitmap(bexit, 602, 507, 0);

                }
                else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bsettings) - 280 &&
                    evento.mouse.x <= LARGURA_TELA - 400 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bsettings) - 50)
                {
                      bsettings = al_load_bitmap("Settings maior.png");
                      al_draw_bitmap(bsettings, 330, 509, 0);

                }
                else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bplay) - 530 &&
                    evento.mouse.x <= LARGURA_TELA - 700 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bplay) - 50)
                {
                      bplay = al_load_bitmap("Play1.png");
                      al_draw_bitmap(bplay, 45, 510, 0);
                }
                else
                {
                      bplay = al_load_bitmap("Play1.png");
                      bsettings = al_load_bitmap("Settings.png");
                      bexit = al_load_bitmap("exit.png");
                }

            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bexit) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bexit) - 50)
                {
                    saire = true;
                }
                else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bsettings) - 280 &&
                    evento.mouse.x <= LARGURA_TELA - 400 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bsettings) - 50)
                {
                      imagem = al_load_bitmap("universo.jpg");
                      al_draw_bitmap(imagem, 0, 0, 0);
                      al_flip_display();
                }
                else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(bplay) - 530 &&
                    evento.mouse.x <= LARGURA_TELA - 700 && evento.mouse.y <= ALTURA_TELA - 50 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(bplay) - 50)
                {
                    imagem = al_load_bitmap("capa Save-cortada.jpg");
                      al_draw_bitmap(imagem, 0, 0, 0);
                      al_flip_display();
                }
            }
        }
                       // Atualiza a tela
                          al_flip_display();
    }

    al_destroy_bitmap(imagem);
    al_destroy_bitmap(bexit);
    al_destroy_bitmap(bsettings);
    al_destroy_bitmap(bplay);
    al_destroy_sample(musica_capa);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);

    return 0;
}

bool inicializar()
{

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }

    if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        return false;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        return false;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        return false;
    }
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar teclado.\n");
        return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar a janela.\n");
        return false;
    }
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        al_destroy_sample(sample);
        return false;
    }
    al_set_window_title(janela, "Testando sons");

    id_music = malloc(sizeof(ALLEGRO_SAMPLE_ID));
    musica_capa = al_load_sample("04.wav");
    al_play_sample(musica_capa, 0.6, 0.3, 1, ALLEGRO_PLAYMODE_LOOP, id_music);
    if (!musica_capa)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        al_destroy_sample(sample);
        return false;
    }
    // Configura o título da janela
    al_set_window_title(janela, "Rotinas de Mouse - www.rafaeltoledo.net");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}

