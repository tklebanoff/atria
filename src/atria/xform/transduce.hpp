// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/reduce.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/transduce
 */
template <typename XformT,
          typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto transduce(XformT&& xform, ReducingFnT&& step,
               StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  return reduce(
    xform(std::forward<ReducingFnT>(step)),
    std::forward<StateT>(state),
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
