#pragma once

#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include <compression.h>

#include "gfx/gfx.h"

enum CollisionType : unsigned char
{
    Right,
    Left,
    Up,
    Down,
    None
};

void setup()
{
    gfx_Begin();

    gfx_SetPalette(mypalette, sizeof_mypalette, 0);
    gfx_SetTransparentColor(0);

    gfx_SetDrawBuffer();
}

class Utils
{
public:
    static void drawTitleScreen(unsigned char index)
    {
        gfx_FillScreen(255);
        
        gfx_ScaledTransparentSprite_NoClip(OmoriTitleScreenWords, 85, 38, 2, 2);
        gfx_TransparentSprite(OmoriTitleScreenLight, 155, 0);

        if (index == 0)
        {
            gfx_ScaledTransparentSprite_NoClip(OmoriTitleScreen1, 105, 240 - OmoriTitleScreen1_height - OmoriTitleScreen1_height, 2, 2);
            gfx_TransparentSprite(OmoriTitleScreenLightThings1, 149, 46);
        }
        else if (index == 1)
        {
            gfx_ScaledTransparentSprite_NoClip(OmoriTitleScreen2, 105, 240 - OmoriTitleScreen1_height - OmoriTitleScreen1_height, 2, 2);
            gfx_TransparentSprite(OmoriTitleScreenLightThings2, 149, 46);
        }
        else if (index == 2)
        {
            gfx_ScaledTransparentSprite_NoClip(OmoriTitleScreen3, 105, 240 - OmoriTitleScreen1_height - OmoriTitleScreen1_height, 2, 2);
            gfx_TransparentSprite(OmoriTitleScreenLightThings3, 149, 46);
        }

        gfx_Sprite(ButtonNewGame, 30, 218);
        gfx_Sprite(ButtonContinue, 135, 218);
        gfx_Sprite(ButtonOptions, 235, 218);

        gfx_RLETSprite(Hand, 130 - Hand_width, 221);

        gfx_BlitBuffer();
    }

    static void drawCharacter(int x, int y, CollisionType type)
    {
        gfx_FillScreen(255);

        if (type == Down)
        {
            // Run down animation

            gfx_RLETSprite(OmoriWalkDown1, x, y);
        }

        if (type == None)
        {
            // Run down animation

            gfx_RLETSprite(OmoriWalkDown2, x, y);
        }

        gfx_BlitBuffer();
    }

    static bool getButtonDown(uint8_t index)
    {
        kb_lkey_t keys[6] = { kb_KeyLeft, kb_KeyRight, kb_KeyUp, kb_KeyDown, kb_Key2nd };
        
        if (index > 4)
            return false;

        return kb_IsDown(keys[index]);
    }

    static bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight)
    {
        return firstX < secondX + secondWidth // First object's left side is to the left of the second object's right side,         first object is on the right
            && firstX + firstWidth > secondX // First object's right side is to the right of the second object's left side,         first object is on the left
            && firstY < secondY + secondHeight // The first object's top is above the second object's bottom,                       first object is underneath
            && firstY + firstHeight > secondY; // The first object's bottom is lower than the second object's top,                  first object is above
    }

    static CollisionType checkCollisionDirection(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight)
    {
        bool onRight = firstX + firstWidth < secondX + secondWidth && firstX + firstWidth > secondX && firstY < secondY + secondHeight && firstY + firstHeight > secondY;
        bool onLeft = firstX < secondX + secondWidth && firstX > secondX && firstY < secondY + secondHeight && firstY + firstHeight > secondY;
        bool above = firstY + firstHeight > secondY && firstY < secondY&& firstX + firstWidth > secondX && firstX < secondX + secondWidth;
        bool under = firstY + firstHeight > secondY && firstY < secondY + secondHeight && firstX + firstWidth > secondX && firstX < secondX + secondWidth;

        if (onRight && firstY + firstHeight > secondY + 2 && firstY < secondY + secondHeight - 2)
            return Right;
        else if (onLeft && firstY + firstHeight > secondY + 2 && firstY < secondY + secondHeight - 2)
            return Left;
        else if (above)
            return Up;
        else if (under)
            return Down;
        else
            return None;
    };
};