#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

class Signal{

public:

    Signal();
    Signal(size_t size, int discr_fr);

    int get_size();
    double* get_m_data();
    int get_disc_freq();
    void resize(size_t new_size);
    double get_max();
    double get_min();
    void clear();

    void generate_sine(double freq, double sig_ampl);

    double& operator[](size_t index);
    const double& operator[](size_t index)const;

    Signal operator +(Signal second_sig);
    Signal operator -(Signal second_sig);
    Signal operator +=(Signal second_sig);
    Signal operator -=(Signal second_sig);
private:
    size_t m_data_size;
    double* m_data;
    int disc_freq;

};
#endif
