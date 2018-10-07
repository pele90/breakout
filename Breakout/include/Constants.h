#ifndef CONSTANTS_H
#define CONSTANTS_H

// PLAYER
#define PLAYER_MOVEMENT_SPEED 500
#define PLAYER_STARTING_POSITION { 400, 650, 200, 20 }
#define PLAYER_TEXTURE_NAME "player"

// SCREEN
#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768
#define DEFAULT_BOARD_WIDTH 924
#define DEFAULT_BOARD_HEIGHT 668

// GAME
#define DEFAULT_SCORE 0
#define DEFAULT_LIVES 3
#define DEFAULT_LEVEL 1
#define FPS 60;
constexpr int screen_ticks_per_frame = 1000 / FPS;

// BRICK
#define DAMAGED_BRICK_PREFIX "bricks/brick_"
#define DAMAGED_BRICK_SUFFIX "_damaged"

// BALL
#define BALL_MOVEMENT_SPEED 600
#define BALL_STARTING_POSITION { 450, 600, 15, 15 }
#define BALL_STARTING_DIRECTION {2, -12}
#define BALL_TEXTURE_NAME "ball"

// LEVEL
#define NUMBER_OF_LEVELS 5

// LEVEL DEFINITIONS
#define ROW_COUNT "RowCount"
#define COLUMN_COUNT "ColumnCount"
#define ROW_SPACING "RowSpacing"
#define COLUMN_SPACING "ColumnSpacing"
#define BACKGROUND_TEXTURE "BackgroundTexture"
#define BRICK_TYPES "BrickTypes"
#define BRICK_TYPE "BrickType"
#define BRICKS "Bricks"
#define EMPTY_BRICK "_"

// BRICK TYPE DEFINITIONS
#define BRICK_TYPE_ID "Id"
#define BRICK_TYPE_TEXTURE "Texture"
#define BRICK_TYPE_HIT_POINTS "HitPoints"
#define BRICK_TYPE_HIT_SOUND "HitSound"
#define BRICK_TYPE_BREAK_SOUND "BreakSound"
#define BRICK_TYPE_BREAK_SCORE "BreakScore"

// PLAY SCENE
#define PLAY_SCENE_BACKGROUND_TEXTURE_PATH "background/game_background"
#define SCORE_LABEL_NAME "score_value_label"
#define LEVEL_LABEL_NAME "level_value_label"
#define LIVES_LABEL_NAME "heart_"
#define LEVEL_PREFIX "Level_"
#define PLAY_SCENE_LAYOUT_NAME "game_gui"

// MAIN MENU SCENE
#define MAIN_MENU_SCENE_BACKGROUND_TEXTURE_PATH "background/wall_background"
#define PLAY_SCENE_LAYOUT_NAME "main_menu"

// BUTTONS
#define CONTINUE_BUTTON_NAME "continue_button"
#define PLAY_BUTTON_NAME "play_button"
#define EXIT_BUTTON_NAME "exit_button"


#endif // !CONSTANTS_H
