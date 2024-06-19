#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>

#define TILE_SIZE 32

struct game_map_t {
    int width, height;
    std::vector<int> map;
    int get(int x, int y) const  {
        if (x < 0) return 7;
        if (x >= width) return 7;
        if (y < 0) return 7;
        if (y >= height) return 7;
        return map[y*width+x];
    }
};

game_map_t game_map = {
        40, 24, {
            7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,3,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,2,7,
            7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,
            7,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0,7,7,7,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,7,7,7,4,5,5,5,5,6,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,1,0,0,7,
            7,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,4,5,6,7,7,
            7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,7,7,4,5,6,7,7,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
            7,0,1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,
            7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
            7,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,10,
            7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
        }
};

std::shared_ptr<SDL_Texture> load_image(SDL_Renderer *renderer, const std::string &file_name) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(file_name.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,0, 255, 255));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return {texture, [](SDL_Texture *t) {
        SDL_DestroyTexture(t);
    }};
}

union vect_t {
    struct { double x; double y;} v;
    double p[2];
};

vect_t operator+(const vect_t a, const vect_t b) {
    vect_t ret = a;
    ret.v.x += b.v.x;
    ret.v.y += b.v.y;
    return ret;
}
vect_t operator*(const vect_t a, const double b) {
    vect_t ret = a;
    ret.v.x *= b;
    ret.v.y *= b;
    return ret;
}

bool is_collision = false;
double scores = 0;
bool LEFT = false;
bool RIGHT = false;
bool UP = false;

struct player_t {
    vect_t p; ///< position
    vect_t v; ///< velocity
    vect_t a; ///< acceleration
};



bool is_in_collision(vect_t pos, const game_map_t &map) {
    return map.get((int)pos.v.x, (int)pos.v.y) >3 && map.get((int)pos.v.x, (int)pos.v.y) <10;
}

bool is_on_the_ground(player_t player, game_map_t &map) {
    return ((map.get(player.p.v.x, player.p.v.y+0.01) >3) || (map.get(player.p.v.x-0.5, player.p.v.y+0.01) >3) || (map.get(player.p.v.x+0.5, player.p.v.y+0.01) >3));
}

bool get_gold(player_t player, game_map_t &map){
    bool success = (map.get(player.p.v.x, player.p.v.y) <=3) && (map.get(player.p.v.x, player.p.v.y) >0) && is_on_the_ground(player, map);
    if (success) {
            int kam = map.get(player.p.v.x, player.p.v.y);
        map.map[(player.p.v.y-1)*map.width+player.p.v.x] = 0;
        if (map.get(player.p.v.x, player.p.v.y) == 0){
            scores = scores+kam;
        }
    }
    return success;
}

player_t update_player(player_t player_old, game_map_t &map, double dt) {
    player_t player = player_old;

    if (!is_on_the_ground (player_old, map)) player_old.a.v.y = 10;

    player.p = player_old.p + (player_old.v * dt) + (player_old.a*dt*dt)*0.5;
    player.v = player_old.v + (player_old.a * dt);
    player.v =  player.v * 0.99;

    std::vector<vect_t> collision_points = {
            {{-0.49,0.0}},
            {{0.49,0.0}},
            {{-0.5,-0.1}},
            {{0.5,-0.1}},
            {{-0.5,-0.9}},
            {{0.5,-0.9}},
            {{-0.5,-1.1}},
            {{0.5,-1.1}},
            {{-0.5,-1.9}},
            {{0.5,-1.9}},
            {{-0.49,-1.9}},
            {{0.49,-1.9}}

    };
    std::vector<vect_t> collision_mods = {
            {{0.0,-1.0}},
            {{0.0,-1.0}},
            {{0.01,0.0}},
            {{-0.01,0.0}},
            {{0.01,0.0}},
            {{-0.01,0.0}},
            {{0.01,0.0}},
            {{-0.01,0.0}},
            {{0.01,0.0}},
            {{-0.01,0.0}},
            {{-0.1,1.0}},
            {{0.1,1.0}}
    };

    for (int i = 0; i < collision_points.size(); i++) {
        auto test_point = player.p + collision_points[i];

        if (is_in_collision(test_point, map)) {
            is_collision = true;
            if(collision_mods[i].v.y < 0) {
                player.v.v.y = 0;
                player.a.v.y = 0;
                player.p.v.y = player_old.p.v.y;
            }
        if(collision_mods[i].v.y > 0) {
                player.v.v.y = 0;
                player.p.v.y = player_old.p.v.y;
            }
        if(collision_mods[i].v.y == 0) {
                player.v.v.x = collision_mods[i].v.x;
                player.p.v.x = player_old.p.v.x;
            }
        }
    }

    return player;
}

