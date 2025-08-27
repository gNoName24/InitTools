#include <InitTools/InitConsole.h>

namespace InitConsole {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // =================================================================

    // Namespace Block
    namespace Block {
        std::string get_block(int length, const std::string& left, const std::string& right) {
            std::string output(length, ' ');
            int left_size = left.size();
            int right_size = right.size();

            // Заполнение слева
            output.replace(0, left_size, left);

            // Заполнение справа
            output.replace(length - right_size, right_size, right);

            return output;
        }
        std::string get_block(const char* start, const char* end, int length, const std::string& left, const std::string& right) {
            return start + get_block(length, left, right) + end;
        }
    };
};
