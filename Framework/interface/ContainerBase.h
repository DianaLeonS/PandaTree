#ifndef PandaTree_Framework_ContainerBase_h
#define PandaTree_Framework_ContainerBase_h

#include "ContainerElement.h"
#include "IOUtils.h"

#include "TString.h"
#include "TTree.h"

#include <vector>

namespace panda {

  class ContainerBase {
  public:
    ContainerBase(ContainerBase const& src) : name_(src.name_), unitSize_(src.unitSize_) {}
    virtual ~ContainerBase() {}

    char const* getName() const { return name_; }
    void setName(char const* name) { name_ = name; }

    virtual UInt_t size() const = 0;
    virtual void init() = 0;
    virtual ContainerElement::datastore& getData() = 0;
    virtual ContainerElement::datastore const& getData() const = 0;
    virtual ContainerElement& elemAt(UInt_t) = 0;
    virtual ContainerElement const& elemAt(UInt_t) const = 0;

    void setStatus(TTree&, Bool_t, utils::BranchList const& = {"*"});
    void setAddress(TTree&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE);
    void book(TTree&, utils::BranchList const& = {"*"});
    void releaseTree(TTree&);

  private:
    virtual void allocate_(UInt_t) = 0;
    virtual void deallocate_() = 0;

    virtual void doSetStatus_(TTree&, Bool_t, utils::BranchList const& = {"*"}) = 0;
    virtual void doSetAddress_(TTree&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) = 0;
    virtual void doBook_(TTree&, utils::BranchList const& = {"*"}) = 0;

  protected:
    ContainerBase(char const* name, UInt_t unitSize) : name_(name), unitSize_(unitSize) {}

    void updateAddress_();

    TString name_;
    UInt_t const unitSize_;
    Char_t* array_{0};
    TTree* input_{0};
    std::vector<TTree*> outputs_{};
  };

}

#endif
