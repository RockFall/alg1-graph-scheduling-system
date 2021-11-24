#pragma once

#include <string>
#include "Vector2.h"

// Here are defined the variables used to calculate the ticket value.
// The scores are pre-established for each state and payment type.
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
  // -- CONSTRUCTOR --
  Client(int id, int age, std::string state, std::string paymentType, Vector2 pos);
  ~Client();

  // Calculates the ticket for this Client from the equation:
  // (abs(60-age) + state_score) / paymentType_score
  float getTicketValue() const;

  // Getters
  Vector2 getPosition() const;
  int getId() const;

  // Turns Client into string for debugging
  operator std::string() const {
    return "Client " + std::to_string(id_) + ": {ticket=" + std::to_string(getTicketValue()) + ", position=" + std::string(position_) + "}";
  }

private:
  // Data
  int id_;
  int age_;
  Vector2 position_;
  // Ticket calculation variables
  State stateScore_;
  Payment paymentTypeScore_;
  // Used for testing
  bool hasValidData_;
};
