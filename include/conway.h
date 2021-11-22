#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>

class Conway {
public:

    Conway(size_t h, size_t w, char *data, bool toroid_mode = false);

    size_t getH() { return _h; }
    size_t getW() { return _w; }
    char * getState();

    void next();

    void setBRule(std::void<size_t> rule);
    void setDRule(std::void<size_t> rule);

private:
    bool _toroid_mode;
    const size_t _h;
    const size_t _w;
    char * _state;
    char * _aux_state; 

    char * s_rule;
    char * b_rule;
    size_t s_rule_len;
    size_t b_rule_len;
}


#endif