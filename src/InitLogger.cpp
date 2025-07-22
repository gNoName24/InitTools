#include "InitLogger/InitLogger.h"

std::shared_ptr<spdlog::logger> InitLogger::Logger = spdlog::stdout_color_mt("console");

void InitLogger::initLogger() {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();

    formatter->add_flag<LevelShortForm>('S');
    formatter->add_flag<AlignedLocationFlag>('L');

    formatter->set_pattern("[%^%S%$] [%T] [%L] %v");

    Logger->set_formatter(std::move(formatter));
}