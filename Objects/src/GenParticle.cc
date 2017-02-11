#include "../interface/GenParticle.h"

void
panda::GenParticle::datastore::allocate(UInt_t _nmax)
{
  PackedParticle::datastore::allocate(_nmax);

  packedY = new Short_t[nmax_];
  pdgid = new Int_t[nmax_];
  statusFlags = new UShort_t[nmax_];
  parent_ = new Int_t[nmax_];
}

void
panda::GenParticle::datastore::deallocate()
{
  PackedParticle::datastore::deallocate();

  delete [] packedY;
  packedY = 0;
  delete [] pdgid;
  pdgid = 0;
  delete [] statusFlags;
  statusFlags = 0;
  delete [] parent_;
  parent_ = 0;
}

void
panda::GenParticle::datastore::setStatus(TTree& _tree, TString const& _name, utils::BranchList const& _branches)
{
  PackedParticle::datastore::setStatus(_tree, _name, _branches);

  utils::setStatus(_tree, _name, "packedY", _branches);
  utils::setStatus(_tree, _name, "pdgid", _branches);
  utils::setStatus(_tree, _name, "statusFlags", _branches);
  utils::setStatus(_tree, _name, "parent_", _branches);
}

panda::utils::BranchList
panda::GenParticle::datastore::getStatus(TTree& _tree, TString const& _name) const
{
  utils::BranchList blist(PackedParticle::datastore::getStatus(_tree, _name));

  blist.push_back(utils::getStatus(_tree, _name, "packedY"));
  blist.push_back(utils::getStatus(_tree, _name, "pdgid"));
  blist.push_back(utils::getStatus(_tree, _name, "statusFlags"));
  blist.push_back(utils::getStatus(_tree, _name, "parent_"));

  return blist;
}

panda::utils::BranchList
panda::GenParticle::datastore::getBranchNames(TString const& _name) const
{
  utils::BranchList blist(PackedParticle::datastore::getBranchNames(_name));

  blist.push_back(utils::BranchName("packedY").fullName(_name));
  blist.push_back(utils::BranchName("pdgid").fullName(_name));
  blist.push_back(utils::BranchName("statusFlags").fullName(_name));
  blist.push_back(utils::BranchName("parent_").fullName(_name));

  return blist;
}

void
panda::GenParticle::datastore::setAddress(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  PackedParticle::datastore::setAddress(_tree, _name, _branches, _setStatus);

  utils::setAddress(_tree, _name, "packedY", packedY, _branches, _setStatus);
  utils::setAddress(_tree, _name, "pdgid", pdgid, _branches, _setStatus);
  utils::setAddress(_tree, _name, "statusFlags", statusFlags, _branches, _setStatus);
  utils::setAddress(_tree, _name, "parent_", parent_, _branches, _setStatus);
}

void
panda::GenParticle::datastore::book(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _dynamic/* = kTRUE*/)
{
  PackedParticle::datastore::book(_tree, _name, _branches, _dynamic);

  TString size(_dynamic ? "[" + _name + ".size]" : TString::Format("[%d]", nmax_));

  utils::book(_tree, _name, "packedY", size, 'S', packedY, _branches);
  utils::book(_tree, _name, "pdgid", size, 'I', pdgid, _branches);
  utils::book(_tree, _name, "statusFlags", size, 's', statusFlags, _branches);
  utils::book(_tree, _name, "parent_", size, 'I', parent_, _branches);
}

void
panda::GenParticle::datastore::releaseTree(TTree& _tree, TString const& _name)
{
  PackedParticle::datastore::releaseTree(_tree, _name);

  utils::resetAddress(_tree, _name, "packedY");
  utils::resetAddress(_tree, _name, "pdgid");
  utils::resetAddress(_tree, _name, "statusFlags");
  utils::resetAddress(_tree, _name, "parent_");
}

void
panda::GenParticle::datastore::resizeVectors_(UInt_t _size)
{
  PackedParticle::datastore::resizeVectors_(_size);

}

panda::GenParticle::GenParticle(char const* _name/* = ""*/) :
  PackedParticle(new GenParticleArray(1, _name)),
  packedY(gStore.getData(this).packedY[0]),
  pdgid(gStore.getData(this).pdgid[0]),
  statusFlags(gStore.getData(this).statusFlags[0]),
  parent(gStore.getData(this).parentContainer_, gStore.getData(this).parent_[0])
{
}

panda::GenParticle::GenParticle(GenParticle const& _src) :
  PackedParticle(new GenParticleArray(1, gStore.getName(&_src))),
  packedY(gStore.getData(this).packedY[0]),
  pdgid(gStore.getData(this).pdgid[0]),
  statusFlags(gStore.getData(this).statusFlags[0]),
  parent(gStore.getData(this).parentContainer_, gStore.getData(this).parent_[0])
{
  PackedParticle::operator=(_src);

  packedY = _src.packedY;
  pdgid = _src.pdgid;
  statusFlags = _src.statusFlags;
  parent = _src.parent;
}

