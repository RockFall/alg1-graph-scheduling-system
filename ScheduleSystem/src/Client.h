#pragma once

#include <string>
#include "Vector2.h"

// Here are defined the Score as pre-established for
// each state and payment type. Those are used on
// ticket's value calculation.

enum class State
{
  MG = 0,
  PR = 10,
  SP = 20,
  SC = 30,
  RJ = 40,
  RN = 50,
  RS = 60,
  INVALID = -1
};

enum class Payment
{
  DINHEIRO = 1,
  DEBITO = 2,
  CREDITO = 3,
  INVALID = -1
};

class Client {
public:
  Client(int id, int age, std::string state, std::string paymentType, Vector2 pos);
  ~Client();

  float getTicketValue() const;

  operator std::string() const {
    return "Client " + std::to_string(id_) + ": {ticket=" + std::to_string(getTicketValue()) + ", position=" + std::string(position_) + "}";
  }

private:
  int id_;
  int age_;
  State stateScore_;
  Payment paymentTypeScore_;
  Vector2 position_;

  bool hasValidData_;
};
