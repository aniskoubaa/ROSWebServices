#ifndef SERIAL_LIB_H
#define SERIAL_LIB_H

#include <stdlib.h>
#include <coros_common/string_lib.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

template <class T> inline std::string serialize(const T & o) 
{
  std::ostringstream oss;
  boost::archive::text_oarchive oa(oss);
  oa << o;
  return oss.str();
}

template <class T> inline std::string serializeMessage(const T & o) 
{
  std::string s = o.serialization_letter + serialize(o); //old version
  std::string sz = "[" + itos(s.size()) + "]";
  return std::string( s + sz);
}

template <class T> inline T deserialize(const std::string & s) 
{
  T o;
  std::stringstream iss;
  iss << s;
  boost::archive::text_iarchive ia(iss);
  ia >> o;
  return o;
}

template <class T> inline T deserializeMessage(const std::string & s) 
{
  std::string str = s;

  //remove the serialization_letter
  str.erase(0,1);

  //remove the size indicator
  unsigned first = str.find("[");
  unsigned last = str.find("]");
  int size = atoi(str.substr(first+1,last-first-1).c_str());
  str = str.substr(0,size);

  return deserialize<T>(str);
}


#endif //SERIAL_LIB_H

