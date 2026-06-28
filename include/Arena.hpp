#pragma once

#include <cstddef>
#include <cstdlib>

class ArenaAllocator
{
public:
    ArenaAllocator(size_t bytes = 1024 * 1024);
    ~ArenaAllocator() { free(buffer); }

    template <typename T>
    T *allocate()
    {
        std::byte *ptr = offset;
        offset += sizeof(T);
        return reinterpret_cast<T *>(ptr);
    }

    ArenaAllocator(const ArenaAllocator &) = delete;
    ArenaAllocator &operator=(const ArenaAllocator &) = delete;

private:
    size_t size;
    std::byte *buffer;
    std::byte *offset;
};
