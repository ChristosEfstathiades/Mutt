#include "Arena.hpp"

ArenaAllocator::ArenaAllocator(size_t bytes) : size(bytes)
{
    buffer = static_cast<std::byte *>(malloc(size));
    offset = buffer;
}
