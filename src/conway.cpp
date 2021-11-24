#include "conway.h"

Conway::Conway(size_t h, size_t w, char *data, bool toroid_mode = false) :
    _h(h), _w(w) {
    _toroid_mode = toroid_mode;
    // clone data
    _state = new char[(h + 2) * (w + 2)];
    for (size_t i = 0; i < h; ++i) {
        for(size_t j = 0; j < w; ++j) {
            _state[(w + 2) * i + j + 1] = data[i*w + j];
        }
    }    
    _aux_state = new char[(h + 2) * (w + 2)];
    if (!_toroid_mode)
    {
        // first and last column
        for (size_t i = 0; i < _h + 2; ++i) {
            size_t ind;
            ind = i * _w;
            _aux_state[ind] = 0;
            ind += (w - 1);
            _aux_state[ind] = 0;
        }
        // first and last column
        size_t max_ind = (h + 2) * (w + 2);
        for (size_t j = 0; j < _w + 2; ++j) {
            _aux_state[j] = 0;
            _aux_state[--max_ind] = 0;
        }
    }
    // default rules
    // birth rule
    b_rule = new char[1];
    b_rule[0] = 3;
    // supervicence rule
    s_rule = new char[2];
    s_rule[0] = 2;
    s_rule[1] = 3;

}

Conway::~Conway() {
    delete[] _state;
    delete[] _aux_state;
    delete [] s_rule;
    delete [] b_rule;
}

char * getState() {
    char *_out = new char[_h * _w];
    size_t w2 = _w + 2;
    for (size_t i = 0; i < _h; ++i) {
        for (size_t j = 0; j < _w; ++j) {
            _out[i*_w + j] = _state[w2 * i + j + 1];
        }
    }
    return _out;
}

void next() {

    // step 1:
    // aux = 0
    size_t h2 = _h + 2;
    size_t w2 = _w + 2;
    size_t elements = h2 * w2;
    for (size_t i = 0; i < elements; ++i) {
        _aux_state[i] = 0;
    }

    // step 2:
    // if toroid_mode
    if (_toroid_mode) {
        // copy columns
        for (size_t i = 0; i < h0; ++i) {
            _state[w2*i] = _state[w2*i + w2 - 2];
            _state[w2*i + w2 - 1] = _state[w2*i + 1];
        }
        // copy rows
        for (size_t j = 0; j < w0; ++j) {
            _state[j] = _state[(h2 - 2) * w2 + j];
            _state[(h2 - 1) * w2 + j] = _state[j + w2];
        }
    }

    // step 3: 
    // convolution
    for (size_t x = 0; x < 3; ++x) {
        for (size_t y = 0; y < 3; ++y) {
            // skip this case
            if ( x == 0 && y == 0) {
                continue;
            }
            for (size_t i = 1; i < _h + 1; ++i) {
                for (size_t j = 1; j < _w + 1; ++j) {
                    _aux_state[i * (_w + 2) + j] += _state[(i + y - 1)* (_w + 2) + j + x - 1];
                }
            }            
        }
    }

    // step 4: 
    size_t elements = h2 * w2;
    for (size_t i = 0; i < elements; ++i) {
        if (_state[i]) {
            // check supervivence rule
            _state[i] = 0;
            for (size_t j = 0; j < s_rule_len; ++j) {
                if (_aux_state[i] == s_rule[j]) {
                    _state[i] = 1;
                    break;
                }
            }
        }
        else {
            // check birth rule
            for (size_t j = 0; j < b_rule_len; ++j) {
                if (_aux_state[i] == b_rule[j]) {
                    _state[i] = 1;
                    break;
                }
            }
        }
    }

    // end

}

void Conway::setBRule(std::void<size_t> rule) {
    if (b_rule != nullptr) { delete [] b_rule; }
    b_rule_len = rule.size();
    b_rule = new char[b_rule_len];
    for (size_t i = 0; i < b_rule_len; ++i) {
        b_rule[i] = (char)rule[i];
    }
}

void Conway::setSRule(std::void<size_t> rule) {
    if (s_rule != nullptr) { delete [] s_rule; }
    s_rule_len = rule.size();
    s_rule = new char[s_rule_len];
    for (size_t i = 0; i < s_rule_len; ++i) {
        s_rule[i] = (char)rule[i];
    }
}
