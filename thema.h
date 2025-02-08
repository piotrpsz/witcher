//
// Created by piotr on 05.02.25.
//


#pragma once
#include <SDL3/SDL.h>

namespace Witcher::thema {
    // Colors from https://en.wikipedia.org/wiki/Adwaita_(design_language)
    static constexpr SDL_Color BLUE_1    {0x99, 0xc1, 0xf1, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BLUE_2    {0x62, 0xa0, 0xea, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BLUE_3    {0x35, 0x84, 0xe4, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BLUE_4    {0x1c, 0x71, 0xd8, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BLUE_5    {0x1a, 0x5f, 0xb4, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color GREEN_1   {0x8f, 0xf0, 0xa4, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color GREEN_2   {0x57, 0xe3, 0x89, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color GREEN_3   {0x33, 0xd1, 0x7a, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color GREEN_4   {0x2e, 0xc2, 0x7e, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color GREEN_5   {0x26, 0xa2, 0x69, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color YELLOW_1  {0xf9, 0xf0, 0x6b, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color YELLOW_2  {0xf8, 0xe4, 0x5c, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color YELLOW_3  {0xf6, 0xd3, 0x2d, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color YELLOW_4  {0xf5, 0xc2, 0x11, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color YELLOW_5  {0xe5, 0xa5, 0x0a, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color ORANGE_1  {0xff, 0xbe, 0x6f, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color ORANGE_2  {0xff, 0xa3, 0x48, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color ORANGE_3  {0xff, 0x78, 0x00, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color ORANGE_4  {0xe6, 0x61, 0x00, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color ORANGE_5  {0xc6, 0x46, 0x00, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color RED_1     {0xf6, 0x61, 0x51, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color RED_2     {0xed, 0x33, 0x3b, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color RED_3     {0xe0, 0x1b, 0x24, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color RED_4     {0xc0, 0x1c, 0x28, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color RED_5     {0xa5, 0x1d, 0x2d, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color PURPLE_1  {0xdc, 0x8a, 0xdd, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color PURPLE_2  {0xc0, 0x61, 0xcb, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color PURPLE_3  {0x91, 0x41, 0xac, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color PURPLE_4  {0x81, 0x3d, 0x9c, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color PURPLE_5  {0x61, 0x35, 0x83, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BROWN_1   {0xcd, 0xab, 0x8f, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BROWN_2   {0xb5, 0x83, 0x5a, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BROWN_3   {0x98, 0x6a, 0x44, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BROWN_4   {0x86, 0x5e, 0x3c, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color BROWN_5   {0x63, 0x45, 0x2c, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color LIGHT_1   {0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color LIGHT_2   {0xf6, 0xf5, 0xf4, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color LIGHT_3   {0xde, 0xdd, 0xda, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color LIGHT_4   {0xc0, 0xbf, 0xbc, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color LIGHT_5   {0x9a, 0x99, 0x96, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color DARK_1    {0x77, 0x76, 0x7b, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color DARK_2    {0x5e, 0x5c, 0x64, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color DARK_3    {0x3d, 0x38, 0x46, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color DARK_4    {0x24, 0x1f, 0x31, SDL_ALPHA_OPAQUE };
    static constexpr SDL_Color DARK_5    {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };

    static constexpr SDL_Color DEFAULT_MENU_BACKGROUND    {0x33, 0x33, 0x33, SDL_ALPHA_OPAQUE };

    static constexpr SDL_Color DEFAULT_WINDOW_BACKGROUND{0x1e, 0x1f, 0x22, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color DEFAULT_WIDGET_BACKGROUND{0x2e, 0x2f, 0x32, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color DEFAULT_CLICKED_WIDGET_BACKGROUND{0x42, 0x3f, 0x3e, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color DEFAULT_BORDER_OUT       {0x6e, 0x6f, 0x72, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color DEFAULT_BORDER_IN        {0x7e, 0x7f, 0x82, SDL_ALPHA_OPAQUE};

    static constexpr SDL_Color DEFAULT_TEXT_FOREGROUND{0xbc, 0xbe, 0xc4, SDL_ALPHA_OPAQUE};

    static constexpr SDL_Color DEFAULT_FRAME_COLOR{0x00, 0x64, 0x64, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color DEFAULT_CLICKED_FRAME_COLOR{0x64, 0x64, 0, SDL_ALPHA_OPAQUE};
}
