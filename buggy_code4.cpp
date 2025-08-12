#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

class MyString {
private:
    std::vector<char> buffer;

public:
    // Constructor handles null pointer and ensures null termination
    explicit MyString(const char* str = "") {
        if (str) {
            size_t len = strlen(str);
            buffer.reserve(len + 1);
            buffer.assign(str, str + len);
            buffer.push_back('\0');
        } else {
            buffer.push_back('\0');
        }
    }

    // Properly handles Rule of Zero (vector manages resources)
    MyString(const MyString&) = default;
    MyString& operator=(const MyString&) = default;
    MyString(MyString&&) noexcept = default;
    MyString& operator=(MyString&&) noexcept = default;

    // Use size_t for length to match standard conventions
    size_t getLength() const {
        return buffer.empty() ? 0 : buffer.size() - 1;
    }

    const char* c_str() const {
        return buffer.empty() ? "" : buffer.data();
    }

    void append(const char* str) {
        if (!str || *str == '\0') return;

        size_t str_len = strlen(str);
        if (buffer.empty()) {
            buffer.resize(str_len + 1);
            std::copy(str, str + str_len, buffer.begin());
            buffer.back() = '\0';
        } else {
            buffer.pop_back(); // Remove existing null terminator
            buffer.insert(buffer.end(), str, str + str_len);
            buffer.push_back('\0'); // Add new null terminator
        }
    }

    void print() const {
        std::cout << c_str() << '\n'; // Use '\n' instead of endl for efficiency
    }
};

MyString createString(const char* str) {
    return MyString(str); // Return by value (uses move semantics)
}

int main() {
    MyString s("Hello");
    s.append(", World!");
    s.print();

    MyString s3 = createString("Temp");
    s3.append("orary");
    s3.print();

    // Demonstrate copy and move operations
    MyString s4 = s3;
    s4.append(" Copy");
    s4.print();

    MyString s5 = std::move(s4);
    s5.append(" Moved");
    s5.print();

    return 0;
}