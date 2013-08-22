#ifndef ALX_TRANSFORM_HPP
#define ALX_TRANSFORM_HPP


#include <stack>
#include <allegro5/allegro.h>
#include "Value.hpp"
#include "Point.hpp"
#include "Rect.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_TRANSFORM.
 */
class Transform : public Value<ALLEGRO_TRANSFORM> {
public:
    /**
        The default constructor.
     */
    Transform() : Value<ALLEGRO_TRANSFORM>() {
    }

    /**
        constructor from transform.
        @param transform transform.
     */
    Transform(const ALLEGRO_TRANSFORM &transform) : Value<ALLEGRO_TRANSFORM>() {
        al_copy_transform(&get(), &transform);
    }

    /**
        the copy constructor.
        @param src source object.
     */
    Transform(const Transform &src) : Value<ALLEGRO_TRANSFORM>() {
        al_copy_transform(&get(), &src.get());
    }

    /**
        The identity constructor.
     */
    static Transform &identity() {
        auto transform = std::unique_ptr<Transform>(new Transform);
        transform->setIdentity();
        return *transform.release();
    }

    /**
        builds a transformation.
        @param x translation along the x axis.
        @param y translation along the y axis.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
        @param theta rotation angle.
     */
    Transform(float x, float y, float sx, float sy, float theta) {
        set(x, y, sx, sy, theta);
    }

    /**
        Checks the inverse.
        @return tolerance tolerance.
        @return true if invertible, false otherwise.
     */
    bool isInvertible(float tolerance) const {
        return al_check_inverse(&get(), tolerance);
    }

    /**
        Transforms coordinates.
        @param x x.
        @param y y.
     */
    void transform(float &x, float &y) const {
        al_transform_coordinates(&get(), &x, &y);
    }

    /**
        Transforms a point.
        @param pt point.
     */
    void transform(Point<float> &pt) const {
        transform(pt.m_x, pt.m_y);
    }

    /**
        Transforms a rectangle.
        @param rt rectangle.
     */
    void transform(Rect<float> &rt) const {
        transform(rt.m_left, rt.m_top);
        transform(rt.m_right, rt.m_bottom);
    }

    /**
        Uses this transform.
     */
    void setCurrent() {
        al_use_transform(&get());
        _currentTransform() = this;
    }

    /**
        inverts this transform.
     */
    void invert() {
        al_invert_transform(&get());
    }

    /**
        Sets this transform to be the identity transform.
     */
    void setIdentity() {
        al_identity_transform(&get());
    }

    /**
        builds a transformation.
        @param x translation along the x axis.
        @param y translation along the y axis.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
        @param theta rotation angle.
     */
    void set(float x, float y, float sx, float sy, float theta) {
        al_build_transform(&get(), x, y, sx, sy, theta);
    }

    /**
        applies a translation.
        @param x translation along the x axis.
        @param y translation along the y axis.
     */
    void translate(float x, float y) {
        al_translate_transform(&get(), x, y);
    }

    /**
        applies a rotation.
        @param theta rotation angle.
     */
    void rotate(float theta) {
        al_rotate_transform(&get(), theta);
    }

    /**
        applies scaling.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
     */
    void scale(float sx, float sy) {
        al_scale_transform(&get(), sx, sy);
    }

    /**
        returns the current transform.
        @return the current transform.
     */
    static Transform *current() {
        return _currentTransform();
    }

    /**
     * stores the current transform in a stack.
     */
    static void store() {
        auto state = std::unique_ptr<State>(new State);
        state->retrieve(ALLEGRO_STATE_TRANSFORM);
        _storedStates.push(std::move(state));
    }

    /**
     * restores the last stored transform that pops it from the stack.
     */
    static void restore() {
        if (!_storedStates.empty()) {
            auto state = std::move(_storedStates.top());
            state->restore();
            _storedStates.pop();
        }
    }

private:
    //internal current transform
    static Transform*& _currentTransform() {
        static Transform *t = 0;
        return t;
    }

    static std::stack< std::unique_ptr<State> > _storedStates;
};


} //namespace alx


#endif //ALX_TRANSFORM_HPP
