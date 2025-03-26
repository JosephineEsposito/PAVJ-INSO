#include "../libs/tigr.h"
#include "../libs/ActionList.h"
#include "../libs/Action.h"
#include "../libs/Vec2.h"
#include <math.h>

float playerx = 160, playery = 200;
float playerxs = 0, playerys = 0;
bool standing = true;
bool isRecording = false;
float remaining = 0;
Tigr* backdrop, * screen;

// Some simple platformer-esque physics.
// I do not necessarily recommend this as a good way of implementing a platformer :)
void update(float dt) {
  if (remaining > 0)
    remaining -= dt;

  if (isRecording)
  {
    //saved input from start position
  }
  else
  {
    // Read the keyboard and move the player.
    if (standing && tigrKeyDown(screen, TK_SPACE))
      playerys -= 200;
    if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'A'))
      playerxs -= 10;
    if (tigrKeyHeld(screen, TK_RIGHT) || tigrKeyHeld(screen, 'D'))
      playerxs += 10;
  }

  float oldx = playerx, oldy = playery;

  // Apply simply physics.
  playerxs *= exp(-10.0f * dt);
  playerys *= exp(-2.0f * dt);
  playerys += dt * 200.0f;
  playerx += dt * playerxs;
  playery += dt * playerys;

  // Apply collision.
  if (playerx < 8) {
    playerx = 8;
    playerxs = 0;
  }

  if (playerx > screen->w - 8) {
    playerx = screen->w - 8.0f;
    playerxs = 0;
  }

  // Apply playfield collision and stepping.
  float dx = (playerx - oldx) / 10;
  float dy = (playery - oldy) / 10;
  standing = false;
  for (int n = 0; n < 10; n++) {
    TPixel p = tigrGet(backdrop, (int)oldx, (int)oldy - 1);
    if (p.r == 0 && p.g == 0 && p.b == 0)
      oldy -= 1;
    p = tigrGet(backdrop, (int)oldx, (int)oldy);
    if (p.r == 0 && p.g == 0 && p.b == 0 && playerys > 0) {
      playerys = 0;
      dy = 0;
      standing = true;
    }
    oldx += dx;
    oldy += dy;
  }

  playerx = oldx;
  playery = oldy;
}

int main(int argc, char* argv[]) {
  // Load our sprite.
  Tigr* character = tigrLoadImage("character.png");
  if (!character)
    tigrError(0, "Cannot load character.png");

  // Make a window and an off-screen backdrop.
  screen = tigrWindow(320, 240, "Rewind", TIGR_2X);
  backdrop = tigrBitmap(screen->w, screen->h);

  // Fill in the background.
  tigrClear(backdrop, tigrRGB(80, 180, 255));
  tigrFill(backdrop, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  tigrFill(backdrop, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  tigrLine(backdrop, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  int prevx = 0, prevy = 0, prev = 0;
  bool isRecording = false;

  ActionList commands = ActionList();
  Vec2 player_pos = Vec2();

  // Repeat till they close the window.
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
  {
    if (tigrKeyDown(screen, TK_RETURN))
    {
      isRecording = true;
      player_pos = Vec2(160, 200);
      commands.clear();
    }

    unsigned key = 0;
    if (isRecording)
    {
      key |= !!tigrKeyHeld(screen, 'A') * 65;
      key |= !!tigrKeyHeld(screen, 'D') * 68;
      key |= !!tigrKeyHeld(screen, TK_SPACE) * TK_SPACE;

      commands.push(new Action(key));
    }

    // Update the game.
    float dt = tigrTime();
    update(dt);

    // Composite the backdrop and sprite onto the screen.
    tigrBlit(screen, backdrop, 0, 0, 0, 0, backdrop->w, backdrop->h);
    tigrBlitAlpha(screen, character, (int)playerx - character->w / 2, (int)playery - character->h, 0, 0, character->w,
      character->h, 1.0f);

    tigrPrint(screen, tfont, 10, 10, tigrRGBA(0xc0, 0xd0, 0xff, 0xc0), "");
    tigrPrint(screen, tfont, 10, 222, tigrRGBA(0xff, 0xff, 0xff, 0xff), "A D + SPACE");

    // Update the window.
    tigrUpdate(screen);
  }

  tigrFree(character);
  tigrFree(backdrop);
  tigrFree(screen);
  return 0;
}