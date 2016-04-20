#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "xxx.h"
#include "classdef.h"
#include "language.h"
#include "translator_en.h"

using namespace std;


#define WRITE_ELEMENT(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method "</comment>\n" \
            "        <source>" << trEn.method() << "</source>\n" \
            "        <translation>" << theTranslator->method() << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_WITH_C_OPTIMIZATION(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method "</comment>\n" \
            "        <source>" << trEn.method() << "</source>\n" \
            "        <translation>" << theTranslator->method() << "</translation>\n" \
            "    </message>\n"; \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    fout << "    <message>\n" \
            "        <comment>" #method " OPTIMIZE_OUTPUT_FOR_C</comment>\n" \
            "        <source>" << trEn.method() << "</source>\n" \
            "        <translation>" << theTranslator->method() << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_EXTRACTALL(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method " DontExtractAll</comment>\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method " ExtractAll</comment>\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_SINGULAR(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method " Plural</comment>\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method " Singular</comment>\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}


#define WRITE_ELEMENT_ENABLE(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method " Disabled</comment>\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method " Enabled</comment>\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}


#define WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method " DontExtractAll</comment>\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method " ExtractAll</comment>\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    fout << "    <message>\n" \
            "        <comment>" #method " DontExtractAll OPTIMIZE_OUTPUT_FOR_C</comment>\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method " ExtractAll OPTIMIZE_OUTPUT_FOR_C</comment>\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}


#define WRITE_ELEMENT1(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method "</comment>\n" \
            "        <source>" << trEn.method("%1") << "</source>\n" \
            "        <translation>" << theTranslator->method("%1") << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT1REF(method)\
{ \
    QCString a{"%1"}; \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method "</comment>\n" \
            "        <source>" << trEn.method(a) << "</source>\n" \
            "        <translation>" << theTranslator->method(a) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT1INT(method)\
{ \
    Config_setBool(false);                                          \
    for (int i = 1; i < 4; ++i)                                     \
    {                                                               \
        string en{ trEn.method(i) };                                \
        string::size_type pos;                                      \
        pos = en.find("@0");                                        \
        if (pos != string::npos) { en.replace(pos, 2, "%1"); }      \
                                                                    \
        string tr{ theTranslator->method(i) };                      \
        pos = tr.find("@0");                                        \
        if (pos != string::npos) { tr.replace(pos, 2, "%1"); }      \
                                                                    \
        fout << "    <message>\n"                                   \
            "        <comment>" #method " 1</comment>\n"            \
            "        <source>" << en << "</source>\n"               \
            "        <translation>" << tr << "</translation>\n"     \
            "    </message>\n";                                     \
    }                                                               \
}

#define WRITE_ELEMENT2(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method "</comment>\n" \
            "        <source>" << trEn.method("%1", "%2") << "</source>\n" \
            "        <translation>" << theTranslator->method("%1", "%2") << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(method)\
{ \
    Config_setBool(false); \
    std::string result{ "Undefined" }; \
    for (auto compType: list<ClassDef::CompoundType>{ ClassDef::Class, ClassDef::Struct, ClassDef::Union, ClassDef::Interface, \
	                      ClassDef::Protocol, ClassDef::Category, ClassDef::Exception }) { \
		switch (compType)                                       \
		{														\
		case ClassDef::Class:      result = "Class"; break;		\
		case ClassDef::Struct:     result = "Struct"; break;	\
		case ClassDef::Union:      result = "Union"; break;		\
		case ClassDef::Interface:  result = "Interface"; break;	\
		case ClassDef::Protocol:   result = "Protocol"; break;	\
		case ClassDef::Category:   result = "Category"; break;	\
		case ClassDef::Exception:  result = "Exception"; break;	\
		default: break;											\
		}														\
        fout << "    <message>\n" \
                "        <comment>" #method " Plural</comment>\n" \
                "        <source>" << trEn.method(compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method(compType, false) << "</translation>\n" \
                "    </message>\n"; \
        fout << "    <message>\n" \
                "        <comment>" #method " Singular</comment>\n" \
                "        <source>" << trEn.method(compType, true) << "</source>\n" \
                "        <translation>" << theTranslator->method(compType, true) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(method)\
{ \
    Config_setBool(false); \
    std::string result{ "Undefined" }; \
    for (auto compType: list<ClassDef::CompoundType>{ ClassDef::Class, ClassDef::Struct, ClassDef::Union, ClassDef::Interface, \
	                      ClassDef::Protocol, ClassDef::Category, ClassDef::Exception }) { \
		switch (compType)                                       \
		{														\
		case ClassDef::Class:      result = "Class"; break;		\
		case ClassDef::Struct:     result = "Struct"; break;	\
		case ClassDef::Union:      result = "Union"; break;		\
		case ClassDef::Interface:  result = "Interface"; break;	\
		case ClassDef::Protocol:   result = "Protocol"; break;	\
		case ClassDef::Category:   result = "Category"; break;	\
		case ClassDef::Exception:  result = "Exception"; break;	\
		default: break;											\
		}														\
        fout << "    <message>\n" \
                "        <comment>" #method << result << " NotTemplate</comment>\n" \
                "        <source>" << trEn.method("%1", compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method("%1", compType, false) << "</translation>\n" \
                "    </message>\n"; \
        fout << "    <message>\n" \
                "        <comment>" #method << result << " IsTemplate</comment>\n" \
                "        <source>" << trEn.method("%1", compType, true) << "</source>\n" \
                "        <translation>" << theTranslator->method("%1", compType, true) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(method)\
{ \
    Config_setBool(false); \
    fout << "    <message>\n" \
            "        <comment>" #method << " FirstCapital Singular</comment>\n" \
            "        <source>" << trEn.method(true, true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true, true) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method << " FirstCapital Plural</comment>\n" \
            "        <source>" << trEn.method(true, false) << "</source>\n" \
            "        <translation>" << theTranslator->method(true, false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method << " FirstSmall Singular</comment>\n" \
            "        <source>" << trEn.method(false, true) << "</source>\n" \
            "        <translation>" << theTranslator->method(false, true) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message>\n" \
            "        <comment>" #method << " FirstSmall Plural</comment>\n" \
            "        <source>" << trEn.method(false, false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false, false) << "</translation>\n" \
            "    </message>\n"; \
}



void GenerateTranslatorSentences(const std::string& lang_readable,
                                 const std::string& fname_suffix,
                                 const std::string& xx_XX = "")
{
    cerr << "Generating sentence definitions for " << lang_readable << " ... ";

    // Construct the File Name, and open the file for writing.
    string fname{ "doxy_" + fname_suffix + ".ts2" };
    ofstream  fout(fname);

    // If the file could not be open, finish with error message.
    if (!fout.is_open())
    {
        cerr << "Open for output to '" << fname << "' failed.\n";
        exit(1);
    }

    // File was open for writing. Generate the output.
    //
    // If the translator object exists, delete it. New one will
    // be created immediately.
    if (theTranslator != nullptr)
        delete theTranslator;

    // Create the translator object for the language (and also the English one).
    setTranslator(lang_readable);
    TranslatorEnglish trEn;

    //------------------------------------------------------------------------------------
    // The document heading.
    fout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<!DOCTYPE TS>\n"
            "<TS version=\"2.0\"";
    if (!xx_XX.empty())
    {
        fout << " language=\"" << xx_XX << "\"";
    }
    fout << ">\n";
    
    //------------------------------------------------------------------------------------
    // The RTF context
    fout << "<context>\n"
            "    <name>doxy-rtf</name>\n";


    WRITE_ELEMENT(trRTFansicp);
    WRITE_ELEMENT(trRTFCharSet);

    fout << "</context>\n";

    //------------------------------------------------------------------------------------
    // The Text context.
    fout << "<context>\n"
            "    <name>doxy-text</name>\n";

    // Some tricks from the older code (throw it away after clarification).
#if 0
    
    fout << "\n<! --trWriteList() should be replaced using\n"
        "     &trLSep;, &trLSepAnd2;, and &trLSepAnd; sentences\n\n";

    WriteSentence(fout, "trWriteList1", theTranslator->trWriteList(1));
    WriteSentence(fout, "trWriteList2", theTranslator->trWriteList(2));
    WriteSentence(fout, "trWriteList3", theTranslator->trWriteList(3));

    fout << "-->\n\n";

    // Extract the separator definitions.
    //
    std::string sAnd(theTranslator->trWriteList(3));
    std::string s;

    std::string::size_type pos = sAnd.find("@1");
    s = sAnd.substr(2, pos-2);

    sAnd.erase(0, pos+2);
    pos = sAnd.find("@2");
    sAnd.erase(pos);

    std::string sAnd2(theTranslator->trWriteList(2));

    pos = sAnd2.find("@1");
    sAnd2.erase(pos);
    sAnd2.erase(0, 2);

    WriteSentence(fout, "trLSep", s);
    WriteSentence(fout, "trLSepAnd", sAnd);
    WriteSentence(fout, "trLSepAnd2", sAnd2);

    fout << "\n<!-- Should be normal Sentence templates instead using "
        "trWriteList inside -->\n\n";

    // The original.
    //
    fout << "<!--\n";
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(1));
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(2));
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(3));
    fout << "-->\n";

    // Two entitities possible -- inheriting from one and many.
    //
    s = theTranslator->trInheritsList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trInherits", s);

    s = theTranslator->trInheritsList(2);
    pos = s.find("@0");
    std::string::size_type pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trInheritsList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(1));
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(2));
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(3));
    fout << "-->\n";

    s = theTranslator->trInheritedByList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trInheritedBy", s);

    s = theTranslator->trInheritedByList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trInheritedByList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(1));
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(2));
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(3));
    fout << "-->\n";

    s = theTranslator->trReimplementedFromList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trReimplementedFrom", s);

    s = theTranslator->trReimplementedFromList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trReimplementedFromList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(1));
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(2));
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(3));
    fout << "-->\n";

    s = theTranslator->trReimplementedInList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trReimplementedIn", s);

    s = theTranslator->trReimplementedInList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trReimplementedInList", s);
    //-----------------------------------------------------------------
