#ifndef CONSTANTS_H
#define CONSTANTS_H

// PLAYER
#define PLAYER_MOVEMENT_SPEED 500.f
#define PLAYER_STARTING_POSITION { 450, 700, 150, 20 }
#define PLAYER_TEXTURE_NAME "ui/player"

// SCREEN
#define DEFAULT_SCREEN_WIDTH 1024.f
#define DEFAULT_SCREEN_HEIGHT 768.f
#define DEFAULT_BOARD_WIDTH 924.f
#define DEFAULT_BOARD_HEIGHT 668.f

// GAME
#define DEFAULT_SCORE 0
#define DEFAULT_LIVES 3
#define DEFAULT_LEVEL 1
#define FPS 60;
constexpr float screen_ticks_per_frame = 1000.f / FPS;

// BRICK
#define DAMAGED_BRICK_PREFIX "bricks/brick_"
#define DAMAGED_BRICK_SUFFIX "_damaged"

// BALL
#define BALL_MOVEMENT_SPEED 600.f
#define BALL_STARTING_POSITION { 450, 600, 15, 15 }
#define BALL_STARTING_DIRECTION {2, -12}
#define BALL_TEXTURE_NAME "ui/ball"

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
#define INFINITE_BRICK_TYPE "Infinite"

// PLAY SCENE
#define PLAY_SCENE_BACKGROUND_TEXTURE_PATH "background/game_background"
#define SCORE_LABEL_NAME "game_score_value_label"
#define LEVEL_LABEL_NAME "level_value_label"
#define LIVES_LABEL_NAME "heart_"
#define LEVEL_PREFIX "Level_"
#define PLAY_SCENE_LAYOUT_NAME "game_gui"
#define PLAY_PAUSE_LABEL_NAME "pause_label"

// MAIN MENU SCENE
#define MAIN_MENU_SCENE_BACKGROUND_TEXTURE_PATH "background/wall_background"
#define MAIN_MENU_SCENE_LAYOUT_NAME "main_menu"

// END GAME SCENE
#define END_GAME_SCENE_BACKGROUND_TEXTURE_PATH "background/wall_background"
#define END_GAME_SCENE_LAYOUT_NAME "end_game_menu"
#define END_GAME_MESSAGE_LABEL_NAME "game_over_label"
#define END_GAME_SCORE_VALUE_LABEL_NAME "score_value_label"
#define GAME_OVER_TEXTURE_NAME "game_over_image"
#define GAME_COMPLETE_LABEL_NAME "game_complete_label"

// BUTTONS
#define MENU_BUTTON_NAME "menu_button"
#define PLAY_BUTTON_NAME "play_button"
#define EXIT_BUTTON_NAME "exit_button"
#define RESTART_BUTTON_NAME "restart_button"
#define HOVERED_BUTTON_ALPHA 200
#define FULL_ALPHA 255
#define HOVER_BUTTON_POSITION_VALUE 3
#define HOVER_BUTTON_SCALE_VALUE 6
#define BUTTON_CLICK_SOUND "button_click"

// DATASET DEFINITIONS
#define BUTTON_ELEMENT "Button"
#define LABEL_ELEMENT "Label"
#define IMAGE_ELEMENT "Image"

#define NAME_ATTRIBUTE "name"
#define VISIBLE_ATTRIBUTE "visible"
#define TEXTURE_NAME_ATTRIBUTE "texture_name"
#define RECT_ATTRIBUTE "rect"
#define TEXT_ATTRIBUTE "text"
#define FONT_NAME "font_name"
#define FONT_COLOR "font_color"
#define FONT_SIZE "font_size"
#define VISIBLE_FALSE_VALUE "0"
#define VISIBLE_TRUE_VALUE "1"

// MUSIC
#define MENU_MUSIC_NAME "menu_music"
#define GAME_MUSIC_NAME "game_music"
#define BALL_PLAYER_HIT "ball_player_hit"
#define MUSIC_VOLUME_MODIFIER 0.75f

#endif // !CONSTANTS_H
