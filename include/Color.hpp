#ifndef ALX_COLOR_HPP
#define ALX_COLOR_HPP


#include <algorithm>
#include <initializer_list>
#include <allegro5/allegro.h>


#ifdef min
#undef min
#endif


#ifdef max
#undef max
#endif


namespace alx {


/**
    Color class.
 */
class Color {
public:
    /**
        Constructor from single 32-bit color value.
        @param value 32-bit color value in the form of 0xAARRGGBB.
     */
    Color(uint32_t value = 0) {
        m_color.value = value;
    }

    /**
        Constructor from integer color components.
        @param red initial value of the red color component.
        @param green initial value of the green color component.
        @param blue initial value of the blue color component.
        @param alpha initial value of the alpha color component.
     */
    Color(int red, int green, int blue, int alpha = 255) {
        set(red, green, blue, alpha);
    }

    /**
        Constructor from float color components.
        @param red initial value of the red color component.
        @param green initial value of the green color component.
        @param blue initial value of the blue color component.
        @param alpha initial value of the alpha color component.
     */
    Color(float red, float green, float blue, float alpha = 1.0f) {
        set(red, green, blue, alpha);
    }

    /**
        Initializes the color from an initializer list.
        @param components the individual color components; the components read are: red, green, blue, alpha, in that order.
     */
    Color(std::initializer_list<int> components) {
        operator = (components);
    }

    /**
        Initializes the color from an initializer list.
        @param components the individual color components; the components read are: red, green, blue, alpha, in that order.
     */
    Color(const std::initializer_list<float> &components) {
        operator = (components);
    }

    /**
        Constructor from allegro color.
     */
    Color(const ALLEGRO_COLOR &color) {
        operator = (color);
    }

    /**
        Copy constructor.
     */
    Color(const Color &c) {
        operator = (c);
    }

    /**
        Converts the internal color components to a color using the function al_map_rgba.
        @return an allegro color instance.
     */
    operator ALLEGRO_COLOR () const {
        return al_map_rgba(m_color.component.red, m_color.component.green, m_color.component.blue, m_color.component.alpha);
    }

    /**
        Conversion to 32-bit value.
        @return a 32-bit value.
     */
    operator uint32_t () const {
        return m_color.value;
    }

    /**
        Conversion to 32-bit lvalue.
        @return a 32-bit lvalue.
     */
    operator uint32_t& () {
        return m_color.value;
    }

    /**
        Returns the red color component.
        @return the red color component.
     */
    uint8_t red() const {
        return m_color.component.red;
    }

    /**
        Returns the green color component.
        @return the green color component.
     */
    uint8_t green() const {
        return m_color.component.green;
    }

    /**
        Returns the blue color component.
        @return the blue color component.
     */
    uint8_t blue() const {
        return m_color.component.blue;
    }

    /**
        Returns the alpha color component.
        @return the alpha color component.
     */
    uint8_t alpha() const {
        return m_color.component.alpha;
    }

    /**
        Returns the red color component as a float.
        @return the red color component as a float.
     */
    float redFloat() const {
        return _intToFloat(m_color.component.red);
    }

    /**
        Returns the green color component as a float.
        @return the green color component as a float.
     */
    float greenFloat() const {
        return _intToFloat(m_color.component.green);
    }

    /**
        Returns the blue color component as a float.
        @return the blue color component as a float.
     */
    float blueFloat() const {
        return _intToFloat(m_color.component.blue);
    }

    /**
        Returns the alpha color component as a float.
        @return the alpha color component as a float.
     */
    float alphaFloat() const {
        return _intToFloat(m_color.component.alpha);
    }

    /**
        Assignment from integer initializer list.
        @param components color components.
        @return reference to this.
     */
    Color &operator = (const std::initializer_list<int> &components) {
        std::initializer_list<int>::const_iterator it = components.begin();
        switch (components.size()) {
            case 4: m_color.component.alpha = _int(*(it + 3));
            case 3: m_color.component.blue  = _int(*(it + 2));
            case 2: m_color.component.green = _int(*(it + 1));
            case 1: m_color.component.red   = _int(*it);
        }
        return *this;
    }

