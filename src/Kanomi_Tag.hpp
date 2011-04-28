#ifndef KANOMI_TAG_HPP_
#define KANOMI_TAG_HPP_

namespace kanomi {

template <class FIELD, class STENCIL>
struct Tag {
  typedef FIELD FieldT;
  typedef STENCIL StencilT;
};

} // namespace kanomi

#endif /* KANOMI_TAG_HPP_ */
