from common import *
from base import Definition
from obj import Object
from output import FileOutput

class Tree(Definition, Object):
    """
    Tree definition. Definition file syntax:

    {<Name>}
    <branch definitions>
    <function definitions>
    """

    def __init__(self, line, source):
        Definition.__init__(self, line, '\\{([^\\}]+)\\}$')
        Object.__init__(self, self.matches.group(1), source)

    def generate_header(self):
        """
        Write the header file.
        """

        header = FileOutput('{PACKDIR}/Objects/interface/{name}.h'.format(PACKDIR = PACKDIR, name = self.name))
        header.writeline('#ifndef {PACKAGE}_Objects_{name}_h'.format(PACKAGE = PACKAGE, name = self.name))
        header.writeline('#define {PACKAGE}_Objects_{name}_h'.format(PACKAGE = PACKAGE, name = self.name))
        header.writeline('#include "../../Framework/interface/TreeEntry.h"')
        header.writeline('#include "Constants.h"')

        included = []
        for objbranch in self.objbranches:
            if objbranch.objname not in included:
                header.writeline('#include "{brobj}.h"'.format(brobj = objbranch.objname))
                included.append(objbranch.objname)

        for include in self.includes:
            include.write(header)

        header.newline()
        header.writeline('namespace {NAMESPACE} {{'.format(NAMESPACE = NAMESPACE))
        header.newline()
        header.indent += 1

        header.writeline('class {name} : public TreeEntry {{'.format(name = self.name))
        header.writeline('public:')
        header.indent += 1
        
        header.writeline('{name}();'.format(name = self.name)) # default constructor
        header.writeline('{name}({name} const&);'.format(name = self.name)) # copy constructor
        header.writeline('~{name}() {{}}'.format(name = self.name)) # destructor
        header.writeline('{name}& operator=({name} const&);'.format(name = self.name)) # assignment operator

        if len(self.functions) != 0:
            header.newline()
            for function in self.functions:
                function.write_decl(header, context = 'class')

        if len(self.objbranches) != 0:
            header.newline()
            for objbranch in self.objbranches:
                objbranch.write_decl(header)

        if len(self.branches) != 0:
            header.newline()
            for branch in self.branches:
                branch.write_decl(header, context = 'TreeEntry')

        header.newline()
        header.writeline('static utils::BranchList getListOfBranches();')

        header.newline()
        header.indent -= 1
        header.writeline('protected:')
        header.indent += 1
        header.writeline('void doSetStatus_(TTree&, utils::BranchList const&) override;')
        header.writeline('utils::BranchList doGetStatus_(TTree&) const override;')
        header.writeline('utils::BranchList doGetBranchNames_() const override;')
        header.writeline('void doSetAddress_(TTree&, utils::BranchList const&, Bool_t setStatus) override;')
        header.writeline('void doBook_(TTree&, utils::BranchList const&) override;')
        header.writeline('void doGetEntry_(Long64_t) override;')
        header.writeline('void doReleaseTree_(TTree&) override;')
        header.writeline('void doInit_() override;')

        header.newline()
        header.indent -= 1
        header.writeline('public:')
        header.indent += 1
        header.write_custom_block('{name}.h.classdef'.format(name = self.name))

        header.indent -= 1

        header.writeline('};')

        header.newline()
        header.write_custom_block('{name}.h.global'.format(name = self.name))

        header.newline()

        header.indent -= 1
        header.writeline('}')
        header.newline()

        header.writeline('#endif')
        header.close()

    def generate_source(self):
        """
        Write the .cc file.
        """

        src = FileOutput('{PACKDIR}/Objects/src/{name}.cc'.format(PACKDIR = PACKDIR, name = self.name))
        src.writeline('#include "../interface/{name}.h"'.format(name = self.name))
        src.newline()

        src.writeline('{NAMESPACE}::{name}::{name}() :'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.indent += 1
        src.writeline('TreeEntry("{name}")'.format(name = self.name))
        src.indent -= 1
        src.writeline('{')
        src.indent += 1
        if len(self.objbranches) != 0:
            src.writeline('objects_ = {' + ', '.join(['&{name}'.format(name = b.name) for b in self.objbranches]) + '};')
            src.writeline('collections_ = {' + ', '.join(['&{name}'.format(name = b.name) for b in self.objbranches if b.conttype == 'Collection']) + '};')
            src.newline()
            
        for ref in self.references:
            ref.write_def(src, self.objbranches)
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('{NAMESPACE}::{name}::{name}({name} const& _src) :'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.indent += 1
        initializers = ['TreeEntry(_src.getName())']
        for objbranch in self.objbranches:
            initializers.append(objbranch.cpyctor())
        for branch in self.branches:
            branch.init_copy(initializers, context = 'TreeEntry')
        src.writelines(initializers, ',')
        src.indent -= 1
        src.writeline('{')
        src.indent += 1
        if len(self.objbranches) != 0:
            src.writeline('objects_ = {' + ', '.join(['&{name}'.format(name = b.name) for b in self.objbranches]) + '};')
            src.writeline('collections_ = {' + ', '.join(['&{name}'.format(name = b.name) for b in self.objbranches if b.conttype == 'Collection']) + '};')
            src.newline()
        for branch in self.branches:
            if branch.is_array():
                branch.write_assign(src, context = 'TreeEntry')
        for ref in self.references:
            ref.write_def(src, self.objbranches)
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('{NAMESPACE}::{name}&'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{NAMESPACE}::{name}::operator=({name} const& _src)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        if len(self.branches) != 0:
            for branch in self.branches:
                branch.write_assign(src, context = 'TreeEntry')
            src.newline()
        if len(self.objbranches) != 0:
            for objbranch in self.objbranches:
                objbranch.write_assign(src)
            src.newline()
        if len(self.references) != 0:
            for ref in self.references:
                ref.write_def(src, self.objbranches)
            src.newline()
        src.writeline('return *this;')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*static*/')
        src.writeline('panda::utils::BranchList')
        src.writeline('{NAMESPACE}::{name}::getListOfBranches()'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        src.writeline('utils::BranchList blist;')
        src.writeline('blist += {{{bnames}}};'.format(bnames = ', '.join('"{name}"'.format(name = branch.name) for branch in self.branches if '!' not in branch.modifier)))
        for objbranch in self.objbranches:
            src.writeline('blist += {otype}::getListOfBranches().fullNames("{name}");'.format(otype = objbranch.objname, name = objbranch.name))
        src.writeline('return blist;')
        src.indent -= 1
        src.writeline('}')

        src.writeline('/*protected*/')
        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doSetStatus_(TTree& _tree, utils::BranchList const& _branches)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        for branch in self.branches:
            branch.write_set_status(src, context = 'TreeEntry')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('panda::utils::BranchList')
        src.writeline('{NAMESPACE}::{name}::doGetStatus_(TTree& _tree) const'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        src.writeline('utils::BranchList blist;')
        src.newline()
        for branch in self.branches:
            branch.write_get_status(src, context = 'TreeEntry')
        src.writeline('return blist;')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('panda::utils::BranchList')
        src.writeline('{NAMESPACE}::{name}::doGetBranchNames_() const'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        src.writeline('return getListOfBranches();')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doSetAddress_(TTree& _tree, utils::BranchList const& _branches, Bool_t _setStatus)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        for branch in self.branches:
            branch.write_set_address(src, context = 'TreeEntry')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doBook_(TTree& _tree, utils::BranchList const& _branches)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        for branch in self.branches:
            branch.write_book(src, context = 'TreeEntry')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doGetEntry_(Long64_t _entry)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        src.write_custom_block('{name}.cc.doGetEntry_'.format(name = self.name))
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('/*protected*/')
        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doReleaseTree_(TTree& _tree)'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        for branch in self.branches:
            branch.write_release_tree(src, context = 'TreeEntry')
        src.indent -= 1
        src.writeline('}')
        src.newline()

        src.writeline('void')
        src.writeline('{NAMESPACE}::{name}::doInit_()'.format(NAMESPACE = NAMESPACE, name = self.name))
        src.writeline('{')
        src.indent += 1
        for branch in self.branches:
            branch.write_init(src, context = 'TreeEntry')

        src.write_custom_block('{name}.cc.doInit_'.format(name = self.name))
        src.indent -= 1
        src.writeline('}')
        src.newline()

        if len(self.functions) != 0:
            src.newline()
            for function in self.functions:
                function.write_def(src, context = self.name)

        src.newline()
        src.write_custom_block('{name}.cc.global'.format(name = self.name))

        src.close()
