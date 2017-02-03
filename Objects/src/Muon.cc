#include "../interface/Muon.h"

void
panda::Muon::datastore::allocate(UInt_t _nmax)
{
  Lepton::datastore::allocate(_nmax);

  triggerMatch = new Bool_t[nmax_][nMuonTriggerObjects];
}

void
panda::Muon::datastore::deallocate()
{
  Lepton::datastore::deallocate();

  delete [] triggerMatch;
  triggerMatch = 0;
}

void
panda::Muon::datastore::setStatus(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::datastore::setStatus(_tree, _name, _branches);

  utils::setStatus(_tree, _name, "triggerMatch", _branches);
}

void
panda::Muon::datastore::setAddress(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  Lepton::datastore::setAddress(_tree, _name, _branches, _setStatus);

  utils::setAddress(_tree, _name, "triggerMatch", triggerMatch, _branches, _setStatus);
}

void
panda::Muon::datastore::book(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _dynamic/* = kTRUE*/)
{
  Lepton::datastore::book(_tree, _name, _branches, _dynamic);

  TString size(_dynamic ? "[" + _name + ".size]" : TString::Format("[%d]", nmax_));

  utils::book(_tree, _name, "triggerMatch", size + TString::Format("[%d]", nMuonTriggerObjects), 'O', triggerMatch, _branches);
}

void
panda::Muon::datastore::resetAddress(TTree& _tree, TString const& _name)
{
  Lepton::datastore::resetAddress(_tree, _name);

  utils::resetAddress(_tree, _name, "triggerMatch");
}

void
panda::Muon::datastore::resizeVectors_(UInt_t _size)
{
  Lepton::datastore::resizeVectors_(_size);

}

panda::Muon::Muon(char const* _name/* = ""*/) :
  Lepton(new MuonArray(1, _name)),
  triggerMatch(gStore.getData(this).triggerMatch[0])
{
}

panda::Muon::Muon(datastore& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  triggerMatch(_data.triggerMatch[_idx])
{
}

panda::Muon::Muon(Muon const& _src) :
  Lepton(new MuonArray(1, gStore.getName(&_src))),
  triggerMatch(gStore.getData(this).triggerMatch[0])
{
  Lepton::operator=(_src);

  std::memcpy(triggerMatch, _src.triggerMatch, sizeof(Bool_t) * nMuonTriggerObjects);
}

panda::Muon::Muon(ArrayBase* _array) :
  Lepton(_array),
  triggerMatch(gStore.getData(this).triggerMatch[0])
{
}

panda::Muon::~Muon()
{
  destructor();
  gStore.free(this);
}

void
panda::Muon::destructor()
{
  /* BEGIN CUSTOM Muon.cc.destructor */
  /* END CUSTOM */

  Lepton::destructor();
}

panda::Muon&
panda::Muon::operator=(Muon const& _src)
{
  Lepton::operator=(_src);

  std::memcpy(triggerMatch, _src.triggerMatch, sizeof(Bool_t) * nMuonTriggerObjects);

  return *this;
}

void
panda::Muon::setStatus(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::setStatus(_tree, _branches);

  TString name(gStore.getName(this));

  utils::setStatus(_tree, name, "triggerMatch", _branches);
}

UInt_t
panda::Muon::setAddress(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  Lepton::setAddress(_tree, _branches, _setStatus);

  TString name(gStore.getName(this));

  utils::setAddress(_tree, name, "triggerMatch", triggerMatch, _branches, _setStatus);

  return -1;
}

UInt_t
panda::Muon::book(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::book(_tree, _branches);

  TString name(gStore.getName(this));

  utils::book(_tree, name, "triggerMatch", TString::Format("[%d]", nMuonTriggerObjects), 'O', triggerMatch, _branches);

  return -1;
}

void
panda::Muon::releaseTree(TTree& _tree)
{
  Lepton::releaseTree(_tree);

  TString name(gStore.getName(this));

  utils::resetAddress(_tree, name, "triggerMatch");
}

void
panda::Muon::init()
{
  Lepton::init();

  for (auto& p0 : triggerMatch) p0 = false;
}


/* BEGIN CUSTOM Muon.cc.global */
/* END CUSTOM */
