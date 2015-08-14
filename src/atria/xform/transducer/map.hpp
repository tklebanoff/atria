// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/meta/utils.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto map = [](auto mapping) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      return step(ABL_FORWARD(s), mapping(ABL_FORWARD(is)...));
    };
  };
};

#else // ABL_CXX14

namespace detail {

struct map_rf_gen
{
  template <typename ReducingFnT,
            typename MappingT>
  struct apply
  {
    ReducingFnT step;
    MappingT mapping;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        step(std::forward<State>(s),
             mapping(std::forward<Inputs>(is)...)))
  };
};

} // namespace detail

template <typename T>
using map_t = transducer_impl<detail::map_rf_gen, T>;

/*!
 * Similar to clojure.core/map$1
 */
template <typename MappingT>
auto map(MappingT&& mapping)
  -> map_t<estd::decay_t<MappingT> >
{
  return map_t<estd::decay_t<MappingT> > {
    std::forward<MappingT>(mapping) };
}

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
