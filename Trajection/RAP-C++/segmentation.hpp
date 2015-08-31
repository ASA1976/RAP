// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef SEGMENTATION_ASSOCIATION
#define SEGMENTATION_ASSOCIATION
#include "trajection.hpp"

namespace segmentation {

  template <typename Indexical, typename Elemental>
  struct Segmental {
    Elemental* pointer;
    Indexical index;
  };

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

  }

}
#define SEGMENTATION_VECTOR(INDEXICAL, ELEMENTAL) \
{ \
  segmentation::To< INDEXICAL, ELEMENTAL >, \
  segmentation::From< INDEXICAL, ELEMENTAL > \
}
#define SEGMENTATION_SAFE_VECTOR(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::SafeTo< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::SafeFrom< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_LOCATOR(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::Contains< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_TRAVERSE(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_SAFE_VECTOR(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_LOCATOR(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_INCREMENT_LINER(INDEXICAL, ELEMENTAL) \
{ \
  segmentation::increment::Begin< INDEXICAL, ELEMENTAL >, \
  segmentation::increment::Traverse< INDEXICAL, ELEMENTAL >, \
  segmentation::To< INDEXICAL, ELEMENTAL >, \
  segmentation::From< INDEXICAL, ELEMENTAL > \
}
#define SEGMENTATION_INCREMENT_SAFE_LINER(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::increment::BeginSafely< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::increment::TraverseSafely< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::SafeTo< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::SafeFrom< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_INCREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::Begins< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::increment::Traversable< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_INCREMENT_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_INCREMENT_LINER(INDEXICAL, ELEMENTAL), \
  SEGMENTATION_INCREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_INCREMENT_SAFE_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_INCREMENT_SAFE_LINER(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_INCREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_DECREMENT_LINER(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::decrement::Begin< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::decrement::Traverse< INDEXICAL, ELEMENTAL >, \
  segmentation::To< INDEXICAL, ELEMENTAL >, \
  segmentation::From< INDEXICAL, ELEMENTAL > \
}
#define SEGMENTATION_DECREMENT_SAFE_LINER(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::decrement::BeginSafely< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::decrement::TraverseSafely< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::SafeTo< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::SafeFrom< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_DECREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  segmentation::Begins< INDEXICAL, ELEMENTAL, LENGTH >, \
  segmentation::decrement::Traversable< INDEXICAL, ELEMENTAL, LENGTH > \
}
#define SEGMENTATION_DECREMENT_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_DECREMENT_LINER(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_DECREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_DECREMENT_SAFE_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_DECREMENT_SAFE_LINER(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_DECREMENT_TRANSPOSER(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_AXIS(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_INCREMENT_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_DECREMENT_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
}
#define SEGMENTATION_SAFE_AXIS(INDEXICAL, ELEMENTAL, LENGTH) \
{ \
  SEGMENTATION_INCREMENT_SAFE_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH), \
  SEGMENTATION_DECREMENT_SAFE_DIRECTION(INDEXICAL, ELEMENTAL, LENGTH) \
}
#endif
