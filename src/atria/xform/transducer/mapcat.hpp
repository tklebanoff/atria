// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/mapcat$1
 */
template <typename MappingT>
auto mapcat(MappingT&& mapping)
  -> ABL_DECLTYPE_RETURN(
    comp(
      cat,
      map(std::forward<MappingT>(mapping))))

} // namespace xform
} // namespace atria
