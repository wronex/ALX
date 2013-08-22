#ifndef ALX_VECTOR2BASEBASE_HPP
#define ALX_VECTOR2BASEBASE_HPP


namespace alx {


/**
    A 2d vector class that is base for classes that want to have a Vector2 interface.
    @param D derived class type.
    @param T type of coordinate.
 */
template <class D, class T> class Vector2Base {
public:
    /**
        the default constructor.
        @param x default x value.
        @param y default y value.
     */
    Vector2Base(T x = 0, T y = 0) : m_x(x), m_y(y) {
    }

    /**
        Returns the x coordinate.
     */
    T x() const {
        return m_x;
    }

    /**
        Returns the y coordinate.
     */
    T y() const {
        return m_y;
    }

    /**
        Equality test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator == (const U &vec) const {
        return m_x == vec.x() && m_y == vec.y();
    }

    /**
        Difference test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator != (const U &vec) const {
        return !operator == (vec);
    }

    /**
        Less-than test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator < (const U &vec) const {
        return m_y < vec.y() || (m_y == vec.y() && m_x < vec.x());
    }

    /**
        Less-than-or-equal test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator <= (const U &vec) const {
        return m_y < vec.y() || (m_y == vec.y() && m_x <= vec.x());
    }

    /**
        Greater-than test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator > (const U &vec) const {
        return m_y > vec.y() || (m_y == vec.y() && m_x > vec.x());
    }

    /**
        Greater-than-or-equal test.
        @param vec the other vector to compare this to.
        @return true if the test is successful.
     */
    template <class U> bool operator >= (const U &vec) const {
        return m_y > vec.y() || (m_y == vec.y() && m_x >= vec.x());
    }

    /**
        Returns x * y.
        @return x * y.
     */
    T product() const {
        return m_x * m_y;
    }

    /**
        Sets the x coordinate.
        @param x x value.
     */
    void setX(T x) {
        m_x = x;
    }

    /**
        Sets the y coordinate.
        @param y y value.
     */
    void setY(T y) {
        m_y = y;
    }

    /**
        Sets the x and y coordinates.
        @param x x value.
        @param y y value.
     */
    void set(T x, T y) {
        setX(x);
        setY(y);
    }

    /**
        Adds a vector to this.
        @param vec vector to add to this.
        @return reference to this.
     */
    template <class U> D &operator += (const U &vec) {
        set(m_x + vec.x(), m_y + vec.y());
        return _derived();
    }

    /**
        Adds two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the sum of both points.
     */
    template <class U> D operator + (const U &vec) {
        return D(x() + vec.x(), y() + vec.y());
    }

    /**
        Subtracts a vector from this.
        @param vec vector to subtract from this.
        @return reference to this.
     */
    template <class U> D &operator -= (const U &vec) {
        set(m_x - vec.x(), m_y - vec.y());
        return _derived();
    }

    /**
        Subtracts two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the difference of both points.
     */
    template <class U> D operator - (const U &vec) {
        return D(x() - vec.x(), y() - vec.y());
    }

    /**
        Multiplies a vector to this.
        @param vec vector to multiply to this.
        @return reference to this.
     */
    template <class U> D &operator *= (const U &vec) {
        set(m_x * vec.x(), m_y * vec.y());
        return _derived();
    }

    /**
        Multiplies two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the product of both points.
     */
    template <class U> D operator * (const U &vec) {
        return D(x() * vec.x(), y() * vec.y());
    }

    /**
        Divides this by a vector.
        @param vec vector to divide this by.
        @return reference to this.
     */
    template <class U> D &operator /= (const U &vec) {
        set(m_x / vec.x(), m_y / vec.y());
        return _derived();
    }

    /**
        Divides two points.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the quotient of both points.
     */
    template <class U> D operator / (const U &vec) {
        return D(x() / vec.x(), y() / vec.y());
    }

    /**
        Divides this by a vector and sets the modulo.
        @param vec vector to divide this by.
        @return reference to this.
     */
    template <class U> D &operator %= (const U &vec) {
        set(m_x % vec.x(), m_y % vec.y());
        return _derived();
    }

    /**
        Divides two points and returns the modulo.
        @param a 1st vector.
        @param b 2nd vector.
        @return a vector which contains the modulo of the division of both points.
     */
    template <class U> D operator % (const U &vec) {
        return D(x() % vec.x(), y() % vec.y());
    }

    /**
        Adds a value to both coordinates.
        @param val value to add.
        @return reference to this.
     */
    D &operator += (T val) {
        set(m_x + val, m_y + val);
        return _derived();
    }

    /**
        Adds a value to a vector and creates a new vector.
        @param val value to add.
        @return a new vector.
     */
    D operator + (T val) const {
        return D(m_x + val, m_y + val);
    }

    /**
        Subtracts a value from both coordinates.
        @param val value to subtract.
        @return reference to this.
     */
    D &operator -= (T val) {
        set(m_x - val, m_y - val);
        return _derived();
    }

    /**
        Subtracts a value from a vector and creates a new vector.
        @param val value to subtract.
        @return a new vector.
     */
    D operator - (T val) const {
        return D(m_x - val, m_y - val);
    }

    /**
        Multiplies a value to both coordinates.
        @param val value to multiply this with.
        @return reference to this.
     */
    D &operator *= (T val) {
        set(m_x * val, m_y * val);
        return _derived();
    }

    /**
        Multiplies a value to a vector and creates a new vector.
        @param val value to multiply this with.
        @return a new vector.
     */
    D operator * (T val) const {
        return D(m_x * val, m_y * val);
    }

    /**
        Divides both coordinates by a value.
        @param val value to divide this with.
        @return reference to this.
     */
    D &operator /= (T val) {
        set(m_x / val, m_y / val);
        return _derived();
    }

    /**
        Divides a vector by a value and creates a new vector.
        @param val value to divide this with.
        @return a new vector.
     */
    D operator / (T val) const {
        return D(m_x / val, m_y / val);
    }

    /**
        Sets both coordinates to the modulo of the division.
        @param val value to divide this with.
        @return reference to this.
     */
    D &operator %= (T val) {
        set(m_x % val, m_y % val);
        return _derived();
    }

    /**
        Divides a vector by a value and creates a new vector with the modulo.
        @param val value to divide this with.
        @return a new vector.
     */
    D operator % (T val) const {
        return D(m_x % val, m_y % val);
    }

    /**
        Invert the sign of the components.
     */
    D operator - () const {
        return D(-m_x, -m_y);
    }

    /**
        Invert the sign of the components.
     */
    D operator + () const {
        return D(+m_x, +m_y);
    }

private:
    //coordinates
    T m_x;
    T m_y;

    friend class Transform;

    //Get derived instance.
    const D &_derived() const {
        return *static_cast<const D *>(this);
    }

    //Get derived instance.
    D &_derived() {
        return *static_cast<D *>(this);
    }
};


} //namespace alx


#endif //ALX_VECTOR2BASEBASE_HPP

