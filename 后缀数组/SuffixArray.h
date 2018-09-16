#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include <string>

class SuffixArray
{
public:
    SuffixArray(std::string s);
    ~SuffixArray();
    
    void buildSa();
    void getHeight();
    
    const int* getSa();
    const int* getH();
private:
    int *m_prank;
    int *m_pheight;
    int *m_psa;
    int m_n;
    std::string m_str;
};

#endif // SUFFIXARRAY_H
