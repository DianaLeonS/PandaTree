#include "../interface/ContainerBase.h"

#include <algorithm>
#include <stdexcept>

void
panda::ContainerBase::setStatus(TTree& _tree, utils::BranchList const& _branches)
{
  doSetStatus_(_tree, _branches);
}

panda::utils::BranchList
panda::ContainerBase::getStatus(TTree& _tree) const
{
  return doGetStatus_(_tree);
}

panda::utils::BranchList
panda::ContainerBase::getBranchNames(Bool_t _fullName/* = kTRUE*/) const
{
  if (_fullName)
    return getData().getBranchNames(name_);
  else
    return getData().getBranchNames("");
}

void
panda::ContainerBase::setAddress(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  doSetAddress_(_tree, _branches, _setStatus, true);
}

void
panda::ContainerBase::book(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  doBook_(_tree, _branches);
}
