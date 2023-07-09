#include "game.h"
#include <iostream>
#include "SDL.h"
#include "foodnbomb.cpp"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, bomb);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, food.GetCount(), bomb.GetCount());
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.food_body.x = x;
      food.food_body.y = y;
      food.Setflag(Flag_type::green);
      return;
    }
  }
}

void Game::PlaceBomb(){
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check the location is not occupied by a snake item before placing
    // bomb.
    if (!snake.SnakeCell(x, y)) {
      bomb.bomb_body.x = x;
      bomb.bomb_body.y = y;
      bomb.Setflag(Flag_type::red);
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.food_body.x == new_x && food.food_body.y == new_y) {
    
    PlaceFood();
    food.Display_on_screen(food.Checkflag());
    food.Count();
    score++;
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if there's bomb over here
  if (bomb.bomb_body.x == new_x && bomb.bomb_body.y == new_y) {
    PlaceBomb();
    bomb.Display_on_screen(bomb.Checkflag());
    bomb.Count();
    // check if food is eaten to decrease the length of snake.
    if (food.GetCount() > 0) food.Distroy(); 
    if(score > 0) --score;
    snake.DistroyBody();
    //No more snake
    if(bomb.GetCount()+3 > food.GetCount() || snake.size < 4) {
      std::cout<< " Snake dead, don't go on bombs!"<<"\n";
      snake.alive = false;
    }

  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

int Game :: GetFoodCount(){
  return food.GetCount();
}

int Game::GetBombCount(){
  return bomb.GetCount();
}