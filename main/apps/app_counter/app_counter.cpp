/**
 * @file app_counter.cpp
 * @author Dingushippo
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_counter.h"
#include "spdlog/spdlog.h"


using namespace MOONCAKE::APPS;


void AppCounter::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Get hal
    _data.hal = mcAppGetDatabase()->Get("HAL")->value<HAL::Hal *>();
}


void AppCounter::onResume()
{
    ANIM_APP_OPEN();

    _data.hal->canvas()->fillScreen(THEME_COLOR_BG);
    _data.hal->canvas()->setFont(FONT_REPL);
    _data.hal->canvas()->setTextColor(TFT_ORANGE, THEME_COLOR_BG);
    _data.hal->canvas()->setTextSize(2);
}

static uint32_t counter = 0;

void AppCounter::onRunning()
{

    auto pressed_key = _data.hal->keyboard()->getKey();
    if (pressing_key.x >= 0) 
    {
        if (strcmp(_data.hal->keyboard()->getKeyValue(_data.hal->keyboard()->getKey()).value_first, ";") == 0) 
        {
            counter++;
        }
        else if (strcmp(_data.hal->keyboard()->getKeyValue(_data.hal->keyboard()->getKey()).value_first, ".") == 0) 
        {
            counter--;
        }
    }


    // Draw display
    _data.hal->canvas()->fillScreen(THEME_COLOR_BG);
    _data.hal->canvas()->setCursor(10, 5);
    _data.hal->canvas()->setTextSize(1);
    _data.hal->canvas()->print("Counter");

    // Set formatted string in buffer
    snprintf(_data.string_buffer, sizeof(_data.string_buffer), "Count: %02d", counter);
    
    // Display string buffer in center
    _data.hal->canvas()->setTextSize(2);
    _data.hal->canvas()->drawCenterString(_data.string_buffer, _data.hal->canvas()->width() / 2, _data.hal->canvas()->height() / 2 - 10);

    _data.hal->canvas_update();

    if (_data.hal->homeButton()->pressed())
    {
        _data.hal->playNextSound();
        spdlog::info("quit counter");
        destroyApp();
    }
}
