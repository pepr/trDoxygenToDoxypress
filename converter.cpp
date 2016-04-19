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
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "\">\n" \
            "        <source>" << trEn.method() << "</source>\n" \
            "        <translation>" << theTranslator->method() << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_C(method)\
{ \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    fout << "    <message method=\"" #method "C\">\n" \
            "        <source>" << trEn.method() << "</source>\n" \
            "        <translation>" << theTranslator->method() << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_F(method)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "F\">\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_T(method)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "T\">\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_EXTRACTALL(method)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "-DontExtractAll\">\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message method=\"" #method "-ExtractAll\">\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}


#define WRITE_ELEMENT_FC(method)\
{ \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    fout << "    <message method=\"" #method "FC\">\n" \
            "        <source>" << trEn.method(false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_TC(method)\
{ \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    fout << "    <message method=\"" #method "TC\">\n" \
            "        <source>" << trEn.method(true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT1(method, arg)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "\">\n" \
            "        <source>" << trEn.method(arg) << "</source>\n" \
            "        <translation>" << theTranslator->method(arg) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT1REF(method, arg)\
{ \
    QCString a{arg}; \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "\">\n" \
            "        <source>" << trEn.method(a) << "</source>\n" \
            "        <translation>" << theTranslator->method(a) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT1INT(method, arg)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "\">\n" \
            "        <source>" << trEn.method(arg) << "</source>\n" \
            "        <translation>" << theTranslator->method(arg) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT2(method, a1, a2)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "\">\n" \
            "        <source>" << trEn.method(a1, a2) << "</source>\n" \
            "        <translation>" << theTranslator->method(a1, a2) << "</translation>\n" \
            "    </message>\n"; \
}

#define WRITE_ELEMENT_COMPOUNDTYPE_F(method)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
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
        fout << "    <message method=\"" #method << result << "F\">\n" \
                "        <source>" << trEn.method(compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method(compType, false) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_COMPOUNDTYPE_T(method)\
{ \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
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
        fout << "    <message method=\"" #method << result << "T\">\n" \
                "        <source>" << trEn.method(compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method(compType, false) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_COMPOUNDTYPE_1_F(method, a1)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
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
        fout << "    <message method=\"" #method << result << "F\">\n" \
                "        <source>" << trEn.method(a1, compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method(a1, compType, false) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_COMPOUNDTYPE_1_T(method, a1)\
{ \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
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
        fout << "    <message method=\"" #method << result << "T\">\n" \
                "        <source>" << trEn.method(a1, compType, false) << "</source>\n" \
                "        <translation>" << theTranslator->method(a1, compType, false) << "</translation>\n" \
                "    </message>\n"; \
	} \
}


#define WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(method)\
{ \
    Config_setBool(false); /* emulate OPTIMIZE_OUTPUT_FOR_C is False */ \
    fout << "    <message method=\"" #method "-FirstCapitalSingular\">\n" \
            "        <source>" << trEn.method(true, true) << "</source>\n" \
            "        <translation>" << theTranslator->method(true, true) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message method=\"" #method "-FirstCapitalPlural\">\n" \
            "        <source>" << trEn.method(true, false) << "</source>\n" \
            "        <translation>" << theTranslator->method(true, false) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message method=\"" #method "-FirstSmallSingular\">\n" \
            "        <source>" << trEn.method(false, true) << "</source>\n" \
            "        <translation>" << theTranslator->method(false, true) << "</translation>\n" \
            "    </message>\n"; \
    fout << "    <message method=\"" #method "-FirstSmallPlural\">\n" \
            "        <source>" << trEn.method(false, false) << "</source>\n" \
            "        <translation>" << theTranslator->method(false, false) << "</translation>\n" \
            "    </message>\n"; \
}



void GenerateTranslatorSentences(const string & sLang)
{
    cerr << "Generating sentence definitions for " << sLang << " ... ";

    // Construct the File Name.
    string fname{ "doxy_" + sLang + ".ts2" };

    // Open the file for writing.
    ofstream  fout(fname);

    // If the file could not be open, finish with error message.
    if (! fout.is_open())
    {
        cerr << "Open for output to " << fname << " failed.\n";
        exit(1);
    }

    // File was open for writing. Generate the output.
    //
    // If the translator object exists, delete it. New one will
    // be created immediately.
    if (theTranslator != nullptr)
        delete theTranslator;

    // Set the language.
    setTranslator(sLang);
    TranslatorEnglish trEn;

    //------------------------------------------------------------------------------------
    fout << "Language id: " << sLang << "\n";
    fout << "<context>\n"
            "    <name>doxy-text</name>\n";

    //WRITE_ELEMENT(idLanguage);

#if 0
    fout << "<!-- Simple sentences -->\n\n";

    WriteSentence(fout, "trReferences",
        theTranslator->trReferences());

///    WriteSentence(fout, "trAlphabeticalList",
///        theTranslator->trAlphabeticalList());

    WriteSentence(fout, "idLanguage",
        theTranslator->idLanguage());

    WriteSentence(fout, "latexLanguageSupportCommand",
        theTranslator->latexLanguageSupportCommand());

///    WriteSentence(fout, "idLanguageCharset",
///        theTranslator->idLanguageCharset());

    WriteSentence(fout, "trRelatedFunctions",
        theTranslator->trRelatedFunctions());

    WriteSentence(fout, "trRelatedSubscript",
        theTranslator->trRelatedSubscript());

    WriteSentence(fout, "trDetailedDescription",
        theTranslator->trDetailedDescription());

    WriteSentence(fout, "trMemberTypedefDocumentation",
        theTranslator->trMemberTypedefDocumentation());

    WriteSentence(fout, "trMemberEnumerationDocumentation",
        theTranslator->trMemberEnumerationDocumentation());

    WriteSentence(fout, "trMemberFunctionDocumentation",
        theTranslator->trMemberFunctionDocumentation());

    Config_setBool(true);
    WriteSentence(fout, "trMemberDataDocumentationC",
        theTranslator->trMemberDataDocumentation());

    Config_setBool(false);
    WriteSentence(fout, "trMemberDataDocumentation",
        theTranslator->trMemberDataDocumentation());

    WriteSentence(fout, "trMore",
        theTranslator->trMore());

    WriteSentence(fout, "trListOfAllMembers",
        theTranslator->trListOfAllMembers());

    WriteSentence(fout, "trMemberList",
        theTranslator->trMemberList());

    WriteSentence(fout, "trEnumName",
        theTranslator->trEnumName());

    WriteSentence(fout, "trEnumValue",
        theTranslator->trEnumValue());

    WriteSentence(fout, "trDefinedIn",
        theTranslator->trDefinedIn());

    WriteSentence(fout, "trModules",
        theTranslator->trModules());

    WriteSentence(fout, "trClassHierarchy",
        theTranslator->trClassHierarchy());

    Config_setBool(true);
    WriteSentence(fout, "trCompoundListC",
        theTranslator->trCompoundList());

    Config_setBool(false);
    WriteSentence(fout, "trCompoundList",
        theTranslator->trCompoundList());

    WriteSentence(fout, "trFileList",
        theTranslator->trFileList());

///    Config_setBool(true);
///    WriteSentence(fout, "trHeaderFilesC",
///        theTranslator->trHeaderFiles());
///
///    Config_setBool(false);
///    WriteSentence(fout, "trHeaderFiles",
///        theTranslator->trHeaderFiles());

    WriteSentence(fout, "trCompoundMembers",
        theTranslator->trCompoundMembers());

    Config_setBool(true);
    WriteSentence(fout, "trFileMembersC",
        theTranslator->trFileMembers());

    Config_setBool(false);
    WriteSentence(fout, "trFileMembers",
        theTranslator->trFileMembers());

    WriteSentence(fout, "trRelatedPages",
        theTranslator->trRelatedPages());

    WriteSentence(fout, "trExamples",
        theTranslator->trExamples());

    WriteSentence(fout, "trSearch",
        theTranslator->trSearch());

    WriteSentence(fout, "trClassHierarchyDescription",
        theTranslator->trClassHierarchyDescription());

    Config_setBool(true);
    WriteSentence(fout, "trCompoundListDescriptionC",
        theTranslator->trCompoundListDescription());

    Config_setBool(false);
    WriteSentence(fout, "trCompoundListDescription",
        theTranslator->trCompoundListDescription());

///    WriteSentence(fout, "trHeaderFilesDescription",
///        theTranslator->trHeaderFilesDescription());

    WriteSentence(fout, "trExamplesDescription",
        theTranslator->trExamplesDescription());

    WriteSentence(fout, "trRelatedPagesDescription",
        theTranslator->trRelatedPagesDescription());

    WriteSentence(fout, "trModulesDescription",
        theTranslator->trModulesDescription());

///    WriteSentence(fout, "trNoDescriptionAvailable",
///        theTranslator->trNoDescriptionAvailable());

    WriteSentence(fout, "trDocumentation",
        theTranslator->trDocumentation());

    WriteSentence(fout, "trModuleIndex",
        theTranslator->trModuleIndex());

    WriteSentence(fout, "trHierarchicalIndex",
        theTranslator->trHierarchicalIndex());

    Config_setBool(true);
    WriteSentence(fout, "trCompoundIndexC",
        theTranslator->trCompoundIndex());

    Config_setBool(false);
    WriteSentence(fout, "trCompoundIndex",
        theTranslator->trCompoundIndex());

    WriteSentence(fout, "trFileIndex",
        theTranslator->trFileIndex());

    WriteSentence(fout, "trModuleDocumentation",
        theTranslator->trModuleDocumentation());

    Config_setBool(true);
    WriteSentence(fout, "trClassDocumentationC",
        theTranslator->trClassDocumentation());

    Config_setBool(false);
    WriteSentence(fout, "trClassDocumentation",
        theTranslator->trClassDocumentation());

    WriteSentence(fout, "trFileDocumentation",
        theTranslator->trFileDocumentation());

    WriteSentence(fout, "trExampleDocumentation",
        theTranslator->trExampleDocumentation());

    WriteSentence(fout, "trPageDocumentation",
        theTranslator->trPageDocumentation());

    WriteSentence(fout, "trReferenceManual",
        theTranslator->trReferenceManual());

    WriteSentence(fout, "trDefines",
        theTranslator->trDefines());

///    WriteSentence(fout, "trFuncProtos",
///        theTranslator->trFuncProtos());

    WriteSentence(fout, "trTypedefs",
        theTranslator->trTypedefs());

    WriteSentence(fout, "trEnumerations",
        theTranslator->trEnumerations());

    WriteSentence(fout, "trFunctions",
        theTranslator->trFunctions());

    WriteSentence(fout, "trVariables",
        theTranslator->trVariables());

    WriteSentence(fout, "trEnumerationValues",
        theTranslator->trEnumerationValues());

    WriteSentence(fout, "trDefineDocumentation",
        theTranslator->trDefineDocumentation());

///    WriteSentence(fout, "trFunctionPrototypeDocumentation",
///        theTranslator->trFunctionPrototypeDocumentation());

    WriteSentence(fout, "trTypedefDocumentation",
        theTranslator->trTypedefDocumentation());

    WriteSentence(fout, "trEnumerationTypeDocumentation",
        theTranslator->trEnumerationTypeDocumentation());

    WriteSentence(fout, "trEnumerationValueDocumentation",
        theTranslator->trEnumerationValueDocumentation());

    WriteSentence(fout, "trFunctionDocumentation",
        theTranslator->trFunctionDocumentation());

    WriteSentence(fout, "trVariableDocumentation",
        theTranslator->trVariableDocumentation());

    Config_setBool(true);
    WriteSentence(fout, "trCompoundsC",
        theTranslator->trCompounds());

    Config_setBool(false);
    WriteSentence(fout, "trCompounds",
        theTranslator->trCompounds());

///    WriteSentence(fout, "trWrittenBy",
///        theTranslator->trWrittenBy());

    WriteSentence(fout, "trForInternalUseOnly",
        theTranslator->trForInternalUseOnly());

///    WriteSentence(fout, "trReimplementedForInternalReasons",
///        theTranslator->trReimplementedForInternalReasons());

    WriteSentence(fout, "trWarning",
        theTranslator->trWarning());

///    WriteSentence(fout, "trBugsAndLimitations",
///        theTranslator->trBugsAndLimitations());

    WriteSentence(fout, "trVersion",
        theTranslator->trVersion());

    WriteSentence(fout, "trDate",
        theTranslator->trDate());

    WriteSentence(fout, "trReturns",
        theTranslator->trReturns());

    WriteSentence(fout, "trSeeAlso",
        theTranslator->trSeeAlso());

    WriteSentence(fout, "trParameters",
        theTranslator->trParameters());

    WriteSentence(fout, "trExceptions",
        theTranslator->trExceptions());

    WriteSentence(fout, "trGeneratedBy",
        theTranslator->trGeneratedBy());

    WriteSentence(fout, "trNamespaceList",
        theTranslator->trNamespaceList());

    WriteSentence(fout, "trFriends",
        theTranslator->trFriends());

    WriteSentence(fout, "trRelatedFunctionDocumentation",
        theTranslator->trRelatedFunctionDocumentation());

    WriteSentence(fout, "trPublicMembers",
        theTranslator->trPublicMembers());

    WriteSentence(fout, "trPublicSlots",
        theTranslator->trPublicSlots());

    WriteSentence(fout, "trSignals",
        theTranslator->trSignals());

    WriteSentence(fout, "trStaticPublicMembers",
        theTranslator->trStaticPublicMembers());

    WriteSentence(fout, "trProtectedMembers",
        theTranslator->trProtectedMembers());

    WriteSentence(fout, "trProtectedSlots",
        theTranslator->trProtectedSlots());

    WriteSentence(fout, "trStaticProtectedMembers",
        theTranslator->trStaticProtectedMembers());

    WriteSentence(fout, "trPrivateMembers",
        theTranslator->trPrivateMembers());

    WriteSentence(fout, "trPrivateSlots",
        theTranslator->trPrivateSlots());

    WriteSentence(fout, "trStaticPrivateMembers",
        theTranslator->trStaticPrivateMembers());

    WriteSentence(fout, "trNamespaceMembers",
        theTranslator->trNamespaceMembers());

    WriteSentence(fout, "trNamespaceIndex",
        theTranslator->trNamespaceIndex());

    WriteSentence(fout, "trNamespaceDocumentation",
        theTranslator->trNamespaceDocumentation());

    WriteSentence(fout, "trNamespaces",
        theTranslator->trNamespaces());

///    WriteSentence(fout, "trAlphabeticalList",
///        theTranslator->trAlphabeticalList());

    WriteSentence(fout, "trReturnValues",
        theTranslator->trReturnValues());

    WriteSentence(fout, "trMainPage",
        theTranslator->trMainPage());

    WriteSentence(fout, "trPageAbbreviation",
        theTranslator->trPageAbbreviation());

///    WriteSentence(fout, "trSources",
///        theTranslator->trSources());

    WriteSentence(fout, "trDeprecated",
        theTranslator->trDeprecated());

    WriteSentence(fout, "trConstructorDocumentation",
        theTranslator->trConstructorDocumentation());

    WriteSentence(fout, "trGotoSourceCode",
        theTranslator->trGotoSourceCode());

    WriteSentence(fout, "trGotoDocumentation",
        theTranslator->trGotoDocumentation());

    WriteSentence(fout, "trPrecondition",
        theTranslator->trPrecondition());

    WriteSentence(fout, "trPostcondition",
        theTranslator->trPostcondition());

    WriteSentence(fout, "trInvariant",
        theTranslator->trInvariant());

    WriteSentence(fout, "trInitialValue",
        theTranslator->trInitialValue());

    WriteSentence(fout, "trCode",
        theTranslator->trCode());

    WriteSentence(fout, "trGraphicalHierarchy",
        theTranslator->trGraphicalHierarchy());

    WriteSentence(fout, "trGotoGraphicalHierarchy",
        theTranslator->trGotoGraphicalHierarchy());

    WriteSentence(fout, "trGotoTextualHierarchy",
        theTranslator->trGotoTextualHierarchy());

    WriteSentence(fout, "trPageIndex",
        theTranslator->trPageIndex());

    WriteSentence(fout, "trNote",
        theTranslator->trNote());

    WriteSentence(fout, "trPublicTypes",
        theTranslator->trPublicTypes());

    Config_setBool(true);
    WriteSentence(fout, "trPublicAttribsC",
        theTranslator->trPublicAttribs());

    Config_setBool(false);
    WriteSentence(fout, "trPublicAttribs",
        theTranslator->trPublicAttribs());

    WriteSentence(fout, "trStaticPublicAttribs",
        theTranslator->trStaticPublicAttribs());

    WriteSentence(fout, "trProtectedTypes",
        theTranslator->trProtectedTypes());

    WriteSentence(fout, "trProtectedAttribs",
        theTranslator->trProtectedAttribs());

    WriteSentence(fout, "trStaticProtectedAttribs",
        theTranslator->trStaticProtectedAttribs());

    WriteSentence(fout, "trPrivateTypes",
        theTranslator->trPrivateTypes());

    WriteSentence(fout, "trPrivateAttribs",
        theTranslator->trPrivateAttribs());

    WriteSentence(fout, "trStaticPrivateAttribs",
        theTranslator->trStaticPrivateAttribs());

    WriteSentence(fout, "trTodo",
        theTranslator->trTodo());

    WriteSentence(fout, "trTodoList",
        theTranslator->trTodoList());

    WriteSentence(fout, "trReferencedBy",
        theTranslator->trReferencedBy());

    WriteSentence(fout, "trRemarks",
        theTranslator->trRemarks());

    WriteSentence(fout, "trAttention",
        theTranslator->trAttention());

    WriteSentence(fout, "trInclByDepGraph",
        theTranslator->trInclByDepGraph());

    WriteSentence(fout, "trSince",
        theTranslator->trSince());

    WriteSentence(fout, "trLegendTitle",
        theTranslator->trLegendTitle());

    WriteSentence(fout, "trLegendDocs",
        theTranslator->trLegendDocs());

    WriteSentence(fout, "trLegend",
        theTranslator->trLegend());

    WriteSentence(fout, "trTest",
        theTranslator->trTest());

    WriteSentence(fout, "trTestList",
        theTranslator->trTestList());

///    WriteSentence(fout, "trDCOPMethods",
///        theTranslator->trDCOPMethods());

    WriteSentence(fout, "trProperties",
        theTranslator->trProperties());

    WriteSentence(fout, "trPropertyDocumentation",
        theTranslator->trPropertyDocumentation());

    WriteSentence(fout, "trInterfaces",
        theTranslator->trInterfaces());

    Config_setBool(true);
    WriteSentence(fout, "trClassesC",
        theTranslator->trClasses());

    Config_setBool(false);
    WriteSentence(fout, "trClasses",
        theTranslator->trClasses());

    WriteSentence(fout, "trPackageList",
        theTranslator->trPackageList());

    WriteSentence(fout, "trPackageListDescription",
        theTranslator->trPackageListDescription());

    WriteSentence(fout, "trPackages",
        theTranslator->trPackages());

///    WriteSentence(fout, "trPackageDocumentation",
///        theTranslator->trPackageDocumentation());

    WriteSentence(fout, "trDefineValue",
        theTranslator->trDefineValue());

    WriteSentence(fout, "trBug",
        theTranslator->trBug());

    WriteSentence(fout, "trBugList",
        theTranslator->trBugList());

    WriteSentence(fout, "trRTFansicp",
        theTranslator->trRTFansicp());

    WriteSentence(fout, "trRTFCharSet",
        theTranslator->trRTFCharSet());

    WriteSentence(fout, "trRTFGeneralIndex",
        theTranslator->trRTFGeneralIndex());


    fout << "\n<!-- Sets of simple sentences -->\n";

    WriteSentence(fout, "trFileListDescriptionF",
        theTranslator->trFileListDescription(false));
    WriteSentence(fout, "trFileListDescriptionT",
        theTranslator->trFileListDescription(true));

    fout << "<!-- -->\n";

    Config_setBool(true);
    WriteSentence(fout, "trCompoundMembersDescriptionFC",
        theTranslator->trCompoundMembersDescription(false));
    WriteSentence(fout, "trCompoundMembersDescriptionTC",
        theTranslator->trCompoundMembersDescription(true));

    Config_setBool(false);
    WriteSentence(fout, "trCompoundMembersDescriptionF",
        theTranslator->trCompoundMembersDescription(false));
    WriteSentence(fout, "trCompoundMembersDescriptionT",
        theTranslator->trCompoundMembersDescription(true));

    fout << "<!-- -->\n";

    Config_setBool(true);
    WriteSentence(fout, "trFileMembersDescriptionFC",
        theTranslator->trFileMembersDescription(false));
    WriteSentence(fout, "trFileMembersDescriptionTC",
        theTranslator->trFileMembersDescription(true));

    Config_setBool(false);
    WriteSentence(fout, "trFileMembersDescriptionF",
        theTranslator->trFileMembersDescription(false));
    WriteSentence(fout, "trFileMembersDescriptionT",
        theTranslator->trFileMembersDescription(true));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trNamespaceListDescriptionF",
        theTranslator->trNamespaceListDescription(false));
    WriteSentence(fout, "trNamespaceListDescriptionT",
        theTranslator->trNamespaceListDescription(true));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trNamespaceMemberDescriptionF",
        theTranslator->trNamespaceMemberDescription(false));
    WriteSentence(fout, "trNamespaceMemberDescriptionT",
        theTranslator->trNamespaceMemberDescription(true));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trclass",   theTranslator->trClass(false, true ));
    WriteSentence(fout, "trclasses", theTranslator->trClass(false, false));
    WriteSentence(fout, "trClass",   theTranslator->trClass(true,  true ));
    WriteSentence(fout, "trClasses", theTranslator->trClass(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trfile",    theTranslator->trFile(false, true ));
    WriteSentence(fout, "trfiles",   theTranslator->trFile(false, false));
    WriteSentence(fout, "trFile",    theTranslator->trFile(true,  true ));
    WriteSentence(fout, "trFiles",   theTranslator->trFile(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trnamespace",  theTranslator->trNamespace(false, true ));
    WriteSentence(fout, "trnamespaces", theTranslator->trNamespace(false, false));
    WriteSentence(fout, "trNamespace",  theTranslator->trNamespace(true,  true ));
    WriteSentence(fout, "trNamespaces", theTranslator->trNamespace(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trgroup",  theTranslator->trGroup(false, true ));
    WriteSentence(fout, "trgroups", theTranslator->trGroup(false, false));
    WriteSentence(fout, "trGroup",  theTranslator->trGroup(true,  true ));
    WriteSentence(fout, "trGroups", theTranslator->trGroup(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trpage",  theTranslator->trPage(false, true ));
    WriteSentence(fout, "trpages", theTranslator->trPage(false, false));
    WriteSentence(fout, "trPage",  theTranslator->trPage(true,  true ));
    WriteSentence(fout, "trPages", theTranslator->trPage(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trmember",  theTranslator->trMember(false, true ));
    WriteSentence(fout, "trmembers", theTranslator->trMember(false, false));
    WriteSentence(fout, "trMember",  theTranslator->trMember(true,  true ));
    WriteSentence(fout, "trMembers", theTranslator->trMember(true,  false));

///    fout << "<!-- -->\n";
///
///    WriteSentence(fout, "trfield",   theTranslator->trField(false, true ));
///    WriteSentence(fout, "trfields",  theTranslator->trField(false, false));
///    WriteSentence(fout, "trField",   theTranslator->trField(true,  true ));
///    WriteSentence(fout, "trFields",  theTranslator->trField(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trglobal",  theTranslator->trGlobal(false, true ));
    WriteSentence(fout, "trglobals", theTranslator->trGlobal(false, false));
    WriteSentence(fout, "trGlobal",  theTranslator->trGlobal(true,  true ));
    WriteSentence(fout, "trGlobals", theTranslator->trGlobal(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trauthor",  theTranslator->trAuthor(false, true ));
    WriteSentence(fout, "trauthors", theTranslator->trAuthor(false, false));
    WriteSentence(fout, "trAuthor",  theTranslator->trAuthor(true,  true ));
    WriteSentence(fout, "trAuthors", theTranslator->trAuthor(true,  false));

    fout << "<!-- -->\n";

    WriteSentence(fout, "trClassDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Class, true));
    WriteSentence(fout, "trClassDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Class, false));

    fout << "\n";

    WriteSentence(fout, "trStructDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Struct, true));
    WriteSentence(fout, "trStructDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Struct, false));

    fout << "\n";

    WriteSentence(fout, "trUnionDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Union, true));
    WriteSentence(fout, "trUnionDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Union, false));

    fout << "\n";

    WriteSentence(fout, "trInterfaceDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Interface, true));

    WriteSentence(fout, "trInterfaceDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Interface, false));

    fout << "\n";

    WriteSentence(fout, "trExceptionDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Exception, true));

    WriteSentence(fout, "trExceptionDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Exception, false));

    fout << "<!-- -->\n";


    fout << "\n------------------------------------------\n\n";

    fout << "\n<!-- Template sentences (or what should be) -->\n\n";

    WriteSentence(fout, "trDefinedAtLineInSourceFile",
        theTranslator->trDefinedAtLineInSourceFile());

    WriteSentence(fout, "trDefinedInSourceFile",
        theTranslator->trDefinedInSourceFile());

    WriteSentence(fout, "trFileReference",
        theTranslator->trFileReference("%1"));

    WriteSentence(fout, "trNamespaceReference",
        theTranslator->trNamespaceReference("%1"));

    WriteSentence(fout, "trCollaborationDiagram",
        theTranslator->trCollaborationDiagram("%1"));

    WriteSentence(fout, "trInclDepGraph",
        theTranslator->trInclDepGraph("%1"));

    WriteSentence(fout, "trPackage",
        theTranslator->trPackage("%1"));


    fout << "\n<!-- Sets of template sentences -->\n\n";

    WriteSentence(fout, "trClassReference",
        theTranslator->trCompoundReference("%1", ClassDef::Class, false));

    WriteSentence(fout, "trClassTemplateReference",
        theTranslator->trCompoundReference("%1", ClassDef::Class, true));

    fout << "\n";

    WriteSentence(fout, "trStructReference",
        theTranslator->trCompoundReference("%1", ClassDef::Struct, false));

    WriteSentence(fout, "trUnionReference",
        theTranslator->trCompoundReference("%1", ClassDef::Union, false));

    WriteSentence(fout, "trInterfaceReference",
        theTranslator->trCompoundReference("%1", ClassDef::Interface, false));

    WriteSentence(fout, "trExceptionReference",
        theTranslator->trCompoundReference("%1", ClassDef::Exception, false));

    fout << "\n<!-- Simple sentences with fixed-name generated-sentence "
            "references inside\n\n";

    WriteSentence(fout, "trGeneratedAutomatically",
        theTranslator->trGeneratedAutomatically("&ProjName;"));

    WriteSentence(fout, "trGeneratedAt",
        theTranslator->trGeneratedAt("&GenDate;", "&ProjName;"));

    fout << "-->\n\n"
            "<!-- ... but they can be also implemented as "
            "template sentences)-->\n\n";

    WriteSentence(fout, "trGeneratedAutomatically",
        theTranslator->trGeneratedAutomatically("%1"));

    WriteSentence(fout, "trGeneratedAt",
        theTranslator->trGeneratedAt("%1", "%2"));

    fout << "\n<!-- Simple fragments that should be converted "
            "to template sentences -->\n\n";

        WriteSentence(fout, "trThisIsTheListOfAllMembers",
        theTranslator->trThisIsTheListOfAllMembers());

    WriteSentence(fout, "trIncludingInheritedMembers",
        theTranslator->trIncludingInheritedMembers());

    fout << "\n<!-- should be converted to something like... -->\n\n";

    WriteSentence(fout, "trThisIsTheListOfAllMembers",
        theTranslator->trThisIsTheListOfAllMembers() + "%1.");

    WriteSentence(fout, "trTheListOfAllMembersIncludingInherited",
        theTranslator->trThisIsTheListOfAllMembers() + "%1"
        + theTranslator->trIncludingInheritedMembers());

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
    WRITE_ELEMENT(trMemberDataDocumentation);
    WRITE_ELEMENT_C(trMemberDataDocumentation);                // C
    WRITE_ELEMENT(trMore);
    WRITE_ELEMENT(trListOfAllMembers);
    WRITE_ELEMENT(trMemberList);
    WRITE_ELEMENT(trThisIsTheListOfAllMembers);
    WRITE_ELEMENT(trIncludingInheritedMembers);
    WRITE_ELEMENT1(trGeneratedAutomatically, "%1");
    WRITE_ELEMENT(trEnumName);
    WRITE_ELEMENT(trEnumValue);
    WRITE_ELEMENT(trDefinedIn);



    // quick reference sections

    WRITE_ELEMENT(trModules);
    WRITE_ELEMENT(trClassHierarchy);

    WRITE_ELEMENT(trCompoundList);
    WRITE_ELEMENT_C(trCompoundList); // C

    WRITE_ELEMENT(trFileList);
    //virtual QCString trHeaderFiles); // C
    WRITE_ELEMENT(trCompoundMembers);

    WRITE_ELEMENT(trFileMembers);
    WRITE_ELEMENT_C(trFileMembers); // C

    WRITE_ELEMENT(trRelatedPages);
    WRITE_ELEMENT(trExamples);
    WRITE_ELEMENT(trSearch);
    WRITE_ELEMENT(trClassHierarchyDescription);

    WRITE_ELEMENT_EXTRACTALL(trFileListDescription);
    // WRITE_ELEMENT_T(trFileListDescription);

    WRITE_ELEMENT(trCompoundListDescription);
    WRITE_ELEMENT_C(trCompoundListDescription); //C

    WRITE_ELEMENT_F(trCompoundMembersDescription);
    WRITE_ELEMENT_T(trCompoundMembersDescription);

    WRITE_ELEMENT_F(trFileMembersDescription);
    WRITE_ELEMENT_T(trFileMembersDescription);
    WRITE_ELEMENT_FC(trFileMembersDescription); // C
    WRITE_ELEMENT_TC(trFileMembersDescription); // C

    //virtual QCString trHeaderFilesDescription);
    WRITE_ELEMENT(trExamplesDescription);
    WRITE_ELEMENT(trRelatedPagesDescription);
    WRITE_ELEMENT(trModulesDescription);
    //virtual QCString trNoDescriptionAvailable);


    // index titles (the project name is prepended for these)

    WRITE_ELEMENT(trDocumentation);
    WRITE_ELEMENT(trModuleIndex);
    WRITE_ELEMENT(trHierarchicalIndex);

	WRITE_ELEMENT(trCompoundIndex);
	WRITE_ELEMENT_C(trCompoundIndex); // C

	WRITE_ELEMENT(trFileIndex);
    WRITE_ELEMENT(trModuleDocumentation);

	WRITE_ELEMENT(trClassDocumentation);
	WRITE_ELEMENT_C(trClassDocumentation); // C

	WRITE_ELEMENT(trFileDocumentation);
    WRITE_ELEMENT(trExampleDocumentation);
    WRITE_ELEMENT(trPageDocumentation);
    WRITE_ELEMENT(trReferenceManual);
    WRITE_ELEMENT(trDefines);
    //virtual QCString trFuncProtos() = 0;
    WRITE_ELEMENT(trTypedefs);
    WRITE_ELEMENT(trEnumerations);
    WRITE_ELEMENT(trFunctions);
    WRITE_ELEMENT(trVariables);
    WRITE_ELEMENT(trEnumerationValues);
    WRITE_ELEMENT(trDefineDocumentation);
    //virtual QCString trFunctionPrototypeDocumentation() = 0;
    WRITE_ELEMENT(trTypedefDocumentation);
    WRITE_ELEMENT(trEnumerationTypeDocumentation);
    WRITE_ELEMENT(trFunctionDocumentation);
    WRITE_ELEMENT(trVariableDocumentation);

	WRITE_ELEMENT(trCompounds);
	WRITE_ELEMENT_C(trCompounds); // C

	WRITE_ELEMENT2(trGeneratedAt, "%1", "%2");

    //virtual QCString trWrittenBy() = 0;

	WRITE_ELEMENT1(trClassDiagram, "%1");

	WRITE_ELEMENT(trForInternalUseOnly);
    //virtual QCString trReimplementedForInternalReasons() = 0;
    WRITE_ELEMENT(trWarning);
    //virtual QCString trBugsAndLimitations() = 0;
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
	
	WRITE_ELEMENT_F(trNamespaceListDescription);
	WRITE_ELEMENT_T(trNamespaceListDescription);
	
	WRITE_ELEMENT(trFriends);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990405
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRelatedFunctionDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990425
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_COMPOUNDTYPE_1_F(trCompoundReference, "%1");
	WRITE_ELEMENT_COMPOUNDTYPE_1_T(trCompoundReference, "%1");

	WRITE_ELEMENT1(trFileReference, "%1");
    WRITE_ELEMENT1(trNamespaceReference, "%1");

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
    WRITE_ELEMENT1INT(trWriteList, 1);
    WRITE_ELEMENT1INT(trInheritsList, 1);
    WRITE_ELEMENT1INT(trInheritedByList, 1);
    WRITE_ELEMENT1INT(trReimplementedFromList, 1);
    WRITE_ELEMENT1INT(trReimplementedInList, 1);
    WRITE_ELEMENT(trNamespaceMembers);

	WRITE_ELEMENT_F(trNamespaceMemberDescription);
	WRITE_ELEMENT_T(trNamespaceMemberDescription);

	WRITE_ELEMENT(trNamespaceIndex);
    WRITE_ELEMENT(trNamespaceDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990522
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNamespaces);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990728
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_COMPOUNDTYPE_F(trGeneratedFromFiles);
	WRITE_ELEMENT_COMPOUNDTYPE_T(trGeneratedFromFiles);
	//virtual QCString trAlphabeticalList() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990901
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReturnValues);
    WRITE_ELEMENT(trMainPage);
    WRITE_ELEMENT(trPageAbbreviation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-991003
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trSources() = 0;
    WRITE_ELEMENT(trDefinedAtLineInSourceFile);
    WRITE_ELEMENT(trDefinedInSourceFile);

	//////////////////////////////////////////////////////////////////////////
    // new since 0.49-991205
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDeprecated);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.0.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trCollaborationDiagram, "%1");
    WRITE_ELEMENT1(trInclDepGraph, "%1");
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

	WRITE_ELEMENT(trPublicAttribs);
	WRITE_ELEMENT_C(trPublicAttribs); // C

	WRITE_ELEMENT(trStaticPublicAttribs);
    WRITE_ELEMENT(trProtectedTypes);
    WRITE_ELEMENT(trProtectedAttribs);
    WRITE_ELEMENT(trStaticProtectedAttribs);
    WRITE_ELEMENT(trPrivateTypes);
    WRITE_ELEMENT(trPrivateAttribs);
    WRITE_ELEMENT(trStaticPrivateAttribs);

    /////////////////////////////////////////////////////////////trClasses/////////////
    // new since 1.1.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trTodo);
    WRITE_ELEMENT(trTodoList);

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
    // new since 1.2.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trTest);
    WRITE_ELEMENT(trTestList);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.1
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trDCOPMethods() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trProperties);
    WRITE_ELEMENT(trPropertyDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.4
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trInterfaces() = 0;

	WRITE_ELEMENT(trClasses);
	WRITE_ELEMENT_C(trClasses); // C


    WRITE_ELEMENT1(trPackage, "%1");
    WRITE_ELEMENT(trPackageList);
    WRITE_ELEMENT(trPackageListDescription);
    WRITE_ELEMENT(trPackages);
    //virtual QCString trPackageDocumentation() = 0;
    WRITE_ELEMENT(trDefineValue);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trBug);
    WRITE_ELEMENT(trBugList);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.6
    //////////////////////////////////////////////////////////////////////////


    /*! Used as ansicpg for RTF file
    *
    * The following table shows the correlation of Charset name, Charset Value and
    * <pre>
    * Codepage number:
    * Charset Name       Charset Value(hex)  Codepage number
    * ------------------------------------------------------
    * DEFAULT_CHARSET           1 (x01)
    * SYMBOL_CHARSET            2 (x02)
    * OEM_CHARSET             255 (xFF)
    * ANSI_CHARSET              0 (x00)            1252
    * RUSSIAN_CHARSET         204 (xCC)            1251
    * EE_CHARSET              238 (xEE)            1250
    * GREEK_CHARSET           161 (xA1)            1253
    * TURKISH_CHARSET         162 (xA2)            1254
    * BALTIC_CHARSET          186 (xBA)            1257
    * HEBREW_CHARSET          177 (xB1)            1255
    * ARABIC _CHARSET         178 (xB2)            1256
    * SHIFTJIS_CHARSET        128 (x80)             932
    * HANGEUL_CHARSET         129 (x81)             949
    * GB2313_CHARSET          134 (x86)             936
    * CHINESEBIG5_CHARSET     136 (x88)             950
    * </pre>
    *
    */
    WRITE_ELEMENT(trRTFansicp);

    /*! Character sets
    *  <pre>
    *   0 — ANSI
    *   1 — Default
    *   2 — Symbol
    *   3 — Invalid
    *  77 — Mac
    * 128 — Shift Jis
    * 129 — Hangul
    * 130 — Johab
    * 134 — GB2312
    * 136 — Big5
    * 161 — Greek
    * 162 — Turkish
    * 163 — Vietnamese
    * 177 — Hebrew
    * 178 — Arabic
    * 179 — Arabic Traditional
    * 180 — Arabic user
    * 181 — Hebrew user
    * 186 — Baltic
    * 204 — Russian
    * 222 — Thai
    * 238 — Eastern European
    * 254 — PC 437
    * 255 — OEM
    * </pre>
    */
    WRITE_ELEMENT(trRTFCharSet);
    WRITE_ELEMENT(trRTFGeneralIndex);

    // Translation of the word

    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trClass);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trFile);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trNamespace);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trGroup);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trPage);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trMember);
    //virtual QCString trField(bool first_capital, bool singular) = 0;
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

    WRITE_ELEMENT1INT(trImplementedFromList, 1);
    WRITE_ELEMENT1INT(trImplementedInList, 1);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.16
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRTFTableOfContents);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.17
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDeprecatedList);

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

    //virtual QCString trSearchForIndex);
    WRITE_ELEMENT(trSearchResultsTitle);
    WRITE_ELEMENT1INT(trSearchResults, 1);
    WRITE_ELEMENT(trSearchMatches);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.8
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT1REF(trSourceFile, "%1");

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.9
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDirIndex);
    WRITE_ELEMENT(trDirDocumentation);
    WRITE_ELEMENT(trDirectories);
    WRITE_ELEMENT(trDirDescription);
    WRITE_ELEMENT1(trDirReference, "%1");
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trDir);

#if 0
	//////////////////////////////////////////////////////////////////////////
    // new since 1.4.1
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trOverloadText() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.4.6
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCallerGraph() = 0;
    WRITE_ELEMENT(trEnumerationValueDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.5.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trMemberFunctionDocumentationFortran() = 0;
    WRITE_ELEMENT(trCompoundListFortran() = 0;
    WRITE_ELEMENT(trCompoundMembersFortran() = 0;
    WRITE_ELEMENT(trCompoundListDescriptionFortran() = 0;
    WRITE_ELEMENT(trCompoundMembersDescriptionFortran(bool extractAll) = 0; // F, T, FC, TC
    WRITE_ELEMENT(trCompoundIndexFortran() = 0;
    WRITE_ELEMENT(trTypeDocumentation() = 0;
    WRITE_ELEMENT(trSubprograms() = 0;
    WRITE_ELEMENT(trSubprogramDocumentation() = 0;
    WRITE_ELEMENT(trDataTypes() = 0;
    WRITE_ELEMENT(trModulesList() = 0;
    WRITE_ELEMENT(trModulesListDescription(bool extractAll) = 0;
    WRITE_ELEMENT(trCompoundReferenceFortran(const char *clName,
        ClassDef::CompoundType compType,
        bool isTemplate) = 0;
    WRITE_ELEMENT(trModuleReference(const char *namespaceName) = 0;
    WRITE_ELEMENT(trModulesMembers() = 0;
    WRITE_ELEMENT(trModulesMemberDescription(bool extractAll) = 0;
    WRITE_ELEMENT(trModulesIndex() = 0;
    WRITE_ELEMENT(trModule(bool first_capital, bool singular) = 0;
    WRITE_ELEMENT(trGeneratedFromFilesFortran(ClassDef::CompoundType compType,
        bool single) = 0;
    WRITE_ELEMENT(trType(bool first_capital, bool singular) = 0;
    WRITE_ELEMENT(trSubprogram(bool first_capital, bool singular) = 0;
    WRITE_ELEMENT(trTypeConstraints() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDirRelation(const char *name) = 0;
    WRITE_ELEMENT(trLoading() = 0;
    WRITE_ELEMENT(trGlobalNamespace() = 0;
    WRITE_ELEMENT(trSearching() = 0;
    WRITE_ELEMENT(trNoMatches() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.3
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trDirDependency(const char *name) = 0;
    WRITE_ELEMENT(trFileIn(const char *name) = 0;
    WRITE_ELEMENT(trIncludesFileIn(const char *name) = 0;
    WRITE_ELEMENT(trDateTime(int year, int month, int day, int dayOfWeek,
        int hour, int minutes, int seconds, trFileMembersDescription
        bool includeTime) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.7.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCiteReferences() = 0;
    WRITE_ELEMENT(trCopyright() = 0;
    WRITE_ELEMENT(trDirDepGraph(const char *name) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDetailLevel() = 0;
    WRITE_ELEMENT(trTemplateParameters() = 0;
    WRITE_ELEMENT(trAndMore(const QCString &number) = 0;
    WRITE_ELEMENT(trEnumGeneratedFromFiles(bool single) = 0;
    WRITE_ELEMENT(trEnumReference(const char *name) = 0;
    WRITE_ELEMENT(trInheritedFrom(const char *members, const char *what) = 0;
    WRITE_ELEMENT(trAdditionalInheritedMembers() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trPanelSynchronisationTooltip(bool enable) = 0;
    WRITE_ELEMENT(trProvidedByCategory() = 0;
    WRITE_ELEMENT(trExtendsClass() = 0;
    WRITE_ELEMENT(trClassMethods() = 0;
    WRITE_ELEMENT(trInstanceMethods() = 0;
    WRITE_ELEMENT(trMethodDocumentation() = 0;
    WRITE_ELEMENT(trDesignOverview() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trInterfaces() = 0;
    WRITE_ELEMENT(trServices() = 0;
    WRITE_ELEMENT(trConstantGroups() = 0;
    WRITE_ELEMENT(trConstantGroupReference(const char *namespaceName) = 0;
    WRITE_ELEMENT(trServiceReference(const char *sName) = 0;
    WRITE_ELEMENT(trSingletonReference(const char *sName) = 0;
    WRITE_ELEMENT(trServiceGeneratedFromFiles(bool single) = 0;
    WRITE_ELEMENT(trSingletonGeneratedFromFiles(bool single) = 0;

#endif

    fout << "\n<!-- (end) -->\n";

    fout << "</context>\n";

    // Close the output file.
    //
    fout.close();

    std::cerr << "\n";

}


int main()
{
	GenerateTranslatorSentences("english");
	GenerateTranslatorSentences("german");
	GenerateTranslatorSentences("czech");
	GenerateTranslatorSentences("dutch");

    /// GenerateTranslatorSentences("afrikaans");
    /// GenerateTranslatorSentences("arabic");
    /// GenerateTranslatorSentences("armenian");
    /// GenerateTranslatorSentences("brazilian");
    /// GenerateTranslatorSentences("catalan");
    /// GenerateTranslatorSentences("chinese");
    /// GenerateTranslatorSentences("chinese-traditional");
    /// GenerateTranslatorSentences("croatian");
    /// GenerateTranslatorSentences("czech");
    /// GenerateTranslatorSentences("danish");
    /// GenerateTranslatorSentences("dutch");
    /// GenerateTranslatorSentences("english");
    /// GenerateTranslatorSentences("esperanto");
    /// GenerateTranslatorSentences("finnish");
    /// GenerateTranslatorSentences("french");
    /// GenerateTranslatorSentences("german");
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
