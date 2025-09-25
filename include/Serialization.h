#pragma once
#include <string>

namespace AN {
class Serialization {
public:
    static bool save(const std::string &filename);
    static bool load(const std::string &filename);
};
}