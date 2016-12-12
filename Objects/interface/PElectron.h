#ifndef PandaTree_Objects_PElectron_h
#define PandaTree_Objects_PElectron_h
#include "Constants.h"
#include "PLepton.h"
#include "../../Framework/interface/Container.h"
#include "../../Framework/interface/Ref.h"
#include "../../Framework/interface/RefVector.h"
#include "PSuperCluster.h"

namespace panda {

  class PElectron : public PLepton {
  public:
    struct datastore : public PLepton::datastore {
      datastore() : PLepton::datastore() {}
      ~datastore() { deallocate(); }

      /* PParticle
      Float_t* pt{0};
      Float_t* eta{0};
      Float_t* phi{0};
      */
      /* PLepton
      Short_t* q{0};
      Bool_t* loose{0};
      Bool_t* medium{0};
      Bool_t* tight{0};
      Float_t* chiso{0};
      Float_t* nhiso{0};
      Float_t* phoiso{0};
      Float_t* puiso{0};
      Bool_t* tauDecay{0};
      Bool_t* hadDecay{0};
      ContainerBase const* matchedGenContainer_{0};
      UInt_t* matchedGen_{0};
      */
      Float_t* chisoPh{0};
      Float_t* nhisoPh{0};
      Float_t* phisoPh{0};
      Float_t* ecaliso{0};
      Float_t* hcaliso{0};
      Float_t* isoPUOffset{0};
      Float_t* sieie{0};
      Float_t* sipip{0};
      Float_t* hOverE{0};
      Bool_t* veto{0};
      Bool_t (*matchHLT)[nElectronHLTObjects]{0};
      ContainerBase const* superClusterContainer_{0};
      UInt_t* superCluster_{0};

      void allocate(UInt_t n) override;
      void deallocate() override;
      void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {}) override;
      void setAddress(TTree&, TString const&, utils::BranchList const& = {}, Bool_t setStatus = kTRUE) override;
      void book(TTree&, TString const&, utils::BranchList const& = {}, Bool_t dynamic = kTRUE) override;
      void resetAddress(TTree&, TString const&) override;
      void resizeVectors_(UInt_t) override;
    };

    typedef PLepton base_type;
    typedef Array<PElectron> array_type;
    typedef Collection<PElectron> collection_type;

    PElectron(char const* name = "");
    PElectron(PElectron const&);
    PElectron(datastore&, UInt_t idx);
    ~PElectron();
    PElectron& operator=(PElectron const&);

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {}) override;
    void setAddress(TTree&, utils::BranchList const& = {}, Bool_t setStatus = kTRUE) override;
    void book(TTree&, utils::BranchList const& = {}) override;
    void resetAddress(TTree&) override;

    void init() override;

    double m() const override { return 5.109989e-4; }
    double combiso() const override { return chiso + std::max(nhiso + phoiso - isoPUOffset, Float_t(0.)); }

    /* PParticle
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
    */
    /* PLepton
    Short_t& q;
    Bool_t& loose;
    Bool_t& medium;
    Bool_t& tight;
    Float_t& chiso;
    Float_t& nhiso;
    Float_t& phoiso;
    Float_t& puiso;
    Bool_t& tauDecay;
    Bool_t& hadDecay;
    Ref<PGenParticle> matchedGen;
    */
    Float_t& chisoPh;
    Float_t& nhisoPh;
    Float_t& phisoPh;
    Float_t& ecaliso;
    Float_t& hcaliso;
    Float_t& isoPUOffset;
    Float_t& sieie;
    Float_t& sipip;
    Float_t& hOverE;
    Bool_t& veto;
    Bool_t (&matchHLT)[nElectronHLTObjects];
    Ref<PSuperCluster> superCluster;

    /* BEGIN CUSTOM PElectron.h.classdef */
    /* END CUSTOM */

    void destructor() override;

  protected:
    PElectron(ArrayBase*);
  };

  typedef PElectron::array_type PElectronArray;
  typedef PElectron::collection_type PElectronCollection;
  typedef Ref<PElectron> PElectronRef;
  typedef RefVector<PElectron> PElectronRefVector;

  /* BEGIN CUSTOM PElectron.h.global */
  /* END CUSTOM */

}

#endif
