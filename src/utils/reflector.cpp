#include "utils/reflector.h"
namespace burglar {

Reflector::Reflector() {}

Reflector::~Reflector() {
  std::map<std::string, ObjectFactory*>::iterator it = objectFactories.begin();
  for (; it != objectFactories.end(); ++it) {
    delete it->second;
  }
  objectFactories.clear();
}

void Reflector::registerFactory(const std::string& className, ObjectFactory* of) {
  std::map<std::string, ObjectFactory*>::iterator it = objectFactories.find(className);
  if (it != objectFactories.end()) {
    std::cout << "object already registered" << std::endl;
  } else {
    objectFactories[className] = of;
  }
}

ReflectObject* Reflector::getNewInstance(const std::string& className) {
  std::map<std::string, ObjectFactory*>::iterator it = objectFactories.find(className);
  if (it != objectFactories.end()) {
    ObjectFactory* of = it->second;
    return of->newInstance();
  }
  return NULL;
}

Reflector& reflector() {
  static Reflector reflector;
  return reflector;
}
}  // namespace burglar