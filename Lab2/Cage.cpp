#include "Cage.h"

namespace gol {
    Cage::Cage(char state) : state('.') {}

    char Cage::get_state() {
        return state;
    }

    void Cage::set_state(char st) {
        state = st;
    }
}
