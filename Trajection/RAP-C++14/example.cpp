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
template <typename Integral>
using Numeral = numeration::Axial< Integral >;

const char *const TitleFormat = "%s; %s trajection: ";

template <typename Indexical, typename Elemental, Indexical length>
static bool TestNumerator(const Numeral< Indexical > &numerator, const Elemental(&values)[length])
{
  const auto &increment = numerator.increment;
  const auto &decrement = numerator.decrement;
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
  const Numeral< Indexical > &numerator,
  const Endemical (&values)[length]
) {
  const auto &counter = numerator.increment.liner;
  const auto &account = numerator.increment.transposer;
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
  const Numeral< Indexical > &numerator,
  const Endemical (&values)[length]
) {
  const auto &counter = numerator.increment.liner;
  const auto &account = numerator.increment.transposer;
  const auto &vector = traverse.vector;
  const auto &locator = traverse.locator;
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
  const Numeral< Indexical > &numerator,
  const Endemical (&values)[length]
) {
  const auto &counter = numerator.increment.liner;
  const auto &account = numerator.increment.transposer;
  Positional position;
  Indexical count;
  liner.begin(space, position);
  for (counter.begin(0, count); account.traversable(count); counter.traverse(count)) {
    liner.to(position).at = values[count];
    if (liner.from(position).at != values[count])
      return false;
    if (count < length - 1)
      liner.traverse(position);
  }
  return true;
}
template <typename Spatial, typename Positional, typename Endemical, typename Indexical, Indexical length>
static bool TestDirection(
  const Directional< Spatial, Positional, Endemical > &direction,
  Spatial &space,
  const Numeral< Indexical > &numerator,
  const Endemical (&values)[length]
) {
  const auto &counter = numerator.increment.liner;
  const auto &account = numerator.increment.transposer;
  const auto &liner = direction.liner;
  const auto &transposer = direction.transposer;
  Positional position;
  Indexical count;
  if (!transposer.begins(space))
    return false;
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
  if (transposer.traversable(position))
    return false;
  return true;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestPointer(const Numeral< Indexical > &numerator, const Elemental (&values)[length])
{
  static const auto &vector = localization::Vector< Indexical, Elemental >;
  static const auto &increment = localization::increment::Liner< Elemental >;
  static const auto &decrement = localization::decrement::Liner< Elemental >;
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
  if(TestLiner(increment, first, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Pointer", "decreasing lineal");
  if (TestLiner(decrement, last, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  delete first;
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestSegment(const Numeral< Indexical > &numerator, const Elemental (&values)[length])
{
  static const auto &traverse = segmentation::Traverse< Indexical, Elemental, length >;
  static const auto &increment = segmentation::increment::Direction< Indexical, Elemental, length >;
  static const auto &decrement = segmentation::decrement::Direction< Indexical, Elemental, length >;
  static const auto &safe_increment = segmentation::increment::SafeDirection< Indexical, Elemental, length >;
  static const auto &safe_decrement = segmentation::decrement::SafeDirection< Indexical, Elemental, length >;
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
  if (TestDirection(increment, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "fast decreasing directional");
  if (TestDirection(decrement, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "safe increasing directional");
  if (TestDirection(safe_increment, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Segment", "safe decreasing directional");
  if (TestDirection(safe_decrement, pointer, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  delete pointer;
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestArray(const Numeral< Indexical > &numerator, const Elemental (&values)[length])
{
  static const auto &traverse = ordination::Traverse< Indexical, Elemental, length >;
  static const auto &increment = ordination::increment::Direction< Indexical, Elemental, length >;
  static const auto &decrement = ordination::decrement::Direction< Indexical, Elemental, length >;
  static const auto &safe_increment = ordination::increment::Direction< Indexical, Elemental, length >;
  static const auto &safe_decrement = ordination::decrement::Direction< Indexical, Elemental, length >;
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
  if (TestDirection(increment, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "fast decreasing directional");
  if (TestDirection(decrement, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Array", "safe increasing directional");
  if (TestDirection(safe_increment, array, numerator, values)) {
    puts("pass");
  } else {
	puts("fail");
	result = false;
  }
  printf(TitleFormat, "Array", "safe decreasing directional");
  if (TestDirection(safe_decrement, array, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  return result;
}
template <typename Indexical, typename Elemental, Indexical length>
static bool TestLinkedList(const Numeral< Indexical > &numerator, const Elemental (&values)[length])
{
  using junction::Junctional;
  const auto &counter = numerator.increment.liner;
  const auto &account = numerator.increment.transposer;
  const auto &increment = junction::increment::Direction< Elemental >;
  const auto &decrement = junction::decrement::Direction< Elemental >;
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
  if (TestDirection(increment, first, numerator, values)) {
    puts("pass");
  } else {
    puts("fail");
    result = false;
  }
  printf(TitleFormat, "Linked List", "decreasing directional");
  if (TestDirection(decrement, last, numerator, values)) {
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
  using IndexIntegral = int;
  using Textual = char;
  static const IndexIntegral count = 3;
  static const auto &numerator = numeration::FiniteAxis< IndexIntegral, 0, count >;
  static const auto &axis = ordination::Axis< IndexIntegral, const Textual, count >;
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
