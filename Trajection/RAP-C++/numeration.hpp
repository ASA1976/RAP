// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef NUMERATION_ASSOCIATION
#define NUMERATION_ASSOCIATION
#include "trajection.hpp"

namespace numeration {

  template <typename Integral>
  static inline bool Begins(const Integral &integer)
  {
    return integer;
  }
  template <typename Integral, Integral beginning, Integral ending>
  static inline bool FiniteBegins(const Integral &integer)
  {
    return integer >= beginning && integer <= ending;
  }
  template <typename Integral>
  static inline void Begin(const Integral &value, Integral &integer)
  {
    integer = value;
  }
  template <typename Integral, Integral beginning, Integral ending>
  static inline void FiniteBegin(const Integral &value, Integral &integer)
  {
    if (!FiniteBegins< Integral, beginning, ending >(value))
      throw value;
    Begin(value, integer);
  }
  template <typename Integral>
  static inline trajection::Referential< const Integral > To(const Integral &integer)
  {
    trajection::Referential< const Integral > referral = {integer};
    return referral;
  }
  template <typename Integral, Integral beginning, Integral ending>
  static inline trajection::Referential< const Integral > FiniteTo(const Integral &integer)
  {
    if (!FiniteBegins< Integral, beginning, ending >(integer))
      throw integer;
    return To(integer);
  }

  namespace increment {

    template <typename Integral>
    static inline bool Traversable(const Integral &integer)
    {
      const Integral next = integer + 1;
      return integer < next;
    }
    template <typename Integral, Integral beginning, Integral ending>
    static inline bool FiniteTraversable(const Integral &integer)
    {
      return integer >= beginning && integer < ending;
    }
    template <typename Integral>
    static inline void Traverse(Integral &integer)
    {
      integer++;
    }
    template <typename Integral, Integral beginning, Integral ending>
    static inline void FiniteTraverse(Integral &integer)
    {
      if (!FiniteTraversable< Integral, beginning, ending >(integer))
        throw integer;
      Traverse(integer);
    }

  }

  namespace decrement {

    template <typename Integral>
    static inline bool Traversable(const Integral &integer)
    {
      const Integral previous = integer - 1;
      return integer > previous;
    }
    template <typename Integral, Integral beginning, Integral ending>
    static inline bool FiniteTraversable(const Integral &integer)
    {
      return integer > beginning && integer <= ending;
    }
    template <typename Integral>
    static inline void Traverse(Integral &integer)
    {
      integer--;
    }
    template <typename Integral, Integral beginning, Integral ending>
    static inline void FiniteTraverse(Integral &integer)
    {
      if (!FiniteTraversable< Integral, beginning, ending >(integer))
        throw integer;
      Traverse(integer);
    }

  }

}
#define NUMERATION_INCREMENT_LINER(INTEGRAL) \
{ \
  numeration::Begin< INTEGRAL >, \
  numeration::increment::Traverse< INTEGRAL >, \
  numeration::To< INTEGRAL >, \
  numeration::To< INTEGRAL > \
}
#define NUMERATION_INCREMENT_FINITE_LINER(INTEGRAL, BEGINNING, ENDING) \
{ \
  numeration::FiniteBegin< INTEGRAL, BEGINNING, ENDING >, \
  numeration::increment::FiniteTraverse< INTEGRAL, BEGINNING, ENDING >, \
  numeration::FiniteTo< INTEGRAL, BEGINNING, ENDING >, \
  numeration::FiniteTo< INTEGRAL, BEGINNING, ENDING > \
}
#define NUMERATION_INCREMENT_TRANSPOSER(INTEGRAL) \
{ \
  numeration::Begins< INTEGRAL >, \
  numeration::increment::Traversable< INTEGRAL > \
}
#define NUMERATION_INCREMENT_FINITE_TRANSPOSER(INTEGRAL, BEGINNING, ENDING) \
{ \
  numeration::FiniteBegins< INTEGRAL, BEGINNING, ENDING >, \
  numeration::increment::FiniteTraversable< INTEGRAL, BEGINNING, ENDING > \
}
#define NUMERATION_INCREMENT_DIRECTION(INTEGRAL) \
{ \
  NUMERATION_INCREMENT_LINER(INTEGRAL), \
  NUMERATION_INCREMENT_TRANSPOSER(INTEGRAL) \
}
#define NUMERATION_INCREMENT_FINITE_DIRECTION(INTEGRAL, BEGINNING, ENDING) \
{ \
  NUMERATION_INCREMENT_FINITE_LINER(INTEGRAL, BEGINNING, ENDING), \
  NUMERATION_INCREMENT_FINITE_TRANSPOSER(INTEGRAL, BEGINNING, ENDING ) \
}
#define NUMERATION_DECREMENT_LINER(INTEGRAL) \
{ \
  numeration::Begin< INTEGRAL >, \
  numeration::decrement::Traverse< INTEGRAL >, \
  numeration::To< INTEGRAL >, \
  numeration::To< INTEGRAL > \
}
#define NUMERATION_DECREMENT_FINITE_LINER(INTEGRAL, BEGINNING, ENDING) \
{ \
  numeration::FiniteBegin< INTEGRAL, BEGINNING, ENDING >, \
  numeration::decrement::FiniteTraverse< INTEGRAL, BEGINNING, ENDING >, \
  numeration::FiniteTo< INTEGRAL, BEGINNING, ENDING >, \
  numeration::FiniteTo< INTEGRAL, BEGINNING, ENDING > \
}
#define NUMERATION_DECREMENT_TRANSPOSER(INTEGRAL) \
{ \
  numeration::Begins< INTEGRAL >, \
  numeration::decrement::Traversable< INTEGRAL > \
}
#define NUMERATION_DECREMENT_FINITE_TRANSPOSER(INTEGRAL, BEGINNING, ENDING) \
{ \
  numeration::FiniteBegins< INTEGRAL, BEGINNING, ENDING >, \
  numeration::decrement::FiniteTraversable< INTEGRAL, BEGINNING, ENDING > \
}
#define NUMERATION_DECREMENT_DIRECTION(INTEGRAL) \
{ \
  NUMERATION_DECREMENT_LINER(INTEGRAL), \
  NUMERATION_DECREMENT_TRANSPOSER(INTEGRAL) \
}
#define NUMERATION_DECREMENT_FINITE_DIRECTION(INTEGRAL, BEGINNING, ENDING) \
{ \
  NUMERATION_DECREMENT_FINITE_LINER(INTEGRAL, BEGINNING, ENDING), \
  NUMERATION_DECREMENT_FINITE_TRANSPOSER(INTEGRAL, BEGINNING, ENDING ) \
}
#define NUMERATION_AXIS(INTEGRAL) \
{ \
  NUMERATION_INCREMENT_DIRECTION(INTEGRAL), \
  NUMERATION_DECREMENT_DIRECTION(INTEGRAL) \
}
#define NUMERATION_FINITE_AXIS(INTEGRAL, BEGINNING, ENDING) \
{ \
  NUMERATION_INCREMENT_FINITE_DIRECTION(INTEGRAL, BEGINNING, ENDING), \
  NUMERATION_DECREMENT_FINITE_DIRECTION(INTEGRAL, BEGINNING, ENDING) \
}
#endif
