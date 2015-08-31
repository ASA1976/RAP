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
  using Lineal = trajection::Lineal< Junctional< Elemental >*, Junctional< Elemental >*, Elemental >;
  template <typename Elemental>
  using Transpositional = trajection::Transpositional< Junctional< Elemental >*, Junctional< Elemental >* >;
  template <typename Elemental>
  using Directional = trajection::Directional< Junctional< Elemental >*, Junctional< Elemental >*, Elemental >;
  template <typename Elemental>
  using Axial = trajection::Axial< Junctional< Elemental >*, Junctional< Elemental >*, Elemental >;

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
    return list != 0;
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
      return position->next != 0;
    }

    template <typename Elemental>
    const Lineal< Elemental > Liner = {
      Begin< Elemental >,
	  Traverse< Elemental >,
	  To< Elemental >,
	  From< Elemental >
    };
    template <typename Elemental>
    const Transpositional< Elemental > Transposer = {
      Begins< Elemental >,
	  Traversable< Elemental >
    };
    template <typename Elemental>
    const Directional< Elemental > Direction = {
      Liner< Elemental >,
	  Transposer< Elemental >
    };

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
      return position->previous != 0;
    }

    template <typename Elemental>
    const Lineal< Elemental > Liner = {
      Begin< Elemental >,
	  Traverse< Elemental >,
	  To< Elemental >,
	  From< Elemental >
    };
    template <typename Elemental>
    const Transpositional< Elemental > Transposer = {
      Begins< Elemental >,
	  Traversable< Elemental >
    };
    template <typename Elemental>
    const Directional< Elemental > Direction = {
      Liner< Elemental >,
	  Transposer< Elemental >
    };

  }

  template <typename Elemental>
  const Axial< Elemental > Axis = {
    increment::Direction< Elemental >,
	decrement::Direction< Elemental >
  };

}
#endif