panda::GenParticle::GenParticle(datastore& _data, UInt_t _idx) :
  PackedParticle(_data, _idx),
  packedY(_data.packedY[_idx]),
  pdgid(_data.pdgid[_idx]),
  statusFlags(_data.statusFlags[_idx]),
  parent(_data.parentContainer_, _data.parent_[_idx])
{
}

panda::GenParticle::GenParticle(ArrayBase* _array) :
  PackedParticle(_array),
  packedY(gStore.getData(this).packedY[0]),
  pdgid(gStore.getData(this).pdgid[0]),
  statusFlags(gStore.getData(this).statusFlags[0]),
  parent(gStore.getData(this).parentContainer_, gStore.getData(this).parent_[0])
{
}

panda::GenParticle::~GenParticle()
{
  destructor();
  gStore.free(this);
}

void
panda::GenParticle::destructor()
{
  /* BEGIN CUSTOM GenParticle.cc.destructor */
  /* END CUSTOM */

  PackedParticle::destructor();
}

panda::GenParticle&
panda::GenParticle::operator=(GenParticle const& _src)
{
  PackedParticle::operator=(_src);

  packedY = _src.packedY;
  pdgid = _src.pdgid;
  statusFlags = _src.statusFlags;
  parent = _src.parent;

  return *this;
}

void
panda::GenParticle::doSetAddress_(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/, Bool_t _setStatus/* = kTRUE*/)
{
  PackedParticle::doSetAddress_(_tree, _name, _branches, _setStatus);

  utils::setAddress(_tree, _name, "packedY", &packedY, _branches, _setStatus);
  utils::setAddress(_tree, _name, "pdgid", &pdgid, _branches, _setStatus);
  utils::setAddress(_tree, _name, "statusFlags", &statusFlags, _branches, _setStatus);
  utils::setAddress(_tree, _name, "parent_", gStore.getData(this).parent_, _branches, true);
}

void
panda::GenParticle::doBook_(TTree& _tree, TString const& _name, utils::BranchList const& _branches/* = {"*"}*/)
{
  PackedParticle::doBook_(_tree, _name, _branches);

  utils::book(_tree, _name, "packedY", "", 'S', &packedY, _branches);
  utils::book(_tree, _name, "pdgid", "", 'I', &pdgid, _branches);
  utils::book(_tree, _name, "statusFlags", "", 's', &statusFlags, _branches);
  utils::book(_tree, _name, "parent_", "", 'I', gStore.getData(this).parent_, _branches);
}

void
panda::GenParticle::doReleaseTree_(TTree& _tree, TString const& _name)
{
  PackedParticle::doReleaseTree_(_tree, _name);

  utils::resetAddress(_tree, _name, "packedY");
  utils::resetAddress(_tree, _name, "pdgid");
  utils::resetAddress(_tree, _name, "statusFlags");
  utils::resetAddress(_tree, _name, "parent_");
}

void
panda::GenParticle::doInit_()
{
  PackedParticle::doInit_();

  packedY = 0;
  pdgid = 0;
  statusFlags = 0;
  parent.init();

  /* BEGIN CUSTOM GenParticle.cc.doInit_ */
  /* END CUSTOM */
}

/* BEGIN CUSTOM GenParticle.cc.global */
namespace panda {
  extern PackingHelper packingHelper;
}

void
panda::GenParticle::pack_()
{
  packedPt = packingHelper.packUnbound(pt_);
  packedPhi = std::round(phi_/3.2f*std::numeric_limits<Short_t>::max());
  packedM = packingHelper.packUnbound(pt_);

  double reducedm2(mass_ / pt_);
  reducedm2 *= reducedm2;
  double c(std::cosh(eta_));
  double y(std::log((std::sqrt(reducedm2 + c * c) + std::sinh(eta_)) / std::sqrt(1. + reducedm2)));
  packedY = y / 6.0f * std::numeric_limits<Short_t>::max();
}

void
panda::GenParticle::unpack_() const
{
  if (unpacked_)
    return;

  pt_ = packingHelper.unpackUnbound(packedPt);
  // shift particle phi to break degeneracies in angular separations
  // plus introduce a pseudo-random sign of the shift
  double shift(pt_ < 1. ? 0.1 * pt_ : 0.1 / pt_);
  double sign((int(pt_ * 10.) % 2 == 0) ? 1 : -1);
  phi_ = (packedPhi + sign * shift) * 3.2f / std::numeric_limits<Short_t>::max();
  mass_ = packingHelper.unpackUnbound(packedM);

  double y(packedY * 6.0f / std::numeric_limits<Short_t>::max());
  double c(std::cosh(y));
  double reducedm2(mass_ * mass_ / (mass_ * mass_ + pt_ * pt_));
  eta_ = std::log((std::sqrt(c * c - reducedm2) + std::sinh(y)) / std::sqrt(1. - reducedm2));

  unpacked_ = true;
}
/* END CUSTOM */
