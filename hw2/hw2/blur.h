#ifndef BLUR_H
#define BLUR_H

#include "image_process.h"

class Blur : public ImageProcess{
public:
    Blur():_ksize(5){}
    Blur(int ksize):_ksize(ksize){}

    void set_ksize(int ksize){
        _ksize = ksize;
    }

protected:
    int _ksize;
};

#endif // BLUR_H
