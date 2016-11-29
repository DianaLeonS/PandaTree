#ifndef PandaTree_Objects_Run_h
#define PandaTree_Objects_Run_h
#include "Constants.h"
#include "../../Framework/interface/TreeEntry.h"

namespace panda {

  class Run : public TreeEntry {
  public:
    Run();
    Run(Run const&);
    ~Run() {}
    Run& operator=(Run const&);

    void init() override;

    UInt_t run{};
    UInt_t hltMenu{};

  protected:
    void doSetStatus_(TTree&, Bool_t, utils::BranchList const&) override;
    void doSetAddress_(TTree&, utils::BranchList const&, Bool_t setStatus) override;
    void doBook_(TTree&, utils::BranchList const&) override;
    void doReleaseTree_(TTree&) override;

  public:
    /* BEGIN CUSTOM */
    /* END CUSTOM */
  };

  /* BEGIN CUSTOM */
  /* END CUSTOM */

}

#endif
