
#include <vector>

template <typename T>
struct Validator {
    T value;
    bool negate_next;
    bool result;

    Validator(const T& val) : value(val), negate_next(false), result(true) {}

    // Convert to bool for use in if statements
    operator bool() const {
        return result;
    }

    // Check if value equals target
    Validator& toBe(const T& target) {
        bool condition = (value == target);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Check if value is in vector
    Validator& toBeOneOf(const std::vector<T>& vec) {
        bool found = false;
        for (const auto& item : vec) {
            if (value == item) {
                found = true;
                break;
            }
        }
        bool condition = found;
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Greater than or equal
    Validator& ge(const T& target) {
        // a >= b is equivalent to !(a < b)
        bool condition = !(value < target);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Less than or equal
    Validator& le(const T& target) {
        // a <= b is equivalent to !(a > b), and a > b is equivalent to (b < a)
        bool condition = !(target < value);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Greater than
    Validator& gt(const T& target) {
        // a > b is equivalent to (b < a)
        bool condition = (target < value);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Less than
    Validator& lt(const T& target) {
        bool condition = (value < target);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Negate the following conditions
    Validator& Not() {
        negate_next = !negate_next;
        return *this;
    }
};

// Main expect function
template <typename T>
Validator<T> expect(const T& value) {
    return Validator<T>(value);
}
