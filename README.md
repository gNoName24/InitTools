# InitLogger

### Добавление в CMake проект через FetchContent:
```cmake
FetchContent_Declare(
    initlogger
    GIT_REPOSITORY https://github.com/gNoName24/InitLogger.git
    GIT_TAG        <version>
)
FetchContent_MakeAvailable(initlogger)

target_link_libraries(MyAwesomeProject PRIVATE
    initlogger
)
```

### Использование:
```cpp
#include "InitLogger/InitLogger.h"

int main() {
  initLogger();
  log_info("1 + 1 = {}", 3);

  return 0;
}
```