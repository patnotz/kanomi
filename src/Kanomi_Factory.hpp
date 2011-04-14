#ifndef KANOMI_FACTORY_HPP_
#define KANOMI_FACTORY_HPP_

namespace kanomi {

template <class FIELD, class STENCIL> struct Factory;

template <class FIELD, class MODEL>
struct enabled {
  typedef enabled<FIELD,MODEL> type;
  typedef FIELD FieldT;
  typedef MODEL ModelT;
  static const bool value = false;
};

template <class FIELD>
struct enabled_pred {
  template <class IMPL>
  struct apply : enabled<FIELD,typename IMPL::ModelT> {};
};

#define ENABLE_MODEL(FIELD_TYPE, MODEL_TYPE) \
    template <> \
    struct enabled<FIELD_TYPE,MODEL_TYPE> { \
      typedef enabled<FIELD_TYPE,MODEL_TYPE> type; \
      typedef FIELD_TYPE FieldT; \
      typedef MODEL_TYPE ModelT; \
      static const bool value = true; \
    }

} // namespace kanomi

#endif /* KANOMI_FACTORY_HPP_ */