void draw_map(SDL_Renderer *renderer, game_map_t & map, std::shared_ptr<SDL_Texture> tex) {
    for (int y = 0; y < map.height; y++)
        for (int x = 0; x < map.width; x++) {
            SDL_Rect dst = {x * TILE_SIZE, y*TILE_SIZE, TILE_SIZE*2,TILE_SIZE*2};
            if (map.get(x,y) > 0) {
                SDL_Rect src = {128*(map.get(x,y) - 1), 0, TILE_SIZE*4-1,TILE_SIZE*4};
                SDL_RenderCopy(renderer, tex.get(), &src, &dst);
            }
        }
}



int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using namespace  std;
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool still_playing = true;

    SDL_Init(SDL_INIT_TIMER);

    SDL_AudioDeviceID dev;
    SDL_AudioDeviceID devm;
    SDL_AudioSpec specs = {};

    specs.freq= 48000;
    specs.format = AUDIO_S32;
    specs.channels = 2;
    specs.samples=4096;

    SDL_Init(SDL_INIT_AUDIO);

    Uint32 wav_lenght = 2000;
    Uint32 music_lenght = 50000;
    Uint8 *wav_buffer;
    Uint8 *music_buffer;

    if (SDL_LoadWAV("8-bit-jump-001-171817.wav", &specs, &wav_buffer, &wav_lenght) == NULL){
        printf("ERROR 1");
    }
    SDL_ClearQueuedAudio(dev);
    if (SDL_LoadWAV("SLOWER-TEMPO2019-12-11_-_Retro_Platforming_-_David_Fesliyan.wav", &specs, &music_buffer, &music_lenght) == NULL){
        printf("ERROR 2");
    }

    dev = SDL_OpenAudioDevice(nullptr, 0, &specs, nullptr, 0);
    devm = SDL_OpenAudioDevice(nullptr, 0, &specs, nullptr, 0);

    if(devm != 0) {
            int i = 0;
            while (still_playing && i<2){
            SDL_QueueAudio(devm, music_buffer, music_lenght);
            SDL_PauseAudioDevice(devm, 1);
            i++;
            }
    }

        if(dev != 0) {
            SDL_QueueAudio(dev, wav_buffer, wav_lenght);
            SDL_PauseAudioDevice(dev, 1);
    }

    double dt = 1./60.;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(1280, 800, 0, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    char* title = "G O L D   M I N E";
    SDL_SetWindowTitle(window, title);

    auto playerP = load_image(renderer, "player.bmp");
    auto background_texture = load_image(renderer, "background.bmp");
    auto background1_texture = load_image(renderer, "background1.bmp");
    auto playerL = load_image(renderer, "playerL.bmp");
    auto playerR = load_image(renderer, "playerR.bmp");
    auto playerUP = load_image(renderer, "playerUP.bmp");
    auto player_texture = playerP;
    auto tiles_texture = load_image(renderer, "tiles.bmp");
    auto end_texture = load_image(renderer, "koniec.bmp");
    auto scores_texture = load_image(renderer, "scores.bmp");
    auto start_texture = load_image(renderer, "start.bmp");
    auto minut1_texture = load_image(renderer, "minut1.bmp");
    auto help_texture = load_image(renderer, "help.bmp");
    auto pauza_texture = load_image(renderer, "pauza.bmp");
    auto scoresN_texture = load_image(renderer, "scores_number.bmp");
    auto time_texture = load_image(renderer, "time.bmp");
    auto gold_texture = load_image(renderer, "gold.bmp");


    player_t player;
    player.p.v.x = 20.5;
    player.p.v.y = 22.9;
    player.a.v.x = 0;
    player.a.v.y = 0;
    player.v.v.x = 0;
    player.v.v.y = 0;

    //ekran startowy
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background1_texture.get(), NULL, NULL);
    SDL_Rect texrh;
    texrh.x = 490; texrh.y = 240; texrh.w = 250; texrh.h = 150;
    SDL_RenderCopy(renderer, start_texture.get(), NULL, &texrh);
    SDL_RenderPresent(renderer);

    bool key = false;
    while (!key) {
        SDL_Event event1;
        while (SDL_PollEvent(&event1) && event1.type == SDL_KEYDOWN)
        {
            if (event1.key.keysym.scancode == SDL_SCANCODE_RETURN){
                key = true;
                still_playing = true;
            }
        if (event1.key.keysym.scancode == SDL_SCANCODE_Q){
            key = true;
            still_playing = false;
            }
        }
    }

    SDL_PauseAudioDevice(devm, 0);

    double game_time = 0.;
    steady_clock::time_point current_time = steady_clock::now();
    while (still_playing) {
        // events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    still_playing = false;
                break;
                case SDL_KEYDOWN:
                    if (is_on_the_ground(player, game_map)) {
                        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                                        player.a.v.y = -700;
                                        if(!UP){
                                            SDL_ClearQueuedAudio(dev);
                                            SDL_LoadWAV("8-bit-jump-001-171817.wav", &specs, &wav_buffer, &wav_lenght);
                                            SDL_QueueAudio(dev, wav_buffer, wav_lenght);
                                            SDL_PauseAudioDevice(dev, 0);
                                            UP = true;
                                }
                                UP = false;
                                RIGHT = false;
                                LEFT = false;
                        }
                        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                                player.a.v.x = -5;
                                RIGHT = false;
                                LEFT = true;
                                UP = false;
                        }
                        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                                player.a.v.x = 5;
                                RIGHT = true;
                                LEFT = false;
                                UP = false;
                        }
                    }else{
                    if(is_in_collision(player.p, game_map) || is_collision){
                        player.a.v.y=0;
                        player.a.v.x=0;
                        is_collision=true;
                        }
                    }
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        double game_time_old = game_time;
                        SDL_PauseAudioDevice(devm, 1);
                        SDL_PauseAudioDevice(dev, 1);
                        player_t player_old = player;
                        player.v.v.x = 0;
                        player.v.v.y = 0;
                        player.a.v.x = 0;
                        player.a.v.y = 0;
                        SDL_Rect texr;
                        texr.x = 500; texr.y = 160; texr.w = 172; texr.h = 111;
                        SDL_RenderCopy(renderer, pauza_texture.get(), NULL, &texr);
                        SDL_RenderPresent(renderer);
                        SDL_Event event1;
                        bool key = false;
                        while (!key){
                            SDL_Delay(10);
                            key = SDL_PollEvent(&event1) && event1.type == SDL_KEYDOWN && event1.key.keysym.scancode == SDL_SCANCODE_SPACE;
                        }
                        if (is_on_the_ground(player, game_map)){
                            if (player_old.a.v.x > 0) player.a.v.x = 5;
                            if (player_old.a.v.x < 0) player.a.v.x = -5;
                        }else{player.a.v.y = 10;}
                        SDL_QueueAudio(dev, wav_buffer, wav_lenght);
                        SDL_PauseAudioDevice(devm, 0);
                        game_time = game_time_old;
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_Q) still_playing = false;
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) player.a.v.y = 0;
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) player.a.v.x = 0;
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)player.a.v.x = 0;
                    break;
            }
            }
            if (SDL_GetQueuedAudioSize(devm) < 10){
                still_playing = false;
                SDL_QueueAudio(dev, wav_buffer, wav_lenght);
                SDL_PauseAudioDevice(dev, 1);
            }




        // physics

        game_time += dt;

        player = update_player(player, game_map, dt);

        if(~is_on_the_ground(player, game_map) && abs(player.v.v.x)<0.001) {player_texture = playerUP;}
        if(is_on_the_ground(player, game_map)){
            if(abs(player.v.v.x)<0.01 && abs(player.v.v.y)<0.01){
                player_texture = playerP;
            }else{
                if(RIGHT && abs(player.v.v.y)<0.01){player_texture = playerR;}
            if(LEFT && abs(player.v.v.y)<0.01){player_texture = playerL;}
            }
        }

        int score_old = scores;
        if (get_gold(player, game_map)){
            if(scores != score_old){
                SDL_ClearQueuedAudio(dev);
                SDL_LoadWAV("coin-pickup-98269.wav", &specs, &wav_buffer, &wav_lenght);
                SDL_QueueAudio(dev, wav_buffer, wav_lenght);
                SDL_PauseAudioDevice(dev, 0);
            }
        }

        int t = int(game_time*100000);

        // graphics
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture.get(), NULL, NULL);

        draw_map(renderer, game_map, tiles_texture);

        SDL_Rect player_rect = {(int)(player.p.v.x*TILE_SIZE-(TILE_SIZE/2)),(int)(player.p.v.y*TILE_SIZE-TILE_SIZE),32, 64};
        {
            int r = 0, g = 0, b = 0;
            if (is_on_the_ground(player, game_map)) {
                g = 255, r = 0;
            }
            if (is_in_collision(player.p, game_map) || is_collision == true) {
                r = 255, g = 0;
                is_collision = false;
            }
            SDL_SetRenderDrawColor(renderer, r,g,b, 0xFF);
        }
        //SDL_RenderDrawRect(renderer,  &player_rect);
        SDL_RenderCopyEx(renderer, player_texture.get(), NULL, &player_rect,0, NULL, SDL_FLIP_NONE);

        SDL_Rect scores_rect = {250, 0, 256, 30};
        SDL_SetRenderDrawColor(renderer, 255,255,255,0xFF);
        SDL_RenderDrawRect(renderer, &scores_rect);
        SDL_RenderFillRect(renderer, &scores_rect);
        SDL_Rect texrs;
        texrs.x = 280; texrs.y = 3; texrs.w = 176; texrs.h = 26;
        SDL_RenderCopy(renderer, scores_texture.get(), NULL, &texrs);
        if(scores > 0){
            texrs.x = 416; texrs.y = 0; texrs.w = 62; texrs.h = 30;
            SDL_Rect src = {62*(scores-1), 0, 62, 30};
            SDL_RenderCopy(renderer, scoresN_texture.get(), &src, &texrs);
        }

        SDL_Rect timer_rect = {700, 0, 300, 30};
        SDL_RenderDrawRect(renderer, &timer_rect);
        SDL_RenderFillRect(renderer, &timer_rect);
        texrs.x = 700; texrs.y=0; texrs.w=300; texrs.h=27;
        t = int(game_time*100000)/100000;
        if (t <= 240) {SDL_RenderCopy(renderer, help_texture.get(), NULL, &texrs);}
        if (t > 240){SDL_RenderCopy(renderer, minut1_texture.get(), NULL, &texrs);}


        if (scores >= 10){
            game_map.map[game_map.width*(game_map.height-2)-1] = 11;
            game_map.map[game_map.width*(game_map.height-1)-1] = 12;
        }

        SDL_RenderPresent(renderer);

        if ((player.p.v.x*game_map.width + player.p.v.y)>1600){
            still_playing = false;
        }
        // delays

        current_time = current_time + microseconds((long long int)(dt*1000000.0));
        std::this_thread::sleep_until(current_time);

    }
    //koniec gry
    SDL_PauseAudioDevice(devm, 1);
    SDL_PauseAudioDevice(dev, 1);
    SDL_Rect end_rect = {490, 150, 256, 64};
    SDL_SetRenderDrawColor(renderer, 255,0,0,0xFF);
    SDL_RenderDrawRect(renderer, &end_rect);
    SDL_RenderFillRect(renderer, &end_rect);
    SDL_Rect texr;
    texr.x = 520; texr.y=160; texr.w=192; texr.h=40;
    SDL_RenderCopy(renderer, end_texture.get(),NULL, &texr);

    texr.x = 490; texr.y=220; texr.w=256; texr.h=56;
    if ((player.p.v.x*game_map.width + player.p.v.y)>1600){
        SDL_RenderCopy(renderer, gold_texture.get(),NULL, &texr);
    } else if (SDL_GetQueuedAudioSize(devm) == 0){
    SDL_RenderCopy(renderer, time_texture.get(),NULL, &texr);
    }


    SDL_RenderPresent(renderer);
    SDL_ClearQueuedAudio(dev);
    SDL_LoadWAV("mixkit-arcade-retro-game-over-213.wav", &specs, &wav_buffer, &wav_lenght);
    SDL_QueueAudio(dev, wav_buffer, wav_lenght);
    SDL_PauseAudioDevice(dev,0);
    SDL_Delay(1000);

    bool key2 = false;
    while (!key2) {
        SDL_Event event2;
        while (SDL_PollEvent(&event2) && event2.type == SDL_KEYDOWN)
        {
        if (event2.key.keysym.scancode == SDL_SCANCODE_Q){
            key2 = true;
            still_playing = false;
            }
        }
    }
    SDL_PauseAudioDevice(dev, 1);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(dev);
    SDL_CloseAudioDevice(devm);
    SDL_FreeWAV(wav_buffer);
    SDL_FreeWAV(music_buffer);

    SDL_Quit();

    return 0;
}

