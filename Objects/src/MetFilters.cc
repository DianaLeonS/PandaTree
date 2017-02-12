#include "../interface/MetFilters.h"

panda::MetFilters::MetFilters(char const* _name/* = ""*/) :
  Singlet(_name)
{
}

panda::MetFilters::MetFilters(MetFilters const& _src) :
  Singlet(_src.name_),
  globalHalo16(_src.globalHalo16),
  hbhe(_src.hbhe),
  hbheIso(_src.hbheIso),
  ecalDeadCell(_src.ecalDeadCell),
  badsc(_src.badsc),
  badMuons(_src.badMuons),
  duplicateMuons(_src.duplicateMuons),
  dupECALClusters(_src.dupECALClusters),
  unfixedECALHits(_src.unfixedECALHits)
{
  globalHalo16 = _src.globalHalo16;
  hbhe = _src.hbhe;
  hbheIso = _src.hbheIso;
  ecalDeadCell = _src.ecalDeadCell;
  badsc = _src.badsc;
  badMuons = _src.badMuons;
  duplicateMuons = _src.duplicateMuons;
  dupECALClusters = _src.dupECALClusters;
  unfixedECALHits = _src.unfixedECALHits;
}

panda::MetFilters::~MetFilters()
{
}

panda::MetFilters&
panda::MetFilters::operator=(MetFilters const& _src)
{
  globalHalo16 = _src.globalHalo16;
  hbhe = _src.hbhe;
  hbheIso = _src.hbheIso;
  ecalDeadCell = _src.ecalDeadCell;
  badsc = _src.badsc;
  badMuons = _src.badMuons;
  duplicateMuons = _src.duplicateMuons;
  dupECALClusters = _src.dupECALClusters;
  unfixedECALHits = _src.unfixedECALHits;

  return *this;
}

void
panda::MetFilters::doSetStatus_(TTree& _tree, utils::BranchList const& _branches)
{
  utils::setStatus(_tree, name_, "globalHalo16", _branches);
  utils::setStatus(_tree, name_, "hbhe", _branches);
  utils::setStatus(_tree, name_, "hbheIso", _branches);
  utils::setStatus(_tree, name_, "ecalDeadCell", _branches);
  utils::setStatus(_tree, name_, "badsc", _branches);
  utils::setStatus(_tree, name_, "badMuons", _branches);
  utils::setStatus(_tree, name_, "duplicateMuons", _branches);
  utils::setStatus(_tree, name_, "dupECALClusters", _branches);
  utils::setStatus(_tree, name_, "unfixedECALHits", _branches);
}

panda::utils::BranchList
panda::MetFilters::doGetStatus_(TTree& _tree) const
{
  utils::BranchList blist;

  blist.push_back(utils::getStatus(_tree, name_, "globalHalo16"));
  blist.push_back(utils::getStatus(_tree, name_, "hbhe"));
  blist.push_back(utils::getStatus(_tree, name_, "hbheIso"));
  blist.push_back(utils::getStatus(_tree, name_, "ecalDeadCell"));
  blist.push_back(utils::getStatus(_tree, name_, "badsc"));
  blist.push_back(utils::getStatus(_tree, name_, "badMuons"));
  blist.push_back(utils::getStatus(_tree, name_, "duplicateMuons"));
  blist.push_back(utils::getStatus(_tree, name_, "dupECALClusters"));
  blist.push_back(utils::getStatus(_tree, name_, "unfixedECALHits"));

  return blist;
}

panda::utils::BranchList
panda::MetFilters::doGetBranchNames_() const
{
  utils::BranchList blist;

  blist.push_back(utils::BranchName("globalHalo16").fullName(name_));
  blist.push_back(utils::BranchName("hbhe").fullName(name_));
  blist.push_back(utils::BranchName("hbheIso").fullName(name_));
  blist.push_back(utils::BranchName("ecalDeadCell").fullName(name_));
  blist.push_back(utils::BranchName("badsc").fullName(name_));
  blist.push_back(utils::BranchName("badMuons").fullName(name_));
  blist.push_back(utils::BranchName("duplicateMuons").fullName(name_));
  blist.push_back(utils::BranchName("dupECALClusters").fullName(name_));
  blist.push_back(utils::BranchName("unfixedECALHits").fullName(name_));

  return blist;
}

void
panda::MetFilters::doSetAddress_(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  utils::setAddress(_tree, name_, "globalHalo16", &globalHalo16, _branches, _setStatus);
  utils::setAddress(_tree, name_, "hbhe", &hbhe, _branches, _setStatus);
  utils::setAddress(_tree, name_, "hbheIso", &hbheIso, _branches, _setStatus);
  utils::setAddress(_tree, name_, "ecalDeadCell", &ecalDeadCell, _branches, _setStatus);
  utils::setAddress(_tree, name_, "badsc", &badsc, _branches, _setStatus);
  utils::setAddress(_tree, name_, "badMuons", &badMuons, _branches, _setStatus);
  utils::setAddress(_tree, name_, "duplicateMuons", &duplicateMuons, _branches, _setStatus);
  utils::setAddress(_tree, name_, "dupECALClusters", &dupECALClusters, _branches, _setStatus);
  utils::setAddress(_tree, name_, "unfixedECALHits", &unfixedECALHits, _branches, _setStatus);
}

void
panda::MetFilters::doBook_(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  utils::book(_tree, name_, "globalHalo16", "", 'O', &globalHalo16, _branches);
  utils::book(_tree, name_, "hbhe", "", 'O', &hbhe, _branches);
  utils::book(_tree, name_, "hbheIso", "", 'O', &hbheIso, _branches);
  utils::book(_tree, name_, "ecalDeadCell", "", 'O', &ecalDeadCell, _branches);
  utils::book(_tree, name_, "badsc", "", 'O', &badsc, _branches);
  utils::book(_tree, name_, "badMuons", "", 'O', &badMuons, _branches);
  utils::book(_tree, name_, "duplicateMuons", "", 'O', &duplicateMuons, _branches);
  utils::book(_tree, name_, "dupECALClusters", "", 'O', &dupECALClusters, _branches);
  utils::book(_tree, name_, "unfixedECALHits", "", 'O', &unfixedECALHits, _branches);
}

void
panda::MetFilters::doReleaseTree_(TTree& _tree)
{
  utils::resetAddress(_tree, name_, "globalHalo16");
  utils::resetAddress(_tree, name_, "hbhe");
  utils::resetAddress(_tree, name_, "hbheIso");
  utils::resetAddress(_tree, name_, "ecalDeadCell");
  utils::resetAddress(_tree, name_, "badsc");
  utils::resetAddress(_tree, name_, "badMuons");
  utils::resetAddress(_tree, name_, "duplicateMuons");
  utils::resetAddress(_tree, name_, "dupECALClusters");
  utils::resetAddress(_tree, name_, "unfixedECALHits");
}

void
panda::MetFilters::doInit_()
{
  globalHalo16 = false;
  hbhe = false;
  hbheIso = false;
  ecalDeadCell = false;
  badsc = false;
  badMuons = false;
  duplicateMuons = false;
  dupECALClusters = false;
  unfixedECALHits = false;

  /* BEGIN CUSTOM MetFilters.cc.doInit_ */
  /* END CUSTOM */
}


/* BEGIN CUSTOM MetFilters.cc.global */
/* END CUSTOM */
