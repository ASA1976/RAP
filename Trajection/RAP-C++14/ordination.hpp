// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef ORDINATION_ASSOCIATION
#define ORDINATION_ASSOCIATION
#include "trajection.hpp"

namespace ordination {

  template <typename Indexical, typename Elemental>
  struct Ordinal {
    Elemental *array;
    Indexical index;
  };
  template <typename Indexical, typename Elemental, Indexical length>
  using Vectorial = trajection::Vectorial< Elemental[length], Indexical, Elemental >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Locational = trajection::Locational< Elemental[length], Indexical >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Traversal = trajection::Traversal< Elemental[length], Indexical, Elemental >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Lineal = trajection::Lineal< Elemental[length], Ordinal< Indexical, Elemental >, Elemental >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Transpositional = trajection::Transpositional< Elemental[length], Ordinal< Indexical, Elemental > >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Directional = trajection::Directional< Elemental[length], Ordinal< Indexical, Elemental >, Elemental >;
  template <typename Indexical, typename Elemental, Indexical length>
  using Axial = trajection::Axial< Elemental[length], Ordinal< Indexical, Elemental >, Elemental >;

  template <typename Indexical, typename Elemental, Indexical length>
  static inline bool Contains(const Elemental(&array)[length], const Indexical &index)
  {
    if (index < 0) {
      if (index < 0 - length)
        return false;
    } else {
      if (index >= length)
        return false;
    }
    return true;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< Elemental > To(Elemental(&array)[length], const Indexical &index)
  {
    trajection::Referential< Elemental > referral = {array[index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< Elemental > SafeTo(Elemental(&array)[length], const Indexical &index)
  {
    if (!Contains(array, index))
      throw index;
    return To(array, index);
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< const Elemental > From(const Elemental(&array)[length], const Indexical &index)
  {
    trajection::Referential< const Elemental > referral = {array[index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< const Elemental > SafeFrom(const Elemental(&array)[length], const Indexical &index)
  {
    if (!Contains(array, index))
      throw index;
    return From(array, index);
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< Elemental > To(const Ordinal< Indexical, Elemental > &position)
  {
    trajection::Referential< Elemental > referral = {position.array[position.index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< Elemental > SafeTo(const Ordinal< Indexical, Elemental > &position)
  {
    if (position.index >= length)
      throw position.index;
    return To(position);
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< const Elemental > From(const Ordinal< Indexical, Elemental > &position)
  {
    trajection::Referential< const Elemental > referral = {position.array[position.index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< const Elemental > SafeFrom(const Ordinal< Indexical, Elemental > &position)
  {
    if (position.index >= length)
      throw position.index;
    return From(position);
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline bool Begins(const Elemental(&array)[length])
  {
    return length > 0;
  }

  namespace increment {

    template <typename Indexical, typename Elemental, Indexical length>
    static inline void Begin(Elemental(&array)[length], Ordinal< Indexical, Elemental > &position)
    {
      position.array = array;
      position.index = 0;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline bool Traversable(const Ordinal< Indexical, Elemental > &position)
    {
      return position.index >= 0 && position.index < length - 1;
    }
    template <typename Indexical, typename Elemental>
    static inline void Traverse(Ordinal< Indexical, Elemental > &position)
    {
      position.index++;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void TraverseSafely(Ordinal< Indexical, Elemental > &position)
    {
      if (position.index >= length)
        throw position.index;
      Traverse(position);
    }

    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental, length > Liner = {
      Begin< Indexical, Elemental, length >,
	  Traverse< Indexical, Elemental >,
	  To< Indexical, Elemental >,
	  From< Indexical, Elemental >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental, length > SafeLiner = {
      Begin< Indexical, Elemental, length >,
	  TraverseSafely< Indexical, Elemental, length >,
	  SafeTo< Indexical, Elemental, length >,
	  SafeFrom< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Transpositional< Indexical, Elemental, length > Transposer = {
      Begins< Indexical, Elemental, length >,
      Traversable< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental, length > Direction = {
      Liner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental, length > SafeDirection = {
      SafeLiner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };

  }

  namespace decrement {

    template <typename Indexical, typename Elemental, Indexical length>
    static inline void Begin(Elemental(&array)[length], Ordinal< Indexical, Elemental > &position)
    {
      position.array = array;
      position.index = length - 1;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline bool Traversable(const Ordinal< Indexical, Elemental > &position)
    {
      return position.index > 0 && position.index < length;
    }
    template <typename Indexical, typename Elemental>
    static inline void Traverse(Ordinal< Indexical, Elemental > &position)
    {
      position.index--;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void TraverseSafely(Ordinal< Indexical, Elemental > &position)
    {
      if (!Traversable< Indexical, Elemental, length >(position))
        throw position.index;
      Traverse(position);
    }

    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental, length > Liner = {
      Begin< Indexical, Elemental, length >,
      Traverse< Indexical, Elemental >,
      To< Indexical, Elemental >,
      From< Indexical, Elemental >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental, length > SafeLiner = {
      Begin< Indexical, Elemental, length >,
      TraverseSafely< Indexical, Elemental, length >,
      SafeTo< Indexical, Elemental, length >,
      SafeFrom< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Transpositional< Indexical, Elemental, length > Transposer = {
      Begins< Indexical, Elemental, length >,
      Traversable< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental, length > Direction = {
      Liner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental, length > SafeDirection = {
      SafeLiner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };

  }

  template <typename Indexical, typename Elemental, Indexical length>
  const Vectorial< Indexical, Elemental, length > Vector = {
    To< Indexical, Elemental, length >,
    From< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Vectorial<Indexical, Elemental, length > SafeVector = {
    SafeTo< Indexical, Elemental, length >,
    SafeFrom< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Locational< Indexical, Elemental, length > Locator = {
    Contains< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Traversal< Indexical, Elemental, length > Traverse = {
    SafeVector< Indexical, Elemental, length >,
    Locator< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Axial< Indexical, Elemental, length > Axis = {
    increment::Direction< Indexical, Elemental, length >,
    decrement::Direction< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Axial< Indexical, Elemental, length > SafeAxis = {
    increment::SafeDirection< Indexical, Elemental, length >,
    decrement::SafeDirection< Indexical, Elemental, length >
  };

}
#endif
