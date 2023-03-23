#pragma once
#include <exception>
class ComponentNotFoundException : public std::exception {};

class ChildNotFoundException: public std::exception {};

class GameObjectIsAlreadyChildException : public std::exception {};

