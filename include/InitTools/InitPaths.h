#ifndef NONAME24_INITTOOLS_INIT_PATHS_H
#define NONAME24_INITTOOLS_INIT_PATHS_H

/*
    Версия InitTools на момент обновления модуля: 1.1.0
    Зависимости: Нет
    Зависимости C++:
        string_view / string,
        unordered_map,
        windows.h / unistd.h / mach-o/dyld.h
        filesystem
    
    Использование:
        Вызывая init() инициализируются root и root_data переменные.
        root - Содержит путь к корню папки, где был запущен исполняемый файл
        root_data - Содержит в себе выражение root + <root_data до инициализации> - Стандартное значение: "/Resources"
        Первоначальный root_data можно изменить только до вызова init(), после он будет преобразован в root + root_data.

        Переменная paths используется в качестве хранения всех остальных путей в виде:
            <ключ> - <значение> / <std::string/_view> - <std::string/_view>
        Если paths не нужен, отключите INITTOOLS_INITPATHS_ENABLE_PATHS.
        Также paths использует std::string по умолчанию,
            но есть возможность использовать std::string_view, включив INITTOOLS_INITPATHS_USE_STRING_VIEW.
    
    Словарь:
        INITTOOLS_INITPATHS_ENABLE_PATHS - Включение paths
        INITTOOLS_INITPATHS_USE_STRING_VIEW - Использование std::string_view вместо std::string в paths

        void init() - Инициализация двух следующих переменных
        std::string root - Путь к корню папки, где был запущен исполняемый файл
        std::string root_data - Выражение root + <root_data до инициализации>, которое инициализируется в init()
        std::unordered_map<std::string/_view, std::string/_view> paths (опционально) - Хранилище путей
*/

#define INITTOOLS_INITPATHS_ENABLE_PATHS true
#define INITTOOLS_INITPATHS_USE_STRING_VIEW false

#include <string>
#if INITTOOLS_INITPATHS_USE_STRING_VIEW
#include <string_view>
#endif
#include <unordered_map>

namespace InitPaths {
    extern std::string root;
    extern std::string root_data;
    #if INITTOOLS_INITPATHS_ENABLE_PATHS
        #if INITTOOLS_INITPATHS_USE_STRING_VIEW
            extern std::unordered_map<std::string_view, std::string_view> paths;
        #else
            extern std::unordered_map<std::string, std::string> paths;
        #endif
    #endif

    void init();
};

#endif // NONAME24_INITTOOLS_INIT_PATHS_H