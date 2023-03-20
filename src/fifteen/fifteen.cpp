#include "fifteen.hpp"

fifteen::fifteen(state_mask state) : state(state) {}
auto fifteen::set(uint8_t index, uint64_t value) -> void {
    uint64_t offset = index << 2;
    uint64_t mask = ~(msb_64bit_mask >> offset);
    state = (state & mask) | (value << (60 - offset));
}

auto fifteen::get(uint8_t index) const -> uint8_t {
    uint8_t offset = index << 2;
    return (state & (msb_64bit_mask >> offset)) >> (60 - offset);
}

auto fifteen::correctly_placed() const -> uint8_t {
    uint64_t in_place = state & correct_placement;
    uint8_t cnt = 0;
    uint64_t mask = ~msb_64bit_mask;
    for(int i = 0; i < 15; i++) {
        cnt += ((in_place & mask) != 0);
        mask >>= 4;
    }
    cnt += ((state & 0xF) == 0);
    return cnt;
}

auto fifteen::misplaced() const -> uint8_t {
    return 16 - correctly_placed();
}


auto fifteen::is_solved() const -> bool {
    return state == correct_placement;
}

auto fifteen::swap(uint8_t index1, uint8_t index2) -> void {
    auto val2 = get(index1);
    set(index1, get(index2));
    set(index2, val2);
}


auto fifteen::get_random() -> fifteen {
    fifteen a;
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF};
    std::random_device rd;
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(numbers), std::end(numbers), rng);
    for(int i = 0; i < 16; i++) {
        a.set(i, numbers[i]);
    }
    return a;
}

auto fifteen::get_correct() -> fifteen {
    return fifteen(correct_placement);
}

auto fifteen::operator==(const fifteen& other) const -> bool {
    return state == other.state;
}

auto fifteen::operator!=(const fifteen& other) const -> bool {
    return !(*this == other);
}

auto fifteen::print() const -> void {
    for(int i = 0; i <= 3; i++) {
        std::printf("[%2d][%2d][%2d][%2d]\n", get(4 * i), get(4 * i + 1), get(4 * i + 2), get(4 * i + 3));
    }
}
