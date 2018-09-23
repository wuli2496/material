#include "SuffixArray.h"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

const int N = 256;

SuffixArray::SuffixArray(int* pa, int n)
    :m_prank(NULL), m_pheight(NULL),  m_psa(NULL)
{
    m_a = pa;
    m_n = n;
}

SuffixArray::~SuffixArray()
{
    delete []m_prank;
    delete []m_psa;
    delete []m_pheight;
}

void SuffixArray::buildSa()
{
    m_prank = new int[m_n];
    int n = max(N, m_n);
    int* tmp = new int[m_n];
    int* c = new int[n];
    m_psa = new int[m_n];
    m_pheight = new int[m_n];
    
    memset(c, 0, sizeof(int) * n);
    for (int i = 0; i < m_n; i++)
    {
        m_prank[i] = m_a[i];
        c[m_prank[i]]++;
    }
    
    for (int i = 1; i < n; i++)
    {
        c[i] += c[i - 1];
    }
    
    for (int i = m_n - 1; i >= 0; i--)
    {
        m_psa[--c[m_prank[i]]] = i;
    }
    
    int m =  m_n;
    for (int i = 1; i <= m_n; i <<= 1) 
    {
        int p = 0;
        for (int j = m_n - i; j < m_n; j++)
        {
            tmp[p++] = j;
        }
        for (int j = 0; j < m_n; j++)
        {
            if (m_psa[j] >= i)
            {
                tmp[p++] = m_psa[j] - i;
            }
        }
        
        memset(c, 0, sizeof(int) * n);
        for (int j = 0; j < m_n; j++)
        {
            c[m_prank[tmp[j]]]++;
        }
        
        for (int j = 1; j < n; j++)
        {
            c[j] += c[j - 1];
        }
        
        
        for (int j = m_n - 1; j >= 0; j--)
        {
            m_psa[--c[m_prank[tmp[j]]]] = tmp[j];
        }
        
        swap(m_prank, tmp);
        
        m_prank[m_psa[0]] = 0;
        
        m = 0;
        for (int j = 1; j < m_n; j++)
        {
            if (tmp[m_psa[j - 1]] == tmp[m_psa[j]] 
            && m_psa[j- 1] + i < m_n 
            && m_psa[j] + i < m_n 
            && tmp[m_psa[j - 1] + i] == tmp[m_psa[j] + i])
            {
                m_prank[m_psa[j]] = m;
            }
            else 
            {
                m_prank[m_psa[j]] = ++m;
            }
        }
        
        if (m >= m_n - 1) break;
    }
    
    delete []c;
    delete []tmp;
    
    return;
}

void SuffixArray::getHeight()
{
    m_pheight[0] = 0;
    
    int k = 0;
    for (int i = 0; i < m_n; i++)
    {
        int curPos = m_prank[i];
        if (curPos == 0) continue;
        curPos--;
        
        int j = m_psa[curPos];
        if (k)
        {
            k--;
        }
        while (i + k < m_n && j + k < m_n && m_a[i + k] == m_a[j + k]) k++;
        m_pheight[m_prank[i]] = k;
    }
}

const int* SuffixArray::getSa()
{
   return m_psa;
}

const int* SuffixArray::getH()
{
    return m_pheight;
}

