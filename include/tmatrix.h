// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <assert.h>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0|| sz> MAX_VECTOR_SIZE)
      throw length_error("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      if (pMem == nullptr)
          throw bad_alloc();
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[]pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              sz = v.sz;
              delete[]pMem;
              Y* p = new T[sz];
              if (p == nullptr) throw bad_alloc();
              pMem = p;
          }
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return (*this);
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = 0;
      delete[]pMem;
      pMem = nullptr;
      swap(*this, v);
      return(*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) throw out_of_range("out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw out_of_range("out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return 0;
      else
          for (int i = 0; i < sz; i++)
              if (pMem[i] != v.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] += val;
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] -= val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] *= val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw logic_error("vectors have different lengths");
      TDynamicVector <T> res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] += v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw logic_error("vectors have diffrent lengths");
      TDynamicVector<T> res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] -= v.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v)// noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw logic_error("vectors have different lengths");
      t res = t();
      for (int i = 0; i < sz; i++)
          res += pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s == 0 || s > MAX_MATRIX_SIZE)
          throw length_error("Matrix size should be greater than zero and ess than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0;
      else
          for (int i = 0; i < sz; i++)
              if (pMem[i] != m.pMem[i]) return 0;
      return 1;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (int i = 0; i < z; i++)
          res[i] = pMem[i] * val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) throw logic_error("different lengths");
      TDynamicVector <T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] * v;
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw logic_error("different lengths");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] + m.pMem[i];
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw logic_error("different lengths");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] - m.pMem[i];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw logic_error("different lengths");
      TDynamicMatrix res(sz);
      size_t pMemSize = pMem[0].size();
      TDynamicVector <T> tmp(pMemSize);
      for(int i=0;i<sz;i++)
          for (int j = 0; j < pMemSize; j++) {
              for (int k = 0; k < pMemSize; k++)
                  tmp[k] = m.pMem[k][j];
              res[i][j] += pMem[i] * tmp;
          }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i]<<endl;
      return ostr;
  }
};

#endif
