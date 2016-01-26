#ifndef BASE_MESSAGE_H
#define BASE_MESSAGE_H

class BaseMessage
{
  
public:
  
  BaseMessage(char letter) :  serialization_letter(letter) {}
  
  BaseMessage(char letter, int code) :  serialization_letter(letter), message_code(code) {}
  
  virtual std::string serialize() {}; //TODO: make it pure virtual immediately
  
  virtual void deserialize() {};   //TODO: make it pure virtual immediately
  
  const char serialization_letter;
  
  int message_code;
  
};

#endif //BASE_MESSAGE_H
