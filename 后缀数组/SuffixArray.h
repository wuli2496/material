#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

class SuffixArray
{
public:
    SuffixArray(int* pa, int n);
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
    int* m_a;
};

#endif // SUFFIXARRAY_H
