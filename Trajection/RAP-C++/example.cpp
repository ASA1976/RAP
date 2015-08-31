// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "numeration.hpp"
#include "localization.hpp"
#include "segmentation.hpp"
#include "ordination.hpp"
#include "junction.hpp"
#include <stdio.h>

using trajection::Vectorial;
using trajection::Traversal;
using trajection::Lineal;
using trajection::Directional;
using trajection::Axial;

const char *const TitleFormat = "%s; %s trajection: ";

template <typename Indexical, typename Elemental, Indexical length>
static bool TestNumerator(
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Elemental(&values)[length]
) {
  using trajection::Transpositional;
  typedef Directional< const Indexical, Indexical, const Indexical > IndexDirectional;
  const IndexDirectional
    &increment = numerator.increment,
    &decrement = numerator.decrement;
  Indexical position, count;
  printf(TitleFormat, "Numerator", "axial");
  count = 0;
  if (!increment.transposer.begins(length)) {
    puts("fail");
    return false;
  }
  for (increment.liner.begin(0, position); increment.transposer.traversable(position); increment.liner.traverse(position)) {
    if (count >= length || position != count) {
      puts("fail");
      return false;
    }
    count++;
  }
  if (position != count || position != length) {
	puts("fail");
    return false;
  }
  if (!decrement.transposer.begins(length)) {
    puts("fail");
    return false;
  }
  for (decrement.liner.begin(length, position); decrement.transposer.traversable(position); decrement.liner.traverse(position)) {
    if (count > length || position != count) {
      puts("fail");
      return false;
    }
    count--;
  }
  if (position != count || position < 0) {
	puts("fail");
    return false;
  }
  puts("pass");
  return true;
}
template <typename Spatial, typename Indexical, typename Endemical, Indexical length>
static bool TestVector(
  const Vectorial< Spatial, Indexical, Endemical > &vector,
  Spatial &space,
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Endemical (&values)[length]
) {
  using trajection::Transpositional;
  typedef Lineal< const Indexical, Indexical, const Indexical > IndexLineal;
  typedef Transpositional< const Indexical, Indexical > IndexTranspositional;
  const IndexLineal &counter = numerator.increment.liner;
  const IndexTranspositional &account = numerator.increment.transposer;
  Indexical count;
  for (counter.begin(0, count); account.traversable(count); counter.traverse(count)) {
    vector.to(space, count).at = values[count];
    if (vector.from(space, count).at != values[count])
      return false;
  }
  return true;
}
template <typename Spatial, typename Indexical, typename Endemical, Indexical length>
static bool TestTraverse(
  const Traversal< Spatial, Indexical, Endemical > &traverse,
  Spatial &space,
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Endemical (&values)[length]
) {
  using trajection::Transpositional;
  using trajection::Locational;
  typedef Lineal< const Indexical, Indexical, const Indexical > IndexLineal;
  typedef Transpositional< const Indexical, Indexical > IndexTranspositional;
  typedef Vectorial< Spatial, Indexical, Endemical > TraverseVectorial;
  typedef Locational< Spatial, Indexical > TraverseLocational;
  const IndexLineal &counter = numerator.increment.liner;
  const IndexTranspositional &account = numerator.increment.transposer;
  const TraverseVectorial &vector = traverse.vector;
  const TraverseLocational &locator = traverse.locator;
  Indexical count;
  for (counter.begin(0, count); account.traversable(count); counter.traverse(count)) {
    if (!locator.contains(space, count))
      return false;
    vector.to(space, count).at = values[count];
    if (vector.from(space, count).at != values[count])
      return false;
  }
  if (locator.contains(space, count))
    return false;
  return true;
}
template <typename Spatial, typename Positional, typename Endemical, typename Indexical, Indexical length>
static bool TestLiner(
  const Lineal< Spatial, Positional, Endemical > &liner,
  Spatial &space,
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Endemical (&values)[length]
) {
  using trajection::Transpositional;
  typedef Lineal< const Indexical, Indexical, const Indexical > IndexLineal;
  typedef Transpositional< const Indexical, Indexical > IndexTranspositional;
  const IndexLineal &counter = numerator.increment.liner;
  const IndexTranspositional &account = numerator.increment.transposer;
  Positional position;
  Indexical count;
  liner.begin(space, position);
  for (counter.begin(0, count); account.traversable(count); counter.traverse(count)) {
    liner.to(position).at = values[count];
    if (liner.from(position).at != values[count])
      return false;
    liner.traverse(position);
  }
  return true;
}
template <typename Spatial, typename Positional, typename Endemical, typename Indexical, Indexical length>
static bool TestDirection(
  const Directional< Spatial, Positional, Endemical > &direction,
  Spatial &space,
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Endemical (&values)[length]
) {
  using trajection::Transpositional;
  typedef Lineal< const Indexical, Indexical, const Indexical > IndexLineal;
  typedef Transpositional< const Indexical, Indexical > IndexTranspositional;
  typedef Lineal< Spatial, Positional, Endemical > DirectionLineal;
  typedef Transpositional< Spatial, Positional > DirectionTranspositional;
  const IndexLineal &counter = numerator.increment.liner;
  const IndexTranspositional &account = numerator.increment.transposer;
  const DirectionLineal &liner = direction.liner;
  const DirectionTranspositional &transposer = direction.transposer;
  Positional position;
  Indexical count;
  if (!transposer.begins(space)) {
    return false;
  }
  liner.begin(space, position);
  for (counter.begin(0, count); account.traversable(count); counter.traverse(count)) {
    liner.to(position).at = values[count];
    if (liner.from(position).at != values[count])
      return false;
    if (count < length - 1) {
      if (!transposer.traversable(position))
        return false;
      liner.traverse(position);
    }
  }
  if (transposer.traversable(position)) {
    return false;
  }
  return true;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestPointer(
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Elemental (&values)[length]
) {
  typedef Vectorial< Elemental *const, Indexical, Elemental > LocalVector;
  typedef Lineal< Elemental *const, Elemental*, Elemental > LocalLineal;
  static const LocalVector vector = LOCALIZATION_VECTOR(Indexical, Elemental);
  static const LocalLineal
    increment = LOCALIZATION_INCREMENT_LINER(Elemental),
    decremental = LOCALIZATION_DECREMENT_LINER(Elemental);
  Elemental *const first = new Elemental[length], *const last = first + length - 1;
  bool result;
  result = true;
  printf(TitleFormat, "Pointer", "vectorial");
  if (TestVector(vector, first, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Pointer", "increasing lineal");
  if (TestLiner(increment, first, numerator, values)) {
    puts ("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Pointer", "decreasing lineal");
  if (TestLiner(decremental, last, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  delete first;
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestSegment(
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Elemental (&values)[length]
) {
  using segmentation::Segmental;
  typedef Traversal< Elemental *const, Indexical, Elemental > SegmentTraversal;
  typedef Axial< Elemental *const, Segmental< Indexical, Elemental >, Elemental > SegmentAxial;
  static const SegmentTraversal traverse = SEGMENTATION_TRAVERSE(Indexical, Elemental, length);
  static const SegmentAxial
    fast = SEGMENTATION_AXIS(Indexical, Elemental, length),
    safe = SEGMENTATION_SAFE_AXIS(Indexical, Elemental, length);
  Elemental *const pointer = new Elemental[length];
  bool result;
  result = true;
  printf(TitleFormat, "Segment", "traversal");
  if (TestTraverse(traverse, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "fast increasing directional");
  if (TestDirection(fast.increment, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "fast decreasing directional");
  if (TestDirection(fast.decrement, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "safe increasing directional");
  if (TestDirection(safe.increment, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "safe decreasing directional");
  if (TestDirection(safe.decrement, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  delete pointer;
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestArray(
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Elemental (&values)[length]
) {
  using ordination::Ordinal;
  typedef Traversal< Elemental[length], Indexical, Elemental > OrdonnanceTraversal;
  typedef Axial< Elemental[length], Ordinal< Indexical, Elemental >, Elemental > OrdonnanceAxial;
  static const OrdonnanceTraversal traverse = ORDINATION_TRAVERSE(Indexical, Elemental, length);
  static const OrdonnanceAxial
    fast = ORDINATION_AXIS(Indexical, Elemental, length),
    safe = ORDINATION_SAFE_AXIS(Indexical, Elemental, length);
  Elemental array[length];
  bool result;
  result = true;
  printf(TitleFormat, "Array", "traversal");
  if (TestTraverse(traverse, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "fast increasing directional");
  if (TestDirection(fast.increment, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "fast decreasing directional");
  if (TestDirection(fast.decrement, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "safe increasing directional");
  if (TestDirection(safe.increment, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "safe decreasing directional");
  if (TestDirection(safe.decrement, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestLinkedList(
  const Axial< const Indexical, Indexical, const Indexical > &numerator,
  const Elemental (&values)[length]
) {
  using trajection::Transpositional;
  using junction::Junctional;
  typedef Axial< Junctional< Elemental >*, Junctional< Elemental >*, Elemental > JunctionAxial;
  typedef Lineal< const Indexical, Indexical, const Indexical > IndexLineal;
  typedef Transpositional< const Indexical, Indexical > IndexTranspositional;
  static const JunctionAxial axis = JUNCTION_AXIS(Elemental);
  const IndexLineal &counter = numerator.increment.liner;
  const IndexTranspositional &account = numerator.increment.transposer;
  Junctional< Elemental > *first, *last;
  Indexical count;
  bool result;
  result = true;
  first = new Junctional< Elemental >;
  first->previous = 0;
  last = first;
  for (counter.begin(1, count); account.traversable(count); counter.traverse(count)) {
    last->next = new Junctional< Elemental >;
    last->next->previous = last;
    last = last->next;
  }
  last->next = 0;
  printf(TitleFormat, "Linked List", "increasing directional");
  if (TestDirection(axis.increment, first, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Linked List", "decreasing directional");
  if (TestDirection(axis.decrement, last, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  while (last) {
    last = first->next;
    delete first;
    first = last;
  }
  return result;
}
int main()
{
  using ordination::Ordinal;
  typedef int IndexIntegral;
  typedef char Textual;
  static const IndexIntegral count = 3;
  typedef Axial< const IndexIntegral, IndexIntegral, const IndexIntegral > IndexAxial;
  typedef Axial< const Textual[count], Ordinal< IndexIntegral, const Textual >, const Textual > TextAxial;
  static const IndexAxial numerator = NUMERATION_FINITE_AXIS(IndexIntegral, 0, count);
  static const TextAxial axis = ORDINATION_AXIS(IndexIntegral, const Textual, count);
  static const Textual values[count] = {'R', 'A', 'P'};
  Ordinal< IndexIntegral, const Textual > ordonnance;
  bool passed, more;
  if (TestNumerator(numerator, values)) {
    TestPointer(numerator, values);
    TestSegment(numerator, values);
    passed = TestArray(numerator, values);
    TestLinkedList(numerator, values);
    if (passed) {
      printf(TitleFormat, "Textual Array", "cyclic axial");
      if (more = axis.increment.transposer.begins(values)) {
        for (axis.increment.liner.begin(values, ordonnance); more; axis.increment.liner.traverse(ordonnance)) {
          printf("'%c'", axis.increment.liner.from(ordonnance).at);
          if (more = axis.increment.transposer.traversable(ordonnance))
            printf(", ");
        }
      }
      printf(", ");
      if (more = axis.decrement.transposer.begins(values)) {
        for (axis.decrement.liner.begin(values, ordonnance); more; axis.decrement.liner.traverse(ordonnance)) {
          printf("'%c'", axis.decrement.liner.from(ordonnance).at);
          if (more = axis.decrement.transposer.traversable(ordonnance))
            printf(", ");
        }
      }
      puts(".");
    }
  }
  return 0;
}
