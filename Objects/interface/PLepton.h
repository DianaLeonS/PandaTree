#ifndef PandaTree_Objects_PLepton_h
#define PandaTree_Objects_PLepton_h
#include "Constants.h"
#include "PParticle.h"
#include "../../Framework/interface/Collection.h"
#include "../../Framework/interface/Array.h"
#include "../../Framework/interface/Ref.h"

namespace panda {

  class PLepton : public PParticle {
  public:
    struct datastore : public PParticle::datastore {
      datastore() : PParticle::datastore() {}
      ~datastore() { deallocate(); }

      /* PParticle
      Float_t* pt{0};
      Float_t* eta{0};
      Float_t* phi{0};
      */
      Text_t const** q{0};
      Bool_t* loose{0};
      Bool_t* tight{0};
      Float_t* chiso{0};
      Float_t* nhiso{0};
      Float_t* phoiso{0};
      Float_t* puiso{0};
      Bool_t* tauDecay{0};
      Bool_t* hadDecay{0};

      void allocate(UInt_t n) override;
      void deallocate() override;
      void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {"*"}) override;
      void setAddress(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
      void book(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t dynamic = kTRUE) override;
    };

    typedef Array<PLepton, PParticle::array_type> array_type;
    typedef Collection<PLepton, PParticle::collection_type> collection_type;

    PLepton(char const* name = "");
    PLepton(PLepton const&);
    PLepton(datastore&, UInt_t idx);
    ~PLepton();
    PLepton& operator=(PLepton const&);

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {"*"}) override;
    void setAddress(TTree&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) override;
    void book(TTree&, utils::BranchList const& = {"*"}) override;

    void init() override;

    virtual double combiso() const { return 0.; }

    /* PParticle
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
    */
    Text_t const*& q;
    Bool_t& loose;
    Bool_t& tight;
    Float_t& chiso;
    Float_t& nhiso;
    Float_t& phoiso;
    Float_t& puiso;
    Bool_t& tauDecay;
    Bool_t& hadDecay;

    /* BEGIN CUSTOM */
    /* END CUSTOM */

  protected:
    PLepton(ArrayBase*);
  };

  typedef PLepton::array_type PLeptonArray;
  typedef PLepton::collection_type PLeptonCollection;
  typedef Ref<PLepton> PLeptonRef;

  /* BEGIN CUSTOM */
  /* END CUSTOM */

}

#endif
