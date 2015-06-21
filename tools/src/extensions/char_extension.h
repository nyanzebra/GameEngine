#pragma once

namespace cppe {
    namespace character {
        inline int as_int(const char& c, const bool& is_negative) {
            if (!is_negative) {
                return c - '0';
            } else {
                return (c - '0') * (-1);
            }
        }
    }
}