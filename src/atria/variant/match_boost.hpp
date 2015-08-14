// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/variant/variant_types_boost.hpp>
#include <atria/variant/visitor.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant/apply_visitor.hpp>
ABL_RESTORE_WARNINGS
#include <utility>

namespace atria {
namespace variant {

namespace detail {

template <typename T>
struct is_boost_variant : std::is_base_of<
  meta::unpack<boost::variant, variant_types_t<estd::decay_t<T> > >,
  estd::decay_t<T> >
{};

} // namespace detail

/*!
 * Destructure a `boost::variant` with a given set of functions.  This
 * uses C++ function overload rules to pick the right function.  If
 * the passed in variant is a non-const l-value, alternatives can
 * destructure by reference and mutate the variant in place.
 *
 * @note This method can destructure either instances of
 *       `boost::variant<...>` or for subclasses of
 *       `boost::variant<Ts...>` for which `meta::variant_types` is
 *       defined to return `meta::pack<Ts...>`.
 *
 * @note `boost::variant` does not support destructuring by r-value
 *       reference, and so doesn't this.
 *
 * @return The return type is deduced as the `meta::common_type<>` of
 *         the result of destructuring all alternatives in the variant.
 */
template <typename VariantT, typename ...FnTs>
auto match(VariantT& variant, FnTs&& ...fns)
  -> estd::enable_if_t<
  detail::is_boost_variant<estd::decay_t<VariantT> >{},
    visitor_result_of_t<
      detail::visitor_impl<FnTs...>,
      variant_types_t<VariantT&> > >
{
  auto visit = visitor_for<VariantT&>(std::forward<FnTs>(fns)...);
  return boost::apply_visitor(visit, variant);
}

template <typename VariantT, typename ...FnTs>
auto match(const VariantT& variant, FnTs&& ...fns)
  -> estd::enable_if_t<
  detail::is_boost_variant<estd::decay_t<VariantT> >{},
    visitor_result_of_t<
      detail::visitor_impl<FnTs...>,
      variant_types_t<const VariantT&> > >
{
  auto visit = visitor_for<const VariantT&>(std::forward<FnTs>(fns)...);
  return boost::apply_visitor(visit, variant);
}

} // namespace variant
} // namespace atria
