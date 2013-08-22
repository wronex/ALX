#ifndef ALX_SYSTEM_HPP
#define ALX_SYSTEM_HPP


#include "FilePath.hpp"
#include "Config.hpp"


namespace alx {


/**
    Class with system functions.
 */
class System {
public:
    /**
        Returns the standard application path.
        @param id id.
        @return the standard path.
     */
    static FilePath standardPath(int id) {
        return al_get_standard_path(id);
    }

    /**
        Returns the system config.
        @return the system config.
     */
    static Config config() {
        return Config(al_get_system_config(), false);
    }
};


} //namespace alx


#endif //ALX_SYSTEM_HPP