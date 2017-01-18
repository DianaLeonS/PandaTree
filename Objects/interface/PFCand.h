#ifndef PandaTree_Objects_PFCand_h
#define PandaTree_Objects_PFCand_h
#include "Constants.h"
#include "ParticleM.h"
#include "../../Framework/interface/Container.h"
#include "../../Framework/interface/Ref.h"
#include "../../Framework/interface/RefVector.h"

namespace panda {

  class PFCand : public ParticleM {
  public:
    struct datastore : public ParticleM::datastore {
      datastore() : ParticleM::datastore() {}
      ~datastore() { deallocate(); }

      /* Particle
      Float_t* pt{0};
      Float_t* eta{0};
      Float_t* phi{0};
      */
      /* ParticleM
      Float_t* mass{0};
      */
      Short_t* q{0};
      Float_t* puppiW{0};
      Float_t* puppiWNoLep{0};
      Int_t* pftype{0};

      void allocate(UInt_t n) override;
      void deallocate() override;
      void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {"*"}) override;
      void setAddress(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
      void book(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t dynamic = kTRUE) override;
      void resetAddress(TTree&, TString const&) override;
      void resizeVectors_(UInt_t) override;
    };

    typedef ParticleM base_type;
    typedef Array<PFCand> array_type;
    typedef Collection<PFCand> collection_type;

    PFCand(char const* name = "");
    PFCand(PFCand const&);
    PFCand(datastore&, UInt_t idx);
    ~PFCand();
    PFCand& operator=(PFCand const&);

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {"*"}) override;
    void setAddress(TTree&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
    void book(TTree&, utils::BranchList const& = {"*"}) override;
    void resetAddress(TTree&) override;

    void init() override;

    TLorentzVector puppiP4() const { TLorentzVector p4; p4.SetPtEtaPhiM(pt * puppiW, eta, phi, m() * puppiW); return p4; }
    TLorentzVector puppiNoLepP4() const { TLorentzVector p4; p4.SetPtEtaPhiM(pt * puppiWNoLep, eta, phi, m() * puppiWNoLep); return p4; }

    /* Particle
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
    */
    /* ParticleM
    Float_t& mass;
    */
    Short_t& q;
    Float_t& puppiW;
    Float_t& puppiWNoLep;
    Int_t& pftype;

    /* BEGIN CUSTOM PFCand.h.classdef */
    /* END CUSTOM */

    void destructor() override;

  protected:
    PFCand(ArrayBase*);
  };

  typedef PFCand::array_type PFCandArray;
  typedef PFCand::collection_type PFCandCollection;
  typedef Ref<PFCand> PFCandRef;
  typedef RefVector<PFCand> PFCandRefVector;

  /* BEGIN CUSTOM PFCand.h.global */
  /* END CUSTOM */

}

#endif
