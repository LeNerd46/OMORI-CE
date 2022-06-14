/*
 *--------------------------------------
 * Program Name: OMORI
 * Author: Devon Shoutz
 * License:
 * Description: OMORI for the TI-84 Plus CE
 *--------------------------------------
*/

#include <graphx.h>
#include <sys/rtc.h>

#include "utils.h"
#include "title.h"

int main(void)
{
    setup();

    int x = 0;
    int y = 0;

    uint8_t seconds = 0;

    rtc_Enable(RTC_SEC_INT);

    Utils::drawTitleScreen(0);

    while (rtc_IsBusy());

    rtc_AckInterrupt(RTC_INT_MASK);

    do {

        if (rtc_ChkInterrupt(RTC_SEC_INT))
        {
            seconds++;

            rtc_AckInterrupt(RTC_SEC_INT);
        }

        if (seconds == 1)
            Utils::drawTitleScreen(0);
        else if (seconds == 2)
            Utils::drawTitleScreen(1);
        else if (seconds == 3)
        {
            Utils::drawTitleScreen(2);
            seconds = 0;
        }

    } while (kb_Data[1] != kb_2nd);

    // while (rtc_IsBusy());

    // rtc_AckInterrupt(RTC_INT_MASK);

    /*while (seconds < 5)
    {
        if (rtc_ChkInterrupt(RTC_SEC_INT))
        {
            seconds++;

            rtc_AckInterrupt(RTC_SEC_INT);
        }
    }*/

    Utils::drawCharacter(x, y, None);

    do {

        kb_Scan();

        if (Utils::getButtonDown(0))
        {
            x--; // Left
            Utils::drawCharacter(x, y, None);
        }
        if (Utils::getButtonDown(1))
        {
            x++; // Right
            Utils::drawCharacter(x, y, None);
        }
        if (Utils::getButtonDown(2))
        {
            y--; // Up
            Utils::drawCharacter(x, y, None);
        }
        if (Utils::getButtonDown(3))
        {
            y++; // Down
            Utils::drawCharacter(x, y, Down);
        }

    } while( kb_Data[6] != kb_Clear);
    
    gfx_End();
    
    return 0;
}