#endif


    // The following source was taken directly from the translator.h,
	// (at the time of Doxygen version 1.8.12) and the
    // virtual method identifies were wrapped to the macros. In cases when
    // the OPTIMIZE_OUTPUT_FOR_C setting makes a difference, the method was
    // called twice with different macros. In cases when the method produces
    // a different message based on a boolean argument, the macro variations
	// for True and False was called. Some macros combine the "optimize for C"
	// with the boolean argument.
	//
	// When the method argument is to be inserted into the message as a value
	// (e.g. name of a method), the placeholder like "%1" is passed to the macro.

    //////////////////////////////////////////
    // --- Language control methods -------------------

    WRITE_ELEMENT(idLanguage);
    WRITE_ELEMENT(latexLanguageSupportCommand);

    // --- Language translation methods -------------------

    WRITE_ELEMENT(trRelatedFunctions);
    WRITE_ELEMENT(trRelatedSubscript);
    WRITE_ELEMENT(trDetailedDescription);
    WRITE_ELEMENT(trMemberTypedefDocumentation);
    WRITE_ELEMENT(trMemberEnumerationDocumentation);
    WRITE_ELEMENT(trMemberFunctionDocumentation);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trMemberDataDocumentation);
    WRITE_ELEMENT(trMore);
    WRITE_ELEMENT(trListOfAllMembers);
    WRITE_ELEMENT(trMemberList);
    WRITE_ELEMENT(trThisIsTheListOfAllMembers);
    WRITE_ELEMENT(trIncludingInheritedMembers);
    WRITE_ELEMENT1(trGeneratedAutomatically);
    WRITE_ELEMENT(trEnumName);
    WRITE_ELEMENT(trEnumValue);
    WRITE_ELEMENT(trDefinedIn);


    // quick reference sections

    WRITE_ELEMENT(trModules);
    WRITE_ELEMENT(trClassHierarchy);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundList);
    WRITE_ELEMENT(trFileList);
    WRITE_ELEMENT(trCompoundMembers);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trFileMembers);
    WRITE_ELEMENT(trRelatedPages);
    WRITE_ELEMENT(trExamples);
    WRITE_ELEMENT(trSearch);
    WRITE_ELEMENT(trClassHierarchyDescription);
    WRITE_ELEMENT_EXTRACTALL(trFileListDescription);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundListDescription);
    WRITE_ELEMENT_EXTRACTALL(trCompoundMembersDescription);
    WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(trFileMembersDescription);

    WRITE_ELEMENT(trExamplesDescription);
    WRITE_ELEMENT(trRelatedPagesDescription);
    WRITE_ELEMENT(trModulesDescription);


    // index titles (the project name is prepended for these)

    WRITE_ELEMENT(trDocumentation);
    WRITE_ELEMENT(trModuleIndex);
    WRITE_ELEMENT(trHierarchicalIndex);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundIndex);
	WRITE_ELEMENT(trFileIndex);
    WRITE_ELEMENT(trModuleDocumentation);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trClassDocumentation);
	WRITE_ELEMENT(trFileDocumentation);
    WRITE_ELEMENT(trExampleDocumentation);
    WRITE_ELEMENT(trPageDocumentation);
    WRITE_ELEMENT(trReferenceManual);
    WRITE_ELEMENT(trDefines);
    WRITE_ELEMENT(trTypedefs);
    WRITE_ELEMENT(trEnumerations);
    WRITE_ELEMENT(trFunctions);
    WRITE_ELEMENT(trVariables);
    WRITE_ELEMENT(trEnumerationValues);
    WRITE_ELEMENT(trDefineDocumentation);
    WRITE_ELEMENT(trTypedefDocumentation);
    WRITE_ELEMENT(trEnumerationTypeDocumentation);
    WRITE_ELEMENT(trFunctionDocumentation);
    WRITE_ELEMENT(trVariableDocumentation);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompounds);
	WRITE_ELEMENT2(trGeneratedAt);
	WRITE_ELEMENT1(trClassDiagram);
	WRITE_ELEMENT(trForInternalUseOnly);
    WRITE_ELEMENT(trWarning);
    WRITE_ELEMENT(trVersion);
    WRITE_ELEMENT(trDate);
    WRITE_ELEMENT(trReturns);
    WRITE_ELEMENT(trSeeAlso);
    WRITE_ELEMENT(trParameters);
    WRITE_ELEMENT(trExceptions);
    WRITE_ELEMENT(trGeneratedBy);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990307
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNamespaceList);
	WRITE_ELEMENT_EXTRACTALL(trNamespaceListDescription);
	WRITE_ELEMENT(trFriends);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990405
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRelatedFunctionDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990425
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(trCompoundReference);
	WRITE_ELEMENT1(trFileReference);
    WRITE_ELEMENT1(trNamespaceReference);

    WRITE_ELEMENT(trPublicMembers);
    WRITE_ELEMENT(trPublicSlots);
    WRITE_ELEMENT(trSignals);
    WRITE_ELEMENT(trStaticPublicMembers);
    WRITE_ELEMENT(trProtectedMembers);
    WRITE_ELEMENT(trProtectedSlots);
    WRITE_ELEMENT(trStaticProtectedMembers);
    WRITE_ELEMENT(trPrivateMembers);
    WRITE_ELEMENT(trPrivateSlots);
    WRITE_ELEMENT(trStaticPrivateMembers);
    WRITE_ELEMENT1INT(trWriteList);
    WRITE_ELEMENT1INT(trInheritsList);
    WRITE_ELEMENT1INT(trInheritedByList);
    WRITE_ELEMENT1INT(trReimplementedFromList);
    WRITE_ELEMENT1INT(trReimplementedInList);
    WRITE_ELEMENT(trNamespaceMembers);
	WRITE_ELEMENT_EXTRACTALL(trNamespaceMemberDescription);
	WRITE_ELEMENT(trNamespaceIndex);
    WRITE_ELEMENT(trNamespaceDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990522
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNamespaces);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990728
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(trGeneratedFromFiles);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990901
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReturnValues);
    WRITE_ELEMENT(trMainPage);
    WRITE_ELEMENT(trPageAbbreviation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-991003
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDefinedAtLineInSourceFile);
    WRITE_ELEMENT(trDefinedInSourceFile);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.0.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trCollaborationDiagram);
    WRITE_ELEMENT1(trInclDepGraph);
    WRITE_ELEMENT(trConstructorDocumentation);
    WRITE_ELEMENT(trGotoSourceCode);
    WRITE_ELEMENT(trGotoDocumentation);
    WRITE_ELEMENT(trPrecondition);
    WRITE_ELEMENT(trPostcondition);
    WRITE_ELEMENT(trInvariant);
    WRITE_ELEMENT(trInitialValue);
    WRITE_ELEMENT(trCode);

    WRITE_ELEMENT(trGraphicalHierarchy);
    WRITE_ELEMENT(trGotoGraphicalHierarchy);
    WRITE_ELEMENT(trGotoTextualHierarchy);
    WRITE_ELEMENT(trPageIndex);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNote);
    WRITE_ELEMENT(trPublicTypes);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trPublicAttribs);
	WRITE_ELEMENT(trStaticPublicAttribs);
    WRITE_ELEMENT(trProtectedTypes);
    WRITE_ELEMENT(trProtectedAttribs);
    WRITE_ELEMENT(trStaticProtectedAttribs);
    WRITE_ELEMENT(trPrivateTypes);
    WRITE_ELEMENT(trPrivateAttribs);
    WRITE_ELEMENT(trStaticPrivateAttribs);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReferencedBy);
    WRITE_ELEMENT(trRemarks);
    WRITE_ELEMENT(trAttention);
    WRITE_ELEMENT(trInclByDepGraph);
    WRITE_ELEMENT(trSince);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trLegendTitle);
    WRITE_ELEMENT(trLegendDocs);
    WRITE_ELEMENT(trLegend);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trProperties);
    WRITE_ELEMENT(trPropertyDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trClasses);
    WRITE_ELEMENT1(trPackage);
    WRITE_ELEMENT(trPackageList);
    WRITE_ELEMENT(trPackageListDescription);
    WRITE_ELEMENT(trPackages);
    WRITE_ELEMENT(trDefineValue);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.6
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRTFGeneralIndex);

    // Translation of the word

    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trClass);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trFile);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trNamespace);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trGroup);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trPage);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trMember);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trGlobal);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.7
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trAuthor);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.11
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReferences);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.13
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1INT(trImplementedFromList);
    WRITE_ELEMENT1INT(trImplementedInList);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.16
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRTFTableOfContents);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.18
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trEvents);
    WRITE_ELEMENT(trEventDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trPackageTypes);
    WRITE_ELEMENT(trPackageMembers);
    WRITE_ELEMENT(trStaticPackageMembers);
    WRITE_ELEMENT(trPackageAttribs);
    WRITE_ELEMENT(trStaticPackageAttribs);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.1
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trAll);
    WRITE_ELEMENT(trCallGraph);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trSearchResultsTitle);
    WRITE_ELEMENT1INT(trSearchResults);
    WRITE_ELEMENT(trSearchMatches);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.8
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT1REF(trSourceFile);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.9
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDirIndex);
    WRITE_ELEMENT(trDirDocumentation);
    WRITE_ELEMENT(trDirectories);
    WRITE_ELEMENT(trDirDescription);
    WRITE_ELEMENT1(trDirReference);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trDir);

	//////////////////////////////////////////////////////////////////////////
    // new since 1.4.1
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trOverloadText);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.4.6
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCallerGraph);
    WRITE_ELEMENT(trEnumerationValueDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.5.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trMemberFunctionDocumentationFortran);
    WRITE_ELEMENT(trCompoundListFortran);
    WRITE_ELEMENT(trCompoundMembersFortran);
    WRITE_ELEMENT(trCompoundListDescriptionFortran);
    WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(trCompoundMembersDescriptionFortran);
    WRITE_ELEMENT(trCompoundIndexFortran);
    WRITE_ELEMENT(trTypeDocumentation);
    WRITE_ELEMENT(trSubprograms);
    WRITE_ELEMENT(trSubprogramDocumentation);
    WRITE_ELEMENT(trDataTypes);
    WRITE_ELEMENT(trModulesList);
    WRITE_ELEMENT_EXTRACTALL(trModulesListDescription);
    WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(trCompoundReferenceFortran);
    WRITE_ELEMENT1(trModuleReference);
    WRITE_ELEMENT(trModulesMembers);
    WRITE_ELEMENT_EXTRACTALL(trModulesMemberDescription);
    WRITE_ELEMENT(trModulesIndex);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trModule);
    WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(trGeneratedFromFilesFortran);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trType);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trSubprogram);
    WRITE_ELEMENT(trTypeConstraints);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trDirRelation);
    WRITE_ELEMENT(trLoading);
    WRITE_ELEMENT(trGlobalNamespace);
    WRITE_ELEMENT(trSearching);
    WRITE_ELEMENT(trNoMatches);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trFileIn);
    WRITE_ELEMENT1(trIncludesFileIn);
    ///??? virtual QCString trDateTime(int year, int month, int day, int dayOfWeek,
    ///???     int hour, int minutes, int seconds, trFileMembersDescription
    ///???     bool includeTime) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.7.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCiteReferences);
    WRITE_ELEMENT(trCopyright);
    WRITE_ELEMENT1(trDirDepGraph);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDetailLevel);
    WRITE_ELEMENT(trTemplateParameters);
    WRITE_ELEMENT1(trAndMore);
    WRITE_ELEMENT_SINGULAR(trEnumGeneratedFromFiles);
    WRITE_ELEMENT1(trEnumReference);
    WRITE_ELEMENT2(trInheritedFrom);
    WRITE_ELEMENT(trAdditionalInheritedMembers);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT_ENABLE(trPanelSynchronisationTooltip);
    WRITE_ELEMENT(trProvidedByCategory);
    WRITE_ELEMENT(trExtendsClass);
    WRITE_ELEMENT(trClassMethods);
    WRITE_ELEMENT(trInstanceMethods);
    WRITE_ELEMENT(trMethodDocumentation);
    WRITE_ELEMENT(trDesignOverview);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trInterfaces);
    WRITE_ELEMENT(trServices);
    WRITE_ELEMENT(trConstantGroups);
    WRITE_ELEMENT1(trConstantGroupReference);
    WRITE_ELEMENT1(trServiceReference);
    WRITE_ELEMENT1(trSingletonReference);
    WRITE_ELEMENT_SINGULAR(trServiceGeneratedFromFiles);
    WRITE_ELEMENT_SINGULAR(trSingletonGeneratedFromFiles);

    //----------------------------------------------------------------------
    fout << "</context>\n";
    fout.close();

    std::cerr << "\n";
}


