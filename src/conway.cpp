#include "conway.h"

Conway::Conway(size_t h, size_t w, char *data, bool toroid_mode = false) :
    _h(h), _w(w) {
    _toroid_mode = toroid_mode;
    // clone data
    _state = new char[h * w];
    size_t max_ind = _h * _w;
    for (size_t i = 0; i < max_ind; ++i) {
        _state = data[i];
    }
    _aux_state = new char[(h + 2) * (w + 2)];
    // if (!_toroid_mode)
    {
        for (size_t i = 0; i < _h + 2; ++i) {
            size_t ind;
            ind = i * _w;
            _aux_state[ind] = 0;
            ind += (w - 1);
            _aux_state[ind] = 0;
        }
        for (size_t j = 0; j < _w + 2; ++j) {
            size_t ind;
            ind = j;
            _aux_state[ind] = 0;
            ind = max_ind - j;
            _aux_state[ind] = 0;
        }
    }
}

Conway::~Conway() {
    if (*_state != nullptr) {
        delete _state;
    }
    if (*_aux_state != nullptr) {
        delete _aux_state;
    }
}

char * getState() {
    size_t max_ind = _h * _w;
    char * temp_state = new char[max_ind];
    for (size_t i = 0; i < max_ind; ++i) {
        temp_state = _state[i];
    }
    return temp_state;
}

void next() {
    // copy data from state to aux
    for (size_t i = 0; i < _h; ++i) {
        for (size_t j = 0; j < _w; ++j) {
            _aux_state[(i + 1)*(_w + 2) + j + 1] = _state[i * _w + j];
            // another way to do it
            // size_t ind = i * _w + j;
            // _aux_state[ind + 2 * _i + _w + 3] = _state[ind];
        }
    }
    // if toroid, copy boarders
    if (_toroid_mode) {
        for (size_t i = 0; i < _h + 2; ++i) {
            size_t ind;
            ind = i * (_w + 2);
            _aux_state[ind] = _aux_state[ind + _w];
            _aux_state[ind + _w + 1] = _aux_state[ind + 1];   
            // another way to do it
            // _aux_state[ind + _w + 2 - 1] = _aux_state[ind + 1];   
        }
        for (size_t j = 0; j < _w + 2; ++j) {
            _aux_state[j] = _aux_state[(_h + 1)*(_w + 2) + j];
            _aux_state[(_h + 1)*(_w + 2) + j] = _aux_state[(_w + 2) + j];
            // another way to do it
            // size_t ind = _h * _w + j;
            // _aux_state[j] = _aux_state[(_h + 1)*(_w + 2) + j];
            // _aux_state[(_h + 1)*(_w + 2) + j] = _aux_state[(_w + 2) + j];
        }
    }
    // state = 0
    size_t k = _w * _h; 
    for (size_t i = 0; i < k; ++i) {
        _state[i] = 0;
    }
    // convolution
    for (size_t i0 = 0; i0 < _h; ++i0) {
        for (size_t j0 = 0; j0 < _w; ++j0) {

            for (size_t i = 0; i < 3; ++i ){
                for (size_t j  0; j < 3; ++j) {
                    if (i == j) { continue; }
                    _state[i0 * _h + j0] += _aux_state[(i0 + 2) * (_w + 2) ];
                }
            }

        }
    }
}
