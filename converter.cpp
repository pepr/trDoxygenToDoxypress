#include <fstream>
#include <iostream>
#include <string>

#include "xxx.h"
#include "language.h"
#include "translator_en.h"

using namespace std;


///void WriteSentence(ofstream & fout,
///                   const string & SentenceId,
///                   const string & SentenceBody)
///{   
///    // Sentence beginning
///    fout << "<sentence id=\"" << SentenceId << "\">";
///    
///    // Now output the body.
///    fout << SentenceBody;
///    
///    // Close the definition.
///    fout << "</sentence>\n";      
///}

#define WRITE_ELEMENT(SentenceId)\
{ \
    fout << "    <message method=\"" #SentenceId "\">\n" \
            "        <source>" << trEn.SentenceId() << "</source>\n" \
            "        <translation>" << theTranslator->SentenceId() << "</translation>\n" \
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


//////////////////////////////////////////
// --- Language control methods -------------------

    WRITE_ELEMENT(idLanguage);
#if 0
    virtual QCString idLanguage() = 0;
    virtual QCString latexLanguageSupportCommand() = 0;

    // --- Language translation methods -------------------

    virtual QCString trRelatedFunctions() = 0;
    virtual QCString trRelatedSubscript() = 0;
    virtual QCString trDetailedDescription() = 0;
    virtual QCString trMemberTypedefDocumentation() = 0;
    virtual QCString trMemberEnumerationDocumentation() = 0;
    virtual QCString trMemberFunctionDocumentation() = 0;
    virtual QCString trMemberDataDocumentation() = 0;
    virtual QCString trMore() = 0;
    virtual QCString trListOfAllMembers() = 0;
    virtual QCString trMemberList() = 0;
    virtual QCString trThisIsTheListOfAllMembers() = 0;
    virtual QCString trIncludingInheritedMembers() = 0;
    virtual QCString trGeneratedAutomatically(const char *s) = 0;
    virtual QCString trEnumName() = 0;
    virtual QCString trEnumValue() = 0;
    virtual QCString trDefinedIn() = 0;

    // quick reference sections

    virtual QCString trModules() = 0;
    virtual QCString trClassHierarchy() = 0;
    virtual QCString trCompoundList() = 0;
    virtual QCString trFileList() = 0;
    //virtual QCString trHeaderFiles() = 0;
    virtual QCString trCompoundMembers() = 0;
    virtual QCString trFileMembers() = 0;
    virtual QCString trRelatedPages() = 0;
    virtual QCString trExamples() = 0;
    virtual QCString trSearch() = 0;
    virtual QCString trClassHierarchyDescription() = 0;
    virtual QCString trFileListDescription(bool extractAll) = 0;
    virtual QCString trCompoundListDescription() = 0;
    virtual QCString trCompoundMembersDescription(bool extractAll) = 0;
    virtual QCString trFileMembersDescription(bool extractAll) = 0;
    //virtual QCString trHeaderFilesDescription() = 0;
    virtual QCString trExamplesDescription() = 0;
    virtual QCString trRelatedPagesDescription() = 0;
    virtual QCString trModulesDescription() = 0;
    //virtual QCString trNoDescriptionAvailable() = 0;

    // index titles (the project name is prepended for these)

    virtual QCString trDocumentation() = 0;
    virtual QCString trModuleIndex() = 0;
    virtual QCString trHierarchicalIndex() = 0;
    virtual QCString trCompoundIndex() = 0;
    virtual QCString trFileIndex() = 0;
    virtual QCString trModuleDocumentation() = 0;
    virtual QCString trClassDocumentation() = 0;
    virtual QCString trFileDocumentation() = 0;
    virtual QCString trExampleDocumentation() = 0;
    virtual QCString trPageDocumentation() = 0;
    virtual QCString trReferenceManual() = 0;
    virtual QCString trDefines() = 0;
    //virtual QCString trFuncProtos() = 0;
    virtual QCString trTypedefs() = 0;
    virtual QCString trEnumerations() = 0;
    virtual QCString trFunctions() = 0;
    virtual QCString trVariables() = 0;
    virtual QCString trEnumerationValues() = 0;
    virtual QCString trDefineDocumentation() = 0;
    //virtual QCString trFunctionPrototypeDocumentation() = 0;
    virtual QCString trTypedefDocumentation() = 0;
    virtual QCString trEnumerationTypeDocumentation() = 0;
    virtual QCString trFunctionDocumentation() = 0;
    virtual QCString trVariableDocumentation() = 0;
    virtual QCString trCompounds() = 0;
    virtual QCString trGeneratedAt(const char *date, const char *projName) = 0;
    //virtual QCString trWrittenBy() = 0;
    virtual QCString trClassDiagram(const char *clName) = 0;
    virtual QCString trForInternalUseOnly() = 0;
    //virtual QCString trReimplementedForInternalReasons() = 0;
    virtual QCString trWarning() = 0;
    //virtual QCString trBugsAndLimitations() = 0;
    virtual QCString trVersion() = 0;
    virtual QCString trDate() = 0;
    virtual QCString trReturns() = 0;
    virtual QCString trSeeAlso() = 0;
    virtual QCString trParameters() = 0;
    virtual QCString trExceptions() = 0;
    virtual QCString trGeneratedBy() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990307
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trNamespaceList() = 0;
    virtual QCString trNamespaceListDescription(bool extractAll) = 0;
    virtual QCString trFriends() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990405
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trRelatedFunctionDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990425
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trCompoundReference(const char *clName,
        ClassDef::CompoundType compType,
        bool isTemplate) = 0;

    virtual QCString trFileReference(const char *fileName) = 0;
    virtual QCString trNamespaceReference(const char *namespaceName) = 0;

    virtual QCString trPublicMembers() = 0;
    virtual QCString trPublicSlots() = 0;
    virtual QCString trSignals() = 0;
    virtual QCString trStaticPublicMembers() = 0;
    virtual QCString trProtectedMembers() = 0;
    virtual QCString trProtectedSlots() = 0;
    virtual QCString trStaticProtectedMembers() = 0;
    virtual QCString trPrivateMembers() = 0;
    virtual QCString trPrivateSlots() = 0;
    virtual QCString trStaticPrivateMembers() = 0;
    virtual QCString trWriteList(int numEntries) = 0;
    virtual QCString trInheritsList(int numEntries) = 0;
    virtual QCString trInheritedByList(int numEntries) = 0;
    virtual QCString trReimplementedFromList(int numEntries) = 0;
    virtual QCString trReimplementedInList(int numEntries) = 0;
    virtual QCString trNamespaceMembers() = 0;
    virtual QCString trNamespaceMemberDescription(bool extractAll) = 0;
    virtual QCString trNamespaceIndex() = 0;
    virtual QCString trNamespaceDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990522
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trNamespaces() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990728
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trGeneratedFromFiles(ClassDef::CompoundType compType,
        bool single) = 0;
    //virtual QCString trAlphabeticalList() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990901
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trReturnValues() = 0;
    virtual QCString trMainPage() = 0;
    virtual QCString trPageAbbreviation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-991003
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trSources() = 0;
    virtual QCString trDefinedAtLineInSourceFile() = 0;
    virtual QCString trDefinedInSourceFile() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-991205
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trDeprecated() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.0.0
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trCollaborationDiagram(const char *clName) = 0;
    virtual QCString trInclDepGraph(const char *fName) = 0;
    virtual QCString trConstructorDocumentation() = 0;
    virtual QCString trGotoSourceCode() = 0;
    virtual QCString trGotoDocumentation() = 0;
    virtual QCString trPrecondition() = 0;
    virtual QCString trPostcondition() = 0;
    virtual QCString trInvariant() = 0;
    virtual QCString trInitialValue() = 0;
    virtual QCString trCode() = 0;

    virtual QCString trGraphicalHierarchy() = 0;
    virtual QCString trGotoGraphicalHierarchy() = 0;
    virtual QCString trGotoTextualHierarchy() = 0;
    virtual QCString trPageIndex() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.0
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trNote() = 0;
    virtual QCString trPublicTypes() = 0;
    virtual QCString trPublicAttribs() = 0;
    virtual QCString trStaticPublicAttribs() = 0;
    virtual QCString trProtectedTypes() = 0;
    virtual QCString trProtectedAttribs() = 0;
    virtual QCString trStaticProtectedAttribs() = 0;
    virtual QCString trPrivateTypes() = 0;
    virtual QCString trPrivateAttribs() = 0;
    virtual QCString trStaticPrivateAttribs() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.3
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trTodo() = 0;
    virtual QCString trTodoList() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.4
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trReferencedBy() = 0;
    virtual QCString trRemarks() = 0;
    virtual QCString trAttention() = 0;
    virtual QCString trInclByDepGraph() = 0;
    virtual QCString trSince() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.5
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trLegendTitle() = 0;
    virtual QCString trLegendDocs() = 0;
    virtual QCString trLegend() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.0
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trTest() = 0;
    virtual QCString trTestList() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.1
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trDCOPMethods() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.2
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trProperties() = 0;
    virtual QCString trPropertyDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.4
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trInterfaces() = 0;
    virtual QCString trClasses() = 0;
    virtual QCString trPackage(const char *name) = 0;
    virtual QCString trPackageList() = 0;
    virtual QCString trPackageListDescription() = 0;
    virtual QCString trPackages() = 0;
    //virtual QCString trPackageDocumentation() = 0;
    virtual QCString trDefineValue() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.5
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trBug() = 0;
    virtual QCString trBugList() = 0;

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
    virtual QCString trRTFansicp() = 0;

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
    virtual QCString trRTFCharSet() = 0;
    virtual QCString trRTFGeneralIndex() = 0;

    // Translation of the word

    virtual QCString trClass(bool first_capital, bool singular) = 0;
    virtual QCString trFile(bool first_capital, bool singular) = 0;
    virtual QCString trNamespace(bool first_capital, bool singular) = 0;
    virtual QCString trGroup(bool first_capital, bool singular) = 0;
    virtual QCString trPage(bool first_capital, bool singular) = 0;
    virtual QCString trMember(bool first_capital, bool singular) = 0;
    //virtual QCString trField(bool first_capital, bool singular) = 0;
    virtual QCString trGlobal(bool first_capital, bool singular) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.7
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trAuthor(bool first_capital, bool singular) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.11
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trReferences() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.13
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trImplementedFromList(int numEntries) = 0;
    virtual QCString trImplementedInList(int numEntries) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.16
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trRTFTableOfContents() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.17
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trDeprecatedList() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.18
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trEvents() = 0;
    virtual QCString trEventDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trPackageTypes() = 0;
    virtual QCString trPackageMembers() = 0;
    virtual QCString trStaticPackageMembers() = 0;
    virtual QCString trPackageAttribs() = 0;
    virtual QCString trStaticPackageAttribs() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.1
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trAll() = 0;
    virtual QCString trCallGraph() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.3
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trSearchForIndex() = 0;
    virtual QCString trSearchResultsTitle() = 0;
    virtual QCString trSearchResults(int numDocuments) = 0;
    virtual QCString trSearchMatches() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.8
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trSourceFile(QCString& filename) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.9
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trDirIndex() = 0;
    virtual QCString trDirDocumentation() = 0;
    virtual QCString trDirectories() = 0;
    virtual QCString trDirDescription() = 0;
    virtual QCString trDirReference(const char *dirName) = 0;
    virtual QCString trDir(bool first_capital, bool singular) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.4.1
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trOverloadText() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.4.6
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trCallerGraph() = 0;
    virtual QCString trEnumerationValueDocumentation() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.5.4
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trMemberFunctionDocumentationFortran() = 0;
    virtual QCString trCompoundListFortran() = 0;
    virtual QCString trCompoundMembersFortran() = 0;
    virtual QCString trCompoundListDescriptionFortran() = 0;
    virtual QCString trCompoundMembersDescriptionFortran(bool extractAll) = 0;
    virtual QCString trCompoundIndexFortran() = 0;
    virtual QCString trTypeDocumentation() = 0;
    virtual QCString trSubprograms() = 0;
    virtual QCString trSubprogramDocumentation() = 0;
    virtual QCString trDataTypes() = 0;
    virtual QCString trModulesList() = 0;
    virtual QCString trModulesListDescription(bool extractAll) = 0;
    virtual QCString trCompoundReferenceFortran(const char *clName,
        ClassDef::CompoundType compType,
        bool isTemplate) = 0;
    virtual QCString trModuleReference(const char *namespaceName) = 0;
    virtual QCString trModulesMembers() = 0;
    virtual QCString trModulesMemberDescription(bool extractAll) = 0;
    virtual QCString trModulesIndex() = 0;
    virtual QCString trModule(bool first_capital, bool singular) = 0;
    virtual QCString trGeneratedFromFilesFortran(ClassDef::CompoundType compType,
        bool single) = 0;
    virtual QCString trType(bool first_capital, bool singular) = 0;
    virtual QCString trSubprogram(bool first_capital, bool singular) = 0;
    virtual QCString trTypeConstraints() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.0
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trDirRelation(const char *name) = 0;
    virtual QCString trLoading() = 0;
    virtual QCString trGlobalNamespace() = 0;
    virtual QCString trSearching() = 0;
    virtual QCString trNoMatches() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.3
    //////////////////////////////////////////////////////////////////////////

    //virtual QCString trDirDependency(const char *name) = 0;
    virtual QCString trFileIn(const char *name) = 0;
    virtual QCString trIncludesFileIn(const char *name) = 0;
    virtual QCString trDateTime(int year, int month, int day, int dayOfWeek,
        int hour, int minutes, int seconds,
        bool includeTime) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.7.5
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trCiteReferences() = 0;
    virtual QCString trCopyright() = 0;
    virtual QCString trDirDepGraph(const char *name) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.0
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trDetailLevel() = 0;
    virtual QCString trTemplateParameters() = 0;
    virtual QCString trAndMore(const QCString &number) = 0;
    virtual QCString trEnumGeneratedFromFiles(bool single) = 0;
    virtual QCString trEnumReference(const char *name) = 0;
    virtual QCString trInheritedFrom(const char *members, const char *what) = 0;
    virtual QCString trAdditionalInheritedMembers() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.2
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trPanelSynchronisationTooltip(bool enable) = 0;
    virtual QCString trProvidedByCategory() = 0;
    virtual QCString trExtendsClass() = 0;
    virtual QCString trClassMethods() = 0;
    virtual QCString trInstanceMethods() = 0;
    virtual QCString trMethodDocumentation() = 0;
    virtual QCString trDesignOverview() = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.4
    //////////////////////////////////////////////////////////////////////////

    virtual QCString trInterfaces() = 0;
    virtual QCString trServices() = 0;
    virtual QCString trConstantGroups() = 0;
    virtual QCString trConstantGroupReference(const char *namespaceName) = 0;
    virtual QCString trServiceReference(const char *sName) = 0;
    virtual QCString trSingletonReference(const char *sName) = 0;
    virtual QCString trServiceGeneratedFromFiles(bool single) = 0;
    virtual QCString trSingletonGeneratedFromFiles(bool single) = 0;

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
