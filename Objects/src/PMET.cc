#include "../interface/PMET.h"

panda::PMET::PMET() :
  Singlet()
{
}

panda::PMET::PMET(PMET const& _src) :
  Singlet(_src.name_),
  pt(_src.pt),
  phi(_src.phi)
{
}

panda::PMET::PMET(TString const& _name) :
  Singlet(_name)
{
}

panda::PMET::~PMET()
{
}

panda::PMET&
panda::PMET::operator=(PMET const& _src)
{
  Singlet::operator=(_src);

  pt = _src.pt;
  phi = _src.phi;

  return *this;
}

void
panda::PMET::setStatus(TTree& _tree, Bool_t _status, utils::BranchList const& _branches/* = {"*"}*/)
{
  Singlet::setStatus(_tree, _status, _branches);

  utils::setStatus(_tree, name_, "pt", _status, _branches);
  utils::setStatus(_tree, name_, "phi", _status, _branches);
}

void
panda::PMET::setAddress(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  Singlet::setAddress(_tree, _branches);

  utils::setStatusAndAddress(_tree, name_, "pt", &pt, _branches);
  utils::setStatusAndAddress(_tree, name_, "phi", &phi, _branches);
}

void
panda::PMET::book(TTree& _tree, utils::BranchList const& _branches/* = {"*"}*/)
{
  Singlet::book(_tree, _branches);

  utils::book(_tree, name_, "pt", "", 'F', &pt, _branches);
  utils::book(_tree, name_, "phi", "", 'F', &phi, _branches);
}

void
panda::PMET::init()
{
  Singlet::init();

  pt = 0.;
  phi = 0.;
}


/* BEGIN CUSTOM */
/* END CUSTOM */
