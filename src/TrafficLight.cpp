#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/*
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics.
    // The received object should then be returned by the receive function.
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop
    // runs and repeatedly calls the receive function on the message queue.
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be
    // started in a thread when the public method „simulate“ is called. To do
    // this, use the thread queue in the base class.
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
  // FP.2a : Implement the function with an infinite loop that measures the
  // time between two loop cycles and toggles the current phase of the traffic
  // light between red and green and sends an update method to the message
  // queue using move semantics. The cycle duration should be a random value
  // between 4 and 6 seconds. Also, the while-loop should use
  // std::this_thread::sleep_for to wait 1ms between two cycles.

  std::random_device rd; // non-determistic seed generator
  std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator

  // Construct uniform probability density function for integers in [a, b].
  // uniform_int_distribution<T=int>::uniform_int_distribution(T a, T b)
  std::uniform_int_distribution<> dis(4000, 6000);

  // Generate a random int in [4000, 6000] with Mersenne Twister.
  double cycleDuration = dis(gen); // Let units of cycleDuration be milliseconds.

  // Define local refernce time variable and initialize.
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  lastUpdate = std::chrono::system_clock::now();

  while (true) {
    // Sleep at every iteration to reduce CPU usage.
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // Compute time difference since last local reference time.
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    if (timeSinceLastUpdate >= cycleDuration) {
      if(_currentPhase == TrafficLightPhase::red)
        _currentPhase = TrafficLightPhase::green;
      else
        _currentPhase = TrafficLightPhase::red;

      // Send update message to the message queue.
      // _messageQueue.send(); // Uncomment after FP.3

      // Reset stop watch for next cycle.
      lastUpdate = std::chrono::system_clock::now();
    }
  }
}
