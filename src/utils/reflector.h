#pragma once
#include <iostream>
#include <map>
#include <string>

namespace burglar {

class ReflectObject {
 public:
  virtual ~ReflectObject() {}
};

class ObjectFactory {
 public:
  ObjectFactory() {}
  virtual ~ObjectFactory() {}
  virtual ReflectObject* newInstance() = 0;
};

class Reflector {
 public:
  Reflector();
  ~Reflector();
  void registerFactory(const std::string& className, ObjectFactory* of);
  ReflectObject* getNewInstance(const std::string& className);

 private:
  std::map<std::string, ObjectFactory*> objectFactories;
};

Reflector& reflector();

#define REFLECT(name)                                                                                 \
  class ObjectFactory_##name : public ObjectFactory {                                                 \
   public:                                                                                            \
    ObjectFactory_##name() {}           \
    virtual ~ObjectFactory_##name() {} \
    ReflectObject* newInstance() { return new name(); }                                               \
  };                                                                                                  \
  class Register_##name {                                                                             \
   public:                                                                                            \
    Register_##name() { reflector().registerFactory(#name, new ObjectFactory_##name()); }             \
  };                                                                                                  \
  Register_##name register_##name

template <typename T>
T* getNewInstance(const std::string& className) {
  return dynamic_cast<T*>(reflector().getNewInstance(className));
}

}  // namespace burglar
