# InitTools

### Добавление в CMake проект через FetchContent:
```cmake
FetchContent_Declare(
    inittools
    GIT_REPOSITORY https://github.com/gNoName24/InitTools.git
    GIT_TAG        <version>
)
FetchContent_MakeAvailable(inittools)

target_link_libraries(MyAwesomeProject PRIVATE
    InitTools::InitTools
)
```

### Использование InitLogger:
```cpp
#include <InitTools/InitLogger.h>

int main() {
  InitLogger::initLogger();
  InitLogger::log_info("1 + 1 = {}", 3);

  return 0;
}
```
