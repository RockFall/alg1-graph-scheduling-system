#include "Client.h"


State s_toState(std::string state){
  if (state == "MG")
    return State::MG;
  else if (state == "PR")
    return State::PR;
  else if (state == "SP")
    return State::SP;
  else if (state == "SC")
    return State::SC;
  else if (state == "RJ")
    return State::RJ;
  else if (state == "RN")
    return State::RN;
  else if (state == "RS")
    return State::RS;

  return State::INVALID;
}

Payment s_toPayment(std::string payment){
  if (payment == "DINHEIRO")
    return Payment::DINHEIRO;
  else if (payment == "DEBITO")
    return Payment::DEBITO;
  else if (payment == "CREDITO")
    return Payment::CREDITO;

  return Payment::INVALID;
}

Client::Client(int id, int age, std::string state, std::string paymentType, Vector2 pos)
  : id_(id), age_(age), position_(pos), hasValidData_(true)
{
  stateScore_ = s_toState(state);
  paymentTypeScore_ = s_toPayment(paymentType);

  if (stateScore_ == State::INVALID ||
      paymentTypeScore_ == Payment::INVALID ||
      age_ < 0 || age_ > 130 ||
      id_ < 0){

    hasValidData_ = false;
  }
}

Client::~Client()
{

}

float Client::getTicketValue() const
{
  if (hasValidData_)
    return ((float)(abs(60 - age_) + (int)stateScore_) / (float)paymentTypeScore_);
  else
    return -1;
}
