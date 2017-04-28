#include "xgboostcpp/XGBooster.h"
#include "xgboostcpp/XGBoosterImpl.h"

#include "boost-pba/portable_binary_oarchive.hpp"
#include "boost-pba/portable_binary_iarchive.hpp"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

// include all std functions
using namespace std;
#include "xgboost/wrapper/xgboost_wrapper.h"
#include "xgboost/src/gbm/gbm.h"
#include "xgboost/src/data.h"
#include "xgboost/src/learner/learner-inl.hpp"
#include "xgboost/src/io/io.h"
#include "xgboost/src/utils/utils.h"
#include "xgboost/src/utils/math.h"
#include "xgboost/src/utils/group_data.h"
#include "xgboost/src/io/simple_dmatrix-inl.hpp"

using namespace xgboost;
using namespace xgboost::io;

// Learner (IGradBooster):
BOOST_SERIALIZATION_ASSUME_ABSTRACT(xgboost::gbm::IGradBooster);
BOOST_CLASS_EXPORT_GUID(xgboost::gbm::IGradBooster, "IGradBooster");
BOOST_CLASS_EXPORT_GUID(xgboost::gbm::GBLinear, "GBLinear")
BOOST_CLASS_EXPORT_GUID(xgboost::gbm::GBTree, "GBTree")

// Tree model:
typedef xgboost::tree::RTreeNodeStat RTreeNodeStat;
typedef xgboost::tree::TreeModel<bst_float, RTreeNodeStat> TreeModel;
BOOST_SERIALIZATION_ASSUME_ABSTRACT(TreeModel);
BOOST_CLASS_EXPORT_GUID(TreeModel, "TreeModel");
BOOST_CLASS_EXPORT_GUID(xgboost::tree::RegTree, "RegTree");

// Loss function:
BOOST_SERIALIZATION_ASSUME_ABSTRACT(xgboost::learner::IObjFunction);
BOOST_CLASS_EXPORT_GUID(xgboost::learner::IObjFunction, "IObjFunction");
BOOST_CLASS_EXPORT_GUID(xgboost::learner::RegLossObj, "RegLossObj");

// namespace boost { serialization {
XGBOOSTCPP_BEGIN_NAMESPACE(boost)
XGBOOSTCPP_BEGIN_NAMESPACE(serialization)

template<class Archive> void serialize(Archive & ar, xgboost::wrapper::Booster &booster, const unsigned int version)
{
    ar & boost::serialization::base_object<learner::BoostLearner>(booster);
}

XGBOOSTCPP_END_NAMESPACE(serialization)
XGBOOSTCPP_END_NAMESPACE(boost)
// }}

// ##################################################################
// #################### portable_binary_*archive ####################
// ##################################################################

XGBOOSTCPP_NAMESPACE_BEGIN

typedef portable_binary_oarchive OArchive;
template void XGBooster::serialize<OArchive>(OArchive &ar, const unsigned int);
template void XGBooster::Impl::serialize<OArchive>(OArchive &ar, const unsigned int);
template void XGBooster::Recipe::serialize<OArchive>(OArchive &ar, const unsigned int);

typedef portable_binary_iarchive IArchive;
template void XGBooster::serialize<IArchive>(IArchive &ar, const unsigned int);
template void XGBooster::Impl::serialize<IArchive>(IArchive &ar, const unsigned int);
template void XGBooster::Recipe::serialize<IArchive>(IArchive &ar, const unsigned int);

XGBOOSTCPP_NAMESPACE_END

typedef portable_binary_oarchive OArchive;
template void xgboost::tree::RegTree::serialize<OArchive>(OArchive &ar, const unsigned int);

typedef portable_binary_iarchive IArchive;
template void xgboost::tree::RegTree::serialize<IArchive>(IArchive &ar, const unsigned int);

BOOST_CLASS_EXPORT_IMPLEMENT(xgboostcpp::XGBooster);
BOOST_CLASS_EXPORT_IMPLEMENT(xgboostcpp::XGBooster::Impl);

