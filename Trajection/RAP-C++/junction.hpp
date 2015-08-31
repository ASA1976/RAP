// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef JUNCTION_ASSOCIATION
#define JUNCTION_ASSOCIATION
#include "trajection.hpp"

namespace junction {

  template <typename Elemental>
  struct Junctional {
    Junctional< Elemental > *previous, *next;
    Elemental element;
  };

  template <typename Elemental>
  static inline trajection::Referential< Elemental > To(Junctional< Elemental > *const &position)
  {
    trajection::Referential< Elemental > referral = {position->element};
    return referral;
  }
  template <typename Elemental>
  static inline trajection::Referential< const Elemental > From(Junctional< Elemental > *const &position)
  {
    trajection::Referential< const Elemental > referral = {position->element};
    return referral;
  }
  template <typename Elemental>
  static inline void Begin(Junctional< Elemental >* &list, Junctional< Elemental >* &position)
  {
    position = list;
  }
  template <typename Elemental>
  static inline bool Begins(Junctional< Elemental > *const &list)
  {
    return list;
  }

  namespace increment {

    template <typename Elemental>
    static inline void Traverse(Junctional< Elemental >* &position)
    {
      position = position->next;
    }
    template <typename Elemental>
    static inline bool Traversable(Junctional< Elemental > *const &position)
    {
      return position->next;
    }

  }

  namespace decrement {

    template <typename Elemental>
    static inline void Traverse(Junctional< Elemental >* &position)
    {
      position = position->previous;
    }
    template <typename Elemental>
    static inline bool Traversable(Junctional< Elemental > *const &position)
    {
      return position->previous;
    }

  }

}
#define JUNCTION_INCREMENT_LINER(ELEMENTAL) \
{ \
  junction::Begin< ELEMENTAL >, \
  junction::increment::Traverse< ELEMENTAL >, \
  junction::To< Elemental >, \
  junction::From< Elemental > \
}
#define JUNCTION_INCREMENT_TRANSPOSER(ELEMENTAL) \
{ \
  junction::Begins< Elemental >, \
  junction::increment::Traversable< Elemental > \
}
#define JUNCTION_INCREMENT_DIRECTION(ELEMENTAL) \
{ \
  JUNCTION_INCREMENT_LINER(ELEMENTAL), \
  JUNCTION_INCREMENT_TRANSPOSER(ELEMENTAL) \
}
#define JUNCTION_DECREMENT_LINER(ELEMENTAL) \
{ \
  junction::Begin< ELEMENTAL >, \
  junction::decrement::Traverse< ELEMENTAL >, \
  junction::To< Elemental >, \
  junction::From< Elemental > \
}
#define JUNCTION_DECREMENT_TRANSPOSER(ELEMENTAL) \
{ \
  junction::Begins< Elemental >, \
  junction::decrement::Traversable< Elemental > \
}
#define JUNCTION_DECREMENT_DIRECTION(ELEMENTAL) \
{ \
  JUNCTION_DECREMENT_LINER(ELEMENTAL), \
  JUNCTION_DECREMENT_TRANSPOSER(ELEMENTAL) \
}
#define JUNCTION_AXIS(ELEMENTAL) \
{ \
  JUNCTION_INCREMENT_DIRECTION(ELEMENTAL), \
  JUNCTION_DECREMENT_DIRECTION(ELEMENTAL) \
}
#endif
