// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef NUMERATION_ASSOCIATION
#define NUMERATION_ASSOCIATION
#include "trajection.hpp"

namespace numeration {

  template <typename Integral>
  using Lineal = trajection::Lineal< const Integral, Integral, const Integral >;
  template <typename Integral>
  using Transpositional = trajection::Transpositional< const Integral, Integral >;
  template <typename Integral>
  using Directional = trajection::Directional< const Integral, Integral, const Integral >;
  template <typename Integral>
  using Axial = trajection::Axial< const Integral, Integral, const Integral >;

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

    template <typename Integral>
    const Lineal< Integral > Liner = {
      Begin< Integral >,
      Traverse< Integral >,
      To< Integral >,
      To< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Lineal< Integral > FiniteLiner = {
      FiniteBegin< Integral, beginning, ending >,
      FiniteTraverse< Integral, beginning, ending >,
      FiniteTo< Integral, beginning, ending >,
      FiniteTo< Integral, beginning, ending >
    };
    template <typename Integral>
    const Transpositional< Integral > Transposer = {
      Begins< Integral >,
      Traversable< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Transpositional< Integral > FiniteTransposer = {
      FiniteBegins< Integral, beginning, ending >,
      FiniteTraversable< Integral, beginning, ending >
    };
    template <typename Integral>
    const Directional< Integral > Direction = {
      Liner< Integral >,
      Transposer< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Directional< Integral > FiniteDirection = {
      FiniteLiner< Integral, beginning, ending >,
      FiniteTransposer< Integral, beginning, ending >
    };

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

    template <typename Integral>
    const Lineal< Integral > Liner = {
      Begin< Integral >,
      Traverse< Integral >,
      To< Integral >,
      To< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Lineal< Integral > FiniteLiner = {
      FiniteBegin< Integral, beginning, ending >,
      FiniteTraverse< Integral, beginning, ending >,
      FiniteTo< Integral, beginning, ending >,
      FiniteTo< Integral, beginning, ending >
    };
    template <typename Integral>
    const Transpositional< Integral > Transposer = {
      Begins< Integral >,
      Traversable< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Transpositional< Integral > FiniteTransposer = {
      FiniteBegins< Integral, beginning, ending >,
      FiniteTraversable< Integral, beginning, ending >
    };
    template <typename Integral>
    const Directional< Integral > Direction = {
      Liner< Integral >,
      Transposer< Integral >
    };
    template <typename Integral, Integral beginning, Integral ending>
    const Directional< Integral > FiniteDirection = {
      FiniteLiner< Integral, beginning, ending >,
      FiniteTransposer< Integral, beginning, ending >
    };

  }

  template <typename Integral>
  const Axial< Integral > Axis = {
    increment::Direction< Integral >,
    decrement::Direction< Integral >
  };
  template <typename Integral, Integral beginning, Integral ending>
  const Axial< Integral > FiniteAxis = {
    increment::FiniteDirection< Integral, beginning, ending >,
    decrement::FiniteDirection< Integral, beginning, ending >
  };

}
#endif
