#include "image.h"

TestImageStream::TestImageStream()
    : height(384), pos(0) {
}

TestImageStream::~TestImageStream() {
}

size_t TestImageStream::getWidth() const {
    return 384;
}

bool TestImageStream::readLine(std::vector<bool>& buffer) {
    if (pos >= height) {
        return false;
    }
    
    for (size_t i = 0; i < buffer.size(); i++) {
        bool x = (i / 48) % 2 == 0;
        bool y = (pos / 48) % 2 == 0;
        if (y) {
            buffer[i] = !x;
        } else {
            buffer[i] = x;
        }
    }

    pos++;
    return true;
}

