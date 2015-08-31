// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef LOCALIZATION_ASSOCIATION
#define LOCALIZATION_ASSOCIATION
#include "trajection.hpp"

namespace localization {

  template <typename Indexical, typename Elemental>
  using Vectorial = trajection::Vectorial< Elemental *const, Indexical, Elemental >;
  template <typename Elemental>
  using Lineal = trajection::Lineal< Elemental *const, Elemental*, Elemental >;

  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< Elemental > To(Elemental *const &pointer, const Indexical &index)
  {
    trajection::Referential< Elemental > referral = {pointer[index]};
    return referral;
  }
  template <typename Indexical, typename Elemental>
  static inline trajection::Referential< const Elemental > From(Elemental *const &pointer, const Indexical &index)
  {
    trajection::Referential< const Elemental > referral = {pointer[index]};
    return referral;
  }
  template <typename Elemental>
  static inline void Begin(Elemental *const &pointer, Elemental* &point)
  {
    point = pointer;
  }
  template <typename Elemental>
  static inline trajection::Referential< Elemental > To(Elemental *const &point)
  {
    trajection::Referential< Elemental > referral = {*point};
    return referral;
  }
  template <typename Elemental>
  static inline trajection::Referential< const Elemental > From(Elemental *const &point)
  {
    trajection::Referential< const Elemental > referral = {*point};
    return referral;
  }

  namespace increment {

    template <typename Elemental>
    static inline void Traverse(Elemental* &point)
    {
      point++;
    }

    template <typename Elemental>
    const Lineal< Elemental > Liner = {
      Begin< Elemental >,
      Traverse< Elemental >,
      To< Elemental >,
      From< Elemental >
    };

  }

  namespace decrement {

    template <typename Elemental>
    static inline void Traverse(Elemental* &point)
    {
      point--;
    }

    template <typename Elemental>
    const Lineal< Elemental > Liner = {
      Begin< Elemental >,
      Traverse< Elemental >,
      To< Elemental >,
      From< Elemental >
    };

  }

  template <typename Indexical, typename Elemental>
  const Vectorial< Indexical, Elemental > Vector = {
    To< Indexical, Elemental >,
    From< Indexical, Elemental >
  };

}
#endif
