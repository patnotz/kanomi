#ifndef KANOMI_MODELPROVIDER_HPP_
#define KANOMI_MODELPROVIDER_HPP_

#include <Kanomi_mpl.hpp>

namespace kanomi {

template <class FIELD, class MODEL>
struct enabled {
  typedef enabled<FIELD,MODEL> type;
  typedef FIELD FieldT;
  typedef MODEL ModelT;
  static const bool value = false;
};

#define ENABLE_MODEL(FIELD_TYPE, MODEL_TYPE) \
    template <> \
    struct enabled<FIELD_TYPE,MODEL_TYPE> { \
      typedef enabled<FIELD_TYPE,MODEL_TYPE> type; \
      typedef FIELD_TYPE FieldT; \
      typedef MODEL_TYPE ModelT; \
      static const bool value = true; \
    }

template <class MODELS, class FIELD>
struct ModelProvider {
private:
  struct enabled_pred {
    template <class IMPL>
    struct apply : enabled<FIELD,typename IMPL::ModelT> {};
  };
  typedef typename bf::result_of::
      find_if<MODELS, enabled_pred>::type iter_type;
public:
  typedef typename bf::result_of::value_of<iter_type>::type ProviderT;
};


} // namespace kanomi

#endif /* KANOMI_MODELPROVIDER_HPP_ */
