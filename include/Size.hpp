#ifndef ALX_SIZE_HPP
#define ALX_SIZE_HPP


#include "Vector2Base.hpp"


namespace alx {


/**
    A size object.
    @param T type of member.
 */
template <class T> class Size : public Vector2Base<Size<T>, T> {
public:
    /**
        constructor from width and height.
     */
    Size(T w = T(), T h = T()) : Vector2Base<Size<T>, T>(w, h) {
    }

    /**
        Returns the width.
        @return the width.
     */
    T width() const {
        return Vector2Base<Size<T>, T>::x();
    }

    /**
        Returns the height.
        @return the height.
     */
    T height() const {
        return Vector2Base<Size<T>, T>::y();
    }

    /**
        Returns width * height.
        @return width * height.
     */
    T area() const {
        return Vector2Base<Size<T>, T>::product();
    }

    /**
        Less-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator < (const Size<T> &pt) const {
        return area() < pt.area();
    }

    /**
        Less-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator <= (const Size<T> &pt) const {
        return area() <= pt.area();
    }

    /**
        Greater-than test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator > (const Size<T> &pt) const {
        return area() > pt.area();
    }

    /**
        Greater-than-or-equal test.
        @param pt the other size to compare this to.
        @return true if the test is successful.
     */
    bool operator >= (const Size<T> &pt) const {
        return area() >= pt.area();
    }

    /**
        Sets the width.
        @param w new width.
     */
    void setWidth(T w) {
        setX(w);
    }

    /**
        Sets the height.
        @param h new height.
     */
    void setHeight(T h) {
        setY(h);
    }

    /**
        Sets both the width and height.
        @param w new width.
        @param h new height.
     */
    void set(T w, T h) {
        setWidth(w);
        setHeight(h);
    }
};


/**
    Creates a size.
    @param w width.
    @param h height.
    @return a size with the given values.
 */
template <class T> Size<T> makeSize(T w, T h) {
    return Size<T>(w, h);
}


} //namespace alx


#endif //ALX_SIZE_HPP
