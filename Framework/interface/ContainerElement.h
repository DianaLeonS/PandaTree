#ifndef PandaTree_Framework_ContainerElement_h
#define PandaTree_Framework_ContainerElement_h

//! Base class for elements of containers.
/*!
  ContainerElement is the base class of objects that are elements of containers (Array = fixed size and Collection = dynamic size).
  All deriving class of ContainerElement must have a subclass named datastore (which derives from ContainerElement::datastore) where
  arrays of plain-old-data types and vectors of objects are held. This big chunk of memory is in turn owned by a Container, which
  also holds an array of ContainerElements. Individual "data members" of a ContainerElement-derived class are references to the
  elements of their associated datastore, linked by the Container.
  By construction, the standard usage of the ContainerElement object is therefore to define a container first and to fetch from it
  as an element. However, it is also possible to use a ContainerElement class as a singlet. This operation is rather expensive as
  every singlet instantiation of a ContainerElement will create a one-element Array in memory in the back end.
*/

#include "Object.h"
#include "IOUtils.h"

#include "TTree.h"
#include "TString.h"

#include <vector>
#include <map>

namespace panda {

  namespace utils {
    class AllocatorBase;
  }

  class ContainerBase;
  class ArrayBase;

  class ContainerElement : public Object {
  public:
    /*!
      Actual arrays and vectors written to the tree are members of datastore. For example, given a tree with branches
      particle.size/i
      particle.pt[particle.size]/F
      the Particle datastore will have
      Float_t pt[N];
      which gets written to / read from the tree.
      The i-th Particle instance on the other hand has
      Float_t& pt;
      which is a reference to datastore::pt[i].
    */
    struct datastore {
      datastore() {}
      virtual ~datastore() { deallocate(); }

      virtual void allocate(UInt_t n) { nmax_ = n; }
      virtual void deallocate() {}
      virtual void setStatus(TTree&, TString const&, Bool_t, utils::BranchList const& = {"*"}) {}
      virtual void setAddress(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t setStatus = kTRUE) {}
      virtual void book(TTree&, TString const&, utils::BranchList const& = {"*"}, Bool_t dynamic = kTRUE) {}

      UInt_t nmax() const { return nmax_; }

    protected:
      UInt_t nmax_;
    };

    //! Standard constructor.
    ContainerElement(datastore&, UInt_t) {}
    //! Copy constructor.
    /*!
      Copy construction is similar to default-construction, and involves a creation of a one-element Array.
    */
    ContainerElement(ContainerElement const& src) : Object(src) {}
    ~ContainerElement() {}
    ContainerElement& operator=(ContainerElement const&) { return *this; }

    void setName(char const*) override;

  protected:
    //! Ctor for singlet instantiation
    /*!
      When a derived class is instantiated as a singlet, the object must create a new one-element Array
      and set its references to the element of the array. This array is controlled by a global StoreManager
      instance.
    */
    ContainerElement(ArrayBase*);

  private:
    //! Hidden default constructor.
    ContainerElement() {}
  };

  namespace utils {

    class StoreManager {
    public:
      void add(ContainerElement const* obj, ArrayBase* array) { store_.emplace(obj, array); }
      ArrayBase& getArray(ContainerElement const* obj) const { return *store_.at(obj); }
      template<class O> typename O::datastore& getData(O const*) const;
      char const* getName(ContainerElement const*) const;
      void free(ContainerElement const*);

    private:
      std::map<ContainerElement const*, ArrayBase*> store_{};
    };

    template<class O>
    typename O::datastore&
    StoreManager::getData(O const* _obj) const
    {
      return static_cast<typename O::datastore&>(store_.at(_obj)->getData());
    }
    
  }

  extern utils::StoreManager gStore;
}

#endif
