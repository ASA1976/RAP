// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef SEGMENTATION_ASSOCIATION
#define SEGMENTATION_ASSOCIATION
#include "trajection.hpp"

namespace segmentation {

  template <typename Indexical, typename Elemental>
  struct Segmental {
    Elemental *pointer;
    Indexical index;
  };
  template <typename Indexical, typename Elemental>
  using Vectorial = trajection::Vectorial< Elemental *const, Indexical, Elemental >;
  template <typename Indexical, typename Elemental>
  using Locational = trajection::Locational< Elemental *const, Indexical >;
  template <typename Indexical, typename Elemental>
  using Traversal = trajection::Traversal< Elemental *const, Indexical, Elemental >;
  template <typename Indexical, typename Elemental>
  using Lineal = trajection::Lineal< Elemental *const, Segmental< Indexical, Elemental >, Elemental >;
  template <typename Indexical, typename Elemental>
  using Transpositional = trajection::Transpositional< Elemental *const, Segmental< Indexical, Elemental > >;
  template <typename Indexical, typename Elemental>
  using Directional = trajection::Directional< Elemental *const, Segmental< Indexical, Elemental >, Elemental >;
  template <typename Indexical, typename Elemental>
  using Axial = trajection::Axial< Elemental *const, Segmental< Indexical, Elemental >, Elemental >;

  template <typename Indexical, typename Elemental, Indexical length>
  static inline bool Contains(Elemental *const &pointer, const Indexical &index)
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
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< Elemental > To(Elemental *const &pointer, const Indexical &index)
  {
    trajection::Referential< Elemental > referral = {pointer[index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< Elemental > SafeTo(Elemental *const &pointer, const Indexical &index)
  {
    if (!Contains< Indexical, Elemental, length >(pointer, index))
      throw index;
    return To(pointer, index);
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< const Elemental > From(Elemental *const &pointer, const Indexical &index)
  {
    trajection::Referential< const Elemental > referral = {pointer[index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< const Elemental > SafeFrom(Elemental *const &pointer, const Indexical &index)
  {
    if (!Contains< Indexical, Elemental, length >(pointer, index))
      throw index;
    return From(pointer, index);
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< Elemental > To(const Segmental< Indexical, Elemental > &position)
  {
    trajection::Referential< Elemental > referral = {position.pointer[position.index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< Elemental > SafeTo(const Segmental< Indexical, Elemental > &position)
  {
    if (position.index < 0 || position.index >= length)
      throw position.index;
    return To(position);
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< const Elemental > From(const Segmental< Indexical, Elemental > &position)
  {
    trajection::Referential< const Elemental > referral = {position.pointer[position.index]};
    return referral;
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline trajection::Referential< const Elemental > SafeFrom(const Segmental< Indexical, Elemental > &position)
  {
    if (position.index < 0 || position.index >= length)
      throw position.index;
    return From(position);
  }
  template <typename Indexical, typename Elemental, Indexical length>
  static inline bool Begins(Elemental *const &pointer)
  {
    return pointer != 0 && length > 0;
  }

  namespace increment {

    template <typename Indexical, typename Elemental>
    static inline void Begin(Elemental *const &pointer, Segmental< Indexical, Elemental > &position)
    {
      position.pointer = pointer;
      position.index = 0;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void BeginSafely(Elemental *const &pointer, Segmental< Indexical, Elemental > &position)
    {
      if (!pointer)
        throw pointer;
      if (length < 1)
        throw length;
      Begin(pointer, position);
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline bool Traversable(const Segmental< Indexical, Elemental > &position)
    {
      return position.index >= 0 && position.index < length - 1;
    }
    template <typename Indexical, typename Elemental>
    static inline void Traverse(Segmental< Indexical, Elemental > &position)
    {
      position.index++;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void TraverseSafely(Segmental< Indexical, Elemental > &position)
    {
      if (!Traversable< Indexical, Elemental, length >(position))
        throw position.index;
      Traverse(position);
    }

    template <typename Indexical, typename Elemental>
    const Lineal< Indexical, Elemental > Liner = {
      Begin< Indexical, Elemental >,
      Traverse< Indexical, Elemental >,
      To< Indexical, Elemental >,
      From< Indexical, Elemental >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental > SafeLiner = {
      BeginSafely< Indexical, Elemental, length >,
      TraverseSafely< Indexical, Elemental, length >,
      SafeTo< Indexical, Elemental, length >,
      SafeFrom< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Transpositional< Indexical, Elemental > Transposer = {
      Begins< Indexical, Elemental, length >,
      Traversable< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental > Direction = {
      Liner< Indexical, Elemental >,
      Transposer< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental > SafeDirection = {
      SafeLiner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };

  }

  namespace decrement {

    template <typename Indexical, typename Elemental, Indexical length>
    static inline void Begin(Elemental *const &pointer, Segmental< Indexical, Elemental > &position)
    {
      position.pointer = pointer;
      position.index = length - 1;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void BeginSafely(Elemental *const &pointer, Segmental< Indexical, Elemental > &position)
    {
      if (!pointer)
        throw pointer;
      if (length < 1)
        throw length;
      Begin< Indexical, Elemental, length>(pointer, position);
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline bool Traversable(const Segmental< Indexical, Elemental > &position)
    {
      return position.index > 0 && position.index < length;
    }
    template <typename Indexical, typename Elemental>
    static inline void Traverse(Segmental< Indexical, Elemental > &position)
    {
      position.index--;
    }
    template <typename Indexical, typename Elemental, Indexical length>
    static inline void TraverseSafely(Segmental< Indexical, Elemental > &position)
    {
      if (!Traversable< Indexical, Elemental, length >(position))
        throw position.index;
      Traverse(position);
    }

    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental > Liner = {
      Begin< Indexical, Elemental, length >,
      Traverse< Indexical, Elemental >,
      To< Indexical, Elemental >,
      From< Indexical, Elemental >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Lineal< Indexical, Elemental > SafeLiner = {
      BeginSafely< Indexical, Elemental, length >,
      TraverseSafely< Indexical, Elemental, length >,
      SafeTo< Indexical, Elemental, length >,
      SafeFrom< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Transpositional< Indexical, Elemental > Transposer = {
      Begins< Indexical, Elemental, length >,
      Traversable< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental > Direction = {
      Liner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };
    template <typename Indexical, typename Elemental, Indexical length>
    const Directional< Indexical, Elemental > SafeDirection = {
      SafeLiner< Indexical, Elemental, length >,
      Transposer< Indexical, Elemental, length >
    };

  }

  template <typename Indexical, typename Elemental>
  const Vectorial< Indexical, Elemental > Vector = {
    To< Indexical, Elemental >,
    From< Indexical, Elemental >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Vectorial< Indexical, Elemental > SafeVector = {
    SafeTo< Indexical, Elemental, length >,
    SafeFrom< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Locational< Indexical, Elemental > Locator = {
    Contains< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Traversal< Indexical, Elemental > Traverse = {
    SafeVector< Indexical, Elemental, length >,
    Locator< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Axial< Indexical, Elemental > Axis = {
    increment::Direction< Indexical, Elemental, length >,
    decrement::Direction< Indexical, Elemental, length >
  };
  template <typename Indexical, typename Elemental, Indexical length>
  const Axial< Indexical, Elemental > SafeAxis = {
    increment::SafeDirection< Indexical, Elemental, length >,
    decrement::SafeDirection< Indexical, Elemental, length >
  };

}
#endif