int main()
{
    /// GenerateTranslatorSentences("afrikaans");
    /// GenerateTranslatorSentences("arabic");
    /// GenerateTranslatorSentences("armenian");
    /// GenerateTranslatorSentences("brazilian");
    /// GenerateTranslatorSentences("catalan");
    /// GenerateTranslatorSentences("chinese");
    /// GenerateTranslatorSentences("chinese-traditional");
    /// GenerateTranslatorSentences("croatian");
    GenerateTranslatorSentences("czech", "cz", "cs_CZ");
    /// GenerateTranslatorSentences("danish");
    GenerateTranslatorSentences("dutch", "nl", "nl_NL");
    GenerateTranslatorSentences("english", "en", "en_EN");
    /// GenerateTranslatorSentences("esperanto");
    /// GenerateTranslatorSentences("finnish");
    /// GenerateTranslatorSentences("french");
    GenerateTranslatorSentences("german", "de", "de_DE");
    /// GenerateTranslatorSentences("greek");
    /// GenerateTranslatorSentences("hungarian");
    /// GenerateTranslatorSentences("indonesian");
    /// GenerateTranslatorSentences("italian");
    /// GenerateTranslatorSentences("japanese");
    /// GenerateTranslatorSentences("japanese-en");
    /// GenerateTranslatorSentences("korean");
    /// GenerateTranslatorSentences("korean-en");
    /// GenerateTranslatorSentences("latvian");
    /// GenerateTranslatorSentences("lithuanian");
    /// GenerateTranslatorSentences("macedonian");
    /// GenerateTranslatorSentences("norwegian");
    /// GenerateTranslatorSentences("persian");
    /// GenerateTranslatorSentences("polish");
    /// GenerateTranslatorSentences("portuguese");
    /// GenerateTranslatorSentences("romanian");
    /// GenerateTranslatorSentences("russian");
    /// GenerateTranslatorSentences("serbian");
    /// GenerateTranslatorSentences("serbian-cyrillic");
    /// GenerateTranslatorSentences("slovak");
    /// GenerateTranslatorSentences("slovene");
    /// GenerateTranslatorSentences("spanish");
    /// GenerateTranslatorSentences("swedish");
    /// GenerateTranslatorSentences("turkish");
    /// GenerateTranslatorSentences("ukrainian");
    /// GenerateTranslatorSentences("vietnamese");


	return 0;
}
