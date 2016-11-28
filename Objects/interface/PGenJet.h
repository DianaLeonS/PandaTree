#ifndef PandaTree_Objects_PGenJet_h
#define PandaTree_Objects_PGenJet_h
#include "Constants.h"
#include "PParticleM.h"
#include "../../Framework/interface/Collection.h"
#include "../../Framework/interface/Array.h"
#include "../../Framework/interface/Ref.h"

namespace panda {

  class PGenJet : public PParticleM {
  public:
    struct datastore : public PParticleM::datastore {
      datastore() : PParticleM::datastore() {}
      ~datastore() { deallocate(); }

      /* PParticle
      Float_t* pt{0};
      Float_t* eta{0};
      Float_t* phi{0};
      */
      /* PParticleM
      Float_t* mass{0};
      */
      Int_t* pdgid{0};

      void allocate(UInt_t n) override;
      void deallocate() override;
      void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {"*"}) override;
      void setAddress(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
      void book(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t dynamic = kTRUE) override;
    };

    typedef Array<PGenJet, PParticleM::array_type> array_type;
    typedef Collection<PGenJet, PParticleM::collection_type> collection_type;

    PGenJet(char const* name = "");
    PGenJet(PGenJet const&);
    PGenJet(datastore&, UInt_t idx);
    ~PGenJet();
    PGenJet& operator=(PGenJet const&);

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {"*"}) override;
    void setAddress(TTree&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
    void book(TTree&, utils::BranchList const& = {"*"}) override;

    void init() override;

    /* PParticle
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
    */
    /* PParticleM
    Float_t& mass;
    */
    Int_t& pdgid;

    /* BEGIN CUSTOM */
    /* END CUSTOM */

  protected:
    PGenJet(ArrayBase*);
  };

  typedef PGenJet::array_type PGenJetArray;
  typedef PGenJet::collection_type PGenJetCollection;
  typedef Ref<PGenJet> PGenJetRef;

  /* BEGIN CUSTOM */
  /* END CUSTOM */

}

#endif