    /**
        Assignment from float initializer list.
        @param components color components.
        @return reference to this.
     */
    Color &operator = (const std::initializer_list<float> &components) {
        std::initializer_list<float>::const_iterator it = components.begin();
        switch (components.size()) {
            case 4: m_color.component.alpha = _floatToInt(*(it + 3));
            case 3: m_color.component.blue  = _floatToInt(*(it + 2));
            case 2: m_color.component.green = _floatToInt(*(it + 1));
            case 1: m_color.component.red   = _floatToInt(*it);
        }
        return *this;
    }

    /**
        assignment from allegro color.
        @param color color.
        @return reference to this.
     */
    Color &operator = (const ALLEGRO_COLOR &color) {
        al_unmap_rgba(color, &m_color.component.red, &m_color.component.green, &m_color.component.blue, &m_color.component.alpha);
        return *this;
    }

    /**
        sets the red color component.
        @param c value of component.
     */
    void setRed(uint8_t c) {
        m_color.component.red = c;
    }

    /**
        sets the green color component.
        @param c value of component.
     */
    void setGreen(uint8_t c) {
        m_color.component.green = c;
    }

    /**
        sets the blue color component.
        @param c value of component.
     */
    void setBlue(uint8_t c) {
        m_color.component.blue = c;
    }

    /**
        sets the alpha color component.
        @param c value of component.
     */
    void setAlpha(uint8_t c) {
        m_color.component.alpha = c;
    }

    /**
        sets the red color component from a float.
        @param f value of component.
     */
    void setRed(float f) {
        m_color.component.red = _floatToInt(f);
    }

    /**
        sets the green color component from a float.
        @param f value of component.
     */
    void setGreen(float f) {
        m_color.component.green = _floatToInt(f);
    }

    /**
        sets the blue color component from a float.
        @param f value of component.
     */
    void setBlue(float f) {
        m_color.component.blue = _floatToInt(f);
    }

    /**
        sets the alpha color component from a float.
        @param f value of component.
     */
    void setAlpha(float f) {
        m_color.component.alpha = _floatToInt(f);
    }

    /**
        Sets all the color components.
        @param red initial value of the red color component.
        @param green initial value of the green color component.
        @param blue initial value of the blue color component.
        @param alpha initial value of the alpha color component.
     */
    void set(int red, int green, int blue, int alpha = 255) {
        m_color.component.red   = std::max(0, std::min(red, 255));
        m_color.component.green = std::max(0, std::min(green, 255));
        m_color.component.blue  = std::max(0, std::min(blue , 255));
        m_color.component.alpha = std::max(0, std::min(alpha, 255));
    }

    /**
        Sets all the color components from float values.
        @param red initial value of the red color component.
        @param green initial value of the green color component.
        @param blue initial value of the blue color component.
        @param alpha initial value of the alpha color component.
     */
    void set(float red, float green, float blue, float alpha = 1.0f) {
        m_color.component.red   = _floatToInt(red  );
        m_color.component.green = _floatToInt(green);
        m_color.component.blue  = _floatToInt(blue );
        m_color.component.alpha = _floatToInt(alpha);
    }

private:
    //color
    union {
        struct {
            uint8_t blue;
            uint8_t green;
            uint8_t red;
            uint8_t alpha;
        } component;
        uint32_t value;
    } m_color;    //converts float color component to integer
    static uint8_t _floatToInt(float f) {
        return 255 * std::max(0.0f, std::min(f, 1.0f));
    }

    //converts int color component to float
    static float _intToFloat(uint8_t c) {
        return c / 255.0f;
    }

    //converts nt to color component
    static uint8_t _int(int c) {
        return std::max(0, std::min(c, 255));
    }
};


} //namespace alx


#endif //ALX_COLOR_HPP
