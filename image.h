#ifndef image_data_h
#define image_data_h

#include <cstdlib>
#include <vector>

class ImageStream {
public:
    virtual ~ImageStream() {}

    virtual size_t getWidth() const = 0;
    virtual bool readLine(std::vector<bool>& buffer) = 0;
};

class TestImageStream : public ImageStream {
public:
    TestImageStream();
    virtual ~TestImageStream();

    virtual size_t getWidth() const;
    virtual bool readLine(std::vector<bool>& buffer);

protected:
    size_t height, pos;
};

#endif
