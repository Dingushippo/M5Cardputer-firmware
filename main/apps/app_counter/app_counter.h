/**
 * @file app_counter.h
 * @author Dingushippo
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mooncake.h>
#include "../../hal/hal.h"
#include "../utils/theme/theme_define.h"
#include "../utils/anim/anim_define.h"
#include "../utils/icon/icon_define.h"

#include "assets/timer_big.h"
#include "assets/timer_small.h"


namespace MOONCAKE
{
    namespace APPS
    {
        class AppCounter : public APP_BASE
        {
            private:
                struct Data_t
                {
                    HAL::Hal* hal = nullptr;
                    char string_buffer[100];
                };
                Data_t _data;

            public:
                void onCreate() override;
                void onResume() override;
                void onRunning() override;
        };

        class AppCounter_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "COUNTER"; }
            void* getAppIcon() override { return (void*)(new AppIcon_t(image_data_timer_big, image_data_timer_small)); }
            void* newApp() override { return new AppCounter; }
            void deleteApp(void *app) override { delete (AppCounter*)app; }
        };
    }
}
