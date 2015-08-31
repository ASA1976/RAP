// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef TRAJECTION_ASSOCIATION
#define TRAJECTION_ASSOCIATION

namespace trajection {

  template <typename Subjective>
  struct Referential {
    Subjective &at;
  };
  template <typename Spatial, typename Positional, typename Endemical>
  struct Vectorial {
    Referential< Endemical > (&to)(Spatial&, const Positional&);
    Referential< const Endemical > (&from)(const Spatial&, const Positional&);
  };
  template <typename Spatial, typename Positional>
  struct Locational {
    bool (&contains)(const Spatial&, const Positional&);
  };
  template <typename Spatial, typename Positional, typename Endemical>
  struct Traversal {
    const Vectorial< Spatial, Positional, Endemical > &vector;
    const Locational< Spatial, Positional > &locator;
  };
  template <typename Spatial, typename Positional, typename Endemical>
  struct Lineal {
    void (&begin)(Spatial&, Positional&);
    void (&traverse)(Positional&);
    Referential< Endemical > (&to)(const Positional&);
    Referential< const Endemical > (&from)(const Positional&);
  };
  template <typename Spatial, typename Positional>
  struct Transpositional {
    bool (&begins)(const Spatial&);
    bool (&traversable)(const Positional&);
  };
  template <typename Spatial, typename Positional, typename Endemical>
  struct Directional {
    const Lineal< Spatial, Positional, Endemical > &liner;
    const Transpositional< Spatial, Positional > &transposer;
  };
  template <typename Spatial, typename Positional, typename Endemical>
  struct Axial {
    const Directional< Spatial, Positional, Endemical > &increment, &decrement;
  };

}
#endif
