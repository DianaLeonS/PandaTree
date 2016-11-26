#ifndef PandaTree_Objects_PPFCand_h
#define PandaTree_Objects_PPFCand_h
#include "Constants.h"
#include "PParticleM.h"
#include "../../Framework/interface/Container.h"
#include "../../Framework/interface/Ref.h"

namespace panda {

  class PPFCand : public PParticleM {
  public:
    typedef Container<PPFCand, PParticleMCollection> PPFCandCollection;
    typedef Ref<PPFCandCollection> PPFCandRef;

    struct array_data : public PParticleM::array_data {
      static UInt_t const NMAX{256};

      array_data() : PParticleM::array_data() {}

      /* PParticle
      Float_t pt[NMAX]{};
      Float_t eta[NMAX]{};
      Float_t phi[NMAX]{};
      */
      /* PParticleM
      Float_t mass[NMAX]{};
      */
      Float_t q[NMAX]{};
      Float_t weight[NMAX]{};
      Int_t pftype[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, utils::BranchList const& = {"*"});
      void book(TTree&, TString const&, utils::BranchList const& = {"*"});
    };

    PPFCand(char const* name = "");
    PPFCand(PPFCand const&);
    PPFCand(array_data&, UInt_t idx);
    ~PPFCand();
    PPFCand& operator=(PPFCand const&);

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {"*"}) override;
    void setAddress(TTree&, utils::BranchList const& = {"*"}) override;
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
    Float_t& q;
    Float_t& weight;
    Int_t& pftype;

    /* BEGIN CUSTOM */
    /* END CUSTOM */

  protected:
    PPFCand(utils::AllocatorBase const&, char const* name);
  };

  typedef PPFCand::PPFCandCollection PPFCandCollection;
  typedef PPFCand::PPFCandRef PPFCandRef;

  /* BEGIN CUSTOM */
  /* END CUSTOM */

}

#endif
