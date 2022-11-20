#include "Signal.h"

Signal::Signal()
{
    m_data = new double[0];
    disc_freq = 44100;
    m_data_size = 0;
}

Signal::Signal(size_t size, int discr_fr)
{
    if (discr_fr < 0)
        throw new _exception;

    m_data = new double[size];
    disc_freq = discr_fr;
    m_data_size = size;
}

int Signal::get_size()
{
    return m_data_size;
}

double* Signal::get_m_data()
{
    return m_data;
}

int Signal::get_disc_freq()
{
    return disc_freq;
}

void Signal::resize(size_t new_size)
{
    int counter = 0;
    double* resized_arr = new double[new_size];

    if(m_data_size >= new_size)
       counter = new_size;
    else
       counter = m_data_size;

    for (auto i = 0; i < counter; i++)
        resized_arr[i] = m_data[i];

    delete[] m_data;
    m_data = resized_arr;
    m_data_size=new_size;
}

double Signal::get_max()
{
    double max_value = m_data[0];
    for(int i=0; i<this->get_size();i++){
        if(m_data[i]>max_value)
            max_value = m_data[i];
    }
    return max_value;
}

double Signal::get_min()
{
    double min_value = m_data[0];
    for(int i = 0; i < this->get_size(); i++){
        if(m_data[i]<min_value)
            min_value = m_data[i];
    }
    return min_value;
}

void Signal::clear()
{
    m_data_size = 0;
    delete [] m_data;
}

void Signal::generate_sine(double freq, double sig_ampl)
{
    for (size_t i = 0; i < m_data_size; i++)
        m_data[i] = sig_ampl * sin((2 * M_PI * freq * i) / (44100));
    return;
}

double& Signal::operator[](size_t index)
{
    if (index>m_data_size-1)
        throw new _exception;
    return m_data[index];
}

const double& Signal::operator[](size_t index) const
{
    if (index>m_data_size-1)
        throw new _exception;
    return m_data[index];
}

Signal Signal::operator +(Signal sig)
{
    int max_length = std::max(this->get_size(),sig.get_size());
    int min_length = std::min(this->get_size(),sig.get_size());

    Signal result(max_length,44100);

    for(int i=0; i<max_length;i++)
        if(i<min_length)
            result[i] = this->m_data[i] + sig.m_data[i];
        else
            max_length == this->get_size() ? result[i]=this->m_data[i] : result[i]=sig.m_data[i];
    return result;
}

Signal Signal::operator -(Signal sig)
{
    int max_length = std::max(this->get_size(), sig.get_size());
    int min_length = std::min(this->get_size(), sig.get_size());

    Signal result(max_length, 44100);

    for(int i = 0; i < max_length; i++)
        if(i < min_length)
            result[i] = this->m_data[i] - sig.m_data[i];
        else
            max_length == this->get_size() ? result[i]=this->m_data[i] : result[i]=sig.m_data[i];
    return result;
}

Signal Signal::operator +=(Signal sig)
{
    return *this + sig;
}

Signal Signal::operator -=(Signal sig)
{
    return *this - sig;
}
