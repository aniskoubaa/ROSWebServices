#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <sstream>
using namespace std;
// the followig function from: http://www.stroustrup.com/bs_faq2.html
static inline 
string itos(int i) // convert int to string
{
  stringstream s;
  s << i;
  return s.str();
}

template <typename T>
string mtos(T message)
{
  stringstream s;
  s << message;
  return s.str();
}


static inline std::string* satosa(const std::string array[], int size )
{
  std::string * result = new std::string[size];
  for (int i=0; i<size; i++)
    result[i] = mtos(array[i]);

  return result;
}

#endif //STRING_LIB_H
