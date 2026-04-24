
#include &lt;vector&gt;

template &lt;typename T&gt;
struct Validator {
    T value;
    bool negate_next;
    bool result;

    Validator(const T&amp; val) : value(val), negate_next(false), result(true) {}

    // Convert to bool for use in if statements
    operator bool() const {
        return result;
    }

    // Check if value equals target
    Validator&amp; toBe(const T&amp; target) {
        bool condition = (value == target);
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Check if value is in vector
    Validator&amp; toBeOneOf(const std::vector&lt;T&gt;&amp; vec) {
        bool found = false;
        for (const auto&amp; item : vec) {
            if (value == item) {
                found = true;
                break;
            }
        }
        bool condition = found;
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Greater than or equal
    Validator&amp; ge(const T&amp; target) {
        bool condition = (value &gt;= target);
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Less than or equal
    Validator&amp; le(const T&amp; target) {
        bool condition = (value &lt;= target);
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Greater than
    Validator&amp; gt(const T&amp; target) {
        bool condition = (value &gt; target);
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Less than
    Validator&amp; lt(const T&amp; target) {
        bool condition = (value &lt; target);
        if (negate_next) condition = !condition;
        result = result &amp;&amp; condition;
        return *this;
    }

    // Negate the following conditions
    Validator&amp; Not() {
        negate_next = !negate_next;
        return *this;
    }
};

// Main expect function
template &lt;typename T&gt;
Validator&lt;T&gt; expect(const T&amp; value) {
    return Validator&lt;T&gt;(value);
}
