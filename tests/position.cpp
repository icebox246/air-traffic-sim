#include <cstdlib>

#include "../src/RealPosition.hpp"
#include "../src/util.hpp"

int main() {
    RealPosition position(1, 2);
    auto pos2 = position.moved(1, 3);

    ASSERT_EQ(pos2.x(), 2);
    ASSERT_EQ(pos2.y(), 5);

    return EXIT_SUCCESS;
}
