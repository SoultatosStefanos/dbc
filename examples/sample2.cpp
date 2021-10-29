/**
 * @file sample2.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dbc/dbc.hpp"

namespace
{

class vehicle // sample interface
{
public:
  virtual ~vehicle () = default;

  bool
  engine_works () const noexcept // class invariant
  {
    return true;
  }

  bool
  engine_running () const noexcept
  {
    dbc::invariant (engine_works ());
    return engine_running_impl ();
  }

  //
  // Double invariant validation because of mutator method.
  // Ensuring and requiring through the class interface.
  //
  void
  start_engine ()
  {
    dbc::invariant (engine_works ());
    dbc::require (!engine_running ());
    start_engine_impl ();
    dbc::ensure (engine_running ());
    dbc::invariant (engine_works ());
  }

  //
  // Double invariant validation because of mutator method.
  // Ensuring and requiring through the class interface.
  //
  void
  stop_engine ()
  {
    dbc::invariant (engine_works ());
    dbc::require (engine_running ());
    stop_engine_impl ();
    dbc::ensure (!engine_running ());
    dbc::invariant (engine_works ());
  }

protected:
  virtual bool engine_running_impl () const noexcept = 0;
  virtual void start_engine_impl () = 0;
  virtual void stop_engine_impl () = 0;
};

class car : public vehicle
{
public:
  car () : engine_running_ (false){};
  ~car () = default;

  bool
  engine_running_impl () const noexcept override
  {
    return engine_running_;
  }

  std::string
  engine_sound () const
  {
    dbc::invariant (engine_works ());
    return sound;
  }

  //
  // Postconditions may be strengthened down the inheritance chain.
  // Preconditions shouldn't be strengthened down the inheritance chain.
  //
  //
  void
  start_engine_impl () override
  {
    engine_running_ = true;
    sound = "brumbrum";
    dbc::ensure (engine_sound () == "brumbrum"); // may add other postconditions
  }

  void
  stop_engine_impl () override
  {
    engine_running_ = false;
  }

private:
  bool engine_running_;
  std::string sound;
};

}